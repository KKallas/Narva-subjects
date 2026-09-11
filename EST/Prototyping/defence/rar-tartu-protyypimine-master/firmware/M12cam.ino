/*
  AtomS3R-M12 dual-mode blob detector (Arduino IDE)

  What it does
  ------------
  1) TUNING MODE
     - Wi-Fi + simple web UI
     - JPEG preview snapshots at /jpg
     - optional MJPEG stream at /stream
     - threshold mask at /mask.bmp
     - sample target color from center patch
     - save thresholds/mode in NVS (Preferences)
     - reboot into run mode from web UI, USB serial, or RobotSerial UART

  2) RUN MODE
     - no Wi-Fi
     - JPEG detection path as configured
     - blob detection every frame
     - prints FPS + LEFT/CENTER/RIGHT over USB Serial
     - sends robot-control lines over RobotSerial UART to the motor-controller Atom/Pico
     - accepts commands over RobotSerial UART, e.g. "mode tune"

  USB Serial commands and RobotSerial commands
  --------------------------------------------
  help
  status
  sample
  clear
  th <r> <g> <b>
  sat <n>
  step <n>
  minpix <n>
  roi <percent_from_top_to_start_scanning>   e.g. roi 35
  every <n>                                  tuning-mode detection every nth preview frame
  bands <leftPercent> <rightPercent>         e.g. bands 40 60
  save
  mode tune
  mode run
  reboot

  RobotSerial wiring
  ------------------
  Assumption:
    M12 G1 = GPIO1 = camera TX -> Pico RX
    M12 G2 = GPIO2 = camera RX <- Pico TX

  If your board labels map differently, only change ROBOT_UART_TX_PIN and ROBOT_UART_RX_PIN.
*/

#ifndef _M5_ATOM_S3R_CAM_H_
#define _M5_ATOM_S3R_CAM_H_

#define PWDN_GPIO_NUM   -1
#define RESET_GPIO_NUM  -1
#define XCLK_GPIO_NUM   21
#define SIOD_GPIO_NUM   12
#define SIOC_GPIO_NUM   9

#define Y9_GPIO_NUM     13
#define Y8_GPIO_NUM     11
#define Y7_GPIO_NUM     17
#define Y6_GPIO_NUM     4
#define Y5_GPIO_NUM     48
#define Y4_GPIO_NUM     46
#define Y3_GPIO_NUM     42
#define Y2_GPIO_NUM     3

#define VSYNC_GPIO_NUM  10
#define HREF_GPIO_NUM   14
#define PCLK_GPIO_NUM   40

#define POWER_GPIO_NUM  18

#endif

#include <WiFi.h>
#include <Preferences.h>
#include "esp_camera.h"
#include "img_converters.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"

// ---------------- Wi-Fi ----------------
// Fill in your real Wi-Fi if you want STA mode.
// If STA fails, camera falls back to AP mode.
const char* STA_SSID = "";
const char* STA_PASS = "";

const char* AP_SSID  = "AtomS3R-M12";
const char* AP_PASS  = "12345678";

static const bool PREFER_STA = true;

// ---------------- Mode / camera choices ----------------
enum BootMode : uint8_t {
  MODE_TUNING = 0,
  MODE_RUN    = 1
};

enum DirCode : uint8_t {
  DIR_NONE   = 0,
  DIR_LEFT   = 1,
  DIR_CENTER = 2,
  DIR_RIGHT  = 3
};

// Tuning mode resolution / quality.
static const framesize_t TUNE_FRAME_SIZE   = FRAMESIZE_HVGA;
static const int         TUNE_JPEG_QUALITY = 10;  // lower = better JPEG quality

// Run mode resolution.
static const framesize_t RUN_FRAME_SIZE = FRAMESIZE_HVGA;

static const uint32_t BOOT_OVERRIDE_MS       = 3000;
static const uint32_t RUN_BLOB_PRINT_MS      = 120;
static const uint16_t MASK_DOWNSAMPLE        = 4;
static const char*    PREF_NAMESPACE         = "blobcfg";

// ---------------- Robot UART output/input ----------------
// 2-way UART between M12 camera and motor-controller Atom/Pico.
//
// Wiring:
//   M12 G1 / GPIO1 / TX  ->  Pico RX
//   M12 G2 / GPIO2 / RX  <-  Pico TX
//   M12 GND              ->  Pico GND
//
// Output format to Pico:
//   BLOB dir=LEFT cx=123 cy=210 count=456 area1000=12 bbox=(10,20)-(30,40)
//   NONE
//
// Input commands from Pico:
//   mode tune
//   mode run
//   reboot
//   sample
//   save
//   etc.
static const bool     ROBOT_UART_ENABLED = true;
static const int      ROBOT_UART_TX_PIN  = 1;       // M12 G1 -> Pico RX
static const int      ROBOT_UART_RX_PIN  = 2;       // M12 G2 <- Pico TX
static const uint32_t ROBOT_UART_BAUD    = 115200;

HardwareSerial RobotSerial(1);
String gRobotSerialLine;

// ---------------- Web ----------------
WiFiServer gServer(80);
IPAddress  gWebIP;
bool       gWifiStarted = false;

#define PART_BOUNDARY "123456789000000000000987654321"
static const char* STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char* STREAM_BOUNDARY     = "\r\n--" PART_BOUNDARY "\r\n";
static const char* STREAM_PART         = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";

// ---------------- Persistent config ----------------
struct PersistedConfig {
  uint8_t mode;               // MODE_TUNING / MODE_RUN
  uint8_t targetValid;        // 0 / 1
  uint8_t targetNr;
  uint8_t targetNg;
  uint8_t targetNb;

  uint8_t thrR;
  uint8_t thrG;
  uint8_t thrB;
  uint8_t minSat;
  uint8_t scanStep;

  uint16_t minBlobPixels;
  uint16_t scanStartYPermille;  // 0..1000
  uint8_t detectEveryN;         // tuning preview detect cadence
  uint8_t leftPct;              // left band edge in %
  uint8_t rightPct;             // right band edge in %
};

struct BlobInfo {
  bool found;
  int  cx;
  int  cy;
  int  count;
  int  area1000;
  int  minX;
  int  minY;
  int  maxX;
  int  maxY;
  int  imgW;
  int  imgH;
  DirCode dir;
  uint32_t ms;
};

Preferences gPrefs;
PersistedConfig gCfg;
BootMode gMode = MODE_TUNING;
BlobInfo gLastBlob;

String gSerialLine;
bool   gPendingSample = false;

// RGB buffer used when converting JPEG -> RGB888
uint8_t* gRgbBuf    = nullptr;
size_t   gRgbBufLen = 0;

// FPS / stats
uint32_t gTunePreviewFrames   = 0;
uint32_t gTunePreviewStartMs  = 0;
uint32_t gRunFrames           = 0;
uint32_t gRunStartMs          = 0;
uint32_t gTuneDetectCounter   = 0;
uint32_t gLastRunBlobPrintMs  = 0;

// ---------------- Forward declarations ----------------
void setDefaults();
void clampConfig();
void loadConfig();
void saveConfig();
void clearTarget();

const char* modeName(BootMode m);
const char* dirName(DirCode d);

void printHelp();
void printStatusToSerial();

void initRobotUart();
void robotWriteLine(const String& line);
void robotSendBlobLine(const BlobInfo& blob);
void robotSendNoneLine();
void pollRobotUartCommands();

void pollSerialCommands();
void handleSerialLine(String line);
BootMode chooseModeAtBoot();
void switchModeAndReboot(BootMode nextMode);

camera_config_t buildCameraConfig(BootMode mode);
bool initCameraForMode(BootMode mode);
void applySensorTuning(BootMode mode);

bool startWifiForTuning();
String ipToString();

bool ensureRgbBuffer(int w, int h);

static inline void rgbToNorm(uint8_t r, uint8_t g, uint8_t b,
                             uint8_t& nr, uint8_t& ng, uint8_t& nb, int& sat);
static inline void rgb565To888(uint16_t px, uint8_t& r, uint8_t& g, uint8_t& b);
static inline bool matchPixelNorm(uint8_t nr, uint8_t ng, uint8_t nb, int sat);

bool sampleCenterRGB888(const uint8_t* rgb, int w, int h);
bool sampleCenterRGB565(const uint16_t* px, int w, int h);

BlobInfo detectBlobRGB888(const uint8_t* rgb, int w, int h);
BlobInfo detectBlobRGB565(const uint16_t* px, int w, int h);
void updateLastBlob(const BlobInfo& blob);

bool processJpegFrame(camera_fb_t* fb, bool doSample, bool doDetect);
void noteTunePreviewFrame(size_t bytes);
void noteRunFrame();

void loopTuning();
void loopRun();

void handleHttpClient();
void serveRoot(WiFiClient& client);
void serveStatusJson(WiFiClient& client);
void serveSetQuery(WiFiClient& client, const String& query);
void serveSave(WiFiClient& client);
void serveSample(WiFiClient& client);
void serveClear(WiFiClient& client);
void serveSetMode(WiFiClient& client, const String& query);
void serveJpegSnapshot(WiFiClient& client);
void serveMaskBmp(WiFiClient& client);
void serveMjpegStream(WiFiClient& client);
void serve404(WiFiClient& client);

void sendText(WiFiClient& client, const char* status, const char* contentType, const String& body);
void sendBinaryHeader(WiFiClient& client, const char* status, const char* contentType, size_t length);
String getQueryValue(const String& query, const String& key);
bool getQueryInt(const String& query, const String& key, int& out);

void writeLE16(WiFiClient& client, uint16_t v);
void writeLE32(WiFiClient& client, uint32_t v);

// ---------------- HTML UI ----------------
static const char MAIN_PAGE[] PROGMEM = R"HTML(
<!doctype html>
<html>
<head>
  <meta charset="utf-8">
  <title>AtomS3R-M12 Blob Tuning</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial, sans-serif; margin: 16px; background: #111; color: #eee; }
    h1 { margin: 0 0 12px 0; }
    .row { display: flex; flex-wrap: wrap; gap: 16px; align-items: flex-start; }
    .card { background: #1b1b1b; padding: 12px; border-radius: 10px; border: 1px solid #333; }
    img { background: #000; border: 1px solid #444; border-radius: 6px; max-width: 100%; height: auto; }
    input { width: 90px; margin: 3px; }
    button, a.btn {
      display: inline-block; background: #2b5cff; color: white; text-decoration: none;
      border: none; padding: 8px 12px; border-radius: 8px; margin: 4px 4px 4px 0; cursor: pointer;
    }
    button.alt, a.btn.alt { background: #444; }
    button.warn { background: #d46a00; }
    button.good { background: #1f8b4c; }
    pre { white-space: pre-wrap; word-break: break-word; }
    .small { color: #aaa; font-size: 0.9em; }
    .field { margin-bottom: 8px; }
  </style>
</head>
<body>
  <h1>AtomS3R-M12 Blob Tuning</h1>
  <div class="small">
    Main page uses repeated snapshots so controls stay responsive. Optional MJPEG stream:
    <a class="btn alt" href="/stream" target="_blank">Open /stream</a>
  </div>

  <div class="row" style="margin-top:12px;">
    <div class="card">
      <div><b>Preview</b></div>
      <img id="cam" src="/jpg" width="640">
      <div class="small">JPEG preview</div>
    </div>

    <div class="card">
      <div><b>Mask</b></div>
      <img id="mask" src="/mask.bmp" width="320">
      <div class="small">Green = threshold match, blue = left/right bands, red = ROI start</div>
    </div>
  </div>

  <div class="row" style="margin-top:16px;">
    <div class="card">
      <div class="field"><b>Threshold / scan</b></div>
      <div>
        thrR <input id="thrR" type="number" min="0" max="255">
        thrG <input id="thrG" type="number" min="0" max="255">
        thrB <input id="thrB" type="number" min="0" max="255">
      </div>
      <div>
        sat <input id="minSat" type="number" min="0" max="255">
        step <input id="scanStep" type="number" min="1" max="12">
        minpix <input id="minBlobPixels" type="number" min="1" max="5000">
      </div>
      <div>
        roi% <input id="roiPct" type="number" min="0" max="90">
        every <input id="detectEveryN" type="number" min="1" max="10">
      </div>
      <div>
        left% <input id="leftPct" type="number" min="0" max="90">
        right% <input id="rightPct" type="number" min="10" max="100">
      </div>
      <div style="margin-top:10px;">
        <button onclick="applyCfg()">Apply</button>
        <button class="good" onclick="saveCfg()">Save</button>
        <button class="alt" onclick="sampleTarget()">Sample center</button>
        <button class="warn" onclick="clearTarget()">Clear target</button>
      </div>
      <div style="margin-top:8px;">
        <button class="warn" onclick="bootRun()">Save + reboot to RUN</button>
      </div>
    </div>

    <div class="card" style="min-width:320px;">
      <div><b>Status</b></div>
      <pre id="statusBox">Loading...</pre>
    </div>
  </div>

<script>
let bootLoaded = false;

function byId(id) { return document.getElementById(id); }

async function getStatus() {
  try {
    const r = await fetch('/status');
    const s = await r.json();

    if (!bootLoaded) {
      byId('thrR').value = s.thrR;
      byId('thrG').value = s.thrG;
      byId('thrB').value = s.thrB;
      byId('minSat').value = s.minSat;
      byId('scanStep').value = s.scanStep;
      byId('minBlobPixels').value = s.minBlobPixels;
      byId('roiPct').value = s.roiPct;
      byId('detectEveryN').value = s.detectEveryN;
      byId('leftPct').value = s.leftPct;
      byId('rightPct').value = s.rightPct;
      bootLoaded = true;
    }

    const blobLine = s.blobFound
      ? `FOUND dir=${s.dir} cx=${s.cx} cy=${s.cy} area1000=${s.area1000} count=${s.count} bbox=(${s.minX},${s.minY})-(${s.maxX},${s.maxY})`
      : 'NONE';

    byId('statusBox').textContent =
`mode: ${s.mode}
ip: ${s.ip}
targetValid: ${s.targetValid}
targetNorm: (${s.targetNr}, ${s.targetNg}, ${s.targetNb})
thr: (${s.thrR}, ${s.thrG}, ${s.thrB})
minSat: ${s.minSat}
scanStep: ${s.scanStep}
minBlobPixels: ${s.minBlobPixels}
roiPct: ${s.roiPct}
detectEveryN: ${s.detectEveryN}
leftPct/rightPct: ${s.leftPct}/${s.rightPct}

blob: ${blobLine}
lastUpdateMs: ${s.blobMs}`;
  } catch (e) {
    byId('statusBox').textContent = 'Status fetch failed: ' + e;
  }
}

async function applyCfg() {
  const q = new URLSearchParams({
    thrR: byId('thrR').value,
    thrG: byId('thrG').value,
    thrB: byId('thrB').value,
    minSat: byId('minSat').value,
    step: byId('scanStep').value,
    minpix: byId('minBlobPixels').value,
    roi: byId('roiPct').value,
    every: byId('detectEveryN').value,
    left: byId('leftPct').value,
    right: byId('rightPct').value
  });
  await fetch('/set?' + q.toString());
  await getStatus();
  refreshMask();
}

async function saveCfg() {
  await fetch('/save');
  await getStatus();
}

async function sampleTarget() {
  await fetch('/sample');
  await getStatus();
  refreshMask();
}

async function clearTarget() {
  await fetch('/clear');
  await getStatus();
  refreshMask();
}

async function bootRun() {
  await fetch('/save');
  await fetch('/setmode?m=run');
}

function refreshPreview() {
  byId('cam').src = '/jpg?t=' + Date.now();
}

function refreshMask() {
  byId('mask').src = '/mask.bmp?t=' + Date.now();
}

window.onload = () => {
  getStatus();
  refreshPreview();
  refreshMask();
  setInterval(refreshPreview, 350);
  setInterval(refreshMask, 900);
  setInterval(getStatus, 700);
};
</script>
</body>
</html>
)HTML";

// ---------------- Helpers ----------------
void setDefaults() {
  gCfg.mode               = MODE_TUNING;
  gCfg.targetValid        = 0;
  gCfg.targetNr           = 0;
  gCfg.targetNg           = 0;
  gCfg.targetNb           = 0;

  gCfg.thrR               = 18;
  gCfg.thrG               = 18;
  gCfg.thrB               = 18;
  gCfg.minSat             = 20;
  gCfg.scanStep           = 4;

  gCfg.minBlobPixels      = 40;
  gCfg.scanStartYPermille = 350;
  gCfg.detectEveryN       = 2;
  gCfg.leftPct            = 40;
  gCfg.rightPct           = 60;

  gLastBlob = {false, 0,0,0,0, 0,0,0,0, 0,0, DIR_NONE, 0};
}

void clampConfig() {
  gCfg.mode               = (gCfg.mode == MODE_RUN) ? MODE_RUN : MODE_TUNING;
  gCfg.targetValid        = gCfg.targetValid ? 1 : 0;
  gCfg.scanStep           = constrain(gCfg.scanStep, 1, 12);
  gCfg.minSat             = constrain(gCfg.minSat, 0, 255);
  gCfg.thrR               = constrain(gCfg.thrR, 0, 255);
  gCfg.thrG               = constrain(gCfg.thrG, 0, 255);
  gCfg.thrB               = constrain(gCfg.thrB, 0, 255);
  gCfg.minBlobPixels      = constrain(gCfg.minBlobPixels, 1, 5000);
  gCfg.scanStartYPermille = constrain(gCfg.scanStartYPermille, 0, 900);
  gCfg.detectEveryN       = constrain(gCfg.detectEveryN, 1, 10);
  gCfg.leftPct            = constrain(gCfg.leftPct, 0, 90);
  gCfg.rightPct           = constrain(gCfg.rightPct, 10, 100);

  if (gCfg.rightPct <= gCfg.leftPct + 5) {
    gCfg.rightPct = min(100, (int)gCfg.leftPct + 5);
  }
}

void loadConfig() {
  setDefaults();

  if (!gPrefs.begin(PREF_NAMESPACE, true)) {
    Serial.println("Preferences open (read) failed, using defaults");
    return;
  }

  gCfg.mode               = gPrefs.getUChar("mode", gCfg.mode);
  gCfg.targetValid        = gPrefs.getUChar("tvalid", gCfg.targetValid);
  gCfg.targetNr           = gPrefs.getUChar("tnr", gCfg.targetNr);
  gCfg.targetNg           = gPrefs.getUChar("tng", gCfg.targetNg);
  gCfg.targetNb           = gPrefs.getUChar("tnb", gCfg.targetNb);

  gCfg.thrR               = gPrefs.getUChar("thrR", gCfg.thrR);
  gCfg.thrG               = gPrefs.getUChar("thrG", gCfg.thrG);
  gCfg.thrB               = gPrefs.getUChar("thrB", gCfg.thrB);
  gCfg.minSat             = gPrefs.getUChar("minSat", gCfg.minSat);
  gCfg.scanStep           = gPrefs.getUChar("step", gCfg.scanStep);

  gCfg.minBlobPixels      = gPrefs.getUInt("minPix", gCfg.minBlobPixels);
  gCfg.scanStartYPermille = gPrefs.getUInt("roiPm", gCfg.scanStartYPermille);
  gCfg.detectEveryN       = gPrefs.getUChar("every", gCfg.detectEveryN);
  gCfg.leftPct            = gPrefs.getUChar("leftPct", gCfg.leftPct);
  gCfg.rightPct           = gPrefs.getUChar("rightPct", gCfg.rightPct);

  gPrefs.end();
  clampConfig();
}

void saveConfig() {
  clampConfig();

  if (!gPrefs.begin(PREF_NAMESPACE, false)) {
    Serial.println("Preferences open (write) failed");
    return;
  }

  gPrefs.putUChar("mode",     gCfg.mode);
  gPrefs.putUChar("tvalid",   gCfg.targetValid);
  gPrefs.putUChar("tnr",      gCfg.targetNr);
  gPrefs.putUChar("tng",      gCfg.targetNg);
  gPrefs.putUChar("tnb",      gCfg.targetNb);

  gPrefs.putUChar("thrR",     gCfg.thrR);
  gPrefs.putUChar("thrG",     gCfg.thrG);
  gPrefs.putUChar("thrB",     gCfg.thrB);
  gPrefs.putUChar("minSat",   gCfg.minSat);
  gPrefs.putUChar("step",     gCfg.scanStep);

  gPrefs.putUInt("minPix",    gCfg.minBlobPixels);
  gPrefs.putUInt("roiPm",     gCfg.scanStartYPermille);
  gPrefs.putUChar("every",    gCfg.detectEveryN);
  gPrefs.putUChar("leftPct",  gCfg.leftPct);
  gPrefs.putUChar("rightPct", gCfg.rightPct);

  gPrefs.end();
  Serial.println("Config saved to Preferences");
}

void clearTarget() {
  gCfg.targetValid = 0;
  gCfg.targetNr = gCfg.targetNg = gCfg.targetNb = 0;
  gLastBlob = {false, 0,0,0,0, 0,0,0,0, 0,0, DIR_NONE, millis()};
}

const char* modeName(BootMode m) {
  return (m == MODE_RUN) ? "RUN" : "TUNING";
}

const char* dirName(DirCode d) {
  switch (d) {
    case DIR_LEFT:   return "LEFT";
    case DIR_CENTER: return "CENTER";
    case DIR_RIGHT:  return "RIGHT";
    default:         return "NONE";
  }
}

// ---------------- Robot UART helpers ----------------
void initRobotUart() {
  if (!ROBOT_UART_ENABLED || (ROBOT_UART_TX_PIN < 0 && ROBOT_UART_RX_PIN < 0)) {
    Serial.println("Robot UART disabled");
    return;
  }

  RobotSerial.begin(ROBOT_UART_BAUD, SERIAL_8N1, ROBOT_UART_RX_PIN, ROBOT_UART_TX_PIN);

  Serial.printf(
    "Robot UART enabled: baud=%lu TX=G%d RX=G%d\n",
    (unsigned long)ROBOT_UART_BAUD,
    ROBOT_UART_TX_PIN,
    ROBOT_UART_RX_PIN
  );
}

void robotWriteLine(const String& line) {
  // Keep USB Serial output for debugging.
  Serial.println(line);

  // Send the same clean line to the motor-controller Atom/Pico.
  if (ROBOT_UART_ENABLED && ROBOT_UART_TX_PIN >= 0) {
    RobotSerial.println(line);
  }
}

void robotSendBlobLine(const BlobInfo& blob) {
  char buf[180];

  snprintf(
    buf,
    sizeof(buf),
    "BLOB dir=%s cx=%d cy=%d count=%d area1000=%d bbox=(%d,%d)-(%d,%d)",
    dirName(blob.dir),
    blob.cx,
    blob.cy,
    blob.count,
    blob.area1000,
    blob.minX,
    blob.minY,
    blob.maxX,
    blob.maxY
  );

  robotWriteLine(String(buf));
}

void robotSendNoneLine() {
  robotWriteLine("NONE");
}

void pollRobotUartCommands() {
  if (!ROBOT_UART_ENABLED || ROBOT_UART_RX_PIN < 0) return;

  while (RobotSerial.available()) {
    char ch = (char)RobotSerial.read();

    if (ch == '\r' || ch == '\n') {
      if (gRobotSerialLine.length() > 0) {
        String line = gRobotSerialLine;
        gRobotSerialLine = "";

        line.trim();
        if (line.length() > 0) {
          Serial.print("ROBOT_UART_CMD> ");
          Serial.println(line);

          // Reuse the exact same parser as USB Serial.
          // This allows Pico to send:
          //   mode tune
          //   mode run
          //   reboot
          //   sample
          //   save
          //   etc.
          handleSerialLine(line);
        }
      }
    } else if (isPrintable((unsigned char)ch)) {
      gRobotSerialLine += ch;

      if (gRobotSerialLine.length() > 120) {
        gRobotSerialLine.remove(0, gRobotSerialLine.length() - 120);
      }
    }
  }
}

// ---------------- USB Serial command helpers ----------------
void printHelp() {
  Serial.println();
  Serial.println("Commands via USB Serial or RobotSerial:");
  Serial.println("  help");
  Serial.println("  status");
  Serial.println("  sample");
  Serial.println("  clear");
  Serial.println("  th <r> <g> <b>        e.g. th 18 18 18");
  Serial.println("  sat <n>               e.g. sat 20");
  Serial.println("  step <n>              e.g. step 4");
  Serial.println("  minpix <n>            e.g. minpix 40");
  Serial.println("  roi <pct>             e.g. roi 35");
  Serial.println("  every <n>             tuning detect every nth preview frame");
  Serial.println("  bands <l> <r>         e.g. bands 40 60");
  Serial.println("  save");
  Serial.println("  mode tune");
  Serial.println("  mode run");
  Serial.println("  reboot");
  Serial.println();
}

void printStatusToSerial() {
  Serial.printf(
    "mode=%s targetValid=%u targetNorm=(%u,%u,%u) thr=(%u,%u,%u) minSat=%u step=%u minBlobPixels=%u roiPct=%u every=%u bands=%u/%u\n",
    modeName((BootMode)gCfg.mode),
    gCfg.targetValid,
    gCfg.targetNr, gCfg.targetNg, gCfg.targetNb,
    gCfg.thrR, gCfg.thrG, gCfg.thrB,
    gCfg.minSat, gCfg.scanStep, gCfg.minBlobPixels,
    (unsigned)(gCfg.scanStartYPermille / 10),
    gCfg.detectEveryN,
    gCfg.leftPct, gCfg.rightPct
  );

  if (gLastBlob.found) {
    Serial.printf(
      "lastBlob found=1 dir=%s cx=%d cy=%d count=%d area1000=%d bbox=(%d,%d)-(%d,%d)\n",
      dirName(gLastBlob.dir),
      gLastBlob.cx, gLastBlob.cy,
      gLastBlob.count,
      gLastBlob.area1000,
      gLastBlob.minX,
      gLastBlob.minY,
      gLastBlob.maxX,
      gLastBlob.maxY
    );
  } else {
    Serial.println("lastBlob found=0");
  }
}

void handleSerialLine(String line) {
  line.trim();
  line.toLowerCase();
  if (line.length() == 0) return;

  int a, b, c;
  char word[16] = {0};

  if (line == "help") {
    printHelp();
    return;
  }
  if (line == "status") {
    printStatusToSerial();
    return;
  }
  if (line == "sample") {
    gPendingSample = true;
    Serial.println("Will sample center on next processed frame");
    return;
  }
  if (line == "clear") {
    clearTarget();
    Serial.println("Target cleared");
    return;
  }
  if (line == "save") {
    saveConfig();
    return;
  }
  if (line == "reboot") {
    Serial.println("Rebooting...");
    delay(100);
    ESP.restart();
    return;
  }

  if (sscanf(line.c_str(), "th %d %d %d", &a, &b, &c) == 3) {
    gCfg.thrR = constrain(a, 0, 255);
    gCfg.thrG = constrain(b, 0, 255);
    gCfg.thrB = constrain(c, 0, 255);
    Serial.printf("thr=(%u,%u,%u)\n", gCfg.thrR, gCfg.thrG, gCfg.thrB);
    return;
  }
  if (sscanf(line.c_str(), "sat %d", &a) == 1) {
    gCfg.minSat = constrain(a, 0, 255);
    Serial.printf("minSat=%u\n", gCfg.minSat);
    return;
  }
  if (sscanf(line.c_str(), "step %d", &a) == 1) {
    gCfg.scanStep = constrain(a, 1, 12);
    Serial.printf("scanStep=%u\n", gCfg.scanStep);
    return;
  }
  if (sscanf(line.c_str(), "minpix %d", &a) == 1) {
    gCfg.minBlobPixels = constrain(a, 1, 5000);
    Serial.printf("minBlobPixels=%u\n", gCfg.minBlobPixels);
    return;
  }
  if (sscanf(line.c_str(), "roi %d", &a) == 1) {
    gCfg.scanStartYPermille = constrain(a, 0, 90) * 10;
    Serial.printf("roiPct=%u\n", (unsigned)(gCfg.scanStartYPermille / 10));
    return;
  }
  if (sscanf(line.c_str(), "every %d", &a) == 1) {
    gCfg.detectEveryN = constrain(a, 1, 10);
    Serial.printf("detectEveryN=%u\n", gCfg.detectEveryN);
    return;
  }
  if (sscanf(line.c_str(), "bands %d %d", &a, &b) == 2) {
    gCfg.leftPct = constrain(a, 0, 90);
    gCfg.rightPct = constrain(b, 10, 100);
    clampConfig();
    Serial.printf("bands=%u/%u\n", gCfg.leftPct, gCfg.rightPct);
    return;
  }
  if (sscanf(line.c_str(), "mode %15s", word) == 1) {
    if (strcmp(word, "run") == 0) {
      switchModeAndReboot(MODE_RUN);
      return;
    }
    if (strcmp(word, "tune") == 0 || strcmp(word, "tuning") == 0) {
      switchModeAndReboot(MODE_TUNING);
      return;
    }
  }

  Serial.println("Unknown command. Type 'help'.");
}

void pollSerialCommands() {
  while (Serial.available()) {
    char ch = (char)Serial.read();

    if (ch == '\r' || ch == '\n') {
      if (gSerialLine.length() > 0) {
        handleSerialLine(gSerialLine);
        gSerialLine = "";
      }
    } else if (isPrintable((unsigned char)ch)) {
      gSerialLine += ch;

      if (gSerialLine.length() > 120) {
        gSerialLine.remove(0, gSerialLine.length() - 120);
      }
    }
  }
}

BootMode chooseModeAtBoot() {
  BootMode saved = (gCfg.mode == MODE_RUN) ? MODE_RUN : MODE_TUNING;
  Serial.printf("Saved mode: %s\n", modeName(saved));
  Serial.printf("Type 't' or 'r' within %lu ms to override boot mode...\n", (unsigned long)BOOT_OVERRIDE_MS);

  String line;
  uint32_t start = millis();

  while (millis() - start < BOOT_OVERRIDE_MS) {
    while (Serial.available()) {
      char ch = (char)Serial.read();

      if (ch == '\r' || ch == '\n') {
        line.trim();
        line.toLowerCase();

        if (line == "t" || line == "tune" || line == "tuning") {
          Serial.println("Boot override: TUNING");
          return MODE_TUNING;
        }
        if (line == "r" || line == "run") {
          Serial.println("Boot override: RUN");
          return MODE_RUN;
        }

        line = "";
      } else if (isPrintable((unsigned char)ch)) {
        line += ch;
      }
    }

    delay(10);
  }

  return saved;
}

void switchModeAndReboot(BootMode nextMode) {
  gCfg.mode = (uint8_t)nextMode;
  saveConfig();
  Serial.printf("Switching mode to %s and rebooting...\n", modeName(nextMode));
  delay(150);
  ESP.restart();
}

// ---------------- Camera ----------------
camera_config_t buildCameraConfig(BootMode mode) {
  camera_config_t c = {
    .pin_pwdn     = PWDN_GPIO_NUM,
    .pin_reset    = RESET_GPIO_NUM,
    .pin_xclk     = XCLK_GPIO_NUM,
    .pin_sscb_sda = SIOD_GPIO_NUM,
    .pin_sscb_scl = SIOC_GPIO_NUM,

    .pin_d7       = Y9_GPIO_NUM,
    .pin_d6       = Y8_GPIO_NUM,
    .pin_d5       = Y7_GPIO_NUM,
    .pin_d4       = Y6_GPIO_NUM,
    .pin_d3       = Y5_GPIO_NUM,
    .pin_d2       = Y4_GPIO_NUM,
    .pin_d1       = Y3_GPIO_NUM,
    .pin_d0       = Y2_GPIO_NUM,

    .pin_vsync    = VSYNC_GPIO_NUM,
    .pin_href     = HREF_GPIO_NUM,
    .pin_pclk     = PCLK_GPIO_NUM,

    .xclk_freq_hz = 20000000,
    .ledc_timer   = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,

    .pixel_format = PIXFORMAT_JPEG,
    .frame_size   = (mode == MODE_TUNING) ? TUNE_FRAME_SIZE : RUN_FRAME_SIZE,

    .jpeg_quality = (mode == MODE_TUNING) ? TUNE_JPEG_QUALITY : 10,
    .fb_count     = 2,
    .fb_location  = CAMERA_FB_IN_PSRAM,
    .grab_mode    = CAMERA_GRAB_LATEST,
    .sccb_i2c_port = 0,
  };

  return c;
}

bool initCameraForMode(BootMode mode) {
  pinMode(POWER_GPIO_NUM, OUTPUT);
  digitalWrite(POWER_GPIO_NUM, LOW);
  delay(500);

  camera_config_t config = buildCameraConfig(mode);
  esp_err_t err = esp_camera_init(&config);

  if (err != ESP_OK) {
    Serial.printf("Camera init failed: 0x%x\n", err);
    return false;
  }

  applySensorTuning(mode);
  Serial.printf("Camera init OK in %s mode\n", modeName(mode));
  return true;
}

void applySensorTuning(BootMode mode) {
  sensor_t* s = esp_camera_sensor_get();
  if (!s) return;

  s->set_brightness(s, 1);
  s->set_contrast(s, 0);
  s->set_saturation(s, 0);

  s->set_whitebal(s, 1);
  s->set_awb_gain(s, 1);
  s->set_gain_ctrl(s, 1);
  s->set_exposure_ctrl(s, 1);

  // Uncomment these if the camera is physically mounted upside down:
  // s->set_vflip(s, 1);
  // s->set_hmirror(s, 1);

  (void)mode;
}

// ---------------- Wi-Fi ----------------
bool startWifiForTuning() {
  WiFi.setSleep(false);

  if (PREFER_STA && STA_SSID && strlen(STA_SSID) > 0) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(STA_SSID, STA_PASS);

    Serial.printf("Connecting to Wi-Fi SSID: %s\n", STA_SSID);

    uint32_t start = millis();

    while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
      delay(300);
      Serial.print(".");
    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {
      gWebIP = WiFi.localIP();
      gWifiStarted = true;
      gServer.begin();

      Serial.print("Wi-Fi connected. IP: ");
      Serial.println(gWebIP);

      return true;
    }

    Serial.println("STA connect failed, falling back to AP mode");
    WiFi.disconnect(true, true);
    delay(100);
  }

  WiFi.mode(WIFI_AP);

  if (!WiFi.softAP(AP_SSID, AP_PASS)) {
    Serial.println("SoftAP start failed");
    return false;
  }

  gWebIP = WiFi.softAPIP();
  gWifiStarted = true;
  gServer.begin();

  Serial.printf("AP started. SSID: %s  PASS: %s  IP: %s\n",
                AP_SSID,
                AP_PASS,
                gWebIP.toString().c_str());

  return true;
}

String ipToString() {
  if (!gWifiStarted) return "off";
  return gWebIP.toString();
}

// ---------------- RGB helpers ----------------
bool ensureRgbBuffer(int w, int h) {
  size_t need = (size_t)w * (size_t)h * 3;

  if (gRgbBuf && gRgbBufLen == need) return true;

  if (gRgbBuf) {
    free(gRgbBuf);
    gRgbBuf = nullptr;
    gRgbBufLen = 0;
  }

  gRgbBuf = (uint8_t*)heap_caps_malloc(need, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);

  if (!gRgbBuf) {
    gRgbBuf = (uint8_t*)malloc(need);
  }

  if (!gRgbBuf) {
    Serial.printf("RGB buffer alloc failed: %u bytes\n", (unsigned)need);
    return false;
  }

  gRgbBufLen = need;
  return true;
}

static inline void rgbToNorm(uint8_t r, uint8_t g, uint8_t b,
                             uint8_t& nr, uint8_t& ng, uint8_t& nb, int& sat) {
  int sum = (int)r + (int)g + (int)b;
  if (sum < 1) sum = 1;

  nr = (uint8_t)((r * 255) / sum);
  ng = (uint8_t)((g * 255) / sum);
  nb = (uint8_t)((b * 255) / sum);

  int maxv = max((int)r, max((int)g, (int)b));
  int minv = min((int)r, min((int)g, (int)b));
  sat = maxv - minv;
}

static inline void rgb565To888(uint16_t px, uint8_t& r, uint8_t& g, uint8_t& b) {
  uint8_t r5 = (px >> 11) & 0x1F;
  uint8_t g6 = (px >> 5)  & 0x3F;
  uint8_t b5 =  px        & 0x1F;

  r = (r5 << 3) | (r5 >> 2);
  g = (g6 << 2) | (g6 >> 4);
  b = (b5 << 3) | (b5 >> 2);
}

static inline bool matchPixelNorm(uint8_t nr, uint8_t ng, uint8_t nb, int sat) {
  if (!gCfg.targetValid) return false;
  if (sat < gCfg.minSat) return false;

  int dr = abs((int)nr - (int)gCfg.targetNr);
  int dg = abs((int)ng - (int)gCfg.targetNg);
  int db = abs((int)nb - (int)gCfg.targetNb);

  return (dr <= gCfg.thrR && dg <= gCfg.thrG && db <= gCfg.thrB);
}

// ---------------- Sampling ----------------
bool sampleCenterRGB888(const uint8_t* rgb, int w, int h) {
  const int half = 6;
  int cx = w / 2;
  int cy = h / 2;

  uint32_t sumNr = 0, sumNg = 0, sumNb = 0;
  int count = 0;

  for (int y = max(0, cy - half); y <= min(h - 1, cy + half); y++) {
    for (int x = max(0, cx - half); x <= min(w - 1, cx + half); x++) {
      const uint8_t* p = &rgb[(y * w + x) * 3];

      uint8_t nr, ng, nb;
      int sat;

      rgbToNorm(p[0], p[1], p[2], nr, ng, nb, sat);

      if (sat < gCfg.minSat) continue;

      sumNr += nr;
      sumNg += ng;
      sumNb += nb;
      count++;
    }
  }

  if (count <= 0) return false;

  gCfg.targetNr    = sumNr / count;
  gCfg.targetNg    = sumNg / count;
  gCfg.targetNb    = sumNb / count;
  gCfg.targetValid = 1;

  return true;
}

bool sampleCenterRGB565(const uint16_t* px, int w, int h) {
  const int half = 6;
  int cx = w / 2;
  int cy = h / 2;

  uint32_t sumNr = 0, sumNg = 0, sumNb = 0;
  int count = 0;

  for (int y = max(0, cy - half); y <= min(h - 1, cy + half); y++) {
    for (int x = max(0, cx - half); x <= min(w - 1, cx + half); x++) {
      uint8_t r, g, b;
      rgb565To888(px[y * w + x], r, g, b);

      uint8_t nr, ng, nb;
      int sat;

      rgbToNorm(r, g, b, nr, ng, nb, sat);

      if (sat < gCfg.minSat) continue;

      sumNr += nr;
      sumNg += ng;
      sumNb += nb;
      count++;
    }
  }

  if (count <= 0) return false;

  gCfg.targetNr    = sumNr / count;
  gCfg.targetNg    = sumNg / count;
  gCfg.targetNb    = sumNb / count;
  gCfg.targetValid = 1;

  return true;
}

// ---------------- Detection ----------------
static inline DirCode dirFromX(int cx, int w) {
  int leftEdge  = (w * gCfg.leftPct) / 100;
  int rightEdge = (w * gCfg.rightPct) / 100;

  if (cx < leftEdge)  return DIR_LEFT;
  if (cx > rightEdge) return DIR_RIGHT;
  return DIR_CENTER;
}

BlobInfo detectBlobRGB888(const uint8_t* rgb, int w, int h) {
  BlobInfo b = {false, 0,0,0,0, w, h, -1, -1, w, h, DIR_NONE, millis()};

  int y0 = ((int64_t)h * gCfg.scanStartYPermille) / 1000;

  int64_t sumX = 0;
  int64_t sumY = 0;
  int count = 0;
  int total = 0;

  int minX = w;
  int minY = h;
  int maxX = -1;
  int maxY = -1;

  for (int y = y0; y < h; y += gCfg.scanStep) {
    for (int x = 0; x < w; x += gCfg.scanStep) {
      total++;

      const uint8_t* p = &rgb[(y * w + x) * 3];

      uint8_t nr, ng, nb;
      int sat;

      rgbToNorm(p[0], p[1], p[2], nr, ng, nb, sat);

      if (!matchPixelNorm(nr, ng, nb, sat)) continue;

      count++;
      sumX += x;
      sumY += y;

      if (x < minX) minX = x;
      if (y < minY) minY = y;
      if (x > maxX) maxX = x;
      if (y > maxY) maxY = y;
    }
  }

  if (count < gCfg.minBlobPixels || total <= 0) {
    b.found = false;
    b.count = count;
    b.area1000 = (total > 0) ? (count * 1000 / total) : 0;
    return b;
  }

  b.found    = true;
  b.cx       = (int)(sumX / count);
  b.cy       = (int)(sumY / count);
  b.count    = count;
  b.area1000 = count * 1000 / total;
  b.minX     = minX;
  b.minY     = minY;
  b.maxX     = maxX;
  b.maxY     = maxY;
  b.imgW     = w;
  b.imgH     = h;
  b.dir      = dirFromX(b.cx, w);

  return b;
}

BlobInfo detectBlobRGB565(const uint16_t* px, int w, int h) {
  BlobInfo b = {false, 0,0,0,0, w, h, -1, -1, w, h, DIR_NONE, millis()};

  int y0 = ((int64_t)h * gCfg.scanStartYPermille) / 1000;

  int64_t sumX = 0;
  int64_t sumY = 0;
  int count = 0;
  int total = 0;

  int minX = w;
  int minY = h;
  int maxX = -1;
  int maxY = -1;

  for (int y = y0; y < h; y += gCfg.scanStep) {
    for (int x = 0; x < w; x += gCfg.scanStep) {
      total++;

      uint8_t r, g, bl;
      rgb565To888(px[y * w + x], r, g, bl);

      uint8_t nr, ng, nb;
      int sat;

      rgbToNorm(r, g, bl, nr, ng, nb, sat);

      if (!matchPixelNorm(nr, ng, nb, sat)) continue;

      count++;
      sumX += x;
      sumY += y;

      if (x < minX) minX = x;
      if (y < minY) minY = y;
      if (x > maxX) maxX = x;
      if (y > maxY) maxY = y;
    }
  }

  if (count < gCfg.minBlobPixels || total <= 0) {
    b.found = false;
    b.count = count;
    b.area1000 = (total > 0) ? (count * 1000 / total) : 0;
    return b;
  }

  b.found    = true;
  b.cx       = (int)(sumX / count);
  b.cy       = (int)(sumY / count);
  b.count    = count;
  b.area1000 = count * 1000 / total;
  b.minX     = minX;
  b.minY     = minY;
  b.maxX     = maxX;
  b.maxY     = maxY;
  b.imgW     = w;
  b.imgH     = h;
  b.dir      = dirFromX(b.cx, w);

  return b;
}

void updateLastBlob(const BlobInfo& blob) {
  gLastBlob = blob;
  gLastBlob.ms = millis();
}

// ---------------- JPEG frame processing ----------------
bool processJpegFrame(camera_fb_t* fb, bool doSample, bool doDetect) {
  if (!fb) return false;
  if (!(doSample || doDetect)) return true;

  if (!ensureRgbBuffer(fb->width, fb->height)) return false;

  bool ok = fmt2rgb888(fb->buf, fb->len, fb->format, gRgbBuf);

  if (!ok) {
    Serial.println("fmt2rgb888 failed");
    return false;
  }

  if (doSample) {
    bool sampled = sampleCenterRGB888(gRgbBuf, fb->width, fb->height);

    if (sampled) {
      Serial.printf("SAMPLED targetNorm=(%u,%u,%u)\n",
                    gCfg.targetNr,
                    gCfg.targetNg,
                    gCfg.targetNb);
    } else {
      Serial.println("Sample failed: center patch too gray/dim");
    }
  }

  if (doDetect && gCfg.targetValid) {
    BlobInfo blob = detectBlobRGB888(gRgbBuf, fb->width, fb->height);
    updateLastBlob(blob);
  }

  return true;
}

void noteTunePreviewFrame(size_t bytes) {
  uint32_t now = millis();

  if (gTunePreviewStartMs == 0) gTunePreviewStartMs = now;

  gTunePreviewFrames++;

  uint32_t dt = now - gTunePreviewStartMs;

  if (dt >= 1000) {
    float fps = (1000.0f * gTunePreviewFrames) / (float)dt;

    Serial.printf("TUNE preview fps=%.1f lastJpeg=%uKB\n",
                  fps,
                  (unsigned)(bytes / 1024));

    gTunePreviewFrames = 0;
    gTunePreviewStartMs = now;
  }
}

void noteRunFrame() {
  uint32_t now = millis();

  if (gRunStartMs == 0) gRunStartMs = now;

  gRunFrames++;

  uint32_t dt = now - gRunStartMs;

  if (dt >= 1000) {
    float fps = (1000.0f * gRunFrames) / (float)dt;

    Serial.printf("RUN jpeg-detect fps=%.1f\n", fps);

    gRunFrames = 0;
    gRunStartMs = now;
  }
}

// ---------------- HTTP helpers ----------------
void sendText(WiFiClient& client, const char* status, const char* contentType, const String& body) {
  client.printf("HTTP/1.1 %s\r\n", status);
  client.printf("Content-Type: %s\r\n", contentType);
  client.printf("Content-Length: %u\r\n", (unsigned)body.length());
  client.println("Cache-Control: no-store");
  client.println("Connection: close");
  client.println();
  client.print(body);
}

void sendBinaryHeader(WiFiClient& client, const char* status, const char* contentType, size_t length) {
  client.printf("HTTP/1.1 %s\r\n", status);
  client.printf("Content-Type: %s\r\n", contentType);
  client.printf("Content-Length: %u\r\n", (unsigned)length);
  client.println("Cache-Control: no-store");
  client.println("Connection: close");
  client.println();
}

String getQueryValue(const String& query, const String& key) {
  int p = 0;
  while (p < query.length()) {
    int amp = query.indexOf('&', p);
    if (amp < 0) amp = query.length();

    String pair = query.substring(p, amp);
    int eq = pair.indexOf('=');
    String k = (eq >= 0) ? pair.substring(0, eq) : pair;
    String v = (eq >= 0) ? pair.substring(eq + 1) : "";

    if (k == key) return v;

    p = amp + 1;
  }

  return "";
}

bool getQueryInt(const String& query, const String& key, int& out) {
  String v = getQueryValue(query, key);

  if (v.length() == 0) return false;

  out = v.toInt();
  return true;
}

void writeLE16(WiFiClient& client, uint16_t v) {
  uint8_t b[2];

  b[0] = v & 0xFF;
  b[1] = (v >> 8) & 0xFF;

  client.write(b, 2);
}

void writeLE32(WiFiClient& client, uint32_t v) {
  uint8_t b[4];

  b[0] = v & 0xFF;
  b[1] = (v >> 8) & 0xFF;
  b[2] = (v >> 16) & 0xFF;
  b[3] = (v >> 24) & 0xFF;

  client.write(b, 4);
}

// ---------------- HTTP endpoints ----------------
void serveRoot(WiFiClient& client) {
  sendText(client, "200 OK", "text/html; charset=utf-8", String(MAIN_PAGE));
}

void serveStatusJson(WiFiClient& client) {
  String json = "{";

  json += "\"mode\":\"" + String(modeName(gMode)) + "\",";
  json += "\"ip\":\"" + ipToString() + "\",";
  json += "\"targetValid\":" + String((int)gCfg.targetValid) + ",";
  json += "\"targetNr\":" + String((int)gCfg.targetNr) + ",";
  json += "\"targetNg\":" + String((int)gCfg.targetNg) + ",";
  json += "\"targetNb\":" + String((int)gCfg.targetNb) + ",";
  json += "\"thrR\":" + String((int)gCfg.thrR) + ",";
  json += "\"thrG\":" + String((int)gCfg.thrG) + ",";
  json += "\"thrB\":" + String((int)gCfg.thrB) + ",";
  json += "\"minSat\":" + String((int)gCfg.minSat) + ",";
  json += "\"scanStep\":" + String((int)gCfg.scanStep) + ",";
  json += "\"minBlobPixels\":" + String((int)gCfg.minBlobPixels) + ",";
  json += "\"roiPct\":" + String((int)(gCfg.scanStartYPermille / 10)) + ",";
  json += "\"detectEveryN\":" + String((int)gCfg.detectEveryN) + ",";
  json += "\"leftPct\":" + String((int)gCfg.leftPct) + ",";
  json += "\"rightPct\":" + String((int)gCfg.rightPct) + ",";

  json += "\"blobFound\":" + String(gLastBlob.found ? 1 : 0) + ",";
  json += "\"dir\":\"" + String(dirName(gLastBlob.dir)) + "\",";
  json += "\"cx\":" + String(gLastBlob.cx) + ",";
  json += "\"cy\":" + String(gLastBlob.cy) + ",";
  json += "\"count\":" + String(gLastBlob.count) + ",";
  json += "\"area1000\":" + String(gLastBlob.area1000) + ",";
  json += "\"minX\":" + String(gLastBlob.minX) + ",";
  json += "\"minY\":" + String(gLastBlob.minY) + ",";
  json += "\"maxX\":" + String(gLastBlob.maxX) + ",";
  json += "\"maxY\":" + String(gLastBlob.maxY) + ",";
  json += "\"blobMs\":" + String(gLastBlob.ms);

  json += "}";

  sendText(client, "200 OK", "application/json", json);
}

void serveSetQuery(WiFiClient& client, const String& query) {
  int v;

  if (getQueryInt(query, "thrR", v))   gCfg.thrR = constrain(v, 0, 255);
  if (getQueryInt(query, "thrG", v))   gCfg.thrG = constrain(v, 0, 255);
  if (getQueryInt(query, "thrB", v))   gCfg.thrB = constrain(v, 0, 255);
  if (getQueryInt(query, "minSat", v)) gCfg.minSat = constrain(v, 0, 255);
  if (getQueryInt(query, "step", v))   gCfg.scanStep = constrain(v, 1, 12);
  if (getQueryInt(query, "minpix", v)) gCfg.minBlobPixels = constrain(v, 1, 5000);
  if (getQueryInt(query, "roi", v))    gCfg.scanStartYPermille = constrain(v, 0, 90) * 10;
  if (getQueryInt(query, "every", v))  gCfg.detectEveryN = constrain(v, 1, 10);
  if (getQueryInt(query, "left", v))   gCfg.leftPct = constrain(v, 0, 90);
  if (getQueryInt(query, "right", v))  gCfg.rightPct = constrain(v, 10, 100);

  clampConfig();

  sendText(client, "200 OK", "text/plain", "OK\n");
}

void serveSave(WiFiClient& client) {
  saveConfig();
  sendText(client, "200 OK", "text/plain", "saved\n");
}

void serveSample(WiFiClient& client) {
  camera_fb_t* fb = esp_camera_fb_get();

  if (!fb) {
    sendText(client, "500 Internal Server Error", "text/plain", "camera capture failed\n");
    return;
  }

  bool ok = processJpegFrame(fb, true, true);

  esp_camera_fb_return(fb);

  if (!ok) {
    sendText(client, "500 Internal Server Error", "text/plain", "sample failed\n");
    return;
  }

  String body = "sampled ";
  body += String((int)gCfg.targetNr) + " ";
  body += String((int)gCfg.targetNg) + " ";
  body += String((int)gCfg.targetNb) + "\n";

  sendText(client, "200 OK", "text/plain", body);
}

void serveClear(WiFiClient& client) {
  clearTarget();
  sendText(client, "200 OK", "text/plain", "cleared\n");
}

void serveSetMode(WiFiClient& client, const String& query) {
  String m = getQueryValue(query, "m");
  m.toLowerCase();

  if (m == "run") {
    gCfg.mode = MODE_RUN;
    saveConfig();

    sendText(client, "200 OK", "text/plain", "rebooting to RUN\n");
    client.flush();

    delay(150);
    ESP.restart();
    return;
  }

  if (m == "tune" || m == "tuning") {
    gCfg.mode = MODE_TUNING;
    saveConfig();

    sendText(client, "200 OK", "text/plain", "rebooting to TUNING\n");
    client.flush();

    delay(150);
    ESP.restart();
    return;
  }

  sendText(client, "400 Bad Request", "text/plain", "bad mode\n");
}

void serveJpegSnapshot(WiFiClient& client) {
  camera_fb_t* fb = esp_camera_fb_get();

  if (!fb) {
    sendText(client, "500 Internal Server Error", "text/plain", "camera capture failed\n");
    return;
  }

  bool doDetect = false;

  if (gCfg.targetValid) {
    gTuneDetectCounter++;
    doDetect = ((gTuneDetectCounter % gCfg.detectEveryN) == 0);
  }

  if (gPendingSample) {
    doDetect = true;
    processJpegFrame(fb, true, doDetect);
    gPendingSample = false;
  } else if (doDetect) {
    processJpegFrame(fb, false, true);
  }

  sendBinaryHeader(client, "200 OK", "image/jpeg", fb->len);
  client.write(fb->buf, fb->len);

  noteTunePreviewFrame(fb->len);

  esp_camera_fb_return(fb);
}

void serveMaskBmp(WiFiClient& client) {
  camera_fb_t* fb = esp_camera_fb_get();

  if (!fb) {
    sendText(client, "500 Internal Server Error", "text/plain", "camera capture failed\n");
    return;
  }

  bool ok = processJpegFrame(fb, false, true);

  if (!ok || !gRgbBuf) {
    esp_camera_fb_return(fb);
    sendText(client, "500 Internal Server Error", "text/plain", "mask conversion failed\n");
    return;
  }

  int srcW = fb->width;
  int srcH = fb->height;

  int outW = max(1, srcW / (int)MASK_DOWNSAMPLE);
  int outH = max(1, srcH / (int)MASK_DOWNSAMPLE);

  uint32_t rowSize   = ((24 * outW + 31) / 32) * 4;
  uint32_t imageSize = rowSize * outH;
  uint32_t fileSize  = 54 + imageSize;

  sendBinaryHeader(client, "200 OK", "image/bmp", fileSize);

  // BITMAPFILEHEADER
  client.write((const uint8_t*)"BM", 2);
  writeLE32(client, fileSize);
  writeLE16(client, 0);
  writeLE16(client, 0);
  writeLE32(client, 54);

  // BITMAPINFOHEADER
  writeLE32(client, 40);
  writeLE32(client, outW);
  writeLE32(client, outH);
  writeLE16(client, 1);
  writeLE16(client, 24);
  writeLE32(client, 0);
  writeLE32(client, imageSize);
  writeLE32(client, 2835);
  writeLE32(client, 2835);
  writeLE32(client, 0);
  writeLE32(client, 0);

  uint8_t* row = (uint8_t*)malloc(rowSize);

  if (!row) {
    esp_camera_fb_return(fb);
    return;
  }

  int roiLineY = (outH * gCfg.scanStartYPermille) / 1000;
  int leftBand = (outW * gCfg.leftPct) / 100;
  int rightBand = (outW * gCfg.rightPct) / 100;

  for (int y = outH - 1; y >= 0; y--) {
    memset(row, 0, rowSize);

    for (int x = 0; x < outW; x++) {
      int srcX = min(srcW - 1, x * (int)MASK_DOWNSAMPLE);
      int srcY = min(srcH - 1, y * (int)MASK_DOWNSAMPLE);

      const uint8_t* p = &gRgbBuf[(srcY * srcW + srcX) * 3];

      uint8_t nr, ng, nb;
      int sat;

      rgbToNorm(p[0], p[1], p[2], nr, ng, nb, sat);

      bool match = matchPixelNorm(nr, ng, nb, sat);

      uint8_t blue = 0;
      uint8_t green = 0;
      uint8_t red = 0;

      if (match) {
        blue = 0;
        green = 255;
        red = 0;
      }

      if (x == leftBand || x == rightBand) {
        blue = 255;
        green = 0;
        red = 0;
      }

      if (y == roiLineY) {
        blue = 0;
        green = 0;
        red = 255;
      }

      uint8_t* q = &row[x * 3];
      q[0] = blue;
      q[1] = green;
      q[2] = red;
    }

    client.write(row, rowSize);
  }

  free(row);
  esp_camera_fb_return(fb);
}

void serveMjpegStream(WiFiClient& client) {
  client.println("HTTP/1.1 200 OK");
  client.printf("Content-Type: %s\r\n", STREAM_CONTENT_TYPE);
  client.println("Cache-Control: no-store");
  client.println("Connection: close");
  client.println();

  uint32_t frames = 0;
  uint32_t startMs = millis();

  while (client.connected()) {
    pollSerialCommands();
    pollRobotUartCommands();

    camera_fb_t* fb = esp_camera_fb_get();

    if (!fb) {
      delay(10);
      continue;
    }

    client.print(STREAM_BOUNDARY);
    client.printf(STREAM_PART, (unsigned)fb->len);

    if (client.write(fb->buf, fb->len) == 0) {
      esp_camera_fb_return(fb);
      break;
    }

    esp_camera_fb_return(fb);

    frames++;

    uint32_t now = millis();

    if (now - startMs >= 1000) {
      float fps = (1000.0f * frames) / (float)(now - startMs);

      Serial.printf("MJPEG fps=%.1f\n", fps);

      frames = 0;
      startMs = now;
    }

    delay(1);
  }

  client.stop();
}

void serve404(WiFiClient& client) {
  sendText(client, "404 Not Found", "text/plain", "not found\n");
}

void handleHttpClient() {
  WiFiClient client = gServer.available();

  if (!client) return;

  client.setTimeout(1000);

  String reqLine = client.readStringUntil('\n');
  reqLine.trim();

  // Consume remaining request headers.
  while (client.connected()) {
    String h = client.readStringUntil('\n');

    if (h == "\r" || h.length() == 0) break;
  }

  if (!reqLine.startsWith("GET ")) {
    sendText(client, "405 Method Not Allowed", "text/plain", "only GET supported\n");
    client.stop();
    return;
  }

  int sp1 = reqLine.indexOf(' ');
  int sp2 = reqLine.indexOf(' ', sp1 + 1);

  if (sp1 < 0 || sp2 < 0) {
    serve404(client);
    client.stop();
    return;
  }

  String url = reqLine.substring(sp1 + 1, sp2);
  String path = url;
  String query = "";

  int q = url.indexOf('?');

  if (q >= 0) {
    path = url.substring(0, q);
    query = url.substring(q + 1);
  }

  if (path == "/") {
    serveRoot(client);
  } else if (path == "/status") {
    serveStatusJson(client);
  } else if (path == "/set") {
    serveSetQuery(client, query);
  } else if (path == "/save") {
    serveSave(client);
  } else if (path == "/sample") {
    serveSample(client);
  } else if (path == "/clear") {
    serveClear(client);
  } else if (path == "/setmode") {
    serveSetMode(client, query);
  } else if (path == "/jpg") {
    serveJpegSnapshot(client);
  } else if (path == "/mask.bmp") {
    serveMaskBmp(client);
  } else if (path == "/stream") {
    serveMjpegStream(client);
    return;
  } else {
    serve404(client);
  }

  delay(1);
  client.stop();
}

// ---------------- Main loops ----------------
void loopTuning() {
  pollSerialCommands();
  pollRobotUartCommands();
  handleHttpClient();
  delay(2);
}

void loopRun() {
  pollSerialCommands();
  pollRobotUartCommands();

  camera_fb_t* fb = esp_camera_fb_get();

  if (!fb) {
    Serial.println("Camera capture failed");
    delay(5);
    return;
  }

  bool ok = processJpegFrame(fb, gPendingSample, true);

  if (gPendingSample) {
    gPendingSample = false;
  }

  if (!ok) {
    Serial.println("processJpegFrame failed");
    esp_camera_fb_return(fb);
    delay(5);
    return;
  }

  BlobInfo blob = gLastBlob;

  uint32_t now = millis();

  if (now - gLastRunBlobPrintMs >= RUN_BLOB_PRINT_MS) {
    gLastRunBlobPrintMs = now;

    if (blob.found) {
      robotSendBlobLine(blob);
    } else {
      robotSendNoneLine();
    }
  }

  noteRunFrame();
  esp_camera_fb_return(fb);
}

// ---------------- setup / loop ----------------
void setup() {
  Serial.begin(115200);
  delay(300);

  initRobotUart();

  Serial.println();
  Serial.println("AtomS3R-M12 dual-mode blob detector");
  printHelp();

  loadConfig();
  gMode = chooseModeAtBoot();

  if (!initCameraForMode(gMode)) {
    Serial.println("Camera init failed, rebooting...");
    delay(1000);
    ESP.restart();
  }

  if (gMode == MODE_TUNING) {
    if (!startWifiForTuning()) {
      Serial.println("Wi-Fi/AP start failed, rebooting...");
      delay(1000);
      ESP.restart();
    }

    Serial.println("TUNING mode ready.");
    Serial.print("Open http://");
    Serial.println(ipToString());
  } else {
    Serial.println("RUN mode ready. Wi-Fi is off.");
    Serial.println("Watch USB Serial for FPS and RobotSerial for BLOB/NONE output.");
  }

  printStatusToSerial();
}

void loop() {
  if (gMode == MODE_TUNING) {
    loopTuning();
  } else {
    loopRun();
  }
}
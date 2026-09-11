/*
  Atom PICO / M5Stack Atom Matrix robot base controller
  -----------------------------------------------------
  Board target: ESP32-PICO-D4 Atom-style board, e.g. M5Stack Atom Matrix.
  Arduino IDE: select a compatible ESP32 board such as "M5Stack-ATOM" or "ESP32 Dev Module".

  Features:
  - Reads blob result lines from camera module over hardware UART.
    Expected camera lines:
      BLOB dir=LEFT cx=123 cy=210 count=456 area1000=12 bbox=(10,20)-(30,40)
      NONE
  - 2-way UART to camera:
      Camera G1 / TX -> Pico G32 / RX
      Camera G2 / RX <- Pico G26 / TX
  - Web UI with:
      manual    : browser arrow buttons drive motors
      auto_demo : uses camera blob direction + TOF distance
      agent     : exposes camera/TOF state and accepts REST motor commands
      camera mode buttons: tuning mode, run mode
  - REST API:
      GET /api/state
      GET /api/camera
      GET /api/camera/tune
      GET /api/camera/run
      GET /api/tof
      GET /api/mode?set=manual|auto|agent
      GET /api/drive?left=120&right=120
      GET /api/agent/drive?left=120&right=80
      GET /api/stop
  - VL53L1X TOF over I2C using Pololu's VL53L1X Arduino library.
  - DFRobot DRI0044 TB6612 motor driver: DIR + PWM per motor.

  Libraries to install in Arduino Library Manager:
  - VL53L1X by Pololu

  Hardware notes:
  - All grounds must be common: Atom GND, camera GND, motor PSU GND, DRI0044 GND.
  - DRI0044 VCC = Atom logic voltage, normally 3.3 V.
  - DRI0044 VM = motor supply, for your motors start around 3-6 V.
  - TOF should preferably run from 3.3 V I2C unless your breakout has safe level shifting.
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <VL53L1X.h>
#include <esp_arduino_version.h>

// ----------------------------- User config -----------------------------

// Fill these in. If STA fails, the sketch starts its own AP.
const char* WIFI_SSID = "";
const char* WIFI_PASS = "";

const char* AP_SSID   = "AtomPicoRobot";
const char* AP_PASS   = "12345678";   // min 8 characters

// ----------------------------- Camera UART -----------------------------
//
// Wiring:
//
//   Camera M12 G1 / GPIO1 / TX  ->  Pico G32 / RX
//   Camera M12 G2 / GPIO2 / RX  <-  Pico G26 / TX
//   Camera GND                  ->  Pico GND
//
// Camera sends BLOB/NONE lines to Pico.
// Pico sends only simple mode commands for now:
//   mode tune
//   mode run
static const int CAM_UART_RX_PIN = 32;      // Pico receives camera G1/TX here
static const int CAM_UART_TX_PIN = 26;      // Pico sends to camera G2/RX here
static const uint32_t CAM_UART_BAUD = 115200;

// I2C for VL53L1X.
static const int I2C_SCL_PIN = 21;
static const int I2C_SDA_PIN = 25;
static const uint32_t I2C_FREQ_HZ = 400000;

// DRI0044 motor driver pins.
static const int MOTOR_L_PWM_PIN = 19;
static const int MOTOR_L_DIR_PIN = 22;
static const int MOTOR_R_PWM_PIN = 23;
static const int MOTOR_R_DIR_PIN = 33;

// Set these after the first wheel test if one side runs backward.
static const bool MOTOR_L_INVERT = true;
static const bool MOTOR_R_INVERT = true;

// Motor/PWM settings.
static const int PWM_FREQ_HZ = 20000;
static const int PWM_RES_BITS = 8;
static const int PWM_MAX = 255;
static const int MAX_USER_SPEED = 210;
static const int AUTO_FAST = 155;
static const int AUTO_SLOW = 75;
static const int AUTO_SEARCH = 125;

// Safety timings.
static const uint32_t MANUAL_CMD_TIMEOUT_MS = 550;
static const uint32_t AGENT_CMD_TIMEOUT_MS  = 900;
static const uint32_t CAMERA_STALE_MS       = 650;
static const uint32_t TOF_PERIOD_MS         = 60;
static const uint32_t STATUS_PRINT_MS       = 2000;

// TOF safety.
static const int HARD_STOP_DISTANCE_MM = 80;
static const int AUTO_STOP_DISTANCE_MM = 140;
static const int AUTO_SLOW_DISTANCE_MM = 320;

// Keep this false unless actively debugging over USB Serial.
// Printing every camera line can slow the controller down.
static const bool ECHO_CAMERA_LINES = false;

// ----------------------------- Types/state -----------------------------

enum RobotMode : uint8_t {
  MODE_MANUAL = 0,
  MODE_AUTO_DEMO = 1,
  MODE_AGENT = 2
};

struct CameraBlob {
  bool found = false;
  char dir[12] = "NONE";
  int cx = -1;
  int cy = -1;
  int count = 0;
  int area1000 = 0;
  int minX = -1;
  int minY = -1;
  int maxX = -1;
  int maxY = -1;
  uint32_t lastMs = 0;
  uint32_t linesSeen = 0;
  uint32_t parseErrors = 0;
};

struct CameraControlState {
  char lastCommand[24] = "none";
  uint32_t lastCommandMs = 0;
  uint32_t commandsSent = 0;
};

struct TofState {
  bool present = false;
  bool valid = false;
  int distanceMm = -1;
  uint32_t lastMs = 0;
  uint32_t errors = 0;
};

struct MotorState {
  int requestedLeft = 0;
  int requestedRight = 0;
  int appliedLeft = 0;
  int appliedRight = 0;
  char source[16] = "boot";
  uint32_t lastCmdMs = 0;
};

RobotMode gMode = MODE_MANUAL;
CameraBlob gCam;
CameraControlState gCamCtrl;
TofState gTof;
MotorState gMotor;

WebServer server(80);
HardwareSerial CamSerial(1);
VL53L1X tof;
String camLine;

uint32_t lastTofReadMs = 0;
uint32_t lastStatusPrintMs = 0;

#if ESP_ARDUINO_VERSION_MAJOR >= 3
  // Arduino-ESP32 core 3.x uses pin-based LEDC calls.
#else
static const int MOTOR_L_PWM_CH = 0;
static const int MOTOR_R_PWM_CH = 1;
#endif

// ----------------------------- HTML UI -----------------------------

static const char INDEX_HTML[] PROGMEM = R"HTML(
<!doctype html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width,initial-scale=1">
  <title>Atom Robot Controller</title>
  <style>
    :root { color-scheme: dark; }
    body { font-family: Arial, sans-serif; margin: 14px; background: #101114; color: #eee; }
    h1 { margin: 0 0 10px; font-size: 1.35rem; }
    .grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(260px, 1fr)); gap: 12px; }
    .card { background: #1a1c21; border: 1px solid #333842; border-radius: 12px; padding: 12px; }
    button { background: #2e63ff; color: white; border: 0; border-radius: 10px; padding: 10px 14px; margin: 4px; font-size: 1rem; }
    button.secondary { background: #555b68; }
    button.warn { background: #cc4b37; }
    button.good { background: #1f8b4c; }
    button.active { outline: 3px solid #88aaff; }
    .arrows { display: grid; grid-template-columns: 80px 80px 80px; grid-template-rows: 64px 64px 64px; gap: 6px; align-items: stretch; justify-content: center; }
    .arrows button { margin: 0; font-size: 1.4rem; }
    .fwd { grid-column: 2; grid-row: 1; }
    .left { grid-column: 1; grid-row: 2; }
    .stop { grid-column: 2; grid-row: 2; }
    .right { grid-column: 3; grid-row: 2; }
    .back { grid-column: 2; grid-row: 3; }
    pre { white-space: pre-wrap; word-break: break-word; background: #0b0c0f; padding: 10px; border-radius: 8px; overflow-x: auto; }
    .value { font-size: 1.6rem; font-weight: 700; }
    .small { color: #aab; font-size: 0.9rem; }
    input { width: 70px; padding: 7px; border-radius: 8px; border: 1px solid #444; background: #111; color: #eee; }
    code { background: #0b0c0f; padding: 2px 5px; border-radius: 4px; }
  </style>
</head>
<body>
  <h1>Atom Robot Controller</h1>
  <div class="grid">
    <div class="card">
      <h2>Mode</h2>
      <button id="modeManual" onclick="setMode('manual')">Manual</button>
      <button id="modeAuto" onclick="setMode('auto')">Automatic demo</button>
      <button id="modeAgent" onclick="setMode('agent')">Agent</button>
      <button class="warn" onclick="stopRobot()">STOP</button>
      <p class="small">Manual uses the arrow buttons. Auto follows camera blob direction. Agent exposes REST state and accepts REST motor commands.</p>
    </div>

    <div class="card">
      <h2>Camera module</h2>
      <button class="warn" onclick="cameraTune()">Camera tuning mode</button>
      <button class="good" onclick="cameraRun()">Camera run mode</button>
      <p class="small">
        These send <code>mode tune</code> or <code>mode run</code> to the camera over UART.
      </p>
      <div class="small" id="cameraCmd">Last command: ?</div>
    </div>

    <div class="card">
      <h2>Manual drive</h2>
      <div class="arrows">
        <button class="fwd"  data-l="170" data-r="170">▲</button>
        <button class="left" data-l="-130" data-r="130">◀</button>
        <button class="stop" onclick="stopRobot()">■</button>
        <button class="right" data-l="130" data-r="-130">▶</button>
        <button class="back" data-l="-150" data-r="-150">▼</button>
      </div>
      <p class="small">Hold a direction button. Repeated commands are sent while held; motors stop if commands time out.</p>
    </div>

    <div class="card">
      <h2>Live state</h2>
      <div>Mode: <span id="mode" class="value">?</span></div>
      <div>TOF distance: <span id="tof" class="value">?</span></div>
      <div>Camera: <span id="camera" class="value">?</span></div>
      <div>Motors: <span id="motors" class="value">?</span></div>
      <div class="small" id="age">?</div>
    </div>

    <div class="card">
      <h2>Agent/API test</h2>
      <p class="small">Switch to Agent mode, then send an external command here or from another program.</p>
      <label>Left <input id="agentL" type="number" value="120"></label>
      <label>Right <input id="agentR" type="number" value="120"></label>
      <button onclick="agentDrive()">Send agent drive</button>
      <button class="secondary" onclick="fetch('/api/state').then(r=>r.text()).then(t=>document.getElementById('raw').textContent=t)">Refresh raw JSON</button>
      <pre id="raw"></pre>
    </div>

    <div class="card">
      <h2>Useful endpoints</h2>
      <pre>GET /api/state
GET /api/camera
GET /api/camera/tune
GET /api/camera/run
GET /api/tof
GET /api/mode?set=manual|auto|agent
GET /api/drive?left=120&right=120
GET /api/agent/drive?left=120&right=80
GET /api/stop</pre>
    </div>
  </div>

<script>
let holdTimer = null;

function api(url) {
  return fetch(url).then(r => r.json()).catch(e => console.log(e));
}

function setMode(m) {
  api('/api/mode?set=' + encodeURIComponent(m)).then(updateFromState);
}

function stopRobot() {
  api('/api/stop').then(updateFromState);
}

function drive(l, r) {
  return api('/api/drive?left=' + l + '&right=' + r);
}

function cameraTune() {
  api('/api/camera/tune').then(updateFromState);
}

function cameraRun() {
  api('/api/camera/run').then(updateFromState);
}

function agentDrive() {
  const l = Number(document.getElementById('agentL').value || 0);
  const r = Number(document.getElementById('agentR').value || 0);
  api('/api/agent/drive?left=' + l + '&right=' + r).then(updateFromState);
}

function startHold(btn) {
  const l = Number(btn.dataset.l), r = Number(btn.dataset.r);
  drive(l, r).then(updateFromState);
  holdTimer = setInterval(() => drive(l, r).then(updateFromState), 140);
}

function endHold() {
  if (holdTimer) clearInterval(holdTimer);
  holdTimer = null;
  stopRobot();
}

document.querySelectorAll('.arrows button[data-l]').forEach(btn => {
  btn.addEventListener('pointerdown', e => { e.preventDefault(); startHold(btn); });
  btn.addEventListener('pointerup', e => { e.preventDefault(); endHold(); });
  btn.addEventListener('pointercancel', e => { e.preventDefault(); endHold(); });
  btn.addEventListener('pointerleave', e => { if (holdTimer) endHold(); });
});

function updateFromState(s) {
  if (!s) return;

  document.getElementById('mode').textContent = s.mode;
  document.getElementById('tof').textContent = s.tof.valid ? (s.tof.distance_mm + ' mm') : 'invalid';
  document.getElementById('camera').textContent = s.camera.found ? (s.camera.dir + ' cx=' + s.camera.cx) : 'NONE';
  document.getElementById('motors').textContent = s.motors.applied_left + ' / ' + s.motors.applied_right;
  document.getElementById('age').textContent = 'camera age=' + s.camera.age_ms + ' ms, source=' + s.motors.source;

  document.getElementById('cameraCmd').textContent =
    'Last command: ' + s.camera_control.last_command +
    ', age=' + s.camera_control.command_age_ms + ' ms';

  document.getElementById('modeManual').classList.toggle('active', s.mode === 'manual');
  document.getElementById('modeAuto').classList.toggle('active', s.mode === 'auto_demo');
  document.getElementById('modeAgent').classList.toggle('active', s.mode === 'agent');

  document.getElementById('raw').textContent = JSON.stringify(s, null, 2);
}

setInterval(() => api('/api/state').then(updateFromState), 500);
api('/api/state').then(updateFromState);
</script>
</body>
</html>
)HTML";

// ----------------------------- Helpers -----------------------------

const char* modeName(RobotMode m) {
  switch (m) {
    case MODE_MANUAL: return "manual";
    case MODE_AUTO_DEMO: return "auto_demo";
    case MODE_AGENT: return "agent";
    default: return "unknown";
  }
}

int clampSpeed(int v) {
  if (v > MAX_USER_SPEED) return MAX_USER_SPEED;
  if (v < -MAX_USER_SPEED) return -MAX_USER_SPEED;
  return v;
}

void pwmAttachMotorPins() {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcAttach(MOTOR_L_PWM_PIN, PWM_FREQ_HZ, PWM_RES_BITS);
  ledcAttach(MOTOR_R_PWM_PIN, PWM_FREQ_HZ, PWM_RES_BITS);
#else
  ledcSetup(MOTOR_L_PWM_CH, PWM_FREQ_HZ, PWM_RES_BITS);
  ledcSetup(MOTOR_R_PWM_CH, PWM_FREQ_HZ, PWM_RES_BITS);
  ledcAttachPin(MOTOR_L_PWM_PIN, MOTOR_L_PWM_CH);
  ledcAttachPin(MOTOR_R_PWM_PIN, MOTOR_R_PWM_CH);
#endif
}

void pwmWriteMotor(int pin, int channel, int duty) {
  duty = constrain(duty, 0, PWM_MAX);
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  (void)channel;
  ledcWrite(pin, duty);
#else
  (void)pin;
  ledcWrite(channel, duty);
#endif
}

void writeOneMotor(int pwmPin, int pwmChannel, int dirPin, bool invert, int speed) {
  speed = constrain(speed, -PWM_MAX, PWM_MAX);
  if (invert) speed = -speed;

  if (speed == 0) {
    pwmWriteMotor(pwmPin, pwmChannel, 0);
    return;
  }

  bool forward = speed > 0;
  digitalWrite(dirPin, forward ? HIGH : LOW);
  pwmWriteMotor(pwmPin, pwmChannel, abs(speed));
}

void setMotorsRaw(int left, int right, const char* source) {
  left = clampSpeed(left);
  right = clampSpeed(right);

  gMotor.requestedLeft = left;
  gMotor.requestedRight = right;
  strncpy(gMotor.source, source, sizeof(gMotor.source) - 1);
  gMotor.source[sizeof(gMotor.source) - 1] = 0;
  gMotor.lastCmdMs = millis();
}

bool forwardMotionRequested(int left, int right) {
  return (left > 0 || right > 0);
}

void applyMotorOutputs() {
  int left = gMotor.requestedLeft;
  int right = gMotor.requestedRight;

  if (gTof.valid && gTof.distanceMm > 0 && gTof.distanceMm < HARD_STOP_DISTANCE_MM && forwardMotionRequested(left, right)) {
    left = 0;
    right = 0;
  }

  gMotor.appliedLeft = left;
  gMotor.appliedRight = right;

#if ESP_ARDUINO_VERSION_MAJOR >= 3
  writeOneMotor(MOTOR_L_PWM_PIN, -1, MOTOR_L_DIR_PIN, MOTOR_L_INVERT, left);
  writeOneMotor(MOTOR_R_PWM_PIN, -1, MOTOR_R_DIR_PIN, MOTOR_R_INVERT, right);
#else
  writeOneMotor(MOTOR_L_PWM_PIN, MOTOR_L_PWM_CH, MOTOR_L_DIR_PIN, MOTOR_L_INVERT, left);
  writeOneMotor(MOTOR_R_PWM_PIN, MOTOR_R_PWM_CH, MOTOR_R_DIR_PIN, MOTOR_R_INVERT, right);
#endif
}

void stopMotors(const char* source) {
  setMotorsRaw(0, 0, source);
  applyMotorOutputs();
}

String ipString() {
  if (WiFi.getMode() & WIFI_MODE_STA && WiFi.status() == WL_CONNECTED) return WiFi.localIP().toString();
  if (WiFi.getMode() & WIFI_MODE_AP) return WiFi.softAPIP().toString();
  return "0.0.0.0";
}

// ----------------------------- Camera UART parser/control -----------------------------

void sendCameraCommand(const char* cmd) {
  if (!cmd || strlen(cmd) == 0) return;

  CamSerial.println(cmd);

  strncpy(gCamCtrl.lastCommand, cmd, sizeof(gCamCtrl.lastCommand) - 1);
  gCamCtrl.lastCommand[sizeof(gCamCtrl.lastCommand) - 1] = 0;
  gCamCtrl.lastCommandMs = millis();
  gCamCtrl.commandsSent++;

  Serial.print("Sent camera command: ");
  Serial.println(cmd);
}

void resetCameraBlobToNone() {
  gCam.found = false;
  strncpy(gCam.dir, "NONE", sizeof(gCam.dir));
  gCam.dir[sizeof(gCam.dir) - 1] = 0;
  gCam.cx = gCam.cy = -1;
  gCam.count = 0;
  gCam.area1000 = 0;
  gCam.minX = gCam.minY = gCam.maxX = gCam.maxY = -1;
  gCam.lastMs = millis();
}

void parseCameraLine(String line) {
  line.trim();
  if (line.length() == 0) return;

  if (ECHO_CAMERA_LINES) {
    Serial.print("CAM> ");
    Serial.println(line);
  }

  gCam.linesSeen++;

  if (line == "NONE") {
    resetCameraBlobToNone();
    return;
  }

  if (!line.startsWith("BLOB ")) {
    return;
  }

  char dir[12] = {0};
  int cx, cy, count, area1000, minX, minY, maxX, maxY;

  int matched = sscanf(
    line.c_str(),
    "BLOB dir=%11s cx=%d cy=%d count=%d area1000=%d bbox=(%d,%d)-(%d,%d)",
    dir, &cx, &cy, &count, &area1000, &minX, &minY, &maxX, &maxY
  );

  if (matched == 9) {
    gCam.found = true;
    strncpy(gCam.dir, dir, sizeof(gCam.dir) - 1);
    gCam.dir[sizeof(gCam.dir) - 1] = 0;
    gCam.cx = cx;
    gCam.cy = cy;
    gCam.count = count;
    gCam.area1000 = area1000;
    gCam.minX = minX;
    gCam.minY = minY;
    gCam.maxX = maxX;
    gCam.maxY = maxY;
    gCam.lastMs = millis();
  } else {
    gCam.parseErrors++;
  }
}

void pollCameraUart() {
  while (CamSerial.available() > 0) {
    char ch = (char)CamSerial.read();

    if (ch == '\n' || ch == '\r') {
      if (camLine.length() > 0) {
        parseCameraLine(camLine);
        camLine = "";
      }
    } else {
      camLine += ch;
      if (camLine.length() > 180) {
        camLine.remove(0, camLine.length() - 180);
      }
    }
  }
}

// ----------------------------- TOF -----------------------------

void initTof() {
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN, I2C_FREQ_HZ);
  tof.setTimeout(120);

  if (!tof.init()) {
    Serial.println("VL53L1X init failed. Continuing without TOF.");
    gTof.present = false;
    return;
  }

  gTof.present = true;
  tof.setDistanceMode(VL53L1X::Long);
  tof.setMeasurementTimingBudget(50000);
  tof.startContinuous(50);
  Serial.println("VL53L1X init OK.");
}

void pollTof() {
  uint32_t now = millis();
  if (!gTof.present || now - lastTofReadMs < TOF_PERIOD_MS) return;
  lastTofReadMs = now;

  uint16_t mm = tof.read(false);
  if (tof.timeoutOccurred()) {
    gTof.valid = false;
    gTof.errors++;
    return;
  }

  gTof.valid = true;
  gTof.distanceMm = (int)mm;
  gTof.lastMs = now;
}

// ----------------------------- Control logic -----------------------------

bool cameraIsFresh() {
  return (millis() - gCam.lastMs) <= CAMERA_STALE_MS;
}

void updateAutoDemo() {
  if (gMode != MODE_AUTO_DEMO) return;

  if (gTof.valid && gTof.distanceMm > 0 && gTof.distanceMm < AUTO_STOP_DISTANCE_MM) {
    setMotorsRaw(0, 0, "auto_tof_stop");
    return;
  }

  if (!cameraIsFresh()) {
    setMotorsRaw(0, 0, "auto_cam_stale");
    return;
  }

  if (!gCam.found) {
    setMotorsRaw(AUTO_SEARCH, -AUTO_SEARCH, "auto_search");
    return;
  }

  int fast = AUTO_FAST;
  int slow = AUTO_SLOW;

  if (gTof.valid && gTof.distanceMm > 0 && gTof.distanceMm < AUTO_SLOW_DISTANCE_MM) {
    fast = 105;
    slow = 45;
  }

  if (strcmp(gCam.dir, "LEFT") == 0) {
    setMotorsRaw(slow, fast, "auto_left");
  } else if (strcmp(gCam.dir, "RIGHT") == 0) {
    setMotorsRaw(fast, slow, "auto_right");
  } else if (strcmp(gCam.dir, "CENTER") == 0) {
    setMotorsRaw(fast, fast, "auto_center");
  } else {
    setMotorsRaw(0, 0, "auto_unknown");
  }
}

void updateWatchdogs() {
  uint32_t now = millis();

  if (gMode == MODE_MANUAL && now - gMotor.lastCmdMs > MANUAL_CMD_TIMEOUT_MS) {
    if (gMotor.requestedLeft != 0 || gMotor.requestedRight != 0) {
      setMotorsRaw(0, 0, "manual_timeout");
    }
  }

  if (gMode == MODE_AGENT && now - gMotor.lastCmdMs > AGENT_CMD_TIMEOUT_MS) {
    if (gMotor.requestedLeft != 0 || gMotor.requestedRight != 0) {
      setMotorsRaw(0, 0, "agent_timeout");
    }
  }
}

// ----------------------------- JSON/API -----------------------------

void sendCors() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET,POST,OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  server.sendHeader("Cache-Control", "no-store");
}

String cameraJson() {
  uint32_t now = millis();

  String s;
  s.reserve(320);

  s += "{\"found\":"; s += gCam.found ? "true" : "false";
  s += ",\"dir\":\""; s += gCam.dir; s += "\"";
  s += ",\"cx\":"; s += gCam.cx;
  s += ",\"cy\":"; s += gCam.cy;
  s += ",\"count\":"; s += gCam.count;
  s += ",\"area1000\":"; s += gCam.area1000;
  s += ",\"bbox\":{\"min_x\":"; s += gCam.minX;
  s += ",\"min_y\":"; s += gCam.minY;
  s += ",\"max_x\":"; s += gCam.maxX;
  s += ",\"max_y\":"; s += gCam.maxY; s += "}";
  s += ",\"age_ms\":"; s += (now - gCam.lastMs);
  s += ",\"fresh\":"; s += cameraIsFresh() ? "true" : "false";
  s += ",\"lines_seen\":"; s += gCam.linesSeen;
  s += ",\"parse_errors\":"; s += gCam.parseErrors;
  s += "}";

  return s;
}

String cameraControlJson() {
  uint32_t now = millis();

  String s;
  s.reserve(140);

  s += "{\"last_command\":\""; s += gCamCtrl.lastCommand; s += "\"";
  s += ",\"command_age_ms\":"; s += gCamCtrl.lastCommandMs ? (now - gCamCtrl.lastCommandMs) : 0;
  s += ",\"commands_sent\":"; s += gCamCtrl.commandsSent;
  s += "}";

  return s;
}

String tofJson() {
  uint32_t now = millis();

  String s;
  s.reserve(140);

  s += "{\"present\":"; s += gTof.present ? "true" : "false";
  s += ",\"valid\":"; s += gTof.valid ? "true" : "false";
  s += ",\"distance_mm\":"; s += gTof.distanceMm;
  s += ",\"age_ms\":"; s += gTof.lastMs ? (now - gTof.lastMs) : 0;
  s += ",\"errors\":"; s += gTof.errors;
  s += "}";

  return s;
}

String motorJson() {
  String s;
  s.reserve(180);

  s += "{\"requested_left\":"; s += gMotor.requestedLeft;
  s += ",\"requested_right\":"; s += gMotor.requestedRight;
  s += ",\"applied_left\":"; s += gMotor.appliedLeft;
  s += ",\"applied_right\":"; s += gMotor.appliedRight;
  s += ",\"source\":\""; s += gMotor.source; s += "\"";
  s += ",\"cmd_age_ms\":"; s += (millis() - gMotor.lastCmdMs);
  s += "}";

  return s;
}

String stateJson() {
  String s;
  s.reserve(1100);

  s += "{\"mode\":\""; s += modeName(gMode); s += "\"";
  s += ",\"uptime_ms\":"; s += millis();
  s += ",\"ip\":\""; s += ipString(); s += "\"";
  s += ",\"camera\":"; s += cameraJson();
  s += ",\"camera_control\":"; s += cameraControlJson();
  s += ",\"tof\":"; s += tofJson();
  s += ",\"motors\":"; s += motorJson();
  s += "}";

  return s;
}

void sendJson(int code, const String& json) {
  sendCors();
  server.send(code, "application/json", json);
}

int argInt(const char* name, int fallback) {
  if (!server.hasArg(name)) return fallback;
  return server.arg(name).toInt();
}

bool setModeFromString(const String& m) {
  if (m == "manual") {
    gMode = MODE_MANUAL;
  } else if (m == "auto" || m == "auto_demo" || m == "automatic") {
    gMode = MODE_AUTO_DEMO;
  } else if (m == "agent") {
    gMode = MODE_AGENT;
  } else {
    return false;
  }

  stopMotors("mode_change");
  Serial.printf("Mode changed to %s\n", modeName(gMode));
  return true;
}

void handleRoot() {
  sendCors();
  server.send_P(200, "text/html", INDEX_HTML);
}

void handleState() {
  sendJson(200, stateJson());
}

void handleCamera() {
  sendJson(200, cameraJson());
}

void handleCameraTune() {
  stopMotors("camera_tune");
  sendCameraCommand("mode tune");
  sendJson(200, stateJson());
}

void handleCameraRun() {
  sendCameraCommand("mode run");
  sendJson(200, stateJson());
}

void handleTof() {
  sendJson(200, tofJson());
}

void handleMode() {
  if (!server.hasArg("set")) {
    sendJson(200, String("{\"mode\":\"") + modeName(gMode) + "\"}");
    return;
  }

  String m = server.arg("set");
  m.toLowerCase();

  if (!setModeFromString(m)) {
    sendJson(400, "{\"ok\":false,\"error\":\"unknown mode\"}");
    return;
  }

  sendJson(200, stateJson());
}

void handleDrive() {
  if (gMode == MODE_AUTO_DEMO) {
    sendJson(409, "{\"ok\":false,\"error\":\"manual drive rejected in auto_demo mode\"}");
    return;
  }

  int left = argInt("left", 0);
  int right = argInt("right", 0);

  setMotorsRaw(left, right, gMode == MODE_AGENT ? "agent_drive" : "manual_drive");
  applyMotorOutputs();

  sendJson(200, stateJson());
}

void handleAgentDrive() {
  if (gMode != MODE_AGENT) {
    sendJson(409, "{\"ok\":false,\"error\":\"agent drive only active in agent mode\"}");
    return;
  }

  int left = argInt("left", 0);
  int right = argInt("right", 0);

  setMotorsRaw(left, right, "agent_drive");
  applyMotorOutputs();

  sendJson(200, stateJson());
}

void handleStop() {
  stopMotors("api_stop");
  sendJson(200, stateJson());
}

void handleNotFound() {
  if (server.method() == HTTP_OPTIONS) {
    sendCors();
    server.send(204, "text/plain", "");
    return;
  }

  sendJson(404, "{\"ok\":false,\"error\":\"not found\"}");
}

void initWeb() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/api/state", HTTP_GET, handleState);

  server.on("/api/camera", HTTP_GET, handleCamera);
  server.on("/api/camera/tune", HTTP_GET, handleCameraTune);
  server.on("/api/camera/run", HTTP_GET, handleCameraRun);

  server.on("/api/tof", HTTP_GET, handleTof);
  server.on("/api/mode", HTTP_GET, handleMode);
  server.on("/api/drive", HTTP_GET, handleDrive);
  server.on("/api/agent/drive", HTTP_GET, handleAgentDrive);
  server.on("/api/stop", HTTP_GET, handleStop);

  server.onNotFound(handleNotFound);
  server.begin();

  Serial.println("HTTP server started.");
}

// ----------------------------- Wi-Fi -----------------------------

void startWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.printf("Connecting to Wi-Fi SSID '%s'", WIFI_SSID);

  uint32_t start = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - start < 9000) {
    delay(250);
    Serial.print(".");
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Wi-Fi connected. Open: http://");
    Serial.println(WiFi.localIP());
    return;
  }

  Serial.println("STA failed. Starting fallback AP.");

  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASS);

  Serial.print("AP started. SSID: ");
  Serial.print(AP_SSID);
  Serial.print("  PASS: ");
  Serial.print(AP_PASS);
  Serial.print("  Open: http://");
  Serial.println(WiFi.softAPIP());
}

// ----------------------------- Setup/loop -----------------------------

void initMotors() {
  pinMode(MOTOR_L_DIR_PIN, OUTPUT);
  pinMode(MOTOR_R_DIR_PIN, OUTPUT);

  digitalWrite(MOTOR_L_DIR_PIN, LOW);
  digitalWrite(MOTOR_R_DIR_PIN, LOW);

  pwmAttachMotorPins();
  stopMotors("init");

  Serial.println("Motor PWM initialized.");
}

void printStatus() {
  uint32_t now = millis();

  if (now - lastStatusPrintMs < STATUS_PRINT_MS) return;

  lastStatusPrintMs = now;

  Serial.printf(
    "mode=%s ip=%s tof=%s %dmm cam=%s dir=%s age=%lums motors=%d/%d source=%s camCmd=%s\n",
    modeName(gMode),
    ipString().c_str(),
    gTof.valid ? "valid" : "invalid",
    gTof.distanceMm,
    gCam.found ? "BLOB" : "NONE",
    gCam.dir,
    (unsigned long)(now - gCam.lastMs),
    gMotor.appliedLeft,
    gMotor.appliedRight,
    gMotor.source,
    gCamCtrl.lastCommand
  );
}

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println();
  Serial.println("Atom robot base controller starting...");

  initMotors();

  CamSerial.begin(CAM_UART_BAUD, SERIAL_8N1, CAM_UART_RX_PIN, CAM_UART_TX_PIN);

  Serial.printf(
    "Camera UART started: baud=%lu RX=G%d TX=G%d\n",
    (unsigned long)CAM_UART_BAUD,
    CAM_UART_RX_PIN,
    CAM_UART_TX_PIN
  );

  initTof();
  startWiFi();
  initWeb();

  gCam.lastMs = millis();
  gMotor.lastCmdMs = millis();

  Serial.println("Ready.");
  Serial.print("Open web UI: http://");
  Serial.println(ipString());
}

void loop() {
  pollCameraUart();
  pollTof();
  server.handleClient();

  updateAutoDemo();
  updateWatchdogs();
  applyMotorOutputs();

  printStatus();

  delay(2);
}
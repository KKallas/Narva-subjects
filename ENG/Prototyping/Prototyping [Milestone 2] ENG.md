## Prototyping: Milestone 2 — Key Technology Prototype

**Workload:** 16 hours | **Assessment:** 20 points | **Meeting: Sat 21.03**

The point of this milestone is to test the critical technical components before you build the final robot. Start with the drive — without a chassis that drives you cannot test anything else. Once the drive works, add communication. Once communication works, add the web interface. The sensors you can test on the side on a breadboard.

That means that by the end of the milestone you have a **test chassis that drives** and that you control from a web page — not a pretty robot, but proof that all the core systems work. If something does not work, ask before you spend a whole day searching.

---

### 1. Drive prototype

**Goal:** the motors must turn the wheels, change direction and change speed.

**What you need:**
- 2× DC motors with gearboxes (from your M1 specification)
- Motor driver (L298N, TB6612FNG, DRV8833 — or whatever you ordered)
- M5 Atom (or another ESP32 board)
- Battery/power supply (a lab bench supply is fine to start with)
- Wheels + test chassis (read below)

**The simplest test chassis — the phone is the chassis:**

Print 2 brackets that attach to the phone (clamps around the phone, double-sided tape, or a rubber band). Each bracket holds one axle:
- **Drive axles:** one motor + wheel on each side of the phone. The motor mounts inside the bracket.
- **Support at the front:** one castor wheel or simply a slippery knob that slides on the floor — so the phone does not tip forward.

The result: the phone lies horizontally, two motors/wheels on the sides, a support at the front. Three contact points in total. The driver and the MCU are taped on top of the phone or sit next to it connected with wires.

This is not the final robot — it is a test platform. What matters is that it drives, not that it looks good.

**Wiring:**

MCU → motor driver → motors. Check your driver's datasheet — the connections depend on the driver model. The principle is always the same:

| Driver input | What it does | MCU side |
|:---|:---|:---|
| IN1, IN2 (motor A) | Direction control | 2 digital outputs |
| IN3, IN4 (motor B) | Direction control | 2 digital outputs |
| ENA (motor A) | PWM speed control | 1 PWM output |
| ENB (motor B) | PWM speed control | 1 PWM output |

*NB: some drivers (TB6612, DRV8833) have a separate PWM input instead of ENA/ENB. Check your driver's datasheet. Use free pins on your MCU board that support PWM.*

**Starter code (Arduino IDE):**

```cpp
// CHANGE pin numbers to match your MCU board and wiring!
// M5 Atom Lite: available pins are 19, 22, 23, 25, 26, 32, 33 etc.
// Check your board's pinout diagram
const int IN1 = ;  // fill in your pin
const int IN2 = ;  // fill in your pin
const int IN3 = ;  // fill in your pin
const int IN4 = ;  // fill in your pin
const int ENA = ;  // must be PWM-capable pin
const int ENB = ;  // must be PWM-capable pin

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // ESP32 PWM setup
  ledcAttach(ENA, 1000, 8);  // pin, frequency, resolution (8 bit = 0-255)
  ledcAttach(ENB, 1000, 8);
}

void forward(int speed) {
  // speed: 0-255
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  ledcWrite(ENA, speed);
  ledcWrite(ENB, speed);
}

void backward(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  ledcWrite(ENA, speed);
  ledcWrite(ENB, speed);
}

void turnLeft(int speed) {
  // left wheel stops, right wheel forward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  ledcWrite(ENA, 0);
  ledcWrite(ENB, speed);
}

void turnRight(int speed) {
  // right wheel stops, left wheel forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  ledcWrite(ENA, speed);
  ledcWrite(ENB, 0);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  ledcWrite(ENA, 0);
  ledcWrite(ENB, 0);
}

void loop() {
  // Test: drive 2s forward, stop, backward, turn
  forward(200);
  delay(2000);
  stop();
  delay(500);
  backward(200);
  delay(2000);
  stop();
  delay(500);
  turnLeft(150);
  delay(1000);
  stop();
  delay(2000);
}
```

**Your task:**
1. Connect the motors and upload the code — do both wheels turn?
2. If one wheel turns the wrong way → swap that motor's IN1/IN2 connections (or swap them in the code)
3. Test different PWM values (50, 100, 150, 200, 255) — what is the minimum value at which the wheels start to turn?
4. Put everything on the test chassis and check whether it drives — this chassis is the basis for your push test and your communication test

**YouTube search terms:**
- `ESP32 DC motor L298N tutorial`
- `ESP32 PWM motor speed control`
- `TB6612FNG motor driver wiring Arduino`
- `DRV8833 motor driver ESP32`
- `differential drive robot Arduino`

---

### 2. Communication prototype

**Prerequisite:** the drive prototype (step 1) must work — at the end of the communication test you verify that the command arrived by seeing the motor move.

**Everyone starts the same way:** first test sending commands from a **computer** over a USB cable (the MCU's built-in FTDI). You can use the Arduino Serial Monitor or a Python script on the computer. This works for everyone, regardless of the final option. Later you replace the computer with the phone (option A) or with your own ESP32 WiFi solution (option B).

#### Step 2a: Test from the computer (everyone)

Load the command protocol onto the MCU and send commands from the computer:

**MCU side (Arduino):**

```cpp
#include <ArduinoJson.h>  // Add: Sketch → Manage Libraries → ArduinoJson

void setup() {
  Serial.begin(115200);
  // ... motor pin setup from above
}

void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');

    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, line);

    if (err) {
      Serial.println("{\"error\": \"JSON parse failed\"}");
      return;
    }

    const char* cmd = doc["cmd"];
    int speed = doc["speed"] | 150;  // default 150

    if (strcmp(cmd, "forward") == 0) {
      forward(speed);
      Serial.println("{\"status\": \"ok\", \"cmd\": \"forward\"}");
    } else if (strcmp(cmd, "back") == 0) {
      backward(speed);
      Serial.println("{\"status\": \"ok\", \"cmd\": \"back\"}");
    } else if (strcmp(cmd, "left") == 0) {
      turnLeft(speed);
      Serial.println("{\"status\": \"ok\", \"cmd\": \"left\"}");
    } else if (strcmp(cmd, "right") == 0) {
      turnRight(speed);
      Serial.println("{\"status\": \"ok\", \"cmd\": \"right\"}");
    } else if (strcmp(cmd, "stop") == 0) {
      stop();
      Serial.println("{\"status\": \"ok\", \"cmd\": \"stop\"}");
    } else {
      Serial.println("{\"error\": \"unknown command\"}");
    }
  }
}
```

**Test from the computer (Python):**

```python
# pip install pyserial
import serial
import json
import time

# MCU is connected to computer via USB — find the port:
# Windows: COM3, COM4 etc. (check Device Manager)
# Mac/Linux: /dev/ttyUSB0 or /dev/ttyACM0 (ls /dev/tty*)
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
time.sleep(2)  # wait for MCU restart

def send_cmd(cmd, speed=150):
    payload = json.dumps({"cmd": cmd, "speed": speed}) + "\n"
    start = time.time()
    ser.write(payload.encode())
    response = ser.readline().decode().strip()
    elapsed_ms = (time.time() - start) * 1000
    print(f"Cmd: {cmd}, response: {response}, time: {elapsed_ms:.1f} ms")
    return response, elapsed_ms

# Test
send_cmd("forward", 200)
time.sleep(2)
send_cmd("stop")
```

**Your task:**
1. Connect the MCU to the computer with a USB cable (the same cable you upload code with)
2. Run the Python script on the computer (or type into the Serial Monitor by hand: `{"cmd":"forward","speed":200}`)
3. Does the motor move? Does the JSON response come back?
4. If yes → the serial protocol works, move on to step 2b

#### Step 2b: Replace the computer with the phone or with WiFi

**Option A (phone + USB OTG):** the same Python script as on the computer, but now running in Termux on the phone. The phone connects to the MCU over an OTG cable.

1. Install Termux (from F-Droid; the Play Store version is outdated)
2. In Termux: `pkg install python` and `pip install pyserial`
3. Connect the MCU with the OTG cable, check whether `/dev/ttyUSB0` appears
4. Run the same Python script — does it work as it did on the computer?

**If OTG does not work:** some phones do not support USB host mode. Check: Settings → OTG / USB developer options. If it still does not work — switch to option B.

**Option B (WiFi):** add a WiFi web server to the MCU. The serial protocol code stays (for testing from a computer), but control now goes over WiFi.

If OTG does not work or you chose option B, the ESP32 serves the web page itself over WiFi.

```cpp
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "SumoBot_1";      // robot's own WiFi name
const char* password = "sumo1234";    // password

WebServer server(80);

void setup() {
  Serial.begin(115200);
  // motor setup ...

  WiFi.softAP(ssid, password);
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());  // usually 192.168.4.1

  server.on("/cmd", HTTP_GET, []() {
    String cmd = server.arg("c");
    int speed = server.arg("s").toInt();
    if (speed == 0) speed = 150;

    if (cmd == "f") forward(speed);
    else if (cmd == "b") backward(speed);
    else if (cmd == "l") turnLeft(speed);
    else if (cmd == "r") turnRight(speed);
    else if (cmd == "s") stop();

    server.send(200, "text/plain", "OK:" + cmd);
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
```

Test in the browser: connect the phone/computer to the WiFi `SumoBot_1`, open `http://192.168.4.1/cmd?c=f&s=200` — the robot should drive forward.

**YouTube search terms:**
- `ESP32 USB OTG serial communication`
- `Termux Python serial USB OTG`
- `ESP32 WiFi web server motor control`
- `ESP32 softAP access point Arduino`
- `ArduinoJson ESP32 serial protocol`

---

### 3. Web interface prototype

**Prerequisite:** the drive (step 1) and communication (step 2) must work.

**Goal:** one web page with a button → you press it → the motor moves. Prove that the whole chain "browser → server → MCU → motor" works.

#### Option A: FastAPI on the phone (Termux)

```python
# Install in Termux: pip install fastapi uvicorn pyserial
from fastapi import FastAPI
from fastapi.responses import HTMLResponse
import serial
import json

app = FastAPI()
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)

PAGE = """
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Sumobot</title>
  <style>
    button { width: 80px; height: 80px; font-size: 24px; margin: 5px; }
    .row { text-align: center; }
  </style>
</head>
<body>
  <h2>Sumobot Control</h2>
  <div class="row">
    <button onclick="send('f')">↑</button>
  </div>
  <div class="row">
    <button onclick="send('l')">←</button>
    <button onclick="send('s')">■</button>
    <button onclick="send('r')">→</button>
  </div>
  <div class="row">
    <button onclick="send('b')">↓</button>
  </div>
  <p id="status">—</p>
  <script>
    async function send(cmd) {
      const r = await fetch('/cmd?c=' + cmd);
      document.getElementById('status').textContent = await r.text();
    }
  </script>
</body>
</html>
"""

@app.get("/", response_class=HTMLResponse)
def page():
    return PAGE

@app.get("/cmd")
def cmd(c: str, s: int = 150):
    payload = json.dumps({"cmd": {"f":"forward","b":"back","l":"left","r":"right","s":"stop"}[c], "speed": s})
    ser.write((payload + "\n").encode())
    response = ser.readline().decode().strip()
    return response

# Run in Termux: uvicorn main:app --host 0.0.0.0 --port 8000
```

Open `http://localhost:8000` in the phone's browser — or the phone's IP address from another device (same WiFi).

#### Option B: the ESP32 serves the web page itself

If you are using the WiFi option, put the HTML straight into the ESP32 code:

```cpp
// Add to setup():
server.on("/", HTTP_GET, []() {
  server.send(200, "text/html",
    "<!DOCTYPE html><html><head>"
    "<meta name='viewport' content='width=device-width'>"
    "<style>button{width:80px;height:80px;font-size:24px;margin:5px;}"
    ".r{text-align:center;}</style></head><body>"
    "<h2>Sumobot</h2>"
    "<div class='r'><button onclick=\"fetch('/cmd?c=f')\">↑</button></div>"
    "<div class='r'>"
    "<button onclick=\"fetch('/cmd?c=l')\">←</button>"
    "<button onclick=\"fetch('/cmd?c=s')\">■</button>"
    "<button onclick=\"fetch('/cmd?c=r')\">→</button></div>"
    "<div class='r'><button onclick=\"fetch('/cmd?c=b')\">↓</button></div>"
    "</body></html>");
});
```

**Your task:**
1. Start the server (Termux or ESP32)
2. Open the web page on the phone/computer
3. Press the arrow buttons — does the robot move?
4. If it moves → the base of the web interface works, and on top of it you can build the camera stream and the click-and-drive logic

**YouTube search terms:**
- `ESP32 web server control motors`
- `FastAPI Python beginner tutorial`
- `Termux Python web server`
- `ESP32 HTML button motor control`
- `robot web interface ESP32 WiFi`

---

### 4. Sensor prototype

**Goal:** prove that the sensor gives a sensible reading and that the MCU can read it. You can do this on a breadboard in parallel with the other steps — it does not depend on the drive.

**Communication protocols between sensors and the MCU:**

Most sensors use one of two protocols. Before you wire anything up, know which protocol your sensor uses:

- **I2C** (Inter-Integrated Circuit) — 2 wires (SDA + SCL), several sensors can share one bus (each with its own address). Used by: VL53L0X, TCS34725, BMP280, etc. In Arduino code: `#include <Wire.h>`. More info: https://en.wikipedia.org/wiki/I%C2%B2C
- **One-Wire** — 1 data wire (+ power + GND). Used by: the DS18B20 temperature sensor and others. In Arduino code: `#include <OneWire.h>`. More info: https://en.wikipedia.org/wiki/1-Wire
- **Trigger/Echo** (HC-SR04) — not a standard protocol; the MCU sends a pulse to the Trig pin and measures the length of the Echo pulse. No separate library needed.
- **Analogue** — the sensor outputs a voltage of 0–3.3 V, the MCU reads it with `analogRead()`. The simplest option, but less accurate.

#### Distance sensor (HC-SR04 or VL53L0X)

How the sensor is wired depends on your MCU and your sensor. Check your sensor's datasheet. The principle:

| Sensor pin | Where to connect it | Notes |
|:---|:---|:---|
| VCC | 5V (VIN) or 3.3V | Depends on the sensor — check the datasheet |
| Trig | A free digital output | HC-SR04 only |
| Echo | A free digital input | HC-SR04: **Echo is 5V!** Use a voltage divider (2 resistors) if your MCU is 3.3V |
| SDA, SCL | I2C bus pins | The VL53L0X and TCS34725 use I2C |
| GND | GND | |

*NB: the VL53L0X is 3.3V and uses I2C — no voltage divider needed. The HC-SR04's Echo output is 5V and the ESP32/M5 Atom input is 3.3V — without a divider you risk damaging the MCU.*

**HC-SR04 starter code:**

```cpp
const int TRIG = ;  // fill in your pin
const int ECHO = ;  // fill in your pin (through voltage divider!)

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

float measureDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);  // timeout 30ms
  float distance_cm = duration * 0.034 / 2.0;
  return distance_cm;
}

void loop() {
  float cm = measureDistance();
  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.println(" cm");
  delay(100);
}
```

#### Colour sensor (TCS34725 or a simpler analogue sensor)

The TCS34725 uses an I2C connection (SDA + SCL). Install the library: Arduino IDE → Libraries → "Adafruit TCS34725".

```cpp
#include <Wire.h>
#include <Adafruit_TCS34725.h>

Adafruit_TCS34725 tcs = Adafruit_TCS34725(
  TCS34725_INTEGRATIONTIME_50MS,
  TCS34725_GAIN_4X
);

void setup() {
  Serial.begin(115200);
  if (!tcs.begin()) {
    Serial.println("Color sensor not found! Check I2C wiring (SDA/SCL pins).");
    while (1);
  }
}

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  Serial.print("R:"); Serial.print(r);
  Serial.print(" G:"); Serial.print(g);
  Serial.print(" B:"); Serial.print(b);
  Serial.print(" C:"); Serial.println(c);

  // Simple detection: is the surface light (arena) or dark (boundary)?
  if (c < 500) {
    Serial.println(">>> DARK SURFACE (boundary?)");
  } else {
    Serial.println(">>> LIGHT SURFACE (arena)");
  }

  delay(200);
}
```

**Your task:**
1. Connect the sensor on the breadboard, upload the code, open the Serial Monitor
2. Distance sensor: move your hand in front of the sensor to 5, 10, 20, 50 cm — do the readings match?
3. Colour sensor: try white paper, black paper, red/blue — does it tell them apart?
4. If it does not work → run an I2C scanner (search for `ESP32 I2C scanner`), check whether the sensor is visible at all

**YouTube search terms:**
- `HC-SR04 ESP32 distance sensor`
- `VL53L0X ESP32 I2C distance sensor`
- `TCS34725 color sensor Arduino`
- `ESP32 I2C scanner` (if the sensor does not respond)
- `voltage divider 5V to 3.3V` (for the HC-SR04 Echo line)

---

### 5. Starting the PCB design

**Goal:** start designing the motor driver board. The board must be ready to order before 08.04 (the deadline for the 2nd order).

PCB design takes time — do not leave it to the last minute. Start with the schematic; it is essentially the same block diagram as in M1, but with the actual footprints and values of the components.

**Minimum PCB content:**
- MCU sockets (the M5 Atom or similar plugs into a pin header — it is not soldered directly onto the board!)
- Motor driver IC + supporting components
- Motor connectors
- Battery connector + power switch
- Sensor connectors (distance, colour, I2C)
- Voltage regulator (if the battery voltage ≠ the logic voltage)

**What not to do:**
- Do not solder the MCU development board directly onto the PCB — use pin headers so you can swap the board
- Do not forget the ground — a common GND between all components
- Do not use traces that are too thin for the motor current (at least 1 mm for the motor traces)

**YouTube search terms:**
- `KiCad 8 beginner tutorial PCB design`
- `Fusion 360 Electronics PCB design`
- `ESP32 motor driver PCB design`
- `PCB design for beginners schematic to board`
- `how to order PCB JLCPCB` (or `PCBWay`)

---

### Push test (Analysis 1)

**Prerequisite:** the driving test chassis from step 1.

Attach a string to the test chassis and a sled with weights to the other end — and measure how much your motors can pull. The step-by-step guide is in the uus_plaan.md file.

**YouTube search terms:**
- `robot stall force test` (how a robot's pushing force is measured)
- `DC motor torque test DIY` (measuring motor torque)
- `friction coefficient measurement inclined plane` (measuring the friction coefficient with an inclined surface)

---

### Measuring communication latency (Analysis 2)

**Prerequisite:** the communication prototype from step 2 must work.

Measure the time from sending a command to receiving the response. Use the `send_cmd()` function above — `elapsed_ms` is already the latency of one measurement. Test first from the computer (USB), then from the phone (OTG) or over WiFi — does the latency change?

```python
import csv
import time

# Variant A (OTG) — use send_cmd() defined above
# Variant B (WiFi) — replace send_cmd() with HTTP request:
#   import requests
#   def send_cmd(cmd, speed=150):
#       start = time.time()
#       r = requests.get(f"http://192.168.4.1/cmd?c={cmd[0]}&s={speed}")
#       elapsed_ms = (time.time() - start) * 1000
#       return r.text, elapsed_ms

with open("latency.csv", "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["latency_ms"])
    for i in range(100):
        _, elapsed_ms = send_cmd("stop", 0)  # stop command — motor doesn't move
        writer.writerow([round(elapsed_ms, 2)])
        time.sleep(0.05)

print("Done! Data in latency.csv")
```

Then make a histogram in Jupyter Lab — the guide is in the uus_plaan.md file.

---

### Sensor statistics (Analysis 3)

Use the MCU to log the data. Add serial output in CSV format to the code:

```cpp
// Distance sensor logging (30 measurements per distance)
// Move obstacle to target distance, press "Enter" in Serial Monitor
void loop() {
  if (Serial.available()) {
    Serial.readStringUntil('\n');  // wait for user input

    Serial.println("Starting 30 measurements...");
    for (int i = 0; i < 30; i++) {
      float cm = measureDistance();
      Serial.println(cm, 2);  // copy to CSV
      delay(100);
    }
    Serial.println("---");
  }
}
```

Copy the Serial Monitor output into a CSV file, then continue in Jupyter Lab — the guide is in the uus_plaan.md file.

---

### Assessment criteria

| Category | Points | What is assessed |
|:---|:---|:---|
| Work files | 4 p | Code in the repo, schematics, photos of the build |
| Analysis | 4 p | 3 Jupyter notebooks with measurement results |
| Prototype | 4 p | Drive, communication, web interface, sensor — do they work? |
| Documentation | 4 p | Specification update with the conclusions from M1 |
| Q&A | 4 p | Demo at the meeting + discussion |
| **Total** | **20 p** | |

---

### Combined list of YouTube search terms

Search for these on YouTube — do not watch the whole video, scroll to the part where your problem is.

**Motors and drive:**
- `ESP32 DC motor L298N tutorial`
- `ESP32 PWM motor speed control`
- `TB6612FNG motor driver wiring`
- `DRV8833 ESP32 motor driver`
- `differential drive robot Arduino`

**Communication and WiFi:**
- `ESP32 USB OTG serial communication`
- `Termux Python serial USB OTG`
- `ESP32 WiFi web server Arduino`
- `ESP32 softAP access point`
- `ArduinoJson serial protocol`

**Web interface:**
- `ESP32 web server control motors`
- `FastAPI Python beginner tutorial`
- `robot web interface ESP32`

**Sensors:**
- `HC-SR04 ESP32 ultrasonic sensor`
- `VL53L0X time of flight ESP32`
- `TCS34725 color sensor Arduino`
- `ESP32 I2C scanner`
- `voltage divider 5V 3.3V Arduino`

**PCB design:**
- `KiCad 8 beginner tutorial`
- `Fusion 360 Electronics PCB`
- `ESP32 motor driver PCB design`
- `how to order PCB JLCPCB`

**General robot building:**
- `SMARS robot build` (inspiration for the chassis)
- `sumo robot Arduino build`
- `how to prototype electronics project`

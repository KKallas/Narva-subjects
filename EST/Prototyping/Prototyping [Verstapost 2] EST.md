## Prototüüpimine: Verstapost 2 — Võtmetehnoloogia prototüüp

**Maht:** 16 tundi | **Hindamine:** 20 punkti | **Kohtumine: L 21.03**

Selle verstaposti mõte on testida kriitilised tehnilised komponendid enne kui ehitad lõpliku roboti. Alusta ajamist — ilma sõitva šassiita ei saa midagi muud testida. Kui ajam töötab, lisa side. Kui side töötab, lisa veebiliides. Andurid saad testida kõrvalt maketeerimisplaadil.

See tähendab et verstaposti lõpuks on sul **sõitev testšassii** mida juhid veebilehelt — mitte ilus robot, aga tõestus et kõik põhisüsteemid töötavad. Kui midagi ei tööta, küsi enne kui kulutad kogu päeva otsimisele.

---

### 1. Ajami prototüüp

**Eesmärk:** mootorid peavad rattaid pöörama, suunda vahetama ja kiirust muutma.

**Mida vaja:**
- 2× DC mootorit käigukastiga (sinu V1 spetsifikatsioonist)
- Mootori draiver (L298N, TB6612FNG, DRV8833 — või mida tellisid)
- M5 Atom (või muu ESP32 plaat)
- Aku/toiteallikas (esialgu võib kasutada labori toiteplokki)
- Rattad + testšassii (loe alt)

**Lihtsaim testšassii — telefon ongi šassii:**

Prindi 2 kronsteini mis kinnituvad telefoni külge (klambrid ümber telefoni, kahepoolne teip, või kummipael). Iga kronstein hoiab ühte telge:
- **Veoteljed:** mõlemale poole telefoni üks mootor + ratas. Mootor kinnitub kronsteini sisse.
- **Tugi ees:** üks kuulratas (castor) või lihtsalt libe nupp mis maas libiseb — et telefon ei kukuks ette.

Tulemus: telefon lamab horisontaalselt, kaks mootorit/ratast külgedel, tugi ees. Kokku 3 toetuspunkti. Draiver ja MCU on teibiga telefoni peale kinnitatud või kõrval juhtmetega ühendatud.

See ei ole lõplik robot — see on testimisplatvorm. Oluline on et sõidab, mitte et ilus on.

**Ühendamine:**

MCU → mootori draiver → mootorid. Vaata oma draiveri andmelehte — ühendus sõltub draiveri mudelist. Põhimõte on alati sama:

| Draiveri sisend | Mida teeb | MCU pool |
|:---|:---|:---|
| IN1, IN2 (mootor A) | Suuna juhtimine | 2 digitaalväljundit |
| IN3, IN4 (mootor B) | Suuna juhtimine | 2 digitaalväljundit |
| ENA (mootor A) | PWM kiiruse juhtimine | 1 PWM väljund |
| ENB (mootor B) | PWM kiiruse juhtimine | 1 PWM väljund |

*NB: mõnel draiveril (TB6612, DRV8833) on ENA/ENB asemel eraldi PWM sisend. Vaata oma draiveri andmelehte. Kasuta oma MCU plaadilt vabu viike mis toetavad PWM-i.*

**Stardikood (Arduino IDE):**

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

**Sinu ülesanne:**
1. Ühenda mootorid ja lae kood üles — kas mõlemad rattad pöörlevad?
2. Kui üks ratas pöörleb vastupidi → vaheta selle mootori IN1/IN2 ühendused (või koodis)
3. Testi erinevaid PWM väärtusi (50, 100, 150, 200, 255) — mis on minimaalne väärtus kus rattad hakkavad pöörlema?
4. Pane kõik testšassiile ja testi kas sõidab — see šassii on su tõuketesti ja sidetesti alus

**YouTube otsisõnad:**
- `ESP32 DC motor L298N tutorial`
- `ESP32 PWM motor speed control`
- `TB6612FNG motor driver wiring Arduino`
- `DRV8833 motor driver ESP32`
- `differential drive robot Arduino`

---

### 2. Side prototüüp

**Eeldus:** ajami prototüüp (samm 1) peab töötama — side testi lõpus kontrollid kas käsk jõuab kohale sellega et mootor liigub.

**Kõik alustavad ühtemoodi:** esmalt testi käskude saatmist **arvutist** läbi USB-kaabli (MCU sisseehitatud FTDI). Saad kasutada Arduino Serial Monitori või Pythoni skripti arvutil. See töötab kõigil, olenemata lõplikust variandist. Hiljem asendad arvuti telefoni (variant A) või oma ESP32 WiFi lahendusega (variant B).

#### Samm 2a: Testi arvutist (kõik)

Lae MCU-le käsuprotokoll ja saada käske arvutist:

**MCU pool (Arduino):**

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

**Test arvutist (Python):**

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

**Sinu ülesanne:**
1. Ühenda MCU arvutiga USB-kaabliga (sama kaabel millega koodi üles laed)
2. Käivita Pythoni skript arvutil (või kirjuta Serial Monitorisse käsitsi: `{"cmd":"forward","speed":200}`)
3. Kas mootor liigub? Kas JSON vastus tuleb tagasi?
4. Kui jah → seerialprotokoll töötab, mine edasi sammu 2b juurde

#### Samm 2b: Asenda arvuti telefoni või WiFi-ga

**Variant A (telefon + USB OTG):** sama Pythoni skript mis arvutil, aga jookseb nüüd Termuxis telefoni peal. Telefon ühendub MCU-ga OTG kaabli kaudu.

1. Paigalda Termux (F-Droid'ist, Play Store'i versioon on aegunud)
2. Termuxis: `pkg install python` ja `pip install pyserial`
3. Ühenda MCU OTG kaabliga, kontrolli kas `/dev/ttyUSB0` ilmub
4. Käivita sama Pythoni skript — kas töötab nagu arvutil?

**Kui OTG ei tööta:** mõni telefon ei toeta USB host-režiimi. Kontrolli: Seaded → OTG / USB arendaja valikud. Kui ikka ei tööta — mine variant B peale.

**Variant B (WiFi):** lisa MCU-le WiFi veebiserver. Seerialprotokolli kood jääb alles (testimiseks arvutist), aga juhtimine käib nüüd WiFi kaudu.

Kui OTG ei tööta või valisid variandi B, teenindab ESP32 ise veebilehte WiFi kaudu.

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

Test brauseris: ühenda telefon/arvuti WiFi `SumoBot_1`, ava `http://192.168.4.1/cmd?c=f&s=200` — robot peaks edasi sõitma.

**YouTube otsisõnad:**
- `ESP32 USB OTG serial communication`
- `Termux Python serial USB OTG`
- `ESP32 WiFi web server motor control`
- `ESP32 softAP access point Arduino`
- `ArduinoJson ESP32 serial protocol`

---

### 3. Veebiliidese prototüüp

**Eeldus:** ajam (samm 1) ja side (samm 2) peavad töötama.

**Eesmärk:** üks veebileht millel on nupp → vajutad → mootor liigub. Tõesta et terve ahel "brauser → server → MCU → mootor" töötab.

#### Variant A: FastAPI telefonis (Termux)

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

Ava telefoni brauseris `http://localhost:8000` — või teisest seadmest telefoni IP-aadress (sama WiFi).

#### Variant B: ESP32 ise teenindab veebilehte

Kui kasutad WiFi varianti, lisa HTML otse ESP32 koodi:

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

**Sinu ülesanne:**
1. Käivita server (Termux või ESP32)
2. Ava veebileht telefonis/arvutis
3. Vajuta noolenuppe — kas robot liigub?
4. Kui liigub → veebiliidese baas töötab, edasi saab ehitada kaamera voogu ja klõpsa-ja-sõida loogika

**YouTube otsisõnad:**
- `ESP32 web server control motors`
- `FastAPI Python beginner tutorial`
- `Termux Python web server`
- `ESP32 HTML button motor control`
- `robot web interface ESP32 WiFi`

---

### 4. Anduri prototüüp

**Eesmärk:** tõesta et andur annab mõistliku näidu ja MCU suudab seda lugeda. Seda saab teha maketeerimisplaadil paralleelselt teiste sammudega — ei sõltu ajamist.

**Sideprotokollid andurite ja MCU vahel:**

Enamik andureid kasutab ühte kahest protokollist. Enne ühendamist tead mis protokolli sinu andur kasutab:

- **I2C** (Inter-Integrated Circuit) — 2 juhet (SDA + SCL), mitu andurit saab ühele siinile ühendada (igal oma aadress). Kasutavad: VL53L0X, TCS34725, BMP280 jne. Arduino koodis: `#include <Wire.h>`. Rohkem infot: https://en.wikipedia.org/wiki/I%C2%B2C
- **One-Wire** — 1 andmejuhe (+ toide + GND). Kasutavad: DS18B20 temperatuuriandur jt. Arduino koodis: `#include <OneWire.h>`. Rohkem infot: https://en.wikipedia.org/wiki/1-Wire
- **Trigger/Echo** (HC-SR04) — ei ole standardprotokoll, MCU saadab pulsi Trig viigule ja mõõdab Echo pulsi pikkust. Ei vaja eraldi teeki.
- **Analoog** — andur annab pinget 0–3.3V, MCU loeb `analogRead()` kaudu. Lihtsaim variant, aga vähem täpne.

#### Kaugusandur (HC-SR04 või VL53L0X)

Anduri ühendus sõltub sinu MCU-st ja andurist. Vaata oma anduri andmelehte. Põhimõte:

| Anduri viik | Kuhu ühendada | Märkused |
|:---|:---|:---|
| VCC | 5V (VIN) või 3.3V | Sõltub andurist — vaata andmelehte |
| Trig | Vaba digitaalväljund | Ainult HC-SR04 |
| Echo | Vaba digitaalsisend | HC-SR04: **Echo on 5V!** Kasuta pingejagurit (2 takistit) kui MCU on 3.3V |
| SDA, SCL | I2C siini viigud | VL53L0X ja TCS34725 kasutavad I2C-d |
| GND | GND | |

*NB: VL53L0X on 3.3V ja kasutab I2C-d — ei vaja pingejagurit. HC-SR04 Echo väljund on 5V, ESP32/M5 Atom sisend on 3.3V — ilma jagurita riskid MCU kahjustamisega.*

**HC-SR04 stardikood:**

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

#### Värviandur (TCS34725 või lihtsam analoogandur)

TCS34725 kasutab I2C ühendust (SDA + SCL). Paigalda teek: Arduino IDE → Libraries → "Adafruit TCS34725".

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

**Sinu ülesanne:**
1. Ühenda andur maketeerimisplaadil, lae kood, ava Serial Monitor
2. Kaugusandur: liiguta kätt anduri ees 5, 10, 20, 50 cm kaugusele — kas näidud vastavad?
3. Värviandur: proovi valge paber, must paber, punane/sinine — kas eristab?
4. Kui ei tööta → käivita I2C scanner (otsingusse `ESP32 I2C scanner`), kontrolli kas andur on üldse nähtav

**YouTube otsisõnad:**
- `HC-SR04 ESP32 distance sensor`
- `VL53L0X ESP32 I2C distance sensor`
- `TCS34725 color sensor Arduino`
- `ESP32 I2C scanner` (kui andur ei vasta)
- `voltage divider 5V to 3.3V` (HC-SR04 Echo joone jaoks)

---

### 5. PCB disaini alustamine

**Eesmärk:** alusta mootori draiveriplaadi disainimist. Plaat peab olema valmis tellimiseks enne 08.04 (2. tellimuse tähtaeg).

PCB disain on aeganõudev — ära jäta viimasele minutile. Alusta skeemist (schematic), see on põhimõtteliselt sama plokkskeem mis V1-s, aga komponentide tegelike jalgade ja väärtusetga.

**Minimaalne PCB sisu:**
- MCU ühenduspesad (M5 Atom vms ühendub pistikuribaga — ei joodeta otse plaadile!)
- Mootori draiveri IC + toetavad komponendid
- Mootori pistikud
- Aku pistik + toitelüliti
- Anduri pistikud (kaugus, värv, I2C)
- Toiteregulaator (kui aku pinge ≠ loogika pinge)

**Mida mitte teha:**
- Ära joodeta MCU arendusplaati otse PCB-le — kasuta pistikuribasid et saaksid plaati vahetada
- Ära unusta maandust — ühine GND kõigi komponentide vahel
- Ära kasuta liiga peenikesi radu mootori voolu jaoks (vähemalt 1 mm mootori radadele)

**YouTube otsisõnad:**
- `KiCad 8 beginner tutorial PCB design`
- `Fusion 360 Electronics PCB design`
- `ESP32 motor driver PCB design`
- `PCB design for beginners schematic to board`
- `how to order PCB JLCPCB` (või `PCBWay`)

---

### Tõuketest (Analüüs 1)

**Eeldus:** sõitev testšassii sammust 1.

Kinnita nöör testšassii külge, teise otsa kelk raskustega — ja mõõda kui palju su mootorid jaksavad vedada. Samm-sammult juhend on uus_plaan.md failis.

**YouTube otsisõnad:**
- `robot stall force test` (kuidas mõõdetakse roboti tõukejõudu)
- `DC motor torque test DIY` (mootori pöördemomendi mõõtmine)
- `friction coefficient measurement inclined plane` (hõõrdeteguri mõõtmine kaldu pinnaga)

---

### Side latentsuse mõõtmine (Analüüs 2)

**Eeldus:** side prototüüp sammust 2 peab töötama.

Mõõda aeg käsu saatmisest kuni vastuse saamiseni. Kasuta ülalpool olevat `send_cmd()` funktsiooni — `elapsed_ms` on juba ühe mõõtmise latentsus. Testi esmalt arvutist (USB), siis telefonist (OTG) või WiFi kaudu — kas latentsus muutub?

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

Edasi tee histogram Jupyter Lab'is — juhend on uus_plaan.md failis.

---

### Anduri statistika (Analüüs 3)

Kasuta MCU-d andmete logimiseks. Lisa koodi seerialväljund CSV formaadis:

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

Kopeeri Serial Monitori väljund CSV faili, edasi Jupyter Lab'is — juhend on uus_plaan.md failis.

---

### Hindamiskriteeriumid

| Kategooria | Punktid | Mida hinnatakse |
|:---|:---|:---|
| Tööfailid | 4 p | Kood repos, skeemid, fotod ülesehitusest |
| Analüüs | 4 p | 3 Jupyter notebooki mõõtmistulemustega |
| Prototüüp | 4 p | Ajam, side, veebiliides, andur — kas töötavad? |
| Dokumentatsioon | 4 p | Spetsifikatsiooni uuendus V1 järeldustega |
| Küsimused-vastused | 4 p | Demo kohtumisel + arutelu |
| **Kokku** | **20 p** | |

---

### YouTube otsisõnade koondnimekiri

Otsi neid YouTube'ist — ära vaata kogu videot, keri sinna kus sinu probleem on.

**Mootorid ja ajam:**
- `ESP32 DC motor L298N tutorial`
- `ESP32 PWM motor speed control`
- `TB6612FNG motor driver wiring`
- `DRV8833 ESP32 motor driver`
- `differential drive robot Arduino`

**Side ja WiFi:**
- `ESP32 USB OTG serial communication`
- `Termux Python serial USB OTG`
- `ESP32 WiFi web server Arduino`
- `ESP32 softAP access point`
- `ArduinoJson serial protocol`

**Veebiliides:**
- `ESP32 web server control motors`
- `FastAPI Python beginner tutorial`
- `robot web interface ESP32`

**Andurid:**
- `HC-SR04 ESP32 ultrasonic sensor`
- `VL53L0X time of flight ESP32`
- `TCS34725 color sensor Arduino`
- `ESP32 I2C scanner`
- `voltage divider 5V 3.3V Arduino`

**PCB disain:**
- `KiCad 8 beginner tutorial`
- `Fusion 360 Electronics PCB`
- `ESP32 motor driver PCB design`
- `how to order PCB JLCPCB`

**Üldine robotiehitus:**
- `SMARS robot build` (inspiratsioon šassii jaoks)
- `sumo robot Arduino build`
- `how to prototype electronics project`

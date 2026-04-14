# Narva College Technical Curriculum 2026/27 — Semester 1

## Building a Robot Dispensing System

### Big picture

All three courses build one system: a professional dispensing system for the MG400 robot arm. The robot and compressor are available — students build the toolkit that makes a €3000 robot useful.

First year lesson learned: electronics consumed all the time and we never reached machine learning. This time the structure is different: **every electronics task is tied to a specific data source** that will later be used in ML. Nobody builds a circuit that ends up in a cabinet — everything goes into the working system.

**Workstation**: polycarbonate worktable (100×100mm grid, 5mm metal holes). Sensors, mounts and accessories are 3D-printed modules that snap onto the table. Each team gets their own MG400 (5 robots, 4 teams — one spare).

**Motivation for the student**: Dobot's own software is unusable. You build something better. The MG400 costs €3000 and sits in warehouses because toolkits are not manufactured. Every tool you build and document is a potential product. Nordson EFD sells dispensing calibration for €15,000 — your version is a robot + €50 in electronics + your software.

### Teams

4 teams, up to 5 members each (max 20 students). Each team gets their own MG400 and their own worktable section. Within the team, roles are divided: someone is responsible for sensors, someone for software, someone for mechanics, someone for documentation. Roles rotate between milestones.

### Grading philosophy

Grading is positive — you receive full points for what you do correctly. If a prototype does not work but the student explains why and proposes alternatives — points are still achievable.

### Grading structure

**Smaller projects: 5 × 20 points = max 100 points**

Four grading categories per project:

* **Working files** (5p): code, schematics, design files — everything in the repo
* **Analysis** (5p): testing, validation, Jupyter notebook, Fourier/ML
* **Prototype** (5p): working physical implementation
* **Documentation** (5p): specifications, justifications, guides

**Integration project: max 70 points**

* Working files (17p)
* Analysis (17p)
* Prototype (18p)
* Documentation (18p)

**Total possible: 170 points.** The grade is calculated from the best 100.

The student chooses which projects to complete:
* 5 small projects = max 100p (enough for an A)
* Integration only = max 70p (ideally executed = C)
* Integration + some small ones = points can be added (e.g. integration 60p + 2 small projects 40p = 100p)
* 3 small projects = max 60p (enough for an E)

### Peer review (replaces Q&A points)

Previous year problem: reviewing 4 × 3h of defenses to find who asked what — unrealistic.

**New system: written peer review**

Each non-presenting student fills out a **structured form in MS Teams chat** for each other team:

```
TEAM: [name]
STRENGTH: [one specific technical thing that worked well]
QUESTION: [one technical question you want to know]
SUGGESTION: [one specific improvement]
```

Rules:
* Each student must submit feedback for **at least 2 teams** (out of 3 other teams)
* Feedback must be **technical and specific** — "it was good" does not count
* Feedback is **written** → automatic tracking, no need to review video
* Grading: 0p (did not submit), 1p (submitted but superficial), 2p (substantive)
* Max 4 bonus points per defense (2 teams feedback × 2p)

**Why this works**: student grades depend directly on whether they listened to others. And the written form means you do not have to watch 12h of video — you read the chat in 15 minutes.

### MS Teams transcription at defenses

Defenses take place in MS Teams (school requirement). Teams transcribes automatically.

**Workflow after defense:**
1. Download MS Teams transcript
2. Give the transcript to Claude with the instruction: "Extract each team's demo results, questions asked, and identified problems"
3. Claude structures → grading sheet by team
4. If transcription quality is questionable (names wrong, technical term distorted) → Claude marks those spots and asks only about them
5. Instructor reviews only the marked spots, not the entire recording

**Time savings**: 12h of video → 30 min of review.

### Grading scale

* **91–100 points**: A
* **81–90 points**: B
* **71–80 points**: C
* **61–70 points**: D
* **51–60 points**: E
* **0–50 points**: F

Minimum to pass: 51 points.

**Bonus points** (in addition to peer review): discovering instructor's errors, substantively helping other teams, exceptionally good collaboration.

### Git repo as the only submission channel

The instructor creates a git repo for each team before the semester begins. **What is not in the repo does not get graded.** No exceptions.

**Repo structure** (instructor creates template):

Each lab/task is a separate directory. If lab 2 builds on lab 1, **copy the necessary files** into the lab 2 folder and develop there. Yes, this duplicates code — but it is a deliberate compromise: beginners understand directories, not git branches. And the old lab never breaks.

```
team-N/
├── andmehoive/
│   ├── lab1/                 ← Raw ADC + FFT
│   │   ├── src/              ← Arduino code
│   │   ├── data/             ← CSV measurements
│   │   ├── notebooks/        ← Jupyter analysis (lab1_fft.ipynb)
│   │   └── docs/             ← schematics, photos, description
│   ├── lab2/                 ← Op-amp + 4 configurations
│   │   ├── src/              ← Arduino code (lab1 code + op-amp + digital filter)
│   │   ├── data/             ← 4 × 30 measurements
│   │   ├── notebooks/        ← Fourier comparison (lab2_comparison.ipynb)
│   │   └── docs/
│   ├── lab3/                 ← dP/dt interrupt + I2C
│   │   ├── src/              ← Arduino code (lab2 code + derivative + interrupt + VL53L0X)
│   │   ├── data/
│   │   ├── notebooks/        ← lab3_derivative.ipynb
│   │   ├── pcb/              ← KiCad/EDA schematic + layout + Gerber
│   │   └── docs/
│   ├── task4/                ← MG400 data collection
│   │   ├── src/              ← Python script (MG400 API + UART + CSV logging)
│   │   ├── data/             ← 500+ measurements
│   │   ├── notebooks/        ← task4_analysis.ipynb
│   │   └── docs/
│   ├── task5/                ← ML model
│   │   ├── src/              ← training scripts
│   │   ├── models/           ← pickle/joblib model file
│   │   ├── notebooks/        ← task5_ml.ipynb
│   │   └── docs/
│   └── integration/
├── nutilahendused/
│   ├── lab1/                 ← MG400 API + web interface
│   │   ├── src/
│   │   └── docs/
│   ├── lab2/                 ← ESP32 WiFi + HMAC
│   │   ├── src/
│   │   └── docs/
│   ├── lab3/                 ← MQTT + InfluxDB
│   ├── task4/                ← Unified UI
│   ├── task5/                ← VPN + API
│   └── integration/
├── 3d-print/
│   ├── lab1/                 ← Syringe holder
│   │   ├── fusion/           ← .f3d + .step exports
│   │   ├── stl/              ← print files
│   │   └── docs/             ← drawings, photos, measurements
│   ├── lab2/                 ← Worktable modules
│   ├── lab3/                 ← Electronics enclosure
│   ├── task4/                ← Generative design
│   ├── task5/                ← Test bench frame
│   └── integration/
└── README.md                 ← team overview, members, status
```

**Why this matters:**

1. **Grading**: the instructor only looks at the repo. If it is not committed → it does not exist → 0p
2. **Reproducibility**: another team must be able to build the project from the repo
3. **Analysis**: all work is preserved for later (curriculum development, examples for the next course)
4. **Git history**: commits show who did what and when — teamwork is transparent

**Fusion 360 files in the repo:**

Fusion 360 .f3d files are in the cloud, but the repo must contain:
* `.f3d` export (File → Export → .f3d) — full parametric model
* `.step` export — universal, opens in any CAD
* `.stl` — print file
* Screenshot/render if important views or notes need to be added
* 2D drawing as PDF (if required)

**Defense submission = Git tag:**

When a team is ready for defense, they create a tag:

```bash
git tag -a andmehoive-lab1 -m "Andmehõive Labor 1 kaitsmine"
git push origin andmehoive-lab1
```

Tag naming convention: `{course}-{project}`, for example:
* `andmehoive-lab1`, `andmehoive-lab2`, `andmehoive-task5`
* `nutilahendused-lab1`, `nutilahendused-integration`
* `3d-print-lab1`, `3d-print-task4`

**Tag = "this is my final version".** The instructor grades only the tagged state. If there is no tag → not submitted → 0p.

The tag must be created **72h before the defense**. Git history shows the exact time — no disputes.

**Rules:**
* Commit messages describe the work done concisely (not "update" or "fix")
* Large binary files (STL, GCODE, .f3d) → `.gitignore` + precise reference in the corresponding folder's README on where to get the file (e.g. Fusion 360 sharing link, Teams folder, Google Drive). "Files are in the cloud" is not sufficient — the README must contain the file name, location and access instructions
* Data files (CSV) MUST be in the repo — they are the basis for analysis
* Jupyter notebooks MUST be in the repo with outputs (Run All before committing)

### Submission requirements

* Defense = tag in the repo, **72h before the defense date**
* Teams have 5 min for presentation
* 10 min questions and discussion per team
* Written feedback to other teams in MS Teams chat during the defense

### Previous year work

Previous course work **is not built upon**. It is used as teaching material:
* "Look at what the previous course did — what went wrong and why?"
* One practical exercise: try to build from their documentation. What is missing? This teaches the value of documentation.

---

## Data Acquisition (6 ECTS)

*Building the nervous system*

### Concept

Build a pressure measurement system for the MG400 dispensing system and learn from that data. One pressure sensor, one breadboard — but four configurations that show step by step why each improvement is necessary. Fourier analysis makes the difference visible: you can see in frequency domain exactly what the filter removes.

The ML focus is specific and measurable: **how much material is left in the syringe?** In a pneumatic syringe (air → silicone plunger → silicone → nozzle ≥2mm), the shape of the pressure curve is affected by two opposing physical effects: (1) air compressibility — more air means slower pressure rise, and (2) material back-pressure in the nozzle — more material means greater resistance. The exact relationship between fill level and pressure curve shape depends on the specific system (syringe dimensions, nozzle diameter, material viscosity, temperature) — and determining this relationship is the ML task. By measuring the pressure curve shape at the moment the valve opens (response time, rise rate, plateau value), the remaining volume can be estimated — without an additional sensor.

### What you learn

* Analog-to-digital converter (ADC) fundamentals and error sources
* Operational amplifier (op-amp) usage for signal conditioning
* Analog and digital filtering methods
* Fourier analysis (FFT) for characterizing signals in time and frequency domains
* Derivative (dP/dt) and interrupts (IRQ) for real-time response
* I2C communication protocol, noise diagnostics and filtering
* Data collection, cleaning and visualization (Jupyter Lab, pandas, scipy)
* Training and validating machine learning models (scikit-learn)

### Work

Labs 1–3 build on **the same breadboard** — each lab adds a layer, not starting from scratch. The same MPX5700AP pressure sensor, the same ESP32, but the configuration changes and Fourier shows the effect of each change.

**Lab 1: Raw signal and first Fourier (34h)**

Connect the pressure sensor directly to the ESP32 ADC. Measure. See what comes out.

Specifically:
* **The first contact session starts with electronics and soldering basics** (~3h): soldering iron handling and safety, TH soldering on a practice board (resistors, capacitors, LEDs, header pins), SMD soldering (0805/1206 passive components). Passive vs. active components: what is a resistor, capacitor, LED, op-amp IC, microcontroller. Breadboard: how rows are connected, power rails. Multimeter: voltage, resistance, continuity. Nobody connects a sensor before soldering and component knowledge are in place.
* Connect MPX5700AP to the breadboard: power, GND, output → ESP32 ADC (directly, without adding anything in between)
* Arduino code: read ADC value at 100Hz sampling rate, send via UART to computer
* Collect 30 measurements in three pressure categories (low, medium, high — use MG400 compressor)
* Convert ADC values to Pascals using the MPX5700AP datasheet formula
* Simulate the circuit in Falstad, compare simulation with real measurements
* **Jupyter Lab — time domain**: visualize the signal, calculate mean, standard deviation, noise level
* **Jupyter Lab — Fourier (FFT)**: `scipy.fft` — view the signal in frequency domain. What frequencies are there? Where do the peaks come from? (MG400 motors, switch-mode power supplies, ground loops). What is the noise floor?

Result: the student sees that the raw signal is noisy and Fourier shows exactly which frequencies are interfering. Noise sources are revealed by measurement — this is part of the task, not a given answer.

*Required topics: ESP32 Arduino, UART, ADC, Jupyter Lab, Falstad, scipy.fft*

**Lab 2: Op-amp and filtering — Fourier shows the difference (30h)**

The MPX5700AP output is 0.2–4.7V, but the ESP32 ADC reads 0–3.3V. Add a signal chain and see with Fourier what changes.

Same breadboard, four configurations — the student **reconnects wires**:

| Config | Circuit | What Fourier shows |
|:---|:---|:---|
| 1 (lab 1) | MPX → direct to ADC | Raw data: noise peaks (motors, power supplies) + broad noise floor |
| 2 | MPX → voltage divider → ADC | Signal amplitude better, but noise still there |
| 3 | MPX → op-amp (offset + scaling) → ADC | Common-mode noise lower (op-amp CMRR), signal is in ADC range |
| 4 | Config 3 + digital filter in code (moving average) | High-frequency noise gone, only slow pressure change remains |

Specifically:
* Simulate in Falstad: voltage divider vs. op-amp
* Build the op-amp (LM358N) circuit on the same breadboard: offset (-0.2V) + scaling (upper end 3.2V)
* Measure all configurations with an oscilloscope
* Collect **the same 30 measurements with each configuration, same pressure** — 4 × 30 = 120 measurements in one CSV
* Add a digital filter to the Arduino code (moving average, N=10)
* **Jupyter Lab — four-way comparison**:
  * Time domain: 4 signals side by side — visually see what changes
  * Fourier: 4 spectra side by side — see how each step removes noise
  * SNR (signal-to-noise ratio) calculation for each configuration
  * Table: config × SNR × amplitude × noise level

**"Aha" moment**: Fourier shows specific noise sources (motor PWM, power supply switching, ground loops) and proves with numbers why each filtering step is necessary. The student must figure out what the frequencies are and where they come from — this is part of the task.

*Required topics: op-amp theory and practice, Falstad, oscilloscope, digital filtering, Fourier comparative analysis*

**Lab 3: dP/dt derivative, interrupt threshold and I2C calibration (24h)**

Two new capabilities: (A) a real-time safety mechanism based on the pressure curve derivative and (B) nozzle calibration with an I2C distance sensor. System pressure is ~2 bar — safe, but in case of a clog the system must react on its own.

**Part A: Pressure curve derivative and interrupt**

Normal dispensing: pressure rises slowly (dP/dt is small). Clogged nozzle: pressure rises quickly (dP/dt is large). Empty syringe: pressure drops (dP/dt is negative).

Specifically:
* Add derivative calculation to the Arduino code: `dP = (P_now - P_prev) / dt`
* Add a comparator (op-amp as Schmitt trigger) + ESP32 interrupt: if dP/dt exceeds the threshold → interrupt → STOP signal to the MG400
* **Fourier makes this mandatory**: the derivative **amplifies noise** (high-frequency component × 2πf). The derivative of the raw signal gives a false alarm every 20ms. The derivative of the filtered signal works correctly.
* Jupyter Lab: show side by side — raw signal dP/dt (noisy, constant false alarms) vs. filtered signal dP/dt (clean, responds only to real problems)
* Test: simulate a clogged nozzle (block the nozzle) — does the interrupt fire? How fast?
* Test: simulate an empty syringe — does the alarm trigger?

**Part B: I2C distance sensor for nozzle calibration**

A VL53L0X on the worktable measures the nozzle Z-height. When the syringe is changed manually, the system automatically checks position.

Specifically:
* Connect VL53L0X to ESP32 (I2C: SDA + SCL), test with a short cable — works
* Extend the cable to 30–50 cm, run it alongside the MG400 power cables — see what happens (noise, wrong values, timeouts)
* **Diagnosis**: how to tell that the I2C line is noisy? Oscilloscope shows distorted signal edges
* **Solution**: RC filter (100Ω + 100pF) on SDA and SCL lines, twisted pair, shielding
* Collect measurements: short wire vs. long noisy vs. long filtered
* Calibration sequence: MG400 moves the nozzle to a known position → VL53L0X measures → calculate offset X/Y/Z

* Design a **PCB for the entire system**: pressure sensor + op-amp + comparator (dP/dt interrupt) + VL53L0X connector sockets + ESP32 header pins. Schematic + layout + DRC.
* **Lab 3 defense includes PCB design review** — the instructor checks the schematic before ordering. No board goes to manufacturing without review.
* Gerber file generation and ordering (JLCPCB etc.) immediately after defense. The board arrives in time for task 4.

*Required topics: derivative and interrupt, comparator/Schmitt trigger, I2C protocol and noise filtering, PCB design and ordering*

**Task 4: Data collection with the MG400 (24h)**

Now the system has: pressure sensor (op-amp + filter), dP/dt alarm (interrupt), nozzle calibration (VL53L0X). If the PCB has arrived — solder and test. If not — continue with the breadboard. The MG400 is a data factory — it performs the same dispensing hundreds of times with different parameters.

Specifically:
* Write a Python script that: (a) sends a dispensing command to the MG400 (speed, pressure, trajectory), (b) reads ESP32 sensor data via UART, (c) logs everything to CSV
* Each measurement records: pressure curve (entire time series, not just one number), nozzle Z-height, MG400 parameters, timestamp
* Collect at least 500 measurements: 5 speeds × 5 pressures × 20 repetitions
* The MG400 does this automatically — the student writes the script and lets the robot work
* **Pressure curve analysis in Jupyter Lab**:
  * pandas: data cleaning, correlation matrix, distributions, outliers
  * **Response time vs. fill level**: measure the pressure curve shape at the moment the valve opens at different fill levels. Does the curve change and how? The relationship is not known in advance — this is the measurement and ML task.
  * Fourier: does the pressure curve spectrum change with fill level? (yes — more air = different resonance)
  * Question: what else affects response time besides fill level? Temperature? Material age? Nozzle diameter?

*Required topics: Python automation, MG400 API, pandas, time series analysis, Fourier*

**Task 5: Machine learning model (30h)**

Use the task 4 dataset for model training. One specific question: **how much material is left in the syringe?**

Specifically:
* Train/test split (80/20), cross-validation
* Linear regression → decision tree → random forest
* **Input features from the pressure curve**:
  * Time features: response time (from valve opening to inflection point), rise rate (dP/dt max), pressure plateau value, area under the curve
  * Fourier features: dominant frequency, spectral energy, frequency distribution shape
  * Environment: temperature (if measured), nozzle diameter, pressure setpoint
* **Output**: remaining volume (ml) — regression
* **Comparison 1 — features**: do Fourier features improve the model compared to time features alone?
* **Comparison 2 — signal quality**: is a model trained on op-amp data (lab 2 config 3-4) better than one trained on raw data (config 1)?
* **Comparison 3 — between teams**: whose model predicts better on their own device? Whose model works on another team's device? (Different syringes, materials, temperatures)
* MSE, R², residual analysis
* **Practical result**: threshold — "syringe has less than 2ml, replace!" At what accuracy can the model say this?

*Required topics: scikit-learn, model training and validation, feature engineering, time series features*

**Integration project: Automatic fill level monitoring**

Closed loop: MG400 dispenses → pressure sensor measures → model estimates remaining volume → web interface shows "syringe has ~4.2ml" → if below threshold → alert to operator. The interrupt ensures safety (clog → stop), ML provides information (when to replace the syringe).

### Lab progression summary

```
Lab 1: Raw ADC
  → "I get a number, but it's noisy"
  → Fourier shows: noise peaks + noise floor (sources revealed by measurement)

Lab 2: Op-amp + filter (4 configurations on the same board)
  → "Now the signal is clean"
  → Fourier shows: each step removes something specific

Lab 3: dP/dt derivative + interrupt + I2C + PCB design
  → "The system reacts on its own and self-calibrates"
  → Fourier shows: WHY you must filter before taking the derivative (noise × 2πf)
  → PCB is defended and ordered

Task 4: MG400 automatic data collection (PCB arrives)
  → "500 measurements, robot does the work"
  → Response time vs. fill level: relationship revealed by measurement

Task 5: ML model
  → "The model tells how much material is in the syringe"
  → Feature engineering: Fourier features vs. time features
```

### Contact hours schedule

* **[12.09.26]** Consultation session 1 (optional): electronics and soldering basics — soldering iron, TH and SMD soldering, passive and active components, breadboard, multimeter
* **[12.09.26]** ESP32 first program, ADC basics, Jupyter Lab introduction, first FFT
* **[03.10.26]** Lab 1 defense
* **[03.10.26]** Op-amp theory, Falstad simulation, four-way comparison
* **[~15.10.26]** **Consultation session 2**: practical op-amp help — how the offset and scaling circuit actually works, common mistakes, oscilloscope usage
* **[24.10.26]** Lab 2 defense
* **[24.10.26]** Derivative, comparator, interrupt + I2C noise diagnostics
* **[~05.11.26]** **Consultation session 3**: resolution determination — how to calculate the system's actual resolution (ADC bits × op-amp gain × noise level → effective resolution). PCB schematic pre-check.
* **[14.11.26]** Lab 3 defense (includes PCB design review → ordering immediately after)
* **[14.11.26]** MG400 API and automatic data collection in Python
* **[05.12.26]** Task 4 defense
* **[05.12.26]** Machine learning introduction: scikit-learn, time series features, pressure curve analysis
* **[16.01.27]** Task 5 defense
* **[TBD]** Integration project defense

---

## Smart Solutions (6 ECTS)

*Building the brain*

### Concept

The MG400 software is unusable, but the API works. Each team builds a **control station** for their MG400: a Raspberry Pi with a screen on the worktable, connected to the MG400 via LAN cable and to ESP32 sensors via USB. The RPI runs a web server — the operator controls the robot from a browser (phone, laptop, anywhere). Result: a mini industrial computer that replaces Dobot's software with something usable.

```
Phone/laptop (browser)
        │ WiFi
        ▼
   ┌─────────────────────┐
   │  RPI + screen        │  ← on the worktable, always connected
   │  Flask web server   │
   │  Python MG400 API   │
   │  Sensor reading     │
   └──┬──────────┬───────┘
      │ LAN      │ USB/UART
      ▼          ▼
   MG400      ESP32 (sensors)
```

### What you learn

* IPv4 fundamentals and routing (what is IP, subnet, gateway, why MG400 is on a LAN port)
* RPI setup and Linux command line
* MG400 API (TCP/IP socket) programming in Python
* Web interface creation (HTML/JS + Flask)
* ESP32 communication with RPI (USB/UART, WiFi, HTTP GET/POST, MQTT)
* User management and locking mechanism (one operator at a time, view mode for others)
* Digital Ocean droplet setup (cloud server)
* VPN setup (WireGuard) — secure remote tunnel
* Nginx reverse proxy — central portal that routes traffic to the correct robot
* Reverse VPN: ESP32 settings accessible remotely without socket-level encryption (VPN tunnel protects)
* MQTT and data logging (InfluxDB)
* System fault tolerance: watchdogs, heartbeat, recovery — how to detect that a service has crashed and recover without ruining work in progress

### Work

**Lab 1: RPI control station and MG400 API (28h)**

First task: get the RPI working and move the robot.

Specifically:
* RPI setup: OS installation, SSH, WiFi, static IP configuration
* **IPv4 fundamentals**: what is an IP address, subnet mask, gateway. Why MG400 is connected via LAN cable (its own subnet). How RPI talks to the MG400 (Ethernet) and the rest of the world (WiFi) simultaneously — two network interfaces, two subnets.
* MG400 TCP/IP API (port 29999 dashboard, port 30003 movement): write a Python wrapper
* Flask web server on the RPI: buttons for movement, position saving, compressor control
* RPI screen: show status (MG400 connected/not, last command, position)
* Test: open browser on phone → RPI IP → move the robot

*Required topics: RPI setup, Linux command line, IPv4 and routing, Python TCP/IP socket, Flask, HTML/JS*

**Lab 2: ESP32 sensors and RPI integration (26h)**

The ESP32 (Data Acquisition sensors) must talk to the RPI. Two options: USB/UART (simpler) and WiFi (more flexible).

Specifically:
* **USB/UART**: ESP32 → USB → RPI. In Python `pyserial`, ESP32 sends JSON for each measurement
* **WiFi alternative**: ESP32 in AP mode, RPI connects via WiFi. ESP32 serves an HTTP API (GET /data)
* **Simple HTTP communication**: ESP32 sends data to the RPI web server (HTTP POST) or RPI requests from ESP32 (HTTP GET) — socket-level communication without a complex protocol. The student understands what an HTTP request and response is.
* **MQTT introduction**: ESP32 sends data via MQTT (publish), RPI listens (subscribe). Mosquitto broker runs locally on the RPI initially. This prepares for lab 3 (MQTT on the droplet) and task 4 (data logging).
* RPI Flask service reads ESP32 data AND controls the MG400 — one web page shows both
* RPI screen: real-time sensor data + MG400 status
* Test latency: measure time from command to response (USB vs WiFi vs MQTT)

*Required topics: ESP32 WiFi/UART, pyserial, HTTP GET/POST, MQTT basics, JSON API, RPI integration*

**Lab 3: Digital Ocean droplet and VPN (30h)**

The control station works locally. Now make it remotely accessible — securely.

Specifically:
* **Digital Ocean droplet setup**: create a cloud server (Ubuntu), SSH access, firewall configuration (ufw)
* **WireGuard VPN setup**: the droplet is the VPN server, each team's RPI is a VPN client. Each RPI gets a fixed VPN IP (10.0.0.1, 10.0.0.2, 10.0.0.3, 10.0.0.4). The tunnel is always up.
* **Nginx reverse proxy on the droplet**: one central web page showing all connected robots:
  ```
  https://robots.kool.ee/
    ├── Robot 1 [●online]  → click → /robot/1/ → proxy_pass http://10.0.0.1:5000/
    ├── Robot 2 [●online]  → click → /robot/2/ → proxy_pass http://10.0.0.2:5000/
    ├── Robot 3 [○offline]
    └── Robot 4 [●online]  → click → /robot/4/ → proxy_pass http://10.0.0.4:5000/
  ```
  The user sees the RPI web page exactly as if sitting at the lab desk — but from somewhere remote.
* **Reverse VPN logic**: RPI connects to the droplet → the droplet sees the RPI → nginx routes user traffic through the VPN tunnel to the RPI. Result: ESP32 settings and MG400 control accessible remotely **without the ESP32 having to do encryption** — the VPN tunnel protects all traffic.
* **IPv4 routing in practice**: the RPI has 3 networks — MG400 LAN (e.g. 192.168.1.x), local WiFi (e.g. 192.168.0.x), VPN tunnel (10.0.0.x). How the routing table works, why packets reach the right destination.
* **Robot status page** (simple Flask/HTML on the droplet): pings VPN IPs, shows who is online, link to each robot
* Test: sit at home, open browser, go to robots.kool.ee, click on your team's robot, control the robot on the lab worktable

*Required topics: Digital Ocean, Linux server, SSH, firewall, WireGuard VPN, nginx reverse proxy, IPv4 routing*

**Task 4: MQTT data logging and unified interface (30h)**

Bring all data flow into one system: sensors → RPI → cloud → history. The central portal shows all robots' status.

Specifically:
* Mosquitto MQTT broker on the droplet (same server as VPN and nginx)
* ESP32 → RPI → MQTT: sensor data from every measurement
* RPI → MQTT: MG400 position and status
* InfluxDB on the droplet: all measurements saved automatically
* **Unified web interface on the RPI** (Flask): control + real-time sensors + historical graphs + CSV/JSON export
* **Extending the central portal** (on the droplet): add the latest measurement, status, fill level estimate to the robots list — one glance shows all 4 robots' state
* **User locking** — only one operator at a time:
  * When someone opens robot control → lock engages, others see "Robot 2 — controlled by: kaspar, since 14:32"
  * **View mode** for others: camera feed, sensor data, MG400 status — all visible in real time. But buttons are grayed out, commands cannot be sent.
  * **Doorbell**: if you want to use the robot but someone else is controlling → "Please release" button sends the other person a notification
  * **Admin override**: if the connection dropped and the lock stayed on (user's browser closed) → admin password can unlock
  * Lock releases automatically if the user has not sent anything for 5 min (timeout)
* Dispensing "recipes": save parameter sets and repeat them
* Camera view (USB camera on the RPI): operator sees what the robot is doing
* ESP32 offline buffer: if WiFi drops, buffer 100 messages in LittleFS, send when connection recovers
* UX test: give the system to another team — can they figure it out in 5 minutes?

*Required topics: MQTT, Mosquitto, InfluxDB, Flask dashboard, nginx, session management, locking mechanism, UX*

**Task 5: Fault tolerance, REST API and LLM integration (34h)**

The RPI does 5 things at once: Flask, MG400 communication, ESP32 reading, MQTT, camera. One of them crashes. How to detect and recover without ruining a dispensing in progress?

**Part A: Cheap hardware limitations (academic focus)**

The RPI is a €50 computer controlling a €3000 robot. This is a good trade-off — but it has real limitations that an expensive industrial computer does not feel. The goal **is not** to make the RPI into an industrial controller. The goal is to **understand the limitations, measure them and design around them**.

Specifically:
* **Measure the limitations**: RPI Flask serves a web page → simultaneously ESP32 sends data via USB → simultaneously MG400 TCP socket waits for a response. Python GIL means these **do not truly run in parallel**. Measure: what happens when all three occur simultaneously? How long does Flask block when the MG400 response is delayed? How many ESP32 measurements are lost during that time?
* **Where it stumbles**: MG400 TCP response waiting blocks web page loading. MQTT publishing takes time when the network is slow. Measure and document each limitation with a specific number.
* **Simple design around limitations**: not complex watchdogs, but simple architecture — separate processes (not threads) for critical services, queue for data exchange, timeouts on every socket connection. If MG400 does not respond in 2 seconds → do not wait, mark "connection lost" and continue with the others.
* **Safe state is simple**: if something is wrong → compressor off. Never continue automatically after a fault. This does not require complex logic — only discipline.
* **Practical test**: pull the ESP32 USB cable out during dispensing. Pull the MG400 LAN cable out. Turn off WiFi. What happens in each case? Does the system go to a safe state? Does it recover when the connection returns? Document each scenario: what happens, how long it takes, whether the product is ruined.
* **Jupyter Lab analysis**: collect a fault log (which service, when, how long it lasted). Visualize: are faults correlated with load? What is the average recovery time? **Where is the boundary** where the RPI is no longer sufficient and real industrial hardware is needed?

**Part B: REST API and LLM**

Specifically:
* REST API on the RPI: /status, /dispense, /history, /export — documented, JSON
* API accessible also through the central portal: robots.kool.ee/robot/1/api/ → proxy to RPI API
* Time lock: remote control endpoints only work when the local operator has activated them on the RPI screen (time-based permission)
* README endpoint (/api) describing all endpoints — language models can read it and understand what the system does
* Demonstrate full cycle: operator activates from RPI → remote user (or LLM) sends API command through the portal → robot dispenses → data is saved → automatic locking on timeout
* API audit log: who, when, what was requested

*Required topics: watchdog, heartbeat, fault tolerance, safe state, REST API design, time lock, LLM integration, audit log*

**Integration project: Complete control station**

RPI control station as a complete product: cloning one SD card → a new MG400 is immediately usable. Setup: connect LAN to MG400, connect ESP32 via USB, power on. Installable with one script. Automatic VPN connection. Locking works. Fault tolerance works. Documentation sufficient for another person to set up the system.

### Contact hours schedule

* **[12.09.26]** RPI setup, IPv4 fundamentals, MG400 API, first movement
* **[12.09.26]** Flask introduction, HTML/JS basics
* **[03.10.26]** Lab 1 defense
* **[03.10.26]** ESP32 ↔ RPI communication (USB/UART and WiFi)
* **[~15.10.26]** **Consultation session 1**: IPv4 routing in practice — what is subnet, gateway, why RPI has 3 network interfaces, how packets travel. Hands-on: `ip route`, `ping`, `traceroute`.
* **[24.10.26]** Lab 2 defense
* **[24.10.26]** Digital Ocean, Linux server, WireGuard VPN
* **[~05.11.26]** **Consultation session 2**: VPN in practice — WireGuard setup step by step, public/private key logic, why the tunnel works behind NAT, how to check if the tunnel is up.
* **[14.11.26]** Lab 3 defense
* **[14.11.26]** MQTT, InfluxDB, unified interface
* **[~25.11.26]** **Consultation session 3**: nginx reverse proxy — how the droplet routes traffic to the correct RPI, proxy_pass logic, HTTPS certificate (Let's Encrypt), troubleshooting when the proxy does not work.
* **[05.12.26]** Task 4 defense
* **[05.12.26]** REST API, time lock, LLM integration
* **[16.01.27]** Task 5 defense
* **[TBD]** Integration project defense

---

## 3D Printing and CAD (6 ECTS)

*Building the body*

### Concept

You start in Blender — make a simple object and learn how hard it is to keep a model "watertight" (solid) when working with vertices and polygons. Every wrong click creates a hole, a flipped normal, a non-manifold edge. This gives a very intuitive understanding of what Fusion is good at: in Fusion the model is *always* solid, because the tool does not let you create invalid geometry.

Academic core: **how an object's shape affects manufacturing**. Simple example: rotate an object in 4 orientations and see what happens to print time, support material volume and strength. The slicer cuts the model into layers — each layer's cross-section area and perimeter length determine print time. This is integration in practice: print time ≈ sum(layer_time) over all layers, where layer_time depends on the cross-section.

### What you learn

* Polygon modeling (Blender) — what is a mesh, why STL is triangles, where errors occur
* The path from Blender to the printer: mesh → STL export → slicer → G-code → print. What goes wrong at each step (open edges, flipped normals, walls too thin, non-manifold geometry).
* Parametric modeling (Fusion 360) — why constraint-based design is better for manufacturing than freeform modeling
* Design inputs: physical (strength, mass), business (print time, material cost), aesthetic (surface quality, shape)
* Orientation optimization: integration layer by layer → predicting print time, supports and strength
* Assembly and fastener design (snap-fit, print-pause, metal inserts)
* Mechanical simulation (Fusion 360 FEA)
* Generative design and comparison with manual design
* Technical drawings per ISO standards

### Work

**Lab 1: From Blender to the printer — the path and pitfalls (34h)**

The first lab does NOT start with Fusion. Start with Blender — make a pen holder for the MG400 tool flange. The robot draws on the first day. Then fix it in Fusion and later replace the pen with a syringe.

**Part A: Blender and mesh-based modeling**

First print: **pen holder for the MG400 tool flange**. The simplest possible tool — a tube that holds a pen and attaches to the flange. The robot draws on the very first day.

Specifically:
* Make a pen holder in Blender — tube + flange mount
* Export STL — open in slicer. What happens? (likely: open edges, flipped normals, walls too thin, non-manifold spots)
* **Mesh diagnostics**: what is a triangle mesh, why STL is only triangles, what is normal direction and why it matters (the slicer does not know what is "inside" and "outside"). How to find and fix errors (Blender 3D Print toolbox, Meshmixer).
* Fix errors, print, mount on MG400, **draw**. By the end of the first day: the robot moves and leaves a mark on paper. The pen holder is imprecise and wobbly — but it works.

**Part B: FDM physics — why shape affects everything**

Same pen holder, but now understand WHY the printer behaves the way it does:

**Overhang and the 45-degree rule:**
* Print the same wall at 30, 45, 60 and 90 degree angles (relative to vertical)
* Below 45 degrees — each layer rests on the previous one by ~50%, enough that the plastic does not sag
* 90 degrees (horizontal ceiling) — nothing supports it, plastic sags down → support material needed → time + material + poor surface underneath
* **Why exactly 45 degrees?** Geometry: layer height 0.2mm, layer offset 0.2mm = 45 degree diagonal. Below that angle the previous layer does not reach far enough.

**Straight vs. round:**
* Print two versions: straight-walled holder and round-walled holder (same volume, same wall thickness)
* Measure: print time, surface quality. Round is slower (the head must constantly change direction, acceleration/deceleration at every step) and the surface is stepped (circles → polygon between layers).
* **Why straight is better for FDM?** The nozzle moves in a straight line at full speed. A curve means constant deceleration and acceleration. Material usage is the same, but time and quality are worse.

**Orientation and strength:**
* Same holder, 4 orientations — print all
* **Tensile test for each orientation**: FDM inter-layer bonding is the WEAKEST point. Tension along the layer direction = strong (the plastic itself). Tension perpendicular to layers = weak (inter-layer adhesion). Orientation determines where the weak point is.
* Jupyter Lab: visualize layer cross-sections for each orientation, calculate print time mathematically (sum of layer perimeters and areas), compare with slicer estimate

**Practical conclusion**: orientation choice is NOT aesthetic — it is mathematical optimization where the inputs are speed, strength and support material cost. The designer must know these rules BEFORE starting to draw a part in Fusion.

**Part C: From Blender to Fusion — why constraints drive design**

The pen holder worked, but it is wobbly and dimensions do not match. Now make the same thing in Fusion:
* Measure the MG400 tool flange with calipers — enter measurements as parameters
* Pen diameter, angle, height — all parametric, changeable
* Export STL — no errors in the slicer (because Fusion generates correct mesh)
* Print, mount on MG400 — drawing is immediately better (no wobble, dimensions match)
* **This is the point of Fusion**: the design input is measured constraints (flange dimensions, pen diameter), not eyeballing

**Part D: From pen to syringe**

Now replace the pen with a syringe — same mounting point, but add:
* Syringe diameter (larger than the pen) — change the parameter in Fusion
* Pneumatic connection point (MG400 compressor hose)
* Test 3 syringe sizes: 5ml, 10ml, 20ml — change parameter, export, print. One model, many variants.
* Print, test on MG400: does the syringe hold? Can you swap it with one hand?

Progression: Blender pen holder → Fusion pen holder → Fusion syringe holder. Each step adds a constraint.

*Required topics: Blender basics, mesh/STL diagnostics, slicer and orientation, print time integration, Fusion 360 parametric design, FDM constraints*

**Lab 2: Worktable modules and fasteners (30h)**

Design modules that mount into the worktable's 5mm holes. Here constraints come into play that Blender cannot solve.

Specifically:
* Design a universal mounting foot that fits the 5mm hole pattern and 100mm grid — dimensions must be **precise** (this is why Fusion, not Blender)
* A sensor-specific top for each sensor that snaps onto the foot (snap-fit)
* Spring mechanism fastener: push down, snap, done. Pull up, released.
* **Bolt-nut-washer compression — PLA stronger than the material**:
  * FDM inter-layer adhesion is weak in tension (layers pull apart). But in compression PLA is strong.
  * Bolt + nut + washer compresses layers together → inter-layer force changes from tension to compression → part withstands several times more
  * Same principle as prestressed reinforced concrete: metal (bolt) carries tensile load, plastic (PLA) carries compression. Washer distributes force over a larger area → does not dig into the plastic.
  * **Practical test**: print the same part (a) without bolts, (b) bolted through. Tensile test with MG400. Measure failure load. Document the difference.
  * Design rule: where to place bolt holes so that layers are always under compression? Where are the load paths?
* Mechanical simulation (Fusion FEA): does the snap-fit hold? Where are the stress concentrations?
* Fusion 360 2D drawing: manufacturing instructions for another person

*Required topics: Fusion 360 assemblies, snap-fit design, compression fasteners, FEA, 2D drawing*

**Lab 3: Electronics enclosure and print-pause (28h)**

An integrated enclosure that holds the ESP32, op-amp board and all connections. Mounts as a worktable module.

Specifically:
* Integration graph (draw.io): which components, how they connect
* Bill of materials (BOM)
* Enclosure: ventilation openings, cable entries, mounting elements
* Print-pause workflow: pause the print, insert nuts/magnets/inserts, continue
* Assembly guide clear enough for another team to replicate

*Required topics: integration graph, BOM, print-pause, assembly guide*

**Task 4: Improving an existing design — three approaches (30h)**

The instructor has existing 3D printed + bolted designs: pressure tube nozzles, external solenoid mounts, syringe tips. They work, but are first versions. The student picks one and improves it along **one specific metric**:

**(A) Manufacturing speed** — same strength, but prints faster
**(B) Strength** — same print time, but withstands more
**(C) Number of use cycles** — same shape, but durability testing shows longer lifespan

Specifically:
* Analyze the existing design: where is material wasted? Where is the weak point? What orientation was it printed in and why?
* **Approach 1 — manual engineering design**: ribs along load paths, wall thickness changes, FDM-friendly geometry, bolt hole placement
* **Approach 2 — Fusion 360 generative design**: define mounting points, loads, keep-out zones — let the algorithm propose
* Print all 3 versions (original + manual + generative)
* Orientation optimization for each version (using the lab 1 method — integration)
* Repeatable test with MG400: the robot applies the same load to each version, measure results
* **Comparison table**: print time, mass, strength, number of use cycles, support material cost
* Is the manual improvement better than generative? Why? (usually yes — because the engineer knows FDM constraints, the algorithm does not)

*Required topics: existing design analysis, generative design, FEA, FDM optimization, test methodology*

**Task 5: ISO drawing and CNC ordering (24h)**

Design a metal part (worktable module, mount, etc.) and order it as a 2D CNC service externally. **The ISO drawing is the order document** — if the drawing is wrong, the wrong part arrives. This validates whether the student can produce a functional drawing.

Specifically:
* Design a metal part in Fusion that requires CNC cutting (e.g. worktable mounting plate, robot base plate, test bench element)
* **ISO technical drawing**: views, sections, dimensions, tolerances, surface roughness, material specification
* GD&T for critical surfaces (e.g. hole position tolerance that must match a 3D printed insert)
* Tolerance analysis: CNC part (±0.1mm) + 3D printed insert (±0.3mm) — do they fit together?
* **Instructor review before ordering** — same logic as PCB in Data Acquisition. No part goes to manufacturing without review.
* Order from a 2D CNC service (laser cutting, milling, etc.). The part arrives by the start of semester 2.
* **Validation**: when the part arrives — measure with calipers. Do the measurements match the drawing? Does the 3D printed insert fit? If not → why? Was the drawing wrong or did the CNC manufacturer make an error?

*Required topics: ISO technical drawings, GD&T, tolerance analysis, CNC service ordering and validation*

**Integration project: Complete mechanical package**

All mechanical components with production-ready documentation: syringe holder + sensor modules + electronics enclosure + test bench frame. A package from which another person can assemble the system.

### Contact hours schedule

* **[11.09.26]** Blender basics, mesh and STL, polygons → triangles → errors
* **[11.09.26]** Slicer, orientation, first print — and why it is not ideal
* **[02.10.26]** Lab 1 defense (Blender + Fusion + orientation analysis)
* **[02.10.26]** Fusion assemblies, snap-fit, metal inserts, spring mechanisms
* **[23.10.26]** Lab 2 defense
* **[23.10.26]** Print-pause, component insertion, enclosure design
* **[13.11.26]** Lab 3 defense
* **[13.11.26]** Generative design workflow
* **[04.12.26]** Task 4 defense
* **[04.12.26]** ISO drawings, GD&T, CNC communication
* **[16.01.27]** Task 5 defense
* **[TBD]** Integration project defense

---

## Course interplay

```
Semester 1 (Sept 2026 — Jan 2027):
┌──────────────────────────────────────────────────────────┐
│ Data Acquisition      Smart Solutions       3D Printing  │
│ ────────────────      ───────────────       ───────────  │
│ L1: Raw ADC + FFT     L1: RPI + MG400 API  L1: Holder   │
│ L2: Op-amp + 4 conf.  L2: ESP32 ↔ RPI      L2: Modules  │
│ L3: dP/dt IRQ + I2C   L3: DO droplet + VPN L3: Encl.    │
│ T4: MG400 data coll.  T4: MQTT+DB+UI       T4: GenDes   │
│ T5: ML model          T5: REST API + LLM   T5: Frame    │
└──────────────────────────────────────────────────────────┘
```

### Fourier analysis throughout Data Acquisition

```
Lab 1: FFT shows raw signal noise (motors, power supplies, ground loops)
    ↓
Lab 2: FFT shows each configuration's effect (4 spectra side by side)
    ↓
Lab 3: FFT shows why the derivative needs filtering (noise × 2πf)
    ↓
Task 4: FFT shows whether the pressure curve spectrum changes with fill level
    ↓
Task 5: FFT features → ML feature engineering
```

### Pressure curve logic and ML focus

Pneumatic syringe (air → silicone plunger → silicone → nozzle ≥2mm):

```
Valve opens → pressure starts rising → multiple physical effects simultaneously:

  Effect 1: Air compressibility
    → more air in the cylinder = pressure rises more slowly
    → less air = pressure rises faster

  Effect 2: Material back-pressure in the nozzle
    → more material = greater resistance to flow
    → less material = lower resistance

  Effect 3: Material incompressibility
    → silicone does not compress = transmits pressure immediately to the nozzle
    → air compresses = absorbs energy

Combined effect of these → pressure curve shape changes with fill level
Exact relationship revealed by measurement → ML model learns it
```

* **Clogged nozzle**: pressure rises sharply and does not drop (dP/dt large → interrupt)
* **Nozzle ≥2mm**: previous year lesson learned — a finer nozzle clogs

**ML question**: the pressure curve shape depends on fill level, but also on temperature, material age and nozzle diameter. The relationship is not linear or obvious — determining it is the ML task. No additional sensor (scale, optics) is needed — the pressure curve contains sufficient information.

**Practical value**: the system tells the operator "syringe has ~3.5ml, enough for ~12 more dispensings". No existing Dobot tool offers this.

### Hardware dependency timeline

Three courses in parallel — hardware must not conflict. Solution: **2 ESP32 per team** (€5 each), one always stays on the breadboard, the other connected to the RPI.

```
            SEPT        OCT         NOV         DEC         JAN
Data Acq.   ESP32-A     ESP32-A     ESP32-A     ESP32-A     Jupyter
            breadboard  breadboard  breadboard  +RPI+MG400  (data
            (only)      (only)      +PCB des.   (integr.)   only)

Smart Sol.  RPI+MG400   RPI+ESP32-B RPI         RPI+all     RPI+all
            (API)       (comm.)     +DO droplet (integr.)   (API+LLM)

3D Print    Fusion 360  Fusion 360  Fusion 360  Fusion 360  Fusion 360
            printer     printer     printer     printer     (no HW
            (no electronics needed)                          needed)
```

**Conflict-free**: ESP32-A (Data Acquisition, breadboard) and ESP32-B (Smart Solutions, RPI USB) work in parallel. MG400 is Sept-Oct only in Smart Solutions' hands (API learning), Nov-Dec Data Acquisition joins (data collection). 3D Printing does not need electronics at all.

**Integration point** (Nov-Dec): Task 4 in both courses — all hardware comes together for the first time. This is planned, not a conflict.

### What each course produces for the others

| Source | Output | Consumer |
|:---|:---|:---|
| Data Acquisition L1-L2 | Pressure sensor + op-amp + filter (on breadboard) | Data Acquisition T4 |
| Data Acquisition L3 | dP/dt interrupt safety mechanism + VL53L0X nozzle calibration | Data Acquisition T4 |
| Data Acquisition L3 | PCB (Gerber ordered) | Data Acquisition T4 |
| Data Acquisition T5 | Trained ML model (fill level estimation from pressure curve) | Data Acquisition Integration |
| Smart Solutions L1 | RPI control station + MG400 Python wrapper | Data Acquisition T4 |
| Smart Solutions L2 | ESP32 ↔ RPI integration | Data Acquisition T4 |
| Smart Solutions L3 | VPN remote tunnel (Digital Ocean + WireGuard) | Smart Solutions T5 |
| Smart Solutions T4 | MQTT + InfluxDB + unified web interface on RPI | Data Acquisition T4-T5 |
| Smart Solutions T5 | REST API + LLM interface | Smart Solutions Integration |
| 3D Printing L1 | Syringe holder for MG400 (pneumatics, quick-change) | Data Acquisition T4, Smart Solutions L1 |
| 3D Printing L2 | Worktable modules (sensor and VL53L0X mounts) | Data Acquisition L3 |
| 3D Printing L3 | Electronics enclosure (ESP32 + op-amp + PCB) | 3D Printing Integration |
| 3D Printing T5 | Test bench frame (aluminum + printed inserts) | 3D Printing Integration |

### Component ordering

**BEFORE the semester starts** (July 2026) order:

**RPI control station (one per team):**
* Raspberry Pi 4 (4 pcs + 1 spare) — needs Ethernet + WiFi + USB + HDMI
* 7" touchscreen or HDMI monitor (4 pcs)
* SD cards 32GB+ (8 pcs — spares)
* RPI power supplies (4 pcs)
* LAN cables for MG400 connection (4 pcs)
* Digital Ocean account (one for the course, each team gets their own droplet)

**Electronics:**
* ESP32 / M5 Atom Lite — **2 per team** (ESP32-A for breadboard, ESP32-B for RPI). Total 8 pcs + 4 spare = 12 pcs
* MPX5700AP pressure sensor (10 pcs)
* LM358N op-amp (20 pcs)
* VL53L0X distance sensor I2C (10 pcs)
* Resistor and capacitor kit (5 kits) — including 100Ω + 100pF for I2C filter
* Breadboards (20 pcs)
* Jumper wire kits (10 kits)
* Soldering irons + solder (5 kits, one per team)
* USB cables (20 pcs)

**Dispensing supplies:**
* Syringes 5ml, 10ml, 20ml (20 pcs of each size)
* Dispensing nozzles ≥2mm (50 pcs — consumable)
* Silicone / dispensing paste for testing (5 tubes)

**3D printing:**
* PLA filament (10 kg)
* PETG filament (5 kg — for enclosures)
* Heat-set inserts (M3 nuts, 100 pcs)

**Already available:**
* MG400 robot arms (5 pcs) + compressors
* Polycarbonate worktables (100×100mm grid, 5mm holes)
* 3D printers
* Oscilloscope (lab)

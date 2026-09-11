# Narva College Technical Curriculum 2026/27 — v2

## Building the Tag-Assembly Cell

### Big picture

All three semester-1 courses and the semester-2 Prototyping course build one machine: an **MG400 robot cell that assembles the Cyber Tag Arms tag**. The tag is an M5 AtomS3 (24×24 mm, 0.85" screen), a battery module, and a polycarbonate glass glued over the screen so that a suction cup can lift the finished tag by its face. The robot dispenses transparent UV resin on the bezel, picks the glass with a suction cup, places it, cures it with a UV LED on the nozzle, photographs the result and moves the tag to the finished tray.

The robot, the compressor (Dobot mini vacuum pump box) and the base Python software for the MG400 are given. Dobot's own software is not used. Students build the tool, the fixtures, the electronics, the control station, the data pipeline and the models that make a €3000 robot do useful work. Every tool built and documented is a potential product: nobody sells this toolkit for the MG400.

First-year lesson: electronics ate all the time and machine learning never happened. This year **every electronics task is tied to a data stream that is later used for learning**, and every course produces parts of the same cell. Nothing is built that ends up in a cabinet.

**Workstation**: polycarbonate worktable (100×100 mm grid, 5 mm holes). Fixtures, trays, sensor posts and enclosures are 3D-printed modules that snap onto the table. Each team gets its own MG400 (5 robots, 4 teams of 3, one spare), its own pump box and suction kit, and its own table section.

**One assembly cycle** (semester-1 scope is the glass; plugging the battery module is a semester-2 stretch goal):

1. An AtomS3 is placed into the gluing jig from the source tray.
2. Valve energized, pump in blow mode → the syringe dispenses resin dots or a bead on the screen bezel. Pressure curve logged.
3. Valve released, pump in suction mode → the cup picks a PC glass from the source tray. Vacuum curve logged; pick success is visible in it.
4. Glass placed on the resin, short press, blow-off to release.
5. Robot moves so the UV LED is over the tag and the syringe tip is outside the light cone. LED on for a few seconds. Cured through the glass.
6. Nozzle camera takes an image. Tag moved to a finished slot.
7. One record is written: cycle id, team, robot parameters, dispense time, cure time, both curves at 100 Hz, syringe fill (ground truth), image, outcome label.

```
                          ┌────────────────────────────┐
  Browser (anywhere) ───► │ RPI control station        │ ◄── LAN ── MG400 (+ DO to pump box, fallback)
                          │ Flask + base MG400 package │
                          │ workflow recorder / replay │
                          └──────┬──────────────┬──────┘
                                 │ USB/UART      │ WiFi (MJPEG)
                                 ▼               ▼
      ┌──────────────────────────────────┐   ┌──────────────┐
      │ TOOL BOARD on the arm (ESP32)    │   │ nozzle cam   │
      │ • valve driver (3/2, spring ret.)│   │ (ESP32-CAM / │
      │ • P sensor, syringe branch       │   │ AtomS3R-CAM) │
      │ • vacuum sensor, cup branch      │   └──────────────┘
      │ • pump box on/off + vac/blow     │
      │ • UV LED driver (405 nm, shroud) │
      │ • VL53L0X (nozzle Z calibration) │
      │ • dP/dt comparator → STOP        │
      └───────┬──────────────────────────┘
              │ 4 mm tube from pump box (−70 … +110 kPa, 24 V, I/O controlled)
              ▼
      ┌──────────────┐  unpowered   ┌──────────────────────────────────────┐
      │ 3/2 valve    │ ───────────► │ suction cup φ13/φ16 (lifting nozzle) │
      │ direct-acting│  energized   ├──────────────────────────────────────┤
      │ vacuum-rated │ ───────────► │ amber syringe 5/10 ml, 0.8–1.2 mm tip│
      └──────────────┘              │ UV LED 405 nm, ≥30 mm from the tip   │
                                    └──────────────────────────────────────┘
```

**Why the pressure sensor is still the centre of Data Acquisition**: the sensor was chosen to estimate how much resin is left in the syringe from the shape of the pressure curve. With a thin resin that dependence may turn out to be too small to matter. If so, the same sensor is the clog detector (resin cured in the tip) and the pick verifier (vacuum curve). Setting out to find one thing and finding another is ordinary engineering; both outcomes are graded the same.

**Motivation for the student**: a €3000 robot that sits in a warehouse because nobody makes its tools. A dispensing calibration product from Nordson EFD costs €15 000; yours is the robot plus €50 of electronics plus your software. The 2027 summer camp will use the tags this cell makes. That is a user who does not care about your grade.

### Teams

12 students this year: **4 teams of 3**. Each team gets its own MG400 and its own worktable section; one robot stays spare. Within the team, roles are divided: sensors, software, mechanics; documentation is shared. Roles rotate between labs. Four teams rather than three keeps the cross-team comparisons (models, workflows, UX tests) meaningful and leaves the peer review rules unchanged. If enrolment drops below 10, fall back to 3 teams of 3–4 and "at least 2 teams" in peer review becomes "both other teams".

### Grading philosophy

Grading is positive: you receive full points for what you do correctly. If a prototype does not work but the student explains why and proposes alternatives, points are still achievable.

### Grading structure

**Smaller projects: 5 × 20 points = max 100 points**

Four grading categories per project:

* **Working files** (5p): code, schematics, design files, everything in the repo
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
* Integration + some small ones = points add up (e.g. integration 60p + 2 small projects 40p = 100p)
* 3 small projects = max 60p (enough for an E)

### Peer review (replaces Q&A points)

Previous year problem: reviewing 4 × 3 h of defenses to find who asked what is unrealistic.

Each non-presenting student fills out a **structured form in MS Teams chat** for each other team:

```
TEAM: [name]
STRENGTH: [one specific technical thing that worked well]
QUESTION: [one technical question you want answered]
SUGGESTION: [one specific improvement]
```

Rules:
* Each student must submit feedback for **at least 2 teams** (out of 3 other teams)
* Feedback must be **technical and specific**; "it was good" does not count
* Feedback is **written**, so tracking is automatic, no video review
* Grading: 0p (did not submit), 1p (submitted but superficial), 2p (substantive)
* Max 4 bonus points per defense (2 teams × 2p)

### MS Teams transcription at defenses

Defenses take place in MS Teams (school requirement). Teams transcribes automatically.

1. Download the MS Teams transcript
2. Give it to an agent with the instruction: "Extract each team's demo results, questions asked and identified problems"
3. The agent structures it into a grading sheet by team
4. Doubtful spots (names wrong, technical term distorted) are marked and only those are checked
5. The instructor reviews the marked spots, not the whole recording

### Grading scale

* **91–100 points**: A
* **81–90 points**: B
* **71–80 points**: C
* **61–70 points**: D
* **51–60 points**: E
* **0–50 points**: F

Minimum to pass: 51 points.

**Bonus points** (in addition to peer review): discovering the instructor's errors, including bugs in the base MG400 package fixed by a merged pull request; substantively helping other teams; exceptionally good collaboration.

### Git repo as the only submission channel

**Each team creates and owns its git repo** (GitHub or GitLab, the team's choice). The instructor gets read access, or the repo is public, by the first meeting; the URL is posted in the MS Teams channel. The repo stays with the team after the course: it is their portfolio and, if they want, their product. **What is not in the repo does not get graded.** No exceptions.

The structure below is a template the team applies itself; the instructor does not create anything in the team's repo.

Each lab is a separate directory. If lab 2 builds on lab 1, **copy the necessary files** into the lab 2 folder and develop there. This duplicates code on purpose: beginners understand directories, not branches, and the old lab never breaks.

```
team-N/
├── AGENTS.md                 ← what the system is, how to run each lab, interfaces (for agents and for people)
├── README.md                 ← team overview, members, status
├── data-acquisition/
│   ├── lab1/                 ← Raw ADC + FFT
│   │   ├── src/              ← Arduino code
│   │   ├── data/             ← CSV measurements
│   │   ├── notebooks/        ← Jupyter analysis
│   │   └── docs/             ← schematics, photos, description
│   ├── lab2/                 ← Op-amp + 4 configurations, both sensors
│   ├── lab3/                 ← dP/dt interrupt + I2C + tool PCB (pcb/ with schematic, layout, Gerber)
│   ├── lab4/                ← MG400 data collection (500+ cycles)
│   ├── lab5/                ← ML model (models/ with the pickle/joblib file)
│   └── integration/
├── smart-solutions/
│   ├── lab1/                 ← RPI control station on the base MG400 package
│   ├── lab2/                 ← ESP32 tool-board interface + camera
│   ├── lab3/                 ← Droplet + VPN
│   ├── lab4/                ← MQTT + InfluxDB + workflow recorder
│   ├── lab5/                ← Fault tolerance + REST API + agent
│   └── integration/
├── 3d-print/
│   ├── lab1/                 ← Pen holder → syringe + LED holder on the lifting nozzle
│   │   ├── fusion/           ← .f3d + .step exports
│   │   ├── stl/              ← print files
│   │   └── docs/             ← drawings, photos, caliper tables
│   ├── lab2/                 ← Tray, jig and work-area modules
│   ├── lab3/                 ← Tool-board and control-station enclosures
│   ├── lab4/                ← Design improvement, three approaches
│   ├── lab5/                ← ISO drawing + CNC order
│   └── integration/
└── prototyping/              ← semester 2
    ├── milestone1/ … milestone5/
    └── full-project/
```

**Fusion 360 files in the repo**: `.f3d` export, `.step` export, `.stl`, screenshots or renders where notes are needed, 2D drawing as PDF where required.

**Defense submission = git tag**, created **72 h before the defense**:

```bash
git tag -a data-acquisition-lab1 -m "Data Acquisition Lab 1 defense"
git push origin data-acquisition-lab1
```

Tag naming: `{course}-{project}`, e.g. `data-acquisition-lab1`, `smart-solutions-lab4`, `3d-print-integration`, `prototyping-milestone3`. No tag → not submitted → 0p.

Rules:
* Commit messages describe the work (not "update" or "fix")
* Large binaries (STL, G-code, .f3d) → `.gitignore` plus a precise reference in the folder README (file name, location, access). "Files are in the cloud" is not sufficient
* Data files (CSV) MUST be in the repo; they are the basis of the analysis
* Jupyter notebooks MUST be in the repo with outputs (Run All before committing)

### Submission requirements

* Defense = tag in the repo, 72 h before the defense date
* 5 min presentation per team
* 10 min questions and discussion per team, including **one live change** requested on the spot (a different slot, a different dispense time, a different tag orientation). The system must be changed and run during the defense, not explained.
* Written feedback to other teams in the MS Teams chat during the defense

### Agents

Assume every student works with a coding agent (Claude Code, Codex, whatever). The course does not fight this and does not grade it. What it does:

* Every lab has an **Acceptance** list whose items are physical or measured: a CSV of a given shape, a caliper table, a scale reading, a video of the robot, an oscilloscope screenshot. An agent can write the code; it cannot produce the artefact.
* Grading looks at the artefact, the data and the answers at the defense, never at the volume of code.
* The team repo's `AGENTS.md` is graded as documentation, because it has a real reader: the other teams' agents and next year's course.
* The base MG400 package ships with its own README and `AGENTS.md`, so an agent can drive the robot from the first session.
* **Agent consultation** (optional, Data Acquisition, ~24.09): Claude Code, Codex and Hermes side by side on the lab 1 code. Same footing as the op-amp and resolution consultations: the student decides whether to come. Content: set up each one; give it the team's `AGENTS.md` and the lab 1 folder; let it write the UART logger and the FFT notebook; see where each goes wrong (wrong pin, invented datasheet formula, notebook without outputs); learn to check its work against the physical result. The point is not which agent is best but that the agent's output is unverified until the measurement agrees.

### Previous year work

Previous course work is not built upon. It is teaching material: "Look at what the previous course did. What went wrong and why?" One exercise: try to build from their documentation. What is missing? That is the value of documentation.

### Ordering rule and calendar

* Session 1 runs on what is on the shelf: last year's leftovers and the mystery box. No order before it.
* At every meeting the **next lab's text and component list** are handed out. Between meetings the team finishes the current lab, prepares the next one, and defends the current one at the next meeting.
* The consolidated order for meeting N goes out **10 days before meeting N**. Anything not on the list is the team's own purchase.
* Every lab document ends with **Components for the next lab** (quantities per team). That section is the order list.

Meeting dates: 3D Print on Fridays (11.09, 02.10, 23.10, 13.11, 04.12, 16.01), Data Acquisition and Smart Solutions on Saturdays (12.09, 03.10, 24.10, 14.11, 05.12, 16.01). These are contact sessions: the next lab is handed out, nothing is defended.

**Defences are online, on the Tuesday after the week of the contact session**, and the same day for all three subjects: 06.10.26, 27.10.26, 17.11.26 (PCB review and order), 08.12.26, 19.01.27. Tag 72 h before, i.e. the Saturday of the contact-session weekend. See `plan_2026_27_ENG_v3.md` for the current lab-by-lab plan.

| Order date | For meeting | What goes in the order |
|:--|:--|:--|
| none | 11–12.09, session 1 | Shelf and mystery box: MPX5700AP, Atom Lite, breadboards, LM358N, resistor/capacitor kits, soldering kits, syringes and 4 mm tube, RPI + SD + LAN cable, MG400 suction kit and pump box, PLA, calipers, pens. Instructor buys the resin bench-test set on 09.09: 405 nm resin, amber syringes with 0.6/0.8/1.2 mm tips, one 405 nm LED, goggles. |
| 22.09 | 02–03.10, session 2 | Data Acquisition L2: MPX5100DP ×10, MPXV6115V ×10, LM358N ×20, breadboards, jumper kits. Smart Solutions L2: second Atom Lite per team (×6), nozzle camera ×6, 3/2 valve ×6 with 4 mm push-in fittings and tube, logic-level MOSFET modules ×12, 405 nm LEDs 1–3 W ×10 with star heatsinks, constant-current LED drivers ×6, USB cables. 3D Print L2: M5 bolts/nuts/washers, heat-set inserts, PETG, magnets. Consumables: amber syringes ×40, tips ×50 per size, tip caps, nitrile gloves, IPA, resin 1 kg, 405 nm goggles ×8. |
| 13.10 | 23–24.10, session 3 | Data Acquisition L3: VL53L0X ×10, LM393 comparators, 100 Ω / 100 pF, twisted and shielded cable, JST connectors. Smart Solutions L3: Digital Ocean credit, domain. 3D Print L3: cable glands, strain reliefs, LED heatsinks, magnets, inserts, PETG. Suction cups φ13 and φ16. |
| 03.11 | 13–14.11, session 4 | Tool-board BOM: MOSFETs, flyback diodes, optocouplers, 24 V → 5 V buck modules ×6, headers, connectors. Digital scale 0.01 g ×4. Dummy PC glasses ×30. Resin refill. **PCBs are ordered on 14.11, the day of the review.** |
| 24.11 | 04–05.12, session 5 | AtomS3 or AtomS3R ×10 and batteries ×10 for real assembly cycles. Spare valves, tips, resin. 3D Print L5: the CNC or die-cut order for the glass batch is placed by the teams after the 04.12 review. |
| 06.01.27 | 16.01.27, L5 defenses | Spares only. Semester-2 list handed out on 16.01. |

### Hardware decision gates

| Gate | Date | Decision |
|:--|:--|:--|
| A — resin dose and cure | 18.09 | Bench test: amber 10 ml syringe, tips 0.6/0.8/1.2 mm, 20–100 kPa, pulses 50–500 ms; dose mass per pulse on a 0.01 g scale; drip after the pulse. Then five glasses cured with a 405 nm LED at 30 mm for 5/10/20/40 s and pulled off with the MG400. Output: one tip, one pressure, one pulse, one cure time. These are the first recipe. |
| B — pressure sensors | 22.09 (order) | MPX5100DP (0–100 kPa) on the syringe branch, MPXV6115V (−115–0 kPa) on the cup branch. Same family as the MPX5700AP, so lab 1–2 formulas transfer. The 5700 is used on 12.09 and then serves as the "wrong range" example. |
| C — 3/2 valve | 22.09 (order) | Direct-acting, spring return, vacuum-rated (pilot valves do not switch under vacuum). Common ← pump line; NO (unpowered) → cup; NC (energized) → syringe. Coil 24 V from the pump box supply or 12 V with its own. Under 100 g. |
| D — nozzle camera | 22.09 (order) | M5 AtomS3R-CAM (firmware and mounts exist from the spring 2026 projects) or AI-Thinker ESP32-CAM. WiFi MJPEG either way; the tool board only powers it. |
| E — tool PCB freeze | 14.11 (review) | ESP32, both sensor footprints, op-amp stage, dP/dt comparator, two MOSFET valve drivers with flyback diodes, constant-current 405 nm LED channel with a hardware enable that is low by default, two optocoupled pump-box outputs, VL53L0X connector, camera power, 24 V → 5 V buck, USB-UART. |

**UV resin constraints** (appear in 3D Print L1/L3, Data Acquisition L3, Smart Solutions L2):
* 405 nm, not 365 nm: polycarbonate absorbs most light below about 385 nm.
* Resin cures in daylight: amber syringes, tip caps when idle, shrouded LED aimed away from the tip. Resin cured inside the tip is the real clog case for the dP/dt interrupt.
* Cure dose = time × irradiance. Measured once (cure time vs. pull-off force), stored as a recipe parameter.
* Safety: 405 nm goggles at the table, LED interlocked to the ESP32 (off when unpowered, off unless the robot is at the cure pose, always times out), shroud. Uncured resin is a skin sensitizer: nitrile gloves, IPA, cured waste only into the bin.

**Tag hardware**: the AtomS3 dev kit with 0.85" screen is listed as end-of-life at M5Stack; AtomS3R has the same footprint and screen. Decide before ordering the tag batch. Laser cutting polycarbonate produces toxic fumes and yellow edges: the glass batch is CNC-milled or die-cut, which is the 3D Print L5 order.

---

## Data Acquisition (6 ECTS)

*Building the nervous system*

### Concept

Build the pressure and vacuum measurement for the tool, and learn from that data. Two pressure sensors, one breadboard, four configurations that show step by step why each improvement is necessary. Fourier analysis makes the difference visible.

The ML question is specific and measurable: **does the resin level in the syringe change the dose, and can the pressure curve tell us the level?** In a pneumatic syringe the curve at valve opening is shaped by air compressibility (more air → slower rise), by the material's back-pressure at the tip, and by the material's incompressibility. With a thin UV resin the second effect is small, so the outcome may be "no compensation needed". That is a valid result, graded the same as a compensation table, and it turns the sensor into a clog detector and a pick verifier instead.

### What you learn

* ADC fundamentals and error sources; effective resolution of a sensor in a given pressure range
* Op-amp signal conditioning (offset, scaling, CMRR)
* Analog and digital filtering
* Fourier analysis (FFT) in time and frequency domains
* Derivative (dP/dt) and interrupts for real-time reaction
* I2C, noise diagnostics and filtering on long cables
* PCB design and ordering
* Data collection with a robot, cleaning and visualization (Jupyter Lab, pandas, scipy)
* Training and validating ML models (scikit-learn), including honest null results

### Work

Labs 1–3 build on **the same breadboard**. Each lab adds a layer.

**Lab 1: Raw signal and first Fourier (34h)**

Connect a pressure sensor directly to the ESP32 ADC. Measure. See what comes out.

Specifically:
* **The first contact session starts with the bench** (~3h): breadboard rows and rails, passive vs. active components, reading a pinout off a datasheet, multimeter: voltage, resistance, continuity. Nobody connects a sensor before this is in place. No soldering in this lab — everything is built on a solderless spring breadboard from the shelf kit; hand soldering starts with the tool PCB, designed in Lab 3 and populated when the boards arrive.
* Connect the sensor on the shelf (MPX5700AP on 12.09; MPX5100DP when it arrives) to the breadboard: power, GND, output → ESP32 ADC, nothing in between
* Arduino code: read the ADC at 100 Hz, send via UART to the computer
* Pressure source: hand syringe on day one, the MG400 pump box from week two. Target range 0–110 kPa
* Collect 30 measurements in three pressure categories (low, medium, high)
* Convert ADC values to Pascals with the datasheet formula
* Simulate the circuit in Falstad, compare with real measurements
* **Jupyter Lab, time domain**: mean, standard deviation, noise level
* **Jupyter Lab, Fourier**: `scipy.fft`. What frequencies are there? Where do the peaks come from (MG400 motors, switch-mode supplies, ground loops)? What is the noise floor?
* **Resolution task**: Pa per LSB for the MPX5700AP and for the MPX5100DP in a 0–110 kPa system (ADC bits × sensor span). Why the 5700 uses 15 % of its range here and what that does to the noise floor in Pa.
* **Order list**: simulation → breadboard → measurement → order. The Lab 2 parts list is written as Mouser part numbers with package and stock checked and one line per part saying which simulation or measurement asks for it; it goes out on 22.09.

Acceptance: CSV of 90 measurements, notebook with spectrum and noise-source hypotheses, the Pa/LSB number for both sensors, oscilloscope screenshot.

*Required topics: ESP32 Arduino, UART, ADC, Jupyter Lab, Falstad, scipy.fft*

**Lab 2: Op-amp and filtering, Fourier shows the difference (30h)**

The MPX5100DP output is 0.2–4.7 V, the ESP32 ADC reads 0–3.3 V. Add a signal chain and see with Fourier what changes.

Same breadboard, four configurations; the student **reconnects wires**:

| Config | Circuit | What Fourier shows |
|:---|:---|:---|
| 1 (lab 1) | MPX → direct to ADC | Raw: noise peaks (motors, supplies) + broad noise floor |
| 2 | MPX → voltage divider → ADC | Amplitude better, noise still there |
| 3 | MPX → op-amp (offset + scaling) → ADC | Common-mode noise lower (CMRR), signal in ADC range |
| 3b | MPXV6115V (vacuum) → the same op-amp stage, inverted slope | The cup branch is instrumented with the same circuit |
| 4 | Config 3 + digital filter in code (moving average) | High-frequency noise gone, only the slow pressure change remains |

Specifically:
* Simulate in Falstad: voltage divider vs. op-amp
* Build the op-amp (LM358N) circuit: offset (−0.2 V) + scaling (top end 3.2 V)
* Measure all configurations with the oscilloscope
* Collect **the same 30 measurements per configuration, same pump-box pulse** — 4 × 30 = 120 in one CSV, plus 30 vacuum pulses on the cup branch
* Add a digital filter to the Arduino code (moving average, N=10)
* **Jupyter Lab, four-way comparison**: time domain side by side, four spectra side by side, SNR per configuration, table config × SNR × amplitude × noise

Acceptance: four spectra from the same pulse, SNR table, vacuum-branch curve of one pick.

*Required topics: op-amp theory and practice, Falstad, oscilloscope, digital filtering, Fourier comparison*

**Lab 3: dP/dt derivative, interrupt threshold, I2C calibration and the tool PCB (24h)**

Two capabilities and one board: (A) a real-time safety mechanism on the pressure derivative, (B) nozzle calibration with an I2C distance sensor, (C) the tool PCB that carries all of it plus the valve, pump and LED drivers.

**Part A: derivative and interrupt**

Normal dispensing: pressure rises slowly. Tip cured shut (resin left in daylight): pressure rises fast. Empty syringe: pressure drops.

Specifically:
* Derivative in the Arduino code: `dP = (P_now − P_prev) / dt`
* Comparator (op-amp as Schmitt trigger) + ESP32 interrupt: if dP/dt exceeds the threshold → interrupt → valve released, STOP to the MG400
* **Fourier makes this mandatory**: the derivative amplifies noise (× 2πf). The derivative of the raw signal gives a false alarm every 20 ms; the derivative of the filtered signal works
* Jupyter Lab: raw dP/dt vs. filtered dP/dt side by side
* Test with a real clog: a tip cured in daylight. Does the interrupt fire, and how fast on the scope?
* Test an empty syringe: does the alarm trigger?

**Part B: I2C distance sensor for nozzle calibration**

A VL53L0X on the table measures nozzle Z-height. After a syringe change the system checks position by itself.

Specifically:
* VL53L0X to the ESP32 (I2C), short cable: works
* Extend to 30–50 cm alongside the MG400 power cables: noise, wrong values, timeouts
* Diagnosis on the oscilloscope: distorted edges
* Fix: RC filter (100 Ω + 100 pF) on SDA and SCL, twisted pair, shielding
* Three datasets: short / long noisy / long filtered
* Calibration sequence: MG400 moves the nozzle to a known position → VL53L0X measures → offset X/Y/Z

**Part C: the tool PCB**

* Schematic + layout + DRC for the board in Gate E. The command interface it implements is the one frozen in Smart Solutions L2
* **Safe state is measurable**: with the ESP32 unpowered, the vacuum sensor proves the line is on the cup branch and nothing dispenses; the LED enable is low
* **Lab 3 defense includes the PCB review.** No board is ordered without it. Gerber ordered the same day; it arrives for task 4

Acceptance: interrupt latency on the scope, three VL53L0X datasets, schematic + layout + DRC-clean Gerber, safe-state measurement.

*Required topics: derivative and interrupt, comparator/Schmitt trigger, I2C protocol and noise filtering, PCB design and ordering*

**Lab 4: Data collection with the MG400 (24h)**

The system has: two sensors on op-amp + filter, dP/dt alarm, nozzle calibration, and (if the PCB arrived) the tool board. The MG400 is a data factory: it runs the assembly cycle hundreds of times with different parameters.

Specifically:
* Python script on the base MG400 package: (a) runs a cycle with given parameters (speed, pressure, dispense ms, cure s), (b) reads the ESP32 via UART, (c) writes one record per cycle (CSV in the repo and the shared database)
* Dispense goes into the waste cup for most of the dataset (no tag consumed); pick/place recirculates the same five dummy glasses between source and finished slots, so a 5+5 tray supports unlimited cycles without a human
* At least 500 cycles: 5 speeds × 5 pressures × 20 repetitions
* **Ground truth for fill level**: (a) scale reading of the syringe every 25 cycles, or (b) known full volume minus counted dispenses at a weighed mean dose. Each record carries the estimate and the method
* **Pick-success label** from the vacuum curve (plateau reached or not), verified against the camera image
* **Cure side dataset**: cure time × pull-off force, 5 × 5 tags, to fix the recipe value
* **Jupyter Lab**: pandas cleaning, correlation matrix, distributions, outliers; response time vs. fill level; Fourier of the curve at different fill levels; what else affects the curve (temperature, tip diameter, pressure setpoint)?

Acceptance: ≥500 records with both curves and images in the shared database and as CSV in the repo; the pull-off table.

*Required topics: Python automation, MG400 API, pandas, time series, Fourier*

**Lab 5: Machine learning model (30h)**

Use the task 4 dataset. One question stated as a hypothesis with two equally graded outcomes.

* **H1**: dose per unit time depends on fill level → produce the compensation table (dispense-ms vs. fill) and show the corrected dose scatter on the scale
* **H0**: within ±10 % dose, no dependence → prove it with residuals and delete compensation from the recipe

Specifically:
* Train/test split (80/20), cross-validation
* Linear regression → decision tree → random forest
* **Features**: time features (response time, max dP/dt, plateau, area under the curve), Fourier features (dominant frequency, spectral energy, shape), environment (temperature if measured, tip diameter, setpoint)
* **Output**: remaining volume (ml), regression
* **Comparison 1, features**: do Fourier features improve the model?
* **Comparison 2, signal quality**: op-amp data (config 3–4) vs. raw (config 1)
* **Comparison 3, between teams**: whose model predicts on their own device? Whose works on another team's device?
* MSE, R², residual analysis; the proof is the dispensed mass on the scale, not the model's own score
* **Second, smaller model**: pick-success classifier from the vacuum curve (binary), used by Smart Solutions L5 for retry logic
* **Practical result**: "syringe below 2 ml, replace" at what accuracy, or "fill level does not matter, watch dP/dt instead"

Acceptance: the model file loads in the RPI Flask app and returns an estimate for a live curve; ten scale-weighed dispenses at two fill levels.

*Required topics: scikit-learn, training and validation, feature engineering, time-series features*

**Integration project: Automatic fill-level and fault monitoring**

Closed loop: MG400 dispenses → sensors measure → model estimates remaining volume and pick success → web interface shows "syringe has ~4.2 ml", "pick OK" → below threshold or clog → alert and safe state.

### Lab progression summary

```
Lab 1: Raw ADC → "I get a number, but it's noisy"; Fourier shows peaks + floor; wrong-range sensor shows why Pa/LSB matters
Lab 2: Op-amp + filter, 4 configs + vacuum branch → "Now the signal is clean"; Fourier shows what each step removes
Lab 3: dP/dt + interrupt + I2C + tool PCB → "The tool reacts on its own and self-calibrates"; PCB reviewed and ordered
Lab 4: MG400 runs 500 cycles → dataset with ground truth; PCB arrives
Lab 5: ML → "fill level matters / does not matter", pick classifier
```

### Contact hours

* **[12.09.26]** Consultation 1 (optional): electronics basics, breadboard and multimeter
* **[~24.09.26]** Consultation 2 (optional): agents on lab 1. Claude Code, Codex and Hermes on the team's own code and `AGENTS.md`; where each goes wrong and how to check it against the measurement
* **[12.09.26]** ESP32 first program, ADC, Jupyter Lab, first FFT. Lab 2 text and component list handed out
* **[03.10.26]** Lab 1 defense; op-amp theory, Falstad, four-way comparison. Lab 3 handed out
* **[~15.10.26]** Consultation 3: op-amp offset and scaling in practice, oscilloscope
* **[24.10.26]** Lab 2 defense; derivative, comparator, interrupt, I2C noise. Lab 4 handed out
* **[~05.11.26]** Consultation 4: resolution determination, PCB schematic pre-check
* **[14.11.26]** Lab 3 defense with PCB review, PCB ordered; MG400 data collection in Python. Lab 5 handed out
* **[05.12.26]** Lab 4 defense; ML introduction, features from pressure curves
* **[16.01.27]** Lab 5 defense
* **[TBD]** Integration project defense

---

## Smart Solutions (6 ECTS)

*Building the brain*

### Concept

Each team builds a **control station** for its MG400: a Raspberry Pi with a screen on the worktable, connected to the MG400 by LAN and to the ESP32 tool board by USB, running a Flask web server. The operator controls the robot from a browser. The station replaces Dobot's software, which is not used at all: the instructor's **base MG400 Python package** is the only path to the robot, and students build on it, extend it, and fix it.

The reason the station connects to a cloud server is not remote control for its own sake. Four robots must produce **one dataset**: every cycle from every team lands in the same database with the same record format. That is what makes cross-team models in Data Acquisition L5 possible, and it is the reason a central IoT system exists.

```
Phone/laptop (browser)
        │ WiFi / VPN
        ▼
   ┌─────────────────────────┐
   │  RPI + screen           │  ← on the worktable, always connected
   │  Flask web server       │
   │  base MG400 package     │
   │  tool-board interface   │
   │  workflow record/replay │
   └──┬──────────┬───────┬───┘
      │ LAN      │ USB   │ WiFi
      ▼          ▼       ▼
   MG400     tool board  nozzle cam
```

### What you learn

* IPv4 fundamentals and routing (two, later three, network interfaces on one RPI)
* RPI setup and Linux command line
* Using, reading and extending a Python package for a TCP/IP robot API; contributing fixes upstream
* Web interfaces (HTML/JS + Flask)
* ESP32 ↔ RPI communication (USB/UART, WiFi, HTTP, MQTT), command/response interfaces for a physical tool
* Video streaming from an embedded camera and its latency
* Operator locking (one operator, view mode for the rest)
* Cloud server (Digital Ocean), WireGuard VPN, nginx reverse proxy
* MQTT and time-series logging (InfluxDB), one record format across teams
* Fault tolerance on cheap hardware: watchdogs, heartbeat, safe state
* REST API design that an agent can use

### Work

**Lab 1: RPI control station on the base MG400 package (28h)**

Get the RPI working and move the robot. Pick a tag with the suction cup from a phone on day one.

Specifically:
* RPI setup: OS, SSH, WiFi, static IP
* **IPv4 fundamentals**: IP, subnet, gateway. Why the MG400 is on a LAN cable (its own subnet). Two interfaces, two subnets on one RPI
* **Base MG400 package**: install from the tagged git URL, read it, run its CLI: connect, enable, clear error, jog, read position, toggle DO, stop. Dobot's own software is not used
* Add what is missing for the cell: pump box DO control (suction / blow-off), position teach/save/replay, a status poll. Fixes to the base go back as pull requests
* Flask web server on the RPI: movement buttons, saved positions, suction on/off, blow-off
* RPI screen: status (MG400 connected, last command, position)
* `AGENTS.md` in the team repo: what the system is, how to run it, where the base package README is

Acceptance: video of a tag lifted and placed from a phone; teach/save/replay of three points; `AGENTS.md` that another team's agent can use.

*Required topics: RPI setup, Linux CLI, IPv4 and routing, using a Python package, Flask, HTML/JS*

**Lab 2: Tool-board interface and nozzle camera (26h)**

The ESP32 on the tool must talk to the RPI, and it must **act**, not only report. The message format defined here is what the Data Acquisition L3 PCB implements.

Specifically:
* **USB/UART**: ESP32 → USB → RPI, `pyserial`, JSON per measurement (pressure, vacuum, valve state, LED state)
* **Commands**: `valve`, `pump` (off / suction / blow), `dispense_ms`, `uv_ms`. `uv_ms` is refused unless the RPI has confirmed the cure pose, and the LED always times out on the ESP32 side
* **WiFi alternative**: ESP32 in AP mode, HTTP GET /data, POST /cmd. The student understands what a request and a response are
* **MQTT introduction**: ESP32 publishes, RPI subscribes, Mosquitto on the RPI. Prepares lab 3 and task 4
* **Nozzle camera**: MJPEG stream to the RPI page. Latency of camera vs. sensor data measured
* One page: MG400 status, pressure, vacuum, camera; a dispense triggered from the browser with its curve visible
* Latency test: command to response for USB vs. WiFi vs. MQTT

Acceptance: the one page working; a browser-triggered dispense with its curve; the interface document (message format) in the repo, used by Data Acquisition L3.

*Required topics: ESP32 WiFi/UART, pyserial, HTTP, MQTT basics, JSON interfaces, MJPEG*

**Lab 3: Digital Ocean droplet and VPN (30h)**

The station works locally. Make it remotely accessible, securely, camera included.

Specifically:
* **Droplet**: Ubuntu, SSH, ufw
* **WireGuard**: droplet is the VPN server, each team's RPI a client with a fixed VPN IP (10.0.0.1–4). Tunnel always up
* **nginx reverse proxy** on the droplet: one page listing all robots, `/robot/N/` → `proxy_pass` to the RPI. The camera MJPEG must survive the proxy (buffering off for that location)
* **Reverse VPN logic**: the RPI connects out, the droplet routes users in. ESP32 settings and robot control are reachable remotely without the ESP32 doing any encryption
* **IPv4 routing in practice**: three networks on the RPI (MG400 LAN, local WiFi, VPN). Routing table, why packets reach the right place
* Status page on the droplet: pings VPN IPs, who is online, link per robot

Acceptance: from outside the lab, place a tag and watch it on the nozzle camera.

*Required topics: Digital Ocean, Linux server, SSH, firewall, WireGuard, nginx, IPv4 routing*

**Lab 4: Shared database and workflow recorder (30h)**

Bring all data into one system: tool board → RPI → cloud → history, in the one record format all teams share. And make the robot teachable in minutes.

Specifically:
* Mosquitto on the droplet; RPI publishes every cycle's record (section "One assembly cycle", step 7); InfluxDB stores it with a team tag. **Same bucket, same schema for all four teams**
* **Workflow recorder**: the operator jogs the robot while watching the nozzle camera, presses record at each waypoint, picks an action (suction on/off, dispense N ms, UV cure N s, blow-off, wait), saves. Replay runs the cycle. Workflows are JSON in the repo
* **Unified interface on the RPI**: control + live sensors + camera + history graphs + CSV/JSON export
* **Central portal on the droplet**: per-team cycle count, last record, last image, fill-level estimate; one glance shows the state of all four robots
* **User locking**: one operator at a time; view mode for others (camera, sensors, status visible, buttons greyed); doorbell ("please release"); admin override; 5-minute timeout
* ESP32 offline buffer: 100 messages in LittleFS when WiFi drops
* UX test: another team records a workflow in under 5 minutes without help

Acceptance: a workflow recorded by another team in under 5 minutes; 100 cycles from it in the shared database; the portal showing all teams.

*Required topics: MQTT, Mosquitto, InfluxDB, Flask dashboard, nginx, session management, locking, UX*

**Lab 5: Fault tolerance, REST API and an agent that runs the cell (34h)**

The RPI does five things at once: Flask, MG400, tool board, MQTT, camera. One of them crashes. Detect and recover without ruining a tag in progress.

**Part A: cheap hardware limitations**

The RPI is a €50 computer controlling a €3000 robot. Understand the limitations, measure them, design around them.

Specifically:
* **Measure**: Flask serving a page while the ESP32 streams over USB while the MG400 socket waits. Python GIL: not truly parallel. How long does Flask block? How many measurements are lost?
* **Design around**: separate processes for critical services, queues between them, timeouts on every socket. MG400 silent for 2 s → "connection lost", carry on with the rest
* **Safe state is physical**: pump off, valve unpowered → cup branch, LED enable low. Pull the ESP32 USB mid-dispense and show on the vacuum sensor that the line went to the cup. Pull the MG400 LAN. Kill WiFi. Document each case: what happens, how long, is the tag ruined
* **Jupyter Lab**: fault log (service, when, how long). Correlation with load, mean recovery time, where the RPI stops being enough

**Part B: REST API and the agent**

Specifically:
* REST API on the RPI: `/status`, `/cycle`, `/workflow`, `/history`, `/export`, documented JSON
* Reachable through the portal: `robots.kool.ee/robot/N/api/`
* Time lock: remote endpoints work only after the local operator activates them on the RPI screen
* `/api` README endpoint describing every endpoint, written so an agent can run the whole cycle
* **Demo**: an agent (whatever the team uses) is given only the API description and asked to assemble one tag through the portal. Retry-on-pick-failure uses the Data Acquisition L5 classifier
* API audit log: who, when, what

Acceptance: the agent-driven cycle succeeds on the first attempt, with an audit log of every call; the three cable-pull cases documented with times.

*Required topics: watchdog, heartbeat, safe state, REST API design, time lock, agent integration, audit log*

**Integration project: Complete control station**

Clone one SD card → a new MG400 is usable: connect LAN, connect the tool board, power on. One install script, automatic VPN, locking, fault tolerance, workflow recorder. Documentation sufficient for a stranger to set it up.

### Contact hours

* **[12.09.26]** RPI setup, IPv4, base MG400 package, first movement, first pick. Lab 2 handed out
* **[03.10.26]** Lab 1 defense; ESP32 ↔ RPI, tool-board interface, camera. Lab 3 handed out
* **[~15.10.26]** Consultation 1: IPv4 routing in practice (`ip route`, `ping`, `traceroute`)
* **[24.10.26]** Lab 2 defense; Digital Ocean, WireGuard. Lab 4 handed out
* **[~05.11.26]** Consultation 2: WireGuard step by step, keys, NAT, checking the tunnel
* **[14.11.26]** Lab 3 defense; MQTT, InfluxDB, workflow recorder. Lab 5 handed out
* **[~25.11.26]** Consultation 3: nginx reverse proxy, MJPEG through the proxy, Let's Encrypt
* **[05.12.26]** Lab 4 defense; REST API, time lock, agents
* **[16.01.27]** Lab 5 defense
* **[TBD]** Integration project defense

---

## 3D Printing and CAD (6 ECTS)

*Building the body*

### Concept

You start in Blender and learn how hard it is to keep a mesh watertight when working with vertices and polygons. Then you see what Fusion is good at: the model is always solid because the tool does not let you create invalid geometry.

Academic core: **how shape affects manufacturing**. Rotate an object in four orientations and see what happens to print time, support volume and strength. Print time ≈ sum of layer times, each layer's time set by its cross-section: integration in practice.

Everything printed in this course goes onto the robot or onto the table: the syringe and LED holder on the lifting nozzle, the trays and jig, the enclosures. Fit is measured with calipers and with the robot.

### What you learn

* Polygon modeling (Blender): mesh, STL as triangles, where errors come from
* Blender → STL → slicer → G-code → print, and what goes wrong at each step
* Parametric modeling (Fusion 360) from measured constraints
* Design inputs: physical (strength, mass), business (time, cost), aesthetic
* Orientation optimization: layer-by-layer integration predicts time, supports, strength
* Assemblies and fasteners (snap-fit, print-pause, inserts, bolt compression)
* FEA in Fusion 360
* Generative design vs. manual engineering
* ISO drawings, GD&T, tolerance analysis, CNC ordering and validation

### Work

**Lab 1: From Blender to the printer, then to Fusion (34h)**

**Part A: Blender and mesh modeling.** First print: a **pen holder for the MG400 tool flange**. Tube plus flange mount. The robot draws on the first day — with a marker taped to the flange and the drawing routine from the base package, while the holder is still printing. The three-hour session is for modelling, export and the slicer; the printed holder goes on the robot in the week after. Students write no robot motion code in this lab.
* Make it in Blender, export STL, open in the slicer. What happens? (open edges, flipped normals, thin walls, non-manifold)
* Mesh diagnostics: triangles, normals, inside/outside; Blender 3D Print toolbox, Meshmixer
* Fix, print, mount, draw. Imprecise and wobbly, but it works

**Part B: FDM physics.** Same holder, understand why the printer behaves as it does.
* Overhang and the 45° rule: print the same wall at 30/45/60/90°. Layer height 0.2 mm, offset 0.2 mm = 45° diagonal
* Straight vs. round: same volume, same wall; measure time and surface. Round is slower (constant deceleration) and stepped
* Orientation and strength: four orientations, tensile test each. Inter-layer bonding is the weakest point
* Jupyter Lab: layer cross-sections per orientation, print time by summing perimeters and areas, compare with the slicer

**Part C: Blender to Fusion.** The pen holder is wobbly and the dimensions do not match.
* Measure the MG400 tool flange with calipers, enter as parameters
* Pen diameter, angle, height parametric
* Export STL: no errors. Print, mount: drawing is immediately better

**Part D: From pen to syringe beside the suction cup.** The tool is the Dobot suction kit's lifting nozzle with a syringe next to it.
* Measure the lifting nozzle and its spring travel
* Syringe holder clamps to it: tip 5–10 mm above the cup face, 4 mm tube routing for both branches, a mounting boss for the UV LED shroud at least 30 mm from the tip, aimed so the cone misses the tip
* Syringe sizes 5 and 10 ml as parameters; export, print, test
* Test on the MG400: does the cup still lift a glass with the holder attached? Can the syringe be swapped one-handed?

Acceptance: robot drawing on day one; orientation table with tensile numbers; syringe swapped one-handed while mounted; cup lifts a glass with the holder on.

*Required topics: Blender, mesh/STL diagnostics, slicer and orientation, print-time integration, Fusion parametric design, FDM constraints*

**Lab 2: Work-area modules, tray and jig (30h)**

Design the modules that mount into the table's 5 mm holes and 100 mm grid. These are the fixtures the robot picks from, so positions must be **precise**: this is why Fusion, not Blender.

Specifically:
* Universal mounting foot for the hole pattern; sensor- and fixture-specific tops that snap onto it
* Spring fastener: push down, snap, done; pull up, released
* **The tray set**: 5 glass slots + 5 AtomS3 slots (source), 5 finished slots, gluing jig holding an AtomS3 screen-up with the bezel reachable, VL53L0X post, waste-cup holder, camera calibration target
* **Bolt-nut-washer compression, PLA stronger than the material**: layers weak in tension, strong in compression; a bolt through the part turns inter-layer tension into compression, as in prestressed concrete. Print the same part (a) without bolts, (b) bolted through; tensile test with the MG400; document the failure loads. Design rule: where do bolt holes go so that layers are always in compression?
* FEA: does the snap-fit hold? Where are the stress concentrations?
* **Registration test**: print the tray twice on different printers, measure slot positions with calipers; the MG400 must pick from both with the same taught points. This repeatability number is what Data Acquisition L4 relies on
* Fusion 360 2D drawing: manufacturing instructions for another person

Acceptance: caliper table for both tray prints; robot picks 5 of 5 glasses from each; bolted vs. unbolted failure loads.

*Required topics: Fusion assemblies, snap-fit, compression fasteners, FEA, 2D drawing*

**Lab 3: Enclosures and print-pause (28h)**

Two enclosures: the tool-board housing on the arm and the control-station housing on the table.

Specifically:
* Integration graph (draw.io): components and connections
* Bill of materials
* **Tool housing**: light; valve and board inside; camera on a short adjustable mount seeing the nozzle tip and the tray in one frame; UV LED with heatsink and shroud; strain relief for tube and USB; ventilation
* **Station housing**: RPI + screen, cable entries, mounting to the table
* Print-pause workflow: pause, insert nuts/magnets/inserts, continue
* Assembly guide clear enough for another team to replicate

Acceptance: arm-mounted mass under 250 g with valve and empty syringe; a camera frame showing tip and tray; another team assembles the housing from the guide.

*Required topics: integration graph, BOM, print-pause, assembly guide*

**Lab 4: Improving an existing design, three approaches (30h)**

Candidates: the syringe holder from lab 1, the tray from lab 2, the valve bracket from lab 3. The student picks one and improves it along **one metric**: (A) print speed at equal strength, (B) strength at equal print time, (C) use cycles.

Specifically:
* Analyze the existing design: wasted material, weak point, orientation and why
* **Approach 1, manual engineering**: ribs on load paths, wall thickness, FDM-friendly geometry, bolt placement
* **Approach 2, generative design** in Fusion: mounting points, loads, keep-out zones; let the algorithm propose
* Print all three (original, manual, generative), orientation optimized with the lab 1 method
* Repeatable test with the MG400: same load on each version
* Comparison table: print time, mass, strength, cycles, support cost. Is manual better than generative? Why?

*Required topics: design analysis, generative design, FEA, FDM optimization, test methodology*

**Lab 5: ISO drawing and CNC order (24h)**

Design a part that is made outside and order it. **The drawing is the order document.** Preferred object: **the polycarbonate glass batch for the tags** (50–100 pieces, CNC-milled or die-cut, never laser-cut), toleranced against the gluing jig. Alternative: the tray base plate that registers the tray to the robot.

Specifically:
* ISO drawing: views, sections, dimensions, tolerances, surface, material
* GD&T for critical features (glass outline vs. jig pocket; hole positions vs. printed inserts)
* Tolerance analysis: CNC (±0.1 mm) + printed part (±0.3 mm), do they fit?
* **Instructor review before ordering**, same logic as the PCB
* Order; the parts arrive for semester 2
* **Validation on arrival**: calipers, fit in the jig, fit under the suction cup. If wrong, was it the drawing or the shop?

*Required topics: ISO drawings, GD&T, tolerance analysis, CNC ordering and validation*

**Integration project: Complete mechanical package**

Syringe and LED holder, tray and jig set, both enclosures, the glass drawing, all with manufacturing-ready documentation from which a stranger assembles the cell.

### Contact hours

* **[11.09.26]** Blender basics, mesh and STL, slicer, orientation, first print. Lab 2 handed out
* **[02.10.26]** Lab 1 defense; Fusion assemblies, snap-fit, inserts, springs, tray design. Lab 3 handed out
* **[23.10.26]** Lab 2 defense; print-pause, enclosures, camera and LED mounting. Lab 4 handed out
* **[13.11.26]** Lab 3 defense; generative design. Lab 5 handed out
* **[04.12.26]** Lab 4 defense; ISO drawings, GD&T, CNC communication; drawing review
* **[16.01.27]** Lab 5 defense
* **[TBD]** Integration project defense

---

## Prototyping (3 ECTS, semester 2)

*Everything together, and a model in production*

### Concept

The three courses' parts become one working cell, and the model is put to work: the cell assembles tags for the 2027 summer camp. The camp is an external user; its deadline is real.

Students arrive with working sensors and a tool board (Data Acquisition), a control station with a workflow recorder and API (Smart Solutions), and the mechanical package (3D Print). If something is half done, milestone 1 exists to finish it.

### Work

The student chooses: 5 milestones in sequence (× 20p = max 100p) OR the full project (max 100p).

**Milestone 1: Audit and specification update (10h)**
* Audit each subsystem: state, gaps, risks. Which team's tool board, tray, workflow and model go into the cell?
* Update the specification with semester-1 experience
* Define the minimum working cell that demonstrates the model in the loop
* Schedule and division of work

**Milestone 2: Integration prototype (16h)**
* First complete tag glued by the robot from a recorded workflow: web command → MG400 → dispense → pick → place → cure → image → record
* Integration problems: timing, latency, states
* First 100 cycles with the integrated cell

**Milestone 3: Model in the loop (18h)**
* Load the trained model (pickle/joblib) into the Flask server
* Closed loop: fill-level estimate shown live; compensation on or off according to the L5 result; pick-retry on the classifier
* Test: full syringe to empty, does the estimate fall sensibly?
* Test: another team's model on your cell. Works? If not, why?

**Milestone 4: Functional prototype with enclosures (16h)**
* Everything in its housing, cable management, labelled connections
* Battery module plugging by the robot (press-fit with the cup or a second fixture), if in scope
* UX test: another team assembles a tag within 10 minutes
* Maintenance guide: what breaks, how to replace it

**Milestone 5: Production run (14h)**
* A run of tags for the summer camp with full documentation: user guide, maintenance guide, BOM, software install
* Demonstration: specification targets vs. measured performance
* Repo: code, CAD, BOM, guides
* 5-minute demo: how the cell works, how to set it up, how the model calibrates

**Full project (alternative)**: same content, defended at once. Requires a physically working cell.

### Contact hours

* **[27.02.27]** System audit, integration planning; Milestone 1 defense
* **[20.03.27]** Milestone 2 defense; model deployment workshop (pickle → Flask → MG400 loop)
* **[17.04.27]** Milestone 3 defense; production documentation
* **[29.05.27]** Milestone 4 defense; Milestone 5 / full project defense

---

## Course interplay

```
Semester 1 (Sept 2026 – Jan 2027):
┌────────────────────────────────────────────────────────────────────────┐
│ Data Acquisition          Smart Solutions              3D Printing     │
│ ────────────────          ───────────────              ───────────     │
│ L1: Raw ADC + FFT         L1: RPI + base package       L1: Pen → syringe + LED holder │
│ L2: Op-amp, 4 conf + vac  L2: Tool-board i/f + camera  L2: Tray, jig, modules │
│ L3: dP/dt, I2C, tool PCB  L3: Droplet + VPN            L3: Enclosures  │
│ L4: 500 cycles + truth    L4: Shared DB + recorder     L4: Improve a part │
│ L5: ML, H1/H0 + pick clf  L5: Faults, API, agent       L5: Glass drawing + CNC │
└────────────────────────────────────────────────────────────────────────┘
                                   │
                                   ▼
Semester 2 (Feb – May 2027): Prototyping — one cell, model in the loop, tags for the camp
```

### Fourier analysis throughout Data Acquisition

```
Lab 1: FFT shows raw noise (motors, supplies, ground loops)
Lab 2: FFT shows each configuration's effect (spectra side by side)
Lab 3: FFT shows why the derivative needs filtering (noise × 2πf)
Lab 4: FFT shows whether the curve spectrum changes with fill level
Lab 5: FFT features vs. time features in the model
```

### Pressure curve logic

Pneumatic syringe (air → plunger → resin → tip 0.8–1.2 mm):

```
Valve opens → pressure rises → three effects at once:
  1. Air compressibility: more air in the barrel = slower rise
  2. Material back-pressure at the tip: more material = more resistance (small for thin resin)
  3. Material incompressibility: resin transmits pressure immediately, air absorbs it
→ curve shape may change with fill level; measured, not assumed
```

* **Clogged tip** (resin cured in daylight): pressure rises sharply and stays → dP/dt interrupt
* **Pick**: vacuum curve reaches a plateau when the cup seals on the glass; no plateau = no glass
* **Cure**: dose = time × irradiance; measured once against pull-off force

### Hardware dependency timeline

Two ESP32 per team: ESP32-A stays on the breadboard (Data Acquisition), ESP32-B is on the RPI (Smart Solutions). The tool board replaces both from December.

```
            SEPT        OCT         NOV         DEC         JAN
Data Acq.   ESP32-A     ESP32-A     ESP32-A     tool PCB    Jupyter
            breadboard  +2 sensors  +PCB design +MG400      (data only)
Smart Sol.  RPI+MG400   RPI+ESP32-B RPI+droplet RPI+all     RPI+all
            base pkg    +valve+cam  +VPN        +DB+recorder +API+agent
3D Print    Fusion      Fusion      Fusion      Fusion      Fusion
            nozzle      tray, jig   enclosures  improve     CNC order
```

**Integration point** (Nov–Dec): task 4 in every course; all hardware comes together for the first time. Planned, not a conflict.

### What each course produces for the others

| Source | Output | Consumer |
|:---|:---|:---|
| Data Acquisition L1–L2 | Two sensors on op-amp + filter (breadboard) | Data Acquisition L4 |
| Data Acquisition L3 | dP/dt safety, VL53L0X calibration, **tool PCB** | Smart Solutions L4–L5, 3D Print L3, Prototyping |
| Data Acquisition L4 | 500+ cycle dataset with ground truth | Data Acquisition L5, all teams |
| Data Acquisition L5 | Fill-level model (or its null result), pick classifier | Smart Solutions L5, Prototyping M3 |
| Smart Solutions L1 | RPI station on the base package, teach/replay | Data Acquisition L4 |
| Smart Solutions L2 | Tool-board command interface, camera stream | Data Acquisition L3 (PCB), 3D Print L3 |
| Smart Solutions L3 | VPN and proxy | Smart Solutions L4–L5 |
| Smart Solutions L4 | Shared database, record schema, workflow recorder | Data Acquisition L4–L5, Prototyping |
| Smart Solutions L5 | REST API an agent can run | Prototyping |
| 3D Print L1 | Syringe + LED holder on the lifting nozzle | Data Acquisition L4, Smart Solutions L2 |
| 3D Print L2 | Tray, jig, VL53L0X post; registration numbers | Data Acquisition L3–L4 |
| 3D Print L3 | Tool and station enclosures, camera and LED mounts | Prototyping |
| 3D Print L5 | Glass batch drawing and parts | Prototyping M5, summer camp |

### Component list

**Already available**: MG400 ×5 with suction kits and mini vacuum pump boxes; polycarbonate worktables; 3D printers; oscilloscope; last year's leftovers (MPX5700AP, Atom Lite, LM358N, breadboards, kits); the mystery box.

**Ordered per session** (see the ordering calendar above): sensors, valves, cameras, LEDs and drivers, MOSFET modules, VL53L0X, comparators, tool-board BOM, scales, syringes and tips, resin, goggles, gloves, IPA, RPI parts as needed, AtomS3/AtomS3R and batteries, PC sheet, filament, inserts, magnets, fasteners.

**Before the semester** (done or on 09.09): base MG400 package published with README, `AGENTS.md`, a v0.1 tag and a CLI; the resin bench-test set for Gate A. Teams create their own repos from the template above and post the URLs before the first meeting.

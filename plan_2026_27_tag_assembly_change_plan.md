# Plan: rebuilding the 2026/27 labs around the tag-assembly cell

Date: 09.09.2026. First contact sessions: 11.09 (3D Print), 12.09 (Data Acquisition, Smart Solutions).

This document turns your nine-point brief into concrete changes for every lab of the three semester-1 courses (5 labs each, EST + ENG) and the semester-2 Prototyping milestones. It replaces the abstract "dispensing system" target in `plan_2026_27_*_sem1.md` with one physical product: **the MG400 assembles the Cyber Tag Arms tag** (AtomS3 + battery module + polycarbonate glass glued over the screen).

Nothing in the grading structure, repo rules, peer review or contact-hour dates changes. Only the object the labs build changes, plus the hardware that the change forces.

Adhesive decision (09.09): **transparent UV resin** (the 405 nm SLA printer resin), cured by a **UV LED on the robot nozzle**. Consequences are marked with "UV" below.

---

## 0. Your brief → what it forces

| # | Your point | Consequence for the labs |
|:--|:--|:--|
| 1 | MG400 assembles the tag (AtomS3, 0.85" screen, battery module, PC glass glued in front so the suction cup seats on the screen) | One assembly cycle becomes the unit of work in every course. 3D Print L2 designs the fixtures for a 24×24 mm part. Suction cup ≥ φ13 mm from the Dobot kit seats on a 24×24 glass. |
| 2 | Keep the pressure-curve → fill-level idea, but as a hypothesis (compensation needed or not). New sensor because the MG400 pump box is low range | Data Acquisition keeps its whole Fourier/op-amp arc; only the sensor part number and the pressure range (0–110 kPa instead of 4–7 bar) change. L5 gets an explicit null-hypothesis outcome that scores the same as a positive one. |
| 2b | UV: adhesive = transparent UV resin, UV LED on the nozzle | Resin is thin (roughly 100–500 mPa·s), so the pump box range is enough and the problem flips from "enough pressure" to "small, drip-free dose". Curing is a fourth tool action (`uv_ms`) with its own driver on the tool board. Resin cures in daylight, so the syringe and tip must be shielded, and the LED cone must never reach the tip. |
| 3 | Syringe dispenser mounted on the suction-cup lifting nozzle, one 3/2 solenoid valve: cup by default, syringe when energized | The pneumatic line from the pump box is shared. Unpowered valve = cup. This fixes the safe state (valve off, pump off = nothing dispenses) and defines the tool board (point 7). |
| 4 | End state = a working sample of the machine assembling a test tag | This is the semester-2 Prototyping M2/M5 demo and the integration project in each course. |
| 5 | ML and lots of samples, otherwise the central IoT control system has no reason to exist | Every cycle from every team logs the same record into the shared InfluxDB. The dataset, not the dashboard, is the product of Smart Solutions L4. |
| 6 | Everyone uses an agent | Labs are written as specs with physics-locked acceptance tests. Grade the artefact and the data, never the code volume. Team repo gets an `AGENTS.md`. Defense includes one live change. |
| 7 | Final tool = PCB with ESP32 logic + solenoid valve drivers | Data Acquisition L3 PCB *is* the tool board. Its interface is fixed in Smart Solutions L2, its enclosure in 3D Print L3. |
| 8 | ESP32 camera on the nozzle so a remote operator can record workflows quickly | Smart Solutions L2 (stream), L3 (through VPN), L4 (teach/record/replay UI). 3D Print L3 mounts it. |
| 9 | Modular 3D-printed work area, tray with ≥5 source slots and ≥5 finished slots | 3D Print L2 becomes the tray + jig lab. Data Acquisition L4 uses it for 5-cycle batches. |
| 10 | Instructor provides the base Python software for the MG400; Dobot's own software is not used | Smart Solutions L1 stops being "write a TCP wrapper" and becomes "install, read, run, extend, fix". Every course's robot script imports the same package. Bug reports and pull requests to it are the existing bonus-point path ("finding the instructor's errors"), now with a concrete target. |

---

## 1. The target system (what all 15 labs build)

```
                          ┌────────────────────────────┐
  Browser (anywhere) ───► │ RPI control station        │ ◄── LAN ── MG400 (+ DO to pump box, fallback)
                          │ Flask + base MG400 package │
                          │ recipe/workflow recorder   │
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
      ┌──────────────┐  unpowered   ┌─────────────────────────┐
      │ 3/2 valve    │ ───────────► │ suction cup (φ13/φ16)   │  lifting nozzle, spring
      │ direct-acting│  energized   ├─────────────────────────┤
      │ vacuum-rated │ ───────────► │ amber syringe 5/10 ml, 0.8–1.2 mm tip; UV LED 405 nm offset ≥30 mm from tip │
      └──────────────┘              └─────────────────────────┘
```

**One assembly cycle** (semester 1 scope: gluing the glass; battery plugging is a semester-2 stretch goal):

1. Human or robot places an AtomS3 into the jig (source tray, slot 1–5).
2. Valve energized, pump in blow mode → syringe dispenses resin dots or a bead along the screen bezel. Pressure curve logged.
3. Valve off, pump in suction mode → cup picks a PC glass from the source tray. Vacuum curve logged (pick success is visible in it).
4. Glass placed on the resin, short press, pump blow-off to release.
5. Robot moves the nozzle so the UV LED is over the tag and the syringe tip is outside the cone. LED on for `uv_ms` (seconds, not minutes, for a thin layer under clear PC). Cured through the glass.
6. Nozzle cam takes an image of the result. Tag moved to a finished slot.
7. Record written: cycle id, team, robot parameters, dispense time, cure time, both curves at 100 Hz, syringe fill (ground truth), image, outcome label.

**Tag BOM**: AtomS3 (24×24×13 mm, 0.85" IPS) or AtomS3R, battery (ATOM TailBat 190 mAh, 55×22×14 mm, or Atomic Battery Base), PC glass ≈ 24×24 mm, transparent UV resin (a few tens of mg per tag).

**UV curing constraints** (they show up in 3D Print L1/L3, Data Acquisition L3 and Smart Solutions L2):
* Use a 405 nm LED, not 365 nm. Polycarbonate absorbs most light below about 385 nm, so 365 nm would not cure through the glass; 405 nm passes.
* Resin cures under daylight and slowly under room LEDs. Amber or black-taped syringes, an opaque tip cap when idle, and the LED aimed away from the tip with a shroud. Resin cured inside the tip is the real clog case, which is what the dP/dt interrupt from Data Acquisition L3 is for.
* Cure dose is time × irradiance. Measure it once (cure time vs. pull-off force with the MG400) and store it as a recipe parameter rather than guessing.
* Safety: 405 nm at LED power is an eye hazard. Goggles rated for 405 nm at the table, LED interlocked to the ESP32 (off when the board is unpowered or when the robot is not at a cure pose), shroud on the LED. Uncured resin is a skin sensitizer: nitrile gloves, IPA cleaning, cured waste only into the bin.

**Work area**: modules snap into the 100 mm grid / 5 mm holes of the polycarbonate table. Tray module: 5 glass slots + 5 AtomS3 slots (source), 5 finished slots, one gluing jig, one VL53L0X post, one waste cup for dry dispensing.

---

## 2. Hardware decisions and gates

Each gate has a date because a downstream lab document cannot be finished before it.

### Gate A — resin dose and cure test (decided: UV resin; bench test by 18.09)

The adhesive is transparent 405 nm UV resin. The pump box range (110 kPa) is more than enough for it; the open questions are dose control and cure.

Bench test: 10 ml amber syringe, tips 0.6 / 0.8 / 1.2 mm, pressure 20–100 kPa in steps, pulses 50–500 ms. Measure dose mass per pulse on the 0.01 g scale, and drip after the pulse ends. Then glue five glasses to five scrap PC squares with a 405 nm LED at 30 mm for 5 / 10 / 20 / 40 s and pull them apart with the MG400 (the 3D Print L2 tensile fixture). Result: one tip size, one pressure setpoint, one pulse length, one cure time. These go into the first workflow recipe.

Things to expect:
* A thin resin drips. The cure for drips is a small tip, low pressure and short pulses, not vacuum suck-back (the cup branch owns the vacuum). If drips remain, a needle tip with a small dead volume helps more than more pressure.
* Because resin viscosity is low, the material back-pressure term in the fill-level model is small. The null outcome (no time compensation needed) is now the likelier one in Data Acquisition L5. It is graded the same as the positive outcome, so nothing is lost. The sensor was bought to measure fill level; if the data says fill level does not matter, the same sensor is the clog detector and the pick verifier. Setting out to find one thing and finding another is ordinary engineering, and the lab text says so, so nobody feels pushed to invent a dependence that is not there.
* Resin bonds well to PC and to the AtomS3 plastic shell; check that it does not creep onto the screen area before it is cured (dispense on the bezel, not the glass centre).
* Sensor range stays as in Gate B; the external-compressor fallback is no longer needed.

### Gate B — pressure sensors (order now, confirm by 03.10)

Recommendation: two analog sensors from the same family as before, so labs 1–3 keep their formula, op-amp and offset logic unchanged.

| Branch | Sensor | Range | Output | Why |
|:--|:--|:--|:--|:--|
| Syringe (positive) | MPX5100DP | 0–100 kPa | 0.2–4.7 V | Same transfer-function shape as the MPX5700AP, uses the full pump range instead of 15 % of it |
| Cup (vacuum) | MPXV6115V | −115–0 kPa | 0.2–4.7 V | Pick success and cup seal quality become measurable; second data stream for ML |

Alternative: one compound-range I2C sensor (e.g. XGZP6847D, −100…+100 kPa) on the common port. Cleaner mechanically, but it removes the analog signal chain that labs 1–2 teach. Reject unless Gate A forces a redesign.

The 10 MPX5700AP already ordered are still useful: L1 session on 12.09 runs on them (any sensor gives a noise spectrum), and the L1 analysis asks the team to calculate why the range is wrong. The correct sensors arrive before the L1 defense on 03.10.

### Gate C — 3/2 valve (choose by 22.09, in the session-2 order; Smart Solutions L2 needs it)

* Direct-acting, spring return, explicitly vacuum-rated. Pilot-operated valves need minimum pressure and do not switch under vacuum.
* Port assignment: common ← pump line; NO (unpowered) → cup; NC (energized) → syringe.
* Coil voltage 24 V if the tool board takes 24 V from the pump box supply, else 12 V with its own supply. Decide together with the board power design.
* Mass matters: it rides on the arm. Target < 100 g.

### Gate D — nozzle camera (choose by 22.09, in the session-2 order)

* Option 1: M5 AtomS3R-CAM. Firmware and mount already exist in the repo (`EST/Prototyping/defence/rar-tartu-protyypimine-master`, `defence/Tallinn/cam`). Lowest risk.
* Option 2: AI-Thinker ESP32-CAM. Cheapest, needs its own 5 V and a programmer.
* Either way it is a WiFi MJPEG source; the tool board only supplies power.

### Gate E — tool PCB freeze (14.11, Data Acquisition L3 review)

Board contents: ESP32 (Atom Lite header or module), MPX5100DP + MPXV6115V footprints, op-amp stage, comparator for dP/dt interrupt, two MOSFET valve drivers with flyback diodes (valve + spare), a constant-current UV LED channel (1–3 W, 405 nm, PWM-able, with a hardware enable that is low by default), two optocoupled outputs for pump box control, VL53L0X connector, cam power connector, 24 V → 5 V buck, USB-UART. Ordered right after the review, arrives for L4.

### Tag hardware

* The AtomS3 dev kit with 0.85" screen is listed as EOL at M5Stack. Check stock; AtomS3R has the same footprint and screen. Decide before ordering 8+ tags and the glass batch.
* PC glass: laser cutting polycarbonate produces toxic fumes and yellow edges. Use CNC milling or die cutting. This is exactly the order that 3D Print L5 can place (see below).

### Ordering rule

* Session 1 runs on what is on the shelf: last year's leftovers and the mystery box. No order before it.
* At every meeting the next lab's **component list** is handed out with the next lab's text. Teams use the time between meetings to finish the current lab, prepare the next one, and defend the current one at the next meeting.
* The consolidated order for meeting N goes out **10 days before meeting N**. Anything not on the list is the team's own purchase, as before.
* Each lab document therefore ends with a section **Components for the next lab** with quantities per team. That section is the order list; there is no separate spreadsheet.
* Gates A–D above are timed to the order dates, not to the defenses.

### Ordering calendar

Meeting dates: 3D Print on Fridays (11.09, 02.10, 23.10, 13.11, 04.12, 16.01), Data Acquisition and Smart Solutions on Saturdays (12.09, 03.10, 24.10, 14.11, 05.12, 16.01). One order per meeting pair, on the earlier date.

| Order date | For meeting | What goes in the order |
|:--|:--|:--|
| none | 11–12.09, session 1 | Shelf and mystery box: MPX5700AP, Atom Lite, breadboards, LM358N, resistor/capacitor kits, soldering kits, syringes and 4 mm tube, RPI + SD + LAN cable, MG400 suction kit and pump box, PLA, calipers, pens. Instructor buys the Gate A bench-test set immediately (09.09): 405 nm resin, one amber syringe set with 0.6/0.8/1.2 mm tips, one 405 nm LED, goggles. |
| 22.09 | 02–03.10, session 2 (L1 defense, L2 intro) | Data Acquisition L2: MPX5100DP ×10, MPXV6115V ×10, LM358N ×20, extra breadboards and jumper kits. Smart Solutions L2: second Atom Lite per team (×6), camera ×6 (Gate D), 3/2 valve ×6 with 4 mm push-in fittings and tube (Gate C), logic-level MOSFET modules ×12, 405 nm LEDs 1–3 W ×10 with star heatsinks and constant-current drivers ×6, USB cables. 3D Print L2: M5 bolts/nuts/washers for the table holes, heat-set inserts, PETG, magnets. Consumables: amber syringes ×40, tips ×50 each size, tip caps, nitrile gloves, IPA, resin 1 kg, 405 nm goggles ×8. |
| 13.10 | 23–24.10, session 3 (L2 defense, L3 intro) | Data Acquisition L3: VL53L0X ×10, LM393 comparators, 100 Ω / 100 pF, twisted and shielded cable, JST connectors. Smart Solutions L3: Digital Ocean credit, domain, nothing physical. 3D Print L3: cable glands, strain reliefs, LED heatsinks, magnets, inserts, PETG. Suction cups φ13 and φ16. |
| 03.11 | 13–14.11, session 4 (L3 defense + PCB review, L4 intro) | Tool-board BOM so it is on the shelf when the boards arrive: MOSFETs, flyback diodes, optocouplers, 24 V → 5 V buck modules ×6, headers, connectors. Digital scale 0.01 g ×4. Dummy PC glasses (cut from sheet) ×30. Resin refill. **PCBs are ordered on 14.11, the day of the review**, so they land before 05.12. |
| 24.11 | 04–05.12, session 5 (L4 defense, L5 intro) | AtomS3 or AtomS3R ×10 and batteries ×10 for real assembly cycles in L5 and semester 2. Spare valves, tips, resin. 3D Print L5: the CNC or die-cut order for the glass batch is placed by the teams after the 04.12 review, arriving for semester 2. |
| 06.01.27 | 16.01.27, L5 defenses | Spares only. Semester-2 list handed out on 16.01. |

---

## 3. Per-course lab changes

Format for each lab: **Keep** / **Change** / **New** / **Physics-locked acceptance** (what a team must show that an agent cannot write for them) / **Data produced** (record that goes into the shared database).

The existing lab documents in `ENG/*/…[Lab 1–3]` and `EST/*/…` are last year's texts (UR5, PCB in lab 2, 4–7 bar). They are rewritten, not patched. Labs 4–5 documents do not exist yet.

### 3.1 Data Acquisition

**L1 — Raw signal and first Fourier** (defense 03.10)
* Keep: breadboard, 100 Hz ADC → UART, 30 measurements × 3 levels, Falstad, FFT noise sources.
* Change: no soldering session in L1 (no practice boards on the shelf). The first session is bench basics on the solderless breadboard — rows and rails, passive vs. active, datasheet pinout, multimeter; hand soldering moves to the tool PCB (designed in L3, populated when the boards arrive in L4).
* New: the Lab 2 order list is produced by the team as Mouser part numbers in `docs/bom_lab2.md`, one line per part saying which simulation or measurement asks for it. Order of work: Falstad → breadboard → measurement → order on 22.09.
* Change: pressure source = hand syringe for day one, MG400 pump box from week two. Sensor = MPX5700AP on 12.09, MPX5100DP when it arrives. Target range 0–110 kPa.
* New: analysis task "effective resolution of the 5700 vs. the 5100 in a 0–110 kPa system" (ADC bits × sensor span → Pa per LSB). This replaces the Resolution Determination consultation content with a lived example.
* Acceptance: CSV of 90 measurements, notebook with spectrum, a number for Pa/LSB for both sensors, oscilloscope screenshot.
* Data: none to the central DB yet (no RPI link until Smart Solutions L2).

**L2 — Op-amp and filtering, four configurations** (defense 24.10)
* Keep: everything. Four configurations, 4 × 30 measurements, SNR table, moving average.
* Change: offset/scaling numbers for the 0.2–4.7 V of the 5100 into 0–3.2 V; same circuit, new resistor values. Add the vacuum sensor as configuration 3b (same op-amp stage, inverted slope) so the cup branch is instrumented by the end of L2.
* Acceptance: four spectra side by side from the same pump box pulse, SNR numbers.

**L3 — dP/dt interrupt, I2C, tool PCB** (defense 14.11, PCB review)
* Keep: derivative, Schmitt trigger, interrupt → STOP, VL53L0X with long-cable noise diagnosis and RC fix, PCB review before ordering.
* Change: the PCB is the tool board from Gate E, not a sensor-only board. Adds valve drivers, pump box control and the UV LED channel. Clog test now uses the real valve and a real clog: leave a tip in daylight until the resin cures in it, energize, does the interrupt drop the valve within one sample?
* New: "safe state" is a measurable thing: with power removed from the ESP32, prove with the vacuum sensor that the cup branch is connected and nothing dispenses.
* Acceptance: schematic + layout + DRC clean, Gerber, interrupt latency measured on the scope, three VL53L0X datasets (short / long noisy / long filtered).

**L4 — Data collection with the MG400** (defense 05.12)
* Keep: Python script (on the base MG400 package), 500+ cycles, pandas cleaning, Fourier of curves, response-time analysis.
* Change: the cycle is the assembly cycle from section 1. Dispense goes into the waste cup for the bulk of the dataset (no tag consumed), pick/place recirculates the same five dummy glasses between source and finished slots so a 5+5 tray supports unlimited cycles without a human.
* New: ground truth for fill level. Two accepted methods: (a) scale reading of the syringe every 25 cycles, (b) known full volume minus counted dispenses at a weighed mean dose. Each record carries the fill estimate and its method.
* New: pick-success label from the vacuum curve (plateau reached or not), verified by the cam image.
* New: cure time is a recorded parameter. A small side dataset (cure time × pull-off force, 5 × 5 tags) is enough to set the recipe value and is a physics-locked number the team cannot write from a chair.
* Acceptance: ≥500 records in the shared DB with both curves and images, plus the CSV in the repo.
* Data: this is the dataset every L5 uses.

**L5 — ML model** (defense 16.01.27)
* Keep: train/test, linear → tree → forest, time features vs. Fourier features, cross-team model transfer, MSE/R².
* Change: the question is stated as a hypothesis with two equally graded outcomes. H1: dose per unit time depends on fill level → produce the compensation table (dispense-ms vs. fill) and show the corrected dose scatter. H0: within ±10 % dose, no dependence → prove it with the residuals and delete the compensation from the recipe. The proof is the dispensed mass on the scale, not the model's own score.
* New: second, smaller model: pick-success classifier from the vacuum curve (binary, easy win, immediately useful in Smart Solutions L5 for retry logic).
* Acceptance: model file loads in the RPI Flask app (Smart Solutions L4 endpoint) and returns a fill estimate for a live curve; scale measurement of ten dispenses at two fill levels.

### 3.2 Smart Solutions

**L1 — RPI control station and MG400 API** (defense 03.10)
* Keep: RPI setup, IPv4 with two interfaces, Flask buttons, RPI screen.
* Change: the MG400 TCP wrapper is not written by the students. They install the instructor's base package (pip from a tagged git URL, so fixes propagate), read it, run it from the command line, and build the Flask layer on top. Dobot's own software is off the table. First-day goal is pick-and-place a tag with the Dobot suction kit, controlled from the phone. Pump box wired to the MG400 DO for now (the ESP32 takes over in L2).
* Change: what a team adds in L1 is the missing piece, not the base: pump box DO control if absent, position teach/save/replay, a status poll. Anything they fix in the base goes back as a pull request. A merged PR is bonus points under the existing rule.
* New: the team repo gets an `AGENTS.md` describing the system and pointing at the base package's README. This is the documentation whose real user is the other teams' agents and the next year's course.
* Acceptance: video of a tag lifted and placed from a phone; position teach/save/replay of three points.

**L2 — ESP32 sensors and RPI integration** (defense 24.10)
* Keep: UART JSON, WiFi alternative, HTTP GET/POST, local Mosquitto, latency comparison.
* Change: the ESP32 now also *acts*: it takes commands (`valve`, `pump`, `dispense_ms`, `uv_ms`) and reports both sensors and the LED state. `uv_ms` is refused unless the RPI has confirmed the cure pose, and the LED always times out on the ESP32 side. The message format is the tool-board interface that Data Acquisition L3 implements on the PCB. Freeze it in this lab.
* New: nozzle camera streaming to the RPI page (Gate D). Latency of cam vs. sensor data measured.
* Acceptance: one page showing MG400 status, pressure, vacuum and the cam; a dispense triggered from the browser, curve visible.

**L3 — Digital Ocean droplet and VPN** (defense 14.11)
* Keep: everything (droplet, WireGuard, nginx, status page, routing).
* Change: the cam MJPEG must survive the proxy (nginx buffering off for that location). Remote operator sees the nozzle from home.
* Acceptance: from outside the lab, place a tag and watch it on the nozzle cam.

**L4 — MQTT logging and unified interface** (defense 05.12)
* Keep: Mosquitto and InfluxDB on the droplet, locking, view mode, doorbell, offline buffer, UX test.
* Change: "recipes" become **workflows**: the operator jogs the robot while watching the cam, presses record at each waypoint, picks an action (suction on/off, dispense N ms, UV cure N s, blow-off, wait), and saves. Replay runs the cycle. This is your point 8.
* New: the shared record schema (section 1, step 6) is written by every team into the same InfluxDB bucket with a team tag. The central portal shows per-team cycle counts and the last image. The dataset is the deliverable; the dashboard is its viewer.
* Acceptance: a workflow recorded in under 5 minutes by another team; 100 cycles from that workflow in the DB.

**L5 — Fault tolerance, REST API, LLM** (defense 16.01.27)
* Keep: measured RPI limitations, separate processes and queues, cable-pull tests, REST API through the portal, time lock, audit log.
* Change: safe state is now physical and testable: pump off, valve unpowered → cup branch. Pull the ESP32 USB mid-dispense and show on the vacuum sensor that the line went to the cup.
* New: the `/api` README is written so an agent can run the whole cycle. Demo: an agent (Claude Code, whatever the team uses) is given only the API description and asked to assemble one tag through the portal. Retry-on-pick-failure uses the Data Acquisition L5 classifier.
* Acceptance: the agent-driven cycle succeeds on the first attempt with an audit log showing every call.

### 3.3 3D Printing and CAD

**L1 — Blender to printer, then Fusion** (defense 02.10)
* Keep: Blender pen holder on day one, mesh diagnostics, 45° rule, straight vs. round, orientation tensile test, print-time integration, Fusion rebuild with measured flange.
* Change: Part D "from pen to syringe" becomes "syringe next to the suction cup". Measure the Dobot lifting nozzle and its spring travel; the syringe holder clamps to it, nozzle tip 5–10 mm above the cup face, 4 mm tube routing for both branches, and a mounting boss for the UV LED shroud at least 30 mm from the tip, aimed so the cone misses the tip. Syringe sizes 5 and 10 ml as parameters (20 ml is unnecessary for resin doses).
* Acceptance: syringe swapped one-handed while mounted; cup still lifts a glass with the holder attached.

**L2 — Work-area modules** (defense 23.10)
* Keep: universal foot for the 5 mm holes and 100 mm grid, snap-fit tops, bolt-compression tensile test with the MG400, FEA, 2D drawing.
* Change: the modules are the tray and jig set from section 1: 5+5+5 slots, gluing jig that holds an AtomS3 with the screen up and reachable by the bead, VL53L0X post, waste cup holder, cam calibration target.
* New: registration test. Print the tray twice on different printers; measure slot positions with calipers; the MG400 must pick from both with the same taught points. This is the repeatability number Data Acquisition L4 relies on.
* Acceptance: caliper table for both prints, robot picks 5 of 5 glasses from each.

**L3 — Enclosure and print-pause** (defense 13.11)
* Keep: integration graph, BOM, ventilation, cable entries, print-pause for inserts and magnets, assembly guide.
* Change: two enclosures instead of one: the tool-board housing on the arm (light, valve and board inside, cam on a short adjustable mount looking at the nozzle tip, UV LED with heatsink and shroud, strain relief for tube and USB) and the RPI + screen housing at the table.
* Acceptance: arm-mounted mass measured (target < 250 g with valve and syringe empty), cam image shows the nozzle tip and the tray in one frame.

**L4 — Improving an existing design, three approaches** (defense 04.12)
* Keep: manual vs. generative vs. original, MG400 load test, comparison table.
* Change: candidate parts are the syringe holder from L1, the tray from L2, the valve bracket from L3. The metric options (speed, strength, cycles) stay.

**L5 — ISO drawing and CNC order** (defense 16.01.27)
* Keep: ISO drawing, GD&T, tolerance analysis printed insert vs. CNC part, instructor review, order, validate on arrival.
* Change: the part is one of: (a) the PC glass batch for the tags (CNC-milled or die-cut, 50–100 pcs, tolerance against the jig), (b) the tray base plate that registers the tray to the robot. Option (a) is preferred: it has a user outside the course (the 2027 game), which is the strongest protection against renaming a drawing "sufficient".

### 3.4 Prototyping, semester 2 (milestones in `plan_2026_27_EST.md`)

Keep the five-milestone structure. Rename the objects:
* M1 audit → which team's tool board, tray, workflow and model go into the cell.
* M2 integration prototype → first complete tag glued by the robot from a recorded workflow.
* M3 ML deployment → fill-level model live; compensation on or off by the L5 result; pick-retry logic live.
* M4 functional prototype with enclosures → battery module plugging added (press-fit with the cup, or a second fixture), cable management, another team assembles a tag in 10 minutes.
* M5 production-ready → a run of tags for the 2027 summer camp with full documentation. The camp is the external user.

The current `ENG/Prototyping/… [Milestone N]` documents are the sumo-arena texts from spring 2026 and are unrelated; they stay as an archive. New milestone documents are written in January 2027.

---

## 4. Cross-cutting rules

### Agents (your point 6)

* Each lab document has an **Acceptance** section whose items are physical or measured: a CSV with a given shape, a caliper table, a scale reading, a video of the robot, a scope screenshot. An agent can write the code that produces them, which is fine. It cannot produce the artefact.
* The team repo template gets `AGENTS.md` at the root: system description, interfaces, how to run each lab. It is graded as documentation because it has a real reader.
* The base MG400 package ships with its own README and `AGENTS.md` so an agent can drive the robot from the first session. Its issue tracker is where "the instructor's software is buggy" turns into a graded, physics-locked contribution: a PR is either merged and the robot behaves, or it is not.
* At each defense, one live change requested on the spot (different slot, different dispense time, different tag orientation). Ten minutes are already reserved for questions; this uses part of them. It is the "master is sick" moment for the semester and needs no extra structure.
* Do not add rubrics for "AI use". Grade the artefact, the data and the answers.

### Data (your point 5)

* One record format for the whole year, defined in Smart Solutions L2 and frozen in L4. Every team writes into the same bucket. Cross-team model transfer in Data Acquisition L5 is only possible because of this.
* The central portal exists to make four robots produce one dataset. Say this in the Smart Solutions concept paragraph; it answers "why the cloud" better than the VPN does.

### ML questions the year can actually answer

1. Fill level from the dispense pressure curve, and whether time compensation is needed (Data Acquisition L5, hypothesis with two valid outcomes).
2. Pick success from the vacuum curve (binary, feeds retry logic in Smart Solutions L5).
3. Bead quality from the nozzle-cam image (semester 2, only if 1 and 2 are done).

---

## 5. Document rewrite schedule

All documents exist in EST and ENG. Write EST first (student language), translate with an agent, review the terminology. Template: keep the current headings (Objective, Background, Tools, Project Breakdown, Simulation/Analysis, Testing, Development Log, Results, Feedback) and add four short sections: **Interfaces** (what this lab gives to and takes from the other courses), **Acceptance**, **Data produced**, and **Components for the next lab** (the order list, quantities per team).

The rule from section 2 sets the deadlines: the lab N+1 text and its component list are handed out at meeting N, and the text is final on the order date before meeting N+1.

| Date | Documents | Depends on |
|:--|:--|:--|
| 10.09 | 3D Print L1 (EST+ENG) + L2 component list | measure the lifting nozzle first |
| 11.09 | Data Acquisition L1, Smart Solutions L1 (EST+ENG) + L2 component lists | nothing; shelf hardware |
| 11.09 | Base MG400 Python package published: repo, tag `v0.1`, README with every call, `AGENTS.md`, a CLI that connects, enables, jogs, reads position, toggles DO and stops | your code |
| 18.09 | Gate A result (tip, pressure, pulse, cure time) into the plan and into L2 texts | bench test |
| 22.09 | L2 for all three courses final; session-2 order out | Gate A, B, C, D |
| 02–03.10 | L2 handed out with L3 component lists | |
| 13.10 | L3 for all three courses final, tool-board interface spec; session-3 order out | L2 texts |
| 23–24.10 | L3 handed out with L4 component lists | |
| 03.11 | L4 for all three courses final, record schema; session-4 order out | L3 texts |
| 13–14.11 | L4 handed out with L5 component lists; PCB review and PCB order | |
| 24.11 | L5 for all three courses final; session-5 order out | L4 texts |
| 04–05.12 | L5 handed out with the semester-2 list | |
| Jan 2027 | Prototyping M1–M5 | semester-1 results |
| Rolling | `plan_2026_27_EST.md` and `_ENG_sem1.md`: replace the concept paragraphs, course-interplay table and order list with sections 1–2 of this document | this plan approved |

Existing files to retire from the active set (keep in git): `ENG/*/… [Lab 1–3]`, `EST/*/… [Lab 1–3]`, both consultation documents (their content moves into Data Acquisition L1 and L2 as tasks).

---

## 6. Decisions only you can make

1. Who controls the pump box: ESP32 tool board (robot-agnostic, my recommendation) or MG400 DO (simpler on day one). The plan above assumes the ESP32 from L2 onward.
2. AtomS3 vs. AtomS3R for the tag, given the EOL listing.
3. 3D Print L5 object: glass batch or tray base plate.
4. Battery module plugging by the robot: semester-2 stretch goal (as written) or out of scope.
5. Base package scope for day one: connect/enable/clear-error, MovJ/MovL/jog, position read, DO for the pump box, emergency stop, and a small CLI. Anything beyond that (recipes, Flask) is student work. Also: where the repo lives and whether teams get write access or PR-only.
6. UV LED power class: a 1 W LED cures slower but needs no heatsink and is safer at the table; 3 W cures in seconds but needs a heatsink and stricter interlocks. The Gate A bench test answers this.

Sources used for hardware facts:
* Dobot mini vacuum pump box −70…110 kPa, 24 V, I/O controlled, 4 mm tube: https://www.robotshop.com/products/mg400-accessory-mini-vacuum-pump-box
* Dobot suction cup kit sizes φ4/φ8/φ13/φ16: https://www.dobot-robots.com/products/accessories/vacuum-suction-cup-kit.html
* AtomS3 24×24×13 mm, 0.85" IPS, EOL listing: https://shop.m5stack.com/products/atoms3-dev-kit-w-0-85-inch-screen
* ATOM TailBat 190 mAh, 55×22×14 mm: https://shop.m5stack.com/products/atom-tailbat

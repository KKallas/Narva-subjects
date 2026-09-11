# Plan 2026/27 v3 — the three semester-1 subjects

Draft 10.09.26. Covers 3D Printing and CAD, Data Acquisition, Smart Solutions: what students build in each of the five labs, and what has to be bought for it. Prototyping (semester 2, Milestones 1–5) is unchanged in `plan_2026_27_ENG_v2.md`.

Supersedes `labs_build_lists.md` and `lab1_build_list.md`.

## How a lab runs

Every lab is the same four beats, and the calendar already fits them:

1. **The meeting.** We take the half-written lab document and go through the problem together — what is being built, what is unknown, what could go wrong. Everyone leaves with the same understanding and their own copy of the document.
2. **Build and simulate with what is already here.** The shelf, the old-stuff box, Falstad, Fusion, the slicer, a dry jog. There are no new parts yet and that is not a reason to wait — it is how you find out what you need.
3. **Order, within a week.** What the simulation and the first build say you need, as real part numbers with stock checked. The order date is ten days before the next meeting.
4. **The parts arrive at the next meeting**, where the next lab is handed out. The previous lab is defended online on the Tuesday after that week, so the contact session is for teaching and handing over, never for defending.

Nobody is blocked waiting for parts, because the first week never needs them.

## One sensor, on the syringe

There is **one pressure sensor per cell, and it sits on the syringe branch**. The suction cup has none. Everything the cup does is judged by the nozzle camera and by whether the glass is where it should be — which is cheaper, is the same evidence a person would use, and forces the camera to be a real instrument instead of decoration.

That decision runs through every subject. Data Acquisition instruments one branch, not two, and its second model is about the dispense rather than the pick. The tool board carries one analog channel. The sample line carries one pressure field. The pneumatics still have two branches, because the valve switches between them, but only one of them is measured.

## The five demos

Each stage ends in one thing that only works if all three subjects worked.

| Stage | Handed out | Defended online | The demo |
| :-- | :--- | :--- | :--- |
| 1 | 11–12.09 | Tue 06.10 | Press a letter on the Atom → the MG400 draws it |
| 2 | 02–03.10 | Tue 27.10 | The robot picks a glass off a printed tray while the browser shows the camera and the live pressure trace as the valve switches |
| 3 | 23–24.10 | Tue 17.11 | A resin bead lands on a bezel, cures, and the cell stops itself when the tip clogs — reachable from outside the lab |
| 4 | 13–14.11 | Tue 08.12 | The cell runs unattended for an hour and writes down every cycle |
| 5 | 04–05.12 | Tue 19.01 | Ask over an API for a tag; a learned policy picks the glass; the model sets the dose; the glass is a manufactured part |

## Hours per team

| Subject | L1 | L2 | L3 | L4 | L5 | Total |
| :--- | --: | --: | --: | --: | --: | --: |
| 3D Printing | 30 | 34 | 28 | 30 | 24 | 146 |
| Data Acquisition | 32 | 26 | 32 | 22 | 30 | 142 |
| Smart Solutions | 28 | 26 | 30 | 30 | 34 | 148 |

## Dates

**Contact sessions.** 3D Printing meets Fridays: 11.09, 02.10, 23.10, 13.11, 04.12, 16.01.
Data Acquisition and Smart Solutions meet Saturdays: 12.09, 03.10, 24.10, 14.11, 05.12, 16.01.
Order dates: 22.09, 13.10, 03.11, 24.11, 06.01. PCBs are ordered 17.11, the day of the review.

**Defences are online, on the Tuesday after the week we meet**: 06.10, 27.10, 17.11, 08.12, and 19.01.27. The tag is due 72 h before, which is always the Saturday — the same weekend as the contact session where the next lab is handed out.

So one lab runs: handed out at a contact session · three weeks of work · tag on the Saturday of the next contact session · defend online on the Tuesday after it. The contact session is for teaching and for the handover, never for defending. From Lab 3 onward the cell is reachable through the VPN, so a team can drive its own robot during the defence from anywhere; before that, whoever has to show hardware joins the call from the lab.

---

# 3D Printing and CAD

## Lab 1 — The printer, and a tool that gives (30 h)
*Out 11.09 · order 22.09 · defense 06.10, online*

**Session 1, together (3 h).** First login to Fusion. Sketch, extrude, parameters — enough for one part. Everyone leaves with a printed calibration plate in their hand, and the robot draws a letter with a marker taped to its flange.

**Build**

1. **Calibration plate, in Fusion, during the session.** Five clearances — 0.0 / 0.1 / 0.2 / 0.3 / 0.4 mm on the diameter — driven by one user parameter, and **each clearance appears twice**:
   * **Printed in place**: the peg sits inside its hole and the two are printed together as one job. Nothing is assembled afterwards.
   * **Printed apart**: the same hole, with its peg printed flat beside it, to be pushed in by hand after the print.

   **The plate must slice under 45 minutes** — if it does not, make it smaller. That constraint is part of the exercise.
2. **Two different numbers come out of it, and that is the point.**
   * On the printed-in-place side: at the small clearances the two walls have fused into one lump and the peg will never move. Somewhere up the row it comes free and spins. That threshold is roughly one nozzle width, and it is why an internal wall welds itself shut.
   * On the printed-apart side: measure every hole and every peg with calipers *before* trying to fit them — the hole comes out smaller than drawn and the peg bigger, and the difference is the number to remember. Then fit them: too tight, right, sloppy.
   * Write both numbers down. **The in-place clearance and the assembly clearance are not the same**, and every later part in every later lab uses whichever of the two applies to it.
3. **Overhang piece**: four walls at 30 / 45 / 60 / 90°, no supports, sag measured.
4. **Tensile coupons**: four orientations, two each, pulled apart on the robot through a scale. The inter-layer strength ratio from this is used in every later lab.
5. **Pen holder, in Blender** — the other way of modelling, and where meshes bite. Export, watch the slicer complain, fix it, print it.
6. **The holder must give.** A flexure, a sprung barrel, a foam pad — their design. Test: teach the pen 2 mm too low on purpose. Nothing breaks, the line still draws.
7. **Straight against curved**: a square tube and a round tube, same wall, same height, same cross-section area. Slice both at identical settings and compare the times; print one pair and read the stepped surface of the round one with calipers at 0 / 45 / 90°. A curve costs time that a flat face does not, and this is the number that says how much.
8. **Print-time notebook**: slice the STL in numpy, sum the layer areas, compare with the slicer and with the clock, for four orientations plus the two tubes. Orientation is a calculation, not a taste.

**Simulate before ordering:** slice everything in three orientations and pick one with a reason. There is nothing else to simulate in this lab and that is the point — the printer is the simulator, and it costs 40 minutes a run.

**Order by 22.09:** PLA in the colour they want, M5 bolts/nuts/washers, heat-set inserts, PETG, magnets.

**I provide:** two printers with a known profile, PLA on the shelf, calipers per team, a steel ruler, pens and masking tape, the luggage scale or HX711 set, the MG400 with the base package and the drawing routine.

## Lab 2 — The table (34 h)
*Out 02.10 · order 13.10 · defense 27.10, online*

**Session 2, together.** Why a pick point that is right today is wrong next week. Repeatability as a measured number.

**Build**

1. **Universal foot** for the table's 5 mm holes at 100 mm pitch, with a spring fastener: thumb in, holds 2 kg of pull, tab releases it.
2. **Snap-top standard**, 30 × 30 mm. Every module for the rest of the year plugs into it.
3. **Source tray**: 3 + 3 pockets first to prove the clearance from Lab 1, then the full 5 + 5.
4. **Finished tray, gluing jig, waste-cup holder, VL53L0X post, camera calibration target.**
5. **Bolt compression coupons**: the same bar plain and with an M5 bolt through it, both pulled to failure. Prestressed concrete, in PLA.
6. **The pen holder rebuilt in Fusion**, parametric, from caliper measurements of the flange. Draw the same letter with both holders and measure the difference with a ruler.
7. **Registration test**: print the tray on two printers, caliper every pocket, teach the pick points on one and pick 5 of 5 from the other without re-teaching. The number `max |A − B|` is what the other subjects quote all year.
8. **FEA** on the snap hook and both coupons, before printing.
9. **A 2D drawing** of the tray and the foot with a dimension table.

**Simulate before ordering:** FEA on the hook, and slice the tray set to see what a full tray costs in hours before you print two of them.

**Order by 13.10:** PETG, more magnets and inserts, suction cups φ13 and φ16, sacrificial dummy glasses.

**I provide:** the polycarbonate worktable with its 5 mm grid, a second printer for the registration test, the AtomS3 shell (or a printed dummy) to size the jig, dummy PC glasses.

## Lab 3 — The tool (28 h)
*Out 23.10 · order 03.11 · defense 17.11, online*

**Session 3, together.** Pressure finds every layer line. Where the load path goes, and why last year's caps leaked.

**Build**

1. **Measure the Dobot lifting nozzle** and its spring travel.
2. **Syringe holder** clamped to the fixed part of the nozzle: tip 5–10 mm above the cup face, both 4 mm tube runs, syringe size as a parameter, swappable with one hand. Start from last year's holder — measure it, say what is wrong with it, change that.
3. **LED boss** at least 30 mm from the tip, aimed so the cone misses the tip and hits the cure point.
4. **Three-stop syringe clamp** for the pressure levels Data Acquisition needs. Bolts and washers carry the tension; printed spacers only ever get squeezed.
5. **Syringe cap with a designed O-ring groove** for the air line. Last year's caps are on the shelf and they leaked; the brief is "why?".
6. **Valve port adapters**, bolted to the valve's own mounting holes, sealed with an O-ring face and the toothpick-and-thread-glue pipe joint.
7. **Leak test**: 110 kPa held five minutes, soapy water on every joint, then 500 valve cycles and the same test again.

**Simulate before ordering:** the O-ring groove arithmetic from the measured bore, the blow-off force, and the plate section, all on paper before any CAD. That is what decides the O-ring size on the order.

**Order by 03.11:** O-rings in the size the groove calculation asked for, anaerobic thread sealant, cyanoacrylate, PVC pipe, M5 threaded rod and wing nuts, toothpicks.

**I provide:** the 3/2 valves (arrived 02.10), the pump box, the MG400 suction kit, syringes and tips, a spray bottle of soapy water, last year's leaking caps and holders on a labelled shelf.

## Lab 4 — Enclosures, and one part made better (30 h)
*Out 13.11 · order 24.11 · defense 08.12, online*

**Session 4, together.** Mass on the arm, cables that catch, and how to define a test before you redesign anything.

**Build**

1. **An integration graph** in draw.io: every component a node, every tube and cable an edge, each housing's boundary drawn on it.
2. **A BOM with masses**, because the arm has a budget.
3. **Every internal component modelled** as a placeholder body with real measured dimensions.
4. **The tool housing**: valve and board inside, no tube bend under 20 mm, ventilation at the coil, strain reliefs, camera on a lockable two-axis mount, lid on magnets or inserts. Under 250 g with an empty syringe.
5. **The panel mount and the station shelf**: the phone held at the table edge at a readable angle, chargeable in place and removable with one hand; the station box and its cables off the worktable. On the Lab 2 feet.
6. **Print-pause**: nuts and magnets embedded mid-print, at least three features.
7. **One part improved against one stated metric** — print time at equal strength, strength at equal print time, or cycles before wear. Pick the part and **define the test before the redesign**. Manual redesign against generative design, three pieces each, tested on the robot with the same fixture and the same taught points.
8. **20 dry cycles** with the housed tool, and an assembly guide with a photo per step.

**Simulate before ordering:** FEA on all versions with the same load and mesh, and Fusion's mass against the scale within 10 %.

**Order by 24.11:** PETG, cable glands, strain reliefs, spare magnets and inserts, filament for the improved part.

**I provide:** the tool board or its Gate E envelope, the camera, the LED with its star heatsink, a contact thermometer, the kitchen scale.

## Lab 5 — The drawing and the order (24 h)
*Out 04.12 · order placed by the teams after the 04.12 review · defense 19.01, online*

**Session 5, together.** A drawing is a contract with someone who will never speak to you. Every ambiguity becomes their choice.

**Build**

1. **Decide the object and the quantity** on day one: the glass batch, or the base plate.
2. **Measure what it meets** — the AtomS3 shell, its corner radius, the tray pocket.
3. **Requirements as numbers**, written before any geometry.
4. **A parametric Fusion model.**
5. **An ISO drawing with GD&T**: views, a section, a title block, and real geometric tolerancing — flatness, position, profile of a surface — with datums named, not just ± numbers on dimensions. Surface and material notes.
6. **A tolerance stack**, worst case and RSS, for the glass in the pocket and on the bezel.
7. **Hand-cut test pieces** from sample sheet, filed to the drawing and checked against it. The cheapest reality check in the year.
8. **A real quote from a real shop**: their drawing sent, their questions answered, their price and lead time recorded.
9. **A validation plan written before the parts arrive**, and run when they do.

**Simulate before ordering:** the tolerance stack is the simulation. If it says the part cannot be made at that price, that is the result.

**Order:** the CNC or die-cut glass batch, placed by the teams after the 04.12 review.

**I provide:** polycarbonate sample sheet, files and a cutting jig, two shop contacts, the review on 04.12 and a second look by e-mail before the order goes.

---

# Data Acquisition

## Lab 1 — The device, and the first signal (32 h)
*Out 12.09 · order 22.09 · defense 06.10, online*

**Session 1, together (3 h).** The bench: breadboard rows and rails, what in the kit is passive and what is active, reading a pinout off a datasheet, and the multimeter. Nothing is soldered in this lab; everything is on a solderless breadboard, so a wiring mistake costs a jumper wire and not a sensor.

**Build**

1. **The Atom as a WiFi access point with a captive portal.** Join `team-N-tag`, the browser opens by itself.
2. **Image upload to the 0.85" screen** through that portal — pick a file, it appears on the device.
3. **Letter chooser**: the screen loops the alphabet, a press picks the one showing and sends it out.
4. **Pressure prototype**: the MPX5700AP from the old box straight to the ADC. Supply and output checked with the multimeter before the ESP32 is connected.
5. **100 Hz sampling** → one line per sample over UART, and a Python logger writing CSV.
6. **Measurements**: 10 × 3 pressure levels with the syringe by hand, then the same with the pump box once Smart Solutions can switch it, then the same again on the MPX5100DP when it arrives.
7. **The first spectrum**: FFT of the raw signal, every peak given a hypothesis, two of them tested by switching that source off and re-measuring.
8. **Falstad model** of sensor → ADC with a noise source; simulated noise against measured, in mV and in LSB.
9. **Pa per LSB** for both sensors, and what 15 % of a sensor's span does to the noise floor in Pascals.

**Simulate before ordering:** the Falstad model and the Pa/LSB arithmetic. Those two decide which sensor goes on the order and why.

**Order by 22.09:** MPX5100DP with a spare, LM358N with spares, jumper kit. No vacuum sensor: the cup branch is not instrumented.

**I provide:** MPX5700AP, AtomS3 units with screens, breadboards and passive kits, multimeters, an oscilloscope with FFT, syringes and 4 mm tube, the pump box, the MG400.

## Lab 2 — The signal chain (28 h)
*Out 03.10 · order 13.10 · defense 27.10, online*

**Session 2, together.** Why the sensor's 4.7 V will not go into a 3.3 V pin, and what an op-amp actually does about it.

**Build**

1. **Config 1**: Lab 1's wiring re-measured, so all four spectra are comparable.
2. **Config 2**: a divider.
3. **Config 3**: an LM358N stage that subtracts the 0.2 V offset and scales 4.7 V into the ADC range.
4. **Config 4**: config 3 plus digital filtering in firmware — a moving average, a median filter, and oversampling with decimation. Three filters, one config, and the Fourier plot of each says what it actually removed. A median kills a spike that an average only smears.
5. **15 measurements per configuration**, one CSV, one SNR table, four spectra, four scope screenshots at the same pulse.
6. **The uncertainty budget**: resolution, noise, drift over an hour, and absolute accuracy against a reference — the multimeter on the sensor output, and a reference gauge or a known head of water if one can be had. State the measurement uncertainty of the finished chain as one number with its units, and say which term dominates it.
7. **The curve of one real valve switch**, logged end to end: pump to blow, valve to the syringe branch, pressure rises, valve back to the cup, pressure falls. The rising edge is what stage 3 puts a derivative threshold on and what stage 5 learns the dispense from, so it is worth logging cleanly once.

**Simulate before ordering:** the op-amp stage in Falstad with a 50 mV common-mode noise source, and the resistor values chosen there. Those values are the order.

**Order by 13.10:** the resistors and capacitors the simulation picked, VL53L0X, LM393 comparators, 100 Ω / 100 pF, twisted and shielded cable, JST connectors.

**I provide:** the 3/2 valve and MOSFET modules (arrived 02.10), the scope, the pump box, glasses for the pick.

## Lab 3 — Real-time safety, and the board (30 h)
*Out 24.10 · order 03.11 · defense 17.11, online, PCB ordered the same day*

**Session 3, together.** A tip that has cured shut. What must happen in one sample, and why the station cannot be the one to do it.

**Build**

1. **dP/dt from the Lab 2 data**, with the threshold chosen from the measured slopes — a normal dispense against a clog. Show in the frequency domain why differentiating multiplies noise by 2πf, and therefore why the filter has to come before the derivative and not after it.
2. **Falstad**: differentiator plus a Schmitt trigger with enough hysteresis that ripple does not toggle it.
3. **On the breadboard**: comparator → ESP32 interrupt → valve released, alarm latched, event sent, without waiting for the station.
4. **Latency on the scope**: threshold crossed to coil released. One number, and the whole safety argument rests on it.
5. **Polling against interrupt, measured.** Build the same protection as a polling loop as well, and put the two side by side: worst-case latency, what happens when the main loop is busy, lines of code, and how long each took to get working. Accuracy, cost and development time — the choice is defended with all three, not just the fastest number.
6. **Two cores.** Sampling and the safety path on one core, the JSON stream and the link on the other, as separate FreeRTOS tasks with a queue between them. Measure the jitter of the 100 Hz sampling with the other core loaded, and again with everything on one core. That difference is the reason the ESP32 has two.
7. **Clog test and empty-syringe test**, for real.
8. **VL53L0X nozzle calibration**: 100 readings on a short cable, 100 on 40 cm beside the robot's power cables, then 100 with RC filtering and a twisted pair.
9. **The tool PCB in Fusion 360 Electronics**: schematic → layout → DRC clean → Gerber, their own, from their own footprints. Pre-check at the consultation on 05.11, reviewed at the online defence on 17.11, ordered the same day only if the review passes.
10. **Safe state proved** with the ESP32 unpowered, and with one sensor rather than two: the valve's spring return puts the pump on the cup, so the syringe branch reads no pressure on your only sensor, nothing can leave the tip, and the LED enable is low. Show all three on one trace.

**Simulate before ordering:** the comparator in Falstad with both ramps and 20 mV of ripple on the input. The R and C values that come out go on the board.

**Order by 03.11:** MOSFETs, flyback diodes, optocouplers, 24 V → 5 V buck modules, headers and connectors — the tool-board BOM. **PCBs on 14.11**, after the review.

**I provide:** Fusion 360 Electronics on the same education licence, the JLCPCB account and the 05.11 pre-check, a scope with two channels, the 3/2 valve, the cured-shut tip for the clog test.

## Lab 4 — The dataset (22 h)
*Out 14.11 · order 24.11 · defense 08.12, online*

**Session 4, together.** What makes a dataset a designed object rather than a pile of logs: randomisation, ground truth, and deliberate failures.

**Build**

1. **Teach the waypoints**: waste cup, five source slots, five finished slots, camera pose, VL53L0X post.
2. **A cycle script**: parameters in, one record out — a CSV row, both curves, one image — published to the shared database.
3. **Recirculation** so five dummy glasses support unlimited cycles, then 20 cycles unattended with a person in the room.
4. **The grid**: 3 speeds × 3 pressures × 20 repetitions, randomised in blocks. At least 180 cycles per team; four teams pooled is over 700 records.
5. **Ground truth for fill level**: the syringe on the scale every 25 cycles.
6. **Labels**: pick success from the camera frame taken after the lift — a documented, deterministic check, not a trained model. And at least 25 deliberate dispense failures: 15 with a tip left to cure shut, 10 with the syringe run empty. Without failures there is no classifier.
7. **A 50-cycle subset** logged through the raw Lab 1 path with the same cycle ids, so signal quality can be compared later.
8. **The cleaning notebook**: what was dropped and why, correlations, outliers, response time against fill.

**Simulate before ordering:** nothing to simulate; this is robot time. Plan the run instead — how long 180 cycles takes, when the scale readings happen, who is in the room.

**Order by 24.11:** resin refill, tips, spare dummy glasses, a 0.01 g scale if there is not one per team.

**I provide:** the shared database credentials, the scale, dummy glasses, resin, gloves and goggles.

## Lab 5 — The model, and a policy that learns (30 h)
*Out 05.12 · order 06.01 · defense 19.01, online*

**Session 5, together.** Two questions: does the fill level change the dose, and can the cell get better at picking by itself. One is answered with a model, the other with a policy.

**Build**

1. **Load the pool**: your records and the other three teams' from the shared bucket.
2. **One feature-extraction function**, used by the notebook and by the station app. The same function, not two that agree today.
3. **A split by weighing block**, with 5-fold grouped cross-validation on the rest.
4. **Linear regression → decision tree → random forest** on fill level, with residuals.
5. **Comparison 1**: time features against time + Fourier features. **Comparison 2**: op-amp curves against the raw 50-cycle subset, same cycle ids.
6. **H1 or H0, decided from the residuals** — either a compensation table, or a proof that none is needed and the sensor is a clog detector and pick verifier instead. Both are the same grade.
7. **The scale proof**: ten weighed dispenses at two fill levels, with compensation as decided.
8. **A three-way classifier on the dispense curve**: normal, clogged tip, empty syringe. Same sensor, same features, and the classes come from the deliberate failures in Lab 4. Confusion matrix, exported for the cell to use. This is what the single sensor is worth beyond the fill question, and it is the software twin of the hardware interrupt built in Lab 3.
9. **A learned pick policy — a contextual bandit.** Actions: 3 dwell times × 3 Z offsets. Context: cup diameter and slot. Reward: automatic, from the camera frame after the lift — no sensor on the cup, no scale, no human, which is what makes 400 trials possible in an afternoon. Write the check down before you run it, and measure how often it disagrees with a person watching. Thompson sampling over a Beta posterior per arm. Run a random policy first as the baseline, then the bandit, at least 200 trials each.
10. **The learning curve**: success rate against trial number, both policies on one axis, and the final policy as a table a person can read.

**The bandit's action range is whitelisted.** It proposes only within limits you set, the dP/dt interrupt sits above it and is not learnable, and the UV interlock is untouched. A policy that can explore into a 5 mm Z offset breaks glass.

Item 9 is why this lab always has a positive result. If the resin turns out not to care about fill level, H0 is the honest answer to question one — and the learning curve still went up.

**Simulate before ordering:** run the bandit against the recorded Lab 4 picks first, offline. If it does not beat the baseline on data you already have, it will not beat it on the robot.

**Order by 06.01:** spares only.

**I provide:** the pooled bucket with all four teams' records, dummy glasses that survive 400 picks, and the safety limits for the action range.

---

# Smart Solutions

## Lab 1 — The chain (28 h)
*Out 12.09 · order 22.09 · defense 06.10, online*

**Session 1, together.** Three boxes that each work are not a system. The system is the part between them.

**Build**

1. **The lab network, on a real router.** The address plan on paper first, then configured: a subnet for the robots, DHCP reservations so the MG400 and the station keep the addresses you gave them, the WiFi the Atom joins, the firewall, and a route left ready for the tunnel that arrives in Lab 3. This is the box where subnets, the routing table and NAT actually live, so it is where they get learned.
2. **Laptop talks to the MG400**: address, connect, enable, clear error, jog each axis, read position, DO on and off.
3. **Laptop talks to the Atom**: the letter picked on the screen arrives, over whatever link they choose.
4. **Letter → motion**: at least three letters, the team's initials. Where the paper is, what the pen-down Z is, what happens when the robot is not ready — all theirs.
5. **The pump box** on two DO lines: suction, blow, off, from their own code.
6. **Move it off your own laptop.** The station is a machine that stays in the lab: a second laptop, or a spare PC. Same code, no IDE on it, static IP on the robot subnet, the whole thing starting on boot without anyone logging in. Code that runs where you wrote it is not the same as code that runs.
7. **The station page**: jog buttons, teach a pose, go to a pose, delete a pose, the saved list — served over the lab network.
8. **The phone is the panel.** A Samsung on a stand at the table edge, full-screen browser on that page, and the jog buttons big enough to hit with a thumb. The operator never touches a keyboard.
9. **First pick**: teach four poses and replay them so the cup lifts a tag and puts it down.
10. **`AGENTS.md`** good enough that someone else's agent can start the system.

**Simulate before ordering:** draw the network before you plug anything in — robot, station, laptop, phone, Atom, addresses and subnets on one diagram. Most of week one is that diagram being wrong.

**Order by 22.09:** the second Atom per team, the nozzle camera, USB cables, the 3/2 valve with push-in fittings, MOSFET modules, 405 nm LEDs with star heatsinks and drivers.

**I provide:** the MG400 with its factory address, the base package with README and `AGENTS.md`, **a router per team (or one router with a subnet per team)**, a Samsung phone per team as the panel with a stand, a USB-C to Ethernet adapter per station, LAN cables, lab WiFi credentials, the pump box.

**No Raspberry Pi this year.** The three jobs it used to do are split: **the router** carries the network — subnets, routing table, NAT, DHCP, firewall. **The droplet** carries everything that has to be up when nobody is in the room. **The ESP32 is the cheap local logic unit** — the constrained processor that has to serve several peripherals at once in real time, which is where the hard part of concurrency now lives. The station itself is just a laptop or spare PC in the lab running the web app and talking to the robot, and the phone is its screen.

## Lab 2 — The tool board (26 h)
*Out 03.10 · order 13.10 · defense 27.10, online*

**Session 2, together.** An interface is a promise to someone who is not in the room. Four teams and two subjects have to agree on it.

**Build**

1. **Wire the arm**: both sensors to the ESP32, the valve through a MOSFET module, the camera.
2. **Firmware, reporting**: one JSON sample line every 10 ms, in the schema fixed in `LAB_CONVENTIONS.md`.
3. **Firmware, commands**: `valve`, `pump`, `dispense`, `uv`, `stop`, `clear` — one JSON object per line, an ack for each.
4. **Firmware, safety**: `uv` refused without `pose_ok`, the LED off after its milliseconds no matter what, safe state on a lost link.
5. **Station side**: serial reader, ring buffer, a command call that waits for its ack.
6. **One screen in the browser**: robot jog from Lab 1, live p and v, a 10 s rolling plot, the camera, buttons for pump and valve.
7. **MQTT as a second transport**, and a measured latency comparison of the two.
8. **Freeze `docs/tool-board-interface.md`** and hand it to the team designing the PCB. Hard deadline — their board depends on it.

**Simulate before ordering:** none needed; the parts are here. Instead, write the interface document first and build to it.

**Order by 13.10:** Digital Ocean credit and a domain, JST connectors, cable.

**I provide:** the valve, MOSFET modules and camera (arrived 02.10), the frozen JSON schema, the sensors from Data Acquisition Lab 2.

## Lab 3 — The cell on the internet (30 h)
*Out 24.10 · order 03.11 · defense 17.11, online*

**Session 3, together.** Where packets actually go. A robot on a private subnet, a router with the tunnel route on it, and a droplet that is the only address the outside world ever sees.

**Build**

1. **A practice droplet** of their own: SSH keys only, sudo user, firewall.
2. **A WireGuard server** on it, built from nothing.
3. **A WireGuard client** on the station, then a peer stanza on the shared course droplet. The phone gets the WireGuard app and the same treatment, so the panel works from outside the lab too.
4. **nginx** so the team's station lives at its own path on the course droplet.
5. **Flask working under a path prefix** — links, static files, and the camera `<img src>`.
6. **The camera through the proxy** at the same frame rate as locally, ±2. If it stalls it is buffering, and finding that is the lab.
7. **HTTPS** with certbot. One team does it, the others check it.
8. **The routing table exercise**: read the table on the router and on the station, `traceroute` to the robot, to the droplet and to the internet, and explain each hop before you run it. Then break one route on purpose and predict which of the three stops working.
9. **NAT, seen rather than described**: what the router rewrites on the way out, why the tunnel does not need a port opened inbound, and what the droplet sees as your source address.
10. **A 48-hour tunnel log** from the droplet side, which is the only box that is always on, plus one test from outside the building — on the phone, over mobile data, with lab WiFi off.

**Simulate before ordering:** the network diagram again, now with the tunnel on it, before a single config file is written.

**Order by 03.11:** droplet credit top-up if needed. Nothing physical.

**I provide:** the course droplet, the domain, the DNS records, and the router with its admin access.

## Lab 4 — The shared database and the recorder (30 h)
*Out 14.11 · order 24.11 · defense 08.12, online*

**Session 4, together.** Shared state, and what a second user does to code that assumed one.

**Build**

1. **Publisher on the station**: every cycle to `cell/N/cycle`, samples to `cell/N/sample`.
2. **Subscriber on the droplet** writing into InfluxDB.
3. **The workflow recorder**: jog with the camera in view, Record adds a step, the workflow saves as JSON and replays.
4. **Recorder actions mapped** onto the frozen tool-board interface.
5. **Cycle record assembly**: cycle id, curves sliced by event, response times.
6. **One page**: control, recorder, live plot, camera, the last 20 cycles with sparklines.
7. **The portal** on the droplet: all four teams' cycle counts and status live, **and a historical dashboard over the stored series** — cycles per day, dose against time, pressure curves from any past cycle recalled by id. Live numbers are a status page; a database earns its keep only when you can ask it about last week.
8. **Locking**: one session owns the robot, everyone else sees view mode.
9. **A UX test with another team**, then 50 replays of their workflow into the shared bucket.

**Simulate before ordering:** nothing physical to order. Write the record schema down first and check it against what Data Acquisition Lab 5 will need to train on.

**Order by 24.11:** nothing, unless the droplet needs more disk.

**I provide:** the MQTT broker and the InfluxDB instance on the course droplet with per-team credentials — shared by definition, since four teams write into one bucket. Everything published and queried is theirs.

## Lab 5 — Fault tolerance, the API, and an agent (34 h)
*Out 05.12 · order 06.01 · defense 19.01, online*

**Session 5, together.** What happens when a part of your system is gone. And the year's real exam: can an agent that has never seen your cell run it from your documentation.

**Build**

1. **A baseline, on both processors.** On the station: the single-process app under load, lost samples counted, where the interpreter lock actually bites, what blocks in a socket read, why threads do not fix it here — measured, not quoted from an article. **On the ESP32**: the same question on the cheap unit that has to sample at 100 Hz, hold the safety path, answer commands and keep a WiFi link alive at once. Load it until something gives, and write down what gave — a missed sample, a queue that overflowed, a heap that ran out, or the watchdog. That number is the budget everything else in this lab is spent from.
2. **Split it, on both sides.** On the station: a robot process, a tool process, a web process, over sockets and queues. On the ESP32: separate tasks with priorities and a queue between them, the real-time path pinned away from the network stack, and the watchdog fed by the right one. Re-run both baselines and show what changed.
3. **Timeouts** on both links, with a state for each thing being lost.
4. **Heartbeats and a supervisor** that restarts what dies.
5. **A safe state on every fault**: board stopped, robot stopped, lock released, the cycle written as failed.
6. **A REST API** under `/api/`: status, run a cycle, fetch a record, with its own README.
7. **Pick retry**, using the camera check after each lift — and, if the Data Acquisition bandit is ready, its policy chooses the retry action.
8. **A time lock**: remote API enabled from the panel at the table for N minutes, refused outside that window. It has to be pressed in the room.
9. **An audit log** of every API call with its source.
10. **The ESP32 offline buffer**: when the link drops, the last messages go to flash and replay when it returns.
11. **The agent demo**: write the README, hand it to an agent that has never seen the cell, and let it make one tag on the first attempt. Keep the transcript, including everything the agent got wrong — those are defects in your documentation, and they are the finding.

**Simulate before ordering:** pull the cables in a planned order and write down what should happen before you pull each one. That prediction, compared with what actually happened, is the lab's best table.

**Order by 06.01:** spares only.

**I provide:** the agent access for the demo, a second team to test against, and the fault list to work through.

---

# What I need to get

## Before 11.09 — on the shelf or bought today

| Item | Qty | Note |
| :--- | :--- | :--- |
| AtomS3 (with the 0.85" screen) | 8–10 | **On the shelf, confirmed 10.09.** The letter UI runs on the screen from day one. Two per team plus spares; the units for the tags themselves still come with the 24.11 order. |
| Fusion 360 education licences | 12 | First login is session 1; account activation cannot happen in the room. |
| PLA | 4–6 spools | Every team prints in the first session. |
| Calipers 0.01 mm | 4 | One per team, all year. |
| Pens, markers, masking tape, A4 | — | Day one drawing. |
| Old-stuff box, sorted and labelled | 1 shelf | Last year's holders, caps, feet, trays, boards. Each with a label saying what it was. This is the starting point for three labs. |
| Resin bench-test set | 1 | 405 nm resin, amber syringes with 0.6/0.8/1.2 mm tips, one LED, goggles. |
| Base MG400 package published, tagged, with README and `AGENTS.md` | 1 | Plus the drawing routine: 50 mm square and circle, pen-down Z as the argument. |

## Order 22.09 → arrives 02–03.10

Data Acquisition L2: MPX5100DP ×10 (one per cell plus spares — the only pressure sensor in the cell), LM358N ×20, breadboards, jumper kits.
Smart Solutions L2: second Atom per team ×6, nozzle camera ×6, 3/2 valve ×6 with 4 mm push-in fittings and tube, logic-level MOSFET modules ×12, 405 nm LEDs 1–3 W ×10 with star heatsinks, constant-current drivers ×6, USB cables.
3D Print L2: M5 bolts/nuts/washers, heat-set inserts, PETG, magnets.
Consumables: amber syringes ×40, tips ×50 per size, tip caps, nitrile gloves, IPA, resin 1 kg, 405 nm goggles ×8.

## Order 13.10 → arrives 23–24.10

Data Acquisition L3: VL53L0X ×10, LM393 comparators, 100 Ω / 100 pF, twisted and shielded cable, JST connectors, plus the resistors and capacitors each team's Falstad model asked for.
Smart Solutions L3: Digital Ocean credit, domain.
3D Print L3: **O-rings in the sizes the groove calculations produced, anaerobic thread sealant, cyanoacrylate, PVC pipe, M5 threaded rod and wing nuts, toothpicks**, cable glands, strain reliefs, LED heatsinks, magnets, inserts, PETG. Suction cups φ13 and φ16.

## Order 03.11 → arrives 13–14.11

Tool-board BOM: MOSFETs, flyback diodes, optocouplers, 24 V → 5 V buck modules ×6, headers, connectors.
Digital scale 0.01 g ×4. Dummy PC glasses ×30. Resin refill.
**PCBs are ordered on 14.11**, the day of the review, only for the boards that pass it.

## Order 24.11 → arrives 04–05.12

AtomS3 or AtomS3R ×10 and batteries ×10 for real assembly cycles. Spare valves, tips, resin. PETG and filament for the improved parts.
Polycarbonate sample sheet for the Lab 5 hand-cut test pieces.
3D Print L5: the CNC or die-cut glass order is placed by the teams themselves after the 04.12 review.

## Order 06.01 → arrives 16.01

Spares only. Semester-2 list handed out on 16.01.

## On the bench all year

Two 3D printers with a known profile · oscilloscope with FFT · four multimeters · four sets of calipers · luggage scale or HX711 + 20 kg cell · 0.01 g scale · soldering station (first used in the Lab 3 PCB work, not before) · contact thermometer · the polycarbonate worktable with its 5 mm / 100 mm grid · MG400 per team plus one spare · pump box per team · course droplet with the shared broker and database.

---

# Decisions this plan assumes

1. **Fusion comes first, Blender second.** Day one is a first Fusion login ending in a printed part, because that fits three hours and Blender does not. The mesh lesson still happens, on the pen holder, in week two — and it lands harder when they already know what a clean solid model feels like.

2. **The letter UI has its screen from day one.** The AtomS3 units are on the shelf. The AtomS3/AtomS3R line in the 24.11 order is now only for the tags that get assembled in stage 4 and 5, and can be trimmed to what the production run actually needs.

3. **3D Printing had six topics for five slots.** "Improving an existing design" is merged into Lab 4 beside the enclosures, keeping manual against generative and dropping the third approach. The alternative is to drop generative design and make "the second version must beat the first on one stated metric" a rule in every lab, which costs no hours at all.

4. **There is no Raspberry Pi this year, so the station is a laptop or spare PC that stays in the lab, and a Samsung phone is its screen.** Smart Solutions Lab 1 starts on the student's own laptop and moves onto that machine inside the same lab — same lesson as before, and arguably a better one, because "it runs on my machine" dies in week one. Three consequences:
   * The MG400 is on Ethernet, so each station needs a USB-C to Ethernet adapter if it has no port.
   * **The droplet is now the only always-on box.** Anything that had to run for days moves there; anything local is scoped to a session. The unattended hour in stage 4 and the 60-minute production run in M5 are fine — a laptop left plugged in covers an hour.
   * The phone is a genuinely better operator panel than the small screen was: touch jog, mounted at the table, and it already has WireGuard and a browser. If a team wants to go further and run the station itself on a phone under Termux, that is a good stretch goal — but Ethernet to the robot and USB serial to the tool board both need adapters and permission fiddling, so it is not the baseline.

   `plan_2026_27_ENG_v2.md` still describes an RPI station throughout, including the Prototyping milestones. Those need the same substitution before semester 2.

5. **The tool arrives at stage 3.** Data Acquisition needs pressure levels before that, so their Labs 1 and 2 use a hand on the plunger and the pump box. The printed clamp makes it repeatable from stage 3 onward.

6. **The bandit is the ML insurance policy.** The fill-level question may honestly come out H0. The learned pick policy produces a rising learning curve either way, so the year's ML story does not depend on the resin behaving.

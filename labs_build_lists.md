# Labs 1–5, all three courses — what each team builds

Draft 10.09.26. Supersedes `lab1_build_list.md`, which covered stage 1 only.

Each stage ends in one demo that needs all three courses. No team's demo works alone, which is harder to fake than a report.

| Stage | The demo | 3D Printing builds | Data Acquisition builds | Smart Solutions builds |
| :-- | :--- | :--- | :--- | :--- |
| **1** | Press a letter on the Atom screen → the robot draws it | the printer, and a pen holder that gives | the Atom UI, and the first pressure reading | the chain: laptop ↔ robot ↔ Atom |
| **2** | The robot picks a glass off a printed tray while you watch the vacuum curve in a browser | the table: feet, tray, jig | the signal chain that makes the curve readable | the tool board interface and the camera |
| **3** | A resin bead lands on a bezel, cures, and the cell stops itself when the tip clogs — from outside the lab | the tool on the arm | real-time safety, and the board that carries it | the cell on the internet |
| **4** | The cell runs unattended for an hour and writes down every cycle | enclosures, and one part made better | the dataset | the shared database and the recorder |
| **5** | Ask over an API for a tag; the model decides the dose; the glass is a manufactured part | the ISO drawing and the CNC order | the model, and H1 or H0 | fault tolerance, the API, and an agent that drives it |

Hours per team, rebalanced from the load audit. Totals unchanged from the plan.

| Course | L1 | L2 | L3 | L4 | L5 | Total |
| :--- | --: | --: | --: | --: | --: | --: |
| 3D Printing | 30 | 34 | 28 | 30 | 24 | 146 |
| Data Acquisition | 32 | 28 | 30 | 22 | 30 | 142 |
| Smart Solutions | 28 | 26 | 30 | 30 | 34 | 148 |

---

## Two things that apply to every lab

**Day one of every lab has no parts.** The order for a lab goes out ten days after it is handed out, so the first days are always: inventory what is on the shelf, build it where parts are free (Falstad, Fusion, the slicer, a dry jog), and let that tell you what to order. You find out what you need by starting, not by waiting to be given it.

**The agent writes the code; the measurement decides whether it was right.** Every one of these labs is passed with a measured number, and no agent can produce one. That is the whole design. An agent will write a captive portal in four minutes and a PCB layout in ten, and it will be confidently wrong about the things that only a caliper, a scope or a scale can settle. Each lab below names where it will lie to you. Learning to catch that is the actual subject of this year — the code was never the hard part.

---

# Stage 1 — "Press a letter, the robot draws it"

## 3D Printing Lab 1 — the printer (30 h)

1. **Tolerance block: a cylinder inside a cube.** One cube with a round hole, one peg for it, printed at five clearances (0.0, 0.1, 0.2, 0.3, 0.4 mm on diameter). Measure every hole and peg with calipers *before* trying to fit them.
2. **Overhang piece**: four walls at 30°, 45°, 60°, 90°, no supports. Measure the sag.
3. **Tensile coupons**: four orientations, two each, pulled apart on the robot through a scale. The inter-layer ratio from this is used in every later lab.
4. **Pen holder for the MG400 flange, with give in it.** A flexure, a sprung barrel, a foam pad — their design. If the taught Z is 2 mm low, the holder gives and the pen survives.
5. **Print-time notebook**: slice the STL in numpy, sum the layers, compare with the slicer and with the clock.

What it teaches: the hole comes out smaller than drawn and the peg bigger; below one nozzle width two internal walls weld into one; a rigid tool breaks the pen, the paper or the robot's alarm. Output that everything downstream uses: this printer's clearance number and this material's inter-layer ratio.

Where the agent lies: it will give you a nominal fit and a "standard" 0.2 mm clearance. It has never seen your printer. Only the calipers know.

Eats the hours: the coupons and the pen holder revisions.

## Data Acquisition Lab 1 — the device (32 h)

1. **AtomS3 as a WiFi access point with a captive portal.** Join `team-N-tag`, the browser opens by itself.
2. **Image upload to the 0.85" screen** through that portal — pick a file, it appears on the Atom.
3. **Letter chooser**: the screen loops the alphabet, a press picks the one showing and sends it out.
4. **Pressure prototype**: MPX5700AP from the old box straight to the ADC, 100 Hz, one line per sample over UART.
5. **Python logger** → CSV.
6. **First spectrum**: FFT of the raw signal, every peak given a hypothesis, two of them tested by switching that source off.
7. **Falstad model** of sensor → ADC with a noise source, simulated noise against measured.
8. **The Lab 2 order list** as real part numbers.

What it teaches: 128×128 pixels and a fixed colour format is all the screen you get, and no argument changes it. The raw pressure signal is noisy and the range is wrong — both get fixed in Lab 2, and the difference is only visible because this was measured first.

Where the agent lies: the captive portal it writes will be for a different ESP32 core version, and the sampling loop it writes will claim 100 Hz while sending inside the timing loop. Test Example 2 — 1000 lines in 10 s, no gap over 20 ms — is what catches it.

Eats the hours: the portal and the image format.

## Smart Solutions Lab 1 — the chain (28 h)

1. **Laptop talks to the MG400**: address, connect, enable, clear error, jog, read position.
2. **Laptop talks to the Atom**: the picked letter arrives, over whatever link they choose.
3. **Letter → motion**: three letters minimum, their own initials. Where the paper is, what the pen-down Z is, what happens when the robot is not ready — all theirs.
4. **Move it to the RPI**: same code, a box with no screen and no IDE. Static IP on the robot subnet, the whole thing starting on boot.
5. **The station page**: jog buttons, teach a pose, go to a pose, a list of saved poses.
6. **`AGENTS.md`** that lets someone else's agent start the system.

What it teaches: three boxes that each work are not a system; the system is the part between them. And code that runs on your laptop is not code that runs on the machine.

Where the agent lies: it will invent MG400 calls that do not exist. The package README is the only truth, and finding a real bug in that package is worth bonus points.

Eats the hours: the letter paths and the move to the RPI.

---

# Stage 2 — "It picks a glass off the tray, and you can see the vacuum"

## 3D Printing Lab 2 — the table (34 h)

1. **Universal foot** for the table's 5 mm holes at 100 mm pitch, with a spring fastener: thumb in, 2 kg pull to hold, tab to release.
2. **Snap-top standard**, 30 × 30 mm — every module built for the rest of the year plugs into it.
3. **Source tray**: 3 + 3 pockets first to prove the clearance from Lab 1, then the full 5 + 5.
4. **Finished tray, gluing jig, waste-cup holder, VL53L0X post, camera calibration target.**
5. **Bolt compression coupons**: the same bar plain and with an M5 bolt through it, both pulled to failure. Prestressed concrete, in PLA.
6. **The pen holder rebuilt in Fusion** from caliper measurements of the flange, parametric. Draw the same letter with both holders and measure the difference.
7. **Registration test**: print the tray on two printers, caliper every pocket, teach the pick points on one and pick 5 of 5 from the other without re-teaching.
8. **FEA** on the snap hook and both coupons, before printing.
9. **A 2D drawing** of the tray and the foot with a dimension table.

What it teaches: repeatability is a number you measure, not a hope. The registration number from item 7 is what sets the pick tolerance for the rest of the year.

Where the agent lies: it cannot tell you your snap hook will survive 20 insertions. FEA gives a strain number and the twentieth insertion gives the truth.

Eats the hours: the tray set and the two-printer registration.

## Data Acquisition Lab 2 — the signal chain (28 h)

1. **Config 1**: Lab 1's wiring, re-measured, so all four spectra are comparable.
2. **Config 2**: a divider.
3. **Config 3**: an LM358N stage that subtracts the 0.2 V offset and scales 4.7 V into the ADC's range.
4. **Config 3b**: the vacuum sensor on the identical stage — its output runs the other way, so the slope inverts in software.
5. **Config 4**: config 3 plus a moving average in firmware.
6. **15 measurements per config**, one CSV, one SNR table, four spectra.
7. **The vacuum curve of one real pick**, logged end to end: approach, seal, lift, release. Its plateau is the pick-success signal that stage 4 labels and stage 5 classifies.

What it teaches: what each stage of a signal chain does to noise, seen in the frequency domain rather than asserted.

Where the agent lies: it will hand you textbook resistor values and forget the LM358 is on a single supply and cannot swing to its rails. The scope at 0 and 100 kPa settles it.

Eats the hours: the op-amp stage, which is the first one most of them will build.

## Smart Solutions Lab 2 — the tool board (26 h)

1. **Wire the arm**: both sensors to the ESP32, the valve through a MOSFET module, the camera.
2. **Firmware, reporting**: one JSON sample line every 10 ms, in the schema fixed in `LAB_CONVENTIONS.md` because four teams have to interoperate.
3. **Firmware, commands**: `valve`, `pump`, `dispense`, `uv`, `stop`, `clear` — one JSON object per line, an ack for each.
4. **Firmware, safety**: `uv` refused without `pose_ok`, the LED off after its milliseconds no matter what, safe state on a lost link.
5. **RPI side**: serial reader, ring buffer, a command call that waits for its ack.
6. **One screen in the browser**: robot jog from Lab 1, live p and v, a 10 s rolling plot, the camera, buttons for pump and valve.
7. **MQTT as the second transport**, and a latency comparison of the two.
8. **Freeze `docs/tool-board-interface.md`** and hand it to the team designing the PCB. This is a hard deadline; their board depends on it.

What it teaches: an interface is a promise to someone who is not in the room.

Where the agent lies: it will write a serial reader that blocks, and the plot will look fine until the robot moves. Measure the latency; do not ask the agent whether it is fast.

Eats the hours: the command/ack protocol and the freeze.

---

# Stage 3 — "It puts a bead down, cures it, and stops itself — from outside the lab"

## 3D Printing Lab 3 — the tool (28 h)

1. **Measure the Dobot lifting nozzle** and its spring travel.
2. **Syringe holder** clamped to the fixed part of the nozzle, tip 5–10 mm above the cup face, both 4 mm tube runs, syringe size as a parameter, swappable with one hand. Start from last year's holder: measure it, say what is wrong with it, change that.
3. **LED boss** ≥30 mm from the tip, aimed so the cone misses the tip and hits the cure point.
4. **Three-stop syringe clamp** for the pressure levels Data Acquisition needs — bolts and washers carry the tension, printed spacers only ever get squeezed.
5. **Syringe cap with a designed O-ring groove** for the air line. Last year's caps leaked; they are on the shelf, and the brief is "why?".
6. **Valve port adapters**, bolted to the valve's own holes, sealed with an O-ring face and the toothpick-and-thread-glue pipe joint.
7. **Leak test**: 110 kPa held five minutes, soapy water on every joint, then 500 valve cycles and the same test again.

What it teaches: pressure finds every layer line. Steel carries tension, PLA carries compression, and a printed wall leaks through itself long before a seal fails.

Where the agent lies: it will give you an O-ring groove from a handbook table without knowing your barrel's bore or its spread across three caliper readings.

Eats the hours: the holder revisions and the leak chasing.

## Data Acquisition Lab 3 — safety and the board (30 h)

1. **dP/dt from the Lab 2 data**, threshold chosen from the measured slopes: a normal dispense against a tip cured shut.
2. **Falstad**: differentiator plus a Schmitt trigger with enough hysteresis that ripple does not toggle it.
3. **On the breadboard**: comparator → ESP32 interrupt → valve released, alarm latched, event sent — without waiting for the RPI.
4. **Latency on the scope**: threshold crossed to coil released. One number, and the whole safety story rests on it.
5. **Clog test and empty-syringe test**, for real.
6. **VL53L0X nozzle calibration**: 100 readings on a short cable, 100 on 40 cm beside the robot's power cables, then 100 with RC filtering and a twisted pair.
7. **The tool PCB**: schematic → layout → DRC clean → Gerber, their own, from their own footprints. Pre-check on 05.11, reviewed at the defense on 14.11, ordered the same day only if the review passes.
8. **Safe state proved with the ESP32 unpowered.**

What it teaches: a safety mechanism you have not timed is a story. And a board is where every decision of the last three labs becomes permanent.

Where the agent lies: it will produce a schematic that looks right and omit the flyback diode, or route a 24 V trace at signal width. DRC catches some of it, the review catches the rest, and neither of them is the agent.

Eats the hours: the PCB. Start the schematic in week one, not week three.

## Smart Solutions Lab 3 — the cell on the internet (30 h)

1. **A practice droplet** of their own: SSH keys only, sudo user, firewall.
2. **WireGuard server** on it, from nothing.
3. **WireGuard client** on the RPI, then a peer stanza on the shared course droplet.
4. **nginx** so the team's station lives at its own path on the course droplet.
5. **Flask working under a path prefix** — links, static files, the camera `<img src>`.
6. **The camera through the proxy** at the same frame rate as locally. If it stalls, it is buffering, and finding that is the lab.
7. **HTTPS** with certbot; one team does it, the others check it.
8. **The routing table exercise**: three interfaces on the RPI, `traceroute` to the robot, to the droplet, to the internet.
9. **A 48-hour tunnel log**, and one test from outside the building.

What it teaches: where packets actually go, which is the subject of the course.

Where the agent lies: it will give you an nginx config that works for a root-mounted app and silently breaks every relative URL under a prefix.

Eats the hours: the proxy and the camera.

---

# Stage 4 — "It runs by itself and writes down what it did"

## 3D Printing Lab 4 — enclosures, and one part made better (30 h)

1. **An integration graph** in draw.io: every component a node, every tube and cable an edge, each housing's boundary drawn on it.
2. **A BOM with masses**, because the arm has a budget.
3. **Every internal component modelled** as a placeholder body with real measured dimensions.
4. **The tool housing**: valve and board inside, tube runs with no tight bends, ventilation at the coil, strain reliefs, camera on a lockable two-axis mount, lid on magnets or inserts. Under 250 g with an empty syringe.
5. **The station housing** for the RPI and its screen, on the Lab 2 feet.
6. **Print-pause**: nuts and magnets embedded mid-print, at least three features.
7. **One part improved against one stated metric** — print time at equal strength, strength at equal print time, or cycles before wear. Pick the part, define the test *before* the redesign, then manual redesign against generative design, three pieces each, tested on the robot with the same fixture.
8. **20 dry cycles** with the housed tool, and an assembly guide with a photo per step.

What it teaches: defining the test before the redesign is the skill; the redesign is the easy half.

Where the agent lies: it will tell you the redesign is 30 % lighter. The scale and the fixture tell you whether it still survives.

Eats the hours: the tool housing and the improvement test.

## Data Acquisition Lab 4 — the dataset (22 h)

1. **Teach the waypoints**: waste cup, five source slots, five finished slots, camera pose, VL53L0X post.
2. **A cycle script**: parameters in, one record out — a CSV row, both curves, one image — published to the shared database.
3. **Recirculation** so five dummy glasses support unlimited cycles, then 20 cycles unattended with a person in the room.
4. **The grid**: 3 speeds × 3 pressures × 20 repetitions, randomised in blocks, ≥ 180 cycles per team. Four teams pooled is over 700 records, and stage 5 trains on the pool.
5. **Ground truth for fill level**: the syringe on the scale every 25 cycles.
6. **Labels**: pick success from the vacuum curve, and at least 25 deliberate failures — without failures there is no classifier.
7. **A 50-cycle subset** logged through the raw Lab 1 path, same cycle ids, so signal quality can be compared later.
8. **The cleaning notebook**: what was dropped and why, correlations, outliers, response time against fill.

What it teaches: a dataset is a designed object. Randomisation, ground truth and deliberate failures are decisions made before the robot starts, not after.

Where the agent lies: it will clean your outliers away without telling you which ones. Count them, name them, keep the count.

Eats the hours: robot time, which runs while you do something else.

## Smart Solutions Lab 4 — the shared database and the recorder (30 h)

1. **Publisher on the RPI**: every cycle to `cell/N/cycle`, samples to `cell/N/sample`.
2. **Subscriber on the droplet** writing into InfluxDB. The broker and the database instance are given, because four teams share them; everything written and read is theirs.
3. **The workflow recorder**: jog with the camera in view, Record adds a step, the workflow saves as JSON and replays.
4. **Recorder actions mapped** onto the frozen tool-board interface.
5. **Cycle record assembly**: cycle id, curves sliced by event, response times.
6. **One page**: control, recorder, live plot, camera, the last 20 cycles with sparklines.
7. **The portal** on the droplet: all four teams' cycle counts and status, live.
8. **Locking**: one session owns the robot, everyone else sees view mode.
9. **A UX test with another team**, then 50 replays of their workflow into the shared bucket.

What it teaches: shared state, and what a second user does to code that assumed one.

Where the agent lies: it will write a QoS 0 publisher that drops records silently under load, and the count will look fine until you compare it with the robot's.

Eats the hours: the recorder.

---

# Stage 5 — "Ask it for a tag"

## 3D Printing Lab 5 — the drawing and the order (24 h)

1. **Decide the object and the quantity** on day one: the glass batch, or the base plate.
2. **Measure what it meets** — the AtomS3 shell, its corner radius, the tray pocket.
3. **Requirements as numbers** before any geometry.
4. **A parametric Fusion model.**
5. **An ISO drawing**: views, a section, tolerances, surface and material notes, title block. This is the lab.
6. **A tolerance stack**, worst case and RSS, for the glass in the pocket and on the bezel.
7. **Hand-cut test pieces** from sample sheet, filed to the drawing, checked against it — the cheapest reality check in the year.
8. **A real quote from a real shop**, their drawing sent, their questions answered.
9. **A validation plan written before the parts arrive**, and run when they do.

What it teaches: a drawing is a contract with someone who will never speak to you. Every ambiguity in it becomes their choice, not yours.

Where the agent lies: it will produce a tolerance that no shop can hold at that price. The quote is the answer.

Eats the hours: the drawing, correctly.

## Data Acquisition Lab 5 — the model (30 h)

1. **Load the pool**: your records and the other three teams' from the shared bucket.
2. **One feature-extraction function**, used by the notebook and by the RPI app. The same function, not two that agree today.
3. **A split by weighing block**, 5-fold grouped cross-validation on the rest.
4. **Linear regression → decision tree → random forest** on fill level, with residuals.
5. **Comparison 1**: time features against time + Fourier features.
6. **Comparison 2**: op-amp curves against the raw 50-cycle subset, same cycle ids.
7. **Comparison 3**: train on one team, test on the others, as far as the data allows.
8. **H1 or H0, decided from the residuals** — either a compensation table, or a proof that none is needed and the sensor is a clog detector instead. Both are the same grade.
9. **The scale proof**: ten weighed dispenses at two fill levels, with compensation as decided.
10. **A pick-success classifier** from the vacuum curve, with its confusion matrix, exported for the cell to use.

What it teaches: the honest negative result. And that the proof is the mass on the scale, never the model's own score.

Where the agent lies: this is the big one. It will hand you an R² of 0.97 by leaking cycles from the same syringe fill across the split. The grouped split is the entire lab, and the residuals are how you catch it.

Eats the hours: features and the write-up, not the fitting.

## Smart Solutions Lab 5 — fault tolerance and the API (34 h)

1. **A baseline**: the single-process app under load, with the lost samples counted.
2. **Split it**: a robot process, a tool process, a web process, talking over sockets.
3. **Timeouts** on both links, and a state for each thing being lost.
4. **Heartbeats and a supervisor** that restarts what dies.
5. **A safe state on every fault**: board stopped, robot stopped, lock released, the cycle recorded as failed.
6. **A REST API** under `/api/`: status, run a cycle, fetch a record, with its own README.
7. **Pick retry**, using the Data Acquisition classifier on the live vacuum curve.
8. **A time lock**: remote API enabled from the RPI screen for N minutes, and refused outside that window.
9. **An audit log** of every API call with its source.
10. **The ESP32 offline buffer**: when the link drops, the last messages go to flash and replay.
11. **The agent demo**: write the README, hand it to an agent that has never seen the cell, and let it make one tag on the first attempt. Keep the transcript, including everything it got wrong.

What it teaches: everything above is about what happens when a part of your system is gone. And item 11 is the year's real exam — if an agent can drive your cell from your documentation, your documentation is true.

Where the agent lies: here it is the subject rather than the risk. Whatever it gets wrong in the demo is a defect in your README, and that is the finding.

Eats the hours: the process split and the retry logic.

---

# Decisions before this can be handed out

1. **AtomS3 count.** The letter UI needs the 0.85" screen and the plan has the batch arriving in December with one unit on the shelf. Either it is the first line of the 22.09 order, or the chooser runs headless on an Atom Lite and the screen is added when they arrive.

2. **3D Printing has six topics and five slots.** "Improving an existing design, three approaches" is merged into Lab 4 above, next to the enclosures, keeping manual against generative and dropping the third approach. The alternative is to drop generative design and make "the second version must beat the first on one stated metric" a rule in every lab instead, which costs no hours at all. Your call, and it changes the Lab 4 title.

3. **Smart Solutions Lab 1 now starts on a laptop** and moves to the RPI inside the same lab. That is a real lesson and it gets the letter drawn in week one, but it means the RPI station is finished later than the current document assumes.

4. **The letter alphabet.** Twenty-six letters of robot motion is a lab of its own. Three letters — the team's initials — is the requirement above; the alphabet grows if there is time.

5. **The tool arrives at stage 3, not stage 1.** Data Acquisition needs pressure levels before that, so their Lab 1 and Lab 2 measurements use a hand on the plunger and the pump box, exactly as their documents already say. The printed clamp makes it repeatable from stage 3 onward.

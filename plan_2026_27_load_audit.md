# Load audit 2026/27 — every checklist item, and what to do about it

Purpose: one row per checklist item in all 20 lab documents, with a verdict on whether a team of three — mostly software people, most of them holding a soldering iron for the first time, with an agent on the laptop and last year's leftovers on the shelf — can actually do it in the hours allotted.

Written 09.09.26. Source: `ENG/2026-27/*/*.md`, checklist items in the **Project Breakdown** section of each document.

## The rule this audit obeys

**Students write their own code and make their own mistakes.** Nothing here is solved for them in advance. No skeleton with the hard part filled in, no sketch shipped with a planted bug, no notebook where the analysis cells are already written. A logger that drifts because they wrote the timing wrong is worth more than any exercise we could design around it — they built it, they will find it, and finding it is the skill the whole degree is for. A team that is handed the working version learns that the working version comes from somewhere else.

**And nothing in these documents tells a student that something is hard.** Last year worked because nobody explained that it shouldn't. The documents state what has to be true at the end, and they say nothing about the difficulty of getting there. That is deliberate and it is not negotiable.

So the hours in this audit come from three places only, none of which is difficulty:

1. **Repetition that the statistics do not need.** 30 × 3 measurements repeated for three sources, 120 rows in one lab, three separate 300-reading I2C runs, a 500-cycle grid. Halving these changes no conclusion in any notebook.
2. **The same lesson taught twice.** Three transports where two make the comparison. Three redesign approaches where two make the argument. A status page in one lab and a portal in the next.
3. **Infrastructure that is shared by definition.** One MQTT broker and one database for four teams is one installation, not four. Everything else on the servers, each team still builds itself.

Plus one thing that is not a cut at all: **last year's leftovers are the official starting point.** You may start from last year's holder, cap, foot or tray — but measure it with calipers, state in one line what is wrong with it, and say what you changed. That is a better first exercise than an empty sketch, and it is what engineering actually looks like. It is the opposite of being given the answer: they are given a thing that does not work well enough, and told to find out why.

Where an item still does not fit its hours after all of that, the fix is **hours moved between labs**, or scope cut from the lab. Not a shortcut handed across the table.

## Verdicts

| Verdict | Meaning |
| :--- | :--- |
| **KEEP** | Leave it. This is the learning, including the parts that will hurt. |
| **TRIM** | Same task, less of it — fewer repetitions, fewer configurations, smaller grid. The conclusion survives the cut. |
| **SKIP** | Drop it. Costs hours, teaches something another item already teaches. |
| **MOVE** | Belongs in a different lab, where its subject already is. |
| **REUSE** | Start from last year's leftover part. Measure it, say what is wrong with it, say what you changed. |
| **RIG** | Shared infrastructure, installed once centrally because it is shared, not because it is hard. Teams still write everything that touches it. |
| **HOURS** | The work is right, the hours are wrong. Move hours from a lighter lab in the same course. |

---

# Data Acquisition

Course hours as written: 34 / 30 / 24 / 24 / 30 = 142.
**Proposed: 30 / 28 / 32 / 22 / 30 = 142.** Same total, moved to where the work actually is — Lab 3, which carries a comparator, an I2C investigation and a first PCB in 24 hours, takes eight hours from Labs 1 and 4, which are the ones carrying repetition.

## Lab 1 — Raw signal and first Fourier (34 h → 30 h, 13 items)

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Bench session: breadboard, passive kit, multimeter | KEEP | The 3 h is right for this and nothing else. |
| 2 | Repo from template, `AGENTS.md` | KEEP | The template is a folder tree and an empty `AGENTS.md`. They write what goes in it. |
| 3 | MPX5700AP on the breadboard, checked with the meter | KEEP | Meter before ESP32 is the habit that saves the sensors. |
| 4 | Firmware: 100 Hz ADC → UART | KEEP | They write it. The ones who put the send inside the timing loop will find out from Test Example 2, which is exactly what that test is there for. |
| 5 | Python UART logger → CSV | KEEP | They write it. |
| 6 | 30 × 3 hand syringe, MPX5700AP | TRIM | 10 × 3. This sensor is the "wrong range" example; it does not need a full dataset to make its point. |
| 7 | 30 × 3 pump box (week two) | TRIM | 10 × 3. Enough to show the noise changes with the source. |
| 8 | 30 × 3 MPX5100DP | KEEP | The dataset that matters, and the one Lab 2 compares against. |
| 9 | Falstad model with noise source | KEEP | Cheap, and the sim-vs-measured table is the best thing in the lab. |
| 10 | Notebook: time domain, Fourier, Pa/LSB | KEEP | Their notebook. `scipy.fft` has documentation and they have an agent. |
| 11 | Oscilloscope screenshot with the pump box running | KEEP | |
| 12 | Lab 2 order list as Mouser part numbers | KEEP | New, cheap, and the ordering discipline pays for itself in every later lab. |
| 13 | Tag 72 h before 03.10 | KEEP | |

**~4 h out, from repetition only.** Lab 1 gives two of its hours to Lab 3.

## Lab 2 — Op-amp and filtering (30 h → 28 h, 12 items)

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Copy `lab1/` → `lab2/`, `config` column | KEEP | |
| 2 | Falstad: divider vs. op-amp, 50 mV common-mode | KEEP | Before the breadboard, as written. |
| 3 | Config 2: divider | KEEP | |
| 4 | Config 3: LM358N differential stage | KEEP | The core of the lab, and the first op-amp most of them will build. Let them burn a few; that is what the five spares in the order are for. |
| 5 | Config 3b: MPXV6115V on the same stage | KEEP | |
| 6 | Config 4: moving average N = 10 | KEEP | |
| 7 | 30 per config, 120 rows | TRIM | 15 per config, 60 rows. The SNR table is unchanged. |
| 8 | 30 vacuum pulses | TRIM | 15. |
| 9 | One real MG400 pick logged end to end | KEEP | The vacuum curve here is what Lab 4 labels. |
| 10 | Notebook: four-way comparison, SNR table | KEEP | |
| 11 | Scope screenshots of all four configs | KEEP | |
| 12 | Tag | KEEP | |

**~4 h out, from repetition only.**

## Lab 3 — dP/dt, interrupt, I2C, tool PCB (24 h → 32 h, 13 items)

The worst hours-to-content ratio in the semester. The answer is hours, not help.

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Copy `lab2/` → `lab3/`, derivative column | KEEP | |
| 2 | Notebook: raw vs. filtered dP/dt, threshold from data | KEEP | Threshold chosen from data is the lesson. |
| 3 | Falstad: differentiator + LM393 Schmitt | KEEP | Simulating it first is the whole point; they will get the hysteresis wrong on the bench and the sim tells them why. |
| 4 | Breadboard: comparator → interrupt → valve off | HOURS | Their circuit, their values. This item is why the lab needs 32 h. |
| 5 | Latency on the scope | KEEP | The number the whole safety story rests on. |
| 6 | Clog test, empty-syringe test | KEEP | |
| 7 | VL53L0X 10 cm, 300 readings | TRIM | 100. |
| 8 | VL53L0X 40 cm next to MG400 cables, 300 readings | TRIM | 100. |
| 9 | RC + twisted pair + shield, 300 readings | TRIM | 100. |
| 10 | Calibration sequence: Z offset, X/Y scan | KEEP | |
| 11 | PCB: schematic → layout → DRC → Gerber | HOURS | Their board, drawn from their own schematic, footprints from the datasheets. The 05.11 consultation is a pre-check of their work, not a starting file. If it still will not fit, cut the board's scope at the Gate E review — fewer sections on the first board — rather than pre-drawing any of it. |
| 12 | Safe-state measurement (ESP32 unpowered) | KEEP | Cheap and it is the safety argument. |
| 13 | Tag, PCB review, order 14.11 | KEEP | The 14.11 date is the real constraint. Protect it with hours, and by starting the schematic in week one instead of week three. |

**~3 h out from the I2C repetition, ~8 h in from Labs 1 and 4.** Net: the lab becomes possible without anyone being handed anything.

## Lab 4 — Data collection with the MG400 (24 h → 22 h, 12 items)

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Copy `lab3/` → `lab4/`, cycle script on the base package | KEEP | The base MG400 package is the robot's driver, the same as `pyserial` is the port's. Everything above it is theirs. |
| 2 | Waypoints taught and saved | KEEP | |
| 3 | Cycle script: one cycle → one record → published | KEEP | |
| 4 | Recirculation, 20 cycles unattended | KEEP | |
| 5 | **Grid: 5 speeds × 5 pressures × 20 reps = 500 cycles** | TRIM | 3 × 3 × 20 = 180 per team. Pooled over four teams that is 720 records and Lab 5 trains on the pool. The single biggest saving in the semester, and it costs nothing but robot time. |
| 6 | Ground truth: scale every 25 cycles | KEEP | |
| 7 | Pick label rule, ≥ 25 deliberate failures | KEEP | Without deliberate failures there is no classifier. |
| 8 | Signal-quality subset: 50 cycles on the raw path | KEEP | |
| 9 | Cure dataset: 5 cure times × 5 glasses, pull-off force | MOVE | To Prototyping M2, where the tag has to actually stick. It is a second experiment with its own rig and it is not the ML question. |
| 10 | Notebook: cleaning, correlation, distributions, Fourier vs. fill | KEEP | |
| 11 | ≥ 500 records in the database and repo | TRIM | ≥ 250 per team, following item 5. |
| 12 | Tag | KEEP | |

**~12 h out, all of it robot time and one moved experiment.** Lab 4 gives six hours to Lab 3.

## Lab 5 — ML model, H1/H0 (30 h, 12 items)

The one lab where their own trade is the subject. Change nothing except the item that depends on other teams.

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Load own + other teams' records from the bucket | KEEP | |
| 2 | Feature extraction as one shared function | KEEP | The core discipline: the same function in the notebook and on the RPI. |
| 3 | 80/20 by weighing block, 5-fold grouped CV | KEEP | They will get grouping wrong at least once and see an impossible R². That is the lesson of the whole lab and it must not be pre-empted. |
| 4 | Linear → tree → forest, MSE, R², residuals | KEEP | |
| 5 | Comparison 1: time vs. time + Fourier features | KEEP | |
| 6 | Comparison 2: op-amp vs. raw subset | KEEP | |
| 7 | Comparison 3: 4 × 4 train/test between teams | TRIM | Best-effort on whatever is in the bucket on the day. Not a pass condition, because it depends on three other teams being finished. |
| 8 | H1 or H0 decided from residuals | KEEP | The point of the whole course. |
| 9 | Scale proof: 10 weighed dispenses × 2 fill levels | KEEP | The physical proof beats the model score. |
| 10 | Pick-success classifier, confusion matrix | KEEP | |
| 11 | Both models load in the Flask app | KEEP | |
| 12 | Tag | KEEP | |

---

# Smart Solutions

Course hours: 28 / 26 / 30 / 30 / 34 = 148. Unchanged — the cuts below land in the two labs that need them.

## Lab 1 — RPI control station (28 h, 11 items)

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Image SD, SSH, WiFi, hostname | KEEP | A spare imaged card lives on the shelf as a *spare part*, for the card that dies at 21:00. Not as a shortcut past the setup. |
| 2 | Static IP on `eth0` in the MG400 subnet | KEEP | |
| 3 | Install base package in a venv, read its README | KEEP | |
| 4 | CLI session: connect → enable → jog → DO | KEEP | First contact with the robot. |
| 5 | Wire the pump box to two DO lines | KEEP | |
| 6 | Own layer: `pump`, `teach`, `goto` | KEEP | |
| 7 | Flask page: jog buttons, position list, Teach/Go/Delete | KEEP | Their first Flask app. They are software students; this is their home ground and the one week they get to be fast. |
| 8 | RPI screen: full-screen browser on the status page | KEEP | |
| 9 | First pick: teach four poses, replay | KEEP | The moment the course becomes real. |
| 10 | `AGENTS.md` at the repo root | KEEP | |
| 11 | Base-package fixes as pull requests | KEEP | Bonus points, optional, as written. Finding the instructor's bug is worth more than being spared it. |

## Lab 2 — Tool-board interface and camera (26 h, 11 items)

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Wire the arm: sensors, valve MOSFET, camera | KEEP | |
| 2 | Firmware: JSON sample line every 10 ms | KEEP | The schema is fixed in `LAB_CONVENTIONS.md` because four teams must interoperate. Implementing it is theirs. |
| 3 | Firmware: command parser, `valve`/`pump`/`dispense`/`uv`/`stop` | KEEP | The interface they own and freeze. |
| 4 | Safety in firmware: `uv` needs `pose_ok`, LED timeout | KEEP | Non-negotiable. |
| 5 | RPI serial reader, ring buffer, ack waiting | KEEP | |
| 6 | Flask page: live p/v numbers and 10 s rolling plot | KEEP | |
| 7 | **WiFi variant: ESP32 AP, `GET /data`, `POST /cmd`** | SKIP | Two transports make the comparison; three make it three times. |
| 8 | MQTT variant: Mosquitto, publish/subscribe | KEEP | Keep this one — it is reused in Lab 4. |
| 9 | Latency for all three transports | TRIM | Two transports, same table, same conclusion. |
| 10 | Freeze `docs/tool-board-interface.md`, hand to the PCB team | KEEP | Hard deadline: the PCB depends on it. |
| 11 | `AGENTS.md` updated | KEEP | |

**~7 h out, all from the duplicated transport.**

## Lab 3 — Droplet and VPN (30 h, 11 items)

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Practice droplet: SSH keys, sudo user, `ufw` | KEEP | Their own droplet to break is the whole point. |
| 2 | WireGuard server on the practice droplet | KEEP | Each team builds a server from nothing. This is where server work is actually learned. |
| 3 | WireGuard client on the RPI | KEEP | |
| 4 | Peer stanza on the course droplet | KEEP | |
| 5 | nginx location for the team | KEEP | Their config. A broken proxy that they fix is the lab. |
| 6 | Flask under a path prefix | KEEP | |
| 7 | Camera through the proxy at the same fps | KEEP | The buffering lesson is worth the pain. |
| 8 | HTTPS with certbot (one team, others check) | KEEP | Already shared between teams, as written. |
| 9 | Status page app on the droplet | SKIP | Built again as the portal in Lab 4. Build it once, there. |
| 10 | Routing table exercise, `traceroute` ×3 | KEEP | Cheap, and it is the actual subject of the course. |
| 11 | 48-hour tunnel log, outside-the-lab test | KEEP | Passive; costs nothing but the wait. |

**~4 h out, from the duplicated status page.**

## Lab 4 — Shared database and workflow recorder (30 h, 12 items)

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Mosquitto on the droplet, per-team users and ACLs | RIG | One broker for four teams is one installation. Each team already built a server from nothing in Lab 3; doing it again on a box everyone shares only creates the chance for one team to break it for the other three. Teams still write every publisher, subscriber and ACL that is theirs. |
| 2 | InfluxDB org, bucket, tokens | RIG | Same reason, same boundary: the instance is given, everything written to it and read from it is theirs. |
| 3 | RPI publisher: cycle and sample topics | KEEP | |
| 4 | Droplet subscriber → InfluxDB | KEEP | |
| 5 | Workflow recorder on the RPI page | KEEP | The core of the lab and of Prototyping M2. |
| 6 | Recorder actions → tool-board interface | KEEP | |
| 7 | Cycle record assembly, curve slicing | KEEP | |
| 8 | Unified page: control + recorder + plot + camera + last 20 | KEEP | |
| 9 | Central portal on the droplet | KEEP | Now the only portal, having absorbed the Lab 3 status page. |
| 10 | Locking: Take control, view mode | KEEP | |
| 11 | ESP32 offline buffer in LittleFS | MOVE | To Lab 5, where fault tolerance is the subject. |
| 12 | UX test with another team, 100 replays | TRIM | 50 replays. The UX test stays. |

**~7 h out: shared infrastructure installed once, one feature moved to the lab it belongs in, half the replays.**

## Lab 5 — Fault tolerance, REST API, agent (34 h, 12 items)

The biggest workload in the semester and the one where their own trade is the subject. Nothing given.

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Baseline: single-process app under load | KEEP | You cannot argue for processes without it. |
| 2 | Split into `mg400d`, `toold`, web | KEEP | |
| 3 | Timeouts: 2 s socket, 500 ms UART | KEEP | |
| 4 | Heartbeats and a supervisor | KEEP | |
| 5 | Safe state on every fault | KEEP | |
| 6 | REST API blueprint under `/api/` | KEEP | |
| 7 | Pick retry through the DA classifier | KEEP | Where the two courses finally meet. |
| 8 | Time lock: enable remote API for N minutes | KEEP | |
| 9 | Audit log CSV | KEEP | |
| 10 | Portal nginx location for `/api/` | KEEP | Reuses their own Lab 3 config. |
| 11 | Agent demo: README → agent → one tag, first attempt | KEEP | The best single item in the whole plan. Protect its hours. |
| 12 | Fault log notebook, `AGENTS.md` rewritten | KEEP | |
| + | ESP32 offline buffer, arriving from Lab 4 | NEW | ~3 h, and it belongs here. |

---

# 3D Printing and CAD

Course hours: 34 / 30 / 28 / 30 / 24 = 146.
**Proposed: 30 / 34 / 28 / 30 / 24 = 146.** Part C moves from Lab 1 to Lab 2 and takes its hours with it.

## Lab 1 — Blender → printer → Fusion (34 h → 30 h, 19 items)

Nineteen items and five parts. The fullest document in the set even after the day-one fix.

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Day one: model, export, slice, start print; robot draws with a taped marker | KEEP | Already cut to fit three hours. The draw routine is given because the robot is a demo on day one, not a deliverable — nobody is graded on it. |
| 2 | Week after: fix mesh, print, mount, redraw | KEEP | |
| 3 | Mesh diagnostics write-up | KEEP | Cheap, and it is the Blender lesson. |
| 4 | B1 overhang test piece, 30/45/60/90° | KEEP | One print, four answers. |
| 5 | B2 straight vs. round tube | SKIP | Lowest value per hour in the course; the stepping is visible on the overhang piece anyway. |
| 6 | B3 tensile: 4 orientations × 3 coupons = 12 pulls | TRIM | 4 × 2 = 8 pulls. The inter-layer ratio is what Part E and Lab 2 need, and it survives two coupons. |
| 7 | B4 print-time integration notebook | KEEP | Slicing a mesh with a plane in numpy is a programming problem given to programmers. It is the one place in this course where they are the experts, and taking it away would be the worst trade in the plan. |
| 8 | Part C: measure the flange, rebuild the holder in Fusion | MOVE | The caliper table stays here; the Fusion rebuild goes to Lab 2, where Fusion is the subject. This is the cut that makes Lab 1 fit. |
| 9 | D1 measure the lifting nozzle and spring travel | KEEP | |
| 10 | D2 syringe holder in Fusion | REUSE | Last year's holder as the starting body: measure it, list what is wrong with it, change that. |
| 11 | D3 aim the LED cone | TRIM | One more constraint inside D2, not a separate deliverable. |
| 12 | D4 print, mount, lift test, one-handed swap | KEEP | Accepted on the robot, not on the screen. |
| 13 | E1 measure the syringe | KEEP | |
| 14 | E2 pressure and force table before CAD | KEEP | The calculation *is* the lesson: Boyle, plunger area, 70 N, section. |
| 15 | E3 clamp in Fusion | KEEP | If it is late, Data Acquisition measures with a hand on the plunger, exactly as their Lab 1 already says. The dependency has a fallback that costs nobody a grade, so no reference part is needed. |
| 16 | E4 print, load test, 30 cycles | KEEP | |
| 17 | E5 syringe cap with O-ring groove | REUSE | Start from last year's leaking samples. "Here is the part, here is why it failed" is the best brief in the whole course. |
| 18 | E6 tube joint, toothpick, thread glue, cure | KEEP | Cheap, and it is the trick that makes the rest hold air. |
| 19 | Repo | KEEP | |

**~4 h out from B2 and the tensile trim, ~4 h moved out with Part C.**

## Lab 2 — Work-area modules, tray and jig (30 h → 34 h, 14 items)

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 0 | *(incoming)* Fusion rebuild of the pen holder, from Lab 1 Part C | NEW | Arrives with its four hours. Fusion is this lab's tool anyway, and the before/after drawing comparison still works. |
| 1 | Measure the table: holes, pitch, thickness | KEEP | |
| 2 | Universal foot with spring fastener | REUSE | Last year's foot as the starting geometry if one exists. |
| 3 | Snap top standard, 20 insertion cycles | KEEP | |
| 4 | Tray set: 5 + 5 + 5 pockets, jig, post, cup holder, target | TRIM | First print 3 + 3 + 3 to prove the clearance, full set once `pocket_clear` is right. Saves two failed full-tray prints. |
| 5 | Gluing jig with the bezel reachable at 90° and 60° | KEEP | |
| 6 | Bolt compression coupons, plain vs. bolted | KEEP | The prestressed-concrete lesson that Lab 1 Part E already leans on. |
| 7 | FEA on the snap hook and both coupons | KEEP | |
| 8 | Registration test on two printers, 30-row caliper table | KEEP | The number three other courses quote. |
| 9 | 2D drawing with dimension table | KEEP | |
| 10 | Valve survey and port measurements | KEEP | |
| 11 | Port adapter in Fusion | KEEP | |
| 12 | Print adapter, make the tube joints, cure | KEEP | |
| 13 | Valve rig, leak test, 500 cycles | KEEP | |
| 14 | Repo | KEEP | |

## Lab 3 — Enclosures and print-pause (28 h, 12 items)

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Integration graph in draw.io | KEEP | The only place the whole cell is drawn. |
| 2 | BOM with per-item masses | KEEP | |
| 3 | Model every internal component as a placeholder body | KEEP | Measuring the eight things you have to fit *is* the enclosure lesson. Handing over a component library would remove the reason the housing ends up the right size. |
| 4 | Tool housing | KEEP | |
| 5 | LED shroud on the L1 boss | KEEP | |
| 6 | Station housing for RPI and screen | REUSE | Last year's RPI enclosure as the base if one exists. |
| 7 | Print-pause: embed nuts and magnets mid-print | KEEP | Cheap, memorable, a real production technique. |
| 8 | Print both, assemble, 20 dry cycles | KEEP | |
| 9 | Mass measurement under 250 g | KEEP | The arm-mounted constraint. |
| 10 | Camera frame showing tip and tray | KEEP | |
| 11 | Assembly guide with a photo per step | KEEP | |
| 12 | Repo | KEEP | |

## Lab 4 — Improving an existing design (30 h, 11 items)

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Pick the part and the metric on day one | KEEP | |
| 2 | Analyse the original | KEEP | |
| 3 | Define the test: fixture, load, failure criterion | KEEP | Defining the test before the redesign is the actual skill. |
| 4 | Approach 1, manual redesign | KEEP | |
| 5 | Approach 2, generative design | TRIM | Two approaches, not three. Generative costs cloud time and a learning curve for one comparison row. |
| 6 | FEA on all three versions | TRIM | Two versions. |
| 7 | Print-time integration on all three, three orientations each | TRIM | Two versions, two orientations: nine slices becomes four. |
| 8 | Print 3 versions × 3 pieces | TRIM | 2 × 3. |
| 9 | Test on the MG400, same fixture and points | KEEP | |
| 10 | Comparison table and conclusion | KEEP | |
| 11 | Repo | KEEP | |

**~8 h out.** Two approaches compared properly beat three compared badly. Retitle the lab if you take this.

## Lab 5 — ISO drawing and CNC order (24 h, 12 items)

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Decide the object and quantity on day one | KEEP | |
| 2 | Measure the AtomS3 shell and corner radius | KEEP | |
| 3 | Functional requirements as numbers | KEEP | |
| 4 | Parametric Fusion model | KEEP | |
| 5 | ISO drawing: views, section, tolerances, title block | KEEP | The subject of the lab. |
| 6 | Tolerance stack, worst case and RSS | KEEP | |
| 7 | Hand-cut test pieces from the sample sheet | KEEP | The cheapest reality check in the course. |
| 8 | Quotes from two shops | TRIM | One shop each; compare quotes across the four teams instead. Same lesson, a quarter of the e-mail. |
| 9 | Instructor review of drawing v1 | KEEP | |
| 10 | Validation plan written before the parts arrive | KEEP | |
| 11 | Run the validation on arrival (semester 2) | KEEP | |
| 12 | Repo | KEEP | |

---

# Prototyping (semester 2)

Mostly integration and writing, on a cell that already exists. Few cuts.

## Milestone 1 — Audit and specification (10 h, 10 items)

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Collect semester-1 evidence per subsystem | KEEP | |
| 2 | Cold-start every candidate subsystem | KEEP | Finds three months of rot in an afternoon. |
| 3 | Audit table: state, evidence, gaps, risks | KEEP | |
| 4 | Replay notebook on all four teams' data | KEEP | |
| 5 | Lay out the chosen parts and photograph | KEEP | |
| 6 | Define the minimum working cell | KEEP | The most valuable hour of the milestone. |
| 7 | Update the specification with measured baselines | KEEP | |
| 8 | Schedule M2–M5 as repository milestones | KEEP | |
| 9 | Spares list and the 17.02 order | KEEP | |
| 10 | Tag | KEEP | |

10 h for ten items is tight, but eight of them are writing about work already done.

## Milestone 2 — First tag from a recorded workflow (16 h, 10 items)

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Mount the parts, cold start, VL53L0X check | KEEP | |
| 2 | Record the assembly workflow | KEEP | |
| 3 | State machine in Flask, drawn in draw.io | KEEP | |
| 4 | Per-step logging: command, ack, event, arrival | KEEP | |
| 5 | Dry run, 10 cycles | KEEP | |
| 6 | Wet run on scrap polycarbonate, 5 cycles | KEEP | |
| 7 | The real tag, filmed end to end | KEEP | The moment the whole plan is for. |
| 8 | 100 cycles with recirculating dummies | TRIM | 50. The reliability argument holds. |
| 9 | Latency: 30 repetitions per link | TRIM | 15. |
| 10 | Notebooks, specification update, tag | KEEP | |
| + | Cure-time dataset, arriving from DA Lab 4 | NEW | ~2 h, and it belongs here, where the tag has to stick. |

## Milestone 3 — Model in the loop (18 h, 10 items)

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Copy model files with `MODEL.md` | KEEP | |
| 2 | Load models at start, expose sha256 in `/status` | KEEP | |
| 3 | Feature extraction on the RPI, matching the notebook | KEEP | The hard part, and the right hard part. |
| 4 | Close the loop in the state machine | KEEP | |
| 5 | Compensation on or off per `MODEL.md` | KEEP | |
| 6 | Drain test: full to empty, scale every 10 dispenses | KEEP | |
| 7 | Dose check: 10 weighed above 4 ml, 10 below 1.5 ml | KEEP | |
| 8 | Retry test: 50 picks, 25 set up to fail | KEEP | |
| 9 | Cross-team test: three other models on 30 curves | TRIM | Best-effort, as in DA Lab 5. Depends on other teams. |
| 10 | Notebooks, docs, tag | KEEP | |

## Milestone 4 — Enclosures and battery plugging (16 h, 10 items)

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Fit everything into the housings | KEEP | |
| 2 | Label every cable and tube, `connections.csv` | KEEP | Cheap, and it is what makes the cell maintainable. |
| 3 | Dry cycle and cable-pull cases in the housed cell | KEEP | |
| 4 | Battery insertion force by hand, 10 insertions | KEEP | |
| 5 | Design and print the battery fixture | KEEP | |
| 6 | 20 robot plugging attempts, go/no-go by 08.05 | KEEP | The go/no-go date is the safety valve. |
| 7 | User guide and maintenance guide drafts | KEEP | |
| 8 | UX test with another team | KEEP | |
| 9 | 100 cycles housed, temperature every 10 | TRIM | 50 cycles, temperature every 5. |
| 10 | Notebooks, specification, tag | KEEP | |

## Milestone 5 — Production run (14 h, 10 items)

| # | Item | Verdict | Note |
| :-- | :--- | :--- | :--- |
| 1 | Freeze the production workflow and recipe | KEEP | |
| 2 | Tag acceptance test and registry CSV | KEEP | |
| 3 | Rehearsal: 20 production cycles on dummies | KEEP | |
| 4 | Real run: 5 tags per team, numbered, registered | KEEP | What the summer camp actually uses. |
| 5 | 60 minutes unattended with the event log | KEEP | |
| 6 | Documentation package | KEEP | |
| 7 | Install test by someone who did not write the guide | KEEP | The best test in the entire plan. |
| 8 | `spec_vs_measured.md` | KEEP | |
| 9 | Demo script and rehearsal video | KEEP | |
| 10 | Hand-over and tag | KEEP | |

---

# What the instructor provides

Short, because almost nothing is provided. This is the whole list.

| What | Why it is not a shortcut |
| :--- | :--- |
| Base MG400 Python package with README and `AGENTS.md` (already in the plan) | The robot's driver, the same way `pyserial` is the port's driver. Everything above it is written by the teams, and its bugs are worth bonus points to whoever finds them. |
| A drawing routine in that package: 50 mm square and circle, pen-down Z as the argument | Day one only, and nobody is graded on it. It exists so the robot moves in the first three hours. |
| The JSON command and sample schema, already in `LAB_CONVENTIONS.md` | An interface between four teams and two courses. Implementing it is theirs. |
| One MQTT broker and one InfluxDB instance on the course droplet, with per-team credentials | Shared by definition. Each team already builds a server from nothing in Smart Solutions Lab 3. |
| Last year's leftovers, sorted and labelled on a shelf: holders, caps, feet, trays, enclosures, boards | Things that do not work well enough, handed over with the question "why not?". The opposite of an answer. |
| Spare parts, including one imaged SD card | For the component that dies at 21:00. A spare part is not a solution. |
| Consultations on the dates already in the plan, and the PCB pre-check on 05.11 | A look at their work, not a starting file. |

# Hours

Per team, if every TRIM, SKIP and MOVE above is taken.

| Course | As written | After cuts | Rebalanced |
| :--- | ---: | ---: | :--- |
| Data Acquisition | 142 h | ~119 h | 30 / 28 / 32 / 22 / 30 — eight hours moved into Lab 3 |
| Smart Solutions | 148 h | ~130 h | unchanged; the cuts land in L2, L3, L4 where they are needed |
| 3D Printing | 146 h | ~132 h | 30 / 34 / 28 / 30 / 24 — Part C moved into Lab 2 |
| Prototyping | 74 h | ~70 h | unchanged |

Every hour above comes from repetition, from a lesson taught twice, or from infrastructure that is shared by definition. Not one comes from making the work easier, and nothing a student would have had to figure out has been figured out for them.

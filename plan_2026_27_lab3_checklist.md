# Lab 3 checklist — all three subjects, 2026/27

Draft 02.10.26. To be ticked by Kaspar before the three `[Lab 3] EST.md` documents are written.

Sources: the EST Lab 1 and Lab 2 documents as they actually went out (`EST/2026-27/`), the learning outcomes in `plan_2026_27_opivaljundid_coverage.md`, and `plan_2026_27_ENG_v3.md`. The ENG Lab 3 drafts in `ENG/2026-27/` describe the old cell (syringe, resin, RPI) and are not used as a base.

How to use: tick what goes in, strike what does not, answer the decisions in section 0. Hours are my estimate per team.

---

## 0. Decisions first — these change all three documents

- [ ] **D1. Is there glue in Lab 3?** Labs 1–2 as written never touch a syringe: the sensor sits on the suction line, and the Data Acquisition story is "the vacuum holds". Everything below assumes **no glue, valve or UV in Lab 3** — the cell assembles the stack dry and learns to decide for itself. Glue then enters in Lab 4 or in Prototyping. If glue must start now, 3D L3 becomes the dispensing tool and the snap-fit / print-pause outcomes move to L4.
- [ ] **D2. The common demo.** Proposed: *the robot builds one full stack dry — battery module, Atom, glass — lifts only when the box says "the vacuum holds", sends a bad grip to scrap, and is started and watched from a phone outside the lab by the one person who holds the lock.*
- [ ] **D3. Is plugging the Atom onto the battery module in scope?** The robot stops at about 12 N. If the plug needs more, the stack is only placed, not mated. Needs one bench try before the text is written.
- [ ] **D4. Dates.** Lab 2 went out 06–07.10 with the order on 16.10. Same pattern for Lab 3 gives: out **27.10** (3D) and **28.10** (DA, SS), order **06.11**, first defence **17.11**, online. The plan says 23–24.10 and 03.11. Which?
- [ ] **D5. Hours.** Plan v3: 3D 28, DA 30, SS 30. Labs 1–2 ran at 30 / 32 / 28. Keep the plan's numbers?
- [ ] **D6. PCB scope and timing.** Review at the 17.11 defence, ordered the same day, boards arrive in December and are soldered in Lab 4. Does the board switch the pump box itself (so the box is smart without a laptop), or does the decision still go through the station and the MG400 DO line?
- [ ] **D7. Who orders what.** Teams build their own `docs/bom.md` again. But the comparator (LM393), the PCB order and the MQTT broker on the course droplet are yours. Confirm.
- [ ] **D8. Named tools in the outcomes.** Smart Solutions outcomes say WireGuard and nginx; Lab 2 let teams pick an SSH tunnel and Caddy. Leave it (concept covered), or make Lab 3 require the named ones?

---

## 1. 3D Printing and CAD — Lab 3

**Where the course stands against its nine outcomes**

| Outcome | After L1–L2 | Proposed home |
| :--- | :--- | :--- |
| 1 Blender, mesh problems | not required so far (software was free choice) | **gap — L3 small item or L4** |
| 2 Fusion, parametric, constraints | covered | — |
| 3 FDM physics: overhang, straight vs curved, orientation vs strength | only bend/break numbers and layer direction | L4 (with the improved part) |
| 4 Print time as a calculation, orientation | not covered | L4 |
| 5 Snap-fit, bolt–nut–washer compression | not covered | **L3** |
| 6 Print-pause, embedded metal | not covered | **L3** |
| 7 Improve one part by one metric, manual vs generative | not covered | L4 |
| 8–9 ISO drawing with GD&T, order, validate | not covered | L5 |

**Already promised to Lab 3 in the L1–L2 texts**
- The Gridfinity foot and clearance are the standard "the next modules sit on".
- "There are no cables in this lab, but there are in the next ones" — the cable space under the grid.
- The layout must show where the other workstations go, with room left for later modules.
- Atom and battery holders exist but were never run; the L2 test used glass only.
- The refit number says how much slop the next labs must tolerate.

**Proposed title:** *Labor 3 — Moodul: korpus, kinnitused ja kaablid*

**Items**
- [ ] **A. Integration graph** (draw.io): every part a node, every cable and tube an edge, which module each lives in, the cable path under the grid past the pipe and dowel beams. ~2 h
- [ ] **B. Electronics module as a Gridfinity holder**: Atom, sensor and op-amp board inside, tube and cable entries, strain relief as print, Atom screen and USB-C reachable. Board outline agreed with Data Acquisition by a fixed date; a cardboard dummy until then. ~8 h
- [ ] **C. Snap-fit lid**: a hook sized from the Lab 1 bend and break numbers, opened and closed 20 times, measured before and after. ~4 h
- [ ] **D. Print-pause**: magnets in the foot and captive nuts, a small test block first, pause height written down per feature. ~4 h
- [ ] **E. Bolt compression on the camera post**: a bolt through the segmented post from Lab 2, image shake measured again against the Lab 2 number. ~3 h
- [ ] **F. Full process, all three parts**: battery module, Atom, glass through input, workstation, output and scrap; four stacks; holders out and back. Closes what Lab 2 left untested. ~5 h
- [ ] **G. Assembly guide** that another team follows with a stopwatch, questions counted. ~2 h
- [ ] *Optional* — FEA on the hook before printing.
- [ ] *Optional* — mesh item for outcome 1: take a community STL (a Gridfinity bin or the Atom), try to change it, write down what breaks.
- [ ] *Deferred to L4* — overhang, straight vs curved, print-time calculation, mass budget on the arm.

**Concepts:** load path in a snap hook · elastic limit as a design number · friction is not a location · prestress (bolt carries tension, plastic only compression) · pause height and pocket clearance · strain relief · designing around a part that does not exist yet.

**Files the checklist would name:** `docs/integration.drawio`, `docs/snap_test.csv`, `docs/print_pause.md`, `docs/assembly_guide.md`, `docs/stack_test.csv`, `docs/bom.md`. Tag `3d-print-lab3`.

---

## 2. Data Acquisition — Lab 3

**Where the course stands against its ten outcomes**

| Outcome | After L1–L2 | Proposed home |
| :--- | :--- | :--- |
| 1 Signal path, analog and digital | covered | — |
| 2 ADC, error sources, effective resolution | Pa per step, before and after | L3 adds resolution after filtering |
| 3 Op-amp stage, simulated and measured | covered | — |
| 4 Choose by measured comparison: divider vs op-amp, analog vs digital filter, polling vs IRQ | op-amp vs raw only; divider only argued | **L3: analog vs digital filter, polling vs IRQ** |
| 5 Analog (RC, Schmitt) and digital (average, median, oversampling) filtering, Fourier | not covered | **L3** |
| 6 Interrupts, hardware timers, two cores | not covered | **L3** |
| 7 PCB in Fusion Electronics, Gerber, order | not covered | **L3** (review at the defence) |
| 8 Uncertainty, absolute accuracy, repeatability | three pressure points against calculation | L4, as dataset preparation |
| 9 Automated collection with the robot | not covered | L4 |
| 10 ML model | not covered | L5 |

**Already promised to Lab 3 in the L1–L2 texts**
- "The slope itself you do not compute in this lab; that is Lab 3's work."
- "The stage that the filter and the derivative are built on."
- "The same logic, moved onto the tool board."
- Lab 1 announced four spectra including a divider; Lab 2 delivered two. Lab 3 can close that with the filtered configurations.

**Proposed title:** *Labor 3 — Vaakum püsib: filter, tuletis, katkestus ja trükkplaat*

**Items**
- [ ] **A. Filter before derivative**, on the Lab 2 recordings: raw slope against filtered slope, and the spectrum that shows the derivative multiplying noise by 2πf. ~3 h
- [ ] **B. Three digital filters and one analog**: moving average, median, oversampling with decimation, and an RC on the stage output. Spectrum and delay for each, one chosen with numbers. ~4 h
- [ ] **C. The decision "the vacuum holds"**: leak rate in kPa/s after the pump stops, good grips against partial grips, threshold from the two distributions, time to decision, wrong accepts and wrong rejects counted. ~5 h
- [ ] **D. The fast event**: the cup comes off. Differentiator and Schmitt trigger in Falstad, then on the breadboard, into an interrupt; hysteresis set so ripple does not fire it. ~4 h
- [ ] **E. Polling against interrupt**, same protection built both ways: worst latency on the scope, behaviour when the loop is busy, time it took to get working. ~3 h
- [ ] **F. Hardware timer and two cores**: sampling and the decision on one core, screen and link on the other; 100 Hz jitter measured both ways. ~3 h
- [ ] **G. The board**: schematic, layout, DRC, Gerber in Fusion Electronics; outline that fits the 3D Lab 3 module; pre-check around 05.11; review at the defence. ~8 h
- [ ] *Optional* — the board switches the pump box itself (see D6).
- [ ] *Drop or defer* — VL53L0X and the long I2C cable. It was there to calibrate a syringe tip that this cell does not have. It is in the registered assignment text, not in the outcomes.
- [ ] *Deferred to L4* — uncertainty budget; soldering the board when it arrives.

**Concepts:** derivative as a noise amplifier · filter delay is the price of the filter · median removes a spike that an average smears · hysteresis · a decision has two kinds of error · interrupt latency against loop time · jitter · why a safety path does not wait for the station · a schematic is reviewed before it is ordered.

**Files the checklist would name:** `docs/filter_choice.md`, `docs/hold_decision.md`, `docs/latency.csv`, `docs/jitter.csv`, `pcb/` with schematic PDF, DRC report and Gerber, `docs/pump_control.md` updated, `docs/bom.md`. Tag `data-acquisition-lab3`.

---

## 3. Smart Solutions — Lab 3

**Where the course stands against its twelve outcomes**

| Outcome | After L1–L2 | Proposed home |
| :--- | :--- | :--- |
| 1 Station setup: static IP, SSH, interfaces | covered on laptop and droplet | — |
| 2 IPv4 routing, several subnets | address plan and NAT as an idea; no routing table work | **L3** |
| 3 MG400 API in Python, Flask page | covered | — |
| 4 ESP32 integration: UART, WiFi, HTTP, MQTT | all but MQTT | **L3** |
| 5 Droplet | covered in L2 | — |
| 6 VPN tunnel | covered in L2, tool was free choice | see D8 |
| 7 Reverse proxy, HTTPS | covered in L2 with a self-renewing proxy | see D8 |
| 8 User lock | only a written agreement | **L3** |
| 9 MQTT log with a database, historical dashboard | not covered | L4 |
| 10 Limits of cheap hardware under concurrency | not covered | L5 |
| 11 Fault scenarios, safe-state recovery | link loss done in L2 | L5 |
| 12 REST API and an agent | not covered | L5 |

Lab 2 already did what the plan had in Lab 3 (droplet, tunnel, HTTPS). What it skipped is the plan's Lab 2: the cell as one integrated system. That is what Lab 3 picks up.

**Already promised to Lab 3 in the L1–L2 texts**
- "The droplet and relay that the next layer is built on."
- The table camera image is something "the Smart Solutions lab has to measure from"; the image-to-table relation is "taught once".
- The tool camera exists so the robot "sees what it lifts".
- Positions are known as cell name plus offset.
- How do you tell from a distance that the robot has left its nest — asked in L2, not yet built.

**Proposed title:** *Labor 3 — Rakk kui üks süsteem: töövoog, pilt ja lukk*

**Items**
- [ ] **A. Three networks, one routing table**: robot Ethernet, WiFi, tunnel. Read the table, predict each route, trace three destinations, break one on purpose. ~4 h
- [ ] **B. The process as data**: the stack assembly as a list of steps with cell names and offsets from `layout.md`, replayable, with a scrap branch. ~7 h
- [ ] **C. The camera as an instrument**: table camera pixel to cell, taught once; which input pockets are full; tool camera says whether the cup is centred. A written, deterministic check, not a trained model. ~8 h
- [ ] **D. The station obeys the box**: lift only on "holds", stop on the alarm from Data Acquisition; time from alarm to robot stopped. ~3 h
- [ ] **E. MQTT as the second transport**: broker on the droplet, Atom and station publish state and events, latency against the HTTP path. Prepares the Lab 4 database. ~5 h
- [ ] **F. The lock**: one session owns the robot, the rest watch; it expires. Replaces the paper agreement from Lab 2. ~3 h
- [ ] *Optional* — the page shows when the robot is out of its nest.
- [ ] *Optional* — rebuild the tunnel with WireGuard and the proxy with nginx, if D8 says so.
- [ ] *Deferred to L4* — database, historical dashboard, workflow recorder. *To L5* — processes, supervisor, REST API, agent.

**Concepts:** a routing table is a decision per packet · NAT seen, not described · a process is data, not code · a camera needs calibration before it measures · publish/subscribe against request/response · shared state and who owns it · a check you can state in words before you run it.

**Files the checklist would name:** `docs/routing.md`, `data/workflow.json`, `docs/camera_check.md`, `docs/latency.csv`, `docs/lock.md`, `docs/atom_page.md` updated, `docs/bom.md`. Tag `smart-solutions-lab3`.

---

## 4. Handovers between the three (one team, three documents)

- [ ] Board outline and connector side: Data Acquisition → 3D, by a fixed date about ten days in.
- [ ] The "holds" and "alarm" lines and their format: Data Acquisition → Smart Solutions, agreed in week one.
- [ ] Cell name plus offset for every position: 3D → Smart Solutions workflow.
- [ ] Scrap bin exists and is reachable: 3D → Smart Solutions scrap branch.
- [ ] Anything that joins the Atom gets its settings and test button on the Atom page.

## 5. Document form (same as Lab 2 unless you say otherwise)

- [ ] Sections as in the EST Lab 2 files: Kuidas see dokument töötab · Eesmärk · Kontrollnimekiri · Sisendid · Vahendid · Taustainfo · Osad · Ohutus · Komponendid selle labori jaoks · Hindamiskriteeriumid · Kaitsmine · Arenduspäevik · Väljundid ja tulemused · Tagasiside.
- [ ] A one-page `[Labor 3 kokkuvõte]` per subject.
- [ ] No ready shopping list, only hints in sentences; order file is `docs/bom.md`.
- [ ] No code: JSON lines, formulas and short pseudocode only.
- [ ] Taustainfo: one quick practical video per concept. I will put a title and a search phrase where I do not have a real link, for you to replace.
- [ ] Smart Solutions has no `[Labor 2 kokkuvõte]` yet. Write it in the same pass?

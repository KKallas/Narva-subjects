# Lab document conventions 2026/27 (shared by all four courses)

Source of truth for content: `plan_2026_27_ENG_v2.md` (root of repo). Rationale and per-lab Keep/Change/New lists: `plan_2026_27_tag_assembly_change_plan.md` section 3. Do not contradict either. Where the plan is silent, decide concretely and consistently with these conventions.

## Files

Folder: `ENG/2026-27/<Course>/`. File names:
* `Data Acquisition [Lab 1] ENG.md` … `[Lab 3]`, `Data Acquisition [Lab 4] ENG.md`, `[Lab 5]`
* `Smart Solutions [Lab 1] ENG.md` … `[Lab 3]`, `[Lab 4]`, `[Lab 5]`
* `3D Printing [Lab 1] ENG.md` … `[Lab 3]`, `[Lab 4]`, `[Lab 5]`
* `Prototyping [Milestone 1] ENG.md` … `[Milestone 5]`

## The document is the team's report

Every lab document is handed out **partially filled**. The instructor fills what is known — dates, interfaces, acceptance items, safety, the questions worth answering — and marks it **GIVEN**. Everything the team has to find out is marked **TO BE CHARTED** and left blank, including things the instructor does not know the answer to.

The team copies the document into their repository as the lab folder's `README.md` on the first day and fills it in as the work happens. It is the deliverable, not a companion to it: at the tag it is read exactly as it stands, and a blank left blank is graded as an answer. Nothing is ever deleted from it — a wrong number stays, dated, with the correction written under it.

The writing rule, which applies to every filled-in block: **it must need no translation**. Real file names, real numbers, units on everything, the reason standing next to the choice. The Development Log in particular is a diary written to yourself, in the language the team works in, but understandable by a person who was not in the room — dated entries, added and never edited, numbers instead of adjectives.

The `How this document works` block and the eight `TO BE CHARTED` blocks below are verbatim in every document (only "lab" becomes "milestone" in Prototyping). Do not paraphrase them per course.

## Document template (in this order)

```
## <Course>: Lab N — <Title from the plan>

**Workload:** NN hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** DD.MM.YY | **Order date:** DD.MM.YY | **Defense:** DD.MM.YY

### How this document works
The verbatim block (GIVEN vs. TO BE CHARTED, copy into the repo on day one, nothing deleted, no translation needed). Identical in every document.

### Objective
2–4 paragraphs. What is built, why, how it fits the cell. End with the italic living-document sentence (verbatim below), then the TO BE CHARTED objective block.

### Interfaces
Two short lists: **Takes from** (which other lab/course output this lab needs) and **Gives to** (which lab/course consumes this lab's output). Use the "What each course produces for the others" table in the plan.

### Background Information
Bulleted links with one-line explanations. Only use URLs you are sure exist (manufacturer datasheet pages, docs.m5stack.com, randomnerdtutorials.com, falstad.com, scipy/sklearn/flask/influxdata/wireguard/nginx official docs, Fusion 360 / Blender / PrusaSlicer official docs). If unsure of a URL, give the resource name and a search phrase instead of a URL. End with the italic sources sentence (verbatim below).

### Tools
Numbered list of hardware and software. End with the italic tools sentence (verbatim below).

### Project Breakdown
Checklist (`- [ ]`) of 6–12 concrete steps in order. End with the italic breakdown sentence (verbatim below).

### Simulation   (only where the plan has simulation: Falstad, Fusion FEA, generative design, network diagrams; otherwise omit)

### Analysis
Jupyter Lab / measurement tasks, numbered, with the exact quantities from the plan (30 measurements × 3 levels, 4 × 30, 500 cycles, etc.). Say what the notebook must show.

### Testing
Two or three "Test Example N" subsections in the style of the old labs, then the italic testing sentence (verbatim below).

### Acceptance
Bulleted list of physical or measured items that must exist in the repo at the tag. These are the things an agent cannot produce: CSV of a stated shape, caliper table, scale readings, oscilloscope screenshot, video of the robot doing X, a measured number.

### Data produced
What goes into the shared database or repo data folder, with the schema below where relevant. For labs before Smart Solutions L4 say "repo only".

### Safety   (only where relevant: robot motion, pneumatics, UV LED, resin, soldering, mains)

### Components for the next lab
Table: Item | Qty per team | Note. Quantities from the ordering calendar in the plan. This section is the order list for the next meeting; the order goes out on the next lab's order date.

### Assessment criteria
| Category | Points |
| :--- | :--- |
| Working files — <what> | 5 p |
| Analysis — <what> | 5 p |
| Prototype — <what> | 5 p |
| Documentation — <what> | 5 p |
| **Total** | **20 p** |

### Required for the defense
"**Only a link to the git repository, tagged `<course>-<labN>` 72 h before the defense.**" then a bulleted list of what the tagged repo must contain (folder per the repo template in the plan: src/, data/, notebooks/, docs/, pcb/, fusion/, stl/, models/ as relevant). Mention the one live change at the defense.

### Development Log
The TO BE CHARTED diary block with the dated-entry skeleton.

### Results
The TO BE CHARTED end-of-lab block: repository and tag, the three or four numbers with units, what we would do differently, what the next lab should know.

### Feedback
```

Every section that the team fills ends with its **TO BE CHARTED** block, verbatim from an existing document: Objective (the objective as it turned out), Background (your sources), Tools (what you actually used), Project Breakdown (dates and your own steps), Analysis (the answers), Testing (your tests and your failures), Acceptance (where each item is), Development Log (the diary), Results (end of lab). The italic sentences below stay where they are; the TO BE CHARTED block goes after them.

Verbatim italic sentences (copy exactly):
* Objective: *This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*
* Background: *Add your own sources and useful information here that would help you understand the project years later when you reopen it.*
* Tools: *If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*
* Breakdown: *How far along are you? When will you be done? How could you go faster? — the usual questions*
* Testing: *These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

## Fixed facts (use exactly)

Teams: 12 students, 4 teams of 3, one MG400 per team, one spare robot.
Grading: 5 labs × 20 p (5/5/5/5), integration 70 p, grade from best 100. Peer review in MS Teams chat, max 4 bonus p per defense. Tag 72 h before the defense, which is the Saturday before it. 5 min presentation + 10 min questions including one live change, on the call.
Repo: created and owned by the team; instructor has read access; `AGENTS.md` at the root.
Tag names: `data-acquisition-lab1|lab2|lab3|lab4|lab5`, `smart-solutions-…`, `3d-print-…`, `prototyping-milestone1…5`.

Contact sessions (lab handed out; never a defence):
* Data Acquisition and Smart Solutions, Saturdays: 12.09.26 (L1 out), 03.10.26 (L2 out), 24.10.26 (L3 out), 14.11.26 (L4 out), 05.12.26 (L5 out), 16.01.27.
* 3D Printing, Fridays: 11.09.26, 02.10.26, 23.10.26, 13.11.26, 04.12.26, 16.01.27 (same pattern, one day earlier).

Defences are **online, on the Tuesday after the week of the contact session**, and are the same day for all three subjects: L1 06.10.26, L2 27.10.26, L3 17.11.26 (with the PCB review; PCBs ordered that day), L4 08.12.26, L5 19.01.27. The tag is due 72 h before, which is always the Saturday of the contact-session weekend. Write the defence date in the metadata line as `DD.MM.YY, online`.
* Prototyping: M1 out 16.01.27 (semester-2 list), M1 def 27.02.27 (M2 out), M2 def 20.03.27 (M3 out), M3 def 17.04.27 (M4+M5 out), M4 and M5 def 29.05.27.
Order dates (10 days before the meeting): 22.09.26, 13.10.26, 03.11.26, 24.11.26, 06.01.27; PCB order 14.11.26. Semester 2: 17.02.27, 10.03.27, 07.04.27, 19.05.27.
Optional consultations: Data Acquisition ~12.09 breadboard + multimeter, ~24.09 agents (Claude Code, Codex, Hermes), ~15.10 op-amp, ~05.11 resolution + PCB pre-check. Smart Solutions ~15.10 IPv4 routing, ~05.11 WireGuard, ~25.11 nginx.

Workload hours: DA 34/30/24/24/30. SS 28/26/30/30/34. 3D 34/30/28/30/24. Prototyping 10/16/18/16/14.

Hardware:
* MG400 with Dobot mini vacuum pump box: −70 … +110 kPa, 24 V DC, controlled by I/O, 4 mm tube. Suction cups φ4/8/13/16 mm; use φ13 or φ16 on the 24×24 mm glass.
* Sensors: **one pressure sensor per cell, on the syringe branch only** — MPX5100DP (0–100 kPa differential, 0.2–4.7 V). MPX5700AP (15–700 kPa abs) is on the shelf and used on day one of Lab 1 as the wrong-range example. The suction cup is not instrumented; pick success is read from the nozzle camera. VL53L0X I2C distance sensor. LM358N op-amp, LM393 comparator.
* Valve: 3/2 direct-acting, spring return, vacuum-rated, 24 V (or 12 V). Common ← pump line; NO (unpowered) → suction cup; NC (energized) → syringe. Unpowered = cup = safe.
* UV: transparent 405 nm resin (SLA printer resin). 405 nm LED 1–3 W on a star heatsink, constant-current driver, shroud, mounted ≥30 mm from the tip, aimed so the cone misses the tip. Never 365 nm (polycarbonate blocks it). Amber syringes 5/10 ml, blunt tips 0.6/0.8/1.2 mm, tip caps. Goggles rated for 405 nm, nitrile gloves, IPA.
* Tag: M5 AtomS3 (24×24×13 mm, 0.85" IPS; EOL, AtomS3R is the replacement), ATOM TailBat (190 mAh) or Atomic Battery Base, polycarbonate glass ≈ 24×24 mm.
* Control station: Raspberry Pi 4 + screen, LAN to MG400 (ports 29999 dashboard, 30003 motion), USB to the tool board, WiFi to the camera.
* Camera: M5 AtomS3R-CAM or AI-Thinker ESP32-CAM, MJPEG over WiFi.
* ESP32: M5 Atom Lite (ESP32-A on the breadboard for Data Acquisition, ESP32-B on the RPI for Smart Solutions). Tool PCB replaces both from December.
* Base MG400 Python package: provided by the instructor, installed with pip from a tagged git URL. CLI: connect, enable, clear error, jog, MovJ/MovL, read position, DO on/off, stop. Bugs are fixed by pull request (bonus points when merged).

## Tool-board interface (defined in Smart Solutions L2, implemented on the PCB in Data Acquisition L3, used by Data Acquisition L4)

UART 115200 8N1 over USB, one JSON object per line, both directions.

Tool board → RPI, one sample per 10 ms (100 Hz):
```
{"t":123456,"p":45.2,"valve":0,"pump":"off","uv":0,"z":112,"alarm":0}
```
`t` ms since boot; `p` kPa on the syringe branch, the cell's only pressure sensor (there is none on the cup); `valve` 0 = cup, 1 = syringe; `pump` "off" | "suction" | "blow"; `uv` 0/1; `z` mm from VL53L0X or null; `alarm` 1 when the dP/dt interrupt has fired (latched until `clear`).

RPI → tool board:
```
{"cmd":"valve","on":1}
{"cmd":"pump","mode":"blow"}            // "off" | "suction" | "blow"
{"cmd":"dispense","ms":200}             // valve to syringe for ms, then back to cup; requires pump "blow"
{"cmd":"uv","ms":5000,"pose_ok":1}      // refused unless pose_ok=1; LED times out on the board regardless
{"cmd":"stop"}                          // valve off, pump off, uv off
{"cmd":"clear"}                         // clears alarm latch
{"cmd":"status"}
```
Reply to every command: `{"ack":"<cmd>","ok":1}` or `{"ack":"<cmd>","ok":0,"err":"<reason>"}`. Events: `{"ev":"dispense_start","t":…}`, `{"ev":"dispense_end","t":…}`, `{"ev":"alarm","t":…,"dpdt":…}`. The RPI slices curves out of the sample stream using event timestamps.

## Cycle record (defined in Smart Solutions L4, written by Data Acquisition L4, read by Data Acquisition L5 and Prototyping)

CSV columns (one row per cycle) in `data/cycles.csv`; curves in `data/curves/<cycle_id>.csv` (columns t_ms, p_kpa); images in `data/images/<cycle_id>.jpg`:

```
cycle_id, team, timestamp_utc, workflow_id, robot_speed_pct, pump_setpoint_kpa, dispense_ms, cure_s, tip_mm,
syringe_ml_nominal, fill_ml_estimate, fill_method (scale|count), dose_mg (if weighed, else empty),
pick_ok (0|1|empty, from the camera check), dispense_ok (0|1), clog_alarm (0|1), z_mm, response_ms, dpdt_max, plateau_kpa, auc,
image_file, notes
```
InfluxDB: measurement `cycle` with tags `team`, `robot`, `workflow_id` and the scalar columns as fields; measurement `sample` with tag `cycle_id` and fields `p_kpa`, `valve`, `uv` at 100 Hz. Same bucket for all four teams.

## Style

* Match the tone of the existing docs (`ENG/Data Acquisition/Data Acquisition [Lab 3] ENG.md`, `ENG/Prototyping/Prototyping [Milestone 4] ENG.md`): direct, concrete, numbers not adjectives.
* Each document 150–300 lines.
* **No code samples.** No Arduino/C++ sketches, no Python scripts, nothing that pretends to be runnable. Allowed: the JSON interface lines above, one-line formulas, short config fragments where the lab is about configuration (an nginx location, a WireGuard peer stanza), and language-neutral logic pseudocode of 3–8 lines when a procedure must be stated ("every 10 ms: read ADC → convert → ring buffer → if dP/dt > threshold → release valve, latch alarm"). No pin numbers, no library calls, no register names. Invented code has been a problem in earlier documents; the student's agent writes the code, the document states the logic and the acceptance.
* Physics-locked acceptance items: say the number, the file, the measurement.
* State the "found another use" principle wherever the fill-level hypothesis appears: a null result is graded the same as a positive one.
* Do not invent part numbers beyond those listed; where a generic part is fine say so (e.g. "any logic-level N-MOSFET, e.g. IRLZ44N").

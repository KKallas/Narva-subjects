## Prototyping: Milestone 1 — System audit and specification update

**Workload:** 10 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 16.01.27 | **Order date:** 17.02.27 | **Defense:** 27.02.27

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the milestone folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

Semester 1 produced parts: a tool board with two sensors, a dP/dt alarm and a Z calibration (Data Acquisition), a control station with a workflow recorder, a shared database and a REST API (Smart Solutions), and the syringe/LED holder, tray, jig, enclosures and the glass batch (3D Print). Four teams built four of each. None of them is yet a cell that assembles a tag from one web command. Milestone 1 decides, with evidence, which parts become the cell, what is missing, and what the cell must do by 29.05.27.

The audit covers every subsystem: tool board, sensors and alarm, VL53L0X calibration, fill-level model and pick classifier, control station and base package, tool-board interface and camera, VPN and portal, workflow recorder and database, REST API and fault tolerance, syringe/LED holder, tray and jig set, both enclosures, the improved part from 3D Print L4, and the glass batch from 3D Print L5. For each: state, gaps, risks, and one measured number that proves the state. Parts can be mixed across teams: your tool board with another team's tray and a third team's model is a normal outcome. The choice is made on numbers from the semester-1 data (registration error, interrupt latency, model MAE, mass on the arm), not on ownership. The L5 outcome on fill level is taken as it is: if a team's model showed H0 (no compensation needed within ±10 % dose), that is a result and the sensor's job in the cell is clog detection and pick verification. A null result is graded the same as a positive one.

The milestone ends with an updated specification (the M1 document from spring 2026 is the format reference: numbered, testable requirements; performance targets with a measurement method), a definition of the **minimum working cell** that shows the model in the loop, a schedule for M2–M5 with names on the tasks, and the spares order for 17.02.27. **Full-project alternative:** the same content as M1–M5, defended at once on 29.05.27 in the folder `prototyping/full-project/`, tagged `prototyping-full-project`. It requires a physically working cell at the defense; a plan is not accepted. A team choosing the full project still hands in the M1 audit and specification by 27.02.27, because the order list comes from it.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* Data Acquisition L3 (tool PCB, dP/dt safety, VL53L0X calibration), L4 (500+ cycle dataset with ground truth), L5 (fill-level model or its null result, pick classifier).
* Smart Solutions L1 (station on the base package), L2 (tool-board interface, camera), L3 (VPN, proxy), L4 (shared database, record schema, workflow recorder), L5 (REST API, fault tolerance).
* 3D Print L1 (syringe + LED holder), L2 (tray, jig, VL53L0X post, registration numbers), L3 (enclosures, camera and LED mounts), L4 (improved part), L5 (glass batch drawing and parts).

**Gives to**
* Milestone 2: the list of chosen parts, the updated specification, the minimum-cell definition, the spares on the shelf.
* All four teams: the schema consistency report (which team's `cycles.csv` deviates and how), needed before any cross-team model run in M3.

### Background Information

* M5Stack AtomS3 documentation — dimensions, screen, header pinout of the tag: https://docs.m5stack.com/en/core/AtomS3
* M5Stack AtomS3R documentation — the replacement for the EOL AtomS3, same footprint: https://docs.m5stack.com/en/core/AtomS3R
* Dobot MG400 product page — work envelope and payload for the reach check of the chosen tray layout: https://www.dobot-robots.com/products/desktop-four-axis/mg400.html
* scikit-learn model persistence — how a pickle/joblib file is loaded and why the library version must match: https://scikit-learn.org/stable/model_persistence.html
* pandas CSV validation — resource name, search phrase "pandas read_csv dtype validation assert columns".
* Writing a requirements specification with MoSCoW priorities — search phrase "MoSCoW prioritization testable requirements example".

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. One MG400 per team with pump box and suction kit, the polycarbonate worktable section.
2. All four teams' semester-1 hardware on the table for the audit day (27.02.27 is the audit session; the parts are compared side by side).
3. Calipers, 0.01 g scale, oscilloscope, contact thermometer, kitchen scale for the arm mass.
4. RPI control station (Smart Solutions) with the base MG400 package and the team's Flask app.
5. Jupyter Lab, pandas, scipy, scikit-learn (same version as the L5 pickle).
6. Git repository, folder `prototyping/milestone1/` with `docs/`, `notebooks/`, `data/`.
7. draw.io for the cell block diagram; GitHub/GitLab milestones for the schedule.

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Collect the semester-1 evidence per subsystem: file paths of caliper tables, scope screenshots, `cycles.csv`, model files, cable-pull logs, mass measurements. No evidence file, no "works" state.
- [ ] Power up each candidate subsystem once (cold-start test below) and record the result.
- [ ] Fill the audit table: one row per subsystem, columns State | Evidence | Gaps | Risks | Team chosen | Why (a number).
- [ ] Run the replay notebook on all four teams' `data/cycles.csv`, `data/curves/`, `data/images/` and the model files; fix or report every schema deviation.
- [ ] Choose the parts for the cell and lay them out on the table; photograph them with the team labels visible.
- [ ] Define the minimum working cell: which parts, which workflow, which model, what it must show at the M3 defense.
- [ ] Update the specification: requirements, performance targets with a "measured baseline (semester 1)" column, interfaces, test plan mapped to M2–M5 analyses.
- [ ] Write the schedule: M2–M5 as repository milestones with tasks, owners and hours (16/18/16/14 h per student).
- [ ] Derive the spares list from the consumables notebook and write `docs/order_17-02-27.md`.
- [ ] Tag `prototyping-milestone1` by 24.02.27.

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

### Analysis

1. **Replay of the semester-1 datasets** (`notebooks/audit_replay.ipynb`). Load `data/cycles.csv` from all four teams. Check per team: the column list equals the 26 columns of the cycle record (see Data produced); dtypes; `dispense_ms`, `cure_s`, `tip_mm`, `pump_setpoint_kpa` within the ranges of the recipe; number of rows (≥ 500 expected); `pick_ok` class balance; `fill_method` values only `scale` or `count`; every `cycle_id` has a curve file and an image file. For the curves: median Δt = 10 ms, fraction of gaps > 15 ms, length in samples. Load the chosen fill model and pick classifier; predict on 20 curves from each team; report four MAE values (ml) and four accuracies. The notebook must show one table team × check → pass/fail and a list of fixes needed before M2. It must run on all four data folders without edits.
2. **Measured baseline for the specification** (`notebooks/baseline.ipynb`). From the semester-1 data compute the numbers that go into the "measured baseline" column: mean dose and its CV at the recipe (from rows with `dose_mg`), pick success rate (mean `pick_ok`), clog-alarm rate, median `response_ms`, registration error of the chosen tray (3D Print L2 caliper table, both prints), interrupt latency (Data Acquisition L3 scope value), camera and USB latency (Smart Solutions L2 table), recovery time per cable-pull case (Smart Solutions L5), arm-mounted mass (3D Print L3). Every row: parameter, value, unit, source file, team. Parameters without a semester-1 number are marked "not measured" and get a test in M2.
3. **Consumables per 100 cycles** (`notebooks/consumables.ipynb`). From `dose_mg` and cycle counts: resin per cycle and per 100 cycles (g), tip changes per 100 cycles (from `clog_alarm` and `notes`), syringes per 100 cycles. Multiply by the planned cycles M2–M5 (100 + about 300 for the drain test and retry test + 100 in housing + the production run). Output: the quantities in the Components table below, with the calculation visible.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: Cold start of the chosen station

Everything off. Power on the RPI, the tool board and the MG400 in that order. Measure with a stopwatch the time until the web page shows the sensor stream at 100 Hz and the robot position, and one jog from the page moves the robot. Record the time and every manual step that was needed (a service restart, a cable reseat). Each manual step is a gap in the audit table.

#### Test Example 2: Schema replay without edits

Point the replay notebook at each team's `data/` folder in turn. It must fail loudly (an assertion with the column name) on a missing or renamed column, and pass on the chosen team's data. Keep the four outputs in the notebook.

#### Test Example 3: Safe state re-check

With the chosen tool board running and the pump in suction, pull the USB cable. The vacuum sensor value `v` on the cup branch must show the line went to the cup (valve unpowered) and the UV LED must be off. Photograph the meter or the last streamed sample. A board that fails this does not go into the cell, whatever its other numbers.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* `docs/audit.md`: the audit table with at least 14 rows (one per subsystem listed in the Objective), each with an evidence file path and one measured number.
* `docs/minimum_cell.md`: the list of chosen parts with the owning team, and a photo of the parts laid out on the worktable with team labels visible.
* `docs/specification.md`: at least 10 numbered requirements with MUST/SHOULD/COULD, a performance-target table with the columns Parameter | Target | Minimum acceptable | Measured baseline (semester 1) | Measurement method | Milestone where measured.
* `notebooks/audit_replay.ipynb` with outputs: the team × check table for all four teams, four MAE values, four accuracies.
* `notebooks/baseline.ipynb` and `notebooks/consumables.ipynb` with outputs.
* Cold-start time and the list of manual steps in `docs/audit.md`; a photo of the safe-state check.
* Repository milestones M2–M5 with tasks, owners and hours; `docs/schedule.md` with the same in one page.
* `docs/order_17-02-27.md`: the spares list with quantities derived in the consumables notebook.

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Repo only. Nothing new goes into the shared database in this milestone. The replay notebook reads the cycle record as defined in Smart Solutions L4:

```
cycle_id, team, timestamp_utc, workflow_id, robot_speed_pct, pump_setpoint_kpa, dispense_ms, cure_s, tip_mm,
syringe_ml_nominal, fill_ml_estimate, fill_method (scale|count), dose_mg (if weighed, else empty),
pick_ok (0|1|empty), dispense_ok (0|1), clog_alarm (0|1), z_mm, response_ms, dpdt_max, plateau_kpa, auc,
image_file, notes
```

Curves in `data/curves/<cycle_id>.csv` (t_ms, p_kpa), images in `data/images/<cycle_id>.jpg`. If a team's data deviates, the deviation and the converter that fixes it are described in `docs/audit.md`; the schema itself is not changed.

### Components for the next milestone

Spares from the audit; quantities are the consumables notebook's result, the numbers below are the default if the notebook gives less.

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| Blunt tips, the recipe size (0.8 or 1.2 mm) | 10 | Plus 5 of the other size |
| Tip caps | 10 | Resin cures in daylight; an open tip is a clog |
| Amber syringes 5 ml and 10 ml | 3 + 3 | 5 ml for the M3 drain test |
| 405 nm resin | 250 g | Shared bottle if the notebook shows less than 100 g per team |
| 3/2 valve, direct-acting, spring return, vacuum-rated, 24 V (or 12 V) | 1 | Spare; same type as on the tool board |
| 405 nm LED 1–3 W on star heatsink | 1 | Spare; same power class as the recipe was measured with |
| Polycarbonate glasses | 10 | From the 3D Print L5 batch, no order; validated on arrival per L5 |
| Nitrile gloves, IPA | 1 box, 500 ml | Shared |
| Anything the audit listed as missing | as listed | With the evidence row that found it |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — audit table with evidence paths, chosen-parts list, schedule as repository milestones | 5 p |
| Analysis — replay notebook passing on all four teams' data, baseline table, consumables calculation | 5 p |
| Prototype — the chosen parts physically on one table, cold-start test done, safe-state check photographed | 5 p |
| Documentation — specification with testable targets and a baseline column, minimum-cell definition, order list | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `prototyping-milestone1` 72 h before the defense.**

* `prototyping/milestone1/docs/`: `audit.md`, `minimum_cell.md` with the photo, `specification.md`, `schedule.md`, `order_17-02-27.md`, the draw.io block diagram of the cell.
* `prototyping/milestone1/notebooks/`: the three notebooks with outputs (Run All before committing).
* `prototyping/milestone1/data/`: the four teams' `cycles.csv` (or a README with the exact path and tag in each team's repository) and the model files used, with their sha256 in `docs/audit.md`.
* Repository milestones M2–M5 visible to the instructor.
* Live change at the defense: the instructor changes one number in the performance-target table (for example tags per hour, or the pick success minimum); the team shows on the spot which requirements, which M2–M5 tests and which order quantities change, and edits the specification in the repository during the session.

### Development Log

**TO BE CHARTED — a diary.** One entry per working session, written to yourself, in the language your team works in, and written so that a person who was not there understands it without having to ask. Date first, then who was there, what you tried, what actually happened in numbers, what you decided and why, and what is left open for next time. Entries are added, never edited: if the entry of 18.09 turned out wrong, the entry of 25.09 says so and the old one stays as it was.

Adjectives are not results. "The sensor was noisy" is nothing; "±14 LSB at rest, ±40 LSB with the pump box running" is an entry. Two or three honest sentences per session are enough — but the session with the mistake in it deserves five.

**DD.MM.YY — who was there**
* Did:
* Happened (numbers):
* Decided, and why:
* Open for next time:

### Results

**TO BE CHARTED, at the end.**

* Git repository and tag:
* The three or four numbers this milestone produced, with units:
* What we would do differently if we started again on day one:
* What the next milestone should know before it starts:

### Feedback

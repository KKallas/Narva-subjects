## Prototyping: Milestone 2 — Integration prototype: first tag from a recorded workflow

**Workload:** 16 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 27.02.27 | **Order date:** 10.03.27 | **Defense:** 20.03.27

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the milestone folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

The parts chosen in Milestone 1 become one cell. The result of this milestone is one physical tag: an AtomS3 with a polycarbonate glass glued over the screen by the robot, from one command on the web page, through a workflow recorded with the Smart Solutions L4 recorder: web command → MG400 → dispense → pick → place → cure → image → record. Nothing is typed into a terminal during the cycle. The tag is shown at the defense.

The second result is the list of integration problems and how each was solved. Semester 1 tested every subsystem alone; together they fail in three ways. **Timing**: the dispense starts before the robot has arrived, the cure starts before the glass is released, the image is taken while the arm is still moving. **Latency**: a web click reaches the tool board 50–300 ms later depending on the path (Smart Solutions L2 table), the camera frame lags the sensor stream, the position poll is slower than the motion. **States**: the tool board raises an alarm mid-dispense, the MG400 reports an error, the camera does not answer, a pick fails; the cycle must end in a defined state with a record written, never hang. The cycle is written as a state machine with a timeout on every wait and a SAFE state reachable from every other state.

The third result is the first 100 cycles of the integrated cell with a record per cycle in the shared database. Real tags are scarce (the 24.11 order was AtomS3 or AtomS3R ×10 for all teams), so the 100 cycles use the Data Acquisition L4 method: dispense into the waste cup and pick/place of the five dummy glasses recirculating between source and finished slots; at least 10 of the 100 cycles are wet (resin on a scrap polycarbonate square in the jig, glass glued and cured); at least 1 is the real tag. Cycle time and failure-mode statistics from these 100 cycles are the first measured values against the Milestone 1 targets.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* Milestone 1: chosen parts, specification with targets, minimum-cell definition, spares.
* Data Acquisition L3 / L4: tool board with the JSON interface, the record-writing script.
* Smart Solutions L4 (workflow recorder, shared database), L5 (REST API, safe state, fault handling).
* 3D Print L1 (syringe + LED holder), L2 (tray, jig, VL53L0X post, waste cup), L5 (glass batch).

**Gives to**
* Milestone 3: the running cell, the state machine with its timeouts, the 100-cycle dataset, the workflow JSON.
* Milestone 4: the cell to be housed, the connection list.
* All teams: the timing budget (latency table), reused by anyone whose cell stalls.

### Background Information

* Flask documentation — request handling, background work outside the request thread: https://flask.palletsprojects.com/
* InfluxDB documentation — writing points with tags and fields, querying by tag: https://docs.influxdata.com/influxdb/
* scipy.stats — percentiles and distributions for the cycle-time analysis: https://docs.scipy.org/doc/scipy/reference/stats.html
* Dobot MG400 product page — motion speed, repeatability, I/O: https://www.dobot-robots.com/products/desktop-four-axis/mg400.html
* Finite state machines for machine control — search phrase "state machine timeout safe state industrial sequence design".
* Base MG400 Python package README and `AGENTS.md` — in the package repository (tagged URL from Smart Solutions L1); MovJ/MovL, position read, DO, stop.

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. The cell from Milestone 1: MG400, pump box, tool board with valve, sensors, UV LED, VL53L0X, nozzle camera, syringe + LED holder, tray and jig set, RPI control station.
2. Consumables: amber syringe with the recipe tip, tip caps, 405 nm resin, five dummy glasses, scrap polycarbonate squares 24×24 mm, at least 2 real glasses from the L5 batch, 1 AtomS3 or AtomS3R.
3. 405 nm goggles, nitrile gloves, IPA.
4. Oscilloscope or logic analyser for one latency cross-check (USB command to valve coil).
5. Stopwatch or video with a visible clock for the robot-arrival cross-check.
6. Jupyter Lab, pandas, scipy; InfluxDB client.
7. Git repository, folder `prototyping/milestone2/` with `src/`, `src/workflows/`, `data/`, `notebooks/`, `docs/`.

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Mount the chosen parts on the cell; run the Milestone 1 cold-start test again; run the VL53L0X Z calibration after mounting the syringe.
- [ ] Record the assembly workflow with the L4 recorder: jig approach, bezel path with dispense, glass pick, place with press, cure pose, image pose, finished slot. Save as JSON in `src/workflows/`.
- [ ] Write the state machine in the Flask app: states, transitions, timeouts, SAFE. Draw it in draw.io before coding it.
- [ ] Log per step: command sent, ack received, event received, robot arrived (position poll). One CSV row per step per cycle.
- [ ] Dry run: empty syringe, no glass, 10 cycles; every step in the log in order, every record row complete.
- [ ] Wet run on scrap polycarbonate: 5 cycles; check the bead lands on the bezel area, not the centre; check the cure by pulling the glass by hand.
- [ ] The real tag: one AtomS3, one glass from the L5 batch, filmed from the web click to the finished slot.
- [ ] 100 cycles with recirculating dummy glasses (≥ 10 wet, ≥ 1 real); records in the shared database.
- [ ] Latency measurements: 30 repetitions of each link in the chain.
- [ ] Notebooks; update `docs/specification.md` with the first measured values; tag `prototyping-milestone2` by 17.03.27.

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

The cycle, in tool-board commands (interface from Smart Solutions L2):

```
at bezel pose:   {"cmd":"pump","mode":"blow"} → {"cmd":"dispense","ms":<recipe>} → wait ev dispense_end
at glass slot:   {"cmd":"pump","mode":"suction"} → move down → wait until v below plateau → lift
at jig:          move down, hold 500 ms → {"cmd":"pump","mode":"blow"} for 100 ms → {"cmd":"pump","mode":"off"}
at cure pose:    {"cmd":"uv","ms":<recipe>,"pose_ok":1}
at image pose:   GET the camera frame → data/images/<cycle_id>.jpg
always:          every wait has a timeout; on timeout or {"ev":"alarm"} → {"cmd":"stop"} → SAFE → record written
```

### Analysis

1. **Cycle time over 100 cycles** (`notebooks/cycle_time.ipynb`). From `data/step_times.csv` (cycle_id, step, t_start_ms, t_end_ms): total cycle time per cycle as a histogram; median, minimum, 95th percentile; the median duration of each step as a stacked bar; the share of time in robot motion, in tool-board waits, in cure, in image capture and in record writing. State whether the median meets the Milestone 1 target; if no target was set in M1, use 60 s and write the measured value into the specification. Show separately the 10 wet cycles and the dry ones.
2. **Failure modes over 100 cycles** (`notebooks/failure_modes.ipynb`). Every cycle with `pick_ok = 0`, `dispense_ok = 0`, `clog_alarm = 1`, a refused `uv`, an MG400 error, a step timeout or a missing image gets a class in `notes` as `fail=<class>`. Show the Pareto table (class, count, time lost in s, recovered automatically yes/no, cycles until the next failure), and for the top two classes the fix that was made and whether it held in the last 30 cycles.
3. **Latency chain** (`notebooks/latency.ipynb`). 30 repetitions each: web click → RPI handler entered; RPI command → tool-board `ack`; `ack` → `dispense_start` event; MovL command of a 100 mm move → position poll reports arrival; image request → file on disk. Table of median and 95th percentile per link; one link cross-checked with the scope (command timestamp vs valve coil voltage). From the 95th percentiles, the timeout of each wait in the state machine: timeout = 2 × p95 + 100 ms, written into `docs/state_machine.md`.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: Dry cycle from the web page

Empty syringe, no glass in the source slot, one click. The step log must show every command, ack and event in the recorded order, the cycle must end in IDLE with a record row that has every column filled (`pick_ok = 0` is the expected value here). Run it after every change to the state machine; it takes one cycle time.

#### Test Example 2: Alarm mid-dispense

Leave a tip in daylight until the resin cures in it; mount it; start a cycle. The `{"ev":"alarm"}` must move the state machine to SAFE within one sample period, the robot must stop, the record must carry `clog_alarm = 1` and `fail=clog` in `notes`, and the next cycle must be refused until `{"cmd":"clear"}` was sent from the page. Keep the curve file of that cycle as the reference clog.

#### Test Example 3: Camera lost

Switch the camera's power off during the pick step. The cycle must finish with `image_file` empty and `fail=image` in `notes`, without waiting longer than the image timeout, and the next cycle must run normally once the camera is back. Repeat with the MG400 LAN cable during the cure wait: the LED must time out on the board, the state must go to SAFE, and the record must be written.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* Video, uncut, of the first complete tag: the web click, the cell, the finished slot, with the page visible.
* The physical tag at the defense; photo in `docs/` showing the glass on the bezel with no resin on the screen area.
* `data/cycles.csv` with ≥ 100 rows of this milestone's `workflow_id`, curves and images per cycle, and the same rows in the shared InfluxDB under the team tag (a query screenshot with the count).
* `data/step_times.csv` with ≥ 100 × (number of steps) rows.
* `data/latency.csv`: 30 × 5 rows; one scope screenshot of the cross-check.
* `docs/state_machine.md`: draw.io diagram, transition table, timeout per wait with the p95 it came from.
* `src/workflows/<name>.json`: the recorded workflow, and the record of who recorded it and how long it took.

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Shared database and repo. Every cycle is a row in `data/cycles.csv` in the Smart Solutions L4 schema and a point in the InfluxDB `cycle` measurement (tags `team`, `robot`, `workflow_id`), with the 100 Hz samples in `sample`. No columns are added. Two conventions on top of the schema, used from here to the end of the course:
* `notes` carries `fail=<class>` (`pick`, `dispense`, `clog`, `uv_refused`, `mg400`, `timeout`, `image`) for a failed cycle and `dry` or `wet` for the dispense target.
* Step timings are a separate file `data/step_times.csv` (cycle_id, step, t_start_ms, t_end_ms), repo only.

### Safety

* Robot motion: nobody inside the MG400 envelope while a workflow runs; the stop button on the web page and the physical stop are both within reach of the person watching. The first 100 cycles are unattended in the sense that nobody presses buttons, not that nobody is in the room.
* UV: 405 nm goggles for everyone at the table when the LED is enabled; the LED runs only with `pose_ok = 1` and the on-board timeout; the shroud stays on. Never look into the cure pose from below the table edge.
* Resin: nitrile gloves, tip caps whenever the syringe is idle, IPA for cleaning, only cured resin into the bin. Uncured resin on skin is washed off with soap and water, not IPA.

### Components for the next milestone

Nothing new unless the Milestone 1 audit or the first 100 cycles found a gap. The 0.01 g scale (03.11 order) and the 5 ml syringes from the M1 spares are what Milestone 3 needs.

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| Gaps found in the audit or in the 100 cycles | as listed in `docs/order_10-03-27.md` | Each line with the failure class or audit row that caused it |
| Tips, syringes, resin | 0 | From the M1 spares unless the consumables notebook was wrong; then say by how much |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — state machine in the Flask app, workflow JSON, step logging, records in the shared database | 5 p |
| Analysis — cycle-time distribution, failure-mode Pareto with fixes, latency chain with timeouts derived from it | 5 p |
| Prototype — the real tag glued from one web command (video and the object), 100 cycles completed | 5 p |
| Documentation — state-machine document, integration-problem list with solutions, specification updated with measured values | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `prototyping-milestone2` 72 h before the defense.**

* `prototyping/milestone2/src/`: the Flask app with the state machine, `src/workflows/` with the JSON; `AGENTS.md` at the repository root updated with how to run one cycle.
* `prototyping/milestone2/data/`: `cycles.csv`, `curves/`, `images/`, `step_times.csv`, `latency.csv`.
* `prototyping/milestone2/notebooks/`: the three notebooks with outputs.
* `prototyping/milestone2/docs/`: `state_machine.md`, the integration-problem list, the tag photo, the video link, the updated `specification.md`.
* Live change at the defense: the instructor names a different source slot, a different dispense time or a different tag orientation; the team changes it on the page or in the workflow and runs one cycle during the session.

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

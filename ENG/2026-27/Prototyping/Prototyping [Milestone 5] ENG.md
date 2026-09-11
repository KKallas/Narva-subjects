## Prototyping: Milestone 5 — Production run for the summer camp

**Workload:** 14 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 17.04.27 | **Order date:** 19.05.27 | **Defense:** 29.05.27

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the milestone folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

The 2027 summer camp plays with the tags this cell makes. The camp is the external user: it needs a box of working tags on a date, and it does not care about the grade. The target is **at least 16 finished tags**, 8 per playing pair with spares, across the four cells; that is at least 4 accepted tags per team from the 5 sets of hardware per team in the production order (AtomS3R ×20, batteries ×20 in total). If the camp's game specification changes the number of players or tags per pair, the target changes with it and the specification says so; the per-team quota is then the new total divided by the number of working cells, rounded up. A tag is accepted when it passes the tag acceptance test below, not when the cycle record says `dispense_ok = 1`.

Five sets of hardware per team give a thin yield statistic, so the production run is rehearsed first: at least 20 production-workflow cycles on dummy tags (a glass glued onto a 24×24 mm scrap polycarbonate square in the jig), with the same acceptance test applied to each, before the first real AtomS3R goes into the jig. Yield, resin per tag, time per accepted tag and tags per hour are computed over rehearsal and real cycles together, and reported separately.

The second deliverable is the documentation package that lets someone else run the cell in June without the team: user guide (from the Milestone 4 draft, after the UX test edits), maintenance guide, bill of materials with supplier, price and lead time per line, and the software install from a blank SD card (the Smart Solutions integration image or the install script). A team member who did not write the install guide installs the spare RPI from it, timed. The third deliverable is the demonstration of the specification: every performance target from Milestone 1 with its measured value and the notebook it came from, in one table, and the 5-minute demo (how the cell works, how to set it up, how the model calibrates) as a written script with a time per minute.

Milestones 4 and 5 run in parallel from 17.04.27 and are defended together on 29.05.27. The production run needs the cell housed and the maintenance guide in place (Milestone 4) and the model in the loop (Milestone 3); the run itself is the last two weeks. **Full project** teams defend the same content on the same day.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* Milestone 4: the housed cell, connection table, user and maintenance guides.
* Milestone 3: the model in the loop, the "replace syringe" and retry logic.
* 3D Print L5: the glass batch, validated on arrival; the drawing goes into the documentation package.
* Smart Solutions integration project: the SD-card image or install script.

**Gives to**
* The 2027 summer camp: the tags in a labelled box with the tag registry and a one-page card.
* Next year's course: the documentation package and the specification-vs-measured table as the starting point for the next audit.

### Background Information

* InfluxDB documentation — querying a whole production run by `workflow_id` and exporting it: https://docs.influxdata.com/influxdb/
* Flask documentation — deployment of the app as a service on the RPI, for the install guide: https://flask.palletsprojects.com/
* WireGuard documentation — client configuration for the install guide: https://www.wireguard.com/
* nginx documentation — the proxy location for the camera stream, for the install guide: https://nginx.org/en/docs/
* M5Stack AtomS3R documentation — firmware flashing of the tags, if the camp's firmware is loaded by the team: https://docs.m5stack.com/en/core/AtomS3R
* First-pass yield and Pareto analysis in small production runs — search phrase "first pass yield calculation small batch production Pareto".

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. The housed cell from Milestone 4 with the model in the loop.
2. Production hardware: AtomS3R ×5, battery modules ×5, glasses from the L5 batch (plus the 07.04.27 reserve), 405 nm resin, tips and tip caps.
3. Scrap polycarbonate squares 24×24 mm for the 20 rehearsal cycles.
4. 0.01 g scale (resin per tag), calipers (glass offset), the nozzle camera (screen inspection), a stopwatch.
5. Spare RPI with a blank SD card for the install test.
6. Jupyter Lab, pandas, scipy; InfluxDB client.
7. A labelled box for the tags and a printed one-page card; LiPo bag for storage.
8. Git repository, folder `prototyping/milestone5/` with `src/`, `data/`, `notebooks/`, `docs/`, `fusion/`, `stl/`, `models/`.

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Freeze the production workflow as `src/workflows/production_v1.json` and the recipe (tip, setpoint, dispense_ms, cure_s, compensation on or off, retry policy).
- [ ] Write the tag acceptance test (below) and `data/tag_acceptance.csv` with one row per tag.
- [ ] Rehearsal: at least 20 production cycles on dummy tags; acceptance test on each; fix what fails before the real run.
- [ ] Real run: 5 AtomS3R per team; each tag numbered on the back and in the registry; battery plugged by the robot or the human per the Milestone 4 decision.
- [ ] Unattended run of at least 60 minutes (rehearsal cycles are fine) with the event log; nobody touches the cell.
- [ ] Documentation package: `user_guide.md`, `maintenance_guide.md`, `bom.csv`, `install.md`, the CAD file list, the glass drawing.
- [ ] Install test: a team member who did not write `install.md` sets up the spare RPI from it; time and every stop noted.
- [ ] `docs/spec_vs_measured.md`: every Milestone 1 target with its measured value and source.
- [ ] Demo script `docs/demo.md` (5 minutes, one line per 30 s) and a rehearsal video.
- [ ] Hand-over: the tags in the box with the registry and card; tag `prototyping-milestone5` by 26.05.27.

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

Tag acceptance test, per tag, in this order: (1) the tag boots on the battery alone, screen visible through the glass; (2) no resin on the screen area in the nozzle-camera image; (3) glass offset to the bezel under 0.5 mm with calipers; (4) the cup lifts the tag by the glass at the recipe vacuum and holds it for 10 s; (5) no glass movement when pushed by thumb. One row per tag: tag_id, team, cycle_id, date, battery_type, tests 1–5 as 0/1, accepted, note.

### Analysis

1. **Production yield** (`notebooks/production.ipynb`). All cycles of `production_v1` (rehearsal and real): attempted, accepted, rejected by class (resin on screen, glass offset over 0.5 mm, pick fail, clog, cure fail, battery not seated, other); first-pass yield in percent for rehearsal and for the real run; resin per tag from the scale before and after the run; time per accepted tag and tags per hour from `step_times.csv`; interventions per 10 cycles. Pareto of rejection classes and, for the top class, what was changed between rehearsal and the real run.
2. **Specification targets vs measured performance** (`notebooks/spec_vs_measured.ipynb`). One row per performance target in the Milestone 1 specification: target, minimum acceptable, measured value, milestone and notebook it came from, pass or fail. At least: cycle time, pick success rate, dose CV, fill-estimate MAE, retry success, tags per hour, unattended minutes, arm mass, UX assembly time, first-pass yield. The rows that fail get one sentence on the cause and one on what would fix it. The notebook renders the table that goes into `docs/spec_vs_measured.md`.
3. **Unattended run** (`notebooks/unattended.ipynb`). At least 60 minutes with nobody touching the cell: cycles completed, every state transition into SAFE or ALARM with its time and cause, retries, alerts, the mean number of cycles between interventions, and where and why it stopped if it did. From this, the maximum unattended time the team writes into the user guide, with the rule used to derive it.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: Fresh install

A team member who did not write `install.md` takes the spare RPI and a blank SD card and follows the guide: image or install script, network, VPN, tool board, camera. Stop the clock when the Milestone 2 dry cycle passes on that RPI. Every step where the person had to ask counts as a missing line; edit the guide and record the time.

#### Test Example 2: Tag acceptance

Run the five checks above on one rehearsal tag deliberately made bad (glass placed 1 mm off, or cure cut to a third of the recipe). The test must reject it, and the row must say which check failed. Then run it on a good tag; all five must pass. The test is used unchanged on every tag of the real run.

#### Test Example 3: One hour hands-off

Start the unattended run with the source tray full and the syringe above 4 ml. For 60 minutes nobody touches the cell, the page or the robot. If the cell stops, it must be in SAFE with pump off, valve on the cup branch, LED off, and the log must show why. The stop is not a failure of the test; a stop without a logged cause, or a stop that is not in SAFE, is.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* At least 4 accepted tags per team, physically in the box at the defense, numbered, with `data/tag_registry.csv` and the printed card; at least 16 across the four teams.
* `data/tag_acceptance.csv`: one row per tag attempted (rehearsal and real), at least 25 rows.
* `data/production.csv` or the `production_v1` rows in `data/cycles.csv` with curves and images, and the same rows in the shared database.
* Scale readings of the resin before and after the run (photo or CSV).
* `data/unattended_run.csv`: at least 60 minutes of event log with timestamps.
* `data/install_test.csv`: steps, times, stops, with the name of the installer.
* `docs/user_guide.md`, `docs/maintenance_guide.md`, `docs/bom.csv` (every part: qty, supplier, unit price, lead time), `docs/install.md`, `docs/cad_files.md` (every CAD file with its location), the glass drawing PDF.
* `docs/spec_vs_measured.md` and `docs/demo.md`; the rehearsal video of the 5-minute demo.

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Shared database and repo. Production cycles under `workflow_id = production_v1` in the Milestone 3 schema (with `fill_model_ml` and `pick_pred`). A tag registry, repo only, `data/tag_registry.csv`: tag_id, team, cycle_id, date, atom_type, battery_type, accepted, handed_over. Optionally the same as an InfluxDB measurement `tag` with tag `team` and the fields above, so the portal can show tags per team.

### Safety

* More than one hour of unattended operation: the cell runs only with a person in the room, the physical stop and the page stop within reach, and the cordon around the envelope in place. The Smart Solutions L5 watchdog is active: on loss of the tool board, the MG400 or the Flask process the cell must reach SAFE by itself (pump off, valve unpowered, LED enable low); the cable-pull cases are re-run in the housed cell before the first unattended run.
* UV: the LED shroud on, the on-board timeout and `pose_ok` interlock active, goggles for everyone in the room during the run, the cure pose not visible from a seated position.
* Resin: gloves, tip caps between runs, IPA, cured waste only; the syringe is replaced at the model's 2 ml alert, not run dry.
* Batteries: plugged tags are stored switched off in the LiPo bag; no charging during the unattended run; a warm or swollen module is removed from the run.
* The maximum unattended time in the user guide is the one measured in Analysis 3, not a guess.

### Components for the next milestone

There is no next milestone; this list is for the summer camp and the June hand-over. Nothing can be ordered through the course after 29.05.27.

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| Polycarbonate glasses | 5 | Spares for the camp from the L5 batch, in the box with the tags |
| Tips of the recipe size, tip caps | 5 + 5 | For anyone running the cell in June |
| 405 nm resin | remaining bottle | Stored in the dark with the cell |
| Battery modules | 1 spare | If the production order left one |
| Printed user guide and maintenance guide | 1 each | In the station housing |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — production workflow and recipe frozen, all production cycles and the tag registry in the repo and the database, BOM and CAD file list | 5 p |
| Analysis — yield with rejection Pareto, specification-vs-measured table with causes for failures, unattended-run analysis with the derived limit | 5 p |
| Prototype — at least 4 accepted tags in the box, 60 minutes unattended, fresh install passed by a stranger to the guide | 5 p |
| Documentation — user guide, maintenance guide, install guide that passed the install test, 5-minute demo script and video | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `prototyping-milestone5` 72 h before the defense.**

* `prototyping/milestone5/src/`: the app as installed on the production RPI, `src/workflows/production_v1.json`, the install script; `AGENTS.md` at the root final.
* `prototyping/milestone5/models/`: the model files in production with `MODEL.md`.
* `prototyping/milestone5/data/`: `cycles.csv`, `curves/`, `images/`, `step_times.csv`, `tag_acceptance.csv`, `tag_registry.csv`, `unattended_run.csv`, `install_test.csv`.
* `prototyping/milestone5/notebooks/`: the three notebooks with outputs.
* `prototyping/milestone5/docs/`: the documentation package, `spec_vs_measured.md`, `demo.md`, the video link, the final `specification.md`.
* `prototyping/milestone5/fusion/`, `stl/`: the final CAD set or `docs/cad_files.md` with locations.
* The 5-minute demo is given live, then 10 minutes of questions with the live change: the instructor names a different slot, dispense time or tag orientation, or one install step to be repeated on the spare RPI; the team runs it during the session and one more tag, or dummy tag, comes out of the cell.

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

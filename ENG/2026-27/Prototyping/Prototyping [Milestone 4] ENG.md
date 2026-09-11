## Prototyping: Milestone 4 — Functional prototype with enclosures and battery plugging

**Workload:** 16 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 17.04.27 | **Order date:** 19.05.27 | **Defense:** 29.05.27

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the milestone folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

The cell from Milestone 3 works on a bench with cables in the open. Milestone 4 puts every part into its housing from 3D Print L3: the tool housing on the arm (tool board, valve, camera mount, UV LED with heatsink and shroud, strain relief for tube and USB) and the station housing on the table (RPI and screen). Every cable and tube gets a label at both ends and a row in the connection table; the cell must start after somebody else has unplugged and replugged everything by the labels alone. Mass on the arm is measured again with the housing on; the 3D Print L3 target of under 250 g with valve and empty syringe stays.

The second part is the semester-2 stretch goal: the robot plugs the battery module. The glass exists so that the suction cup can lift the finished tag by its face, and that is the mechanism: after the cure, the robot picks the tag by the glass, carries it to a second fixture that holds the battery module (ATOM TailBat or Atomic Battery Base) pins up, and presses the tag onto it. The press force comes from the lifting nozzle's spring, so the first measurement is whether the spring delivers the insertion force at all (weigh the force of a hand insertion on the scale first). If the spring does not, the fixture gets a rigid stop under the nozzle or a second, fixed pusher. **Whether this is in scope is decided by a measurement, not by opinion:** 20 robot attempts by 08.05.27; 16 or more fully seated (the tag boots on the battery alone) keeps it in; fewer means the fallback: the human plugs the battery at the finished tray, and the user guide documents it as a manual step with a photo and a measured time. The fallback is a valid outcome; the analysis of why the robot could not do it is the deliverable in that case.

The third part is the two documents that make the cell usable by people who did not build it. **UX test:** another team gets the cell switched off, the user guide and a box with an AtomS3, a glass and a battery, and assembles one tag within 10 minutes without asking anything; every stop longer than 30 s is a missing line in the guide. **Maintenance guide:** what breaks and how to replace it, for the tip, the syringe, the valve, the LED and the cup, each with the symptom, the sensor number that shows it, the replacement steps, the re-check after replacement (Z calibration, taught points, pose_ok) and the measured replacement time.

Milestones 4 and 5 run in parallel from 17.04.27 and are defended together on 29.05.27. The order date for both is 19.05.27; the production hardware should already be on its way from the 07.04.27 order.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* 3D Print L3 (tool and station enclosures, camera and LED mounts, assembly guide), L2 (tray and jig; the battery fixture is a new module on the same foot), L4 (the improved part, if it is one of the housed parts).
* Milestone 3: the cell with the model in the loop.
* Smart Solutions L5: safe state and fault handling, which the housed cell must still pass (cable-pull cases).

**Gives to**
* Milestone 5: the production-ready cell, the connection table, the user guide draft, the maintenance guide.
* Next year's course: the maintenance guide and the UX test protocol.

### Background Information

* M5Stack ATOM TailBat documentation — dimensions, header, charging: https://docs.m5stack.com/en/atom/tailbat
* M5Stack Atomic Battery Base — resource name; search phrase "M5Stack Atomic Battery Base docs".
* M5Stack AtomS3R documentation — bottom header pinout and mechanical drawing for the fixture: https://docs.m5stack.com/en/core/AtomS3R
* Fusion 360 help — joints and interference check for the battery fixture: https://help.autodesk.com/view/fusion360/ENU/
* PrusaSlicer documentation — print-pause for inserts in the fixture: https://help.prusa3d.com/
* LiPo handling — search phrase "LiPo battery safety storage swelling puncture".
* Cable labelling practice — search phrase "cable labelling both ends connection table wiring documentation".

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. The cell from Milestone 3, both enclosures from 3D Print L3, strain reliefs, cable glands, label maker or printed labels and clear tape.
2. Battery modules ×1 (+2 shared) and AtomS3/AtomS3R ×1 (+2 shared) from the 07.04.27 order; the Milestone 5 production hardware if it has arrived.
3. Fusion 360 and a printer for the battery fixture; PETG or PLA, heat-set inserts, M5 bolts for the table foot.
4. 0.01 g scale and a kitchen scale (arm mass, insertion force); contact or IR thermometer for the LED heatsink and the buck module.
5. Stopwatch and a phone camera for the UX test.
6. Jupyter Lab, pandas.
7. Git repository, folder `prototyping/milestone4/` with `src/`, `fusion/`, `stl/`, `data/`, `notebooks/`, `docs/`.

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Fit the tool board, valve, camera, LED and strain reliefs into the tool housing; the station into its housing; measure the arm mass with valve and empty syringe.
- [ ] Label every cable and tube at both ends; write `docs/connections.csv` (label, from, to, signal or medium, connector).
- [ ] Run the Milestone 2 dry cycle and the Smart Solutions L5 cable-pull cases in the housed cell; record the results.
- [ ] Measure the insertion force of the battery module by hand on the scale (10 insertions); compare with the nozzle spring force at full compression.
- [ ] Design and print the battery fixture on the table foot; check in Fusion that the pressed tag and the fixture do not collide with the nozzle housing.
- [ ] Record the plugging step in the workflow; 20 robot attempts by 08.05.27; take the go/no-go decision and write it in `docs/battery_decision.md`.
- [ ] Write the user guide draft and the maintenance guide; time each of the five replacements.
- [ ] UX test with another team (two visitors from two teams if possible); log times, stops and questions.
- [ ] 100 cycles in the housed cell with temperature readings every 10 cycles.
- [ ] Notebooks; specification update; tag `prototyping-milestone4` by 26.05.27.

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

Insertion force from the scale, one line: F = m × 9.81 / 1000 with m in grams read while pressing the module onto the tag on the scale pan.

### Analysis

1. **UX test timings** (`notebooks/ux_test.ipynb`). For each visitor: time from first touch to a finished tag in the finished slot, split into steps read off the video (power on, load tray and syringe, start the workflow, wait, remove the tag, plug the battery if manual); every stop longer than 30 s with the guide line that was missing; every question they wanted to ask (written, not answered). Table visitor × step; pass/fail against 10 minutes; the list of guide edits made afterwards and the second visitor's time after the edits.
2. **Battery plugging** (`notebooks/battery.ipynb`). Hand insertion force: 10 readings, mean and range in N; nozzle spring force at full compression from the scale. 20 robot attempts: outcome per attempt (seated and boots, partially seated, missed, dropped), the position offset measured with calipers for partial seats, success rate with its go/no-go verdict. In the fallback case: the human plug time over 10 tags and the failure analysis (which of force, alignment, fixture stiffness or tag orientation was the limit, with the number that shows it).
3. **Housed endurance** (`notebooks/housed_run.ipynb`). 100 cycles in the housed cell: LED heatsink and buck-module temperature every 10 cycles (before the first cycle as reference), communication errors and disconnects counted from the log, failure-mode Pareto as in Milestone 2 compared with the open-bench run, arm mass with housing. Maintenance timings: each of the five replacements once by a team member and once by a visitor, with the re-check result (dose within 10 % of before after a tip change, 5 of 5 picks after a cup change).

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: Replug by labels

Cell off. A person from another team unplugs every connector and tube, then plugs everything back using only the labels and `docs/connections.csv`. Power on; the Milestone 2 dry cycle must pass. Time it; any connector that could be plugged wrongly without an error is a design fault to fix (keying, a different connector, a note in the guide).

#### Test Example 2: Battery plug verification

After the robot (or the human, in the fallback) plugs the battery, disconnect the cell's USB from the tag and switch the battery on: the AtomS3 must show its boot screen on the battery alone. Then check with calipers that the module sits flush on all four sides (gap under 0.3 mm). A tag that boots but sits crooked counts as partially seated.

#### Test Example 3: Tip replacement with re-check

Follow the maintenance guide to replace the tip; run the VL53L0X Z calibration; run 5 wet cycles on scrap polycarbonate; weigh the doses. Mean dose within 10 % of the value before the change and the bead on the bezel area in all 5 images. If not, the guide misses a step.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* Photos of both closed housings with the labels visible; the arm mass reading with housing, valve and empty syringe (target under 250 g).
* `docs/connections.csv` with one row per cable and tube; the replug test time and the name of the person who did it.
* `data/ux_test.csv`: visitor, step, t_start_s, t_end_s, stop_reason; a video of at least one visitor's run.
* `data/battery_test.csv`: 10 hand-force rows and 20 robot-attempt rows (or the fallback's 10 human-plug rows); `docs/battery_decision.md` with the verdict and the numbers.
* `fusion/` and `stl/` of the battery fixture (or a README with the file location); a photo of it on the table foot.
* `data/housed_run.csv`: 100 cycles with temperature readings every 10 cycles; the cycles also in the shared database.
* `data/maintenance_times.csv`: 5 parts × 2 persons with the re-check result.
* `docs/maintenance_guide.md` and `docs/user_guide.md` (draft).

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Shared database and repo. Cycles as in Milestone 3, under this milestone's `workflow_id` (with the plugging step if in scope). `data/ux_test.csv`, `data/battery_test.csv`, `data/maintenance_times.csv` and the temperature readings are repo only.

### Safety

* Batteries (LiPo): never puncture, bend or short the pouch; the fixture presses on the AtomS3 shell and the module's connector, never on the pouch; a swollen, dented or warm module is removed and put in a LiPo bag, not used. Charge only supervised, on a non-flammable surface. Modules that are not in use are stored switched off in a LiPo bag, not in the tray.
* The robot presses with a limited force: the nozzle spring, or a stop that limits travel; no press move is run at full speed; the first attempt on a new fixture is done at 10 % speed with a hand on the stop.
* The rules of Milestone 2 stay: nobody inside the envelope during a workflow, goggles when the LED is enabled, gloves and tip caps for resin. The closed tool housing must not block the LED shroud or the heatsink; the housed-run temperatures show whether it does.

### Components for the next milestone

Milestone 5 is the last one; this is the production hardware if it was not ordered on 07.04.27. **19.05.27 is the last date**; a delivery that late arrives in the defense week, so the production run must be planned for the days between arrival and 29.05.27.

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| AtomS3R | 5 (20 in total) | Only if not already in the 07.04.27 order |
| Battery modules | 5 (20 in total) | The type that passed the M4 test |
| Polycarbonate glasses | 7–8 (30 in total) | Only if not already in the 07.04.27 order |
| 405 nm resin | 1 kg shared | If the 07.04.27 bottle is below 300 g |
| Battery fixture consumables: heat-set inserts, M5 bolts | 4 + 4 | From the 3D Print shelf if available |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — connection table, battery fixture CAD and STL, plugging step in the workflow, housed-run records in the database | 5 p |
| Analysis — UX test timings with guide fixes, battery plugging numbers and verdict, housed endurance with temperatures and maintenance times | 5 p |
| Prototype — everything housed and labelled under 250 g on the arm, replug test passed, battery plugged by the robot or the documented fallback, 100 housed cycles | 5 p |
| Documentation — user guide draft that passed a 10-minute UX test, maintenance guide for tip, syringe, valve, LED and cup with times, battery decision document | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `prototyping-milestone4` 72 h before the defense.**

* `prototyping/milestone4/src/`: the workflow with the plugging step (or the fallback marked in the workflow as a manual wait); `AGENTS.md` at the root updated.
* `prototyping/milestone4/fusion/` and `stl/`: the battery fixture and any housing changes, `.f3d`, `.step`, `.stl` or a README with their location.
* `prototyping/milestone4/data/`: `connections.csv`, `ux_test.csv`, `battery_test.csv`, `housed_run.csv`, `maintenance_times.csv`, `cycles.csv`, `curves/`, `images/`.
* `prototyping/milestone4/notebooks/`: the three notebooks with outputs.
* `prototyping/milestone4/docs/`: `user_guide.md`, `maintenance_guide.md`, `battery_decision.md`, photos, video links, the updated `specification.md`.
* Live change at the defense: the instructor names one part (tip, syringe, valve, LED or cup); the team replaces it by the maintenance guide during the session, does the re-check, and runs one cycle. Alternatively a different slot, dispense time or tag orientation as in the earlier milestones.

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

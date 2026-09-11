## Prototyping: Milestone 3 — Model in the loop

**Workload:** 18 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 20.03.27 | **Order date:** 07.04.27 | **Defense:** 17.04.27

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the milestone folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

The Data Acquisition L5 models go to work. The fill-level regressor and the three-way dispense classifier (pickle or joblib files from `data-acquisition/lab5/models/`) are loaded by the Flask server at start-up and called after every dispense. The pick is judged by the camera check, not by a model — there is no sensor on the cup. The page shows the fill estimate live ("syringe ≈ 4.2 ml"), the record carries it, and two decisions are taken by the model instead of a person: whether to compensate the dispense time, and whether to retry a pick.

Compensation is on or off according to the L5 result of the model you chose in Milestone 1. **H1** (dose depends on fill level): the compensation table dispense-ms vs fill is in the recipe and the cell uses it. **H0** (no dependence within ±10 % dose): compensation is deleted from the recipe, and the fill estimate serves one purpose, the "syringe below 2 ml, replace" alert; the pressure sensor's job is clog detection and pick verification. Both outcomes are valid and graded the same; this milestone checks on the scale which one holds on this cell, and a team that finds its L5 conclusion does not hold here reports that as the result. Setting out to find one thing and finding another is ordinary engineering.

Three tests make the model's behaviour measurable: a 5 ml syringe run from full to empty with the scale as truth, 50 picks of which half are set up to fail, and the other three teams' model files on 30 of your curves. The last one answers whether a model trained on one tool board transfers to another; when it does not, the reason (features computed differently, sensor offset, a different tip) is the finding.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* Data Acquisition L5: fill-level model (or its null result) and pick classifier as pickle/joblib files, with the feature list they were trained on; L4 dataset for canned test curves.
* Milestone 2: the cell, the state machine, the 100-cycle dataset, the timeouts.
* Smart Solutions L5: the REST API (`/status`, `/cycle`) and the retry hook that the agent demo used.

**Gives to**
* Milestone 4 and 5: the cell with the model in the loop; the "replace syringe" and "pick failed" logic that the maintenance guide and the production run depend on.
* All teams and the Data Acquisition integration project: the cross-team transfer table (which model works on which cell).

### Background Information

* scikit-learn model persistence — loading pickle/joblib, version pinning, why a different scikit-learn version breaks the load: https://scikit-learn.org/stable/model_persistence.html
* Flask documentation — application start-up hooks, keeping one loaded model object per process: https://flask.palletsprojects.com/
* scipy.stats — mean absolute error, confidence intervals, monotonic trend test for the drain curve: https://docs.scipy.org/doc/scipy/reference/stats.html
* Confusion matrix, precision and recall for the pick classifier — search phrase "scikit-learn confusion_matrix precision recall binary classifier".
* Resin density for converting scale grams to millilitres — the datasheet of the resin bottle used since Gate A (search phrase "<resin brand> 405 nm resin density g/cm3"); use 1.1 g/ml if the datasheet gives none.

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. The cell from Milestone 2.
2. 0.01 g digital scale (03.11 order); a 5 ml amber syringe with the recipe tip, tip caps.
3. Scrap polycarbonate squares, the five dummy glasses, a 0.5 mm and a 3 mm shim for the induced pick failures.
4. The four teams' model files and their feature-extraction descriptions (from each team's `data-acquisition/lab5/`).
5. Jupyter Lab, pandas, scipy, scikit-learn pinned to the version in the model's `MODEL.md`.
6. 405 nm goggles, nitrile gloves, IPA.
7. Git repository, folder `prototyping/milestone3/` with `src/`, `models/`, `data/`, `notebooks/`, `docs/`.

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Copy the chosen model files into `models/` with a `MODEL.md`: training team, date, feature list in order, scikit-learn version, sha256, L5 outcome (H1 or H0) and its ±10 % dose evidence.
- [ ] Load both models at Flask start; expose the file name, sha256 and version in `/status`.
- [ ] Feature extraction on the RPI from the sliced curve (event timestamps from the tool board): the same features, in the same order, as in the L5 notebook. Verify with one canned L4 curve: same estimate ±0.01 ml.
- [ ] Close the loop in the state machine (pseudocode below): estimate after every dispense, classify after every pick, alert below 2 ml, retry once on a failed pick.
- [ ] Set compensation on or off per `MODEL.md`; if on, load the compensation table into the recipe.
- [ ] Drain test: 5 ml syringe from full to the empty alarm, scale reading every 10 dispenses.
- [ ] Dose check: 10 weighed dispenses above 4 ml and 10 below 1.5 ml with compensation as set.
- [ ] Retry test: 50 picks, 25 set up to fail, in random order, camera image as truth.
- [ ] Cross-team test: the other three models on 30 of your curves with scale truth.
- [ ] Notebooks, `docs/model_in_loop.md`, specification update; tag `prototyping-milestone3` by 14.04.27.

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

The loop, language-neutral:

```
after dispense_end: slice curve by events → features → fill_ml = fill_model(features); show on page; write to record
if H1: next dispense_ms = compensation_table[fill_ml]      (H0: dispense_ms stays the recipe value)
if fill_ml < 2 ml or alarm: finish the current tag → alert "replace syringe" → refuse the next cycle until clear
after pick lift: pick_ok = camera_check(frame)
if pick_ok == 0: blow-off, retry once at the same slot → if 0 again: move to the next slot once → else SAFE
```

Fill from the scale, one line: fill_ml = (m_now − m_empty) / ρ, with ρ from the resin datasheet (1.1 g/ml default), m_empty the syringe with tip weighed before filling.

### Analysis

1. **Estimate vs scale over one syringe** (`notebooks/drain_test.ipynb`). A 5 ml syringe, weighed with tip before filling, run from full to the empty alarm with dispenses into the waste cup; scale reading every 10 dispenses, at least 15 readings. If the recipe dose drains too slowly, raise `dispense_ms` for this test so the syringe empties within about 150 dispenses, and say so. Plot model estimate and scale truth against dispense count; MAE in ml; is the estimate monotonic (Spearman correlation with the count); at which dispense the estimate crossed 2 ml and at which the scale did. Then the dose check: 10 weighed dispenses above 4 ml and 10 below 1.5 ml with compensation as set by `MODEL.md`; mean and CV per level; the difference between levels in percent. If H0 was set and the low-level dose differs by more than 10 %, or H1 was set and the compensated doses differ by more than 10 %, the L5 conclusion does not hold on this cell: report it, do not hide it.
2. **Pick-retry success** (`notebooks/retry_test.ipynb`). 50 picks: 25 normal, 25 set up to fail (empty slot ×8, glass offset 3 mm ×9, glass tilted on the 0.5 mm shim ×8), in random order. Truth from the camera image at the lift pose. Confusion matrix of the classifier against the truth; precision and recall; retry success rate per failure type (an offset glass should succeed after a re-seat, an empty slot never); the time cost of one retry in seconds from `step_times.csv`.
3. **Another team's model on this cell** (`notebooks/cross_team.ipynb`). Run all four teams' fill models on the same 30 curves from the drain test (which have scale truth). MAE per model; a scatter of each model's estimate against truth. For every model with MAE more than twice your own model's, state the cause found: feature order, sensor offset (compare plateau kPa of both boards at the same setpoint), tip size, scikit-learn version. Same for the pick classifiers on the 50 retry-test curves: accuracy per team.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: Model loads and reproduces L5

Start the Flask app; `/status` must return the model file names, sha256 and scikit-learn version. Feed one canned curve from `data-acquisition/lab4/data/curves/` through the RPI feature extraction; the estimate must equal the L5 notebook's value for that curve within 0.01 ml. Run this after every change to the feature code.

#### Test Example 2: Induced pick failure and retry

Leave the source slot empty; start a cycle. The classifier must return 0 on the first lift, the state machine must retry once at the same slot, then once at the next slot, then go to SAFE with `pick_ok = 0` and `retries=2` in `notes`. Then put a glass 3 mm off centre in the slot: the first pick must be flagged, the retry must succeed, the record must have `pick_ok = 1` and `retries=1`.

#### Test Example 3: Low-fill alert

Feed a curve recorded from an almost empty syringe (from the drain test) as the live curve. The page must show the alert, the running cycle must finish, the next cycle must be refused until `{"cmd":"clear"}` is sent after a syringe change and the estimate is above 2 ml again.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* `data/drain_test.csv`: at least 15 rows (n_dispense, scale_g, fill_ml_truth, fill_model_ml, dispense_ms); photo of the scale with the syringe at the first and the last reading.
* `data/dose_check.csv`: 20 rows (level, n, dose_mg, dispense_ms, compensation on|off).
* `data/retry_test.csv`: 50 rows (n, setup, pick_pred, pick_truth, retries, outcome, image_file).
* `data/cross_team.csv`: 30 curves × 4 models for fill, 50 curves × 4 models for pick.
* Video: the page with the estimate falling over at least 20 dispenses; one induced failure with the retry visible on the robot.
* `models/` with both files, `MODEL.md` and the sha256 that `/status` reports.
* Curves and records of every cycle of this milestone in `data/` and in the shared database.

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Shared database and repo, schema as in Milestone 2. Two fields are added to the InfluxDB `cycle` measurement, `fill_model_ml` and `pick_pred`, and appended as the last two columns of `data/cycles.csv` after `notes`. `fill_ml_estimate` and `fill_method` keep their L4 meaning (ground truth by scale or count) so semester-1 readers are not broken; the Milestone 1 replay notebook is re-run once on the new file and the result kept in `notebooks/`. `notes` carries `retries=<n>` and, where applicable, `fail=<class>` as before.

### Safety

The rules of Milestone 2 apply unchanged. The drain test and the retry test add hours of robot running: the stop within reach, goggles on whenever the LED is enabled, tip caps between test blocks.

### Components for the next milestone

Two blocks. The first is for the Milestone 4 battery-plugging tests. The second is the tag hardware for the Milestone 5 production run: **order it now (07.04.27) if at all possible**; the last possible date is 19.05.27, which puts the delivery in the week of the defense.

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| Battery module, ATOM TailBat (190 mAh) or Atomic Battery Base | 1 (+2 shared, 6 in total) | For the M4 plugging tests; the two spares go to the teams that attempt robot plugging |
| AtomS3 or AtomS3R | 1 (+2 shared, 6 in total) | For the M4 plugging and UX tests; AtomS3R if AtomS3 is out of stock |
| AtomS3R for the production run | 5 (20 in total) | 16 tags for the camp plus spares; preferably in this order |
| Battery modules for the production run | 5 (20 in total) | Same type as tested in M4 |
| Polycarbonate glasses | 7–8 (30 in total) | Reserve beside the 3D Print L5 batch; same drawing |
| 405 nm resin | 1 kg shared | Production run and rehearsals |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — models loaded in Flask with `/status` evidence, feature extraction matching L5, loop in the state machine | 5 p |
| Analysis — drain test with MAE and threshold crossing, dose check per the H1/H0 setting, retry confusion matrix, cross-team table with causes | 5 p |
| Prototype — live estimate on the page during a run, retry executed by the robot, syringe run to empty | 5 p |
| Documentation — `MODEL.md`, `model_in_loop.md` with the loop and its thresholds, specification updated with the measured MAE and retry rate | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `prototyping-milestone3` 72 h before the defense.**

* `prototyping/milestone3/src/`: the Flask app with the loop; `AGENTS.md` at the root updated with the model endpoints.
* `prototyping/milestone3/models/`: both model files and `MODEL.md`.
* `prototyping/milestone3/data/`: `drain_test.csv`, `dose_check.csv`, `retry_test.csv`, `cross_team.csv`, `cycles.csv`, `curves/`, `images/`.
* `prototyping/milestone3/notebooks/`: the three notebooks with outputs, plus the re-run of the M1 replay notebook.
* `prototyping/milestone3/docs/`: `model_in_loop.md`, the video links, the updated `specification.md`.
* Live change at the defense: the instructor asks to switch compensation on or off, or to swap in another team's model file; the team does it in the repository and on the RPI and runs one cycle with the new estimate visible on the page.

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

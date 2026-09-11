## Data Acquisition: Lab 5 — Machine learning model, H1/H0

**Workload:** 30 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 05.12.26 | **Order date:** 06.01.27 | **Defense:** 19.01.27, online

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the lab folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

Use the Lab 4 dataset to answer one question stated as a hypothesis with two equally graded outcomes. **H1**: the dose per unit time depends on the fill level of the syringe; the result is a compensation table (dispense-ms vs. fill) and the corrected dose scatter shown on the scale. **H0**: within ±10 % dose there is no dependence; the result is a residual analysis that proves it and the compensation is deleted from the recipe. Either way the proof is the dispensed mass on the 0.01 g scale, not the model's own score.

The sensor was chosen to estimate the remaining volume from the shape of the pressure curve. With a thin 405 nm resin the material back-pressure term is small and H0 is the likelier outcome. Setting out to find one thing and finding another is ordinary engineering: if fill level does not matter, the same one sensor is still the clog detector and the empty-syringe detector, and the second model in this task — the three-way dispense classifier — is the one that goes into production in Smart Solutions L5 and Prototyping M3.

Three comparisons frame the regression: do Fourier features improve the model over time-domain features; does the op-amp signal chain (configs 3–4) beat the raw ADC (config 1) on the same cycles; and whose model works on whose robot. The last one is why four teams write to one bucket.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* Data Acquisition L4: `data/cycles.csv`, `data/curves/`, `data/curves_raw/`, `data/images/`, `docs/features.md`, the weighed-dose subset, the cure table. The other three teams' records from the shared InfluxDB bucket.
* Smart Solutions L4: the Flask app and the database endpoint the model plugs into.

**Gives to**
* Smart Solutions L5: `models/dispense_model.joblib` and its input definition, used to stop a run on a clog or an empty syringe; the fill estimate shown in the portal. The pick retry is driven by the camera check, not by a model.
* Prototyping M3: `models/fill_model.joblib` or the H0 decision, the compensation table or its absence in the recipe, the cross-team transfer result.
* All teams: the comparison tables, so the same question is not re-answered four times.

### Background Information

* scikit-learn user guide: https://scikit-learn.org/stable/
* Cross-validation, `train_test_split`, `GroupKFold`: https://scikit-learn.org/stable/modules/cross_validation.html
* Ensembles, random forest: https://scikit-learn.org/stable/modules/ensemble.html
* Linear models: https://scikit-learn.org/stable/modules/linear_model.html
* Regression metrics (MSE, R²), classification metrics (precision, recall, confusion matrix): https://scikit-learn.org/stable/modules/model_evaluation.html
* Model persistence with joblib: https://scikit-learn.org/stable/model_persistence.html
* `scipy.fft` for the spectral features: https://docs.scipy.org/doc/scipy/reference/fft.html
* pandas: https://pandas.pydata.org/docs/
* Data leakage in time-ordered data, group splits: search "data leakage time series group k-fold".
* Residual analysis for a null result, equivalence testing: search "two one-sided tests equivalence testing explained".
* Feature importance and permutation importance: search "scikit-learn permutation importance".

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. Python 3, Jupyter Lab, pandas, numpy, scipy, scikit-learn, joblib, matplotlib
2. The Lab 4 dataset in the repo and the shared InfluxDB bucket (all four teams)
3. RPI control station with the Flask app (Smart Solutions L4) and the tool board, for the live-curve test
4. MG400, syringe, recipe tip, digital scale 0.01 g, for the ten weighed dispenses at two fill levels
5. 405 nm goggles, nitrile gloves, IPA
6. git

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Copy `lab4/` data references to `lab5/`; load `cycles.csv` and all curves; pull the other teams' records from the bucket
- [ ] Feature extraction as one function used by the notebook and by the RPI app, definitions from `docs/features.md`
- [ ] Split: 80/20 held out by weighing block, 5-fold grouped cross-validation on the 80
- [ ] Linear regression → decision tree → random forest on the fill level; MSE, R², residuals
- [ ] Comparison 1: time features only vs. time + Fourier features
- [ ] Comparison 2: op-amp curves vs. the 50-cycle raw subset, same cycle ids
- [ ] Comparison 3: 4 × 4 matrix, train on one team, test on each other team
- [ ] H1 or H0 decided from the residuals; compensation table written or deleted from the recipe
- [ ] Scale proof: ten weighed dispenses at two fill levels, with and without compensation
- [ ] Three-way dispense classifier (normal, clogged tip, empty syringe) from the pressure curve; confusion matrix; exported
- [ ] Both models load in the RPI Flask app and return a result for a live curve
- [ ] Tag `data-acquisition-lab5` 72 h before 19.01.27

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

### Analysis

Notebook `notebooks/lab5_model.ipynb`, run with outputs before commit. Every number below appears in it.

1. **Dataset.** Rows loaded, rows after the Lab 4 cleaning, rows with `dose_mg`, rows per team from the bucket. Target for the regression: `fill_ml_estimate` (ml). Note its uncertainty from the ground-truth method (interpolation between weighings, or the drift of the counted method); a model cannot be better than its label.
2. **Features.** Time features: `response_ms`, `dpdt_max`, `plateau_kpa`, `auc`, rise time 10–90 %, overshoot. Fourier features from the dispense curve: dominant frequency, spectral energy in 0–5 Hz and 5–50 Hz, spectral centroid, first three FFT magnitudes as shape. Environment: `pump_setpoint_kpa`, `robot_speed_pct`, `tip_mm`, temperature if it was recorded. Feature extraction is one function with one signature (curve in, feature row out) and it is the same file the RPI app imports.
3. **Split.** 80/20 held out by weighing block (all cycles between two scale readings stay together), because neighbouring cycles share almost the same fill. 5-fold grouped cross-validation on the training part. State the block ids in each fold.
4. **Models.** Linear regression, decision tree, random forest, in that order, same features, same folds. Table: `model | features | CV MSE | CV R² | test MSE | test R²`. Residual plot vs. fill level and vs. setpoint for the best model.
5. **Comparison 1, Fourier features.** The table above twice: time features only, time + Fourier. Permutation importance of the Fourier columns. One sentence: do they help, and by how much R².
6. **Comparison 2, signal quality.** The 50 cycles that have both an op-amp curve and a raw config 1 curve. Same model, same split, features from each curve set. Table of MSE and R² for both. Where the raw signal loses: which features become noise.
7. **Comparison 3, between teams.** Train on team A's data, test on B, C, D; all 16 combinations; R² matrix 4 × 4. Where transfer fails, look at the feature distributions: tip size, setpoint, sensor offset. One paragraph on what a model would need to be device-independent.
8. **H1 or H0.** Decision rule written before the scale test: H1 if the best model's residual spread lets a fill-dependent correction change the dose by more than ±10 % across the syringe range, and the dose-vs-fill slope in the weighed subset is significant; H0 otherwise. If H1: compensation table `dispense_ms` vs. fill in 1 ml steps in `models/compensation.csv`, and the predicted corrected dose scatter. If H0: the residuals of dose vs. fill within ±10 %, an equivalence argument, and the compensation field removed from the recipe JSON. Both are full marks.
9. **Scale proof.** Ten dispenses onto the 0.01 g scale at a full syringe (≈ 9 ml) and ten at a near-empty one (≈ 2 ml), recipe setpoint and tip. Under H0, without compensation: the two means agree within ±10 % of each other. Under H1: ten more at each level with the compensation table applied; the corrected means agree within ±10 % and the uncorrected ones do not. `data/scale_proof.csv`: `run, fill_ml, compensated (0|1), dispense_ms, dose_mg`. This is the acceptance measurement.
10. **Three-way dispense classifier.** Input: the pressure curve of one dispense, or its features — rise time, dP/dt max, plateau value, area under the curve, fall time. Labels: normal, clogged tip, empty syringe, from the deliberate failures in Lab 4. Logistic regression and a decision tree; confusion matrix on the 20 % test; precision and recall for each failure class, since those are the ones that stop a run. It is the software twin of the hardware interrupt from Lab 3, so compare the two on the same curves: which fires first, and which is right. If the classifier is trivially perfect, say what the threshold is and why a model was not needed.
11. **Practical result.** One of two sentences with a number: "syringe below 2 ml is detected with X % accuracy and Y false alarms per 100 cycles; replace at that estimate", or "fill level does not change the dose within ±10 %; the recipe uses a fixed pulse and the alarm watches dP/dt". Written in `docs/result.md` and in the recipe.
12. **Deployment.** `models/fill_model.joblib` (or `models/H0.md` stating there is nothing to deploy for fill), `models/dispense_model.joblib`, the feature function, and `models/README.md` with the input format (the curve columns `t_ms, p_kpa`) and the output (ml, or the class among normal / clogged / empty). The Smart Solutions Flask app loads them and shows the estimate for the last live curve.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: the feature function is the same everywhere

Run the feature function on ten stored curves in the notebook and on the RPI. The feature rows are identical to 4 decimal places. A difference means two copies of the function exist; there must be one.

#### Test Example 2: the model answers on a live curve

On the RPI, run one dispense. Within 1 s of `dispense_end` the app shows a fill estimate (or, under H0, the pick result only) for that curve, and the value is within the model's test MSE of the current scale reading. Screenshot with the timestamp.

#### Test Example 3: pick classifier on a known failure

Empty source slot, one pick attempt. The classifier returns failure with probability above 0.9; with a glass in the slot, success above 0.9. Five of each.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* `data/scale_proof.csv` with ten weighed dispenses at each of two fill levels (twenty more with compensation if H1), photographed scale readings in `docs/scale/`
* `notebooks/lab5_model.ipynb` with the model table, the three comparison tables (features, signal quality, 4 × 4 between teams), residual plots and the written H1/H0 decision
* `models/dispense_model.joblib` with its confusion matrix on held-out data; `models/fill_model.joblib` or `models/H0.md`
* Screenshot or short video of the RPI Flask app returning a result for a live curve (Test Example 2)
* `docs/result.md` with the practical sentence and its number
* The recipe JSON in the repo with the compensation table present (H1) or the field removed (H0), with the commit that did it

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Repo: `models/` (joblib files, feature function, `README.md`, `compensation.csv` if H1), `data/scale_proof.csv`, `docs/result.md`. The updated recipe goes to the Smart Solutions workflow JSON. The fill estimate and the pick probability become fields on the `cycle` record from Prototyping M3 onward; propose the two column names in `models/README.md`.

### Safety

The scale proof and the live-curve test run the robot and dispense resin: the Lab 4 rules apply (a person at the emergency stop, gloves, tip caps, cured waste only). No UV work in this task.

### Components for the next lab

Nothing. The next order date (06.01.27) covers spares only, and the semester-2 integration list is handed out on 16.01.27 with Prototyping Milestone 1.

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| — | — | Semester-2 list handed out on 16.01.27 |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — feature function, training notebook, exported models, `models/README.md` with the input and output format | 5 p |
| Analysis — model table, three comparisons, grouped split, residuals, H1/H0 decision with the rule stated before the scale test | 5 p |
| Prototype — scale proof at two fill levels, live curve answered on the RPI, pick classifier on real failures | 5 p |
| Documentation — `result.md` with the number, recipe updated, cross-team transfer explained, `AGENTS.md` | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `data-acquisition-lab5` 72 h before the defense.**

The defence is online on 19.01.27. The tag deadline is 72 h before it, which is Saturday 16.01.27 — the same weekend as the contact session where the next lab is handed out. Anything that has to be shown live, the robot moving or a print or a measurement, has to be visible on the call, so join from the lab.

The tagged repo must contain, under `data-acquisition/lab5/`:
* `src/` — feature extraction, training script, the RPI-side loader
* `data/` — `scale_proof.csv`, references to the Lab 4 data and the bucket query used
* `notebooks/lab5_model.ipynb` with outputs
* `models/` — `dispense_model.joblib`, `fill_model.joblib` or `H0.md`, `compensation.csv` if H1, `README.md`
* `docs/` — `result.md`, scale photos, screenshot of the live estimate
* `AGENTS.md` updated so an agent can retrain and redeploy

At the defense: 5 min presentation, 10 min questions, one live change requested on the spot, for example: retrain without the Fourier features and report the new test R², or run a pick on an empty slot and show the classifier's output in the app.

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
* The three or four numbers this lab produced, with units:
* What we would do differently if we started again on day one:
* What the next lab should know before it starts:

### Feedback

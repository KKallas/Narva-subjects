## Data Acquisition: Lab 4 — Data collection with the MG400

**Workload:** 24 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 14.11.26 | **Order date:** 24.11.26 | **Defense:** 08.12.26, online

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the lab folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

The tool now has two sensors on op-amp + filter, a dP/dt alarm, nozzle calibration and, when the boards arrive, the tool PCB. The MG400 becomes a data factory: it runs the assembly cycle hundreds of times with different parameters and writes one record per cycle. This dataset is what Lab 5 trains on and what the other three teams' models are tested against, so the record format is the shared one from Smart Solutions L4 and every row carries its ground truth.

The bulk of the dataset consumes nothing. Dispensing goes into the waste cup, so no tag is glued. Pick and place recirculate the same five dummy polycarbonate glasses between the source slots and the finished slots: after five cycles the trays swap roles in software, and the 5 + 5 tray supports unlimited cycles without a human. A human is needed only to weigh the syringe every 25 cycles.

Two ground-truth methods for the fill level are accepted; each record says which one it used. The pick-success label comes from the nozzle camera frame after the lift, by a written deterministic check, since the cup has no sensor. A small side dataset, 5 cure times × 5 glued glasses pulled off with the MG400, fixes the cure time in the recipe. That table is a number the team cannot write from a chair.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* Data Acquisition L3: the tool board (or the breadboard with the L3 firmware) streaming the JSON samples and events; the alarm; the Z calibration.
* Smart Solutions L1: the RPI station on the base MG400 package, teach/save/replay.
* Smart Solutions L4: the shared InfluxDB bucket, the cycle record schema, the workflow recorder.
* 3D Print L1: syringe and LED holder on the lifting nozzle. 3D Print L2: tray (5 + 5 slots), gluing jig, waste-cup holder, VL53L0X post, registration numbers.

**Gives to**
* Data Acquisition L5: `data/cycles.csv`, `data/curves/`, `data/images/`, the cure table, the weighed-dose subset. All four teams' datasets are in the same bucket.
* Smart Solutions L4–L5: 500+ real records in the portal, the pick label used for retry logic.
* Prototyping: the recipe (tip, pressure, pulse, cure time) as measured.

### Background Information

* pandas (read_csv, merge, groupby, corr, describe): https://pandas.pydata.org/docs/
* `scipy.fft` for the per-curve spectrum: https://docs.scipy.org/doc/scipy/reference/fft.html
* `scipy.signal` (find_peaks for the plateau, welch): https://docs.scipy.org/doc/scipy/reference/signal.html
* pyserial documentation: search "pyserial readline documentation".
* Base MG400 package: README and `AGENTS.md` in the package repo (URL in the MS Teams channel); MovJ, MovL, DO, stop.
* Dobot MG400 TCP/IP protocol (ports 29999 and 30003): search "Dobot TCP-IP protocol MG400 dashboard 29999".
* Design of experiments, randomized blocks: search "randomized block design confounding explained".
* MPX5100DP datasheet for the plateau limits: https://www.nxp.com/docs/en/data-sheet/MPX5100.pdf

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. MG400 with the pump box, suction cup φ13 or φ16, 3/2 valve
2. Tool PCB (or the Lab 3 breadboard with ESP32-A) with both sensors, VL53L0X, UV LED channel
3. RPI control station with the base MG400 package, pyserial, MQTT to the shared InfluxDB
4. Nozzle camera (MJPEG over WiFi)
5. Tray 5 + 5, gluing jig, waste cup, five dummy PC glasses, VL53L0X post
6. Amber syringes 10 ml, tips at the Gate A size, tip caps, 405 nm resin
7. Digital scale 0.01 g; a hanging scale or the 3D Print L2 tensile fixture for pull-off
8. 405 nm goggles, nitrile gloves, IPA
9. Python 3, Jupyter Lab, pandas, scipy, matplotlib
10. git

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Copy `lab3/` to `lab4/`; the cycle script starts from the base MG400 package and the L3 stream reader
- [ ] Waypoints taught and saved: waste cup, five source slots, five finished slots, camera pose, VL53L0X post
- [ ] Cycle script: parameters in → one cycle → one record out (CSV row, curves, image) → published to the shared database
- [ ] Recirculation: after five cycles source and finished swap; 20 cycles unattended with a person in the room
- [ ] Parameter grid: 5 speeds × 5 pressures × 20 repetitions, randomized within blocks of 25
- [ ] Ground truth: scale reading every 25 cycles (method a) or counted dispenses at a weighed mean dose (method b); the weighed-dose subset every 25th cycle onto the scale pan
- [ ] Pick label rule from the camera frame after the lift; at least 25 deliberate dispense failures (15 clogged tip, 10 empty syringe) in the dataset
- [ ] Signal-quality subset: 50 cycles logged in parallel with the raw config 1 path
- [ ] Cure side dataset: 5 cure times × 5 glasses, pull-off force
- [ ] Notebook: cleaning, correlation, distributions, outliers, response time vs. fill, Fourier vs. fill
- [ ] ≥ 500 records in the shared database and in the repo
- [ ] Tag `data-acquisition-lab4` 72 h before 08.12

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

### Analysis

Notebook `notebooks/lab4_dataset.ipynb`, run with outputs before commit.

1. **The cycle.** Waste-cup cycle: move to the waste cup → pump blow → `dispense` for `dispense_ms` → pressure curve sliced from `dispense_start` − 200 ms to `dispense_end` + 800 ms → move to source slot i → pump suction → lift → camera frame for the pick check → place in finished slot i → blow-off → camera pose, image → record. `cure_s` is 0 in waste-cup cycles; the UV LED is used only in the cure side dataset.
2. **Parameter grid, 500 cycles.** Speeds 20 / 40 / 60 / 80 / 100 % of the MG400 speed setting. Pressures 20 / 40 / 60 / 80 / 100 kPa, set at the pump box and verified as the syringe-branch plateau. `dispense_ms` and `tip_mm` are the Gate A recipe values and are constant. The 25 combinations are shuffled within every block of 25 cycles, so the fill level, which falls with the cycle count, is not confounded with pressure or speed. State the block order in the notebook.
3. **Ground truth for fill level.** Method (a): every 25 cycles the robot parks, the syringe is swapped out one-handed, weighed on the 0.01 g scale, swapped back. `fill_ml_estimate = (m − m_empty) / ρ`, ρ measured by the team by weighing 5 ml of resin. Between weighings the estimate is interpolated by cycle count. Method (b): `fill_ml_estimate = V_full − n · dose_mean`, with `dose_mean` from 20 weighed dispenses at the recipe. Every record carries `fill_method` and `fill_ml_estimate`; the weighed-dose subset (every 25th cycle dispensed onto the scale pan instead of the waste cup) carries `dose_mg`. Compare the two methods on the same syringe: how far apart are they after 100 cycles?
4. **Labels.** `pick_ok = 1` when the camera frame taken after the lift shows the glass under the cup — a written, deterministic check, not a model. Score 50 frames by hand as well and report the agreement in a 2 × 2 table; that disagreement rate is the noise floor of every pick number in this dataset. Separately, at least 25 deliberate dispense failures — 15 with a tip left to cure shut, 10 with the syringe run empty — so the Lab 5 classifier has all three classes.
5. **Derived columns.** `response_ms` (dispense start to 90 % of plateau), `dpdt_max`, `plateau_kpa`, `auc` (kPa·s over the dispense window), `z_mm` from the VL53L0X at the start of each block. Definitions written once in `docs/features.md`, shared with Lab 5.
6. **Cleaning.** Duplicated cycle ids, curves shorter than the window, samples with gaps above 20 ms, alarms. What is dropped and why; count before and after.
7. **Correlation and distributions.** Correlation matrix of the scalar columns. Histograms of `response_ms`, `plateau_kpa`, `dpdt_max` per pressure setpoint. Outliers by the 1.5 IQR rule, listed with cycle ids and, where possible, a cause (weighing pause, alarm, empty slot).
8. **Response time vs. fill level.** Scatter with the setpoint as colour. Does the curve change with fill at all at this viscosity? This is the first look at H1/H0; it is not the decision, Lab 5 makes that with the scale. A null result here is graded the same as a dependence.
9. **Fourier vs. fill level.** Spectrum of the dispense curve at full, half and near-empty syringe, same setpoint. Dominant frequency, spectral energy, shape. Does anything move?
10. **What else moves the curve.** Temperature if measured (write the room temperature per block at minimum), tip diameter (one block with the second tip size), setpoint. One figure per factor.
11. **Cure side dataset.** Five glasses per cure time at 3 / 5 / 10 / 20 / 40 s, glued on scrap PC squares with the recipe dose, LED at 30 mm. Pull-off with the MG400 pulling through a hanging scale or the 3D Print L2 fixture at 5 mm/s; peak force in N. `data/cure_pulloff.csv`: `tag_id, cure_s, dose_mg, pull_off_N, failure_mode`. Plot force vs. cure time and pick the recipe value with a margin.
12. **Signal-quality subset.** 50 cycles (two setpoints × 25) where the MPX5100DP is also read by ESP32-A on the breadboard as config 1 (sensor direct to ADC, teed into the same line). Curves in `data/curves_raw/<cycle_id>.csv`, marked `config1` in `notes`. Lab 5 comparison 2 uses this subset.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: one cycle, one record

Run one cycle. Exactly one new row in `cycles.csv`, one curve file with `t_ms, p_kpa` of 100 ± 5 samples per second over the window, one image, and the same row visible in the shared database within 10 s. Run it after every script change.

#### Test Example 2: 20 cycles unattended

20 cycles with recirculation, nobody touching the cell. Five glasses end where they started, zero alarms, 20 records, `pick_ok = 1` on all 20 with the image confirming it. If a glass is dropped, the tray registration or the pick pose is wrong; fix before running 500.

#### Test Example 3: ground truth agrees

Method (a) and method (b) on the same syringe over 100 cycles differ by under 0.5 ml at the end. A larger gap means the mean dose drifted; the weighed subset shows when.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* `data/cycles.csv` with ≥ 500 rows in the schema below, every row with `fill_ml_estimate` and `fill_method`, ≥ 25 rows with `pick_ok = 0`, ≥ 20 rows with `dose_mg`
* `data/curves/<cycle_id>.csv` for every row and `data/images/<cycle_id>.jpg` for every row; the same records in the shared InfluxDB bucket with the team tag
* `data/cure_pulloff.csv` with 25 rows and the chosen cure time written in the recipe
* `data/curves_raw/` with the 50-cycle config 1 subset
* Scale readings as photographed numbers in `docs/scale/` for every weighing
* Video in `docs/` (or a link in the README) of 20 unattended cycles with recirculation
* `notebooks/lab4_dataset.ipynb` with the cleaning counts, correlation matrix, response time vs. fill, Fourier vs. fill

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

`data/cycles.csv`, one row per cycle:
```
cycle_id, team, timestamp_utc, workflow_id, robot_speed_pct, pump_setpoint_kpa, dispense_ms, cure_s, tip_mm,
syringe_ml_nominal, fill_ml_estimate, fill_method (scale|count), dose_mg (if weighed, else empty),
pick_ok (0|1|empty), dispense_ok (0|1), clog_alarm (0|1), z_mm, response_ms, dpdt_max, plateau_kpa, auc,
image_file, notes
```
Curves in `data/curves/<cycle_id>.csv` (`t_ms, p_kpa`), images in `data/images/<cycle_id>.jpg`. InfluxDB: measurement `cycle` with tags `team`, `robot`, `workflow_id` and the scalar columns as fields; measurement `sample` with tag `cycle_id` and fields `p_kpa`, `valve`, `uv` at 100 Hz. Same bucket for all four teams. The CSV in the repo is mandatory; the database copy is the shared one.

### Safety

* **Robot running unattended.** Unattended means nobody is touching the cell, not that nobody is in the room: one team member stays within reach of the MG400 emergency stop for the whole run. The first 25 cycles of any new workflow run at 25 % speed. Tubes and the USB cable are routed so no arm pose pulls them. The script stops on any alarm, on a lost MG400 connection (2 s silence) and on a lost tool-board stream, and leaves the pump off and the valve unpowered. Hands never go into the tray while the program is running; the weighing pause is a parked robot with the program waiting for a keypress.
* **UV.** The LED is used only in the cure side dataset, with the shroud fitted, goggles rated for 405 nm on everyone at the table, and the `pose_ok` interlock in place. Never look into the cone, including the reflection off the polycarbonate.
* **Resin.** Nitrile gloves when handling syringes, tips and glued glasses. Tip cap on whenever the syringe is off the robot; a tip left open in daylight is the Lab 3 clog case. IPA for cleanup. Only cured waste into the bin; the waste cup is cured under the LED before emptying.

### Components for the next lab

Order goes out on 24.11.26. Quantities per team. Lab 5 is analysis; only consumables.

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| Blunt tips, recipe size | 10 | Spares for the Lab 5 scale-weighed dispenses |
| Resin refill | 1 | 405 nm transparent |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — cycle script on the base package, stream reader, recirculation, database publish, CSV and curves of the stated shape | 5 p |
| Analysis — cleaning counts, correlation, outliers with causes, response time and Fourier vs. fill, cure table | 5 p |
| Prototype — 500 cycles run, 20 unattended on video, both ground-truth methods on one syringe, pull-off measured | 5 p |
| Documentation — `features.md`, block order and room conditions, scale photos, `AGENTS.md` telling an agent how to run a block | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `data-acquisition-lab4` 72 h before the defense.**

The defence is online on 08.12.26. The tag deadline is 72 h before it, which is Saturday 05.12.26 — the same weekend as the contact session where the next lab is handed out. Anything that has to be shown live, the robot moving or a print or a measurement, has to be visible on the call, so join from the lab.

The tagged repo must contain, under `data-acquisition/lab4/`:
* `src/` — cycle script, stream reader, feature extraction, database publish
* `data/` — `cycles.csv`, `curves/`, `curves_raw/`, `images/`, `cure_pulloff.csv`
* `notebooks/lab4_dataset.ipynb` with outputs
* `docs/` — `features.md`, block plan, scale photos, video link, workflow JSON used
* `AGENTS.md` updated so an agent can run one block of 25 cycles

At the defense: 5 min presentation, 10 min questions, one live change requested on the spot, for example: run five cycles at a setpoint not in the grid and show the five new rows in the database, or change the pick slot order and show the recirculation still closes.

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

## Data Acquisition: Lab 2 — Op-amp and filtering, Fourier shows the difference

**Workload:** 30 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 03.10.26 | **Order date:** 13.10.26 | **Defense:** 27.10.26, online

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the lab folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

The MPX5100DP output is 0.2–4.7 V. The ESP32 ADC reads 0–3.3 V, non-linearly above about 2.5 V, and the pin is not 5 V tolerant. Lab 1 stopped at 60 kPa for this reason. Lab 2 adds a signal chain so that the full 0–100 kPa lands inside the ADC range, and uses Fourier to show what each step of the chain does to the noise measured in Lab 1.

Same breadboard, same logger, four configurations. The team reconnects wires between them; nothing else changes, so the four spectra are comparable. Config 1 is the Lab 1 wiring (sensor direct to ADC). Config 2 is a voltage divider. Config 3 is an LM358N op-amp stage that subtracts the 0.2 V offset and scales 4.7 V to 3.2 V. Config 4 is config 3 plus digital filtering in the firmware: a moving average, a median and oversampling with decimation, each with its own spectrum.

There is one pressure sensor in this cell and it is on the syringe branch. The suction cup is not instrumented — a pick is judged by the nozzle camera and by whether the glass ended up where it should. So this lab conditions one signal well rather than two adequately, and the acceptance item is the curve of one real valve switch: pump to blow, valve to the syringe, pressure rises, valve back to the cup, pressure falls. That rising edge is what Lab 3 puts a derivative threshold on and what Lab 5 learns the dispense from.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* Data Acquisition L1: breadboard, ESP32-A, the 100 Hz logger, the CSV format, the Lab 1 spectra (config 1 is Lab 1 re-measured).
* Smart Solutions L1: the station switching the pump box to suction / blow and the valve between the branches, so a real pressure edge exists to measure.
* 3D Print L1 (if ready): the syringe holder on the lifting nozzle, so the syringe branch can be teed to the sensor on the arm.

**Gives to**
* Data Acquisition L3: both sensors on the op-amp stage; the filtered signal is what the dP/dt derivative is computed from.
* Data Acquisition L4: two sensors on op-amp + filter on the breadboard, the fallback if the PCB is late.
* Smart Solutions L2: the two kPa values (`p`, `v`) that the tool-board JSON carries.

### Background Information

* LM358 product page and datasheet (single-supply, output swing, GBW): https://www.ti.com/product/LM358
* MPX5100DP datasheet: https://www.nxp.com/docs/en/data-sheet/MPX5100.pdf
* Falstad circuit simulator (op-amp with offset reference and gain): https://www.falstad.com/circuit/circuitjs.html
* ESP32 ADC attenuation and non-linearity: https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
* `scipy.signal` (welch, lfilter for the moving-average model): https://docs.scipy.org/doc/scipy/reference/signal.html
* `scipy.fft`: https://docs.scipy.org/doc/scipy/reference/fft.html
* pandas: https://pandas.pydata.org/docs/
* Differential amplifier with a reference voltage, one resistor formula: search "op-amp differential amplifier level shift single supply".
* Common-mode rejection ratio explained: search "CMRR differential amplifier ground noise".
* Moving average as a low-pass filter, its frequency response: search "moving average filter frequency response sinc".

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. M5 Atom Lite (ESP32-A), the Lab 1 logger
2. MPX5100DP ×2 (one in use, one spare) — the cell's only pressure sensor
3. LM358N ×5, resistor and capacitor kit, two breadboards, jumper kit
4. MG400 pump box, 4 mm tube, T-pieces, suction cup φ13 or φ16, polycarbonate glass
5. Oscilloscope (two channels: sensor output and op-amp output)
6. Multimeter
7. Arduino IDE, Python 3, Jupyter Lab, scipy, pandas, matplotlib
8. Falstad
9. git

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Copy `lab1/` to `lab2/`; the logger gets a `config` column
- [ ] Falstad: divider vs. op-amp stage, with a 50 mV common-mode noise source on the sensor ground; choose resistor values
- [ ] Config 2: divider so that 4.7 V → 3.2 V (for example 10 kΩ / 22 kΩ); measure with the scope at 0 and 100 kPa
- [ ] Config 3: LM358N differential stage, reference 0.2 V from a divider, gain 3.2 V / 4.5 V ≈ 0.71; measure with the scope at 0, 50, 100 kPa
- [ ] Config 4: moving average N = 10 in the Arduino code, `adc_f = sum(last 10) / 10`, logged next to the raw value
- [ ] Same pump-box pulse, 30 measurements per configuration, 120 rows in one CSV
- [ ] 15 valve switches logged end to end: pump to blow, valve to syringe for 2 s, valve back to cup
- [ ] One real pick with the MG400 logged end to end (approach, seal, lift, release)
- [ ] Notebook: four-way comparison, SNR table, the valve-switch curve
- [ ] Oscilloscope screenshots of all four configurations at the same pulse
- [ ] Tag `data-acquisition-lab2` 72 h before 27.10

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

### Simulation

Two Falstad circuits, saved in `docs/`:

1. **Divider.** Sensor as a voltage source 0.2–4.7 V with 50 mV of 50 Hz noise in series with its ground return. Divider to 3.2 V full scale. Observe: the noise is divided by the same ratio as the signal; the ratio of signal to noise does not change.
2. **Op-amp stage.** LM358 model (or the generic op-amp), single supply 5 V. Non-inverting input from the sensor, inverting input referenced to 0.2 V from a divider, gain set to 0.71 by the feedback pair. Put the 50 mV noise on the ground of both inputs (common mode) and watch it disappear at the output; put it on one input only (differential) and watch it pass. This is CMRR. Record the resistor values that give 0.2 V → 0.00 V and 4.7 V → 3.2 V and use them on the breadboard.

Then compare: simulated output at 0 / 50 / 100 kPa vs. multimeter reading on the real stage. Deviations above 50 mV mean the 0.2 V reference is off; measure it.

### Analysis

Notebook `notebooks/lab2_comparison.ipynb`, run with outputs before commit.

1. **Calibration per configuration.** For each configuration derive the formula from ADC to kPa: config 1 as in Lab 1; config 2 divides by the ratio; config 3 inverts the op-amp stage (`Vin = Vout / G + 0.2 V`) and then applies the sensor transfer function. Check each formula at two points against the multimeter.
2. **The same pulse, 4 × 30.** The pump box in blow mode for 1 s into a closed 10 ml syringe (plunger fixed), then off. That pulse is the unit. 30 pulses per configuration, 5 s at 100 Hz each, all in `data/lab2_pulses.csv` with columns `meas_id, config, pulse_nn, t_ms, adc_raw, adc_filtered, p_kpa`. 120 measurements. Configurations are wired one after the other on the same afternoon; write the order and the room conditions in the notebook.
3. **Valve switches, 15 of them.** Pump to blow, valve to the syringe branch for 2 s, valve back to the cup: 15 records in `data/lab2_switch.csv` (`meas_id, t_ms, adc_raw, adc_filtered, p_kpa`) with a `phase` column (idle, rising, plateau, falling). Report the 10–90 % rise time of the pressure edge in each configuration — it is the number Lab 3's derivative threshold has to live above.
4. **Time domain side by side.** One pulse per configuration on one figure, same axes, kPa. Rise time (10–90 %) and the plateau value per configuration. Does the divider or the op-amp change the plateau? It should not; if it does, the calibration is wrong.
5. **Four spectra side by side.** Welch over the 5 s window, same axes, amplitude in kPa. Mark the Lab 1 peaks. Which peaks survive the divider, which are reduced by the op-amp (common mode), which are removed by the moving average, and which remain because they are below the filter cutoff? The moving average with N = 10 at 100 Hz has its first null at 10 Hz and −3 dB at about 4.4 Hz; compute this and show it on the spectrum.
6. **SNR table.** Signal = plateau minus baseline (kPa). Noise = standard deviation of the last 2 s of the plateau (kPa). SNR in dB. Table: `config | amplitude kPa | noise kPa | SNR dB | noise floor Pa`. Also the effective resolution: noise in LSB × Pa/LSB from Lab 1, recomputed for each configuration's gain.
7. **Filter cost.** The moving average delays the signal by (N − 1) / 2 samples = 45 ms. Show it on the step. Lab 4 and Lab 3 must know this number: it is part of the dP/dt alarm latency.
8. **Vacuum curve analysis.** For the 30 vacuum pulses: time to reach −50 kPa, plateau value, leak rate after the pump is off (kPa/s). For the real pick: mark the seal moment on the curve. State in one sentence what "pick succeeded" looks like on this curve; that sentence becomes the Lab 4 label rule.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: stage does not clip

Pump box at 100 kPa on the syringe branch. Op-amp output measured with the scope is 3.2 V ± 0.15 V and the ADC reads 3900–4050. At 0 kPa the output is under 0.05 V and the ADC reads under 60. If the top is flat at 3.5 V, the LM358 is at its single-supply swing limit; lower the gain.

#### Test Example 2: same pulse, same plateau

The plateau of the 1 s pulse, in kPa, is the same within ±3 % for configurations 1, 2, 3 and 4 after calibration. A configuration that reads a different pressure has a formula error, not a physics difference.

#### Test Example 3: filter delay

Step the pressure with the pump. The filtered column reaches 50 % of the step 45 ± 10 ms after the raw column does. If the delay is 0 ms, the filter is not running on the stream; if it is over 100 ms, N is wrong.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* `data/lab2_pulses.csv` with 120 measurements (4 configurations × 30) of the same pump-box pulse, raw and filtered columns
* `data/lab2_vacuum.csv` with 30 vacuum pulses and `data/lab2_pick.csv` with one real MG400 pick, seal moment marked in the notebook
* Four spectra side by side from the same pulse and the SNR table (config × amplitude × noise × SNR) in `notebooks/lab2_comparison.ipynb`
* Four oscilloscope screenshots in `docs/`, one per configuration, same pulse, same time base
* Multimeter check of the op-amp stage at 0 / 50 / 100 kPa written in `docs/README.md` next to the resistor values used
* Falstad exports for the divider and the op-amp stage

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Repo only. The `p` and `v` conversion formulas from this lab are written into `docs/interface.md` in the form Smart Solutions L2 needs (ADC → kPa for each branch).

### Components for the next lab

Order goes out on 13.10.26. Quantities per team.

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| VL53L0X breakout | 2 | I2C distance sensor for nozzle Z calibration; one spare |
| LM393 | 2 | Dual comparator, DIP-8, dP/dt Schmitt trigger |
| 100 Ω resistor | 4 | Series on SDA and SCL, two spare |
| 100 pF capacitor | 4 | To ground on SDA and SCL, two spare |
| Twisted / shielded 4-wire cable, 50 cm | 1 | The long I2C run alongside the MG400 cables |
| JST connector set | 1 | Sensor and cable ends; the same family goes on the PCB |
| KiCad or Fusion 360 Electronics | — | Free; installed before 24.10 |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — Arduino code with moving average, logger with config column, CSVs of the stated shape | 5 p |
| Analysis — four-way comparison, SNR table, filter delay, the valve-switch curve with its rise time | 5 p |
| Prototype — op-amp stage measured at three points, both sensors on it, scope screenshots, real pick logged | 5 p |
| Documentation — resistor values with justification, Falstad exports, `docs/interface.md`, development log | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `data-acquisition-lab2` 72 h before the defense.**

The defence is online on 27.10.26. The tag deadline is 72 h before it, which is Saturday 24.10.26 — the same weekend as the contact session where the next lab is handed out. Anything that has to be shown live, the robot moving or a print or a measurement, has to be visible on the call, so join from the lab.

The tagged repo must contain, under `data-acquisition/lab2/`:
* `src/` — Arduino sketch with the moving average and both conversions, Python logger
* `data/` — `lab2_pulses.csv`, `lab2_vacuum.csv`, `lab2_pick.csv`
* `notebooks/lab2_comparison.ipynb` with outputs
* `docs/` — schematic of the op-amp stage with values, four scope screenshots, Falstad exports, `interface.md`, README
* `AGENTS.md` updated for the new configurations

At the defense: 5 min presentation, 10 min questions, one live change, for example: change N to 4 and show the new spectrum, or move the vacuum sensor to the syringe branch and show the reading make sense within 3 minutes.

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

## Data Acquisition: Lab 1 — The device, and the first signal

**Workload:** 32 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 12.09.26 | **Order date:** 22.09.26 | **Defense:** 06.10.26, online

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the lab folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

This course owns the small computer on the tool. By the end of the year it is a board on the robot's arm that samples two pressure sensors, shuts a valve in one sample when a tip clogs, and feeds a model that says how much resin is left. It starts here as an AtomS3 on the bench, and the first thing it does is not measure anything: it is a WiFi access point with a captive portal, it shows a picture you uploaded on its 0.85" screen, and it loops through the alphabet until you press the letter you want. That letter goes out to the Smart Solutions team, who move the robot, and the 3D Printing team's pen holder draws it. Three courses, one demo: **press a letter, the robot draws it.**

The second thing it does is measure. The MPX5700AP from the old box, wired straight to the ADC, nothing in between — no divider, no op-amp, no filter. Sampled at 100 Hz, one line per sample over UART, logged to CSV by your own Python. The signal is noisy and the sensor's range is wrong for a 0–110 kPa cell: it uses about 15 % of its span, and the analysis asks what that does to the resolution in pascals per ADC step. That is deliberate. Lab 2 fixes the signal chain, and the fix is only visible if the raw case has been measured and kept. The right sensor, the MPX5100DP, goes on the order on 22.09 and arrives before the defense; you repeat the measurements on it and compare. That one sensor, on the syringe branch, is the only pressure sensor this cell ever gets: the suction cup is judged by the nozzle camera and by whether the glass ended up where it should, not by a sensor of its own.

Before any of it, the first session is the bench: breadboard rows and rails, which parts in the kit are passive and which are active, reading a pinout from a datasheet, and the multimeter — voltage, resistance, continuity. Nothing is soldered in this lab. Everything is on a solderless breadboard, so a wiring mistake costs a jumper wire, not a sensor. Soldering arrives with the tool PCB later in the year.

There are no new parts on day one, and that is not a reason to wait. Draw the circuit in Falstad, build it from the shelf, measure it, and only then write the order — real part numbers, stock checked, one line per part saying which simulation or measurement asked for it.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* Shelf hardware: AtomS3 units, MPX5700AP, breadboards, passive kits, multimeters, syringes and 4 mm tube, the pump box.
* Smart Solutions L1: the channel that carries the letter from the Atom to the station — agree its shape with them in week one. From week two, their station switching the pump box to suction and blow, so you have a second pressure source.
* 3D Printing L1: nothing needed. The three-stop syringe clamp arrives in their Lab 3; until then the syringe is held by hand.

**Gives to**
* Smart Solutions L1: the letter, as one message on the agreed channel — for example one JSON line `{"letter":"A"}` — every time the button is pressed.
* Data Acquisition L2: the breadboard, the 100 Hz logger, the CSV format and the first spectra. L2 reconnects wires on the same board and compares against these files.
* Data Acquisition L3: the Atom firmware, which grows into the tool board.

### Background Information

* **AtomS3 documentation** (pinout, ADC-capable pins, the 0.85" 128×128 display, the button): https://docs.m5stack.com/en/core/AtomS3
* **ESP32 as an access point with a captive portal**: search phrase "ESP32 Arduino captive portal DNSServer WiFi AP". The trick is answering every DNS query with your own address.
* **Images on the display**: search phrase "AtomS3 M5GFX draw image RGB565 128x128". Work out how many bytes one picture is before you write the upload.
* **MPX5700AP datasheet** (transfer function, 15–700 kPa absolute, 5 V supply): https://www.nxp.com/docs/en/data-sheet/MPX5700.pdf
* **MPX5100DP datasheet** (0–100 kPa differential, 0.2–4.7 V output): https://www.nxp.com/docs/en/data-sheet/MPX5100.pdf
* **ESP32 ADC in Arduino**: attenuation, 12-bit range, non-linearity near 0 V and above about 2.5 V: https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
* **ESP32 UART in Arduino** (Serial at 115200): https://randomnerdtutorials.com/esp32-uart-communication-serial-arduino/
* **Falstad circuit simulator**: https://www.falstad.com/circuit/circuitjs.html
* **`scipy.fft`** (rfft, rfftfreq, windowing): https://docs.scipy.org/doc/scipy/reference/fft.html
* **`scipy.signal`** (welch, periodogram): https://docs.scipy.org/doc/scipy/reference/signal.html
* **pandas**: https://pandas.pydata.org/docs/
* **Nyquist and aliasing**, one page with pictures: search phrase "aliasing sampling theorem explained".
* **Boyle's law with a trapped gas volume** (`p1 · V1 = p2 · V2` in absolute pressure): search phrase "Boyle's law syringe trapped air absolute pressure".
* **Dobot MG400 mini vacuum pump box**: search phrase "Dobot MG400 vacuum pump box IO control".
* **Mouser**: https://www.mouser.ee — part search, datasheet links, package and stock. The order list is written here.

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. AtomS3 ×2 per team, USB-C cables
2. MPX5700AP (12.09), MPX5100DP (after the 22.09 order)
3. Solderless breadboard, jumper wire kit, pin headers, resistor/capacitor kit
4. Multimeter (voltage, resistance, continuity)
5. Oscilloscope with FFT function
6. 10 ml syringe, 4 mm tube, T-piece; the pump box from week two through the Smart Solutions station
7. Arduino IDE or PlatformIO with the ESP32 board package
8. Python 3, Jupyter Lab, numpy, pandas, scipy, matplotlib
9. Falstad circuit simulator
10. Mouser catalogue for the 22.09 order list
11. Git, one repo per team with `AGENTS.md` at the root

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Bench session done: breadboard rows and rails understood, passive kit sorted, multimeter checked against a known resistor and against the 5 V rail
- [ ] Repo created from the template, instructor has read access, URL posted in MS Teams, this file copied in as `README.md`
- [ ] Atom as an access point: a phone joins `team-N-tag` and the browser opens the portal page by itself
- [ ] Image upload: pick a file on the portal page, it appears on the 0.85" screen
- [ ] Letter chooser: the screen loops the alphabet; the button picks the letter showing and sends one message on the channel agreed with Smart Solutions
- [ ] MPX5700AP on the breadboard: 5 V, GND, Vout → ADC pin; supply and output checked with the multimeter before the Atom is connected
- [ ] Firmware: every 10 ms → read ADC → send one line `t_ms,adc` over UART at 115200, from a timer or a scheduled deadline, not from a fixed wait after each send
- [ ] Python logger: reads the UART stream, writes CSV with `t_ms, adc`
- [ ] Hand-syringe measurements: 10 × 3 levels with the MPX5700AP
- [ ] Pump-box measurements (week two): 10 × 3 with the pump box as the source
- [ ] MPX5100DP arrives: same wiring, 30 × 3 — this is the dataset that Lab 2 compares against
- [ ] Falstad model of the sensor → ADC path with a noise source
- [ ] Notebook: time domain, Fourier, Pa/LSB for both sensors
- [ ] Oscilloscope screenshot of the raw sensor output with the pump box running
- [ ] Lab 2 order list written as Mouser part numbers in `docs/bom_lab2.md`, ready for 22.09
- [ ] Tag `data-acquisition-lab1` 72 h before 06.10

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

### Simulation

Build the sensor → ADC path in Falstad: a voltage source for the sensor output (0.2–4.7 V for the MPX5100DP, about 0.7–1.6 V for the MPX5700AP over 0–110 kPa gauge), the sensor's output impedance, the ADC input as a 10 pF sample capacitor with a switch, and an AC source in series that stands for pickup at 50 Hz and at a switch-mode frequency of your choice. Save the circuit as a link or exported text in `docs/`. Every component value you settle on here is what later justifies a line in the order list; the simulation comes before the breadboard and the breadboard before the order.

Two things to see: what the ADC samples when the pickup amplitude is 50 mV, and what happens to the reading above 3.3 V. Compare the simulated noise amplitude in volts with the measured standard deviation converted back to volts. Write the comparison as one table in the notebook: simulated against measured, in mV and in LSB.

### Analysis

All measurements go into `notebooks/lab1_analysis.ipynb`, run with outputs before commit.

1. **The screen budget.** How many bytes is one 128×128 picture in the format the display takes? How long does the upload take over the portal, and what happens when the file is bigger than the device can hold? One short table: format, bytes, upload time, the first thing that fails. This is the first constraint of the year that cannot be argued with.
2. **Pascal scale.** Convert ADC values to pressure with the datasheet transfer function. MPX5700AP: `Vout = Vs · (0.0012858 · P + 0.04)`, P in kPa absolute, Vs = 5 V. MPX5100DP: `Vout = Vs · (0.009 · P + 0.04)`, P in kPa differential. Solve for P. State the ADC full-scale voltage you assume (3.3 V, 12 bit) and check it against the multimeter: Vout at rest with the meter and with the ADC, the difference under 2 %.
3. **Measurements.** Levels: low ≈ 10–20 kPa, medium ≈ 40–50 kPa, high ≈ 90–110 kPa gauge with the pump box. One measurement = 5 s at 100 Hz = 500 samples. Each as `data/raw/<sensor>_<source>_<level>_<nn>.csv` (columns `t_ms, adc`) and one summary `data/lab1_measurements.csv`: `meas_id, sensor, source, level, mean_adc, std_adc, mean_kpa, std_kpa, file`. For the MPX5100DP directly on the ADC: its output reaches 3.3 V at about 69 kPa and the pin is not 5 V tolerant, so cap its high level at 60 kPa and write in the notebook why the full range is a Lab 2 problem.
4. **Time domain.** Per level, sensor and source: mean, standard deviation, min–max, in LSB and in Pa. Plot 5 s of one measurement per level. Is the noise the same at all three levels? The same with the hand syringe and with the pump box?
5. **Fourier.** `rfft` of one 500-sample window per level, `rfftfreq` with fs = 100 Hz, amplitude in LSB. Then `welch` over the full 5 s. List every peak above the floor with its frequency. A hypothesis per peak: MG400 servo drivers, pump box motor, USB supply ripple, ground loop through the laptop charger, mains. Test at least two hypotheses by switching that source off and measuring again. What is the noise floor in LSB and in Pa?
6. **Aliasing.** With fs = 100 Hz nothing above 50 Hz can be seen correctly. Record one 10 s file at 1 kHz (change the firmware constant) and compare its spectrum with the 100 Hz one. Which peaks in the 100 Hz spectrum are aliases? Confirm at least one with the oscilloscope FFT.
7. **Resolution, Pa per LSB.** ADC step = 3.3 V / 4096 = 0.806 mV nominal. Sensitivity from the datasheets: 6.4 mV/kPa for the MPX5700AP, 45 mV/kPa for the MPX5100DP. `Pa/LSB = ADC step / sensitivity`, both numbers. What fraction of the MPX5700AP span does 0–110 kPa use? Multiply the measured noise in LSB by Pa/LSB for both sensors: the noise floor in Pa is what says whether a 2 kPa change is visible. A two-row table; it is an acceptance item.
8. **Linearity against Boyle.** With the syringe at 10, 8, 6, 5 and 4 ml of trapped air, plot mean pressure against volume. The prediction is `p_abs = p0 · V0 / V`, where `V0` includes the dead volume of the tube, T-piece and sensor port. Fit the dead volume from your curve. A deviation is a leak, a wrong dead volume or sensor non-linearity — say which you think it is, and propose how you would check linearity across the full scale with a reference gauge.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: The portal opens by itself

A phone that has never seen the network joins `team-N-tag`. Pass: the portal page is on its screen within 10 s, without anyone typing an address. Test with two different phones; one of them is not yours.

#### Test Example 2: Sample rate is 100 Hz

Log 10 s. The CSV has 1000 ± 5 lines and `t_ms` advances by 10 ± 1 ms with no gap above 20 ms. Run this after every firmware change; formatting and sending the text inside the timing loop is the usual cause of drift, and this test is how you find out whether you did that.

#### Test Example 3: ADC agrees with the multimeter

Sensor at rest, no pressure. Multimeter on Vout reads the datasheet zero-pressure value (about 0.85 V for the MPX5700AP at atmospheric; 0.20 ± 0.05 V for the MPX5100DP). The logger's mean ADC over 5 s, converted to volts, is within 2 % of the meter. Failing this means the full-scale assumption or the attenuation is wrong; fix it before any measurement is kept.

#### Test Example 4: A step is a step

Push the syringe plunger 2 ml in under 0.5 s. The logged pressure rises by the same amount (±10 %) on three repeats, and the rise is visible in under 3 samples. Smeared over 20 samples, something is buffering: the UART, the Python reader or a leaking tube.

#### Test Example 5: The letter arrives

Press the button on the Atom with the letter A showing. Pass: the message for A reaches the Smart Solutions station in under 500 ms, ten times out of ten, measured together with that team from their log. Then press B before their robot has finished A, and write down what happened.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* Video: a phone joins the Atom's network, the portal opens by itself, an image is uploaded and appears on the screen, a letter is chosen with the button.
* The letter message log for Test Example 5, with timestamps from both sides.
* `data/lab1_measurements.csv` with 90 rows for the MPX5100DP and 30 + 30 for the MPX5700AP (syringe and pump box), plus the raw 500-sample files.
* `notebooks/lab1_analysis.ipynb` with outputs: the screen budget, spectra per level, a list of peaks with a hypothesis each, at least two hypotheses tested by switching a source off.
* The Pa/LSB table for both sensors and the noise floor in Pa, as numbers in the notebook and in `docs/README.md`.
* One oscilloscope screenshot in `docs/` of the raw sensor output with the pump box running, with the FFT trace or a time-base note.
* Photo of the breadboard wiring in `docs/`, matching a hand-drawn schematic.
* Multimeter against ADC (Test Example 3) as a one-line result in the notebook.
* `docs/bom_lab2.md`: the Lab 2 order as Mouser part numbers, each line with a link, the package and a one-line reason from the simulation or the measurement.

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Repo only. `data/lab1_measurements.csv`, `data/raw/*.csv`, notebook outputs. Nothing goes to a shared database before Smart Solutions L4.

### Safety

* **Wiring.** USB out of the Atom and the 5 V rail off before any wire is moved. Reversed supply pins kill a pressure sensor in under a second, and the pinout is read from the datasheet, not guessed from the case.
* **Mains.** Only the laboratory's own supplies and the pump box PSU go into wall sockets. No opened supplies on the bench. The breadboard never carries more than 24 V. Check with the multimeter that the 5 V rail is 5 V before the sensor goes in.
* **Pump box.** 110 kPa is a low pressure, but a 4 mm tube popping off a fitting still throws the tube. Push-in fittings must click. Do not point an open tube at anyone.
* **No soldering in this lab.** If someone reaches for the iron, the answer is the breadboard.

### Components for the next lab

Order goes out on 22.09.26. Quantities per team. Every line is turned into a Mouser part number with a link in `docs/bom_lab2.md` before the order date: check the package against the breadboard (DIP-8, not SOIC), check stock, and write in one line which simulation or measurement asks for that part.

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| MPX5100DP | 2 | Syringe branch, 0–100 kPa, 0.2–4.7 V. One in use, one spare — the cell's only pressure sensor |
| LM358N | 5 | Dual op-amp, DIP-8, for the offset + scaling stage; spares for the ones that burn |
| Breadboard | 1 | Second board so the op-amp stage does not crowd the sensor wiring |
| Jumper wire kit | 1 | Male-male, assorted lengths |
| Resistor and capacitor kit | from the shelf | Values chosen in the Lab 2 Falstad simulation |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — Atom firmware (portal, image, letter chooser, 100 Hz sampling), Python logger, CSV files of the stated shape | 5 p |
| Analysis — notebook with the screen budget, time domain, spectra, tested noise hypotheses, Pa/LSB for both sensors | 5 p |
| Prototype — portal opens on a stranger's phone, letter reaches the station, breadboard measured with both sensors and both sources, oscilloscope screenshot | 5 p |
| Documentation — `AGENTS.md`, schematic and photos, Falstad model with comparison, Lab 2 order list as Mouser part numbers, this README | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `data-acquisition-lab1` 72 h before the defense.**

The defence is online on 06.10.26. The tag deadline is 72 h before it, which is Saturday 03.10.26 — the same weekend as the contact session where the next lab is handed out. Anything that has to be shown live, the robot moving or a print or a measurement, has to be visible on the call, so join from the lab.

The tagged repo must contain, under `data-acquisition/lab1/`:
* `src/` — the Atom firmware and the Python UART logger
* `data/` — `lab1_measurements.csv` and `raw/`
* `notebooks/lab1_analysis.ipynb` with outputs
* `docs/` — breadboard schematic (hand-drawn photo is fine), photos, oscilloscope screenshot, Falstad export, `bom_lab2.md`, README with the Pa/LSB table
* `README.md` — this document, filled in
* `AGENTS.md` at the repo root updated so that an agent can flash, log and run the notebook

At the defense: 5 min presentation, 10 min questions. One live change on the spot, for example: change the sample rate to 200 Hz and show the new spectrum; add a symbol to the letter chooser and show it arrive at the station; or swap the sensor and show the reading in kPa within 2 minutes.

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

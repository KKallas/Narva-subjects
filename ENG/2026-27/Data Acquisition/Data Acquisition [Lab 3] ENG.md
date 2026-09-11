## Data Acquisition: Lab 3 — dP/dt derivative, interrupt threshold, I2C calibration and the tool PCB

**Workload:** 24 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 24.10.26 | **Order date:** 03.11.26 | **Defense:** 17.11.26, online (with PCB review; PCBs ordered 17.11.26)

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the lab folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

Three things, one board. (A) A real-time safety mechanism on the pressure derivative: a tip that has cured shut in daylight makes the syringe pressure rise sharply, and the tool must release the valve within one sample and tell the MG400 to stop, without waiting for the RPI. (B) Nozzle calibration: a VL53L0X on the table measures the nozzle Z height, so after a syringe change the system checks its own position, and the lab shows why a 40 cm I2C cable next to the MG400 power cables needs filtering. (C) The tool PCB: everything from Labs 1–3 plus the valve driver, pump-box control and the UV LED channel on one board that implements the command interface frozen in Smart Solutions L2.

Fourier makes Part A mandatory rather than optional. The derivative multiplies every spectral component by 2πf: a 1 LSB ripple at 40 Hz becomes a 250 LSB/s slope. The derivative of the raw Lab 1 signal gives a false alarm every 20 ms; the derivative of the Lab 2 filtered signal works. You show both side by side.

The PCB is reviewed at the defense on 17.11 and ordered the same day; it arrives for Lab 4. No board is ordered without the review. The board's safe state is a measured thing: with the ESP32 unpowered, the vacuum sensor proves the line is on the cup branch, nothing leaves the tip, and the LED enable is low.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* Data Acquisition L2: both sensors on the op-amp stage, the filtered signal, the 45 ms filter delay.
* Smart Solutions L2: the tool-board command interface (JSON below), the 3/2 valve with its MOSFET module, the pump-box control, the camera power need.
* Smart Solutions L1: the base MG400 package `stop` command on port 29999, used by the RPI when the alarm event arrives.
* 3D Print L2: the VL53L0X post and the tray registration numbers; 3D Print L3: the enclosure the board must fit (arm-mounted mass under 250 g).

**Gives to**
* Data Acquisition L4: the tool board (or the breadboard with the same firmware) streaming samples at 100 Hz with `alarm` and `z`.
* Smart Solutions L4–L5: the physical safe state and the alarm event the fault-tolerance work relies on.
* 3D Print L3: board outline, connector positions and mounting holes for the tool enclosure.
* Prototyping: the board that goes into the cell.

### Background Information

* LM393 comparator product page and datasheet (open-collector output, hysteresis with positive feedback): https://www.ti.com/product/LM393
* LM358 (the differentiator stage): https://www.ti.com/product/LM358
* VL53L0X product page, datasheet and API user manual: https://www.st.com/en/imaging-and-photonics-solutions/vl53l0x.html
* ESP32 external interrupts in Arduino: https://randomnerdtutorials.com/interrupts-timers-esp32-arduino-ide-pir-sensor/
* ESP32 I2C in Arduino (bus speed, multiple devices, pull-ups): https://randomnerdtutorials.com/esp32-i2c-communication-arduino-ide/
* Falstad (Schmitt trigger and RC differentiator): https://www.falstad.com/circuit/circuitjs.html
* KiCad (schematic, layout, DRC, Gerber export): https://www.kicad.org/ and https://docs.kicad.org/
* JLCPCB (order, Gerber viewer, capabilities): https://jlcpcb.com/
* Fusion 360 Electronics as the alternative: search "Fusion 360 electronics schematic to PCB tutorial".
* I2C signal integrity on long cables: search "I2C long cable rise time series resistor capacitance".
* Flyback diode on an inductive load: search "flyback diode solenoid MOSFET driver".
* Optocoupler output stage (PC817): search "PC817 optocoupler transistor output wiring".
* Dobot MG400 I/O and the pump box control lines: search "Dobot MG400 IO interface vacuum pump box".

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. M5 Atom Lite (ESP32-A), the Lab 2 breadboard with both sensors on the op-amp stage
2. LM393 ×2, LM358N, resistor and capacitor kit
3. VL53L0X ×2, 100 Ω ×4, 100 pF ×4, 50 cm twisted/shielded cable, JST connector set
4. 3/2 valve with MOSFET module and flyback diode (from Smart Solutions L2), MG400 pump box
5. Amber syringe with a tip cured shut in daylight (the real clog), one empty syringe
6. Oscilloscope (two channels), multimeter
7. MG400 with the RPI station (Smart Solutions L1–L2)
8. KiCad or Fusion 360 Electronics
9. Arduino IDE, Python 3, Jupyter Lab, scipy, pandas
10. git

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Copy `lab2/` to `lab3/`; derivative column added to the sample stream
- [ ] Notebook: raw dP/dt vs. filtered dP/dt from the Lab 2 pulse data, threshold chosen from the data
- [ ] Falstad: differentiator + LM393 Schmitt trigger, hysteresis set so the raw ripple does not toggle it
- [ ] Breadboard: comparator output → ESP32 interrupt pin → valve MOSFET off, alarm latched, event sent
- [ ] Latency measured on the scope: pressure crossing the threshold → valve coil released
- [ ] Clog test with a tip cured in daylight; empty-syringe test
- [ ] VL53L0X on a 10 cm cable: 300 readings at 50 mm
- [ ] VL53L0X on 40 cm next to the MG400 cables: 300 readings, errors counted, scope on SDA/SCL
- [ ] RC on SDA and SCL, twisted pair, shield grounded at the ESP32 end: 300 readings
- [ ] Calibration sequence: MG400 to the taught pose above the post → Z offset; ±5 mm scan → X/Y offset
- [ ] PCB schematic → layout → DRC clean → Gerber checked in a viewer; pre-check at the ~05.11 consultation
- [ ] Safe-state measurement on the breadboard version of the drivers (ESP32 unpowered)
- [ ] Tag `data-acquisition-lab3` 72 h before 17.11; PCB review at the defense; order placed 17.11

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

### Simulation

**Falstad, comparator.** Input: a ramp that rises 50 kPa in 100 ms (normal dispense, about 500 kPa/s) and a second ramp that rises 50 kPa in 10 ms (clog, 5000 kPa/s), both through the Lab 2 op-amp scaling so they are in volts. Stage 1: RC differentiator (or an op-amp differentiator with a series resistor to limit gain at high frequency). Stage 2: LM393 with positive feedback, the threshold set between the two slopes, hysteresis wide enough that 20 mV of ripple on the input does not toggle the output. Add a 40 Hz, 20 mV sine on the input and confirm the output stays quiet on the normal ramp and fires once on the clog ramp. Record R, C and the hysteresis resistors in `docs/`; they go on the PCB.

**PCB DRC.** Run the design rule check with the manufacturer's rules (JLCPCB 2-layer defaults: 0.15 mm track and clearance minimum, 0.3 mm drill). Zero errors; every warning explained in `pcb/README.md`. Open the Gerber set in the manufacturer's viewer and in a second viewer; screenshot both. Mass and outline are constraints from 3D Print L3: target board ≤ 80 × 60 mm, 2-layer, 1.6 mm.

### Analysis

Notebook `notebooks/lab3_analysis.ipynb`, run with outputs before commit.

1. **Derivative on recorded data.** From the Lab 2 pulse CSV compute `dP = (P_now − P_prev) / dt` on the raw column and on the filtered column, dt = 10 ms. Plot both over one pulse on the same axes. Count threshold crossings for a threshold of 2000 kPa/s on each: the raw column crosses on noise, the filtered one crosses only on the real edge. Show the spectrum of the derivative vs. the spectrum of the signal: amplitude ratio at each frequency is 2πf.
2. **Threshold.** From 30 normal pulses: maximum dP/dt per pulse, mean and standard deviation. From 10 clog pulses (tip cured shut): the same. The threshold sits between the two distributions with a margin stated in kPa/s. If they overlap, say so and explain what the comparator can and cannot detect.
3. **Firmware logic** (language-neutral, this is the whole of it):
   ```
   every 10 ms: read ADC → convert → push to ring buffer → moving average → dP/dt
   if dP/dt > threshold, or comparator interrupt fired: valve to cup, latch alarm, emit {"ev":"alarm"}
   if 300 ms after dispense_start the plateau is below 50 % of the setpoint: latch alarm, err "empty"
   alarm stays latched until {"cmd":"clear"}
   ```
   The comparator path is hardware and fires in microseconds; the software path fires within one sample. Both release the valve. The RPI receives the alarm event and sends `stop` to the MG400 on port 29999; that latency is measured separately and is the RPI's number, not the board's.
4. **Latency on the scope.** Channel 1: op-amp output (pressure). Channel 2: valve MOSFET gate or coil voltage. Trigger on channel 2 falling. Clog pulse with the real cured tip. Latency = time from the pressure slope exceeding the threshold to the coil release. Ten repeats, table in the notebook, mean and maximum. Target: under 10 ms for the software path, under 1 ms for the comparator path.
5. **Empty syringe.** Air passes through the tip, pressure never reaches the setpoint. Does the dP/dt comparator fire? It should not. Does the plateau rule fire? It must, within 300 ms of dispense start. Ten repeats.
6. **VL53L0X, three datasets.** Same post, nozzle held by the MG400 at 50 mm, 300 readings each, columns `t_ms, z_mm, status` in `data/vl53_short.csv`, `data/vl53_long_noisy.csv`, `data/vl53_long_filtered.csv`. Per dataset: mean, standard deviation, number of timeouts and out-of-range readings, read time per sample. Scope screenshots of SDA and SCL edges for the long cable before and after the 100 Ω + 100 pF fix, rise time measured 10–90 %.
7. **Calibration sequence.** MG400 moves the nozzle to the taught pose above the post; the reading minus the expected height is the Z offset. Then a scan of ±5 mm in 0.5 mm steps in X and in Y: the readings jump where the tip leaves the beam; the centre of the two edges is the X/Y offset. Table of three runs; repeatability in mm. Compare with the tray registration numbers from 3D Print L2.
8. **PCB documentation.** Block diagram, schematic PDF, layout images, BOM with quantities and the connector map: which JST goes to which sensor, valve, pump box line, camera, VL53L0X, 24 V in. Power budget: 24 V in, buck to 5 V, what draws what, LED channel current.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: the alarm drops the valve

With the cured tip on the syringe: pump to blow, `dispense 200`. Within 10 ms of the pressure slope exceeding the threshold the valve coil is de-energized (scope), the stream shows `"alarm":1`, and `{"ev":"alarm"}` arrives at the RPI. A second `dispense` is refused with `ok:0` until `clear`. Ten out of ten.

#### Test Example 2: no false alarms on a normal dispense

Good tip, 30 dispenses at the Gate A recipe (tip, pressure, pulse). Zero alarms. The maximum dP/dt seen is logged per dispense and stays under the threshold by the margin stated in the notebook.

#### Test Example 3: I2C survives the long cable

400 consecutive VL53L0X readings on the 40 cm filtered cable with the MG400 moving at 100 % speed next to it: zero timeouts, standard deviation under 3 mm at 50 mm. The same test on the unfiltered long cable is kept as the negative result.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* Interrupt latency table (10 clog events) with the scope screenshots in `docs/`; mean and maximum in ms
* `notebooks/lab3_analysis.ipynb` with raw vs. filtered dP/dt side by side and the threshold justified from 30 normal + 10 clog pulses
* Three VL53L0X datasets of 300 readings each with their statistics, and SDA/SCL scope screenshots before and after the fix
* Calibration table: Z, X, Y offsets from three runs
* `pcb/` with schematic PDF, layout, DRC report with zero errors, Gerber set, BOM, connector map
* Safe-state measurement written in `docs/safe_state.md`: ESP32 unpowered, pump driven to suction and to blow through the MG400 DO fallback; multimeter reading of the syringe sensor (0.2 V, no pressure — the valve's spring return has put the pump on the cup) and a glass lifted by the cup to show suction is where it should be; paper under the tip dry after 10 s of blow; LED enable pin under 0.3 V
* PCB review passed on 17.11 and the order confirmation (5 boards per team) in `pcb/order/`

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Repo only. The board's sample and command format is the tool-board interface from Smart Solutions L2; `docs/interface.md` states which fields are implemented and any deviation.

Tool board → RPI, one line per 10 ms:
```
{"t":123456,"p":45.2,"v":-12.3,"valve":0,"pump":"off","uv":0,"z":112,"alarm":0}
```
RPI → tool board (each answered with `{"ack":"<cmd>","ok":1}` or `{"ack":"<cmd>","ok":0,"err":"<reason>"}`):
```
{"cmd":"valve","on":1}
{"cmd":"pump","mode":"blow"}
{"cmd":"dispense","ms":200}
{"cmd":"uv","ms":5000,"pose_ok":1}
{"cmd":"stop"}
{"cmd":"clear"}
{"cmd":"status"}
```
Events: `{"ev":"dispense_start","t":…}`, `{"ev":"dispense_end","t":…}`, `{"ev":"alarm","t":…,"dpdt":…}`.

### Safety

* **Robot STOP wiring.** The alarm path releases the valve on the board; the MG400 stop goes through the RPI (`stop` on port 29999). Until that path is tested, every clog test is run with a person at the MG400 emergency stop. The first ten dispenses of any new firmware run at 25 % robot speed. Optional: the comparator output can also be wired to an MG400 digital input as a hardware stop; if you do, document the input and test it separately.
* **Pneumatics.** 110 kPa and −70 kPa. Push-in fittings must click; a cured tip means the syringe is a closed vessel, so hold it in its holder, not in the hand, during clog tests. Release pressure through the valve before removing a syringe.
* **UV LED interlock.** The LED channel is off when unpowered (enable pulled low on the board), refuses `uv` without `pose_ok`, and times out on the board regardless of the RPI. 405 nm goggles at the bench whenever the LED is connected. Shroud fitted before the first power-on. Never 365 nm. The LED is never aimed at the tip; cured resin in the tip is the clog you are trying to detect.
* **Resin.** Nitrile gloves, IPA for cleanup, tip caps when idle, cured waste only into the bin. Uncured resin is a skin sensitizer.

### Components for the next lab

Order goes out on 03.11.26. Quantities per team. PCBs: 5 per team, ordered on 17.11.26 after the review.

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| Logic-level N-MOSFET | 3 | Valve driver, spare driver, one spare; any logic-level part, e.g. IRLZ44N |
| Schottky diode | 3 | Flyback across the valve coil and the spare channel |
| PC817 optocoupler | 2 | The two pump-box control outputs |
| 24 V → 5 V buck module | 1 | Board supply from the pump-box 24 V |
| Pin headers | as per BOM | ESP32 module socket, programming, test points |
| JST connectors | as per BOM | Sensors, VL53L0X, valve, pump box, camera power, 24 V in |
| LED constant-current driver | 1 | Only if not already ordered in Smart Solutions L2 |
| Digital scale, 0.01 g | 1 | Syringe weighing, dose weighing, ground truth in Lab 4 |
| Dummy PC glasses | 8 | Five recirculating in the tray, three spare |
| Resin refill | 1 | 405 nm transparent |
| PCB | 5 | Ordered 17.11.26 from the reviewed Gerber; arrives for Lab 4 |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — firmware with derivative, interrupt and alarm latch; `pcb/` with schematic, layout, DRC report, Gerber, BOM | 5 p |
| Analysis — raw vs. filtered dP/dt, threshold from data, latency table, three VL53L0X datasets with statistics | 5 p |
| Prototype — clog and empty tests on the real valve, calibration sequence run on the MG400, safe state measured | 5 p |
| Documentation — connector map, power budget, `safe_state.md`, `interface.md`, review notes and order confirmation | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `data-acquisition-lab3` 72 h before the defense.**

The defence is online on 17.11.26. The tag deadline is 72 h before it, which is Saturday 14.11.26 — the same weekend as the contact session where the next lab is handed out. Anything that has to be shown live, the robot moving or a print or a measurement, has to be visible on the call, so join from the lab.

The tagged repo must contain, under `data-acquisition/lab3/`:
* `src/` — firmware with the alarm logic and the I2C calibration sequence; the Python side that reads the stream and runs the calibration
* `data/` — clog and normal dispense logs, the three VL53L0X datasets, calibration runs
* `notebooks/lab3_analysis.ipynb` with outputs
* `pcb/` — schematic PDF, layout, DRC report, Gerber, BOM, connector map, `README.md`
* `docs/` — scope screenshots, `safe_state.md`, `interface.md`, Falstad export
* `AGENTS.md` updated

The defense includes the PCB review: the instructor walks through the schematic against the Gate E list (ESP32, both sensor footprints, op-amp stage, comparator, two MOSFET valve drivers with flyback diodes, LED channel with enable low by default, two optocoupled pump-box outputs, VL53L0X connector, camera power, 24 V → 5 V buck, USB-UART). Boards are ordered the same day only if the review passes. One live change, for example: lower the threshold by 30 % and show a normal dispense still passes, or move the VL53L0X post 10 mm and rerun the calibration.

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

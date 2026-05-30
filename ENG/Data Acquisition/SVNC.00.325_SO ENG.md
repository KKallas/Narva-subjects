## General Information
### Objectives
The course provides the skills to build a measurement and data acquisition system for a real engineering problem — pressure-based volume estimation for the Dobot MG400 dispensing system. Students start from sensor selection and the raw signal and progress to PCB design, statistical characterisation of the measurement system (resolution, noise level, measurement uncertainty, absolute accuracy), and a machine-learning model that estimates the syringe fill level from the shape of the pressure curve. Every technical choice is made on the basis of a measured comparison of alternatives: voltage divider vs op-amp, polling vs interrupt (IRQ), analogue vs digital filtering. The academic framing is **signal processing theory** (Fourier analysis, filtering, the effect of differentiation on noise) and **machine learning** on time series (feature extraction, model training and validation).

### Learning Outcomes
A student who has completed the course:
- distinguishes the components of a data acquisition system and describes the analogue and digital parts of the signal chain;
- explains the operating principle of an analogue-to-digital converter, its main error sources, and the calculation of effective resolution;
- designs an op-amp-based signal conditioning circuit (offset and scaling) and justifies component choices on the basis of simulation and measurements;
- selects an appropriate solution from alternatives (voltage divider vs op-amp, analogue vs digital filter, polling vs IRQ) on the basis of measured comparison, taking accuracy, cost, and development time into account;
- applies analogue (RC filter, Schmitt trigger) and digital filtering (averaging, median, oversampling) techniques and assesses their effectiveness using Fourier analysis;
- programs an ESP32 microcontroller using interrupts (IRQ), hardware timers, and dual-core operation for real-time measurements;
- designs a printed circuit board (Fusion 360 EDA), prepares Gerber files, and orders manufacturing from JLCPCB;
- characterises a measurement system statistically (resolution, measurement uncertainty, absolute accuracy, repeatability) and documents the results in Jupyter Lab;
- automates data collection (Python + robot API) and gathers a sufficient dataset for training a machine-learning model;
- trains and validates a machine-learning model (scikit-learn) on measurement data, extracting features from the time series (including Fourier features).

### Brief Course Description
The course builds a pressure measurement system for the Dobot MG400 dispensing system step by step. The labs build the physical measurement system: the first prototype with the MPX5700AP pressure sensor and an ESP32 together with a web interface (Lab 1), an op-amp-based signal conditioning prototype together with a comparison against a voltage-divider solution as well as PCB design for ordering from JLCPCB and validation of robot integration (Lab 2), pneumatic measurement of syringe fill level using two alternative solutions — including monitoring the derivative of the analogue signal with a Schmitt trigger and IRQ, dual-core ESP32 programming, and analogue and digital filtering (Lab 3). Each lab includes a simulation (Falstad), a physical prototype, statistical analysis of measurements (Jupyter Lab), and a quantitative comparison of at least two solution alternatives. Assignments 4–5 use the completed system and the MG400 robot for automated data collection (hundreds of measurements at different fill levels) and train a machine-learning model that estimates the syringe fill level from the shape of the pressure curve. The course-spanning theme is engineering decision-making based on measured data.

### Assessment
List of independent assignments and instructions for completing them:

Assessment structure: 5 projects × 20 points = max 100 points. The integration project is worth max 70 points (perfectly executed = grade C). A total of 170 points is possible; the grade is calculated from the best 100. Students choose which projects to complete — the integration project can be submitted on its own, with the remaining work added to improve the grade.

Four assessment categories per project:
- Working files (5p): code, schematics, design files — all in the git repo
- Analysis (5p): Jupyter notebook, Fourier analysis, measurement results
- Prototype (5p): a working physical implementation
- Documentation (5p): specifications, justifications, instructions

#### Consultation 1: Electronics and soldering basics (optional)
For students who have not previously worked with electronics. Held before the first assignment.

Soldering iron handling:
- Safety requirements, iron maintenance, working with solder and flux
- First soldering: practice board with TH (through-hole) components — resistors, capacitors, LEDs, pin headers
- SMD soldering: 0805 and 1206 passive components (resistors, capacitors) on a practice board
- Inspection: visual inspection (cold joint, bridge, too little/too much solder)

Component familiarity:
- Passive components: resistor (R), capacitor (C), inductor (L) — what they do, what they look like, how to read the value (colour codes, markings)
- Active components: LED (polarity!), transistor, op-amp IC, microcontroller — how they differ from passives
- Breadboard: how the rows are internally connected, the power rails, how to avoid a short
- Multimeter: measuring voltage, resistance, and continuity

Outcome: the student can solder TH and SMD components, recognises passive and active components, and can work on a breadboard.

#### Assignment 1: Raw signal and the first Fourier
Build a pressure measurement circuit with the MPX5700AP sensor and an ESP32 microcontroller. Connect the sensor directly to the ADC, collect 30 measurements in three pressure categories (MG400 compressor), convert ADC values to Pascals. Simulate the circuit in Falstad. In Jupyter Lab, visualise the signal in the time domain and apply Fourier analysis (scipy.fft) to identify noise sources in the frequency domain.

#### Assignment 2: Op-amp and filtering — Fourier comparison
Build, on the same breadboard, an operational amplifier (LM358N) circuit that offsets and scales the MPX5700AP signal into the ESP32 ADC range. Measure four configurations (direct ADC, voltage divider, op-amp, op-amp + digital filter) using the same measurements (4 × 30 = 120 measurements). In Jupyter Lab, compare all four configurations side by side: time domain, Fourier spectra, SNR calculation. Identify specific noise sources (motor PWM, switching power supplies, ground loops) and prove with numbers why each filtering step is necessary.

#### Assignment 3: dP/dt derivative, IRQ threshold, I2C calibration, and PCB design
Add a safety mechanism based on the derivative of the pressure curve (dP/dt): a comparator (op-amp as a Schmitt trigger) + an ESP32 interrupt. Use Fourier analysis to show why differentiation amplifies noise (× 2πf) and why filtering must be done before taking the derivative. Add a VL53L0X distance sensor (I2C) for nozzle calibration: diagnose an I2C line noise problem with a longer cable and solve it with an RC filter. Design a PCB for the entire system (pressure sensor + op-amp + comparator + VL53L0X + ESP32 pin header). The lab defence includes a PCB design review — ordering happens immediately after the defence. The system pressure is ~2 bar.

#### Assignment 4: Data collection with the MG400
Write a Python script that automates data collection: a dispensing command to the MG400 → ESP32 sensor data over UART → CSV logging. Collect at least 500 measurements (5 speeds × 5 pressures × 20 repetitions). Each measurement records the entire pressure curve as a time series. In Jupyter Lab, analyse the shape of the pressure curve vs fill level — the relationship emerges from the measurements, not from a pre-given theory. Once the PCB has arrived — solder it and test.

#### Assignment 5: Machine learning model
Train a model on the dataset from assignment 4 to answer the question: how much material is left in the syringe? Input features from the pressure curve (time-domain features: response time, dP/dt max, plateau value, area under the curve; Fourier features: dominant frequency, spectral energy). Compare linear regression, decision tree, and random forest. Assess whether Fourier features improve the model, whether a model trained on op-amp data is better than one trained on raw data, and whether the model works on another team's device. Practical outcome: a threshold of "less than 2ml left in the syringe, replace it!" — and the accuracy with which the model says so.

#### Bonus assignment: Automatic fill-level monitoring
A closed loop: MG400 dispenses → pressure sensor measures → model estimates remaining volume → web interface shows the estimate → if below the threshold → operator warning. The IRQ ensures safety (clog → stop), the ML provides the information (when to replace the syringe).

### Schedule of Contact Hours
- **[~12.09.26]** Consultation 1 (optional): electronics and soldering basics — soldering iron, TH and SMD soldering, passive and active components, breadboard, multimeter
- **[~12.09.26]** First ESP32 program, ADC basics, introduction to Jupyter Lab, first FFT
- **[~03.10.26]** Defence of Assignment 1
- **[~03.10.26]** Op-amp theory, Falstad simulation, fourfold comparison
- **[~15.10.26]** Consultation 2: practical op-amp help — offset and scaling circuit, typical mistakes, using an oscilloscope
- **[~24.10.26]** Defence of Assignment 2
- **[~24.10.26]** Derivative, comparator, IRQ + I2C noise diagnostics
- **[~05.11.26]** Consultation 3: determining resolution — ADC bits × op-amp gain × noise level → effective resolution. PCB schematic pre-check.
- **[~14.11.26]** Defence of Assignment 3 (includes PCB design review → ordering immediately after)
- **[~14.11.26]** MG400 API and automated data collection in Python
- **[~05.12.26]** Defence of Assignment 4
- **[~05.12.26]** Introduction to machine learning: scikit-learn, time-series features, pressure curve analysis
- **[~16.01.27]** Defence of Assignment 5
- **[TBD]** Defence of the integration project

### Conditions for Admission to Final Assessment
The student has successfully defended at least one assignment with a passing result.

### Minimum Total Points Required for Admission to Final Assessment
51

### Final Assessment Scale
Differentiated (A, B, C, D, E, F, mi)

### Composition of the Final Grade
5 projects × 20 points = max 100 points. The integration project is worth max 70 points (perfectly executed = C). A total of 170 points is possible; the grade is calculated from the best 100. The integration project can be submitted on its own (sufficient to pass the course), with the remaining work added to improve the grade.

|   |   |
|---|---|
| A | 91 points |
| B | 81 points |
| C | 71 points |
| D | 61 points |
| E | 51 points |
| F | The student has accumulated fewer than 51 points |
| mi | The student has not submitted assignments or participated in the final assessment |

### Resolving Outstanding Work
By agreement with the responsible lecturer

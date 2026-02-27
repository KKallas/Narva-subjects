## Data Acquisition: Lab 3

## \! Safety Instructions \!

### UR5 Robot Operation

Before activating the robot, make sure the workspace is clean and no one is in the robot's work area. When starting the robot, always stand at least two meters away until the system is fully initialized and the program is loaded.

When testing a new program, keep your hand on the STOP button at all times. Never watch the robot's movement with trust — assume something can go wrong. Do the first run-throughs always at reduced speed (25-50%), even if the program seems correct. If the robot behaves unexpectedly or makes strange movements, press STOP immediately. Never try to stop the robot with your hand — that is dangerous for both you and the robot.

Before finishing work, always move the robot to a safe home position and switch it off. Leave the work surface tidy so the next user doesn't encounter unexpected obstacles.

### Pneumatic System Operation

The pneumatic system operates at up to 7 bar pressure, which is sufficient to cause injuries if a hose or fitting comes loose. Before pressurizing the system, check all connections by hand — 6mm and 4mm quick-fit fittings must be fully engaged with an audible click sound. If the fitting goes on easily without resistance, it's not properly secured.

The connection between the compressor and the hose is especially critical, as that's where the highest pressure and greatest airflow are. Check this connection stack every time before turning on the compressor. If you hear a hissing sound from the system, there's a leaking connection somewhere — turn off the compressor immediately and find the leak before continuing.

Never direct pressurized airflow toward yourself or others. Never connect or disconnect quick-fit fittings while the system is pressurized — first release the pressure through the solenoid valve or turn off the compressor and wait until the pressure has dropped to zero.

If you're working simultaneously with both the robot and pneumatics, make sure the pneumatic hoses don't fall within the robot's movement trajectory. The robot doesn't "feel" the hose and can pinch it or drag it along.

## Objective

Create and test 2 methods for measuring remaining material in a syringe using only compressed air, and whether the syringe is empty or clogged. The first method is #4 below, and you may freely choose the second from the remaining three.

The principle is simple: if we have a constant-pressure source and a switchable solenoid valve (fully open or closed), then the pressure in the syringe rises until the plunger overcomes the silicone resistance and starts moving. While the plunger is stuck, pressure builds quickly in the closed volume. When the plunger starts moving, the rate of pressure increase drops significantly, because the volume into which air flows starts growing. Within a few milliseconds, the system reaches dynamic equilibrium — pressure stabilizes and stays constant because the air inflow balances the volume of outgoing silicone. In dynamic equilibrium, the plunger continues moving at a constant speed limited by the needle tip resistance, not the air inflow. This entire pressure build-up and stabilization happens quickly but the silicone moves slowly, which is why we need to monitor the 2-100ms window from when pressure starts flowing until the plunger should have moved from its position.

We need to find two parameters: how long it takes before the plunger starts moving, and what the plunger position is 100 milliseconds after it starts moving. Distance divided by time gives us the average speed. We have several solutions to choose from to get the desired result:

1. MPX5700AP connected directly to M5 Atom Lite
   Teaches timer usage and basic ESP32 ADC properties
   \>2ms allows ESP32 both polling and timer solutions. This time, please solve the data change reading through a timer.
2. MPX5700AP through a voltage divider to M5 Atom Lite
   Teaches multi-core processor programming and shared variable management
   Here, please solve the sensor reading through an additional thread running on the second core independently to achieve 1ms or sub-1ms readings.
3. MPX5700AP through an op-amp scaling only the range of interest to 0-3.3V with amplified signal to M5 Atom Lite
   Teaches analog signal conditioning and digital filtering
   Essentially digital filtering, use a timer.
4. MPX5700AP through an op-amp monitoring the rate of change
   Teaches differential signal processing and derivative measurement in the analog domain, and IRQ solution on ESP32
   MPX5700AP through an op-amp (LM358N) configured as a Schmitt-trigger comparator using positive feedback. The op-amp monitors the rate of pressure change — when the change slows down (plunger started moving), it generates an IRQ signal to the microcontroller. Positive feedback creates hysteresis that keeps the signal clean and prevents oscillation between thresholds. Use IRQ to know when the plunger started moving, and start a timer that takes a second measurement exactly 100 milliseconds later to find out how high the pressure has risen.

Choose an optional design version and draw one board in Fusion 360 EDA that can implement both versions using either jumpers or 0R resistor soldering. If the op-amp was unclear in the first round, I recommend swapping version 4 → 3 here. Go through the same thing a second time and you'll understand it much better.

### Signal Filtering

Signal filtering is where noise meets meaning, where the chaos of the universe becomes usable data.

#### Analog Side

A resistor and capacitor together make an RC filter, but really they stretch time. The resistor slows the current, the capacitor collects charge. The resistor creates a delay that lets fast changes die out while slower changes pass through. You see this everywhere in power circuits, because switching regulators and digital circuits spray electromagnetic noise across the entire spectrum. The RC filter tells everything "wait a moment", and noise, being impatient and high-frequency, gets tired.

A capacitor alone, directly to ground, works differently. There's no resistor, so there's no deliberate delay in your signal path, but the capacitor still creates a low-impedance path to ground for fast frequencies. This is aggressive filtering — noise is routed to ground almost immediately, though real components always add a bit of delay, just nanoseconds instead of microseconds.

The differential signal trick is elegant: take your original signal, filter one copy through an RC chain to create a delayed, smoothed version, then compare it to the unfiltered version. What you get is essentially a derivative — the rate of change. Noise tends to be similar in both signals and cancels out when compared. Real information, edges and transitions, remain clearly visible. That's why differential transmission rules everywhere signals need to travel far or stay clean.

#### Digital Side

Digital filtering works on a different principle — you can't change physics, but you can take more samples and ask smarter questions. Oversampling means reading your ADC faster than strictly necessary or averaging multiple adjacent readings. Each sample contains noise, but if that noise is random (and usually it is), averaging multiple samples smooths out the sharp corners while the signal reinforces itself. The math is simple; the results are powerful.

Spatial oversampling means reading multiple physical sensors or multiple points in space — think reading three temperature sensors and averaging them, or scanning a detector array and combining pixels. Bit-depth oversampling means taking a 12-bit ADC and reading it thousands of times to achieve effective 14-bit or 16-bit precision. The noise level doesn't change, but your ability to see through it does.

Sometimes a simple approach — take the median of a small number of samples rather than the mean — works better than complex averaging. The median completely ignores outliers. If your noise occasionally has wild spikes from electromagnetic interference or bit errors, averaging spreads that spike across the entire filtered output. The median simply throws it away. Three or five samples, take the middle value, move on. It's crude but effective, especially in hostile electromagnetic environments inside microcontrollers where motor drivers or solenoids create voltage irregularities.

The deeper truth is that all filtering, analog or digital, is understanding what you're trying to preserve versus what you're trying to destroy. There's no universal "clean signal" — there's only the question of what matters in your specific system, at your specific timescales, and what can safely be ignored.

## Lab Structure

### Part 1: Choose two solutions and build a prototype

Choose an optional solution from the three offered variants. Build both prototypes on a breadboard to test their operating principles before the PCB design. If you haven't built similar analog circuit logic before, simulate first in Falstad (make sure to put it in the development log, it helps with grading) — it saves time and components.

### Part 2: PCB Design

Design one PCB from which both selected solutions can be easily built. Use jumpers or 0Ω resistor positions in the schematic that can be soldered as needed to select between the two configurations. Clearly mark on the *silkscreen* or in comments which components go where for each configuration.

Order at least 10 boards (typically JLCPCB gives you 5 pieces minimum anyway). Considering that each board remains one specific configuration after soldering, you need at least four working boards — two for testing each solution and two spares in case something breaks or soldering fails.

### Part 3: PCB Functional Test

Solder both configurations (use two different boards with different configurations). Test that both analog circuits produce expected output signals — check op-amp outputs with an oscilloscope and multimeter. Verify that IRQ signals are generated at the correct moments and the timer reads the ADC at the correct interval.

### Part 4: Integration with Pressure System and Measurement

Connect both solutions to the pneumatic system and perform complete testing as described in the analysis section. 3D print a fixture and set up the camera and remaining test hardware/software. Perform 6×100 measurements for both configurations and analyze results in Jupyter Lab. Compare the accuracy, repeatability, and reliability (deviation) of both methods.

### Technical Tasks

#### Comparative analysis (Jupyter Lab):

* Determine the resolution, measurement uncertainty, and absolute accuracy for both solutions based on collected data ([link](https://docs.google.com/document/d/1JpWw1INjQ7y8hc0LWF63XZwhcZW0h86u2kE3aBuDFro/edit?usp=sharing))
* Estimate the total production cost for 100 units based on component and PCB prices, create a BOM (bill of materials) — a simple table: component, quantity, location, product link, where to buy
* Create a 6×100 measurement table for six different fill levels: 10ml, 8ml, 6ml, 4ml, 2ml, and 0ml

#### PCB design (Fusion):

* Create a schematic drawing that supports both solutions through jumpers or 0Ω resistors
  Clearly mark in the schematic which components are shared and which differ between configurations
* Create PCB layout
* Run Design Rule Check before finalizing the board
* Generate Gerber files according to JLCPCB specifications and verify them with a viewer

#### Code (Arduino):

* Implement interrupt (IRQ) handling for the Schmitt trigger output
* Set up a timer at 0.5ms interval for analog input reading
* Use threads for differential signal polling on the second core
* Write automated tests that verify both methods' results match expected values

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

### Background Information

* **ESP32 Interrupt**
  [https://www.youtube.com/watch?v=WVK2Wx386XE](https://www.youtube.com/watch?v=WVK2Wx386XE)
* **ESP32 threads**
  [https://www.youtube.com/watch?v=k\_D\_Qu0cgu8](https://www.youtube.com/watch?v=k_D_Qu0cgu8)
* **Schmitt trigger**
  [https://www.youtube.com/watch?v=Nrp8OgQLAlw](https://www.youtube.com/watch?v=Nrp8OgQLAlw)
* **Low Pass filter**
  [https://www.youtube.com/watch?v=OBM5T5\_kgdI](https://www.youtube.com/watch?v=OBM5T5_kgdI)
  [https://www.youtube.com/watch?v=oHKwwvcn77Y](https://www.youtube.com/watch?v=oHKwwvcn77Y)
* **High Pass filter**
  [https://www.youtube.com/watch?v=H30kRgI5bi0](https://www.youtube.com/watch?v=H30kRgI5bi0)
* **Noise management**
  [https://www.youtube.com/watch?v=u40kX1DYKdA](https://www.youtube.com/watch?v=u40kX1DYKdA)
* **Layer configuration in Fusion 360**
  * Open your PCB project in the Fusion 360 electronics workspace. Access the layer manager from the Electronics tab: Create \> Layer Stack View. In the layer manager you see the default layers (Top, Bottom, Core, Solder Mask).
  * For the base material (core), set FR4 with a thickness of about 1.5mm (if the final board is 1.6mm). Set both copper layers to 1 oz (35 µm). Add solder mask layers on top and bottom (about 0.2-0.4mm (1 mil) thickness). Verify that the total thickness matches JLCPCB standard options (e.g. 1.6mm) — they have specific standard stackups and this simplifies things.
  * **Design and export**
    * For manufacturing file generation, export Gerber files and drill files via the CAM preview or use an ODB++ file, ensuring the stackup is correctly interpreted.

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

### Tools

1. M5 Atom
2. M5 Camera module
3. MPX5700AP
4. Arduino IDE
5. VS Code
6. Git
7. Oscilloscope
8. Multimeter
9. UR5

*If the plan changes, update the tools too, or make a [draw.io](http://draw.io) diagram showing how things are functionally related.*

### Project Breakdown

Break this into logical pieces before starting the project so progress can be assessed

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**Simulation**

Before building the physical circuit, simulate the analog circuit in Falstad that monitors the rate of voltage change. The circuit must respond by pulling the voltage up or down at the moment when the pressure rise curve slows down — this is the signal that the plunger has started moving.

Use the op-amp in the simulation as a differential amplifier or comparator. As input, provide a slowly rising voltage that simulates the pressure sensor output, and add a breakpoint where the rate of increase drops sharply. Monitor the op-amp output and adjust feedback resistors and capacitors until you find a configuration that gives a clear logic signal at the breakpoint.

**Why simulate**

Simulation gives you three important things before you start assembling hardware. First, you see whether your analog circuit behaves as expected at all — whether the derivative calculation or comparator threshold works at the correct time ranges and voltage values. Second, you find the right threshold for IRQ signal generation without having to repeatedly resolder components. Third, you can test different noise scenarios — add small oscillation to the input signal in the simulation and see whether the Schmitt trigger hysteresis keeps the output stable.

Falstad is the ideal tool for this because you can change resistor and capacitor values in real-time and immediately see the result. Save your working schematic and add it to the project documentation — years later it will explain why you chose those specific component values, and it helps with grading too.

**Analysis**

For testing, build a simple two-syringe system. Take two regular 10ml syringes and connect them to each other with a short piece of 4mm tubing. Connect a pneumatic fitting to the top of each syringe, which then connects to the solenoid valve — this way you can control compressed air flow into both syringes.

Attach a camera to the first syringe that can automatically detect the syringe fill level. This works because the dark silicone plunger is clearly distinguishable against the light syringe body background, and the actual material volume can be read from the image.

The test cycle works as follows: push a designated amount (time) of material from the first syringe to the second using air, take your measurements, then use the second pneumatic fitting to push the material back into the first syringe. Now you can repeat the test without disassembling the system.

Before thorough testing, set up the timer so that the analog input is recorded at 0.5ms intervals (try to use supersampling). This fast sampling rate (2kHz) allows seeing the pressure rise rate change with sufficient detail — you can precisely determine the moment when the plunger starts moving and the pressure rise slows down.

With such an aid, you can make hundreds of measurements with minimal manual work. Collect data into a Jupyter Lab report for six different fill levels: 10ml, 8ml, 6ml, 4ml, 2ml, and 0ml. At each fill level, do 60-100 measurements to get a statistically reliable picture of both methods' accuracy and repeatability.

From the collected data, you can find the optimal threshold for the op-amp's pressure rise rate monitoring — the moment from which to start counting time to determine how far the plunger has traveled in 100ms. From the same data, calculate the resolution and measurement uncertainty for both methods. If you add a calibrated reference gauge to the circuit, you can also determine the absolute accuracy.

*These are the first two examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go\!*

### Development Log

### Results

Make sure to provide everything for grading:

* Software/Work files (**4** points): code, EDA design, or technical files
* Simulation (**4** points): appropriate simulation methods, analysis, testing
* Prototype/Physical project (**4** points): execution, quality, functionality
* Documentation (**4** points): specifications, design choice justifications, user manual

Git repo:
Arduino file:
Jupyter Analysis (please include specific file names, otherwise I might look at the wrong thing):
Development log:

### Feedback

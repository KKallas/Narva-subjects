## Data Acquisition: Lab 2

## Objective

Lab 2 is a decision and integration point. In Lab 1 we tested the voltage divider solution for interfacing the MPX5700AP pressure sensor with ESP32. Now we build an op-amp based alternative (LM358N), measure its accuracy and cost, compare the two approaches, and choose which one to proceed with. With the chosen solution we design a PCB in Autodesk Fusion and order from JLCPCB. In parallel we validate the entire system concept — building a working prototype where a physical signal (pressure from the syringe) travels through ESP32 and reaches the UR5 robot, making it rotate its head proportionally to the measured pressure.

If the lab succeeds, we have two concrete results: a made decision and a finished PCB design for the next lab, plus a working prototype that proves the signal path (syringe→sensor→ESP32), communication protocol (GPIO+HTTP) and control logic (pressure→robot movement) all work together.

### Lab Structure

#### Part 1: Signal Conditioning Selection

Lab 1 gave us the voltage divider results. Now we prototype the op-amp variant on a breadboard or protoboard. LM358N dual op-amp: one half shifts the signal 0.2V downward, the other half scales the upper end to 3.2V. We measure accuracy with an oscilloscope, do the same 30 measurements (1ml, 5ml, 9ml) in Jupyter Lab, and compare with the voltage divider. We decide based on cost, accuracy, and development time.

#### Part 2: PCB Design

We take the chosen solution and draw a PCB in Fusion that connects the MPX5700AP, signal conditioning circuit (voltage divider OR op-amp), and M5 Atom Lite interface. The lab ends with Gerber files ready for JLCPCB ordering.

#### Part 3: Robot Integration

We use the existing prototype (breadboard setup) to test the entire chain:

* GPIO wake-up: press a button on ESP32, ESP32 pulls a GPIO pin, UR5 wakes up
* HTTP communication: robot sends a GET request, ESP32 responds with a pressure value
* Control logic: robot converts pressure to a rotation angle and moves the head

This part gives functional confirmation that the concept works before we move to the final PCB.

### Technical Tasks

#### Signal conditioning prototype:

* Build the LM358N circuit on a breadboard
* Calibrate offset and scaling
* Measure signal quality with an oscilloscope
* Document components and costs

#### Comparative analysis (Jupyter Lab):

* 30 measurements with op-amp solution (10 × 1ml, 10 × 5ml, 10 × 9ml)
* Convert ADC values to Pascals
* Calculate resolution and noise level
* Compare with Lab 1 voltage divider results
* Decide: cost/accuracy/complexity balance

#### PCB design (Fusion):

* Schematic drawing of the chosen solution
* Component placement
* Trace routing
* Design Rule Check
* Gerber file generation according to JLCPCB specifications

#### Robot functional test:

* GPIO pin configuration between ESP32 and UR5
* HTTP API creation on ESP32 (endpoint for reading pressure)
* UR5 program writing: GPIO listening → HTTP GET → pressure reading → head rotation
* Testing: syringe→pressure→robot reacts

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

### Background Information

* **Fusion**
  First PCB: [https://www.youtube.com/playlist?list=PLmA\_xUT-8UlL80Xm8Gxz98YNum3I9GInr](https://www.youtube.com/playlist?list=PLmA_xUT-8UlL80Xm8Gxz98YNum3I9GInr)
  Or
  [https://www.youtube.com/watch?v=H6CNmnT6kGo](https://www.youtube.com/watch?v=H6CNmnT6kGo)
  How to prepare an order for JLCPCB:
  [https://www.youtube.com/watch?v=Ufu4nr0PfIc](https://www.youtube.com/watch?v=Ufu4nr0PfIc)
* **UR5 robot**
  Manual: [https://www.universal-robots.com/download/manuals-cb-series/user/ur5/16/user-manual-ur5-cb-series-sw16-english-us/](https://www.universal-robots.com/download/manuals-cb-series/user/ur5/16/user-manual-ur5-cb-series-sw16-english-us/)
  GPIO:
  [https://www.universal-robots.com/articles/ur/interface-communication/connecting-internal-inputs-and-outputs-io-on-the-robots-controller/](https://www.universal-robots.com/articles/ur/interface-communication/connecting-internal-inputs-and-outputs-io-on-the-robots-controller/)
* **LM358N**
  What is an op-amp: [https://www.youtube.com/watch?v=kbVqTMy8HMg](https://www.youtube.com/watch?v=kbVqTMy8HMg)
  How to use the dual op-amp: [https://www.hnhcart.com/blogs/learn/lm358-ic-and-its-applications?srsltid=AfmBOopTLVTs58AWnydEefADw4rA58yyP0q2xIXfWn7fCmtJJsc2qgXH](https://www.hnhcart.com/blogs/learn/lm358-ic-and-its-applications?srsltid=AfmBOopTLVTs58AWnydEefADw4rA58yyP0q2xIXfWn7fCmtJJsc2qgXH)
  Use one half to shift the signal 0.2V downward and scale the upper end to about 3.2V with the other half of the LM358N
* **Analog-digital interface logic**
  And how they all depend on op-amps
  [https://www.youtube.com/watch?v=g4BvbAKNQ90](https://www.youtube.com/watch?v=g4BvbAKNQ90)

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

### Tools

1. M5 Atom
2. MPX5010DP
3. Arduino IDE
4. VS Code
5. Git
6. Oscilloscope
7. Multimeter
8. UR5
9. Router?

*If the plan changes, update the tools too, or make a [draw.io](http://draw.io) diagram showing how things are functionally related.*

### Project Breakdown

- [ ] Op-amp simulation (offset and scaling)
- [ ] Signal conditioning prototype
- [ ] Accuracy determination for prototype v2
- [ ] Comparative analysis
- [ ] PCB design
- [ ] M5 Atom firmware fixes for robot interfacing
- [ ] Robot functional test

*How far along are you? When will you be done? How could you go faster? — the usual questions*

### Simulation

You have an MPX5700AP that outputs 0.2V to 4.7V. The ESP32 ADC wants 0V to 3.3V. Two problems: wrong starting point and wrong voltage.

**First op-amp:** Shifts the signal 0.2V downward. Now you have 0V to 4.5V.

**Second op-amp:** Scales the 4.5V range down to about 3.2V. Leave 0.1V buffer room so the ADC doesn't saturate.

#### What to do in the simulator

**Example 1:** Build a summing amplifier that removes the 0.2V DC offset. Determine the resistor values and describe how you chose those values.

**Example 2:** Build a non-inverting amplifier with a gain below one (attenuator) that compresses the 4.5V range to 3.2V. Again — determine the resistor values and describe how you chose those values.

### Why Simulate

Test circuit errors cheaply on screen, not on a breadboard. If you come back a year later, you can immediately see why you chose those specific components. Change parameters, see what happens, learn how the circuit behaves before going to look for components from the bin.

### Analysis

**Comparative analysis**

Compare the voltage divider (Lab 1) and op-amp solution:

* Accuracy: ADC noise level and resolution for both
* Cost: total component cost
* Development time: how long it took to build the prototype, how development costs distribute to the product
* Process complexity assessment

**Requirements**

Determine the minimum accuracy you need. How precise does the pressure measurement need to be for the robot to effectively use the dispenser?

**Automation**

Create a test script that automatically checks:

* ADC reads the sensor correctly (compare with known pressure)
* Signal conditioning doesn't saturate at extreme values
* …

*These are the first two examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go\!*

### Development Log

### Results

Git repo:
Readme:
Development log:

### Feedback

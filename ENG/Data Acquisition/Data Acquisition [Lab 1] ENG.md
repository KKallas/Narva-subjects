## Data Acquisition: Lab 1

### Objective

Build a pressure gauge mock-up that will later be used for controlling syringe dispenser pressure. We build a technology mock-up with the core functional components and a skeleton user interface, using the MPX5700AP sensor and an ESP32-based M5 Atom Lite control module. Connect a differential pressure sensor via plastic tubing to a syringe and attempt to display pressure on a web page in real-time (\~4hz).

Determine the system's accuracy and measurement density (resolution)

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

### Background Information

* **Electronics basics**
  tinkercad: [https://www.tinkercad.com/circuits](https://www.tinkercad.com/circuits)
  falstad sim: [https://www.falstad.com/circuit/circuitjs.html](https://www.falstad.com/circuit/circuitjs.html)

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

### Tools

1. M5 Atom
2. MPX5010DP
3. Arduino IDE
4. VS Code
5. Git
6. Oscilloscope

*If the plan changes, update the tools too, or make a [draw.io](http://draw.io) diagram showing how things are functionally related.*

### Project Breakdown

- [ ] Base project (schematic and description)
- [ ] Pressure test with oscilloscope
- [ ] Modify the HTML page so that it only shows pressure reading and wifi setup
- [ ] Connect the pressure sensor to M5 Atom
- [ ] Add necessary API endpoint and test
- [ ] Jupyter lab resolution analysis

*How far along are you? When will you be done? How could you go faster? — the usual questions*

### Simulation

For the first project, the main part is learning electronics basics through simulators. Please submit 1 simulation with an explanation of which part of the process you tested and what you learned.

### Analysis

#### Determine resolution and range for the digital system

Create a Jupyter Lab notebook, measure pressure 30 times (low, medium, high) by creating pressure with the syringe by pushing the plunger to either 1ml, 5ml, or 9ml

#### Create a Pascal scale

Create a calculated scale in Pascals, propose how to test whether the error is linear across the full scale range

#### Analysis structure

##### Jupyter Lab notebook preparation

1. Create a new notebook
2. Import data analysis libraries
3. Create a function for reading data from ESP32

##### Test protocol: 30 measurements in three categories

Low pressure (1ml):

* 10 measurements with syringe at 1ml of air
* Save data

Medium pressure (5ml):

* 10 measurements with syringe at 5ml of air
* Save data

High pressure (9ml):

* 10 measurements with syringe at 9ml of air
* Save data

### **Analysis Tasks**

1. **Create Pascal scale** — convert ADC values to Pascals using the MPX5700AP formula
2. **Linearity test** — check whether the relationship between syringe volume and pressure is linear
3. **Resolution determination** — calculate noise level and effective resolution

*These are the first two examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go\!*

### Development Log

### Results

Git repo:
Readme:
Development log:

### Feedback

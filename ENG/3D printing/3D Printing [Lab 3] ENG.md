## 3D Printing and CAD: Lab 3

### Objective

Design and print the first functional enclosure for the syringe holder that integrates all necessary components into one working whole. This is no longer a prototype on a breadboard — now everything must fit into a compact and functional enclosure.

#### Design Constraints

The solution must account for the following requirements:

**Pneumatic system:** The pressure sensor and solenoid valve must be as close to the syringe as possible. The goal is to minimize "dead" air volume in the system — every extra cubic centimeter of tubing and cavity adds delay and reduces precision. The shorter the path from the compressor to the syringe, the faster the system responds and the less energy is wasted building up pressure in empty space.

**~~Power supply:~~** ~~Since the UR5 digital IO is 24V, it makes sense to power the ESP32 module from the same source via a voltage regulator. Additionally, we then use two more voltage regulators: 24V->12V for the solenoid and 24V->5V for the Atom. The 24V power supply goes in the robot controller box and should be powerful enough for both the solenoid (typically 0.5-1A) and ESP32 (maximum 500mA with peripherals).~~

**Power supply:** Since the UR5 digital IO is 24V, it makes sense to power the ESP32 module from the same source via a voltage regulator. Additionally, we use a voltage regulator 24V→5V for the Atom. The solenoid is 24V, so it can be powered directly from the 24V supply (through a relay or MOSFET controlled by ESP32). The 24V power supply goes in the robot controller box and should be powerful enough for both the solenoid (typically 0.5-1A) and ESP32 (maximum 500mA with peripherals).

**Signal transmission:** ESP32 must send signals to the robot controller — either digital or analog depending on what you're measuring and how the robot software is configured. These signals must be reliable and noise-resistant, because robot movements and solenoid valve switching generate electromagnetic interference.

For analog signals, the ESP32 output (0-3.3V) must be amplified with an op-amp to the robot's 0-10V analog input range. For digital signals, there are two good options for level-shifting ESP32's 3.3V logic to the robot's 24V input: a MOSFET (e.g. 2N7002) with a pull-up resistor to 24V, or an optocoupler (e.g. PC817) if you want galvanic isolation and extra protection.

A WiFi router is connected to both the robot and ESP32, enabling network communication through protocols like Modbus TCP/IP.

**PCB as a structural element:** Since the electronics need to be near the syringe anyway, don't waste this opportunity — use the PCB board as part of the mechanical structure. The process is as follows: first print a separate frame, then print the enclosure blank with an opening for the PCB. Pause the print at the right height, place the PCB into the opening, and put the frame on top of the PCB so that it brings the board edges level with the highest component and the depth of the opening. Now continue printing on top — the frame holds the PCB in the correct position and ensures a strong attachment. This way the board becomes part of the structure, similar to how threaded rods or steel tubes add rigidity. The PCB provides strength exactly where the electronics are located and reduces the need for separate support structures.

**Mechanical strength:** Robot movements create inertial forces, pushing into the syringe creates reaction forces, and the entire structure must withstand this without bending. Use 16mm diameter tubes and M5 threaded rods to increase strength. You can either print these in with a pause (design an opening, pause print, place element, resume printing) or assemble them separately with screws and clips afterwards. Both are acceptable — what matters is that the structure doesn't bend or vibrate during use.

### Functional Requirements

The enclosure must fulfill the following functions:

**Mounting to the robot:** The syringe must attach to the robot's tool tip securely and precisely. The mounting point must be rigid enough that the syringe's position in space is predictable.

**Pneumatic dispensing:** A pneumatic fitting (threaded cap with a tube end) is screwed onto the back end of the syringe, which allows pushing silicone out in controlled amounts using the plunger. Each time the syringe is replaced, the pneumatic fitting must be manually unscrewed from the old syringe and screwed onto the new one. The enclosure design must allow easy access to the back end of the syringe so that the fitting replacement is convenient without removing enclosure parts.

**Quick replacement:** The syringe must be replaceable easily and quickly without tools. Think of it like a quick-change mount — click open, pull out the old syringe, put in a new one, click closed. When the syringe is in the right position and locked, there should be clear feedback: an audible click, a visible edge that sits flush with the enclosure, or a mechanical feel that the locking mechanism has fully engaged. The operator should not be left wondering whether the syringe is properly secured or not.

**Safety elements:** The M5 Atom Lite must be near the syringe, and its button can be used as an emergency stop button if something goes wrong. This gives the operator physical control over the system even if the robot software doesn't respond or the connection is lost.

**External connections:** The 24V power supply and GPIO connections are located in the robot controller box — this means cables must come from your enclosure that reach there. Account for cable path length and the ability to properly secure them so they don't get caught in the robot's movements.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

### Background Information

* **Component vs body**
  [https://www.youtube.com/watch?v=L6MMw-dfS8s](https://www.youtube.com/watch?v=L6MMw-dfS8s)
* **3D printing with steel inserts**
  [https://www.youtube.com/watch?v=XpDG8VxZsw4](https://www.youtube.com/watch?v=XpDG8VxZsw4)
* **Bolts perpendicular to layers**
  [https://www.youtube.com/watch?v=cC5KlelZlx4](https://www.youtube.com/watch?v=cC5KlelZlx4)
  And learning from others' mistakes
  [https://www.youtube.com/watch?v=A1d8aFPtQ8c](https://www.youtube.com/watch?v=A1d8aFPtQ8c)
* **Fusion project RPI Pico Box**
  [https://www.youtube.com/watch?v=wt1nlLSl8TQ](https://www.youtube.com/watch?v=wt1nlLSl8TQ)
* **Infill**
  [​​https://www.youtube.com/watch?v=nV3GbN6hLjg](https://www.youtube.com/watch?v=nV3GbN6hLjg)

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

### Tools

1. Fusion 360
2. Prusa Core One
3. Syringe 10ml N1
4. Universal Robotics UR5 robot
5. M5 Atom Lite
6. PCB board (from Data Acquisition Lab 3)
7. Solenoid valve 12V
8. Pneumatic fittings and tubing
9. 24V power supply (depending on configuration)
10. ~~BUCK 24V-\>12V~~
11. BUCK 24V-\>5V
12. …

*If the plan changes, update the tools too, or make a [draw.io](http://draw.io) diagram showing how things are functionally related.*

### Project Breakdown

* **Part 1: Component diagram** Create a schematic diagram (draw.io) showing all components: PCB, M5 Atom, solenoid valve, pressure sensor, syringe, pneumatic connections, cables. Mark what goes inside the enclosure and what stays outside.
* **Part 2: Internal component modeling** Model all internal components in Fusion 360 and plan how to place them using the print-pause method. Mark pause points and ensure that upper surfaces are level with the next layer.
* **Part 3: External enclosure design** Design the external enclosure that houses all components and meets the functional requirements (quick replacement, mechanical strength, cable outlets).
* **Part 4: Slicing plan** Create a print plan in Prusa Slicer with pauses. Document (video or screenshots) where the print pauses and which components are placed at each point.
* **Part 5: Printing and assembly** Print the enclosure, install components, test functionality.

*How far along are you? When will you be done? How could you go faster? — the usual questions*

### Development Log

### Results

Make sure to provide everything for grading:

* Work files (**4** points): Fusion 360 files
* Simulation (this time a component schematic diagram) (**4** points): draw.io
* Prototype (**4** points):
* Documentation (**4** points): specifications, design choice justifications, user manual

Fusion project:
Development log:
Version 3 initial assignment:

### Feedback

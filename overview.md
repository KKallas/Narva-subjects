# **Narva College Technical Curriculum**

## **Building a Robotic Dispensing System**

### **The Big Picture**

All assignments connect to one central project: creating a professional-grade dispensing system for the Dobot MG400 robot. This isn't academic busywork—it's solving a real market problem. The €3,000 Dobot sits in warehouses because nobody makes the tools it needs to be useful.

Students work in rotating teams across different courses, each developing essential subsystems. By the final Prototyping course, students cherry-pick the best solutions from all teams to build their own integrated system. Think of it as open-source collaboration with academic rigor.

The logic is simple: learn by building something that matters, together.

### **Assessment Philosophy**

Each course follows the same structure: six projects (five small, one comprehensive), working in five-person teams. Small projects worth 20 points each (5×20 \= 100 points). Integration project offers two paths: 40 points as supplement to assignments, or 100 points as standalone alternative. Maximum 100 points from base work, plus bonus opportunities.

The grading works on positive assessment—you get full points for what you complete correctly. This sounds easy until you hit the natural barriers: time constraints, technical roadblocks, team dynamics, and the inherent messiness of making things work in the real world. These forces ensure that perfect scores require exceptional work, not just showing up.

Five assessment categories per project:

* **Technical Files** (4/8 points): Code, schematics, design files  
* **Simulation/Analysis** (4/8 points): Testing, validation, performance analysis  
* **Physical Implementation** (4/8 points): Working prototype, build quality  
* **Documentation** (4/8 points): Clear specifications, design rationale, user guides  
* **Peer Evaluation** (4/8 points): Q\&A performance, constructive feedback to other teams  
* **Bonus points** (10 per assignment): Awarded for identifying and correcting instructor errors, providing substantive help to other teams, or demonstrating extraordinary collaboration and knowledge sharing within and beyond your team. If you feel you have earned it, remind the professor during your defense to ensure it gets noted.

---

## **Data Acquisition (6 ECTS)**

*Building the nervous system*

### **The Point**

Modern devices generate data constantly. This course teaches you to capture, clean, and analyze that data effectively. You'll progress from basic measurements to sophisticated closed-loop optimization systems, working with real hardware under actual industrial conditions. Students work in teams of 5 (4 teams total) to solve increasingly complex measurement challenges.

### **What You'll Learn**

Distinguish between data acquisition system components and understand hardware-based signal processing chains (hardware filtering). Master analog-to-digital converter principles and primary error sources. Design and implement custom solutions for practical data acquisition problems, selecting appropriate methodologies and hardware while using various data interfaces. Apply common post-processing techniques for measured data analysis, processing, characterizing and visualizing data with synchronized measurements across multiple devices. Analyze, document and present measurement data according to academic writing standards.

### **The Work**

Projects become progressively more challenging \- early projects are accessible to everyone, but later ones require the deep knowledge and skills developed through previous work. The final integration project combines all five preceding projects into a comprehensive system.

**Assignment 1: Digital Pressure Measurement & Baseline Characterization**  
Build a physical test bench by attaching the pressure sensor (e.g., MPX5700AP) to a syringe via tubing to allow for manual pressure application. Connect the sensor to the M5 Atom (ESP32) microcontroller. Implement ADC readings and perform all signal conditioning (offset, scaling, unit conversion) in software. Use Jupyter Lab to analyze the sensor's transfer function under real physical conditions and determine the system's effective resolution and noise floor within a target operating range (e.g., 4-7bar). This establishes your digital measurement baseline and its practical limitations.

**Subjects required:** Time allocation: 34 hours

* **Physical prototyping (sensor, syringe, tubing)**  
* **Arduino & ESP32**  
* **Jupyter lab**  
* **USB UART**  
* **Data analysis and visualization**  
* **Dobot basics**

**Assignment 2: Analog Signal Conditioning & Comparative Analysis**  
Using the test bench from Assignment 1, now design a dual-stage operational amplifier circuit in an electronics simulator to precondition the sensor signal specifically for the critical operating range (e.g., 4-7bar), maximizing resolution and noise immunity before the ADC. Finalize the design in Fusion 360 EDA for PCB ordering. Capture a new dataset with the analog front-end and perform a rigorous comparative analysis in Jupyter Lab against your Assignment 1 digital baseline. Quantify the resolution improvement and justify the choice of method based on application requirements.

**Subjects required:** Time allocation: 24 hours

* **Analog electronics simulation (https://www.youtube.com/watch?v=cjJoAo8DUhE)**  
* **Fusion 360 EDA basics**  
* **Digital filtering**  
* **NTP sync**  
* Arduino & ESP32 (for data capture with new PCB)  
* Jupyter lab (for comparative analysis)  
* USB UART

**Assignment 3: Noise-Resistant Systems** Now we add RC filtering to eliminate electrical interference from nearby Dobot motors, analog sensor noise etc. Add a comparator circuit for hardware-based threshold detection for the speed of pressure change to estimate how much of the material is left in the syringe or is it empty. Design a PCB with 2 out of 4 possible designs we have studied and build a simple autonomous testing rig to collect 1000s of datapoints.

**Subjects required:** Time allocation: 30 hours

* Analog electronics simulation  
* Arduino & ESP32  
* Jupyter lab  
* USB UART  
* **PCB ordering**  
* **Analog filtering**

**Assignment 4: Testbench and ML building** Test if fixed time window or comparator timing will give better result for volume estimation. Set up multiple systems to run in parallel to collect pressure buildup data under different known volumes, implement testbench and to collect input and output data for ML model building. Use a simple linear regression model to build a LUT for the realtime system and test the estimation system.  
**Subjects required:** Time allocation: 24 hours

* Arduino & ESP32  
* Jupyter lab  
* USB UART  
* Dobot basics  
* Filtering (Analog/Digital/ML)  
* **Scikit-learn**

**Assignment 5: Predictive Quality Model** Now we will draw the most common shapes that will be used to dispense silicone or solder paste. These would be straight line, arc and area fill. You will need to make a testbench with input and output buffer to hold the test plates, then the robot can do 5 before you need to add more clean plates and collect the done samples. Once done make high resolution images out of the plates and analyze which speed/pressure angular movement will give best solution

**Subjects required:** Time allocation: 36 hours

* Arduino & ESP32  
* Jupyter lab  
* USB UART  
* Dobot basics  
* Filtering (Analog/Digital/ML)  
* NTP sync  
* **Scikit-learn**

**Integration Project: Closed-Loop Optimization** This project requires implementing pressure-based process monitoring, volume estimation, and quality assessment \- capabilities developed incrementally in Assignments 1-5 but which Integration track students must design independently as a unified system. Design syringe dispenser for the UR5 or Dobot that will use compressed air to push out the silicone/solder paste and is capable of making high quality straight lines, arcs and fill an area (with uniform width and thickness of the material, keeping as close as possible to the planned shape). To test the system out make automated tests where you have input buffer clean plates, working area, taking high resolution pictures and output buffer. The buffer can be \>5 but would be better at 10-30

## **Evaluation Structure**

* **Smaller projects**: 5 projects × 20 points each \= 100 points maximum  
* **Integration project**: 100/40 points maximum  
* **Total possible**: 140 points  
* **Grade A threshold**: 91-100 points from the base 100

### **Assessment Criteria**

Each project evaluated on five components:

**Smaller Projects (up to 20 points each):**

* Software/Work files (4 points): software code, EDA design, or technical files  
* Simulation (4 points): appropriate simulation methods, analysis, testing  
* Prototype/Physical project (4 points): implementation, quality, functionality  
* Documentation (4 points): specifications, design choice justifications, implementation guide  
* Q\&A session and feedback (4 points): each relevant question earns points

**Integration Project (up to 40 points):**

* Software/Work files (8 points)  
* Simulation (8 points)  
* Prototype/Physical project (8 points)  
* Documentation (8 points)  
* Q\&A session and feedback (8 points)

### **Submission Requirements**

* Projects must be submitted 72 hours before defense  
* Teams have 5 minutes for project presentation  
* 15 minutes allocated for questions and feedback per team  
* Points awarded for questions asked; instructor justifies point deductions for work deficiencies

### **Grading Scale**

* **91-100 points**: A  
* **81-90 points**: B  
* **71-80 points**: C  
* **61-70 points**: D  
* **51-60 points**: E  
* **0-50 points**: F

**Minimum passing**: 51 points. Students can choose which projects to complete. Examples: two smaller projects \+ integration project (80 points), or three smaller projects (60 points).

**Important**: If physical implementation fails completely, maximum points remain achievable if the student demonstrates engineering problem-solving by explaining failure causes and proposing alternative approaches.

## **Contact Sessions Schedule**

* **\[13.09\]** Analog/digital measurement circuits, applications and operating principles  
* **\[13.09\]** ESP32 microprocessor and Arduino development environment  
* **\[13.09\]** Fusion 360 EDA for simple single-layer PCB boards  
* **\[4.10\]** Data collection and analysis using Jupyter Lab  
* **\[4.10\]** Assignment 1 defense  
* **\[4.10\]** Assignment 2 defense  
* **\[25.10\]** DoBot collaboration through signals  
* **\[25.10\]** Analog noise and filtering  
* **\[25.10\]** Analog filter workshop  
* **\[15.11\]** Assignment 3 defense  
* **\[15.11\]** Assignment 4 defense  
* **\[6.12\]** Machine learning models and uses scikit-learn  
* **\[6.12\]** Assignment 5 defense  
* **\[17.01\]** Additional assignment defense

---

## **Smart Solutions (6 ECTS)**

*Building the brain*

### **The Point**

Create IoT systems that even micro and small production facilities can actually use and reach positive ROI in less than a year. Transform physical device interfaces into web interfaces, implement proper security, and make everything accessible through standard protocols. Focus on practical solutions with maxim self reliance and multiple backup strategies. By centering on universal web interfaces rather than specialized hardware, students acquire skills and systematic thinking allowing extend the expected lifespan of heavy machinery well into the next 20 years. .

Students work in teams of 5 (4 teams total) to develop increasingly sophisticated systems. Each device gets its own intelligent user interface. This year's practical project involves creating a syringe dispenser for the Dobot robot with a user-friendly web interface for monitoring and control.

### **What You'll Learn**

Create completely self-sufficient integrated IoT systems. We will use ESP32 by M5Stack and Ardiono development environment and webpage interfaces for optimal cost/performance ratio.   
Beyond local access to device controls we will make MQTT database droplets to log and provide externally driven functionality. To keep things in the similar realm and provide LLMs access to the newly built interfaces we will build HTTP API  interface along with the web interface. Apply security measures in smart systems including secure MQTT brokers in cloud services and protected tunnels for web interface remote access.

### **The Work**

Projects become progressively more challenging \- early projects are accessible to everyone, but later ones require the deep knowledge and skills developed through previous work. The final integration project (Secure Remote Dispensing System) combines all five preceding projects into a comprehensive system requiring thorough understanding and application of previous work.

**Assignment 1: Basic Control Interface** Develop control interface for later use with  the pneumatic dispenser using M5Stack ESP32. Implement GPIO control for solenoid valves, configure WiFi access point, create simple web server. Create a network setup web page with QR code generations png  for direct user connection with basic authentication. Make it work, make it accessible.

**Subjects required:** Time allocation: 24 hours

* **Arduino & ESP32**  
* **ESP32 Communications basics (i2C, SPI, UART, AD, DA)**  
* **WEB development basics (preact & water.css)**

**Assignment 2: Secure Remote Access** Implement industrial-grade security. Set up Open VPN server on Digital Ocean, configure ESP32 as VPN client, implement certificate-based authentication. Enable encrypted communication for remote monitoring and control. Include proper key management and access logging.

**Subjects required:** Time allocation: 28 hours

* **ServerDroplet setup**  
* **Linux tools basics**  
* **Networking basics (IP, Routing, NAT, Firewall conf)**  
* **VPN Setup (openVPN)**

**Assignment 3: Cloud MQTT Infrastructure** MQTT is important because it is very similar to ROS communication system so compare this as an alternative for web api. Deploy and configure scalable MQTT broker on Digital Ocean platform. Implement secure communication channel for all MQTT traffic. MQTT Broker should support device authentication and message persistence. Implement proper credential management on ESP32 clients and demonstrate secure data exchange. Build a central server user interface as a webservice in Flask.

**Subjects required:** Time allocation: 30 hours

* Jupyter lab  
* **MQTT Protocol and parties (Publisher, Broker, Subscriber)**  
* **Flask**  
* **Database configuration**

**Assignment 4: Camera-Based Measurement System** Build visual measurement system using M5-CAM to provide ground truth validation for the pressure-based volume estimation developed in Data Acquisition. Create a dual-syringe testbench where material transfers between syringes via solenoid-controlled valves \- this allows repeated measurements without material waste. Mount camera to capture plunger position from consistent angle and lighting. Implement triggered image capture at test completion, edge detection to locate plunger position in frame, and conversion to volume measurement based on syringe geometry. Build web interface displaying captured image, detected plunger position, calculated volume, and comparison against pressure-derived estimate. System should log all measurements to database for later analysis of pressure-to-volume correlation accuracy across hundreds of test cycles.

**Subjects required:** Time allocation: 32 hours

* **ESP32Cam and** Arduino  
* WEB development basics  
* **Jupyter lab image processing**

**Assignment 5: HTTP-Based Remote Control with Time-Gated Access** Flask service on Digital Ocean with REST API for machine control. Implement user-activated access windows with configurable timeout \- remote control endpoints only functional when explicitly enabled by local user action. Status/monitoring endpoints remain accessible, control endpoints require active session. Self-documenting API with README endpoint for LLM integration. Authentication, rate limiting, audit logging. Demonstrate the full cycle: local activation, remote LLM-driven operation, automatic lockout on timeout.

**Subjects required:** Time allocation: 34 hours

* Arduino and ESP32  
* Flask  
* **LLM interface to read data and control individual machines**

**Integration: Complete Autonomous System** This project requires implementing secure remote access, cloud infrastructure, camera integration, and time-gated API control \- capabilities developed incrementally in Assignments 1-5 but which Integration track students must design independently as a unified system. VPN, MQTT, web interface, camera validation, HTTP API \- unified system with multiple access paths (local web, remote VPN, MQTT messages, LLM via HTTP). To be used as interface for the Data Acquisition class machine

## **Evaluation Structure**

* **Smaller projects**: 5 projects × 20 points each \= 100 points maximum  
* **Integration project**: 100/40 points maximum  
* **Total possible**: 140 points  
* **Grade A threshold**: 91-100 points from the base 100

### **Assessment Criteria**

Each project evaluated on five components:

**Smaller Projects (up to 20 points each):**

* Software/Work files (4 points): software repository, scripts, or technical files  
* Public server configuration setup (4 points): kubernetes, docker, ssh, pip  
* Prototype (4 points): implementation, quality, functionality  
* Documentation (4 points): specifications, design choice justifications, implementation guide  
* Q\&A session and feedback (4 points): each relevant question earns points

**Integration Project (up to 40 points):**

* Software/Work files (8 points)  
* Configuration files for automatic deployment (8 points)  
* Prototype/Physical project (8 points)  
* Documentation (8 points)  
* Q\&A session and feedback (8 points)

### **Submission Requirements**

* Projects must be submitted 72 hours before defense  
* Teams have 5 minutes for project presentation  
* 15 minutes allocated for questions and feedback per team  
* Points awarded for questions asked; instructor justifies point deductions for work deficiencies

### **Grading Scale**

* **91-100 points**: A  
* **81-90 points**: B  
* **71-80 points**: C  
* **61-70 points**: D  
* **51-60 points**: E  
* **0-50 points**: F

**Minimum passing**: 51 points. Students can choose which projects to complete. Examples: two smaller projects \+ integration project (80 points), or three smaller projects (60 points).

**Important**: If prototype fails to achieve full functionality, maximum points remain achievable if student demonstrates engineering problem-solving by explaining failure causes and proposing alternative approaches.

## **Contact Sessions Schedule**

* **\[13.9\]** WEB basics (preact and water.css)  
* **\[13.9\]** VPS and Linux tools / Containers and automation  
* **\[4.10\]** Assignment 1 defense  
* **\[4.10\]** Assignment 2 defense  
* **\[25.10\]** Routing basics  
* **\[25.10\]** Assignment 3 defense  
* **\[15.11\]** API  
* **\[15.11\]** Assignment 4 defense  
* **\[6.12\]** Assignment 5 defense  
* **\[24.1\]** Additional assignment defense

---

## **3D Printing and CAD (6 ECTS)**

*Building the body*

### **The Point**

Master the complete mechanical design workflow from concept to validated physical part. Learn parametric modeling, simulation-based optimization, and advanced manufacturing techniques that balance functional requirements with manufacturing constraints. Use AI-assisted generative design tools as part of modern engineering practice to create optimized designs for real-world scientific, educational, and industrial contexts.

Students work in teams of 5 (4 teams total) to solve increasingly sophisticated design challenges. Through iterative practical activities, students acquire skills to create optimized designs while learning to use machine learning-based generative design tools as part of contemporary engineering workflows.

### **What You'll Learn**

Create parametric models using constraint-based design principles in Fusion 360\. Design functional assemblies with various connection methods (threaded parts, bolts, adhesive joints). Apply generative design techniques for optimization and analyze and validate designs through parametric strength simulation. Master advanced 3D printing techniques including print-in-place mechanisms, multi-directional printing, and component addition. Prepare technical drawings according to ISO standards with appropriate dimensions and tolerances.

### **The Work**

Projects become progressively more challenging \- early projects are accessible to everyone, but later ones require the deep knowledge and skills developed through previous work. The final integration project combines all five preceding projects into a comprehensive system requiring thorough understanding and application of previous work.

**Assignment 1: Syringe Mount Design** Design simple mounting bracket for attaching standard syringes to Dobot MG400 robot arm. Create a properly constrained model in Fusion 360 that holds the syringe securely. Design must include appropriate attachment points for the robot arm interface. Submit complete constraint-based 3D model, technical drawings, and functional 3D-printed prototype.

**Subjects required:** Time allocation: 34 hours

* **Fusion 360 sketch and constraints**  
* **Fusion 360 assembly and vices**  
* **3D printer slicer and 1st print FDM limitations**

**Assignment 2: Print-in-Place Spring Clamp** Design single-piece printable spring-loaded clamp for quick syringe attachment and release on dispensing system. Create a mechanism including printed springs or flex elements, trigger/release mechanism, and retention details that all print as one unit without assembly. Design must account for appropriate clearances, material flexibility characteristics, and printable overhangs. Clamp should enable one-handed operation for syringe insertion or removal. Submit Fusion 360 model with proper constraints, print settings documentation, and functional printed prototype demonstrating spring action and secure retention properties.

**Subjects required:** Time allocation: 38 hours

* Fusion 360 sketch and constraints  
* Fusion 360 assembly and vices  
* 3D printer slicer  
* **Fusion 360 mechanical simulation**  
* **Fusion 360 2D drawing**

**Assignment 3: Initial System Integration** Design first-iteration dispenser prototype integrating all subsystems: pneumatic actuator mounting, ESP32 controller enclosure, solenoid valve housing, pressure sensor placement, and robot interface connections. Create system architecture showing component relationships, cable routing, tubing paths, and signal connections. Determine which components share enclosures versus require separate housings based on thermal, electrical, and maintenance considerations. Produce bill of materials, assembly sequence documentation, and print all custom mechanical parts. This design establishes baseline functionality \- systematic refinement based on operational testing occurs in the Prototyping course.

**Subjects required:** Time allocation: 22 hours

* **Integration graph**  
* **BOM**  
* Fusion 360 sketch and constraints  
* Fusion 360 assembly and vices  
* Fusion 360 mechanical simulation  
* **3D printer slicer for multidirectional printing**  
* **Assembly instruction documentation**

**Assignment 4: Generative vs. Engineered Automated Design**

Recreate the Assignment 1 syringe mount using two AI-assisted approaches, then test both against your original manual design. First, use Fusion 360's generative design with properly defined attachment points, load cases (dispenser mass, robot acceleration, cantilevered moment), keep-out volumes, and manufacturing constraints. Accept what the algorithm proposes.

Second, build an automated parametric model that encodes engineering reasoning—not aesthetic optimization but structural logic. This means programmatic rib placement along load paths, wall thickness calculated from expected stresses, infill patterns aligned with force directions, geometry that prints fast because it respects FDM constraints from the start. Use tools like nTop, Synera, Grasshopper, or Python scripting with FEA validation in the loop. The goal: a part that prints faster than the generative version while matching or exceeding its structural performance.

Print all three versions. Design a repeatable strength and deflection test using the MG400 as your measurement instrument—program consistent load application sequences and measure response at fixed points. Run multiple samples of each design through identical protocols.

Document the comparison: print time, mass, deflection under reference load, failure mode, and how well each method's predictions matched physical results. The core question isn't which part looks more sophisticated—it's whether encoding engineering knowledge into automated tools outperforms letting algorithms search the design space blindly.

**Subjects required:** Time allocation: 30 hours

* Fusion 360 generative design workflow  
* Parametric/automated modeling with embedded structural logic  
* FEA setup and load path analysis  
* FDM print optimization (orientation, supports, time)  
* MG400-based repeatable test fixture design  
* Quantitative comparison methodology

**Assignment 5: Modular Testbench Frame System** Design standardized aluminum frame (100x100mm base unit) with precise mounting features that accepts interchangeable 3D printed fixture plates. The metal frame provides rigidity, repeatability, and fixed registration to the robot base. Printed inserts snap or bolt into the frame and configure the workspace for specific tasks: syringe holder positions, plate buffers, camera mounts, sensor brackets. Design the frame for CNC manufacturing with proper ISO technical drawings, GD\&T for critical registration surfaces, and tolerance analysis for insert fit. Design minimum three different insert configurations demonstrating the system's flexibility. Validate manufactured frame against specifications and verify that inserts from different print batches achieve consistent positioning.

**Subjects required:** Time allocation: 24 hours

* Fusion 360 2D drawing environment  
* ISO technical drawing standards  
* GD\&T fundamentals  
* Tolerance stack-up analysis (frame-to-insert interface)  
* CNC manufacturing communication  
* Modular design principles  
* Metrology and inspection methods  
* Insert interchangeability validation

**Integration Project: Complete Dispensing System Mechanical Package** This project requires implementing parametric design, print-in-place mechanisms, system integration, generative optimization, and modular fixturing \- capabilities developed incrementally in Assignments 1-5 but which Integration track students must design independently as a unified system. Design complete mechanical package for the dispensing system: robot-mounted dispenser assembly with optimized tool mount, quick-change syringe mechanism, integrated electronics enclosure, and modular testbench frame with application-specific inserts. Produce manufacturing-ready documentation for all components \- 3D print files with validated settings, CNC drawings with GD\&T for metal frame, and assembly instructions. Validate the complete system: test generative design predictions against physical measurements, verify insert interchangeability across the frame system, confirm syringe changes can be performed one-handed. The delivered system must physically integrate with Smart Solutions electronics and Data Acquisition sensing infrastructure.

## **Evaluation Structure**

* **Smaller projects**: 5 projects × 20 points each \= 100 points maximum  
* **Integration project**: 100/40 points maximum  
* **Total possible**: 140 points  
* **Grade A threshold**: 91-100 points from the base 100

### **Assessment Criteria**

Each project evaluated on five components:

**Smaller Projects (up to 20 points each):**

* Work files (4 points): Fusion 360 files  
* Simulation (strength, thermal, iterative designs) (4 points): Fusion 360 analysis  
* Prototype (4 points): implementation, quality, functionality  
* Documentation (4 points): specifications, design choice justifications, implementation guide  
* Q\&A session and feedback (4 points): each relevant question earns points

**Integration Project (up to 40 points):**

* Software/Work files (8 points)  
* Simulation (8 points)  
* Prototype/Physical project (8 points)  
* Documentation (8 points)  
* Q\&A session and feedback (8 points)

### **Submission Requirements**

* Projects must be submitted 72 hours before defense  
* Teams have 5 minutes for project presentation  
* 15 minutes allocated for questions and feedback per team  
* Points awarded for questions asked; instructor justifies point deductions for work deficiencies

### **Grading Scale**

* **91-100 points**: A  
* **81-90 points**: B  
* **71-80 points**: C  
* **61-70 points**: D  
* **51-60 points**: E  
* **0-50 points**: F

**Minimum passing**: 51 points. Students can choose which projects to complete. Examples: two smaller projects \+ integration project (80 points), or three smaller projects (60 points).

**Important**: If prototype fails to achieve full functionality, maximum points remain achievable if student demonstrates engineering problem-solving by explaining failure causes and proposing alternative approaches.

## **Contact Sessions Schedule**

* **\[12.09\]** Fusion 360 and parametric design  
* **\[12.09\]** 3D printer, first print  
* **\[12.09\]** Multi-component object, spring in Fusion 360  
* **\[3.10\]** Project documentation  
* **\[3.10\]** Assignment 1 defense  
* **\[3.10\]** Assignment 2 defense  
* **\[24.10\]** FDM design specifics (strength lines, materials)  
* **\[24.10\]** Printer CAM for adding objects or multi-directional printing  
* **\[24.10\]** Fusion 360 generative design  
* **\[14.11\]** Assignment 3 defense  
* **\[14.11\]** Assignment 4 defense  
* **\[5.12\]** Test execution and documentation  
* **\[5.12\]** Assignment 5 defense  
* **\[17.01\]** Additional assignment defense

---

## **Prototyping (3 ECTS)**

*Bringing it all together*

### **The Point**

Transform three courses worth of components into one working system. Choose the best technologies developed by all teams, integrate them effectively, and create something ready for real-world use. This is where learning becomes creating.

Students enter with completed subsystems from Data Acquisition (sensing and measurement), Smart Solutions (control interfaces and remote access), and 3D Printing/CAD (mechanical design and fixtures). The challenge is integration and refinement, not starting from scratch.

Building on the first semester's three parallel courses, this course follows industrial development principles, starting with simple control systems and advancing to sensor integration and precision motion control. It focuses on extending the capabilities of small industrial robots (Dobot) by creating specialized tools. Since standard tools are not available for small robots, students develop industrial solutions like dispensing systems, UV curing devices, screwdrivers, and soldering solutions. These tools are designed both as educational materials and for actual production use, opening opportunities for small-scale entrepreneurship.

Through practical work, students learn about different materials and processes while considering industrial precision and safety requirements. Advanced students can submit their own project ideas that are not limited to Dobot accessories. Individual projects must receive instructor approval and require personalized curricula based on project complexity and objectives.

### **What You'll Learn**

Create complete but simple automation systems for industrial robots. Master ESP32-based control system creation and connection to industrial robots. Understand various sensors and their integration into systems. Comprehend precision tool operating principles and create reliable control systems. Design and assemble devices combining electronics, mechanics, and software. Acquire system documentation and maintenance skills through practical work.

### **The Work**

Students choose between two approaches:

**Progressive Milestones**   
Submit 5 smaller projects sequentially, each worth up to 20 points (total up to 100 points)

* **Milestone 1**: Comprehensive system specification (10h)  
* **Milestone 2**: Key technology validation prototype (16h)  
* **Milestone 3**: Integrated technical prototype (18h)  
* **Milestone 4**: Enclosed functional prototype (16h)  
* **Milestone 5**: Production-ready system (14h)

**Comprehensive Integration**  
Submit only final comprehensive project worth up to 100 points

Projects become progressively more challenging \- early projects are accessible to everyone, but later ones require the deep knowledge and skills developed through previous work. The comprehensive defense covers all five preceding milestone materials and skills, combining them into a complete system requiring thorough understanding and application of previous work.

**Important**: For comprehensive project selection (instead of milestones), submission for defense requires at least partially completed built prototype with thorough documentation. Purely theoretical work without a physical prototype will not qualify for defense in a comprehensive project approach, even if the presentation is otherwise thorough.

### **Milestone Details**

**Specification Document** Develop comprehensive specification for dispensing system. Include functional requirements, performance targets, interface definitions, and environmental conditions. Research commercial systems, identify key technologies, and define clear success criteria. Submit a detailed specification document with diagrams, use cases, and technical parameters that guide the entire development process.

*Assessment criteria: Technical specifications, analysis*

**Key Technology Prototype** Build working prototype of critical technical components specifically the dispensing actuator and precision dosing mechanism. Students choose actuation method (servo-driven, pneumatic, or hybrid) based on lessons learned from first-semester prototypes. This focused prototype should demonstrate core functionality without integration concerns. Validate basic dosing principle, volume control accuracy, and material compatibility. Submit working technical prototype, test results documenting performance against specifications, and potential modifications to original specifications based on findings.

*Assessment criteria: Schematics, programming \+ appropriate simulation methods, analysis, testing*

**Technical Integration Prototype** Create complete system prototype with all components in proper spatial positions but without final enclosure or user interface. This prototype should implement complete system architecture including ESP32 control, sensor integration, and robot communication. Verify system integration, identify compatibility problems, and validate complete workflow. Submit integrated prototype, interface documentation, and performance validation against specifications.

*Assessment criteria: Programming \+ simulation \+ implementation, quality, functionality*

**Enclosed Functional Prototype** Develop enhanced prototype with necessary enclosures, cable management, and user interface elements. This version should address practical considerations like maintenance accessibility, durability, and usability. Implement appropriate mounting methods, create professional connections, and ensure protection against environmental effects. Submit enclosed prototype, user manual draft, and operation validation in real conditions.

*Assessment criteria: Full technical package \+ specifications, design choice justifications*

**Production-Ready System** Complete dispensing system with all enhancements for reliability, manufacturability, and maintenance. This version should represent production-ready design that could be replicated. Optimize component selection, finalize documentation, and demonstrate reliable operation. Submit final system, complete documentation package (user manual, maintenance instructions, parts list), system operation demonstration with intended functionality, and GitHub repository link.

*Assessment criteria: Complete package, design choice justifications, implementation guide*

**Comprehensive Defense** For students choosing to present all work at once rather than sequential milestones, comprehensive defense covering all development process aspects. Should include thorough documentation of design evolution, technical challenges overcome, test results, and final performance validation. Students must demonstrate mastery over the entire development process and explain design decisions made. Students must justify technology choices based on first-semester experience \- demonstrating why selected approaches improve on earlier prototypes.

## **Evaluation Structure**

* **Progressive approach**: 5 milestones × 20 points each \= 100 points maximum  
* **Comprehensive approach**: 1 project \= 100 points maximum  
* **Grade A threshold**: 91-100 points

### **Assessment Criteria**

Each project evaluated on five components:

**Milestone Projects (up to 20 points each):**

* Software/Work files (4 points): technical specifications, schematics, programming  
* Simulation (4 points): appropriate simulation methods, analysis, testing  
* Prototype/Physical project (4 points): implementation, quality, functionality  
* Documentation (4 points): specifications, design choice justifications, implementation guide  
* Q\&A session and feedback (4 points): each relevant question earns points

**Comprehensive Project (up to 100 points):**

* Software/Work files (20 points)  
* Simulation (20 points)  
* Prototype/Physical project (20 points)  
* Documentation (20 points)  
* Q\&A session and feedback (20 points)

### **Submission Requirements**

* Projects must be submitted 72 hours before defense  
* Teams have 5 minutes for project presentation  
* 15 minutes allocated for questions and feedback per team  
* Points awarded for questions asked; instructor justifies point deductions for work deficiencies

### **Grading Scale**

* **91-100 points**: A  
* **81-90 points**: B  
* **71-80 points**: C  
* **61-70 points**: D  
* **51-60 points**: E  
* **0-50 points**: F

**Minimum passing**: 51 points. Students can choose between approaches:

* Submit milestones progressively achieving at least 51 points (e.g., at least 3 milestone projects)  
* Submit only comprehensive project achieving at least 51 points

**Important**: If prototype fails to achieve full functionality, maximum points remain achievable if student demonstrates engineering problem-solving by explaining failure causes and proposing alternative approaches.

## **Contact Sessions Schedule**

* **\[28.02\]** Specification writing, updating, milestones  
* **\[28.02\]** Key technology identification and testing methods  
* **\[21.03\]** Milestone 1 defense  
* **\[21.03\]** Milestone 2 defense / Common prototyping errors and how to avoid them  
* **\[18.04\]** Milestone 3 defense   
* **\[18.04\]** Documentation for production prototype  
* **\[30.05\]** Milestone 4 defense  
* **\[30.05\]** Milestone 5 defense  
* **\[TBD\]** Additional assignment defense

---

## **The Integration Logic**

This curriculum builds knowledge systematically while maintaining focus on practical outcomes. Each course contributes essential capabilities:

* **Data Acquisition**: Measurement and analysis capabilities  
* **Smart Solutions**: Communication and control infrastructure  
* **3D Printing/CAD**: Physical system design and manufacturing  
* **Prototyping**: System integration and production readiness

Students work across teams throughout the year, then integrate the best solutions from all groups in their final prototypes. This collaborative approach mirrors real engineering practice while ensuring individual mastery.

The result: students who can conceive, design, build, and deploy complete technical systems. Not just academic exercises, but solutions to real problems that create actual value.

That's the point.

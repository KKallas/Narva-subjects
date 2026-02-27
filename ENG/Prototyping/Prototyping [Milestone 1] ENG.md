## Prototyping: Milestone 1

You spent last semester building subsystems. Data Acquisition gave you sensors and measurement chains. Smart Solutions gave you web interfaces, VPN tunnels, and MQTT infrastructure. 3D Printing gave you mechanical design and manufacturing skills. Each of those courses produced working pieces. None of them produced a working system.

This course is where the pieces become a system. You enter with tested components and proven technologies. The challenge is integration, refinement, and making something that works reliably enough to use for real.

But before you touch a single wire or print a single part — you write a specification. Building without a specification is how projects die. You don't know what "done" looks like, you can't divide work across the team, and you can't test against anything. The specification is the contract between your present self (who has ideas) and your future self (who has to deliver).

This milestone is where your team commits to a project track and produces a specification detailed enough that another team could build the system from your document alone.

### Choose Your Track

Your team chooses one of three project tracks. Read all three carefully before committing.

| | Track A: Syringe Dispenser | Track B: Sumo Robot | Track C: MG400 Workbench |
| :--- | :--- | :--- | :--- |
| **Status** | Default track | Bonus project | Bonus project |
| **Continuity** | Continues semester 1 directly | New project, new domain | New project, extends MG400 ecosystem |
| **Robot platform** | Dobot MG400 | Android phone + SMARS-inspired chassis | Dobot MG400 |
| **Primary disciplines** | Sensing, pneumatics, precision control | Mobile computing, motor control, mechanical design | Modular fixturing, mechanical design, USB integration |
| **Hardware starting point** | Mostly available from semester 1 | Recycled phone, salvaged motors/batteries, 3D-printed chassis | Aluminum extrusion, 3D printed fixtures, USB-C devices |
| **Risk level** | Low — known problem, prior work exists | High — new territory, summer deadline | Medium — well-scoped mechanical problem |
| **Real-world motivation** | Commercial dispensing tools cost 10x what the robot costs | Narva College inaugural robot arena event this summer | Portable debug tools maximize learning time everywhere |

*Track A is the safe choice — you know the problem and have working components. Tracks B and C are bonus projects with more freedom and more risk. If your specification for a bonus track isn't convincing enough that you understand the problem deeply and can deliver, the instructor may ask you to switch to Track A.*

---

#### Track A: Syringe Dispenser

A Dobot MG400-mounted syringe dispensing system for applying silicone. This is the continuation of everything you built last semester — pressure sensing from Data Acquisition, web control from Smart Solutions, and mechanical mounting from 3D Printing.

**What you're dispensing and why:** The solenoid valve has a top cap that sits between the main body and two 4mm tubes. These tubes are glued into the main body using silicone. The task is to fill that small cap volume between the body and the tubes with silicone — precisely and repeatably. You already have the solenoid, a manually built version of the assembly, and a Fusion 360 model of the part. The geometry is known; the challenge is automating the fill.

**The actuation question:** How do you press the syringe plunger? Your specification must evaluate at least three options and justify the chosen approach:

* **Dobot pneumatic system** — uses the MG400's built-in air supply to push the plunger with compressed air. Simple control (on/off valve), but pressure regulation determines flow precision.
* **Small servo motor** — a servo mechanically presses the plunger. Gives direct position control over how far the plunger has moved, but adds mechanical complexity to the mount.
* **MG400 built-in rotary axis** — use the robot's own 4th axis rotation or Z-axis movement as the pressing mechanism. No extra actuator needed, but constrains the robot's positioning during dispensing.

Your specification must define the complete system: which actuation method and why, precision targets (fill volume accuracy, repeatability), control architecture from sensor to robot movement, and a test methodology for validating dispensing quality against the known cap geometry.

What "done" looks like for the full Prototyping course: a production-ready dispensing system that can draw straight lines, arcs, and area fills with uniform width and thickness, with automated testing using an input buffer of clean plates and an output buffer of completed samples.

You have the advantage of three courses worth of working prototypes, measured data, and documented failures. Use them. The specification should reference specific numbers from your semester 1 work — not theory, but what you actually measured.

---

#### Track B: Sumo Robot

A SMARS-inspired but even simpler battery-powered robot controlled by an Android phone, designed for sumo wrestling competitions at Narva College's inaugural robot arena event this summer. The design philosophy: start simple, recycle used electronics (old phones, salvaged motors, repurposed batteries), and build something that works first. The robots need to actually work and actually compete — this is not just an exercise.

**The phone-as-brain concept:** An older Android phone serves as the robot's brain. It has camera, compute power, display, and connectivity already built in. The phone connects to the motor chassis via USB OTG cable and runs the remote driving software. This means your "embedded system" is actually an Android app. The phone sits on top of the chassis, the OTG cable runs to a motor driver board, and the operator controls the robot remotely.

**The arena format:** The arena is 3×3 meters with a red circle in the center. The game puts 5 robots on each side — 10 robots total on the field. The red circle can barely fit 5 bots, which means positioning, pushing power, and agility all matter. Sumo rules apply: push opponents out, stay inside yourself.

Your specification must cover: chassis mechanical design (SMARS-inspired tracks, ground clearance, weight distribution for pushing — keep it simple and printable), motor selection and driver electronics (prefer recycled/salvaged components where possible), phone mounting and OTG interface protocol, software architecture (Android app for remote driving), arena dimensions and 5v5 game constraints, power budget and battery runtime, and a realistic timeline that ends with working robots before summer.

The summer deadline is real. Your specification must include a development schedule that accounts for parts ordering lead time, printing time, software development iterations, and at least two weeks of testing before the event. You need enough robots for a 5v5 match — plan accordingly.

---

#### Track C: MG400 Modular Workbench

A portable modular workbench that assembles around the Dobot MG400 robot, inspired by welder's T-slot tables. The concept: an aluminum extrusion frame that creates a 4-axis work area around the robot, with standardized mounting positions for 3D-printed tool holders. Debug and manufacturing tools mount at specific positions where the robot and operator can both reach them.

**The budget constraint:** Total extra cost beyond the MG400 robot itself must not exceed €1,000. This covers the frame, connectors, 3D-printed parts, tools, and USB-C hub — everything needed to turn a bare robot into a complete workstation.

**The portability requirement:** This workbench must be something a student can set up on a home kitchen table and easily pack up again. It should also adapt from one project to another within the school — swap tool holders, reconfigure positions, and redeploy for different tasks without rebuilding the frame. Think about it as a kit that goes from a carrying case to a working station in under 10 minutes.

**Reference tool list and approximate costs:**

| Tool | Purpose | Approximate Cost | Notes |
| :--- | :--- | :--- | :--- |
| USB video microscope | PCB inspection, solder joint quality | €30–80 | USB-C preferred |
| USB-C soldering iron (TS101 or similar) | Soldering and rework | €50–80 | PD-powered |
| Compact digital oscilloscope (DSO138 or USB-based) | Signal debugging | €30–150 | USB-C if available |
| USB signal generator | Test waveform generation | €20–50 | Function generator module |
| USB-C PD power supply (65W+) | Power for USB-C tools | €30–50 | GaN charger |
| USB-C hub (powered, 7+ ports) | Central device connectivity | €30–60 | Must support PD passthrough |
| Aluminum extrusion kit (2020/2040 profiles + brackets) | Frame structure | €80–150 | Cut to size or modular lengths |
| 3D printing filament | Tool holders, mounts, fixtures | €20–40 | PLA/PETG |
| Fasteners, T-nuts, corner brackets | Assembly hardware | €20–40 | M5 for 2020 profile |

*This is a starting reference — your specification must include your own researched BOM with actual product links and verified prices. The total must stay under €1,000.*

Your specification must cover: frame dimensions and aluminum extrusion profile selection (2020, 2040, etc.), integration with the MG400 work envelope and coordinate system, 3D-printed holder designs for each tool position, USB-C hub architecture and power delivery for connected devices, cable management, assembly/disassembly procedure, tool position specifications relative to the robot's coordinate frame, and a verification method for ensuring repeatable positioning after reassembly.

The goal: a student with this workbench can practice robotics, soldering, measurement, and debugging at home with the same tools available in the lab, and easily adapt the setup between projects at school. More tool access means more learning time.

---

### Objective

Write a comprehensive system specification for your chosen project track. The specification must include functional requirements, performance targets, interface definitions, component selections with justifications, risk analysis, and test criteria. It must be detailed enough that another team could build the system from your document alone.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

*Your specification is your blueprint for Milestones 2–5. If you change tracks later, you lose the specification work. Choose carefully and specify thoroughly.*

### Background Information

#### Shared Resources (all tracks)

* **How to write a technical specification**
  [https://www.youtube.com/watch?v=OA6BfCUBnuo](https://www.youtube.com/watch?v=OA6BfCUBnuo)
* **Requirements engineering — MoSCoW prioritization**
  [https://www.youtube.com/watch?v=jBMnTJa4ZnI](https://www.youtube.com/watch?v=jBMnTJa4ZnI)
* **draw.io for system diagrams**
  [https://app.diagrams.net/](https://app.diagrams.net/)
* **How to create a BOM (bill of materials)**
  [https://www.youtube.com/watch?v=fRhL7bXjITg](https://www.youtube.com/watch?v=fRhL7bXjITg)

#### Track A: Syringe Dispenser

* **Dobot MG400 documentation and work envelope**
  [https://www.dobot-robots.com/products/desktop-four-axis/mg400.html](https://www.dobot-robots.com/products/desktop-four-axis/mg400.html)
* **Commercial dispensing system benchmarks (Nordson EFD)**
  [https://www.nordson.com/en/divisions/efd/products/dispensing-systems](https://www.nordson.com/en/divisions/efd/products/dispensing-systems)
* **Time-pressure dispensing principles**
  [https://www.youtube.com/watch?v=jG5Lab-z3r4](https://www.youtube.com/watch?v=jG5Lab-z3r4)

#### Track B: Sumo Robot

* **SMARS — open-source modular robot platform (design inspiration)**
  [https://www.smarsfan.com/](https://www.smarsfan.com/)
* **Robot sumo competition rules (RobotChallenge)**
  [https://www.robotchallenge.org/fileadmin/user_upload/en_Mini_Sumo.pdf](https://www.robotchallenge.org/fileadmin/user_upload/en_Mini_Sumo.pdf)
* **Android USB Host (OTG) mode documentation**
  [https://developer.android.com/develop/connectivity/usb/host](https://developer.android.com/develop/connectivity/usb/host)
* **DC motor control with H-bridge (TB6612FNG)**
  [https://www.youtube.com/watch?v=JPPTRj0KWFg](https://www.youtube.com/watch?v=JPPTRj0KWFg)
* **Differential drive / tank steering kinematics**
  [https://www.youtube.com/watch?v=aE7RosGMcwg](https://www.youtube.com/watch?v=aE7RosGMcwg)
* **Android app development with Kotlin**
  [https://developer.android.com/courses](https://developer.android.com/courses)

#### Track C: MG400 Modular Workbench

* **Aluminum extrusion (2020 V-slot) system guide**
  [https://www.youtube.com/watch?v=pT03yWCTmGg](https://www.youtube.com/watch?v=pT03yWCTmGg)
* **Dobot MG400 work envelope and coordinate system**
  [https://www.dobot-robots.com/products/desktop-four-axis/mg400.html](https://www.dobot-robots.com/products/desktop-four-axis/mg400.html)
* **USB-C Power Delivery explained**
  [https://www.youtube.com/watch?v=LhTd5siGE1c](https://www.youtube.com/watch?v=LhTd5siGE1c)
* **Modular fixturing concepts (welding table accessories)**
  [https://www.youtube.com/watch?v=mH2h0NBlYeg](https://www.youtube.com/watch?v=mH2h0NBlYeg)
* **Portable electronics workstation design ideas**
  [https://www.youtube.com/watch?v=YLIPaSk5vos](https://www.youtube.com/watch?v=YLIPaSk5vos)

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

### Tools

1. Fusion 360 (concept mockups and spatial analysis)
2. draw.io or Excalidraw (system architecture diagrams)
3. Git repository
4. VS Code or text editor (specification document)
5. Jupyter Lab (feasibility calculations and analysis)
6. Spreadsheet tool (BOM, cost analysis, comparison tables)

Track-specific additions:

* Track A: Oscilloscope, pressure test bench, semester 1 prototype for reference measurements
* Track B: Android phone for OTG feasibility testing, motor driver board for bench tests
* Track C: Calipers, measuring tape, MG400 access for work envelope verification

*If the plan changes, update the tools too, or make a [draw.io](http://draw.io) diagram showing how things are functionally related.*

### What Goes Into a Specification

This section teaches you what a proper engineering specification looks like. Each subsection below must appear in your specification document. The examples use the syringe dispenser since everyone understands that context from semester 1 — adapt them to your chosen track.

*You have 10 hours. A complete but shallow specification beats a deep but incomplete one. Cover all sections first, then deepen the areas most critical to your track.*

#### System Overview

One-paragraph description of what the system does. A context diagram showing the system boundary — what is inside vs. outside the system. Who uses it, who maintains it, what environment it operates in.

#### Functional Requirements

Numbered list of things the system MUST do. Each requirement must be testable — you can write a test that proves it works or doesn't.

Use MoSCoW prioritization:
* **MUST** — system fails without this
* **SHOULD** — important but not critical
* **COULD** — nice to have if time allows

Example: *"FR-001 (MUST): The system shall dispense a continuous line of material with uniform width (variation < 10% of target width) at speeds between 5 mm/s and 50 mm/s."*

Aim for at least 10 functional requirements.

#### Performance Targets

Quantitative specifications with units and measurement methods. Use this table format:

| Parameter | Target | Minimum Acceptable | Measurement Method |
| :--- | :--- | :--- | :--- |
| Line width accuracy | ±0.1 mm | ±0.3 mm | Microscope measurement |
| Dispensing speed | 5–50 mm/s | 5–20 mm/s | Robot trajectory timing |
| Syringe change time | < 30 s | < 60 s | Stopwatch |

Fill this with your track's actual parameters.

#### System Architecture

Block diagram showing all subsystems and their interfaces. For each interface, specify: protocol, signal levels, data format. Reference the three prerequisite courses explicitly — which subsystem came from which course (or is new for this project).

#### Component Selection and Justification

For each major component: what it is, why you chose it, what alternatives you considered. Use the decision-making pattern from Data Acquisition Lab 2 (where you compared voltage divider vs. op-amp) — same structure, different subject matter.

Include a preliminary BOM (bill of materials) with estimated costs. Track B and C teams: include where to order each component and estimated lead time.

#### Mechanical Concept

Dimensioned concept sketches — either Fusion 360 renders or hand sketches with measurements. Identify critical dimensions and tolerances. Justify material choices.

At least one critical dimension must be physically verified — measured from real hardware, a datasheet, or the robot itself. Don't guess — measure.

#### Electrical Architecture

Block-level schematic showing all electrical connections. Power budget: voltage rails, current consumption per subsystem, total draw vs. supply capacity. Signal list: what connects to what, voltage levels, protocols.

#### Software Architecture

Module diagram showing software components and their relationships. Communication protocol definitions. State machine or flowchart for main control logic.

Track B teams: this is where your Android app architecture lives. Define the OTG communication protocol, the motor control interface, and the user interface.

#### Risk Analysis

Table of identified technical risks. Each risk gets: description, likelihood (H/M/L), impact (H/M/L), and a mitigation strategy. Identify at least 5 real risks — not generic "things might break" but specific technical risks you've identified during specification writing.

Example: *"Risk: ESP32 ADC nonlinearity causes >5% error at high pressure. Likelihood: M. Impact: H. Mitigation: Use op-amp signal conditioning from DA Lab 2 design, validate with calibration at 5 pressure points."*

#### Test Plan

For each functional requirement: how will you test it? What equipment is needed? What constitutes pass/fail? This directly feeds Milestone 2 (key technology validation) — the tests you define here are the tests you'll run there.

#### Development Timeline

Map remaining Milestones 2–5 to specific deliverables. Who does what (team role assignments). Dependencies between tasks. For Track B: the timeline must end with working robots before the summer arena event — work backwards from that date.

### Project Breakdown

**Phase 1: Research and Benchmarking**

- [ ] Survey existing commercial or open-source solutions for your chosen track
- [ ] Document at least 3 reference systems with their specifications
- [ ] Identify key differentiators and limitations of existing solutions

**Phase 2: Requirements Definition**

- [ ] Write functional requirements (minimum 10)
- [ ] Define performance targets with measurement methods
- [ ] Identify all external interfaces (mechanical, electrical, software)

**Phase 3: System Architecture**

- [ ] Create system block diagram in draw.io
- [ ] Define all inter-subsystem interfaces
- [ ] Map subsystems to prerequisite course work (what exists vs. what's new)

**Phase 4: Feasibility Analysis**

- [ ] Component selection with alternatives analysis
- [ ] Preliminary BOM with cost estimate
- [ ] Power budget calculation
- [ ] Identify top 5 technical risks with mitigation strategies

**Phase 5: Concept Design**

- [ ] Mechanical concept sketches with critical dimensions
- [ ] Electrical block diagram with signal list
- [ ] Software architecture diagram

**Phase 6: Test Planning and Timeline**

- [ ] Write test plan for each functional requirement
- [ ] Create development timeline for Milestones 2–5
- [ ] Assign team roles and responsibilities

*How far along are you? When will you be done? How could you go faster? — the usual questions*

### Feasibility Analysis

Since you are writing a specification and not building yet, the "simulation" for this milestone is analytical work that validates whether your specification is physically feasible. Don't spec something you can't build.

#### Analysis 1: Physical Feasibility Check

Pick the most critical performance parameter from your specification. Show with calculations or a simple simulation that your design can achieve it.

**Track A example:** Calculate the pressure required to achieve your target flow rate through a given needle gauge. Use Poiseuille's law or manufacturer data. Does your pneumatic system supply enough pressure? Is the flow rate compatible with your target dispensing speed?

**Track B example:** Calculate the torque required to push an opponent robot (estimated mass) out of the arena within the time limit. Does your selected motor provide enough torque through the gear ratio? What is the battery runtime at full load?

**Track C example:** Model the MG400 work envelope in Fusion 360. Place your workbench frame and tool holders in the model. Does the robot reach all required positions without collision? What is the maximum tool height before the robot cannot reach over it?

#### Analysis 2: Cost-Performance Tradeoff

Identify one design decision where you face a cost-performance tradeoff. Present the analysis in the same format as the voltage divider vs. op-amp comparison from Data Acquisition Lab 2:

* Option A: description, cost, performance
* Option B: description, cost, performance
* Decision and rationale

#### Analysis 3: Prior Work Review

**Track A:** Review the measurement data, web interface performance, or mechanical design from semester 1. What worked? What needs improvement? Reference actual numbers from your previous lab work — not theory, but what you measured. Use this data to justify specification choices.

**Tracks B and C:** Since there is no semester 1 predecessor, perform a technology survey instead. Find 3 comparable projects (GitHub repos, Instructables, research papers, YouTube builds) and analyze their specifications vs. actual results. What can you learn from their experience? What mistakes will you avoid?

*These are your first analyses. Add more as you discover questions during specification writing. A specification that raises no questions is a specification that didn't look deeply enough.*

### Development Log

### Results

**All tracks submit:**

| Deliverable | Description |
| :--- | :--- |
| Specification document | PDF or Markdown — all sections from "What Goes Into a Specification" above |
| System architecture diagram | draw.io — block diagram with interfaces |
| Feasibility analysis notebook | Jupyter Lab — all three analyses with calculations |
| BOM spreadsheet | Components, quantities, unit costs, total, and supplier links |
| Concept models | Fusion 360 — dimensioned concept mockups |
| Development timeline | Gantt chart or milestone table for Milestones 2–5 |

Git repo:
Specification document:
System architecture diagram:
Feasibility analysis notebook:
BOM spreadsheet:
Development log:

### Grading

Each category is worth up to 4 points. Total: 20 points.

**Work Files (4 points) — Specification Completeness**

All required specification sections present and substantive (not placeholders). Fusion 360 concept models exist and are properly constrained. draw.io diagrams are clear and complete. Files are organized in a git repository with meaningful commit history.

* 4 pts: All sections complete with depth
* 3 pts: Most sections complete, minor gaps
* 2 pts: Core sections only, significant gaps
* 1 pt: Skeletal document
* 0 pts: Not submitted

**Simulation / Analysis (4 points) — Feasibility Validation**

Physical feasibility calculation is correct and relevant. Cost-performance tradeoff analysis uses real numbers. Semester 1 retrospective (Track A) references actual measured data, or technology survey (Tracks B/C) references real projects. Calculations are reproducible in submitted Jupyter notebook.

* 4 pts: All three analyses complete with correct methodology
* 3 pts: Two analyses complete
* 2 pts: One analysis complete
* 1 pt: Attempt without rigor
* 0 pts: No analysis

**Prototype / Physical (4 points) — Concept Viability**

Mechanical concept has realistic dimensions (not fantasy numbers). Component selections are actual purchasable parts with datasheets. Power budget adds up (total consumption vs. supply capacity). At least one critical dimension has been physically verified (measured from real hardware or datasheet). For Track A: semester 1 prototype photos/measurements included as reference.

* 4 pts: Concept is buildable as specified
* 3 pts: Mostly buildable, minor feasibility gaps
* 2 pts: Major feasibility gaps identified
* 1 pt: Dimensions or components are not realistic
* 0 pts: No concept design

**Documentation (4 points) — Specification Quality**

Requirements are numbered, testable, and prioritized (MUST/SHOULD/COULD). Diagrams use proper notation and are readable. Risk analysis identifies real risks (not generic). Test plan maps to specific requirements. Writing is clear, organized, and free of ambiguity.

* 4 pts: Specification could guide development by another team
* 3 pts: Clear but needs clarification in places
* 2 pts: Understandable only to the authors
* 1 pt: Disorganized
* 0 pts: Not documented

**Q&A Session and Feedback (4 points) — Defense Performance**

Team can explain and defend every specification choice. Team can identify weaknesses and unknowns in their own specification. Team provides substantive questions and feedback to other teams' specifications.

* 4 pts: Strong defense and active participation
* Scale down proportionally

### Feedback

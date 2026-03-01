## Prototyping: Milestone 1

You spent last semester building subsystems. Data Acquisition gave you sensors and measurement chains. Smart Solutions gave you web interfaces, VPN tunnels, and MQTT infrastructure. 3D Printing gave you mechanical design and manufacturing skills. Each of those courses produced working pieces. None of them produced a working system.

This course is where the pieces become a system. You enter with tested components and proven technologies. The challenge is integration, refinement, and making something that works reliably enough to use for real.

But before you touch a single wire or print a single part — you write a specification. Building without a specification is how projects die. You don't know what "done" looks like, you can't divide work across the team, and you can't test against anything. The specification is the contract between your present self (who has ideas) and your future self (who has to deliver).

This milestone is where your team chooses a project track and produces a specification detailed enough that another team could build the system from your document alone.

---

#### A: Syringe Dispenser

A Dobot MG400-mounted syringe dispensing system for applying silicone. This is the continuation of everything you built last semester — pressure sensing from Data Acquisition, web control from Smart Solutions, and mechanical mounting from 3D Printing.

**What you're dispensing and why:** The solenoid valve has a top cap that sits on the solenoid body. Two 4-millimeter tubes are attached to this cap. These tubes are glued into place with silicone. The task is to fill the small volume between the cap body and the tubes with silicone — precisely and repeatably. You already have the solenoid cap, a manually built version of the assembly, and a Fusion 360 model of the part. The geometry is known; the challenge is automating the fill. The cap design itself can also be modified.

**The actuation question:** How do you press the syringe plunger? Your specification must choose the most suitable of three options with logical justification:

* **Dobot pneumatic system** — uses the MG400's built-in air supply to push the plunger with compressed air. Simple control (open/closed/over- and under-pressure valve), but pressure regulation determines flow precision.
* **Small servo motor** — a servo mechanically presses the plunger. Gives direct position control over how far the plunger has moved, but adds mechanical complexity to the mount.
* **MG400 built-in rotary axis** — use the robot's own 4th axis rotation or Z-axis movement as the pressing mechanism. No extra actuator needed, but constrains the robot's positioning during dispensing.

Your specification must define the complete system: which actuation method and why, precision targets (fill volume accuracy, repeatability), control architecture from sensor to robot movement, and a test methodology for validating dispensing quality against the known cap geometry.

What "done" looks like at the end of the Prototyping course: a production-ready dispensing system that can draw straight lines, arcs, and area fills with uniform width and thickness, with automated testing using an input buffer of clean plates and an output buffer of completed samples.

You have the advantage of three courses worth of working prototypes, measured data, and documented failures. Use them.

---

#### B: Sumo Robot

A SMARS-inspired but even simpler battery-powered robot controlled by an Android phone, designed for sumo wrestling competitions at Narva College's robot arena inaugural event this summer. Design philosophy: start simple, reuse old electronics (phones can be systematically reused) and build something that works first. The robots must actually work — drive, measure distance ahead, see color underneath, see the camera view ahead, and position themselves by reading QR codes from the ceiling and their locations.

**The phone-as-brain concept:** An older Android phone serves as the robot's brain. It has camera, compute power, display, and connectivity already built in. The phone connects to the motor chassis via USB OTG cable and ESP32 MCU which interfaces the remote driving software. This means your "embedded system" is actually an Android app. The phone sits on top of the chassis, the OTG cable runs to the motor driver board, and the operator controls the robot remotely.

**The arena format:** The arena is 3×3 meters with a red circle in the center. The game puts 5 robots on each side — 10 robots total on the field. The red circle can barely fit 5 bots, which means positioning, pushing power, and agility all matter. Sumo rules apply: push opponents out, stay inside yourself.

Your specification must cover: chassis mechanical design (SMARS-inspired tracks, ground clearance, weight distribution for pushing — keep it simple and printable), motor selection and driver electronics (prefer recycled/salvaged components where possible), phone mounting and OTG interface protocol, software architecture (Android app for remote driving), arena dimensions and 5v5 game constraints, power budget and battery runtime, and a realistic timeline that ends with working robots before summer.

The summer deadline is real. Your specification must include a development schedule that accounts for parts ordering lead time, printing time, software development iterations, and at least two weeks of testing before the event. You need enough robots for a 5v5 match — plan accordingly.

---

#### C: MG400 Modular Workbench

This project consists of three interconnected subprojects that together form a complete portable workstation around the Dobot MG400 robot. The goal: a student can take the entire workflow — robot, worktable, tools, and documentation — home, or reconfigure it between projects at school. If the documentation is good enough, the same workflow can be replicated on another identical robot, even in another country.

**Budget:** Your specification must define and justify a target budget for the entire kit (beyond the MG400 robot itself). How much can the complete kit cost for the school to offer it as a student rental? That number must come from your analysis, not from a prescribed limit.

##### Subproject 1: Worktable

A modular worktable where 3D-printed constructions — tool holders, jigs, fixtures — can be easily mounted. The table must create a work area around the robot where both the robot and the operator can reach the tools.

The core design question: how do you build a table that is rigid enough for work, light enough to carry, and modular enough to reconfigure? Options range widely — aluminum extrusion (2020/2040), PVC sheets with CNC-drilled pin grids, 3D-printed connectors with metal tubing, plywood with CNC-cut sockets — and each approach has its own tradeoffs between rigidity, weight, cost, and modularity. Your job is to choose and justify.

Critical requirements:
* Must integrate with the MG400 work envelope and coordinate system
* 3D-printed holder mounting positions must be documented relative to the robot's coordinate frame
* Positions must be repeatable after disassembly and reassembly
* Full documentation must be sufficient for someone else to reproduce the same setup

##### Subproject 2: Transport System

A transport box (cardboard, plywood, foam case, etc.) that fits the Dobot MG400, the worktable, and all tools. It must be durable enough for a student to safely transport the kit between school and home.

Your specification must cover:
* Internal dimensions and layout — everything must fit in its place with no loose space for items to rattle around
* Protective padding for the robot and tools
* Weight and carry capacity — one person must be able to carry it
* Material choice and cost
* Inventory checklist inside the box (to verify everything is returned)

##### Subproject 3: Electronics Tools

A set of electronics tools covering soldering, measurement, debugging, and signal analysis. Prefer USB-C powered tools where possible — one power supply and hub covers the entire kit.

| Tool | Purpose | Notes |
| :--- | :--- | :--- |
| Soldering iron (TS101 or similar) | Soldering and rework | USB-C PD powered |
| Oscilloscope / multimeter | Signal measurement and debugging | Compact, USB-based or DSO138 |
| Power supply | Adjustable voltage for circuit power | USB-C PD if possible |
| Signal generator | Test waveform generation | Function generator module |
| Serial analyzer | UART/SPI/I2C debugging | Saleae Logic or similar |
| Soldering microscope | PCB inspection, solder joint quality | USB video microscope |
| USB-C PD power supply (65W+) | Power for all USB-C tools | GaN charger |
| USB-C hub (powered, 7+ ports) | Central connectivity | Must support PD passthrough |

*This is a starting reference — your specification must include your own researched BOM with actual product links and verified prices.*

Your specification must cover all three subprojects with BOM, dimensions, material choices, and justifications. Every technical parameter — budget, weight, dimensions, number of tools, power capacity — is something you define and justify, not something prescribed for you. The entire system must be documented well enough that another team could reproduce it.

---

### Objective

Write a comprehensive system specification for your chosen project track. The specification must include functional requirements, performance targets, interface definitions, component selections with justifications, risk analysis, and test criteria. It must be detailed enough that another team could build the system from your document alone.

### Background Information

#### Shared Resources

#### A: Syringe Dispenser

* **Dobot MG400 documentation and work envelope**
  [https://www.dobot-robots.com/products/desktop-four-axis/mg400.html](https://www.dobot-robots.com/products/desktop-four-axis/mg400.html)
* **Commercial dispensing system benchmarks**

  tba
* **Time-pressure dispensing principles**
  [https://www.youtube.com/watch?v=jG5Lab-z3r4](https://www.youtube.com/watch?v=jG5Lab-z3r4)

#### B: Sumo Robot

* **SMARS — open-source modular robot platform (design inspiration)**
  [https://www.smarsfan.com/](https://www.smarsfan.com/)
* **mecArena**
  [https://github.com/KKallas/Robot-Arena/blob/main/BOT-SPECIFICATIONS.md](https://github.com/KKallas/Robot-Arena/blob/main/BOT-SPECIFICATIONS.md)
* **Android USB Host (OTG) mode documentation**
  [https://developer.android.com/develop/connectivity/usb/host](https://developer.android.com/develop/connectivity/usb/host)
* **DC motor control**
  [https://www.youtube.com/watch?v=ygrsIqWOh3Y&t=77s](https://www.youtube.com/watch?v=ygrsIqWOh3Y&t=77s)
* **Differential drive / tank steering kinematics**
  [https://www.youtube.com/watch?v=aE7RosGMcwg](https://www.youtube.com/watch?v=aE7RosGMcwg)
* **Android terminal (Python and Flask)**
  [https://www.youtube.com/watch?v=HarwU8bxvTQ](https://www.youtube.com/watch?v=HarwU8bxvTQ)

#### C: MG400 Modular Workbench

* **Dobot MG400 work envelope and coordinate system**
  [https://www.dobot-robots.com/products/desktop-four-axis/mg400.html](https://www.dobot-robots.com/products/desktop-four-axis/mg400.html)

* **Modular fixturing concepts**
  tba


*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

### Tools

1. Fusion 360 (concept mockups and spatial analysis)
2. draw.io or Excalidraw (system architecture diagrams)
3. Git repository
4. VS Code or text editor (specification document)
5. Jupyter Lab (feasibility calculations and analysis)
6. Spreadsheet tool (BOM, cost analysis, comparison tables)

* A: Oscilloscope, pressure test bench, semester 1 prototype for reference measurements
* B: Android phone for OTG feasibility testing, motor driver board for bench tests
* C: Calipers, measuring tape, MG400 access for work envelope verification

*If the plan changes, update the tools too, or make a [draw.io](http://draw.io) diagram showing how things are functionally related.*

### What Goes Into a Specification

This section teaches you what a proper engineering specification looks like. Each subsection below must appear in your specification document. The examples use the syringe dispenser since everyone understands that context from semester 1 — adapt them to your chosen project.

*You have 10 hours. A complete but shallow specification beats a deep but incomplete one. Cover all sections first, then deepen the areas most critical to your project.*

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

Quantitative specifications with units and measurement methods. Every parameter is something you define — what is critical to measure for your system, what is the target, and what is the minimum acceptable level? Use this table format:

| Parameter | Target | Minimum Acceptable | Measurement Method |
| :--- | :--- | :--- | :--- |
| ... | ... | ... | ... |
| ... | ... | ... | ... |
| ... | ... | ... | ... |

Choose parameters that are critical for your project. The numbers must come from your analysis — don't pull them out of thin air or guess, justify why that specific value.

#### Component Selection and Justification

For each major component: what it is, why you chose it, what alternatives you considered. Use the decision-making pattern from Data Acquisition Lab 2 (where you compared voltage divider vs. op-amp) — same structure, different subject matter.

Include a preliminary BOM (bill of materials) with estimated costs. B and C teams: include where to order each component and estimated lead times.

#### Mechanical Concept

Dimensioned concept sketches — either Fusion 360 renders or hand sketches with measurements. Identify critical dimensions and tolerances. Justify material choices.

At least one critical dimension must be physically verified — measured from real hardware, a datasheet, or the robot itself. Don't guess — measure.

#### Electrical Architecture

Block-level schematic showing all electrical connections. Power budget: voltage rails, current consumption per subsystem, total draw vs. supply capacity. Signal list: what connects to what, voltage levels, protocols.

#### Software Architecture

Module diagram showing software components and their relationships. Communication protocol definitions. State machine or flowchart for main control logic.

B teams: this is where your Android app architecture lives. Define the OTG communication protocol, the motor control interface, and the user interface.

#### Test Plan

For each functional requirement: how will you test it? What equipment is needed? What constitutes pass/fail? This directly feeds Milestone 2 (key technology validation) — the tests you define here are the tests you'll run there.

#### Development Timeline

Map remaining Milestones 2–5 to specific deliverables. Who does what (team role assignments). Dependencies between tasks. For B: the timeline must end with working robots before the summer arena event — work backwards from that date.

### Project Breakdown

**Phase 1: Research and Benchmarking**

- [ ] Survey existing commercial or open-source solutions for your chosen project
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

**A example:** Calculate the pressure required to achieve your target flow rate through a given needle gauge. Use Poiseuille's law or manufacturer data. Does your pneumatic system supply enough pressure? Is the flow rate compatible with your target dispensing speed?

**B example:** Calculate the torque required to push an opponent robot (estimated mass) out of the arena within the time limit. Does your selected motor provide enough torque through the gear ratio? What is the battery runtime at full load?

**C example:** Model the MG400 work envelope in Fusion 360. Place your workbench frame and tool holders in the model. Does the robot reach all required positions without collision? What is the maximum tool height before the robot cannot reach over it?

#### Analysis 2: Cost-Performance Tradeoff

Identify one design decision where you face a cost-performance tradeoff. Present the analysis in the same format as the voltage divider vs. op-amp comparison from Data Acquisition Lab 2:

* Option A: description, cost, performance
* Option B: description, cost, performance
* Decision and rationale

#### Analysis 3: Prior Work Review

**A:** Review the measurement data, web interface performance, or mechanical design from semester 1. What worked? What needs improvement? Reference actual numbers from your previous lab work — not theory, but what you measured. Use this data to justify specification choices.

**B and C:** Since there is no semester 1 predecessor, perform a technology survey instead. Find 3 comparable projects (GitHub repos, Instructables, research papers, YouTube builds) and analyze their specifications vs. actual results. What can you learn from their experience? What mistakes will you avoid?

*These are your first analyses. Add more as you discover questions during specification writing. A specification that raises no questions is a specification that didn't look deeply enough.*

### Development Log

### Results

**For the defense you only need a git repository link.**

The repository must contain:

* **Project description in `.md` format** — specification, simulations, analyses, and explanations of how to carry out the project. Markdown is the primary format for all documentation.
* **Software file archives** — if you used software like Fusion 360, FlatCAM, etc., the submission version must be uploaded to git as an archive (`.zip`, `.7z`). The instructor must be able to test the exact version you are defending.
* **Milestone for each milestone** — create a GitHub/GitLab milestone for each subsequent milestone (2–5). This is your development schedule and task tracking in one place.
* **First prototype shopping list** — a list of components that need to be ordered or purchased to build the Milestone 2 technology prototype. For each component: name, quantity, supplier, price, and lead time. The goal is to place orders immediately after the defense so no time is wasted.

| Deliverable | Format |
| :--- | :--- |
| Specification document | `.md` — all sections from "What Goes Into a Specification" above |
| System architecture diagram | draw.io (`.drawio` file in repo) — block diagram with interfaces |
| Feasibility analysis notebook | Jupyter Lab (`.ipynb` file in repo) — all three analyses with calculations |
| BOM table | `.md` or `.csv` — components, quantities, unit costs, total, and supplier links |
| Concept models | Fusion 360 (`.f3z` archive in repo) — dimensioned concept mockups |
| Development timeline | GitHub/GitLab milestones — for Milestones 2–5 |
| First prototype shopping list | `.md` or `.csv` — components, quantities, supplier, price, lead time |

Git repo link:

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

Physical feasibility calculation is correct and relevant. Cost-performance tradeoff analysis uses real numbers. Semester 1 retrospective (A) references actual measured data, or technology survey (B/C) references real projects. Calculations are reproducible in submitted Jupyter notebook.

* 4 pts: All three analyses complete with correct methodology
* 3 pts: Two analyses complete
* 2 pts: One analysis complete
* 1 pt: Attempt without rigor
* 0 pts: No analysis

**Prototype / Physical (4 points) — Concept Viability**

Mechanical concept has realistic dimensions (not fantasy numbers). Component selections are actual purchasable parts with datasheets. Power budget adds up (total consumption vs. supply capacity). At least one critical dimension has been physically verified (measured from real hardware or datasheet). For A: semester 1 prototype photos/measurements included as reference.

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

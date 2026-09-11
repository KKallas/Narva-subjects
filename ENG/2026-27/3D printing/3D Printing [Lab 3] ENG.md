## 3D Printing and CAD: Lab 3 — Enclosures and print-pause

**Workload:** 28 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 23.10.26 | **Order date:** 03.11.26 | **Defense:** 17.11.26, online

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the lab folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

The cell now has a tool on the nozzle (L1), fixtures on the table (L2), an ESP32 tool board on a breadboard with a valve, two sensors and a camera (Data Acquisition L2, Smart Solutions L2), and an RPI with a screen that drives the robot (Smart Solutions L1). None of it has a housing, so cables catch on the arm and the camera moves every time someone touches it. This lab designs two enclosures: the tool housing on the arm and the control-station housing on the table.

The tool housing carries the 3/2 valve and the tool board, the nozzle camera on a short adjustable mount that sees the syringe tip and the tray in one frame, the 405 nm LED on its star heatsink with a shroud on the L1 boss, strain reliefs for the two 4 mm tubes and the USB cable, and ventilation for the valve coil and the LED driver. It rides on the arm, so mass is the constraint: under 250 g with the valve and an empty syringe mounted. The tool PCB does not exist yet (it is frozen at the 14.11 review and arrives for L4), so the board bay is designed to the Gate E envelope and checked against the Data Acquisition team's layout at the 05.11 pre-check. The station housing holds the RPI 4 and its screen at the table edge, with cable entries for LAN, USB and power, and mounts on the L2 feet.

Two methods are new: the print-pause workflow (pause at a layer, drop in nuts, magnets or inserts, continue printing over them) and the assembly guide. The guide is graded by another team assembling your housing from it without asking you anything. Before any of that: an integration graph in draw.io of every component and connection, and a bill of materials with mass per item, because the 250 g budget is decided on paper first.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* 3D Printing L1: the syringe + LED holder with its boss position (`led_boss_offset`) and tube routing; L2: the foot and plug standard for the station housing.
* Smart Solutions L2: the tool-board command interface, the camera (AtomS3R-CAM or ESP32-CAM) with its firmware and stream; the valve (Gate C) and the LED with its constant-current driver.
* Data Acquisition L2–L3: the breadboard tool electronics now, the Gate E PCB outline (ask for the board dimensions and connector edge before 03.11).
* Order of 13.10: cable glands, strain reliefs, LED star heatsink, magnets, inserts, PETG, suction cups φ13 and φ16.

**Gives to**
* Prototyping M4: both housings, the camera and LED mounts, the assembly guide, the BOM.
* Data Acquisition L4: a tool that survives 500 cycles without a cable coming loose; the camera frame that labels pick success.
* Smart Solutions L4: the camera view used by the workflow recorder.
* 3D Printing L4: the valve bracket is a candidate part to improve.

### Background Information

* **draw.io**: https://www.drawio.com/ — the integration graph; export as `.drawio` and PNG.
* **Fusion 360, components vs. bodies, joints, sheet-like shells**: https://help.autodesk.com/view/fusion360/ENU/ — search "Shell", "Component vs body", "Rigid group", "Center of mass" (Inspect > Properties gives the mass with a material assigned).
* **PrusaSlicer, pause at height and colour change**: https://help.prusa3d.com/ — search "Insert pause print", "M601", "Custom G-code at layer". The pause height must be a layer boundary above the top face of the inserted part.
* **Heat-set inserts**: search phrase "heat set insert hole diameter M3 PETG" — start at 4.0 mm hole for M3 brass inserts, check with your own insert.
* **M5 AtomS3R-CAM**: https://docs.m5stack.com/ — search "AtomS3R-CAM"; the lens position and the field of view (the AtomS3R-CAM page states the camera module and its FOV) set the mount geometry.
* **AI-Thinker ESP32-CAM**: search phrase "ESP32-CAM OV2640 board dimensions 27 x 40.5 mm".
* **Raspberry Pi 4 mechanical drawing**: https://www.raspberrypi.com/documentation/ — search "Raspberry Pi 4 mechanical drawing" (85 × 56 mm, hole pattern 58 × 49 mm, M2.5).
* **Ventilation and heat in enclosures**: search phrase "solenoid valve coil temperature rise continuous duty" — the coil is warm at 100 % duty; slots on two opposite faces.
* **405 nm LED thermal**: search phrase "3W LED star heatsink thermal resistance" — 1–3 W with no airflow needs the star plus fins or the aluminium of the housing.

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. Fusion 360, draw.io
2. PrusaSlicer with pause-at-layer; PETG for both housings
3. Digital calipers, a kitchen scale (1 g) for the mass budget, a 0.01 g scale if the Data Acquisition team has received theirs
4. The 3/2 valve with push-in fittings, the ESP32 tool electronics on the breadboard or a perfboard (Data Acquisition L2 state), the camera, the 405 nm LED on the star heatsink with its driver, 4 mm tube, USB cable
5. Cable glands ×4, strain reliefs ×4, magnets 6×3 mm, M3 inserts, M3 and M5 bolts
6. Raspberry Pi 4 and the screen the Smart Solutions team uses (measure it; the plan does not fix a screen model), LAN and power cables
7. MG400 with the L1 holder and the L2 tray set, the RPI station
8. 405 nm goggles ×3, nitrile gloves; IPA for cleaning the shroud
9. Soldering iron with an insert tip
10. A stopwatch and a second team for the assembly-guide test

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Integration graph in draw.io: every component (pump box, valve, cup, syringe, LED + driver, camera, tool board, sensors, VL53L0X, RPI, screen, MG400, tubes, cables) as a node; every tube, cable and mechanical mount as an edge, labelled with what it carries (24 V, 5 V, USB, 4 mm air, WiFi). Mark the boundary of each housing on the graph.
- [ ] BOM (`docs/bom.csv`): columns `item, qty, mass_g_each, mass_g_total, inside (tool|station|none), source, note`. Weigh every real item on the kitchen scale. Sum the tool-side mass before drawing anything; the printed housing gets what is left of 250 g.
- [ ] Model every inside component in Fusion as a placeholder body with real dimensions (valve with fittings, board envelope from Gate E, camera, LED star with shroud, syringe 10 ml, tubes as 4 mm sweeps). Assign materials so Fusion's mass agrees with the scale within 10 %.
- [ ] Tool housing: shell around the L1 holder; valve and board inside; tube runs with no bend radius under 20 mm; ventilation slots on two opposite faces near the valve coil and the LED driver; glands or strain reliefs where the tubes and the USB leave; lid on magnets or M3 inserts. Camera on a two-axis friction mount (ball or two hinges) with a range of ±20° tilt and ±20° pan, lockable with one M3 screw.
- [ ] LED and shroud: the star heatsink bolts to the L1 boss; the shroud is a printed tube (matte black PETG or painted) of length such that the cone at 30 mm below the LED covers a 30 mm circle and the syringe tip is outside the cone. Check in Fusion with the cone sketch from L1, then on the bench with the LED at the lowest driver current and goggles on: a white card at the cure distance shows the spot; the tip is in shadow.
- [ ] Station housing: RPI 4 on its 58 × 49 mm hole pattern with M2.5 standoffs, the screen in a bezel at 30–45° to the table, entries for LAN, USB (tool board), power, HDMI/ribbon; ventilation over the SoC; two L2 feet on the underside so it snaps to the grid at the table edge.
- [ ] Print-pause: pick at least three features to embed (M5 nuts for the station feet, 6×3 mm magnets for a lid, M3 inserts in the camera mount). Model the pocket 0.2 mm larger than the part and 0.2 mm deeper; set the pause one layer above the pocket top; document the pause height per feature. Practice on a 30 × 30 mm test block first.
- [ ] Print both housings, assemble, mount the tool on the robot, run 20 dry cycles (dispense to waste cup, pick, place, cure pose with the LED off) at 50 % speed and check nothing rubs or comes loose.
- [ ] Mass measurement: the tool housing complete with valve, board, camera, LED, empty syringe and 200 mm of each tube, off the robot, on the scale. Photo of the display.
- [ ] Camera frame: with the tool at the dispense pose over the jig, save one camera frame in which the syringe tip and at least three tray pockets are visible; mark them on the image.
- [ ] Assembly guide (`docs/assembly_guide.md`): numbered steps with a photo each, the tools needed, the pause heights, the torque rule for inserts. Give the housing parts and the guide to another team; time them; note every question they asked. Fix the guide.
- [ ] Repo: `3d-print/lab3/` with `fusion/`, `stl/`, `docs/`, `notebooks/`; `AGENTS.md` updated with the housing interfaces.

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

### Simulation

Fusion 360 static stress on the mounting, PETG material.

1. **Tool housing mount**: fix the clamp faces on the lifting nozzle (as in L1). Apply the housing's total mass (from the BOM) as a body load with an acceleration of 5 g in the worst direction (horizontal, across the clamp); 5 g is a chosen margin above the robot's real deceleration, state it in the report. Report the peak stress at the clamp and at the boss, and the displacement at the camera lens. Camera displacement under 0.5 mm at 5 g is the target: a moving camera ruins the pick label.
2. **Camera mount**: 5 N at the lens, in the direction of a finger bump. Displacement and stress.
3. **Station housing feet**: 20 N pull on the screen bezel (someone leans on it); stress at the L2 snap hooks.
4. Screenshots in `docs/fea/`; one table in the README: case, load, peak stress, displacement, pass/fail.

### Analysis

1. **Mass budget** (`docs/bom.csv` + `notebooks/mass.ipynb` or a table in the README): predicted mass from Fusion per printed part and per bought part vs. measured mass on the scale; total tool-side mass; the margin to 250 g. State which part to thin first if over.
2. **Thermal check** (`docs/thermal.csv`): with the housing closed, valve energized continuously and LED at driver current for 60 s cycles (5 s on, 55 s off, goggles on, shroud on, aimed at the table), read the valve body and the LED star temperature with the contact thermometer or IR sensor every 5 minutes for 30 minutes. Columns `t_min, valve_C, led_star_C, ambient_C`. PETG softens at about 80 °C; report the margin.
3. **Camera frame geometry** (`docs/camera_frame.md`): the saved frame with the tip and tray pockets marked; the distance from the lens to the tip (calipers) and the field of view derived from the known 24 mm pocket size in pixels; the lens-to-tip distance is what Smart Solutions L4 uses to place the recorder's crosshair.
4. **Assembly-guide test** (`docs/guide_test.md`): who assembled it, time in minutes, number of questions asked, list of the questions, and the guide changes made in response.
5. **Print-pause record** (`docs/print_pause.csv`): columns `part, feature, insert, pocket_w_mm, pocket_d_mm, pause_layer_mm, result (ok|shifted|crushed)`. One row per embedded feature, including the test block.
6. **Dimensions** (`docs/dimensions.csv`): three axis measurements per housing part.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: Fusion 360 Intersection Test

Before printing, verify that the virtual objects in the computer are properly constrained relative to each other and check that objects don't intersect each other. For this lab: both housings with every placeholder body inside, the lid on, the tubes as sweeps, the camera at both ends of its tilt range, and the LED cone sketch. Interference is permitted only at fastener and insert contact faces.

#### Test Example 2: Basic Dimensions

After printing, you need at least one measurement in each axis — three measurements that are easy to check with calipers, to verify the finished object is to scale and not stretched. When the drawing is complete, a dimension table must be included (this is as necessary as automated testing in software).

#### Test Example 3: Mass under 250 g

Tool housing complete (valve, board, camera, LED with heatsink and shroud, empty 10 ml syringe, 200 mm of each tube, USB pigtail to the first strain relief) on the kitchen scale. Photo with the reading. Pass: under 250 g.

#### Test Example 4: Tip and tray in one frame

Tool at the dispense pose over the jig. One saved camera frame shows the syringe tip and at least three pockets of the source tray. Pass: both identifiable by someone who has not seen the setup, without explanation.

#### Test Example 5: Strain relief

Pull each tube and the USB cable at the gland with 10 N on the scale for 10 s. Nothing moves inside the housing; the fitting on the valve does not rotate. Then 20 dry cycles at 50 % speed: no cable or tube touches the tray or the arm.

#### Test Example 6: Another team assembles it

Another team assembles the tool housing from the printed parts, the loose components and `assembly_guide.md`, with the stopwatch running. Pass: complete in under 30 minutes, and the assembled tool passes Test Example 3 and 4.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* Photo of the scale reading with the complete tool housing: the number in grams, under 250 g.
* The saved camera frame with the tip and three pockets marked (`docs/camera_frame.md`).
* `docs/guide_test.md` with the other team's name, time and questions; their confirmation is a commit by one of them or a line in the MS Teams channel.
* `docs/bom.csv` with weighed masses; `docs/thermal.csv` with 7 rows (0–30 minutes).
* `docs/print_pause.csv` with at least four rows (test block + three features); photo of each embedded feature.
* Integration graph as `.drawio` and PNG.
* FEA screenshots of the three cases and the pass/fail table.
* Both housings on the robot and on the table; video of 20 dry cycles at 50 % speed.

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Repo only. The BOM and the assembly guide are the seed of the Prototyping M4 maintenance guide; keep them as separate files.

### Safety

* 405 nm LED: never look into the LED, with or without the shroud. Goggles rated for 405 nm on everyone at the table whenever the driver is powered. The LED is powered only from the constant-current driver, only through the tool board's enable (low by default), and only for the thermal test and the spot check in this lab; it always times out on the board.
* Shroud on before power. Aim at the table, never at eye level; the spot check uses a white card at 30 mm.
* Uncured resin is not used in this lab; if a syringe with resin is on the bench, tip cap on, nitrile gloves, IPA for the shroud.
* The valve coil and the LED star get hot in the thermal test; measure with the contact sensor, do not touch.
* Soldering iron for inserts: 200 °C or more, on a board, not on the table sheet.
* Dry cycles at 20 % speed first, then 50 %; nobody's hands on the table while the robot is enabled.

### Components for the next lab

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| Filament (PETG or PLA, the material of the part chosen in L4) | 1 spool | Three versions of one part, each printed at least twice |
| Hook / fixture hardware for the load test | 1 set | M5 eye bolt or hook, 2 m of cord or a strap, a bracket for the scale; whatever the L4 test rig needs that was not in L1–L2 |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — both housings parametric with placeholder components, 3MF with pause heights, draw.io graph | 5 p |
| Analysis — mass budget vs. scale, thermal table, camera geometry, FEA table, print-pause record | 5 p |
| Prototype — tool under 250 g on the robot, tip and tray in one frame, 20 dry cycles, station housing on the feet | 5 p |
| Documentation — BOM, assembly guide passed by another team, AGENTS.md | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `3d-print-lab3` 72 h before the defense.**

The defence is online on 17.11.26. The tag deadline is 72 h before it, which is Saturday 14.11.26 — the same weekend as the contact session where the next lab is handed out. Anything that has to be shown live, the robot moving or a print or a measurement, has to be visible on the call, so join from the lab.

The tagged repo must contain, under `3d-print/lab3/`:
* `fusion/`: `.f3d` and `.step` of both housings with the placeholder components; the FEA studies.
* `stl/`: all STL and `.3mf` with the pause heights set.
* `docs/`: `integration.drawio` and PNG, `bom.csv`, `assembly_guide.md` with photos, `guide_test.md`, `thermal.csv`, `print_pause.csv`, `camera_frame.md`, `dimensions.csv`, `fea/`, videos and photos.
* `notebooks/`: `mass.ipynb` if used (a table in the README is acceptable).
* `README.md`: what is in each housing, how to open it, the pause heights, the camera mount adjustment.
* Team `AGENTS.md` updated with the housing layout and the camera lens-to-tip distance.

Live change at the defense: the instructor asks for the camera tilted to a different view (e.g. the finished tray instead of the source tray) and a new frame saved; or asks to swap the syringe with the housing on, under 60 s; or asks which pause height changes if the magnet becomes 8×3 mm.

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

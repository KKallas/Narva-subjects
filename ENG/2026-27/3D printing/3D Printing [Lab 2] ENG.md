## 3D Printing and CAD: Lab 2 — Work-area modules, tray and jig

**Workload:** 30 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 02.10.26 | **Order date:** 13.10.26 | **Defense:** 27.10.26, online

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the lab folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

The robot picks glasses and AtomS3 units from fixed positions, glues in a jig, and drops finished tags into slots. Every one of those positions is a 3D-printed module that snaps into the polycarbonate worktable: 100 mm grid, 5 mm holes. This lab designs the module system and the complete tray set for one team's cell. Positions must repeat to under 0.5 mm, because Data Acquisition L4 teaches the pick points once and then runs 500 cycles without a human. That is why this lab is Fusion, not Blender.

Three things are designed. A universal foot that locates on the 5 mm holes and 100 mm pitch, with a spring fastener (push down, snap; pull up, released) and a socket that any top snaps into. The tray set: 5 glass slots and 5 AtomS3 slots as the source, 5 finished slots, a gluing jig that holds an AtomS3 24×24×13 mm screen-up with the bezel reachable by the syringe tip, a VL53L0X post, a waste-cup holder for dry dispensing, and a camera calibration target. And a load-bearing rule: PLA layers are weak in tension and strong in compression, so a bolt through the part turns inter-layer tension into compression, like prestressed concrete. You print the same part unbolted and bolted, pull both apart with the MG400 and document the failure loads. Fusion FEA on the snap-fit and on the bolted part shows where the stress goes before you print.

The fourth thing is small and it is what stops the cell from working: the 3/2 solenoid valve that arrives with the 02.10 order has ports nobody can use directly — the thread is not the tube's, the two ports sit too close together for a wrench, and there are no push-in fittings for them. So the ports are printed. An adapter block bolts to the valve on the valve's own mounting holes, carries the PVC pipe on each side with the joint recipe from L1 (pipe in, toothpick wedged alongside, high-pressure thread glue over it, full cure before pressure), and seals against the valve's port face with an O-ring in a designed groove, not with glue alone. It is the same load case as the bolt coupon in this lab, only with air behind it: pressure tries to push the block off the valve, the bolts hold it on, and the PLA between them is in compression the whole time. Design it wrong and the block lifts off its seal at 110 kPa; design it right and it is the cheapest part in the cell.

The registration test is the number the other courses wait for: print the tray twice on two different printers, measure every slot with calipers, and let the MG400 pick 5 of 5 glasses from each with the same taught points. A 2D drawing with a dimension table makes the tray reproducible by someone who has never seen your Fusion file.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* 3D Printing L1: the syringe + LED holder on the nozzle (the jig must leave the tip room to reach the bezel), the inter-layer strength ratio and the MG400 maximum pull from `tensile.ipynb`, the caliper column format, and the two pressure recipes — the O-ring groove rule from `cap.md` and the toothpick-and-thread-glue tube joint with its measured pull force and cure time.
* Smart Solutions L1: RPI station with teach/save/replay of points, used for the registration test.
* Order of 22.09: M5 bolts/nuts/washers, M3 inserts, PETG, magnets, O-ring assortment, thread sealant, PVC pipe.
* Smart Solutions L2 order of 22.09: the 3/2 solenoid valve and its 4 mm push-in fittings, on the bench from 03.10.
* Data Acquisition L3 (parallel): the VL53L0X sensor's board size and the height it needs above the table; ask the team before printing the post.

**Gives to**
* Data Acquisition L3: the VL53L0X post at a known height for nozzle Z calibration.
* Data Acquisition L4: tray, jig, waste cup and the registration number (max slot deviation between prints) that sets the pick tolerance.
* Smart Solutions L2: the camera calibration target in a known grid position.
* 3D Printing L3: the foot and socket standard for the station housing; L3 mounts the RPI housing on the same feet. Also the valve with its printed port adapters as one body with real dimensions — that is what the tool housing is built around.
* Smart Solutions L2 and Data Acquisition L3: a valve that can actually be plumbed into the cup and syringe branches.
* 3D Printing L4: the tray is a candidate part; L5: the tray base plate is the alternative CNC part.

### Background Information

* **Fusion 360 help, assemblies, joints, user parameters**: https://help.autodesk.com/view/fusion360/ENU/ — search "Joints", "As-built joint", "User parameters", "Interference".
* **Fusion 360 simulation (static stress)**: same help site, search "Static Stress simulation study", "Structural constraints", "Loads", "Mesh settings".
* **Fusion 360 drawings**: same help site, search "Create drawing from design", "Dimension table", "Section view".
* **Snap-fit design**: search phrase "snap fit design guide cantilever BASF" (the BASF/Bayer cantilever snap-fit guides give the deflection and strain formulas); the permissible strain for PLA is about 1–2 %, PETG 3–4 %.
* **PrusaSlicer, dimensional accuracy**: https://help.prusa3d.com/ — search "Dimensional accuracy", "XY size compensation", "Elephant foot compensation".
* **M5 AtomS3 dimensions and drawing**: https://docs.m5stack.com/en/core/AtomS3 — 24×24×13 mm, screen 0.85", button under the screen; the bezel width comes from your own calipers.
* **VL53L0X**: ST datasheet, search phrase "VL53L0X datasheet field of view 25 degrees"; the breakout board dimensions from the board you receive.
* **Camera calibration target**: search phrase "OpenCV calibrateCamera checkerboard pattern size" — the target is a raised or two-colour checkerboard with a 5 mm square, printed, with its origin on a table hole.
* **Prestressed concrete principle**: search phrase "prestressed concrete tension compression principle" — the same idea as the bolted PLA part.

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. Fusion 360 with the Simulation workspace (static stress)
2. PrusaSlicer and two different printers (different model or at least different machines; note their names and nozzle sizes)
3. PETG for the tray, jig and feet; PLA for the test coupons and the calibration target
4. Digital calipers, a depth gauge or the calipers' depth rod, a 300 mm steel ruler
5. M5 bolts 20/30 mm, nuts, washers; M3 heat-set inserts and a soldering iron with an insert tip
6. Magnets 6×3 mm
7. MG400 with the L1 holder, φ13 and φ16 cups, pump box; the RPI station with saved points
8. Force measurement from L1 (luggage scale or HX711 + 20 kg cell), a hook bolted to the table
9. Polycarbonate dummy glasses 24×24×2 mm ×5, AtomS3 ×1 (the shelf unit; the batch arrives in December) or a printed 24×24×13 mm dummy with the same corner radius
10. A 30 ml disposable cup for the waste-cup holder, the VL53L0X breakout board from the Data Acquisition team
11. The 3/2 solenoid valve with its coil, the pump box as the pressure source, PVC pipe, toothpicks, high-pressure thread sealant, O-ring assortment
12. The Data Acquisition pressure sensor on its breadboard, borrowed for the leak tests; soapy water in a spray bottle

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Measure the table: hole diameter (three holes), pitch over five holes divided by four, sheet thickness, hole edge condition. Enter as parameters `hole_d`, `pitch`, `sheet_t`.
- [ ] Universal foot: a plate spanning two holes at 100 mm pitch, two locating pins (`hole_d` − 0.1 mm), and one spring fastener: a printed cantilever clip that pushes through a 5 mm hole and hooks under the sheet; pull up to release. Socket on top: 30×30 mm square with two snap hooks. Print three feet; measure the pins; adjust the clearance until a foot inserts by thumb and holds 2 kg of pull upward on the scale.
- [ ] Snap top standard: a 30×30 mm plug with the mating hooks. Every module below carries this plug. Test insertion 20 times on one foot; measure the insertion and removal force on the scale on cycle 1 and cycle 20.
- [ ] Tray set in one Fusion design with the AtomS3 (24×24×13 mm) and the glass (24×24×2 mm) as referenced components: source tray (5 glass pockets + 5 AtomS3 pockets), finished tray (5 pockets), gluing jig, VL53L0X post, waste-cup holder, calibration target. Pocket clearance as a parameter (`pocket_clear`, start at 0.3 mm), 45° lead-in chamfer on every pocket, an 8 mm hole in every glass-pocket floor so a finger or a pin can push a stuck glass out.
- [ ] Gluing jig: the AtomS3 sits screen-up with 0.2 mm clearance on two sides and a spring finger on the third; the bezel (all four edges of the screen) is reachable by a syringe tip of 1.2 mm at 90° and at 60° from horizontal; the glass placed on it must be pushable down 0.5 mm by the cup (no wall above the screen plane). Check the tip reach in Fusion with the L1 holder assembly inserted.
- [ ] Bolt compression coupons: a bar 40 × 12 × 8 mm printed standing (layers perpendicular to the load) with a loop at each end; version (a) plain, version (b) with a 5.2 mm hole along the axis, an M5 bolt, washer and nut torqued by hand plus a quarter turn. Three of each. Pull with the MG400 through the scale; record the peak force and where it broke.
- [ ] FEA (Simulation section) on the snap hook and on both coupon versions before printing.
- [ ] Registration test: print the source tray on printer A and on printer B, same STL and profile. Caliper table of all pocket positions on both (Analysis 2). Teach the five glass pick points on print A with the RPI station; swap to print B on the same feet without re-teaching; pick 5 of 5 with the same points; repeat the swap three times.
- [ ] 2D drawing of the source tray and the foot in Fusion: three views, one section through a pocket, dimension table, tolerance on pocket position ±0.2 mm, material and printer note. PDF in `docs/`.
- [ ] Valve survey: measure the solenoid valve — body outline, mounting hole pattern and thread, port spacing, port bore, port face flatness and any raised seat, coil dimensions, mass. Photograph each port with a ruler. Into `docs/valve.csv` and `docs/valve.md`; state in one sentence per port why the port as delivered cannot take your pipe.
- [ ] Port adapter in Fusion: one block per port face (or one block spanning both, if the spacing allows), O-ring in a face groove against the port seat, sized by the L1 rule; PVC pipe port using the L1 joint; bolted to the valve's own mounting holes with washers, or clamped by a bridge if the valve has no usable holes. Parameters `port_pitch`, `port_bore`, `oring_cord`, `pipe_od`, `bolt_pitch`.
- [ ] Print the adapter with 5 perimeters and 100 % infill within 3 mm of any air path; make the tube joints; give them the full cure time before the first pressure.
- [ ] Valve rig on the bench: pump box → adapter → valve → adapter → cup branch and syringe branch, sensor on the syringe branch. Leak test and cycle test (Test Example 6).
- [ ] Repo: `3d-print/lab2/` with `fusion/`, `stl/`, `notebooks/`, `docs/`; `AGENTS.md` updated with the module standard (foot pitch, plug size, parameter names).

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

### Simulation

Fusion 360 static stress, PLA or PETG material from the library (note which; edit the yield strength to 50 MPa for PLA, 45 MPa for PETG if the library value differs by more than 20 %).

1. **Snap hook**: fix the plug body, apply a prescribed displacement equal to the hook engagement depth (start 1.0 mm) to the hook face. Report the maximum von Mises stress at the hook root and the maximum strain. Pass on screen: strain under 1.5 % for PLA, 3 % for PETG. Add a fillet at the root (0.5 mm), re-run, report the change. Screenshot both in `docs/fea/`.
2. **Coupon (a) unbolted**: fix one loop, 100 N on the other. Report peak stress; expected failure is at the neck in the inter-layer direction, so multiply by the L1 inter-layer ratio when you predict the failure load.
3. **Coupon (b) bolted**: same, plus a bolt preload (Fusion "Bolt connector" preload, start 500 N). Show that the axial stress in the bar stays compressive up to the failure load of (a). Write down the predicted failure load for both versions before the physical test and compare in Analysis 3.
4. **Foot under upward pull**: 20 N upward on the socket. Report the clip stress. This is the load of a top being pulled off carelessly.
5. **Valve port adapter under pressure**: apply 110 kPa as a pressure load on the internal faces of the air path and add the bolt connectors with their preload. Two things to report: the peak stress in the block wall around the air path, and whether the sealing face lifts anywhere — check the displacement plot at the groove, not just the stress. The bolt preload must stay above three times the blow-off force from Analysis 7 at every bolt. Run it again with one bolt removed to see what a half-tightened assembly does. Screenshots in `docs/fea/`.

### Analysis

1. **Snap-fit cycling** (`docs/snapfit.csv`): cycle number (1, 5, 10, 20), insertion force N, removal force N, visible damage (0/1). Notebook or table; state the drop in removal force from cycle 1 to 20 in percent.
2. **Registration caliper table** (`docs/registration.csv`): for each of the 15 pockets on print A and print B: pocket X centre, Y centre (measured as wall-to-wall over the pocket and the tray edge, then centre = edge + wall + width/2), pocket width X, width Y, depth. Reference is the foot pin hole nearest the tray origin. 30 rows, columns `print, pocket_id, x_mm, y_mm, w_x_mm, w_y_mm, depth_mm`. Notebook `notebooks/registration.ipynb`: per pocket the deviation A − B in X and Y, the maximum, the mean and the standard deviation; a scatter of A vs. B positions; the number to report is `max |A − B|` in mm. This is the "registration number" quoted in Data Acquisition L4.
3. **Pick test** (`docs/pick_test.csv`): columns `print, swap_cycle, pocket_id, cup_d_mm, picked (0/1), placed_back (0/1), notes`; 2 prints × 3 swap cycles × 5 pockets = 30 rows. Pass is 5 of 5 on every row.
4. **Bolt compression** (`docs/bolt_test.csv`): columns `version (a|b), coupon, peak_force_N, predicted_N, break_location, bolt_preload_note`. 6 rows. Notebook: ratio of bolted to unbolted mean failure force; comparison with the FEA prediction; one paragraph stating the design rule: where bolt holes go so that layers are always in compression.
5. **Print dimensional accuracy** (`docs/dimensions.csv`): three axis measurements per printed module (foot, source tray, finished tray, jig, post, cup holder, target), nominal vs. printed, and the XY compensation value used in the slicer, if any.
6. **Jig reach check** (`docs/jig_reach.md`): photo of the syringe tip at all four bezel edges with the AtomS3 in the jig, and the measured height of the screen plane above the table (calipers, three readings).
7. **Valve port adapter** (`docs/valve.md`, `docs/valve.csv`): port bore and pitch with three readings each; sealing face area and the blow-off force `F = p · A_face` at 110 kPa and at the pump box maximum; the bolt preload you can actually reach by hand on an M3 or M4 (measure it, or state the torque and the `F ≈ T / (0.2 · d)` estimate and say it is an estimate); the ratio preload / blow-off, which must be at least 3; the O-ring groove numbers by the same rule as the L1 cap. Then the measured result: leak rate at 110 kPa before and after 500 valve cycles, and the pull force of each pipe joint. One paragraph on which of the two seals — the O-ring face or the glued pipe joint — is the weaker one on your build, with the evidence.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: Fusion 360 Intersection Test

Before printing, verify that the virtual objects in the computer are properly constrained relative to each other and check that objects don't intersect each other. For this lab: the full tray set on the feet, the AtomS3 in the jig, a glass in every pocket, and the L1 holder at the pick pose above pocket 1 and at the dispense pose over the jig. Interference is permitted only at the snap-hook contact faces.

#### Test Example 2: Basic Dimensions

After printing, you need at least one measurement in each axis — three measurements that are easy to check with calipers, to verify the finished object is to scale and not stretched. When the drawing is complete, a dimension table must be included (this is as necessary as automated testing in software). For this lab the dimension table is part of the 2D drawing PDF.

#### Test Example 3: Foot insertion and hold

A foot inserts into two table holes by thumb (no tool, no hammer), the fastener clicks, and a 2 kg upward pull on the scale does not release it. Pull the release tab: it comes out. Three feet, three holes positions each.

#### Test Example 4: Registration swap

Teach five pick points on tray print A. Remove A, insert B on the same feet, pick 5 of 5 glasses at 50 % speed with the same points. Swap back to A, pick 5 of 5. Video of one full swap and pick round.

#### Test Example 5: Bezel reachable

With an AtomS3 in the jig and the L1 holder on the robot with an empty syringe and a 1.2 mm tip, jog the tip to 1 mm above each of the four bezel edges. The tip touches no jig wall. Photo per edge.

#### Test Example 6: Valve ports hold air, before and after cycling

Adapters bolted on, both branches plugged, sensor on the line, pressure at 110 kPa. Hold 5 minutes: drop under 5 %. Soapy water on every joint and every bolt line: no bubbles in 30 s. Then energize the valve 500 times at 2 Hz with the pressure on (the coil gets warm; that is part of the test), let it cool, and repeat the hold and the soap. Pass: the drop after cycling is within 2 percentage points of the drop before. Record both in `docs/valve.md`. A joint that starts leaking only after cycling is a glue joint that was pressurised before it cured, or a groove that is too shallow — say which one you found.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* `docs/registration.csv` with 30 rows (15 pockets × 2 prints) and the notebook giving `max |A − B|` in mm; both printer names stated.
* `docs/pick_test.csv` with 30 rows, all `picked = 1`, and the video of a swap.
* `docs/bolt_test.csv` with 6 rows: mean failure force unbolted and bolted, and the FEA prediction for both.
* `docs/snapfit.csv` with the cycle-1 and cycle-20 forces.
* The tray set physically on the team's table: source tray, finished tray, jig with an AtomS3 in it, VL53L0X post with the sensor mounted, waste-cup holder with a cup, calibration target; one photo of the whole table section from above with a ruler in frame.
* `docs/valve.csv` and `docs/valve.md`: port measurements, the blow-off and preload numbers, the groove sizing, and the leak result before and after 500 cycles, with the soap-test photos.
* The valve on the bench with printed adapters on both ports, plumbed to both branches, in one photo with the pressure reading visible.
* 2D drawing PDF of the source tray and the foot with a dimension table.
* FEA screenshots of the snap hook (with and without fillet) and of both coupons.

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Repo only. The registration number and the jig screen-plane height are copied by the Data Acquisition team into their L4 notes; keep the file names above so they can be found.

### Safety

* Tensile pulls: scale end bolted to a table hole, robot at 20 % speed, MovL not more than 30 mm past the expected break, safety glasses, nobody inside the arm's reach.
* Heat-set inserts: the iron is at 200 °C or more; work on a board, not on the table sheet.
* Pick test at 50 % speed only after 5 of 5 at 20 %.
* Pressure on printed parts: first hold test with the assembly inside a cardboard box or behind the bench screen, nobody in line with a port, glasses on. Pressure off before anything is touched or a bolt is turned. An adapter that has been pressurised before the glue cured is thrown away, not re-glued.
* Thread sealant and cyanoacrylate: ventilation, gloves, cure time from the label. The valve coil is warm after the 500-cycle test; let it cool before handling.

### Components for the next lab

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| Cable glands (PG7 or M12, for 4–6 mm cable) | 4 | Tool housing and station housing entries |
| Strain reliefs (tube and USB) | 4 | 4 mm tube ×2, USB cable ×2 |
| Star heatsink for the 405 nm LED (20 mm star) | 1 | The LED itself arrives with the Smart Solutions L2 order |
| Magnets 6×3 mm | 10 | Lids on both housings |
| M3 heat-set inserts | 20 | Housing lids, camera mount |
| PETG | 1 spool | Both housings |
| O-rings, the size used in L1 and L2 | 20 | Spares; the seal is the consumable, the block is not |
| High-pressure thread sealant | 1 | Refill if the L1 tube is out |
| Suction cups φ13 | 2 | Spares for the tool; the φ13/φ16 choice is made in L3 |
| Suction cups φ16 | 2 | See above |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — parametric tray set with the AtomS3 and glass as components, foot and plug standard, STL and 3MF | 5 p |
| Analysis — registration table and number, pick CSV, bolt test vs. FEA, snap-fit cycling, valve adapter pressure and leak numbers | 5 p |
| Prototype — the tray set on the table, robot picks 5 of 5 from both prints, foot holds 2 kg, valve plumbed on printed ports and holding 110 kPa | 5 p |
| Documentation — 2D drawing with dimension table, FEA screenshots, design rule for bolt placement, AGENTS.md | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `3d-print-lab2` 72 h before the defense.**

The defence is online on 27.10.26. The tag deadline is 72 h before it, which is Saturday 24.10.26 — the same weekend as the contact session where the next lab is handed out. Anything that has to be shown live, the robot moving or a print or a measurement, has to be visible on the call, so join from the lab.

The tagged repo must contain, under `3d-print/lab2/`:
* `fusion/`: `.f3d` and `.step` of the tray set, foot, plug, coupons and the valve port adapter; the FEA studies saved in the design.
* `stl/`: all STL and `.3mf` files, named by module and printer (`source_tray_printerA.3mf`).
* `notebooks/`: `registration.ipynb`, `bolt_test.ipynb`, run with outputs.
* `docs/`: `registration.csv`, `pick_test.csv`, `bolt_test.csv`, `snapfit.csv`, `dimensions.csv`, `jig_reach.md`, `valve.csv`, `valve.md`, `fea/` screenshots, the drawing PDF, photos and videos.
* `README.md`: which modules exist, which foot positions they take on the team's table (grid coordinates), and how to add a new top.
* Team `AGENTS.md` updated with the module standard.

Live change at the defense: the instructor names a different table position for the source tray (e.g. one grid step to the left); the team moves the feet, re-teaches nothing, and the robot picks from pocket 3 using a pick point offset by 100 mm in the station. Or: change `pocket_clear` to 0.5 mm and show the interference check and the drawing update.

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

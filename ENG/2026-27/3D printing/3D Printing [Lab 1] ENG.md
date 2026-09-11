## 3D Printing and CAD: Lab 1 — The printer, and a tool that gives

**Workload:** 30 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 11.09.26 | **Order date:** 22.09.26 | **Defense:** 06.10.26, online

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the lab folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

By the end of the year the MG400 assembles a tag: an AtomS3 with a polycarbonate glass glued over its screen. Every part that clamps to the robot, snaps into the table or holds the electronics comes out of a printer in this room. This lab is about that printer — what it actually does to the numbers you give it — and it ends with the first tool on the robot: a pen holder, so that the robot can draw the letter that Data Acquisition picks on a screen and Smart Solutions sends across. Three courses, one demo: **press a letter, the robot draws it.**

The first session is three hours, and you leave it with a printed part in your hand. It is your first login to Fusion, and the part is a calibration plate: five clearances, each printed twice — once with the peg sitting inside its hole and printed together with it, once with the peg printed beside the hole to be pushed in afterwards. The plate must slice under 45 minutes; if it does not, make it smaller. While it prints, the robot draws with a marker taped to its flange, using the drawing routine that ships with the base MG400 package. You give it a pen-down height and a speed. No motion code is written in this lab.

The week after, the plate tells you two numbers that every later part will use: the clearance at which two printed walls stop welding into one, and the clearance at which a separately printed peg goes in. They are not the same number. Then the pen holder, in Blender this time, so you meet the other way of modelling and see where meshes bite. The holder must give — a flexure, a spring, a pad, your design — because a rigid tool breaks the pen, the paper, or the robot's alarm when the taught height is 2 mm off. Around it, the physics of the process: overhangs, a straight wall against a curved one, four print orientations pulled apart on the robot, and a notebook that predicts print time from the geometry alone.

There are no new parts on day one, only the shelf and the old-stuff box. That is not a reason to wait. Build with what is here, let it show you what you need, and write that down as the order that goes out on 22.09.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* Shelf: two printers with a known profile, PLA, calipers, a steel ruler, pens, a marker, masking tape, A4 paper, the luggage scale or the HX711 set.
* Old-stuff box: last year's pen holders and tool parts. Measure them, say what is wrong with them, and start from there if it helps.
* Instructor: the base MG400 Python package with its drawing routine (50 mm square and circle, pen-down Z and speed as the arguments).
* Smart Solutions L1: the chain that takes the letter from the Atom and moves the robot. Until it exists, the given routine draws the square.

**Gives to**
* Smart Solutions L1: the pen holder that draws the letter on the demo day.
* 3D Printing L2: the two clearance numbers, the inter-layer strength ratio, the caliper column format, and the Blender holder that gets rebuilt in Fusion.
* 3D Printing L3 and L4: the clearance numbers again, for every clamp, lid and pocket.

### Background Information

* **Fusion 360 help, sketches, parameters and constraints**: https://help.autodesk.com/view/fusion360/ENU/ — search "User Parameters" and "Sketch constraints". One parameter should drive all ten features of the plate.
* **Blender manual, modeling and mesh editing**: https://docs.blender.org/manual/en/latest/ — vertices, edges, faces, normals, and the 3D Print Toolbox add-on (Edit > Preferences > Add-ons, search "3D-Print Toolbox").
* **Blender STL export**: https://docs.blender.org/manual/en/latest/files/import_export/stl.html
* **PrusaSlicer documentation**: https://help.prusa3d.com/ — search "Overhangs", "Print time estimate", "Seam position", "Supports".
* **Prusa knowledge base, layer height and overhang angle**: https://help.prusa3d.com/article/layers-and-perimeters_1748
* **Clearance and print-in-place**: search phrase "3D print clearance test print in place tolerance". The threshold where two walls fuse is about one extrusion width; find yours.
* **Why FDM parts fail between layers**: search phrase "FDM interlayer adhesion Z strength anisotropy". One article with a picture of a Z-axis fracture is enough.
* **MG400 mount**, last year's Fusion model of the tool flange: https://a360.co/4nruicX — use it to check your own measurements, not instead of them.
* **STL mesh repair**: Meshmixer (Autodesk, free, "Inspector" tool) or the Blender toolbox "Make Manifold"; search phrase "Meshmixer inspector make solid".
* **Print-time model**: search phrase "FDM print time estimation perimeter length layer area". The notebook builds its own from first principles; a paper is not required.
* **Tensile test on a robot**: search phrase "HX711 load cell Arduino tare calibrate" for the load-cell option.
* **Compliant mechanisms in plastic**: search phrase "printed flexure compliant mechanism PLA living hinge". The holder's give can come from geometry, not from a bought spring.

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. Fusion 360 (education licence, activated before the session — it cannot be done in the room)
2. Blender 4.x with the 3D Print Toolbox add-on enabled
3. PrusaSlicer, the lab printers, PLA
4. Digital calipers (0.01 mm), a steel ruler, a pen with a known diameter (measure it), a marker, masking tape, A4 paper taped flat to the table
5. MG400 with the base Python package installed with pip; its CLI for jog, MovL, DO on/off; its drawing routine
6. Force measurement for the tensile test: digital luggage scale (0.01 kg, up to 50 kg) or an HX711 + 20 kg load cell on any microcontroller; whichever is on the shelf
7. Jupyter Lab with numpy, `numpy-stl` or `trimesh`, matplotlib
8. Git, one repo per team with `AGENTS.md` at the root

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Day one, in the three-hour session: calibration plate in Fusion — five clearances (0.0 / 0.1 / 0.2 / 0.3 / 0.4 mm on the diameter) driven by one user parameter, each clearance once printed in place and once printed apart. Slice it; it must be under 45 minutes; if not, shrink it. Start the print.
- [ ] Day one, while it prints: marker taped to the MG400 flange, pen-down Z found by jogging, the given routine run at 20 % speed for a 50 mm square and a 50 mm circle on paper. Photo of the drawing before you go home.
- [ ] Measure the plate: three caliper readings per hole and per peg before anything is fitted. Then fit them. Which in-place pegs are fused solid, which spin free; which separate pegs will not go, go with a push, go loose. Two numbers into `docs/clearance.md`: the in-place clearance and the assembly clearance.
- [ ] Overhang piece: four walls of 20 × 15 × 1.6 mm at 30°, 45°, 60° and 90° from vertical, 0.2 mm layers, no supports. Photograph the underside of each; measure the sag at the free edge with calipers.
- [ ] Straight against curved: a square tube and a round tube, same wall (1.2 mm), same height (30 mm), same cross-section area (±2 %). Slice both at identical settings and record the times. Print one pair; read the stepped surface of the round one with calipers at 0°, 45°, 90°.
- [ ] Tensile coupons: one coupon in four orientations (flat, on edge, standing, 45°), two per orientation. Measure the MG400's maximum sustained pull first. Pull each apart through the scale; record the peak force and where it broke.
- [ ] Pen holder in Blender: tube plus flange plate. Export STL, open in PrusaSlicer, screenshot every warning. Fix in Blender or Meshmixer. Print.
- [ ] The holder gives: design the compliance in — a flexure, a sprung barrel, a foam pad — so that a pen taught 2 mm too low survives. Mount it, run the same routine, draw the same square. Then teach it 2 mm low on purpose and run again.
- [ ] Print-time notebook: slice each STL into 0.2 mm layers in numpy, sum perimeter and area per layer, model the time, compare with the slicer and with the clock — four orientations of the coupon plus the two tubes.
- [ ] Repo: `3d-print/lab1/` with `fusion/`, `blender/`, `stl/`, `notebooks/`, `docs/` (caliper tables, photos, videos), this file as `README.md`, and the team `AGENTS.md` updated.
- [ ] Tag `3d-print-lab1` 72 h before 06.10.

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

### Simulation

The simulator in this lab is the slicer, and it costs forty minutes a run. Use it before every print, not after.

1. The plate: slice, read the time, and shrink the geometry until it is under 45 minutes. Keep the `.3mf` of the version you printed.
2. The tensile coupon in four orientations at identical settings (0.2 mm layer, 2 perimeters, 15 % infill, same speeds): estimated time, filament mass, support volume, number of layers, from the slicer.
3. The two tubes at identical settings: time, and the layer preview of the round one showing the stair-steps.
4. The pen holder in at least three orientations. Pick the one where the flexure and the clamp have the fewest layers in tension along the load, and say why in `docs/orientation.md` with the slicer screenshots.

### Analysis

1. **Clearance table** (`docs/clearance.csv`, `docs/clearance.md`): one row per feature — nominal clearance, printed in place or apart, three readings of hole diameter, three of peg diameter, mean and spread, and the result (fused / free; will not go / push fit / loose). Then the two numbers, each with one sentence: the in-place clearance, above which the walls no longer weld; the assembly clearance, at which a separate peg fits by hand. State how much smaller than nominal the holes came out and how much bigger the pegs.
2. **Overhang** (`docs/fdm_tests.md`): sag in mm at 30 / 45 / 60 / 90°, with the photos. Where does 45° actually sit on your printer?
3. **Straight against curved** (same file): slicer time for each tube, printed time, the caliper step height at three angles on the round one, and one paragraph on why a curve costs time that a flat face does not.
4. **Orientation and strength** (`docs/tensile.csv`, `notebooks/tensile.ipynb`): the coupon is a flat bar 60 × 10 × 3 mm with a loop at each end and a neck of 2.0 × 1.2 mm in the middle, so that the neck breaks before the loops and within the robot's pull. If the expected failure force is above 70 % of the measured maximum pull, reduce the neck to 1.2 × 1.2 mm and say so. Columns `orientation, coupon, neck_w_mm, neck_t_mm, peak_force_N, break_location, notes`. Mean per orientation, stress at failure `σ = F / (w · t)`, and the ratio of the standing (inter-layer) strength to the flat strength. That ratio is a design rule for every later lab; write it as one.
5. **Print-time integration** (`notebooks/print_time.ipynb`): per layer the perimeter length P and the area A; layer time `t = P / v_perimeter + A · f_infill / (w · v_infill) + t_layer_change` with w the extrusion width (0.45 mm) and the speeds from your slicer profile. Sum over layers. Show the cross-section area against Z for all four coupon orientations on one axis, a table orientation × (your time, slicer time, clock time, error %), and which orientation has the largest cross-section step and why it prints slowest. Errors under 20 % are expected; explain the sign.
6. **Mesh diagnostics** (`docs/mesh_report.md`): for the first Blender export and the fixed one, the counts the toolbox reported — triangles, non-manifold edges, flipped normals, zero-area faces, thin-wall faces — and what you did about each.
7. **Drawing comparison** (`docs/drawing_compare.md`): the 50 mm square drawn with the taped marker on day one and with the printed holder, measured with a ruler at four points; deviation in mm. Then the drawing made with the holder taught 2 mm low.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: The plate fits the session

The calibration plate slices under 45 minutes at 0.2 mm layers on the lab profile, and it carries all ten features. If it is over, the geometry shrinks; the feature count does not.

#### Test Example 2: Basic Dimensions

After printing, you need at least one measurement in each axis — three measurements that are easy to check with calipers, to verify the finished object is to scale and not stretched. When the drawing is complete, a dimension table must be included (this is as necessary as automated testing in software). For the pen holder: clamp bore (X), pen bore (Y), overall height (Z), nominal against printed, in `docs/dimensions.csv`.

#### Test Example 3: The holder gives

With the printed holder and a pen, teach the pen-down Z 2 mm lower than the value that draws correctly. Run the square. Pass: the pen is not broken, the paper is not torn, the robot did not alarm, and the square is still visible. Fail: any of those. A holder that passes this at 2 mm is asked, at the defense, what it does at 4.

#### Test Example 4: Same routine, same square

The given routine draws a 50 mm square with the taped marker and again with the printed holder, same speed, same paper position. Pass: both squares measure 50 ± 1 mm on each side. The difference between the two is the holder, and it goes in `docs/drawing_compare.md`.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* Photo of the MG400 drawing the 50 mm square with a marker taped to the flange, dated 11.09.26, in `docs/`.
* The printed calibration plate, and `docs/clearance.csv` with three readings per feature and the two clearance numbers stated in `docs/clearance.md`.
* `docs/fdm_tests.md`: sag at 30 / 45 / 60 / 90° in mm, the two tube times and the step height, with photos.
* `docs/tensile.csv` with 8 rows and `notebooks/tensile.ipynb` with the four-orientation table and the inter-layer strength ratio; the MG400 maximum pull recorded in the same notebook.
* `notebooks/print_time.ipynb` with outputs: your time against slicer time against clock time for four orientations and two tubes.
* `docs/mesh_report.md` with the defect counts of the first and the fixed Blender export.
* The Blender `.blend`, the exported STL and the `.3mf` of the pen holder; the holder itself.
* Video: the square drawn with the printed holder; video: the 2 mm-low run with nothing broken.
* `docs/dimensions.csv` with three axis measurements for every printed part.

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Repo only. The two clearance numbers, the inter-layer ratio and the caliper tables are quoted by Labs 2, 3 and 4 and by the other courses; keep the file names and column names above so they can be found.

### Safety

* Printer hot end is 200–230 °C and the bed up to 60 °C for PLA. Remove parts with the spatula after the bed has cooled; no fingers near the nozzle while it moves.
* MG400 workspace while drawing: nobody's hands on the table while the robot is enabled. First run at 20 % speed with the emergency stop within reach of the person at the laptop, not the person at the robot.
* Tensile test: the coupon snaps and the robot keeps moving for a moment. Fix the scale end to the table with a bolt through a 5 mm hole, not by hand; stand outside the arm's reach; safety glasses; run the pull at 20 % speed as a MovL of at most 30 mm past the expected break.
* Side cutters cut away from the face; wire ends and support stubs fly.

### Components for the next lab

Order goes out on 22.09.26. Quantities per team. Every line is a real part number with stock checked, written after the simulation says you need it.

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| PLA | 1 spool | State the colour and the mass used in Lab 1 |
| M5 bolts (20 and 30 mm), nuts, washers | 20 sets | Table holes are 5 mm; also the bolt compression test in Lab 2 |
| M3 heat-set inserts | 20 | Snap tops and print-pause practice |
| PETG | 1 spool | Tray and jig; PLA creeps under the AtomS3 clamp |
| Magnets 6×3 mm | 10 | Calibration target and tray lids |
| Digital luggage scale or HX711 + 20 kg load cell | 1 | Only if not on the shelf after this lab |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — Fusion plate with one driving parameter, Blender holder, STL and 3MF for every print | 5 p |
| Analysis — the two clearance numbers, tensile table with inter-layer ratio, print-time integration vs. slicer, tube comparison | 5 p |
| Prototype — plate printed in the first session; robot drew on day one with the marker and again with the printed holder; the holder survives 2 mm low | 5 p |
| Documentation — clearance and caliper tables, mesh report, orientation reasoning, README, AGENTS.md | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `3d-print-lab1` 72 h before the defense.**

The defence is online on 06.10.26. The tag deadline is 72 h before it, which is Saturday 03.10.26 — the same weekend as the contact session where the next lab is handed out. Anything that has to be shown live, the robot moving or a print or a measurement, has to be visible on the call, so join from the lab.

The tagged repo must contain, under `3d-print/lab1/`:
* `fusion/`: `.f3d` and `.step` of the calibration plate with its parameter.
* `blender/`: the `.blend` of the pen holder, first and fixed.
* `stl/`: every printed STL and the `.3mf` slicer projects with the orientation used.
* `notebooks/`: `print_time.ipynb` and `tensile.ipynb`, run with outputs.
* `docs/`: `clearance.csv`, `clearance.md`, `fdm_tests.md`, `tensile.csv`, `mesh_report.md`, `dimensions.csv`, `drawing_compare.md`, `orientation.md`, the photos and videos (or links with file name and location if over the size limit).
* `README.md`: this document, filled in.
* Team `AGENTS.md` updated with the lab folder layout and the parameter names.

Live change at the defense: the instructor names a clearance (e.g. 0.25 mm) or a pen diameter; the team changes the parameter, re-slices, and shows the new time. Printing during the defense is not required; the changed model and the slicer time are.

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

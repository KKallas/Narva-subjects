## 3D Printing and CAD: Lab 4 — Improving an existing design, three approaches

**Workload:** 30 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 13.11.26 | **Order date:** 24.11.26 | **Defense:** 08.12.26, online

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the lab folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

Three parts from this course are now on the cell and have been used for weeks: the syringe holder from Lab 1, the tray from Lab 2, the valve bracket from Lab 3. Each was designed once and printed as soon as it worked. This task takes one of them and improves it along one metric, three ways, and measures which way wins.

The team picks the part and the metric. Metric A: print speed at equal strength (same failure load, shorter slicer time). Metric B: strength at equal print time (same slicer time ±5 %, higher failure load). Metric C: use cycles (more syringe swaps, tray insertions or valve mountings before a measured property drifts out of tolerance). Then three versions are compared: the original as it is, a manual redesign (ribs on the load paths, wall thickness, FDM-friendly geometry, bolt placement from the Lab 2 rule), and a generative design from Fusion 360 given the same mounting points, loads and keep-out zones. All three are printed in the orientation that the Lab 1 method says is best for them, and all three are put through the same repeatable load test on the MG400.

The output is a comparison table: print time, mass, failure load or cycles, support cost, and the answer to the question the task exists for: is manual engineering better than generative design for a part like this, and why? FEA on all three versions comes before printing, so that the table also says how good the prediction was.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* 3D Printing L1: the candidate syringe holder, the inter-layer strength ratio, the print-time integration notebook, the MG400 maximum pull and the coupon pulling method.
* 3D Printing L2: the candidate tray, the bolt-placement rule, the FEA settings for PLA/PETG, the registration numbers (a redesigned tray must keep them).
* 3D Printing L3: the candidate valve bracket, the mass budget (a redesigned bracket must keep the tool under 250 g).
* Data Acquisition L4 (parallel): the cell is running 500 cycles with the original parts; coordinate when the part is swapped.
* Order of 03.11: filament, hook and fixture hardware for the load test.

**Gives to**
* Prototyping M1 audit: which version of the part goes into the cell.
* 3D Printing integration project: the improved part with its documentation.
* 3D Printing L5: the design-analysis habit (where the tolerance goes) used on the glass drawing.

### Background Information

* **Fusion 360 generative design**: https://help.autodesk.com/view/fusion360/ENU/ — search "Generative Design workspace", "Preserve geometry", "Obstacle geometry", "Design conditions", "Manufacturing constraints additive". Check the education licence covers generative outcomes before the study is set up; if not, the generative study runs on the instructor's account.
* **Fusion 360 static stress**: same site, search "Static Stress", "Bolt connector", "Contact sets".
* **Design for FDM**: search phrase "design for FDM 3D printing guidelines wall thickness ribs overhang" — ribs along the load path, wall thickness as a multiple of extrusion width (0.45 mm × n), 45° chamfers instead of supports.
* **PrusaSlicer, time and support estimates**: https://help.prusa3d.com/ — search "Print time estimate", "Support material", "Paint-on supports".
* **Topology optimisation background**: search phrase "topology optimization SIMP method introduction" — what the generative algorithm is doing under the hood, one page is enough.
* **Test methodology**: search phrase "repeatability reproducibility test method small sample standard deviation" — n = 3 per version, report mean and range, not only the mean.

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. Fusion 360 with Simulation and Generative Design workspaces
2. PrusaSlicer, one printer used for all versions (state which), the filament from the 03.11 order
3. Digital calipers, kitchen scale (1 g) for part mass
4. MG400 with the RPI station, the force measurement from L1 (luggage scale or HX711 + 20 kg cell), the hook and fixture hardware from the 03.11 order
5. The original part as printed in L1/L2/L3 (do not reprint the original with new settings; if it is damaged, reprint from the original `.3mf` unchanged)
6. For metric C: the mating parts (syringes, glasses and cups, the valve) and a counter
7. Jupyter Lab with the L1 `print_time.ipynb` copied into `3d-print/lab4/notebooks/`

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Pick the part and the metric; write both and the reason in `README.md` on the first day. Write the load case in one sentence: where the force comes from, its direction, its magnitude (from L1–L3 measurements or from the cell: cup pull-off force, syringe swap force, valve mass × 5 g).
- [ ] Analyse the original (`docs/analysis_original.md`): slicer time, mass, support volume, the orientation it was printed in and why; the weak point (from the L1/L2 test data or from the damage it has already suffered); where material is wasted (regions with no load path, walls thicker than needed, infill that carries nothing); the print-time integration curve (cross-section area vs. Z) that shows where the time goes.
- [ ] Define the test: fixture, load direction, robot speed, what "failure" or "out of tolerance" means, the number of repetitions (3 per version for load; for cycles, up to 100 cycles or until the tolerance is crossed). The test is defined and dry-run on the original before any redesign is drawn.
- [ ] Approach 1, manual: redesign in Fusion in the same file as the original (copy the design, keep the mounting geometry as a locked sketch). Ribs on the load path, wall thickness in multiples of 0.45 mm, chamfers instead of overhangs, bolt holes placed by the Lab 2 rule. Keep every interface dimension (nozzle clamp, table pins, valve holes) identical.
- [ ] Approach 2, generative: preserve geometry = the interfaces; obstacle geometry = the syringe, tubes, cup travel, LED cone, or the pockets and feet; load case as above with a safety factor of 2; manufacturing constraint = additive, overhang 45°, minimum thickness 1.8 mm. Pick one outcome by the metric, export as a body, clean it (Fusion "Design from outcome"), and check it prints without a support forest.
- [ ] FEA on all three versions with the same load, same constraints, same mesh size (Simulation section). Predicted failure load per version written down before printing.
- [ ] Orientation: run the L1 print-time integration on all three, in three orientations each; pick the orientation per version by the metric (time for A, inter-layer direction away from the load for B and C). Nine slicer runs in a table.
- [ ] Print: three versions × 3 pieces (load test) or × 1 piece (cycle test), same printer, same profile except orientation and supports. Record the actual print time from the printer's display.
- [ ] Test on the MG400: same fixture, same taught points, same speed for all pieces; scale readings or cycle counts to CSV. Video of one pull per version.
- [ ] Comparison table and conclusion in the notebook and the README: is manual better than generative? Where did the generative result cheat (thin features, support cost, unprintable overhangs) and where did it find something you did not?
- [ ] Repo: `3d-print/lab4/` with `fusion/`, `stl/`, `notebooks/`, `docs/`; `AGENTS.md` updated with which version is now on the cell.

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

### Simulation

Two simulations, both in Fusion 360.

1. **Static stress on all three versions**: same material (the filament actually used, yield strength edited to the datasheet value), same constraints on the preserved geometry, same load case and magnitude, same mesh size (adaptive refinement off, element size set explicitly so the three studies are comparable). Report per version: peak von Mises stress, its location, displacement at the point of use (syringe tip, pocket centre, valve face), and the predicted failure load = load × yield / peak stress, corrected by the L1 inter-layer ratio if the peak is across layers. Table in `docs/fea/fea_table.md` with screenshots.
2. **Generative design study**: preserve, obstacle and load definitions; the outcome explorer filtered by the metric (mass for A, max displacement or safety factor for B, mass with a thicker minimum wall for C); the chosen outcome and two rejected ones with the reason. Screenshots in `docs/generative/`.
3. **Print-time integration**: the L1 notebook run on the nine STL files (three versions × three orientations), compared with the slicer estimate; the orientation choice per version follows from this table.

### Analysis

1. **Original-part analysis** (`docs/analysis_original.md`): the items in the Project Breakdown, with numbers: time in minutes, mass in g, support volume in cm³, the weak point named with the L1/L2 measurement that shows it.
2. **Orientation table** (`docs/orientation.csv`): columns `version, orientation, my_time_min, slicer_time_min, support_cm3, layers_across_load (0|1)`. Nine rows. The chosen orientation per version marked.
3. **Load or cycle test** (`docs/load_test.csv`): for metrics A and B, columns `version, piece, orientation, peak_force_N, break_location, predicted_N`; nine rows. For metric C, columns `version, cycle, measured_property_mm_or_N, in_tolerance (0|1)`; one row per cycle per version, up to 100, and the cycle at which the property left the tolerance band. Notebook `notebooks/comparison.ipynb`: mean and range per version; predicted vs. measured; bar chart of the metric with the "equal" constraint drawn as a line (equal strength for A, equal time for B).
4. **Comparison table** (in the notebook and the README): columns `version, print_time_min (slicer, measured), mass_g, failure_load_N or cycles, support_cm3, support_removal_min, fea_predicted_N, orientation`. Three rows. Under it, four sentences: which version wins on the chosen metric; by how much; what it costs on the other metrics; and whether the generative outcome would have been chosen without the manual version to compare against.
5. **Dimensions** (`docs/dimensions.csv`): three axis measurements per printed piece; for the tray, the pocket positions in the L2 format so the registration number can be re-checked.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: Fusion 360 Intersection Test

Before printing, verify that the virtual objects in the computer are properly constrained relative to each other and check that objects don't intersect each other. For this task: each version in the assembly it belongs to (holder on the nozzle with syringe, tubes and LED cone; tray on the feet with glasses and the holder at the pick pose; bracket in the tool housing with the valve and fittings). The generative outcome is checked after clean-up, not before.

#### Test Example 2: Basic Dimensions

After printing, you need at least one measurement in each axis — three measurements that are easy to check with calipers, to verify the finished object is to scale and not stretched. When the drawing is complete, a dimension table must be included (this is as necessary as automated testing in software). The interface dimensions of all three versions must agree with the original within 0.2 mm; otherwise the comparison is between different parts.

#### Test Example 3: Interface fit

Each version mounts where the original mounts (nozzle clamp, table pins, valve holes) with no filing. Time to mount under 2 minutes. For the holder: the one-handed swap from L1 still passes. For the tray: pick 5 of 5 with the L2 taught points. For the bracket: tool mass still under 250 g.

#### Test Example 4: Repeatable load test

Same fixture bolted to the same table holes, same taught points, same speed (20 %), same MovL length for every piece. The original is pulled first and last; if its two results differ by more than 15 %, the fixture moved and the series is repeated.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* `README.md` first commit of the task naming the part, the metric and the load case in one sentence each.
* `docs/load_test.csv` with nine rows (or the cycle rows for metric C) and the video of one pull per version.
* `docs/orientation.csv` with nine rows.
* `docs/fea/fea_table.md` with the predicted failure load per version written before the test (commit date earlier than the load CSV).
* Comparison table with three rows and the four-sentence conclusion.
* All three versions physically present at the defense, the winning one mounted on the cell.
* Photos of the scale reading (mass) for each version.

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Repo only. The comparison table is quoted in the Prototyping M1 audit.

### Safety

* Load tests: fixture bolted to the table, robot at 20 % speed, MovL not more than 30 mm past the expected break, safety glasses, nobody inside the arm's reach. A generative part can fail in an unexpected place; expect fragments.
* If the part is the holder, the syringe is empty for all tests; if the bracket, the valve is unpowered and the LED disconnected.
* Coordinate with the Data Acquisition team before removing the original from a running cell.

### Components for the next lab

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| Polycarbonate sheet sample, 2 mm, clear, protective film both sides | 1 piece (about 200 × 300 mm) | Test cuts and the fit check against the jig before the batch is ordered |
| Quotes from two CNC-milling or die-cutting shops | 2 | Not a part: obtain them before 04.12 with a preliminary drawing, so the L5 review can compare price, lead time and their stated tolerance |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — three versions in one Fusion file with locked interfaces, generative study, nine 3MF files | 5 p |
| Analysis — orientation table, load or cycle CSV, FEA prediction vs. measurement, comparison table | 5 p |
| Prototype — three versions printed, interface fit passed, repeatable test run, winner on the cell | 5 p |
| Documentation — original-part analysis, the four-sentence conclusion, generative outcome reasoning, AGENTS.md | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `3d-print-lab4` 72 h before the defense.**

The defence is online on 08.12.26. The tag deadline is 72 h before it, which is Saturday 05.12.26 — the same weekend as the contact session where the next lab is handed out. Anything that has to be shown live, the robot moving or a print or a measurement, has to be visible on the call, so join from the lab.

The tagged repo must contain, under `3d-print/lab4/`:
* `fusion/`: `.f3d` and `.step` of the three versions; the FEA studies; the generative study or its exported outcome.
* `stl/`: nine `.3mf` files (three versions × three orientations) and the STL of the printed orientation per version.
* `notebooks/`: `print_time.ipynb` (copied from L1 and run on the nine files), `comparison.ipynb`, with outputs.
* `docs/`: `analysis_original.md`, `orientation.csv`, `load_test.csv`, `dimensions.csv`, `fea/`, `generative/`, videos, photos.
* `README.md`: part, metric, load case, comparison table, conclusion, which version is on the cell.
* Team `AGENTS.md` updated.

Live change at the defense: the instructor changes the load magnitude or direction by a stated amount; the team re-runs the static stress on the winning version and states the new predicted failure load. Or: the instructor names a different metric and the team says, from the table, which version would win and why.

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

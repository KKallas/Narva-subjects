## 3D Printing and CAD: Lab 5 — ISO drawing and CNC order

**Workload:** 24 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 04.12.26 | **Order date:** 06.01.27 | **Defense:** 19.01.27, online

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the lab folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

Everything so far was printed in the lab, where a wrong dimension costs an hour. This task designs a part that is made outside and orders it. The drawing is the order document: the shop reads it, not your Fusion file, and what the drawing does not say the shop decides. The preferred object is the polycarbonate glass batch for the tags: 50–100 pieces, about 24 × 24 mm, 2 mm clear polycarbonate, CNC-milled or die-cut, never laser-cut. It has a user outside the course: the 2027 summer camp plays with tags built from this batch, so a drawing that is "good enough" is not an option. The alternative object, for a team that can argue for it, is the tray base plate that registers the tray to the robot, in aluminium or polycarbonate.

The glass is toleranced against two things it meets in the cell: the gluing-jig pocket from Lab 2 (a printed part, ±0.3 mm) and the φ13 / φ16 suction cup that lifts it by its face. The drawing therefore carries ISO views and a section, dimensions with tolerances, GD&T on the outline and the corner radius, surface and edge condition, material and film. A tolerance analysis shows whether a CNC part at ±0.1 mm and a printed pocket at ±0.3 mm fit together at worst case, and the notebook shows the same with a stack-up.

The order goes out after the instructor review at the 04.12 meeting, the same logic as the PCB review in Data Acquisition L3. The parts arrive in semester 2 and are validated on arrival: calipers, fit in the jig, lift with the cup. If they are wrong, the report says whether it was the drawing or the shop.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* 3D Printing L2: the gluing-jig pocket dimensions and the registration numbers; the tray drawing format; the pocket-position caliper data.
* 3D Printing L1 and L3: the cup (φ13 or φ16, decided in L3) and the tool it sits on.
* Data Acquisition L4: the pick-success data with the dummy glasses (cut from sheet, ±0.3 mm or worse): how much outline error the pick already tolerates.
* Order of 24.11: the 2 mm polycarbonate sample and the two shop quotes.
* Tag hardware decision (AtomS3 vs. AtomS3R, made before the 24.11 tag order): the glass outline follows the tag's screen shell.

**Gives to**
* Prototyping M5 and the summer camp 2027: the glass batch and its drawing.
* Prototyping M1 audit: the validation report (drawing or shop).
* 3D Printing integration project: the manufacturing-ready drawing.

### Background Information

* **Fusion 360 drawings**: https://help.autodesk.com/view/fusion360/ENU/ — search "Drawing", "Section view", "Detail view", "Geometric tolerance", "Datum", "Surface texture", "Title block".
* **ISO 128 and ISO 129 (drawing presentation and dimensioning)**: search phrase "ISO 129-1 dimensioning rules summary"; the standards are paid, summaries are enough for this task.
* **ISO 1101 (GD&T)**: search phrase "ISO 1101 geometrical tolerancing profile of a surface position datum" — profile of a surface is the control for the outline of the glass; position for the plate holes.
* **ISO 2768 general tolerances**: search phrase "ISO 2768-m table linear dimensions" — the default the shop applies to anything you do not tolerance; write the class in the title block.
* **Polycarbonate sheet data**: search phrase "polycarbonate sheet 2 mm datasheet thickness tolerance" — sheet thickness tolerance is typically ±0.1 mm or worse; you do not control it, you specify the acceptable range.
* **Why not laser**: search phrase "laser cutting polycarbonate fumes yellowing" — polycarbonate chars, releases toxic fumes and yellows at the edge; every shop that laser-cuts acrylic will offer it anyway.
* **Die cutting vs. CNC milling for small plastic parts**: search phrase "die cutting polycarbonate 2 mm minimum quantity tooling cost" and "CNC routing polycarbonate small parts tabs".
* **Suction cup contact**: dobot-robots.com, MG400 suction cup kit page; the cup's lip diameter is what must land inside the glass face with margin.
* **Tolerance stack-up**: search phrase "tolerance stack-up worst case vs RSS root sum square" — both are computed in the notebook.

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. Fusion 360 (Drawing workspace)
2. Digital calipers (0.01 mm), a micrometer if available (sheet thickness), a radius gauge or a printed radius template
3. The gluing jig from L2 (both prints) and the source tray; an AtomS3 or AtomS3R from the 24.11 order
4. MG400 with the tool, φ13 and φ16 cups, the RPI station
5. The 2 mm polycarbonate sample from the 24.11 order; a hand file, a fine saw or a scoring knife for test pieces (no laser, no hot tools)
6. The two shop quotes; the shop's own drawing requirements (file format, units, tolerance class they can hold)
7. Jupyter Lab for the stack-up notebook
8. In semester 2, on arrival: the same calipers and jig, the 0.01 g scale for one glass mass (a check on thickness and material)

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Decide the object (glass batch or base plate) and the quantity on day one; write it in the README with the reason. For the glass: 50–100 pieces, the number set by the tag count planned for the camp plus 30 % scrap.
- [ ] Measure what the glass meets: the AtomS3 (or AtomS3R) shell outline and corner radius (three units if available, three readings each), the L2 jig pocket on both prints (width X, width Y, depth, corner radius), the cup lip diameter for φ13 and φ16. Table in `docs/mating_dims.csv`.
- [ ] Define the functional requirements as numbers in `docs/requirements.md`: outline fits the pocket at worst case; the glass covers the screen and the bezel band where the resin sits; the cup lip lands on the face with at least 2 mm margin on every side at the worst-case pick offset (from the L2 registration number plus the robot repeatability); thickness range accepted; edge condition (no burr above 0.05 mm, no crack); protective film on both faces, removed by the operator after the pick or before; optical: clear, no yellowing at the edge, no scratches on the screen side.
- [ ] Fusion model of the glass with the outline, corner radius and thickness as parameters; the jig pocket and the cup as referenced components; the pick pose with the maximum offset.
- [ ] ISO drawing: front view with outline dimensions and corner radius, a section showing thickness and edge condition, a detail of one corner; datums A (one edge), B (adjacent edge), C (face); profile of a surface on the outline against A|B, flatness on C, thickness with limits; surface note for the edge; material "polycarbonate, clear, 2 mm, film both sides"; quantity; the tolerance class in the title block; "CNC milled or die cut, laser cutting not permitted" as a note on the drawing.
- [ ] Tolerance analysis (`docs/tolerance.md`): worst-case and RSS stack for the glass in the pocket (glass outline ±0.1, pocket ±0.3, printed pocket clearance from L2) and for the cup on the face (glass outline, pick offset, cup lip). State the minimum pocket clearance that still fits at worst case and check it against the L2 `pocket_clear` value; if the L2 value is too small, the jig is reprinted and the L2 caliper table updated.
- [ ] Test pieces from the sample sheet: three glasses cut and filed by hand to the drawing; check in the jig and under the cup; note what a ±0.3 mm hand-made part does, so the difference from CNC is seen before the batch arrives.
- [ ] Shop communication: send the drawing PDF plus DXF (or what the shop asks for) to both shops; record their questions verbatim in `docs/shop_questions.md`; every question means the drawing was incomplete, fix it and note the fix.
- [ ] Instructor review at the 04.12 meeting (drawing v1) and a second look by e-mail before the order; the checklist in `docs/review.md` signed off. Order placed after the review; order confirmation, price, lead time and the shop's stated tolerance in the repo.
- [ ] Validation plan (`docs/validation_plan.md`), written before the parts arrive: sample size (10 of 50, 15 of 100), which dimensions, the accept limits, the fit test in both jig prints, the lift test with both cups 10 times each, and the decision tree: out of tolerance vs. drawing → whose fault.
- [ ] On arrival (semester 2, before the Prototyping M1 defense): run the validation plan, fill `docs/validation.csv`, write the one-page report `docs/validation_report.md`.
- [ ] Repo: `3d-print/lab5/` with `fusion/`, `docs/`, `notebooks/`; `AGENTS.md` updated with the glass part number, the drawing revision and the shop.

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

### Simulation

The simulation here is the tolerance stack-up in `notebooks/stackup.ipynb`.

1. **Glass in the pocket**: chain = pocket width (nominal, ±0.3 printed) − glass width (nominal, ±0.1 CNC or the shop's stated value) − 2 × clearance. Worst case: minimum pocket with maximum glass. RSS: `√(Σ tol²)`. Show the clearance distribution for 1000 Monte Carlo draws with uniform tolerances, the fraction that would jam (clearance < 0), and the nominal clearance that gives 0 jams at worst case. Same for the corner radius (a glass corner radius smaller than the pocket's jams first).
2. **Cup on the face**: chain = half glass width − pick offset (L2 registration `max |A − B|` + robot repeatability, take 0.1 mm if not measured) − half cup lip diameter. Margin per side for φ13 and φ16; which cup keeps 2 mm at worst case.
3. **Thickness and cure**: thickness range from the sheet datasheet; the cure dose changes with thickness only slightly at 405 nm, but the jig floor-to-screen-plane height from L2 must accommodate the maximum thickness; check the number.
4. One table at the end: feature, nominal, tolerance, worst-case result, RSS result, pass/fail, and the drawing dimension that was changed because of it.

### Analysis

1. **Mating dimensions** (`docs/mating_dims.csv`): columns `feature, unit_id, reading_1, reading_2, reading_3, mean, spread`; the AtomS3 outline and corner radius, both jig pockets, both cup lips. At least 8 features.
2. **Tolerance analysis** (`docs/tolerance.md` and the notebook): the two stacks, the Monte Carlo result, the clearance chosen, the cup chosen.
3. **Hand-cut pieces** (`docs/hand_cut.csv`): three pieces, outline X and Y at three places each, fit in the jig (0/1), lifted by the cup (0/1). Shows what ±0.3 mm looks like.
4. **Shop questions and drawing revisions** (`docs/shop_questions.md`, `docs/drawing_revisions.md`): every question, the drawing change it caused, the revision letter; the two quotes side by side: unit price, tooling cost, lead time, stated tolerance, file format asked for, minimum quantity.
5. **Validation** (semester 2, `docs/validation.csv`): columns `part_id, x_mm, y_mm, t_mm, r_mm, edge_ok, film_ok, fits_jig_A, fits_jig_B, lifted_13, lifted_16`; 10 or 15 rows. Notebook `notebooks/validation.ipynb`: mean and spread per dimension vs. the drawing limits; Cp if the spread allows; the verdict per feature: in tolerance, out of tolerance and the drawing said so (shop), out of tolerance because the drawing did not say (drawing).
6. **Alternative object only** (base plate): hole positions vs. the printed inserts they take (position tolerance vs. insert hole ±0.3), plate flatness, the same stack-up logic.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: Fusion 360 Intersection Test

Before printing, verify that the virtual objects in the computer are properly constrained relative to each other and check that objects don't intersect each other. For this task: the glass at maximum material condition (nominal + 0.1 mm) in the jig pocket at minimum material condition (nominal − 0.3 mm), and the cup at the worst-case pick offset on the glass face. No interference, and the cup lip fully on the face.

#### Test Example 2: Basic Dimensions

After printing, you need at least one measurement in each axis — three measurements that are easy to check with calipers, to verify the finished object is to scale and not stretched. When the drawing is complete, a dimension table must be included (this is as necessary as automated testing in software). For the glass: X, Y and thickness on every sampled part, in `docs/validation.csv`; the dimension table is on the drawing.

#### Test Example 3: Drawing read by a stranger

Give the drawing PDF alone (no Fusion file, no explanation) to another team; they cut one glass from the sample sheet by hand and measure it. Every question they ask is a missing item on the drawing. Pass: zero questions on the second revision.

#### Test Example 4: Fit and lift on arrival

Each sampled glass: drops into both jig prints by gravity and comes out with the ejection hole; lifted 10 times by the chosen cup at 50 % speed from the source tray to the jig, 10 of 10. Video of one part.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* Drawing PDF, revision letter on it, with datums, profile tolerance on the outline, thickness limits, edge and film notes, material, quantity, and the "no laser cutting" note; the DXF or STEP the shop asked for.
* `docs/review.md`: the instructor's review items from 04.12 and how each was closed; the order confirmation (PDF or screenshot) with date, quantity, price, lead time and the shop's stated tolerance.
* `docs/mating_dims.csv` with at least 8 features × 3 readings.
* `notebooks/stackup.ipynb` with outputs: worst case, RSS, Monte Carlo, the clearance and the cup chosen.
* `docs/hand_cut.csv` with 3 rows and the photos.
* `docs/shop_questions.md` with the questions from both shops and the drawing changes.
* `docs/validation_plan.md` written before arrival (commit date before the order confirmation date).
* After arrival (semester 2): `docs/validation.csv` with 10 or 15 rows, the video of Test Example 4, and `docs/validation_report.md` with the drawing-or-shop verdict.

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Repo only. The drawing PDF and the validation report are copied into the Prototyping M5 production documentation; the glass part number and revision go into the team `AGENTS.md`.

### Safety

* Laser cutting polycarbonate is forbidden. Polycarbonate under a laser does not vaporise cleanly: it chars and releases toxic fumes (it is a carbonate ester; the decomposition products irritate the lungs and eyes), and the edge yellows and cracks. No shop is allowed to laser-cut this part, and the lab laser is not used on the sample sheet either; the drawing says so.
* Hand-cutting the sample: score-and-snap or fine saw, edges filed; safety glasses; no hot-wire or heated blade (same fumes).
* On arrival: the film stays on until the lift test; edges of milled polycarbonate can be sharp before deburring.
* Lift tests at 50 % speed only after 10 of 10 at 20 %; nobody's hands on the table while the robot is enabled.

### Components for the next lab

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| — | 0 | Nothing. The order of 06.01.27 is spares only; the semester-2 list is handed out on 16.01.27 with the Prototyping Milestone 1 text. The glass batch itself was ordered by the team after the 04.12 review and arrives for semester 2. |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — parametric glass with jig and cup as components, drawing source, DXF/STEP as sent | 5 p |
| Analysis — mating dimensions, stack-up notebook, hand-cut comparison, validation CSV and verdict | 5 p |
| Prototype — reviewed drawing, order placed with confirmation, three hand-cut pieces tested; batch validated on arrival | 5 p |
| Documentation — drawing complete enough that the shop asked nothing on the final revision, review checklist, validation plan and report, AGENTS.md | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `3d-print-lab5` 72 h before the defense.**

The defence is online on 19.01.27. The tag deadline is 72 h before it, which is Saturday 16.01.27 — the same weekend as the contact session where the next lab is handed out. Anything that has to be shown live, the robot moving or a print or a measurement, has to be visible on the call, so join from the lab.

The tagged repo must contain, under `3d-print/lab5/`:
* `fusion/`: `.f3d` and `.step` of the glass (or the plate) with the mating components; the drawing source.
* `docs/`: the drawing PDF (all revisions, latest marked), the DXF/STEP sent, `requirements.md`, `mating_dims.csv`, `tolerance.md`, `hand_cut.csv`, `shop_questions.md`, `drawing_revisions.md`, `review.md` with the order confirmation, `validation_plan.md`; after arrival `validation.csv` and `validation_report.md`.
* `notebooks/`: `stackup.ipynb` with outputs; `validation.ipynb` after arrival.
* `README.md`: object, quantity, shop, revision, order date, expected arrival, and the validation status.
* Team `AGENTS.md` updated.

The defense on 16.01.27 is before the batch arrives: it is defended on the drawing, the stack-up, the hand-cut pieces and the order confirmation. The validation on arrival is added to the same folder in semester 2 and is part of the Prototyping M1 audit.

Live change at the defense: the instructor changes one input (the pocket tolerance to ±0.4 mm, the cup to the other size, or the tag to AtomS3R with a different corner radius); the team re-runs the stack-up notebook and says which drawing dimension changes and by how much.

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

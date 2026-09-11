## Prototyping: Milestone 5 — Production-Ready System

**Workload:** 14 hours | **Assessment:** 20 points | **Meeting: Sat 30.05**

At the end of M4 you had a tested enclosure, autonomy working at some level (up to the agent level with Claude Code, say) and ten simulated matches behind you (with a timer and a red area printed on paper — the real game infrastructure is built separately). M5 is the last milestone before the arena event. The core message: **if somebody else can take your repo, read it and build the same rover, M5 is finished**.

M5 has three parallel goals:

1. **Refine your rover into its final form** — the weaknesses that came out of the M4 tests fixed, documented, re-tested repeatedly
2. **Add localisation** — ArUco markers mounted on the arena ceiling, so the rover knows not only "what is in front of me" but also "where on the arena I am". This gives the autonomous agent a location-aware memory.
3. **Make the documentation production-run ready** — a third party must be able to assemble the same rover from the same repo without asking you anything

Plus one thing you have been accumulating all semester but have not yet put together: **a combined view of the M1–M4 measurements**. What improved? What got worse? What was left unsolved? This is the moment of truth for an engineering project — did what the specification predicted actually come true?

The priority order is: first the refinement (fix every row in the M4 table where "acceptable = no"). Then the localisation. Then documentation that a stranger really can read. Finally the combined graph.

---

### 1. Refinement and documentation of limitations

**Prerequisite:** at the end of M4 you have a table of "before / reinforcement / after / acceptable?". Every row — especially the ones where acceptable = no — is an input for M5.

**Goal:** M5 is not a "fix everything" milestone. It is an **honest documentation of limitations**. Every shortcoming left over from M4 must reach the end of M5 either (a) fixed and re-tested, or (b) clearly written down as a **documented limitation** — this is the technical limit, we are not solving it mechanically any more, we leave it to **software, control logic or the next generation of hardware**.

**Why documenting is just as important as fixing:**

The next people who work with your prototype — the software developer, whoever writes the control logic, whoever builds the next version — have to **know** what works and what does not. A documented limitation is **solvable** in the layer above (a filter in the code, manual calibration, a compromise in the strategy). A hidden limitation **bites** the user without warning.

Quietly dropping it, where a row simply disappears from the report, is not reasonable. But neither is "I have to polish everything to mechanical perfection" the point of engineering responsibility. A smart engineer knows **where more machining effort is worth it**, and where it is time to write the limitation down and hand it over to the next layer.

**An example M5 refinement table, continuing from where the M4 table ended:**

| Component | M4 status | M5 decision | Result | Final status |
|:---|:---|:---|:---|:---|
| Battery bay | Swap in 35 sec (over the threshold) | Magnetic fastening | Swap in 22 sec | Solved mechanically |
| Claude Code agent | Success 3/5 (got stuck on the edge) | `rover_stop` confirmation + better tool documentation | Success 4/5 | Solved in software |
| Colour sensor stability at the boundary | Confidence 0.52 | Not solvable mechanically — the sensor is unreliable at the edge, a better sensor placement would not change much | The same | **Documented limitation** — the software filters out confidence < 0.7, the operator does not see "ON TARGET" |
| Motor vibration above 80% | The mounting is not guaranteed | Bolt-and-nut construction tried, the vibration cannot be eliminated entirely | Slightly better | **Documented limitation** — the software limits the maximum speed to 75% |
| ... | ... | ... | ... | ... |

**We expect this table from the point of view of a stranger reading it too:** if someone opens the repo, they must be able to see from this table whether some M4 shortcoming has been solved, or whether they have to account for a documented limitation in their own use.

**Small things the M4 tests may not cover but that get in the way in a match — document those too:**

- The rover's start-up time (if it is over 10 sec, is it simplifiable, or do you document "needs time to start")
- Reconnecting the web interface after a WiFi dropout (is it automatic, or is it documented as "the operator reopens it")
- The rover's serial number or team marker being visible even upside down (the referee has to identify it)

**The principle:** every weakness you find gets either a solution or a line in the documentation. We assess both equally — because both help the next people know what kind of system they are working with.

---

### 2. Localisation — the arena's standard equipment

**Prerequisite:** the rover's front camera works; the M3 raycast from an image to a floor coordinate works.

**The problem:** so far the rover knows only as much about its location as it can see from the front camera. That limits the autonomy — the agent cannot decide "I have already checked the left side, I'll go right", because it has no location-aware memory.

**The solution — the arena's agreed standard format:**

The arena has **three levels of navigation aid**, all of them available to every team. Each team chooses which ones to use — from the cheapest (ArUco only) to the most accurate (combining all three).

**These are architecturally prepared aids, not the only permitted methods.** A team may also use other localisation solutions — UWB positioning (Decawave/Qorvo), a magnetic compass + dead reckoning, optical flow from a downward camera, a home-built solution, etc. The standard format does not restrict you; it simply guarantees that **some aids are always there** if you want to use them.

---

#### Level 1 — ArUco markers on the ceiling *(square accuracy, the recommended baseline)*

**9 markers** from the DICT_4X4_50 dictionary, each **20 × 20 cm** (fits on an A4 sheet), mounted at the **centre** of every 1×1 m OSB module on the ceiling at about **2 m height**.

The standard layout with chess-style notation (viewed from above). **The two opposite walls of the arena are marked by agreement in red and blue** — which team starts at which wall is decided at the match:

```
        Blue side
   ┌──────┬──────┬──────┐
   │  A3  │  B3  │  C3  │
   ├──────┼──────┼──────┤
   │  A2  │  B2  │  C2  │
   ├──────┼──────┼──────┤
   │  A1  │  B1  │  C1  │
   └──────┴──────┴──────┘
        Red side
```

The ArUco IDs correspond to the squares:

| Square | ArUco ID | Square | ArUco ID | Square | ArUco ID |
|:---|:---|:---|:---|:---|:---|
| A1 | 0 | B1 | 1 | C1 | 2 |
| A2 | 3 | B2 | 4 | C2 | 5 |
| A3 | 6 | B3 | 7 | C3 | 8 |

**The "top" edge of the markers faces the blue side** — all 9 markers on the ceiling are oriented the same way, regardless of which side the rover reads them from. That gives the rover a global heading reference (it can tell where the "blue side" is).

**The size of 20×20 cm — how it was derived:**

- Camera FOV ~60°, resolution 640 px → at 2 m height the visible area is 2.3 m wide → ~278 px/m
- ArUco decoding needs at least 30 px per edge → minimum marker = **11 cm**
- Doubled for safety margin (reflections, shadows, angles): **20 × 20 cm**

If your camera's FOV or resolution differs, do the same calculation. A ceiling lower than 2 m → you can make the marker smaller; higher → it has to be bigger.

**On the rover's side:** the rover needs an **upward-facing camera** — only that can see the markers on the ceiling. Two practical solutions:

- **A separate ceiling-facing camera:** add a second M5-CAM (or a simple USB webcam) with its lens pointing up. This is simpler and keeps the front camera stream separate from the overhead stream.
- **Reorienting the existing camera:** if the rover already uses the M5-CAM for the autopilot/agent, you can remount it facing up and navigate only with the colour sensors + ArUco. The front camera disappears and the agent has to rely entirely on the location memory + the downward sensors.

Both are workable — choose according to what your hardware allows. The rover's server reads a frame from the upward-facing camera with OpenCV's `cv2.aruco` module, decodes the ID of the visible marker, and knows its square.

---

#### Level 2 — Colour dots on the floor grid *(more accurate, uses the colour sensor you already have)*

The floor is drilled with a **10×10 cm grid** (5 mm holes). As a standard navigation aid, 3D-printed coloured studs are fitted (≤ 2 mm high, they do not obstruct the rover's driving).

| Location | Colour | How many in total | Meaning |
|:---|:---|:---|:---|
| The **centre** of every module | **Blue** | 9 | Reference for the module's centre |
| The **4 corners** of every module | **Yellow** | 9 × 4 = 36 | Reference for a module corner (a cluster forms at shared corners — neighbouring modules both mark the same physical place) |
| The centre of the arena (the centre of B2) | **Green** | 1 | The global origin (0, 0) |

The colours (blue, yellow, green) are chosen so that they are **clearly distinguishable with an RGB sensor** — each has its own dominant channel (B high for blue, R+G high for yellow, G high for green). In addition, **they do not interfere with the red marked areas**. White would be hard to tell apart from the light OSB surface with an RGB sensor (all three channels high in both), which is why green is chosen. The rover's colour sensor(s) (M4 section 2) read them when the rover drives over.

**The red areas and the colour dots:** if a red area (paper/film) is placed over a colour dot, **a hole is cut in it at that spot**. The colour dots always stay visible — the holes are made as needed at the start of each match, once the position of the area is known.

**The benefit for the rover:** when the rover drives over a blue dot, it knows "I am currently at the centre of module B2" — much more precise than ArUco's "I am in square B2".

---

#### Level 3 — Magnets in the floor grid *(very accurate, optional)*

An **NdFeB magnet** can be fitted into every 10 cm hole (a disc 5 mm in diameter × 2 mm thick — it goes 5 mm deep into the hole and does not obstruct the rover's driving).

The standard magnet layout (the same as the colour dots — the magnets are in the same holes):

- The **centre of every module** — 9 magnets
- The **4 corners of every module** — 9 × 4 = 36 magnets (at shared corners you can put one magnet in the hole that counts for both modules; but the count is 36)

The rover adds a **Hall or reed sensor** underneath. When the rover drives over a magnet, the sensor registers the exact moment. It gives a millisecond-accurate location reference.

**The advantage:** the magnets are **inside the floor**, not on top — the Hall sensor reads them through non-magnetic material too, so there is no need to cut holes in the red areas for the magnets (unlike with the colour dots).

**Not compulsory** — if a team prefers the colour dots or ArUco alone, they do not have to use magnets.

---

**Combining — what to choose:**

| Approach | Extra hardware | Accuracy | Who it suits |
|:---|:---|:---|:---|
| ArUco only | None (the front camera already) | Square accuracy (1 m) | A first version, the least risk |
| ArUco + colour dots | None (the colour sensor already) | ~5 cm at the dots | Middle ground, uses what you have |
| All three | A Hall sensor in addition | ~1 cm at the magnets | Maximum accuracy; no need to cut the red areas around the dots |

**Recommendation:** start with **ArUco only**, add the colour dots when you need better accuracy. Do the magnets last, once the rest already works.

**Other approaches (for the learning value):** UWB positioning (Decawave/Qorvo), a magnetic compass + dead reckoning, optical flow from a downward camera. The arena's standard format does not require them, but if a team wants to experiment — go ahead.

---

**The rover's logic:**

1. Every ~1 sec (or more often) the rover's server reads a frame from the **upward-facing camera** with the ArUco decoder
2. It recognises the ID of the visible marker → it knows its square
3. When it drives over a colour dot, the downward-facing colour sensor registers it → a more precise position
4. When the downward-facing Hall sensor reacts to a magnet → the most precise position

These are a **natural complement to the M3 raycast**: the raycast gives a precise coordinate for objects *visible ahead*; the arena's standard equipment gives the coordinate of where the rover *itself* is on the arena.

**Uses in M5:**

- **M4 Level 3 (the Claude Code agent)** gets a location memory: "I have been in squares A1, A2 and B2 — now try row C"
- **In the operator interface, display** a small 3×3 grid with a dot showing which square the rover is currently in
- **In a later verification** the game master can compare: if the rover says "I am in square B2" but the overview camera (once it is ready) sees it in C3 → a calibration problem

**Calibration check:**

1. Put the rover in the centre of B2 (the centre of the arena). Does the software say "B2"? Does the colour sensor see the blue dot?
2. Put the rover in the centre of A1. Does the software say "A1"?
3. Put the rover on the border of A1 and B1. Does the software give a reasonable answer ("A1 or B1, not fully confident") or does it hang?

**Typical problems:**

- **The markers are too small** → they are not read. Check before printing: marker width in px in the camera × distance / camera FOV ≥ 30 px.
- **The lamp light reflects off the marker** → laminate on a matt surface, not a glossy one.
- **The transition between two markers** → several seconds of "I see none". That is fine — the rover knows it is between two and can decide based on the previous position.
- **The colour dots are blurred** → clean the sensor, check the lighting; the difference between yellow and blue has to stay solid.
- **The magnets are too weak** → use stronger NdFeBs (N42 or higher); a Hall sensor is more sensitive to bigger magnets.

**YouTube/AI search terms:**

- `OpenCV ArUco marker detection tutorial`
- `ceiling marker robot localization`
- `aruco DICT_4X4_50 print A4`
- `Hall effect sensor magnet detection`
- `NdFeB magnet specifications N42`
- `indoor robot localization options comparison`

---

### 3. Production-run-ready documentation

**Prerequisite:** you have the M1 specification, the M2 tests, the M3 integration, the M4 refinement — all present in the repo.

**Goal:** a third party (not a member of your team, but somebody from another team) must be able to take **your repo and the components ordered from the order list** and build the same rover with them. Without asking you anything. Without any "you know, it'll get clearer once we build it together" moments. If they get stuck, that is a fault in your documentation, not a misunderstanding on their part.

**What production-run-ready documentation contains:**

| Document | What is in it | Format |
|:---|:---|:---|
| **README.md at the repo root** | What this project is, what the rover is like, how to get started | Markdown |
| **Assembly instructions** | Step by step, with pictures, at every step what you need, what to do, what to check | Markdown / PDF |
| **3D print files + CAD source files** | STLs with validated printing settings (orientation, supports, infill for each part) **AND** the CAD source files — for Fusion 360 `.f3z`/`.f3d` archives, for CadQuery `.py` script files. The STLs are an export; the actual design must be openable and editable. | STL + .f3z/.f3d or .py + a table of the settings |
| **BOM (Bill of Materials)** | The final component list with actual prices and suppliers | CSV or a Markdown table |
| **Software installation guide** | Clone the repo → configure → flash the MCU → start the server → the web page opens | Markdown |
| **Maintenance guide** | What wears out fastest, how to replace it, how often to check | Markdown |
| **List of known issues** | Every fault the M4 tests found + the solution or a justified decision to leave it | Markdown |
| **Operator guide** | How to play one match — from start-up to result | Markdown, 1 page |

**Minimum requirements for the assembly instructions:**

- **Every step is numbered** (not "then put the screw in", but "9. Put an M3×8 screw into the upper left hole of the motor")
- **Every step has a picture** (not one picture per 5 steps, but a picture for every step)
- **Every component is called by the same name** as in the BOM (if the BOM says "DRI0044 motor driver", do not use "L298" in the instructions)
- **The tools** listed at the start of the step, not repeated every time
- **Check points** ("after this step the wheels must turn smoothly, without catching") — without them the user does not know whether they did it right

**The software installation guide must contain:**

- Operating system requirements (Windows / Linux / Android in the case of Termux)
- The required installations (Python version, packages, Arduino IDE, drivers)
- Setting up the Python environment (the venv commands specifically)
- The command for cloning the repo
- The MCU flashing procedure (with which software, which port, which speed)
- A check of the first start-up (what you must see to be sure everything works)
- Typical errors on the first installation (the port is busy, a driver is missing, the WiFi password is wrong)

**An example maintenance guide:**

| Wearing part | Symptom | Action | Frequency |
|:---|:---|:---|:---|
| Motor mounting bolt | The motor vibrates | Loctite + tighten | Check after every 10 matches |
| Battery | Shorter runtime | Replace with a new one | After 100 charges |
| Colour sensor lens | Dirt, the reading gets less certain | Clean with a dry cloth | Before every round of matches |
| Wheels | The surface is worn | Replace with new ones | Based on a visual check |

---

### 4. Operator guide — 1 page

**Prerequisite:** the rover works and the levels of autonomy work.

**Goal:** one **A4 page** (double-sided if necessary) from which an operator (who has never seen it before) can run a whole match from start to finish. Not "what a rover is", but "how to play".

**What it contains:**

- **Start-up** — you switch it on, wait N seconds until the button glows green
- **Opening the web interface** — over which WiFi network, at which address
- **Calibrating the rover** — put the rover on the arena, check the colour sensor, press "calibrate"
- **The plan of the match** — 90 sec; the start comes as a signal from the referee (the clock starts from the server or the referee says "start"). At the end the rover automatically gets a "stop" command.
- **Switching the levels of autonomy** — when manual, when autopilot, when the agent (a short recommendation)
- **In a fault situation** — if the WiFi drops, if the rover does not respond, if the sensor shows something wrong — what to do first
- **After the match** — how to look at the result, how to prepare for the next one (including the battery swap)

The rule: **no more than one page**. If it does not fit, something is too complicated and needs simplifying on the interface side, not a longer guide.

---

### Production-run time budget (Analysis 1)

**Prerequisite:** the production-run-ready documentation has been put together.

**Goal:** work out how many extra rovers you can produce within the production window (30.05–11.06, ~12 days). This is an engineering question: is the documentation good, and do the physical constraints (printer, people) allow a production run at all?

**Measurement:**

1. **Time accounting for the 3D-printed parts:**
   - Measure the print time of every part (read it from the slicer or take it with a timer)
   - For every part note: file name, duration, material consumption (in grams)
   - Add up one rover's worth of parts

2. **Assembly time:**
   - Measure the real assembly time (if you get to build one more — use that)
   - If you do not, estimate the time of every step from the documentation + add a 30% reserve for unknown problems

3. **Component delivery:**
   - What is the longest lead time in the BOM? If a part takes 14 days, nothing makes it into the production run
   - Does the local stock (what is available in the classroom) let you start right away?

**Calculation in Jupyter Lab:**

- One rover = N printer hours + M person-hours
- You have K printers and L people available
- 12 days = 12 × usable days (a printer can run overnight, a person cannot)
- The result: the actual production-run capacity

**Table in the report:**

| Part | Print time (h) | Material used (g) | Notes |
|:---|:---|:---|:---|
| Base plate | 4.5 | 65 | 0.2 mm layers, 30% infill |
| Motor mount (×2) | 1.2 | 18 | Bolt+nut version |
| ... | ... | ... | ... |
| **The whole rover** | ... | ... | |

**Assessment:** if one rover takes 15 printer hours and 4 person-hours in total, then with one printer and two people you can produce about 5 rovers in 12 days. Does that meet the requirement?

---

### Documentation walkthrough (Analysis 2)

**Prerequisite:** the whole documentation has been put together (section 3).

**Goal:** your documentation works **only if** a third party can get things done from it. The only way to check that is to let somebody try.

**Measurement:**

1. **Choose a third person** — preferably a member of another team who has not seen your project before. At the very least a friend or a classmate.
2. **Give them only the repo link** + (if needed) the box of components.
3. **Let them try** one specific task:
   - Option A: install the software from scratch (a new computer, an empty environment)
   - Option B: find one part in the BOM and show which shop to order it from
   - Option C: read the assembly instructions and describe what they would build (without actually building it — you cannot afford to wait during the production run)
4. **Note every place** where they get stuck:
   - A term is not defined
   - A picture is missing
   - A command cannot be copied (it contains a curly quote that does not work from the browser)
   - It assumes knowledge that is not there

**Table in the report:**

| Place in the guide | Problem | Action | Done? |
|:---|:---|:---|:---|
| Software step 3 | "pip install" does not work the same way on Windows as on Linux | Add both variants | Yes |
| Assembly step 8 | The picture does not show which bolt | Mark it on the picture with an arrow | Yes |
| BOM row 15 | "ESP32-CAM" — which model exactly? | Add an AliExpress link | Yes |
| ... | ... | ... | ... |

**Assessment:** if the third person finds **fewer than 10 problems** — the documentation is good, fix them. If more than 20 → a bigger rewrite is needed, not just fixes.

---

### Combined graph of the M1–M4 measurements (Analysis 3)

**Prerequisite:** the measurements from all the earlier milestones are in the repo as CSV files.

**Goal:** this is **the moment of truth for the whole project**. What did you promise in the M1 specification? What did the M2 tests show? What improved with the M3 integration? What changed in the M4 refinement? One Jupyter notebook that brings it all together and **shows visually** the story of the rover's development.

**What to bring together:**

| Milestone | Metric | Type of number |
|:---|:---|:---|
| M1 | The speed promised in the specification | m/s |
| M1 | The battery runtime promised in the specification | min |
| M2 | Measured pushing force | N |
| M2 | Measured communication latency (median, max) | ms |
| M2 | Measured distance sensor accuracy | cm |
| M3 | Click-and-drive error | cm |
| M3 | Boundary detection success rate | % |
| M3 | Battery runtime with the integrated system | min |
| M4 | Enclosure durability over 5 collisions | % of parts loosened |
| M4 | Colour sensor confidence | 0–1 |
| M4 | Success rate of the levels of autonomy | 5/5 |
| M4 | Reliability over 10 matches | number of restarts |

**Visualisations:**

- **Line graph on a time axis:** every milestone is a point, connected by lines — what improved, what got worse
- **Specification vs. reality:** a bar chart where for each metric the M1 promise stands next to the M4 measurement
- **Use of time:** how many hours each milestone took, compared to what was planned in the specification

**Table in the report:**

| Metric | M1 specification | M4 measured | Assessment |
|:---|:---|:---|:---|
| Max speed | 0.5 m/s | 0.42 m/s | Below spec, but enough for a match |
| Battery runtime | 60 min | 38 min | Below spec, has to be charged between rounds of matches |
| Communication delay | < 100 ms | 87 ms (95th percentile) | Within spec |
| Click-and-drive error | < 5 cm | 12 cm | Over spec — fix before the production run |
| ... | ... | ... | ... |

**A short reflection (1 free-form paragraph):**

- What was the biggest surprise for your team from M1 to M4?
- Which prediction held true and which went completely wrong?
- If you had to write the M1 specification again today, what would you change?

This reflection is not small talk — it is the most valuable part of everything you have learned over the whole semester. The real result of an engineering project is what you do differently **at the start of the next project**.

---

### Assessment criteria

| Category | Points | What is assessed |
|:---|:---|:---|
| Work files | 4 p | Final code, STLs **and CAD source files** (Fusion `.f3z`/`.f3d` or CadQuery `.py`), BOM, photos and videos |
| Analysis | 4 p | 3 Jupyter notebooks (production-run time budget, documentation walkthrough, M1–M4 combined graph) |
| Prototype | 4 p | The rover is refined, the localisation (ArUco on the ceiling) works, the results are documented |
| Documentation | 4 p | Production-run ready (assembly, software, maintenance, operator guide, known issues) |
| Q&A | 4 p | Demo at the meeting + reflection: what of this carries over into the next projects? |
| **Total** | **20 p** | |

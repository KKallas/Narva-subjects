## Prototyping: Milestone 4 — Functional Prototype with an Enclosure

**Workload:** 16 hours | **Assessment:** 20 points | **Teamwork:** teams of 4

### What you do

You take the M3 enclosure and make it match-ready: you test its durability and reinforce the weak spots with concrete bolt-and-nut fastenings. You add "ON TARGET" feedback to the rover that tells the operator whether their rover is on the red area. You add three levels of autonomy — from manual clicking all the way to a Claude Code (or similar) agent that finds the red area and drives there by itself.

**Game rules:** 90 seconds, both teams' rovers start from their own wall, the winning team is the one with more rovers on the red area at the end (≥ 70% overlap).

**Evaluating and reinforcing the M3 enclosure** — four specific tests on the existing enclosure:

- A: motor heat test (5 min at full throttle, check for deformation)
- B: repeated wall collision test (3–5× on the same enclosure, cumulative damage)
- C: battery swap time test with a beginner operator (< 30 sec)
- D: component removability for debugging (sensor < 2 min, compute platform < 1 min, motor < 5 min)

For each fault, a decision: simple loosening → Loctite; repeated loosening → bolt-and-nut fastening (bolt through the PLA, nut on top compressing the layers); plastic fracture → design change. At the end of M4 you have a "before-and-after" comparison table: where you spent time and how much it paid off.

**Operator feedback "ON TARGET"** — the rover itself decides in real time whether it is on the red area (≥ 70% of its underside on the patch) and shows the operator a large indicator. Three options, in increasing complexity:

- A: single sensor + confidence score + stability filter (M3 baseline)
- B: 2–4 sensors on the rover's underside, a "70% agree" rule
- C: a downward-facing camera on the rover, measuring the area in the image

**Levels of autonomy on the rover side** — the operator selects in the web interface:

- **Level 1 (manual):** M3 click-and-drive from the front camera
- **Level 2 (autopilot):** a "Find red" button; the software finds the largest red region in the image and clicks it itself
- **Level 3 (existing agent):** Claude Code (or similar) works through a clean tool kit — `rover_camera`, `rover_status`, `rover_rotate`, `rover_drive`, `rover_click`, `rover_stop`. Your job is not to build the agent but to design a simple and clear API.

**Game context** — the overview camera, the official scoring and the match protocol are built outside M4. In M4 you run your tests with a timer and a red area printed on paper; the rover must be ready to listen to the referee's "start"/"stop" commands and to accept only preparation commands outside of a match.

### Analyses (Jupyter Lab)

Three analyses in Jupyter notebooks:

1. **Operator feedback accuracy** — you deliberately place the rover in the centre of the patch, on its edge, and on the bare arena. You read 30 seconds of readings and compare whether the indicator matches expectations. In the centre ~100%, on the edge ~0%, on the bare arena 0%.
2. **Comparison of the autonomy levels** — the same task (drive onto the red area) at each of the three levels, 5 attempts each. Measure success rate, time, number of operator clicks, wrong moves. Where does each level fit, where does it fail?
3. **System reliability over 10 matches** — **diagnostics**, not a pass/fail requirement. Drive 10 consecutive 90-second matches, log the faults from the software (WiFi dropouts, lost commands, sensor instability, agent errors). The goal is not to reach zero but to know where the system gets weak over time.

### Required for the defence

**Only a link to the git repository.** The repo must contain:

- Working code (at least two levels of autonomy working, the third documented even if broken)
- API documentation for the tool kit (for Level 3), so that a stranger can get Claude Code talking to your rover
- Jupyter notebooks for the analyses together with the measurement data (CSV)
- An updated specification + a **before-and-after table** of the enclosure reinforcements
- STLs with print settings for the reinforced enclosure **+ CAD source files** (Fusion `.f3z`/`.f3d` archives or CadQuery `.py` scripts)
- Photos and videos of the enclosure and the tests

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Work files — code in the repo, STLs **+ CAD source files** (Fusion `.f3z`/`.f3d` or CadQuery `.py`), photos/videos | 4 p |
| Analysis — 3 Jupyter notebooks | 4 p |
| Prototype — PLA enclosure with bolted fastenings, at least 2 levels of autonomy working | 4 p |
| Documentation — specification update + Level 3 API documentation | 4 p |
| Q&A session — demo + discussion of the levels | 4 p |
| **Total** | **20 p** |

### Full worksheet

📎 *Add a link to the full worksheet here*

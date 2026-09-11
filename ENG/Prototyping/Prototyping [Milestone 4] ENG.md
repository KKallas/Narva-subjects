## Prototyping: Milestone 4 — Functional Prototype with an Enclosure

**Workload:** 16 hours | **Assessment:** 20 points | **Meeting: Sat 30.05**

**NB: the deadline for the 3rd order (the last components) has been postponed to 30.05.**
<link to the order table>

At the end of M3 you had an integrated rover that drives according to clicks in its own front camera stream and stops in front of the red boundary. Now you put it into a solid 3D-printed PLA enclosure and get ready for a real match.

**Game rules:** 90 seconds, both teams' rovers start from their own wall, **each rover = one operator**. There are **marked areas — red-coloured** on the arena. The winning team is the one with more rovers on the red area at the end.

**An important principle:** during the match the rover and the operator use **only the rover's own sensors** — the front camera and the colour sensors. The official score is read by the game master from the overview camera; the rover's own measurement gives the operator quick "ON TARGET" feedback so they know whether they need to keep steering or can move on to the next rover. **The operator does not see the overhead view** — not in the control interface, not on an info panel, and not as a review after the match.

At the end of M4 the operator can choose between three levels of autonomy: from fully manual clicking to an LLM-based agent that finds the red area and drives there by itself. On top of that, **in Analysis 3 we measure** how the system holds up over ten consecutive 90-second matches. That is not a requirement in itself — at a real tournament you do whatever you need to between matches — but a diagnostic: if the rover cannot hold up without constant intervention, the system accumulates faults over time (memory leaks, WiFi does not recover, the calibration drifts). 10 matches in a row is a simple way to make such hidden problems visible.

The priority order is: first the enclosure and its durability tests (without them all the parts are at risk). Then detecting that you are standing on the area. Then the levels of autonomy on the rover side. The game's own infrastructure (overview camera, official scoring, match protocol) is outside M4 — see section 4 for a short description. If something does not work after assembly — **do not continue**, find the fault.

---

### 1. Evaluating and reinforcing the M3 enclosure, and the match load test

**Prerequisite:** from the end of M3 you have a working enclosure — of any material (PLA, PETG, plywood, cardboard, a combination) and built by any method. M4 does not start with "build a new enclosure" but with **"take what you have and make it match-ready"**.

**Goal:** measure the durability of your M3 enclosure with specific tests, find the weak spots and reinforce them with specific techniques (mainly a bolt-and-nut pre-tensioned construction). By the end of M4 you have a **before-and-after comparison**: numbers showing what improved, what stayed the same and what still needs work.

---

**Test A — Motor heat test**

The motor at full throttle for 5 minutes. Start it with a program and turn the rover upside down so the wheels spin in the air. Every minute, measure the temperature of the motor housing (a contact sensor, a contact thermometer or an IR sensor).

After 5 minutes check: has the enclosure deformed around the motor mount? PLA already softens at 50–55 °C — if the motor's heat reaches the plastic, you will see it immediately.

Acceptable threshold: the enclosure temperature at the motor below 45 °C.

---

**Test B — Repeated wall collision test**

On the **same** enclosure, not on a freshly printed one. The test measures **cumulative damage** — does the fifth collision do more damage than the first? If so, something is fatiguing.

Place the rover 1 m from the wall, aim it straight at it, and run "full speed for 1 second". After every collision:

1. Take a photo (from the same angle — for comparison later)
2. Note in a table what moved, loosened or came off
3. Measure the camera angle — make a template with the area visible in the video marked on it and check whether the area is the same after the collision
4. Check the position of the colour sensor — same as with the camera

Repeat **3 times in a row**. If the first 3 go cleanly, you can do 2 more — 5 in total, to satisfy the acceptable threshold. If something breaks or loosens seriously already at the first collision, **stop** and write it down — that is your input for the improvements. You do not need to destroy the enclosure to prove that it is weak.

Acceptable threshold: after 5 collisions no more than 1 part loosened, the camera angle changed by less than 3°, the sensor still at 5 ± 1 mm height.

**If the enclosure is already fragile from M3:** start from 0.5 m at half speed and measure whether it survives that. The goal is to **measure**, not to build a new one because the old one broke during the tests.

---

**Test C — Battery swap time test**

Give the rover to a **beginner operator** (a friend or a classmate who has not seen it before). Let them swap the battery — show them once first, then let them do it. Measure the time.

Acceptable threshold: after one demo the operator should swap the battery in under 30 sec. If it takes longer, the enclosure is too complicated.

---

**Test D — Removability of components for debugging/programming**

Measure how long it takes to:

- Remove the colour sensor (for debugging or replacement)
- Remove the phone or the M5-CAM (for USB debugging)
- Remove a motor (if one breaks between matches)

Acceptable threshold: swapping the colour sensor under 2 min, the compute platform under 1 min, a motor under 5 min.

---

**Each test result → a specific reinforcement**

For each fault you decide on one of three:

| Fault type | Action |
|:---|:---|
| Simple loosening (a bolt has come loose) | Loctite + higher torque; add it to the maintenance procedure |
| Repeated loosening in the same place | **Bolt-and-nut fastening**: print a clearance hole, the bolt goes through the material, a nut on top compresses the layers |
| Plastic fracture or deformation | Design change (thicken the wall, increase the infill, add a reinforcing rib) |
| Too much heat | Either a material change (PLA → PETG in that place) or better airflow (a hole, a fan) |
| A component does not come off or takes a long time | Simplify the mechanics (replace a screw with a clip or a magnet) |

---

**The principle of a bolt-and-nut fastening (if you do not have one yet):**

The weakest point of a printed PLA part is **the adhesion between the layers**. If you screw a motor mounting bolt straight into PLA, it unscrews itself or tears the layers apart — especially when the motor gets hot. The solution: do not leave the load on the plastic alone; direct it through metal that presses the layers against each other.

In practice:

1. In the design, print a clearance hole for the bolt
2. Push the bolt through from below
3. Add a washer and a nut on top
4. Tighten — the nut compresses the layers

Heat-set inserts give the same effect more elegantly — they are pressed into the PLA with a soldering iron and you get a metal thread. But a bolt-and-nut fastening is cheaper and lets you take the enclosure apart and put it back together more times.

---

**At the end of M4 you document:**

| Component | Before (M3) | Reinforcement | After (M4) | Acceptable? |
|:---|:---|:---|:---|:---|
| Motor mount | Bolt straight into PLA | Bolt + nut underneath | Survived 5/5 collisions | Yes |
| Camera holder | Glue | Bolt + rubber washer | Angle changed by 1.5° | Yes |
| Battery bay | Loose space | Clip with a latch | Swap in 18 sec | Yes |
| ... | ... | ... | ... | ... |

This table is one of the most important results of M4 — it shows where you spent your time and how much it paid off.

**YouTube/AI search terms:**

- `bolt and nut joint 3D printed PLA`
- `heat set insert PLA install soldering iron`
- `I2C temperature sensor`
- `loctite threadlocker electronics`

---

### 2. Operator feedback — "am I on target?"

**Prerequisite:** the M3 colour sensor(s) work in the enclosure; the colour of the red area is calibrated.

**The problem we are solving:** the official score comes from the overview camera after the game ends (section 4). But during the match the operator has to **know for themselves right away** whether their rover has reached the red area and whether the game master is going to count that point. Without that feedback they:

- Keep clicking and steering even though the rover is already there
- Move the rover away because they do not know whether it made it
- Waste precious time within the 90 seconds

**The solution:** the rover measures with its own colour sensor whether it is on the red area, and shows the operator a **large, clear "ON TARGET" indicator** in the web interface. The autonomous agent uses the same signal to end its cycle ("goal achieved").

This is not the official score — it is an **operator UX system**. The rover estimates its presence as well as it can, and if the game master's picture shows something else, that is a calibration question you can argue about afterwards. But during the match the operator needs a fast signal, not perfect truth.

**The 70% coverage rule — a shared definition for the operator feedback and the game master's score:**

A rover counts as being on the area if **at least 70% of its underside is on the red area**. The same rule applies on both sides:

- **The rover itself** tries to estimate this with its sensors (options A, B, C below) — feedback for the operator
- **The game master** measures it through the overview camera (section 4) — the official score

In both cases the 70% threshold is geometric and clear — if the measurements disagree, it is either a weakness in the sensor calibration or a disputed borderline situation.

---

**How to measure it? Three options, in increasing complexity:**

**Option A — A single sensor, with a confidence and stability filter** *(the M3 baseline)*

If you have one TCS34725 in the middle underneath from M3, continue with that. Threshold: the sensor is stable (5+ consecutive readings of red) + confidence score ≥ 0.7 = the rover counts as being on the area. That is not literally "70% of the area", but in practice the same logic: the confidence score measures how cleanly the colour matches the calibrated red, and if the rover is standing in the middle of the area and the sensor clearly sees red, then most of the surface beneath it is red.

Simpler, but less accurate at the edges. Fine as a first version.

**Option B — Several sensors on the rover's underside** *(more accurate, a valuable addition for M4)*

Add 2–4 sensors and spread them across the rover's underside (e.g. at four corners or in a triangle). Each sensor reports from its own place: "the floor above me is red" or "it is not". **70% of the sensors agree** = the rover is on the area. With 4 sensors = 3/4, with 5 sensors = 4/5, with 7 sensors = 5/7.

This matches the "70% of the area" idea better — the sensor layout simulates an area measurement by statistical sampling. You add more hardware (a couple of TCSs and an extension of the I2C bus), but the logic stays just as simple: read the values, count who agrees.

**Option C — A downward-facing camera on the rover** *(the most accurate, the most complex)*

Add a small downward-facing camera (a second M5-CAM, or change the angle of the rover's front camera downwards). Analyse the image on the rover's server: how much of the frame is red. It gives a real 70%-of-the-area measurement and works with irregularly shaped areas as well.

An excellent addition if you get that far — and it builds a bridge to Level 3 of autonomy (the LLM agent), because the same camera can also feed the LLM.

---

**Choose according to your team's skills and the deadline.** Option A works if M3 was done properly. Option B gives a more reliable measurement and the clarity you need for a match. M4 assesses **how each option works and where it breaks** — the most perfect one is not compulsory; what matters is that each option is tested and documented.

**The stability filter (in all the options):** a single reading does not count — there must be **at least 5 consecutive readings** of "on the area" (~250 ms) for the rover to consider itself firmly on the area. Otherwise random readings (reflections, shadows) would flip the indicator back and forth. The stability filter also means that the rover has to be **stationary** for a short moment — which matches the logic of the match, where the goal is to reach the area and **stay there**.

**Real-time feedback for the operator and the agent:**

- A large, clear **"ON TARGET"** indicator in the web interface when the measurement crosses the threshold
- The detail of the measurement (confidence %, number of sensors agreeing, coverage %) — for debugging
- It is exactly this feedback that tells the operator "I'll leave the rover here" or the agent "goal achieved"

**The role of the overview camera (more on it in section 4):** **the game master** reads the official score from the overview camera — they decide whether the 70% coverage rule is satisfied. The rover's own estimate is **operator feedback**, not the official score. Both measure the same thing from different viewpoints, and in a match they work in parallel: the operator sees quickly what is happening on screen; the game master keeps the official tally.

**Calibration before the match:**

1. Put the rover in the middle of the red area, watch for 5 seconds. The indicator must consistently show "ON TARGET", confidence score ≥ 0.7.
2. Put the rover on the edge of the area (part of the underside on it, part beside it) — the indicator must firmly show "not on target", confidence score clearly below 0.5.
3. Put the rover on the bare arena surface — it must firmly show "not on target".

**Typical problems:**

- **The rover is on the edge and the indicator flickers** → set a firm rule ("confidence ≥ 0.7 = ON TARGET") and visualise it for the operator.
- **The colour changes with the arena lighting** → calibrate under the same lighting the match takes place in.
- **The sensor sees through the rover's own shadow** → mount the sensor closer (5 mm above the surface).

**YouTube/AI search terms:**

- `TCS34725 esp32`
- `RGB color zone detection robot`
- `confidence score classifier`
- `sliding window filter sensor`

---
### 3. Levels of autonomy — from manual to an LLM agent

**Prerequisite:** the M3 click-and-drive logic on the rover's front camera stream works.

**Goal:** one operator controls **one** rover (controlling several at once from one interface would already be a new project). But they can choose how much they click themselves and how much they let the rover do. M4 introduces three levels, each building on the previous one.

#### Level 1 — Manual (the M3 baseline)

The operator watches the rover's front camera stream. They click in the image where they want the rover to go. The software does the M3 raycast: from the camera angle and FOV it computes the floor coordinate, and the robot turns and drives. The operator is fully responsible for the navigation — finds the red area by eye, clicks on it, watches that the rover gets there.

This level is **compulsory** by the end of M4 — when the higher levels fail, the manual level has to be clearly reliable. Manual is also the fallback in a fault situation: if the agent gets confused, you switch back to manual.

#### Level 2 — Autopilot (simple colour-based steering)

The operator presses a "Find red" button. The software analyses the front camera stream with image analysis methods:

1. Filters the image by colour channels (where in the image is there a reddish region)
2. Finds the centre of the largest such region in pixels
3. Clicks that pixel **itself** — the M3 raycast takes the rover there

The operator watches from the side. If the autopilot makes a mistake (it sees the red colour on a team marker, say, and thinks it is the area), the operator sees it immediately and can take back manual control.

The computation of this level **runs in the browser, i.e. on the mobile phone or the computer** — no LLM or external service is needed, and at the same time you can keep the controller as a simple ESP device rather than fitting much more expensive, more specialised hardware. If you use a phone as the main controller, run it there.

#### Level 3 — An existing agent drives the rover (Claude Code or similar)

**Do not build your own multimodal LLM loop from scratch.** Use an existing agent that is already well made anyway — Claude Code, Cursor, Aider or any similar CLI/IDE agent workflow. Your job is to build it a **clear and simple input-output interface** through which the agent can ask for information about the rover and send commands.

**The principle:** the agent is the worker, you build its workplace. The actual engineering work is designing that interface — the clearer the API, the better the agent works.

**What you build — a few simple tools the agent can call:**

| Tool | What it does | Response |
|:---|:---|:---|
| `rover_camera` | Saves the current front camera image as a file | The file path of the image (e.g. `/tmp/rover_now.jpg`) |
| `rover_status` | Returns the rover's current state | JSON: `{"on_target": false, "battery_pct": 72, "last_action": "drive 2s"}` |
| `rover_rotate <degrees>` | Rotates the rover in place (+ right, − left) | OK / ERR |
| `rover_drive <sec>` | Drives forward for the given time | OK / ERR |
| `rover_click <px> <py>` | Performs an M3 raycast click at an image coordinate | OK / ERR |
| `rover_stop` | Stops all motors immediately | OK |

A simple CLI tool: `rover camera`, `rover rotate -- -30`, `rover drive 2`. Or an MCP server that Claude Code loads directly — whichever feels better to you.

**What the operator does:**

The operator opens Claude Code (or Cursor, etc.) on their laptop and gives it a simple goal:

> "You are driving a rover. Goal: find the red area on the arena and stay on it. The tools you can use are: rover_camera, rover_status, rover_rotate, rover_drive, rover_click, rover_stop. Tell me when you are on target or when you cannot achieve the goal."

From there the agent takes the loop over itself: it takes a picture, thinks, calls a tool, looks at the result, adapts. You do not need to write the prompt loop — that is the agent's own business.

**The operator sees every step** in the same terminal where the agent is running — which image it was given, what the agent decided, which tool it called. That is the natural view for debugging and for safety. To take back manual control they simply close the agent's loop and open the normal web interface again.

**The pedagogical point:**

- The real work is **not building the agent** but designing a clean tool kit. Clearer tool names, better documentation, fewer surprises → better agent behaviour.
- You learn how agents actually work: they are not miracles but systems that need clear I/O.
- The same workflow carries over: whenever you need some system to be available to agents, you use the same pattern of thinking (tools, JSON responses, documented behaviour).

**What M4 assesses:**

- Is the API **clear and self-contained**? Test it: give somebody (a friend, a teacher) Claude Code and your documentation — can they get talking to the rover without your help?
- Is the agent's activity **transparent**? Every tool call and response is logged and viewable.
- Can the operator **stop the agent's activity at any moment** and take back manual control?

**Typical mistakes:**

- **The API is too complicated** — the agent does not understand the parameters. Simplify the names, add clear examples in the documentation.
- **The tools block** — the agent calls `rover_drive 5` and has to wait 5 sec before the next step. Decide whether you prefer synchronous (simpler but slow) or asynchronous (faster but more complex); document the choice.
- **The agent does not look at the situation in between** — if after `rover_drive` the agent does not call `rover_camera` again, it does not know where the rover is. Document the recommended workflow: start every decision with an image.
- **The agent's loop does not end** — always add to the goal "be sure to say when you are on target or when you cannot continue", otherwise the agent may keep trying forever.

**Switching levels:** the same as Level 2 — when the operator switches to manual, the rover stops safely and the agent ends its loop.

**Design freedom:** all three levels do not have to be perfectly finished. M4 assesses how each level **works and when it breaks**. Level 3 is novel and experimental — if the agent finds the red area 60% of the time and fails 40% of the time, that is a good topic for discussion, not a failure of the project. What matters more is what you know about that 40%.

**YouTube/AI search terms:**

- `Claude Code custom tools CLI`
- `MCP server tutorial python`
- `LLM tool use simple API design`
- `agentic loop screenshot feedback`

---

### 4. The game context — the overview camera and the match protocol *(outside the rover's scope)*

A real match also needs the game infrastructure: an **overhead camera** that gives the referee the official score and records the match, and a **match protocol server** (start, a 90 sec countdown, stop, the final score). These are built outside M4, together with the preparation of the game itself. M4's task is to make a rover that works reliably within that infrastructure.

**What you need to know in M4 in order to build the rover correctly:**

- **The game rules apply:** 90 seconds, the winning team is the one with more rovers on the red areas at the end (≥ 70% coverage).
- **The official score is read by the game master from the overview camera.** The rover's "ON TARGET" indicator is **operator UX feedback**, not the authority on the score (see section 2).
- **The information-bubble principle:** the rover and the operator work only with the information from the rover's own sensors. **The operator does not see the overhead view** — not in the control interface, not on an info panel, and not as a review after the match. If the operator could see from above, that would be cheating help that would break the pedagogical point of the project.
- **The start and the end of the match come as a signal from the referee.** The rover and the operator keep track of the state of the match (**ON** / **OFF**) and behave accordingly:
  - **Match ON** (the referee sent "start", the clock is running): all commands allowed — manual clicking, autopilot, agent
  - **Match OFF** (before the start, after the stop): **only preparation commands** — a manual single-step movement for positioning, colour sensor calibration, a camera test. The autonomous modes do not work outside a match.

  The filter has **two layers**: (1) the operator interface does not let game-mode commands be sent when the match has not started (buttons greyed out); (2) **the rover itself** checks the match state and **ignores** any non-matching commands that arrive outside the match — defence in depth, so that if one layer lets a fault through, the other stops it.

  **The rover must react to a stop command immediately — at any time**, regardless of the match state (a physical safety measure).
- **The rover must have a clear team marker on its top surface** (see section 1, the enclosure requirements) so that the overview camera can identify it. Avoid a red team colour — it gets confused with the detection of the red areas.

**Testing in M4 without the full infrastructure:**

- Simulate the 90-sec match with a simple timer (a phone, a stopwatch)
- Instead of the red area you can use a printed A4 sheet or coloured tape on the floor
- Two rover-operator pairs "facing off" on the spot — one team member reads the clock, another checks visually where the rovers ended up
- These are not real matches, but they give enough context for the M4 tests

The real match with the overview camera and the server-side scoring comes later; your job in M4 is to make a rover that works reliably both in practice conditions and in real matches once the infrastructure is ready.

---

### Operator feedback accuracy (Analysis 1)

**Prerequisite:** section 2 (the rover gives the operator "ON TARGET" feedback — option A, B or C) works.

**Goal:** measure whether the rover's "ON TARGET" indicator matches reality — where the rover physically is relative to the red area. Reliable feedback matters to the operator; if the indicator flickers wrongly, they lose trust and the match becomes inefficient.

**Reference:** you deliberately place the rover in specific positions yourself (in the middle, on the edge, on the bare arena) and compare whether the indicator matches what you expect. The game master's infrastructure is not needed — you know where you put the rover. When the game master's system is ready later, the same test can be repeated with their reference and the results compared.

**Measurement — three test positions:**

1. **In the middle of the red area** — it must clearly declare "ON TARGET" (option A: confidence ≥ 0.7; option B: ≥ 70% of the sensors; option C: ≥ 70% of the image area)
2. **On the edge of the red area** — the rover half on it, half beside it, it must clearly declare "not on target" (the measurement below the threshold)
3. **On the bare arena surface** — it must declare "not on target"

At each position take readings for 30 seconds (≈ 600 readings at 50 ms intervals).

**Save as CSV** according to the option you chose:

- **Option A:** timestamp, sensor reading, confidence score, "declares ON TARGET yes/no"
- **Option B:** timestamp, each sensor's reading, "X/N agreed", "declares ON TARGET yes/no"
- **Option C:** timestamp, image area %, "declares ON TARGET yes/no"

**Jupyter Lab analysis:**

| Test | Declares "ON TARGET" % | Median metric | Notes |
|:---|:---|:---|:---|
| Middle of the area | 100% (expected) | 0.92 / 4 sensors out of 4 / 88% of the area | Strong signal |
| Edge of the area | 5% (expected 0) | 0.65 / 2 sensors out of 4 / 55% | Sometimes declares wrongly |
| Bare arena | 0% (expected 0) | — | Fine |

**Assessment:**

- **The declaration % from the middle** must be close to 100% — if it is below 90%, there is a weakness in the sensor or in the measurement
- **The declaration % from the edge** must be close to 0% — if it is over 10%, the rover's indicator misleads the operator (it shows "ON TARGET" even though the rover is actually on the edge and in a real match no point would be awarded)
- **The declaration % on the bare arena** must be exactly 0% — if it is over 0, something is badly wrong

**Comparison of the options** (if you got to try more than one): put the options side by side in a table on the same tests. Where does one option work better than another? Option B (several sensors) should be better at the edges than option A (one sensor). Option C (camera) should be better with irregularly shaped areas.

---

### Comparison of the levels of autonomy (Analysis 2)

**Prerequisite:** all three levels of autonomy (step 3) are at least basically reliable.

**Goal:** measure how well each level works — not just whether it works at all. This gives you **the most important part of the project's learning outcome**: the student understands where each approach fits and where it does not.

**Measurement — the same task, three levels:**

The task: "Drive onto the red area and stay there." The starting point is fixed (for example at the rover's wall), the target is one specific red area on the arena. The distance is identical for all the levels.

Each level performs the task **5 times** in a row. Measure:

| Metric | How to measure |
|:---|:---|
| Success (yes/no) | Is the rover on the area at the end and does it stay there? |
| Time (s) | How long it took from the start to the target |
| Number of operator clicks | How many interactions the operator had to make |
| Wrong moves | How many times the rover drove to the wrong place before reaching the target — see the examples below |

**What counts as a "wrong move":**

- **Level 1 (manual):** the operator clicked the wrong point and had to click again to correct the rover's course
- **Level 2 (autopilot):** the software found the wrong red region (e.g. a team marker, a reflection caused by the lighting, the colour of a sheet at the edge of the arena) and sent the rover there
- **Level 3 (agent):** Claude Code picked the wrong target in the image or made a decision that left the rover in the wrong place

You count every such error that you have to correct afterwards: the rover went off course, you switch the level or click again to bring it back on course. A successful run = 0 wrong moves; a typical run has 1–3.

**Save as CSV** with the columns: level, attempt number, success, time, operator clicks, wrong moves.

**Jupyter Lab analysis:**

- **Success %** by level
- **Median time** by level
- **The operator's cognitive load** = number of clicks × time

**Table in the report:**

| Level | Success 5/5 | Median time (s) | Average clicks | Notes |
|:---|:---|:---|:---|:---|
| 1: Manual | ... | ... | ... | |
| 2: Autopilot | ... | ... | ... | |
| 3: LLM agent | ... | ... | ... | |

**Assessment and discussion:**

- **Where is each level at its best?** Manual is usually fast when the operator is good and the target is visible. Autopilot wins when the target is clearly recognisable but the operator does not want to click themselves. The LLM agent may be slower, but it works when the target is harder to find or when the task is bigger ("check the whole arena and find all the red areas").
- **Where does each level fail?** Manual fails when the operator gets tired or the target is tiny in the camera view. Autopilot fails when the lighting has changed or there are other red objects in the image. The LLM agent fails when the image is confusing, when the agent errs in its own description, or when the API is slow.

After the table, write **a free-form paragraph**: which level would you prefer after these tests? That paragraph brings together one of the main learning outcomes of M4.

---

### System reliability over 10 matches (Analysis 3)

**Prerequisite:** all the M4 functions work.

**Goal:** drive **10 consecutive 90-second matches** in real match conditions and log every system fault from the software. This is **diagnostics**, not a pass/fail requirement: you want to know where the system gets weak over time, so you can fix those places before the tournament.

**Types of event to log:**

| Event | What it means | How to detect it |
|:---|:---|:---|
| `wifi_disconnect` | The operator or the rover lost the connection | WebSocket close event |
| `lost_command` | A command was sent, the rover did not respond | Command + 100 ms timeout without an ACK |
| `sensor_unstable` | The colour sensor's confidence < 0.5 for over 1 sec | The stability filter does not converge |
| `motor_stall` | The motor tries to turn but does not move | Current draw high, the distance does not change |
| `agent_error` | Claude Code / the agent returned an error or a tool failed | An error parsing the API response, an exit code |
| `false_on_target` | The rover declared "ON TARGET", but you looked yourself — it was not | Manual log by the operator |
| `restart_required` | The operator had to restart it manually | Manual log |

**Table in the report:**

| Match # | Rover score (at the end) | WiFi | Lost commands | Sensor instability | Agent errors | False ON TARGET | Restart? |
|:---|:---|:---|:---|:---|:---|:---|:---|
| 1 | 4 | 0 | 0 | 0 | 0 | 0 | no |
| 2 | 3 | 0 | 1 | 0 | 0 | 0 | no |
| 3 | 5 | 0 | 0 | 2 | 1 | 0 | no |
| ... | ... | ... | ... | ... | ... | ... | ... |

**Jupyter Lab summary:**

- The number of faults per match (a line graph over time — do the faults grow over time?)
- The total for each type of event
- Where is the pattern: do the faults always occur at the same moment in the match, in the same type of situation?

**Assessment and action:** the counting does not end here — every fault is the input for the next step. If the WiFi drops regularly, investigate whether the problem is the arena (other devices on the same channel), the power supply or the software. If memory leaks (the faults grow over time), profile the server. If commands are lost repeatedly at the same moment — look at the log, look for the pattern. **The goal is not to reach zero** but to know where your system gets weak and whether those places can be fixed, in order of importance, before the arena event.

---

### Assessment criteria

| Category | Points | What is assessed |
|:---|:---|:---|
| Work files | 4 p | Code in the repo, STLs **+ CAD source files** (Fusion `.f3z`/`.f3d` or CadQuery `.py`), photos and videos of the enclosure and the matches |
| Analysis | 4 p | 3 Jupyter notebooks (operator feedback accuracy, comparison of the levels of autonomy, reliability over 10 matches) |
| Prototype | 4 p | PLA enclosure with bolted fastenings, at least two levels of autonomy working, a 90-sec match finishes cleanly |
| Documentation | 4 p | Specification update + a draft of the user guide |
| Q&A | 4 p | Demo at the meeting + discussion of the levels of autonomy |
| **Total** | **20 p** | |

---

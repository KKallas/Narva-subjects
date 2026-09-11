# Arena and robot standard format

This document brings together the whole project's **agreed standard format** — the physical description of the arena, the navigation aids, the game rules and the constraints on the robot. Every team builds its rover according to this specification.

---

## 1. Physical description of the arena

| Parameter | Value |
|:---|:---|
| Overall arena dimensions | 3000 × 3000 mm (3 × 3 m) |
| Module size | 1000 × 1000 mm (1 × 1 m), 9 modules in total (in a 3 × 3 layout) |
| Hole pitch in the grid | 100 mm (a 10 × 10 grid per module) |
| Hole diameter | 5 mm |
| Hole depth | 5 mm |
| Surface material | OSB (wood) |
| Wall height | 100 mm |
| Wall fastening | The outer holes of the arena |

**Opposite walls:** two opposite walls are marked by agreement in **red** and **blue**. These are global references — which team starts at which wall is decided at the start of each match.

**The surface:** the holes in the modules (a 10 × 10 cm grid, 5 mm in diameter) take 3D-printed studs. The studs carry coloured dots and other aids (see section 2).

---

## 2. Standard equipment — navigation aids

The arena has **three levels of navigation aid**, available to every team. Each team chooses which ones to use.

**These are architecturally prepared aids, not the only permitted methods.** A team may also use other localisation solutions — UWB, a magnetic compass + dead reckoning, optical flow, a home-built solution, etc.

### Level 1 — ArUco markers on the ceiling *(square accuracy, the recommended baseline)*

**9 markers** from the `DICT_4X4_50` dictionary, each **20 × 20 cm**, mounted at the **centre** of every 1×1 m OSB module on the ceiling at about **2 m height**.

The standard layout with chess-style notation (viewed from above):

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

The ArUco IDs:

| Square | ArUco ID | Square | ArUco ID | Square | ArUco ID |
|:---|:---|:---|:---|:---|:---|
| A1 | 0 | B1 | 1 | C1 | 2 |
| A2 | 3 | B2 | 4 | C2 | 5 |
| A3 | 6 | B3 | 7 | C3 | 8 |

**The "top" edge of the markers faces the blue side** — all 9 markers on the ceiling are oriented the same way. That gives the rover a global heading reference.

**The size of 20×20 cm — how it was derived:** the minimum decodable ArUco size of 30 px per edge + a height of 2 m + a 60° FOV camera (640 px) → a minimum of 11 cm, doubled to 20 cm for reliable reading (fits on an A4 sheet).

### Level 2 — Colour dots on the floor grid *(more accurate, uses the colour sensor)*

3D-printed coloured studs (≤ 2 mm high, they do not obstruct the rover's driving):

| Location | Colour | How many in total | Meaning |
|:---|:---|:---|:---|
| The **centre** of every module | **Blue** | 9 | Reference for the module's centre |
| The **4 corners** of every module | **Yellow** | 9 × 4 = 36 | Reference for a module corner (a cluster forms at shared corners) |
| The centre of the arena (the centre of B2) | **Green** | 1 | The global origin (0, 0) |

**The logic of the colour palette:**

| Colour | Meaning | RGB sensor |
|:---|:---|:---|
| Blue | Module centre | High B channel |
| Yellow | Module corner | High R + G |
| Green | Origin (the centre of B2) | High G |
| Red | A marked game area (see section 3) | High R |

**The red areas and the colour dots:** if a red area is placed over a colour dot, **a hole is cut in it at that spot**. The colour dots always stay visible.

### Level 3 — Magnets in the floor grid *(very accurate, optional)*

**NdFeB magnets** (discs 5 mm in diameter × 2 mm thick, they go 5 mm deep into a hole).

The standard layout (the same as the colour dots — the same holes):

- The **centre** of every module — 9 magnets
- The **4 corners** of every module — 9 × 4 = 36 magnets

**The advantage:** the magnets are inside the floor, and a Hall sensor reads them through the red areas as well — there is no need to cut a hole in a red area for a magnet.

---

## 3. Game rules

| Parameter | Value |
|:---|:---|
| Match duration | 90 seconds |
| Number of teams | 2 (the red and the blue side) |
| Number of rovers per team | Decided within the team (one rover = one operator) |
| Starting position | Each team's rovers at their own wall |
| Goal | To have more rovers on the red marked areas at the end than the opponent |
| Scoring threshold | A rover counts as being on an area if ≥ 70% of its underside is on it |
| Source of the official score | The game master, from the overview camera |

**The play areas:**

- **Red marked areas** (of paper, film or a similar material) are placed on the arena at the start of each match
- The areas must not obstruct the rover's driving (they have to be flat on the surface)
- If an area would cover a navigation colour dot, **a hole is cut there** (the dots stay visible)
- The areas may have different shapes and layouts — this is specified at the start of each match

**The course of a match:**

1. **Starting position (before the start):** the rovers are lined up at their own wall in manual mode, the referee confirms the starting position, the score is 0/0
2. **Start:** the referee gives the signal, the clock starts (a 90 sec countdown)
3. **During the game:** the operators move their rovers; the game master reads the score from the overview camera
4. **The end (0:00):** the server locks the score, sends a "stop" command to all the rovers, and displays the result

**Authority over the score:**

- **The official score** = the game master's count from the overview camera (the 70% coverage rule)
- **The rover's own "ON TARGET" indicator** = operator UX feedback only, not the official score
- If they disagree → a calibration problem or a disputed borderline situation (the referee decides from the video)

---

## 4. Constraints and requirements for the robot

### Mechanics

| Parameter | Requirement |
|:---|:---|
| Maximum weight | ~1 kg (recommended) |
| Ground clearance | ≥ 5 mm (the arena studs are up to 2 mm high) |
| Height | No limit, but the marker on the top surface has to be visible to the overview camera |
| Enclosure material | Free choice (PLA, PETG, plywood, cardboard — the team's choice) |
| Mechanical durability | Must survive at least 5 consecutive wall collisions according to the M4 tests |

### Power

- A **battery** on the rover (LiPo, a USB power bank, the phone's internal battery, etc.)
- **Battery swap time** between matches: ≤ 30 sec by a beginner operator
- A power switch or a clear way of switching it on

### Sensors (recommended, not all compulsory)

| Sensor | Purpose | Compulsory? |
|:---|:---|:---|
| Front camera | Navigation with the click-and-drive logic | Yes |
| Colour sensor (underneath) | "ON TARGET" feedback (M4 section 2) | Yes |
| Overview camera (facing up) | Reading the ArUco markers on the ceiling (M5) | Recommended |
| Hall sensor (underneath) | Reading the magnets in the floor grid | Optional |
| Distance sensor | Avoiding collisions | Optional |

### Interface and communication

- A **WiFi** connection between the operator's laptop and the rover
- A **rover server** with a web interface (Python + FastAPI, an ESP32 web server, etc.)
- The **operator interface** must show at least:
  - The real-time stream from the front camera
  - The ability to click-and-drive on the image
  - The state of the rover's own sensor (the "ON TARGET" indicator)
  - A battery state indicator
- **The rover must react to a stop command immediately — at any time** (a safety measure)

### Visual identification for the overview camera

- **A team marker on the top surface** — clear contrast, easily visible to the overview camera
- **Avoid a red team colour** — it gets confused with the marked areas
- Team colours: blue vs. yellow recommended (high contrast)
- The marker must be visible even when the rover is upside down (so that the referee can identify it)

---

## 5. Rules for the operator and the information bubble

**The information-bubble principle:** during a match the rover and the operator work **only with the information from the rover's own sensors**. This is a deliberate boundary — if the operator could see the overview camera, that would be cheating help.

**The operator sees:**

- The real-time stream from their own rover's front camera
- The state of their own rover's sensor (the "ON TARGET" indicator)
- The team's combined score (a number)

**The operator does NOT see:**

- The overview camera's view — not as an image, not as a map, not on the score panel
- Which rover is scoring (only the combined score)
- The opponent rover's front camera view

**The game master sees (from a separate interface):**

- The real-time stream from the overview camera
- The official score (the count of rover ↔ area overlaps)
- The state of both teams
- If needed: a comparison of the official score with the rover's own declaration

---

## 6. The match-state rule (match ON / OFF)

The rover and the operator keep track of the state of the match. Depending on the state, different commands are allowed:

| State | Allowed commands |
|:---|:---|
| **Match ON** (the referee gave the "start", the clock is running) | All commands — manual clicking, autopilot, agent |
| **Match OFF** (before the start, after the stop) | **Only preparation commands** — a manual single-step movement, colour sensor calibration, a camera test. The autonomous modes do not work. |

**Two safety layers (defence in depth):**

1. **The operator interface** does not let game-mode commands be sent before the start (buttons greyed out)
2. **The rover itself** checks the match state and **ignores** non-matching commands that arrive outside a match — so that if one layer lets a fault through, the other stops it

**The rover must react to a stop command immediately — at any time**, regardless of the match state (a physical safety measure).

---

## 7. Levels of autonomy (the agreement in the operator interface)

In their control interface the operator selects one of three levels of autonomy:

| Level | What works | Who decides |
|:---|:---|:---|
| **1 — Manual** | The operator clicks in the image, the M3 raycast takes the rover there | The operator |
| **2 — Autopilot** | The operator presses "Find red", the software filters the image by colour and clicks itself | The software, with the operator watching |
| **3 — Agent** | The operator gives a high-level goal and Claude Code (or similar) uses the rover's tool kit (rover_camera, rover_status, rover_rotate, rover_drive, rover_click, rover_stop) | The agent, with the operator intervening when needed |

Switching levels is immediate and safe — switching to manual in the middle of the agent's activity stops the rover safely.

---

## 8. Summary — what every team builds

- A rover that drives from a click in its own front camera stream (the M3 baseline)
- An enclosure that survives at least 5 collisions (M4 durability)
- A colour sensor and an "ON TARGET" indicator (M4 section 2)
- At least 2 of the 3 levels of autonomy (M4 section 3)
- An upward-facing camera for reading ArUco (M5 standard equipment, level 1)
- A clear team marker on the top surface
- A WiFi connection, an operator interface, an immediate stop command
- The match-state rule built in (ON/OFF, defence in depth)

Optional in addition:
- A downward-facing camera (M4 section 2, option C)
- A Hall sensor for reading the magnets (M5 standard equipment, level 3)
- A distance sensor for avoiding collisions

# Cyber Defense — Game Design (v4)

A two-team cooperative-competitive tower defense game operated by Dobot MG400 robotic arms. Players cooperate to defend a digital asset from waves of cyber-threats, while competing for individual contribution credit. The match either ends in mutual defeat or in a scored survival win.

---

## 1. Theme

Two teams defend a shared digital asset from a wave of incoming cyber-threats. They wield five physical defensive tools (neutralize, honeypot, sandbox, DDoS, software upgrade) and must cooperate to survive while competing for the highest individual contribution.

The narrative framing keeps the game free of violent imagery and lands it in a real-world domain (cybersecurity) that 14–16 year olds find current and credible.

---

## 2. Physical layout (top-down)

```
                    [ TOOLBOX — 5 tools ]
                            │
                    ┌───────────────┐
                    │               │
   ┌─────┐          │               │          ┌───────┐
   │ RED │          │    SCREEN     │          │ GREEN │
   │ bot │ ────────►│               │◄──────── │  bot  │
   └─────┘          │               │          └───────┘
                    └───────────────┘
```

| Element | Position |
|:---|:---|
| **Screen** | Dead center. 30" landscape monitor displaying the game. Not a touchscreen. |
| **Robot Red** | Left side, vertically aligned to screen center |
| **Robot Green** | Right side, vertically aligned to screen center |
| **Toolbox** | Above the screen, horizontally aligned to screen center. Holds 5 M5 Atom tools. |

A **4K camera** is mounted above the entire setup. ArUco markers on:
- Robot tool tips (position tracking)
- Each M5 Atom tool (identity, ownership color, position)
- Screen corners (calibration reference)

The camera detects "tool placed at screen coordinates (x, y)" by tracking each ArUco marker. No physical touchscreen needed — the system is a virtual touchscreen mediated by computer vision.

---

## 3. Hardware

**Per setup (one game station):**
- 2× Dobot MG400 robotic arms (left, right) with soft silicone tool tips
- 1× 30" landscape monitor (game display)
- 5× M5 Atom devices (the five physical tools)
- 1× 4K overhead camera
- 1× toolbox/tray above the screen for resting M5 Atoms
- 3× desktop computers: one per player operator + one for game master

**Per M5 Atom tool:**
- Small front screen showing tool icon
- ArUco marker on top for camera tracking
- Perimeter LED ring acting as countdown timer when active
- Communicates wirelessly (WiFi) with game backend

---

## 4. Calibration (before each match)

The game master runs a quick calibration from their computer:

1. Camera takes a frame of the empty screen
2. Game master clicks the four corners of the screen in the camera image
3. System now knows the homography between camera pixel space and screen pixel space
4. Game master places each M5 Atom into the toolbox and labels it (e.g., "slot 1 = Neutralize")
5. System reads each tool's ArUco ID and records starting position

Calibration takes about 30 seconds. Re-run if the camera or screen shifts.

---

## 5. The five tools

The tools are fixed for the match. **You start with 5, you end with 5.** No respawn. Tools cycle in and out of play via the pickup mechanics.

| Tool | Effect | Type | Range |
|:---|:---|:---|:---|
| **Neutralize** | Removes the single nearest threat instantly | One-shot | Single target near drop point |
| **Honeypot** | 50/50 — either clears all threats in range OR they respawn as 2× more, smaller and faster | Risky AOE | Medium radius |
| **Sandbox** | Freezes all threats in range for 20 seconds | Duration AOE | Medium radius |
| **DDoS** | Pulls threats in range toward the tool and holds them there. Effect ends when any team picks up the tool. | Sustained AOE | Large radius |
| **Software Upgrade** | Shortens the vector length of all currently-spawned threats on the screen by 30% | Global one-shot | Whole screen |

Each tool's M5 Atom screen shows a distinct icon so operators (and yelling teammates) can identify it from across the table.

---

## 6. Tool states and the pickup mechanic

A tool exists in one of three states:

- **Neutral** — sitting in the toolbox, no team color, ArUco shows white
- **Active** — placed on the screen by a team, perimeter LED counting down its 5-second timer, ArUco shows team color
- **Spent** — timer fired, effect resolved, sitting on the screen waiting to be cleared, ArUco still shows team color

When a robot picks up a tool, what happens depends on the tool's state and which team picked it:

| Who picks it up | State | Result |
|:---|:---|:---|
| Same team | Active | **Recall** — timer cancels, tool returns to inventory (resets to neutral color), reusable |
| Same team | Spent | Nothing — your own dead tool stays dead. You wasted a robot move. |
| Other team | Active | **Steal** — tool keeps counting down but ArUco flips to other team's color. When it fires, the new team gets credit. |
| Other team | Spent | **Reset to neutral** — tool re-enters the toolbox as neutral, available to either team for next placement |

Net effect: you have five tools total, and they cycle through neutral → active → spent → neutral via pickup interactions. The cleanup mechanic (other team picking up your spent tools) is the only way to keep the toolbox stocked.

---

## 7. Threats

Threats spawn at the bottom of the screen and migrate upward toward the asset at the top.

Each threat has three properties that vary per instance:
- **Speed** — how fast it moves (slow tanks vs fast scouts)
- **Vector length** — its strength, visualized as a constant-length glowing tail trailing behind it (constant per-threat, not growing)
- **Direction** — not always straight up; some come diagonally, some swerve

When a threat reaches the asset, it deals damage equal to its vector length.

**Single threat type**, but with these three variable parameters, individual threats feel different. Short-tail fast threats are nuisances. Long-tail slow threats are critical to intercept. Diagonal threats can sneak past poorly-placed tools.

---

## 8. Spawn pacing

**Wave-based and adaptive.** The spawn algorithm:

- Match starts with a calm first wave (few short threats)
- Waves escalate over time: more threats per wave, longer vector lengths, faster speeds
- Adaptive: if the team is dominating (asset HP healthy, threats handled), pacing accelerates
- Adaptive: if the team is struggling (asset HP low, threats backing up), pacing eases slightly to give a chance to recover
- Tuned so an average team's defense holds ~60–90 seconds before the asset is overwhelmed

The 90-second match length is the **survival target**. The game is designed to make winning difficult but possible with good team coordination.

---

## 9. The asset and defeat

A single asset is displayed at the top of the screen with a visible HP bar.

- Each threat that reaches the asset deducts HP equal to its vector length
- When HP reaches zero, the game ends immediately in **defeat** — both teams lose
- If the asset HP is still above zero at 90 seconds, defenders win

---

## 10. Scoring

**If attackers win** (asset destroyed before 90 sec):
- Both teams lose, no points awarded
- The threats took the asset down — defending didn't matter

**If defenders win** (asset survives the full 90 sec):
- For each threat wiped from the screen by a tool, the threat's vector length is credited to the team color of the tool that wiped it
- Team with **highest total wiped vector length** → **3 points**
- Other defending team → **1 point**

Credit rules per tool:
- **Neutralize / Honeypot / DDoS / Sandbox** — credit goes to team color of tool that wiped the threat
- **Software Upgrade** — does not directly wipe threats, so no direct score credit. But it shortens future incoming vectors, helping the team survive longer, keeping the win possible.

The selfless move (Software Upgrade) is real strategic depth: someone has to play it for collective survival, even though it gives them zero score.

---

## 11. Tournament structure

The camp closes with a tournament. With 4 teams of 4 students (16 total), 2 simultaneous game tables:

- **Round 1**: Red vs Green on Table 1, Blue vs Yellow on Table 2
- **Round 2**: Red vs Blue on Table 1, Green vs Yellow on Table 2
- **Round 3**: Red vs Yellow on Table 1, Green vs Blue on Table 2

Three rounds total. Every team plays every other team once.

Maximum points per team: 9 (winning all three matches with most-wiped credit). Minimum: 0 (asset destroyed in every match).

Tiebreakers:
1. Most matches won outright
2. Most total survival seconds across all matches

---

## 12. Visual style

Geometry Dash aesthetic: clean geometric shapes on a dark background, neon glows, particle bursts on neutralization, screen shake on critical asset hits, BPM-synced color pulses on wave changes.

- **Asset** — stylized data block at the top of the screen, HP bar
- **Threats** — angular silhouettes with constant-length glowing tails (color tied to threat parameters)
- **Tools** — clean geometric icons on M5 Atom screens; on the game screen, dropped tools show a colored circle in their range with team-color glow
- **Effects** — geometric particle bursts on neutralize, ice crystals on sandbox, blue spiral on DDoS, white pulse on software upgrade

High contrast, readable from across the room, photogenic.

---

## 13. Three control modes

The game supports three robot control modes, taught progressively across the camp:

| Mode | What the operator sees | What they do | Robotics principle taught |
|:---|:---|:---|:---|
| **Blind joint-based** | 6 joint sliders + numeric readouts; **no workspace view** | Move sliders to position the tool tip, then trigger gripper | Forward kinematics intuition (joint angles → spatial position) |
| **Image-based** | Camera view of workspace; tool tray and screen visible | Click a tool in the tray → robot picks it up. Click on the screen → robot places it there. | Inverse kinematics + LUT (spatial click → joint angles) |
| **Agent (Claude Code)** | VS Code with Claude Code, structured game state available as `get_game_state()` | Tell agent the high-level goal in natural language; agent picks tools, places them, reacts | Sense-think-act loop; right model for right job (YOLO classifies threats, LLM strategizes) |

Each level abstracts away the previous level's hard part: spatial reasoning, then coordinate calculation, then strategic decision-making.

---

## 14. Implementation notes

**Game backend:** Python (FastAPI + WebSockets) — same stack used in earlier camp sessions, so familiar to students.

**Game frontend:** HTML5 + Canvas (or WebGL for fancier effects). Geometry Dash aesthetic is straightforward in Canvas.

**Robot control:** Python `pydobot` library or direct TCP/IP to Dobot.

**Camera + ArUco:** Python `cv2.aruco` module, 4K USB webcam.

**M5 Atom firmware:** UIFlow or Arduino IDE, custom sketch to:
- Display tool icon on small screen
- Control perimeter LED ring as countdown timer
- Update ArUco marker color (via a small color overlay or LED indicator near marker)
- Communicate state with backend via WiFi/MQTT

**Game master interface:** Web page showing calibration tools, match timer, score, asset HP, threat counts.

**Operator interface:** Web page rendering the three control modes, one at a time, selected via mode switch. Tournament rounds force the mode (e.g., final round = agent only).

---

## 15. Why this game works for the camp

- **Theme is current** — cybersecurity is what the audience cares about; no violence
- **Cooperation forced** — both teams must survive together for anyone to score
- **Competition real** — within cooperation, individual color credit creates rivalry
- **Robot speed is balanced** — 5-sec timer makes robot speed a meaningful cost, not a handicap
- **Selfless plays exist** — Software Upgrade teaches that sometimes the right move scores zero
- **Tournament closes naturally** — round-robin with cumulative points, fair and dramatic
- **Three control modes map perfectly** — escalating abstraction matches the camp's pedagogy
- **Spectator-friendly** — Geometry Dash aesthetic is photogenic, screen shows the whole story
- **Always ends decisively** — either both lose or one team gets bigger points; no anticlimax

---

*End of game design document.*

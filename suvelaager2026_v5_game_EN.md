# Cyber Tag Arms — Game Design (v5)

A two-player head-to-head robot-arm game about timing, stealing, and territory control — themed as a cybersecurity defense scenario. Each side controls a robotic arm and races to neutralize incoming threats while sabotaging the opponent's attempts. Matches last 90 seconds. Highest score wins.

This version simplifies v4: no shared asset, no cooperation, no five-tool typing. Four generic M5 tags per player. Snatch and denial are the only strategic verbs.

---

## 1. Theme

The screen between two robot arms displays a cyber-defense console. Threats appear at various points across the console as glowing angular shapes with vector tails — short tails for weak threats, long glowing tails for high-value targets. Each player races to **neutralize** as many threats as possible by physically placing a defensive tag (an M5 Atom) on the threat. Whoever banks the most neutralized vector-length wins.

There is no shared asset to defend. Missed threats simply expire and leave no penalty. The competition is purely about who racks up the higher defensive score — and who is willing to sabotage the other to get there.

---

## 2. Physical layout (top-down)

```
   ┌─────────┐                                          ┌─────────┐
   │ RED BIN │                                          │GRN BIN  │
   │ ▣ ▣     │  ┌──────────────────────────────┐        │     ▣ ▣ │
   │ ▣ ▣     │  │                              │        │ ▣ ▣     │
   └─────────┘  │            SCREEN            │        └─────────┘
                │                              │
   ┌─────┐      │     (threats + placed tags)  │           ┌───────┐
   │ RED │      │                              │           │ GREEN │
   │ bot │ ────►│                              │◄────────  │  bot  │
   └─────┘      └──────────────────────────────┘           └───────┘
```

| Element | Position |
|:---|:---|
| **Screen** | Dead center. 30" landscape monitor displaying the game. Not a touchscreen. |
| **Robot Red** | Left of the screen, vertically aligned to screen center |
| **Robot Green** | Right of the screen, vertically aligned to screen center |
| **Red bin** | Top-left corner area, 4 tag slots |
| **Green bin** | Top-right corner area, 4 tag slots |

**Both arms can reach both bins.** This is critical — denial (stealing tags from the opponent's bin) requires the cross-table reach. A robot stealing from the opponent's bin takes meaningful time, which is itself a strategic cost.

A **4K camera** mounted overhead tracks ArUco markers on:
- Robot tool tips (position tracking)
- Each M5 Atom tag (identity, position, team color)
- Screen corners (calibration reference)
- Bin corners (calibration reference)

The camera detects "tag placed on threat at (x, y)" by tracking each ArUco marker against the live game state on the screen.

---

## 3. Hardware

**Per setup (one game station):**
- 2× Dobot MG400 robotic arms (left, right) with soft silicone tool tips
- 1× 30" landscape monitor (game display)
- 8× M5 Atom devices (4 per player as tags) — all visually identical, distinguished only by ArUco color
- 1× 4K overhead camera
- 2× bins (small trays) for tag storage, one near each robot
- 3× desktop computers: one per player operator + one for game master

**Per M5 Atom tag:**
- Small front screen showing a simple icon (a single shield or lock icon — all tags are visually identical)
- ArUco marker on top for camera tracking
- Perimeter LED ring acting as countdown timer when active
- Communicates wirelessly (WiFi) with game backend

Tags are **identical** — there is no "Neutralize" vs "Sandbox" vs "DDoS" differentiation in v5. Every tag does the same thing: neutralize a threat. Strategic depth comes from positioning, timing, and stealing — not from picking the right tool.

---

## 4. Calibration (before each match)

The game master runs a quick calibration from their computer:

1. Camera takes a frame of the empty setup
2. Game master clicks the four corners of the screen, then four corners of each bin
3. System now knows where each region is in camera pixel space
4. Game master places 4 M5 Atoms in the Red bin, 4 in the Green bin
5. System reads each tag's ArUco ID and assigns ownership color (red ArUcos for Red bin's starting tags, green for Green bin's)

Calibration takes about 30 seconds.

---

## 5. The four M5 tags per player

Each player starts with **4 M5 Atom tags** in their bin. All tags are generic — they all do the same thing: neutralize one threat.

A tag exists in one of these states:

| State | Where | Visual |
|:---|:---|:---|
| **In own bin** | Player's starting area | Static, team-color ArUco |
| **Carried** | On the robot gripper | Moves with robot |
| **Placed on threat** | On the screen, on top of a threat | Glowing team-color ring around it, depleting timer ring |
| **Spent / dead** | On the screen after scoring | Greyed out, X marker; blocks reuse of that screen area |
| **In opponent's bin** | Was stolen via denial mechanic | Static, team-color ArUco of *original* owner |

The 8 tags (4 per player) are physically fixed — no respawn. They cycle through states based on what each player chooses to do with them.

---

## 6. Threats

Threats spawn at **random positions on the screen** at variable rates. Each threat has:

- **Vector length** (= value, 5 to 30) — drawn as a glowing tail behind the threat
- **Active duration** (= how long it stays available, 6 to 14 seconds)
- **Position** (fixed for the threat's lifetime — they do not move across the screen)

**Higher vector length = shorter active duration.** High-value threats are short-lived and contested. Low-value threats stick around longer and are safer to engage.

| Vector length range | Approx active duration | Risk profile |
|:---|:---|:---|
| 5–10 | 12–14 sec | Safe — plenty of time to place a tag, low theft incentive |
| 11–20 | 8–10 sec | Standard — competitive window, snatching becomes real |
| 21–30 | 6–7 sec | Contested — high-value, short-window, both arms will fight over it |

If a threat's active duration runs out without a tag being placed on it, it **expires unscored** — disappears with a faint pulse. No damage, no penalty. Just a lost opportunity.

Threats spawn at an adaptive rate, tuned so 5–9 threats are alive on screen at any given time across the 90-sec match.

---

## 7. The core loop: place → countdown → steal → score

This is the only loop in v5. Everything else is variations on it.

**Step 1 — Place.** A robot picks up a tag from a bin (their own or the opponent's stolen tag from their bin), carries it to a live threat, and drops it on top. The tag's ArUco color matches the placing team.

**Step 2 — Countdown starts.** The threat's vector tail begins glowing more intensely. The tag's perimeter LED ring begins depleting in the placing team's color. **The countdown duration is 5 seconds.**

**Step 3 — Snatch window.** During those 5 seconds, the opponent's robot can fly in and **snatch the tag off the threat.**

- If they pick up the tag, the tag's ArUco color flips to their team color
- They must then **carry the tag back to their own bin** before the original countdown expires
- If they make it back in time → **opponent steals the score** (the threat's vector length is credited to them)
- If they don't make it back in time → **the countdown completes mid-transit**, the tag explodes harmlessly, the threat is *still neutralized* (it was placed on at some point), and **the original placer banks the score**

**Step 4 — Score banks.** When the countdown ends, whichever team currently has ArUco color on the tag scores the threat's vector length. The threat disappears with a particle burst. The tag is now **spent** and sits on the screen at its final position.

**Step 5 — Cleanup.** Spent tags block the screen area they sit on. To free that area, a robot must pick up the spent tag and carry it back to a bin (any bin — own or opponent's). The spent tag resets to **fresh** state when it lands in a bin.

If a spent tag lands in your **own** bin → it returns to your pool, fresh and ready to deploy again.
If a spent tag lands in your **opponent's** bin → it stays there as a denial token. Eventually they can use it (which gives the original owner some indirect benefit, since you used a slot for their tool), or it just sits there reducing inventory.

---

## 8. Denial: bin-to-bin theft

This is the second strategic verb in v5.

A robot can fly across the table to the **opponent's bin** and pick up one of their **unused** tags (tags still in the bin, not placed on a threat). The robot then carries the tag back and drops it in their own bin.

- The tag's ArUco color does **not** change — it still belongs to the original team
- But the original team can no longer access it from their bin
- The team that stole the tag now has the option to use it themselves
- If they use it: they place it on a threat. When countdown completes, the score goes to **the original owner** (because the tag's color is still their color)
- Or they can ignore it: just deny the opponent the tool

This means denial is a **time-cost tactic, not a score-grab tactic.** You spend ~3–4 seconds of your arm flying to and from the opponent's bin. In that time, you could have neutralized a threat. The question is whether reducing the opponent's tool pool is worth the lost score opportunity.

**Edge case** — what if a player runs out of tags entirely? They must steal from the opponent (either bin theft or mid-countdown snatch) to keep playing. This forces a switch from defensive to aggressive play late game.

---

## 9. Tag state machine

```
                ┌──────────────────────────────┐
                │                              │
                │           IN BIN             │
                │  (own or opponent's)         │
                │                              │
                └─────────┬────────────────────┘
                          │ robot grabs
                          ▼
                ┌──────────────────────────────┐
                │           CARRIED            │
                │   (on robot gripper)         │
                └─────────┬────────────────────┘
                          │ robot drops on threat
                          ▼
                ┌──────────────────────────────┐
                │       PLACED (countdown)     │
                │   LED ring depleting in      │
                │   placing team's color       │
                └─────────┬────────────────────┘
                          │ snatched by opponent
                          ▼ (color flips)
                ┌──────────────────────────────┐
                │      PLACED (still counting) │
                │   In transit toward          │
                │   opponent's bin             │
                └─────────┬────────────────────┘
                          │ countdown completes
                          ▼
                ┌──────────────────────────────┐
                │           SPENT              │
                │   X marker, blocks area      │
                └─────────┬────────────────────┘
                          │ any robot picks up
                          ▼
                ┌──────────────────────────────┐
                │      RETURNED TO BIN         │
                │   (fresh and reusable)       │
                └──────────────────────────────┘
```

---

## 10. Scoring (single match)

- Each threat neutralized → its vector length is added to the team whose ArUco color was on the tag at countdown end
- After 90 seconds, the team with the **higher total** wins
- Win = **3 points**
- Loss = **1 point** (consolation — they played a real game)
- Tie (exact same score, rare) = **2 points** each

There is no "mutual defeat" outcome in v5 — every match awards points to both teams.

---

## 11. Tournament structure (same as v4)

The camp closes with a round-robin tournament. 4 teams of 4 students (16 total), 2 simultaneous game tables:

- **Round 1**: Red vs Green on Table 1, Blue vs Yellow on Table 2
- **Round 2**: Red vs Blue on Table 1, Green vs Yellow on Table 2
- **Round 3**: Red vs Yellow on Table 1, Green vs Blue on Table 2

Each team plays 3 matches. Maximum tournament points: 9 (3 wins × 3 each). Minimum: 3 (3 losses × 1 each).

**Bonuses for the camp's pedagogical goals:**
- Used 4 different operators across the tournament: **+2**
- Each team member who never operated: **−1**
- Match played using Tier 1 (blind joint-based) interface: **+1 per match**

Tiebreakers:
1. Most matches won outright
2. Most total score across all matches

---

## 12. Visual style

Same Geometry Dash aesthetic as v4: dark navy background with subtle pulsing grid, neon glows, particle bursts on neutralization, screen shake on critical moments.

- **Threats** — angular silhouettes (triangles, hexagons) with constant-length glowing tails (color varies by vector length: short = magenta, long = deep red)
- **Tags placed** — colored circles with the team-color depleting timer ring
- **Spent tags** — greyed-out circles with X marker, dim glow
- **Bins** — outlined rectangles at top corners, with tag slots visible
- **Robot tool tips** — colored rectangles (red or green) with crosshair, thin dashed line back to robot base
- **HUD** — Red score (top-left), countdown timer (top-center), Green score (top-right)
- **Live event banner** — appears above the screen for key events: "SNATCH!", "STOLEN!", "DENIAL!", "TAG RECYCLED"

---

## 13. Three control modes (same as v4)

The same pedagogical scaffolding as v4 carries over:

| Mode | What the operator sees | What they do | Robotics principle taught |
|:---|:---|:---|:---|
| **Blind joint-based** | 6 joint sliders + numeric readouts; **no workspace view** | Move sliders to position the gripper, then trigger gripper | Forward kinematics intuition |
| **Image-based (WASD)** | Camera view of workspace; both bins and screen visible | WASD or arrow keys to move arm; F or Enter to grab/drop | Inverse kinematics + LUT |
| **Agent (Claude Code)** | VS Code with Claude Code, structured game state | Tell agent the high-level goal in natural language; agent decides which threat to engage, when to steal, when to deny | Sense-think-act loop; right model for right job |

The middle tier matches the original Tag Arms control scheme (WASD/Arrows) and is the most playable for casual demo.

**Agent toolkit (Tier 3):**
- `get_game_state()` — returns all live threats (with vector length, active duration remaining, position), all tags (with owner, state, position), score, time remaining
- `move_to(x, y)` — fly the gripper to a screen coordinate
- `grab()` — close gripper (picks up whatever ArUco is closest)
- `release()` — open gripper (drops carried tag)

---

## 14. Implementation notes

**Game backend:** Python (FastAPI + WebSockets)

**Game frontend:** HTML5 + Canvas with Geometry Dash visual treatment

**Robot control:** Python `pydobot` library

**Camera + ArUco:** Python `cv2.aruco`, 4K USB webcam

**M5 Atom firmware:** UIFlow / Arduino IDE — display shield icon, perimeter LED ring as countdown, WiFi/MQTT for state sync

**Game master interface:** Calibration, match timer, score, live event log, threat spawn rate tuning

**Operator interface:** Three modes selectable, tournament rounds force the mode for that round

---

## 15. Why this version works for the camp

- **Simpler than v4** — no shared asset, no five tool types, no cooperation, no "selfless move" tax. Just place, snatch, deny.
- **Same robotics pedagogy** — three control modes, same robotics principles, same team-roles structure
- **More immediate competition** — head-to-head 1v1 is more visceral than cooperative-competitive
- **Decisive matches** — every match produces a clear winner; no "asset destroyed, both lose" anticlimax
- **Cleaner spectator story** — only two things to track: score gap and steal attempts
- **Lower bar to entry** — players grasp the rules in 30 seconds; Tag Arms is a known, intuitive pattern
- **Denial mechanic teaches resource cost reasoning** — is it worth 4 seconds of arm travel to deny one opponent tag?
- **No "balanced fail state" tuning required** — v4's "win/defeat asset HP balance" was tricky to script; v5 is just a 90-sec score race

---

## What changed from v4

| Aspect | v4 (Cyber Defense) | v5 (Cyber Tag Arms) |
|:---|:---|:---|
| Shared asset | Yes, HP-based, mutual defeat possible | None — pure 1v1 score race |
| Tool typing | 5 typed tools (Neutralize, Honeypot, Sandbox, DDoS, Software Upgrade) | 4 generic tags per player |
| Tool count | 5 shared between teams | 4 per team (8 total) |
| Threats | Move from bottom to top toward asset | Fixed positions, expire after active duration |
| Cooperation | Required (both must defend asset) | None — pure competition |
| Outcomes | Defeat (both lose 0) / Win (3-1 split) | Win (3) / Loss (1) / Tie (2-2) |
| Denial mechanic | Implicit via cleanup of spent tools | Explicit via bin-to-bin tag theft |
| Strategic depth | Tool typing + cooperation tension | Snatch + denial timing |

---

*End of game design document.*

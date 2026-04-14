# Cogs — Spec Sheet

## Product

**Cogs** — a browser-based robot control platform for summer camp competitions. The server runs on a single laptop (the game operator's machine). All other players connect to it over local WiFi from any device — phone, tablet, or PC. Used for both Dobot MG400 robotic arm (day 1) and rovers (day 2).

## Users & roles

| Role | Count | Description |
|---|---|---|
| Pilot | 4 per team | Controls robots via the interface |
| Team supervisor | 1 per team | Coordinates pilots, sends messages, can trigger commands on multiple bots |
| Game operator | 1 total | Manages matches (start/pause/reset/save) |

## Supported hardware

| Device | Connection | Count |
|---|---|---|
| Dobot MG400 robotic arm | TCP/IP | 4 (one per team) |
| Rover (cellphone-sized) | HTTP API over WiFi (local Linux + Python server on each rover) | 8 (four per team) |
| USB cameras | USB | Multiple per arena (overhead + optional: upward, dispenser, side) |

---

## Interface

### Layout

Blender-style panel system. The screen is divided into resizable panes using Split.js. Each pane has a dropdown in the top-left corner to select its window type (camera, code, chat, messages, etc.) — any pane can become any window type. Users can split panes further or collapse them.

- Panes resizable by dragging dividers (Split.js).
- Top-left dropdown per pane: select window type (same as Blender's editor type selector).
- Layout saved per user/team in local storage.
- Default layout: three panes side by side (camera, code, chat). Users rearrange as needed.
- Responsive: works on phone (single pane, swipe to switch), tablet, and PC (multi-pane).
- Styling: Pico.css.

### 1. Camera view

- Live overhead camera feed. Clickable: clicking a point sends normalized coordinates `(x, y)` to the server.
- Server-side Python code translates click position to physical coordinates and commands the robot.
- Shows: click target marker, robot position indicator.
- Day 1: click = move arm to position, grip/release based on context.
- Day 2: select rover first, then click = drive to position.
- Multiple camera feeds supported. Any pane can be set to camera view and assigned a different video source.
- Each camera feed can have its own Python processing pipeline on the server. Pipeline output is available as input to the click handler function.
- Examples:
  - Upward-facing camera for tool/gripper orientation detection.
  - Camera inside the dispenser/collection box for automatic point counting.
  - Side camera for height estimation.
- Students can write and modify camera processing pipelines in the code panel — same edit-and-run workflow as the click handler.

### 2. Code panel (center)

- Default view: `main.py` containing the click handler. This is what most students see and edit.
- Advanced mode: exposes the full workspace folder — all files, vision pipeline packages, configs.
- Editable: students can modify code. Changes take effect on next click.
- Output log: stdout, stderr, robot status.
- Syntax highlighting (CodeMirror or Monaco).

**Vision pipeline tools:**

- Vision tools (QR detection, color tracking, object counting, etc.) are packaged as pip packages with source in the workspace.
- Default set is pre-installed. Advanced users can read, edit, and debug the pipeline source code directly.
- Additional tools can be `pip install` from GitHub into the sandbox.
- Integrated terminal available in advanced mode for shell access.

**Sandbox:**

- Each team's environment runs in an isolated sandbox (Docker container or virtual environment).
- Teams can install any pip packages or CLI tools they need during the game.
- Reset returns the sandbox to a clean base image — all user-installed packages and changes are wiped.
- Team code snapshots (version history) are stored outside the sandbox and survive resets.

### 3. Chat panel (right)

- Chat with Claude Code.
- Claude Code sees: team's code, latest camera frame, robot status, match state.
- Claude Code has access to local tools — prebuilt image recognition and QR code reader for detecting bot/arm positions and coordinates from the camera feed.
- Claude Code can install additional command-line tools into its sandbox as needed to achieve the desired result.
- Students ask questions, request strategy, or ask Claude to write code.
- When Claude proposes code changes: diff preview appears in code panel, student clicks Apply or Reject.
- Day 2 only: team can ask Claude to autonomously pilot one rover. Requires all 4 other members to approve via dialog.

---

## Version history

- Every code change saved as timestamped snapshot.
- One-click rollback to any previous state.
- Append-only JSON log on server.

## Calibration

- Startup: place markers at known positions, server computes homography matrix (pixel → physical).
- Deliberately imperfect out of the box — students discover the offset and learn to calibrate.

## Emergency stop

- Persistent red button visible in UI at all times.
- Immediately halts all robot movement for the team.

---

## Special modes

### Game operator

Dedicated mode for the instructor.

**Game setup:**

- Operator loads a game configuration from a `.zip` file or a GitHub repo URL.
- The configuration contains: robot definitions, arena layout, scoring rules, vision pipeline tools, default `main.py` for teams, install scripts.
- On load, the server runs the configuration's install script — installs all dependencies, sets up team sandboxes with the right tools and code.
- After setup completes, teams can connect and see their workspace. Game has not started yet.

**Match controls:**

- **Start game** — begins countdown, activates robot commands for all teams.
- **Pause game** — freezes timer, disables robot commands. Teams keep UI open.
- **Reset game** — clears scores, resets timer, returns to warmup state. Sandboxes reset to the configuration's base state.
- **Save game** — exports match as `.zip`: metadata, scores, timer events, team action logs, camera video recordings, all code snapshots, chat logs.
- Timer and scores pushed to all team screens in real time.
- Match states: setup → warmup → active → paused → finished.

### Team supervisor

One member per team. Same app, with an additional messaging panel.

- Can send text messages to any or all pilots on the team.
- Messages appear as notifications on the pilot's screen. Pilots can reply.
- Messages are available to the team's Python code via a message queue API:

```python
from messages import inbox

def on_click(pixel_x, pixel_y):
    # Check for new supervisor messages
    for msg in inbox.get_new():
        # msg.text is a plain string — team decides how to parse it
        if "stop" in msg.text:
            rover.stop()
        elif msg.text.startswith("go "):
            # team-defined behavior
            ...

    # Normal click handling continues
    phys_x, phys_y = calibration.pixel_to_physical(pixel_x, pixel_y)
    rover.drive_to(phys_x, phys_y)
```

- No special command syntax enforced — supervisor sends plain text, and the team's code decides what to do with it. The parsing logic is part of what students write and iterate on.
- All messages are logged.

---

## Competition scoring

### Day 1 (arm)

- 2 teams per match, shared workspace.
- Yellow cube = 2 pts, green = 5 pts, red = 9 pts.
- 5-minute break between rounds (Claude Code consultation allowed).

### Day 2 (rovers)

- 2 teams per match, 4v4 rovers on 3 × 3 m arena.
- White disc = 1 pt, yellow = 3 pts, red = 7 pts.
- Momentum: each collected disc increases team rover speed (configurable multiplier).

---

## Robot API

Unified Python interface on the server.

```python
class Robot:
    move_to(x, y) -> None
    get_position() -> (float, float)
    stop() -> None
    status() -> "idle" | "moving" | "error"

class Arm(Robot):
    lower_and_grip() -> None
    release() -> None
    set_z(z) -> None

class Rover(Robot):
    set_speed(multiplier) -> None
```

- Both Dobot and rovers are controlled via HTTP API over WiFi — same communication pattern.
- Each rover runs its own Linux + Python server, exposing an HTTP API.
- One command at a time per robot. New command cancels current.
- Software movement limits on arm to prevent collisions.
- Collision warning if two same-team rovers are within threshold distance.

---

## Requirements

| Property | Target |
|---|---|
| Click-to-command latency | < 200 ms |
| Camera | >= 15 fps, >= 720p |
| Browser | Any modern browser (Chrome, Safari, Firefox) — must work on phone, tablet, and PC |
| Network | Local WiFi, no internet needed during matches. All players connect to operator's server |
| Instructor match setup | < 2 min |

### Failure handling

- Camera loss: last frame + "FEED LOST" overlay.
- Robot disconnect: error state in UI, allow reconnect.
- Server crash: auto-restart, restore last code snapshot.

---

## Tech stack

- **Server**: Python, FastAPI, WebSocket.
- **Client**: HTML / JS, Pico.css (styling), Split.js (panel layout).
- **Editor**: CodeMirror or Monaco.
- **AI**: Claude Code CLI (subprocess per team).
- **Dobot**: Official Python SDK over TCP/IP.
- **Rovers**: HTTP API over WiFi (each rover runs local Linux + Python server).

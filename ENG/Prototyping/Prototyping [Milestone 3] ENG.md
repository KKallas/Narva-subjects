## Prototyping: Milestone 3 — Integrated Technical Prototype

**Workload:** 18 hours | **Assessment:** 20 points | **Meeting: Sat 18.04**

**NB: 2nd order: if anyone still has the PCB unordered, let's get it done quickly**

At the end of M2 you had a test chassis that drives and a web page with a "forward" button. Now you put everything together on one chassis and replace the buttons with clicking on the camera image. When the operator clicks a spot in the image, the robot drives there — that is the core task of M3.

The priority order is: first put the components on one chassis and check that everything still works. Then calibrate the camera (without it you cannot translate a click in the image into a location on the ground). Then build the raycast logic. Find a solution that gets the robot "roughly there" within ±10 mm and ±3 degrees. If something does not work, ask a teammate first, then on the Moodle forum or me personally — do not stew on a plan for more than 15 minutes.

---

### 1. Integrated chassis

**Prerequisite:** the M2 drive, communication and web interface must work.

**Goal:** assemble all the components and your PCB on one chassis, powered from one battery, one system that starts with one switch.

**What you need:**
- All the M2 components (motors, driver, MCU, sensors, compute platform)
- Battery (LiPo, USB power bank, etc. — depends on your choice)
- Power switch
- Wires, terminals, double-sided tape / screws

**Task:**

1. Place the components on the chassis so that the camera sees forward (for the raycast), the sensors are in their places (distance forward, colour downward), and the battery is easy to swap
2. Wire up a common power system — one on/off switch
3. Power it up, open the web page, check that everything that worked at the end of M2 still works
4. If something does not work after assembly → **do not continue**, find the fault (usually: bad ground, a loose contact, supply voltage dropping under load)

**Power hierarchy check:**

- Battery voltage (e.g. 7.4V LiPo or 5V power bank) → (boost 5V/12V) → motor driver → motor
- Battery voltage (e.g. 7.4V LiPo or 5V power bank) → regulator → 5V for the logic and 3.3V for the MCU
- **Common GND across all components** — without it the communication will not work

**Check with a multimeter:**

```
Before applying power (multimeter, power OFF):
1. Short-circuit test — multimeter in "continuity" mode (beep). Check VCC → GND,
   12V → GND, 6V → GND, 5V → GND, 3.3V → GND. If it beeps or the resistance is below ~10 Ω → short, do not switch on.
2. Measure the battery voltage (at the battery terminals, no load) — e.g. a full 2S LiPo is ~8.4V; if it differs by much, stop, investigate, understand

Only now switch on:
3. Measure the power distribution points under load — is 5V really 5V, is 6V really 6V?
4. Check that the MCU started up (LED, serial output). If some regulator is hot — switch off immediately.
```

**YouTube/AI search terms:**
- `rover robot chassis layout design`
- `LiPo battery voltage regulator 12V 5V 3.3V`
- `USB-C PD trigger`
- `How to test PCBs`
- `Top PCB hidden tricks`
---

### 2. Camera calibration — an A4 chessboard + OpenCV

**Goal:** calibrate the camera with a single printed A4 chessboard. OpenCV detects all the chessboard corners automatically with sub-pixel accuracy, the chessboard itself defines the coordinate system, and the homography matrix translates every click straight into floor coordinates. **Not a single manual tape-measure measurement at calibration time.**

**Why this is better than a tape measure/laser:**
- **Sub-pixel accuracy** — `cv2.cornerSubPix` refines to below 0.1 pixel
- **63 points instead of 4** (a standard 7×9 chessboard) — RANSAC filters out the noise
- **The whole geometry comes from the internal structure of the pattern** (the known square size) — not from manual measurement
- **Repeatable** — print it once, always use it the same way
- **Visual check** — OpenCV draws the detected corners on top, you see immediately whether it works
- **The same technique** used by real vision systems (cars, drones, industrial robotics)

**Coordinate system:** the chessboard defines the geometry, but we want coordinates relative to the **robot's centre of rotation**, not relative to the chessboard. That is why during calibration we measure one number: **how far the centre of the chessboard is from the robot's centre of rotation** (`X0_CM`). That number goes straight into the homography computation — every pixel click then immediately gives a robot-relative coordinate. X = forward, Y = to the right.

**Layout:** the robot stands still, the camera looks forward. Put the chessboard on the floor in the camera's field of view — where most of the clicks will go. Measure from the robot's centre of rotation to the centre of the chessboard — that is `X0_CM`. If the chessboard is symmetrical about the robot's longitudinal axis, then `Y0_CM = 0`. One measurement, once.

**What you need:**
- A working camera stream + the ability to save one frame
- A printed A4 chessboard with 7×9 inner corners (see below)
- A tape measure (one measurement: robot → centre of the chessboard)
- Python packages: `opencv-python`, `numpy`

---

**Step 1: Generate and print the chessboard on A4**

It is recommended to generate the PDF yourself with Python code — then you know for sure what the square size is and you have a check mark on it. Script in Jupyter Lab:

```python
# pip install matplotlib  (if you don't have it)
import matplotlib.pyplot as plt
import matplotlib.patches as patches

# --- Parameters ---
COLS = 8           # squares horizontally (gives 7 inner corners)
ROWS = 10          # squares vertically (gives 9 inner corners)
SQUARE_MM = 25.0   # side of one square in millimetres
REF_LINE_MM = 50.0 # reference line for verifying the print

# A4 dimensions in inches (matplotlib wants inches)
A4_W_IN = 210 / 25.4
A4_H_IN = 297 / 25.4

fig, ax = plt.subplots(figsize=(A4_W_IN, A4_H_IN))
fig.subplots_adjust(left=0, right=1, top=1, bottom=0)

# Pattern centred
pat_w_mm = COLS * SQUARE_MM
pat_h_mm = ROWS * SQUARE_MM
x0_mm = (210 - pat_w_mm) / 2
y0_mm = (297 - pat_h_mm) / 2

# Draw the black squares
for r in range(ROWS):
    for c in range(COLS):
        if (r + c) % 2 == 0:
            x = (x0_mm + c * SQUARE_MM) / 25.4
            y = (y0_mm + r * SQUARE_MM) / 25.4
            s = SQUARE_MM / 25.4
            ax.add_patch(patches.Rectangle((x, y), s, s, facecolor='black'))

# Reference line at the bottom edge (measure it with a ruler after printing!)
ax.plot([10/25.4, (10 + REF_LINE_MM)/25.4], [5/25.4, 5/25.4],
        'k-', linewidth=2)
ax.text(10/25.4, 8/25.4,
        f'Reference line: {REF_LINE_MM:.0f} mm — measure with a ruler',
        fontsize=8)
ax.text(10/25.4, 12/25.4,
        f'Square size: {SQUARE_MM:.1f} mm | Pattern: {COLS}x{ROWS}',
        fontsize=8)

ax.set_xlim(0, A4_W_IN)
ax.set_ylim(0, A4_H_IN)
ax.set_aspect('equal')
ax.axis('off')

plt.savefig('chessboard_a4.pdf', format='pdf', bbox_inches=None, pad_inches=0)
print("Saved: chessboard_a4.pdf")
```

**Critical when printing:**

- **"Scale = 100%" / "Actual size"** — NOT "Fit to page", "Shrink oversized", "Auto rotate and scale"
- After printing, **measure the reference line with a ruler** — if it is 50 mm (±0.5 mm), then the squares are the correct 25 mm too
- **If the reference line is wrong** → change `SQUARE_MM` in the code to the real value (e.g. you measure 49 mm → the square is 24.5 mm), or print again on a different printer

**Fallback — a ready-made PDF from the internet:**

If Python is not at hand, the [calib.io pattern generator](https://calib.io/pages/camera-calibration-pattern-generator) does the same thing in the browser. Choose "Checkerboard", 8×10 squares, 25 mm square, download the PDF. Still check the printed size with a ruler.

**Step 2: Layout and measuring the offset**

1. Put the robot on the floor, camera looking forward
2. Put the chessboard in the camera's field of view — move it until **the centre of the chessboard is roughly in the centre of the image** (the best spread of corners)
3. Measure from the robot's centre of rotation to the centre of the chessboard: that is `X0_CM`. If the chessboard is symmetrically in front of the robot, then `Y0_CM = 0`
4. Write those numbers into the code — they go into the homography computation

**Step 3: Save one frame with the chessboard**

Save one jpg/png frame from the camera (e.g. open the camera's `/capture` endpoint or save the image from the browser). The chessboard must be fully visible — all 63 inner corners in the frame.

**Step 4: Detect the corners and compute the homography**

*untested example code, may need fixing, there was no data to test it with yet*

```python
import cv2
import numpy as np

# --- Parameters ---
PATTERN_SIZE = (7, 9)       # number of inner corners (columns, rows)
SQUARE_MM    = 25.3         # actual printed square size (measure with a ruler!)

# From the robot's centre of rotation to the centre of the chessboard (measured in step 2)
X0_CM        = 30.0         # forward (cm)
Y0_CM        = 0.0          # to the right (cm), 0 if symmetrical

# --- Load the frame ---
img = cv2.imread("calibration_frame.jpg")
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# --- Detect the chessboard corners ---
found, corners = cv2.findChessboardCorners(gray, PATTERN_SIZE, None)
if not found:
    raise RuntimeError("Chessboard not found! Check the lighting, the position of the pattern, the focus.")

# Refine to sub-pixel level
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
corners_refined = cv2.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)
pixel_pts = corners_refined.reshape(-1, 2).astype(np.float32)

# --- Generate the actual (X, Y) of every corner in cm ---
# The coordinates are around the centre point: the first corner is at (-half_h, -half_w) from the centre
half_rows = (PATTERN_SIZE[1] - 1) / 2.0   # half-width in the X direction (cm)
half_cols = (PATTERN_SIZE[0] - 1) / 2.0   # half-width in the Y direction (cm)

floor_pts = []
for row in range(PATTERN_SIZE[1]):         # row = X direction (forward)
    for col in range(PATTERN_SIZE[0]):     # column = Y direction (to the right)
        x_cm = X0_CM + (row - half_rows) * (SQUARE_MM / 10.0)
        y_cm = Y0_CM + (col - half_cols) * (SQUARE_MM / 10.0)
        floor_pts.append([x_cm, y_cm])
floor_pts = np.array(floor_pts, dtype=np.float32)

# --- Compute the homography (63 points, RANSAC discards the outliers) ---
H, mask = cv2.findHomography(pixel_pts, floor_pts, cv2.RANSAC, 5.0)

# --- Save ---
np.save("homography.npy", H)
print(f"Detected {len(pixel_pts)} corners, used {int(mask.sum())} inliers")

# --- Visual check ---
vis = img.copy()
cv2.drawChessboardCorners(vis, PATTERN_SIZE, corners_refined, found)
cv2.imwrite("calibration_check.jpg", vis)
```

**Step 5: Check the result**

Open `calibration_check.jpg` — every chessboard corner must be marked with a coloured circle, in a sequence of lines. If one row has a corner missing or one landing somewhere else, the detection did not work — check the lighting (avoid shadows and reflections) and make sure the pattern is fully in the frame.

---

**If you do not have a printer — a fallback:**

Mark 4 tape markers on the floor where they appear in the corners of the camera image, and measure their X and Y from the robot's centre of rotation with a tape measure. Then `cv2.getPerspectiveTransform(4 pixels, 4 floor points)` replaces `cv2.findHomography` and the chessboard part. The accuracy is ~±2 cm at best; with the chessboard you get below 1 cm.

---

**YouTube/AI search terms:**
- `OpenCV findChessboardCorners Python`
- `cv2 cornerSubPix tutorial`
- `chessboard camera calibration OpenCV`
- `cv2 findHomography RANSAC`
- `print chessboard A4 calibration` (chessboard PDFs)
- `ArUco marker calibration` (an alternative if the chessboard does not work)

---

### 3. Pixel-to-ground with the homography

**What is the `H` matrix?** H = **h**omography (Greek: *homo* = same, *graphia* = drawing). It is a 3×3 matrix that transforms a pixel coordinate into a floor coordinate. The chessboard calibration gave OpenCV 63 pairs: "this pixel = this point on the floor." From those 63 pairs OpenCV computed one matrix that works for **all** pixels, not just for the 63 corners — that is H. Once it is computed you no longer need the chessboard; the whole transformation is contained in H.

```
pixel (px, py)  →  [ H ]  →  floor (x_cm, y_cm) relative to the robot
```

**Prerequisite:** the calibration (step 2) is done, the `H` matrix exists.

**Goal:** every click in the image → a floor coordinate `(x_forward, y_right)`.

**The idea in code:**

*untested example code, may need fixing, there was no data to test it with yet*

```python
import cv2
import numpy as np

# Load the homography from disk (or use the one in memory)
H = np.load("homography.npy")

def pixel_to_ground(px, py):
    """A click in the image (px, py) → floor coordinate (x_cm_forward, y_cm_right)."""
    point = np.array([[[float(px), float(py)]]], dtype=np.float32)
    transformed = cv2.perspectiveTransform(point, H)
    x_fwd, y_right = transformed[0][0]
    return float(x_fwd), float(y_right)
```

That is the whole logic — 3 lines of work done for you by cv2. From pixel to floor coordinate, taking lens distortion into account, without any trigonometry.

**Check before moving on:**

1. Put an extra object (e.g. a bottle cap) on the floor at a known place — for example `(60 cm forward, 20 cm to the right)`.
2. Click on it in the image — your code must send the click coordinates to the server.
3. On the server call `pixel_to_ground(px, py)` — is the result close to `(60, 20)`?
4. Repeat with 5 places across the floor (near, far, at the edges).

**Tolerance:** the median error should be below 3 cm. If it is over 5 cm → the 4 corner measurements were inaccurate, calibrate again.

**If the error is much larger at the edges** → the camera has lens distortion (fisheye). Solution: pick 4 calibration points that cover the middle of the image (20%–80%), not the edges.

**YouTube/AI search terms:**
- `cv2 perspectiveTransform point example`
- `pixel to world coordinates homography`
- `robot camera ground plane mapping`

---

### 4. Click-and-drive logic

**Prerequisite:** the homography (step 3) gives reliable floor coordinates.

**Goal:** connect the whole chain — click → `pixel_to_ground` → compute distance + angle → turn → drive → stop.

**The core logic:**

A click in the image starts the following chain:

1. **Pixel → floor coordinate**: the homography (step 3) transforms the clicked pixel (px, py) into a floor coordinate (x_forward, y_right) relative to the robot
2. **Coordinate → distance and angle**: distance by Pythagoras, angle with `atan2`. Angle 0° = straight ahead, positive = to the right, negative = to the left
3. **Check**: if the target point is behind the robot (x negative) or too far away (over 3 m) → give up, do not drive
4. **Turn**: if the angle is over 5° (below that it drowns in noise), turn in the right direction. Turning time = angle divided by the rotation speed (degrees per second, measured). Stop, wait a moment (inertia)
5. **Drive straight**: driving time = distance divided by the speed (cm/s, measured). Stop.

You need two measured constants from your own robot: **linear speed** (cm/s) and **rotation speed** (degrees/s). You measure both with a stopwatch.

**The web interface side:**

Replace the M2 buttons with a camera image you can click on. The click coordinates (in pixels) go to the server, and the server starts the turn-and-drive chain. Remember: in the browser the image is scaled — the clicked pixel has to be converted to the camera's actual resolution (`naturalWidth` / displayed width).

**Task:**

1. Measure the linear speed and the turning speed of your robot — take a stopwatch and record the direction and time for a turn and for driving straight
2. Add the drive_to_point logic to the server
3. Add the click event to the web page
4. Open the web page, click a point in the image 50 cm straight in front of the robot — does it get roughly there?
5. Click a diagonal point — does it turn the right way?

**Typical problems:**

- **The robot overshoots:** the linear speed is actually lower — measure again
- **It turns too much/too little:** the rotation speed is wrong — measure again
- **The pixel coordinates are wrong:** you forgot the scaling in the browser (`naturalWidth` vs `clientWidth`)

**YouTube/AI search terms:**
- `differential drive robot turn calculation`
- `JavaScript image click coordinate`
- `FastAPI GET parameters`
- `open loop robot motion timing`

---

### 5. Boundary and zone detection

**Prerequisite:** the colour sensor worked on the M2 breadboard and is now mounted on the robot.

**Goal:** the robot must understand:
- **when it is on a patch of the right colour** (e.g. a scoring point, the starting position, a safe zone)
- **when it is on the boundary** (the red line — stop immediately)
- **when nothing matches** — it now sends the sensor readings to the operator so they know what it actually sees

The last point is important: if the sensor sees something unexpected (a shiny surface, a shadow, the edge area between two patches), the logic must neither panic nor mislead. The operator gets the readings in real time → they can improve the calibration. The sensor should stay within a 5 cm radius of the robot's centre of rotation.

---

**The principle — layered:**

1. **MCU layer:** the sensor is always reading. If the colour matches the **red boundary** → the motors are stopped immediately, regardless of what the server commands. This is a safety mechanism and it must not be delayed.
2. **Telemetry layer:** the sensor sends its readings (R, G, B, C + classification) to the server/web interface every ~100 ms. The operator sees what the robot really "sees" and can classify it.
3. **Classification layer:** the software decides from the readings which zone the robot is in. The rules are simple (RGB ranges) and written on the server, so that you can change them without reflashing the MCU.

---

**Calibrate the zones (once, on the arena):**

Before the game, put the robot on each colour patch, take 30 readings, compute the median and the standard deviation.

Make a table: each zone → mean (R, G, B, C) + spread. Detection is then "which zone is my reading closest to" — the classic nearest-neighbour method.

---

**MCU layer (boundary guard + continuous telemetry):**

The ESP32 has to do two things:
1. **Every loop iteration:** check the boundary (red line → stop). The fastest possible decision, no classification at all.
2. **Every ~100 ms:** send the sensor readings (R, G, B, C) to the web interface — a 100 ms interval is enough for the operator.

---

**Web interface:**

- **Current zone** (text/colour): "red patch", "yellow patch", "red boundary", "**unknown**"
- **Raw values** (debug): R, G, B, C in real time

That last piece of information is gold when something does not work — the operator sees that "the robot was probably on the edge between two patches, that is why it did not classify".

---

**Task:**

1. Write `zone_calibration.py` — calibrate all the arena colours (3 surfaces)
2. Add **only the boundary threshold + continuous telemetry** to the MCU loop (do not classify on the microcontroller)
3. Add `classify_reading()` to the server and send the result to the web interface over WebSocket
4. Add a "current zone" display + the raw values to the web interface
5. Test on the bench: put the robot on each zone, check that the classification matches. Put it between two patches — does it show "unknown"?
6. Test live: send a click-and-drive command that would take the robot over the boundary → does it stop before the boundary?

**YouTube/AI search terms:**
- `Arduino non-blocking loop sensor check`
- `Color calibration multiple surfaces`
- `safety watchdog microcontroller`

---

### 6. Battery logging

**Goal:** know how long the robot lasts before the battery has to be swapped. Also needed for M3 analysis 3 (battery runtime).

**Two options depending on your hardware:**

**A: The phone is the battery** — in Termux you can ask for the phone's battery percentage as JSON with the `termux-battery-status` command. Write a script that asks for it every 30 seconds and logs it to CSV (timestamp + percentage). Requires `pkg install termux-api` + the Termux:API app.

**B: LiPo battery + ESP32 ADC** — measure the battery voltage with the ESP32 ADC through a voltage divider. A full 2S LiPo is 8.4V, but the ESP32 ADC reads a maximum of 3.3V — so you need a voltage divider (e.g. a 3:1 ratio). The ESP32 reads the ADC value, converts it into a voltage (ADC reading × reference voltage / resolution × divider ratio) and sends it as JSON to the serial port every 5 seconds. The server logs it to CSV.

**YouTube/AI search terms:**
- `ESP32 battery voltage monitoring ADC`
- `voltage divider battery measurement`
- `termux-api battery status`
- `LiPo voltage state of charge`

---

### Click-and-drive accuracy (Analysis 1)

**Prerequisite:** step 4 works.

**Preparation:**

1. Mark one clear **reference point** on the robot's body (e.g. a cross in the centre of the body or the tip of the nose). You always measure the robot's position from it.
2. Mark 10 target points on the arena at known coordinates — use the arena's 10×10 cm hole grid.
3. Always place the robot at the same starting point and starting heading (mark it on the floor with tape).

**Recommended extra: a downward-facing sight (3D-printed)**

Replace eyeballing with a physical sight — it makes the measurement much more accurate and much faster.

3D-print a small arm that attaches to the robot and holds a **downward-facing cross** at its end (a thin 3D-printed cross, no electronics — no laser needed).

**Location:** under the centre of rotation there are usually wheels and electronics — putting the sight there is difficult. Two practical options:

- **Front-centre** (recommended) — the arm sticks out in front of the robot's nose, the cross hangs above the floor. You can see visually how the sight approaches the target point while driving.
- **Rear-centre** — the same thing towards the back of the robot. Less intuitive while driving, but fine if the nose is already full (camera, ToF).

Ideally the sight is on the robot's longitudinal axis, but in practice there is always some Y offset as well. **Measure both offsets** — the maths is no harder for it.

**How to account for it in the drive logic:**

Measure the position of the sight from the robot's centre of rotation: `SIGHT_X_CM` (forward) and `SIGHT_Y_CM` (to the right). We want the **sight** to reach the target point, not the centre of rotation. So we compute the target location for the centre of rotation:

```python
# Target point in the robot frame (from the homography)
target_x, target_y = pixel_to_ground(px, py)

# Target for the centre of rotation = target point minus the sight offset
adj_x = target_x - SIGHT_X_CM
adj_y = target_y - SIGHT_Y_CM

# From here the same logic: angle and distance from adj_x, adj_y
distance_cm = math.sqrt(adj_x**2 + adj_y**2)
angle_deg = math.degrees(math.atan2(adj_y, adj_x))
```

**Design specs for the STL:**
- The arm long enough that the cross reaches past the edge of the robot's body (does not block the view)
- Modular mounting — the sight comes off when it is in the way
- A mounting point in the existing 3D-printed body
- The lines of the cross thin (1–2 mm), so they do not hide the target point during the measurement
- The STL in the repo, for example at `cad/sight_cross.stl`

**The benefit:**
- The measurement becomes **observational**: you put the robot in place, the cross shows the exact point on the floor, and you measure its distance from the target point on the hole grid
- You no longer have to guess "was the reference point in the centre of the body really exactly above the hole grid"
- The same thing works for validating the M4 autonomous mode

**Measurement:**

1. Click a target point in the web interface
2. Wait until the robot stops
3. Measure the actual position of the reference point (the sight cross) against the hole grid (nearest hole + an estimate of the offset in cm)
4. Repeat each target point 3 times

**Data analysis in Jupyter Lab:**

Save the measurements as CSV (columns: `target_x`, `target_y`, `actual_x`, `actual_y`). In the Jupyter notebook do the following:

1. **Compute the error of each measurement** — the Euclidean distance between the target point and the actual stopping place (cm)
2. **Compute the distance of each target point from the starting point** — to see whether the error depends on distance
3. **Scatter plot "target vs. actual"** — draw on the same plot the blue points (where it should have got to) and the red points (where it actually got to), and connect each pair with a grey line. This shows visually where and by how much the robot is wrong.
4. **Scatter plot "error vs. distance"** — the distance of the target point from the start on the X axis, the error on the Y axis. Are the more distant target points less accurate?
5. **Median and maximum error** — two numbers that summarise how accurate the system is

**Assessment:** if the median error is below 10 cm and the maximum below 20 cm → usable for manual control. If the error grows with distance → the homography is inaccurate further away (typical), account for it or limit the maximum target distance.

---

### Boundary detection reaction time (Analysis 2)

**Prerequisite:** step 5 works.

**The problem:** the boundary area is 10 cm wide. The robot has to detect it + stop before it drives through. We measure: how fast the sensor reacts and how far the robot travels in that time.

**Measurement 1 — the sensor's reaction time:**

1. Place the colour sensor stationary above the boundary area (the sensor sees the red boundary colour)
2. Quickly pull the boundary out from under the sensor (or slide another colour under the sensor)
3. Write the measurement logic into the MCU code: you press Enter in the Serial Monitor → the timer starts → when the sensor reading changes (the red disappears) → the timer stops → it prints the time in milliseconds. The logic: `micros()` before and after, the difference is the reaction time.
4. Repeat 30 times, save to CSV

**Computation — the stopping distance:**

The stopping distance consists of three parts that add up:

1. **The sensor's reaction time** — you just measured it (median and max from the CSV)
2. **Communication latency** — how long it takes for the command to get from the MCU to the motors (already measured in M2)
3. **The motor braking time** — drive at full speed, send a stop command, measure how much further the robot travels

Total reaction time (worst case) = sensor max + communication max + motor braking

Stopping distance (cm) = the robot's speed (cm/s) × the total reaction time (s)

**Table:**

| Parameter | Min | Median | Max |
|:---|:---|:---|:---|
| Sensor reaction (ms) | ... | ... | ... |
| Communication latency (ms, from M2) | ... | ... | ... |
| Motor braking (ms) | ... | ... | ... |
| Total reaction (ms) | ... | ... | ... |
| Stopping distance (cm) | ... | ... | ... |

**Assessment:** if the maximum stopping distance is below 10 cm → the robot stops within the boundary area. If it is more → either limit the speed, start detecting earlier, or make the boundary area wider.

---

### Battery runtime with the complete system (Analysis 3)

**Prerequisite:** battery logging (step 6) works.

**Measurement:**

1. Charge the battery to 100%
2. Start the robot, start the battery logging script
3. Drive actively for 3 minutes (click on the web page, keep the robot driving) — simulate the load of a match
4. Then 1 minute passively (the robot stands still but the system is running) — the gap between matches
5. Repeat until the battery is at 20%

**Jupyter Lab analysis:**

1. **Line graph: battery % vs. time (in minutes)** — time from the start on the X axis, battery percentage on the Y axis. Add a horizontal line at 20% (the danger threshold).
2. **Compute the time to 20%** — how many minutes did it take?
3. **Compute how many matches you get** — the time to 20% divided by 4 (a 3 min match + a 1 min gap)

**Assessment:** if you get fewer than 3 matches → you need a bigger battery, a faster charger or swappable batteries. If more than 5 → fine.

---

### Assessment criteria

| Category | Points | What is assessed |
|:---|:---|:---|
| Work files | 4 p | Code in the repo, photos/videos of the integrated robot |
| Analysis | 4 p | 3 Jupyter notebooks (accuracy, boundary reaction, battery) |
| Prototype | 4 p | Does click-and-drive work? Does the boundary stop the robot? |
| Documentation | 4 p | Specification update with the integration problems |
| Q&A | 4 p | Demo at the meeting + discussion |
| **Total** | **20 p** | |

---

### Combined list of YouTube/AI search terms

Search for these on YouTube/with AI — do not watch the whole video, scroll to the part where your problem is.

**Assembly and power:**
- `robot chassis layout design`
- `LiPo battery voltage regulator 5V 3.3V`
- `robot power distribution bus`
- `common ground wiring microcontroller`

**Camera and homography:**
- `OpenCV findChessboardCorners Python`
- `cv2 cornerSubPix tutorial`
- `chessboard camera calibration OpenCV`
- `cv2 findHomography RANSAC`
- `print chessboard A4 calibration` (chessboard PDFs)
- `ArUco marker calibration` (an alternative)

**Click-and-drive:**
- `differential drive robot turn calculation`
- `JavaScript image click coordinate`
- `FastAPI GET parameters`
- `open loop robot motion timing`

**Boundary detection:**
- `Arduino non-blocking loop sensor check`
- `robot boundary detection line sensor`
- `TCS34725 color threshold detection`
- `safety watchdog microcontroller`

**Battery monitoring:**
- `ESP32 battery voltage monitoring ADC`
- `voltage divider battery measurement`
- `termux-api battery status`
- `LiPo voltage state of charge`

**Data analysis:**
- `matplotlib scatter plot tutorial`
- `pandas groupby aggregate`
- `numpy interp interpolation`

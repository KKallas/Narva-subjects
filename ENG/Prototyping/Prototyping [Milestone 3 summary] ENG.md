## Prototyping: Milestone 3 — Integrated Technical Prototype

**Workload:** 18 hours | **Assessment:** 20 points | **Teamwork:** teams of 4

### What you do

You put all the M2 components together on a single chassis and replace the manual buttons with clicking on the camera image. When the operator clicks a spot in the camera image, the robot drives there — that is the core task of M3.

**Integrated chassis** — all M2 components (motors, driver, MCU, sensors, compute platform) on one chassis, powered from a single battery, one on/off switch. Check with a multimeter before switching on (short-circuit test, voltage check).

**Camera calibration** — print an A4 chessboard (8×10 squares, 25 mm), place it in the robot camera's field of view, measure the robot's offset from the chessboard centre. OpenCV detects the 63 corners with sub-pixel accuracy and computes the H (homography) matrix — a 3×3 transformation table that turns every pixel into a floor coordinate relative to the robot.

**Click-and-drive** — click on the image → homography → distance and angle → turn → drive → stop. You need two measured constants: linear speed (cm/s) and rotation speed (degrees/s), both with a stopwatch.

**Boundary and zone detection** — the red line is the outer boundary (the MCU detects it immediately and stops the motors regardless of the server). You calibrate the zone colours on the arena itself (30 readings per surface), classification by nearest-neighbour on the server. The web interface shows the current zone + the raw values.

**Battery logging** — log the battery level (the phone's BatteryManager or an ESP32 ADC with a voltage divider) to CSV every 30 seconds.

### Analyses (Jupyter Lab)

Three analyses in Jupyter notebooks:

1. **Click-and-drive accuracy** — 10 target points × 3 repetitions, scatter plot of target vs. actual + error vs. distance, median and maximum error
2. **Boundary detection reaction time** — sensor reaction + communication latency + motor braking = total stopping distance (cm). Does the robot stop within the 10 cm boundary area?
3. **Battery runtime** — battery % vs. time under match conditions (cycles of 3 min active + 1 min passive), how many matches do you get before the 20% threshold?

### Required for the defence

**Only a link to the git repository.** The repo must contain:
- Working code (integrated system: click-and-drive + boundary detection)
- Jupyter notebooks for the analyses together with the measurement data (CSV)
- An updated specification: what changed after integration?
- Photos/videos of the integrated robot

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Work files — code in the repo, photos/videos | 4 p |
| Analysis — three Jupyter notebooks | 4 p |
| Prototype — click-and-drive works, the boundary stops the robot | 4 p |
| Documentation — specification update | 4 p |
| Q&A session and feedback | 4 p |
| **Total** | **20 p** |

### Full worksheet

📎 *Add a link to the full worksheet here*

## Prototyping: Milestone 2 — Key Technology Prototype

**Workload:** 16 hours | **Assessment:** 20 points | **Teamwork:** teams of 4

### What you do

You build and test the most critical technical components separately — before you try to put everything together. Each subprototype must work on its own before you move on to the next one.

**Drive prototype** — motors + driver + wheels on a simple test chassis. Tests: forward/backward, turning, load tests with weights.

**Communication prototype** — ESP32 ↔ phone (USB OTG / WiFi), JSON commands. Start by testing from a computer over USB, then switch over to the phone.

**Web interface prototype** — a minimal web page: one button → the motor moves. Termux + FastAPI on the phone, or an ESP32 web server.

**Sensor prototype** — distance sensor and/or colour sensor on a breadboard. Measurements at different distances and on different surfaces.

**PCB design** — motor driver board in Fusion 360 EDA (schematic, layout, DRC, Gerber files).

### Analyses (Jupyter Lab)

Three analyses in Jupyter notebooks: a push test (load mass vs. speed, measured vs. calculated in the specification), communication latency distribution (100+ measurements, histogram, median and 95th percentile) and sensor detection statistics (accuracy and resolution at different distances and on different surfaces).

### Required for the defence

**Only a link to the git repository.** The repo must contain:
- Working code (ESP32 + phone/computer side)
- Jupyter notebooks for the analyses together with the measurement data (CSV)
- An updated specification: what changed after the first tests?
- PCB design files (schematic + Gerber)

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Work files — drive, communication and sensor code | 4 p |
| Simulation / analysis — three Jupyter analyses | 4 p |
| Prototype / physical — working test chassis and communication | 4 p |
| Documentation — updated specification | 4 p |
| Q&A session and feedback | 4 p |
| **Total** | **20 p** |

### Full worksheet

📎 *Add a link to the full worksheet here*

# Narva College Technical Curriculum 2026/27 — v2 summary

**One machine, four courses, 12 students in 4 teams of 3.** An MG400 cell that assembles the Cyber Tag Arms tag: AtomS3 (24×24 mm, 0.85" screen) + battery module + polycarbonate glass glued over the screen with transparent UV resin, cured by a 405 nm LED on the nozzle. The finished tag is lifted by its face with a suction cup. The 2027 summer camp uses the tags.

**Given**: MG400 ×5, Dobot mini vacuum pump box (−70…+110 kPa) and suction kit, polycarbonate worktable, 3D printers, oscilloscope, and the instructor's **base Python package for the MG400**. Dobot's own software is not used.

**Built by students**: the tool (3/2 valve switching one line between the suction cup, unpowered, and the syringe, energized; two pressure sensors; UV LED; nozzle camera; ESP32 tool PCB), the trays and jig, the enclosures, the RPI control station with a workflow recorder, the cloud database all four teams write into, and the models trained on that data.

## The cycle every course serves

Place AtomS3 in jig → dispense resin on the bezel (pressure curve) → pick glass with the cup (vacuum curve) → place, blow-off → cure with the LED, tip outside the cone → image → finished slot → one record: parameters, both curves at 100 Hz, syringe fill, image, outcome.

## Grading (unchanged from v1)

5 small projects × 20p (working files 5, analysis 5, prototype 5, documentation 5) + integration 70p; grade from the best 100. Peer review in writing in MS Teams chat, 2p per substantive form, max 4p per defense. Each team creates and owns its repo; the instructor gets read access. Git tag 72 h before the defense is the only submission. 5 min presentation, 10 min questions **including one live change to the running system**. Bonus for finding the instructor's errors, including merged pull requests to the base package.

## Agents

Everyone uses one. Each lab has an **Acceptance** list of physical or measured items (CSV, caliper table, scale reading, video, scope screenshot). Grade the artefact and the data, not the code. Team repo has `AGENTS.md`; so does the base package. Optional agent consultation in Data Acquisition around 24.09: Claude Code, Codex and Hermes on the team's lab 1 code, where each goes wrong, how to check against the measurement.

## Ordering

Session 1 on the shelf and the mystery box. Next lab's text and component list handed out at every meeting. Order goes out **10 days before the meeting**: 22.09, 13.10, 03.11, 24.11, 06.01. PCBs ordered 14.11 on review day.

## Hardware gates

| Gate | Date | Decision |
|:--|:--|:--|
| A resin dose and cure | 18.09 | tip size, pressure, pulse, cure time from a bench test with scale and MG400 pull-off |
| B sensors | 22.09 | MPX5100DP (syringe, 0–100 kPa), MPXV6115V (cup, −115–0 kPa); MPX5700AP used on 12.09 as the wrong-range example |
| C valve | 22.09 | direct-acting, spring return, vacuum-rated; unpowered = cup |
| D camera | 22.09 | AtomS3R-CAM or ESP32-CAM, MJPEG over WiFi |
| E tool PCB | 14.11 | ESP32, both sensors, op-amp, comparator, valve drivers, LED channel with default-low enable, pump outputs, VL53L0X, buck |

UV rules: 405 nm (PC blocks 365 nm); amber syringes and tip caps; shrouded LED, interlocked and timing out; goggles, gloves, IPA.

## The fifteen labs

| | Data Acquisition | Smart Solutions | 3D Printing |
|:--|:--|:--|:--|
| **L1** | Raw ADC at 100 Hz, first FFT, Pa/LSB for the wrong and the right sensor | RPI, IPv4, base package CLI, pump DO, teach/replay; pick a tag from a phone | Blender pen holder, robot draws day one; FDM physics; Fusion rebuild; syringe + LED holder on the lifting nozzle |
| **L2** | Op-amp, 4 configs + vacuum branch, spectra and SNR side by side | Tool-board interface (`valve`, `pump`, `dispense_ms`, `uv_ms`), UART/HTTP/MQTT, nozzle camera on the page | Tray 5+5+5, gluing jig, snap feet, bolt-compression test, registration test on two printers |
| **L3** | dP/dt interrupt on a real cured-tip clog, VL53L0X on a long cable, **tool PCB reviewed and ordered** | Droplet, WireGuard, nginx with MJPEG through it; place a tag from home | Tool housing on the arm (valve, board, camera, LED) and station housing; print-pause |
| **L4** | 500+ cycles by the robot, fill ground truth by scale, pick labels, cure vs. pull-off | Shared InfluxDB schema for all teams, workflow recorder (record → replay in 5 min), locking, portal | Improve one part three ways (manual, generative, original), MG400 load test |
| **L5** | H1 compensation table or H0 no dependence, proven on the scale; pick classifier | Measured RPI limits, physical safe state on cable pull, REST API, an agent assembles a tag | ISO drawing of the glass batch, CNC or die-cut order, validation on arrival |
| **Integration** | Fill and fault monitoring in the loop | Clone-an-SD-card station | Manufacturing-ready mechanical package |

**Semester 2, Prototyping**: audit → first tag from a recorded workflow → model in the loop → enclosures and battery plugging → production run for the camp. Dates 27.02, 20.03, 17.04, 29.05.

## Meeting dates

3D Print Fridays 11.09, 02.10, 23.10, 13.11, 04.12, 16.01. Data Acquisition and Smart Solutions Saturdays 12.09, 03.10, 24.10, 14.11, 05.12, 16.01. Consultations optional: agents ~24.09, op-amp ~15.10, resolution ~05.11, nginx ~25.11.

## Still to decide

Pump box control owner (ESP32 recommended, MG400 DO fallback) · AtomS3 vs AtomS3R (AtomS3 listed EOL) · L5 object: glass batch or tray plate · battery plugging in semester 2 or out · base package day-one scope and PR access · 1 W vs 3 W LED.

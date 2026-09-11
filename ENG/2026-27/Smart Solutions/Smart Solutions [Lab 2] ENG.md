## Smart Solutions: Lab 2 — Tool-board interface and nozzle camera

**Workload:** 26 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 03.10.26 | **Order date:** 13.10.26 | **Defense:** 27.10.26, online

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the lab folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

The tool on the arm gets its own computer: an M5 Atom Lite (ESP32-B) on the RPI's USB port. It reports both pressure branches and the state of the valve, pump and UV LED at 100 Hz, and it **acts**: it switches the 3/2 valve between cup and syringe, switches the pump box between off, suction and blow, runs a timed dispense, and runs a timed UV cure. The RPI stops talking to the pump box through the MG400 DO lines and talks to the tool board instead.

The message format you define here is the **tool-board interface** that Data Acquisition Lab 3 implements on the PCB and Data Acquisition Lab 4 drives for 500 cycles. It is frozen in this lab, reproduced below exactly as in the course conventions, and lives in `docs/tool-board-interface.md`. Three transports are tried for the same messages, USB/UART, WiFi HTTP and MQTT, and their command-to-response latency is measured. UART is the one the PCB uses; the other two teach you what a request, a response and a broker are before Lab 3 and Lab 4 need them.

Two safety rules are part of the interface, not an afterthought: `uv` is refused unless the RPI sends `pose_ok=1` (the robot is at the cure pose, tip outside the light cone), and the LED times out on the board regardless of what the RPI does. Unpowered valve = cup branch = safe. The nozzle camera (AtomS3R-CAM or ESP32-CAM) streams MJPEG over WiFi into the same page, so the operator sees the tip while the curve draws.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* Smart Solutions L1: the RPI station, Flask page, base package layer, saved positions.
* 3D Print L1: the syringe + LED holder on the lifting nozzle (LED boss ≥30 mm from the tip).
* Data Acquisition L2: the cell's one pressure sensor (MPX5100DP, syringe branch) and the scaling knowledge; a voltage divider (config 2) is the minimum, the op-amp stage (config 3) when you have it. The cup is not instrumented — the camera judges the pick.

**Gives to**
* Data Acquisition L3: `docs/tool-board-interface.md`, the command set the PCB implements.
* 3D Print L3: the camera position that sees tip and tray in one frame, the LED and valve mounting needs.
* Smart Solutions L3: the page, camera stream and Mosquitto that go behind the VPN.

### Background Information

* **pyserial short introduction** — opening the port, reading lines, timeouts.
  [https://pyserial.readthedocs.io/en/latest/shortintro.html](https://pyserial.readthedocs.io/en/latest/shortintro.html)
* **ESP32 access point web server** — AP mode, GET handlers, the WiFi alternative.
  [https://randomnerdtutorials.com/esp32-access-point-ap-web-server/](https://randomnerdtutorials.com/esp32-access-point-ap-web-server/)
* **ESP32 MQTT publish/subscribe** — the ESP32 side of the MQTT variant.
  [https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide/](https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide/)
* **ESP32-CAM video streaming** — MJPEG stream endpoint, frame size and quality settings.
  [https://randomnerdtutorials.com/esp32-cam-video-streaming-web-server-camera-home-assistant/](https://randomnerdtutorials.com/esp32-cam-video-streaming-web-server-camera-home-assistant/)
* **Mosquitto documentation** — broker install on the RPI, `mosquitto_pub` / `mosquitto_sub` for testing.
  [https://mosquitto.org/documentation/](https://mosquitto.org/documentation/)
* **ArduinoJson** — JSON on a microcontroller without heap surprises. [https://arduinojson.org/](https://arduinojson.org/)
* **M5 AtomS3R-CAM / Atom Lite** — [https://docs.m5stack.com](https://docs.m5stack.com), search phrase: "AtomS3R CAM docs m5stack" and "ATOM Lite docs m5stack". The spring 2026 camera firmware and mounts are in the instructor's repo.
* **MJPEG over HTTP** — search phrase: "multipart/x-mixed-replace MJPEG stream browser img tag". One `<img>` tag is the whole client.
* **Flask streaming responses** — proxying the camera through Flask if the browser cannot reach the camera's WiFi directly. [https://flask.palletsprojects.com/en/stable/patterns/streaming/](https://flask.palletsprojects.com/en/stable/patterns/streaming/)

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. Lab 1 station (RPI, MG400, base package, Flask page)
2. M5 Atom Lite (ESP32-B) on USB to the RPI; Arduino IDE or PlatformIO
3. MPX5100DP on the syringe branch with divider or op-amp stage on a small breadboard on the arm — one sensor, no vacuum sensor
4. 3/2 valve, 24 V, with 4 mm fittings and tube; MOSFET module ×3 (valve, pump-box lines, LED enable); flyback diode across the valve coil
5. Dobot mini vacuum pump box, 24 V; its supply also feeds the valve coil
6. 405 nm LED on star heatsink, constant-current driver, shroud; 405 nm goggles
7. Nozzle camera: M5 AtomS3R-CAM or AI-Thinker ESP32-CAM, powered from the tool board or a USB cable
8. Amber syringe 10 ml with 0.8 mm tip, resin from the Gate A set, waste cup, nitrile gloves, IPA
9. Mosquitto on the RPI; `mosquitto_sub` for watching topics
10. Oscilloscope or logic analyzer for the latency measurement

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Wire the arm: both sensors to the ESP32 ADC through the divider/op-amp, valve through a MOSFET module with a flyback diode, pump-box suction and blow lines through MOSFET modules, LED driver enable through a MOSFET module, camera power. Photo and hand-drawn schematic in `docs/`
- [ ] Firmware, reporting only: one JSON sample line per 10 ms on UART at 115200. RPI reads with pyserial and prints; verify 100 lines per second for 60 s
- [ ] Firmware, commands: parse one JSON object per line; `valve`, `pump`, `dispense`, `uv`, `stop`, `clear`, `status`; ack every command; emit `dispense_start`/`dispense_end` events
- [ ] Safety in firmware: `uv` without `pose_ok=1` → `ok:0, err:"pose"`; LED off after `ms` regardless; hard cap on `ms` (10 000); `stop` cuts everything; boot state = valve off, pump off, uv 0
- [ ] RPI side: a serial reader process writing samples to a ring buffer, a command function that waits for the ack with a 500 ms timeout, curve slicing between `dispense_start` and `dispense_end`
- [ ] Flask page, one screen: MG400 status and jog from Lab 1, live p and v numbers and a 10 s rolling plot, valve/pump/uv state, Dispense N ms button with the curve of the last dispense, UV button greyed unless the robot is at the cure pose, camera `<img>`
- [ ] WiFi variant: ESP32 in AP mode, `GET /data` returns the latest sample, `POST /cmd` takes the same JSON command; RPI client with `requests`
- [ ] MQTT variant: Mosquitto on the RPI; ESP32 publishes `tool/<team>/sample`, subscribes `tool/<team>/cmd`, publishes acks on `tool/<team>/ack`
- [ ] Latency measurement for all three transports (Analysis 1); camera-vs-sensor latency (Analysis 2)
- [ ] Write and freeze `docs/tool-board-interface.md`; hand it to the Data Acquisition L3 PCB designer (that is you, other hat)
- [ ] Update `AGENTS.md`: how to start the reader, how to send a command, what the page shows

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

#### Tool-board interface (frozen in this lab)

Copy this into `docs/tool-board-interface.md` unchanged and add the electrical notes below it. Data Acquisition L3 implements exactly this on the PCB.

UART 115200 8N1 over USB, one JSON object per line, both directions.

Tool board → RPI, one sample per 10 ms (100 Hz):
```
{"t":123456,"p":45.2,"v":-12.3,"valve":0,"pump":"off","uv":0,"z":112,"alarm":0}
```
`t` ms since boot; `p` kPa on the syringe branch, the cell's only pressure sensor; `valve` 0 = cup, 1 = syringe; `pump` "off" | "suction" | "blow"; `uv` 0/1; `z` mm from VL53L0X or null; `alarm` 1 when the dP/dt interrupt has fired (latched until `clear`).

RPI → tool board:
```
{"cmd":"valve","on":1}
{"cmd":"pump","mode":"blow"}            // "off" | "suction" | "blow"
{"cmd":"dispense","ms":200}             // valve to syringe for ms, then back to cup; requires pump "blow"
{"cmd":"uv","ms":5000,"pose_ok":1}      // refused unless pose_ok=1; LED times out on the board regardless
{"cmd":"stop"}                          // valve off, pump off, uv off
{"cmd":"clear"}                         // clears alarm latch
{"cmd":"status"}
```
Reply to every command: `{"ack":"<cmd>","ok":1}` or `{"ack":"<cmd>","ok":0,"err":"<reason>"}`. Events: `{"ev":"dispense_start","t":…}`, `{"ev":"dispense_end","t":…}`, `{"ev":"alarm","t":…,"dpdt":…}`. The RPI slices curves out of the sample stream using event timestamps.

In this lab `z` is always `null` and `alarm` is always 0 (VL53L0X and the dP/dt comparator arrive with Data Acquisition L3); the fields are present so the RPI parser does not change later.

Dispense logic on the board, language-neutral:
```
on command dispense(ms):
  if pump != blow → ack ok:0 err:"pump"
  valve on → emit dispense_start → wait ms → valve off → emit dispense_end → ack ok:1
```
UV logic on the board:
```
on command uv(ms, pose_ok):
  if pose_ok != 1 → ack ok:0 err:"pose"
  if ms > 10000 → ms = 10000
  led on → ack ok:1 → board timer expires after ms → led off (no RPI message needed)
```

### Simulation

No circuit or network simulation in this lab. The draw.io diagram in `docs/tool-signal-path.drawio` shows the signal path RPI ↔ ESP32-B ↔ valve / pump box / LED / sensors / camera for all three transports, with the latency numbers from Analysis 1 written on the arrows after you have measured them.

### Analysis

Notebook `notebooks/lab2_latency.ipynb` with outputs:

1. **Command latency, three transports.** Send `{"cmd":"valve","on":1}` 100 times per transport (UART, HTTP over the ESP32 AP, MQTT through Mosquitto on the RPI). Measure two things per command: (a) RPI time from send to ack, (b) scope time from the RPI's send to the valve MOSFET gate rising (probe the gate, trigger on the UART TX line or an RPI GPIO you toggle at send). Table per transport: mean, median, p95, max in ms for (a) and (b). One boxplot with three boxes. State which transport the PCB will use and why the number, not the feeling, says so.
2. **Camera vs. sensor latency.** Point the camera at the valve LED or at a phone showing a millisecond clock; fire a dispense; find the frame where the change appears and compare its arrival time on the RPI with the `dispense_start` timestamp. 20 repeats. Table: sensor-event-to-frame delay mean and σ in ms, camera fps at the chosen resolution, MJPEG bitrate in kB/s from `ifconfig`/`ip -s link` counters over 60 s.
3. **Sample integrity.** 10 minutes of UART streaming while the Flask page is open and the camera is streaming: count samples received vs. expected (60 000), list gaps > 20 ms. Report loss in %. This is the baseline Lab 5 compares against.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: Refused UV

With the LED disconnected from its driver (driver output open, meter on the enable line), send `{"cmd":"uv","ms":3000}` and `{"cmd":"uv","ms":3000,"pose_ok":0}`: both must return `ok:0`, enable stays low. Send with `pose_ok:1`: enable goes high, `uv` reads 1 in the samples, and after 3000 ± 50 ms enable returns low without any further message from the RPI. Then send `pose_ok:1` with `ms:60000`: enable must drop at 10 000 ms. Scope screenshot of the enable line for the 3 s case in `docs/`.

#### Test Example 2: Browser dispense with curve

Pump in blow at the Gate A pressure, syringe with resin over the waste cup. Press Dispense 200 ms on the phone. Within 1 s the page shows the p curve sliced from `dispense_start` to `dispense_end` plus 200 ms either side, with the rise, the plateau and the fall visible, and a drop of resin has left the tip. Repeat 5 times; the five curves overlay on one plot in the notebook. Then unplug the ESP32 USB and press Dispense: the page must show "tool board offline" within 2 s, not hang.

#### Test Example 3: Three transports, same command

Run the same 20-command sequence (valve on/off ×5, pump suction/off ×5) over UART, HTTP and MQTT from one script, with the reader logging samples throughout. The valve and pump state fields in the sample stream must follow the commands identically on all three transports; the `docs/test_log.md` entry lists any command that was acked but not reflected in the next 50 ms of samples.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* `docs/tool-board-interface.md` containing the interface above word for word, plus electrical notes (which GPIO class drives what, coil supply, LED driver current, camera power), and a changelog line "frozen 24.10.26".
* Video: the one page on a phone showing MG400 status, p, v, camera image of the tip, and a Dispense button pressed with the curve appearing.
* `data/dispense_curves.csv` with 5 dispenses (columns `cycle, t_ms, p_kpa, valve`), sliced by event timestamps.
* `data/latency_<transport>.csv` ×3 (100 rows each, columns `n, rpi_ms, scope_ms`) and the scope screenshot of one UART command with the MOSFET gate rising.
* Scope screenshot of the LED enable line for a 3 s cure showing the board-side timeout.
* `data/stream_10min.csv` or its summary in the notebook: samples received vs. 60 000, gaps listed, loss in %.
* Photo of the arm with valve, sensors, LED with shroud and camera mounted on the 3D Print L1 holder.

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Repo only. The interface document, the three latency CSVs, `dispense_curves.csv`, the 10-minute stream summary. From Lab 4 on, samples and cycle records go to the shared database in the schema defined there.

### Safety

* The 405 nm LED is never powered outside the cure pose. During bench tests of the driver the LED is aimed into a closed box, goggles on. `pose_ok` is set by the RPI only when the base package reports the robot within 2 mm of the saved cure pose.
* The valve's default state is cup. Test this first: with the ESP32 unplugged, pump in suction, the cup must hold a glass. If it does not, the valve is plumbed backwards; fix it before any resin is loaded.
* Resin: gloves, tip cap on when idle, amber syringe, dispense only over the waste cup or a tag. Cured waste only in the bin. IPA for cleanup.
* Lab 1 rules for the robot still apply: hands out, e-stop within reach, 20 % speed on first runs.

### Components for the next lab

Ordered on 13.10.26 for Lab 3 (course-wide, by the instructor): Digital Ocean credit and one domain for the portal. Nothing physical per team.

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| Digital Ocean credit | course-wide | one droplet shared by the four teams, instructor's account |
| Domain for the portal | course-wide | one name, e.g. `robots.kool.ee`; instructor buys, teams get DNS subpaths `/robot/N/` |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — firmware for the command set with acks and events, RPI reader and command layer, Flask page with camera and curve, HTTP and MQTT variants | 5 p |
| Analysis — latency table and boxplot for three transports with scope verification, camera-vs-sensor delay, 10-minute sample integrity | 5 p |
| Prototype — browser-triggered dispense with its curve, refused UV with board-side timeout, camera on the page | 5 p |
| Documentation — `docs/tool-board-interface.md` frozen and complete, wiring photo and schematic, test log, `AGENTS.md` updated | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `smart-solutions-lab2` 72 h before the defense.**

The defence is online on 27.10.26. The tag deadline is 72 h before it, which is Saturday 24.10.26 — the same weekend as the contact session where the next lab is handed out. Anything that has to be shown live, the robot moving or a print or a measurement, has to be visible on the call, so join from the lab.

* `smart-solutions/lab2/src/` — firmware folder (`firmware/`), RPI reader and command module, Flask app (copied from lab1 and extended), HTTP and MQTT client variants
* `smart-solutions/lab2/data/` — `latency_uart.csv`, `latency_http.csv`, `latency_mqtt.csv`, `dispense_curves.csv`, stream summary
* `smart-solutions/lab2/notebooks/lab2_latency.ipynb` with outputs
* `smart-solutions/lab2/docs/` — `tool-board-interface.md`, `tool-signal-path.drawio` + PNG, wiring schematic and photo, scope screenshots, `test_log.md`, video link
* `AGENTS.md` updated at the root
* Live change at the defense: a different dispense time or a different cure time requested on the spot, run from the page, curve shown.

### Development Log

**TO BE CHARTED — a diary.** One entry per working session, written to yourself, in the language your team works in, and written so that a person who was not there understands it without having to ask. Date first, then who was there, what you tried, what actually happened in numbers, what you decided and why, and what is left open for next time. Entries are added, never edited: if the entry of 18.09 turned out wrong, the entry of 25.09 says so and the old one stays as it was.

Adjectives are not results. "The sensor was noisy" is nothing; "±14 LSB at rest, ±40 LSB with the pump box running" is an entry. Two or three honest sentences per session are enough — but the session with the mistake in it deserves five.

**DD.MM.YY — who was there**
* Did:
* Happened (numbers):
* Decided, and why:
* Open for next time:

### Results

**TO BE CHARTED, at the end.**

* Git repository and tag:
* The three or four numbers this lab produced, with units:
* What we would do differently if we started again on day one:
* What the next lab should know before it starts:

### Feedback

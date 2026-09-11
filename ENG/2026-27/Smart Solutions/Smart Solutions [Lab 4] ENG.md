## Smart Solutions: Lab 4 — Shared database and workflow recorder

**Workload:** 30 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 14.11.26 | **Order date:** 24.11.26 | **Defense:** 08.12.26, online

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the lab folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

Bring all data into one system and make the robot teachable in minutes. Every cycle the cell runs produces one record (section "One assembly cycle", step 7 of the plan): cycle id, team, robot parameters, dispense time, cure time, both pressure curves at 100 Hz, syringe fill estimate, image, outcome. The RPI publishes it over MQTT to Mosquitto on the droplet; a subscriber on the droplet writes it to InfluxDB with a `team` tag. **One bucket, one schema, four teams.** The schema is reproduced below from the course conventions and does not change after this defense; Data Acquisition Lab 4 writes 500 cycles per team into it and Data Acquisition Lab 5 trains on all of them.

The second half is the **workflow recorder**. The operator jogs the robot from the page while watching the nozzle camera, presses Record at each waypoint, picks an action (suction on, suction off, dispense N ms, UV cure N s, blow-off, wait N ms) and saves. Replay runs the cycle. Workflows are JSON files in the repo, so they can be diffed, copied between teams and edited by hand. The Lab 1 teach/replay grows into this; nothing is thrown away.

Around these two: a unified RPI page (control, live sensors, camera, history graphs, CSV/JSON export), a central portal on the droplet showing all four robots at a glance, operator locking so that four people on the portal do not fight over one arm, and an offline buffer on the ESP32 so a WiFi drop loses nothing. The UX test is the acceptance: another team records a working workflow on your station in under 5 minutes without your help.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* Smart Solutions L3: the droplet, VPN addresses, nginx proxy, status page.
* Smart Solutions L2: the tool-board interface (ESP32-B now; the Data Acquisition L3 PCB when it arrives in December, same messages).
* 3D Print L2: tray, jig, waste-cup holder; the 5+5 tray that lets replay run unattended.
* Data Acquisition L2–L3: the sensors' scaling and the `alarm` field from the dP/dt comparator.

**Gives to**
* Data Acquisition L4: the cycle record schema, the MQTT topic and the replay that runs the 500 cycles.
* Data Acquisition L5: the shared bucket all models train on.
* Prototyping M2: the workflow JSON that runs the first complete tag.
* Smart Solutions L5: the page, the lock and the history that the REST API exposes.

### Background Information

* **Mosquitto configuration** — listeners, `password_file`, `allow_anonymous false`, per-user ACL.
  [https://mosquitto.org/man/mosquitto-conf-5.html](https://mosquitto.org/man/mosquitto-conf-5.html)
* **Mosquitto authentication methods** — [https://mosquitto.org/documentation/authentication-methods/](https://mosquitto.org/documentation/authentication-methods/)
* **paho-mqtt (Python client)** — [https://pypi.org/project/paho-mqtt/](https://pypi.org/project/paho-mqtt/)
* **InfluxDB v2 documentation** — buckets, tokens, measurements, tags vs. fields.
  [https://docs.influxdata.com/influxdb/v2/](https://docs.influxdata.com/influxdb/v2/)
* **InfluxDB line protocol** — what a write actually looks like; tag cardinality.
  [https://docs.influxdata.com/influxdb/v2/reference/syntax/line-protocol/](https://docs.influxdata.com/influxdb/v2/reference/syntax/line-protocol/)
* **InfluxDB Python client** — [https://docs.influxdata.com/influxdb/v2/api-guide/client-libraries/python/](https://docs.influxdata.com/influxdb/v2/api-guide/client-libraries/python/)
* **ESP32 LittleFS** — writing and reading files on the ESP32 flash, for the offline buffer.
  [https://randomnerdtutorials.com/esp32-write-data-littlefs-arduino/](https://randomnerdtutorials.com/esp32-write-data-littlefs-arduino/)
* **Flask sessions** — cookie-based session for the operator lock.
  [https://flask.palletsprojects.com/en/stable/quickstart/#sessions](https://flask.palletsprojects.com/en/stable/quickstart/#sessions)
* **Chart.js** — history graphs on the RPI page and the portal. [https://www.chartjs.org/docs/latest/](https://www.chartjs.org/docs/latest/)
* **MQTT QoS and retained messages** — search phrase: "MQTT QoS 0 1 2 retained message explained". QoS 1 for cycle records, QoS 0 for the 100 Hz samples.

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. Lab 3 station (RPI, MG400, tool board, camera, VPN, proxy)
2. Droplet: Mosquitto, InfluxDB 2.x, the portal Flask app, nginx
3. ESP32-B with LittleFS; tool PCB from Data Acquisition L3 when it arrives (same interface, drop-in)
4. 3D Print L2 tray set with 5 dummy glasses, gluing jig, waste cup
5. Digital scale 0.01 g (from the 03.11 order) for the syringe fill ground truth
6. Amber syringe, resin, 0.8 mm tip, 405 nm goggles, gloves
7. `mosquitto_sub`, `influx` CLI, browser dev tools
8. A stopwatch and another team, for the UX test

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Mosquitto on the droplet: listener on the VPN address only (10.0.0.254:1883), one user per team, ACL so team N can publish only under `cell/N/#` and everyone can subscribe to `cell/#`
- [ ] InfluxDB on the droplet: org `narva`, bucket `cell` (one for all teams), a write token per team, a read token for everyone; verify with the CLI
- [ ] RPI publisher: after every cycle, `cell/N/cycle` (QoS 1, the record as JSON), `cell/N/sample` (QoS 0, 100 Hz samples batched per 100 ms during a cycle), `cell/N/status` every 5 s (retained: online, lock holder, last cycle id)
- [ ] Droplet subscriber → InfluxDB: measurement `cycle` (tags `team`, `robot`, `workflow_id`; fields = scalar columns), measurement `sample` (tag `cycle_id`; fields `p_kpa`, `valve`, `uv`); images to `/srv/cell/images/<cycle_id>.jpg` over the same topic base64 or via HTTP PUT to the portal
- [ ] Workflow recorder on the RPI page: jog with the camera in view, Record adds `{pose, action, param}`; list editable (reorder, delete, change N); Save writes `data/workflows/<workflow_id>.json`; Replay runs it and produces one record per run
- [ ] Recorder actions map to the tool-board interface: suction → `pump suction`; blow-off → `pump blow` for 300 ms then `off`; dispense N → `pump blow` + `dispense ms`; cure N → move to the pose, then `uv ms pose_ok=1`; wait N → sleep; each step waits for its ack
- [ ] Cycle record assembly: `cycle_id` = `<team>-<YYYYMMDD>-<nnnn>`; curve sliced by events; `response_ms`, `dpdt_max`, `plateau_kpa`, `auc` computed from the curve; `pick_ok` from the plateau on `v`; image from the camera at the end; `fill_ml_estimate` with `fill_method`
- [ ] Unified RPI page: control + recorder, live p/v plot, camera, last 20 cycles as a table with sparkline, history graphs (cycles per hour, response_ms over time), Export CSV / JSON buttons
- [ ] Central portal on the droplet (grown from the Lab 3 status page): per team cycle count today and total, last record's key fields, last image, fill estimate, online/locked state; one screen, refreshes every 10 s
- [ ] Locking: Take control → session owns the lock; others see view mode (camera, sensors, status live; buttons greyed); Doorbell sends "please release" to the owner's page; admin override with a password from the RPI screen; lock expires after 5 min without a command
- [ ] ESP32 offline buffer: when WiFi/MQTT is down, the last 100 messages go to LittleFS and are replayed in order on reconnect (only for the MQTT variant; on UART there is no loss to buffer)
- [ ] UX test with another team (Test Example 3), then 100 replays of their workflow into the shared bucket

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

Workflow JSON, one step per element:
```
{"workflow_id":"t2-glass-v3","team":2,"speed_pct":40,
 "steps":[
  {"pose":{"x":250,"y":-40,"z":60,"r":0},"action":"move"},
  {"pose":{"x":250,"y":-40,"z":12,"r":0},"action":"dispense","ms":200},
  {"pose":{"x":180,"y":30,"z":8,"r":0},"action":"suction","on":1},
  {"pose":{"x":250,"y":-40,"z":10,"r":0},"action":"blowoff"},
  {"pose":{"x":250,"y":-10,"z":45,"r":0},"action":"cure","s":10},
  {"pose":{"x":250,"y":-40,"z":60,"r":0},"action":"wait","ms":500}
 ]}
```
Replay logic:
```
for step in workflow: MovJ(pose) → wait until pose reached (poll ≤ 2 mm) → run action → wait ack/event → next
on any ok:0 or timeout → stop command to the board → robot stop → record with notes = error → release lock
```

### Simulation

A draw.io data-flow diagram in `docs/data-flow.drawio` (PNG beside it): tool board → UART → RPI reader → ring buffer → cycle assembler → MQTT publisher → `wg0` → Mosquitto (droplet) → subscriber → InfluxDB `cell` bucket → portal query → browser. A second lane for the camera image, a third for the retained status topic. Mark on each arrow: message rate, size per message, QoS, and what happens when that link is down (buffered where, lost where, for how long). Under it, the lock state machine: free → held(owner, expires) → free, with doorbell, override and timeout as transitions.

### Analysis

Notebook `notebooks/lab4_pipeline.ipynb` with outputs, reading from InfluxDB, not from local files:

1. **End-to-end record latency.** For 100 cycles, the time from `dispense_end` on the tool board to the record being queryable on the droplet. Table: mean, p95, max in ms. Where does the time go (UART, assembly, MQTT, subscriber, InfluxDB write)?
2. **Sample completeness.** For the same 100 cycles, samples stored in `sample` per cycle vs. expected (cycle duration × 100 Hz). Loss in %; list cycles with gaps > 50 ms.
3. **Offline buffer.** Pull the RPI's WiFi for 30 s during MQTT streaming, 5 times. For each: messages buffered on the ESP32, messages replayed, ordering preserved (yes/no), messages lost. Table. Show that 100 messages covers a 30 s drop at the chosen publish rate, and state the drop length at which it does not.
4. **Portal query cost.** Time the portal's per-team summary query for 1, 4 and (simulated by tag) 12 teams. Table in ms; say when the 10 s refresh would need caching.
5. **UX test result.** Time to first saved workflow for the visiting team, number of questions asked, number of failed replays before the first good one. One line per visiting team.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: Lock behaviour with two phones

Phone A takes control; phone B opens the same page: B sees the camera and the numbers updating, every button greyed, and "held by A, 4:32 left". B presses the doorbell: A's page shows the request within 5 s. A does nothing for 5 minutes: the lock releases, B can take it. A takes it back, and the admin override from the RPI screen removes it immediately. Every transition is a line in the RPI's `data/lock_log.csv` (timestamp, event, from, to).

#### Test Example 2: Record round trip

Run one replay. Within 2 s, `mosquitto_sub -t 'cell/N/cycle'` on the droplet shows the JSON, `influx query` returns the same `cycle_id` in the `cell` bucket with all scalar fields, the image exists on the droplet, and the portal card for team N shows the new count and the new image. Then stop the droplet subscriber, run 5 cycles, start it again: all 5 records must appear (Mosquitto persistence + QoS 1), none duplicated.

#### Test Example 3: Another team records a workflow

A member of another team who has never used your station sits at the RPI with a phone. Start the stopwatch. They jog, record dispense-over-waste-cup, pick a glass from slot 1, place it in finished slot 1, blow-off, save, replay. Stop the stopwatch when the replay finishes with the glass in the finished slot. Under 5 minutes, no questions answered by you (write them down instead). Their workflow file goes in your repo under `data/workflows/` with their team number in the id, and 100 replays of it go into the shared bucket.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* `data/workflows/<other-team>-<name>.json` recorded on your station by another team, plus the stopwatch time and the question list in `docs/ux_test.md` (under 5 minutes).
* 100 cycles from that workflow in the shared `cell` bucket with `team = N`, each with both curves in `sample` and an image; the same 100 as `data/cycles.csv` + `data/curves/` + `data/images/` in the repo.
* Screenshot of the portal showing all four teams' cards with counts, last record time, last image and fill estimate.
* `data/lock_log.csv` from Test Example 1 and a video of two phones showing take control, view mode, doorbell, timeout, override.
* `data/offline_buffer.csv` from the five WiFi pulls (buffered, replayed, lost, ordered).
* The notebook with the five analyses, querying InfluxDB.

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Shared database and repo. This is the cycle record every team writes from now on; reproduce it in `docs/cycle-record.md` unchanged.

CSV columns (one row per cycle) in `data/cycles.csv`; curves in `data/curves/<cycle_id>.csv` (columns t_ms, p_kpa); images in `data/images/<cycle_id>.jpg`:

```
cycle_id, team, timestamp_utc, workflow_id, robot_speed_pct, pump_setpoint_kpa, dispense_ms, cure_s, tip_mm,
syringe_ml_nominal, fill_ml_estimate, fill_method (scale|count), dose_mg (if weighed, else empty),
pick_ok (0|1|empty), dispense_ok (0|1), clog_alarm (0|1), z_mm, response_ms, dpdt_max, plateau_kpa, auc,
image_file, notes
```
InfluxDB: measurement `cycle` with tags `team`, `robot`, `workflow_id` and the scalar columns as fields; measurement `sample` with tag `cycle_id` and fields `p_kpa`, `valve`, `uv` at 100 Hz. Same bucket for all four teams.

Fill level: `fill_ml_estimate` comes from the scale every 25 cycles (`fill_method = scale`) or from nominal volume minus counted dispenses at the weighed mean dose (`count`). Whether the curve can predict it is Data Acquisition L5's question; if it cannot, the same record still carries the clog and pick labels. Setting out to find one thing and finding another is ordinary engineering; a null result is graded the same as a positive one.

Also in the repo: `data/workflows/*.json`, `data/lock_log.csv`, `data/offline_buffer.csv`.

### Components for the next lab

Ordered on 24.11.26 for Lab 5: nothing for this course. The AtomS3/AtomS3R and battery batch on that order is for real assembly cycles and is shared by all courses.

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| — | 0 | no Smart Solutions items; use the shared tag batch for real cycles |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — publisher, droplet subscriber, InfluxDB schema, recorder and replay, unified page, portal, lock, ESP32 buffer, workflow JSONs | 5 p |
| Analysis — record latency breakdown, sample completeness, offline buffer table, portal query cost, UX timing | 5 p |
| Prototype — another team's workflow in under 5 minutes, 100 cycles in the shared bucket with curves and images, portal showing four teams, lock with two phones | 5 p |
| Documentation — `docs/cycle-record.md`, `docs/data-flow.drawio`, `docs/ux_test.md` with questions asked, MQTT topic and ACL table, `AGENTS.md` | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `smart-solutions-lab4` 72 h before the defense.**

The defence is online on 08.12.26. The tag deadline is 72 h before it, which is Saturday 05.12.26 — the same weekend as the contact session where the next lab is handed out. Anything that has to be shown live, the robot moving or a print or a measurement, has to be visible on the call, so join from the lab.

* `smart-solutions/lab4/src/` — RPI app (copied from lab3 and extended: recorder, publisher, lock), droplet subscriber, portal app, ESP32 firmware with the buffer
* `smart-solutions/lab4/data/` — `cycles.csv` (≥100 rows), `curves/`, `images/`, `workflows/`, `lock_log.csv`, `offline_buffer.csv`
* `smart-solutions/lab4/notebooks/lab4_pipeline.ipynb` with outputs
* `smart-solutions/lab4/docs/` — `cycle-record.md`, `data-flow.drawio` + PNG, MQTT topics and ACL table, InfluxDB token handling (no tokens in git), `ux_test.md`, screenshots, video link
* `AGENTS.md` updated: how to record, replay, query the bucket, take and release the lock
* Live change at the defense: the instructor asks for a different dispense time or a different finished slot; you edit the workflow on the page, replay, and the new record shows on the portal within the 10 minutes.

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

## Smart Solutions: Lab 5 — Fault tolerance, REST API and an agent that runs the cell

**Workload:** 34 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 05.12.26 | **Order date:** 06.01.27 | **Defense:** 19.01.27, online

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the lab folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

The RPI does five things at once: Flask, the MG400 socket, the tool-board UART, MQTT, the camera re-stream. One of them stalls or dies. The cell must notice, keep the tag in progress from being ruined, and come back without a human at the keyboard. **Part A** measures what a €50 computer running Python actually does under that load (the GIL, blocking calls, lost samples), then designs around it: one process per critical service, queues between them, a timeout on every socket, a heartbeat from each process, a supervisor that restarts what died. Safe state is physical and is proven with the vacuum sensor, not with a log line: pump off, valve unpowered → cup branch, LED enable low.

**Part B** exposes the station as a REST API an agent can use: `/status`, `/cycle`, `/workflow`, `/history`, `/export`, and `/api`, a README endpoint that describes every endpoint well enough for an agent to run the whole cycle from it. The API is reachable through the portal at `robots.kool.ee/robot/N/api/`, protected by a time lock the local operator activates on the RPI screen, and every call is written to an audit log. The demo is the point of the semester: an agent (Claude Code, Codex, whatever the team uses) is given only the API description and asked to assemble one tag through the portal. When a pick fails, the agent retries — the failure is seen by the camera check, since the cup has no sensor.

This is the last lab before Prototyping. What the RPI cannot do, measured here, is what the integration project's install script has to work around.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* Smart Solutions L4: unified page, recorder/replay, MQTT publisher, lock, shared bucket.
* Data Acquisition L3: the tool PCB with hardware safe state (LED enable low by default, valve unpowered = cup) and the `alarm` field.
* Data Acquisition L5: the three-way dispense classifier (joblib/pickle) loaded in the station app, and the camera check that decides `pick_ok`.
* Smart Solutions L3: portal path and VPN.

**Gives to**
* Prototyping M2–M5: the API the integrated cell is driven through, the fault log that sizes the install script, the supervisor that a cloned SD card boots into.

### Background Information

* **Python `multiprocessing`** — processes, `Queue`, `Pipe`, why threads do not help here.
  [https://docs.python.org/3/library/multiprocessing.html](https://docs.python.org/3/library/multiprocessing.html)
* **Socket timeouts** — `settimeout`, what `recv` does on a dead peer without one.
  [https://docs.python.org/3/library/socket.html#socket.socket.settimeout](https://docs.python.org/3/library/socket.html#socket.socket.settimeout)
* **The GIL** — search phrase: "Python GIL explained CPU-bound vs I/O-bound threads". One process, one interpreter, one thread running Python at a time.
* **systemd service units and watchdog** — `Restart=`, `WatchdogSec=`, `sd_notify`; one unit per process.
  [https://www.freedesktop.org/software/systemd/man/latest/systemd.service.html](https://www.freedesktop.org/software/systemd/man/latest/systemd.service.html)
* **Flask blueprints** — keeping `/api/...` separate from the page routes.
  [https://flask.palletsprojects.com/en/stable/blueprints/](https://flask.palletsprojects.com/en/stable/blueprints/)
* **OpenAPI specification** — a machine-readable description of the API; the `/api` README can be generated from it or written by hand in the same spirit.
  [https://spec.openapis.org/oas/latest.html](https://spec.openapis.org/oas/latest.html)
* **REST API design** — search phrase: "REST API design status codes idempotent POST vs PUT long-running operations polling". A cycle takes 30 s; `POST /cycle` must return immediately with an id to poll.
* **Coding agents** — the documentation of the agent your team uses (Claude Code, Codex CLI, Hermes). Search phrase: "<agent name> docs give it a URL and a task". You only need to know how to hand it a text file and watch what it calls.

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. Lab 4 station (RPI, MG400, tool PCB or ESP32-B, camera, VPN, portal, shared bucket)
2. Data Acquisition L5 pick classifier file and its feature list
3. `htop`, `vmstat`, `iostat`, `journalctl`, `systemd-analyze`
4. Oscilloscope or the tool board's own 100 Hz stream for the safe-state timing
5. Syringe with resin over the waste cup, dummy glasses, one real AtomS3/AtomS3R tag for the agent demo
6. A coding agent on a laptop with access only to `robots.kool.ee/robot/N/api/` and its README
7. `curl`, `ab` or `wrk` for load, `mosquitto_sub`, `influx`
8. draw.io

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Baseline measurement (Analysis 1): the Lab 4 single-process app under load; log lost samples, Flask response time, MG400 poll gaps. Keep the numbers, this is the before
- [ ] Split into processes: `mg400d` (socket, poll, motion queue), `toold` (UART reader, command/ack, ring buffer), `mqttd` (publisher with disk-backed queue), `camd` (MJPEG re-stream), `web` (Flask, API). Queues between them; shared state as a small JSON/SQLite the `web` process reads
- [ ] Timeouts: MG400 socket 2 s → state `mg400: lost`, rest carries on; UART 500 ms without a sample → `tool: lost`; MQTT connect 5 s, publish to disk queue when down; camera 3 s → placeholder frame
- [ ] Heartbeats: every process writes `name, timestamp` to a heartbeat file or socket once a second; a supervisor (systemd units with `Restart=always` and `WatchdogSec`, or your own) restarts anything silent for 5 s and logs it
- [ ] Safe state on every fault: `stop` to the board, robot stop, lock released, cycle record written with `notes = fault:<service>`. Verify with the three cable pulls (Analysis 2) with the syringe over the waste cup
- [ ] REST API blueprint under `/api/`: `GET /api` (README, markdown or JSON), `GET /status`, `POST /cycle` (workflow_id, overrides) → `{cycle_id}` then `GET /cycle/<id>` to poll, `GET|POST /workflow`, `GET /history?n=`, `GET /export?format=csv|json&from=&to=`; JSON in, JSON out, HTTP codes that mean something (202 accepted, 409 locked, 423 time lock, 503 service lost)
- [ ] Pick retry: `/cycle` runs the workflow; after each lift the camera frame goes through the pick check; `pick_ok = 0` → blow-off, retry up to 3 times from the next tray slot, then `dispense_ok`/`pick_ok` recorded; the count of retries in the response
- [ ] Time lock: a button on the RPI screen "Enable remote API for 30 min" (configurable 5–120); outside that window every `/api/` call except `GET /api` and `GET /status` returns 423 with the reason; the remaining time on the RPI screen and in `/status`
- [ ] Audit log `data/api_audit.csv`: timestamp, source IP (X-Forwarded-For through nginx), lock holder, method, path, body hash, response code, duration ms; rotated daily; also shown as the last 50 lines on the page
- [ ] Portal: nginx location `/robot/N/api/` → RPI `/api/`, no buffering needed, 60 s read timeout; the portal card shows "API armed until hh:mm"
- [ ] Agent demo (Test Example 3): write the README, hand it to the agent, one tag, first attempt; keep the transcript and the audit log
- [ ] Fault log notebook (Analysis 3), `AGENTS.md` rewritten so that it points at `/api` and the process layout

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

Cycle endpoint logic:
```
POST /cycle: check time lock → check operator lock (API caller becomes holder) → check all services alive
  → queue workflow to mg400d → return 202 {cycle_id}
mg400d: run steps; after suction step: classify(v curve) → if not ok: blowoff, next slot, retry ≤ 3
  → on completion or fault: write record, publish, release lock
GET /cycle/<id>: state (queued|running|done|fault), step index, retries, record when done
```

### Simulation

A draw.io diagram in `docs/process-architecture.drawio` (PNG beside it): the five processes as boxes, queues as arrows with their direction, max length and what is dropped when full; the heartbeat path to the supervisor; the sockets with their timeouts written on them (MG400 2 s, UART 0.5 s, MQTT 5 s, camera 3 s); the safe-state chain from any fault to `stop` on the board and the physical result (valve unpowered → cup, pump off, LED enable low). A second sheet: the API request path from the agent's laptop through the portal, the time lock and the operator lock to `mg400d`, with the HTTP codes on each refusal.

### Analysis

Notebook `notebooks/lab5_faults.ipynb` with outputs:

1. **RPI limits, before and after.** Load case: Flask serving the full page to 3 browsers, camera re-stream to 2, UART at 100 Hz, MG400 poll at 2 Hz, MQTT publishing, for 10 minutes. Before (Lab 4 single process) and after (separate processes). Table: samples expected vs. received (60 000) and loss %; Flask response time p50/p95/max in ms; longest MG400 poll gap in ms; CPU % per process from `top`; longest single Flask block measured by a 10 Hz ping from a second machine. Then push it: add browsers until loss exceeds 1 %; report the number of clients where the RPI stops being enough.
2. **Cable pulls, three cases, three repeats each.** (a) ESP32/tool-board USB pulled during a 500 ms dispense over the waste cup; (b) MG400 LAN pulled mid-move; (c) RPI WiFi turned off during a cycle. For each: time from the pull to `state = lost` on the page, time to physical safe state (from the vacuum sensor trace: the cup branch reads vacuum or atmosphere as expected within N ms; for the USB pull the board's own stream stops, so read `v` after re-plug and film the valve), time to full recovery after re-plug, whether the tag/glass in progress was ruined (resin where it should not be, glass dropped), what the record says. Table 3 × 3 with times in ms/s.
3. **Fault log over one week.** `data/fault_log.csv` (service, start, end, duration_s, cause if known, load at the time from Analysis 1's metrics) written by the supervisor. Plot faults per service per day; mean and max recovery time; correlation of faults with client count or CPU; one paragraph on where the RPI stops being enough and what the integration project should change (a second RPI, a different camera path, fewer clients).
4. **API latency through the portal.** 100 × `GET /status` local, via VPN, via portal; 10 × full `POST /cycle` → done through the portal. Table p50/p95 in ms and s.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: Kill each process

With a cycle running, `kill -9` each of the five processes in turn (five separate cycles). Expected per process: `mg400d` → robot stops within 2 s, board `stop` sent, record with `fault:mg400d`, restart within 5 s, page shows the gap; `toold` → the board is unaffected and finishes its own timed action, valve back on cup by its own timer; robot stops within 2 s of the missing heartbeat; restart, stream resumes; `mqttd` → cycle completes, records queue to disk, publish on restart, none lost; `camd` → placeholder frame, cycle unaffected; `web` → the cycle in progress completes, page back in 5 s. Each case one line in `docs/test_log.md` with the measured times.

#### Test Example 2: Time lock and audit

From a laptop outside the lab: `GET /api` and `GET /status` work; `POST /cycle` returns 423 with the reason and the RPI screen shows "remote API off". Operator enables 10 min on the screen; `POST /cycle` returns 202; at minute 10 the next call returns 423 again while the running cycle finishes. `data/api_audit.csv` holds every one of these calls with source IP, code and duration, and the page shows them.

#### Test Example 3: The agent assembles one tag

A fresh agent session on a laptop, network access limited to `https://robots.kool.ee/robot/N/api/`. The prompt is the API README's URL and one sentence: "Assemble one tag using this API and report the cycle id." No other help. The agent must find the workflow list, choose the glass workflow, post a cycle, poll it, handle a `pick_ok = 0` retry if one happens, and report the id. Film the robot and the terminal side by side; keep the agent transcript in `docs/agent_transcript.md` and the audit log slice for the run. If the agent fails, the failure is graded as documentation feedback: fix the README, run again, keep both transcripts.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* Video: agent terminal and robot side by side, one tag assembled through the portal on the first attempt of the final run; `docs/agent_transcript.md` and the matching lines of `data/api_audit.csv` (every call, in order).
* `data/cable_pulls.csv` (3 cases × 3 repeats: `case, rep, t_lost_ms, t_safe_ms, t_recover_s, tag_ruined, record_notes`) and the vacuum-sensor trace `data/curves/pull_usb_<rep>.csv` showing the cup branch after the USB pull, with a video of the valve during the pull.
* `data/rpi_limits.csv` before/after with the client count at which loss passes 1 %.
* `data/fault_log.csv` covering at least 7 days of the station being on, and the notebook's per-service plot.
* `data/api_audit.csv` with the time-lock refusals (423) from Test Example 2.
* Screenshot of `GET https://robots.kool.ee/robot/N/api` returning the README, and of the portal card showing "API armed until hh:mm".
* The classifier file loaded on the RPI (path in `docs/`) and at least one cycle in the shared bucket whose `notes` records a retry decided by it.

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Shared database and repo. Cycle records from every API-driven cycle go to the shared bucket in the Lab 4 schema, with `notes` carrying `fault:<service>` or `retry:<n>` where applicable. Repo: `api_audit.csv`, `fault_log.csv`, `cable_pulls.csv`, `rpi_limits.csv`, the pull traces, `docs/api.md` (the same text `GET /api` returns), `docs/agent_transcript.md`.

### Safety

* Cable-pull tests only with the syringe over the waste cup and no tag in the jig. Never pull the tool-board USB with the LED on; if the LED is on when the host disappears, the board's own timeout ends it, but you do not test that with your eyes in the cone. Goggles on.
* Before the first `kill -9` on `mg400d`, check that the MG400 e-stop is within reach and the robot speed is 20 %.
* The remote API can start the robot with nobody at the table. The time lock exists for that reason: the local operator enables it, looks at the workspace, and stays. An armed API with an empty room is a rule violation, not a feature.
* Lab 1 and Lab 2 rules remain: hands out of the workspace during motion, valve default state verified after any wiring change, resin handling with gloves and IPA.

### Components for the next lab

Ordered on 06.01.27; the semester-2 list is handed out on 16.01.27. For the integration project:

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| Spare SD cards, 32 GB | 2 | one clone of the station image, one blank for the install-script test |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — five-process layout with queues, timeouts and supervisor; API blueprint with all endpoints; time lock; audit log; classifier in the retry path | 5 p |
| Analysis — before/after RPI limits with the client count where it breaks, 3 × 3 cable-pull table with sensor evidence, 7-day fault log, API latency through the portal | 5 p |
| Prototype — agent assembles one tag on the first attempt through the portal; every kill and pull ends in physical safe state and recovers without a keyboard | 5 p |
| Documentation — `/api` README an agent could use without help (proved by the transcript), process diagram, test log, `AGENTS.md` pointing at the API | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `smart-solutions-lab5` 72 h before the defense.**

The defence is online on 19.01.27. The tag deadline is 72 h before it, which is Saturday 16.01.27 — the same weekend as the contact session where the next lab is handed out. Anything that has to be shown live, the robot moving or a print or a measurement, has to be visible on the call, so join from the lab.

* `smart-solutions/lab5/src/` — the five process modules, supervisor or systemd unit files (`mg400d.service` etc.), Flask app with the `api` blueprint, classifier loader
* `smart-solutions/lab5/data/` — `api_audit.csv`, `fault_log.csv`, `cable_pulls.csv`, `rpi_limits.csv`, `curves/pull_usb_*.csv`
* `smart-solutions/lab5/notebooks/lab5_faults.ipynb` with outputs
* `smart-solutions/lab5/docs/` — `api.md`, `process-architecture.drawio` + PNG, `agent_transcript.md`, `test_log.md`, screenshots, video links
* `smart-solutions/lab5/models/` — the classifier file or a precise reference to it in the Data Acquisition L5 folder
* `AGENTS.md` rewritten around the API
* Live change at the defense: the instructor gives the agent a different instruction (another slot, a different dispense time, a different tag orientation) and the agent must run it through the API within the 10 minutes, with the audit log shown afterwards.

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

## Smart Solutions: Lab 1 — The chain

**Workload:** 28 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 12.09.26 | **Order date:** 22.09.26 | **Defense:** 06.10.26, online

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the lab folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

Three boxes that each work are not a system. The Data Acquisition team has an Atom that sends a letter when you press a button. The 3D Printing team has a pen holder on the robot's flange. The robot has a TCP port that accepts motion commands. None of that draws anything. The system is the part between them, and that part is yours: **press a letter on the Atom, and the MG400 draws it.**

The chain runs over a network you build. Not a laptop plugged into a robot — a router with a subnet for the robots, addresses that stay where you put them, the WiFi the Atom joins, a firewall, and a route already waiting for the VPN tunnel that arrives in Lab 3. This is where subnets, the routing table and NAT actually live, so it is where they get learned. Draw the address plan on paper before anything is plugged in; most of week one is that drawing being wrong.

The code starts on your own laptop, because that is fast: connect to the robot, jog it, read its position, switch the pump box, receive the letter, turn a letter into a path. Then it moves off your laptop onto a machine that stays in the lab — a spare laptop or PC with no IDE on it, a static address on the robot subnet, and everything starting on boot without anyone logging in. Code that runs where you wrote it is not the same as code that runs. The station serves one page: jog, teach a pose, go to a pose. A Samsung phone on a stand at the table edge shows that page full-screen, with buttons big enough for a thumb. The operator never touches a keyboard.

There is no Raspberry Pi this year. Its jobs are split three ways and each lands somewhere better: the router carries the network, the Digital Ocean droplet (Lab 3) carries what has to be up when nobody is in the room, and the ESP32 on the tool is the cheap local logic unit — the constrained processor that serves several peripherals at once in real time. The station is just the box that talks to the robot and serves the page.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* Instructor: the base MG400 Python package (tagged git URL, README, `AGENTS.md`, CLI), the MG400 with suction kit and mini vacuum pump box, the router with its admin access, a Samsung phone with a stand, a USB-C to Ethernet adapter, LAN cables.
* Data Acquisition L1: the letter, as one message on a channel you agree with them in week one — for example one JSON line `{"letter":"A"}`. Agree the channel before either of you writes code for it.
* 3D Printing L1: the pen holder that gives, on the flange. Until it exists, a marker taped to the flange draws the square with the given routine.

**Gives to**
* Data Acquisition L1: the pump box switched to suction and blow from your station, from week two, so they have a second pressure source.
* Smart Solutions L2: the station app and the package layer the tool board plugs into.
* Data Acquisition L4: the station with teach, save and replay that later runs the data collection.
* All teams' agents: `AGENTS.md`.

### Background Information

* **Dobot MG400 TCP/IP protocol** — Dobot MG400 TCP/IP protocol document (Dobot GitHub, TCP-IP-Protocol). Ports 29999 (dashboard: EnableRobot, ClearError, DO, GetPose) and 30003 (motion: MovJ, MovL, jog). The base package wraps this; read the document to understand what the package does, and to find its bugs.
* **IPv4 subnetting** — search phrase "IPv4 subnet mask gateway explained CIDR /24". You need: address, mask, network, broadcast, gateway, and which packets need a gateway and which do not.
* **Router configuration** — search phrase "router DHCP reservation static lease subnet firewall rule". Whatever router is on the shelf, its manual has these four things; find them before the session.
* **Installing a Python package from git with pip** — tagged URLs, why the tag matters: https://pip.pypa.io/en/stable/topics/vcs-support/
* **Flask quickstart** — routes, templates, JSON responses: https://flask.palletsprojects.com/en/stable/quickstart/
* **Starting a service on boot** — search phrase "systemd service unit run python on boot" for a Linux station, or the equivalent for whatever OS the spare machine runs.
* **Full-screen browser on Android** — search phrase "Android kiosk mode fullscreen browser". The panel must survive a screen timeout and a reboot.
* **Dobot mini vacuum pump box** — search phrase "Dobot vacuum pump box MG400 I/O wiring suction blow". Two DO lines switch it; read the manual for the exact terminals before wiring.
* **draw.io** — for the network diagram: https://app.diagrams.net

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. MG400 with Dobot suction kit (lifting nozzle, φ13 or φ16 cup) and mini vacuum pump box (24 V, I/O controlled)
2. A router per team, or one router with a subnet per team
3. The station: a spare laptop or PC that stays in the lab, with a USB-C to Ethernet adapter if it has no port
4. A Samsung phone with a stand and a charger, as the panel
5. AtomS3 from the Data Acquisition team, sending the letter
6. Base MG400 Python package (instructor's tagged git URL)
7. Python 3.11+, `venv`, pip, Flask
8. Git, the team repo with `AGENTS.md`
9. draw.io
10. An AtomS3 dummy tag or any 24×24 mm object with a flat top, and a tray from the shelf, for the first pick
11. The pen holder from 3D Printing L1; until then, a marker and masking tape

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] The address plan on paper: every device, its interface, its address, mask and gateway, and which packets cross which link. In draw.io, before a cable is plugged in.
- [ ] The router: a subnet for the robots, DHCP reservations so the MG400 and the station keep the addresses you gave them, the WiFi the Atom joins, the firewall, and a route left ready for the Lab 3 tunnel.
- [ ] Laptop talks to the MG400: connect, enable, clear error, jog each axis, read position, DO on and off, from the package CLI first and then from your own code.
- [ ] Laptop talks to the Atom: the letter message arrives on the agreed channel and is logged with a timestamp.
- [ ] Letter → motion: at least three letters, the team's initials, as paths the robot draws with the pen. Where the paper is, what the pen-down Z is, what happens when the robot is not ready — all yours.
- [ ] The pump box on two DO lines: suction, blow, off, from your own code; the Data Acquisition team can ask for it from week two.
- [ ] Move it off your laptop: the same code on the station, no IDE, static IP on the robot subnet, starting on boot without a login.
- [ ] The station page: jog buttons (X/Y/Z/R, step 1/10/50 mm), saved-position list with Go, Teach and Delete, pump buttons, a status line.
- [ ] The phone is the panel: full-screen browser on the page, on the stand at the table edge, surviving a screen timeout and a reboot.
- [ ] First pick: teach `above_source`, `source`, `above_finished`, `finished`; replay lifts a tag and puts it down.
- [ ] `AGENTS.md` in the repo root: what the system is, how to start it, where the base package README is, how to send a letter without the Atom.
- [ ] Every fix to the base package as a pull request to the instructor's repo, linked from `docs/`.
- [ ] Tag `smart-solutions-lab1` 72 h before 06.10.

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

### Simulation

The simulation in this lab is the network diagram, and it is done twice. Once before anything is plugged in: every device, interface, address, mask and gateway, and an arrow for every packet the letter causes — Atom to station, station to robot, station to phone — with the link each one crosses. Then again after the build: read the routing table on the router and on the station and compare, line by line, with the drawing. Every difference is either a mistake in the drawing or a mistake in the network, and you say which. Both versions go in `docs/network.drawio` and `docs/network.md`.

### Analysis

1. **Address plan** (`docs/network.md`): a table — device, interface, address, mask, gateway, and one line on why. Then the routing table of the router and of the station, pasted as text, with each line explained.
2. **Letter latency** (`docs/latency.csv`, `notebooks/lab1_chain.ipynb`): thirty presses. For each: the Atom's send timestamp, the station's receive timestamp, the timestamp of the first motion command sent to the robot. Mean, max and spread for each hop. Which hop is the slow one?
3. **Letter paths** (`docs/letters.md`): the three letters as waypoint lists, the pen-down Z and how it was found, the drawn result measured with a ruler at four points against the intended size.
4. **Boot test** (`docs/boot.csv`): the station power-cycled five times; time from power on to the page loading on the phone; anything that did not come up.
5. **First pick** (`docs/pick_test.csv`): ten picks at 20 % speed; picked, placed, notes.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: The drawing matches the table

The routing table on the station and on the router agree with the diagram in `docs/network.md`, line by line. Then unplug the robot's cable: the diagram must predict which page function stops working, and it does.

#### Test Example 2: Letter to motion under one second

Press a letter on the Atom. Pass: the first motion command reaches the robot within 1 s, ten times out of ten, from the timestamps in `docs/latency.csv`.

#### Test Example 3: The station comes up alone

Power the station off and on. Pass: within 90 s, the page loads on the phone, the robot status shows connected, and nobody has logged in or typed anything. Five times out of five.

#### Test Example 4: Robot not ready

Disable the robot, then press a letter. Pass: the page shows why nothing happened, nothing moves, and the station does not crash or hang. Enable the robot: the next press draws.

#### Test Example 5: Ten of ten

From the four taught poses, replay lifts a dummy tag from the source and places it in the finished slot, 10 of 10 at 20 % speed, with a video of one full round.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* Video: a letter pressed on the Atom, the MG400 drawing it with the printed holder, in one take.
* `docs/network.md` with the address plan, both routing tables and the before/after diagrams.
* `docs/latency.csv` with thirty rows and the hop-by-hop summary in the notebook.
* Video of the station booting to the page on the phone with no login.
* `docs/pick_test.csv` with ten rows and the video of one round.
* `AGENTS.md` verified: another team's agent starts your system from it, and their transcript is in `docs/`.

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Repo only. The saved positions (`data/positions.json`) and the latency CSV are read by Lab 2 and by the Data Acquisition team in Lab 4; keep the file names.

### Safety

* The MG400 workspace is a 440 mm radius; nobody's hands inside it while a command is pending. The person at the phone announces "moving" before every replay.
* The e-stop on the MG400 base is the only stop you trust. The Stop button on the page is a convenience — test it, but keep a hand near the e-stop during every first run of a new sequence.
* First run of any new letter or sequence at 20 % speed, without a tag, with the pen or the cup 20 mm above the surface.
* The pump box runs at 24 V; wire the DO lines with the robot disabled and the box unplugged.
* Router admin password changed from the default on day one, and written in the team's password store, not in the repo.

### Components for the next lab

Order goes out on 22.09.26. Quantities per team.

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| M5 Atom Lite or AtomS3 (second unit, on the tool) | 1 | The first stays on the Data Acquisition breadboard |
| Nozzle camera, M5 AtomS3R-CAM or AI-Thinker ESP32-CAM | 1 | MJPEG over WiFi either way |
| 3/2 valve, direct-acting, spring return, vacuum-rated, 24 V | 1 | Common ← pump, NO → cup, NC → syringe; under 100 g |
| 4 mm push-in fittings | 4 | For the valve and the two branches |
| 4 mm PU tube | 1 m | |
| Logic-level MOSFET module | 3 | Valve, pump box lines, LED enable |
| 405 nm LED 1–3 W on star heatsink | 2 | One spare; never 365 nm |
| Constant-current LED driver | 1 | Matched to the LED current |
| USB cables (station ↔ Atom, station ↔ camera for power) | 2 | |
| 405 nm goggles | 2 | At the table whenever the LED is powered |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — the station app, the letter paths, the router configuration exported, the package layer | 5 p |
| Analysis — address plan with both routing tables explained, hop-by-hop latency, boot and pick tables | 5 p |
| Prototype — a letter pressed on the Atom is drawn by the robot; the station boots alone to the phone; 10 of 10 picks | 5 p |
| Documentation — network diagrams before and after, `AGENTS.md` proven by another team's agent, this README | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `smart-solutions-lab1` 72 h before the defense.**

The defence is online on 06.10.26. The tag deadline is 72 h before it, which is Saturday 03.10.26 — the same weekend as the contact session where the next lab is handed out. Anything that has to be shown live, the robot moving or a print or a measurement, has to be visible on the call, so join from the lab.

The tagged repo must contain, under `smart-solutions/lab1/`:
* `src/`: the station app, the letter paths, the pump box control, the boot configuration.
* `config/`: the router configuration exported, with the password removed.
* `data/positions.json`, `docs/latency.csv`, `docs/boot.csv`, `docs/pick_test.csv`.
* `notebooks/lab1_chain.ipynb` with outputs.
* `docs/`: `network.drawio`, `network.md`, `letters.md`, the videos, the other team's agent transcript.
* `README.md`: this document, filled in.
* `AGENTS.md` at the repo root.

Live change at the defense: the instructor asks for a fourth letter, or moves the paper 50 mm, or renames a pose. The team makes the change on the station — not on a laptop — and the robot draws it during the session.

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

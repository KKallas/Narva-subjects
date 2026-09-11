# Preparation checklist 2026/27 — what must be done and tested before each handout

Written 09.09.26. Companion to `LAB_CONVENTIONS.md`. Two kinds of item:

* **DO** — something to build, buy, decide or write.
* **TEST** — something the instructor must run to completion himself before the document is handed out. A lab whose day-one activity has never been executed by the instructor is not ready, regardless of how good the text is.

Doc-edit items marked **[plan]** implement the agreed changes: handover packets and receipts, the Google Docs development log, seeded faults, the hour budget, the swap exercise, the PCB fit check.

---

## 0. Critical path — the next 14 days

The first handout is 11.09, in two days. Everything in this block is blocking.

| Due | Item | Blocks |
|:--|:--|:--|
| 09.09 | **DO** Buy the Gate A bench set: 405 nm resin, amber syringes with 0.6/0.8/1.2 mm tips, one 405 nm LED, goggles | Gate A, 3D L1 boss check, SS L2, DA L4 |
| 10.09 | **DO** Decide items 1, 5 and 6 of "Decisions only you can make" (pump box owner, base package scope + repo write access, UV LED power class) | Base package, 3D L1, SS L1 |
| 10.09 | **TEST** Base MG400 package on a real robot end to end: connect, enable, clear error, jog, MovJ, MovL, read position, DO on/off, stop | 3D L1, SS L1, DA L1 |
| 10.09 | **TEST** The day-one drawing routine — 50 mm square and circle with a marker taped to the flange, on paper. This is the first thing 12 students see; it cannot fail live | 3D L1 |
| 10.09 | **TEST** Pump box + φ13 and φ16 cup actually lift a 24×24×2 mm PC square, 10 of 10. The entire project assumes this | all courses |
| 11.09 | **DO** Publish base package: repo, tag `v0.1`, README with every call, `AGENTS.md`, CLI. Confirm `pip install` from the tagged URL works on a clean machine | 3D L1, SS L1 |
| 11.09 | **DO** Collect the four repo URLs the teams post, and confirm you have read access to each. Teams create and own their repos; you never make one for them | all |
| 11.09 | **DO** **[plan]** Post the naming convention and the sharing setting for the development log; each team creates its own doc per course and posts the link. Same rule as the repo — the team owns it | all L1 |
| 11.09 | **DO** **[plan]** `LAB_CONVENTIONS.md` rewritten: two-store rule, packet + receipt spec, hour budget, log in Docs | all 20 docs |
| 11.09 | **DO** **[plan]** Apply the conventions edits to the three L1 documents only (the other 17 can follow later) | 11–12.09 handout |
| 12.09 | **TEST** RPI from a clean SD image reaches the MG400 on 29999 and 30003 over LAN, and a phone reaches a Flask page on it over the lab WiFi | SS L1 |
| 12.09 | **TEST** MPX5700AP on a breadboard gives a readable ADC swing when the pump box runs | DA L1 |
| 18.09 | **DO** Gate A bench test complete; the recipe (tip, pressure, pulse, cure time) written into the plan and the L2 texts | all L2 |
| 22.09 | **DO** Gates B, C, D decided; session-2 order out; all three L2 documents final | 02–03.10 handout |

**If something has to slip**, slip the L1 document edits, not the base package or the three tests. A lab can be handed out with an imperfect text; it cannot be handed out with a robot that does not move.

---

## 1. All twenty documents — the plan, applied once

| # | Item | Effort | Due |
|:--|:--|:--|:--|
| 1.1 | **[plan]** `LAB_CONVENTIONS.md`: new **Where things live** block — machine reads it → git; human wrote it in the moment → Google Docs | 1 h | 11.09 |
| 1.2 | **[plan]** Rewrite the Development Log section: lives in a Google Doc, one per team per course, dated entries, photos with a sentence under each, entries added never edited, version history is the timestamp | 1 h | 11.09 |
| 1.3 | **[plan]** Rewrite the verbatim Development Log TO BE CHARTED block in all 20 documents (one text, repeated) | 1 h | 11.09 for L1, rest by 22.09 |
| 1.4 | **[plan]** Add `docs/development-log.pdf` (export at the tag) to every "Required for the defense" list | 30 min | with 1.3 |
| 1.5 | **[plan]** Handover packet spec in the conventions: `handover/<to-course>-lab<N>.md`, five headings — what this is / numbers you need / how to check you got a good one / what isn't true yet / source | 1 h | 22.09 |
| 1.6 | **[plan]** Receipt spec: `handover/received/<from>.md` — what I used it for, what was missing, what was wrong, **minutes from opening to first productive use** | 30 min | 22.09 |
| 1.7 | **[plan]** Turn every "Gives to" line in every Interfaces section into a named packet with a due date. 13 edges in the plan table, ~35 in the documents | 3 h | per lab, see below |
| 1.8 | **[plan]** Add the hour budget to the Project Breakdown of all 20 (planned hours per step on day one, actual, variance line over 50%) | 1 h | 22.09 |
| 1.9 | **[plan]** Redefine assessment category 4 as *Documentation and debugging record* in all 20; empty log = 0 of those 5 points | 1 h | 22.09 |
| 1.10 | **DO** Decide the language rule for the Google Docs log (team's own language) and say it once in the conventions | 10 min | 11.09 |
| 1.11 | **TEST** Hand one finished document to an agent with no context and ask it to produce the lab. Anything it can produce end to end without touching hardware is a lab with no acceptance teeth — fix that lab | 2 h | 22.09 |

---

## 2. 3D Printing

### Lab 1 — handed out 11.09, defended 02.10

* **TEST** the drawing routine (see critical path). Run it twice, from a cold boot.
* **TEST** print one Blender-exported holder yourself on the lab printer with the shelf PLA, and time it. If the printers are not ready on 11.09 the lab's second week is dead.
* **DO** confirm calipers (0.01 mm), the luggage scale or HX711 + 20 kg load cell, and at least 8 PC squares 24×24×2 mm are physically on the table.
* **DO** measure the lifting nozzle yourself once, so you can tell whether a team's `nozzle.csv` is plausible.
* **DO** **[plan]** packet `handover/smart-solutions-lab2.md` and `handover/data-acquisition-lab4.md` due at the L1 tag (30.09): `led_boss_offset`, tip clearance, holder mass, tube routing.
* **RISK** the tensile test is the only source of the MG400 maximum pull, which 3D L2 depends on. If the scale is missing, L2's registration work has no force number.

### Lab 2 — final 22.09, handed out 02.10, defended 23.10

* **DO** Gate A recipe into the text (pressure recipes, O-ring rule, tube joint).
* **TEST** glue one tube joint with toothpick + thread glue and pull it, so the stated cure time is yours and not the internet's.
* **DO** confirm the 3/2 valve (Gate C) is ordered on 22.09 — 3D L2 builds the tool housing around it and needs its real dimensions by 13.10.
* **DO** **[plan]** packets to DA L3 (VL53L0X post height), DA L4 (tray, jig, registration number), SS L2 (calibration target), 3D L3 (foot and socket standard). Four packets, due at the L2 tag 20.10.
* **DO** **[plan]** this is the swap boundary — the L2→L3 packet goes to a *different* team, who must reproduce the registration number from it alone. Write the exercise into both L2 and L3.
* **OPEN** 3D L2 needs the VL53L0X board size from DA L3, which runs in parallel. Both documents say "ask the other team"; put a date on it (13.10) instead of a request.

### Lab 3 — final 13.10, handed out 23.10, defended 13.11

* **DO** freeze the PCB outline and connector edge with DA L3 by **03.11**, as the document already demands. This is the tightest coupling in the semester.
* **TEST** print one enclosure around a cardboard mock-up of the board outline before handing the lab out, and confirm arm-mounted mass stays under 250 g with valve, camera and LED fitted.
* **DO** cable glands, strain reliefs, LED star heatsink, magnets, inserts, PETG in the 13.10 order.
* **DO** **[plan]** seeded fault, different per team: a wrong `led_boss_offset` in the inherited packet, a foot standard off by 2 mm, a stated mass that is 40 g optimistic.
* **RISK — the one real ordering gap.** The PCB is ordered 14.11 and arrives in December, so this enclosure is designed around a board that does not exist. Nothing currently re-checks the fit. See item 5.4.

### Lab 4 — final 03.11, handed out 13.11, defended 04.12

* **DO** decide which part is the "candidate to improve" (tray or valve bracket) and have the original printed so there is a baseline to beat.
* **TEST** run the generative design or FEA workflow once in Fusion with the education licence — confirm the feature is actually enabled on the student licences, not just yours.
* **DO** **[plan]** packet to Prototyping M4 with the assembly guide and BOM.

### Lab 5 — final 24.11, handed out 04.12, defended 16.01

* **DO** decide open item 3: glass batch or tray base plate. This changes the whole lab and it is blocking from 24.11.
* **DO** find and quote the CNC/die-cutting shop **before** 24.11, with lead time. Laser cutting PC is out (fumes, yellow edges); if no shop is reachable in January the lab has no object.
* **TEST** send one dummy drawing to the shop and confirm they accept the format.

---

## 3. Data Acquisition

### Lab 1 — handed out 12.09, defended 03.10

* **TEST** MPX5700AP on a breadboard with the pump box (see critical path). Note the actual ADC swing — the lab asks students to compute why the range is wrong, and you need to know the answer.
* **TEST** the oscilloscope's FFT function works and you can drive it. Two students per scope at most.
* **DO** confirm on the shelf: 10× MPX5700AP, Atom Lites, breadboards, jumper kits, resistor/capacitor kits, multimeters, 10 ml syringes, 4 mm tube, T-pieces.
* **DO** Falstad works from the lab machines (it is browser-based; check the college network does not block it).
* **DO** confirm Mouser accounts / catalogue access, since the L1 deliverable is a Mouser BOM.
* **DO** **[plan]** packet to DA L2 and SS L2: the Pa/LSB table and the noise floor.

### Lab 2 — final 22.09, handed out 03.10, defended 24.10

* **DO** Gates B, C, D by 22.09. MPX5100DP must be in the 22.09 order — one per cell plus spares — or L2 has no correct sensor. No vacuum sensor is ordered: the cup branch is not instrumented.
* **TEST** build the op-amp stage yourself on a breadboard with the new sensors when they arrive, and record the 45 ms filter delay the L3 document quotes. If that number is inherited from last year, verify it.
* **DO** **[plan]** packet to SS L2 (scaling), DA L3 (filtered signal + delay), SS L4 (alarm field basis).

### Lab 3 — final 13.10, handed out 24.10, defended 14.11 (with PCB review)

* **DO** **Gate E is the highest-risk date in the semester.** Schematic, layout, DRC and review must all land on 14.11 for the boards to arrive in December.
* **TEST** run a dP/dt comparator on the breadboard and confirm the interrupt fires on a real clog before students are asked to build one.
* **TEST** VL53L0X reads through the 3D-printed post at the height 3D L2 chose — verify the two teams' numbers agree before the lab starts.
* **DO** freeze the board outline for 3D Print L3 by 03.11 (not 14.11 — the enclosure needs it three weeks earlier).
* **DO** confirm the PCB house, lead time and cost for a 14.11 order arriving before 05.12. If the lead time does not fit, DA L4 runs on breadboards and both documents must say so now, not in December.
* **DO** **[plan]** packet to 3D L3 (outline, connector positions, mounting holes) due **03.11**, and to DA L4 / SS L4 (alarm event, safe state).

### Lab 4 — final 03.11, handed out 14.11, defended 05.12

* **TEST** run 25 cycles yourself with the Gate A recipe and confirm one cycle takes what you think it does. 500 cycles × 4 teams is the largest single time commitment in the semester; if a cycle is 40 s rather than 20 s the lab does not fit in 24 hours.
* **DO** confirm the 0.01 g scale exists for the weighed-dose subset.
* **DO** resin, tips, caps and IPA in the 24.11 order in quantities for 2000 cycles.
* **NOTE** DA L4 consumes SS L4's cycle record schema while both run in parallel. This only works because the schema is GIVEN in the conventions. **Say so in both documents** — it currently reads like an impossible dependency.
* **DO** **[plan]** packet to DA L5 and Prototyping: the measured recipe.

### Lab 5 — final 24.11, handed out 05.12, defended 16.01

* **TEST** train the fill-level model on your own Gate A data and confirm a null result is reachable and gradeable. The plan already expects the null; make sure the notebook template does not assume a positive.
* **DO** confirm all four teams' data is in one bucket and readable with the shared read token.

---

## 4. Smart Solutions

### Lab 1 — handed out 12.09, defended 03.10

* **TEST** clean SD image → MG400 on 29999/30003 → Flask page from a phone (see critical path). Image one card and keep it as the known-good.
* **DO** confirm 4× RPI 4, SD cards, PSUs, LAN cables, and at least one screen per team.
* **DO** decide whether teams get write access to the base package repo or PR-only (open decision 5). The L1 acceptance requires each team to file an issue or PR.
* **TEST** the "another team's agent follows your `AGENTS.md`" check — run it once yourself against your own repo so you know what a passing result looks like.
* **DO** **[plan]** packet to DA L4 and SS L2: the station, saved positions, the replay call.

### Lab 2 — final 22.09, handed out 03.10, defended 24.10

* **DO** Gate C (valve) and Gate D (camera) by 22.09 or this lab has no hardware.
* **TEST** stream MJPEG from the chosen camera and measure the fps you actually get on the lab WiFi. The L3 acceptance compares against this number.
* **TEST** dispense one drop with the Gate A recipe over a waste cup and confirm the p curve has a visible rise, plateau and fall at 100 Hz.
* **DO** freeze the tool-board interface by 13.10 — DA L3 implements it on the PCB and cannot start late.
* **DO** **[plan]** packets to DA L3 (interface spec), 3D L3 (camera position, LED and valve mounting), SS L3 (page, stream, Mosquitto).

### Lab 3 — final 13.10, handed out 24.10, defended 14.11

* **DO** buy the domain and point the A record at the droplet **before 24.10**, and verify DNS has propagated.
* **DO** create the course droplet with a sudo user per team; give each team Digital Ocean credit for their own practice droplet.
* **TEST** do the entire lab yourself on a practice droplet — ufw, WireGuard, nginx, certbot, the MJPEG location — and time it. This is the lab most likely to overrun 30 hours.
* **DO** **[plan]** seeded faults, one per team, prepared and documented so you can reverse them: ufw denying 51820/udp; server-side `AllowedIPs` too wide; MTU left at 1500; droplet clock skewed 4 minutes; A record on a destroyed droplet; `proxy_pass` missing its trailing slash. **TEST each one** — confirm it produces the symptom you expect and is findable in under two hours.
* **DO** **[plan]** remove the answer-key line ("if frames stall, it is buffering, a timeout, or HTTP/1.0") and the two config fragments from the handout; keep the requirement and the acceptance.
* **DO** **[plan]** first-light board: the Teams post format, and the rule that the finder's bonus is paid only when all four teams have a handshake.
* **DO** decide whether certbot stays here or the CA work moves to L4 as mTLS on Mosquitto. If it moves, both texts change on 13.10.
* **DO** consultations are already scheduled — ~15.10 IPv4 routing, ~05.11 WireGuard, ~25.11 nginx. Confirm the rooms.

### Lab 4 — final 03.11, handed out 14.11, defended 05.12

* **TEST** install Mosquitto + InfluxDB on the droplet yourself and push 100 Hz sample traffic from four sources. 4 teams × 100 Hz × 5 fields on a 1 vCPU / 1 GB droplet is the sizing question; measure it, do not assume it.
* **DO** decide the retention policy and disk size before four teams write 500 cycles each.
* **DO** create org, bucket, per-team write tokens and the shared read token.
* **DO** if the CA moves here: generate a reference CA yourself and confirm mTLS works with Mosquitto before writing the text.
* **DO** **[plan]** packet to DA L4 (schema, topics, replay) and Prototyping M2.

### Lab 5 — final 24.11, handed out 05.12, defended 16.01

* **TEST** run an agent against your own REST API and confirm it can complete a cycle. If your own agent cannot, the lab is not ready.
* **DO** decide what the agent is allowed to do unsupervised and write the safety boundary before handout.
* **DO** **[plan]** packet to Prototyping M1, due at the L5 tag (13.01), three days before Prototyping starts.

---

## 5. Cross-cutting items with no home

| # | Item | Due |
|:--|:--|:--|
| 5.1 | **DO** Decide open items 2 (AtomS3 vs AtomS3R, EOL) and 4 (battery plugging in scope) — both affect the tag order and Prototyping | 22.09 |
| 5.2 | **DO** Check AtomS3R stock before ordering 8+ tags and the glass batch | 22.09 |
| 5.3 | **DO** Confirm the college Google Workspace domain for the 16 logs; personal accounts break sharing at the worst moment | 11.09 |
| 5.4 | **DO** **[plan]** Add the PCB fit check to Prototyping M4: when the boards arrive in December, caliper them against the 3D Print L3 enclosure and report *whether it was the drawing or the shop* — the same discipline 3D Print L5 already applies to the CNC parts | 03.11 |
| 5.5 | **DO** Retire the old `ENG/*/… [Lab 1–3]` and `EST/*/… [Lab 1–3]` from the active set so students cannot find last year's text | 11.09 |
| 5.6 | **DO** EST translations. All 20 exist in ENG only in `2026-27/`. The plan says write EST first; that has not happened. Decide: translate before each handout, or run the semester in English | 11.09, then rolling |
| 5.7 | **DO** Peer review in Teams — reframe from opinion to the four-field receipt; write the post template once | 22.09 |
| 5.8 | **TEST** One full dry run of a defense with your own repo: 5 min, 10 min questions, one live change. Confirm 15 minutes × 4 teams fits the session | before 03.10 |

---

## 6. What is not ready and cannot be fixed by writing

Three things carry real schedule risk and no amount of document editing helps:

1. **Gate A has not been run.** Six documents quote "the Gate A recipe" as if it exists. Until the bench test on 18.09 produces one tip, one pressure, one pulse and one cure time, L2 in all three courses cannot be finalised on 22.09.
2. **Gate E lands on 14.11 and the boards arrive in December.** If the PCB house lead time does not fit, DA L4 and SS L4 run on breadboards. Decide the fallback on 03.11, not on 05.12.
3. **The EST versions do not exist for 2026/27.** Twelve students, first-year, in Narva. This is the largest single unbooked block of work in the plan.

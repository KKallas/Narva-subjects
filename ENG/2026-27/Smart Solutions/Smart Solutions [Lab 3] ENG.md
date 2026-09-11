## Smart Solutions: Lab 3 — Digital Ocean droplet and VPN

**Workload:** 30 hours | **Assessment:** 20 points | **Team:** 3 students | **Handed out:** 24.10.26 | **Order date:** 03.11.26 | **Defense:** 17.11.26, online

### How this document works

Half of this document is missing on purpose.

What is written here is **GIVEN**: the dates, the interfaces to the other courses, the acceptance items, the safety rules and the questions worth answering. It is the edge of the map, not the map.

Everything marked **TO BE CHARTED** is empty because the answer is not known yet — not by the instructor either. You chart it: measure, decide, then write the number and the reason for it into this file, next to each other.

Copy this file into your repository as the lab folder's `README.md` on the first day and fill it there while the work is happening. It is not written the night before the defense: a document written afterwards is a story, and a story cannot be graded. The version inside the tag is read exactly as it stands, and a blank that is still blank is an answer too.

Nothing is deleted. A number that turned out wrong stays where it is, dated, with the correction under it. The wrong turn is usually the most useful page in the report — for the team after you, and for you in a year.

Write it so that it needs no translation: real file names, real numbers, units on everything, and the reason standing next to the choice. The reader you are writing for is a teammate who was not in the room that day.

### Objective

The station works on the lab WiFi. Make it reachable from anywhere, securely, camera included. A Digital Ocean droplet (Ubuntu) is the fixed point on the internet: it runs a WireGuard server, and every team's RPI is a WireGuard client with a fixed VPN address, 10.0.0.1 for team 1 through 10.0.0.4 for team 4. The tunnel is brought up by the RPI, kept alive by the RPI, and never needs a port opened at the college: this is the reverse-VPN logic. The droplet's nginx reverse proxy publishes each station under one domain: `robots.kool.ee/robot/N/` → the RPI's Flask page over the tunnel. The nozzle camera's MJPEG stream must survive the proxy, which means `proxy_buffering off` for that location and a long read timeout.

The reason for the cloud is not remote control for its own sake. Four robots must produce one dataset in Lab 4, and the droplet is where Mosquitto, InfluxDB and the central portal will live. In this lab it carries the VPN, the proxy and a status page that pings the four VPN addresses and shows who is online. The RPI now has three networks (MG400 LAN, lab WiFi, VPN) and the routing table must be understood, not copied: which packet leaves by which interface and why.

Acceptance is physical: from outside the lab, on mobile data, place a tag with the robot while watching the nozzle camera through the proxy.

*This is a living document, update the objectives as they change during the work — new knowledge makes old objectives sometimes meaningless. The goal is to keep the team on target at all times, so you don't get lost in the forest of details and the core problem remains unsolved*

**TO BE CHARTED — the objective as it actually turned out.** Once you know what the work really is, rewrite the paragraphs above in your own words and date the rewrite. If the objective still holds unchanged at the defense, write that sentence with its date; that is also a result.

### Interfaces

**Takes from**
* Smart Solutions L2: the one page (status, sensors, camera, dispense), the RPI camera re-stream endpoint, Mosquitto on the RPI.
* Instructor: Digital Ocean credit, the course droplet with a sudo user per team, the domain and its DNS record.

**Gives to**
* Smart Solutions L4: the droplet where Mosquitto, InfluxDB and the portal are installed; the VPN addresses the RPIs publish from.
* Smart Solutions L5: the portal path `robots.kool.ee/robot/N/api/` through which the agent runs the cell.

### Background Information

* **Digital Ocean droplets** — creating, SSH keys, console access.
  [https://docs.digitalocean.com/products/droplets/](https://docs.digitalocean.com/products/droplets/)
* **Digital Ocean: initial server setup** — search phrase: "DigitalOcean initial server setup Ubuntu 24.04 ufw non-root user". Sudo user, SSH keys only, `ufw allow OpenSSH`.
* **WireGuard quick start** — keys, `[Interface]`, `[Peer]`, `AllowedIPs`, `wg show`.
  [https://www.wireguard.com/quickstart/](https://www.wireguard.com/quickstart/)
* **WireGuard conceptual overview** — cryptokey routing: why `AllowedIPs` is both an ACL and a route.
  [https://www.wireguard.com/#conceptual-overview](https://www.wireguard.com/#conceptual-overview)
* **nginx beginner's guide** — server blocks, locations, reload.
  [https://nginx.org/en/docs/beginners_guide.html](https://nginx.org/en/docs/beginners_guide.html)
* **nginx proxy module** — `proxy_pass`, `proxy_buffering`, `proxy_read_timeout`, `proxy_http_version`.
  [https://nginx.org/en/docs/http/ngx_http_proxy_module.html](https://nginx.org/en/docs/http/ngx_http_proxy_module.html)
* **Let's Encrypt with certbot** — HTTPS for the portal, nginx plugin.
  [https://certbot.eff.org/](https://certbot.eff.org/)
* **ufw** — search phrase: "ufw allow limit deny Ubuntu firewall examples". Allow 22/tcp (or a moved SSH port), 80/tcp, 443/tcp, 51820/udp; deny the rest.
* **Linux routing** — search phrase: "ip route show default via metric explained" and "traceroute vs mtr". Consultation ~15.10 covers `ip route`, `ping`, `traceroute` in practice; ~05.11 covers WireGuard step by step.
* **Raspberry Pi networking** — NetworkManager and `nmcli` for a WireGuard connection that comes up at boot.
  [https://www.raspberrypi.com/documentation/computers/configuration.html](https://www.raspberrypi.com/documentation/computers/configuration.html)

*Add your own sources and useful information here that would help you understand the project years later when you reopen it.*

**TO BE CHARTED — your sources.** Every link, datasheet page, forum answer and video that actually helped, each with one line on what you got from it and one line on what was wrong or missing in it. A link with no sentence next to it is not a source.

### Tools

1. Lab 2 station: RPI with Flask page, tool board, camera
2. Course droplet: Ubuntu 24.04, 1 vCPU / 1 GB is enough for four RPIs; a team sudo user each (instructor creates)
3. Practice droplet per team (smallest size, created on day one, destroyed at the defense) for the ufw / WireGuard / nginx steps before touching the shared one
4. WireGuard (`wireguard-tools`) on the droplet and the RPI
5. nginx on the droplet, certbot for HTTPS
6. Domain `robots.kool.ee` (placeholder; the real name is posted in the Teams channel) pointing at the droplet's public IP
7. A phone on mobile data, WiFi off, for the outside-the-lab test
8. `ping`, `traceroute`/`mtr`, `ip route`, `wg show`, `ss -tulpn`, `curl`
9. draw.io

*If the plan changes, update the tools too, or make a draw.io diagram showing how things are functionally related.*

**TO BE CHARTED — what you actually used.** Versions, machine names, which shelf item was substituted for what, what broke and what ran out. The list above is what was expected; this list is what a person needs in order to repeat your work.

### Project Breakdown

- [ ] Practice droplet: create, SSH with keys only, sudo user, `ufw` with OpenSSH + 51820/udp + 80 + 443, `ufw enable`, verify with `ss -tulpn` and a port scan from a laptop
- [ ] WireGuard server on the practice droplet: keys, `wg0` at 10.0.0.254/24, `ListenPort 51820`, IP forwarding not needed (no internet routing through the tunnel, only 10.0.0.0/24)
- [ ] WireGuard client on the RPI: `wg0` at 10.0.0.N/24, `Endpoint` = droplet:51820, `AllowedIPs 10.0.0.0/24`, `PersistentKeepalive 25`; up at boot; `ping 10.0.0.254` from the RPI and `ping 10.0.0.N` from the droplet
- [ ] Repeat on the course droplet: append your `[Peer]` stanza (public key, `AllowedIPs 10.0.0.N/32`) to `/etc/wireguard/wg0.conf` and reload with `wg syncconf`; never restart the interface, the other teams are on it
- [ ] nginx on the course droplet: your own file `/etc/nginx/robots.d/robot-N.conf` included by the main server block, with `location /robot/N/` → `proxy_pass http://10.0.0.N:5000/` and a separate camera location with buffering off (fragment below); `nginx -t` before every reload
- [ ] Flask on the RPI must work under a path prefix: links, static files and the camera `<img src>` relative or prefixed with `/robot/N/`; test the page both locally and through the proxy
- [ ] Camera through the proxy: MJPEG at the same fps as locally ± 2; if frames stall, it is buffering, a timeout, or HTTP/1.0 to the upstream
- [ ] HTTPS with certbot on the course droplet (one team does it, the others check), HTTP redirected to HTTPS
- [ ] Status page: a small Flask app on the droplet (your own at `/team/N/status`) that pings 10.0.0.1–4 every 10 s, shows online/offline, last-seen time, tunnel handshake age from `wg show`, and a link to `/robot/N/`. The best one, chosen at the defense, becomes the root page and the seed of the Lab 4 portal
- [ ] Routing table exercise: `ip route` on the RPI with three interfaces; `traceroute` to the MG400, to the droplet's public IP, to 10.0.0.254; write one line per route in `docs/routing.md`
- [ ] 48-hour tunnel log (Analysis 2), outside-the-lab test (Acceptance), `AGENTS.md` updated with the public URL and the VPN facts

*How far along are you? When will you be done? How could you go faster? — the usual questions*

**TO BE CHARTED — dates and your own steps.** Put the date next to every box you tick, and add the steps this document did not foresee — those are the ones worth reading. A box that cannot be ticked gets one line saying why, rather than being left open.

nginx camera location (the only place buffering is off):
```
location /robot/N/cam.mjpg {
    proxy_pass http://10.0.0.N:5000/cam.mjpg;
    proxy_http_version 1.1;
    proxy_buffering off;
    proxy_read_timeout 1h;
}
```
Droplet-side peer stanza per team:
```
[Peer]
PublicKey = <team N RPI public key>
AllowedIPs = 10.0.0.N/32
```

### Simulation

A draw.io diagram in `docs/three-networks.drawio` (PNG beside it) with:

* The three RPI networks: `eth0` MG400 subnet (ports 29999/30003), `wlan0` lab WiFi (camera, phones on site, default gateway to the internet), `wg0` 10.0.0.N/24 to the droplet
* The droplet: public IP, `wg0` 10.0.0.254, nginx on 80/443, the four peers 10.0.0.1–4
* The proxy path of one browser request from a phone on mobile data: DNS → droplet:443 → nginx → `wg0` → RPI:5000 → (camera re-stream) → `wlan0` → camera
* Arrows labelled with the round-trip numbers from Analysis 1

Under the diagram, the RPI routing table as a code block with one explanatory line per route, and the sentence that explains why the MG400 subnet is never reachable from the droplet (not in any `AllowedIPs`, no forwarding on the RPI) and why that is intended.

### Analysis

Notebook `notebooks/lab3_vpn.ipynb` with outputs:

1. **Latency ladder.** 100 pings each: laptop → RPI on lab WiFi; RPI → droplet public IP; RPI → 10.0.0.254 through the tunnel; phone on mobile data → `robots.kool.ee`. Then 30 timed page loads of `/robot/N/` local vs. through the proxy, and 30 `/status` JSON requests the same way. Table: mean, median, p95 in ms for each hop; the overhead of the tunnel alone (tunnel minus public) and of the proxy alone (proxied page minus local page).
2. **Tunnel uptime, 48 h.** A cron job on the droplet pings 10.0.0.N every 10 s and appends `timestamp, rtt_ms` (or `timeout`) to `data/tunnel_48h.csv`. Plot RTT over time; count outages, their durations, and whether each coincides with a lab WiFi event (note them in `docs/`). Report availability in % and the longest outage in s.
3. **Camera through the proxy.** 60 s of MJPEG local and 60 s through the proxy, from the same phone: fps counted from the multipart boundaries (or from the browser's network tab), kB/s from the droplet's `vnstat`/`ip -s link`. Table local vs. proxied. If fps drops by more than 2, say what fixed it.

**TO BE CHARTED — the answers.** One line for each numbered item above: the number you got, its unit, and where it lives (notebook, cell, file). One line saying why for anything not done. The defense questions come from this section.

### Testing

#### Test Example 1: Tunnel survives a reboot and a WiFi change

Reboot the RPI: within 60 s `wg show` on the droplet reports a fresh handshake for 10.0.0.N and the status page shows the robot online. Then switch the RPI to a phone hotspot (new public address, new NAT): the handshake must recover within 2 × keepalive (50 s) without any change on the droplet. Record both times in `docs/test_log.md`.

#### Test Example 2: MJPEG through the proxy for 10 minutes

Open `https://robots.kool.ee/robot/N/` on a laptop on a different network. The camera image must update continuously for 10 minutes; log the number of stalls > 2 s. A stall that clears only on page reload means buffering or the read timeout. Compare with the same 10 minutes on the lab WiFi.

#### Test Example 3: Firewall and isolation

From a laptop outside the college, port-scan the droplet: only 22 (or your moved SSH port), 80, 443 and 51820/udp answer. From the droplet, `ping` the MG400's LAN address: it must fail (not routed). From team A's RPI, `curl http://10.0.0.B:5000/status` must succeed (all peers see each other on 10.0.0.0/24), and it must be obvious in `docs/` that this is a course decision, not an accident: Lab 4 locking is the protection, not the network.

*These are the first examples, add subsequent tests here so that when you add new parts to this project, you can automatically verify the base part hasn't broken — doing this manually is where most project resources go!*

**TO BE CHARTED — your tests, and your failures.** For every test above: run it, write the result and the date. Then add the tests you invented yourself and — the part that is usually missing — what failed first, what it looked like, and what fixed it.

### Acceptance

* Video: a phone on mobile data (WiFi icon off, visible in the shot) showing `robots.kool.ee/robot/N/` with the live nozzle camera, the operator presses replay of the Lab 1 pick, and the robot in the background places a tag while the camera shows the cup coming down on it. Filmed outside the lab if the robot can be seen through a window or a second phone; otherwise the operator is in the corridor.
* `data/tunnel_48h.csv` (≈17 280 rows) and the notebook's uptime plot with the outage table.
* `data/latency_ladder.csv` (hop, n, ms) and the ladder table.
* Screenshot of `wg show` on the droplet with four peers and handshake ages, and of the status page with all four robots.
* `docs/routing.md`: the RPI `ip route` output with one line per route explained, and `traceroute` outputs to the three destinations.
* Screenshot of the external port scan showing only the four open ports.

**TO BE CHARTED — where each item is.** Next to every item above, the path in the repository and the commit or tag where it appeared. An acceptance item without a path is not accepted; nobody goes looking for it.

### Data produced

Repo only. `tunnel_48h.csv`, `latency_ladder.csv`, `cam_fps.csv` (local vs. proxied, 60 s each). Nothing in the shared database yet; that starts in Lab 4.

### Components for the next lab

Ordered on 03.11.26 for Lab 4: nothing physical for this course. If the RPI still runs on a borrowed HDMI monitor, order the 7" screen now.

| Item | Qty per team | Note |
| :--- | :--- | :--- |
| 7" touch screen for the RPI | 0–1 | only if the station has no screen of its own yet |

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Working files — WireGuard client config at boot, nginx location files with the camera location, status page, Flask working under the path prefix | 5 p |
| Analysis — latency ladder with tunnel and proxy overhead separated, 48 h uptime with outage table, camera fps local vs. proxied | 5 p |
| Prototype — tag placed from outside the lab while watching the camera through the proxy; tunnel recovers after reboot and NAT change | 5 p |
| Documentation — `docs/routing.md` with every route explained, three-network diagram, firewall scan, `AGENTS.md` with the public URL | 5 p |
| **Total** | **20 p** |

### Required for the defense

**Only a link to the git repository, tagged `smart-solutions-lab3` 72 h before the defense.**

The defence is online on 17.11.26. The tag deadline is 72 h before it, which is Saturday 14.11.26 — the same weekend as the contact session where the next lab is handed out. Anything that has to be shown live, the robot moving or a print or a measurement, has to be visible on the call, so join from the lab.

* `smart-solutions/lab3/src/` — Flask app copied from lab2 with prefix support, status page app, cron/ping script
* `smart-solutions/lab3/docs/` — `wg0-client.conf.example` (keys removed), `robot-N.conf` nginx fragment, `routing.md`, `three-networks.drawio` + PNG, screenshots, `test_log.md`, video link
* `smart-solutions/lab3/data/` — `tunnel_48h.csv`, `latency_ladder.csv`, `cam_fps.csv`
* `smart-solutions/lab3/notebooks/lab3_vpn.ipynb` with outputs
* `AGENTS.md` updated: public URL, VPN address, how to check the tunnel
* Live change at the defense: the instructor asks for a different slot; you run it through the portal from a phone on mobile data, not from the lab WiFi.

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

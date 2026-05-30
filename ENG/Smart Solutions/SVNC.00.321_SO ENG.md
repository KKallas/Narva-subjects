## General Information
### Objectives
The course provides practical and theoretical skills for building a control station for an industrial robot. Students build a Raspberry Pi-based control station for the MG400 robotic arm: a web interface for controlling the robot, ESP32 sensor integration, secure remote access via VPN, and a central portal for managing all robots. The academic focus is on computer networking theory (IPv4 routing, subnets, VPN tunnelling, reverse proxy) and on the analysis of cheap-hardware constraints in the context of concurrent programming (Python GIL, blocking, the use of processes and queues).

### Learning Outcomes
A student who has completed the course:
- sets up a Raspberry Pi control station (OS, SSH, static IP, network interfaces);
- explains the principles of IPv4 routing (IP address, subnet, gateway, routing table) and configures a Raspberry Pi with multiple subnets (MG400 LAN, WiFi, VPN);
- programs the MG400 TCP/IP API in Python and builds a Flask web interface for controlling the robot;
- integrates ESP32 sensors with the Raspberry Pi (USB/UART, WiFi, HTTP GET/POST, MQTT);
- configures a Digital Ocean droplet (Linux server, SSH, firewall);
- explains the principles of VPN tunnelling (WireGuard cryptography, public/private key pair, NAT traversal) and configures a WireGuard VPN tunnel;
- explains how a reverse proxy works and configures nginx for the central portal (proxy_pass, HTTPS);
- implements a user-locking mechanism (one operator at a time, view-only mode for others);
- sets up MQTT data logging (Mosquitto + InfluxDB) and builds a historical data dashboard;
- analyses the constraints of cheap hardware (Raspberry Pi) under concurrent programming (Python GIL, blocking, processes vs threads) and designs around them (separate processes, queues, timeouts);
- measures and documents system failure scenarios (connection loss, service crash) and designs safe-state recovery;
- builds a REST API and demonstrates the integration of large language models (LLMs) with the system.

### Brief Course Description
The course builds a complete Raspberry Pi-based control station for the MG400 robotic arm. The architecture: a Raspberry Pi + display on the workbench, connected to the MG400 via a LAN cable and to ESP32 sensors via USB. The Raspberry Pi runs a Flask web server — the operator controls the robot from the browser. A central portal (nginx reverse proxy) runs on a Digital Ocean droplet, listing all connected robots and routing traffic through a VPN tunnel to the correct Raspberry Pi.

The course has two academic cores: (1) **computer networking theory** — the principles of IPv4 routing, subnet separation, VPN tunnelling (WireGuard cryptography and key exchange), reverse proxy logic (nginx), NAT traversal. The Raspberry Pi has three network interfaces (MG400 LAN, WiFi, VPN), giving a practical example of a routing table and packet flow. (2) **Concurrent programming and fault tolerance** — how a single cheap processor (Raspberry Pi) serves multiple peripherals at the same time, where the limits of the Python GIL lie, how to measure blocking, and how to design a system that recovers from faults without losing in-progress work.

### Assessment
List of independent assignments and instructions for completing them:

Assessment structure: 5 projects × 20 points = max 100 points. The integration project is worth max 70 points (perfectly executed = grade C). A total of 170 points is possible; the grade is calculated from the best 100. Students choose which projects to complete — the integration project can be submitted on its own, with the remaining work added to improve the grade.

Four assessment categories per project:
- Working files (5p): code, configuration files, scripts — all in the git repo
- Analysis (5p): latency measurements, fault-tolerance tests, Jupyter analysis
- Prototype (5p): a working system
- Documentation (5p): setup guide, architecture diagram, justifications

#### Assignment 1: Raspberry Pi control station and the MG400 API
Set up the Raspberry Pi control station: OS, SSH, WiFi, static IP. Learn the basics of IPv4 — what an IP address, subnet mask, and gateway are; why the MG400 is on a LAN cable (its own subnet); how the Raspberry Pi talks to the MG400 (Ethernet) and the world (WiFi) at the same time. Program a Python wrapper for the MG400 TCP/IP API (port 29999 dashboard, port 30003 movement). Build a Flask web interface on the Raspberry Pi: buttons for movement, position saving, compressor control. The Raspberry Pi display shows the status. Test: open a browser on a phone → the Raspberry Pi IP → move the robot.

#### Assignment 2: ESP32 sensors and Raspberry Pi integration
Integrate the ESP32 (Data Acquisition sensors) with the Raspberry Pi. USB/UART: the ESP32 sends JSON, the Raspberry Pi reads it with pyserial. WiFi alternative: the ESP32 in AP mode, HTTP GET/POST. Introduction to MQTT: the ESP32 publishes, the Raspberry Pi listens, with the Mosquitto broker running locally on the Raspberry Pi. A Flask service on the Raspberry Pi reads ESP32 data AND controls the MG400 — a single web page shows both. Measure latency: USB vs WiFi vs MQTT.

#### Assignment 3: Digital Ocean droplet and VPN
Set up a Digital Ocean droplet (Ubuntu, SSH, firewall). WireGuard VPN: the droplet is the server, each team's Raspberry Pi is a client with a fixed VPN IP (10.0.0.1–10.0.0.4). Nginx reverse proxy on the droplet: a central web page listing all connected robots (online/offline); clicking a robot → proxy_pass through the VPN tunnel to the Raspberry Pi's Flask server. The user sees the Raspberry Pi web page as if sitting at the lab bench. Reverse VPN logic: ESP32 settings are reachable remotely without socket-level encryption — the VPN tunnel protects all traffic. IPv4 routing in practice: the Raspberry Pi has 3 networks (MG400 LAN, WiFi, VPN tunnel).

#### Assignment 4: MQTT data logging and a unified interface
Mosquitto MQTT broker on the droplet. ESP32 → Raspberry Pi → MQTT, InfluxDB on the droplet. A unified web interface on the Raspberry Pi: control + real-time sensors + historical charts + CSV/JSON export. Extension of the central portal: list of robots + last measurement + status. User locking — only one operator at a time: others see real-time data (camera, sensors, status) but the buttons are greyed out. Doorbell ("please release"), admin override (when the connection drops), auto-timeout (5 min of inactivity). Dispensing recipes. USB camera on the Raspberry Pi. UX test with another team.

#### Assignment 5: Fault tolerance, REST API, and LLM integration
**Fault tolerance**: the Raspberry Pi does 5 things at once (Flask, MG400, ESP32, MQTT, camera). Measure the limits — Python GIL, blocking sockets, camera capture blocking everything. Design simply around them (separate processes, queue, timeout). Safe state: if something is wrong → compressor off. A practical test: pull the ESP32 cable out mid-dispense, pull the MG400 LAN out — what happens? Jupyter Lab: analysis of the fault log, where the limit is at which the Raspberry Pi is no longer enough.
**REST API**: /status, /dispense, /history, /export — documented JSON. Reachable through the central portal (robots.kool.ee/robot/1/api/). Time-locked: remote control only when the local operator has activated it on the Raspberry Pi display. README endpoint (/api) for language models. Demonstration: operator activates → LLM sends a command → robot dispenses → data is saved → automatic locking. Audit log.

#### Bonus assignment: Complete control station
The Raspberry Pi control station as a finished product: clone a single SD card → a new MG400 is immediately usable. Connect the LAN to the MG400, plug the ESP32 in via USB, switch on. Automatic VPN connection. Locking and fault tolerance work. Installable with a single script. Documentation sufficient for another person to set up the system.

### Schedule of Contact Hours
- **[~12.09.26]** Raspberry Pi setup, IPv4 basics, MG400 API, first movement
- **[~12.09.26]** Introduction to Flask, HTML/JS basics
- **[~03.10.26]** Defence of Assignment 1
- **[~03.10.26]** ESP32 ↔ Raspberry Pi communication (USB/UART and WiFi)
- **[~15.10.26]** Consultation 1: IPv4 routing in practice — subnet, gateway, the Raspberry Pi's 3 network interfaces, `ip route`, `ping`, `traceroute`
- **[~24.10.26]** Defence of Assignment 2
- **[~24.10.26]** Digital Ocean, Linux server, WireGuard VPN
- **[~05.11.26]** Consultation 2: VPN in practice — WireGuard step by step, public/private key logic, working behind NAT, tunnel verification
- **[~14.11.26]** Defence of Assignment 3
- **[~14.11.26]** MQTT, InfluxDB, unified interface
- **[~25.11.26]** Consultation 3: nginx reverse proxy — proxy_pass, HTTPS (Let's Encrypt), troubleshooting
- **[~05.12.26]** Defence of Assignment 4
- **[~05.12.26]** REST API, fault tolerance, LLM integration
- **[~16.01.27]** Defence of Assignment 5
- **[TBD]** Defence of the integration project

### Conditions for Admission to Final Assessment
The student has successfully defended at least one assignment with a passing result.

### Final Assessment Scale
Differentiated (A, B, C, D, E, F, mi)

### Composition of the Final Grade
5 projects × 20 points = max 100 points. The integration project is worth max 70 points (perfectly executed = C). A total of 170 points is possible; the grade is calculated from the best 100. The integration project can be submitted on its own (sufficient to pass the course), with the remaining work added to improve the grade.

|   |   |
|---|---|
| A | 91 points |
| B | 81 points |
| C | 71 points |
| D | 61 points |
| E | 51 points |
| F | fewer than 51 points |
| mi | The student has not submitted assignments or participated in the final assessment |

### Resolving Outstanding Work
By agreement with the responsible lecturer

## Smart Solutions: Lab 3

In the previous lab you controlled the ESP32 device directly — the browser talked to the microcontroller directly through the relay. This works with one device but doesn't scale well.

In this lab you rebuild the same functionality on top of a distributed architecture: a central server communicates with ESP32 devices through the MQTT protocol. MQTT is publish/subscribe messaging — devices publish their status to topics, the server listens and saves everything to a time-series database. This is the same pattern used by ROS (Robot Operating System), which you'll get to next semester.

### System Architecture

#### ESP32 devices (clients):

Each device runs its own MQTT client. The device is connected to the robot and controls the pneumatic system — the solenoid valve that controls compressed air flow into the syringe. The pressure sensor (MPX5700AP) is connected to the PCB and measures pressure in the pneumatic system. Create a buffer on the ESP that holds the last 100 measurements, because MQTT QoS1 only works when WiFi is available (if WiFi drops momentarily, measurement data will be lost). Create logic for how the MQTT server and ESP communicate so that messages that are on the ESP but not on the server get sent when the connection is restored.

ESP32 sends an HTML fragment to the **sensors/{uid}/init** channel that describes how to display this device's data. The server saves it and later uses it in a Jinja2 template for rendering the device status. The HTML fragment is stored on the ESP32 in the LittleFS filesystem, which allows modifying it without recompiling the code.

When the device connects to WiFi, it first sends its HTML fragment to the **sensors/{uid}/init** channel. Then the device regularly sends MQTT messages to the central server. Each message contains:

* Device identifier
* Timestamp (ms)
* Valve state (closed/open)
* Pressure 30 ms ago (the time window may need to be adjusted)
* Pressure now

#### MQTT broker (Digital Ocean droplet):

Mediates messages between devices and the central server. Runs on the same droplet as the central server and InfluxDB. Devices must have VPN access to the droplet to send MQTT messages. The MQTT broker (Mosquitto) is lightweight and fast.

#### InfluxDB (Digital Ocean droplet):

Time-series database that stores all MQTT messages with timestamps. InfluxDB is optimized for exactly this kind of data — fast writes, efficient time-based queries.

Example of stored data:

measurement: device\_status
tags:
 \- device\_id: ESP32\_t5\_d1
 \- team: team5
 \- valve\_state: open
fields:
 \- pressure\_30ms\_ago: 2.1
 \- pressure\_now: 4.8
timestamp: 2025\-11\-14T14:32:00Z

#### Central web server (Digital Ocean droplet):

Python Flask web application that:

* Listens to MQTT messages and saves new devices that enter the system to a JSON file that can later be used to show devices that are currently offline.
* Listens to data MQTT messages and saves them to InfluxDB
* Displays a list of all devices, their last seen time, and current status
* Displays historical graphs and data for each device
* Allows exporting data in CSV format

### WiFi

ESP does not connect to WiFi or create an AP until SSID and password are configured through the serial port and saved to NVS (non-volatile storage):

* WiFi username and password are entered via serial port after firmware installation
* If WiFi is not configured, the rest of the program is not started either.

Example of key configuration via serial port:

\> set\_wifi SSID:PASS

### Data Flow

#### Monitoring and logging (MQTT → InfluxDB):

ESP32 → MQTT broker → Central server → InfluxDB

MQTT message:

{
 "device\_id": "ESP32\_team5\_device1",
 "timestamp": 1699876543,
 "valve\_state": "open",
 "pressure\_30ms\_ago": 2.1,
 "pressure\_now": 4.8
}

### Central Server Web Application

#### Main page - Device list:

http://digital\_ocean\_droplet\_ip/

`┌─────────────────────────────────────────────────────────────────┐`
`│ Device Overview                                                 │`
`├─────────────┬──────────────┬─────────────┬───────────┬──────────┤`
`│ Device      │ Description  │ Last Seen   │ Status    │ Action   │`
`├─────────────┼──────────────┼─────────────┼───────────┼──────────┤`
`│ ESP32_t5_d1 │ Test device 1│ 2 min ago   │ Online    │[History] │`
`│             │              │             │ Valve:    │          │`
`│             │              │             │ Open      │          │`
`│             │              │             │ P: 4.8    │          │`
`├─────────────┼──────────────┼─────────────┼───────────┼──────────┤`
`│ ESP32_t5_d2 │ Test device 2│ 5 min ago   │ Online    │[History] │`
`│             │              │             │ Valve:    │          │`
`│             │              │             │ Closed    │          │`
`│             │              │             │ P: 1.2    │          │`
`├─────────────┼──────────────┼─────────────┼───────────┼──────────┤`
`│ ESP32_t3_d1 │ Test device 3│ 15 min      │ Offline   │[History] │`
`│             │              │             │ -         │          │`
`└─────────────┴──────────────┴─────────────┴───────────┴──────────┘`

##### History button:

* Opens the device history page on the central server
* For example: http://digital\_ocean\_droplet\_ip/device/{uid}/history

#### History page:

http://digital\_ocean\_droplet\_ip/device/{uid}/history

`┌─────────────────────────────────────────────────────────────────┐`
`│ {uid} Description - History                                     │`
`├─────────────────────────────────────────────────────────────────┤`
`│                                                                 │`
`│ [Pressure graph last 24h - Chart.js/Plotly]                     │`
`│  6 bar ┤     ╭╮                                                 │`
`│  5 bar ┤    ╭╯╰╮  ╭╮                                            │`
`│  4 bar ┤   ╭╯  ╰╮╭╯╰╮                                           │`
`│  3 bar ┤  ╭╯    ╰╯  ╰╮                                          │`
`│  2 bar ┼──╯          ╰─────────────────                         │`
`│        └──────────────────────────────────────►                 │`
`│          10:00    12:00    14:00    16:00                       │`
`│                                                                 │`
`│ [Valve state - history]                                         │`
`│ Open   ┤ ████░░░░████░░████                                     │`
`│ Closed ┤ ░░░░████░░░░██░░░░                                     │`
`│        └──────────────────────────────────────►                 │`
`│          10:00    12:00    14:00    16:00                       │`
`│                                                                 │`
`├─────────────────────────────────────────────────────────────────┤`
`│ Event log (last 50):                                            │`
`├──────┬─────────────┬───────────┬──────────────┬─────────────────┤`
`│ Time │ Valve       │ P 30ms    │ P now        │ Δ Pressure      │`
`├──────┼─────────────┼───────────┼──────────────┼─────────────────┤`
`│14:32 │ Open        │ 2.1 bar   │ 4.8 bar      │ +2.7 bar        │`
`│14:28 │ Closed      │ 4.8 bar   │ 1.2 bar      │ -3.6 bar        │`
`│14:25 │ Open        │ 1.2 bar   │ 5.1 bar      │ +3.9 bar        │`
`│ ...  │             │           │              │                 │`
`└──────┴─────────────┴───────────┴──────────────┴─────────────────┘`

`[Export data] [CSV] [JSON]`

#### Data export:

http://digital\_ocean\_droplet\_ip/export

`┌─────────────────────────────────────────────────────────────────┐`
`│ Data Export                                                      │`
`├─────────────────────────────────────────────────────────────────┤`
`│ Device: [All ▼] [ESP32_t5_d1] [ESP32_t5_d2] ...                 │`
`│ Team: [All ▼] [Team 5] [Team 3] ...                              │`
`│ Time range: [2025-11-01] to [2025-11-14]                        │`
`│                                                                 │`
`│ Format: ◉ CSV  ○ JSON                                           │`
`│                                                                 │`
`│ [Export] (estimated file size: 124 KB)                           │`
`└─────────────────────────────────────────────────────────────────┘`

Exportable CSV structure:

`device_id,timestamp,valve_state,pressure_30ms_ago,pressure_now,pressure_delta`
`{uid},1699876543,open,2.1,4.8,2.7`
`{uid},1699876789,closed,4.8,1.2,-3.6`
`...`

### Technical Components and Tools

#### ESP32 device:

##### Hardware:

* ESP32 DevKit (M5 Atom Lite)
* M5 3A Relay unit (for solenoid control)
* Data Acquisition lab pressure gauge PCBA ([link](https://docs.google.com/document/d/1Bwf5_EJ4ATtv1ByOnjVSUOAq71pvqj7uIYDA0QPOXv4/edit?usp=sharing))
* Solenoid valve 24V
* Pneumatic fittings and tubing
* 24V power supply → BUCK 24V → 5V (ESP32)

##### Software:

* Arduino IDE or PlatformIO
* PubSubClient library (MQTT) ([github](https://github.com/knolleary/pubsubclient))
* NTPClient library (time synchronization)

##### Additional Software:

* InfluxDB 2.x
* Mosquitto MQTT broker

### Project Breakdown

#### Part 1: LittleFS and Security

* Configure LittleFS
* Upload HTML file to LittleFS
* Add serial port WiFi configuration
* Implement NTP

#### Part 2: MQTT

* Add MQTT library
* Implement data sending (valve\_state, pressures)
* Test MQTT messages with mosquitto\_sub command

#### Part 3: InfluxDB and Central Server MQTT Listener

* Install InfluxDB
* Create bucket and token
* Save data to InfluxDB
* Test with queries

#### Part 4: Central Server Web UI

* Create server HTML pages in Flask ([link](https://flask.palletsprojects.com/en/stable/)) for external login authentication
* Query devices from JSON file
* Query latest data from InfluxDB
* Display device list in HTML
* Add "History" page
* Visualize graphs (Chart.js)

#### Part 5: Data Export

* Create export endpoint
* Generate CSV/JSON
* Add download function

### Background Information

* InfluxDB and Python
  [https://www.youtube.com/watch?v=CdorS9UgRk4\&t=3s](https://www.youtube.com/watch?v=CdorS9UgRk4&t=3s)
* Flask
  [https://www.youtube.com/watch?v=mqhxxeeTbu0\&list=PLzMcBGfZo4-n4vJJybUVV3Un\_NFS5EOgX](https://www.youtube.com/watch?v=mqhxxeeTbu0&list=PLzMcBGfZo4-n4vJJybUVV3Un_NFS5EOgX)
* Mosquitto MQTT
  [https://www.youtube.com/watch?v=5rHWeV0dwxo](https://www.youtube.com/watch?v=5rHWeV0dwxo)
* HTTPS and Flask
  [https://www.youtube.com/watch?v=VqnSenJAheU](https://www.youtube.com/watch?v=VqnSenJAheU)


Add your own sources and useful information here.

### Tools

#### ESP32 device:

* M5 Atom Lite or ESP32 DevKit
* MPX5700AP pressure sensor
* PCB board (from Data Acquisition Lab 3)
* Solenoid valve 24V
* Pneumatic fittings and tubing
* 24V power supply
* BUCK converter 24V→5V

#### Digital Ocean droplet:

* InfluxDB 2.x
* Mosquitto MQTT broker
* Flask

#### Development tools:

* Arduino IDE or PlatformIO
* VS Code
* Git
* MQTT Explorer (for viewing MQTT messages)

### Simulation/Documentation

For this lab, there is no traditional simulation part (like a circuit simulation in Falstad), but rather documentation through two diagrams that explain the system's holistic architecture. These drawings are critical for understanding how a distributed system works — where data flows, how security is implemented, and how different technology layers communicate with each other.

#### Draw the infrastructure graphically

Create an infrastructure diagram ([draw.io](http://draw.io) or another tool) that shows:

##### IP addresses and network:

* Digital Ocean droplet: (VPN server \+ Central server \+ MQTT broker \+ InfluxDB)
* ESP32 devices: (VPN clients)
* Home router: (Home/External NAT, external IP)

##### **Data traffic flows:**

Show data movement with arrows:

1. ESP32 → MQTT broker (port 1883): Status messages
2. MQTT broker → Central server: Message forwarding
3. Central server → InfluxDB (port 8086): Data storage
4. User browser → Central server (port 80/443): Viewing device list

##### **Authentication flows:**

Mark the different authentication layers on the diagram:

1. VPN authentication: OpenVPN
2. Central server authentication: Username/password (in Flask)
3. MQTT authentication: Username/password

##### Example diagrams (below as text version):

    `[User]                                [ESP32 devices]`
    `(public IP)                           (local network)`
         `│                                       │`
         `│                                       │`
         `│                                  [VPN Router]`
         `│                                (OpenVPN client)`
         `│                                       │`
         `│                                       │`
         `└──────────── Internet ─────────────────┘`
                           `│`
                           `▼`
              `┌─────────────────────────────┐`
              `│  Digital Ocean Droplet      │`
              `│  (OpenVPN server + services)│`
              `│  10.8.0.1                   │`
              `├─────────────────────────────┤`
              `│                             │`
              `│  [Flask Server :5000] ◄──── HTTP (public)`
              `│         │                   │`
              `│         ▼                   │`
              `│  [InfluxDB :8086]           │`
              `│         ▲                   │`
              `│         │                   │`
              `│  [MQTT Listener]            │`
              `│         │                   │`
              `│         ▼                   │`
              `│  [Mosquitto :1883] ◄─────── MQTT (VPN 10.8.0.x)`
              `│                             │`
              `└─────────────────────────────┘`

##### Draw the software stack graphically

Create a software stack diagram that shows each component's technology layers vertically and their mutual communication horizontally.

**ESP32 device stack:**

`┌─────────────────────────────────────┐`
`│      Logic (Arduino)                │`
`│   - Valve control (GPIO)            │`
`│   - Pressure reading (ADC)          │`
`│   - MQTT publishing                 │`
`├─────────────────────────────────────┤`
`│        Library layers               │`
`│  - LittleFS (HTML templates)        │`
`│  - PubSubClient (MQTT client)       │`
`│  - NTPClient (time synchronization) │`
`├─────────────────────────────────────┤`
`│     Arduino/ESP-IDF framework       │`
`├─────────────────────────────────────┤`
`│         ESP32 Hardware              │`
`│  (WiFi, ADC, GPIO, Flash, NVS)      │`
`└──────────────┬──────────────────────┘`
               `│`
               `│ MQTT Publish (port 1883)`
               `▼`
`┌─────────────────────────────────────┐`
`│     Mosquitto MQTT Broker           │`
`│     (Digital Ocean droplet)         │`
`└─────────────────────────────────────┘`

**Central server stack:**

`┌─────────────────────────────────────┐`
`│      User browser                   │`
`│  (HTML, CSS, Chart.js graphs)       │`
`└──────────────┬──────────────────────┘`
               `│ HTTP (port 80/443)`
               `▼`
`┌─────────────────────────────────────┐`
`│       Flask web application         │`
`│  Routes:                            │`
`│   - / (device list)                 │`
`│   - /device/<id>/history            │`
`│   - /export                         │`
`├─────────────────────────────────────┤`
`│      Template rendering             │`
`│      (Jinja2 templates)             │`
`├─────────────────────────────────────┤`
`│    InfluxDB client library          │`
`│  (queries, data reading)            │`
`└──────────────┬──────────────────────┘`
               `│`
               `▼`
`┌─────────────────────────────────────┐`
`│       InfluxDB (port 8086)          │`
`│    Bucket: syringe_bucket           │`
`│  Measurement: device_status         │`
`└─────────────────────────────────────┘`

             `┌───────────────────────┐`
             `│   MQTT Listener       │`
             `│  (separate Python     │`
             `│   script or thread)   │`
             `└──────┬────────────────┘`
                    `│`
                    `▼`
             `┌─────────────────────────┐`
             `│ Mosquitto MQTT Broker   │`
             `│     (port 1883)         │`
             `└──────▲──────────────────┘`
                    `│`
                    `│ MQTT Publish`
                    `│`
             `┌──────┴──────────────────┐`
             `│   ESP32 devices         │`
             `│  (PubSubClient)         │`
             `└─────────────────────────┘`

##### Communication between different components (sequence diagram style):

Show how different layers communicate during a specific action:

**Scenario 1: ESP32 sends status**

`ESP32                       MQTT Broker      MQTT Listener    InfluxDB`
`│                               │                │               │`
`│──measurement──>buffer         │                │               │`
`│──publish buffer[0]───────────>│                │               │`
`│  [OK]                         │                │               │`
`│──remove buffer[0]             │                │               │`
`│                               │──forward──────>│               │`
`│                               │                │──write───────>│`
`│                               │                │               │`
`│──measurement──>buffer         │                │               │`
`│──publish buffer[0]────X       │                │               │`
`│  [WiFi drops, FAIL]           │                │               │`
`│                               │                │               │`
`│──measurement──>buffer         │                │               │`
`│──measurement──>buffer         │                │               │`
`│                               │                │               │`
`│  [WiFi restored]              │                │               │`
`│──publish buffer[0]───────────>│                │               │`
`│  [OK]                         │                │               │`
`│──remove buffer[0]             │                │               │`
`│──publish buffer[1]───────────>│                │               │`
`│  [OK]                         │                │               │`
`│──remove buffer[1]             │                │               │`
`│  ...                          │                │               │`

**Scenario 2: User views device list**

`Browser        Flask Server    InfluxDB`
 `│                  │              │`
 `│──GET /──────────>│              │`
 `│                  │              │`
 `│                  │──query──────>│`
 `│                  │  last status │`
 `│                  │              │`
 `│                  │<─result──────│`
 `│                  │              │`
 `│<─HTML + data─────│              │`
 `│  (Jinja2)        │              │`

**Scenario 3: User controls ESP32 valve**

   `Button        ESP32 Logic        MQTT Broker      MQTT Listener    InfluxDB`
    `│                  │                │                  │              │`
    `│──press──────────>│                │                  │              │`
    `│  (GPIO interrupt)│                │                  │              │`
    `│                  │                │                  │              │`
    `│            toggle valve           │                  │              │`
    `│            state (GPIO)           │                  │              │`
    `│                  │                │                  │              │`
    `│                  │──publish──────>│                  │              │`
    `│                  │  topic: sensors/{uid}/status      │              │`
    `│                  │  payload: {"valve_state":"open",  │              │`
    `│                  │   "pressure_30ms_ago":2.1,        │              │`
    `│                  │   "pressure_now":4.8}             │              │`
    `│                  │                │                  │              │`
    `│                  │                │──forward────────>│              │`
    `│                  │                │                  │              │`
    `│                  │                │                  │──write──────>│`
    `│                  │                │                  │  Point(...)  │`
    `│                  │                │                  │              │`

**Technology legend:**

Add a legend to the diagram explaining the technologies used:

* **OpenVPN:** VPN protocol (UDP/TCP)
* **MQTT:** Message broker protocol (TCP, port 1883\)
* **Mosquitto:** MQTT broker software
* **InfluxDB:** Time-series database (HTTP API, port 8086\)
* **Flask:** Python web framework
* **Jinja2:** Template rendering (inside Flask)
* **NTP:** Network Time Protocol (time synchronization)
* **LittleFS:** ESP32 filesystem
* **NVS:** ESP32 non-volatile storage (WiFi credentials)
* **PubSubClient:** Arduino MQTT client library
* **Chart.js:** JavaScript charting library

**Why these diagrams are important:**

These diagrams document the system architecture in a way that makes it possible to:

1. Show that you understand the entire system holistically
2. Use yourself in the future when you need to set the system up again
3. Share with other students so they can learn from your solution
4. Use as a basis when you want to extend the system (e.g. add new sensors)

The diagrams should be detailed enough that someone else could build the system based on them, but not so detailed that they become unreadable. Use colors to distinguish different components and data flows.

**Recommended tools:**

* draw.io (free, web-based)
* Excalidraw (free, minimalist)
* Lucidchart (free version is sufficient)
* PlantUML (if you prefer a code-based approach)

Add both diagrams (as PNG or PDF) to your project documentation and Git repo.

### Testing

#### Test Example 1: MQTT Connection Loss, Recovery

When ESP32 or the router is disconnected from the external network — when the connection is restored, do the intermediate measurements get uploaded?

#### Test Example 2: History Endpoint

Send 100 messages and check whether the history endpoint shows the correct count and correct data.

### Development Log

###

### Results

Make sure to provide everything for grading:

* Work files (**4** points): ESP32 software and git repo
* Simulation/documentation (**4** points): graphical overview in the project
* Prototype (**4** points): Digital Ocean and VPN setup
* Documentation (**4** points): design choice justifications, user manual

### Feedback

## Nutilahendused: Labor 3

Eelmises laboris juhtisid ESP32 seadet otse \- brauser rääkis relay kaudu otse mikrokontrolleriga. See töötab ühe seadmega, aga ei skaleeru hästi.

Selles laboris ehitad sama funktsionaalsuse ümber hajutatud arhitektuuri peale: keskne server suhtleb ESP32 seadmetega läbi MQTT protokolli. MQTT on publish/subscribe sõnumivahetus \- seadmed avaldavad oma staatust teemadele, server kuulab ja salvestab kõik ajalogilisse andmebaasi. See on sama muster, mida kasutab ROS (Robot Operating System), mille juurde jõuate järgmisel semestril.

### Süsteemi arhitektuur

#### ESP32 seadmed (kliendid):

Iga seade jooksutab oma MQTT klienti. Seade on ühendatud roboti külge ja juhib pneumaatilist süsteemi \- solenoidklappi, mis kontrollib suruõhu voolu süstlasse. Rõhuandur (MPX5700AP) on ühendatud PCB plaadile ja mõõdab rõhku pneumaatilises süsteemis. Loo esp peal buffer kus hoiad viimast 100 mõõtmist, sest MQTT QoS1 töötab ainult kui WiFi on olemas (kui WiFi korraks maha kukub siis lähevad ka mõõtmise andmed kaduma). Loo loogika kuidas MQTT server ja ESP suhtlevad nii et sõnumid mis on ESPs aga ei ole servers saaks sinna saadetud kui ühendus taastub. 

ESP32 saadab **sensors/{uid}/init** kanalisse HTML fragmenti, mis kirjeldab kuidas selle seadme andmeid kuvada. Server salvestab selle ja kasutab hiljem Jinja2 template'is seadme staatuse renderdamiseks. HTML fragment on ESP32-l salvestatud LittleFS failisüsteemi, mis võimaldab seda muuta ilma koodi ümber kompileerimata.

Kui seade ühendub WiFisse, saadab ta esimesena **sensors/{uid}/init** kanalisse oma HTML fragmenti. Edasi saadab seade regulaarselt MQTT sõnumeid kesksele serverile. Iga sõnum sisaldab:

* Seadme identifikator  
* Timestamp (ms)  
* Klapi olek (kinni/lahti)  
* Rõhk 30 ms tagasi (võibolla aja-akent tuleb täpsustada)  
* Rõhk praegu

#### MQTT broker (Digital Ocean droplet):

Vahendab sõnumeid seadmete ja keskserveri vahel. Jookseb samas dropletis kus keskserver ja InfluxDB. Seadmed peavad omama VPN juurdepääsu droplet'ile, et MQTT sõnumeid saata. MQTT broker (Mosquitto) on kerge ja kiire.

#### InfluxDB (Digital Ocean droplet):

Time-series andmebaas, mis salvestab kõik MQTT sõnumid timestampiga. InfluxDB on optimeeritud just selliste andmete jaoks \- kiired kirjutamised, efektiivsed ajalised päringud.

Näide salvestatud andmetest:

measurement: device\_status  
tags:  
 \- device\_id: ESP32\_t5\_d1  
 \- team: team5  
 \- valve\_state: open  
fields:  
 \- pressure\_30ms\_ago: 2.1  
 \- pressure\_now: 4.8  
timestamp: 2025\-11\-14T14:32:00Z

#### Keskne veebiserver (Digital Ocean droplet):

Python Flask veebirakendus, mis:

* Kuulab MQTT sõnumeid ja salvestab uued seadmed json mis süsteemi tulevad json faili mida saab hiljem kasutada et näidata seadmeid mis hetkel offline.   
* Kuulab andmetega MQTT sõnumeid ja salvestab need InfluxDB-sse  
* Kuvab nimekirja kõikidest seadmetest, nende viimast nähtud aega ja hetkestaatust  
* Kuvab ajalogilisi graafikuid ja andmeid iga seadme kohta  
* Võimaldab eksportida andmeid csv formaadis

### WiFi

ESP ei ühendu WiFi sse ega ka tee AP enne kui läbi seerial pordi on konfigureeritud SSID ja parool mis  salvestatakse NVS (non-volatile storage) mällu:

* Wifi kasutaja ja parool sisestatakse seriaal pordi kaudu peale firmware installeerimist  
* Kui wifi ei ole seadistatud siis seda ka ülejäänud programmi ei käivitata.

Näide võtme seadistamisest seriaal pordi kaudu:

\> set\_wifi SSID:PASS

### Andmevoog

#### Seire ja logimine (MQTT → InfluxDB):

ESP32 → MQTT broker → Keskserver → InfluxDB

MQTT sõnum:

{  
 "device\_id": "ESP32\_team5\_device1",  
 "timestamp": 1699876543,  
 "valve\_state": "open",  
 "pressure\_30ms\_ago": 2.1,  
 "pressure\_now": 4.8  
}

### Keskserveri veebirakendus

#### Pealeht \- Seadmete nimekiri:

http://digital\_ocean\_droplet\_ip/

`┌─────────────────────────────────────────────────────────────────┐`  
`│ Seadmete ülevaade                                               │`  
`├─────────────┬──────────────┬─────────────┬───────────┬──────────┤`  
`│ Seade       │ Kirjeldus    │ Viimati     │ Staatus   │ Tegevus  │`  
`├─────────────┼──────────────┼─────────────┼───────────┼──────────┤`  
`│ ESP32_t5_d1 │ Testseade 1  │ 2 min tagasi│ Online    │[History] │`  
`│             │              │             │ Klapp:    │          │`  
`│             │              │             │ Lahti     │          │`  
`│             │              │             │ Rõhk: 4.8 │          │`  
`├─────────────┼──────────────┼─────────────┼───────────┼──────────┤`  
`│ ESP32_t5_d2 │ Testseade 2  │ 5 min tagasi│ Online    │[History] │`  
`│             │              │             │ Klapp:    │          │`  
`│             │              │             │ Kinni     │          │`  
`│             │              │             │ Rõhk: 1.2 │          │`  
`├─────────────┼──────────────┼─────────────┼───────────┼──────────┤`  
`│ ESP32_t3_d1 │ Testseade 3  │ 15 min      │ Offline   │[History] │`  
`│             │              │             │ -         │          │`  
`└─────────────┴──────────────┴─────────────┴───────────┴──────────┘`

##### History nupp:

* Avab seadme ajaloo lehe keskserveris  
* Näiteks: http://digital\_ocean\_droplet\_ip/device/{uid}/history

#### Ajaloo lehekülg:

http://digital\_ocean\_droplet\_ip/device/{uid}/history

`┌─────────────────────────────────────────────────────────────────┐`  
`│ {uid} Kirjeldus - Ajalugu                                       │`  
`├─────────────────────────────────────────────────────────────────┤`  
`│                                                                 │`  
`│ [Rõhu graafik viimased 24h - Chart.js/Plotly]                   │`  
`│  6 bar ┤     ╭╮                                                 │`  
`│  5 bar ┤    ╭╯╰╮  ╭╮                                            │`  
`│  4 bar ┤   ╭╯  ╰╮╭╯╰╮                                           │`  
`│  3 bar ┤  ╭╯    ╰╯  ╰╮                                          │`  
`│  2 bar ┼──╯          ╰─────────────────                         │`  
`│        └──────────────────────────────────────►                 │`  
`│          10:00    12:00    14:00    16:00                       │`  
`│                                                                 │`  
`│ [Klapi olek - ajalugu]                                          │`  
`│ Lahti  ┤ ████░░░░████░░████                                     │`  
`│ Kinni  ┤ ░░░░████░░░░██░░░░                                     │`  
`│        └──────────────────────────────────────►                 │`  
`│          10:00    12:00    14:00    16:00                       │`  
`│                                                                 │`  
`├─────────────────────────────────────────────────────────────────┤`  
`│ Sündmuste logi (viimased 50):                                   │`  
`├──────┬─────────────┬───────────┬──────────────┬─────────────────┤`  
`│ Aeg  │ Klapp       │ Rõhk 30ms │ Rõhk praegu  │ Δ Rõhk          │`  
`├──────┼─────────────┼───────────┼──────────────┼─────────────────┤`  
`│14:32 │ Lahti       │ 2.1 bar   │ 4.8 bar      │ +2.7 bar        │`  
`│14:28 │ Kinni       │ 4.8 bar   │ 1.2 bar      │ -3.6 bar        │`  
`│14:25 │ Lahti       │ 1.2 bar   │ 5.1 bar      │ +3.9 bar        │`  
`│ ...  │             │           │              │                 │`  
`└──────┴─────────────┴───────────┴──────────────┴─────────────────┘`

`[Ekspordi andmed] [CSV] [JSON]`

#### Andmete eksport:

http://digital\_ocean\_droplet\_ip/export

`┌─────────────────────────────────────────────────────────────────┐`  
`│ Andmete eksport                                                 │`  
`├─────────────────────────────────────────────────────────────────┤`  
`│ Seade: [Kõik ▼] [ESP32_t5_d1] [ESP32_t5_d2] ...                 │`  
`│ Meeskond: [Kõik ▼] [Team 5] [Team 3] ...                        │`  
`│ Ajavahemik: [2025-11-01] kuni [2025-11-14]                      │`  
`│                                                                 │`  
`│ Formaat: ◉ CSV  ○ JSON                                          │`  
`│                                                                 │`  
`│ [Ekspordi] (eeldatav faili suurus: 124 KB)                      │`  
`└─────────────────────────────────────────────────────────────────┘`

Eksporditav CSV struktuur:

`device_id,timestamp,valve_state,pressure_30ms_ago,pressure_now,pressure_delta`  
`{uid},1699876543,open,2.1,4.8,2.7`  
`{uid},1699876789,closed,4.8,1.2,-3.6`  
`...`

### Tehnilised komponendid ja tööriistad

#### ESP32 seade:

##### Riistvara:

* ESP32 DevKit (M5 Atom Lite)  
* M5 3A Relay unit (solenoidi juhtimiseks)  
* Andmehõive labor rõhu mõõdiku PCBA ([link](https://docs.google.com/document/d/1Bwf5_EJ4ATtv1ByOnjVSUOAq71pvqj7uIYDA0QPOXv4/edit?usp=sharing))  
* Solenoidklapp 24V  
* Pneumaatilised otsikud ja voolikud  
* 24V toiteplokk → BUCK 24V → 5V (ESP32)

##### Tarkvara:

* Arduino IDE või PlatformIO  
* PubSubClient library (MQTT) ([github](https://github.com/knolleary/pubsubclient))  
* NTPClient library (aja sünkronistasioon)

##### Lisa Tarkvaras:

* InfluxDB 2.x  
* Mosquitto MQTT broker

### Projekti ülesehitus

#### Osa 1: LittleFS ja turvalisus

* Konfigureeri LittleFS  
* Laadi HTML fail LittleFS-i  
* Lisa seriaal pordi wifi konfiguratsioon  
* Implementeeri NTP

#### Osa 2: MQTT

* Lisa MQTT library  
* Implementeeri andmete saatmine (valve\_state, rõhud)  
* Testi MQTT sõnumeid mosquitto\_sub käsuga

#### Osa 3: InfluxDB ja keskserveri MQTT listener

* Installi InfluxDB  
* Loo bucket ja token  
* Salvesta andmed InfluxDB-sse  
* Testi päringutega

#### Osa 4: Keskserveri veebi UI

* Loo Flaskis([link](https://flask.palletsprojects.com/en/stable/)) serveri HTML lehed välise sisselogimise jaoks autentimine  
* Päri seadmed json failist  
* Päri InfluxDB-st viimased andmed  
* Kuva seadmete nimekiri HTML-is  
* Lisa "History" leht  
* Visualiseeri graafikud (Chart.js)

#### Osa 5: Andmete eksport

* Loo ekspordi endpoint  
* Genereeri CSV/JSON  
* Lisa download funktsioon

### Taustainfo

* Influx DB and python  
  [https://www.youtube.com/watch?v=CdorS9UgRk4\&t=3s](https://www.youtube.com/watch?v=CdorS9UgRk4&t=3s)  
* Flask  
  [https://www.youtube.com/watch?v=mqhxxeeTbu0\&list=PLzMcBGfZo4-n4vJJybUVV3Un\_NFS5EOgX](https://www.youtube.com/watch?v=mqhxxeeTbu0&list=PLzMcBGfZo4-n4vJJybUVV3Un_NFS5EOgX)  
* Mosquitto MQTT   
  [https://www.youtube.com/watch?v=5rHWeV0dwxo](https://www.youtube.com/watch?v=5rHWeV0dwxo)  
* Https ja Flask  
  [https://www.youtube.com/watch?v=VqnSenJAheU](https://www.youtube.com/watch?v=VqnSenJAheU)


Lisa siia omapoolseid allikaid ja kasuliku informatsiooni.

### Vahendid

#### ESP32 seade:

* M5 Atom Lite või ESP32 DevKit  
* MPX5700AP rõhuandur  
* PCB plaat (Labor 3 andmehõivest)  
* Solenoidklapp 24V  
* Pneumaatilised otsikud ja voolikud  
* 24V toiteplokk  
* BUCK konverter 24V→5V

#### Digital Ocean droplet:

* InfluxDB 2.x  
* Mosquitto MQTT broker  
* Flask

#### Arendustööriistad:

* Arduino IDE või PlatformIO  
* VS Code  
* Git  
* MQTT Explorer (MQTT sõnumite vaatamiseks)

### Simulatsioon/Dokumentatsioon

Selle labori puhul pole traditsioonilise simulatsiooni osa (nagu Falstadis ahelasimulatsioon), vaid dokumenteerimine läbi kahe graafiku, mis selgitavad süsteemi terviklikku arhitektuuri. Need joonised on kriitilised selleks, et mõista kuidas hajutatud süsteem töötab \- kust andmed liiguvad, kuidas turvalisus implementeeritakse, ja kuidas erinevad tehnoloogiakihid omavahel suhtlevad.

#### Joonista graafiliselt infrastruktuur

Loo infrastruktuuri diagramm ([draw.io](http://draw.io) või muu tööriist), mis näitab:

##### IP aadressid ja võrk:

* Digital Ocean droplet: (VPN server \+ Keskserver \+ MQTT broker \+ InfluxDB)  
* ESP32 seadmed: (VPN kliendid)  
* Kodune ruuter: (Kodune/Väline NAT, väline IP)

##### **Andmeliikluse vood:** 

Näita nooltega andmete liikumist:

1. ESP32 → MQTT broker (port 1883): Staatuse sõnumid  
2. MQTT broker → Keskserver: Sõnumite edastamine  
3. Keskserver → InfluxDB (port 8086): Andmete salvestamine  
4. Kasutaja brauser → Keskserver (port 80/443): Seadmete nimekirja vaatamine

##### **Autentimise vood:** 

Märgi joonisele erinevad autentimise kihid:

1. VPN autentimine: OpenVPN  
2. Keskserveri autentimine: Kasutajanimi/parool (Flaskis)  
3. MQTT autentimine: Username/password

##### Näidisdiagrammid  (allpool kui tekstiversioon):

    `[Kasutaja]                            [ESP32 seadmed]`  
    `(avalik IP)                           (kohalik võrk)`  
         `│                                       │`  
         `│                                       │`  
         `│                                  [VPN Ruuter]`  
         `│                                (OpenVPN klient)`  
         `│                                       │`  
         `│                                       │`  
         `└──────────── Internet ─────────────────┘`  
                           `│`  
                           `▼`  
              `┌─────────────────────────────┐`  
              `│  Digital Ocean Droplet      │`  
              `│  (OpenVPN server + teenused)│`  
              `│  10.8.0.1                   │`  
              `├─────────────────────────────┤`  
              `│                             │`  
              `│  [Flask Server :5000] ◄──── HTTP (avalik)`  
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

##### Joonista graafiliselt software stack

Loo software stack diagramm, mis näitab iga komponendi tehnoloogiakihte vertikaalselt ja nende omavahelist suhtlust horisontaalselt.

**ESP32 seadme stack:**

`┌─────────────────────────────────────┐`  
`│      Loogika (Arduino)              │`  
`│   - Valve control (GPIO)            │`  
`│   - Pressure reading (ADC)          │`  
`│   - MQTT publishing                 │`  
`├─────────────────────────────────────┤`  
`│        Library kihid                │`  
`│  - LittleFS (HTML template'id)      │`  
`│  - PubSubClient (MQTT klient)       │`  
`│  - NTPClient (aja sünkronisatsioon) │`  
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

**Keskserveri stack:**

`┌─────────────────────────────────────┐`  
`│      Kasutaja brauser               │`  
`│  (HTML, CSS, Chart.js graafikud)    │`  
`└──────────────┬──────────────────────┘`  
               `│ HTTP (port 80/443)`  
               `▼`  
`┌─────────────────────────────────────┐`  
`│       Flask veebirakendus           │`  
`│  Routes:                            │`  
`│   - /(seadmete nimekiri)            │`  
`│   - /device/<id>/history            │`  
`│   - /export                         │`  
`├─────────────────────────────────────┤`  
`│      Template rendering             │`  
`│      (Jinja2 templates)             │`  
`├─────────────────────────────────────┤`  
`│    InfluxDB client library          │`  
`│  (päringud, andmete lugemine)       │`  
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
             `│  (eraldi Python       │`  
             `│   script või thread)  │`  
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
             `│   ESP32 seadmed         │`  
             `│  (PubSubClient)         │`  
             `└─────────────────────────┘`

##### Suhtlus erinevate komponentide vahel (sequence diagram stiilis):

Näita kuidas erinevad kihid omavahel suhtlevad konkreetse toimingu ajal:

**Stsenaarium 1: ESP32 saadab staatust**

`ESP32                       MQTT Broker      MQTT Listener    InfluxDB`  
`│                               │                │               │`  
`│──mõõtmine──>buffer            │                │               │`  
`│──publish buffer[0]───────────>│                │               │`  
`│  [OK]                         │                │               │`  
`│──eemalda buffer[0]            │                │               │`  
`│                               │──forward──────>│               │`  
`│                               │                │──write───────>│`  
`│                               │                │               │`  
`│──mõõtmine──>buffer            │                │               │`  
`│──publish buffer[0]────X       │                │               │`  
`│  [WiFi katkeb, FAIL]          │                │               │`  
`│                               │                │               │`  
`│──mõõtmine──>buffer            │                │               │`  
`│──mõõtmine──>buffer            │                │               │`  
`│                               │                │               │`  
`│  [WiFi taastub]               │                │               │`  
`│──publish buffer[0]───────────>│                │               │`  
`│  [OK]                         │                │               │`  
`│──eemalda buffer[0]            │                │               │`  
`│──publish buffer[1]───────────>│                │               │`  
`│  [OK]                         │                │               │`  
`│──eemalda buffer[1]            │                │               │`  
`│  ...                          │                │               │`

**Stsenaarium 2: Kasutaja vaatab seadmete nimekirja**

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

**Stsenaarium 3: Kasutaja juhib ESP32 klappi**

   `Nupp          ESP32 Loogika      MQTT Broker      MQTT Listener    InfluxDB`  
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

**Tehnoloogiate legend:**

Lisa diagrammi juurde legend, mis selgitab kasutatud tehnoloogiaid:

* **OpenVPN:** VPN protokoll (UDP/TCP)  
* **MQTT:** Message broker protokoll (TCP, port 1883\)  
* **Mosquitto:** MQTT broker tarkvara  
* **InfluxDB:** Time-series andmebaas (HTTP API, port 8086\)  
* **Flask:** Python web framework  
* **Jinja2:** Template rendering (Flask sees)  
* **NTP:** Network Time Protocol (aja sünkronisatsioon)  
* **LittleFS:** ESP32 failisüsteem  
* **NVS:** ESP32 non-volatile storage (WiFi kredentsiaalid)  
* **PubSubClient:** Arduino MQTT kliendi library  
* **Chart.js:** JavaScript graafikute teek

**Miks need diagrammid on olulised:**

Need diagrammid dokumenteerivad süsteemi arhitektuuri viisil, mida on võimalik:

1. Näidata, et sa mõistad kogu süsteemi terviklikult  
2. Kasutada ise tulevikus kui pead süsteemi uuesti üles seadma  
3. Jagada teiste tudengitega, et nad saaksid sinu lahendusest õppida  
4. Kasutada alusena kui tahad süsteemi laiendada (nt lisada uusi sensoreid)

Diagrammid peaksid olema piisavalt detailsed, et keegi teine saaks nende põhjal süsteemi üles ehitada, kuid mitte nii detailsed, et muutuvad loetamatuks. Kasuta värve, et eristada erinevaid komponente ja andmevooge.

**Soovitatud tööriistad:**

* draw.io (tasuta, veebipõhine)  
* Excalidraw (tasuta, minimalistlik)  
* Lucidchart (tasuta versioon piisab)  
* PlantUML (kui eelistad koodi-põhist lähenemist)

Lisa mõlemad diagrammid (PNG või PDF kujul) oma projekti dokumentatsiooni ja Git reposse.

### Testimine

#### Testinäide 1: MQTT ühenduse kadumine, taastumine

Kui ESP32 või ruuter välisest võrgust ära võtta \- kui ühendus taastub kas vahepealsed mõõtmised saavad üles laetud

#### Testinäide 2: History endpoint

Saada 100 teadet ja kontrolli kas history endpoint näitab õiget kogust ja õigeid andmeid.

### Arenduslogi

### 

### Tulemuised

Vaata et hindamiseks oleks antud ikkagit kõik asjad et saaks:

* Tööfailid (**4** punkti): ESP32 tarkvara ja git repo  
* Simulatsioon/dokumentatsioon (**4** punkti): graafiline ülevaadte projektis  
* Prototüüp (**4** punkti): Digitalocean ja VPN seadistus  
* Dokumentatsioon (**4** punkti): disaini valikute põhjendused, kasutusjuhend

### Tagasiside

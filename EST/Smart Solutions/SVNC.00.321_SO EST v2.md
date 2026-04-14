## Üldinfo
### Eesmärgid
Kursuse eesmärk on anda praktilised ja teoreetilised oskused tööstusroboti juhtimisjaama ehitamiseks. Tudengid ehitavad MG400 robotkäele Raspberry Pi-põhise juhtimisjaama: veebiliides roboti juhtimiseks, ESP32 andurite integratsioon, turvaline kaugligipääs VPN kaudu ja keskne portaal kõigi robotite haldamiseks. Akadeemiline fookus on arvutivõrkude teoorial (IPv4 ruutimine, alamvõrgud, VPN tunneldamine, reverse proxy) ja odava raudvara piirangute analüüsil konkurentse programmeerimise kontekstis (Python GIL, blokeerimine, protsesside ja järjekordade kasutamine).

### Õpiväljundid
Õppeaine läbinud õppija:
- seadistab Raspberry Pi juhtimisjaama (OS, SSH, staatiline IP, võrguliidested);
- selgitab IPv4 ruutimise põhimõtteid (IP-aadress, alamvõrk, gateway, ruutimistabel) ja konfigureerib RPI mitme alamvõrguga (MG400 LAN, WiFi, VPN);
- programmeerib MG400 TCP/IP API-t Pythonis ja ehitab Flask veebiliidese roboti juhtimiseks;
- integreerib ESP32 andureid RPI-ga (USB/UART, WiFi, HTTP GET/POST, MQTT);
- seadistab Digital Ocean dropleti (Linux server, SSH, tulemüür);
- selgitab VPN tunneldamise põhimõtteid (WireGuard krüptograafia, avaliku/privaatvõtme paar, NAT-i läbimine) ja seadistab WireGuard VPN tunneli;
- selgitab reverse proxy tööpõhimõtet ja seadistab nginx keskse portaali jaoks (proxy_pass, HTTPS);
- rakendab kasutaja lukustusmehhanism (üks operaator korraga, vaatamisrežiim teistele);
- seadistab MQTT andmelogi (Mosquitto + InfluxDB) ja ehitab ajaloolise andmete dashboard'i;
- analüüsib odava raudvara (RPI) piiranguid konkurentse programmeerimisel (Python GIL, blokeerimine, protsessid vs. threadid) ja disainib nendega arvestades (eraldi protsessid, järjekorrad, timeout'id);
- mõõdab ja dokumenteerib süsteemi tõrkestsenaariume (ühenduse katkemine, teenuse kokkujooksmine) ja disainib ohutu oleku taastumise;
- ehitab REST API ja demonstreerib keelemudelite (LLM) integratsioonit süsteemiga.

### Sisu lühikirjeldus
Kursus ehitab MG400 robotkäele tervikliku juhtimisjaama Raspberry Pi baasil. Arhitektuur: RPI + ekraan töölaua peal, ühendatud MG400-ga LAN kaabli kaudu ja ESP32 anduritega USB kaudu. RPI jooksutab Flask veebiserverit — operaator juhib robotit brauserist. Digital Ocean dropletil töötab keskne portaal (nginx reverse proxy) mis näitab kõiki ühendatud roboteid ja suunab liikluse läbi VPN tunneli õigele RPI-le.

Kursus sisaldab kahte akadeemilist tuuma: (1) **arvutivõrkude teooria** — IPv4 ruutimise põhimõtted, alamvõrkude eraldamine, VPN tunneldamine (WireGuard krüptograafia ja võtmevahetus), reverse proxy loogika (nginx), NAT-i läbimine. RPI-l on kolm võrguliidest (MG400 LAN, WiFi, VPN) mis annavad praktilise näite ruutimistabelist ja pakettide liikumisest. (2) **Konkurentne programmeerimine ja tõrkekindlus** — kuidas üks odav protsessor (RPI) teenindab mitut perifeeriaseadet samaaegselt, kus on Python GIL-i piirangud, kuidas mõõta blokeerimist ja disainida süsteem mis taastub tõrgetest ilma et pooleliolev töö tuksi läheb.

### Hindamine
Iseseisvate tööde loetelu ja juhised nende tegemiseks:

Hindamisstruktuur: 5 projekti × 20 punkti = max 100 punkti. Integratsiooniprojekt max 70 punkti (ideaalselt vormistatud = C hinne). Kokku võimalik 170 punkti, hinne arvutatakse parimast 100-st. Tudeng valib ise millised projektid teha — integratsiooniprojekti saab esitada iseseisvalt ja ülejäänud tööd lisada punktide parandamiseks.

Iga projekti neli hindamiskategooriat:
- Tööfailid (5p): kood, konfiguratsioonifailid, skriptid — kõik git repos
- Analüüs (5p): latentsuse mõõtmised, tõrkekindluse testid, Jupyter analüüs
- Prototüüp (5p): töötav süsteem
- Dokumentatsioon (5p): seadistusjuhend, arhitektuuriskeem, põhjendused

#### Ülesanne 1: RPI juhtimisstation ja MG400 API
Seadistada Raspberry Pi juhtimisstatsioon: OS, SSH, WiFi, staatiline IP. Õppida IPv4 põhitõed — mis on IP-aadress, subnet mask, gateway; miks MG400 on LAN kaabliga (oma alamvõrk); kuidas RPI räägib MG400-ga (Ethernet) ja maailmaga (WiFi) samaaegselt. Programmeerida MG400 TCP/IP API Python wrapper (port 29999 dashboard, port 30003 movement). Ehitada Flask veebiliides RPI-l: nupud liikumiseks, positsioonide salvestamine, kompressori juhtimine. RPI ekraan näitab staatust. Testi: ava telefonis brauser → RPI IP → liiguta robotit.

#### Ülesanne 2: ESP32 andurid ja RPI integratsioon
Integreerida ESP32 (Andmehõive andurid) RPI-ga. USB/UART: ESP32 saadab JSON-i, RPI loeb pyserial-iga. WiFi alternatiiv: ESP32 AP režiimis, HTTP GET/POST. MQTT tutvustus: ESP32 publitseerib, RPI kuulab, Mosquitto broker lokaalselt RPI-l. Flask teenus RPI-l loeb ESP32 andmeid JA juhib MG400-d — üks veebileht näitab mõlemat. Mõõta latentsust: USB vs WiFi vs MQTT.

#### Ülesanne 3: Digital Ocean droplet ja VPN
Seadistada Digital Ocean droplet (Ubuntu, SSH, tulemüür). WireGuard VPN: droplet on server, iga meeskonna RPI on klient fikseeritud VPN IP-ga (10.0.0.1–10.0.0.4). Nginx reverse proxy dropletil: keskne veebileht mis näitab kõiki ühendatud roboteid (online/offline), klikk robotil → proxy_pass läbi VPN tunneli RPI Flask serverile. Kasutaja näeb RPI veebilehte nagu istuks labori laua taga. Reverse VPN loogika: ESP32 seaded ligipääsetavad kaugelt ilma socket-taseme krüptota — VPN tunnel kaitseb kogu liiklust. IPv4 ruutimine praktikas: RPI-l 3 võrku (MG400 LAN, WiFi, VPN tunnel).

#### Ülesanne 4: MQTT andmelogimine ja ühtne liides
Mosquitto MQTT broker dropletil. ESP32 → RPI → MQTT, InfluxDB dropletil. Ühtne veebiliides RPI-l: juhtimine + reaalajas andurid + ajaloolised graafikud + CSV/JSON eksport. Keskse portaali laiendamine: robotite nimekiri + viimane mõõtmine + olek. Kasutaja lukustus — ainult üks operaator korraga: teised näevad reaalajas (kaamera, andurid, olek) aga nupud on hallid. Uksekell (palun vabasta), admin override (kui ühendus kukkus), auto-timeout (5 min tegevusetust). Doseerimise retseptid. USB kaamera RPI-l. UX test teise meeskonnaga.

#### Ülesanne 5: Tõrkekindlus, REST API ja LLM integratsioon
**Tõrkekindlus**: RPI teeb 5 asja korraga (Flask, MG400, ESP32, MQTT, kaamera). Mõõta piirangud — Python GIL, blocking socket, kaamera hõive blokeerib kõike. Disainida lihtsalt nende ümber (eraldi protsessid, queue, timeout). Ohutu olek: kui midagi on valesti → kompressor kinni. Praktiline test: tõmba ESP32 kaabel välja keset doseerimist, tõmba MG400 LAN välja — mis juhtub? Jupyter Lab: tõrgete logi analüüs, kus on piir kus RPI enam ei piisa.
**REST API**: /status, /dispense, /history, /export — dokumenteeritud JSON. Ligipääsetav läbi keskse portaali (robots.kool.ee/robot/1/api/). Aeglukustus: kaugjuhtimine ainult kui kohalik operaator on RPI ekraanil aktiveerinud. README lõpp-punkt (/api) keelemudelitele. Demonstratsioon: operaator aktiveerib → LLM saadab käsu → robot doseerib → andmed salvestuvad → automaatne lukustamine. Auditlogi.

#### Lisaülesanne: Terviklik juhtimisstation
RPI juhtimisstation kui terviktoode: ühe SD-kaardi kloonimine → uus MG400 on kohe kasutatav. Ühenda LAN MG400-ga, ühenda ESP32 USB-ga, lülita sisse. VPN automaatne ühendus. Lukustus ja tõrkekindlus töötavad. Paigaldatav ühe skriptiga. Dokumentatsioon piisav et teine inimene saab süsteemi üles seada.

### Kontakttundide ajakava
- **[~12.09.26]** RPI seadistus, IPv4 põhitõed, MG400 API, esimene liigutus
- **[~12.09.26]** Flask sissejuhatus, HTML/JS baas
- **[~03.10.26]** Ülesande 1 kaitsmine
- **[~03.10.26]** ESP32 ↔ RPI side (USB/UART ja WiFi)
- **[~15.10.26]** Konsultatsioon 1: IPv4 ruutimine praktikas — subnet, gateway, RPI 3 võrguliidest, `ip route`, `ping`, `traceroute`
- **[~24.10.26]** Ülesande 2 kaitsmine
- **[~24.10.26]** Digital Ocean, Linux server, WireGuard VPN
- **[~05.11.26]** Konsultatsioon 2: VPN praktikas — WireGuard samm-sammult, avaliku/privaatvõtme loogika, NAT-i taga töötamine, tunneli kontroll
- **[~14.11.26]** Ülesande 3 kaitsmine
- **[~14.11.26]** MQTT, InfluxDB, ühtne liides
- **[~25.11.26]** Konsultatsioon 3: nginx reverse proxy — proxy_pass, HTTPS (Let's Encrypt), veaotsing
- **[~05.12.26]** Ülesande 4 kaitsmine
- **[~05.12.26]** REST API, tõrkekindlus, LLM integratsioon
- **[~16.01.27]** Ülesande 5 kaitsmine
- **[TBD]** Integratsiooniprojekti kaitsmine

### Lõpphindamisele pääsemise tingimused
Õppija on positiivsele tulemusele kaitsnud vähemalt ühe ülesande.

### Lõpphindamise skaala
Eristav (A, B, C, D, E, F, mi)

### Lõpphinde kujunemine
5 projekti × 20 punkti = max 100 punkti. Integratsiooniprojekt max 70 punkti (ideaalselt vormistatud = C). Kokku võimalik 170 punkti, hinne arvutatakse parimast 100-st. Integratsiooniprojekti saab esitada iseseisvalt (piisab aine läbimiseks), ülejäänud tööd saab lisada hinde parandamiseks.

|   |   |
|---|---|
| A | 91 punkti |
| B | 81 punkti |
| C | 71 punkti |
| D | 61 punkti |
| E | 51 punkti |
| F | vähem kui 51 punkti |
| mi | Õppija ei ole ülesandeid esitanud ega lõpphindamisel osalenud |

### Võlgnevuste likvideerimine
Kokkuleppel vastutava õppejõuga

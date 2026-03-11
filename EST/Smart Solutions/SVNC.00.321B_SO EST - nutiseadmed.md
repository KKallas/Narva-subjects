## Üldinfo
### Eesmärgid
Anda tudengitele süvendatud oskused hajussüsteemide ehitamises, MQTT protokolli ja ajarea andmebaaside kasutamises, kaamerapõhiste mõõtesüsteemide arendamises ning REST API teenuste loomises keelemudelite integratsiooniga. Kursus eeldab sissejuhatava nutilahenduste kursuse läbimist (SVNC.00.327) ning ehitab seal omandatud veebiliidese, VPN ja krüptograafia oskustele.

### Õpiväljundid
Õppeaine läbinud õppija:
oskab ehitada MQTT-põhise hajussüsteemi mitme ESP32 seadme ja tsentraalse serveri vahel. Tunneb InfluxDB ajarea andmebaasi kasutamist mõõteandmete salvestamiseks ja pärimiseks. Suudab luua Flask-põhise veebiteenuse mis kuvab seadmete andmeid reaalajas. Oskab ehitada kaamerapõhist mõõtesüsteemi ESP32-CAM mooduliga ja integreerida seda olemasoleva infrastruktuuriga. Suudab luua REST API teenuse aeglukustusega kaugjuhtimiseks ja keelemudelite integratsiooniks. Mõistab andmete puhverdamist võrgukatkestuste korral ja suudab disainida tõrkekindlaid süsteeme.

### Sisu lühikirjeldus
Kursus jätkab sealt, kus sissejuhatav nutilahenduste aine lõpetas. Esimene labor ehitab kogu süsteemi ümber MQTT hajusarhitektuurile — Mosquitto vahendaja, InfluxDB andmebaas, Flask veebiliides seadmete jälgimiseks ja andmete ekspordiks. Teine labor lisab kaamerapõhise mõõtesüsteemi mis annab kontrollmõõtmise rõhupõhisele mahuhinnangule. Kolmas labor ehitab HTTP API teenuse aeglukustusega kaugjuhtimiseks ja keelemudelite integratsiooniks. Integratsiooniprojekt ühendab kõik — VPN, MQTT, kaamera, API — ühtseks autonoomseks süsteemiks mitme ligipääsuteega.

### Hindamine
Iseseisvate tööde loetelu ja juhised nende tegemiseks:

#### Ülesanne 1: MQTT hajussüsteem andmelogimisega
Ehita juhtimissüsteem hajusarhitektuurile MQTT avalda/telli protokolliga. Tsentraalne server suhtleb mitme ESP32 seadmega MQTT vahendaja (Mosquitto) kaudu. Kõik andmed logitakse InfluxDB ajareasse. Veebi kasutajaliides (Flask) kuvab seadmete nimekirja, ajaloolisi andmeid ja ekspordi funktsionaalsust. ESP32 hoiab 100 sõnumi puhvrit võrguühenduse kadumise puhuks. Testi: (1) WiFi katkemine ja taasühendus — puhverdatud mõõtmised laetakse üles, (2) ajaloo lõpp-punkt — saada 100 sõnumit, kontrolli arvu ja andmete täpsust.

#### Ülesanne 2: Kaamerapõhine mõõtesüsteem
Ehita visuaalne mõõtesüsteem ESP32-CAM mooduliga, mis annab kontrollmõõtmise rõhupõhisele mahuhinnangu süsteemile. Kasuta ülesande 1 MQTT infrastruktuuri ja InfluxDB andmebaasi mõõtmiste logimiseks. Loo kahe süstlaga testpink kus materjal liigub süstlate vahel solenoidjuhitavate klappide kaudu. Paigalda kaamera kolbi positsiooni jäädvustamiseks. Teosta servade tuvastamine ja teisendamine mahumõõtmiseks süstla geomeetria põhjal. Ehita veebiliides mis kuvab tulemusi ja võrdlust rõhupõhise hinnangu vastu. Süsteem peab logima kõik mõõtmised InfluxDB-sse.

#### Ülesanne 3: HTTP-põhine kaugjuhtimine aeglukustusega
Laienda ülesande 1 Flask teenust REST API-ga masina juhtimiseks. Teosta kasutaja poolt aktiveeritavad juurdepääsuaknad seadistatava aegumisega — kaugjuhtimise lõpp-punktid töötavad ainult kui kohalik kasutaja on need selgelt aktiveerinud. Ise-dokumenteeriv API README lõpp-punktiga keelemudelite integratsiooniks. Integreeri HMAC-SHA256 autentimine (sissejuhatavast kursusest) API päringutele. Päringupiirangud, auditlogi. Demonstreeri täistsüklit: kohalik aktiveerimine, keelemudeliga kaugkasutamine, automaatne lukustamine aegumise korral.

#### Lisaülesanne: Terviklik autonoomne süsteem
Integreeri turvaline VPN juurdepääs, MQTT + InfluxDB infrastruktuur, kaamera valideerimine ja aeglukustusega HTTP API ühtseks süsteemiks mitme ligipääsuteega (kohalik veeb, kaug-VPN, MQTT sõnumid, keelemudelid HTTP kaudu). Kasutatakse liidesena Andmehõive aine masina jaoks.

### Lõpphindamisele pääsemise tingimused
Õppija on positiivsele tulemusele kaitsnud vähemalt ühe labori.

### Minimaalne punktide kogusumma lõpphindamisele pääsemiseks
51

### Lõpphindamise skaala
Eristav (A, B, C, D, E, F, mi)

### Hindamistulemuste teatamise aeg
Info puudub

### Lõpphinde kujunemine
Info puudub

|   |   |
|---|---|
| A | 91 punkti |
| B | 81 punkti |
| C | 71 punkti |
| D | 61 punkti |
| E | 51 punkti |
| F | Õppija on kogunud vähem kui 51 punkti |
| mi | Õppija ei ole ülesandeid esitanud ega lõpphindamisel osalenud |

### Võlgnevuste likvideerimine
Kokkuleppel vastutava õppejõuga

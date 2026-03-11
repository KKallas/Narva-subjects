# **Narva Kolledži tehnikaõppekava**

## **Roboti doseerimissüsteemi ehitamine**

### **Suur pilt**

Kõik ülesanded on seotud ühe projektiga: Dobot MG400 robotile professionaalse doseerimissüsteemi ehitamine. See pole harjutus harjutuse pärast — see on päris turuprobleem. 3000-eurone Dobot seisab ladudes, sest keegi ei tooda tööriistu mida on vaja roboti rakendamiseks.

Tudengid töötavad meeskondades (1–5 liiget, ideaalis 4 meeskonda). Kõik meeskonnad lahendavad sama probleemi — meeskonna sees jagavad liikmed alamsüsteemide vastutust omavahel. Proovi erinevaid rolle: üks kord juhid dokumentatsiooni, teine kord ehitad prototüüpi. Prototüüpimise kursusel valib iga meeskond kõigi tiimide parimatest lahendustest omad ja ehitab terviku prototüübi kokku.

Loogika on lihtne: õpi ehitades midagi vajaliku. Koos.

### **Hindamisfilosoofia**

Iga aine järgib sama ülesehitust: kuus projekti (viis väikest, üks suur), 1–5-liikmelistes meeskondades. Väikesed projektid annavad igaüks kuni 20 punkti (5 × 20 = 100 punkti). Integratsiooniprojekt pakub kaht teed: 40 punkti lisaks väikestele projektidele või 100 punkti iseseisva alternatiivina. Maksimaalselt 100 punkti põhitööst, lisaks boonusvõimalused.

Hindamine on positiivne — saad täispunktid selle eest mida korrektselt teed. See kõlab lihtsalt, kuni kohtud loomulike takistustega: ajapuudus, tehnilised tõrked, meeskonnadünaamika ja päriselu sasipuntrad. Need jõud tagavad et täiuslik tulemus nõuab erakordset tööd, mitte lihtsalt kohaletulekut.

Viis hindamiskategooriat projekti kohta:

* **Tehnilised failid** (4/8 punkti): kood, skeemid, disainifailid
* **Simulatsioon/analüüs** (4/8 punkti): testimine, valideerimine, jõudlusanalüüs
* **Füüsiline teostus** (4/8 punkti): töötav prototüüp, ehituskvaliteet
* **Dokumentatsioon** (4/8 punkti): selged spetsifikatsioonid, disainipõhjendused, kasutusjuhendid
* **Vastastikune hindamine** (4/8 punkti): küsimuste-vastuste sessioon, konstruktiivne tagasiside teistele meeskondadele
* **Boonuspunktid** (10 ülesande kohta): antakse õppejõu vigade avastamise ja parandamise, teiste meeskondade sisulise aitamise või erakordselt hea koostöö eest. Kui arvad et oled teeninud, tuleta kaitsmise ajal õppejõule meelde.

---

## **Andmehõive (6 EAP)**

*Närvisüsteemi ehitamine*

### **Mõte**

Tänapäeva seadmed toodavad pidevalt andmeid. See aine õpetab sind neid andmeid kasutama, puhastama ja analüüsima. Alustad lihtsatest mõõtmistest ja jõuad keerukate tagasisidestatud optimeerimissüsteemideni. Töötad leides küsimusi vastustele mida õppejõud ette ei tea vaid peate koos leidma ja valideerima saadud tulemused. Tudengid töötavad 1–5-liikmelistes meeskondades (ideaalis 4 meeskonda).

### **Mida õpid**

Eristama andmehõivesüsteemi komponente ja mõista riistvarapõhiseid signaalitöötlusahelaid (riistvaraline filtreerimine). Tundma analoog-digitaalmuunduri põhimõtteid ja peamisi veaallikaid. Disainima ja teostama kohandatud lahendusi andmehõive probleemidele, valides sobivaid metoodikaid ja riistvara ning kasutades erinevaid andmeliideseid. Rakendama levinud järeltöötlusmeetodeid mõõteandmete analüüsiks, töötluseks, iseloomustamiseks ja visualiseerimiseks sünkroniseeritud mõõtmistega mitme seadme vahel. Analüüsima, dokumenteerima ja esitlema mõõteandmeid akadeemilise kirjutamise standardite järgi.

### **Töö**

Projektid lähevad järjest raskemaks — esimesed on kõigile jõukohased, hilisemad nõuavad eelnevate tööde käigus omandatud teadmisi. Laborid 1–3 on tehtud, ülesanded 4–5 ja integratsiooniprojekt ehitavad laboritele peale.

**Labor 1: Digitaalne rõhumõõtmine**
Ehita rõhumõõturi prototüüp MPX5700AP rõhuanduri ja M5 Atom (ESP32) mikrokontrolleriga. Kuva rõhku reaalajas (~4Hz) veebilehel. Simuleeri ahelat Falstad-is, testi ostsilloskoobiga. Kogu 30 mõõtmist kolmes kategoorias (2ml, 5ml, 8ml õhku süstlas — 10 igast). Teisenda ADC väärtused Pascaliteks MPX5700AP valemi järgi. Testi lineaarsust süstla mahu ja rõhu vahel. Määra Jupyter Lab'iga süsteemi lahutus, müratase ja viga kogu mõõtevahemikus.

**Vajalikud teemad:** Ajaline maht: 34 tundi

* **Füüsiline prototüüpimine (andur, süstel, torud)**
* **ESP32 (Arduino)**
* **Jupyter Lab**
* **USB UART**
* **Andmeanalüüs ja visualiseerimine**
* **Ahelate simulatsioon (Falstad)**

**Labor 2: Analoogsignaali eeltöötlus ja süsteemi integreerimine**
Testi labori 1 pingejaguri lahendust ja ehita operatsioonivõimendi (LM358N) alternatiiv maketeerimisplaadil. Kalibreeri nihe (nihuta signaali -0,2V) ja skaleerimine (ülemine ots 3,2V-ni). Mõõda täpsust ostsilloskoobiga. Kogu samad 30 mõõtmist opampi lahendusega. Disaini trükkplaat Fusion 360 EDA-s: skeem, komponentide paigutus, rajad, DRC kontroll, Gerber failide genereerimine JLCPCB tellimiseks. Integreeri robotiga: GPIO aktiveerimine, HTTP side ESP32 ja UR5 vahel, juhtimisloogika (rõhk → roboti pea liigutamine).

**Vajalikud teemad:** Ajaline maht: 24 tundi

* **Analoogelektroonika simulatsioon**
* **Fusion 360 EDA põhitõed**
* **Trükkplaadi disain ja tellimine**
* ESP32 (Arduino)
* Jupyter Lab (võrdlusanalüüsiks)
* USB UART

**Labor 3: Mahumõõtmise meetodid**
Loo ja testi 2 meetodit (4-st valikust) süstla täitetaseme mõõtmiseks suruõhu impulsi abil. Põhimõte: püsiv rõhuallikas + solenoidklapp. Valikud: (1) MPX5700AP otse M5 Atomile, (2) pingejaguri kaudu kahetuumalise lõimestamisega, (3) opampiga 0–3,3V skaleerimisega ja digitaalfiltreerimisega, (4) opamp Schmitt-päästikuna positiivse tagasisidega. Disaini üks trükkplaat mis toetab mõlemat valitud meetodit hüppiklõhkude või 0Ω takistitega. Kogu 6×100 mõõtmist erinevatel täitetasemetel (10ml, 8ml, 6ml, 4ml, 2ml, 0ml). Võrdle täpsust ja töökindlust mõlema meetodi vahel.

**Vajalikud teemad:** Ajaline maht: 30 tundi

* Analoogelektroonika simulatsioon
* ESP32 (Arduino)
* Jupyter Lab
* USB UART
* **Trükkplaadi tellimine**
* **Analoogfiltreerimine**
* **Komparaatorahel ja katkestused**

**Ülesanne 4: Testpingi ja masinõppe mudeli ehitamine**
Kasuta labori 3 mõõteandmeid (6×100 mõõtmist kahest meetodist) masinõppe mudeli treenimiseks. Ehita testpink paralleelsete mõõtesüsteemidega täiendavate andmete kogumiseks erinevate teadaolevate mahtude juures. Kasuta lihtsat lineaarset regressioonimudelit otsingutabeli (LUT) ehitamiseks reaalajalise süsteemi jaoks ja testi hindamissüsteemi.

**Vajalikud teemad:** Ajaline maht: 24 tundi

* ESP32 (Arduino)
* Jupyter Lab
* USB UART
* Doboti põhitõed
* Filtreerimine (analoog/digitaalne/ML)
* **Scikit-learn**

**Ülesanne 5: Kvaliteedi ennustav mudel**
Joonistame levinumad kujundid mida kasutatakse silikooni või joodisepasta doseerimiseks: sirge joon, kaar ja pinnatäide. Ehita testpink sisend- ja väljundpuhvriga testplaatide hoidmiseks — robot saab teha 5 tükki enne kui lisad uued puhtad plaadid ja kogud valmis proovid. Tee plaatidest kõrglahutusega pildid ja analüüsi milline kiiruse, rõhu ja nurkkiiruse kombinatsioon annab parima tulemuse.

**Vajalikud teemad:** Ajaline maht: 36 tundi

* ESP32 (Arduino)
* Jupyter Lab
* USB UART
* Doboti põhitõed
* Filtreerimine (analoog/digitaalne/ML)
* NTP sünkroniseerimine
* **Scikit-learn**

**Integratsiooniprojekt: Tagasisidestatud optimeerimine**
See projekt nõuab rõhupõhist protsessijälgimist, mahuhinnangu andmist ja kvaliteedi hindamist — võimekusi mis arendati järk-järgult laborites 1–3 ja ülesannetes 4–5, kuid mille integratsiooniraja tudengid peavad iseseisvalt ühtse süsteemina disainima. Disaini süstladoseerija UR5 või Doboti jaoks mis kasutab suruõhku silikooni/joodisepasta väljasurumiseks ja suudab teha kvaliteetseid sirgeid jooni, kaari ja pinnatäidet (ühtlase laiuse ja paksusega, hoides võimalikult lähedal kavandatud kujule). Testimiseks ehita automatiseeritud testid kus on puhtate plaatide sisendpuhver, tööala, kõrglahutusega pildistamine ja väljundpuhver. Puhver võib olla rohkem kui 5, parem 10–30.

## **Hindamisstruktuur**

* **Väiksemad projektid**: 5 projekti × 20 punkti = maksimaalselt 100 punkti
* **Integratsiooniprojekt**: maksimaalselt 100/40 punkti
* **Võimalik kokku**: 140 punkti
* **Hinde A lävi**: 91–100 punkti põhi 100-st

### **Hindamiskriteeriumid**

Iga projekti hinnatakse viies valdkonnas:

**Väiksemad projektid (kuni 20 punkti):**

* Tarkvara/tööfailid (4 punkti): kood, EDA disain või tehnilised failid
* Simulatsioon (4 punkti): sobivad simulatsioonimeetodid, analüüs, testimine
* Prototüüp/füüsiline projekt (4 punkti): teostus, kvaliteet, funktsionaalsus
* Dokumentatsioon (4 punkti): spetsifikatsioonid, disainivalikute põhjendused, juurutusjuhend
* Küsimuste-vastuste sessioon ja tagasiside (4 punkti): iga sisuline küsimus annab punkte

**Integratsiooniprojekt (kuni 40 punkti):**

* Tarkvara/tööfailid (8 punkti)
* Simulatsioon (8 punkti)
* Prototüüp/füüsiline projekt (8 punkti)
* Dokumentatsioon (8 punkti)
* Küsimuste-vastuste sessioon ja tagasiside (8 punkti)

### **Esitamisnõuded**

* Projektid tuleb esitada 72 tundi enne kaitsmist
* Meeskondadel on 5 minutit esitluseks
* 15 minutit küsimuste ja tagasiside jaoks meeskonna kohta
* Küsimuste eest saab punkte; õppejõud põhjendab punktide mahaarvamist

### **Hindamisskaala**

* **91–100 punkti**: A
* **81–90 punkti**: B
* **71–80 punkti**: C
* **61–70 punkti**: D
* **51–60 punkti**: E
* **0–50 punkti**: F

**Miinimum sooritamiseks**: 51 punkti. Tudeng valib ise millised projektid teha. Näiteks: kaks väikest projekti + integratsiooniprojekt (80 punkti) või kolm väikest projekti (60 punkti).

**Oluline**: kui füüsiline teostus täielikult ebaõnnestub, on maksimaalsed punktid siiski saavutatavad — kui tudeng näitab insenerimõtlemist, selgitades rikke põhjusi ja pakkudes alternatiive.

## **Kontakttundide ajakava**

* **[13.09]** Analoog- ja digitaalmõõteahelad, rakendused ja tööpõhimõtted
* **[13.09]** ESP32 mikroprotsessor ja Arduino arenduskeskkond
* **[13.09]** Fusion 360 EDA lihtsate ühekihiliste trükkplaatide jaoks
* **[4.10]** Andmete kogumine ja analüüs Jupyter Lab'iga
* **[4.10]** Labori 1 kaitsmine
* **[25.10]** Doboti koostöö signaalide kaudu
* **[25.10]** Analoogmüra ja filtreerimine
* **[25.10]** Labori 2 kaitsmine
* **[15.11]** Analoogfiltri töötuba
* **[15.11]** Labori 3 kaitsmine
* **[6.12]** Masinõppe mudelid ja scikit-learn
* **[6.12]** Ülesande 4 kaitsmine
* **[17.01]** Ülesande 5 kaitsmine
* **[TBD]** Lisaülesande kaitsmine

---

## **Nutilahendused (6 EAP)**

*Aju ehitamine*

### **Mõte**

Luua IoT süsteeme mida ka mikro- ja väiketootjad saavad päriselt kasutada ja mille investeering tasub ära alla aastaga. Muuta seadmete füüsilised liidesed veebiliidesteks, rakendada korralik turvalisus ja teha kõik ligipääsetavaks standardprotokollide kaudu. Rõhk on praktilistel lahendustel, maksimaalsel iseseisval ja mitme varuplaaniga. Panustades universaalsetele veebiliidestele spetsiaalse riistvara asemel omandavad tudengid oskused ja süsteemse mõtlemise mis pikendab raskete masinate eluiga järgmise 20 aasta sisse.

Tudengid töötavad 1–5-liikmelistes meeskondades (ideaalis 4 meeskonda). Iga seade saab oma intelligentse kasutajaliidese. Sel aastal ehitame Doboti robotile süstladoseerija kasutajasõbraliku veebiliidesega seire ja juhtimise jaoks.

### **Mida õpid**

Luua täiesti isemajandavaid integreeritud IoT süsteeme. Kasutame M5Stacki ESP32-t ja Arduino arenduskeskkonda ning veebiliidese lahendusi optimaalse hinna-jõudluse suhtega. Lisaks kohalikule ligipääsule ehitame MQTT andmebaasi dropletid logimiseks ja väliselt juhitud funktsionaalsuse pakkumiseks. Et hoida asju samas sfääris ja anda keelemudelitele ligipääs uutele liidestele, ehitame HTTP API liidese koos veebiliidesega. Rakendame turvameetmeid: turvalised MQTT vahendajad pilveteenustes ja kaitstud tunnelid veebiliidese kaugjuurdepääsuks.

### **Töö**

Projektid lähevad järjest raskemaks. Laborid 1–3 on tehtud, ülesanded 4–5 ja integratsiooniprojekt (Turvaline kaugjuhitav doseerimissüsteem) ehitavad laboritele peale.

**Labor 1: Veebipõhine juhtimisliides**
Loo M5 Atom Lite peal veebiserver mis teenindab ühte veebilehte ja pakub kahte API lõpp-punkti. Esimene versioon juhib pardal olevat RGB LED-i värvi veebiliidese kaudu. GET /get tagastab praeguse LED värvi 8-bitise RGB hex-väärtusena, GET /set?value=<väärtus> muudab värvi. Veebileht kuvab praegust värvi, sisaldab värvivalijat ja WiFi seadistuse nuppu. Ainult AP režiim (WiFi otse seadmesse). Testi: (1) LED värvimuutuse sujuvus — leia optimaalne värskendussagedus (1Hz→50Hz) kus kasutaja tajub sujuvat üleminekut ilma vilkumiseta, (2) ESP32 ülekoormuse test — eskaleeri 10-st 100+ SET käsuni sekundis, mõõda vastusaegu, tuvasta millal süsteem ebaõnnestub ja taastub.

**Vajalikud teemad:** Ajaline maht: 24 tundi

* **Arduino & ESP32**
* **ESP32 sidepõhitõed (I2C, SPI, UART, AD, DA)**
* **Veebiarenduse põhitõed (Preact & water.css)**
* **Jupyter Lab QR-koodi generaator**

**Labor 2: Turvaline kaugligipääs krüptograafiaga**
Lisa WiFi kliendirežiim RGB LED juhtimisele ja krüptograafiline turvakiht. Loo avalik ligipääs VPN releed kaudu Digital Oceani dropletil + OpenVPN serveriga. Teosta käsusignatuuride autentimine ajatemplipõhise HMAC-SHA256-ga. AP režiimi leht krüptovõtme üleslaadimiseks (ühekordne, seejärel ligipääsmatu). Allkirjastatud API päringud: GET /set?value=<värv>&signature=<HMAC-SHA256>. VPN-ühendatud ruuter doseerimissüsteemi turvaliseks ligipääsuks. Testi: (1) õige võti töötab, vale ebaõnnestub, (2) käsu latentsus — mõõda aeg ESP32 käsu vastuvõtmisest vastuse saatmiseni (määrab signatuuri ajaakna).

**Vajalikud teemad:** Ajaline maht: 28 tundi

* **Serveri dropleti seadistus**
* **Linuxi tööriistade põhitõed**
* **Võrgupõhitõed (IP, marsruutimine, NAT, tulemüüri seadistus)**
* **VPN seadistus (OpenVPN)**
* **HMAC-SHA256 krüptograafia**

**Labor 3: MQTT hajussüsteem andmelogimisega**
Ehita LED juhtimissüsteem ümber hajusarhitektuurile MQTT avalda/telli protokolliga. Tsentraalne server suhtleb mitme ESP32 seadmega MQTT vahendaja (Mosquitto) kaudu. Kõik andmed logitakse InfluxDB ajareasse. Veebi kasutajaliides (Flask) kuvab seadmete nimekirja, ajaloolisi andmeid ja ekspordi funktsionaalsust. ESP32 hoiab 100 sõnumi puhvrit võrguühenduse kadumise puhuks. Seadmete nimekiri: kõik seadmed, viimati nähtud aeg, olek, klapi seisund ja rõhk. Ajalugu: rõhugraafik (viimased 24h), klapi oleku ajajoon, sündmuslogi. Eksport: CSV/JSON filtreerimisega seadme, meeskonna ja kuupäeva järgi. Testi: (1) WiFi katkemine ja taasühendus — puhverdatud mõõtmised laetakse üles, (2) ajaloo lõpp-punkt — saada 100 sõnumit, kontrolli arvu ja andmete täpsust.

**Vajalikud teemad:** Ajaline maht: 30 tundi

* **MQTT protokoll ja osapooled (avaldaja, vahendaja, tellija)**
* **Flask**
* **InfluxDB ajarea andmebaas**
* **LittleFS ja seadme failisüsteem**
* Arduino & ESP32

**Vajalikud teemad:** Ajaline maht: 30 tundi

* Jupyter Lab
* **MQTT protokoll ja osapooled (avaldaja, vahendaja, tellija)**
* **Flask**
* **Andmebaasi seadistus**

**Ülesanne 4: Kaamerapõhine mõõtesüsteem**
Ehita visuaalne mõõtesüsteem M5-CAM-iga, mis annab kontrollmõõtmise Andmehõives arendatud rõhupõhisele mahuhinnangu süsteemile. Kasuta labori 3 MQTT infrastruktuuri ja InfluxDB andmebaasi mõõtmiste logimiseks. Loo kahe süstlaga testpink kus materjal liigub süstlate vahel solenoidjuhitavate klappide kaudu — nii saab korrata mõõtmisi ilma materjali raiskamata. Paigalda kaamera kolbi positsiooni jäädvustamiseks ühtlase nurga ja valgustusega. Teosta käivitatud pildihõive testi lõpus, servade tuvastamine kolvi leidmiseks kaadris ja teisendamine mahumõõtmiseks süstla geomeetria põhjal. Ehita veebiliides mis kuvab jäädvustatud pilti, tuvastatud kolbi positsiooni, arvutatud mahtu ja võrdlust rõhupõhise hinnangu vastu. Süsteem peab logima kõik mõõtmised InfluxDB-sse hilisemaks analüüsiks sadade testitsüklite ulatuses.

**Vajalikud teemad:** Ajaline maht: 32 tundi

* **ESP32Cam ja** Arduino
* Veebiarenduse põhitõed
* **Jupyter Lab pilditöötlus**

**Ülesanne 5: HTTP-põhine kaugjuhtimine aeglukustusega**
Laienda labori 3 Flask teenust Digital Oceanis REST API-ga masina juhtimiseks. Teosta kasutaja poolt aktiveeritavad juurdepääsuaknad seadistatava aegumisega — kaugjuhtimise lõpp-punktid töötavad ainult kui kohalik kasutaja on need selgelt aktiveerinud. Seire lõpp-punktid (labori 3 ajaloo ja ekspordi liidesed) jäävad kättesaadavaks, juhtimise lõpp-punktid nõuavad aktiivset sessiooni. Ise-dokumenteeriv API README lõpp-punktiga keelemudelite integratsiooniks. Integreeri labori 2 HMAC-SHA256 autentimine API päringutele. Päringupiirangud, auditlogi. Demonstreeri täistsüklit: kohalik aktiveerimine, keelemudeliga kaugkasutamine, automaatne lukustamine aegumise korral.

**Vajalikud teemad:** Ajaline maht: 34 tundi

* Arduino ja ESP32
* Flask
* **Keelemudelite liides andmete lugemiseks ja üksikute masinate juhtimiseks**

**Integratsioon: Terviklik autonoomne süsteem**
See projekt nõuab turvalist kaugligipääsu, pilveinfrastruktuuri, kaamera integreerimist ja aeglukustusega API juhtimist — võimekusi mis arendati järk-järgult laborites 1–3 ja ülesannetes 4–5, kuid mille integratsiooniraja tudengid peavad iseseisvalt ühtse süsteemina disainima. VPN (labor 2), MQTT + InfluxDB (labor 3), veebiliides (labor 1), HMAC-SHA256 autentimine (labor 2), kaamera valideerimine (ülesanne 4), HTTP API (ülesanne 5) — ühtne süsteem mitme ligipääsuteega (kohalik veeb, kaug-VPN, MQTT sõnumid, keelemudelid HTTP kaudu). Kasutatakse liidesena Andmehõive aine masina jaoks.

## **Hindamisstruktuur**

* **Väiksemad projektid**: 5 projekti × 20 punkti = maksimaalselt 100 punkti
* **Integratsiooniprojekt**: maksimaalselt 100/40 punkti
* **Võimalik kokku**: 140 punkti
* **Hinde A lävi**: 91–100 punkti põhi 100-st

### **Hindamiskriteeriumid**

Iga projekti hinnatakse viies valdkonnas:

**Väiksemad projektid (kuni 20 punkti):**

* Tarkvara/tööfailid (4 punkti): tarkvarahoidla, skriptid või tehnilised failid
* Avaliku serveri seadistus (4 punkti): Kubernetes, Docker, SSH, pip
* Prototüüp (4 punkti): teostus, kvaliteet, funktsionaalsus
* Dokumentatsioon (4 punkti): spetsifikatsioonid, disainivalikute põhjendused, juurutusjuhend
* Küsimuste-vastuste sessioon ja tagasiside (4 punkti): iga sisuline küsimus annab punkte

**Integratsiooniprojekt (kuni 40 punkti):**

* Tarkvara/tööfailid (8 punkti)
* Automaatse paigalduse seadistusfailid (8 punkti)
* Prototüüp/füüsiline projekt (8 punkti)
* Dokumentatsioon (8 punkti)
* Küsimuste-vastuste sessioon ja tagasiside (8 punkti)

### **Esitamisnõuded**

* Projektid tuleb esitada 72 tundi enne kaitsmist
* Meeskondadel on 5 minutit esitluseks
* 15 minutit küsimuste ja tagasiside jaoks meeskonna kohta
* Küsimuste eest saab punkte; õppejõud põhjendab punktide mahaarvamist

### **Hindamisskaala**

* **91–100 punkti**: A
* **81–90 punkti**: B
* **71–80 punkti**: C
* **61–70 punkti**: D
* **51–60 punkti**: E
* **0–50 punkti**: F

**Miinimum sooritamiseks**: 51 punkti. Tudeng valib ise millised projektid teha. Näiteks: kaks väikest projekti + integratsiooniprojekt (80 punkti) või kolm väikest projekti (60 punkti).

**Oluline**: kui prototüüp ei saavuta täielikku funktsionaalsust, on maksimaalsed punktid siiski saavutatavad — kui tudeng näitab insenerimõtlemist, selgitades rikke põhjusi ja pakkudes alternatiive.

## **Kontakttundide ajakava**

* **[13.9]** Veebi põhitõed (Preact ja water.css)
* **[13.9]** VPS ja Linuxi tööriistad / konteinerid ja automatiseerimine
* **[4.10]** Labori 1 kaitsmine
* **[25.10]** Marsruutimise põhitõed
* **[25.10]** Labori 2 kaitsmine
* **[15.11]** MQTT ja InfluxDB
* **[15.11]** Labori 3 kaitsmine
* **[6.12]** API ja keelemudelite integratsioon
* **[6.12]** Ülesande 4 kaitsmine
* **[17.01]** Ülesande 5 kaitsmine
* **[TBD]** Lisaülesande kaitsmine

---

## **3D Printimine ja CAD (6 EAP)**

*Keha ehitamine*

### **Mõte**

Omandada täielik mehhaanilise disaini töövoog kontseptsioonist valideeritud füüsilise detailini. Õppida parameetrilist modelleerimist, simulatsioonipõhist optimeerimist ja täiustatud tootmisvõtteid mis tasakaalustavad funktsionaalseid nõudeid tootmispiirangutega. Kasutada tehisintellekti generatiivse disaini tööriistu osana tänapäevasest inseneripraktikast.

Tudengid töötavad 1–5-liikmelistes meeskondades (ideaalis 4 meeskonda). Läbi iteratiivsete praktiliste tööde omandavad tudengid oskused optimeeritud disainide loomiseks, sealhulgas masinõppepõhiste generatiivse disaini tööriistade kasutamise.

### **Mida õpid**

Luua parameetrilisi mudeleid piirangupõhise disaini põhimõtete abil Fusion 360-s. Disainida funktsionaalseid koostusid erinevate ühendusviisidega (keermestatud detailid, poldid, liimühendused). Rakendada generatiivse disaini meetodeid optimeerimiseks ning analüüsida ja valideerida disaine parameetrilise tugevussimulatsiooniga. Omandada 3D printimise edasijõudnud tehnikaid: print-in-place mehhanismid, mitmesunnaline printimine ja komponentide lisamine. Koostada tehnilisi jooniseid ISO standardite järgi sobivate mõõtmete ja tolerantsidega.

### **Töö**

Projektid lähevad järjest raskemaks. Laborid 1–3 on tehtud, ülesanded 4–5 ja integratsiooniprojekt ehitavad laboritele peale.

**Labor 1: Parameetriline süstlahoidik**
Loo süstlahoidiku esimene prototüüp Dobot MG400 roboti jaoks. Disaini Fusion 360-s parameetriliste piirangutega mudel mis võimaldab hõlpsalt muuta süstla diameetrit, asendit ja nurka. Süstla kinnitus roboti tööriistaflantsile, säilitades 80% tööruumist lauatasandil. Toeta pneumaatilise kolvi kinnitust automaatseks doseerimiseks. Testi mitmeid süstlamõõte: 5ml, 10ml, 20ml. Optimeeri asend ja nurk maksimaalse tööruumi säilitamiseks. Testi: (1) Fusion 360 lõikumiskontroll — veendu et detailid ei läbi üksteist enne printimist, (2) mõõtmete kontroll — vähemalt 3 mõõdet iga telje kohta nihkkaliibriga pärast printimist.

**Vajalikud teemad:** Ajaline maht: 34 tundi

* **Fusion 360 visand ja piirangud**
* **Fusion 360 koostud ja kinnitused**
* **3D printeri viilutaja ja esimene print, FDM piirangud**

**Labor 2: Vedrumehhanismiga kiirvahetusklamber**
Paranda süstlahoidikut 3D-prinditud vedrumehhanismiga ilma tööriistadeta kiireks süstlavahetuseks. Disaini ümber UR5 roboti jaoks (erinev tööriistaflantsile kui MG400). Süstla positsiooni korratavus ±1mm piires pärast vahetust. Pneumaatilise kolvi kinnitus ühilduv kiirvahetusmehhanismiga. Modulaarsus nii MG400 kui UR5 toetamiseks. Uuri vedru- ja hingekonstruktsioone 3D printimiseks. Modelleeri UR5 tööriistaflantsile kinnitus spetsifikatsiooni järgi. Loo 3 versiooni testimiseks. Testi: (1) lõikumiskontroll, (2) mõõtmete kontroll nihkkaliibriga.

**Vajalikud teemad:** Ajaline maht: 38 tundi

* Fusion 360 visand ja piirangud
* Fusion 360 koostud ja kinnitused
* 3D printeri viilutaja
* **Fusion 360 mehhaaniline simulatsioon**
* **Fusion 360 2D joonis**

**Labor 3: Integreeritud tootmiskorpus**
Disaini ja prindi funktsionaalne integreeritud korpus mis ühendab kogu elektroonika, pneumaatika ja mehaanika kompaktseks koostuks. Mitte maketeerimisplaadi prototüüp — tootmisvalmis vormitegur mehhaanilise tugevuse ja soojusjuhtimisega. Pneumaatika: minimeeri "surnud mahtu" õhku süsteemis (lühemad torude ja õõnsuste teed parema reageerimise ja täpsuse jaoks). Elekter: M5 Atom toide roboti 24V-st regulaatori kaudu; solenoid 24V; signaali töötlemine (0–3,3V→0–10V võimendus või 3,3V→24V loogikataseme nihe MOSFET/optokooplerga). Signaaliterviklus: EMI kaitse rõhusignaalidele. Mehaanika: trükkplaat sisseehitatud struktuurse tugevdusena; 16mm torud ja M5 keermestangid tugevuseks; pneumaatiline otsik süstla lähedal. Kasutajaliides: M5 Atom nupp hädaseiskamiseks; kiire süstlavahetus ilma tööriistadeta. Koosta komponentide skeem (draw.io), modelleeri kõik sisekomponendid Fusionis, planeeri prindi-pausi punktid komponentide sisestamiseks, prindi, pane kokku ja testi.

**Vajalikud teemad:** Ajaline maht: 22 tundi

* **Integratsioonigraaf (draw.io)**
* **Materjalide nimekiri (BOM)**
* Fusion 360 visand ja piirangud
* Fusion 360 koostud ja kinnitused
* Fusion 360 mehhaaniline simulatsioon
* **3D printeri viilutaja mitmesunnaliseks printimiseks**
* **Prindi-pausi töövoog komponentide sisestamisega**
* **Kokkupanekujuhendi dokumentatsioon**

**Ülesanne 4: Generatiivne vs. insenerteadmistega automatiseeritud disain**

Loo labori 1 süstlakinnitus uuesti kahe tehisintellekti meetodiga ja testi mõlemat oma algse käsitsidisaini vastu. Esiteks kasuta Fusion 360 generatiivset disaini korrektselt määratud kinnituspunktide, koormustega (doseerija mass, roboti kiirendus, konsoolmoment), keelualade ja tootmispiirangutega. Aktsepteeri mida algoritm pakub.

Teiseks ehita automatiseeritud parameetriline mudel mis sisaldab inseneriteadmisi — mitte esteetilist optimeerimist vaid konstruktiivset loogikat. See tähendab programmeeritud ribide paigutust koormusteedele, seinapaksust arvutatuna oodatavatest pingetest, täitemustrit kooskõlas jõusuundadega, geomeetriat mis prindib kiiresti kuna arvestab FDM piiranguid algusest peale. Kasuta tööriistu nagu nTop, Synera, Grasshopper või Pythoni skriptimist FEA valideerimisega ahelas. Eesmärk: detail mis prindib kiiremini kui generatiivne versioon ja on vähemalt sama tugev.

Prindi kõik kolm versiooni. Disaini korratav tugevus- ja läbipainde test kasutades MG400-t mõõteriistana — programmeeri ühtlased koormuse rakendamise jadad ja mõõda vastust fikseeritud punktides. Testi iga disaini mitut eksemplari samade protokollidega.

Dokumenteeri võrdlus: printimisaeg, mass, läbipaine etalonkoormuse all, purunemismood ja kui hästi iga meetodi ennustused kattusid füüsiliste tulemustega. Põhiküsimus pole milline detail näeb keerulisem välja — vaid kas inseneriteadmiste sisestamine automatiseeritud tööriistadesse ületab algoritmide pimedat otsimist disainiruumis.

**Vajalikud teemad:** Ajaline maht: 30 tundi

* Fusion 360 generatiivse disaini töövoog
* Parameetriline/automatiseeritud modelleerimine sisseehitatud konstruktiivse loogikaga
* FEA seadistus ja koormustee analüüs
* FDM prindi optimeerimine (orientatsioon, tugestinad, aeg)
* MG400-põhise korratava testseadme disain
* Kvantitatiivne võrdlusmetoodika

**Ülesanne 5: Modulaarne testpingi raamisüsteem**
Disaini standardne alumiiniumraam (100×100 mm põhiühik) täpsete kinnituskohtadega mis aktsepteerib vahetatavaid 3D-prinditud tarvikuplaate. Metallraam annab jäikuse, korratavuse ja fikseeritud registreerimise roboti alusele. Prinditud sisestused klõpsuvad või poltuvad raami ja seadistavad tööpinna konkreetsete ülesannete jaoks: süstlahoidja positsioonid, plaadipuhvrid, kaamerakinnitused, andurikronsteenid. Disaini raam CNC tootmiseks korrektsete ISO tehniliste joonistega, GD&T kriitiliste registreerimispindade jaoks ja tolerantsianalüüsiga sisestuse sobitumiseks. Disaini vähemalt kolm erinevat sisestuse konfiguratsiooni süsteemi paindlikkuse demonstreerimiseks. Valideeri toodetud raam spetsifikatsioonide vastu ja kinnita et erinevate prindipartiide sisestused saavutavad ühtlase positsioneerimise.

**Vajalikud teemad:** Ajaline maht: 24 tundi

* Fusion 360 2D joonise keskkond
* ISO tehniliste jooniste standardid
* GD&T põhitõed
* Tolerantside kuhjumise analüüs (raami-sisestuse liides)
* CNC tootmise kommunikatsioon
* Modulaarse disaini põhimõtted
* Metroloogia ja kontrollmeetodid
* Sisestuste vahetatavuse valideerimine

**Integratsiooniprojekt: Doseerimissüsteemi täielik mehhaanikapakett**
See projekt nõuab parameetrilist disaini (labor 1), print-in-place mehhanisme (labor 2), süsteemiintegratsiooni (labor 3), generatiivset optimeerimist (ülesanne 4) ja modulaarset tarvikuid (ülesanne 5) — võimekusi mis arendati järk-järgult laborites 1–3 ja ülesannetes 4–5, kuid mille integratsiooniraja tudengid peavad iseseisvalt ühtse süsteemina disainima. Disaini doseerimissüsteemi täielik mehhaanikapakett: robotile paigaldatav doseerija koost optimeeritud tööriistkinnitusega (labori 1 parameetriline ja ülesande 4 generatiivne disain), kiirvahetatav süstlamehhanism (labor 2), integreeritud elektroonika korpus (labor 3) ja modulaarne testpingi raam rakendusspetsiifiliste sisestustega (ülesanne 5). Tooda tootmisvalmis dokumentatsioon kõigi komponentide jaoks — 3D prindifailid valideeritud seadetega, CNC joonised GD&T-ga metallraami jaoks ja kokkupanekujuhendid. Valideeri terviklik süsteem: testi generatiivse disaini ennustusi füüsiliste mõõtmiste vastu, kinnita sisestuste vahetatavust kogu raamisüsteemis, kinnita et süstla vahetamine on ühekäeline. Valmis süsteem peab füüsiliselt integreeruma Nutilahenduste elektroonika ja Andmehõive andurite infrastruktuuriga.

## **Hindamisstruktuur**

* **Väiksemad projektid**: 5 projekti × 20 punkti = maksimaalselt 100 punkti
* **Integratsiooniprojekt**: maksimaalselt 100/40 punkti
* **Võimalik kokku**: 140 punkti
* **Hinde A lävi**: 91–100 punkti põhi 100-st

### **Hindamiskriteeriumid**

Iga projekti hinnatakse viies valdkonnas:

**Väiksemad projektid (kuni 20 punkti):**

* Tööfailid (4 punkti): Fusion 360 failid
* Simulatsioon (tugevus, termiline, iteratiivsed disainid) (4 punkti): Fusion 360 analüüs
* Prototüüp (4 punkti): teostus, kvaliteet, funktsionaalsus
* Dokumentatsioon (4 punkti): spetsifikatsioonid, disainivalikute põhjendused, juurutusjuhend
* Küsimuste-vastuste sessioon ja tagasiside (4 punkti): iga sisuline küsimus annab punkte

**Integratsiooniprojekt (kuni 40 punkti):**

* Tarkvara/tööfailid (8 punkti)
* Simulatsioon (8 punkti)
* Prototüüp/füüsiline projekt (8 punkti)
* Dokumentatsioon (8 punkti)
* Küsimuste-vastuste sessioon ja tagasiside (8 punkti)

### **Esitamisnõuded**

* Projektid tuleb esitada 72 tundi enne kaitsmist
* Meeskondadel on 5 minutit esitluseks
* 15 minutit küsimuste ja tagasiside jaoks meeskonna kohta
* Küsimuste eest saab punkte; õppejõud põhjendab punktide mahaarvamist

### **Hindamisskaala**

* **91–100 punkti**: A
* **81–90 punkti**: B
* **71–80 punkti**: C
* **61–70 punkti**: D
* **51–60 punkti**: E
* **0–50 punkti**: F

**Miinimum sooritamiseks**: 51 punkti. Tudeng valib ise millised projektid teha. Näiteks: kaks väikest projekti + integratsiooniprojekt (80 punkti) või kolm väikest projekti (60 punkti).

**Oluline**: kui prototüüp ei saavuta täielikku funktsionaalsust, on maksimaalsed punktid siiski saavutatavad — kui tudeng näitab insenerimõtlemist, selgitades rikke põhjusi ja pakkudes alternatiive.

## **Kontakttundide ajakava**

* **[12.09]** Fusion 360 ja parameetriline disain
* **[12.09]** 3D printer, esimene print
* **[12.09]** Mitmekomponendiline objekt, vedru Fusion 360-s
* **[3.10]** Projekti dokumenteerimine
* **[3.10]** Labori 1 kaitsmine
* **[24.10]** FDM disaini eripärad (tugevusjooned, materjalid)
* **[24.10]** Printeri CAM objektide lisamiseks või mitmesunnaliseks printimiseks
* **[24.10]** Labori 2 kaitsmine
* **[14.11]** Prindi-pausi töövoog ja komponentide sisestamine
* **[14.11]** Labori 3 kaitsmine
* **[5.12]** Fusion 360 generatiivne disain
* **[5.12]** Ülesande 4 kaitsmine
* **[17.01]** Ülesande 5 kaitsmine
* **[TBD]** Lisaülesande kaitsmine

---

## **Prototüüpimine (3 EAP)**

*Kõik kokku*

### **Mõte**

Muuda kolme kursuse jagu komponente üheks töötavaks süsteemiks. Vali kõigi meeskondade parimad tehnoloogiad, integreeri need ja loo midagi mis on valmis päriselt kasutamiseks. Siin muutub õppimine loomiseks.

Tudengid tulevad valmis alamsüsteemidega: Andmehõivest (anduri- ja mõõtesüsteemid), Nutilahendusest (juhtimisliidesed ja kaugligipääs) ja 3D Printimisest/CAD-ist (mehhaaniline disain ja tarvikud). Väljakutse on integratsioon ja viimistlemine, mitte nullist alustamine.

Tuginedes esimese semestri kolmele paralleelkursusele, järgib see aine tööstuslikke arenduspõhimõtteid — alustades lihtsatest juhtimissüsteemidest ja liikudes andurite integreerimise ja täpse liikumisjuhtimiseni. Fookus on väikeste tööstusrobotite (Dobot) võimekuse laiendamisel spetsiaaltööriistade loomise kaudu. Kuna väikestele robotitele standardtööriistu ei toodeta, arendavad tudengid tööstuslikke lahendusi nagu doseerimissüsteemid, UV kõvendusseadmed, kruvikeerajad ja jootelahendused. Need tööriistad on mõeldud nii õppematerjalideks kui ka tegelikuks tootmiseks, avades võimalusi väikeettevõtluseks.

Praktilise töö käigus õpivad tudengid tundma erinevaid materjale ja protsesse, arvestades tööstuslikku täpsust ja ohutusnõudeid. Edasijõudnud tudengid võivad esitada oma projektiideid mis pole piiratud Doboti tarvikutega. Individuaalprojektid vajavad õppejõu heakskiitu ja isikupärastatud õppekava.

### **Mida õpid**

Luua terviklikke aga lihtsaid automatiseerimissüsteeme tööstusrobotitele. Omandada ESP32-põhiste juhtimissüsteemide loomist ja ühendamist tööstusrobotitega. Mõista erinevaid andureid ja nende süsteemi integreerimist. Tundma täppistööriistade tööpõhimõtteid ja looma usaldusväärseid juhtimissüsteeme. Disainima ja kokku panema seadmeid mis ühendavad elektroonikat, mehaanikat ja tarkvara. Omandama süsteemi dokumenteerimise ja hoolduse oskused läbi praktilise töö.

### **Töö**

Tudeng valib kahe lähenemise vahel:

**Järkjärgulised verstapostid**
Esita 5 väiksemat projekti järjest, igaüks kuni 20 punkti (kokku kuni 100 punkti)

* **Verstapost 1**: Terviklik süsteemispetsifikatsioon (10 t)
* **Verstapost 2**: Võtmetehnoloogia valideerimise prototüüp (16 t)
* **Verstapost 3**: Integreeritud tehniline prototüüp (18 t)
* **Verstapost 4**: Korpusega funktsionaalne prototüüp (16 t)
* **Verstapost 5**: Tootmisvalmis süsteem (14 t)

**Terviklik integratsioon**
Esita ainult lõplik tervikprojekt kuni 100 punkti eest

Projektid lähevad järjest raskemaks. Terviklik kaitsmine katab kõigi viie verstaposti materjale ja oskusi, ühendades need terviklikuks süsteemiks.

**Oluline**: tervikprojekti puhul (verstapostide asemel) nõuab kaitsmine vähemalt osaliselt valminud ehitatud prototüüpi koos põhjaliku dokumentatsiooniga. Puhtalt teoreetiline töö ilma füüsilise prototüübita ei kvalifitseeru tervikprojekti kaitsmisele, isegi kui esitlus on muidu põhjalik.

### **Verstapostide detailid**

**Spetsifikatsiooni dokument**
Koosta terviklik spetsifikatsioon doseerimissüsteemile. Sisalda funktsionaalsed nõuded, jõudluseesmärgid, liideste definitsioonid ja keskkonnatingimused. Uuri kommertssüsteeme, tuvasta võtmetehnoloogiad ja defineeri selged edukriteeriumid. Esita detailne spetsifikatsiooni dokument diagrammide, kasutusjuhtude ja tehniliste parameetritega mis juhivad kogu arendusprotsessi.

*Hindamiskriteeriumid: tehnilised spetsifikatsioonid, analüüs*

**Võtmetehnoloogia prototüüp**
Ehita kriitiliste tehniliste komponentide töötav prototüüp — konkreetselt doseerimise täitur ja täpne doseerimismehhanism. Tudengid valivad aktuatsioonimeetodi (servo, pneumaatika või hübriid) esimese semestri prototüüpidest õpitu põhjal. See fokusseeritud prototüüp peab demonstreerima põhifunktsionaalsust ilma integratsiooniprobleemideta. Valideeri põhiline doseerimisprintsiip, mahumõõtmise täpsus ja materjali sobivus. Esita töötav tehniline prototüüp, testitulemused jõudluse kohta spetsifikatsiooni vastu ja võimalikud muudatused algsele spetsifikatsioonile.

*Hindamiskriteeriumid: skeemid, programmeerimine + sobivad simulatsioonimeetodid, analüüs, testimine*

**Tehniline integratsiooniprototüüp**
Loo terviklik süsteemiprototüüp kõigi komponentidega õigetes ruumilistes positsioonides, kuid ilma lõpliku korpuse ja kasutajaliideseta. See prototüüp peab teostama täieliku süsteemiarhitektuuri — ESP32 juhtimine, andurite integratsioon ja roboti side. Kontrolli süsteemi integratsiooni, tuvasta ühilduvusprobleemid ja valideeri terviklik töövoog. Esita integreeritud prototüüp, liideste dokumentatsioon ja jõudluse valideerimine spetsifikatsiooni vastu.

*Hindamiskriteeriumid: programmeerimine + simulatsioon + teostus, kvaliteet, funktsionaalsus*

**Korpusega funktsionaalne prototüüp**
Arenda täiustatud prototüüp vajalike korpuste, kaablihalduse ja kasutajaliidese elementidega. See versioon peab lahendama praktilised küsimused: hoolduse ligipääsetavus, vastupidavus ja kasutatavus. Teosta sobivad kinnitusviisid, loo professionaalsed ühendused ja taga kaitse keskkonnamõjude eest. Esita korpusega prototüüp, kasutusjuhendi mustand ja kasutuse valideerimine päristingimustes.

*Hindamiskriteeriumid: täielik tehnikapakett + spetsifikatsioonid, disainivalikute põhjendused*

**Tootmisvalmis süsteem**
Lõplik doseerimissüsteem kõigi täiustustega usaldusväärsuse, toodetavuse ja hooldatavuse tagamiseks. See versioon peab esindama tootmisvalmis disaini mida saab kopeerida. Optimeeri komponentide valik, viimistle dokumentatsioon ja demonstreeri usaldusväärset töötamist. Esita lõplik süsteem, täielik dokumentatsioonipakett (kasutusjuhend, hooldusjuhised, osade nimekiri), süsteemi töödemonstratsioon kavandatud funktsionaalsusega ja GitHubi repositooriumi link.

*Hindamiskriteeriumid: terviklik pakett, disainivalikute põhjendused, juurutusjuhend*

**Terviklik kaitsmine**
Tudengitele kes esitavad kogu töö korraga verstapostide asemel. Kaitsmine peab katma kogu arendusprotsessi. Sisalda põhjalik dokumentatsioon disaini arengust, ületatud tehnilistest väljakutsetest, testitulemustest ja lõplikust jõudluse valideerimisest. Tudengid peavad demonstreerima valdamist kogu arendusprotsessi üle ja selgitama tehtud disainiotsuseid. Tudengid peavad põhjendama tehnoloogiavalikuid esimese semestri kogemuse põhjal — näidates miks valitud lahendused parandavad varasemaid prototüüpe.

## **Hindamisstruktuur**

* **Järkjärguline lähenemine**: 5 verstaposti × 20 punkti = maksimaalselt 100 punkti
* **Terviklik lähenemine**: 1 projekt = maksimaalselt 100 punkti
* **Hinde A lävi**: 91–100 punkti

### **Hindamiskriteeriumid**

Iga projekti hinnatakse viies valdkonnas:

**Verstaposti projektid (kuni 20 punkti):**

* Tarkvara/tööfailid (4 punkti): tehnilised spetsifikatsioonid, skeemid, programmeerimine
* Simulatsioon (4 punkti): sobivad simulatsioonimeetodid, analüüs, testimine
* Prototüüp/füüsiline projekt (4 punkti): teostus, kvaliteet, funktsionaalsus
* Dokumentatsioon (4 punkti): spetsifikatsioonid, disainivalikute põhjendused, juurutusjuhend
* Küsimuste-vastuste sessioon ja tagasiside (4 punkti): iga sisuline küsimus annab punkte

**Tervikprojekt (kuni 100 punkti):**

* Tarkvara/tööfailid (20 punkti)
* Simulatsioon (20 punkti)
* Prototüüp/füüsiline projekt (20 punkti)
* Dokumentatsioon (20 punkti)
* Küsimuste-vastuste sessioon ja tagasiside (20 punkti)

### **Esitamisnõuded**

* Projektid tuleb esitada 72 tundi enne kaitsmist
* Meeskondadel on 5 minutit esitluseks
* 15 minutit küsimuste ja tagasiside jaoks meeskonna kohta
* Küsimuste eest saab punkte; õppejõud põhjendab punktide mahaarvamist

### **Hindamisskaala**

* **91–100 punkti**: A
* **81–90 punkti**: B
* **71–80 punkti**: C
* **61–70 punkti**: D
* **51–60 punkti**: E
* **0–50 punkti**: F

**Miinimum sooritamiseks**: 51 punkti. Tudeng valib ise lähenemise:

* Esita verstaposte järk-järgult, kogudes vähemalt 51 punkti (nt vähemalt 3 verstaposti projekti)
* Esita ainult tervikprojekt vähemalt 51 punktile

**Oluline**: kui prototüüp ei saavuta täielikku funktsionaalsust, on maksimaalsed punktid siiski saavutatavad — kui tudeng näitab insenerimõtlemist, selgitades rikke põhjusi ja pakkudes alternatiive.

## **Kontakttundide ajakava**

* **[28.02]** Spetsifikatsiooni kirjutamine, uuendamine, verstapostid
* **[28.02]** Võtmetehnoloogiate tuvastamine ja testimismeetodid
* **[21.03]** Verstaposti 1 kaitsmine
* **[21.03]** Verstaposti 2 kaitsmine / Levinud prototüüpimisvead ja kuidas neid vältida
* **[18.04]** Verstaposti 3 kaitsmine
* **[18.04]** Tootmisprototüübi dokumenteerimine
* **[30.05]** Verstaposti 4 kaitsmine
* **[30.05]** Verstaposti 5 kaitsmine
* **[TBD]** Lisaülesande kaitsmine

---

## **Integratsiooniloogika**

See õppekava ehitab teadmisi süstemaatiliselt, hoides fookust praktilisel tulemusel. Iga aine annab hädavajalikud oskused:

* **Andmehõive**: mõõtmine ja analüüs
* **Nutilahendused**: side ja juhtimise infrastruktuur
* **3D Printimine/CAD**: füüsiline süsteemidisain ja tootmine
* **Prototüüpimine**: süsteemiintegratsioon ja tootmisvalmidus

Tudengid töötavad aasta jooksul meeskondades ja integreerivad oma lõppprototüüpides kõigi gruppide parimad lahendused. Meeskonnas tasub proovida erinevaid rolle — nii areneb laiem inseneripilk. See koostööline lähenemine peegeldab päris inseneripraktikat, tagades samal ajal individuaalse meisterlikkuse.

Tulemus: tudengid kes oskavad välja mõelda, disainida, ehitada ja juurutada terviklikke tehnilisi süsteeme. Mitte akadeemilised harjutused, vaid lahendused päris probleemidele mis loovad tegelikku väärtust.

See ongi mõte.

## Nutikad Lahendused: Labor 1 — Robot, ekraan ja täht

**Töömaht:** 28 tundi | **Hindamine:** 20 punkti | **Meeskond:** 3 tudengit | **Välja antud:** 12.09.26 | **Tellimise kuupäev:** 22.09.26 | **Esimene kaitsmine:** 06.10.26, veebis

### Kuidas see dokument töötab

* Kopeeri see fail esimesel päeval oma repo laborikausta `README.md`-ks ja täida seal, töö käigus.
* KAARDISTA ise on puudu, sest vastust ei tea veel keegi. Sina ise mõõdad ja kirjutad numbri ja põhjuse siia.
* Midagi ei kustutata. Vale number jääb, kuupäevaga, parandus tuleb tema alla.
* Kirjuta nii, et meeskonnakaaslane, kes sel päeval ruumis ei olnud, saab aru: päris failinimed, päris numbrid, ühikud.
* Skeemid ja simulatsioonid lähevad dokumenti pildina, pildi juurde link elavale failile, et teine saaks selle lahti teha ja edasi muuta. Näited on Andmehõive Labori 1 töölehel: Falstadi simulatsioon ja draw.io skeem. Tee enda omad samade tööriistadega.
* Tähtaeg ei ole tähtis. Tähtis on, et asi saab tehtud ja sa saad aru. Ei tulnud esimesel korral välja, tule homme tagasi ja proovi uuesti. Kaitsta saab nii mitu korda, kui vaja.

### Eesmärk

Kolm kasti, mis igaüks töötab, ei ole süsteem. Andmehõive meeskonnal on Atom, mis saadab tähe, kui nuppu vajutad. 3D printimise meeskonnal on pastakahoidik roboti flantsi küljes. Robotil on TCP port, mis võtab vastu liikumiskäske. Mitte miski sellest ei joonista. Süsteem on see osa, mis jääb nende vahele, ja see osa on sinu. Sama meeskond teeb kõiki kolme ainet. Kolm ainet, üks demo: **vajuta tähte, robot joonistab selle.**

Selles laboris on kolm asja:

1. **Robot.** MG400 API-režiimi ja sinu sülearvutist Pythoniga liikuma. Baaspakett on olemas: CLI, leht liugurite, salvestatud asendite ja pumba nuppudega. Sina paned ta tööle, kontrollid tema oletused ja õpetad neli asendit.
2. **Ekraan.** AtomS3 PlatformIO-st, oma WiFi võrk, captive portal ja leht, kust pilt ekraanile läheb. See leht jääb: siit seadistatakse ja testitakse tööriista kogu aasta. Rõhuandur, UART, kõik, mis hiljem juurde tuleb, saab oma seaded ja testinupu siia, mitte eraldi lehele.
3. **Täht.** Atomi nupp valib tähe, jaam saab selle kätte, robot joonistab pastakahoidikuga. Vähemalt kolm tähte.

Esimesel päeval uusi osi ei ole. Ehita sellest, mis riiulil on, ja kirjuta puuduv tellimuseks, mis läheb välja 22.09.

*See on elav dokument. Uuenda eesmärke, kui need töö käigus muutuvad — uued teadmised teevad vanad eesmärgid vahel mõttetuks. Mõte on hoida meeskond kogu aeg sihil, et ei eksitaks detailide metsa ja põhiprobleem ei jääks lahendamata.*

**KAARDISTA ISE — eesmärk nii, nagu ta tegelikult välja tuli.**

### Kontrollnimekiri

**Peab olema tehtud**

- [ ] MG400 API-režiimis, `mg400 status` vastab, leht liigutab robotit, pump imeb ja puhub CLI-st.
- [ ] Neli asendit õpetatud, `data/positions.json`, robot tõstab sildi kümme korda.
- [ ] AtomS3 flashitud PlatformIO-st, teeb oma WiFi võrgu, telefon satub lehele ilma aadressi trükkimata, pilt jõuab ekraanile.
- [ ] Atomi lehel on seadete ja testide osa, `docs/atom_page.md` ütleb, mis seal on.
- [ ] Täht: Atomi nupp valib, jaam saab kätte, robot joonistab kolm tähte.
- [ ] Repo ja arenduspäevik täidetud, tag `smart-solutions-lab1`.

**KAARDISTA ISE — kuupäevad ja sinu enda sammud.**

### Sisendid

* Riiulilt: AtomS3, USB-C kaabel, USB-C → Ethernet adapter, LAN kaabel, marker, maalriteip, paber, AtomS3 näidissilt või mistahes 24 × 24 mm lameda pealsega asi esimese tõstmise jaoks.
* Õppejõult: MG400 API-režiimis, koos pumbakasti ja iminapa komplektiga; MG400 baaspakett.
* Andmehõive L1: täht, üks JSON rida kanalis, mille te esimesel nädalal kokku lepite. Leppige kanal kokku enne, kui kumbki selle jaoks koodi kirjutab.
* 3D printimine L1: pastakahoidik flantsi külge. Kuni seda ei ole, joonistab flantsi külge teibitud marker.

### Vahendid

1. MG400 koos iminapa komplektiga ja pumbakastiga
2. Sülearvuti Ethernet pordi või adapteriga; Python 3.11+, venv, pip, Flask
3. MG400 baaspakett: `code/mg400-base` sellest repost
4. AtomS3, USB-C kaabel; VS Code ja PlatformIO laiendus; M5Unified
5. ESP32-Image-Server alguspunktiks (link taustainfos)
6. Telefon, millega Atomi võrku minna
7. Marker, maalriteip, paber; pastakahoidik 3D printimise L1-st, kui valmis
8. Git, üks repo meeskonna kohta, `AGENTS.md` juurkaustas
9. draw.io

*Kui plaan muutub, uuenda ka vahendeid, või tee draw.io skeem, mis näitab, kuidas asjad omavahel töötavad.*

**KAARDISTA ISE — mida sa päriselt kasutasid.**

### Taustainfo

* **MG400 baaspakett**: README, kus on kaabel ja aadress, CLI ja HTTP API. API-režiim on robotil juba sees; kui ei ole, on `docs/api-mode-utm.md` ühekordne juhend, kuidas see Macist sisse lülitada.
  [https://github.com/KKallas/Narva-subjects/tree/main/code/mg400-base](https://github.com/KKallas/Narva-subjects/tree/main/code/mg400-base)
* **Dobot TCP/IP protokoll**: pordid 29999 (EnableRobot, ClearError, DO, GetPose), 30003 (MovL, ServoP), 30004 (tagasiside iga 8 ms)
  [https://github.com/Dobot-Arm/TCP-IP-Protocol](https://github.com/Dobot-Arm/TCP-IP-Protocol)
  Doboti enda Pythoni näide: [https://github.com/Dobot-Arm/TCP-IP-4Axis-Python](https://github.com/Dobot-Arm/TCP-IP-4Axis-Python)
* **Pumbakast**: otsi fraasi "Dobot MG400 vacuum pump box IO control". Kaks DO liini; klemmid juhendist.
* **AtomS3**: viigud, ekraan, nupp
  [https://docs.m5stack.com/en/core/AtomS3](https://docs.m5stack.com/en/core/AtomS3)
* **PlatformIO**: [https://docs.platformio.org/](https://docs.platformio.org/) ja M5Unified: [https://github.com/m5stack/M5Unified](https://github.com/m5stack/M5Unified)
* **ESP32-Image-Server**: AtomS3 püsivara, mis teeb WiFi võrgu, näitab pilti ja pakub lehte, kust pilt üles laadida. Captive portalit seal ei ole.
  [https://github.com/KKallas/ESP32-Image-Server](https://github.com/KKallas/ESP32-Image-Server)
* **ESP32 WiFi AP**: [https://randomnerdtutorials.com/esp32-access-point-ap-web-server/](https://randomnerdtutorials.com/esp32-access-point-ap-web-server/)
* **Captive portal**: otsi fraasi "ESP32 captive portal DNSServer generate_204 hotspot-detect". Telefon küsib liitumisel kindlat aadressi; kui vastus ei ole see, mida ta ootab, avab ta lehe ise.
* **Flask**: [https://flask.palletsprojects.com/en/stable/quickstart/](https://flask.palletsprojects.com/en/stable/quickstart/)

*Lisa siia oma allikaid ja kasulikku infot, mis aitaks sul projektist aru saada ka aastaid hiljem, kui selle uuesti lahti teed.*

**KAARDISTA ISE — sinu allikad.**

### Osad

#### 1. Robot

Robot on LAN1 pordis aadressil 192.168.1.6 ja API-režiimis: ta teenindab porte 29999, 30003 ja 30004 nii kaua, kui ta on voolu all. Sinu arvuti Ethernet saab käsitsi aadressi 192.168.1.50, mask 255.255.255.0, gateway tühi. Ping enne, kui midagi muud. Kui ping käib, aga port keeldub, on API-režiim väljas; ühekordne juhend on baaspaketi kaustas `docs/`.

Baaspakett: `mg400 status` ütleb režiimi ja asendi; `mg400 serve` annab lehe, kus on ühenda, luba, liugurid X/Y/Z/R, kiirus, kümme salvestatud asendit ja pumba nupud. Esimene liigutus 20 % kiirusel, käsi hädastopi juures. Ainult üks programm saadab liikumiskäske korraga.

Pumbakast on kahel DO liinil. Pakett arvab, et DO2 on imemine ja DO1 puhumine; kontrolli kasti juhendist ja multimeetriga enne, kui ühendad. Andmehõive meeskond küsib pumpa sinu CLI-st teisest nädalast.

Õpeta neli asendit: `above_source`, `source`, `above_finished`, `finished`. Kordamine tõstab sildi allikast ja paneb valmis pessa, kümme korda 20 % kiirusel.

Kirjuta üles: aadressiplaan (robot, arvuti, liides, mask); pordid ja mis igaüks teeb; DO indeksid ja kuidas kontrollitud; neli asendit failis `data/positions.json`; kümme tõstmist failis `docs/pick_test.csv` (tõstetud, pandud, märkus); mis paketis oli valesti või puudu, ja pull request õppejõu repole.

#### 2. Ekraan

ESP32-Image-Server, kaust `atom-image-server`, PlatformIO-s AtomS3 peale. Plaat on `m5stack-atoms3`, M5Unified tunneb ekraani ise ära. Seerial 115200. Ilma salvestatud võrguta teeb Atom oma WiFi võrgu aadressil 192.168.4.1 ja leht on seal: lõika pilt, saada slotti, pilt on ekraanil.

Sinu osa: captive portal. Telefon liitub võrguga ja satub lehele ilma, et keegi aadressi trükiks. DNS vastab igale nimele Atomi aadressiga, ja telefoni kontrollaadressid saavad vastuseks lehe. Logi, mida telefon küsis; Android ja iPhone küsivad eri asju.

Teine osa: lehele tuleb seadete ja testide osa. Praegu: võrgu nimi ja parool, jaama aadress, testinupp, mis näitab ekraanil olekut. See osa jääb ja kasvab: Laboris 2 tulevad siia rõhuanduri lugem ja UART test, hiljem klapp ja LED. Reegel: iga riistvara, mis Atomi külge tuleb, saab oma seaded ja testinupu sellele lehele. Eraldi lehti ei tule.

Kirjuta üles: flashimise sammud ja aeg; AP nimi, aadress, lehe URL; ühe 128 × 128 kaadri üleslaadimise aeg üle AP; captive portali kontrollaadressid, mida telefon küsis; lehe seadete ja testide nimekiri failis `docs/atom_page.md`.

#### 3. Täht

Andmehõive L1 osas 5 valib lühike vajutus tähe ja pikk saadab selle. Kanal on teie kokkulepe: Atom on WiFi võrk ja HTTP server, seega kas jaam küsib Atomilt või Atom saadab jaamale. Üks JSON rida, ajatempel jaamas vastuvõtul.

```
Atom → jaam:   {"letter":"A"}
jaam → robot:  täht → punktide nimekiri → MovL punkt-punktilt, pliiats üles joonte vahel
```
```
täht tuleb:  kui robot ei ole lubatud → midagi ei liigu, leht näitab põhjust
             muidu: pliiats üles → esimene punkt → pliiats alla → punktid → pliiats üles
```

Vähemalt kolm tähte, meeskonna initsiaalid, punktide nimekirjadena. Pliiatsi allasõidu Z leitakse markeriga ja hiljem hoidikuga; kui õpetatud kõrgus on paar millimeetrit paigast ära, jääb hoidik terveks. Esimene joonistus 20 % kiirusel, pliiats 20 mm paberist kõrgemal.

Kirjuta üles: kanal (kes ühendab kelle poole, aadress, formaat) failis `docs/letter_channel.md`; kolm tähte punktidena ja pliiatsi Z failis `docs/letters.md`, joonistatud tulemus joonlauaga mõõdetuna kavandatud suuruse vastu; kolmkümmend vajutust ajatemplitega (Atom saatis, jaam sai, esimene käsk robotile) failis `docs/latency.csv`, keskmine ja maksimum iga hüppe kohta.

**KAARDISTA ISE — vastused.** Iga osa kohta: numbrid, ühikud, kus fail on. Tegemata asja kohta üks rida, miks.

### Ohutus

* MG400 tööala on 440 mm raadius; kellegi käed ei ole selle sees, kui käsk on ootel. Enne iga kordamist ütleb keegi "liigub".
* Hädastopp MG400 alusel on ainus stopp, mida sa usaldad. Stopp-nupp lehel on mugavus; testi seda, aga hoia käsi hädastopi lähedal iga uue jada esimesel jooksul.
* Iga uue tähe või jada esimene jooks 20 % kiirusel, ilma sildita, pliiats või iminapp 20 mm pinnast kõrgemal.
* Ainult üks programm saadab liikumiskäske korraga.
* Pumbakast on 24 V. DO liinid ühendatakse siis, kui robot on keelatud ja kast vooluvõrgust väljas.
* Atomi WiFi parool ei ole vaikimisi oma, kui Atom laborist välja läheb.

### Komponendid järgmiseks laboriks

Tellimus läheb välja 22.09.26. Kogused meeskonna kohta.

| Asi | Kogus meeskonna kohta | Märkus |
| :--- | :--- | :--- |
| M5 Atom Lite või AtomS3 (teine seade, tööriista küljes) | 1 | Esimene jääb Andmehõive maketeerimisplaadile |
| Otsiku kaamera, M5 AtomS3R-CAM või AI-Thinker ESP32-CAM | 1 | MJPEG üle WiFi kummalgi juhul |
| 3/2 klapp, otsetoimeline, vedrutagastusega, vaakumikõlblik, 24 V | 1 | Ühine ← pump, NO → iminapp, NC → süstal; alla 100 g |
| 4 mm push-in liitmikud | 4 | Klapi ja kahe haru jaoks |
| 4 mm PU voolik | 1 m | |
| Loogikataseme MOSFET moodul | 3 | Klapp, pumbakasti liinid, LED-i luba |
| 405 nm LED 1–3 W tähtjahutil | 2 | Üks varuks; mitte kunagi 365 nm |
| Püsivoolu LED draiver | 1 | LED-i voolule vastav |
| USB kaablid (jaam ↔ Atom, jaam ↔ kaamera toiteks) | 2 | |
| 405 nm kaitseprillid | 2 | Laual alati, kui LED on toite all |

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — baaspaketi seadistus ja sinu muudatused, Atomi püsivara, täheteed, `positions.json` | 5 p |
| Analüüs — aadressiplaan, DO kontroll, tõstmise tabel, üleslaadimise aeg, latentsus hüpe-haaval | 5 p |
| Prototüüp — leht liigutab robotit, pump CLI-st, Atom teeb võrgu ja telefon satub lehele, pilt ekraanil, robot joonistab Atomil valitud tähe | 5 p |
| Dokumentatsioon — README, arenduspäevik, `atom_page.md`, `letters.md`, `letter_channel.md`, AGENTS.md | 5 p |
| **Kokku** | **20 p** |

### Kaitsmine

Link git repole, tag `smart-solutions-lab1`.

Kaitsmine on lihtne suuline 15 minuti jutuajamine. Näitad, kuidas Atomil vajutatud tähe robot joonistab, avad telefonist Atomi lehe ja oma arenduspäeviku. Õppejõud küsib umbes viis küsimust selle kohta, kuidas sa selle tegid. Kui esimesel korral ei õnnestu, tuled uuesti.

Repos on kaustas `smart-solutions/lab1/`: `src/` jaama kood (baaspaketi seadistus, tähe kanal, täheteed), `firmware/` Atomi PlatformIO projekt, `data/positions.json`, `docs/` (`atom_page.md`, `letters.md`, `letter_channel.md`, `pick_test.csv`, `latency.csv`, fotod, draw.io skeem ahelast), see fail kui `README.md`, ja `AGENTS.md` uuendatud.

### Arenduspäevik

**KAARDISTA ISE — päevik.** Üks sissekanne iga töösessiooni kohta, kirjutatud iseendale, nii et inimene, kes seal ei olnud, saab aru. Sissekandeid lisatakse, mitte ei muudeta.

**PP.KK.AA — kes olid kohal**
* Tegime:
* Juhtus (numbrid):
* Otsustasime, ja miks:
* Lahti järgmiseks korraks:

### Väljundid ja tulemused

**Väljundid**
* Andmehõive L1: pumbakast imemisele ja puhumisele baaspaketi CLI-st, teisest nädalast; tähe kanal.
* 3D printimine L1: robot joonistab hoidikuga tähe.
* Nutikad Lahendused L2: Atomi leht, kuhu tööriistaplaadi seaded ja testid juurde tulevad; jaam, mille külge tööriistaplaat käib.

**KAARDISTA ISE, lõpus.**
* Git repo ja tag:
* Numbrid, mille see labor andis, ühikutega:
* Mida me teeksime teisiti:
* Mida järgmine labor peaks enne alustamist teadma:

### Tagasiside

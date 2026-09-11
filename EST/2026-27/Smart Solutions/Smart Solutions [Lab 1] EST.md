## Nutikad Lahendused: Labor 1 — Ahel

**Töömaht:** 28 tundi | **Hindamine:** 20 punkti | **Meeskond:** 3 tudengit | **Välja antud:** 12.09.26 | **Tellimise kuupäev:** 22.09.26 | **Kaitsmine:** 06.10.26, veebis

### Kuidas see dokument töötab

Pool sellest dokumendist on meelega puudu.

See, mis siin kirjas on, on **ANTUD**: kuupäevad, seosed teiste ainetega, vastuvõtu tingimused, ohutusreeglid ja küsimused, mida tasub küsida. See on kaardi serv, mitte kaart.

Kõik, mille juures on **KAARDISTA ISE**, on tühi, sest vastust ei tea veel keegi — ka õppejõud mitte. Sina kaardistad selle: mõõdad, otsustad, ja kirjutad numbri ja põhjuse siia faili, kõrvuti.

Kopeeri see fail esimesel päeval oma repo laborikausta `README.md`-ks ja täida seal, töö käigus. Seda ei kirjutata kaitsmise eelõhtul: tagantjärele kirjutatud dokument on jutt, ja juttu ei saa hinnata. Tag'i sees olevat versiooni loetakse täpselt nii, nagu ta on, ja tühi koht, mis jäi tühjaks, on ka vastus.

Midagi ei kustutata. Number, mis osutus valeks, jääb oma kohale, kuupäevaga, ja parandus tuleb tema alla. Vale käik on tavaliselt aruande kõige kasulikum lehekülg — järgmisele meeskonnale, ja sulle endale aasta pärast.

Kirjuta nii, et seda ei peaks tõlkima: päris failinimed, päris numbrid, ühikud iga numbri juures, ja põhjus valiku kõrval. Lugeja, kellele sa kirjutad, on meeskonnakaaslane, kes sel päeval ruumis ei olnud.

### Eesmärk

Kolm kasti, mis igaüks töötab, ei ole süsteem. Andmehõive meeskonnal on Atom, mis saadab tähe, kui nuppu vajutad. 3D printimise meeskonnal on pliiatsihoidik roboti flantsi küljes. Robotil on TCP port, mis võtab vastu liikumiskäske. Mitte miski sellest ei joonista. Süsteem on see osa, mis jääb nende vahele, ja see osa on sinu: **vajuta tähte Atomil, ja MG400 joonistab selle.**

Ahel jookseb võrgus, mille sa ise ehitad. Mitte sülearvuti, mis on roboti külge pistetud — vaid ruuter, kus robotitel on oma alamvõrk, aadressid jäävad sinna, kuhu sa need panid, WiFi, millega Atom liitub, tulemüür, ja marsruut, mis juba ootab VPN tunnelit, mis tuleb Laboris 3. Siin elavad alamvõrgud, ruutimistabel ja NAT päriselt, ja siin need ka selgeks saavad. Joonista aadressiplaan paberile, enne kui midagi sisse pistad; suurem osa esimesest nädalast on see joonis valesti olemas.

Kood algab sinu enda sülearvutis, sest nii on kiire: ühenda robotiga, liiguta seda, loe tema asendit, lülita pumbakasti, võta täht vastu, tee tähest tee. Siis kolib see sinu sülearvutist masinasse, mis jääb laborisse — varu-sülearvuti või lauaarvuti, kus IDE-d peal ei ole, staatiline aadress roboti alamvõrgus, ja kõik käivitub alglaadimisel, ilma et keegi sisse logiks. Kood, mis jookseb seal, kus sa ta kirjutasid, ei ole sama, mis kood, mis jookseb. Jaam pakub üht lehte: liiguta, õpeta asend, mine asendisse. Samsungi telefon alusel laua serval näitab seda lehte täisekraanil, nuppudega, mis on pöidla jaoks piisavalt suured. Operaator ei puutu klaviatuuri.

Sel aastal Raspberry Pi'd ei ole. Tema tööd on jagatud kolmeks ja igaüks läheb paremasse kohta: ruuter kannab võrku, Digital Oceani droplet (Labor 3) kannab seda, mis peab püsti olema ka siis, kui kedagi ruumis ei ole, ja ESP32 tööriista küljes on odav kohalik loogikaüksus — piiratud protsessor, mis teenindab mitut seadet korraga, reaalajas. Jaam on lihtsalt kast, mis räägib robotiga ja pakub lehte.

*See on elav dokument. Uuenda eesmärke, kui need töö käigus muutuvad — uued teadmised teevad vanad eesmärgid vahel mõttetuks. Mõte on hoida meeskond kogu aeg sihil, et ei eksitaks detailide metsa ja põhiprobleem ei jääks lahendamata.*

**KAARDISTA ISE — eesmärk nii, nagu ta tegelikult välja tuli.** Kui sa tead, mis see töö päriselt on, kirjuta ülal olevad lõigud oma sõnadega ümber ja pane kuupäev juurde. Kui eesmärk kaitsmisel ikka muutmata kehtib, kirjuta see lause koos kuupäevaga; ka see on tulemus.

### Liidesed

**Võtab**
* Õppejõult: MG400 baaspakett Pythonis (tag'itud git URL, README, `AGENTS.md`, CLI), MG400 koos iminapa komplekti ja vaakumpumba kastiga, ruuter koos adminni ligipääsuga, Samsungi telefon alusega, USB-C → Ethernet adapter, LAN kaablid.
* Andmehõive L1: täht, ühe sõnumina kanalis, mille te esimesel nädalal kokku lepite — näiteks üks JSON rida `{"letter":"A"}`. Leppige kanal kokku enne, kui kumbki selle jaoks koodi kirjutab.
* 3D printimine L1: pliiatsihoidik, mis annab järele, flantsi küljes. Kuni seda ei ole, joonistab flantsi külge teibitud marker antud rutiiniga ruudu.

**Annab**
* Andmehõive L1: pumbakast sinu jaamast imemisele ja puhumisele lülitatud, teisest nädalast, et neil oleks teine rõhuallikas.
* Nutikad Lahendused L2: jaama rakendus ja paketi kiht, kuhu tööriistaplaat külge käib.
* Andmehõive L4: jaam koos õpeta, salvesta ja korda funktsioonidega, mis hiljem andmekogumist jooksutab.
* Kõigi meeskondade agentidele: `AGENTS.md`.

### Taustainfo

* **Dobot MG400 TCP/IP protokoll** — Dobot MG400 TCP/IP protokolli dokument (Dobot GitHub, TCP-IP-Protocol). Pordid 29999 (dashboard: EnableRobot, ClearError, DO, GetPose) ja 30003 (liikumine: MovJ, MovL, jog). Baaspakett mähib selle sisse; loe dokumenti, et aru saada, mida pakett teeb, ja et leida tema vigu.
* **IPv4 alamvõrgud** — otsi fraasi "IPv4 subnet mask gateway explained CIDR /24". Sul on vaja: aadress, mask, võrk, broadcast, gateway, ja milliste pakettide jaoks on gateway'd vaja ja milliste jaoks mitte.
* **Ruuteri seadistamine** — otsi fraasi "router DHCP reservation static lease subnet firewall rule". Mis ruuter riiulil ka ei ole, tema juhendis on need neli asja; leia need enne kokkusaamist.
* **Pythoni paketi paigaldamine gitist pip'iga** — tag'itud URL-id, miks tag on tähtis: https://pip.pypa.io/en/stable/topics/vcs-support/
* **Flaski kiirstart** — marsruudid, mallid, JSON vastused: https://flask.palletsprojects.com/en/stable/quickstart/
* **Teenuse käivitamine alglaadimisel** — otsi fraasi "systemd service unit run python on boot" Linuxi jaama jaoks, või sama asi selle OS-i jaoks, mis varumasinal peal on.
* **Täisekraani brauser Androidis** — otsi fraasi "Android kiosk mode fullscreen browser". Paneel peab üle elama ekraani kustumise ja taaskäivituse.
* **Dobot vaakumpumba kast** — otsi fraasi "Dobot vacuum pump box MG400 I/O wiring suction blow". Kaks DO liini lülitavad seda; loe juhendist täpsed klemmid enne ühendamist.
* **draw.io** — võrguskeemi jaoks: https://app.diagrams.net

*Lisa siia oma allikaid ja kasulikku infot, mis aitaks sul projektist aru saada ka aastaid hiljem, kui selle uuesti lahti teed.*

**KAARDISTA ISE — sinu allikad.** Iga link, andmelehe lehekülg, foorumivastus ja video, mis päriselt aitas, ja iga juures üks rida: mida sa sealt said, ja mis seal valesti või puudu oli. Link, mille kõrval lauset ei ole, ei ole allikas.

### Vahendid

1. MG400 koos Doboti iminapa komplektiga (tõstev otsik, φ13 või φ16 iminapp) ja vaakumpumba kastiga (24 V, I/O juhitav)
2. Ruuter meeskonna kohta, või üks ruuter alamvõrguga iga meeskonna jaoks
3. Jaam: varu-sülearvuti või lauaarvuti, mis jääb laborisse, USB-C → Ethernet adapteriga, kui tal porti ei ole
4. Samsungi telefon alusega ja laadijaga, paneelina
5. AtomS3 Andmehõive meeskonnalt, mis saadab tähe
6. MG400 baaspakett Pythonis (õppejõu tag'itud git URL)
7. Python 3.11+, `venv`, pip, Flask
8. Git, meeskonna repo koos `AGENTS.md`-ga
9. draw.io
10. AtomS3 näidissilt või mistahes 24×24 mm lameda pealsega asi, ja alus riiulilt, esimese tõstmise jaoks
11. Pliiatsihoidik 3D printimise L1-st; seni marker ja maalriteip

*Kui plaan muutub, uuenda ka vahendeid, või tee draw.io skeem, mis näitab, kuidas asjad omavahel töötavad.*

**KAARDISTA ISE — mida sa päriselt kasutasid.** Versioonid, masinate nimed, mis riiuliasi mille asemele läks, mis läks katki ja mis sai otsa. Ülal olev nimekiri on see, mida oodati; see nimekiri on see, mida inimene vajab, et sinu töö uuesti teha.

### Projekti ülesehitus

- [ ] Aadressiplaan paberil: iga seade, tema liides, tema aadress, mask ja gateway, ja millised paketid millist ühendust läbivad. draw.io-s, enne kui ükski kaabel sisse läheb.
- [ ] Ruuter: alamvõrk robotitele, DHCP reserveeringud, et MG400 ja jaam hoiaksid aadresse, mille sa neile andsid, WiFi, millega Atom liitub, tulemüür, ja marsruut Labori 3 tunneli jaoks valmis jäetud.
- [ ] Sülearvuti räägib MG400-ga: ühenda, luba, tühista viga, liiguta iga telge, loe asendit, DO sisse ja välja — kõigepealt paketi CLI-st, siis oma koodist.
- [ ] Sülearvuti räägib Atomiga: tähesõnum jõuab kokkulepitud kanalis kohale ja logitakse ajatempliga.
- [ ] Täht → liikumine: vähemalt kolm tähte, meeskonna initsiaalid, teedena, mida robot pliiatsiga joonistab. Kus on paber, mis on pliiatsi allasõidu Z, mis juhtub, kui robot ei ole valmis — kõik sinu.
- [ ] Pumbakast kahel DO liinil: imemine, puhumine, väljas, sinu enda koodist; Andmehõive meeskond võib seda teisest nädalast küsida.
- [ ] Koli sülearvutist ära: sama kood jaamas, ilma IDE-ta, staatiline IP roboti alamvõrgus, käivitub alglaadimisel ilma sisselogimiseta.
- [ ] Jaama leht: liigutamise nupud (X/Y/Z/R, samm 1/10/50 mm), salvestatud asendite nimekiri koos Mine, Õpeta ja Kustuta nuppudega, pumba nupud, olekurida.
- [ ] Telefon on paneel: täisekraani brauser lehe peal, alusel laua serval, elab üle ekraani kustumise ja taaskäivituse.
- [ ] Esimene tõstmine: õpeta `above_source`, `source`, `above_finished`, `finished`; kordamine tõstab sildi üles ja paneb maha.
- [ ] `AGENTS.md` repo juurkaustas: mis see süsteem on, kuidas seda käivitada, kus on baaspaketi README, kuidas saata tähte ilma Atomita.
- [ ] Iga parandus baaspaketti pull request'ina õppejõu repole, lingitud kaustast `docs/`.
- [ ] Tag `smart-solutions-lab1` 72 h enne 06.10.

*Kui kaugel te olete? Millal valmis saate? Kuidas saaks kiiremini? — tavalised küsimused*

**KAARDISTA ISE — kuupäevad ja sinu enda sammud.** Pane iga linnukese kõrvale kuupäev ja lisa sammud, mida see dokument ette ei näinud — need on lugemist väärt. Kast, mida ei saa linnukesega märkida, saab ühe rea, miks; teda ei jäeta lihtsalt lahti.

### Simulatsioon

Selle labori simulatsioon on võrguskeem, ja seda tehakse kaks korda. Üks kord enne, kui midagi sisse pistetakse: iga seade, liides, aadress, mask ja gateway, ja nool iga paketi jaoks, mille täht tekitab — Atomist jaama, jaamast robotile, jaamast telefonile — koos ühendusega, mida igaüks läbib. Siis uuesti pärast ehitamist: loe ruutimistabel ruuterilt ja jaamast ja võrdle rida-realt joonisega. Iga erinevus on kas viga joonises või viga võrgus, ja sina ütled, kumb. Mõlemad versioonid lähevad failidesse `docs/network.drawio` ja `docs/network.md`.

### Analüüs

1. **Aadressiplaan** (`docs/network.md`): tabel — seade, liides, aadress, mask, gateway, ja üks rida, miks. Siis ruuteri ja jaama ruutimistabel tekstina, iga rida selgitatud.
2. **Tähe latentsus** (`docs/latency.csv`, `notebooks/lab1_chain.ipynb`): kolmkümmend vajutust. Iga kohta: Atomi saatmise ajatempel, jaama vastuvõtu ajatempel, robotile saadetud esimese liikumiskäsu ajatempel. Keskmine, maksimum ja hajuvus iga hüppe kohta. Milline hüpe on aeglane?
3. **Täheteed** (`docs/letters.md`): kolm tähte punktide nimekirjadena, pliiatsi allasõidu Z ja kuidas see leiti, joonistatud tulemus joonlauaga mõõdetud neljast kohast kavandatud suuruse vastu.
4. **Alglaadimise test** (`docs/boot.csv`): jaam viis korda voolust välja ja sisse; aeg sisselülitamisest lehe laadimiseni telefonis; kõik, mis üles ei tulnud.
5. **Esimene tõstmine** (`docs/pick_test.csv`): kümme tõstmist 20 % kiirusel; tõstetud, pandud, märkused.

**KAARDISTA ISE — vastused.** Iga ülaloleva nummerdatud punkti kohta üks rida: number, mille sa said, tema ühik, ja koht, kus ta elab (notebook, lahter, fail). Iga tegemata asja kohta üks rida, miks. Kaitsmise küsimused tulevad sellest osast.

### Testimine

#### Testinäide 1: Joonis klapib tabeliga

Jaama ja ruuteri ruutimistabel klapivad failis `docs/network.md` oleva joonisega, rida-realt. Siis tõmba roboti kaabel välja: joonis peab ennustama, milline lehe funktsioon seiskub, ja nii ka läheb.

#### Testinäide 2: Tähest liikumiseni alla sekundi

Vajuta Atomil tähte. Läbi: esimene liikumiskäsk jõuab robotini 1 s jooksul, kümme korda kümnest, ajatemplite järgi failis `docs/latency.csv`.

#### Testinäide 3: Jaam tuleb üles ise

Lülita jaam välja ja sisse. Läbi: 90 s jooksul laadib leht telefonis, roboti olek näitab ühendatud, ja keegi ei ole sisse loginud ega midagi kirjutanud. Viis korda viiest.

#### Testinäide 4: Robot ei ole valmis

Keela robot, siis vajuta tähte. Läbi: leht näitab, miks midagi ei juhtunud, midagi ei liigu, ja jaam ei jookse kokku ega jää kinni. Luba robot: järgmine vajutus joonistab.

#### Testinäide 5: Kümme kümnest

Neljast õpetatud asendist tõstab kordamine näidissildi allikast ja paneb valmis pessa, 10 korda 10-st 20 % kiirusel, ühe täisringi videoga.

*Need on esimesed näited. Lisa siia järgmised testid, et kui projektile uusi osi juurde tuleb, saaks automaatselt kontrollida, et vana osa katki ei läinud — käsitsi tehes kulub sellele suurem osa projekti ajast!*

**KAARDISTA ISE — sinu testid ja sinu ebaõnnestumised.** Iga ülaloleva testi kohta: tee see läbi, kirjuta tulemus ja kuupäev. Siis lisa testid, mille sa ise välja mõtlesid, ja — see osa jääb tavaliselt puudu — mis läks esimesena katki, kuidas see välja nägi, ja mis selle korda tegi.

### Vastuvõtt

* Video: täht vajutatud Atomil, MG400 joonistab selle prinditud hoidikuga, ühe võttega.
* `docs/network.md` aadressiplaani, mõlema ruutimistabeli ja enne/pärast joonistega.
* `docs/latency.csv` kolmekümne reaga ja hüpe-haaval kokkuvõte notebookis.
* Video jaama alglaadimisest kuni leheni telefonis, ilma sisselogimiseta.
* `docs/pick_test.csv` kümne reaga ja ühe ringi video.
* `AGENTS.md` kontrollitud: teise meeskonna agent käivitab sinu süsteemi selle põhjal, ja nende transkript on kaustas `docs/`.

**KAARDISTA ISE — kus iga asi on.** Iga ülaloleva punkti kõrvale tee repos ja commit või tag, kus ta ilmus. Vastuvõtu punkt, millel teed ei ole, ei ole vastu võetud; keegi seda otsima ei lähe.

### Tekkivad andmed

Ainult repo. Salvestatud asendeid (`data/positions.json`) ja latentsuse CSV-d loevad Labor 2 ja Andmehõive meeskond Laboris 4; hoia failinimed alles.

### Ohutus

* MG400 tööala on 440 mm raadius; kellegi käed ei ole selle sees, kui käsk on ootel. Inimene telefoni juures ütleb "liigub" enne iga kordamist.
* Hädastopp MG400 alusel on ainus stopp, mida sa usaldad. Stopp-nupp lehel on mugavus — testi seda, aga hoia käsi hädastopi lähedal iga uue jada esimesel jooksul.
* Iga uue tähe või jada esimene jooks 20 % kiirusel, ilma sildita, pliiats või iminapp 20 mm pinnast kõrgemal.
* Pumbakast töötab 24 V peal; ühenda DO liinid siis, kui robot on keelatud ja kast vooluvõrgust väljas.
* Ruuteri adminni parool vahetatud vaikimisi omast ära esimesel päeval, ja kirjas meeskonna paroolihoidlas, mitte repos.

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
| Tööfailid — jaama rakendus, täheteed, ruuteri seadistus eksporditud, paketi kiht | 5 p |
| Analüüs — aadressiplaan mõlema ruutimistabeliga selgitatud, latentsus hüpe-haaval, alglaadimise ja tõstmise tabelid | 5 p |
| Prototüüp — Atomil vajutatud tähe joonistab robot; jaam tuleb ise üles telefonini; 10 tõstmist 10-st | 5 p |
| Dokumentatsioon — võrguskeemid enne ja pärast, `AGENTS.md` tõestatud teise meeskonna agendiga, see README | 5 p |
| **Kokku** | **20 p** |

### Kaitsmiseks on vaja

**Ainult link git repole, tag'iga `smart-solutions-lab1` 72 h enne kaitsmist.**

Kaitsmine on veebis 06.10.26. Tag peab olema tehtud 72 h enne seda, see tähendab laupäeval 03.10.26 — samal nädalavahetusel, kui toimub kontakttund, kus järgmine labor välja antakse. Kõik, mida on vaja elusalt näidata — robot liigub, print, mõõtmine —, peab kõnes näha olema, nii et ühine laborist.

Tag'itud repo peab sisaldama kaustas `smart-solutions/lab1/`:
* `src/`: jaama rakendus, täheteed, pumbakasti juhtimine, alglaadimise seadistus.
* `config/`: ruuteri seadistus eksporditud, parool eemaldatud.
* `data/positions.json`, `docs/latency.csv`, `docs/boot.csv`, `docs/pick_test.csv`.
* `notebooks/lab1_chain.ipynb` väljunditega.
* `docs/`: `network.drawio`, `network.md`, `letters.md`, videod, teise meeskonna agendi transkript.
* `README.md`: see dokument, täidetud.
* `AGENTS.md` repo juurkaustas.

Muudatus kohapeal kaitsmisel: õppejõud küsib neljandat tähte, või nihutab paberit 50 mm, või nimetab asendi ümber. Meeskond teeb muudatuse jaamas — mitte sülearvutis — ja robot joonistab selle kokkusaamise ajal.

### Arenduspäevik

**KAARDISTA ISE — päevik.** Üks sissekanne iga töösessiooni kohta, kirjutatud iseendale, keeles, milles teie meeskond töötab, ja nii, et inimene, kes seal ei olnud, saab aru ilma küsimata. Kõigepealt kuupäev, siis kes olid kohal, mida te proovisite, mis päriselt juhtus — numbrites —, mida otsustasite ja miks, ja mis jäi järgmiseks korraks lahti. Sissekandeid lisatakse, mitte ei muudeta: kui 18.09 sissekanne osutus valeks, ütleb seda 25.09 sissekanne, ja vana jääb nii, nagu ta oli.

Omadussõnad ei ole tulemused. "Andur oli mürarikas" ei ole midagi; "±14 LSB paigal, ±40 LSB kui pumbakast töötab" on sissekanne. Kaks-kolm ausat lauset sessiooni kohta on küllalt — aga sessioon, milles oli viga, väärib viit.

**PP.KK.AA — kes olid kohal**
* Tegime:
* Juhtus (numbrid):
* Otsustasime, ja miks:
* Lahti järgmiseks korraks:

### Tulemused

**KAARDISTA ISE, lõpus.**

* Git repo ja tag:
* Kolm-neli numbrit, mille see labor andis, ühikutega:
* Mida me teeksime teisiti, kui alustaksime uuesti esimesest päevast:
* Mida järgmine labor peaks enne alustamist teadma:

### Tagasiside

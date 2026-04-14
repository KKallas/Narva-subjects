# Narva Kolledži tehnikaõppekava 2026/27 — Semester 1

## Roboti doseerimissüsteemi ehitamine

### Suur pilt

Kõik kolm ainet ehitavad ühte süsteemi: MG400 robotkäele professionaalse doseerimissüsteemi. Robot ja kompressor on olemas — tudengid ehitavad tööriistakomplekti mis muudab €3000 roboti kasulikuks.

Esimese aasta õppetund: elektroonika sõi kogu aja ja masinõppeni ei jõutud. Seekord on struktuur teistsugune: **iga elektroonika ülesanne on seotud konkreetse andmeallikaga** mida hiljem ML-is kasutatakse. Keegi ei ehita ahelat mis jääb kappi — kõik läheb töösüsteemi.

**Töökoht**: polükarbonaadist töölaud (100×100mm samm, 5mm metallaugud). Andurid, kinnitused ja tarvikud on 3D-prinditud moodulid mis klõpsuvad lauale. Iga meeskond saab oma MG400 (5 robotit, 4 meeskonda — üks varuks).

**Motivatsioon tudengile**: Doboti oma tarkvara on kasutuskõlbmatu. Sina ehitad parema. MG400 maksab €3000 ja seisab ladudes sest tööriistakomplekte ei toodeta. Iga tööriist mille sa ehitad ja dokumenteerid on potentsiaalne toode. Nordson EFD müüb doseerimise kalibratsiooni €15 000 eest — sinu versioon on robot + €50 elektroonika + sinu tarkvara.

### Meeskonnad

4 meeskonda, kuni 5 liiget igaühes (max 20 tudengit). Iga meeskond saab oma MG400 ja oma töölaualõigu. Meeskonnasiseselt jagunevad rollid: keegi vastutab andurite, keegi tarkvara, keegi mehaanika, keegi dokumentatsiooni eest.

### Hindamisfilosoofia

Hindamine on positiivne — saad täispunktid selle eest mida korrektselt teed. Kui prototüüp ei tööta, aga tudeng selgitab miks ja pakub alternatiive — punktid on siiski saavutatavad.

### Hindamisstruktuur

**Väiksemad projektid: 5 × 20 punkti = max 100 punkti**

Neli hindamiskategooriat projekti kohta:

* **Tööfailid** (5p): kood, skeemid, disainifailid — kõik repos
* **Analüüs** (5p): testimine, valideerimine, Jupyter notebook, Fourier/ML
* **Prototüüp** (5p): töötav füüsiline teostus
* **Dokumentatsioon** (5p): spetsifikatsioonid, põhjendused, juhendid

**Integratsiooniprojekt: max 70 punkti**

* Tööfailid (17p)
* Analüüs (17p)
* Prototüüp (18p)
* Dokumentatsioon (18p)

**Kokku võimalik: 170 punkti.** Hinne arvutatakse parimast 100-st.

Tudeng valib ise millised projektid teha:
* 5 väikest projekti = max 100p (piisab A-ks)
* Ainult integratsioon = max 70p (ideaalselt vormistatud = C)
* Integratsioon + mõned väiksed = punkte saab juurde lisada (nt integratsioon 60p + 2 väikest tööd 40p = 100p)
* 3 väikest projekti = max 60p (piisab E-ks)

### Vastastikune hindamine (asendab Q&A punkte)

Eelmine aasta probleem: 4 × 3h kaitsmisi läbi vaadata et leida kes küsis mida — ebarealistlik.

**Uus süsteem: kirjalik vastastikune hindamine**

Iga kaitsmisel mitte-esinev tudeng täidab **MS Teams chatis struktureeritud vormi** iga teise meeskonna kohta:

```
MEESKOND: [nimi]
TUGEVUS: [üks konkreetne tehniline asi mis töötas hästi]
KÜSIMUS: [üks tehniline küsimus mida tahad teada]
SOOVITUS: [üks konkreetne parandus]
```

Reeglid:
* Iga tudeng peab esitama tagasiside **vähemalt 2 meeskonnale** (3 teise meeskonna seast)
* Tagasiside peab olema **tehniline ja konkreetne** — "oli hea" ei loe
* Tagasiside on **kirjalik** → automaatne jälgimine, ei vaja videot üle vaadata
* Hindamine: 0p (ei esitanud), 1p (esitas aga pealiskaudne), 2p (sisuline)
* Max 4 boonuspunkti per kaitsmine (2 meeskonnale tagasiside × 2p)

**Miks see töötab**: tudengite hinne sõltub otseselt sellest kas nad kuulasid teisi. Ja kirjalik vorm tähendab et sa ei pea 12h videot vaatama — loed chati läbi 15 minutiga.

### MS Teams transkriptsioon kaitsmistel

Kaitsmised toimuvad MS Teams-is (kooli nõue). Teams transkribeerib automaatselt.

**Töövoog pärast kaitsmist:**
1. Laadi alla MS Teams transkript
2. Anna transkript Claude'ile koos juhisega: "Tõmba välja iga meeskonna demo tulemused, esitatud küsimused, ja tuvastatud probleemid"
3. Claude struktureerib → hindamisleht meeskondade kaupa
4. Kui transkriptsiooni kvaliteet on kahtlane (nimed valesti, tehniline termin moondunud) → Claude märgib need kohad ja küsib ainult nende kohta
5. Õppejõud vaatab üle ainult märgitud kohad, mitte kogu salvestust

**Ajavõit**: 12h video → 30 min ülevaatust.

### Hindamisskaala

* **91–100 punkti**: A
* **81–90 punkti**: B
* **71–80 punkti**: C
* **61–70 punkti**: D
* **51–60 punkti**: E
* **0–50 punkti**: F

Miinimum sooritamiseks: 51 punkti.

**Boonuspunktid** (lisaks vastastikusele hindamisele): õppejõu vigade avastamine, teiste meeskondade sisuline aitamine, erakordselt hea koostöö.

### Git repo kui ainus esitamiskanal

Õppejõud loob iga meeskonnale git repo enne semestri algust. **Mis pole repos, seda ei hinnata.** Erandeid ei ole.

**Repo struktuur** (õppejõud loob template):

Iga labor/ülesanne on eraldi kataloog. Kui labor 2 ehitab labori 1 peale, **kopeeri vajalikud failid** labori 2 kausta ja arenda seal edasi. Jah, see dupleerib koodi — aga see on teadlik kompromiss: algajad saavad aru kataloogidest, mitte git branchidest. Ja vana labor ei lähe kunagi katki.

```
meeskond-N/
├── andmehoive/
│   ├── lab1/                 ← Toor ADC + FFT
│   │   ├── src/              ← Arduino kood
│   │   ├── data/             ← CSV mõõtmised
│   │   ├── notebooks/        ← Jupyter analüüs (lab1_fft.ipynb)
│   │   └── docs/             ← skeemid, fotod, kirjeldus
│   ├── lab2/                 ← Op-amp + 4 konfiguratsiooni
│   │   ├── src/              ← Arduino kood (lab1 kood + op-amp + digifilter)
│   │   ├── data/             ← 4 × 30 mõõtmist
│   │   ├── notebooks/        ← Fourier võrdlus (lab2_comparison.ipynb)
│   │   └── docs/
│   ├── lab3/                 ← dP/dt IRQ + I2C
│   │   ├── src/              ← Arduino kood (lab2 kood + tuletis + IRQ + VL53L0X)
│   │   ├── data/
│   │   ├── notebooks/        ← lab3_derivative.ipynb
│   │   ├── pcb/              ← KiCad/EDA skeem + layout + Gerber
│   │   └── docs/
│   ├── task4/                ← MG400 andmekogumine
│   │   ├── src/              ← Python skript (MG400 API + UART + CSV logimine)
│   │   ├── data/             ← 500+ mõõtmist
│   │   ├── notebooks/        ← task4_analysis.ipynb
│   │   └── docs/
│   ├── task5/                ← ML mudel
│   │   ├── src/              ← treenimise skriptid
│   │   ├── models/           ← pickle/joblib mudeli fail
│   │   ├── notebooks/        ← task5_ml.ipynb
│   │   └── docs/
│   └── integration/
├── nutilahendused/
│   ├── lab1/                 ← MG400 API + veebiliides
│   │   ├── src/
│   │   └── docs/
│   ├── lab2/                 ← ESP32 WiFi + HMAC
│   │   ├── src/
│   │   └── docs/
│   ├── lab3/                 ← MQTT + InfluxDB
│   ├── task4/                ← Ühtne UI
│   ├── task5/                ← VPN + API
│   └── integration/
├── 3d-print/
│   ├── lab1/                 ← Süstlahoidik
│   │   ├── fusion/           ← .f3d + .step ekspordid
│   │   ├── stl/              ← prindifailid
│   │   └── docs/             ← joonised, fotod, mõõtmised
│   ├── lab2/                 ← Töölaua moodulid
│   ├── lab3/                 ← Elektroonika korpus
│   ├── task4/                ← Generatiivne disain
│   ├── task5/                ← Testpingi raam
│   └── integration/
└── README.md                 ← meeskonna ülevaade, liikmed, olek
```

**Miks see on oluline:**

1. **Hindamine**: õppejõud vaatab ainult repot. Kui pole commititud → pole olemas → 0p
2. **Reprodutseeritavus**: teine meeskond peab saama repo järgi projekti üles ehitada
3. **Analüüs**: kõik tööd jäävad alles edaspidiseks (õppekava arendus, näited järgmisele kursusele)
4. **Git ajalugu**: commit'id näitavad kes tegi mida ja millal — meeskonnatöö on läbipaistev

**Fusion 360 failid repos:**

Fusion 360 .f3d failid on pilves, aga repos peab olema:
* `.f3d` eksport (File → Export → .f3d) — täielik parameetriline mudel
* `.step` eksport — universaalne, avaneb igas CAD-is
* `.stl` — prindifail
* Screenshot/render kui vaja lisa olulisi vaateid, märkmeid
* 2D joonis PDF-ina (kui nõutud)

**Kaitsmise esitamine = Git tag:**

Kui meeskond on valmis kaitsmiseks, loovad nad tag'i:

```bash
git tag -a andmehoive-lab1 -m "Andmehõive Labor 1 kaitsmine"
git push origin andmehoive-lab1
```

Tag'i nimekonventsioon: `{aine}-{projekt}`, näiteks:
* `andmehoive-lab1`, `andmehoive-lab2`, `andmehoive-task5`
* `nutilahendused-lab1`, `nutilahendused-integration`
* `3d-print-lab1`, `3d-print-task4`

**Tag = "see on minu lõplik versioon".** Õppejõud hindab ainult tag'itud seisu. Kui tag puudub → pole esitatud → 0p.

Tag peab olema loodud **72h enne kaitsmist**. Git ajalugu näitab täpset aega — vaidlust pole.

**Reeglid:**
* Commit sõnumid kirjeldavad tehtud tööd kokkuvõtvalt (mitte "uuendus" või "fix")
* Suured binaarfailid (STL, GCODE, .f3d) → `.gitignore` + vastava kausta README-s täpne viide kust fail saada (nt Fusion 360 jagamislink, Teams kaust, Google Drive). "Failid on pilves" ei piisa — README peab sisaldama faili nime, asukohta ja ligipääsujuhendit
* Andmefailid (CSV) PEAVAD olema repos — need on analüüsi aluseks
* Jupyter notebookid PEAVAD olema repos koos väljunditega (Run All enne commitimist)

### Esitamisnõuded

* Kaitsmine = tag repos, **72h enne kaitsmiskuupäeva**
* Meeskondadel on 5 min esitluseks
* 10 min küsimused ja arutelu meeskonna kohta
* Kirjalik tagasiside teistele meeskondadele MS Teams chatis kaitsmise ajal

### Eelmise aasta tööd

Eelmise kursuse töid **ei ehitata peale**. Neid kasutatakse õppematerjalina:
* "Vaata mis eelmine kursus tegi — mis läks valesti ja miks?"
* Üks praktiline harjutus: proovi ehitada nende dokumentatsiooni järgi. Mis on puudu? See õpetab dokumenteerimise väärtust.

---

## Andmehõive (6 EAP)

*Närvisüsteemi ehitamine*

### Mõte

Ehita MG400 doseerimissüsteemile rõhumõõtmise süsteem ja õpi sellest andmetest. Üks rõhuandur, üks maketeerimisplaat — aga neli konfiguratsiooni mis näitavad samm-sammult miks iga täiustus on vajalik. Fourier analüüs teeb erinevuse nähtavaks: sa näed sagedusruumis täpselt mida filter eemaldab.

ML-i fookus on konkreetne ja mõõdetav: **kui palju materjali on süstlas järgi?** Pneumaatilises süstlas (õhk → silikoonkork → silikoon → otsik ≥2mm) mõjutavad rõhukõvera kuju kaks vastandlikku füüsikalist efekti: (1) õhu kokkusurutavus — rohkem õhku tähendab aeglasemat rõhutõusu, ja (2) materjali vastusurve otsikus — rohkem materjali tähendab suuremat takistust. Täpne seos täitetaseme ja rõhukõvera kuju vahel sõltub konkreetsest süsteemist (süstla mõõtmed, otsiku diameeter, materjali viskoossus, temperatuur) — ja selle seose väljaselgitamine ongi ML-i ülesanne. Mõõtes rõhukõvera kuju klapi avamise hetkel (reageerimisaeg, tõusu kiirus, platoo väärtus) saab hinnata järelejäänud mahtu — ilma lisaandurita.

### Mida õpid

* Analoog-digitaalmuunduri (ADC) põhimõtted ja veallikad
* Operatsioonivõimendi (op-amp) kasutamine signaali konditsioneerimiseks
* Analoog- ja digitaalfiltreerimise meetodid
* Fourier analüüs (FFT) signaali iseloomustamiseks aja- ja sagedusteljel
* Tuletis (dP/dt) ja katkestused (IRQ) reaalajalise reageerimise jaoks
* I2C sideprotokoll, müradiagnostika ja filtreerimine
* Andmete kogumine, puhastamine ja visualiseerimine (Jupyter Lab, pandas, scipy)
* Masinõppe mudelite treenimine ja valideerimine (scikit-learn)

### Töö

Laborid 1–3 ehitavad **samale maketeerimisplaadile** — iga labor lisab kihi, mitte ei ehita nullist. Sama MPX5700AP rõhuandur, sama ESP32, aga konfiguratsioon muutub ja Fourier näitab iga muutuse mõju.

**Labor 1: Toorsignaal ja esimene Fourier (34h)**

Ühenda rõhuandur otse ESP32 ADC-sse. Mõõda. Vaata mis tuleb.

Konkreetselt:
* **Esimene kontakttund algab elektroonika ja jootmise alustega** (~3h): jootekolbi käsitsemine ja ohutusnõuded, TH jootmine harjutusplaadil (takistid, kondensaatorid, LED-id, pistikuribad), SMD jootmine (0805/1206 pasiivkomponendid). Pasiiv- vs. aktiivkomponendid: mis on takisti, kondensaator, LED, op-amp IC, mikrokontroller. Maketeerimisplaat: kuidas read on ühendatud, toiterööpad. Multimeeter: pinge, takistus, katkestus. Keegi ei ühenda andurit enne kui jootmine ja komponentide tundmine on paigas.
* Ühenda MPX5700AP maketeerimisplaadile: toide, GND, väljund → ESP32 ADC (otse, ilma midagi vahele lisamata)
* Arduino kood: loe ADC väärtust 100Hz sämplimissagedusega, saada UART kaudu arvutisse
* Kogu 30 mõõtmist kolmes rõhukategoorias (madal, keskmine, kõrge — kasuta MG400 kompressorit)
* Teisenda ADC väärtused Pascaliteks MPX5700AP andmelehe valemi järgi
* Simuleeri ahelat Falstad-is, võrdle simulatsiooni päris mõõtmistega
* **Jupyter Lab — ajatelg**: visualiseeri signaali, arvuta keskmine, standardhälve, müratase
* **Jupyter Lab — Fourier (FFT)**: `scipy.fft` — vaata signaali sagedusruumis. Mis sagedused seal on? Kust tulevad piigid? (MG400 mootorid, impulsstoiteallikad, maandussilmused). Mis on mürapõhi?

Tulemus: tudeng näeb et toorsignaal on mürane ja Fourier näitab täpselt mis sagedused segavad. Müra allikad selguvad mõõtmisest — see on osa ülesandest, mitte ette antud vastus.

*Vajalikud teemad: ESP32 Arduino, UART, ADC, Jupyter Lab, Falstad, scipy.fft*

**Labor 2: Op-amp ja filtreerimine — Fourier näitab erinevust (30h)**

MPX5700AP väljund on 0.2–4.7V, aga ESP32 ADC loeb 0–3.3V. Lisa signaaliahel ja vaata Fourier'iga mis muutub.

Sama maketeerimisplaat, neli konfiguratsiooni — tudeng **ühendab juhtmeid ümber**:

| Konfig | Ahel | Mida Fourier näitab |
|:---|:---|:---|
| 1 (labor 1) | MPX → otse ADC | Toorandmed: mürapiigid (mootorid, toiteallikad) + lai mürapõhi |
| 2 | MPX → pingejagur → ADC | Signaali amplituud parem, aga müra ikka seal |
| 3 | MPX → op-amp (nihe + skaleerimine) → ADC | Ühismuutmüra väiksem (op-amp CMRR), signaal on ADC vahemikus |
| 4 | Konfig 3 + digitaalfilter koodis (liikuv keskmine) | Kõrgsageduslik müra kadunud, alles ainult aeglane rõhumuutus |

Konkreetselt:
* Simuleeri Falstad-is: pingejagur vs. op-amp
* Ehita op-amp (LM358N) ahel samale maketeerimisplaadile: nihe (-0.2V) + skaleerimine (ülemine ots 3.2V)
* Mõõda ostsilloskoobiga kõiki konfiguratsioone
* Kogu **iga konfiguratsiooniga samad 30 mõõtmist, sama rõhk** — 4 × 30 = 120 mõõtmist ühes CSV-s
* Lisa Arduino koodi digitaalfilter (liikuv keskmine, N=10)
* **Jupyter Lab — neljakordne võrdlus**:
  * Ajatelg: 4 signaali kõrvuti — visuaalselt näha mis muutub
  * Fourier: 4 spektrit kõrvuti — näha kuidas iga samm eemaldab müra
  * SNR (signal-to-noise ratio) arvutus iga konfiguratsiooni jaoks
  * Tabel: konfig × SNR × amplituud × müratase

**"Aha" hetk**: Fourier näitab konkreetseid müra allikaid (mootorite PWM, toiteallikate switching, maandussilmused) ja tõestab numbritega miks iga filtreerimissamm on vajalik. Tudeng peab ise välja selgitama mis sagedused on ja kust need tulevad — see on osa ülesandest.

*Vajalikud teemad: op-amp teooria ja praktika, Falstad, ostsilloskoop, digitaalfiltreerimine, Fourier võrdlusanalüüs*

**Labor 3: dP/dt tuletis, IRQ lävend ja I2C kalibreerimine (24h)**

Kaks uut võimekust: (A) reaalajaline ohutusmehanism rõhukõvera tuletise põhjal ja (B) otsiku kalibreerimine I2C kaugusanduriga. Rõhk süsteemis on ~2 bar — ohutu, aga ummistuse korral peab süsteem ise reageerima.

**Osa A: Rõhukõvera tuletis ja katkestus**

Normaalne doseerimine: rõhk tõuseb aeglaselt (dP/dt väike). Ummistunud otsik: rõhk tõuseb kiiresti (dP/dt suur). Tühi süstal: rõhk kukub (dP/dt negatiivne).

Konkreetselt:
* Lisa Arduino koodi tuletise arvutus: `dP = (P_now - P_prev) / dt`
* Lisa komparaator (op-amp Schmitt-triggerina) + ESP32 interrupt: kui dP/dt ületab lävendi → katkestus → STOP signaal MG400-le
* **Fourier teeb kohustuslikuks**: tuletis **võimendab müra** (kõrgsageduslik komponent × 2πf). Toorsignaali tuletis annab vale alarmi iga 20ms. Filtreeritud signaali tuletis töötab õigesti.
* Jupyter Lab: näita kõrvuti — toorsignaali dP/dt (mürane, pidevad false alarmid) vs. filtreeritud signaali dP/dt (puhas, reageerib ainult päris probleemidele)
* Testi: simuleeri ummistunud otsikut (pane otsik kinni) — kas IRQ käivitub? Kui kiiresti?
* Testi: simuleeri tühja süstlat — kas alarm tuleb?

**Osa B: I2C kaugusandur otsiku kalibreerimiseks**

VL53L0X töölaua peal mõõdab otsiku Z-kõrgust. Kui süstlat vahetatakse käsitsi, kontrollib süsteem automaatselt positsiooni.

Konkreetselt:
* Ühenda VL53L0X ESP32-ga (I2C: SDA + SCL), testi lühikese kaabliga — töötab
* Pikenda kaablit 30–50 cm, vii MG400 toitejuhtmete kõrvale — vaata mis juhtub (müra, valed väärtused, timeout'id)
* **Diagnoos**: kuidas aru saada et I2C liin on mürane? Ostsilloskoop näitab moonutatud signaali servi
* **Lahendus**: RC filter (100Ω + 100pF) SDA ja SCL liinidele, keerdpaar, ekraneerimine
* Kogu mõõtmised: lühike juhe vs. pikk mürane vs. pikk filtreeritud
* Kalibreerimisjada: MG400 liigub otsiku teadaolevasse positsiooni → VL53L0X mõõdab → arvuta offset X/Y/Z

* Disaini **trükkplaat kogu süsteemi jaoks**: rõhuandur + op-amp + komparaator (dP/dt IRQ) + VL53L0X ühenduspesad + ESP32 pistikuriba. Skeem + layout + DRC.
* **Labori 3 kaitsmine sisaldab PCB disaini ülevaatust** — õppejõud kontrollib skeemi enne tellimist. Ükski plaat ei lähe tootmisse ilma kontrollita.
* Gerber failide genereerimine ja tellimine (JLCPCB vms) kohe pärast kaitsmist. Plaat jõuab kohale ülesande 4 ajaks.

*Vajalikud teemad: tuletis ja IRQ, komparaator/Schmitt-trigger, I2C protokoll ja mürafiltreerimine, PCB disain ja tellimine*

**Ülesanne 4: Andmete kogumine MG400-ga (24h)**

Nüüd on süsteemis: rõhuandur (op-amp + filter), dP/dt alarm (IRQ), otsiku kalibreerimine (VL53L0X). Kui PCB on kohale jõudnud — joodeta ja testi. Kui mitte — jätka maketeerimisplaadiga. MG400 on andmete tehas — ta teeb sama doseerimist sadu kordi erinevate parameetritega.

Konkreetselt:
* Kirjuta Python skript mis: (a) saadab MG400-le doseerimiskäsu (kiirus, rõhk, trajektoor), (b) loeb ESP32 andurite andmed UART kaudu, (c) logib kõik CSV-sse
* Iga mõõtmine salvestab: rõhukõver (terve aegrida, mitte ainult üks number), otsiku Z-kõrgus, MG400 parameetrid, ajatempel
* Kogu vähemalt 500 mõõtmist: 5 kiirust × 5 rõhku × 20 kordust
* MG400 teeb seda automaatselt — tudeng kirjutab skripti ja laseb robotil tööd teha
* **Rõhukõvera analüüs Jupyter Lab-is**:
  * pandas: andmete puhastamine, korrelatsioonimaatriks, jaotused, outlier'id
  * **Reageerimisaeg vs. täitetase**: mõõda rõhukõvera kuju klapi avamise hetkel erinevate täitetasemete juures. Kas ja kuidas kõver muutub? Seos ei ole ette teada — see on mõõtmise ja ML-i ülesanne.
  * Fourier: kas rõhukõvera spekter muutub täitetasemega? (jah — rohkem õhku = erinev resonants)
  * Küsimus: mis veel mõjutab reageerimisaega peale täitetaseme? Temperatuur? Materjali vanus? Otsiku diameeter?

*Vajalikud teemad: Python automatiseerimine, MG400 API, pandas, aegrea analüüs, Fourier*

**Ülesanne 5: Masinõppe mudel (30h)**

Kasuta ülesande 4 andmestikku mudeli treenimiseks. Üks konkreetne küsimus: **kui palju materjali on süstlas järgi?**

Konkreetselt:
* Train/test split (80/20), cross-validation
* Lineaarne regressioon → otsustuspuu → random forest
* **Sisendtunnused rõhukõverast**:
  * Ajatunnused: reageerimisaeg (klapi avamisest murdepunktini), tõusu kiirus (dP/dt max), rõhu platoo väärtus, kõvera pindala
  * Fourier tunnused: dominantsagedus, spektri energia, sagedusjaotuse kuju
  * Keskkond: temperatuur (kui mõõdetud), otsiku diameeter, rõhu seadepunkt
* **Väljund**: järelejäänud maht (ml) — regressioon
* **Võrdlus 1 — tunnused**: kas Fourier tunnused parandavad mudelit võrreldes ainult ajatunnustega?
* **Võrdlus 2 — signaali kvaliteet**: kas op-amp andmetega (labor 2 konfig 3-4) treenitud mudel on parem kui toorandmetega (konfig 1)?
* **Võrdlus 3 — meeskondade vahel**: kelle mudel ennustab paremini oma seadmel? Kelle mudel töötab teise meeskonna seadmel? (Erinevad süstlad, materjalid, temperatuurid)
* MSE, R², residuaalide analüüs
* **Praktiline tulemus**: lävend — "süstlas on alla 2ml, vaheta!" Mis täpsusega suudab mudel seda öelda?

*Vajalikud teemad: scikit-learn, mudeli treenimine ja valideerimine, feature engineering, aegrea tunnused*

**Integratsiooniprojekt: Automaatne täitetaseme jälgimine**

Suletud ahel: MG400 doseerib → rõhuandur mõõdab → mudel hindab järelejäänud mahtu → veebiliides näitab "süstlas on ~4.2ml" → kui alla lävendi → hoiatus operaatorile. IRQ tagab ohutuse (ummistus → peatumine), ML tagab info (millal vahetada süstalt).

### Laborite progressioon kokkuvõttena

```
Labor 1: Toor ADC
  → "Saan numbri, aga mürane"
  → Fourier näitab: mürapiigid + mürapõhi (allikad selguvad mõõtmisest)

Labor 2: Op-amp + filter (4 konfiguratsiooni samal plaadil)
  → "Nüüd on signaal puhas"
  → Fourier näitab: iga samm eemaldab midagi konkreetset

Labor 3: dP/dt tuletis + IRQ + I2C + PCB disain
  → "Süsteem reageerib ise ja kalibreerub"
  → Fourier näitab: MIKS tuleb filtreerida enne tuletist (müra × 2πf)
  → PCB kaitstakse ja tellitakse

Ülesanne 4: MG400 automaatne andmekogumine (PCB jõuab kohale)
  → "500 mõõtmist, robot teeb tööd"
  → Reageerimisaeg vs. täitetase: seos selgub mõõtmisest

Ülesanne 5: ML mudel
  → "Mudel ütleb palju süstlas materjali on"
  → Feature engineering: Fourier tunnused vs. ajatunnused
```

### Kontakttundide ajakava

* **[12.09.26]** 🔧 **Konsultatsioon 1** (vabatahtlik): elektroonika ja jootmise alused — jootekolb, TH ja SMD jootmine, pasiiv- ja aktiivkomponendid, maketeerimisplaat, multimeeter
* **[12.09.26]** ESP32 esimene programm, ADC baas, Jupyter Lab sissejuhatus, esimene FFT
* **[03.10.26]** Labori 1 kaitsmine
* **[03.10.26]** Op-amp teooria, Falstad simulatsioon, neljakordne võrdlus
* **[~15.10.26]** 🔧 **Konsultatsioon 2**: op-amp praktiline abi — kuidas nihke ja skaleerimise ahel reaalselt töötab, tüüpilised vead, ostsilloskoobi kasutamine
* **[24.10.26]** Labori 2 kaitsmine
* **[24.10.26]** Tuletis, komparaator, IRQ + I2C müradiagnostika
* **[~05.11.26]** 🔧 **Konsultatsioon 3**: resolutsiooni määramine — kuidas arvutada süsteemi tegelikku lahutusvõimet (ADC bitid × op-amp võimendus × müratase → efektiivne resolutsioon). PCB skeemi eelkontroll.
* **[14.11.26]** Labori 3 kaitsmine (sisaldab PCB disaini ülevaatust → tellimine kohe pärast)
* **[14.11.26]** MG400 API ja automaatne andmekogumine Pythonis
* **[05.12.26]** Ülesande 4 kaitsmine
* **[05.12.26]** Masinõppe sissejuhatus: scikit-learn, aegrea tunnused, rõhukõvera analüüs
* **[16.01.27]** Ülesande 5 kaitsmine
* **[TBD]** Integratsiooniprojekti kaitsmine

---

## Nutilahendused (6 EAP)

*Aju ehitamine*

### Mõte

MG400 tarkvara on kasutuskõlbmatu, aga API töötab. Iga meeskond ehitab oma MG400 juurde **juhtimisjaama**: Raspberry Pi ekraaniga töölaua peal, ühendatud MG400-ga LAN kaabli kaudu ja ESP32 anduritega USB kaudu. RPI jooksutab veebiserverit — operaator juhib robotit brauserist (telefon, laptop, kust iganes). Tulemus: mini-tööstusarvuti mis asendab Doboti tarkvara millegi kasutatavaga.

```
Telefon/laptop (brauser)
        │ WiFi
        ▼
   ┌─────────────────────┐
   │  RPI + ekraan       │  ← töölaua peal, alati ühendatud
   │  Flask veebiserver  │
   │  Python MG400 API   │
   │  Andurite lugemine  │
   └──┬──────────┬───────┘
      │ LAN      │ USB/UART
      ▼          ▼
   MG400      ESP32 (andurid)
```

### Mida õpid

* IPv4 põhitõed ja ruutimine (mis on IP, subnet, gateway, miks MG400 on LAN pordis)
* RPI seadistamine ja Linux käsurida
* MG400 API (TCP/IP socket) programmeerimine Pythonis
* Veebiliidese loomine (HTML/JS + Flask)
* ESP32 side RPI-ga (USB/UART, WiFi, HTTP GET/POST, MQTT)
* Kasutajahaldus ja lukustusmehhanism (üks operaator korraga, vaatamisrežiim teistele)
* Digital Ocean dropleti seadistamine (pilveserver)
* VPN seadistamine (WireGuard) — turvaline kaugtunnel
* Nginx reverse proxy — keskne portaal mis suunab liikluse õigele robotile
* Reverse VPN: ESP32 seaded ligipääsetavad kaugelt ilma socket-taseme krüptota (VPN tunnel kaitseb)
* MQTT ja andmelogimine (InfluxDB)
* Süsteemi tõrkekindlus: watchdog'id, heartbeat, taastumine — kuidas avastada et üks teenus jooksis kokku ja taastuda ilma et pooleliolev töö tuksi läheb

### Töö

**Labor 1: RPI juhtimisstation ja MG400 API (28h)**

Esimene ülesanne: pane RPI tööle ja liiguta robotit.

Konkreetselt:
* RPI seadistamine: OS installimine, SSH, WiFi, staatiline IP seadistus
* **IPv4 põhitõed**: mis on IP-aadress, subnet mask, gateway. Miks MG400 on ühendatud LAN kaabliga (oma alamvõrk). Kuidas RPI räägib MG400-ga (Ethernet) ja ülejäänud maailmaga (WiFi) samaaegselt — kaks võrguliidest, kaks alamvõrku.
* MG400 TCP/IP API (port 29999 dashboard, port 30003 movement): kirjuta Python wrapper
* Flask veebiserver RPI peal: nupud liikumiseks, positsioonide salvestamine, kompressori juhtimine
* RPI ekraan: näita staatust (MG400 ühendatud/mitte, viimane käsk, positsioon)
* Testi: ava telefonis brauser → RPI IP → liiguta robotit

*Vajalikud teemad: RPI seadistus, Linux käsurida, IPv4 ja ruutimine, Python TCP/IP socket, Flask, HTML/JS*

**Labor 2: ESP32 andurid ja RPI integratsioon (26h)**

ESP32 (Andmehõive andurid) peab rääkima RPI-ga. Kaks varianti: USB/UART (lihtsam) ja WiFi (paindlikum).

Konkreetselt:
* **USB/UART**: ESP32 → USB → RPI. Pythonis `pyserial`, ESP32 saadab JSON-i iga mõõtmise kohta
* **WiFi alternatiiv**: ESP32 AP režiimis, RPI ühendub WiFi-ga. ESP32 teenindab HTTP API-t (GET /data)
* **Lihtne HTTP side**: ESP32 saadab andmeid RPI veebiserverisse (HTTP POST) või RPI küsib ESP32-lt (HTTP GET) — socket-taseme side ilma keeruka protokollita. Tudeng mõistab mis on HTTP päring ja vastus.
* **MQTT tutvustus**: ESP32 saadab andmeid MQTT kaudu (publish), RPI kuulab (subscribe). Mosquitto broker jookseb esialgu RPI peal lokaalselt. See valmistab ette labori 3 (MQTT dropletil) ja ülesande 4 (andmelogimine).
* RPI Flask teenus loeb ESP32 andmeid JA juhib MG400-d — üks veebileht näitab mõlemat
* RPI ekraan: reaalajas andurite andmed + MG400 olek
* Testi latentsust: mõõda aeg käsust kuni vastuseni (USB vs WiFi vs MQTT)

*Vajalikud teemad: ESP32 WiFi/UART, pyserial, HTTP GET/POST, MQTT baas, JSON API, RPI integratsioon*

**Labor 3: Digital Ocean droplet ja VPN (30h)**

Juhtimisstation töötab kohalikult. Nüüd tee see kaugelt ligipääsetavaks — turvaliselt.

Konkreetselt:
* **Digital Ocean dropleti seadistamine**: loo pilveserver (Ubuntu), SSH juurdepääs, tulemüüri seadistus (ufw)
* **WireGuard VPN seadistamine**: droplet on VPN server, iga meeskonna RPI on VPN klient. Iga RPI saab fikseeritud VPN IP (10.0.0.1, 10.0.0.2, 10.0.0.3, 10.0.0.4). Tunnel on alati üleval.
* **Nginx reverse proxy dropletil**: üks keskne veebileht mis näitab kõiki ühendatud roboteid:
  ```
  https://robots.kool.ee/
    ├── Robot 1 [●online]  → klikk → /robot/1/ → proxy_pass http://10.0.0.1:5000/
    ├── Robot 2 [●online]  → klikk → /robot/2/ → proxy_pass http://10.0.0.2:5000/
    ├── Robot 3 [○offline]
    └── Robot 4 [●online]  → klikk → /robot/4/ → proxy_pass http://10.0.0.4:5000/
  ```
  Kasutaja näeb RPI veebilehte täpselt nii nagu istuks labori laua taga — aga kuskilt kaugelt.
* **Reverse VPN loogika**: RPI ühendub dropletiga → droplet näeb RPI-d → nginx suunab kasutaja liikluse läbi VPN tunneli RPI-le. Tulemus: ESP32 seaded ja MG400 juhtimine ligipääsetavad kaugelt **ilma et ESP32 ise peaks krüptot tegema** — VPN tunnel kaitseb kogu liiklust.
* **IPv4 ruutimine praktikas**: RPI-l on 3 võrku — MG400 LAN (nt 192.168.1.x), kohalik WiFi (nt 192.168.0.x), VPN tunnel (10.0.0.x). Kuidas ruutimistabel töötab, miks paketid jõuavad õigesse kohta.
* **Roboti oleku lehekülg** (lihtne Flask/HTML dropletil): pingib VPN IP-sid, näitab kes on online, link igale robotile
* Testi: istu kodus, ava brauser, mine robots.kool.ee, klikka oma meeskonna robotil, juhi robotit labori töölaual

*Vajalikud teemad: Digital Ocean, Linux server, SSH, tulemüür, WireGuard VPN, nginx reverse proxy, IPv4 ruutimine*

**Ülesanne 4: MQTT andmelogimine ja ühtne liides (30h)**

Kogu andmevoog ühtsesse süsteemi: andurid → RPI → pilv → ajalugu. Keskne portaal näitab kõigi robotite staatust.

Konkreetselt:
* Mosquitto MQTT broker dropletil (sama server kus VPN ja nginx)
* ESP32 → RPI → MQTT: andurite andmed igast mõõtmisest
* RPI → MQTT: MG400 positsioon ja olek
* InfluxDB dropletil: kõik mõõtmised salvestuvad automaatselt
* **Ühtne veebiliides RPI-l** (Flask): juhtimine + reaalajas andurid + ajaloolised graafikud + CSV/JSON eksport
* **Keskse portaali laiendamine** (dropletil): lisa robotite nimekirja juurde viimane mõõtmine, olek, täitetaseme hinnang — üks pilk ja näed kõigi 4 roboti seisu
* **Kasutaja lukustus** — ainult üks operaator korraga:
  * Kui keegi avab roboti juhtimise → lukk läheb peale, teised näevad "Robot 2 — juhib: kaspar, alates 14:32"
  * **Vaatamisrežiim** teistele: kaamera pilt, andurite andmed, MG400 olek — kõik nähtav reaalajas. Aga nupud on hallid, käske saata ei saa.
  * **Uksekell**: kui tahad robotit kasutada aga keegi teine juhib → "Palun vabasta" nupp mis saadab teisele teatise
  * **Admin override**: kui ühendus kukkus ära ja lukk jäi peale (kasutaja brauser sulgus) → admin parooliga saab luku lahti teha
  * Lukk vabaneb automaatselt kui kasutaja pole 5 min midagi saatnud (timeout)
* Doseerimise "retseptid": salvesta parameetrikomplekte ja korda neid
* Kaamera vaade (USB kaamera RPI küljes): operaator näeb mida robot teeb
* ESP32 offline-puhver: kui WiFi kaob, puhverda 100 sõnumit LittleFS-i, saada kui ühendus taastub
* UX test: anna süsteem teisele meeskonnale — kas saavad 5 minutiga aru?

*Vajalikud teemad: MQTT, Mosquitto, InfluxDB, Flask dashboard, nginx, sessioonihaldus, lukustusmehhanism, UX*

**Ülesanne 5: Tõrkekindlus, REST API ja LLM integratsioon (34h)**

RPI teeb 5 asja korraga: Flask, MG400 side, ESP32 lugemine, MQTT, kaamera. Üks neist jookseb kokku. Kuidas avastada ja taastuda ilma et pooleliolev doseering tuksi läheb?

**Osa A: Odava raudvara piirangud (akadeemiline fookus)**

RPI on €50 arvuti mis juhib €3000 robotit. See on hea kompromiss — aga tal on reaalsed piirangud mida kallis tööstusarvuti ei tunne. Eesmärk **ei ole** teha RPI-st tööstuskontrollerit. Eesmärk on **mõista piiranguid, mõõta neid ja disainida nendega arvestades**.

Konkreetselt:
* **Mõõda piirangud**: RPI Flask teenindab veebilehte → samal ajal ESP32 saadab andmeid USB kaudu → samal ajal MG400 TCP socket ootab vastust. Python GIL tähendab et need **ei jookse päriselt paralleelselt**. Mõõda: mis juhtub kui kõik kolm toimuvad korraga? Kui kaua Flask blokeerub kui MG400 vastus viibib? Kui palju ESP32 mõõtmisi läheb kaduma sel ajal?
* **Kus komistab**: MG400 TCP vastuse ootamine blokeerib veebilehe laadimist. MQTT publitseerimine võtab aega kui võrk on aeglane. Mõõda ja dokumenteeri iga piirang konkreetse numbriga.
* **Lihtne disain piirangute ümber**: mitte keerulised watchdog'id, vaid lihtne arhitektuur — eraldi protsessid (mitte threadid) oluliste teenuste jaoks, queue andmevahetuseks, timeout'id igale socket-ühendusele. Kui MG400 ei vasta 2 sekundit → ära oota, märgi "ühendus katkenud" ja jätka teistega.
* **Ohutu olek on lihtne**: kui midagi on valesti → kompressor kinni. Mitte kunagi jätka automaatselt pärast tõrget. See ei nõua keerulist loogikat — ainult distsipliini.
* **Praktiline test**: tõmba ESP32 USB kaabel välja keset doseerimist. Tõmba MG400 LAN kaabel välja. Pane WiFi kinni. Mis juhtub igal juhul? Kas süsteem jääb ohutule olekule? Kas taastub kui ühendus tuleb tagasi? Dokumenteeri iga stsenaarium: mis juhtub, kaua kestab, kas toode on rikutud.
* **Jupyter Lab analüüs**: kogu tõrgete logi (mis teenus, millal, kaua kestis). Visualiseeri: kas tõrked on seotud koormusega? Mis on keskmine taastumisaeg? **Kus on piir** kus RPI enam ei piisa ja on vaja päris tööstusraudvara?

**Osa B: REST API ja LLM**

Konkreetselt:
* REST API RPI-l: /status, /dispense, /history, /export — dokumenteeritud, JSON
* API ligipääsetav ka läbi keskse portaali: robots.kool.ee/robot/1/api/ → proxy RPI API-le
* Aeglukustus: kaugjuhtimise lõpp-punktid töötavad ainult kui kohalik operaator on RPI ekraanil need aktiveerinud (ajapõhine luba)
* README lõpp-punkt (/api) mis kirjeldab kõiki lõpp-punkte — keelemudelid saavad seda lugeda ja mõista mida süsteem teeb
* Demonstreeri täistsükkel: operaator aktiveerib RPI-lt → kaugkasutaja (või LLM) saadab API käsu läbi portaali → robot doseerib → andmed salvestuvad → automaatne lukustamine aegumise korral
* API auditlogi: kes, millal, mida küsis

*Vajalikud teemad: watchdog, heartbeat, tõrkekindlus, ohutu olek, REST API disain, aeglukustus, LLM integratsioon, auditlogi*

**Integratsiooniprojekt: Terviklik juhtimisstation**

RPI juhtimisstation kui terviktoode: ühe SD-kaardi kloonimine → uus MG400 on kohe kasutatav. Seadistus: ühenda LAN MG400-ga, ühenda ESP32 USB-ga, lülita sisse. Paigaldatav ühe skriptiga. VPN automaatne ühendus. Lukustus töötab. Tõrkekindlus töötab. Dokumentatsioon mis on piisav et teine inimene saab süsteemi üles seada.

### Kontakttundide ajakava

* **[12.09.26]** RPI seadistus, IPv4 põhitõed, MG400 API, esimene liigutus
* **[12.09.26]** Flask sissejuhatus, HTML/JS baas
* **[03.10.26]** Labori 1 kaitsmine
* **[03.10.26]** ESP32 ↔ RPI side (USB/UART ja WiFi)
* **[~15.10.26]** 🔧 **Konsultatsioon 1**: IPv4 ruutimine praktikas — mis on subnet, gateway, miks RPI-l on 3 võrguliidest, kuidas paketid liiguvad. Käed-külge: `ip route`, `ping`, `traceroute`.
* **[24.10.26]** Labori 2 kaitsmine
* **[24.10.26]** Digital Ocean, Linux server, WireGuard VPN
* **[~05.11.26]** 🔧 **Konsultatsioon 2**: VPN praktikas — WireGuard seadistamine samm-sammult, avaliku/privaatvõtme loogika, miks tunnel töötab NAT-i taga, kuidas kontrollida kas tunnel on üleval.
* **[14.11.26]** Labori 3 kaitsmine
* **[14.11.26]** MQTT, InfluxDB, ühtne liides
* **[~25.11.26]** 🔧 **Konsultatsioon 3**: nginx reverse proxy — kuidas droplet suunab liikluse õigele RPI-le, proxy_pass loogika, HTTPS sertifikaat (Let's Encrypt), veaotsing kui proxy ei tööta.
* **[05.12.26]** Ülesande 4 kaitsmine
* **[05.12.26]** REST API, aeglukustus, LLM integratsioon
* **[16.01.27]** Ülesande 5 kaitsmine
* **[TBD]** Integratsiooniprojekti kaitsmine

---

## 3D Printimine ja CAD (6 EAP)

*Keha ehitamine*

### Mõte

Alustad Blenderis — teed lihtsa objekti ja õpid kui raske on hoida mudelit "vettpidavana" (solid) kui töötad punktide ja polügoonidega. Iga vale klikk tekitab augu, vale normaali, non-manifold serva. See annab väga intuitiivse arusaama milles Fusion on hea: Fusionis on mudel *alati* solid, sest tööriist ei luba sul vigast geomeetriat luua.

Akadeemiline tuum: **kuidas objekti kuju mõjutab tootmist**. Lihtne näide: pööra objekti 4 orientatsiooni ja vaata mis juhtub printimisajaga, tugimaterjali kogusega ja tugevusega. Viilutaja lõikab mudeli kihtideks — iga kihi ristlõike pindala ja perimeetri pikkus määravad printimisaja. See on integreerimine praktikas: printimisaeg ≈ Σ(kihi_aeg) üle kõigi kihtide, kus kihi_aeg sõltub ristlõikest.

### Mida õpid

* Polügoonmodelleerimine (Blender) — mis on mesh, miks STL on kolmnurgad, kus tekivad vead
* Teekond Blenderist printerini: mesh → STL eksport → viilutaja → G-code → print. Mis läheb igas sammus valesti (avatud servad, vale normaali suund, liiga väikesed detailid, non-manifold geomeetria).
* Parameetriline modelleerimine (Fusion 360) — miks piirangupõhine disain on tootmise jaoks parem kui vaba vormimine
* Disaini sisendid: füüsikalised (tugevus, mass), ärilised (printimisaeg, materjali kulu), esteetilised (pinna kvaliteet, kuju)
* Orientatsiooni optimeerimine: integreerimine kihtide kaupa → printimisaja, tugede ja tugevuse ennustamine
* Koostude ja kinnituste disain (snap-fit, print-pause, metallsisestused)
* Mehhaaniline simulatsioon (Fusion 360 FEA)
* Generatiivne disain ja võrdlus käsitsidisainiga
* Tehnilised joonised ISO standardite järgi

### Töö

**Labor 1: Blenderist printerini — teekond ja komistuskohad (34h)**

Esimene labor EI alusta Fusioniga. Alusta Blenderiga — tee pliiatsi hoidik MG400 tööriistaflantsile. Robot joonistab esimesel päeval. Siis paranda Fusionis ja hiljem asenda pliiats süstlaga.

**Osa A: Blender ja mesh-põhine modelleerimine**

Esimene print: **pliiatsi hoidik MG400 tööriistaflantsile**. Lihtsaim võimalik tööriist — toru mis hoiab pliiatsit ja kinnitub flantsi külge. Robot joonistab kohe esimesel päeval.

Konkreetselt:
* Tee Blenderis pliiatsi hoidik — toru + flantsi kinnitus
* Ekspordi STL — ava viilutajas. Mis juhtub? (tõenäoliselt: avatud servad, vale normaali suund, liiga õhukesed seinad, non-manifold kohad)
* **Mesh diagnostika**: mis on kolmnurkvõrk, miks STL on ainult kolmnurgad, mis on normaali suund ja miks see oluline on (viilutaja ei tea mis on "sees" ja mis on "väljas"). Kuidas leida ja parandada vigu (Blender 3D Print toolbox, Meshmixer).
* Paranda vead, prindi, pane MG400 külge, **joonista**. Esimese päeva lõpuks: robot liigub ja jätab paberile jälje. Pliiatsi hoidik on ebatäpne ja logiseb — aga töötab.

**Osa B: FDM füüsika — miks kuju mõjutab kõike**

Sama pliiatsi hoidik, aga nüüd mõista MIKS printer käitub nii nagu ta käitub:

**Overhang ja 45° reegel:**
* Prindi sama sein 30°, 45°, 60° ja 90° nurga all (vertikaali suhtes)
* 45° alla — iga kiht toetub eelmisele ~50% ulatuses, piisab et plastik ei vajuks
* 90° (horisontaalne lagi) — midagi ei toeta, plastik vajub alla → tugimaterjal vajalik → aeg + materjal + halb pind alt
* **Miks just 45°?** Geomeetria: kihi kõrgus 0.2mm, kihi nihke 0.2mm = 45° diagonaal. Alla seda nurka ei ulatu eelmine kiht piisavalt.

**Sirge vs. ümmargune:**
* Prindi kaks versiooni: sirgete seintega hoidik ja ümmarguse seinaga hoidik (sama maht, sama seinapaksus)
* Mõõda: printimisaeg, pinna kvaliteet. Ümmargune on aeglasem (pea peab pidevalt suunda muutma, kiirendus/aeglustus iga sammu juures) ja pind on astmeline (ringid → polügoon kihtide vahel).
* **Miks sirge on parem FDM-is?** Otsik liigub sirgjooneliselt täiskiirusel. Kõver tähendab pidevat aeglustamist ja kiirendamist. Materjali kulu on sama, aga aeg ja kvaliteet on halvemad.

**Orientatsioon ja tugevus:**
* Sama hoidik, 4 orientatsiooni — prindi kõik
* **Tõmbetest igale orientatsioonile**: FDM kihtide vaheline side on NÕRGIM koht. Tõmme kihisuunas = tugev (plastik ise). Tõmme risti kihtidega = nõrk (kihtide vaheline adhesioon). Orientatsioon määrab kus on nõrk koht.
* Jupyter Lab: visualiseeri kihtide ristlõikeid iga orientatsiooni jaoks, arvuta printimisaeg matemaatiliselt (Σ kihtide perimeetrid ja pindalad), võrdle viilutaja ennustusega

**Praktiline järeldus**: orientatsiooni valik EI ole esteetiline — see on matemaatiline optimeerimine kus sisendid on kiirus, tugevus ja tugimaterjali kulu. Disainer peab teadma neid reegleid ENNE kui hakkab Fusionis detaili joonistama.

**Osa C: Blenderist Fusionisse — miks piirangud juhivad disaini**

Pliiatsi hoidik töötas, aga logiseb ja mõõdud ei klapi. Nüüd tee sama asi Fusionis:
* Mõõda MG400 tööriistaflantsit nihkkaliibriga — sisesta mõõdud parameetritena
* Pliiatsi diameeter, nurk, kõrgus — kõik parameetrilised, muudetavad
* Ekspordi STL — viilutajas pole vigu (sest Fusion genereerib korrektse mesh-i)
* Prindi, pane MG400 külge — joonistus on kohe parem (ei logise, mõõdud klapivad)
* **See on Fusioni mõte**: disaini sisend on mõõdetud piirangud (flantsi mõõdud, pliiatsi diameeter), mitte silmamõõt

**Osa D: Pliiatsist süstlaks**

Nüüd asenda pliiats süstlaga — sama kinnituspunkt, aga lisa:
* Süstla diameeter (suurem kui pliiats) — muuda Fusionis parameetrit
* Pneumaatikaühenduse koht (MG400 kompressori voolik)
* Testi 3 süstlamõõtu: 5ml, 10ml, 20ml — muuda parameetrit, ekspordi, prindi. Üks mudel, palju variante.
* Prindi, testi MG400-l: kas süstal püsib? Kas saad vahetada ühe käega?

Progressioon: Blenderi pliiatsi hoidik → Fusioni pliiatsi hoidik → Fusioni süstlahoidik. Iga samm lisab piirangu.

*Vajalikud teemad: Blender baas, mesh/STL diagnostika, viilutaja ja orientatsioon, printimisaja integreerimine, Fusion 360 parameetriline disain, FDM piirangud*

**Labor 2: Töölaua moodulid ja kinnitused (30h)**

Disaini moodulid mis kinnituvad töölaua 5mm aukudesse. Siin tulevad mängu piirangud mida Blenderiga ei lahenda.

Konkreetselt:
* Disaini universaalne kinnitusjalg mis sobib 5mm aukude sammu ja 100mm ruudustikuga — mõõtmed peavad olema **täpsed** (sellepärast Fusion, mitte Blender)
* Iga anduri jaoks spetsiifiline ülaosa mis klõpsub jalale (snap-fit)
* Vedrumehhanismiga kinnitus: surve alla, klõps, valmis. Tõmba üles, lahti.
* **Polt-mutter-seib kompressioon — PLA tugevamaks kui materjal**:
  * FDM kihtide vaheline adhesioon on nõrk tõmbel (kihid lahti). Aga survel on PLA tugev.
  * Polt + mutter + seib surub kihid kokku → kihtide vaheline jõud muutub tõmbest surveks → detail peab mitu korda rohkem vastu
  * Sama põhimõte nagu pingestatud armatuurbetoonis: metall (polt) kannab tõmbekoormust, plast (PLA) kannab survet. Seib jaotab jõu laiemale pinnale → ei suru plastikusse sisse.
  * **Praktiline test**: prindi sama detail (a) ilma poltideta, (b) läbipoldituna. Tõmbetest MG400-ga. Mõõda purunemiskoormust. Dokumenteeri erinevus.
  * Disainireegel: kuhu panna poldiaugud et kihid oleks alati surve all? Kus on koormusteed?
* Mehhaaniline simulatsioon (Fusion FEA): kas snap-fit peab vastu? Kus on pingekonsentratsioonid?
* Fusion 360 2D joonis: tootmisjuhend teisele inimesele

*Vajalikud teemad: Fusion 360 koostud, snap-fit disain, kompressioonkinnitused, FEA, 2D joonis*

**Labor 3: Elektroonika korpus ja print-pause (28h)**

Integreeritud korpus mis hoiab ESP32-d, op-amp plaati ja kõiki ühendusi. Kinnitub töölaua moodulina.

Konkreetselt:
* Integratsioonigraaf (draw.io): mis komponendid, kuidas ühenduvad
* Materjalide nimekiri (BOM)
* Korpus: ventilatsiooniavad, kaablite sisseviigud, kinnituselemendid
* Print-pause töövoog: pausi print, sisesta mutrid/magnetid/sisestused, jätka
* Kokkupanekujuhend mis on piisavalt selge et teine meeskond saab järgi teha

*Vajalikud teemad: integratsioonigraaf, BOM, print-pause, kokkupanekujuhend*

**Ülesanne 4: Olemasoleva disaini parandamine — kolm lähenemist (30h)**

Õppejõul on olemasolevad 3D prinditud + polditatud disainid: rõhutoru otsikud, välise solenoidi kinnitused, süstla otsikud. Need töötavad, aga on esimesed versioonid. Tudeng valib ühe ja parandab seda **ühe konkreetse mõõdiku** kaupa:

**(A) Tootmiskiirus** — sama tugevus, aga prinditakse kiiremini
**(B) Tugevus** — sama printimisaeg, aga peab rohkem vastu
**(C) Kasutuskordade arv** — sama kuju, aga kestavustest näitab pikemat eluiga

Konkreetselt:
* Analüüsi olemasolevat disaini: kus on materjalikulu mõttetu? Kus on nõrk koht? Mis orientatsioonis on prinditud ja miks?
* **Lähenemine 1 — käsitsi inseneridisain**: ribid koormusteedele, seinapaksuse muutmine, FDM-sõbralik geomeetria, poldiaugude paigutus
* **Lähenemine 2 — Fusion 360 generatiivne disain**: defineeri kinnituspunktid, koormused, keelualad — lase algoritmil pakkuda
* Prindi kõik 3 versiooni (algne + käsitsi + generatiivne)
* Orientatsiooni optimeerimine igale versioonile (labori 1 meetodiga — integreerimine)
* Korratav test MG400-ga: robot rakendab sama koormust igale versioonile, mõõda tulemust
* **Võrdlustabel**: printimisaeg, mass, tugevus, kasutuskordade arv, tugimaterjali kulu
* Kas käsitsi parandus on parem kui generatiivne? Miks? (tavaliselt jah — sest insener teab FDM piiranguid, algoritm ei tea)

*Vajalikud teemad: olemasoleva disaini analüüs, generatiivne disain, FEA, FDM optimeerimine, testmetoodika*

**Ülesanne 5: ISO joonis ja CNC tellimine (24h)**

Disaini metalldetail (töölaua moodul, kinnitus vms) ja telli see 2D CNC teenusena väljast. **ISO joonis on tellimusdokument** — kui joonis on vale, tuleb vale detail. See valideerib kas tudeng oskab funktsionaalset joonist teha.

Konkreetselt:
* Disaini Fusionis metalldetail mis vajab CNC lõikamist (nt töölaua kinnitusplaat, roboti alusplaat, testpingi element)
* **ISO tehniline joonis**: vaated, lõiked, mõõtmed, tolerantsid, pinnakaredus, materjali spetsifikatsioon
* GD&T kriitiliste pindade jaoks (nt augu asukoha tolerants mis peab sobima 3D prinditud sisestusega)
* Tolerantsianalüüs: CNC detail (±0.1mm) + 3D prinditud sisestus (±0.3mm) — kas sobivad kokku?
* **Õppejõu ülevaatus enne tellimist** — sama loogika nagu PCB Andmehõives. Ükski detail ei lähe tootmisse ilma kontrollita.
* Tellimine 2D CNC teenuselt (laserlõikus, freesimine vms). Detail jõuab kohale prototüüpimise alguseks (2. semester).
* **Valideerimine**: kui detail kohale jõuab — mõõda nihkkaliibriga. Kas mõõdud vastavad joonisele? Kas 3D prinditud sisestus sobib? Kui ei → miks? Kas joonis oli vale või CNC tootja tegi vea?

*Vajalikud teemad: ISO tehnilised joonised, GD&T, tolerantsianalüüs, CNC teenuse tellimine ja valideerimine*

**Integratsiooniprojekt: Täielik mehhaanikapakett**

Kõik mehaanilised komponendid tootmisvalmis dokumentatsiooniga: süstlahoidik + andurimoodulid + elektroonika korpus + testpingi raam. Pakett mille järgi teine inimene saab süsteemi kokku panna.

### Kontakttundide ajakava

* **[11.09.26]** Blender baas, mesh ja STL, polügoonid → kolmnurgad → vead
* **[11.09.26]** Viilutaja, orientatsioon, esimene print — ja miks see ei ole ideaalne
* **[02.10.26]** Labori 1 kaitsmine (Blender + Fusion + orientatsiooni analüüs)
* **[02.10.26]** Fusion koostud, snap-fit, metallsisestused, vedrumehhanismid
* **[23.10.26]** Labori 2 kaitsmine
* **[23.10.26]** Print-pause, komponentide sisestamine, korpuse disain
* **[13.11.26]** Labori 3 kaitsmine
* **[13.11.26]** Generatiivne disain töövoog
* **[04.12.26]** Ülesande 4 kaitsmine
* **[04.12.26]** ISO joonised, GD&T, CNC kommunikatsioon
* **[16.01.27]** Ülesande 5 kaitsmine
* **[TBD]** Integratsiooniprojekti kaitsmine

---

## Ainete koostoime

```
Semester 1 (sept 2026 — jaan 2027):
┌──────────────────────────────────────────────────────────┐
│ Andmehõive            Nutilahendused        3D Print     │
│ ─────────             ──────────────        ────────     │
│ L1: Toor ADC + FFT    L1: RPI + MG400 API   L1: Hoidik   │
│ L2: Op-amp + 4 konf.  L2: ESP32 ↔ RPI      L2: Moodulid │
│ L3: dP/dt IRQ + I2C   L3: DO droplet + VPN L3: Korpus   │
│ Ü4: MG400 andmekogu.  Ü4: MQTT+DB+UI      Ü4: GenDes   │
│ Ü5: ML mudel          Ü5: REST API + LLM   Ü5: Raam     │
└──────────────────────────────────────────────────────────┘
```

### Fourier analüüs läbi kogu Andmehõive

```
Labor 1: FFT näitab toorsignaali müra (mootorid, toiteallikad, maandussilmused)
    ↓
Labor 2: FFT näitab iga konfiguratsiooni mõju (4 spektrit kõrvuti)
    ↓
Labor 3: FFT näitab miks tuletis vajab filtreerimist (müra × 2πf)
    ↓
Ülesanne 4: FFT näitab kas rõhukõvera spekter muutub täitetasemega
    ↓
Ülesanne 5: FFT tunnused → ML feature engineering
```

### Rõhukõvera loogika ja ML fookus

Pneumaatiline süstal (õhk → silikoonkork → silikoon → otsik ≥2mm):

```
Klapp avaneb → rõhk hakkab tõusma → mitu füüsikalist efekti samaaegselt:

  Efekt 1: Õhu kokkusurutavus
    → rohkem õhku silindris = rõhk tõuseb aeglasemalt
    → vähem õhku = rõhk tõuseb kiiremini

  Efekt 2: Materjali vastusurve otsikus
    → rohkem materjali = suurem takistus voolule
    → vähem materjali = väiksem takistus

  Efekt 3: Materjali kokkusurumatavus
    → silikoon ei suru kokku = edastab rõhu kohe otsikule
    → õhk surub kokku = neelab energiat

Nende efektide koosmõju → rõhukõvera kuju muutub täitetasemega
Täpne seos selgub mõõtmisest → ML mudel õpib selle ära
```

* **Ummistunud otsik**: rõhk tõuseb järsult ja ei lange (dP/dt suur → IRQ)
* **Otsik ≥2mm**: eelmise aasta õppetund — peenem otsik ummistub

**ML küsimus**: rõhukõvera kuju sõltub täitetasemest, aga ka temperatuurist, materjali vanusest ja otsiku läbimõõdust. Seos pole lineaarne ega ilmne — selle väljaselgitamine on ML-i ülesanne. Lisaandurit (kaal, optika) ei ole vaja — rõhukõver sisaldab piisavalt infot.

**Praktiline väärtus**: süsteem ütleb operaatorile "süstlas on ~3.5ml, piisab veel ~12 doseerimiseks". Seda ei paku ükski olemasolev Doboti tööriist.

### Raudvara sõltuvuste ajakava

Kolm ainet paralleelselt — raudvara ei tohi konflikti minna. Lahendus: **2 ESP32 per meeskond** (€5/tk), üks jääb alati maketeerimisplaadile, teine RPI külge.

```
            SEPT        OKT         NOV         DEC         JAN
Andmehõive  ESP32-A     ESP32-A     ESP32-A     ESP32-A     Jupyter
            breadboard  breadboard  breadboard  +RPI+MG400  (ainult
            (ainult)    (ainult)    +PCB dis.   (integr.)   andmed)

Nutilah.    RPI+MG400   RPI+ESP32-B RPI         RPI+kõik    RPI+kõik
            (API)       (side)      +DO droplet (integr.)   (API+LLM)

3D Print    Fusion 360  Fusion 360  Fusion 360  Fusion 360  Fusion 360
            printer     printer     printer     printer     (ei vaja
            (ei vaja elektroonikat)                          raudvara)
```

**Konfliktivaba**: ESP32-A (Andmehõive, maketeerimisplaat) ja ESP32-B (Nutilahendused, RPI USB) töötavad paralleelselt. MG400 on sept-okt ainult Nutilahenduste käes (API õppimine), nov-dec liitub Andmehõive (andmekogumine). 3D Print ei vaja elektroonikat üldse.

**Integratsioonipunkt** (nov-dec): Ü4 mõlemas aines — kõik raudvara tuleb esimest korda kokku. See on plaanipärane, mitte konflikt.

### Mida iga aine toodab teistele

| Allikas | Väljund | Kasutaja |
|:---|:---|:---|
| Andmehõive L1-L2 | Rõhuandur + op-amp + filter (maketeerimisplaadil) | Andmehõive Ü4 |
| Andmehõive L3 | dP/dt IRQ ohutusmehanism + VL53L0X otsiku kalibreerimine | Andmehõive Ü4 |
| Nutilahendused L1 | RPI juhtimisstation + MG400 Python wrapper | Andmehõive Ü4 |
| Nutilahendused L2 | ESP32 ↔ RPI integratsioon | Andmehõive Ü4 |
| Nutilahendused Ü4 | MQTT + InfluxDB + ühtne veebiliides RPI-l | Andmehõive Ü4-Ü5 |
| 3D Print L1 | Süstlahoidik MG400-le (pneumaatika, kiirvahetis) | Andmehõive Ü4, Nutilahendused L1 |
| 3D Print L2 | Töölaua moodulid (anduri- ja VL53L0X kinnitused) | Andmehõive L3 |

### Komponentide tellimine

**ENNE semestri algust** (juuli 2026) tellida:

**RPI juhtimisstation (üks per meeskond):**
* Raspberry Pi 4 (4 tk + varuks 1) — vajab Ethernet + WiFi + USB + HDMI
* 7" puuteekraan või HDMI monitor (4 tk)
* SD kaardid 32GB+ (8 tk — varud)
* RPI toiteallikad (4 tk)
* LAN kaablid MG400 ühenduseks (4 tk)
* Digital Ocean konto (üks kursusele, iga meeskond saab oma dropleti)

**Elektroonika:**
* ESP32 / M5 Atom Lite — **2 per meeskond** (ESP32-A maketeerimisplaadile, ESP32-B RPI külge). Kokku 8 tk + varuks 4 = 12 tk
* MPX5700AP rõhuandur (10 tk)
* LM358N op-amp (20 tk)
* VL53L0X kaugusandur I2C (10 tk)
* Takistid, kondensaatorid komplekt (5 komplekti) — sh 100Ω + 100pF I2C filtriks
* Maketeerimisplaadid (20 tk)
* Juhtmekomplektid (10 komplekti)
* Jootekolbid + tina (5 komplekti, üks per meeskond)
* USB kaablid (20 tk)

**Doseerimise tarvikud:**
* Süstlad 5ml, 10ml, 20ml (20 tk igat mõõtu)
* Doseerimise otsikud ≥2mm (50 tk — kuluvad)
* Silikoon / doseerimispasta testimiseks (5 tuubi)

**3D printimine:**
* PLA filament (10 kg)
* PETG filament (5 kg — korpustele)
* Kuumussisestused (M3 mutrid, 100 tk)

**Olemasolev:**
* MG400 robotkäed (5 tk) + kompressorid
* Polükarbonaadist töölauad (100×100mm samm, 5mm augud)
* 3D printerid
* Ostsilloskoop (labor)

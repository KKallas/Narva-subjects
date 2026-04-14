## Üldinfo
### Eesmärgid
Kursuse eesmärk on anda tudengitele praktilised ja teoreetilised oskused andmehõive süsteemide ehitamiseks, analoogsignaali töötlemiseks ja masinõppe rakendamiseks mõõteandmetele. Kursus keskendub MG400 doseerimissüsteemi rõhumõõtmisele: alustades toorsignaalist ja jõudes masinõppe mudelini mis hindab süstla täitetaset rõhukõvera kujust. Akadeemiline tuum on **signaalitöötluse teooria** (Fourier analüüs aja- ja sagedusruumis, analoog- ja digitaalfiltreerimine, tuletise mõju mürale) ja **masinõpe** (tunnuste eraldamine aegridadest, mudelite treenimine ja valideerimine, feature engineering). Iga elektroonika teema on seotud konkreetse probleemiga — op-amp võimendab rõhuandurit mis mõõdab päris doseerimist, I2C filter on vajalik sest mootorijuhtmed tekitavad müra.

### Õpiväljundid
Õppeaine läbinud õppija:
- eristab andmehõivesüsteemi komponente ja mõistab riistvarapõhiseid signaalitöötlusahelaid;
- selgitab analoog-digitaalmuunduri põhimõtteid, veallikaid ja efektiivse resolutsiooni arvutamist;
- projekteerib operatsioonivõimendiga signaali konditsioneerimise ahela (nihe, skaleerimine) ja põhjendab disainivalikuid;
- rakendab Fourier analüüsi (FFT) müra allikate tuvastamiseks ja filtreerimise tõhususe hindamiseks;
- rakendab tuletise (dP/dt) põhist reaalajalise reageerimise loogikat katkestuste (IRQ) kaudu;
- diagnoosib I2C sideliini müraprobleeme ja rakendab filtreerimislahendusi;
- disainib trükkplaadi (PCB) mis koondab kogu mõõtesüsteemi;
- kogub ja puhastab mõõteandmeid automatiseeritult (Python + MG400 API);
- treenib ja valideerib masinõppe mudelit (scikit-learn) süstla täitetaseme hindamiseks rõhukõvera tunnustest.

### Sisu lühikirjeldus
Kursus ehitab MG400 doseerimissüsteemile rõhumõõtmise süsteemi samm-sammult samale maketeerimisplaadile. Laborid 1–3 lisavad igaüks kihi: toorsignaal → op-amp filtreerimine → dP/dt tuletis ja I2C kalibreerimine. Igas laboris kasutatakse Fourier analüüsi näitamaks mida iga täiustus konkreetselt parandab. Ülesanded 4–5 kasutavad MG400 robotit automaatseks andmekogumiseks (500+ mõõtmist) ja masinõppe mudeli treenimiseks mis hindab süstla täitetaset rõhukõvera kujust. Labor 3 sisaldab ka PCB disaini ja tellimist.

### Hindamine
Iseseisvate tööde loetelu ja juhised nende tegemiseks:

Hindamisstruktuur: 5 projekti × 20 punkti = max 100 punkti. Integratsiooniprojekt max 70 punkti (ideaalselt vormistatud = C hinne). Kokku võimalik 170 punkti, hinne arvutatakse parimast 100-st. Tudeng valib ise millised projektid teha — integratsiooniprojekti saab esitada iseseisvalt ja ülejäänud tööd lisada punktide parandamiseks.

Iga projekti neli hindamiskategooriat:
- Tööfailid (5p): kood, skeemid, disainifailid — kõik git repos
- Analüüs (5p): Jupyter notebook, Fourier analüüs, mõõtmistulemused
- Prototüüp (5p): töötav füüsiline teostus
- Dokumentatsioon (5p): spetsifikatsioonid, põhjendused, juhendid

#### Konsultatsioon 1: Elektroonika ja jootmise alused (vabatahtlik)
Tudengitele kes pole varem elektroonikaga kokku puutunud. Toimub enne esimest ülesannet.

Jootekolbi käsitsemine:
- Ohutusnõuded, kolbi hooldus, tina ja räbustiga töötamine
- Esimene jootmine: harjutusplaat TH (through-hole) komponentidega — takistid, kondensaatorid, LED-id, pistikuribad
- SMD jootmine: 0805 ja 1206 pasiivkomponendid (takistid, kondensaatorid) harjutusplaadile
- Kontroll: visuaalne inspektsioon (külm jootekoht, sild, liiga vähe/palju tina)

Komponentide tundmine:
- Pasiivkomponendid: takisti (R), kondensaator (C), induktor (L) — mis nad teevad, kuidas välja näevad, kuidas lugeda väärtust (värvikoodid, markeering)
- Aktiivkomponendid: LED (polaarsus!), transistor, op-amp IC, mikrokontroller — mille poolest erinevad pasiividest
- Maketeerimisplaat: kuidas read on sisemiselt ühendatud, toiterööpad, kuidas vältida lühist
- Multimeeter: pinge, takistuse ja katkestuse mõõtmine

Tulemus: tudeng oskab joota TH ja SMD komponente, tunneb ära pasiiv- ja aktiivkomponendid, ning saab maketeerimisplaadil hakkama.

#### Ülesanne 1: Toorsignaal ja esimene Fourier
Ehitada rõhumõõtmise ahel MPX5700AP anduriga ja ESP32 mikrokontrolleriga. Ühendada andur otse ADC-sse, koguda 30 mõõtmist kolmes rõhukategoorias (MG400 kompressor), teisendada ADC väärtused Pascaliteks. Simuleerida ahelat Falstad-is. Jupyter Lab-is visualiseerida signaal ajateljel ja rakendada Fourier analüüsi (scipy.fft) müra allikate tuvastamiseks sagedusruumis.

#### Ülesanne 2: Op-amp ja filtreerimine — Fourier võrdlus
Ehitada samale maketeerimisplaadile operatsioonivõimendi (LM358N) ahel mis nihutab ja skaleerib MPX5700AP signaali ESP32 ADC vahemikku. Mõõta nelja konfiguratsiooni (otse ADC, pingejagur, op-amp, op-amp + digitaalfilter) samade mõõtmistega (4 × 30 = 120 mõõtmist). Jupyter Lab-is võrrelda kõiki nelja konfiguratsiooni kõrvuti: ajatelg, Fourier spektrid, SNR arvutus. Tuvastada konkreetsed müra allikad (mootorite PWM, toiteallikate switching, maandussilmused) ja tõestada numbritega miks iga filtreerimissamm on vajalik.

#### Ülesanne 3: dP/dt tuletis, IRQ lävend, I2C kalibreerimine ja PCB disain
Lisada rõhukõvera tuletise (dP/dt) põhine ohutusmehanism: komparaator (op-amp Schmitt-triggerina) + ESP32 katkestus. Fourier analüüsiga näidata miks tuletis võimendab müra (× 2πf) ja miks tuleb filtreerida enne tuletise võtmist. Lisada VL53L0X kaugusandur (I2C) otsiku kalibreerimiseks: diagnoosida I2C liini müraprobleem pikema kaabliga, lahendada RC filtriga. Disainida trükkplaat kogu süsteemi jaoks (rõhuandur + op-amp + komparaator + VL53L0X + ESP32 pistikuriba). Labori kaitsmine sisaldab PCB disaini ülevaatust — tellimine kohe pärast kaitsmist. Rõhk süsteemis on ~2 bar.

#### Ülesanne 4: Andmete kogumine MG400-ga
Kirjutada Python skript mis automatiseerib andmekogumise: MG400-le doseerimiskäsk → ESP32 andurite andmed UART kaudu → CSV logimine. Koguda vähemalt 500 mõõtmist (5 kiirust × 5 rõhku × 20 kordust). Iga mõõtmine salvestab terve rõhukõvera aegrea. Jupyter Lab-is analüüsida rõhukõvera kuju vs. täitetase — seos selgub mõõtmisest, mitte ette antud teooriast. Kui PCB on kohale jõudnud — joota ja testi.

#### Ülesanne 5: Masinõppe mudel
Treenida mudel ülesande 4 andmestikul küsimusele: kui palju materjali on süstlas järgi? Sisendtunnused rõhukõverast (ajatunnused: reageerimisaeg, dP/dt max, platoo väärtus, kõvera pindala; Fourier tunnused: dominantsagedus, spektri energia). Võrrelda lineaarset regressiooni, otsustuspuud ja random foresti. Hinnata kas Fourier tunnused parandavad mudelit, kas op-amp andmetega treenitud mudel on parem kui toorandmetega, ja kas mudel töötab teise meeskonna seadmel. Praktiline tulemus: lävend "süstlas on alla 2ml, vaheta!" — mis täpsusega mudel seda ütleb.

#### Lisaülesanne: Automaatne täitetaseme jälgimine
Suletud ahel: MG400 doseerib → rõhuandur mõõdab → mudel hindab järelejäänud mahtu → veebiliides näitab hinnangut → kui alla lävendi → hoiatus operaatorile. IRQ tagab ohutuse (ummistus → peatumine), ML tagab info (millal vahetada süstalt).

### Kontakttundide ajakava
- **[~12.09.26]** Konsultatsioon 1 (vabatahtlik): elektroonika ja jootmise alused — jootekolb, TH ja SMD jootmine, pasiiv- ja aktiivkomponendid, maketeerimisplaat, multimeeter
- **[~12.09.26]** ESP32 esimene programm, ADC baas, Jupyter Lab sissejuhatus, esimene FFT
- **[~03.10.26]** Ülesande 1 kaitsmine
- **[~03.10.26]** Op-amp teooria, Falstad simulatsioon, neljakordne võrdlus
- **[~15.10.26]** Konsultatsioon 2: op-amp praktiline abi — nihke ja skaleerimise ahel, tüüpilised vead, ostsilloskoobi kasutamine
- **[~24.10.26]** Ülesande 2 kaitsmine
- **[~24.10.26]** Tuletis, komparaator, IRQ + I2C müradiagnostika
- **[~05.11.26]** Konsultatsioon 3: resolutsiooni määramine — ADC bitid × op-amp võimendus × müratase → efektiivne resolutsioon. PCB skeemi eelkontroll.
- **[~14.11.26]** Ülesande 3 kaitsmine (sisaldab PCB disaini ülevaatust → tellimine kohe pärast)
- **[~14.11.26]** MG400 API ja automaatne andmekogumine Pythonis
- **[~05.12.26]** Ülesande 4 kaitsmine
- **[~05.12.26]** Masinõppe sissejuhatus: scikit-learn, aegrea tunnused, rõhukõvera analüüs
- **[~16.01.27]** Ülesande 5 kaitsmine
- **[TBD]** Integratsiooniprojekti kaitsmine

### Lõpphindamisele pääsemise tingimused
Õppija on positiivsele tulemusele kaitsnud vähemalt ühe ülesande.

### Minimaalne punktide kogusumma lõpphindamisele pääsemiseks
51

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
| F | Õppija on kogunud vähem kui 51 punkti |
| mi | Õppija ei ole ülesandeid esitanud ega lõpphindamisel osalenud |

### Võlgnevuste likvideerimine
Kokkuleppel vastutava õppejõuga

## Üldinfo
### Eesmärgid
Anda tudengitele praktilised põhioskused analoog- ja digitaalelektroonika mõõteahelatega, mikrokontrollerite programmeerimise, trükkplaatide disaini ja andmeanalüüsiga. Kursus valmistab ette edasise andmehõive aine jaoks, kus tegeletakse keerukamate mõõtesüsteemide, masinõppe ja optimeerimisega.

### Õpiväljundid
Õppeaine läbinud õppija:
oskab ühendada analoogandurit mikrokontrolleriga ja teostada ADC lugemeid. Tunneb pingejaguri ja operatsioonivõimendi põhiskeeme ning oskab neid simuleerida. Suudab disainida lihtsa ühekihilise trükkplaadi Fusion 360 EDA-s ja tellida selle tootmiseks. Oskab analüüsida mõõteandmeid Jupyter Lab'is — arvutada lahutust, müra ja mõõteviga. Tunneb ESP32 mikrokontrolleri programmeerimist Arduino keskkonnas. Suudab integreerida mõõtesüsteemi tööstusrobotiga signaalide ja HTTP side kaudu.

### Sisu lühikirjeldus
Kursus annab praktilise sissejuhatuse andmehõive alustesse. Tudengid ehitavad rõhumõõturi prototüübi analooganduriga, õpivad ADC tööpõhimõtteid ja signaali eeltöötlust nii tarkvaraliselt kui riistvaraliselt. Teine pool keskendub operatsioonivõimendi skeemidele, trükkplaadi disainile ja robotiga integreerimisele. Kursuse läbiv joon on mõõteandmete analüüs Jupyter Lab'is — iga labor lõpeb kvantitatiivse analüüsiga mis näitab süsteemi tegelikku jõudlust.

### Hindamine
Iseseisvate tööde loetelu ja juhised nende tegemiseks:

#### Labor 1: Digitaalne rõhumõõtmine
Ehita rõhumõõturi prototüüp MPX5700AP rõhuanduri ja M5 Atom (ESP32) mikrokontrolleriga. Kuva rõhku reaalajas (~4Hz) veebilehel. Simuleeri ahelat TinkerCAD-is ja Falstad-is, testi ostsilloskoobiga. Kogu 30 mõõtmist kolmes kategoorias (1ml, 5ml, 9ml õhku süstlas — 10 igast). Teisenda ADC väärtused Pascaliteks MPX5700AP valemi järgi. Testi lineaarsust süstla mahu ja rõhu vahel. Määra Jupyter Lab'iga süsteemi lahutus, müratase ja viga kogu mõõtevahemikus.

#### Labor 2: Analoogsignaali eeltöötlus ja süsteemi integreerimine
Testi labori 1 pingejaguri lahendust ja ehita operatsioonivõimendi (LM358N) alternatiiv maketeerimisplaadil. Kalibreeri nihe (nihuta signaali -0,2V) ja skaleerimine (ülemine ots 3,2V-ni). Mõõda täpsust ostsilloskoobiga. Kogu samad 30 mõõtmist opampi lahendusega. Disaini trükkplaat Fusion 360 EDA-s: skeem, komponentide paigutus, rajad, DRC kontroll, Gerber failide genereerimine JLCPCB tellimiseks. Integreeri robotiga: GPIO aktiveerimine, HTTP side ESP32 ja UR5 vahel, juhtimisloogika (rõhk → roboti pea liigutamine).

#### Lisaülesanne: Opampi konsultatsioon ja edasijõudnud skeemid
Süvendatud töö operatsioonivõimendi konfiguratsioonidega: inverteeriv ja mitteinverteeriv võimendus, võimendus alla ühe, komparaator, ja ahelatega inversioonid. Dokumenteeri iga konfiguratsiooni simulatsioon Falstad-is ja valideeri maketeerimisplaadil.

### Lõpphindamisele pääsemise tingimused
Õppija on positiivsele tulemusele kaitsnud vähemalt ühe labori.

### Minimaalne punktide kogusumma lõpphindamisele pääsemiseks
21

### Lõpphindamise skaala
Eristav (A, B, C, D, E, F, mi)

### Hindamistulemuste teatamise aeg
Info puudub

### Lõpphinde kujunemine
Info puudub

|   |   |
|---|---|
| A | 37 punkti |
| B | 33 punkti |
| C | 29 punkti |
| D | 25 punkti |
| E | 21 punkti |
| F | vähem kui 21 punkti |
| mi | Õppija ei ole ülesandeid esitanud ega lõpphindamisel osalenud |

### Võlgnevuste likvideerimine
Kokkuleppel vastutava õppejõuga

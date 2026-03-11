## Üldinfo
### Eesmärgid
Kursuse eesmärk on anda tudengitele ülevaade kaasaegsetest andmehõive põhimõtetest, meetoditest, seadmetest ja tarkvarast. See tutvustab levinud andmehõive ja signaalitöötluse väljakutseid teaduses ja tööstuses, arendades samal ajal praktilisi oskusi andmehõiveprobleemide lahendamiseks teaduslikes, haridusalastes ja tööstuslikes kontekstides.

### Õpiväljundid
Õppeaine läbinud õppija:
Pärast kursuse läbimist suudavad tudengid eristada andmehõivesüsteemide erinevaid komponente, mõista riistvarapõhiseid signaalitöötlusahelaid (riistvaraline filtreerimine) ning selgitada analoog-digitaalmuundurite põhimõtteid ja peamisi veaallikaid. Nad disainivad ja rakendavad kohandatud lahendusi praktilistele andmehõiveprobleemidele, valivad sobivad andmehõive metodoloogiad ja riistvara ning eristavad erinevaid andmeliidesi. Tudengid rakendavad levinud järeltöötlustehnikaid mõõdetud andmete analüüsimiseks, töötlevad, iseloomustavad ja visualiseerivad andmeid, kasutades nii aja- kui sagedusesitusi, ning analüüsivad, dokumenteerivad ja esitlevad mõõteandmeid vastavalt akadeemilise kirjutamise standarditele.

### Sisu lühikirjeldus
Kursus annab ülevaate kaasaegsetest andmehõive kontseptsioonidest ja seadmetest. Tudengid õpivad erinevaid lähenemisviise andmehõiveprobleemide lahendamiseks ja sobivate riistvaravalikute tegemiseks. Lisaks signaalitöötlusahelate ja analoog-digitaalmuunduse põhiteadmistele käsitleb kursus erinevaid järeltöötlusmeetodeid andmete filtreerimiseks, andmete kuvamiseks aja- ja sageduspiirkondades ning mõõdetud süsteemiparameetrite optimeerimiseks. Kursuse olulise osa moodustavad praktilised sessioonid, kus tudengid lahendavad erinevaid näidisprobleeme, kasutades ühepunktilisi, fikseeritud koguse ja signaali lugemise tehnikaid. Praktiliste tegevuste kaudu omandavad tudengid teadmisi sünkroniseeritud mõõtmiste teostamisest erinevate seadmete vahel ning töötavad välja lahendusi nii madal- kui kõrgsageduslike signaalide mõõtmiseks.

### Hindamine
Iseseisvate tööde loetelu ja juhised nende tegemiseks:

#### Ülesanne 1: Põhiline rõhumõõtmissüsteem
Projekteerida ja rakendada rõhumõõtmissüsteem, kasutades MPX5010DP diferentsiaalrõhuandurit koos M5 Atom mikrokontrolleriga. Tudengid ehitavad andurile lihtsa pingejaguri, rakendavad ADC lugemeid ja koguvad rõhuandmeid. Jupyter Lab'i abil analüüsitakse anduri reageerimisnäitajaid, arvutatakse näitude statistilised parameetrid ja määratakse mõõtesüsteemi tegelik lahutusvõime.

#### Ülesanne 2: Täppis-madalrõhu tuvastusskeem
Arendada kaheastmeline operatsioonivõimenditega skeem, mis parandab MPX5010DP anduri lahutusvõimet kriitilises 0-2 kPa vahemikus. Rakendada komparaatorskeem lävendi tuvastamiseks ja põhiline temperatuurikompensatsioon. Disainida Fusion 360-s trükkplaat, mis majutab signaali töötlemise skeemi. Kasutada Jupyter Lab'i, et võrrelda anduri töötlemata väljundit töödeldud signaaliga, kvantifitseerides lahutusvõime ja mürasummutuse paranemist statistilise analüüsi kaudu.

#### Ülesanne 3: Mürakindel mõõtesüsteem
Projekteerida ja rakendada riistvaralised filtrid, et kõrvaldada elektriline müra rõhuanduri näitudes, mis tekivad Dobot mootorite läheduses töötamisel. Tudengid koguvad müraprofiile erinevates töötingimustes, rakendavad sobivaid filtritopoloogiaid ning kasutavad Jupyter Lab'i sagedusanalüüsi läbiviimiseks, mis näitab filtrite tõhusust. Ülesanne peaks sisaldama signaali FFT analüüsi enne ja pärast filtreerimist.

#### Ülesanne 4: Mitme anduri andmete sünkroniseerimine
Luua süsteem, mis sünkroniseerib rõhumõõtmised Doboti positsiooniteabega. Tudengid rakendavad andmehõivet mitmest andurist (rõhuandurid, positsiooniandurid), käsitlevad ajastuse sünkroniseerimist ning kasutavad Jupyter Lab'i, et analüüsida seoseid roboti positsiooni ja rõhuvariatsioonide vahel. Analüüs peaks tuvastama mustreid, mis võivad ennustada doseerimise ebaühtlusi roboti liikumiskarakteristikute põhjal.

#### Ülesanne 5: Ennustav analüüsimudel
Koguda andmestik rõhunäitudest, mis on seotud edukate ja ebaõnnestunud doseerimisoperatsioonidega. Kasutada Jupyter Lab'i, et luua lihtne masinõppe mudel (logistiline regressioon või otsustuspuu), mis suudab ennustada doseerimise kvaliteeti rõhumustrite põhjal. Mudel peaks tuvastama õrnad rõhukõikumised, mis näitavad probleeme nagu õhumullid, ummistused või materjali ebaühtlused enne, kui need muutuvad nähtavateks tõrgeteks. Mudel tuleb treenida ajaloolistel andmetel ja valideerida uute mõõtmistega, kasutades selgeid ennustustäpsuse mõõdikuid.

#### Lisaülesanne: Suletud ringi optimeerimissüsteem
Projekteerida eksperiment, mis süstemaatiliselt varieerib doseerimisparameetreid (rõhk, ajastus, düüsi kõrgus) ja mõõdab tulemusena saadavat kvaliteeti. Kasutada Jupyter Lab'i, et rakendada lihtne optimeerimisalgoritm, mis suudab tuvastada ideaalsed parameetrid ühtseks doseerimiseks. Luua terviklik analüüsivoog, mida saaks kasutada doseerimisseadme kiireks konfigureerimiseks erinevate vaikude viskoossuste jaoks.

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
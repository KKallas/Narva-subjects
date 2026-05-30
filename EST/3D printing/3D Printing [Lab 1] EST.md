## 3D printimine ja CAD: Labor 1

### Eesmärk

**Eesmärk** Valmistada esimene makett süstla hoidikust robotile Dobot MG400. Tööjoonised ja disaini teeme Fusion 360-s ning prindime esimesed versioonid.

Fusion 360-s tuleb sketšid üles ehitada fikseeritud kinnitustega nii, et saaks kergesti muuta süstla:

* Läbimõõtu \- katsetame erinevaid süstlaid: 5, 10, 20 ml  
* Asukohta \- leiame süstlale sellise koha, mis säilitab maksimaalse tööulatuse  
* Suunda \- kas süstal suunata otse alla, 45 kraadi nurga all või horisontaalselt koos nõela otsikuga

**Maketi eesmärk** Leida süstlale optimaalne asend robotil, et kasutada võimalikult laial spektril (säilitades võimalikult suure tööala). Kuna erinevaid liimimismaterjale müüakse valmis süstlates, peab süstla suurust olema lihtne vahetada.

**Nõuded** Süstal peab kinnituma roboti otsiku külge. Süstla tööriist peab säilitama 80% tööalast lauatasapinnal. Süstlale peab saama kinnitada pneumaatilise kolvi automaatseks doseerimiseks.

*See on elav dokument, uuenda eesmärke kui need töö käigus muutuvad, uued teadmised muudavad vanad eesmärgid pahatihti mõttetuks. Eesmärk on et hoida meeskonda kogu aeg sihil, et ei eksitaks detailide metsa ära ja põhi probleem jääb lahendamata*

### Taustainfo

* **Fusion 360 mudeldamine FDM printimise jaoks**  
  [https://www.youtube.com/watch?v=5hComh1hFzY](https://www.youtube.com/watch?v=5hComh1hFzY)  
  Või print in place   
  [https://www.youtube.com/watch?v=vHHMwpaIrco](https://www.youtube.com/watch?v=vHHMwpaIrco)  
* **3D mudelite harjutused**  
  Too Tall Toby  
  [https://www.tootalltoby.com/](https://www.tootalltoby.com/)  
* **Prusa**  
  Printer: [https://www.prusa3d.com/product/prusa-core-one/](https://www.prusa3d.com/product/prusa-core-one/)  
  Slicer: [https://www.prusa3d.com/page/prusaslicer\_424/](https://www.prusa3d.com/page/prusaslicer_424/)  
* **MG400 mount**  
  Fusion360: [https://a360.co/4nruicX](https://a360.co/4nruicX)

*Lisa siia omapoolseid allikaid ja kasuliku informatsiooni mis aitaks sul projektis aru saada aastaid hiljem kui selle uuesti lahti teed.*

### Vahendid

1. Fusion 360  
2. Pursa Core 1  
3. Süstal 10ml N1

*Kui plaan muutub siis muuda ka vahendeid, või tee [draw.io](http://draw.io)’s joonis kuidas asjad funktsionaalselt seostuvad.*

### Projekti ülesehitus

- [ ] Süstla mudel  
- [ ] MG400 tööriista otsiku kinnitus  
- [ ] Süstla kinnitus  
- [ ] Tegid ikka 3 versiooni  
- [ ] Analüüs

*Kaugel oled? Millal valmis saad? Kuidas kiiremini saaks? \- need tavalised küsimused*

### Testimine

#### Testinäide 1: Fusion 360 ristumise test

Enne kui prindid, kontrolli üle, et virtuaalsed objektid arvutis oleksid ilusti üksteise suhtes kindlalt seostatud ning kontrollitud, et objektid üksteist ei läbistaks.

Näide: [https://www.youtube.com/watch?v=wy6chd2hP24](https://www.youtube.com/watch?v=wy6chd2hP24)

#### Testinäide 2: Põhimõõdud

Pärast printimist on vaja vähemalt ühte mõõtu igas teljes ehk kolme mõõtu, mida oleks lihtne nihikuga kontrollida, kas valminud objekt on mõõtkavas ja pole venitatud. Kui joonis on valmis, on vaja kaasa panna mõõdutabel (see on sama vajalik kui tarkvara automaattestimine).

*Need on kaks esimest näidet, lisa siia järgmised testid et kui hakkad sellele projektile uusi osasi lisama siis saad kontrollida et põhi osa pole katki läinud automaatselt \- kui seda tööd teha käsitsis siis see on kuhu läheb enamus projekti ressursi\!*

### Arenduslogi

### Tulemused

Fusioni projekt:  
Arenduslogi:  
Versioon 2 lähteülesanne: *kirjuta lühike analüüs, mida selles versioonis õpiti ja mida järgmises versioonis teistmoodi teeksid (mis töötas, mis ei töötanud, millised eesmärgid/nõuded muutuvad)*

### Tagasiside

### Õppejõu märkused

* Praktikum on 3h (labor 1)
* Seletan õppekava konteksti: Nutilahenduste, Andmehõive ja 3D printimise ainetes teeme **tehnoloogia prototüüpe** (igaüks keskendub ühele tehnoloogiale eraldi). Lõpliku, terviklahenduse prototüübi paneme kokku alles järgmisel poolaastal Prototüüpimise aines, kus need tehnoloogiad kokku tulevad.
* Seletan, kuidas moodustame gruppid (4 gruppi, max 5 inimest, rollid võivad vahetuda iga labori juures)
* Laborid on poolikult ette täidetud töölehed, mis tuleb ise lõpuni teha, suuliselt kaitsta ja punkte koguda, lisa punkt saab teistelt meeskondadelt küsimuste küsimisega kaitsmise ajal. Ette antud dokumendis võib olla loogika kui ka fakti vigu iga leitud vea eest boonuspunktid (5punkti/iskiluselt kes leiab). 
* Seletan, kuidas käib hindamine (kui meeskond on valmis, valib välja lähima kaitsmise aja ja saadab oma materjalid; kaitsmised on online'is ette kokku lepitud kuupäevadel vähemalt 5 korda)
* Mis on additiivne tootmine, kus ja kuidas seda täna kasutatakse, mis müüb ning mis päriselt tööstuses täna töötab
* Seletan, kuidas käib piirangute põhine disain, kus tähtis ei ole esteetika vaid objekti funktsioon ja kõik mittefunktsionaalsed osad võib lahendada kuidas kunstnik soovib
* Seletan, miks kasutada **tavalist PLA-d** — pahatihti annab see kõige parema ja ka tugevama tulemuse, sest kihid liimuvad PLA-l kõige paremini. Eksootilised filamendid (komposiidid jms) on keerulisemad printida, aga tegelikult ei anna palju paremaid tulemusi. Kui on vaja lisatugevust, on enamasti mõistlikum panna **prindi sisse armatuur** (vedru, polt vms metallosa) kui üritada eksootilisema materjaliga sama tulemust saavutada.
* Boonusülesanne lisapunkti eest: silinder (raadius 20mm / kõrgus 30mm) kuubi (30mm) sees, print-in-place, nii et pärast printimist tuleks lahti
* Nüüd vaatame koos peale dispenser-tööriista näidise (UR5 + laenatud dispenser) — see on **ainult näidis**, et illustreerida, kuidas tööstuses sarnane lahendus välja näeb. Meie teeme sarnase, aga väiksema lahenduse Dobot MG400-le. Selle peal teeme ka taustauuringu peale.
* Praktikumi käigus peaks kõik meeskonnad saama valmis ühe kinnituse disaini, mida siis hakkame joonise ja sideme kaupa üle vaatama, kuidas oleks mõistlik defineerida...
* Esimene katse läheb ka printi, lasen tudengitel ise otsida info, aga kellel abi vaja, annan selle kätte ([https://www.youtube.com/watch?v=U1qRpVyG-P8](https://www.youtube.com/watch?v=U1qRpVyG-P8))
* Kuidas vormistada töö: eksport Fusion arhiivi ja mail õppejõule 72h enne kaitsmist
* Arenduslogi ja lähteülesanne võivad olla kas git või attachment (md, docx, gdoc). **Git'i luban, aga ei nõua** — kes oskab/tahab, võib seda kasutada; kes veel ei oska, võib teha attachmentina. Ei taha, et tööriista valik saaks õppimise takistuseks.

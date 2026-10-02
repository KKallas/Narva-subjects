## 3D printimine ja CAD: Labor 2 — Sisend, töökoht, väljund

**Maht:** 30 tundi | **Hindamine:** 20 punkti | **Meeskonnatöö:** 3-liikmelised meeskonnad | **Välja antud:** 06.10.26 | **Tellimise kuupäev:** 16.10.26 | **Esimene kaitsmine:** 27.10.26, veebis

### Mida teete

Töölaud on olemas ja selle disain ka: Fusioni fail [MG 400 rakis.f3z](MG%20400%20rakis.f3z) ja kirjeldus [MG 400 rakis.md](MG%20400%20rakis.md), mida on hea anda oma AI agendile, et ta teaks, mis Fusionis juba tehtud on. Laud on PLA-st prinditud. Robot seisab oma aluses ja tema ees on **Gridfinity ruudustik**, 7 × 10 ruutu, samm 42 mm. Kõik, mis laua peal elab, on Gridfinity hoidik, mis kukub ruudustikku. Ruudu nimi on täht ja märgiga number, näiteks `B-2`: täht on kaugus robotist, number on külg keskjoonest.

Aasta lõpuks paneb MG400 kokku sildi: AtomS3, mille peale on liimitud polükarbonaatklaas ja mille all on akumoodul. See on väike tootmisliin, ja tootmisliinil on alati sama kuju: **sisend** (mitu objekti, igaühte mitu ühikut), **töökohad** (nii palju, kui on samme, mida üks robot korraga teeb) ja **väljund** (tavaliselt kaks: põhiväljund ja praak). See labor teeb hoidikud kõigi kolme jaoks. Hoidik tuleb ruudustikust välja ja läheb tagasi, ja detail on ikka samas kohas, ilma et robotile midagi uuesti õpetataks.

Laboris 1 mõõdetud printeri lõtk läheb käiku kaks korda: hoidiku jalg ruudustikus ja detail pesas.

Viis osa:

**1. Protsess ja paigutus** — paberil, enne Fusioni. Mis tuleb sisse (AtomS3, klaas, akumoodul), mitu töökohta, mitu väljundit ja millises ruudus igaüks on. Töökoht käib sinna, kus robot on kõige täpsem. Tulemus: `docs/layout.md` sammude, ruutude ja joonisega.

**2. Hoidikud** — esimene print on 1 × 1 kalibreerimishoidik: näitab, kas Gridfinity jalg istub, ja sellega kalibreeritakse robot. Siis sisendhoidikud kolmele detailile (igas vähemalt neli ühikut), töökoha hoidik ja väljundhoidikud. Igal pesal sissejuhtiv kaldserv, inimene saab ligi, peale midagi ei ulatu. Tulemus: hoidikud ruudustikus, iga pesa mõõdetud nihikuga, iga koht kirjas kujul ruut + nihe.

**3. Test** — ainult klaasiga. Neli klaasi sisendist töökohale Atomi mannekeeni peale ja sealt valmis asjade väljundisse. Liimi ei ole, edasi tõstetakse ainult klaas. Siis kõik hoidikud ruudustikust välja ja tagasi, sama jooks uuesti, punkte ei muudeta. Viis ringi. Tulemus: `docs/refit_test.csv`, mitu kahekümnest läks läbi ja kui palju lõtku järgmised laborid peavad taluma.

**4. Kaamera tööriistahoidikul** — Seeed Studio XIAO ESP32S3 Sense kaameramoodul käib olemasoleva iminapa tööriistahoidiku külge. Näeb töökohta, ei jää napale ette, tuleb samasse kohta tagasi. Ja päris küsimus: kust ta toite saab, kui ta on liikuva käe otsas. Tulemus: kinnitus, valitud ja läbi proovitud toide, tööriista kaal enne ja pärast.

**5. Kaamera laua kohal** — tavaline USB UHD veebikaamera robotist kõrgemal, näeb kogu lauda. Post on jäik, prinditud tükkidena, ja käsi ei ulatu temani. Tulemus: pilt, kus kogu ruudustik ja robot on näha, ja number, kui palju pilt roboti liikumise ajal väriseb.

### Kuidas töö käib

Repo ja töökord on Laborist 1 olemas ja samad. Tervet töölehte üle kopeerida ei ole vaja — too oma repo juurde see, mida vaja, ja täida `README.md` oma numbrite ja otsustega. Iga print on uus versioon; vana jääb alles. Ei tulnud esimesel korral välja, tule homme tagasi ja proovi uuesti.

Esimesel päeval uusi osi ei ole — ehita sellest, mis riiulil on. Materjal on PLA.

### Komponendid selle labori jaoks

Tellimus läheb välja 16.10.26 ja jõuab kohale enne kaitsmist. Valmis nimekirja ei ole: meeskond paneb tellimuse ise kokku faili `docs/bom.md`, iga rea juures üks lause, milline osa seda küsib.

### Kaitsmiseks on vaja

**Ainult git repositooriumi link, tag `3d-print-lab2`.** Kaustas `3d-print/lab2/` peab olema:
- lähtefailid, STL ja `.3mf` iga prindi kohta
- `docs/`: `layout.md`, `refit_test.csv`, `bom.md`, fotod
- Täidetud `README.md` koos arenduspäevikuga
- `AGENTS.md` uuendatud

Kaitsmine on lihtne suuline 15 minuti jutuajamine. Võtad hoidikud ruudustikust välja ja paned tagasi, ja robot viib neli klaasi sisendist töökohale ja töökohalt väljundisse, ilma et sa punkte uuesti õpetaksid. Tööriista kaamera on toite all ja veebikaamera näeb kogu lauda. Avad oma arenduspäeviku. Umbes viis küsimust selle kohta, kuidas sa selle tegid. Kaitsta saab nii mitu korda, kui vaja.

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — parameetritega hoidikud Gridfinity jalaga ja kahe kaamera kinnitused, STL ja 3MF iga prindi kohta | 5 p |
| Analüüs — protsess ja paigutus, detailide mõõdud, kasutatud lõtk ja kust see tuli, kalibreerimise nihe, testi tabel, kaamera toite valik | 5 p |
| Prototüüp — neli klaasi liiguvad sisendist töökohale ja töökohalt väljundisse, hoidikud tulevad samasse kohta tagasi, praagil on koht, kaamera istub tööriistahoidikul ja saab toite, veebikaamera näeb kogu lauda | 5 p |
| Dokumentatsioon — README, arenduspäevik, `layout.md`, `refit_test.csv`, `bom.md`, AGENTS.md | 5 p |
| **Kokku** | **20 p** |

### Täielik tööleht

📎 [Link täielikule töölehele](https://github.com/KKallas/Narva-subjects/blob/main/EST/2026-27/3D%20printing/3D%20Printing%20%5BLab%202%5D%20EST.md)

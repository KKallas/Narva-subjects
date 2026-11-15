## Andmehõive: Labor 4 — Masin, mis mõõdab ise

**Maht:** 30 tundi | **Hindamine:** 20 punkti | **Meeskonnatöö:** 3-liikmelised meeskonnad | **Välja antud:** 18.11.26 | **Tellimise kuupäev:** 27.11.26 | **Esimene kaitsmine:** 10.12.26, veebis

### Mida teete

Laboris 3 tegi robot tilga, kaamera pildistas, ja sina lugesid pildid arvutis läbi. Sealt tuli retsept, aga retsept on üks punkt. Liin, mis teeb sadu silte, ei saa iga tilka inimesega üle vaadata, ja süstal ei ole sajandal tilgal sama, mis esimesel: vaiku jääb vähemaks, ruum läheb soojemaks, otsik määrdub.

Selles laboris teeb masin kolm asja ise. **Mõõdab**: programm loeb tilga pildilt iga tsükli järel, ja keegi ei vaata üle. **Ennustab ja parandab**: andmetest sobitatud **mudel** pakub impulsi ette, ja **tagasiside** parandab järele, nii et tilk püsib sihis ka siis, kui süstal tühjeneb. **Kirjutab üles**: iga tsükkel jätab ühe kirje, ja igal kirjel on teada, kas see oli tavaline tilk, kinnine otsik või tühi süstal. Labor 5 õpib nende kirjete peal.

Ja relee läheb välja. Tema asemele tuleb **MOSFET**, ja samad numbrid mõõdetakse uuesti tema peal.

Kirje kuju on ühine Nutikate Lahenduste Labor 4 andmebaasiga. Lepi nendega kokku enne, kui esimene kirje kirjutatakse.

Viis osa:

**1. MOSFET** — IRLZ34N relee asemele: paisu takisti, allatõmbetakisti, ja kaitsediood jääb mähise peale. Samad mõõtmised, mis Laboris 3 relee peal: lülitamise aeg, põrge, lühim tilk. Ja üks asi, mida relee ei osanud: **PWM**, mis hoiab klapi pärast avanemist lahti väiksema vooluga. Mähise vool mõõdetakse dioodi silmuse sees, multimeetri või INA219-ga, ja voolu kuju näitab ostsilloskoobil 0,22 Ω takisti. Tulemus: skeem, MOSFET-i numbrid relee omade kõrval, ja mähise vool ja temperatuur täisvoolu ja PWM-iga.

**2. Tsükkel ja kirje** — üks tsükkel on tilk tilgaplaadile, pilt, mõõtmine ja klaas edasi. Viis klaasi käivad ringi, nii et laud jookseb sadu tsükleid ilma, et inimene neid tagasi tõstaks. Iga kirje juures on ka see, kuidas tema märge teada on: inimene vaatas, pilt ütles või kaal ütles. Tulemus: `docs/record.md` ja ühe tsükli aeg sekundites.

**3. Masin mõõdab** — kas programmi saab usaldada, ütleb kaks võrdlust: Labori 3 üle vaadatud pildid peavad andma samad numbrid, ja tilgaplaadi kaal peab olema programmi ruumalaga nõus. Kui pilt ei ole selline, nagu programm ootab, märgib ta kirje "ei mõõdetud", mitte ei paku numbrit. Tulemus: mõlemad erinevused protsentides ja kolm pilti, kus masin eksis, ja miks.

**4. Mudel ja tagasiside** — mudel ütleb tilga pindala impulsi, rõhu ja otsiku järgi. Vähemalt kaks kuju proovitud, viga mõõdetud kontrolli andmetel, mida mudel ei näinud, ja süstla täidetus proovitud tunnusena. Tagasiside muudab impulssi pärast iga mõõdetud tilka, ülempiiriga. Siis kolm moodi kõrvuti, sada tilka igaüks: ainult retsept, ainult tagasiside, mudel ja tagasiside. Tulemus: mudeli viga protsentides, valitud `k`, kolm graafikut ja tilkade arv sihini pärast süstla vahetust.

**5. Andmestik** — vähemalt 300 tsüklit, seaded juhuslikus järjekorras, ja kolm olukorda igaüks mitu korda: tavaline tilk, kinnine otsik, tühi süstal. Süstal kaalutakse iga 25 tsükli järel. Tulemus: `data/cycles.csv`, kõverad ja pildid, ja samad kirjed Nutikate Lahenduste andmebaasis.

### Kuidas töö käib

Repo ja töökord on Laborist 1 olemas ja samad. Tervet töölehte üle kopeerida ei ole vaja — too oma repo juurde see, mida vaja, ja täida `README.md` oma numbrite ja otsustega. Ei tulnud esimesel korral välja, tule homme tagasi ja proovi uuesti.

Esimesel päeval uusi osi ei ole — ehita sellest, mis riiulil on. MOSFET-i, INA219, 0,22 Ω takistid, vaiguga täidetud süstlad ja kaalu annab õppejõud. Laud, mis jookseb sadu tsükleid, ei jookse tühjas ruumis: inimene hädastopi juures on ruumis kogu aja. Valgustamine käib katte all, ja kõigil laua ääres on kaitseprillid 405 nm jaoks.

### Komponendid selle labori jaoks

Tellimus läheb välja 27.11.26 ja jõuab kohale enne kaitsmist. Valmis nimekirja ei ole: meeskond paneb tellimuse ise kokku faili `docs/bom.md`, iga rea juures üks lause, milline osa või number seda küsib. Tellimine käib ühisest tellimistabelist: [https://moodle.ut.ee/mod/url/view.php?id=1535601](https://moodle.ut.ee/mod/url/view.php?id=1535601).

### Kaitsmiseks on vaja

**Ainult git repositooriumi link, tag `data-acquisition-lab4`.** Kaustas `data-acquisition/lab4/` peab olema:
- `src/` püsivara, tsükli, mõõtmise, mudeli ja tagasiside koodiga
- `data/` kaustas `cycles.csv`, kõverad ja pildid, `notebooks/` võrdluste ja graafikutega
- `docs/`: skeem, ostsilloskoobi pildid, `record.md`, uuendatud `pump_control.md`, `bom.md`
- Täidetud `README.md` koos arenduspäevikuga
- `AGENTS.md` uuendatud

Kaitsmine on lihtne suuline 15 minuti jutuajamine. Laud teeb sinu silme all kümme tsüklit, ja kirjed ilmuvad andmebaasi. Näitad ostsilloskoobil MOSFET-i ja relee serva kõrvuti. Näitad kolme moodi graafikut kõrvuti ja ütled, kui suur on mudeli viga andmetel, mida ta ei näinud. Näitad ühte pilti, kus masin mõõtis valesti, ja mida ta sellega tegi. Avad oma arenduspäeviku. Umbes viis küsimust selle kohta, kuidas sa selle tegid. Kaitsta saab nii mitu korda, kui vaja.

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — Atomi püsivara MOSFET-i ja PWM-iga, tsükli programm, mõõtmise programm, mudel, tagasiside, `cycles.csv` koos kõverate ja piltidega | 5 p |
| Analüüs — MOSFET relee kõrval, masina mõõtmine Labori 3 piltide ja kaalu vastu, mudeli viga kontrolli andmetel, kolme moodi võrdlus, seadete jaotus ja märgete päritolu | 5 p |
| Prototüüp — klapp lülitub MOSFET-iga ja vooluta on süstal õhu peal, tsükkel jookseb inimeseta, tilk jääb mudeli ja tagasisidega sihti, vähemalt 300 kirjet andmebaasis | 5 p |
| Dokumentatsioon — README, arenduspäevik, `record.md`, skeem, `pump_control.md` uuendatud, `bom.md`, AGENTS.md | 5 p |
| **Kokku** | **20 p** |

### Täielik tööleht

📎 [Link täielikule töölehele](https://github.com/KKallas/Narva-subjects/blob/main/EST/2026-27/Data%20Acquisition/Data%20Acquisition%20%5BLab%204%5D%20EST.md)

## Nutikad Lahendused: Labor 3 — Ruuter ja VPN

**Maht:** 30 tundi | **Hindamine:** 20 punkti | **Meeskonnatöö:** 3-liikmelised meeskonnad | **Välja antud:** 28.10.26 | **Tellimise kuupäev:** 06.11.26 | **Esimene kaitsmine:** 19.11.26, veebis

### Mida teete

Laboris 2 käis kaugjuhtimine läbi postkontori: kasutaja jättis sõnumi, Atom tuli ja küsis, robot tegi töö ära. See on aeglane ja pime. Sõnum ootab järgmist postilkäiku, tellida saab ainult terve töö nimekirjast, ja kasutaja ei näe, mis laual toimub. Nüüd tuleb otsetee.

Teid on kaks ja nad jäävad lahku. **Postkontor** on avalik leht Laborist 2: sealt jäetakse sõnum, aga robotit otse ei liigutata ja kaamerapilti ei ole. **Otsetee** on VPN: kes on tunnelis, on justkui labori võrgus, näeb jaama lehte ja kaameraid ja liigutab robotit kohe. Kes ei ole tunnelis, ei näe midagi, isegi mitte seda, et seal midagi on.

Selleks on vaja kahte asja, mida seni ei olnud: oma **ruuter**, kus alamvõrk, aadresside jagamine, NAT, tulemüür ja ruutimistabel päriselt elavad, ja **tunnel** sinu ruuteri ja dropleti vahel. Ja kui robot on kaugelt kättesaadav, ei ole ta enam ruumis, kus sina oled. Ohutus muutub.

Viis osa:

**1. Ruuter** — aadressiplaan enne paberil, siis karbis: robot, jaam, Atom, kaameramoodul ja telefon ühes võrgus, igaüks iga kord sama aadressiga. Roboti aadress 192.168.1.6 on tal sees; kas ehitad võrgu selle ümber või muudad seda, on sinu otsus. Tulemüür ei lase väljast midagi sisse, ja ruuteri vaikimisi parool on vahetatud. Tulemus: aadressiplaan tabelina ja draw.io-s, ja Labori 1 ja 2 asjad töötavad uues võrgus edasi.

**2. Ruutimistabel ja NAT** — jaama ja ruuteri tabel lahti, iga rea kohta üks lause. Kolm teekonda — robotini, dropletini, internetti — ennustatakse enne ja mõõdetakse pärast. Siis dropleti logist: mis aadressi pealt Atomi kõne tuleb ja miks see ei ole Atomi aadress. Tulemus: `docs/routing.md`, ennustus ja tulemus kõrvuti.

**3. VPN** — WireGuard ruuteri ja dropleti vahel, telefon kolmanda osalisena. Privaatne võti ei lahku seadmest, kus ta tehti. Kõige tähtsam otsus on, millised aadressid tunnelisse lähevad: see on korraga marsruut ja luba. Kaks testi: WiFi väljas, tunnel sees — jaama leht avaneb ja robot liigub; tunnel väljas — midagi ei avane. Ruuter taaskäivitub ja tunnel tuleb ise tagasi. Tulemus: tunneli skeem, seadistus ilma võtmeteta, ja üks meelega katki tehtud marsruut ennustusega.

**4. Kaugelt** — latentsus labori võrgus ja läbi tunneli, kaamerad läbi tunneli mobiilse andmesidega. Ja kõige tähtsam: mis juhtub, kui ühendus katkeb keset liigutust. Otsusta, tee ära ja proovi kolm korda. Droplet logib tunnelit 48 tundi. Tulemus: latentsuse ja kaamerate numbrid Labori 2 omade kõrval, `data/tunnel_48h.csv`, kättesaadavus ja pikim katkestus.

**5. Atomi leht** — Andmehõive Labor 3 paneb Atomi külge solenoidklapi ja UV LED-i. Mõlemad saavad seaded ja testinupu samale Atomi lehele, ja üks asi ei ole läbiräägitav: LED kustub ise, aega loeb Atom, mitte brauser. Tulemus: `docs/atom_page.md` uuendatud.

### Kuidas töö käib

Repo ja töökord on Laborist 1 olemas ja samad. Tervet töölehte üle kopeerida ei ole vaja — too oma repo juurde see, mida vaja, ja täida `README.md` oma numbrite ja otsustega. Skeemid lähevad dokumenti pildina, pildi juurde link elavale failile. Ei tulnud esimesel korral välja, tule homme tagasi ja proovi uuesti.

Enne, kui tunnel esimest korda püsti läheb, täiendab meeskond Labori 2 ohutuskokkulepet: kes tohib tunneli kaudu otse juhtida, ja mida ta peab enne seda tegema. Kaugelt ei jooksutata midagi, mille ajal ruumis ei ole inimest, kes hädastoppi ulatub. UV LED-i kaugelt ei lülitata.

Esimesel päeval uusi osi ei ole — ehita sellest, mis riiulil on.

### Komponendid selle labori jaoks

Ruuteri annab õppejõud ja droplet on Laborist 2 olemas; neid tellimusse ei panda. Tellimus läheb välja 06.11.26 ja jõuab kohale enne kaitsmist. Valmis nimekirja ei ole: meeskond paneb tellimuse ise kokku faili `docs/bom.md`, iga rea juures üks lause, milline osa seda küsib.

### Kaitsmiseks on vaja

**Ainult git repositooriumi link, tag `smart-solutions-lab3`.** Kaustas `smart-solutions/lab3/` peab olema:
- `src/` jaama kood, `firmware/` Atomi PlatformIO projekt uuendatud lehega, `data/tunnel_48h.csv` ja latentsuse CSV-d
- `docs/`: aadressiplaan ja võrgu skeem draw.io-s, ruuteri seadistus, tunneli seadistus ilma võtmeteta, `routing.md`, ohutuskokkulepe, `atom_page.md`, ekraanipildid, `bom.md`
- Täidetud `README.md` koos arenduspäevikuga
- `AGENTS.md` uuendatud

Kaitsmine on lihtne suuline 15 minuti jutuajamine. Avad oma telefonist mobiilse andmesidega läbi tunneli jaama lehe, liigutad robotit ja näed seda mõlemas kaameras. Lülitad tunneli välja ja näitad, et leht enam ei avane ja mis robotiga juhtus. Näitad oma ruutimistabelit ja ütled ühe rea kohta, mida see teeb. Avad oma arenduspäeviku. Umbes viis küsimust selle kohta, kuidas sa selle tegid. Kaitsta saab nii mitu korda, kui vaja.

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — ruuteri seadistus, tunneli seadistus mõlemas otsas ilma võtmeteta, jaama kood, Atomi lehe uued osad | 5 p |
| Analüüs — ruutimistabelid seletatud, kolm teekonda ennustuse ja tulemusega, NAT, latentsus laboris ja läbi tunneli, kaamerad läbi tunneli, 48 tunni logi | 5 p |
| Prototüüp — jaama leht avaneb telefonist mobiilse andmesidega ainult läbi tunneli ja liigutab robotit, tunnel tuleb pärast taaskäivitust ise tagasi, katkenud ühendus viib roboti ohutusse olekusse, klapp ja LED on Atomi lehel | 5 p |
| Dokumentatsioon — README, arenduspäevik, aadressiplaan, `routing.md`, ohutuskokkulepe, `atom_page.md`, `bom.md`, AGENTS.md | 5 p |
| **Kokku** | **20 p** |

### Täielik tööleht

📎 [Link täielikule töölehele](https://github.com/KKallas/Narva-subjects/blob/main/EST/2026-27/Smart%20Solutions/Smart%20Solutions%20%5BLab%203%5D%20EST.md)

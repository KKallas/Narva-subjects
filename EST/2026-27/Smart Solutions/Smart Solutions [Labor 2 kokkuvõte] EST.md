## Nutikad Lahendused: Labor 2 — Server internetis ja kaks kaamerat

**Maht:** 28 tundi | **Hindamine:** 20 punkti | **Meeskonnatöö:** 3-liikmelised meeskonnad | **Välja antud:** 07.10.26 | **Tellimise kuupäev:** 16.10.26 | **Esimene kaitsmine:** 27.10.26, veebis

### Mida teete

Laboris 1 sai jaam robotiga rääkima ja Atom sai oma lehe. Kõik see töötab ainult siis, kui sa oled laboris. Su sülearvutil ja Atomil on labori võrgus privaatne aadress: väljast sisse ei saa, aga seest välja saab, ja vastus tuleb sama teed tagasi. Kogu see labor on ehitatud selle asümmeetria peale.

Vahele tuleb **droplet**: väike Linuxi server, millel on avalik aadress ja nimi. Seal jookseb veebiserver, mis töötab nagu **postkontor**. Kasutaja jätab brauserist või telefonist sõnumi: joonista see täht, näita seda pilti. Roboti Atom tuleb kindla vahe tagant ise ja küsib, kas talle on sõnumeid. Kui on, viib ta sõnumi jaama, robot teeb töö ära ja Atom jätab postkontorisse vastuse. Postkontor ei tea, kus robot on, ja ei helista talle kunagi. **Jäta sõnum telefonist, mille WiFi on välja lülitatud, ja robot joonistab tähe.**

See ei ole otsejuhtimine. Sõnum ootab, kuni Atom järgmine kord tuleb, ja sõnumiga saab tellida terve töö, mitte liigutada kätt millimeetri kaupa. Otsejuhtimine tuleb Laboris 3 ruuteri ja VPN-iga.

Laua juurde tuleb **kaks kaamerat**, sest robotit, mida sa ei näe, sa ei käsuta. Veebikaamera laua kohal näeb kogu lauda, aga ei näe, kas napp on klaasi keskel. Kaamera tööriista küljes näeb otsikut, aga ei näe, kuhu käsi läks.

Kolm osa:

**1. Droplet** — õppejõud annab tühja Ubuntu serveri. Iga arvuti, millega sisse minnakse, saab oma SSH võtme; avalikud pooled lähevad õppejõule, vastu tulevad dropleti aadress ja link. Paroolisisselogimine keelatud, tulemüür lahti ainult nendel portidel, mida sa päriselt kasutad, HTTPS pöördproksiga, mis võtab sertifikaadi ise. Siis tee seadistus üks kord meelega uuesti, ainult oma märkmete järgi. Tulemus: leht käib lingi peal HTTPS-iga ja dropleti ehitus on samm-sammult kirjas.

**2. Postkontor** — veebiserver dropletis, kahe külastajaga: kasutaja jätab sõnumi, Atom käib postil. Neli asja ei ole vabatahtlikud: sõnum on töö nimekirjast, mitte liigutus; sõnum aegub; Atom tõendab võtmega, kes ta on; test käib väljast, mobiilse andmesidega. Mõõda 30 sõnumit vajutusest roboti esimese liigutuseni, kahe erineva küsimisvahega. Siis katkesta ühendus keset tööd ja tõmba Atom vooluta. Tulemus: `docs/server_api.md`, lubatud tööde nimekiri, latentsuse tabel Labori 1 numbri kõrval, ja leht, mis ütleb ausalt, kui Atom on vait.

**3. Kaamerad ja Atomi leht** — USB veebikaamera (UHD) posti otsas käib jaama külge; Seeed Studio XIAO ESP32S3 Sense kaameramoodul iminapa kõrval on omaette väike arvuti WiFi-s, nagu Atom. Mõlemad pildid tulevad jaama lehele kõrvuti ja jäävad labori võrku. Mõõda kummagi viide, kaadrisagedus ja ribalaius, ja siis roboti juhtimise latentsus uuesti, mõlema kaamera töötamise ajal. Atomi lehele tulevad juurde rõhuanduri seaded ja testinupp Andmehõive Laborist 2, serveri aadress, Atomi võti ja küsimisvahe. Uut lehte ei tehta. Tulemus: üks pilt kummastki kaamerast samal hetkel, numbrid kummagi kohta, `docs/atom_page.md` uuendatud.

### Kuidas töö käib

Repo ja töökord on Laborist 1 olemas ja samad. Tervet töölehte üle kopeerida ei ole vaja — too oma repo juurde see, mida vaja, ja täida `README.md` oma numbrite ja otsustega. Skeemid lähevad dokumenti pildina, pildi juurde link elavale failile. Ei tulnud esimesel korral välja, tule homme tagasi ja proovi uuesti.

Esimene samm on sinu arvutis, mitte serveris: tee SSH võti ja saada avalik pool õppejõule. Privaatne pool ei lahku su arvutist kunagi.

Enne, kui postkontor esimest korda robotit liigutab, lepib meeskond kokku ja kirjutab faili, kes tohib sõnumeid jätta. Robot võtab sõnumeid vastu ainult siis, kui ruumis on inimene, kes hädastoppi ulatub.

Esimesel päeval uusi osi ei ole — ehita sellest, mis riiulil on.

### Komponendid selle labori jaoks

Droplet ja link tulevad õppejõult; neid tellimusse ei panda. Tellimus läheb välja 16.10.26 ja jõuab kohale enne kaitsmist. Valmis nimekirja ei ole: meeskond paneb tellimuse ise kokku faili `docs/bom.md`, iga rea juures üks lause, milline osa seda küsib.

### Kaitsmiseks on vaja

**Ainult git repositooriumi link, tag `smart-solutions-lab2`.** Kaustas `smart-solutions/lab2/` peab olema:
- `server/` dropletis jooksev veebiserver, `src/` jaama kood kaamerate voogudega, `firmware/` Atomi PlatformIO projekt
- `docs/`: dropleti ehitus samm-sammult, ahela skeem draw.io-s, `server_api.md`, `atom_page.md`, ohutuskokkulepe, latentsuse CSV-d, ekraanipildid ja fotod, `bom.md`
- Täidetud `README.md` koos arenduspäevikuga
- `AGENTS.md` uuendatud

Kaitsmine on lihtne suuline 15 minuti jutuajamine. Avad oma telefonist mobiilse andmesidega lehe, jätad sõnumi, robot joonistab tähe ja vastus ilmub lehele. Jätad sõnumi, mida nimekirjas ei ole, ja näitad, mis sellest sai. Tõmbad Atomi vooluta ja näitad, mida leht siis ütleb. Näitad jaama lehel mõlemat kaamerat. Avad oma arenduspäeviku. Umbes viis küsimust selle kohta, kuidas sa selle tegid. Kaitsta saab nii mitu korda, kui vaja.

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — dropleti seadistus kirjas ja korratav, serveri kood, Atomi püsivara postilkäimisega, jaama kood, kahe kaamera vood, Atomi lehe uued osad | 5 p |
| Analüüs — latentsus sõnumist liigutuseni kahe küsimisvahega ja Labori 1 numbri kõrval, kummagi kaamera viide, kaadrisagedus ja ribalaius, juhtimise latentsus kaameratega ja ilma | 5 p |
| Prototüüp — leht avaneb telefonist mobiilse andmesidega HTTPS-i peal, sõnum paneb roboti tööd tegema ja vastus tuleb tagasi, aegunud ja lubamata sõnum ei liiguta midagi, leht näitab ausalt, kui Atom on vait, üks kaamera näitab kogu lauda ja teine otsikut | 5 p |
| Dokumentatsioon — README, arenduspäevik, `server_api.md`, `atom_page.md`, ohutuskokkulepe, `bom.md`, AGENTS.md | 5 p |
| **Kokku** | **20 p** |

### Täielik tööleht

📎 [Link täielikule töölehele](https://github.com/KKallas/Narva-subjects/blob/main/EST/2026-27/Smart%20Solutions/Smart%20Solutions%20%5BLab%202%5D%20EST.md)

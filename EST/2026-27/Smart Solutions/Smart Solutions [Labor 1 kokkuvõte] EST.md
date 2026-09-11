## Nutikad Lahendused: Labor 1 — Robot, ekraan ja täht

**Maht:** 28 tundi | **Hindamine:** 20 punkti | **Meeskonnatöö:** 3-liikmelised meeskonnad | **Tellimise kuupäev:** 22.09.26 | **Esimene kaitsmine:** 06.10.26, veebis

### Mida teete

Sama meeskond teeb kõiki kolme ainet. Iga aine annab ühe tüki: Andmehõive teeb AtomS3, mille nupp valib tähe ja saadab selle välja. 3D printimine teeb pastakahoidiku, mis käib roboti käe otsa. Robotil MG400 on võrguport, kust ta võtab vastu liikumiskäske. Igaüks neist töötab eraldi, aga eraldi ei joonista neist ükski. Puudu on osa, mis võtab tähe Atomist vastu ja teeb sellest roboti liigutused. Selle osa teed sina. **Vajuta Atomil tähte, robot joonistab selle paberile.**

**Jaam** on sinu sülearvuti, kus jookseb Pythoni programm. Jaam räägib Atomiga üle WiFi ja robotiga üle Etherneti.

Kolm osa:

**1. Robot** — pane MG400 tööle oma sülearvutist. Õppejõud annab baaspaketi: Pythoni programm, mis avab brauseris lehe liugurite ja pumba nuppudega. Kontrolli, kas paketi eeldused (aadressid, pumba DO liinid) vastavad tõele, ja õpeta robotile neli asendit. Tulemus: aadressiplaan, `data/positions.json`, kümme tõstmist.

**2. Ekraan** — laadi AtomS3-le PlatformIO-st püsivara, mis teeb oma WiFi võrgu ja näitab lehte, kust saab pildi ekraanile saata. Kui telefon võrguga liitub, peab leht ise lahti minema, ilma aadressi trükkimata. Lehele tuleb seadete ja testinuppude osa, mis jääb kogu aastaks: kõik, mis hiljem Atomi külge tuleb, saab oma seaded ja testinupu siia. Tulemus: telefon satub lehele ilma aadressita, pilt ekraanil, `docs/atom_page.md`.

**3. Täht** — Atomi nupp valib tähe, täht jõuab jaama, jaam saadab robotile liikumiskäsud, robot joonistab tähe paberile. Kolm tähte. Tulemus: `docs/letter_channel.md`, `docs/letters.md`, `docs/latency.csv`.

### Kuidas töö käib

Kopeeri täielik tööleht esimesel päeval oma repo laborikausta `README.md`-ks ja täida seal, töö käigus. Midagi ei kustutata: vale number jääb, parandus tuleb tema alla. Skeemid ja simulatsioonid lähevad dokumenti pildina, pildi juurde link elavale failile. Tähtaeg ei ole tähtis. Ei tulnud esimesel korral välja, tule homme tagasi ja proovi uuesti.

### Komponendid järgmiseks laboriks

Tellimus läheb välja 22.09.26. Teine Atom tööriista külge, otsiku kaamera, 3/2 klapp liitmike ja voolikuga, MOSFET moodulid, 405 nm LED-id jahutite ja draiveriga, USB kaablid, kaitseprillid. Kogused ja põhjused on töölehel.

### Kaitsmiseks on vaja

**Ainult git repositooriumi link, tag `smart-solutions-lab1`.** Repos peab olema:
- `src/` jaama kood, `firmware/` Atomi PlatformIO projekt, `data/positions.json`
- `docs/`: `atom_page.md`, `letters.md`, `letter_channel.md`, `pick_test.csv`, `latency.csv`, fotod, draw.io skeem
- Täidetud tööleht `README.md`-na koos arenduspäevikuga
- `AGENTS.md` uuendatud

Kaitsmine on lihtne suuline 15 minuti jutuajamine. Näitad, kuidas Atomil vajutatud tähe robot joonistab, avad telefonist Atomi lehe ja oma arenduspäeviku. Umbes viis küsimust selle kohta, kuidas sa selle tegid. Kaitsta saab nii mitu korda, kui vaja.

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — baaspaketi seadistus ja sinu muudatused, Atomi püsivara, täheteed, `positions.json` | 5 p |
| Analüüs — aadressiplaan, DO kontroll, tõstmise tabel, üleslaadimise aeg, latentsus hüpe-haaval | 5 p |
| Prototüüp — leht liigutab robotit, pump käsurealt, Atom teeb võrgu ja telefon satub lehele, pilt ekraanil, robot joonistab Atomil valitud tähe | 5 p |
| Dokumentatsioon — README, arenduspäevik, `atom_page.md`, `letters.md`, `letter_channel.md`, AGENTS.md | 5 p |
| **Kokku** | **20 p** |

### Täielik tööleht

📎 [Link täielikule töölehele](https://github.com/KKallas/Narva-subjects/blob/main/EST/2026-27/Smart%20Solutions/Smart%20Solutions%20%5BLab%201%5D%20EST.md)

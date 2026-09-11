## Andmehõive: Labor 1 — Andur, ja kompressor, mis ise seisma jääb

**Maht:** 32 tundi | **Hindamine:** 20 punkti | **Meeskonnatöö:** 3-liikmelised meeskonnad | **Tellimise kuupäev:** 22.09.26 | **Esimene kaitsmine:** 06.10.26, veebis

### Mida teete

Laboris on viis MG400 ja viis pumbakasti. Üks neist on tark: mõõdab rõhku ja laseb pumbal seista, kui rõhk on käes. Neli ülejäänut töötavad nii kaua, kui DO liin on üleval. Kõik viis peavad käituma nagu tark: igasse väljundtorusse andur, AtomS3 ekraanile rõhk ja otsus, arvutisse Python, mis lülitab pumba MG400 DO liini kaudu. Sama meeskond teeb kõiki kolme ainet: sama Atom saadab ka tähe, mille robot joonistab. **Vajuta tähte, robot joonistab selle.**

Viis osa:

**1. Andur ja esimene signaal** — MPX5700AP maketeerimisplaadil otse ADC-sse, vahel ei ole midagi; jagur ja op-amp tulevad Laboris 2 ja neid võrreldakse selle toore signaaliga. Atom näitab kPa, Python kirjutab CSV 100 Hz. Falstadis andur → ADC koos müraallikaga. Tulemus: Pa ühe ADC sammu kohta, müra LSB-des, spektri tipud nimedega.

**2. Tark kast** — T-liitmik tehase targa kasti torusse, logi viis minutit. Tulemus: välja- ja sisselülitusrõhk, tööaeg, seisuaeg, käivitusi minutis. Need on sinu kasti sihtmärk.

**3. Sinu kast** — Atom otsustab ja näitab, arvuti lülitab pumba. Kui midagi on valesti, pump seisab. Robot võtab napiga klaasi kümme korda. Tulemus: riba, seisuaja alampiir ja käivituste piir failis `docs/pump_control.md`.

**4. Anduri valik ja tellimus** — iga kandidaadi kohta samad numbrid, otsus numbritega. Tulemus: `docs/sensor_choice.md` ja tellimus Mouseri koodidena `docs/bom_lab2.md`, 22.09-ks.

**5. Täht** — lühike vajutus valib tähe, pikk saadab selle jaama. Robot joonistab.

### Kuidas töö käib

Kopeeri täielik tööleht esimesel päeval oma repo laborikausta `README.md`-ks ja täida seal, töö käigus. Midagi ei kustutata: vale number jääb, parandus tuleb tema alla. Skeemid ja simulatsioonid lähevad dokumenti pildina, pildi juurde link elavale failile; näited on töölehel. Tähtaeg ei ole tähtis. Ei tulnud esimesel korral välja, tule homme tagasi ja proovi uuesti.

### Komponendid selle labori jaoks

Tellimus läheb välja 22.09.26 ja jõuab kohale enne kaitsmist. Sinu valitud pumba-andur, T-liitmikud ja korgid, kui riiulilt otsa said. Kogused ja põhjused on töölehel.

### Kaitsmiseks on vaja

**Ainult git repositooriumi link, tag `data-acquisition-lab1`.** Repos peab olema:
- `src/` püsivara ja logijaga, `data/` CSV failidega, `notebooks/` spektritega
- `docs/`: skeemi foto, ostsilloskoobi pilt, Falstadi eksport, `pump_control.md`, `sensor_choice.md`, `bom_lab2.md`
- Täidetud tööleht `README.md`-na koos arenduspäevikuga
- `AGENTS.md` uuendatud

Kaitsmine on lihtne suuline 15 minuti jutuajamine. Näitad, kuidas sinu kast ise seisma jääb ja uuesti käivitub, kui nappi kergitad, ja avad oma arenduspäeviku. Umbes viis küsimust selle kohta, kuidas sa selle tegid. Kaitsta saab nii mitu korda, kui vaja.

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — Atomi püsivara, Pythoni logija ja pumba juhtimine, CSV failid | 5 p |
| Analüüs — Pa ühe ADC sammu kohta, spektrid nimedega, targa kasti numbrid, hoidmiskõverad, anduri valik | 5 p |
| Prototüüp — sinu kast jääb ise seisma imemisel ja puhumisel, USB välja = pump välja, robot võtab klaasi, täht jõuab jaama | 5 p |
| Dokumentatsioon — README, arenduspäevik, `pump_control.md`, `sensor_choice.md`, `bom_lab2.md`, AGENTS.md | 5 p |
| **Kokku** | **20 p** |

### Täielik tööleht

📎 [Link täielikule töölehele](https://github.com/KKallas/Narva-subjects/blob/main/EST/2026-27/Data%20Acquisition/Data%20Acquisition%20%5BLab%201%5D%20EST.md)

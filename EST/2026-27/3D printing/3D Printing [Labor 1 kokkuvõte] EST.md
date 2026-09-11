## 3D printimine ja CAD: Labor 1 — Printer, ja tööriist, mis annab järele

**Maht:** 30 tundi | **Hindamine:** 20 punkti | **Meeskonnatöö:** 3-liikmelised meeskonnad | **Tellimise kuupäev:** 22.09.26 | **Esimene kaitsmine:** 06.10.26, veebis

### Mida teete

Aasta lõpuks paneb MG400 kokku sildi: AtomS3, mille ekraani peale on liimitud polükarbonaatklaas. Iga detail, mis roboti külge kinnitub või elektroonikat hoiab, tuleb selles ruumis printerist välja. See labor räägib sellest printerist ja lõpeb esimese tööriistaga roboti küljes: pastakahoidikuga. Sama meeskond teeb kõiki kolme ainet: sina kirjutad programmi ja sina teed pastaka otsiku. **Vajuta tähte, robot joonistab selle.**

Kolm asja:

**1. Kuup** — Fusionis, 5 × 5 × 5 cm, sees silinder raadiusega 2 cm. Lõtk silindri ja seina vahel on parameeter. Kui print võtab liiga kaua, tee kuup madalamaks. Tulemus: lõtk, millega silinder pöörleb, ja lõtk, millega on kinni sulanud.

**2. Paindlik tükk** — sinu disain, sinu tarkvara. Prindi ja painuta. Tulemus: kuhu maani paindub ja tuleb tagasi, kust alates jääb plastiliselt kõveraks, kus murdub.

**3. Pastakahoidik** — tarkvaras, mille ise valid (Fusion, Blender või muu). Toru kuulpastaka jaoks ja kinnitus MG400 flantsi külge. Vedrutav osa nii, et kui õpetatud kõrgus on paar millimeetrit paigast ära, jääb pastakas terveks ja joon on paberil. Iga print on uus versioon ja uus fail. Robot joonistab sellega tähe, mida ESP32 näitab.

### Kuidas töö käib

Kopeeri täielik tööleht esimesel päeval oma repo laborikausta `README.md`-ks ja täida seal, töö käigus. Midagi ei kustutata: vale number jääb, parandus tuleb tema alla. Tähtaeg ei ole tähtis. Ei tulnud esimesel korral välja, tule homme tagasi ja proovi uuesti.

### Komponendid järgmiseks laboriks

Tellimuse paneb kokku meeskond ise, jagatud Google Sheetis. Tellimus läheb välja 22.09.26. Kirjuta sinna see, mida sul selle labori järgi päriselt puudu jäi.

### Kaitsmiseks on vaja

**Ainult git repositooriumi link, tag `3d-print-lab1`.** Repos peab olema:
- Lähtefailid, STL ja `.3mf` iga prindi kohta
- Täidetud tööleht `README.md`-na koos arenduspäevikuga
- `AGENTS.md` uuendatud

Kaitsmine on lihtne suuline 15 minuti jutuajamine. Näitad, kuidas robot joonistab tähte, mida ESP32 näitab, ja avad oma arenduspäeviku. Umbes viis küsimust selle kohta, kuidas sa selle tegid. Kaitsta saab nii mitu korda, kui vaja.

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — kuup, paindlik tükk, hoidiku versioonid, STL ja 3MF | 5 p |
| Analüüs — lõtk, paindumise ja murdumise numbrid | 5 p |
| Prototüüp — hoidik roboti küljes annab järele, robot joonistab tähe, mida ESP32 näitab | 5 p |
| Dokumentatsioon — README, arenduspäevik, AGENTS.md | 5 p |
| **Kokku** | **20 p** |

### Täielik tööleht

📎 *Lisa siia link täielikule töölehele*

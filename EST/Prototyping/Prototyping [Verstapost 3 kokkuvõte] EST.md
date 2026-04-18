## Prototüüpimine: Verstapost 3 — Integreeritud tehniline prototüüp

**Maht:** 18 tundi | **Hindamine:** 20 punkti | **Meeskonnatöö:** 4-liikmelised meeskonnad

### Mida teete

Panete kõik V2 komponendid ühele šassiile kokku ja asendate käsinupud kaamerapildil klõpsamisega. Kui operaator klõpsab kaamera pildil kohale, sõidab robot sinna — see on V3 põhiülesanne.

**Integreeritud šassii** — kõik V2 komponendid (mootorid, draiver, MCU, andurid, arvutusplatvorm) ühel šassiil, toide ühest akust, üks lüliti sisse/välja. Enne sisselülitamist kontroll multimeetriga (lühiühenduse test, pingekontroll).

**Kaamera kalibreerimine** — prindi A4 malelaud (8×10 ruutu, 25mm), pane roboti kaamera vaatevälja, mõõda roboti offset malelaua keskpunktist. OpenCV tuvastab 63 nurka sub-piksli täpsusega ja arvutab H (homograafia) maatriksi — 3×3 teisendustabel mis muudab iga piksli põrandakoordinaadiks roboti suhtes.

**Klõpsa-ja-sõida** — klõps pildil → homograafia → kaugus ja nurk → pööra → sõida → peatu. Vajad kahte mõõdetud konstanti: lineaarne kiirus (cm/s) ja pöördekiirus (kraadi/s), mõlemad kronomeetriga.

**Piiri ja tsoonide tuvastamine** — punane joon on välispiir (MCU tuvastab kohe, peatab mootorid sõltumata serverist). Tsoonide värve kalibreerid areenil (30 näitu iga pinna kohta), klassifitseerimine lähima naabri meetodiga serveris. Veebiliides näitab praegust tsooni + toorväärtusi.

**Aku logimine** — logi aku taset (telefoni BatteryManager või ESP32 ADC pingejaguriga) CSV-sse iga 30 sekundi tagant.

### Analüüsid (Jupyter Lab)

Kolm analüüsi Jupyter notebooks:

1. **Klõpsa-ja-sõida täpsus** — 10 sihtpunkti × 3 korda, scatter-graafik siht vs tegelik + viga vs kaugus, mediaan- ja maksimaalne viga
2. **Piiri tuvastamise reaktsiooniaeg** — anduri reaktsioon + side latentsus + mootori pidurdus = kogu pidurdusteekond (cm). Kas robot peatub 10cm piirialas?
3. **Aku tööaeg** — aku % vs aeg matšitingimustes (3 min aktiivne + 1 min passiivne tsüklitena), mitu matši saab enne 20% lävit?

### Kaitsmiseks on vaja

**Ainult git repositooriumi link.** Repos peab olema:
- Töötav kood (integreeritud süsteem: klõpsa-ja-sõida + piiri tuvastamine)
- Analüüside Jupyter notebooks koos mõõteandmetega (CSV)
- Uuendatud spetsifikatsioon: mis muutus pärast integratsiooni?
- Fotod/videod integreeritud robotist

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — kood repos, fotod/videod | 4 p |
| Analüüs — kolm Jupyter notebooki | 4 p |
| Prototüüp — klõpsa-ja-sõida töötab, piir peatab | 4 p |
| Dokumentatsioon — spetsifikatsiooni uuendus | 4 p |
| Küsimuste-vastuste sessioon ja tagasiside | 4 p |
| **Kokku** | **20 p** |

### Täielik tööleht

📎 *Lisa siia link täielikule töölehele*

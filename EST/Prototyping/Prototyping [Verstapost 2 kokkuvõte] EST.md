## Prototüüpimine: Verstapost 2 — Võtmetehnoloogia prototüüp

**Maht:** 16 tundi | **Hindamine:** 20 punkti | **Meeskonnatöö:** 4-liikmelised meeskonnad

### Mida teete

Ehitate ja testite kõige kriitilisemad tehnilised komponendid eraldi — enne kui proovite kõike kokku panna. Iga alamprototüüp peab töötama iseseisvalt enne järgmise juurde liikumist.

**Ajami prototüüp** — mootorid + draiver + rattad lihtsale testšassiile. Testid: edasi/tagasi, pööramine, koormustestid raskustega.

**Side prototüüp** — ESP32 ↔ telefon (USB OTG / WiFi), JSON käsud. Alguses testid arvutist USB kaudu, seejärel vahetad telefoni peale.

**Veebiliidese prototüüp** — minimaalne veebileht: üks nupp → mootor liigub. Termux + FastAPI telefoni peal või ESP32 veebiserver.

**Anduri prototüüp** — kaugusandur ja/või värviandur maketeerimisplaadil. Mõõtmised erinevatel kaugustel/pindadel.

**PCB disain** — mootori draiveri plaat Fusion 360 EDA-s (skeem, paigutus, DRC, Gerber failid).

### Analüüsid (Jupyter Lab)

Kolm analüüsi Jupyter notebooks: tõuketest (koormamass vs. kiirus, mõõdetud vs. spetsifikatsioonis arvutatud), side latentsuse jaotus (100+ mõõtmist, histogram, mediaan ja 95. protsentiil) ja anduri tuvastusstatistika (täpsus ja lahutusvõime erinevatel kaugustel/pindadel).

### Kaitsmiseks on vaja

**Ainult git repositooriumi link.** Repos peab olema:
- Töötav kood (ESP32 + telefoni/arvuti pool)
- Analüüside Jupyter notebooks koos mõõteandmetega (CSV)
- Uuendatud spetsifikatsioon: mis muutus pärast esimesi teste?
- PCB disaini failid (skeem + Gerber)

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — ajami, side ja anduri kood | 4 p |
| Simulatsioon / analüüs — kolm Jupyter analüüsi | 4 p |
| Prototüüp / füüsiline — töötav testšassii ja side | 4 p |
| Dokumentatsioon — uuendatud spetsifikatsioon | 4 p |
| Küsimuste-vastuste sessioon ja tagasiside | 4 p |
| **Kokku** | **20 p** |

### Täielik tööleht

📎 *Lisa siia link täielikule töölehele*

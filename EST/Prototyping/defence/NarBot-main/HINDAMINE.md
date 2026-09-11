# NarBot — Verstapostide hindamine

**Hindaja:** Kaspar Kallas
**Hinnatud:** _______________

**Kriteeriumid (per verstapost, 5×4 = 20 p):** Tööfailid · Analüüs · Prototüüp · Dokumentatsioon · Küsimused-vastused

> **Struktuurne märkus:** esitatud on **ainult VP1 ja VP2** (PDF-id). VP3–VP5 puuduvad. Arendus on osaliselt AI-toega ja seda **ei varjata** — `NarbotESP/architecture.md` on sõna-sõnalt LLM-ile antud prompt. Repo on tehniliselt korralik (PlatformIO, clangd, code_style.md, eraldi moodulid).

---

## Üldprofiil — vastupidine teistele tiimidele

| Tugevus | Nõrkus |
|---|---|
| **Tugevaim VP1 spetsifikatsioon** kolmest (MoSCoW nõuded, jõudlustabel mõõtmismeetoditega, riskianalüüs) | **VP2 on suuresti täitmata mall** — korduv "Siia vaja lisada" |
| **Päris KiCad PCB** (sch + pcb + pro) | **Mõõtmistulemused puuduvad** — 8 testi defineeritud, 0 täidetud |
| **Modulaarne firmware** (NarbotESP: wifi/camera/web/led eraldi failides) + CameraDriver 1275 rida | Üks "analüüsi" notebook (CameraTest) = lihtsalt kaamerakaadri haaramine, ilma mõõtmise/markdownita |
| **CAD + dokumentatsiooni PDF** + STL/STEP | ColorCalibration kaust tühi |

**Lühidalt:** parim *vundament* (spetsifikatsioon, PCB, firmware-arhitektuur), aga nõrgim *VP2 teostus* (mõõtmised tegemata). Rubriik rõhutab just mõõtmist — see lööb skoori alla.

---

## VP1 — Süsteemispetsifikatsioon

Tugev, professionaalse struktuuriga spetsifikatsioon:
- **Funktsionaalsed nõuded MoSCoW prioriteediga** (FN-001…015, MUST/SHOULD/COULD) — korralik nõuete-inseneeria
- **Jõudluseesmärkide tabel** — parameeter / eesmärk / miinimum / **mõõtmismeetod** (9 rida)
- 3 referentssüsteemi (SMARS, mecArena, ESP32-CAM) eeliste/puudustega
- Komponentide valik + põhjendus + alternatiivid
- Riskianalüüs (mõju/tõenäosus/leevendus)
- Teostatavusanalüüs: mootori moment F=m·g·μ → T=0,206 Nm, mootorile 0,103 Nm; N20 1:50 annab 0,12–0,18 Nm → **piisav**
- Testimisplaan, arendusgraafik, ostunimekiri

**Hinnang:** VP1 on **kolme tiimi parim spetsifikatsioonidokument**. Ainus piirang: üks teostatavusarvutus (moment), kus KAPO-l oli kolm. Aga spetsifikatsioonina suurepärane.

**Märkmed:**
<!-- kirjuta siia -->


---

## VP2 — Võtmetehnoloogia prototüüp (rubriigi järgi)

| Kategooria | Punktid | Põhjendus |
|---|---|---|
| Tööfailid | **4/4** | Modulaarne firmware (NarbotESP) + CameraDriver (1275 rida) + **päris KiCad PCB** + CAD/STL. Tugevaim koodibaas. (Puudu: ehitusfotod) |
| Analüüs | **1/4** ⚠️ | Rubriik nõuab "3 notebooki mõõtmistulemustega". Olemas **0 reaalset analüüsi** — CameraTest.ipynb on ainult kaamerakaadri haaramine (ilma markdown/mõõtmiseta), ColorCalibration tühi. VP2-s 8 testi defineeritud, **tulemused täitmata** |
| Prototüüp | **3/4** | Firmware katab kõik: mootorid (TB6612), WiFi AP + veebiserver + MJPEG, värviandur (TCS raw I2C). VP2 väidab "töötab" — **kood toetab väidet**, aga tõendeid (ekraanipildid/video/andmed) pole |
| Dokumentatsioon | **2/4** ⚠️ | VP2 on struktureeritud, aga **täitmata mall** — korduv "Siia vaja lisada". Ei sulge V1-vs-mõõdetud silmust (rubriigi nõue) |
| Küsimused-vastused | **? / 4** | **Pole infot** demo/arutelu kohta — täida ise |
| **Kokku (ilma Q&A)** | **10/16** | + Q&A |

---

## ⚠️ Peamine probleem hindamisel

NarBotil on **objektiivselt tugevaim inseneri-vundament** (spetsifikatsioon, PCB, firmware-arhitektuur), aga **VP2 ei tõesta midagi mõõtmistega**. Dokument kirjeldab, *mida testida*, ja jätab iga tulemuse plokki "Siia vaja lisada":
- kauguse täpsus — täitmata
- latentsus — "Siia vaja lisada tulemused"
- tõuketest — täitmata
- värvituvastus — andur isegi valimata ("kasutatav andur" puudu)
- FPS, ekraanipildid, ühendusskeem — kõik täitmata

See on **täpselt vastupidine KAPO-le** (kes esitas reaalsed mõõtmised v2-s). Kui rubriigi "Analüüs" ja "Dokumentatsioon" nõuavad mõõtmistulemusi ja V1-järelduste sulgemist, siis NarBot neid VP2-s **ei esita**, hoolimata sellest et riistvara/firmware ilmselt töötab.

## Soovitus
Kahe variandi vahel:
- **Hinda nagu on:** VP2 ≈ 10/16 + Q&A. Vundament tugev, aga verstaposti tuum (mõõtmine + dokumenteerimine) tegemata.
- **Anna parandusvõimalus (nagu KAPO-le):** firmware ja testplatvorm on olemas — mõõtmised (kaugus, latentsus, FPS, värv, tõuge) saaks olemasoleva riistvaraga kiiresti teha ja malli täita. Siis tõuseks Analüüs ja Dokumentatsioon oluliselt.

Õiglane oleks **sama kohtlemine nagu KAPO** — kui KAPO sai parandada genereeritud andmed reaalseteks, võiks NarBot täita malli reaalsete mõõtmistega. Vundament on selleks tugevaim kolmest.

## Koondhinne

| Verstapost | Punktid / hinne | Kommentaar |
|---|---|---|
| VP1 (spetsifikatsioon) |  | tugevaim spec kolmest |
| VP2 |  | vundament tugev, mõõtmised tegemata |
| **Kokku** |  | |

**Märkmed:**
<!-- kirjuta siia -->

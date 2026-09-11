# ATOM-Sumo — Verstapostide hindamine

**Hindaja:** Kaspar Kallas
**Hinnatud:** _______________

**Alus:** `docs/milestones/VERSTAPOST_REQUIREMENTS_TRACKER.xlsx` (meeskonna enda nõuete-jälgija, 5 verstaposti).
**Kriteeriumid (per nõue):** (1) nõue täidetud · (2) reaalne tõend olemas · (3) reaalne mõõtmine vs genereeritud · (4) lahtine töö dokumenteeritud.

> **Andmete kvaliteet:** erinevalt mõnest teisest tiimist on tõendid **reaalsed mõõtmised** — `tests/results/` sisaldab kuupäevatatud CSV-faile (movement_speed, tof, latency, brownout, tap_drive, color). Pisteliselt kontrollitud: väärtused on realistlikud ja varieeruvad, mitte genereeritud. ✅

> **Konteksti märkus (3 EAP):** maksimumhinde jaoks loevad eelkõige **esimesed 3 verstaposti**. VP4–VP5 on jälgijas, kuid osa nõudeid veel lahtised — vt allpool.

---

## Kokkuvõttetabel — 5 verstaposti

| Verstapost | Nõudeid | ✅ Valmis | ⚠️ Osaline | ❌ Avatud | Üldhinnang |
|---|---|---|---|---|---|
| **VP1 — Spetsifikatsioon** | 10 | 10 | 0 | 0 | ✅ Täielik |
| **VP2 — Juhtahel + testid** | 9 | 9 | 0 | 0 | ✅ Täielik |
| **VP3 — Integratsioon** | 8 | 7 | 1 | 0 | ✅ Peaaegu täielik |
| VP4 — Korpus / valideerimine | 8 | 3 | 2 | 3 | ⚠️ Pooleli |
| VP5 — Lõpppakett | 10 | 7 | 2 | 1 | ⚠️ Pooleli |

**Esimesed 3 verstaposti (max hinde skoop): 26/27 nõuet täidetud, 1 osaline.**

---

## VP1 — Spetsifikatsioon (10/10 ✅)

Kõik nõuded suletud. Tõendid: V1_specification.md, system_block + power_tree diagrammid, BOM.csv + Order1/2.png, power_scheme.md, test_plan.md, CAD/PCB, TECH_COMPARISON.md.

| # | Nõue | Staatus |
|---|---|---|
| 1 | Projekti kontseptsioon | ✅ |
| 2 | Arhitektuur + alamsüsteemid | ✅ |
| 3 | Kõrvalekalle algsest Android-brieftist | ✅ |
| 4 | Funktsionaalsed nõuded + prioriteedid | ✅ |
| 5 | Jõudluseesmärgid | ✅ (võrdle lõpptestidega) |
| 6 | BOM + hankestaatus | ✅ (lõplik BOM vajab täpseid allikaid) |
| 7 | Toitearhitektuur | ✅ (otsene voolumõõtmine veel vaja) |
| 8 | Testiplaan | ✅ |
| 9 | Disainitõendid | ✅ |
| 10 | Võrdlev/tradeoff-analüüs | ✅ |

**Märkmed:**
<!-- kirjuta siia -->


---

## VP2 — Juhtahel + testid (9/9 ✅)

Terve ahel brauser → mootorid demonstreeritud, reaalsed mõõtmised olemas.

| # | Nõue | Staatus | Tõend |
|---|---|---|---|
| 1 | Juhtahel brauser→mootorid | ✅ | firmware + web UI + motion |
| 2 | Wi-Fi AP + veebiserver | ✅ | firmware |
| 3 | Manuaalsed liikumiskäsud | ✅ | movement_speed_test.csv |
| 4 | Kiirus/triiv/pööre mõõtmised | ✅ | 4 reaalset CSV-d |
| 5 | HTTP latentsuse mõõtmine | ✅ | latency notebook + CSV-d |
| 6 | Kaamerastriimi tõend | ✅ | firmware + demo video |
| 7 | ToF integratsioon | ✅ | tof_accuracy + tof_stop CSV, kalibratsioon |
| 8 | PCB tõend | ✅ | schematic+layout+3D+Gerber (2026-06-17) |
| 9 | Toite robustsus (brownout) | ✅ | retest 30/30 OK, PWM 80–180 |

**Tugev koht:** brownout-retest (2026-06-17) — 30/30 rida ilma reseti/Wi-Fi katketa, kaamera vaadeldud. PWM 255 ausalt märgitud kui stabiilsest vahemikust väljas.

**Märkmed:**
<!-- kirjuta siia -->


---

## VP3 — Integratsioon (7/8 ✅, 1 ⚠️)

| # | Nõue | Staatus | Tõend / märkus |
|---|---|---|---|
| 1 | Mootorid+kaamerad+andurid+UI integreeritud | ✅ | main UI |
| 2 | Mõlemad kaamerastriimid UI-s | ✅ | main UI |
| 3 | Eesmine ToF telemeetria | ✅ | tof_accuracy_test.csv |
| 4 | Allapoole värvitelemeetria | ✅ | color repeatability |
| 5 | Klõpsa-ja-sõida | ✅ | 5/5 läbis, mediaanviga 20 mm, max 141 mm |
| 6 | Kaamera kalibratsioon | ✅ | 6 reaalset homograafia punkti, residual 45 mm |
| 7 | Piiri/värvikäitumine | ✅ | TCS34725, classifier flashitud |
| 8 | Lihtne autonoomne käitumine | ⚠️ **Osaline** | operaator nägi pööret ~200 mm; aku tühjenes enne 5-katselise logi täitmist |

**Ainus lahtine punkt:** VP3.8 — autonoomne käitumine vajab täislaetud akuga kordusrun, et 5-katseline logi-CSV lõpetada. Käitumine ise vaadeldud töötavana.

**Märkmed:**
<!-- kirjuta siia -->


---

## VP4 — Korpus / valideerimine (3 ✅ / 2 ⚠️ / 3 ❌)

| # | Nõue | Staatus |
|---|---|---|
| 1 | Korpuse/keha CAD | ✅ |
| 2 | Reaalne mehaaniline CAD-pakett | ✅ |
| 3 | Funktsionaalne prototüübi tarkvara | ✅ |
| 4 | Värvi/märgistatud ala tuvastus | ⚠️ Osaline (korratavus + suletud ahel) |
| 5 | Korpuse löögi/kuumuse valideerimine | ❌ Avatud (mõõdetud testid puuduvad) |
| 6 | Aku hoolduse/ligipääsu valideerimine | ❌ Avatud |
| 7 | Korduvmatši vastupidavus | ❌ Avatud (90 s kordusrun logi) |
| 8 | Kokkupanekufotod | ⚠️ Osaline (vaja mitmenurga lõppfotod) |

**Märkmed:**
<!-- kirjuta siia -->


---

## VP5 — Lõpppakett (7 ✅ / 2 ⚠️ / 1 ❌)

| # | Nõue | Staatus |
|---|---|---|
| 1 | Repo struktuur + indeks | ✅ |
| 2 | Täielik verstapostide jälgitavus | ✅ |
| 3 | Püsivara ehitatavus | ✅ |
| 4 | CAD/PCB pakett | ✅ |
| 5 | Lõplikud piirangud dokumenteeritud | ✅ |
| 6 | Kokkupanekujuhend | ⚠️ Osaline |
| 7 | Flashimise/seadistuse juhend | ✅ |
| 8 | Prindiseaded | ⚠️ Osaline |
| 9 | Lõplik integreeritud mõõtmisanalüüs | ✅ |
| 10 | ArUco/globaalne lokaliseerimine | ❌ Avatud (implementeeri või dok. tulevikutööna) |

**Märkmed:**
<!-- kirjuta siia -->


---

## Hinnanguline kokkuvõte

- **VP1–VP3 (max hinde skoop):** sisuliselt täielik — **26/27** nõuet suletud, ainus osaline (VP3.8 autonoomne käitumine) ootab täislaetud akuga kordusrun. Tõendid on reaalsed mõõtmised, mitte genereeritud andmed.
- **VP4–VP5:** dokumentatsioon ja CAD/PCB tugevad, kuid valideerimistestid (löök/kuumus, aku hooldus, vastupidavus, ArUco) veel lahtised. Need jäävad max-hinde skoobist välja, kuid loevad terviklikkuse poolelt.
- **Üldmulje:** väga distsiplineeritud insenertöö — jälgija, evidence-failid ja ausad "partial/open" staatused näitavad tugevat metoodikat.

---

## Lahtised punktid (kokkuvõttes)

| Verstapost | Lahtine | Mida vaja |
|---|---|---|
| VP3.8 | Autonoomne käitumine | täislaetud aku + 5-katseline logi-CSV |
| VP4.5–4.7 | Korpus/aku/vastupidavus | mõõdetud testitabelid |
| VP4.8 / VP5.6 / VP5.8 | Fotod/juhendid | mitmenurga lõppfotod |
| VP5.10 | ArUco lokaliseerimine | implementeeri või dok. tulevikutööna |

## Koondhinne

| Verstapost | Punktid / hinne | Kommentaar |
|---|---|---|
| VP1 |  |  |
| VP2 |  |  |
| VP3 |  |  |
| (VP4) |  |  |
| (VP5) |  |  |
| **Kokku** |  |  |

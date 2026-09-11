# KAPO Ta4ka — Verstapostide hindamine

**Meeskond:** Aleksandr Markov, Sergei Sizov, Mark-Kirill Gubal
**Hindaja:** Kaspar Kallas
**Hinnatud:** _______________

**Kriteeriumid:** (1) analüüs tehtud · (2) reaalne mõõtmine vs genereeritud · (3) teooria vs mõõdetud võrdlus · (4) järeldus / spetsi uuendus
**Allikas:** GitHubi uuemad **v2-failid** (`svip48-hue/KAPO-Ta4ka`) — mitte lokaalse kausta vanad versioonid.

> **NB:** Õpilane saatis 19.06.2026 e-kirjaga v2-versioonid, mis asendasid varem etteheidetud genereeritud andmed reaalsete mõõtmistega.

---

## Kokkuvõttetabel — 3 verstaposti

| Kriteerium | VP1 — Teostatavus | VP2 — Prototüüp + testid | VP3 — Süsteemi testid |
|---|---|---|---|
| 3 analüüsi olemas | ✅ 3/3 | ✅ 3/3 | ✅ 3/3 |
| Reaalsed mõõtmised | n/a (teoreetiline faas) | ✅ pärast v2-parandust | ✅ pärast v2-parandust |
| Teooria vs mõõdetud | — (annab baasjoone) | ✅ igas analüüsis | ✅ igas analüüsis |
| Järeldus / spetsi uuendus | ✅ | ✅ tugev (5 muudatust) | ✅ tugev (suunab VP4) |
| Genereeritud andmete probleem | — | ⚠️→✅ latentsus parandatud (v2) | ⚠️→✅ klik + aku parandatud (v2) |

---

## VP1 — Teostatavusanalüüs (teoreetiline)

| Analüüs | Sisu | Andmed | Hinnang |
|---|---|---|---|
| 1. Tõukejõud + aku | Ohutustegur 9.7×, ~20 matši | Teoreetiline arvutus | ✅ Korrektne baasjoon |
| 2. Draiveri valik | 3 varianti → DRI0044 | Võrdlusanalüüs | ✅ Põhjendatud |
| 3. Sarnased projektid | 3 avatud sumoroboti projekti | Kirjandus | ✅ Nõue täidetud |

VP1 on igati korras teostatavusfaasina. Andmed on teoreetilised, mis selles faasis ongi õige.

**Märkmed:**
<!-- kirjuta siia -->


---

## VP2 — Prototüüp + esimesed mõõtmised

| Analüüs | Reaalne tulemus | Andmete päritolu | Hinnang |
|---|---|---|---|
| 1. Tõuketest | 0.80 → **0.14 m/s** (reduktorikadu) | ✅ Reaalne (nöör + kelk + stopper) | ✅ Hea, aus |
| 2. Latentsus | mediaan 51 ms, max 390 ms | ⚠️ algselt genereeritud → ✅ **v2 reaalne** | ✅ v2 OK |
| 3. Andurid | VL53L0X ±, TCS34725 5/5 | ✅ Reaalne | ✅ Hea |

**Oluline:** v2-latentsus paljastas päris probleemi — mediaan 51 ms (mitte algne ilus ~4 ms), sest ESP32-C3 teeb kõike ühel tuumal. Lisaks leiti ja parandati päris bug (PING ID `uint32_t` ületäitumine). See on väärtuslikum kui algne "ilus" genereeritud tulemus.

**Märkmed:**
<!-- kirjuta siia -->


---

## VP3 — Tervikliku süsteemi testid

| Analüüs | Reaalne tulemus | Andmete päritolu | Hinnang |
|---|---|---|---|
| 1. Klõpsa-ja-sõida | viga 14→28→43 cm, **nurk ~konstant 9–11°** | ⚠️ algselt `np.random` → ✅ **v2 reaalne vaatlus** | ✅ v2 tugev |
| 2. Piiri reaktsioon | kogu 124 ms, pidurdus 1.2 cm | ✅ Reaalne (border_test.ino, 30 mõõtmist) | ✅ Hea |
| 3. Aku tööaeg | **~40 min, ~10 matši** (8.22V → 6.3V) | ⚠️ algselt teoreetiline → ✅ **v2 multimeeter** | ✅ v2 reaalne |

**Tugevaim analüüs:** v2-klõpsa-ja-sõida. Reaalsest testist tuletati, et viga **ei ole** kaamera kõrgus/nurk (nagu algselt arvati), vaid **konstantne ~9–11° suunanihe** (pöörde kalibreerimine). See on tõeline insenertöö järeldus, mis suunab VP4 õige probleemi juurde.

**Märkmed:**
<!-- kirjuta siia -->


---

## Hinnanguline kokkuvõte

- **VP1:** täies mahus tehtud, teoreetiline faas korrektne.
- **VP2:** kõik 3 analüüsi reaalsete andmetega (v2 järel); latentsus paljastas päris kitsaskoha + bug-fixi.
- **VP3:** kõik 3 reaalsed (v2 järel); klõpsa-ja-sõida annab tugeva diagnostilise järelduse.

**Peamine punkt:** Etteheide "genereeritud andmed pole kasulikud" on v2-versioonides täielikult lahendatud — kõik kolm probleemset analüüsi (VP2 latentsus, VP3 klik, VP3 aku) on nüüd reaalsetel mõõtmistel ja annavad *halvemaid aga ausaid* tulemusi, mis suunavad järgmisi samme.

---

## Lahtised tähelepanekud (hindamise miinused)

- CAD/Fusion VP2 ja VP3 on ainult OneDrive-lingid, mitte repos (VP2 mudelit ei saa otse kontrollida).
- Kuupäevade vastuolu notebookides (VP1 "Mai 2025", VP2 "21.03.2025") — tõenäoliselt copy-paste.
- Lokaalses kaustas on ikka vanad versioonid — hinda **GitHubi v2 järgi**.

## Koondhinne

| Verstapost | Punktid / hinne | Kommentaar |
|---|---|---|
| VP1 |  |  |
| VP2 |  |  |
| VP3 |  |  |
| **Kokku** |  |  |

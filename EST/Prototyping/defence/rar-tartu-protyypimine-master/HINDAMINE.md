# RAR-Tartu (Baruto) — Verstapostide hindamine

**Meeskond:** Margo, Martin, Rein
**Hindaja:** Kaspar Kallas
**Hinnatud:** _______________

**Alus:** sama kriteeriumistik nagu AtomSumo `VERSTAPOST_REQUIREMENTS_TRACKER.xlsx`, kohaldatud sellele projektile.

> ## ⚠️ Oluline struktuurne erinevus
> Erinevalt AtomSumost ja KAPO-st **ei ole see projekt jaotatud verstapostideks** ega sisalda nõuete-jälgijat. Repo on korraldatud valmistoote loogika järgi (README, firmware, docs, 3d_models, media).
>
> **Kriitiline puudus hindamisel:** projektis **puuduvad mõõdetud testandmed** — pole CSV-faile, pole Jupyter-notebooke, pole teooria-vs-mõõdetud võrdlusi ega kvantifitseeritud teste. Ainus analüüsidokument (`optimeerimine.md`) on **kvalitatiivne** (hüpoteesid kitsaskohtade kohta, FPS ~8.8–9 mainitud möödaminnes, ilma testitabelita). See on suurim erinevus teiste tiimidega võrreldes.

---

## Mis on olemas (tugevused)

| Valdkond | Tõend | Hinnang |
|---|---|---|
| Töötav robot | `media/Baruto_first_ride.mp4`, `Baruto_Narva_ride.mp4` | ✅ Demonstreeritud |
| Püsivara | `Pico.ino` (997 rida) + `M12cam.ino` (1940 rida) | ✅ Mahukas, tõsine töö |
| 3 juhtimisrežiimi | manual / auto_demo / agent — koodis reaalselt implementeeritud | ✅ Vastab README väidetele |
| REST API | `/api/state`, `/api/camera`, `/api/tof`, `/api/drive`, `/api/mode` jne | ✅ Olemas koodis |
| Blob-tuvastus | M12 kaamera UART → Pico, värvipõhine | ✅ Töötab (media pildid) |
| Pinout | `docs/pinout.md` — täielik, värvikoodidega | ✅ Väga korralik |
| BOM | `assembly_guide_and_BOM.md` — hinnad + lingid, kokku 82,10 € | ✅ Korralik |
| Kokkupanekujuhend | sammud + filamentkulu (99,98 g) | ✅ Hea |
| CAD / 3D | Fusion `.f3d/.f3z` + STL-id (kere, rattad, roomikud, kaamerahoidja) | ✅ Olemas + muudetav |
| Optimeerimisanalüüs | `optimeerimine.md` — RGB565, LUT, bbox-tracking | ⚠️ Hea sisu, aga **kvalitatiivne, mõõtmisteta** |

---

## Kategooriate võrdlus AtomSumo traceriga

| Kategooria (AtomSumo nõuetest) | RAR-Tartu staatus |
|---|---|
| Projekti kontseptsioon + arhitektuur | ✅ README + lahenduse ülevaade |
| Funktsionaalsed nõuded + eesmärgid | ✅ 5 eesmärki loetletud |
| Juhtahel brauser → mootorid | ✅ Veebiliides + PWM/DIR |
| Wi-Fi + veebiserver | ✅ WebServer koodis |
| Manuaalsed liikumiskäsud | ✅ Manual mode |
| **Kiirus/triiv/pööre mõõtmised** | ❌ **Puuduvad mõõtmised** |
| **Latentsuse mõõtmine** | ❌ Puudub |
| ToF integratsioon | ✅ VL53L1X koodis + pinout; ⚠️ täpsust ei mõõdetud |
| Kaamerastriim / blob | ✅ Töötab; ⚠️ jõudlust (FPS) pole süstemaatiliselt mõõdetud |
| **PCB tõend** | ❌ Puudub (mooduli+Dupont lahendus, oma PCB-d pole) |
| **Toite robustsus (brownout)** | ❌ Pole testitud |
| Autonoomne käitumine | ✅ auto_demo režiim olemas; ⚠️ käitumist pole mõõdetud/logitud |
| Kaamera kalibratsioon | ❌ Pole (kvalitatiivne tuning) |
| CAD-pakett | ✅ Fusion + STL |
| Kokkupanekujuhend + BOM | ✅ Olemas |
| **Integreeritud mõõtmisanalüüs** | ❌ **Puudub** |

---

## Hinnanguline kokkuvõte

**Tugevused:** päriselt töötav robot, mahukas ja struktureeritud püsivara, kolm reaalselt implementeeritud juhtimisrežiimi koos REST API-ga, korralik pinout/BOM/kokkupanek, muudetav CAD. Insenertöö **toote** mõõde on tugev.

**Peamine nõrkus (hindamise mõttes):** projekt ei näita **mõõtmis- ja analüüsioskust**, mis on selle aine verstapostide tuum. Puuduvad:
- verstapostideks jaotatud esitus ja jälgitavus;
- igasugused kvantifitseeritud testid (kiirus, latentsus, ToF täpsus, aku tööaeg, toite robustsus);
- teooria-vs-mõõdetud võrdlused;
- kalibratsioon mõõdetud tõenditega.

`optimeerimine.md` näitab head tehnilist arusaama, kuid jääb hüpoteeside tasemele — ükski väide pole mõõtmisega kinnitatud.

**Soovitus:** kui hindamine nõuab mõõdetud teste (nagu teistelt tiimidelt nõuti), siis siin on see mõõde puudu, kuigi toode ise on valmis ja töötab. Kaaluda, kas paluda tiimil esitada vähemalt paar reaalset mõõtmist (nt mootori kiirus, ToF täpsus, kaamera FPS) — need oleksid olemasoleva riistvaraga kiiresti tehtavad.

---

## Lahtised punktid

| Teema | Mida vaja |
|---|---|
| Verstapostide struktuur | jaotada töö verstapostideks / esitada jälgitavus |
| Liikumismõõtmised | kiirus/triiv/pööre testitabel |
| Latentsus | veebiliides → mootor RTT mõõtmine |
| ToF täpsus | mõõdetud vs reaalne kaugus |
| Kaamera jõudlus | FPS-testitabel (optimeerimisväidete kinnituseks) |
| Toide / aku | tööaeg + brownout-test |

## Koondhinne

| Mõõde | Punktid / hinne | Kommentaar |
|---|---|---|
| Toode / funktsionaalsus |  | töötav robot, firmware, 3 režiimi |
| Dokumentatsioon |  | pinout, BOM, kokkupanek, CAD |
| Mõõtmised / analüüs |  | ⚠️ suuresti puudu |
| **Kokku** |  |  |

**Märkmed:**
<!-- kirjuta siia -->

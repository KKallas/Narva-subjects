# NarBot — Hindamisprotokoll (NarBot-main 2)

**Hindaja:** Kaspar Kallas
**Kuupäev:** _______________
**Versioon:** NarBot-main 2 (uuendatud esitus — asendab NarBot-main hinnangut)

**Kriteeriumid (per verstapost, 5×4 = 20 p):** Tööfailid · Analüüs · Prototüüp · Dokumentatsioon · Küsimused-vastused
**Hindamispõhimõte:** demonstreeritud võimekus + lõpp-vastamine (hindaja on meeskonda töötamas näinud; dokumentatsioon jääb tegelikust tööst maha — V2 PCB tarne venis, V3 on käimas).

---

## Kontekst (oluline õigluse jaoks)

Meeskond on **aktiivselt V3 kallal** ja tegi vahepeal **V2 PCB**, mille tarne võttis kauem aega. Seetõttu jääb kirjalik dokumentatsioon (analüüsi-notebookid, kalibratsiooninumbrid) **tahtlikult ajutiselt maha** — mitmed mõõtmised nõuavad kokkupandud robotit, mis on alles teel. Hindaja on alamsüsteeme **ise töötamas näinud**, seega hinne peegeldab demonstreeritud võimekust, mitte ainult esitatud paberit. Lõpp-vastamine kinnitab arusaamise (kasutatakse motivatsiooni ja töötahte hoidmiseks).

---

## Mis on NarBot-main 2-s juurde tulnud (vs esimene esitus)

| Uus moodul | Sisu | Staatus |
|---|---|---|
| `xiao_click_go/` | Klõpsa-ja-sõida: FrontCam UI + homograafia (piksel → maapind → HTTP → mootor) | ✅ Implementeeritud, kalibreerimine ootab robotit |
| `qr_reader_xiao/` | QR-lugemine (jsQR brauseris), mootori-API, kaugusandur, klõps-sõida HTTP API | ✅ Implementeeritud (QR oli V1-s "tulevane töö") |
| `phone_server/` | Flask telefoni-server (browser → Flask → ESP32), **ühiktestidega** | ✅ Implementeeritud |
| `docs/` | requirements, software_architecture, hardware_interfaces, arena_specification, reference_projects | ✅ Struktureeritud dokumentatsioon |
| Arhitektuuri areng | UART-link maha, kaks XIAO-d WiFi kaudu (FrontCam AP 192.168.4.1 + QR reader 192.168.4.2) | ✅ |

---

## VP1 — Süsteemispetsifikatsioon

Muutumatu ja endiselt **kolme tiimi tugevaim spec**: MoSCoW nõuded (FN-001…015), jõudlustabel mõõtmismeetoditega, riskianalüüs, teostatavusarvutus (moment T=0,206 Nm → mootorile 0,103, N20 1:50 annab 0,12–0,18 → piisav), testimisplaan, BOM.

**Hinnang:** faasikohaselt täielik.

**Märkmed:**
<!-- kirjuta siia -->


---

## VP2 — Võtmetehnoloogia prototüüp (rubriigi järgi)

| Kategooria | Punktid | Tõend / põhjendus |
|---|---|---|
| Tööfailid | **4/4** | Firmware kolmele osale (FrontCam `xiao_click_go`, `qr_reader_xiao`, `phone_server` testidega) + **KiCad V2 PCB** + CAD + `docs/`. Tugevaim koodibaas kolmest |
| Analüüs | **3/4** | ⚠️ `analysis/*.ipynb` on tühjad tüved, `test_plan.md` tühi. **Aga** VP1-s on momendiarvutus, ja võimekus on demonstreeritud → krediteeri lõpp-vastamisel (lase öelda mõõdetud latentsus/ToF/FPS) |
| Prototüüp | **4/4** | Klõpsa-sõida + QR-lugemine + telefoniserver + kaks kaamerat + kaugus/värviandurid + manuaal/klõps-API. Hindaja näinud töötamas |
| Dokumentatsioon | **3/4** | `docs/` jaotus korralik, moodulite README-d + CALIBRATION juhend. Puudu: `test_plan.md` täidetud, V1-vs-mõõdetud silmuse sulgemine (ootab robotit) |
| Küsimused-vastused | **4/4** | Vastavad hästi, motiveeritud (hindaja hinnang) |
| **Kokku** | **18/20** | |

---

## Lõpp-vastamise tingimus (et 3/4 analüüsis oleks kaitstav)

Et "Analüüs 3/4" oleks **dokumenteeritud, mitte ainult usaldus**, kata vastamisel konkreetsed numbrid (need on neil olemasoleva riistvaraga peas/logides):
- mõõdetud **side latentsus** (keskmine + max)
- **ToF täpsus** paaril kaugusel (nt 10/50/100 cm)
- **kaamera FPS** voogedastusel
- **klõpsa-sõida** viga (kui robot kokku pandud) või kalibratsiooni plaan

Kui need numbrid tulevad suuliselt → 3/4 on kaetud. Kui jõuavad ka notebookidesse (V3) → tõuseb 4/4.

---

## Lõpphinne

| Verstapost | Punktid | Kommentaar |
|---|---|---|
| VP1 (spetsifikatsioon) | __ / 20 | tugevaim spec kolmest |
| VP2 | **18 / 20** | vundament + prototüüp tugevad; analüüsi-kirjapanek ootab V3/robotit |
| **Soovitatud** | | demonstreeritud võimekus + lõpp-vastamine |

**Edasine (õpilase enda tasemele lõpetamiseks, ei mõjuta tänast hinnet):**
- Täida `analysis/motor_torque.ipynb` ja `power_budget.ipynb` reaalsete numbritega
- Mõõda ja täida `docs/test_plan.md` (latentsus, ToF, FPS, värv, tõuge)
- Kalibreeri klõpsa-sõida homograafia (`CALIBRATION.md`) kokkupandud robotiga → `enabled: true`

**Märkmed:**
<!-- kirjuta siia -->

## Prototüüpimine: Verstapost 4 — Korpusega funktsionaalne prototüüp

**Maht:** 16 tundi | **Hindamine:** 20 punkti | **Meeskonnatöö:** 4-liikmelised meeskonnad

### Mida teete

Võtate V3 korpuse ja teete selle matšivalmiks: testite vastupidavust, tugevdate nõrgad kohad konkreetsete poldi-mutri kinnitustega. Lisate roverile "ON KOHAL" tagasiside, mis ütleb operaatorile, kas tema rover on punase ala peal. Lisate kolm autonoomsuse astet — manuaalsest klõpsamisest kuni Claude Code'i (vms) agendini, mis ise leiab punase ala ja sõidab sinna.

**Mängu reeglid:** 90 sek, mõlema meeskonna roverid alustavad oma seina äärest, võidab see meeskond, kelle rovereid on lõpus rohkem punase ala peal (≥ 70% kattumine).

**V3 korpuse hindamine ja tugevdamine** — neli konkreetset testi olemasolevale korpusele:

- A: mootori kuumustest (5 min täisgaasil, kontroll deformatsiooni)
- B: korduv kokkupõrketest seinaga (3–5× sama korpus, kumulatiivne kahju)
- C: aku vahetuse aja test algajalt operaatorilt (< 30 sek)
- D: komponentide eemaldatavus silumiseks (andur < 2 min, arvutusplatvorm < 1 min, mootor < 5 min)

Iga vea kohta otsus: lihtne lahtilastus → Loctite; korduv lahtilastus → poldi-mutri kinnitus (polt läbi PLA, mutter peal surub kihte kokku); plastiku murd → disainimuutus. V4 lõpus on sul "enne-pärast" võrdlustabel: kus oled aega kulutanud ja kui palju see tasus.

**Operaatori tagasiside "ON KOHAL"** — rover ise reaalajas otsustab, kas ta on punasel alal (≥ 70% põhjast lataka peal), ja kuvab operaatorile suure indikaatori. Kolm varianti, kasvavas keerukuses:

- A: üksik andur + kindluse skoor + stabiilsuse filter (V3 baas)
- B: 2–4 andurit roveri põhja peal, "70% nõustub" reegel
- C: allavaatav kaamera roveril, pildi pindala mõõtmine

**Autonoomsuse astmed roveri poolel** — operaator valib veebiliideses:

- **Aste 1 (manuaalne):** V3 klõpsa-ja-sõida esikaameralt
- **Aste 2 (autopilot):** "Leia punane" nupp; tarkvara leiab pildi suurima punase piirkonna ja klõpsab ise
- **Aste 3 (olemasolev agent):** Claude Code (vms) töötab läbi puhta tööriistakomplekti — `rover_camera`, `rover_status`, `rover_rotate`, `rover_drive`, `rover_click`, `rover_stop`. Sinu töö pole agendi ehitamine, vaid lihtsa ja selge API disain.

**Mängu kontekst** — ülevaate kaamera, ametlik skoor ja matši-protokoll ehitatakse eraldi V4-st välja. V4-s testid teed taimeriga ja paberile prinditud punase alaga; rover peab olema valmis kohtuniku "start"/"stop" käske kuulama ja matši-välistel hetkedel ainult ettevalmistuse käske vastu võtma.

### Analüüsid (Jupyter Lab)

Kolm analüüsi Jupyter notebooks:

1. **Operaatori-tagasiside täpsus** — paigutad roveri ise teadlikult lataka keskele, servale, paljale areenile. Loed 30 sek näite ja võrdled, kas indikaator vastab oodatule. Keskel ~100 %, serval ~0 %, paljal areenil 0 %.
2. **Autonoomsuse astmete võrdlus** — sama ülesanne (sõida punasele alale) kolme astme kaupa, 5 katset igaüks. Mõõda edukus, aeg, operaatori klõpsude arv, valed sammud. Kus iga aste sobib, kus kukub?
3. **Süsteemi usaldusväärsus 10 matši jooksul** — **diagnostika**, mitte pass/fail nõue. Sõida 10 järjestikust 90-sek matši, logi tarkvarast vead (WiFi katkestused, kaotatud käsud, anduri ebastabiilsus, agendi vead). Eesmärk pole nullini jõuda, vaid teada, kus süsteem aja jooksul nõrgaks läheb.

### Kaitsmiseks on vaja

**Ainult git repositooriumi link.** Repos peab olema:

- Töötav kood (vähemalt kaks autonoomsuse astet töötavad, kolmas on dokumenteeritud isegi kui katki)
- Tööriistakomplekti (Aste 3 jaoks) API-dokumentatsioon, et keegi võõras saaks Claude Code'iga su roveriga rääkima
- Analüüside Jupyter notebooks koos mõõteandmetega (CSV)
- Uuendatud spetsifikatsioon + **enne-pärast tabel** korpuse tugevdustest
- STL-id koos prindiseadetega tugevdatud korpusest
- Fotod ja videod korpusest ning testidest

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — kood repos, STL-id, fotod/videod | 4 p |
| Analüüs — 3 Jupyter notebooki | 4 p |
| Prototüüp — PLA korpus poldikinnitustega, vähemalt 2 autonoomsuse astet töötavad | 4 p |
| Dokumentatsioon — spetsifikatsiooni uuendus + Aste 3 API dokumentatsioon | 4 p |
| Küsimuste-vastuste sessioon — demo + arutelu astmete üle | 4 p |
| **Kokku** | **20 p** |

### Täielik tööleht

📎 *Lisa siia link täielikule töölehele*

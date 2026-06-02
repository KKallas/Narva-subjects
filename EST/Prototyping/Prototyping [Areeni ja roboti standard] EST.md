# Areeni ja roboti standardformaat

Selles dokumendis on kokku pandud kogu projekti **kokkulepitud standardformaat** — areeni füüsiline kirjeldus, navigatsiooni-abivahendid, mängu reeglid ja roboti piirangud. Iga meeskond ehitab oma rovveri selle spetsifikatsiooni järgi.

---

## 1. Areeni füüsiline kirjeldus

| Parameeter | Väärtus |
|:---|:---|
| Areeni kogumõõtmed | 3000 × 3000 mm (3 × 3 m) |
| Mooduli suurus | 1000 × 1000 mm (1 × 1 m), kokku 9 moodulit (3 × 3 paigutuses) |
| Augu samm võrgustikus | 100 mm (10 × 10 võrgustik mooduli kohta) |
| Augu läbimõõt | 5 mm |
| Augu sügavus | 5 mm |
| Pinna materjal | OSB (puit) |
| Seina kõrgus | 100 mm |
| Seina kinnitus | Areeni välimised augud |

**Vastasseinad:** kaks vastasseina on kokku leppides märgitud **punase** ja **sinise** värviga. Need on globaalsed referentsid — kumb meeskond alustab kumma seina äärest, otsustatakse iga matši alguses.

**Pind:** moodulite augud (10 × 10 cm võrgustik, 5 mm läbimõõdus) mahutavad 3D-prinditud punne. Punnid kannavad värvilisi plönne ja muid abivahendeid (vt sektsioon 2).

---

## 2. Standardvarustus — navigatsiooniabi

Areenil on **kolm tasandit navigatsiooniabi**, mis on kõikidele meeskondadele kättesaadavad. Iga meeskond valib, milliseid kasutab.

**Need on arhitektuuriliselt valmis seatud abivahendid, mitte ainsad lubatud meetodid.** Meeskond võib kasutada ka muid asukoha-tuvastamise lahendusi — UWB, magnetkompass + dead reckoning, optiline flow, omaehitatud lahendus vms.

### Tasand 1 — ArUco markerid laes *(ruudu-täpsus, soovituslik baas)*

**9 markerit** sõnaraamatust `DICT_4X4_50`, igaüks **20 × 20 cm**, paigaldatud iga 1×1 m OSB mooduli **keskele** umbes **2 m kõrgusele lakke**.

Standardpaigutus chess-laadse notatsiooniga (vaade ülevalt):

```
        Sinine pool
   ┌──────┬──────┬──────┐
   │  A3  │  B3  │  C3  │
   ├──────┼──────┼──────┤
   │  A2  │  B2  │  C2  │
   ├──────┼──────┼──────┤
   │  A1  │  B1  │  C1  │
   └──────┴──────┴──────┘
        Punane pool
```

ArUco ID-d:

| Ruut | ArUco ID | Ruut | ArUco ID | Ruut | ArUco ID |
|:---|:---|:---|:---|:---|:---|
| A1 | 0 | B1 | 1 | C1 | 2 |
| A2 | 3 | B2 | 4 | C2 | 5 |
| A3 | 6 | B3 | 7 | C3 | 8 |

**Markerite "ülemine" külg suunatud sinise poole** — kõik 9 markerit on laes ühte suunda paigutatud. See annab rovverile globaalse suuna referentsi.

**Suurus 20×20 cm — kuidas saadi:** ArUco minimaalne dekodeeritav suurus 30 px serva kohta + 2 m kõrgus + 60° FOV kaamera (640 px) → minimaalne 11 cm, ohutuks lugemiseks topelt 20 cm (mahub A4 lehele).

### Tasand 2 — Värvitäpid põrandavõrgustikul *(täpsem, kasutab värviandurit)*

3D-prinditud värvilised punnid (≤ 2 mm kõrgus, ei takista roveri sõitu):

| Asukoht | Värv | Mitu kokku | Tähendus |
|:---|:---|:---|:---|
| Iga mooduli **keskpunkt** | **Sinine** | 9 | Mooduli keskpunkti referents |
| Iga mooduli **4 nurka** | **Kollane** | 9 × 4 = 36 | Mooduli nurga referents (jagatud nurkades tekib klaster) |
| Areeni keskpunkt (B2 keskel) | **Roheline** | 1 | Globaalne origin (0, 0) |

**Värvi-paleti loogika:**

| Värv | Tähendus | RGB-andur |
|:---|:---|:---|
| Sinine | Mooduli keskpunkt | Kõrge B kanal |
| Kollane | Mooduli nurk | Kõrge R + G |
| Roheline | Origin (B2 keskel) | Kõrge G |
| Punane | Mängu markeritud ala (vt sektsioon 3) | Kõrge R |

**Punased alad ja värvitäpid:** kui punast ala paigutatakse värvitäpi peale, **lõigatakse selle koha peale auk**. Värvitäpid jäävad alati nähtavale.

### Tasand 3 — Magnetid põrandavõrgustikus *(väga täpne, valikuline)*

**NdFeB magnetid** (5 mm läbimõõdus × 2 mm paksusega kettad, käivad auku 5 mm sügav).

Standard paigutus (sama, mis värvitäppidel — samad augud):

- Iga mooduli **keskpunkt** — 9 magnetit
- Iga mooduli **4 nurka** — 9 × 4 = 36 magnetit

**Eelis:** magnetid asuvad põranda sisus, Hall-andur loeb need ka läbi punaste alade — pole vaja punasesse alasse magneti jaoks auku lõigata.

---

## 3. Mängu reeglid

| Parameeter | Väärtus |
|:---|:---|
| Matši kestus | 90 sekundit |
| Meeskondade arv | 2 (punane ja sinine pool) |
| Roverite arv meeskonnas | Otsustatakse meeskonnasiseselt (üks rover = üks operaator) |
| Algasend | Iga meeskonna roverid oma seina ääres |
| Eesmärk | Saada lõpus rohkem rovereid punaste markeritud alade peal kui vastasel |
| Skoorimise lävi | Rover loetakse alal, kui ≥ 70% tema põhjast on alal |
| Ametliku skoori allikas | Mängujuht ülevaate kaameralt |

**Mängualad:**

- Areenile paigaldatakse iga matši alguses **punast värvi markeritud alad** (paberist, kileest või sarnasest materjalist)
- Alad ei tohi takistada roveri sõitu (peavad olema tasased pinnal)
- Kui ala kataks navigatsiooni-värvitäpi, **lõigatakse sinna auk** (täpid jäävad nähtavale)
- Alad võivad olla erineva kuju ja paigutusega — täpsustatakse iga matši alguses

**Matši kulg:**

1. **Algasend (enne starti):** roverid joondatud oma seina äärde manuaalrežiimis, kohtunik kinnitab algasendi, skoor 0/0
2. **Start:** kohtunik annab märguande, kell käivitub (90 sek taandarv)
3. **Mängu kestel:** operaatorid liigutavad oma rovereid; mängujuht loeb skoori ülevaate kaameralt
4. **Lõpp (0:00):** server lukustab skoori, saadab kõigile roveritele "stop"-käsu, kuvab tulemuse

**Skoori autoriteet:**

- **Ametlik skoor** = mängujuhi loendus ülevaate kaameralt (70% katte reegel)
- **Roveri enda "ON KOHAL" indikaator** = ainult operaatori UX-tagasiside, mitte ametlik skoor
- Kui need lähevad lahku → kalibratsiooni-probleem või vaidlusalune piirisituatsioon (kohtunik otsustab video pealt)

---

## 4. Roboti piirangud ja nõuded

### Mehaanika

| Parameeter | Nõue |
|:---|:---|
| Maksimaalne kaal | ~1 kg (soovituslik) |
| Maapind clearance | ≥ 5 mm (areeni plönnid on kuni 2 mm kõrgemad) |
| Kõrgus | Piirang puudub, aga märgis ülapinnal peab olema nähtav ülevaate kaameralt |
| Korpuse materjal | Vaba (PLA, PETG, vineer, papp — meeskonna valik) |
| Mehaaniline vastupidavus | Peab kestma vähemalt 5 järjestikust kokkupõrget seinaga V4 testide järgi |

### Toide

- **Aku** roveril (LiPo, USB powerbank, telefoni sisemine aku vms)
- **Aku vahetuse aeg** matšide vahel: ≤ 30 sek algajalt operaatorilt
- Toitelüliti või selge sisselülitamine

### Andurid (soovituslikud, mitte kõik kohustuslikud)

| Andur | Otstarve | Kohustuslik? |
|:---|:---|:---|
| Esikaamera | Navigatsioon klõpsa-ja-sõida loogikaga | Jah |
| Värviandur (alt) | "ON KOHAL" tagasiside (V4 sektsioon 2) | Jah |
| Ülevaate kaamera (üles) | ArUco markerite lugemine laes (V5) | Soovituslik |
| Hall-andur (alt) | Magnetite lugemine põrandavõrgustikus | Valikuline |
| Kaugusandur | Kokkupõrgete vältimine | Valikuline |

### Liides ja side

- **WiFi** ühendus operaatori sülearvuti ja roveri vahel
- **Roveri server** veebiliidesega (Python + FastAPI, ESP32 web server vms)
- **Operaatoriliides** peab näitama vähemalt:
  - Esikaamera reaalajavoogu
  - Klõpsa-ja-sõida võimaluse pildi peal
  - Roveri enda anduri olekut ("ON KOHAL" indikaator)
  - Aku oleku näitajat
- **Stop-käsule peab rover reageerima koheselt — igal ajal** (turvameede)

### Visuaalne tuvastus ülevaate kaamera jaoks

- **Meeskonna märgis ülapinnal** — selge kontrast, hästi nähtav ülevaate kaameralt
- **Väldi punast meeskonna värvi** — see ajab segadusse markeritud aladega
- Meeskonna värvid: soovituslikult sinine vs kollane (kõrge kontrast)
- Märgis peab olema nähtav ka rovveri kummuli olles (et kohtunik saaks tuvastada)

---

## 5. Operaatori ja info-mulli reeglid

**Info-mulli põhimõte:** rover ja operaator töötavad matši ajal **ainult roveri enda andurite infoga**. See on tahtlik piir — kui operaator näeks ülevalt vaate kaamerat, oleks see petturlik abi.

**Operaator näeb:**

- Oma roveri esikaamera reaalajavoo
- Oma roveri enda anduri olekut ("ON KOHAL" indikaator)
- Kogu meeskonna ühisskoori (number)

**Operaator EI näe:**

- Ülevaate kaamera vaadet — ei pildina, ei kaardina, ei skooripaneelil
- Millise rover skoorib (ainult ühisskoor)
- Vastase roveri esikaamera vaadet

**Mängujuht näeb (eraldi liidesest):**

- Ülevaate kaamera reaalajavoo
- Ametliku skoori (rover ↔ ala kattumiste loendus)
- Mõlema meeskonna olek
- Vajadusel: võrdleb ametlikku skoori roveri enda deklaratsiooniga

---

## 6. Matši-oleku reegel (matš ON / OFF)

Rover ja operaator hoiavad arvet matši olekust. Sõltuvalt olekust on lubatud erinevad käsud:

| Olek | Lubatud käsud |
|:---|:---|
| **Matš ON** (kohtunik andis "start", kell jookseb) | Kõik käsud — manuaalne klõps, autopiloot, agent |
| **Matš OFF** (enne starti, pärast stoppi) | **Ainult ettevalmistuse käsud** — manuaalne ühe-sammu liigutus, värvianduri kalibreerimine, kaamera test. Autonoomsed režiimid ei tööta. |

**Kaks turvakihti (defense in depth):**

1. **Operaatori liides** ei lase mängu-režiimi käske saata enne starti (nupud grayed-out)
2. **Rover ise** kontrollib matši olekut ja **ignoreerib** mittevastavad käsud, mis matšiväliselt jõuavad — kui üks kiht jätab vea sisse, peatab teine

**Stop-käsule peab rover reageerima koheselt — igal ajal**, sõltumata matši olekust (füüsiline turvameede).

---

## 7. Autonoomsuse astmed (kokkulepe operaatori liideses)

Operaator valib oma juhtimisliideses ühe kolmest autonoomsuse astmest:

| Aste | Mis töötab | Kes otsustab |
|:---|:---|:---|
| **1 — Manuaalne** | Operaator klõpsab pildil, V3 raycast viib rovveri sinna | Operaator |
| **2 — Autopilot** | Operaator vajutab "Leia punane", tarkvara filtreerib pildi värvi ja klõpsab ise | Tarkvara, operaator vaatab kõrvalt |
| **3 — Agent** | Operaator annab kõrgetasemelise eesmärgi, Claude Code (vms) kasutab roveri tööriistakomplekti (rover_camera, rover_status, rover_rotate, rover_drive, rover_click, rover_stop) | Agent, operaator sekkub kui vaja |

Astme vahetamine on kohene ja turvaline — keset agendi tegevust manuaaliks lülitamisel rover peatub ohutult.

---

## 8. Kokkuvõte — mida iga meeskond ehitab

- Rover, mis sõidab oma esikaameravoo klõpsust (V3 baas)
- Korpus, mis kestab vähemalt 5 kokkupõrget (V4 vastupidavus)
- Värviandur ja "ON KOHAL" indikaator (V4 sektsioon 2)
- Vähemalt 2 autonoomsuse astet 3-st (V4 sektsioon 3)
- Ülespoole vaatav kaamera ArUco lugemiseks (V5 standardvarustus tasand 1)
- Selge meeskonna märgis ülapinnal
- WiFi-ühendus, operaatori liides, stop-käsk koheselt
- Matš-oleku reegel sisse ehitatud (ON/OFF, defense in depth)

Lisaks valikulised:
- Allavaatav kaamera (V4 sektsioon 2 variant C)
- Hall-andur magnetite lugemiseks (V5 standardvarustus tasand 3)
- Kaugusandur kokkupõrgete vältimiseks

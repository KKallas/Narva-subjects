## Üldinfo
### Eesmärgid
Kursuse eesmärk on anda tudengitele arusaam 3D modelleerimise ja tootmise terviklikust töövoost. Alustades polügoonmodelleerimisega (Blender) mõistmaks miks solid-modelleerimine (Fusion 360) on inseneritööks vajalik, liikudes edasi FDM printimise füüsika, orientatsiooni optimeerimise, konstruktsiooniliste kinnituste ja tootmisdokumentatsioonini. Akadeemiline tuum on **tootmise geomeetria ja optimeerimise teooria**: printimisaja arvutamine kihtide ristlõigete integreerimisena, orientatsiooni mõju tugevusele (kihtide adhesioonimudel), overhang füüsika (45° reegel kui geomeetriline piir), ja polt-mutter kompressioon kui armatuurbetooni analoogia (metall tõmbel, plast survel). Iga detail mis lauale klõpsub, robotile kinnitub või elektroonikat hoiab — see tuleb siit ainest.

### Õpiväljundid
Õppeaine läbinud õppija:
- modelleerib lihtsa objekti Blenderis ja selgitab miks polügoon-mesh tekitab probleeme teel printerini (avatud servad, valed normaalid, non-manifold geomeetria);
- selgitab miks Fusion 360 solid-modelleerimine väldib neid probleeme ja miks piirangupõhine disain on tootmise jaoks parem kui vaba vormimine;
- selgitab FDM printimise füüsikat: 45° overhang reegel, sirge vs. kõver joone mõju printimisajale, orientatsiooni mõju tugevusele (kihtide vaheline adhesioon);
- arvutab printimisaja kihtide ristlõigete integreerimisena ja optimeerib orientatsiooni kiiruse, tugevuse ja tugimaterjali kulu järgi;
- disainib snap-fit kinnitusi ja rakendab polt-mutter-seib kompressiooni FDM detailide tugevdamiseks (armatuurbetooni analoogia);
- rakendab print-pause töövoogu metallsisestuste (mutrid, magnetid) paigaldamiseks;
- analüüsib olemasolevat disaini ja parandab seda konkreetse mõõdiku kaupa (kiirus, tugevus või kestavus), võrreldes käsitsi inseneridisaini ja generatiivset disaini;
- koostab ISO tehnilise joonise GD&T-ga ja tellib metalldetaili CNC teenuselt;
- valideerib tellitud detaili mõõtmete vastavust joonisele.

### Sisu lühikirjeldus
Kursus alustab Blenderiga — tudeng teeb pliiatsi hoidiku MG400 tööriistaflantsile ja õpib kui raske on hoida mudelit vettpidavana kui töötad punktide ja polügoonidega. See annab intuitiivse arusaama milles Fusion 360 on hea: Fusionis on mudel alati solid, sest tööriist ei luba vigast geomeetriat luua. Edasi õpitakse FDM füüsikat (overhang, orientatsioon, sirge vs. kõver), konstruktsioonilisi kinnitusi (polt-mutter kompressioon kui armatuurbetooni analoogia) ja tootmisdokumentatsiooni (ISO joonised, CNC tellimine). Akadeemiline tuum: printimisaja arvutamine kihtide ristlõigete integreerimisena — orientatsiooni optimeerimine on matemaatiline, mitte esteetiline valik.

### Hindamine
Iseseisvate tööde loetelu ja juhised nende tegemiseks:

Hindamisstruktuur: 5 projekti × 20 punkti = max 100 punkti. Integratsiooniprojekt max 70 punkti (ideaalselt vormistatud = C hinne). Kokku võimalik 170 punkti, hinne arvutatakse parimast 100-st. Tudeng valib ise millised projektid teha — integratsiooniprojekti saab esitada iseseisvalt ja ülejäänud tööd lisada punktide parandamiseks.

Iga projekti neli hindamiskategooriat:
- Tööfailid (5p): Fusion 360 / Blender failid, STL, STEP ekspordid — kõik git repos (suured binaarfailid .gitignore + README-s link)
- Analüüs (5p): orientatsiooni võrdlus, tugevustest, printimisaja arvutus, Jupyter notebook
- Prototüüp (5p): töötav 3D prinditud detail
- Dokumentatsioon (5p): joonised, mõõtmete kontroll, kokkupanekujuhend

#### Ülesanne 1: Blenderist printerini — teekond ja komistuskohad
**Osa A — Blender**: teha pliiatsi hoidik MG400 tööriistaflantsile polügoonmodelleerimisega. Eksportida STL, avastada vead viilutajas (avatud servad, valed normaalid, non-manifold kohad). Mesh diagnostika: mis on kolmnurkvõrk, miks normaali suund on oluline. Parandada, printida, panna MG400 külge — robot joonistab esimesel päeval.
**Osa B — FDM füüsika**: sama hoidik, aga mõista miks printer käitub nii. Overhang ja 45° reegel (kihi kõrgus = kihi nihke = diagonaal). Sirge vs. ümmargune (otsiku kiirus, kiirendus/aeglustus). Orientatsioon ja tugevus (kihtide vaheline adhesioon on nõrgim koht). 4 orientatsiooni printida ja testida. Jupyter Lab: kihtide ristlõigete visualiseerimine, printimisaja matemaatiline arvutus.
**Osa C — Fusion 360**: sama pliiatsi hoidik parameetriliselt. Mõõdud nihkkaliibriga → parameetritena mudelisse. Eksport → viilutajas pole vigu. Prindi → ei logise, mõõdud klapivad.
**Osa D — Pliiatsist süstlaks**: asenda pliiats süstlaga Fusionis. Lisa pneumaatikaühendus. Testi 3 süstlamõõtu (5ml, 10ml, 20ml) — üks mudel, palju variante.

#### Ülesanne 2: Töölaua moodulid ja kinnitused
Disainida moodulid mis kinnituvad töölaua 5mm aukudesse (100mm ruudustik). Universaalne kinnitusjalg + spetsiifiline ülaosa (snap-fit). Polt-mutter-seib kompressioon: metall (polt) kannab tõmbekoormust, plast (PLA) kannab survet, seib jaotab jõu. Sama detail ilma ja läbipoldituna — tõmbetest MG400-ga, mõõta purunemiskoormust. Mehhaaniline simulatsioon (Fusion FEA). 2D joonis tootmisjuhendina.

#### Ülesanne 3: Elektroonika korpus ja print-pause
Integreeritud korpus ESP32 + op-amp plaadi jaoks. Integratsioonigraaf (draw.io), BOM. Print-pause töövoog: pausi print, sisesta mutrid/magnetid/sisestused, jätka. Kokkupanekujuhend mis on piisavalt selge et teine meeskond saab järgi teha.

#### Ülesanne 4: Olemasoleva disaini parandamine — kolm lähenemist
Õppejõu olemasolevad 3D prinditud + polditatud disainid (rõhutoru otsikud, solenoidi kinnitused, süstla otsikud) kui parandamise alus. Tudeng valib ühe ja parandab ühe konkreetse mõõdiku kaupa: (A) tootmiskiirus, (B) tugevus, (C) kasutuskordade arv. Käsitsi inseneridisain vs. Fusion 360 generatiivne disain. Prindida kõik 3 versiooni (algne + käsitsi + generatiivne), korratav test MG400-ga, võrdlustabel.

#### Ülesanne 5: ISO joonis ja CNC tellimine
Disainida metalldetail (töölaua kinnitusplaat, roboti alusplaat vms) ja tellida 2D CNC teenusena väljast. ISO tehniline joonis: vaated, lõiked, mõõtmed, tolerantsid, pinnakaredus, materjal. GD&T kriitiliste pindade jaoks. Tolerantsianalüüs: CNC detail (±0.1mm) + 3D prinditud sisestus (±0.3mm). Õppejõu ülevaatus enne tellimist. Valideerimine: kui detail kohale jõuab — mõõta nihkkaliibriga, kas vastab joonisele, kas 3D prinditud sisestus sobib.

#### Lisaülesanne: Täielik mehhaanikapakett
Kõik mehaanilised komponendid tootmisvalmis dokumentatsiooniga: süstlahoidik + andurimoodulid + elektroonika korpus + CNC detailid. Pakett mille järgi teine inimene saab süsteemi kokku panna.

### Kontakttundide ajakava
- **[~11.09.26]** Blender baas, mesh ja STL, polügoonid → kolmnurgad → vead
- **[~11.09.26]** Viilutaja, orientatsioon, esimene print — ja miks see ei ole ideaalne
- **[~02.10.26]** Ülesande 1 kaitsmine (Blender + Fusion + orientatsiooni analüüs)
- **[~02.10.26]** Fusion koostud, snap-fit, metallsisestused, polt-mutter kompressioon
- **[~23.10.26]** Ülesande 2 kaitsmine
- **[~23.10.26]** Print-pause, komponentide sisestamine, korpuse disain
- **[~13.11.26]** Ülesande 3 kaitsmine
- **[~13.11.26]** Generatiivne disain töövoog
- **[~04.12.26]** Ülesande 4 kaitsmine
- **[~04.12.26]** ISO joonised, GD&T, CNC kommunikatsioon
- **[~16.01.27]** Ülesande 5 kaitsmine (sisaldab ISO joonise ülevaatust → CNC tellimine kohe pärast)
- **[TBD]** Integratsiooniprojekti kaitsmine

### Lõpphindamisele pääsemise tingimused
Õppija on positiivsele tulemusele kaitsnud vähemalt ühe ülesande.

### Minimaalne punktide kogusumma lõpphindamisele pääsemiseks
51

### Lõpphindamise skaala
Eristav (A, B, C, D, E, F, mi)

### Lõpphinde kujunemine
5 projekti × 20 punkti = max 100 punkti. Integratsiooniprojekt max 70 punkti (ideaalselt vormistatud = C). Kokku võimalik 170 punkti, hinne arvutatakse parimast 100-st. Integratsiooniprojekti saab esitada iseseisvalt (piisab aine läbimiseks), ülejäänud tööd saab lisada hinde parandamiseks.

|   |   |
|---|---|
| A | 91 punkti |
| B | 81 punkti |
| C | 71 punkti |
| D | 61 punkti |
| E | 51 punkti |
| F | vähem kui 51 punkti |
| mi | Õppija ei ole ülesandeid esitanud ega lõpphindamisel osalenud |

### Võlgnevuste likvideerimine
Kokkuleppel vastutava õppejõuga

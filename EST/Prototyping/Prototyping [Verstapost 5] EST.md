## Prototüüpimine: Verstapost 5 — Tootmisvalmis süsteem

**Maht:** 14 tundi | **Hindamine:** 20 punkti | **Kohtumine: L 30.05**

V4 lõpus oli sul testitud korpus, mingil tasemel töötav autonoomsus (kuni nt. Claude Code'iga agenditasandini) ja kümme simuleeritud matši seljataga (taimeriga, paberile prinditud punase alaga — päris mängu infrastruktuur ehitatakse eraldi). V5 on viimane verstapost enne areeniüritust. Põhisõnum: **kui keegi teine saab sinu repo ja seda lugedes ehitab sama roveri, on V5 lõpetatud**.

V5-l on kolm paralleelset eesmärki:

1. **Viimistle oma rover lõplikuks** — V4 testidest tulnud nõrkused parandatud, dokumenteeritud, korduvalt üle testitud
2. **Lisa asukoha määramine** — areeni lakke paigaldatud ArUco markerid, et rover teaks mitte ainult "mis on ees", vaid ka "kus areenil ma olen". See annab autonoomsele agendile asukohaaegse mälu.
3. **Tee dokumentatsioon tiraaživalmis** — keegi kolmas peab samast repost saama sama roveri kokku panna ilma sinult küsimata

Pluss üks asi, mida sa terve semestri jooksul oled kogunud, aga pole veel kokku pannud: **V1–V4 mõõtmiste koondvaade**. Mis paranes? Mis halvenes? Mis jäi lahendamata? See on insener-projekti tõehetk — kas spetsifikatsioonis ette ennustatu sai päriselt täidetud?

Prioriteet on järjekorras: kõigepealt viimistlus (paranda kõik V4 tabelis "aktsepteeritav = ei" read). Siis asukoha määramine. Siis dokumentatsioon, mis on tõesti loetav võõrale. Lõpuks koondgraafik.

---

### 1. Viimistlus ja piirangute dokumentatsioon

**Eeldus:** V4 lõpus on sul tabel "enne / tugevdus / pärast / aktsepteeritav?". Iga rida — eriti need, kus aktsepteeritav = ei — on V5 sisendiks.

**Eesmärk:** V5 pole "paranda kõik" verstapost. See on **piirangute aus dokumentatsioon**. Iga V4-st järelejäänud puudus peab jõudma V5 lõppu kas (a) parandatuna ja uuesti testituna, või (b) selgelt kirjas kui **dokumenteeritud piirang** — siin on tehniline piir, mehaaniliselt me seda enam ei lahenda, jätame **tarkvarale, juhtimisloogikale või järgmise põlvkonna riistvarale**.

**Miks dokumenteerimine on sama oluline kui parandamine:**

Järgmised inimesed, kes su prototüübiga töötavad — tarkvaraarendaja, juhtimisloogika kirjutaja, järgmise versiooni ehitaja — peavad **teadma**, mis töötab ja mis ei tööta. Dokumenteeritud piirang on **lahendatav** ülemises kihis (filter koodis, käsitsi kalibreerimine, kompromiss strateegias). Peidetud piirang **hammustab** kasutajat ilma hoiatuseta.

Vaikne mahajätmine, kus rida aruandest lihtsalt kaob, ei ole mõistlik. Aga ka "ma pean kõik mehaaniliselt täiuslikuks lihvima" pole insener-vastutuse mõte. Tark insener teab, **kus tasub veel masinatöö pingutus**, ja kus on aeg piirang üles kirjutada ja anda see üle järgmisele kihile.

**V5 viimistlustabel näidis jätkub V4 tabeli sealt, kus see lõppes:**

| Komponent | V4 staatus | V5 otsus | Tulemus | Lõplik staatus |
|:---|:---|:---|:---|:---|
| Aku-pesa | Vahetus 35 sek (üle lävi) | Magnetkinnitus | Vahetus 22 sek | Lahendatud mehaaniliselt |
| Claude Code agent | Edukus 3/5 (jäi serva peal kinni) | `rover_stop` kinnitus + parem tööriistadokumentatsioon | Edukus 4/5 | Lahendatud tarkvaras |
| Värvianduri stabiilsus piiril | Kindlus 0,52 | Mehaaniliselt ei lahenda — andur on serval ebausaldusväärne, anduri parem paigutus ei muudaks oluliselt | Sama | **Dokumenteeritud piirang** — tarkvara filtreerib kindlus < 0,7 välja, operaator ei näe "ON KOHAL" |
| Mootori vibratsioon kiiremal kui 80% | Pole tagatud paigaldus | Polt-mutter konstruktsioon proovitud, kogu vibratsiooni ei saa elimineerida | Pisut parem | **Dokumenteeritud piirang** — tarkvara piirab max kiiruse 75% peale |
| ... | ... | ... | ... | ... |

**Sellist tabelit ootame ka võõralt lugejalt:** kui keegi avab repo, peab ta sellelt tabelilt aru saama, kas mingit V4 puudust on lahendatud, või kas peab arvestama dokumenteeritud piiranguga oma kasutuses.

**Pisi-asjad, mida V4 testid ei pruugi katta, aga matšil häirivad — ka need dokumenteeri:**

- Roveri sisselülitamise aeg (kui üle 10 sek, kas lihtsustatav või dokumenteerid "vajab käivitamiseks aega")
- Veebiliidese taasühendamine pärast WiFi katkestust (kas automaatne, või dokumenteeritud "operaator avab uuesti")
- Roveri seerianumber või meeskonna märgis on nähtav ka kummuli olles (kohtunik peab tuvastama)

**Põhimõte:** iga avastatud nõrkus saab kas lahenduse või rea dokumentatsioonis. Mõlemat me hindame võrdselt — sest mõlemad aitavad järgmistel inimestel teada, millise süsteemiga nad töötavad.

---

### 2. Asukoha määramine — areeni standardvarustus

**Eeldus:** roveri esikaamera töötab; V3 raycast pildi pealt põranda koordinaadiks töötab.

**Probleem:** seni teab rover oma asukohast nii vähe, kui ta esikaameralt näeb. See piirab autonoomsust — agent ei oska otsustada "olen juba kontrollinud vasakut poolt, lähen paremale", sest tal pole asukohaaegset mälu.

**Lahendus — areeni kokkulepitud standardformaat:**

Areenil on **kolm tasandit navigatsiooniabi**, mis kõik on kõikidele meeskondadele kättesaadavad. Iga meeskond valib, milliseid kasutab — odavaimast (ainult ArUco) kuni täpseima (kombineerib kõik kolm).

**Need on arhitektuuriliselt valmis seatud abivahendid, mitte ainsad lubatud meetodid.** Meeskond võib kasutada ka muid asukoha-tuvastamise lahendusi — UWB-positsioneerimine (Decawave/Qorvo), magnetkompass + dead reckoning, optiline flow alt kaamerast, omaehitatud lahendus vms. Standardformaat ei piira sind; see lihtsalt tagab, et **mingid abivahendid on alati olemas**, kui sa neid kasutada tahad.

---

#### Tasand 1 — ArUco markerid laes *(ruudu-täpsus, soovituslik baas)*

**9 markerit** DICT_4X4_50 sõnaraamatust, igaüks **20 × 20 cm** (mahub A4 lehele), paigaldatud iga 1×1 m OSB mooduli **keskele** umbes **2 m kõrgusele lakke**.

Standardpaigutus chess-laadse notatsiooniga (vaade ülevalt). **Areeni kaks vastasseina on kokku leppides märgitud punase ja sinise värviga** — kumb meeskond alustab kumma seina äärest, otsustatakse matšil:

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

ArUco ID-d vastavad ruutudele:

| Ruut | ArUco ID | Ruut | ArUco ID | Ruut | ArUco ID |
|:---|:---|:---|:---|:---|:---|
| A1 | 0 | B1 | 1 | C1 | 2 |
| A2 | 3 | B2 | 4 | C2 | 5 |
| A3 | 6 | B3 | 7 | C3 | 8 |

**Markerite "ülemine" külg on suunatud sinise poole** — kõik 9 markerit on laes ühte suunda paigutatud, sõltumata sellest, kummalt poolt rover neid loeb. See annab rovverile globaalse suuna referentsi (tunneb ära, kuhu "sinise poole" jääb).

**Suurus 20×20 cm — kuidas saadi:**

- Kaamera FOV ~60°, resolutsioon 640 px → 2 m kõrgusel nähtav ala 2,3 m lai → ~278 px/m
- ArUco dekodeerimine vajab vähemalt 30 px serva kohta → minimaalne marker = **11 cm**
- Ohutusvaruga (peegeldused, varjud, nurgad) topelt: **20 × 20 cm**

Kui sinu kaamera FOV või resolutsioon erineb, tee sama arvutus. Lagi madalam kui 2 m → võid markeri väiksemaks teha; kõrgem → peab suuremaks.

**Roveri pool:** rover vajab **ülespoole vaatavat kaamerat** — ainult see näeb laes asuvaid markereid. Kaks praktilist lahendust:

- **Eraldi kaamera lakkesuunas:** lisada teine M5-CAM (või lihtne USB-webcam), mille objektiiv on suunatud üles. See on lihtsam ja eraldab esikaameravoo ülevaatevoost.
- **Olemasoleva kaamera ümberorienteerimine:** kui rover juba kasutab M5-CAM-i autopilooti/agendi jaoks, võib selle ümber paigaldada üles ja navigeerida ainult värviandurite + ArUco abil. Esikaamera kaob, agent peab täielikult tuginema asukoha-mäluga + alt-anduritega.

Mõlemad on töökindlad — vali oma riistvara võimaluste järgi. Roveri server loeb ülespoole vaatava kaamera kaadri OpenCV `cv2.aruco` mooduliga, dekodeerib nähtava markeri ID, teab oma ruutu.

---

#### Tasand 2 — Värvitäpid põrandavõrgustikul *(täpsem, kasutab juba olemasolevat värviandurit)*

Põrand on puuritud **10×10 cm võrgustikuga** (5 mm augud). Standardseks navigatsiooniabiks paigaldatakse 3D-prinditud värvilised punnid (≤ 2 mm kõrgus, ei takista roveri sõitu).

| Asukoht | Värv | Mitu kokku | Tähendus |
|:---|:---|:---|:---|
| Iga mooduli **keskpunkt** | **Sinine** | 9 | Mooduli keskpunkti referents |
| Iga mooduli **4 nurka** | **Kollane** | 9 × 4 = 36 | Mooduli nurga referents (jagatud nurkades tekib klaster — naabermoodulid mõlemad märgivad sama füüsilist kohta) |
| Areeni keskpunkt (B2 keskel) | **Roheline** | 1 | Globaalne origin (0, 0) |

Värvid (sinine, kollane, roheline) on valitud nii, et need on **RGB-anduriga selgesti eristatavad** — igal on oma kanali domineerimine (S kõrge sinisel, R+G kõrge kollasel, G kõrge rohelisel). Lisaks **ei sega need punaste markeritud aladega**. Valge oleks RGB-anduriga raskelt eristatav heledast OSB-pinnast (mõlema kõik kolm kanalit kõrged), seetõttu valitakse roheline. Roveri värviandur(id) (V4 sektsioon 2) loevad neid, kui rover üle sõidab.

**Punased alad ja värvitäpid:** kui punast ala (paber/kile) paigutatakse värvitäpi peale, **lõigatakse selle koha peale auk**. Värvitäpid jäävad alati nähtavale — augud tehakse vastavalt vajadusele iga matši alguses, kui ala asend on teada.

**Kasu rovveri jaoks:** kui rover sõidab üle sinise täpi, ta teab "olen praegu mooduli B2 keskel" — palju täpsem kui ArUco "olen ruudus B2".

---

#### Tasand 3 — Magnetid põrandavõrgustikus *(väga täpne, valikuline)*

Igasse 10 cm auku võib paigaldada **NdFeB magneti** (5 mm läbimõõdus × 2 mm paksusega ketta — käib auku 5 mm sügav, ei takista roveri sõitu).

Standard magneti-paigutus (sama, mis värvitäppidel — magnetid asuvad samades aukudes):

- Iga **mooduli keskpunkt** — 9 magnetit
- Iga **mooduli 4 nurka** — 9 × 4 = 36 magnetit (jagatud nurkades võib auku panna ühe magneti, mis loeb mõlema mooduli jaoks; aga arvestuses 36)

Rover lisab põhja **Hall- või reed-anduri**. Kui rover üle magneti sõidab, andur registreerib täpse hetke. Annab millisekundi-täpse asukohaviite.

**Eelis:** magnetid asuvad **põranda sisus**, mitte peal — Hall-andur loeb need ka läbi mitte-magnetilise materjali, mistõttu pole vaja punastes aladesse auke lõigata magnetite jaoks (erinevalt värvitäppidest).

**Mitte kohustuslik** — kui meeskond eelistab värvitäppe või ainult ArUco-d, ei pea magneteid kasutama.

---

**Kombineerimine — mida valid:**

| Lähenemine | Riistvara lisa | Täpsus | Sobib kellele |
|:---|:---|:---|:---|
| Ainult ArUco | Pole (juba esikaamera) | Ruudu-täpsus (1 m) | Esmane versioon, vähim riski |
| ArUco + värvitäpid | Pole (juba värviandur) | ~5 cm täppide juures | Keskmine, kasutab olemasolevat |
| Kõik kolm | Hall-andur lisaks | ~1 cm magnetite juures | Maksimaalne täpsus; ei vaja punaste alade lõikamist täppide ümber |

**Soovitus:** alusta **ainult ArUco-ga**, lisa värvitäpid kui täpsust on vaja paremaks. Magnetid tee viimasena, kui ülejäänud juba töötavad.

**Teised lähenemised (õpiväärtuse jaoks):** UWB-positsioneerimine (Decawave/Qorvo), magnetkompass + dead reckoning, optiline flow alt kaamerast. Areeni standardformaat ei nõua neid, aga kui meeskond tahab katsetada — soovi korral.

---

**Roveri loogika:**

1. Iga ~1 sek (või sagedamini) loeb roveri server **ülespoole vaatava kaamera** kaadri ArUco dekoodriga
2. Tunneb nähtava markeri ID → teab oma ruutu
3. Kui üle värvitäpi sõidab, alt-vaatav värviandur registreerib → täpsem positsioon
4. Kui alt-vaatav Hall-andur reageerib magnetile → kõige täpsem positsioon

Need on **loomulik täiendus V3 raycastile**: raycast annab täpse koordinaadi *ette nähtavate* objektide jaoks; areeni standardvarustus annab koordinaadi, kus rover *ise* areenil asub.

**Kasutusalad V5-s:**

- **V4 Aste 3 (Claude Code agent)** saab asukoha-mälu: "Olen olnud ruutudes A1, A2 ja B2 — proovi nüüd C-rida"
- **Operaatoriliideses kuva** väike 3×3 ruudustik koos punktiga, mis ruudus rover praegu on
- **Hilisemas tõestuses** võib mängujuht võrrelda: kui rover ütleb "olen ruudus B2", aga ülevaate kaamera (kui valmis) näeb teda C3 → kalibratsiooni-probleem

**Kalibreerimise kontroll:**

1. Pane rover B2 keskele (areeni keskpunkt). Kas tarkvara ütleb "B2"? Kas värviandur näeb sinist täppi?
2. Pane rover A1 keskele. Kas tarkvara ütleb "A1"?
3. Pane rover A1 ja B1 piirile. Kas tarkvara annab mõistliku vastuse ("A1 või B1, kindlust pole täielikult") või jääb pidama?

**Tüüpilised probleemid:**

- **Markerid liiga väikesed** → ei loeta. Kontrolli enne printimist: marker px laius kaameras × kaugus / kaamera FOV ≥ 30 px.
- **Lambivalgus peegeldub markeris** → kileeri matil pinnal, mitte läikival.
- **Kahe markeri vaheline üleminek** → mitu sekundit "ei näe ühtegi". See on okei — rover teab, et on kahe vahel, ja võib otsustada eelmise positsiooni põhjal.
- **Värvitäpid hägused** → andurit puhasta, valgustust kontrolli; kollase ja sinise erinevus peab jääma kindel.
- **Magnetid liiga nõrgad** → kasuta tugevamaid NdFeB-sid (N42 või kõrgem), Hall-andur tundlikum suurematest magnetitest.

**YouTube/AI otsisõnad:**

- `OpenCV ArUco marker detection tutorial`
- `ceiling marker robot localization`
- `aruco DICT_4X4_50 print A4`
- `Hall effect sensor magnet detection`
- `NdFeB magnet specifications N42`
- `indoor robot localization options comparison`

---

### 3. Tiraaživalmis dokumentatsioon

**Eeldus:** sul on V1 spetsifikatsioon, V2 testid, V3 integratsioon, V4 viimistlus — kõik repos olemas.

**Eesmärk:** keegi kolmas (mitte sinu meeskonnaliige, vaid teise meeskonna inimene) peab saama **sinu repo ja tellimusnimekirjast tellitud komponendid** ja ehitama nendega sama roveri. Ilma sinult midagi küsimata. Ilma "tead, see saab selgemaks, kui koos ehitame" hetkedeta. Kui ta jääb hätta, on see sinu dokumentatsiooni viga, mitte tema arusaamatus.

**Mida tiraaživalmis dokumentatsioon sisaldab:**

| Dokument | Mida sees | Vorm |
|:---|:---|:---|
| **README.md repo juures** | Mis see projekt on, milline rover, kuidas alustada | Markdown |
| **Kokkupanekujuhend** | Samm-sammuline, piltidega, igal sammul mida vaja, mida teha, mida kontrollida | Markdown / PDF |
| **3D prindifailid + CAD lähtefailid** | STL-id valideeritud printimise seadetega (orientatsioon, tugestinad, täituvus iga detaili kohta) **JA** CAD lähtefailid — Fusion 360 puhul `.f3z`/`.f3d` arhiivid, CadQuery puhul `.py` skriptifailid. STL-id on eksport; tegelik disain peab olema avatav ja muudetav. | STL + .f3z/.f3d või .py + tabel märgistustega |
| **BOM (Bill of Materials)** | Lõplik komponentide nimekiri tegelike hindade ja tarnijatega | CSV või Markdown tabel |
| **Tarkvarapaigalduse juhend** | Repo cloneda → seadista → flashi MCU → käivita server → veebileht avaneb | Markdown |
| **Hooldusjuhend** | Mis kulub kõige kiiremini, kuidas vahetada, kui sageli kontrollida | Markdown |
| **Teadaolevate probleemide nimekiri** | Iga viga, mida V4 testid leidsid + lahendus või põhjendatud loobumine | Markdown |
| **Operaatori juhend** | Kuidas üks matš mängida — käivitusest tulemuseni | Markdown, 1 lehekülg |

**Kokkupanekujuhendi miinimumnõuded:**

- **Iga samm on nummerdatud** (mitte "siis pane kruvi", vaid "9. Pane M3×8 kruvi mootori vasakpoolsesse ülemisse avasse")
- **Iga sammu juures on pilt** (mitte üks pilt 5 sammu kohta, vaid igal sammul oma pilt)
- **Iga komponent on nimetatud sama nimega** mis BOM-is (kui BOM ütleb "DRI0044 mootoridraiver", ei kasuta juhendis "L298")
- **Tööriistad** loetletud sammu alguses, mitte iga kord eraldi
- **Kontrollkohad** ("pärast seda sammu peab rataste pööramine olema sujuv, ilma takerdusteta") — ilma nendeta ei tea kasutaja, kas tegi õigesti

**Tarkvarapaigalduse juhend peab sisaldama:**

- Operatsioonisüsteemi nõuded (Windows / Linux / Android Termuxi puhul)
- Vajalikud paigaldused (Pythoni versioon, paketid, Arduino IDE, draiverid)
- Pythoni keskkonna seadistus (venv käsud konkreetselt)
- Repo cloneerimise käsk
- MCU flash-protseduur (millise tarkvaraga, milline port, milline kiirus)
- Esimese käivituse kontroll (mida peab nägema, et veenduda kõik töötab)
- Tüüpilised vead esimesel paigaldusel (port hõivatud, draiver puudub, WiFi parool vale)

**Hooldusjuhendi näide:**

| Kulu-osa | Sümptom | Tegevus | Sagedus |
|:---|:---|:---|:---|
| Mootori kinnituspolt | Mootor vibreerib | Loctite + pinguta | Iga 10 matši järel kontrolli |
| Aku | Lühem tööaeg | Vaheta uue vastu | Pärast 100 laadimist |
| Värvianduri lääts | Mustus, näit ebakindlam | Puhasta kuiva lapiga | Enne iga matširingi |
| Rattad | Pind kulunud | Vaheta uutega | Visuaalse kontrolli järgi |

---

### 4. Operaatori juhend — 1 lehekülg

**Eeldus:** rover töötab ja autonoomsuse astmed töötavad.

**Eesmärk:** üks **A4 lehekülg** (kahepoolne, kui vaja), mille pealt operaator (kes pole varem näinud) saab teha terve matši algusest lõpuni. Mitte "mis on rover", vaid "kuidas mängida".

**Mida sisaldab:**

- **Käivitamine** — lülitad sisse, ootad N sekundit, kuni nupp põleb roheliselt
- **Veebiliidese avamine** — millise WiFi-võrgu kaudu, millise aadressiga
- **Roveri kalibreerimine** — pane rover areeni peale, kontrolli värviandur, vajuta "kalibreeri"
- **Matši kava** — 90 sek; algus tuleb kohtuniku märguandena (kell käivitub serverist või kohtunik ütleb "start"). Lõpus saab rover automaatselt "stop" käsu.
- **Autonoomsuse astmete vahetamine** — millal manuaal, millal autopilot, millal agent (lühike soovitus)
- **Vea olukorras** — kui WiFi katkeb, kui rover ei reageeri, kui andur näitab valet — mida teha esimesena
- **Pärast matši** — kuidas vaadata tulemust, kuidas valmistuda järgmiseks (sh aku vahetus)

Reegel: **mitte rohkem kui üks lehekülg**. Kui ei mahu, on midagi liiga keeruline ja vajab lihtsustamist liidese poolel, mitte juhendi pikendamist.

---

### Tiraaži ajaeelarve (Analüüs 1)

**Eeldus:** tiraaživalmis dokumentatsioon on koostatud.

**Eesmärk:** arvuta välja, mitu lisaroverit jõuad tiraaži-aja jooksul (30.05–11.06, ~12 päeva) toota. See on insener-küsimus: kas dokumentatsioon on hea ja kas füüsilised piirangud (printer, inimesed) üldse lubavad tiraaži?

**Mõõtmine:**

1. **3D-prinditud detailide ajaarvestus:**
   - Mõõda iga detaili printimisaeg (loe slicerist või võta taimeriga)
   - Iga detaili kohta märgi: failinimi, ajaline kestus, materjali kulu (grammides)
   - Liida kokku ühe roveri jagu detaile

2. **Kokkupaneku aeg:**
   - Mõõda päris kokkupaneku aeg (kui jõuad veel ühe ehitada — kasuta seda)
   - Kui ei jõua, hinda iga sammu aeg dokumentatsioonist + lisa 30% reservi tundmatute probleemide jaoks

3. **Komponentide tarne:**
   - Mis on pikim tarneaeg BOM-is? Kui osa võtab 14 päeva, ei jõua midagi tiraaži
   - Kas kohalik varu (mis on klassiruumis olemas) lubab kohe alustada?

**Jupyter Lab arvutus:**

- Üks rover = N tundi printerit + M inimese-tundi
- Sinu kasutuses on K printerit ja L inimest
- 12 päeva = 12 × kasutuspäeva (printer võib töötada üle öö, inimene ei)
- Tulemus: tegelik tiraaži maht

**Tabel raportis:**

| Detail | Print aeg (h) | Materjali kulu (g) | Märkused |
|:---|:---|:---|:---|
| Alusplaat | 4,5 | 65 | 0,2 mm kihid, 30% täituvus |
| Mootori kinnitus (×2) | 1,2 | 18 | Polt+mutter versioon |
| ... | ... | ... | ... |
| **Kogu rover** | ... | ... | |

**Hinnang:** kui üks rover võtab kokku 15 print-tundi ja 4 inimese-tundi, jõuad ühe printeri ja kahe inimesega 12 päevaga umbes 5 roverit toota. Kas see vastab nõudmisele?

---

### Dokumentatsiooni läbikäik (Analüüs 2)

**Eeldus:** kogu dokumentatsioon on koostatud (sektsioon 3).

**Eesmärk:** sinu dokumentatsioon töötab **ainult siis**, kui keegi kolmas saab selle põhjal asju teha. Ainus viis seda kontrollida on lasta kellelgi proovida.

**Mõõtmine:**

1. **Vali kolmas inimene** — eelistatavalt teise meeskonna liige, kes pole sinu projekti varem näinud. Vähemalt sõber või klassikaaslane.
2. **Anna talle ainult repo link** + (kui vaja) komponentide karp.
3. **Lase tal proovida** ühte konkreetset ülesannet:
   - Variant A: paigaldada tarkvara nullist (uus arvuti, tühi keskkond)
   - Variant B: leida üks osa BOM-ist ja näidata, mis poest tellida
   - Variant C: lugeda kokkupanekujuhendit ja kirjeldada, mida ta ehitaks (ilma päriselt ehitamata — sa ei jõua tiraaži ajal oodata)
4. **Märgi iga koht**, kus ta jääb kinni:
   - Termin pole defineeritud
   - Pildi puudus
   - Käsku ei saa kopeerida (sisaldab kõverkriipsu, mis ei tööta brauserist)
   - Eeldab teadmist, mida pole

**Tabel raportis:**

| Asukoht juhendis | Probleem | Tegevus | Tehtud? |
|:---|:---|:---|:---|
| Tarkvara samm 3 | "pip install" ei tööta Windowsil sama moodi kui Linuxil | Lisa kaks varianti | Jah |
| Kokkupanek samm 8 | Pildi peal pole näidatud, milline polt | Märkida pildil noolega | Jah |
| BOM rida 15 | "ESP32-CAM" — milline mudel täpsemalt? | Lisada AliExpressi link | Jah |
| ... | ... | ... | ... |

**Hinnang:** kui kolmas inimene leiab **alla 10 probleemi** — dokumentatsioon on hea, paranda need. Kui üle 20 → vajalik suurem ümberkirjutus, mitte ainult parandused.

---

### V1–V4 mõõtmiste koondgraafik (Analüüs 3)

**Eeldus:** kõikidest varasematest verstapostidest on mõõtmised CSV-failina repos olemas.

**Eesmärk:** see on **kogu projekti tõehetk**. Mida sa V1 spetsifikatsioonis lubasid? Mida V2 testid näitasid? Mis paranes V3 integratsiooniga? Mis muutus V4 viimistluses? Üks Jupyter notebook, mis selle kõik kokku paneb ja **näitab visuaalselt** roveri arengu loo.

**Mida koondada:**

| Verstapost | Mõõdik | Numbri tüüp |
|:---|:---|:---|
| V1 | Spetsifikatsioonis lubatud kiirus | m/s |
| V1 | Spetsifikatsioonis lubatud aku tööaeg | min |
| V2 | Mõõdetud tõuke jõud | N |
| V2 | Mõõdetud side latentsus (mediaan, max) | ms |
| V2 | Mõõdetud kaugusanduri täpsus | cm |
| V3 | Klõpsa-ja-sõida viga | cm |
| V3 | Piiri tuvastamise edukus | % |
| V3 | Aku tööaeg integreeritud süsteemiga | min |
| V4 | Korpuse vastupidavus 5 kokkupõrkest | % osad lõdvenenud |
| V4 | Värviandurite kindlus | 0–1 |
| V4 | Autonoomsuse astmete edukus | 5/5 |
| V4 | 10 matši usaldusväärsus | taaskäivituste arv |

**Visualiseerimised:**

- **Joongraafik ajateljel:** iga verstapost on punkt, ühend joontega — mis paranes, mis halvenes
- **Spetsifikatsioon vs tegelikkus:** baargraafik, kus iga mõõdiku puhul on V1 lubatud kõrvuti V4 mõõdetud
- **Aja kasutus:** kui palju tunde iga verstapost võttis, võrreldes spetsifikatsioonis kavandatuga

**Tabel raportis:**

| Mõõdik | V1 spetsifikatsioon | V4 mõõdetud | Hinnang |
|:---|:---|:---|:---|
| Maks kiirus | 0,5 m/s | 0,42 m/s | Alla spetsi, aga matšiks piisav |
| Aku tööaeg | 60 min | 38 min | Alla spetsi, peab matširingide vahel laadima |
| Sideviivitus | < 100 ms | 87 ms (95. protsentiil) | Spetsi sees |
| Klõpsa-ja-sõida viga | < 5 cm | 12 cm | Üle spetsi — parandada enne tiraaži |
| ... | ... | ... | ... |

**Lühike refleksioon (1 lõik vabas vormis):**

- Mis sinu meeskonna jaoks oli kõige suurem üllatus V1-st V4-ni?
- Mis ennustus pidas paika ja mis täiesti vale läks?
- Kui pidaksid täna kirjutama V1 spetsifikatsiooni uuesti, mida muudaksid?

See refleksioon ei ole jutuke — see on kõige väärtuslikum osa, mida sa terve semestri jooksul oled õppinud. Inseneri-projekti tegelik tulemus on see, mida **järgmise projekti alguses** teisiti teed.

---

### Hindamiskriteeriumid

| Kategooria | Punktid | Mida hinnatakse |
|:---|:---|:---|
| Tööfailid | 4 p | Lõplik kood, STL-id **ja CAD lähtefailid** (Fusion `.f3z`/`.f3d` või CadQuery `.py`), BOM, fotod ja videod |
| Analüüs | 4 p | 3 Jupyter notebook'i (tiraaži ajaeelarve, dokumentatsiooni läbikäik, V1–V4 koondgraafik) |
| Prototüüp | 4 p | Rover on viimistletud, asukoha määramine (ArUco lakke) töötab, tulemused dokumenteeritud |
| Dokumentatsioon | 4 p | Tiraaživalmis (kokkupanek, tarkvara, hooldus, operaatori juhend, teadaolevad probleemid) |
| Küsimused-vastused | 4 p | Demo kohtumisel + refleksioon: mis õpitu kandub edasi järgmistesse projektidesse? |
| **Kokku** | **20 p** | |


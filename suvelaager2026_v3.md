# Robootika suvelaager

## Kaks päeva, üks mäng, kolm juhtimisliidest

Laager kestab kaks päeva. Kaks lauda, igal laual kaks Dobot MG400 robotkätt vastamisi — kokku neli robotit ja kaks mänguplatsi. Igal laual on lisaks **kolm lauaarvutit**: kaks mängijatele (üks meeskonna kohta) ja üks mängujuhile (juhendajale, kes haldab matšid ja kalibreerib kaamera).

Õpilasi on 16; meeskondi neli, igaühes neli inimest. Iga matši ajal on **neli operaatorit** käte taga (üks operaator meeskonna kohta) ja **kaksteist meeskonnaliiget istuvad kõrval**. Need kaksteist pole pealtvaatajad — neil on kindlad rollid, ilma milleta meeskond mängu ei võida (vt allpool).

Mäng on Atomic Bombermani klooni-tüüpi värk: kahe mängija duell, sa liigutad oma tegelast väljakul ja paned pomme maha. Aga sina ise nuppe ei vajuta — sinu eest teeb seda robotkäsi. Sinu töö (kui oled operaator) on robotile öelda, kuhu vajutada. Sinu töö (kui oled tugiroll) on aidata operaatoril paremini öelda.

Päeva jooksul proovid kolme erinevat viisi robotiga rääkida. Igaüks eelmisest mugavam. Teisel päeval võistled samas mängus, mida hommikul vaevu mängida sai — ja näed must valgel, kui palju on rohkem aru saada.

Masin teeb täpselt seda, mida käsid. Esimesel päeval avastad, kui jube on käsku anda viisil, mis pole läbi mõeldud. Teisel päeval saad aru, kui palju kihte on ühe lihtsa "vajuta sinna" ja päriselt vajutamise vahel.

---

## Mäng

Kaks robotit istuvad vastamisi, nende vahel on **monitor**. Ekraanil jookseb Bombermani-tüüpi mäng — sinu tegelane väljakul, vastase tegelane samuti, pommid plahvatavad. Sa juhid oma tegelast nii: robotkäsi liigub ekraani pinna kohale kindlasse kohta, ja **kaamera ülevalt tuvastab tööriista asukoha** (ArUco markeri järgi) — see töötab mängu jaoks samamoodi nagu vajutus. Eraldi nupp paneb pommi maha. Vastane teeb sama, teine robotkäsi liigub sama ekraani kohal.

**Ekraan ise pole puuteekraan.** Kaamera ja ArUco markeri kombo on see, mis "vajutuse" registreerib. Enne mängu kalibreeritakse, kus ekraanil on **tundlikud alad** (mänguruudud, pommi-nupp) — kaamerast nähtud roboti positsioon → vastav tundlik ala → mäng saab sisendi.

Üks matš kestab **90 sekundit**. Võidab see, kes vastase pommi sisse jätab või ellu jääb pikemalt.

---

## Riistvara

Igal laual on sama komplekt.

**Kaks Dobot MG400 robotkätt** vastamisi. Tööstuslik robotkäsi — sama, mis tehases asju kokku paneb, ainult väiksem. Igal robotil on pehme silikoonist ots ja selle peal **ArUco marker**, et kaamera tunneks tööriista asukohta täpselt.

**Tavaline 24–30" monitor** robotite vahel keskel laual. Ei ole puuteekraan. Selle peal jookseb mäng. Mõlemad robotid ulatuvad ekraani kohale.

**4K kaamera** otse ülevalt, vaatab nii ekraanile kui mõlemale robotile alla. See on "vajutuse tuvastaja" — näeb iga roboti tööriista ArUco markerit ja teab täpselt, kus tööriist parasjagu on. Kombineerituna ekraani tundlike alade kalibreerimisega muutub kogu süsteem virtuaalseks puuteekraaniks.

**Kolm lauaarvutit per laud:**

- **Mängija A arvuti** — punase meeskonna operaatori jaoks, kus jookseb tema valitud juhtimisliides ja roveri kontrollpaneel
- **Mängija B arvuti** — sinise meeskonna operaatori jaoks, sama
- **Mängujuhi arvuti** — kohtuniku/juhi jaoks. Siin jooksevad mäng ise, kaamera kalibratsioon, taimer, skoor

**Backend:** Python (sama, mis varasematel päevadel). Iga arvuti räägib backendiga, kes räägib robotitega ja mänguga.

---

## Kalibreerimine enne matši

Enne iga seansi algust **kalibreerib mängujuht oma arvutist** kaamera ja ekraani omavahel:

1. Kaamera teeb pildi monitorist ülevalt
2. Mängujuhi liides näitab pilti ja küsib: "klõpsa pildi peal ekraani neljal nurgal"
3. Pärast nelja klõpsu teab süsteem, kus ekraan kaamera-pildil on
4. Mäng kuvab ekraanil **tundlikud alad** (näiteks mänguruudud — 8×8 võrgustik) — süsteem teab, kus iga tundlik ala on kaamera-koordinaatides

Pärast kalibreerimist: kui robot tööriist (ArUco marker) on kindla tundliku ala kohal vähemalt 200 ms, registreerib mäng selle "vajutusena". See on stabiilsuse filter — juhuslikku ülelendu ei loeta.

Kalibreerimine võtab umbes 30 sek. Tehakse uuesti, kui keegi liigutab kaamerat või kui ekraan nihkub.

---

## Kolm juhtimisliidest

Sama mäng, sama riistvara — kolm erinevat viisi öelda robotile, kuhu vajutada. Iga uus liides on eelmisest mugavam ja räägib robotile kõrgemal abstraktsioonitasemel.

### Tase 1 — HAAS CNC kontrolleri liides

Veebilehel on **HAAS CNC pingi juhtpaneeli koopia** — sama liides, mida masinatöölised iga päev kasutavad freesi või trei juhtimiseks. Põhi-elemendid:

- **HANDLE** — suur keerdratas keskel, millega liigutad valitud liigest sammhaaval
- **Liigese valiku nupud** (F1–F4) — valid, millist roboti liigest parasjagu pöörad
- **CYCLE START** (roheline) ja **FEED HOLD** (punane) — käivita või pause hetkeline liigutus
- **OVERRIDES** lülitid — −10, −5, 100%, +5, +10 — kiiruse muutmine
- **EMERGENCY STOP** (punane seenenupp) — kõik kohe seisma
- **Pomm-nupp** — paneb mängus pommi maha

Toore jõu liides — pead robotiga rääkima tema enda keeles, liigese kaupa. Tahad tööriista kindlasse kohta saada? Pead välja arvutama, milline liigeste kombinatsioon sinu tahetud asendi annab. Valid F-nupuga liigese, keerad HANDLE-iga, vajutad CYCLE START.

Tahtlikult ebamugav, **aga see on päris tööstuslik liides** — sama, mida kasutavad CNC operaatorid kogu maailmas. Et tunneksid päriselt, kui keeruline on rääkida masinaga tema enda käskude tasemel. See on alguspunkt.

---

#### Robootika põhimõte: Liigese-ruumi intuitsioon (forward kinemaatika)

Kui sa juhid robotit liigese kaupa, pead peast välja arvutama, kuidas üks liigese liigutus muutub tööriista asendiks ruumis. Dobot MG400-l on lihtne mudel:

- **Liigend 1** (alus pööramine) → tööriista **suund** ruumis (vasak-parem nurk)
- **Liigend 2 ja 3 summa** (õla- ja küünar-liigesed kokku) → tööriista **kaugus** robotist
- **Liigend 2 ja 3 suhe** → tööriista **kõrgus** maapinnast

Mängu jooksul hakkad ise tundma: "tahan tööriista vasakule → pööran liigend 1", "tahan kõrgemale → muudan liigend 2 ja 3 suhet, mitte nende summat". See on **forward kinemaatika intuitsioon** — liigutusest asendiks.

Päris CNC operaatorid teevad seda peast iga päev. Sellepärast on Tase 1 raske: **sina ise oled see arvuti**, kes liigese-ruumi koordinaate ruumi-koordinaatideks teisendab. Järgmised tasemed lasevad seda tööd masinal teha — sina räägid otse ruumi-keeles.

### Tase 2 — CAM-tarkvara stiilis (AutoCAD DOS lähenemine, palju ka tänapäeva CAM-il)

Veebilehel on **visuaalne mängu kaart vasakul + käsurida paremal**. Sa näed ekraanil mängu väljakut (8×8 ruudustik), saad selekteerida ruute klikiga; käsurea paneelis trükid täpset käsku või kasutad valitud objekti peal operatsiooni.

Töövoog on sarnane vanaaegse AutoCAD DOS-iga (ja paljus ka tänapäeva CAM-tarkvaraga nagu Fusion, Mastercam, SolidCAM):

- Vali kaardil ruut → klikk
- Trüki käsk: `MOVE TO` või `BOMB` → Enter
- Süsteem genereerib roboti liigutuste jada ja täidab

Näiteid:
- `MOVE TO E5` — liigu valitud ruutu
- `BOMB` — pane pomm praegusesse asukohta
- `MOVE X 200 Y 150` — täpsemate koordinaatidega
- `MACRO BOMBRUN` — kasuta meeskonna-promptija loodud lühivormi

Kiirem kui Tase 1, sest sa räägid ruumi-keeles, mitte liigese-keeles. Aga sina pead välja mõtlema iga sammu eraldi ja sisestama selle. Mängu ajal mõtled käskudele, mitte mängule.

---

#### Robootika põhimõte: Pöördkinemaatika ja LUT (Lookup Table)

Kui sa ütled "MOVE X 200 Y 150", siis robot ei tea otse, milliseid liigeseid pöörata. Süsteem peab arvutama vastupidiselt forward kinemaatikale: **etteantud (x, y, z) jaoks, milline on iga liigese nurk?** Seda nimetatakse **pöördkinemaatikaks** (inverse kinematics, IK).

IK matemaatika on raske ja aeglane reaalajas arvutada. Praktikas kasutatakse sageli **LUT-i (Lookup Table)** — eelnevalt välja arvutatud või mõõdetud tabel, kus iga (x, y, z) on seotud vastavate liigeste nurkadega:

```
(x, y, z)      → (j1°, j2°, j3°, j4°)
(0, 0, 100)    → (0°,   45°, −45°, 0°)
(50, 0, 100)   → (0°,   53°, −38°, 0°)
(50, 50, 100)  → (45°,  53°, −38°, 0°)
(200, 150, 0)  → (37°,  78°, −12°, 0°)
...
```

Kalibreerimine: enne mängu liigutab süsteem roboti läbi paljude (x, y, z) punktide ja salvestab iga punkti jaoks liigeste nurgad. Tekib LUT. Pärast seda: "MOVE X 200 Y 150" → vaata LUT-st lähim punkt → leia liigeste nurgad → liiguta.

**Tase 2 töötab sellepärast, et keegi (sina ja sinu meeskond, või eelnevalt juhendaja) on selle LUT-i ehitanud.** Sa räägid x-y keeles, robot saab aru, sest LUT tõlgib. Tase 1 puhul polnud sul LUT-i — pidid ise olema kalkulaator.

### Tase 3 — VS Code + Claude Code agent

Sama tööriist, millega oled eelnevatel päevadel ülesandeid lahendanud. Avad VS Code, sees on Claude Code. Backendis on tööriistad valmis:

- `get_game_state()` — tagastab juba **töödeldud asukohad** (sinu tegelane, vastane, pommid, plahvatusalad) JSON-ina
- `tap(x, y)` — vajutab valitud koordinaadile
- `place_bomb()` — paneb pommi maha
- `screen_capture()` — toore pildi võtmine, kui agent tahab ise vaadata

**Tähtis:** agendile ei anta toort kaamerapilti otsustamiseks. Enne agenti on **objekti-klassifikaator** (YOLO või lihtsam värvi-klassifikaator), mis pildi peal ära tunneb, kus mis on. Agent saab need positsioonid juba selgelt välja loetuna. Tema töö on **otsustada, mida teha**, mitte näha.

Annad agendile lihtsa eesmärgi: *"Mängid Bombermani. Vaata get_game_state'i andmeid, väldi pomme, jahi vastast."* Agent kutsub `get_game_state()`, mõtleb, kutsub `tap()` või `place_bomb()`, vaatab uuesti.

Mängitavus sõltub palju sellest, mida sa promptisse kirjutad. **Õige küsimuse esitamine on parem kui kiire käsk.** Sama agent, kaks erinevat prompti — üks võidab, teine kaotab.

---

#### Robootika põhimõte: Mudelite eri tüübid — millal mida kasutada

Tase 3 paneb kokku **kaks fundamentaalselt erinevat tüüpi mudelit**: klassifikaatori, mis vaatab pilti ja ütleb, mis seal on, ja LLM-i, mis võtab struktureeritud andmed ja otsustab mida teha. Kummalegi mudelitüübile oma roll, õiges kihis. Tasub aru saada **kohe**, sest 2026. aasta insenertöös kohtad mõlemat iga päev.

**LLM (Large Language Model) — küsimus + vastus = vastus**

Sa annad LLM-ile küsimuse (sõnade jada). Mudel võtab eelmiste sõnade järgi ja arvutab, milline järgmine sõna on **kõige tõenäolisem**. Lisab selle vastuse lõppu. Siis sama loogika veel ja veel — võtab kõike, mis siiani vastuses on, otsustab järgmise sõna. Nii koguneb vastus.

Kuidas mudel "teab", mis on tõenäoline järgmine sõna? Treeningu ajal on talle näidatud tohutu hulk teksti. Mudel on õppinud, et iga sõna ja iga lause asub **mitmemõõtmelises ruumis** (sajad mõõtmed) — sarnased asjad on lähestikku, sarnastes kontekstides kasutatud sõnad on lähedal.

Kujuta seda nii: **mudeli teadmised on nagu tähed galaktikates**. Iga sõna, lause, mõte — täht. Sarnased asjad lähestikku, eri valdkonnad eraldi sõõridena. Kui sina küsid midagi, mille täpset vastust mudel pole näinud, siis ta **interpoleerib lähimatest tähtedest** — võtab paari kõige lähedasema punkti ja ümardab vastuse nende vahelt.

See on miks LLM oskab "vastata" küsimustele, mida tal pole konkreetselt õpetatud — sest sarnaseid on miljon. Aga see on ka miks LLM võib **eksida**: kui sinu küsimus on galaktika tühjas kohas (väga harva esinev teema), võib ta haarata vale tähe juurest vastuse.

**Diffuser — pildi või heli loome müraast**

Hoopis teine ehitus. Diffuser-mudelid (Stable Diffusion piltide jaoks, audio diffusion heli jaoks) ei loo midagi sammhaaval. Nad alustavad **müraest** (täielikult juhuslikud pikslid või helikära) ja **järk-järgult eemaldavad müra**, kuni alles jääb täpselt see pilt või heli, mida sa palusid.

Treening on vastupidi: mudelile näidatakse päris pilte ja õpetatakse, kuidas neisse järk-järgult müra lisada (kuni jääb ainult müra). Käivitamine on tagurpidi: müra → samm-sammult müra eemaldamine → lõpuks pilt.

Diffuser annab uut pilti või heli, mida pole varem olnud. LLM annab uut teksti. Aga ehitus on hoopis erinev.

**Klassifikaator nagu YOLO — pildilt asukohad ja sildid**

YOLO ("You Only Look Once") on **objektide tuvastamise mudel**. Sa annad talle pildi. Ta tagastab nimekirja: *"siin pildis on koer asukohas (x=120, y=200), pall asukohas (x=300, y=400), kass asukohas (x=500, y=600)"*. Iga tuvastatud objekt = klass-silt + asukoht + kindlus.

Treening: YOLO-le on näidatud sadu tuhandeid pilte koos sildistatud objektidega ("see ruut pildil on koer", "see ruut on auto"). Mudel õppis, kuidas pilte arvulistest mustritest tundma — millise värvi ja kuju kombinatsioon tähendab "koera", millise "autot".

YOLO on **kiire ja täpne** kindlas ülesandes (objektide tuvastamine). Aga ta ei oska "mõelda" ega "otsustada" — ta lihtsalt nimetab asju ja annab nende asukohad.

**Millal mida kasutada?**

| Olukord | Õige mudel | Miks |
|:---|:---|:---|
| Pildilt asjade tuvastamine ja asukoht | YOLO (klassifikaator) | Kiire (millisekundites), täpne, vähene arvutivõimsus |
| Uue pildi loomine teksti järgi | Diffuser | See on tema spetsialiseering |
| Strateegia, plaan, mitme-sammuline otsus, vestlus | LLM | Suudab konteksti hoida, eesmärgi peale mõelda |
| Pildi nägemine + otsustamine korraga | **Mõlemad koos: YOLO nägemiseks + LLM strateegiaks** | Õige tööriist õiges kihis |

Tase 3 puhul järgime just seda jaotust:

- **YOLO (või lihtsam värvi-klassifikaator)** vaatab kaamera-pilti, leiab kus on sinu tegelane, vastane, pommid. Tagastab struktureeritud andmed JSON-ina.
- **Claude Code (LLM)** võtab need andmed, otsustab strateegia, kutsub `tap()` käsku.

Agent ei pea pilti raw kujul vaatama. **Ta saab juba positsioonid.** Tema töö on otsustada, mitte näha.

See on **õige arhitektuuri näide**: igale ülesandele oma mudel. Sama loogika kehtib päris robootikas — autotehases on YOLO koosteliinil tuvastamas, mis osa läbi liigub; eraldi planeerimis-mudel otsustab, kuhu robotkäsi liigub. Marsi roveris on omaette nägemis-mudel, mis tuvastab kive ja takistusi; eraldi otsustusloogika valib tee.

**Õppetund kogu laagrist:** ära aja mudeleid segi. Igaüks on hea omas ülesandes. Halb arhitekt paneb LLM-i pilti vaatama (aeglane, ebatäpne) või YOLO strateegiat tegema (ei oska). Hea arhitekt teab, mida kuhu panna.

---

## Meeskonnatöö — kuidas 12 mitte-operaatorit kaasa aitavad

Iga matši ajal on 4 operaatorit (üks meeskonna kohta) ja 12 inimest istuvad kõrval. Need kõrval-inimesed pole pealtvaatajad. Iga meeskonna sees on iga matši kohta **neli kindlat rolli**, mille vahel meeskond ise jaotab. Roteerumine on **kohustuslik** — sama inimene ei tohi olla sama rollis kahel järjestikusel matšil.

### Neli rolli meeskonna kohta

**Operaator** — istub roboti taga, kasutab parasjagu kasutusel olevat juhtimisliidest. See on füüsiline tegija.

**Strateeg** — vaatab kõrvalt mängu ekraani, ütleb operaatorile valju häälega, mida teha. Näiteks: "Mine üles. Nüüd pomm. Põgene paremale." Tema vastutab strateegia eest, operaator täidab.

**Vaatleja** — vaatab **vastase** ekraani-poolt ja jälgib, mida vastasmeeskond teeb. Märgib mustreid: "Vastane paneb alati pommi sama nurka", "vastasel võtab agendi peast aru saada 4 sekundit". Nende info läheb järgmise matši operaatorile.

**Promptija/Kodija** — parandab **matšide vahel** liidest või agendi prompti. Tase 1 puhul: midagi ei muuda (lihtsalt vaatab kõrvalt). Tase 2 puhul: võib teha makrosid pikematele käskudele. Tase 3 puhul: kirjutab Claude Code agendi prompti paremaks pärast iga matši — võtab eelmise matši leidudest õppe, paneb need agendile reegliteks.

### Rotatsioon

Iga meeskond peab läbima **kõik neli rolli iga matši ajal**. Pärast matši rollid vahetuvad. Pärast nelja matši on iga inimene olnud kõigis neljas rollis.

**Punktsüsteem soosib rotatsiooni:**

- Iga võidetud matš = **1 punkt**
- Kui meeskond on neljas järjestikuses matšis kasutanud **nelja erinevat operaatorit** = lisaks **+2 boonust**
- Kui ükski inimene on operaator rohkem kui kord enne, kui kõik on operaator olnud = **0 boonust**, ja iga "vahele jäetud" inimene = **−1 punkt**

Lühidalt: meeskond, kelle iga liige operaator saab olla, võidab. Meeskond, kus üks geenius mängib kogu aja, kaotab — isegi kui geenius võidab kõik matšid üksinda.

See on tahtlik. Päris robootika ja päris insenertöö ei juhtu üksinda. Sa ehitad meeskonnaga, dokumenteerid teistele, võtad nõu vastu. See laager õpetab seda kohe selgeks.

---

## Esimene päev — proovimatš ja kaks õppesessiooni

**Aeg:** 2,5 tundi (1 h + 1,5 h, üks vahepaus).

### Slot 1 (1 tund) — Avapresentatsioon ja proovimatš

**Avapresentatsioon (15 min)**. Juhendaja näitab korraks, mis ekraanil toimub: see on Bombermani mäng, sina oled punane tegelane, vastane on sinine, pomm plahvatab paari sekundi pärast. Tutvustab nelja rolli (operaator, strateeg, vaatleja, promptija) ja rotatsiooni reegleid.

**Proovimatš — Tase 1 HAAS-liidesega (45 min)**. Igale meeskonnale antakse Tase 1 liides — HAAS CNC kontrolleri paneeli koopia (keerdratas, liigese-valiku nupud, CYCLE START). Mitte mingeid muid juhiseid. Roteeritakse kohti: matšide vahel vahetuvad operaatorid. Esimene matš 90 sek (siniste vs punaste meeskondade kohta), siis paus, rollid vahetuvad, järgmine matš.

Neli matši tagajärgi 45 minuti sees — iga meeskonna iga liige saab kord operaatoriks. Naerdakse. Keegi ei saa aru, kuidas oma tegelast üldse liigutada — peale seda, kui esimene liigend pööras valele poole. Üks paneb pommi maha, mis ta enda alla plahvatab.

Pärast matše arutletakse minut kahe peale: **mida raske oli? Miks?** Vastus tuleb tavaliselt välja — "robot ei tee seda, mida ma tahan." Mis on tegelikult vale viis öelda. Õige vastus: **ma ei oska robotile õigesti öelda, mida ma tahan**. Liides on liiga toore.

See vahe — "robot ei tee õigesti" versus "ma ei räägi õigesti" — on kogu laagri filosoofiline alus.

### Slot 2 (1,5 tundi) — Õppesessioon 1: AutoCAD DOS stiilis

Esimene päris õppesessioon. Veebilehel on nüüd must terminal-aken. Trükid käsu: `MOVE X 200 Y 150`, Enter, robot liigub. `BOMB` paneb pommi.

**Tutvumine (20 min).** Kõigepealt proovige liidest tundma — sisestage käske, jälgige, kuhu robot läheb. Õppige, kus on ekraani vasak ülanurk koordinaatides, kus alumine parempoolne. Tehke endale kaardistus peas.

**Harjutusmatšid (50 min).** Neli matši 90 sek igaüks, rollide rotatsioon nagu enne. Kindlasti parem kui Tase 1. Aga käske trükkida võtab aega — vastane jõuab samal ajal liikuda kiiremini, kui sa oma käske trükkida jõuad.

Promptija/kodija rolli sisu siin: võib hakata tegema **makrosid** sagedasti kasutatavatele käskudele. Näiteks `M1`, `M2`, `M3` lühivormid kindlate koordinaatide kohta. Need makrod aitavad operaatorit järgmistes matšides — eduka käsutaja töö läheb järgmisele meeskonnaliikmele üle.

**Arutelu (20 min).** Mida õpiti? Tavaliselt — "käsurida on kiirem kui keerdratas, aga ikka aeglane mängu jaoks." See on õige õpik. **Iga abstraktsioonisamm vähendab keerukust, aga ei pruugi olla veel piisav.** Ka selgub: meeskond, kus promptija on teinud head makrod, on operaatorile selgelt eelisseisus. Toetav töö maksab end ära.

---

## Teine päev — Claude Code agent ja võistlus

**Aeg:** 3 tundi (1,5 h + 1,5 h, üks vahepaus).

### Slot 3 (1,5 tundi) — Õppesessioon 2: Claude Code agent

Avad VS Code, sees Claude Code. Backendis on tööriistad: `screen_capture`, `tap(x, y)`, `place_bomb()`, `get_game_state()`. Sama Claude Code, millega oled juba muid ülesandeid lahendanud — uus on ainult roveri tööriistakomplekt.

**Esmane prompt (20 min)**. Meeskond koos kirjutab esimese versiooni prompti agendile. Näiteks: "Mängid Bombermani. Vaata pilti, leia minu tegelane (punane), väldi pomme, jahi vastast." Käivitavad ja vaatavad.

**Harjutusmatšid (60 min).** Neli matši nagu enne, rollide rotatsioon. Esimesed katsed on tihti katastroofilised — agent näeb hästi, aga mõtleb aeglaselt (iga ring 2–5 sekundit). Mängitavus sõltub palju promptist.

**Promptija roll** on selles sessioonis kõige olulisem. Iga matši järel parandab ta prompti vastavalt eelmisele matšile. "Agent ei näinud pommi vasakul → lisa promptisse 'kontrolli kõigepealt, kas pomm on lähedal, alles siis liigu'". "Agent jäi nurka kinni → lisa 'kui sa ei ole 5 sek liikunud, mine vastassuunas'."

Pärast nelja matši on prompt tunduvalt parem kui esimene. Mõni meeskond saab võidu agendiga, teine kaotab pidevalt. Vahe pole agendis — vahe on selles, kui hästi meeskond agendile selgitas, mida nad tahavad.

**Arutelu (10 min).** **Õige küsimuse esitamine on parem kui kiire käsk.** Sama agent, neli erinevat prompti — üks võidab, teine kaotab.

### Slot 4 (1,5 tundi) — Võistlus

**Avapresentatsioon võistlusreeglitest (10 min).**

Meeskonnad on neli, igaüks neljaliikmeline. Mängitakse **ringturniir**:

- Voor 1: A vs B (laud 1), C vs D (laud 2)
- Voor 2: A vs C, B vs D
- Voor 3: A vs D, B vs C

Iga meeskond mängib 3 matši, kokku 6 matši voorude jooksul.

**Reeglid:**

- Iga matš = 90 sek
- Iga meeskond valib enne matši, millist liidest kasutab (Tase 2 või Tase 3 — Tase 1 lubatud aga lollus)
- **Operaator vahetub iga matši järel** — pärast 3 matši on 3 erinevat operaatorit olnud, neljas pole veel. Vajadusel lisataisorts (vt allpool).
- Rotatsioon kontrollitakse: kui meeskond kasutab korraga matšis sama operaatorit, kes oli eelmises matšis, **kaotab automaatselt**

**Punktsüsteem:**

| Sündmus | Punktid |
|:---|:---|
| Matš võidetud | +1 |
| 4 erinevat operaatorit kogu turniiri jooksul | +2 |
| Iga inimene, kes ei saanud üldse operaatoriks olla | −1 |
| Iga matš mängitud Tase 1-ga (HAAS-liides) | +1 boonus (rasked tingimused) |

Maksimaalse boonuse saamiseks (4 operaatorit + Tase 1 mõni kord) peab meeskond:

- Kasutama kõiki 4 liiget operaatorina vähemalt korra
- Olema piisavalt julge proovima ka rasket liidest
- Mängima hästi (võidud on ikkagi alus)

**Lisamatš (~30 min)**. Kui kell lubab, üks lisamatš, kus iga meeskond peab kasutama **Tase 1 HAAS-liidest**. Mängitakse paaride peale (nt finaalis kaks paremat meeskonda). See on tagasivaade — hommikul ei saanud sa selle liidesega midagi teha, õhtul peaksid juba kuidagi mängima.

### Lõpetus (20 min)

Vaadatakse tulemused. Auhinnatakse parim meeskond. **Eraldi mainitakse parima rotatsiooniga meeskond** — see, kes ei jätnud kedagi vaatlejaks ja võitis seda toetudes mitmele inimesele.

Lühike refleksioon: **kui palju on hommiku Tase 1 ja õhtu Tase 3 vahet?** Kõik tunnevad. See ongi laagri tulemus.

---

## Kuidas see sarnaneb päris robootikaga

Sa istud Bombermani ees, agent mängib su eest. Sa ütled talle, mida tahad. Agent mõtleb, kasutab tööriistu, teeb otsuse. Sa vaatad, valideerid, vahel sekkud.

Sama tööriista (Claude Code) kasutavad päris tarkvarainsenerid päriselt. Mitte mängu mängimiseks — koodi kirjutamiseks, andmete analüüsimiseks, infrastruktuuri seadistamiseks. Sa ei õpi siin Bombermani mängima. Sa õpid **kuidas inimene ja agent koos töötavad** — mida öelda, kuidas vastust valideerida, millal sekkuda.

Kolm juhtimisliidest, mida päeva jooksul proovid, vastavad kolmele ajastule arvuti-inimese suhtluses:

- **HAAS CNC kontroller** = 80ndate–90ndate tööstuspingid, operaator juhib masinat liigese kaupa, käsk-haaval
- **AutoCAD DOS** = 90ndate erialatöö, käskude keel, kõrgem abstraktsioon
- **Claude Code agent** = 2020ndate AI-abi, eesmärgi-keel, masin teeb ise

Kogu inimese-arvuti suhtluse lugu mahub ühte Bombermani pärastlõunasse. Ja sa läbid selle ise.

Meeskonnatöö osa on samuti päris. Üksi suudad mängida — aga meeskond, kes oskab strateeg, vaatleja ja promptija eraldi panustada, võidab geeniust üksinda. **Punktid jagatakse nii, et üks geenius ei saa võita üksi.** Päris insenertöös sama lugu: kõige paremaid süsteeme ehitavad meeskonnad, mitte üksikud.

Kahe päeva lõpuks tead kolme asja:

- **Liides on tähtsam kui masin.** Sama Dobot — kolm erinevat mängu, sõltuvalt sellest, kuidas räägid.
- **Iga abstraktsioonisamm on uus võim ja uus risk.** Käsurida annab kiiruse, agent annab automaatsuse, aga eeldab head prompti.
- **Õige küsimus on parem kui kiire käsk** — ja kõige paremaid küsimusi sõnastatakse meeskonnaga koos.

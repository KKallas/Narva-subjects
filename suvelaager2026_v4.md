# Robootika suvelaager

## Kaks päeva, üks mäng, kolm juhtimisliidest

Laager kestab kaks päeva. Meil on kaks lauda, igal laual kaks Dobot MG400 robotkätt kõrvuti — kokku neli robotit ja kaks mänguplatsi. Igal laual on lisaks **kolm lauaarvutit**: kaks mängijatele (üks operaator meeskonna kohta) ja üks mängujuhile, kes haldab matše ja kalibreerib kaamera.

Õpilasi on 16; meeskondi neli, igaühes neli inimest. Iga matši ajal on **neli operaatorit** robotite taga ja **kaksteist meeskonnaliiget kõrval**. Need kaksteist pole pealtvaatajad — neil on kindlad rollid, ilma milleta meeskond mängu ei võida (vt allpool).

Mäng on **küber-tornkaitsemäng**: ekraani all servast tõuseb laine **ründevektoreid**, mis liiguvad üles asseti suunas. Sa pead nad **neutraliseerima** — viie füüsilise tööriistaga, mida robot ekraani peale paigutab. Sa ise nuppe ei vajuta. Sinu eest teeb seda robotkäsi. Sinu töö (kui oled operaator) on robotile öelda, kust tööriist võtta ja kuhu see panna. Sinu töö (kui oled tugiroll) on aidata operaatoril paremini öelda.

Päeva jooksul proovid kolme erinevat viisi robotiga rääkida. Igaüks eelmisest mugavam. Teisel päeval võistled samas mängus, mida hommikul vaevu mängida sai — ja näed must valgel, kui palju on rohkem aru saada.

Masin teeb täpselt seda, mida käsid. Esimesel päeval avastad, kui jube on käsku anda viisil, mis pole läbi mõeldud. Teisel päeval saad aru, kui palju kihte on ühe lihtsa "pane see sinna" ja päriselt panemise vahel.

---

## Mäng

Kaks robotit istuvad kõrvuti, nende vahel keskel on **monitor**. Üleval ekraani kohal on **tööriistakast** — alus, kus puhkavad viis M5 Atomit. Need on mängu tööriistad.

Mängu ülesanne: kaitsta ekraani ülaservas asuvat **assetti** (mingisugune andmeblokk) **ründevektorite** eest. Asseti avatud ülaserv on tema **ründe pind** (attack surface) — see, mille pihta vektorid tulevad. Ründevektorid tõusevad ekraani alaservast üles, igaühel oma kiirus, suund ja **ründevektori pikkus**. Mida pikem vektor, seda tugevam ründevektor — ja mida pikem helendav saba, mis tema järel käib.

Iga ründevektori neutraliseerimiseks on viis tööriista:

| Tööriist | Mõju |
|:---|:---|
| **Neutraliseerimine** | Neutraliseerib lähima ründevektori kohe |
| **Mesipuu** (Honeypot) | 50/50 — kas pühib kõik ründevektorid ulatuses ära, või nad paljunevad kaks korda, väiksemaks ja kiiremaks |
| **Liivakast** (Sandbox) | Külmutab kõik ründevektorid ulatuses 20 sekundiks |
| **DDoS** | Tõmbab ründevektorid enda juurde ja hoiab kinni, kuni keegi tööriista ära korjab |
| **Tarkvarauuendus** | Lühendab kõiki ekraanil olevaid ründevektoreid 30% võrra — vähendab ründe pinda |

Robotkäsi võtab tööriistakastist tööriista ja paneb selle ekraanile **sinna, kus tahad mõju**. Iga ala-mõjuga tööriist (Liivakast, Mesipuu, DDoS) katab ekraanil ringi — see on sinu **kaitse pind** (defense surface). Hästi paigutatud tööriistad katavad kaitse pinnaga võimalikult palju sissetulevaid ründevektoreid. Iga tööriist on füüsiliselt M5 Atom, mille **väikene ekraan näitab ikooni** (millise tööriistaga on tegu), **ülal asuv ArUco marker** annab kaamerale teada asukoha, **ümbritsev LED-rõngas käitub taimerina** ja **näitab kogu aeg värviga, kelle meeskonnale tööriist kuulub** (punane, roheline, või neutraalne valge).

**Ekraan ise pole puuteekraan.** Kaamera ja ArUco markerite kombo on see, mis "panemise" registreerib. Enne mängu kalibreeritakse, kus ekraan kaamerapildil asub — kaamerast nähtud tööriista positsioon → vastav ekraani-koordinaat → mäng saab sisendi.

**Viie tööriistaga alustad, viie tööriistaga lõpetad.** Uut ei tule. Tööriistad käivad mängu jooksul ringi:

- **Sama meeskonna omast tööriista** kui korjad enne taimeri lõppu — taimer tühistub, tööriist läheb kastusse tagasi, oma värvist neutraalsesse olekusse
- **Sama meeskonna omast tühjenenud tööriista** kui korjad — midagi ei juhtu, sinu enda surnud tööriist jääb surnuks
- **Vastasmeeskonna aktiivse tööriista** kui korjad — tööriist jätkab taimeriga, aga ArUco värv vahetub sinu meeskonna värviks. Kui see lõpuks plahvatab, läheb skoor sulle.
- **Vastasmeeskonna tühjenenud tööriista** kui korjad — tööriist taastub kasti neutraalsena, kasutamiseks järgmise paigutuse jaoks

Üks matš kestab **90 sekundit**. Lainete tempo on **adaptiivne** — kui meeskond hakkab tipus olema, läheb kiiremaks; kui asset on hädas, annab natuke aega tagasi. Eesmärk on, et keskmise meeskonna kaitse murraks läbi 60-90 sekundi sees.

**Tulemused:**

- **Ründevektorid võidavad** (asset hävib enne 90 sek) → mõlemad meeskonnad kaotavad, punkte ei jagata
- **Kaitsjad võidavad** (asset elab 90 sek üle) → mõlema meeskonna **neutraliseeritud ründevektorite kogupikkus** loendatakse ja võrreldakse. Suurema arvuga meeskond saab **3 punkti**, väiksem **1 punkti**.

Skoor on meeskonna värvi järgi: ainult need ründevektorid, mille neutraliseeris **sinu meeskonna värviga tööriist**, loevad sulle. Tarkvarauuendus ise ründevektorit ei neutraliseeri — see lühendab vektoreid ehk vähendab ründe pinda. Selline tööriist ei anna otsest skoori, aga aitab meeskonnal ellu jääda. Keegi peab vahel ohverdama, et meeskond üldse võidaks.

---

## Riistvara

Igal laual on sama komplekt.

**Kaks Dobot MG400 robotkätt** kõrvuti. Tööstuslik robotkäsi — sama, mis tehases asju kokku paneb, ainult väiksem. Igal robotil on pehme silikoonist ots **ArUco markeriga**, et kaamera tunneks tööriista asukohta täpselt.

**Tavaline 30" monitor** keskel laual, robotite vahel. Ei ole puuteekraan. Selle peal jookseb mäng. Mõlemad robotid ulatuvad ekraani kohale.

**Tööriistakast** ekraani kohal — lihtne riiul või alus, kus puhkavad viis M5 Atomit. Robotid ulatuvad nii ekraani kui kasti kohale.

**Viis M5 Atomit** — kõigil sama korpus, sama püsivara. Igal aktiivseks paigutatud Atomil on:
- Ette nähtud väike ekraan ikoonidega (Neutraliseerimine, Mesipuu, Liivakast, DDoS, Tarkvarauuendus)
- Pealmise küljega ArUco marker — kaamerale jaoks
- Perimeetri LED-rõngas — 5 sek taimeri visualiseerimine + meeskonna värv

**4K kaamera** otse ülevalt, vaatab ekraanile, tööriistakastile ja mõlemale robotile alla. See on "panemise tuvastaja" — näeb iga tööriista ArUco markerit ja teab täpselt, kus on parasjagu mis.

**Kolm lauaarvutit per laud:**

- **Punase meeskonna operaatori arvuti** — punase operaatori juhtimisliides
- **Rohelise meeskonna operaatori arvuti** — rohelise operaatori juhtimisliides
- **Mängujuhi arvuti** — kohtuniku jaoks: mäng ise, kaamera kalibratsioon, taimer, skoor

**Taustateenus:** Python (sama, mis varasematel päevadel). Iga arvuti räägib taustateenusega, kes räägib robotite ja mänguga.

---

## Kalibreerimine enne matši

Enne iga matši algust kalibreerib mängujuht oma arvutist kaamera ja ekraani omavahel:

1. Kaamera teeb pildi ekraanist ja tööriistakastist
2. Mängujuhi liides näitab pilti ja küsib: "klõpsa ekraani neljal nurgal"
3. Pärast nelja klõpsu teab süsteem, kus ekraan kaamera-pildil on
4. Mängujuht paneb viis M5 Atomit kasti ja annab igaühele rolli (slot 1 = Neutraliseerimine, slot 2 = Mesipuu, jne); süsteem loeb iga tööriista ArUco ID-d ja salvestab algasendi

Pärast kalibreerimist: kui robot toob tööriista ekraani peale, näeb kaamera selle ArUco markeri uut asendit ekraani kohal ja loeb selle tööriista paigutuseks.

Kalibreerimine võtab umbes 30 sekundit. Tehakse uuesti, kui keegi liigutab kaamerat või kui ekraan nihkub.

---

## Kolm juhtimisliidest

Sama mäng, sama riistvara — kolm erinevat viisi öelda robotile, kust tööriist võtta ja kuhu see panna. Iga uus liides on eelmisest mugavam ja räägib robotile kõrgemal abstraktsioonitasemel.

### Tase 1 — Pime liigese-juhtimine

Veebilehel on **kuus liugurit** — üks iga roboti liigese kohta. Iga liugur näitab liigese hetkenurka kraadides. Lisaks on nupud:

- **Haara** — sulgeb tööriista otsa pehmet haaratsit
- **Vabasta** — avab haaratsi
- **EMERGENCY STOP** — kõik kohe seisma

**Ja ainult see.** Sa **ei näe** kaamerapilti, sa **ei näe** ekraani, sa **ei näe**, kus robot parasjagu on. Sul on ainult numbrid: kuus liigese-nurka. Liiguta liugureid, vaata, kuidas numbrid muutuvad, jälgi (ainult oma silmadega laua peal) kuhu robot läheb.

Toore jõu liides — sa pead robotiga rääkima tema enda keeles, liigese kaupa. Tahad tööriista kindlasse kohta? Pead **välja mõtlema**, milline liigese-kombinatsioon sinu tahetud asendi annab.

Tahtlikult ebamugav, **aga tööstuses oli täpselt selline viis robotitega rääkimine 80ndatel ja 90ndatel normaalne**. Robootika kursuste algajad treenivad ka tänapäeval seda, sest see annab füüsilise tunnetuse, kuidas liigeste muutus muutub ruumiliseks asendiks.

---

#### Robootika põhimõte: Liigese-ruumi intuitsioon (forward kinemaatika)

Kui sa juhid robotit liigese kaupa, pead peast välja mõtlema, kuidas üks liigese liigutus muutub tööriista asendiks ruumis. Dobot MG400-l on lihtne mudel:

- **Liigend 1** (alus pööramine) → tööriista **suund** ruumis (vasak-parem nurk)
- **Liigend 2 ja 3 summa** (õla- ja küünar-liigesed kokku) → tööriista **kaugus** robotist
- **Liigend 2 ja 3 suhe** → tööriista **kõrgus** maapinnast

Mängu jooksul hakkad ise tunnetama: "tahan tööriista vasakule → pööran liigend 1", "tahan kõrgemale → muudan liigend 2 ja 3 suhet, mitte nende summat". See on **forward kinemaatika intuitsioon** — liigese-keelest ruumi-keelde.

Sa ise oled see arvuti, kes seda teisendab. Sellepärast on Tase 1 raske. Järgmised tasemed lasevad seda tööd masinal teha — sina räägid otse ruumi-keeles.

### Tase 2 — Pildipõhine "kliki ja jää"

Veebilehel on **kaamera otsevaade** ülevalt — sa näed sama pilti, mida kaamera. Ekraan, tööriistakast, robot, kõik. Tõid liigurid ja liigeste numbrid on **kadunud**.

Töövoog on lihtne:

- Vaatad pildil, kus on tööriistakastis tööriist, mida tahad → **klõpsad selle peale** → robot võtab selle
- Vaatad pildil, kuhu tahad tööriista panna ekraanile → **klõpsad sinna** → robot paneb tööriista sinna

Kaks klõpsu = üks tööriistakäik. Süsteem teeb robotile vajalikud arvutused ise — sa räägid ainult ruumi-keelt ("siia"), mitte enam liigese-keelt ("Liigend 1 peab olema 37°").

Kiirem kui Tase 1, sest sa ei pea enam ise olema kalkulaator. Aga sa ikkagi peab iga sammu eraldi teadma ja klõpsama. Mängu ajal mõtled klõpsudele, mitte mängule.

---

#### Robootika põhimõte: Pöördkinemaatika ja LUT (Lookup Table)

Kui sa klõpsad pildil "siia", siis robot ei tea otse, milliseid liigeseid pöörata. Süsteem peab arvutama vastupidiselt forward kinemaatikale: **etteantud (x, y, z) jaoks, milline on iga liigese nurk?** Seda nimetatakse **pöördkinemaatikaks** (inverse kinematics, IK).

IK matemaatika on raske ja aeglane reaalajas arvutada. Praktikas kasutatakse sageli **LUT-i (Lookup Table)** — eelnevalt välja arvutatud või mõõdetud tabel, kus iga (x, y, z) on seotud vastavate liigeste nurkadega:

```
(x, y, z)      → (j1°, j2°, j3°, j4°)
(0, 0, 100)    → (0°,   45°, −45°, 0°)
(50, 0, 100)   → (0°,   53°, −38°, 0°)
(50, 50, 100)  → (45°,  53°, −38°, 0°)
(200, 150, 0)  → (37°,  78°, −12°, 0°)
...
```

Kalibreerimine: enne mängu liigutab süsteem roboti läbi paljude (x, y, z) punktide ja salvestab iga punkti jaoks liigeste nurgad. Tekib LUT. Pärast seda: klõpsad pildil "siia" (x, y) → vaata LUT-st lähim punkt → leia liigeste nurgad → liiguta.

**Tase 2 töötab sellepärast, et keegi (mängujuht või sina kalibreerimise käigus) on selle LUT-i ehitanud.** Sa räägid x-y keeles, robot saab aru, sest LUT tõlgib. Tase 1 puhul polnud sul LUT-i — pidid ise olema kalkulaator.

### Tase 3 — VS Code + Claude Code agent

Sama tööriist, millega oled eelnevatel päevadel ülesandeid lahendanud. Avad VS Code, sees on Claude Code. Taustateenuses on tööriistad valmis:

- `get_game_state()` — tagastab juba **töödeldud andmed** (sinu meeskonna värv, asseti HP, kõik ekraanil olevad ründevektorid koos nende kiiruse-pikkuse-suunaga, tööriistakasti seis) JSON-ina
- `pick_tool(tool_id)` — robot võtab tööriistakastist nimetatud tööriista
- `place_tool(x, y)` — robot paneb hetkel käeshoitava tööriista ekraani kohale antud koordinaadile
- `recall_tool(tool_id)` — robot korjab oma värvi aktiivse tööriista tagasi enne taimeri lõppu

**Tähtis:** agendile ei anta toort kaamerapilti otsustamiseks. Enne agenti on **objekti-klassifikaator** (YOLO või lihtsam värvi-klassifikaator), mis pildi peal ära tunneb, kus on mis. Agent saab need positsioonid juba selgelt välja loetuna. Tema töö on **otsustada, mida teha**, mitte näha.

Annad agendile lihtsa eesmärgi: *"Mängid küberkaitse-mängu. Vaata get_game_state'i andmeid, kaitse assetti, eelista pikemate vektoritega ründevektoreid, jälgi tööriistakogust, korja vastase tühjenenud tööriistu kasti tagasi."* Agent kutsub `get_game_state()`, mõtleb, kutsub `pick_tool()`, `place_tool()`, vaatab uuesti.

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

- **YOLO (või lihtsam värvi-klassifikaator)** vaatab kaamera-pilti, leiab kus on ründevektorid, milline on iga ründevektori pikkus, kus on tööriistad. Tagastab struktureeritud andmed JSON-ina.
- **Claude Code (LLM)** võtab need andmed, otsustab strateegia, kutsub `pick_tool()` ja `place_tool()` käske.

Agent ei pea pilti raw kujul vaatama. **Ta saab juba positsioonid.** Tema töö on otsustada, mitte näha.

See on **õige arhitektuuri näide**: igale ülesandele oma mudel. Sama loogika kehtib päris robootikas — autotehases on YOLO koosteliinil tuvastamas, mis osa läbi liigub; eraldi planeerimis-mudel otsustab, kuhu robotkäsi liigub. Marsi roveris on omaette nägemis-mudel, mis tuvastab kive ja takistusi; eraldi otsustusloogika valib tee.

**Õppetund kogu laagrist:** ära aja mudeleid segi. Igaüks on hea omas ülesandes. Halb arhitekt paneb LLM-i pilti vaatama (aeglane, ebatäpne) või YOLO strateegiat tegema (ei oska). Hea arhitekt teab, mida kuhu panna.

---

## Meeskonnatöö — kuidas 12 mitte-operaatorit kaasa aitavad

Iga matši ajal on 4 operaatorit (üks meeskonna kohta) ja 12 inimest istuvad kõrval. Need kõrval-inimesed pole pealtvaatajad. Iga meeskonna sees on iga matši kohta **neli kindlat rolli**, mille vahel meeskond ise jaotab. Roteerumine on **kohustuslik** — sama inimene ei tohi olla samas rollis kahel järjestikusel matšil.

### Neli rolli meeskonna kohta

**Operaator** — istub roboti taga, kasutab parasjagu kasutusel olevat juhtimisliidest. See on füüsiline tegija.

**Strateeg** — vaatab mängu ekraani, ütleb operaatorile valju häälega, mida teha. "Pikk vektor tuleb paremalt — paneme Liivakasti! Vastane jättis Mesipuu tühjaks — korja kohe ära!" Tema vastutab strateegia eest, operaator täidab.

**Vaatleja** — vaatab **vastasmeeskonna** poolt: mida nad teevad, mis tööriistu nad on aktiveerinud, mis on nende skoor. Märgib mustreid: "Vastane raiskab Tarkvarauuendust liiga vara", "vastasel võtab agendil tööriista valida 6 sekundit". Nende info läheb järgmise matši operaatorile.

**Promptija/Kodija** — parandab **matšide vahel** liidest või agendi prompti. Tase 1 puhul: midagi ei muuda (lihtsalt vaatab ja õpib). Tase 2 puhul: võib teha makrosid sagedasti kasutatud klõpsude jadadele. Tase 3 puhul: kirjutab Claude Code agendi prompti paremaks pärast iga matši — võtab eelmise matši leidudest õppe, paneb need agendile reegliteks.

### Rotatsioon

Iga meeskond peab läbima **kõik neli rolli iga matši ajal**. Pärast matši rollid vahetuvad. Pärast nelja matši on iga inimene olnud kõigis neljas rollis.

**Punktsüsteem soosib rotatsiooni:**

- Iga võidetud matš (kus sinu meeskond oli suurema skooriga) = **3 punkti**
- Iga matš, kus su meeskond elas kaitsjana üle (aga teine meeskond skoorit rohkem) = **1 punkt**
- Iga matš, kus asset hävis = **0 punkti**
- Kui meeskond on kasutanud kogu turniiri jooksul **nelja erinevat operaatorit** = lisaks **+2 boonust**
- Iga "vahele jäetud" inimene (kes ei saanud kordagi operaator olla) = **−1 punkt**

Lühidalt: meeskond, kelle iga liige operaator saab olla, võidab. Meeskond, kus üks geenius mängib kogu aja, kaotab — isegi kui geenius võidab kõik matšid üksinda.

See on tahtlik. Päris robootika ja päris insenertöö ei juhtu üksinda. Sa ehitad meeskonnaga, dokumenteerid teistele, võtad nõu vastu. See laager õpetab seda kohe selgeks.

---

## Esimene päev — proovimatš ja Tase 2 õppesessioon

**Aeg:** 2,5 tundi (1 h + 1,5 h, üks vahepaus).

### Slot 1 (1 tund) — Avapresentatsioon ja Tase 1 proovimatš

**Avapresentatsioon (15 min).** Mängujuht näitab korraks, mis ekraanil toimub: ründevektorid tõusevad alt üles, asset on ülal, tööriistakast on robotite kohal. Tutvustab viite tööriista (Neutraliseerimine, Mesipuu, Liivakast, DDoS, Tarkvarauuendus), tutvustab tööriista omanduse reegleid (korjamine = taimeri tühistus, tühjenenud vastase tööriist = neutraalsesse kasti tagasi), tutvustab nelja rolli ja rotatsiooni.

**Proovimatš — Tase 1 pime liigese-juhtimine (45 min).** Igale meeskonnale antakse Tase 1 liides — kuus liugurit, paar nuppu, mitte mingit kaamerapilti. Rohkem juhiseid pole. Roteeritakse kohti: matšide vahel vahetuvad operaatorid. Esimene matš 90 sek, siis paus, rollid vahetuvad, järgmine matš.

Neli matši 45 minuti sees — iga meeskonna iga liige saab kord operaatoriks. Naerdakse. Keegi ei saa aru, kus parasjagu nende tööriist on — peale seda, kui esimene liigend pööras valele poole. Üks paneb DDoS-i hoopis tööriistakasti kõrvale ja kaamera ei näe seda enam. Asset hävib igas matšis.

Pärast matše arutletakse minut kahe peale: **mida raske oli? Miks?** Vastus tuleb tavaliselt välja — "robot ei tee seda, mida ma tahan." Mis on tegelikult vale viis öelda. Õige vastus: **ma ei oska robotile õigesti öelda, mida ma tahan**. Liides on liiga toore.

See vahe — "robot ei tee õigesti" versus "ma ei räägi õigesti" — on kogu laagri filosoofiline alus.

### Slot 2 (1,5 tundi) — Õppesessioon 1: Pildipõhine liides

Esimene päris õppesessioon. Veebilehel on nüüd **kaamera otsevaade** ülevalt — sa näed sama pilti, mida kaamera. Klõpsad tööriistakastis tööriistal → robot võtab. Klõpsad ekraanil → robot paneb sinna.

**Tutvumine (20 min).** Kõigepealt proovige liidest tundma — klõpsige tööriistal, jälgige, kuidas robot võtab. Klõpsige eri kohtades ekraanil, vaadake, kuhu robot paneb. Õppige kus on tööriistakasti slot 1, kus slot 5. Tehke endale kaardistus peas: tööriistakast üleval, ründevektorid alt, asset päris ülal.

**Harjutusmatšid (50 min).** Neli matši 90 sek igaüks, rollide rotatsioon nagu enne. Kindlasti parem kui Tase 1. Aga klõpsamine võtab aega — uue tööriista valimine, õige koha klõpsamine, robot liigutab, paigutab. Vahepeal jõuab vastane juba kaks omakorda paigutada.

Promptija/kodija rolli sisu siin: võib hakata tegema **makrosid** sagedasti kasutatud klõpsude jadadele. Näiteks: "Vasak servale Liivakast" = võta kasti slot 3 → pane ekraani vasakule poole. Üks nupp = kogu jada. Need makrod aitavad operaatorit järgmistes matšides — eduka käsutaja töö läheb järgmisele meeskonnaliikmele üle.

**Arutelu (20 min).** Mida õpiti? Tavaliselt — "klõpsamine on kiirem kui liugurid, aga ikka aeglane mängu jaoks." See on õige õpik. **Iga abstraktsioonisamm vähendab keerukust, aga ei pruugi olla veel piisav.** Ka selgub: meeskond, kus promptija on teinud head makrod, on operaatorile selgelt eelisseisus. Toetav töö maksab end ära.

---

## Teine päev — Claude Code agent ja võistlus

**Aeg:** 3 tundi (1,5 h + 1,5 h, üks vahepaus).

### Slot 3 (1,5 tundi) — Õppesessioon 2: Claude Code agent

Avad VS Code, sees Claude Code. Taustateenuses on tööriistad: `get_game_state`, `pick_tool`, `place_tool`, `recall_tool`. Sama Claude Code, millega oled juba muid ülesandeid lahendanud — uus on ainult mängu tööriistakomplekt.

**Esmane prompt (20 min).** Meeskond koos kirjutab esimese versiooni prompti agendile. Näiteks: "Mängid küberkaitse-mängu. Vaata get_game_state, kaitse assetti. Eelista pikemate vektoritega ründevektoreid. Kasuta Liivakasti, kui mitu ründevektorit lähestikku. Kasuta Tarkvarauuendust, kui asset alla 30%." Käivitavad ja vaatavad.

**Harjutusmatšid (60 min).** Neli matši nagu enne, rollide rotatsioon. Esimesed katsed on tihti katastroofilised — agent näeb hästi, aga mõtleb aeglaselt (iga ring 2–5 sekundit). Vahel paneb agent Neutraliseerimise hoopis lähima vältimatu ründevektori peale, mille kõrval oli teine vältimatu ründevektor. Mängitavus sõltub palju promptist.

**Promptija roll** on selles sessioonis kõige olulisem. Iga matši järel parandab ta prompti vastavalt eelmisele matšile. "Agent ei kaitsta assetti aktiivsest tööriistasaarest enam kui 2 sek → lisa promptisse 'kontrolli kõigepealt, kas mõni vana tööriist on tühjenenud, korja kasti tagasi'." "Agent raiskas Tarkvarauuenduse esimese laine peal → lisa 'Tarkvarauuendust kasuta ainult siis, kui ekraanil on vähemalt 5 ründevektorit pikkusega üle 30%'."

Pärast nelja matši on prompt tunduvalt parem kui esimene. Mõni meeskond saab võidu agendiga, teine kaotab pidevalt. Vahe pole agendis — vahe on selles, kui hästi meeskond agendile selgitas, mida nad tahavad.

**Arutelu (10 min).** **Õige küsimuse esitamine on parem kui kiire käsk.** Sama agent, neli erinevat prompti — üks võidab, teine kaotab.

### Slot 4 (1,5 tundi) — Turniir

**Avapresentatsioon võistlusreeglitest (10 min).**

Meeskonnad on neli, igaüks neljaliikmeline. Mängitakse **ringturniiri**:

- **Voor 1:** Punane vs Roheline (laud 1), Sinine vs Kollane (laud 2)
- **Voor 2:** Punane vs Sinine (laud 1), Roheline vs Kollane (laud 2)
- **Voor 3:** Punane vs Kollane (laud 1), Roheline vs Sinine (laud 2)

Iga meeskond mängib 3 matši, mille kõigis on partner üks teistest. Voorud toimuvad mõlemal laual paralleelselt.

**Reeglid:**

- Iga matš = 90 sek
- Iga meeskond valib enne matši, millist liidest kasutab (Tase 2 või Tase 3 — Tase 1 on lubatud aga rumalus)
- **Operaator vahetub iga matši järel** — pärast 3 matši on 3 erinevat operaatorit olnud, neljas vajab lisamatši
- Rotatsioon kontrollitakse: kui meeskond kasutab samas matšis sama operaatorit, kes oli eelmises matšis, **see meeskond kaotab kohe**

**Punktsüsteem:**

| Sündmus | Punktid |
|:---|:---|
| Matš võidetud (sinu meeskond oli suurema skooriga) | +3 |
| Matš kaitsmise võit aga väiksem skoor | +1 |
| Matš kus asset hävis | 0 |
| 4 erinevat operaatorit kogu turniiri jooksul | +2 boonust |
| Iga inimene, kes ei saanud üldse operaatoriks olla | −1 |
| Iga matš mängitud Tase 1 pime liigese-juhtimisega | +1 boonus (raske tingimus) |

Maksimaalse boonuse saamiseks peab meeskond:

- Kasutama kõiki 4 liiget operaatorina vähemalt korra
- Olema piisavalt julge proovima ka rasket liidest (vähemalt korra)
- Mängima hästi (võidud on ikkagi alus)

**Lisamatš (~30 min).** Kui kell lubab, üks lisamatš, kus iga meeskond peab kasutama **Tase 1 pime liigese-juhtimist**. Mängitakse paaride peale (näiteks finaalis kaks paremat meeskonda). See on tagasivaade — hommikul ei saanud sa selle liidesega midagi teha, õhtul peaksid juba kuidagi mängima.

### Lõpetus (20 min)

Vaadatakse tulemused. Auhinnatakse parim meeskond. **Eraldi mainitakse parima rotatsiooniga meeskond** — see, kes ei jätnud kedagi vaatlejaks ja võitis seda toetudes mitmele inimesele.

Lühike refleksioon: **kui palju on hommiku Tase 1 ja õhtu Tase 3 vahet?** Kõik tunnevad. See ongi laagri tulemus.

---

## Kuidas see sarnaneb päris robootikaga

Sa istud küberkaitse-mängu ees, agent mängib su eest. Sa ütled talle, mida tahad. Agent mõtleb, kasutab tööriistu, teeb otsuse. Sa vaatad, valideerid, vahel sekkud.

Sama tööriista (Claude Code) kasutavad päris tarkvarainsenerid päriselt. Mitte mängu mängimiseks — koodi kirjutamiseks, andmete analüüsimiseks, infrastruktuuri seadistamiseks. Sa ei õpi siin tornkaitsemängu mängima. Sa õpid **kuidas inimene ja agent koos töötavad** — mida öelda, kuidas vastust valideerida, millal sekkuda.

Kolm juhtimisliidest, mida päeva jooksul proovid, vastavad kolmele ajastule arvuti-inimese suhtluses:

- **Pime liigese-juhtimine** = 80ndate–90ndate tööstuspingid, operaator juhib masinat liigese kaupa, käsk-haaval
- **Pildipõhine "kliki ja jää"** = 2000ndate CAD/CAM-tarkvara, kus räägid ruumi-keeles, masin teisendab liigese-keelde
- **Claude Code agent** = 2020ndate AI-abi, eesmärgi-keel, masin teeb ise

Kogu inimese-arvuti suhtluse lugu mahub ühte küberkaitse-pärastlõunasse. Ja sa läbid selle ise.

Meeskonnatöö osa on samuti päris. Üksi suudad mängida — aga meeskond, kes oskab strateegi, vaatleja ja promptija eraldi panustada, võidab geeniust üksinda. **Punktid jagatakse nii, et üks geenius ei saa võita üksi.** Päris insenertöös sama lugu: kõige paremaid süsteeme ehitavad meeskonnad, mitte üksikud.

Kahe päeva lõpuks tead kolme asja:

- **Liides on tähtsam kui masin.** Sama Dobot — kolm erinevat mängu, sõltuvalt sellest, kuidas räägid.
- **Iga abstraktsioonisamm on uus võim ja uus risk.** Kliki-liides annab kiiruse, agent annab automaatsuse, aga eeldab head prompti.
- **Õige küsimus on parem kui kiire käsk** — ja kõige paremaid küsimusi sõnastatakse meeskonnaga koos.

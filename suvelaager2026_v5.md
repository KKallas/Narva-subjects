# Robootika suvelaager

## Kaks päeva, üks mäng, kolm juhtimisliidest

Laager kestab kaks päeva. Meil on kaks lauda, igal laual kaks Dobot MG400 robotkätt kõrvuti — kokku neli robotit ja kaks mänguplatsi. Igal laual on lisaks **kolm lauaarvutit**: kaks mängijatele (üks operaator meeskonna kohta) ja üks mängujuhile, kes haldab matše ja kalibreerib kaamera.

Õpilasi on 16; meeskondi neli, igaühes neli inimest. Iga matši ajal on **neli operaatorit** robotite taga ja **kaksteist meeskonnaliiget kõrval**. Need kaksteist pole pealtvaatajad — neil on kindlad rollid, ilma milleta meeskond mängu ei võida (vt allpool).

Mäng on **küberkaitse-mäng**: ekraanil ilmuvad küberohud, igaühel oma väärtus (vektori pikkus) ja aktiivne aeg. Sa pead nad maha lööma — pannes nende peale neljast oma märgist ühe. Sa ise nuppe ei vajuta. Sinu eest teeb seda robotkäsi. Sinu töö (kui oled operaator) on robotile öelda, kust märk võtta ja kuhu see panna. Sinu töö (kui oled tugiroll) on aidata operaatoril paremini öelda.

Päeva jooksul proovid kolme erinevat viisi robotiga rääkida. Igaüks eelmisest mugavam. Teisel päeval võistled samas mängus, mida hommikul vaevu mängida sai — ja näed must valgel, kui palju on rohkem aru saada.

Masin teeb täpselt seda, mida käsid. Esimesel päeval avastad, kui jube on käsku anda viisil, mis pole läbi mõeldud. Teisel päeval saad aru, kui palju kihte on ühe lihtsa "pane see sinna" ja päriselt panemise vahel.

---

## Mäng

Kaks robotit istuvad kõrvuti, nende vahel keskel on **monitor**. Mõlema roboti enda küljele jääb **märkide kast** — neli M5 Atom märki igale meeskonnale. Punased märgid punase kastiga, rohelised märgid rohelise kastiga.

Mängu ülesanne: ekraanil tekivad **küberohud** suvalistesse kohtadesse, igaühel oma vektori pikkus (väärtus) ja aktiivne aeg (kui kaua oht ekraanil püsib). Mida pikem vektor, seda väärtuslikum oht — ja seda lühem aeg, kui kaua oht ekraanil püsib enne, kui ta ise kaob.

| Vektori pikkus | Aktiivne aeg | Riski profiil |
|:---|:---|:---|
| 5–10 (lühike) | 12–14 sek | Ohutu — palju aega märki panna |
| 11–20 (keskmine) | 8–10 sek | Tavaline — vastase varastamise risk on päris |
| 21–30 (pikk) | 6–7 sek | Vaielatav — mõlemad meeskonnad jahivad teda |

Robotkäsi võtab kastist märgi, viib ekraanile ja **paneb selle ohule peale**. Sellega algab **5 sekundi tegevus**:

1. Märgi LED-rõngas hakkab tühjenema sinu meeskonna värvis
2. Vastane saab selle 5 sekundi jooksul märgi sinu pealt **näpata** (võtta üles)
3. Kui vastane saab märgi **enda kasti** tagasi enne, kui tema enda taimer (sama 5 sek) saab läbi → **vastane varastab punktid**
4. Kui vastane ei jõua → märk plahvatab teel ja oht on ikkagi neutraliseeritud — **algne paigutaja saab punktid**

Iga oht, mille olid sa ekraanilt maha löönud, lisab oma vektori pikkuse sinu meeskonna skoorile.

**Märkidega varieeruvad ka asjad ringi:**

- **Pärast skoorimist** märk jääb ekraanile "tühjana" sinna kohta, kuhu paigutati. Et seda uuesti kasutada, peab keegi (oma meeskonna või vastase robot) selle ekraanilt üles korjama ja kasti viima
- **Sama meeskonna kasti viidud tühi märk** läheb ringi tagasi — uuesti kasutatav
- **Vastase kasti viidud tühi märk** jääb sinna seisma — kasutamiseks vastase meeskonnale, aga kui nad selle uuesti panevad, läheb skoor **sinu** meeskonnale (sest ArUco värv on sinu)

**Vastase kasti tühjendamine** — märkide vargus:

- Vastase robot võib **ületada laua** ja võtta sinu kastist **kasutamata märgi** (mitte ekraanil oleva, vaid kastis seisva)
- Ta veab selle enda kasti. Sinul on nüüd üks märk vähem
- Märgi ArUco värv ei muutu — see kuulub ikka sulle. Aga sa ei pääse sellele enam ilma vastase kastist tagasi võtmata

Vastase tühjendamine maksab aega: robot lendab edasi-tagasi (3-4 sek), mille jooksul ei saa keegi punkte. Otsus on: kas hoida vastast väiksemas seisus väärt selle aja kaotust või mitte.

---

### Mängu reeglid kokkuvõttena

- Iga meeskond alustab nelja märgiga oma kastis
- Ohud tekivad ekraanile suvalistesse kohtadesse, igaühel oma vektori pikkus ja aktiivne aeg
- Pane märk ohule → 5 sek taimer → vastane saab näpata
- Kui näppab ja jõuab kasti → varastas punktid
- Kui ei jõua → punktid algsele paigutajale
- Tühjenenud märgid jäävad ekraanile, kuni keegi need üles korjab
- Vastase kasti tühjendamine = denial-taktika

Üks matš kestab **90 sekundit**. Lainete tempo on **adaptiivne** — alguses kerge, lõpus tihedam.

**Tulemused:**

- **Suurema skooriga meeskond** → võitja, saab **3 punkti**
- **Väiksema skooriga meeskond** → kaotaja, saab **1 punkti** (osavõtu eest)
- **Viik** (täpselt sama skoor, harva) → mõlemad **2 punkti**

Erinevalt eelmisest versioonist pole siin "mõlemad kaotavad" tulemust — iga matš annab mõlemale meeskonnale punkte.

---

## Riistvara

Igal laual on sama komplekt.

**Kaks Dobot MG400 robotkätt** kõrvuti. Tööstuslik robotkäsi — sama, mis tehases asju kokku paneb, ainult väiksem. Igal robotil on pehme silikoonist ots **ArUco markeriga**, et kaamera tunneks tööriista asukohta täpselt.

**Tavaline 30" monitor** keskel laual, robotite vahel. Ei ole puuteekraan. Selle peal jookseb mäng. Mõlemad robotid ulatuvad ekraani kohale ja mõlema meeskonna kasti kohale.

**Kaks märkide kasti** — punase meeskonna oma punase roboti pool, rohelise oma rohelise pool. Kõik märgid on visuaalselt **ühesugused** (samad korpused, sama püsivara) — neid eristab ainult ArUco markeri värv (meeskonna omandi tähis).

**Kaheksa M5 Atomit** — neli punast, neli rohelist. Igal Atomil on:
- Ette nähtud väike ekraan kilbi ikooniga (kõik märgid samad — pole erinevaid tööriistatüüpe)
- Pealmise küljega ArUco marker — kaamerale jaoks, värv = omanik
- Perimeetri LED-rõngas — 5 sek taimeri visualiseerimine + meeskonna värv

**4K kaamera** otse ülevalt, vaatab ekraanile, kummalegi kastile ja mõlemale robotile alla.

**Kolm lauaarvutit per laud:**

- **Punase meeskonna operaatori arvuti** — punase operaatori juhtimisliides
- **Rohelise meeskonna operaatori arvuti** — rohelise operaatori juhtimisliides
- **Mängujuhi arvuti** — kohtuniku jaoks: mäng ise, kaamera kalibratsioon, taimer, skoor

**Taustateenus:** Python (sama, mis varasematel päevadel). Iga arvuti räägib taustateenusega, kes räägib robotite ja mänguga.

---

## Kalibreerimine enne matši

Enne iga matši algust kalibreerib mängujuht oma arvutist kaamera ja mängulauad omavahel:

1. Kaamera teeb pildi ekraanist, mõlemast kastist, mõlemast robotist
2. Mängujuhi liides näitab pilti ja küsib: "klõpsa ekraani neljal nurgal, siis kummagi kasti neljal nurgal"
3. Pärast klõpse teab süsteem, kus on ekraan ja kastid kaamera-pildil
4. Mängujuht paneb neli M5 Atomit punasesse kasti, neli rohelisesse; süsteem loeb iga märgi ArUco ID-d ja omistab värvi (punased ArUcod punase meeskonnale, rohelised rohelisele)

Pärast kalibreerimist: kui robot toob märgi ekraanile, näeb kaamera selle ArUco asendit ja loeb selle paigutuseks. Kui keegi viib märgi vale kasti, kaamera näeb seda kohe.

Kalibreerimine võtab umbes 30 sekundit.

---

## Kolm juhtimisliidest

Sama mäng, sama riistvara — kolm erinevat viisi öelda robotile, kust märk võtta ja kuhu see panna. Iga uus liides on eelmisest mugavam ja räägib robotile kõrgemal abstraktsioonitasemel.

### Tase 1 — Pime liigese-juhtimine

Veebilehel on **kuus liugurit** — üks iga roboti liigese kohta. Iga liugur näitab liigese hetkenurka kraadides. Lisaks on nupud:

- **Haara** — sulgeb tööriista otsa pehmet haaratsit
- **Vabasta** — avab haaratsi
- **EMERGENCY STOP** — kõik kohe seisma

**Ja ainult see.** Sa **ei näe** kaamerapilti, sa **ei näe** ekraani, sa **ei näe**, kus robot parasjagu on. Sul on ainult numbrid: kuus liigese-nurka. Liiguta liugureid, vaata, kuidas numbrid muutuvad, jälgi (ainult oma silmadega laua peal) kuhu robot läheb.

Toore jõu liides — sa pead robotiga rääkima tema enda keeles, liigese kaupa. Tahad märki kindlasse kohta? Pead **välja mõtlema**, milline liigese-kombinatsioon sinu tahetud asendi annab.

Tahtlikult ebamugav, **aga tööstuses oli täpselt selline viis robotitega rääkimine 80ndatel ja 90ndatel normaalne**. Robootika kursuste algajad treenivad ka tänapäeval seda, sest see annab füüsilise tunnetuse, kuidas liigeste muutus muutub ruumiliseks asendiks.

---

#### Robootika põhimõte: Liigese-ruumi intuitsioon (forward kinemaatika)

Kui sa juhid robotit liigese kaupa, pead peast välja mõtlema, kuidas üks liigese liigutus muutub tööriista asendiks ruumis. Dobot MG400-l on lihtne mudel:

- **Liigend 1** (alus pööramine) → tööriista **suund** ruumis (vasak-parem nurk)
- **Liigend 2 ja 3 summa** (õla- ja küünar-liigesed kokku) → tööriista **kaugus** robotist
- **Liigend 2 ja 3 suhe** → tööriista **kõrgus** maapinnast

Mängu jooksul hakkad ise tunnetama: "tahan tööriista vasakule → pööran liigend 1", "tahan kõrgemale → muudan liigend 2 ja 3 suhet, mitte nende summat". See on **forward kinemaatika intuitsioon** — liigese-keelest ruumi-keelde.

Sa ise oled see arvuti, kes seda teisendab. Sellepärast on Tase 1 raske. Järgmised tasemed lasevad seda tööd masinal teha — sina räägid otse ruumi-keeles.

### Tase 2 — Pildipõhine "WASD-liigutus"

Veebilehel on **kaamera otsevaade** ülevalt — sa näed sama pilti, mida kaamera. Ekraan, mõlemad kastid, robot, kõik. Liigurid ja liigeste numbrid on **kadunud**.

Töövoog on lihtne:

- **WASD klahvid** (või nooleklahvid teise meeskonna jaoks) liigutavad roboti otsa kaamerapildis X/Y telgedel
- **Tühik** (või Enter) — haara/vabasta märk
- Pole vaja koordinaate trükkida, lihtsalt suuna käsi sinna, kus tahad olla

See on klassikaline mängijate juhtimine — sarnaselt nagu vanasti arkaadimängudes. Tunneb, kuidas sa juhid otse käe asendit, mitte iga liigese eraldi.

Kiirem kui Tase 1, sest sa ei pea enam ise olema kalkulaator. Aga ikkagi pead silmaga jälgima ja igale liigutusele konkreetse käsu andma. Mängu ajal mõtled ikka käsklustele, mitte mängule.

---

#### Robootika põhimõte: Pöördkinemaatika ja LUT (Lookup Table)

Kui sa vajutad nooleklahvi, robot ei tea otse, milliseid liigeseid pöörata. Süsteem peab arvutama vastupidiselt forward kinemaatikale: **etteantud (x, y, z) jaoks, milline on iga liigese nurk?** Seda nimetatakse **pöördkinemaatikaks** (inverse kinematics, IK).

IK matemaatika on raske ja aeglane reaalajas arvutada. Praktikas kasutatakse sageli **LUT-i (Lookup Table)** — eelnevalt välja arvutatud või mõõdetud tabel, kus iga (x, y, z) on seotud vastavate liigeste nurkadega:

```
(x, y, z)      → (j1°, j2°, j3°, j4°)
(0, 0, 100)    → (0°,   45°, −45°, 0°)
(50, 0, 100)   → (0°,   53°, −38°, 0°)
(50, 50, 100)  → (45°,  53°, −38°, 0°)
(200, 150, 0)  → (37°,  78°, −12°, 0°)
...
```

Kalibreerimine: enne mängu liigutab süsteem roboti läbi paljude (x, y, z) punktide ja salvestab iga punkti jaoks liigeste nurgad. Tekib LUT. Pärast seda: vajutad nooleklahvi, süsteem arvutab uue (x, y) → vaata LUT-st lähim punkt → leia liigeste nurgad → liiguta.

**Tase 2 töötab sellepärast, et keegi (mängujuht või sina kalibreerimise käigus) on selle LUT-i ehitanud.** Sa räägid x-y keeles, robot saab aru, sest LUT tõlgib. Tase 1 puhul polnud sul LUT-i — pidid ise olema kalkulaator.

### Tase 3 — VS Code + Claude Code agent

Sama tööriist, millega oled eelnevatel päevadel ülesandeid lahendanud. Avad VS Code, sees on Claude Code. Taustateenuses on tööriistad valmis:

- `get_game_state()` — tagastab juba **töödeldud andmed** (kõik ekraanil olevad ohud koos nende vektori pikkuse ja aktiivse aja jäägiga, kõikide märkide asukoht ja olek, skoor, kell) JSON-ina
- `move_to(x, y)` — liigutab roboti otsa antud ekraani-koordinaadile
- `grab()` — haarab tööriista otsaga (võtab üles, mis on lähedal)
- `release()` — vabastab tööriista (laseb käeshoitava maha)

**Tähtis:** agendile ei anta toort kaamerapilti otsustamiseks. Enne agenti on **objekti-klassifikaator** (YOLO või lihtsam värvi-klassifikaator), mis pildi peal ära tunneb, kus on mis. Agent saab need positsioonid juba selgelt välja loetuna. Tema töö on **otsustada, mida teha**, mitte näha.

Annad agendile lihtsa eesmärgi: *"Mängid küberkaitse-mängu. Vaata get_game_state, eelista pikemate vektoritega ohte. Kui vastase märk on aktiivne sinu meeskonna laksu lähedal, võimalusel näpata. Kui vastase kastis on kasutamata märke ja sa pole hõivatud, võta neid."* Agent kutsub `get_game_state()`, mõtleb, kutsub `move_to()`, `grab()`, `release()`, vaatab uuesti.

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

- **YOLO (või lihtsam värvi-klassifikaator)** vaatab kaamera-pilti, leiab kus on ohud, milline on iga ohu vektori pikkus, kus on märgid, mis on nende olek. Tagastab struktureeritud andmed JSON-ina.
- **Claude Code (LLM)** võtab need andmed, otsustab strateegia, kutsub `move_to()`, `grab()`, `release()` käske.

Agent ei pea pilti raw kujul vaatama. **Ta saab juba positsioonid.** Tema töö on otsustada, mitte näha.

See on **õige arhitektuuri näide**: igale ülesandele oma mudel. Sama loogika kehtib päris robootikas — autotehases on YOLO koosteliinil tuvastamas, mis osa läbi liigub; eraldi planeerimis-mudel otsustab, kuhu robotkäsi liigub.

**Õppetund kogu laagrist:** ära aja mudeleid segi. Igaüks on hea omas ülesandes. Halb arhitekt paneb LLM-i pilti vaatama (aeglane, ebatäpne) või YOLO strateegiat tegema (ei oska). Hea arhitekt teab, mida kuhu panna.

---

## Meeskonnatöö — kuidas 12 mitte-operaatorit kaasa aitavad

Iga matši ajal on 4 operaatorit (üks meeskonna kohta) ja 12 inimest istuvad kõrval. Need kõrval-inimesed pole pealtvaatajad. Iga meeskonna sees on iga matši kohta **neli kindlat rolli**, mille vahel meeskond ise jaotab. Roteerumine on **kohustuslik** — sama inimene ei tohi olla samas rollis kahel järjestikusel matšil.

### Neli rolli meeskonna kohta

**Operaator** — istub roboti taga, kasutab parasjagu kasutusel olevat juhtimisliidest. See on füüsiline tegija.

**Strateeg** — vaatab mängu ekraani, ütleb operaatorile valju häälega, mida teha. "Pikk vektor tekkis paremalt — kiirelt, sinna! Vastase märk on aktiivne keskel — näpata!" Tema vastutab strateegia eest, operaator täidab.

**Vaatleja** — vaatab **vastasmeeskonna** poolt: mida nad teevad, milliseid ohte nad eelistavad, kas nad varastavad palju, kas nad tühjendavad kasti. Märgib mustreid: "Vastane jätab madala väärtusega ohte tähelepanuta", "vastase operaator ei jälgi oma kasti — saab varastada". Nende info läheb järgmise matši operaatorile.

**Promptija/Kodija** — parandab **matšide vahel** liidest või agendi prompti. Tase 1 puhul: midagi ei muuda (lihtsalt vaatab ja õpib). Tase 2 puhul: võib teha makrosid sagedasti kasutatud liigutuste jadadele. Tase 3 puhul: kirjutab Claude Code agendi prompti paremaks pärast iga matši — võtab eelmise matši leidudest õppe, paneb need agendile reegliteks.

### Rotatsioon

Iga meeskond peab läbima **kõik neli rolli iga matši ajal**. Pärast matši rollid vahetuvad. Pärast nelja matši on iga inimene olnud kõigis neljas rollis.

**Punktsüsteem soosib rotatsiooni:**

- Iga **võidetud** matš = **3 punkti**
- Iga **kaotatud** matš = **1 punkti** (osavõtu eest)
- **Viik** = **2 punkti** mõlemale
- Kui meeskond on kasutanud kogu turniiri jooksul **nelja erinevat operaatorit** = lisaks **+2 boonust**
- Iga "vahele jäetud" inimene (kes ei saanud kordagi operaator olla) = **−1 punkt**

Lühidalt: meeskond, kelle iga liige operaator saab olla, võidab. Meeskond, kus üks geenius mängib kogu aja, kaotab — isegi kui geenius võidab kõik matšid üksinda.

See on tahtlik. Päris robootika ja päris insenertöö ei juhtu üksinda. Sa ehitad meeskonnaga, dokumenteerid teistele, võtad nõu vastu. See laager õpetab seda kohe selgeks.

---

## Esimene päev — proovimatš ja Tase 2 õppesessioon

**Aeg:** 2,5 tundi (1 h + 1,5 h, üks vahepaus).

### Slot 1 (1 tund) — Avapresentatsioon ja Tase 1 proovimatš

**Avapresentatsioon (15 min).** Mängujuht näitab korraks, mis ekraanil toimub: küberohud tekivad ekraanile, igaühel oma vektori pikkus ja aktiivne aeg. Igale meeskonnale neli M5 märki oma kastis. Tutvustab põhi-tsüklit (võta märk → pane ohu peale → 5 sek taimer → vastane saab näpata → punktid). Tutvustab kasti vargust (denial) ja nelja rolli (operaator, strateeg, vaatleja, promptija).

**Proovimatš — Tase 1 pime liigese-juhtimine (45 min).** Igale meeskonnale antakse Tase 1 liides — kuus liugurit, paar nuppu, mitte mingit kaamerapilti. Rohkem juhiseid pole. Roteeritakse kohti: matšide vahel vahetuvad operaatorid. Esimene matš 90 sek, siis paus, rollid vahetuvad, järgmine matš.

Neli matši 45 minuti sees — iga meeskonna iga liige saab kord operaatoriks. Naerdakse. Keegi ei saa aru, kus parasjagu nende märk on — peale seda, kui esimene liigend pööras valele poole. Üks paneb märgi hoopis ekraani kõrvale ja kaamera ei näe seda enam. Skoor: 0-0, 0-3, 3-0, 0-0 (paljud märgid läheb kaduma, mitte ohte peale).

Pärast matše arutletakse minut kahe peale: **mida raske oli? Miks?** Vastus tuleb tavaliselt välja — "robot ei tee seda, mida ma tahan." Mis on tegelikult vale viis öelda. Õige vastus: **ma ei oska robotile õigesti öelda, mida ma tahan**. Liides on liiga toore.

See vahe — "robot ei tee õigesti" versus "ma ei räägi õigesti" — on kogu laagri filosoofiline alus.

### Slot 2 (1,5 tundi) — Õppesessioon 1: WASD-liigutuse liides

Esimene päris õppesessioon. Veebilehel on nüüd **kaamera otsevaade** ülevalt — sa näed sama pilti, mida kaamera. Vajutad WASD (või nooleklahve) — robot liigutab seda suunda. Tühik haarab/vabastab.

**Tutvumine (20 min).** Kõigepealt proovige liidest tundma — proovige liikuda kasti, võtke märk, viige ekraanile, pange peale. Õppige, kus on kummagi meeskonna kast, kuidas ulatuda vastase kasti, kui kaua võtab edasi-tagasi liikumine.

**Harjutusmatšid (50 min).** Neli matši 90 sek igaüks, rollide rotatsioon nagu enne. Kindlasti parem kui Tase 1. Nüüd hakkab varastamine ja näppamine tööle — vastane jõuab ka päriselt liikuda. Esimene varastamine tuleb. Esimene kasti tühjendamine tuleb. Naerdakse.

Promptija/kodija rolli sisu siin: võib hakata tegema **makrosid** sagedasti kasutatud liigutuste jadadele. Näiteks: "vasak ülemine ekraani nurk" = üks nupp. "vastase kast" = teine nupp. Need makrod aitavad operaatorit järgmistes matšides.

**Arutelu (20 min).** Mida õpiti? Tavaliselt — "WASD on kiirem kui liugurid, aga ikka aeglane mängu jaoks." See on õige õpik. **Iga abstraktsioonisamm vähendab keerukust, aga ei pruugi olla veel piisav.** Ka selgub: meeskond, kus promptija on teinud head makrod, on operaatorile selgelt eelisseisus. Toetav töö maksab end ära.

---

## Teine päev — Claude Code agent ja võistlus

**Aeg:** 3 tundi (1,5 h + 1,5 h, üks vahepaus).

### Slot 3 (1,5 tundi) — Õppesessioon 2: Claude Code agent

Avad VS Code, sees Claude Code. Taustateenuses on tööriistad: `get_game_state`, `move_to`, `grab`, `release`. Sama Claude Code, millega oled juba muid ülesandeid lahendanud — uus on ainult mängu tööriistakomplekt.

**Esmane prompt (20 min).** Meeskond koos kirjutab esimese versiooni prompti agendile. Näiteks: *"Mängid küberkaitse-mängu. Vaata get_game_state, eelista pikema vektoriga ohte (üle 15). Kui vastase märk on aktiivne ja sa pole hõivatud, võimalusel näpata. Hoia kindlasti vähemalt üks märk kastis varuks."* Käivitavad ja vaatavad.

**Harjutusmatšid (60 min).** Neli matši nagu enne, rollide rotatsioon. Esimesed katsed on tihti katastroofilised — agent näeb hästi, aga mõtleb aeglaselt (iga ring 2–5 sekundit). Vahel paneb agent märgi ohule, kes on juba pea-aegu aegumas — taimer saab läbi enne, kui keegi näpata jõuab. Vahel agent ignoreerib pika vektoriga ohte ja jahib lühikesi. Mängitavus sõltub palju promptist.

**Promptija roll** on selles sessioonis kõige olulisem. Iga matši järel parandab ta prompti vastavalt eelmisele matšile. "Agent jahtis 6-väärtuslikku ohtu pika vektori asemel → lisa promptisse 'eelista alati vektorit üle 18, kui selline on saadaval'." "Agent ei näpanud vastase märki kunagi → lisa 'kui vastase aktiivne märk on lähemal kui 200 pikslit minu otsast, näpata kohe'."

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
| Matš kaotatud | +1 |
| Viik | +2 mõlemale |
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

Sama tööriista (Claude Code) kasutavad päris tarkvarainsenerid päriselt. Mitte mängu mängimiseks — koodi kirjutamiseks, andmete analüüsimiseks, infrastruktuuri seadistamiseks. Sa ei õpi siin sildimängu mängima. Sa õpid **kuidas inimene ja agent koos töötavad** — mida öelda, kuidas vastust valideerida, millal sekkuda.

Kolm juhtimisliidest, mida päeva jooksul proovid, vastavad kolmele ajastule arvuti-inimese suhtluses:

- **Pime liigese-juhtimine** = 80ndate–90ndate tööstuspingid, operaator juhib masinat liigese kaupa, käsk-haaval
- **WASD-liigutus** = 2000ndate mängude ja CAD-tarkvara stiil, kus räägid otse käe asendist, masin teisendab liigese-keelde
- **Claude Code agent** = 2020ndate AI-abi, eesmärgi-keel, masin teeb ise

Kogu inimese-arvuti suhtluse lugu mahub ühte küberkaitse-pärastlõunasse. Ja sa läbid selle ise.

Meeskonnatöö osa on samuti päris. Üksi suudad mängida — aga meeskond, kes oskab strateegi, vaatleja ja promptija eraldi panustada, võidab geeniust üksinda. **Punktid jagatakse nii, et üks geenius ei saa võita üksi.** Päris insenertöös sama lugu: kõige paremaid süsteeme ehitavad meeskonnad, mitte üksikud.

Kahe päeva lõpuks tead kolme asja:

- **Liides on tähtsam kui masin.** Sama Dobot — kolm erinevat mängu, sõltuvalt sellest, kuidas räägid.
- **Iga abstraktsioonisamm on uus võim ja uus risk.** WASD annab kiiruse, agent annab automaatsuse, aga eeldab head prompti.
- **Õige küsimus on parem kui kiire käsk** — ja kõige paremaid küsimusi sõnastatakse meeskonnaga koos.

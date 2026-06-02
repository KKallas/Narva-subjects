## Prototüüpimine: Verstapost 4 — Korpusega funktsionaalne prototüüp

**Maht:** 16 tundi | **Hindamine:** 20 punkti | **Kohtumine: L 30.05**

**NB: 3. tellimuse (viimased komponendid) tähtaeg on edasi lükatud kuni 30.05.**
<tellimistabeli link>

V3 lõpus oli sul integreeritud rover, mis sõidab klõpsude järgi oma esikaameravoos ja peatub punase piiri ees. Nüüd paned ta kindlasse 3D-prinditud PLA korpusesse ja valmistud päris matšiks.

**Mängu reeglid:** 90 sekundit, mõlema meeskonna roverid alustavad oma seina äärest, **iga rover = üks operaator**. Areenil on **markeeritud alad — punast värvi**. Võidab see meeskond, kelle rovereid on lõpus rohkem punase ala peal.

**Oluline põhimõte:** rover ja operaator kasutavad matši ajal **ainult roveri enda andureid** — esikaamerat ja värviandureid. Ametliku skoori loeb mängujuht ülevaate kaameralt; operaatorile annab roveri enda mõõtmine kiire "ON KOHAL" tagasiside, et ta teaks, kas vaja edasi tüürida või võib järgmise rovveri juurde liikuda. **Ülevalt vaadet operaator ei näe** — ei juhtimisliideses, ei info-paneelil, ei pärast matši ülevaateks.

V4 lõpus on operaatoril valida kolme autonoomsuse astme vahel: täismanuaalsest klõpsamisest kuni LLM-il põhineva agendini, mis leiab punase ala ja sõidab sinna ise. Lisaks **mõõdame Analüüsis 3**, kuidas süsteem peab vastu kümnele järjestikusele 90-sekundilisele matšile. See pole iseenesest nõue — päris turniiril teed matšide vahel kõike, mida vaja — vaid diagnostika: kui rover ei pea vastu ilma pideva sekkumiseta, kogub süsteem vigu aja jooksul (mälu lekib, WiFi ei taasta end, kalibratsioon vajub ära). 10 matši järjest on lihtne viis selliseid varjatud probleeme nähtavale tuua.

Prioriteet on järjekorras: kõigepealt korpus ja selle vastupidavustestid (ilma selleta on kõik osad ohus). Siis alal seismise tuvastamine. Siis autonoomsuse astmed roveri poolel. Mängu enda infrastruktuur (ülevaate kaamera, ametlik skoor, matši-protokoll) on V4-st väljas — vt sektsioon 4 lühikirjelduse jaoks. Kui pärast kokkupanekut midagi ei tööta — **ära jätka**, otsi viga.

---

### 1. V3 korpuse hindamine, tugevdamine ja matšikoormuse test

**Eeldus:** sul on V3 lõpust olemas töötav korpus — ükskõik mis materjalist (PLA, PETG, vineer, papp, kombinatsioon) ja ükskõik mis meetodiga ehitatud. V4 ei alga "ehita uus korpus", vaid **"võta see, mis sul on, ja tee matšivalmiks"**.

**Eesmärk:** mõõta konkreetsete testidega oma V3 korpuse vastupidavus, leida nõrgad kohad ja tugevdada need konkreetsete võtetega (peamiselt poldi-mutri pingestatud konstruktsiooniga). V4 lõpuks on sul **enne-pärast võrdlus**: numbrid, mis näitavad, mis paranes, mis jäi samaks ja mis vajab veel tööd.

---

**Test A — Mootori kuumustest**

Mootor täisgaasil 5 minutit. Käivita programmiga ja pane rover tagurpidi, nii et rattad pöörlevad õhus. Iga minuti järel mõõda mootori korpuse temperatuur (puuteandur, kontaktitermomeeter või IR-andur).

Pärast 5 minutit kontrolli: kas korpus on mootori kinnituspesa juures deformeerunud? PLA pehmeneb juba 50–55 °C juures — kui mootori soojus jõuab plastini, näed seda kohe.

Aktsepteeritav lävi: korpuse temperatuur mootori juures alla 45 °C.

---

**Test B — Korduv kokkupõrketest seinaga**

**Sama** korpuse peal, mitte uut printides. Test mõõdab **kumulatiivset kahjustust** — kas viies kokkupõrge teeb rohkem kahju kui esimene? Kui jah, on midagi väsimas.

Aseta rover 1 m kaugusele seinast, suuna otse vastu, käivita "täiskiirusel 1 sekund". Pärast iga kokkupõrget:

1. Pildista (sama nurga alt — võrdle hiljem)
2. Märgi tabelisse, mis liikus, lõdvenes või tuli lahti
3. Mõõda kaamera nurka — tee shabloon, kus on märgitus videol nähtav ala kontrolli kas ala on sama ka peale kokkupõrget
4. Kontrolli värvianduri positsiooni - sama mis kaameraga

Korda **3 korda järjest**. Kui esimesed 3 lähevad puhtalt, võid teha veel 2 — kokku 5, et täita aktsepteeritavat läve. Kui juba esimese kokkupõrkega midagi murdub või lõdveneb tõsiselt, **peatu** ja kirjuta üles — seal ongi täiendamise sisend. Pole vaja korpust hävitada, et tõestada, et ta on nõrk.

Aktsepteeritav lävi: pärast 5 kokkupõrget mitte rohkem kui 1 osa lõdvenenud, kaamera nurk muutunud alla 3°, andur ikka 5 ± 1 mm kõrgusel.

**Kui korpus on V3-st juba habras:** alusta 0,5 m kaugusest poolkiirusega ja mõõda, kas see kannatab. Eesmärk on **mõõta**, mitte ehitada uut sellepärast, et vana läks testides katki.

---

**Test C — Aku vahetuse aja test**

Anna rover **algajale operaatorile** (sõbrale või klassikaaslasele, kes pole varem näinud). Lase tal akut vahetada — alguses näita üks kord ette, siis lase teha. Mõõda aega.

Aktsepteeritav lävi: pärast ühte demo peaks operaator vahetama aku alla 30 sek. Kui võtab kauem, on korpus liiga keeruline.

---

**Test D — Komponentide eemaldatavus silumiseks/programeerimiseks**

Mõõda, kui kaua võtab:

- Värvianduri eemaldamine (silumiseks või asendamiseks)
- Telefoni või M5-CAMi eemaldamine (USB silumiseks)
- Mootori eemaldamine (kui üks läheb matšide vahel katki)

Aktsepteeritav lävi: värvianduri vahetus alla 2 min, arvutusplatvorm alla 1 min, mootor alla 5 min.

---

**Iga testi tulemus → konkreetne tugevdamine**

Iga vea kohta otsustad ühe kolmest:

| Vea tüüp | Tegevus |
|:---|:---|
| Lihtne lahtilastus (polt lõdvenenud) | Loctite + tugevam pinge; lisada hooldusprotsessi |
| Korduv lahtilastus samas kohas | **Poldi-mutri kinnitus**: prindi avaus (clearance hole), polt läheb materjalist läbi, mutter peal surub kihte kokku |
| Plastiku murd või deformatsioon | Disainimuutus (paksendada sein, suurendada täituvust, lisada tugevdusribi) |
| Liiga suur kuumus | Kas materjalivahetus (PLA → PETG selles kohas) või parem õhuvool (auk, ventilaator) |
| Komponent ei tule lahti või võtab kaua | Mehaanikat lihtsustada (vahetada kruvi klipi või magneti vastu) |

---

**Poldi-mutri kinnituse põhimõte (kui sul seda veel pole):**

PLA prinditud osa nõrgim koht on **kihtide vaheline adhesioon**. Kui mootori kinnituspolt keerata otse PLA-sse, kruvib see end lahti või rebib kihid lahti — eriti kui mootor kuumeneb. Lahendus: ära lase koormusel jääda ainult plastile; suuna see metalli kaudu, mis surub kihte üksteise vastu.

Praktiliselt:

1. Disainis prindi avaus (clearance hole) poldi jaoks
2. Lükka polt alt läbi
3. Pane peale surveseib ja mutter
4. Pinguta — mutter surub kihte kokku

Soojapressmutrid (heat-set inserts) annavad sama efekti elegantsemalt — neid surutakse jootekolviga PLA sisse ja saad metalse keerme. Aga poldi-mutri-kinnitus on odavam ja lubab korpust rohkem kordi lahti ja kokku panna.

---

**V4 lõpus dokumenteerid:**

| Komponent | Enne (V3) | Tugevdus | Pärast (V4) | Aktsepteeritav? |
|:---|:---|:---|:---|:---|
| Mootori kinnitus | Polt otse PLA-sse | Polt + mutter alla | Pidas 5/5 kokkupõrget | Jah |
| Kaamera hoidja | Liim | Polt + kummiseib | Nurk muutus 1,5° | Jah |
| Aku-pesa | Vaba ruum | Klips lukustusega | Vahetus 18 sek | Jah |
| ... | ... | ... | ... | ... |

See tabel on V4 üks tähtsamatest tulemustest — ta näitab, kus oled aega kulutanud ja kui palju see tasus.

**YouTube/AI otsisõnad:**

- `bolt and nut joint 3D printed PLA`
- `heat set insert PLA install soldering iron`
- `I2C temperature sensor`
- `loctite threadlocker electronics`

---

### 2. Operaatori tagasiside — "kas ma olen kohal?"

**Eeldus:** V3 värviandur(id) töötavad korpuses; punase ala värv on kalibreeritud.

**Probleem, mida lahendame:** ametliku skoori saab peale mängu lõppu ülevaate kaameralt (sektsioon 4). Aga operaator peab matši ajal **kohe ise teadma**, kas tema rover on punasele alale jõudnud ja kas mängujuht hakkab seda punkti lugema. Ilma selle tagasisideta ta:

- Klõpsab ja tüürib edasi, kuigi rover on juba kohal
- Liigutab roveri minema, sest ei tea, kas ta jõudis
- Raiskab 90 sekundi piires kallist aega

**Lahendus:** rover ise mõõdab oma värvianduriga, kas ta on punase ala peal, ja kuvab operaatorile **suure selge "ON KOHAL" indikaatori** veebiliideses. Sama signaal kasutab ka autonoomne agent, et oma tsüklit lõpetada ("eesmärk täidetud").

See pole ametlik skoor — see on **operaatori UX-süsteem**. Rover hindab oma kohaolekut nii hästi, kui suudab, ja kui mängujuhi pilt näitab teist asja, on see kalibratsiooni-küsimus, mille kohta saab pärast vaielda. Aga matši ajal vajab operaator kiiret signaali, mitte täiuslikku tõde.

**70% katte reegel — ühine määratlus operaatori-tagasisidele ja mängujuhi skoorile:**

Rover loetakse alal olevaks, kui **vähemalt 70% tema põhjast on punase ala peal**. Sama reegel kehtib mõlemal pool:

- **Rover ise** üritab seda oma anduritega hinnata (variandid A, B, C allpool) — operaatorile tagasiside
- **Mängujuht** mõõdab seda ülevaate kaamera kaudu (sektsioon 4) — ametlik skoor

Mõlemal puhul on 70% lävi geomeetriline ja selge — kui mõõtmised lähevad lahku, on tegu kas anduri kalibratsiooni nõrkusega või vaidlusaluse piirisituatsiooniga.

---

**Kuidas seda mõõta? Kolm varianti, kasvavas keerukuses:**

**Variant A — Üksik andur, kindluse ja stabiilsuse filtriga** *(V3 baas)*

Kui sul on V3-st üks TCS34725 keskel all, jätka sellega. Lävi: andur stabiilne (5+ järjestikust näitu punast) + kindluse skoor ≥ 0,7 = rover loetakse alal. See pole otseselt "70% pindala", aga praktiliselt sama loogika: kindluse skoor mõõdab, kui puhtalt värv vastab kalibreeritud punasele, ja kui rover seisab ala keskel ning andur näeb selgelt punast, on tema all enamus pinda punane.

Lihtsam, aga ebatäpsem servadel. Sobib esimeseks versiooniks.

**Variant B — Mitu andurit roveri põhja peal** *(täpsem, V4 jaoks väärtuslik täiendus)*

Lisa 2–4 andurit ja paiguta nad laiali roveri põhjale (nt nelja nurka või kolmnurka). Iga andur ütleb oma kohast: "minu kohal põrand on punane" või "ei ole". **70% anduritest nõustub** = rover on alal. 4 anduri puhul = 3/4, 5 anduri puhul = 4/5, 7 anduri puhul = 5/7.

See vastab paremini "70% pindala" mõttele — anduri paigutus simuleerib pindala mõõtmist statistilise näidismeetodi abil. Lisad rohkem riistvara (paar TCS-i ja I2C pooli pikenduse), aga loogika jääb sama lihtne: loe näite, loenda nõustujaid.

**Variant C — Allavaatav kaamera roveril** *(kõige täpsem, kõige keerulisem)*

Lisa väike allavaatav kaamera (teine M5-CAM või muuda roveri esikaamera nurka alla). Roveri serveris analüüsi pilti: kui suur osa kaadrist on punane. Annab tegeliku 70% pindala mõõtmise ja töötab ka ebakorrapäraste ala-kuju puhul.

Suurepärane lisandus, kui jõuad — ja loob silla autonoomsuse Astme 3 (LLM agent) jaoks, sest sama kaamera saab toita ka LLM-i.

---

**Vali oma meeskonna oskuste ja tähtaja järgi.** Variant A töötab, kui V3 oli korralikult tehtud. Variant B annab usaldusväärsema mõõtmise ja matšiks vajaliku selguse. V4 hindab seda, **kuidas iga variant töötab ja kus ta katki läheb** — pole kohustuslik kõige täiuslikum, oluline on, et iga variant on testitud ja dokumenteeritud.

**Stabiilsuse filter (kõikidel variantidel):** üks näit ei loe — peab olema **vähemalt 5 järjestikust näitu** "on alal" (~250 ms), et rover loeks ennast kindlalt alal olevaks. Vastasel juhul juhuslikud lugemised (peegeldused, varjud) lülitaksid indikaatorit edasi-tagasi. Stabiilsuse filter tähendab ka, et rover peab olema **paigal** lühikese hetke jooksul — see vastab matši loogikale, kus eesmärk on jõuda alale ja **jääda sinna**.

**Reaalaja tagasiside operaatorile ja agendile:**

- Suur selge **"ON KOHAL"** indikaator veebiliideses, kui mõõtmine ületab läve
- Mõõtmise detail (kindluse %, nõustujate arv, kattumise %) — silumiseks
- Just see tagasiside ütleb operaatorile "jätan roveri siia" või agendile "eesmärk täidetud"

**Ülevaate kaamera roll (sektsioonis 4 lähemalt):** **mängujuht** loeb ülevaate kaameralt ametlikku skoori — tema otsustab, kas 70% katte reegel on täidetud. Roveri enda hinnang on **operaatori tagasiside**, mitte ametlik skoor. Mõlemad mõõdavad sama asja erinevatest vaadetest, ja matšil töötavad nad paralleelselt: operaator näeb kiiresti, mis ekraanil toimub; mängujuht peab ametlikku arvet.

**Kalibreerimine enne matši:**

1. Pane rover punase ala keskele, vaata 5 sekundit. Indikaator peab püsivalt näitama "ON KOHAL", kindluse skoor ≥ 0,7.
2. Pane rover ala servale (osa põhjast peal, osa kõrval) — indikaator peab kindlalt näitama "ei ole kohal", kindluse skoor selgelt alla 0,5.
3. Pane rover paljale areeni pinnale — peab kindlalt näitama "ei ole kohal".

**Tüüpilised probleemid:**

- **Rover on serval ja indikaator vilgub** → kindel reegel ("kindlus ≥ 0,7 = ON KOHAL") ja visualiseeri see operaatorile.
- **Värv muutub areenivalgustusega** → kalibreeri sama valgustusega, kus matš toimub.
- **Andur näeb läbi roveri varju** → paigalda andur lähemale (5 mm pinna kohal).

**YouTube/AI otsisõnad:**

- `TCS34725 esp32`
- `RGB color zone detection robot`
- `confidence score classifier`
- `sliding window filter sensor`

---

### 3. Autonoomsuse astmed — manuaalsest LLM agendini

**Eeldus:** V3 klõpsa-ja-sõida loogika roveri esikaameravoo peal töötab.

**Eesmärk:** üks operaator juhib **ühte** roverit (mitme samaaegne juhtimine ühest liidesest oleks juba uus projekt). Aga ta saab valida, kui palju ta ise klõpsab ja kui palju lubab roveril ise teha. V4 toob sisse kolm taset, igaüks ehitab eelmise peale.

#### Aste 1 — Manuaalne (V3 baas)

Operaator vaatab roveri esikaameravoogu. Klõpsab pildil sinna, kuhu tahab, et rover läheks. Tarkvara teeb V3 raycast'i: kaameranurga ja FOV järgi arvutab põrandakoordinaadi, robot pöörab ja sõidab. Operaator vastutab navigeerimise eest täielikult — leiab punase ala silmaga, klõpsab sellele, jälgib, et rover jõuab kohale.

See aste on V4 lõpuks **kohustuslik** — kõrgemate astmete kukkudes peab manuaalne olema selgelt töökindel. Manuaalne on ka veaolukorra tagasitõmbumine: kui agent jääb segadusse, lülitad manuaali tagasi.

#### Aste 2 — Autopilot (lihtne värvi-suunamine)

Operaator vajutab nuppu "Leia punane". Tarkvara analüüsib esikaameravoogu pildianalüüsi-meetoditega:

1. Filtreerib pildi värvikanalite järgi (kus pildil on punakas piirkond)
2. Leiab suurima sellise piirkonna keskpunkti pikslites
3. Klõpsab **ise** sellele pikslile — V3 raycast viib roveri sinna

Operaator vaatab kõrvalt. Kui autopilot teeb vea (näeb näiteks meeskonna märgisel punast värvi ja arvab, et see on ala), näeb operaator seda kohe ja saab manuaali tagasi võtta.

Selle astme **arvutus jookseb browseris, ehk mobiiltelefonis või arvutis** — pole vaja LLM-i ega välist teenust, samas saab hoida kontrollerit lihtsa ESP seadmena mitte ei panema palju kallimat spetsiifilisemat raudvara. Kui kasutad telefoni põhikontrollerina siis jooksuta seal peal.

#### Aste 3 — Olemasolev agent juhib roverit (Claude Code vms)

**Ära ehita oma multimodaalset LLM-tsüklit nullist.** Kasuta olemasolevat agenti, mis on niikuinii hästi tehtud — Claude Code, Cursor, Aider või mis iganes sarnane CLI/IDE agendiga töövoog. Sinu ülesanne on ehitada talle **selge ja lihtne sisend-väljund liides**, mille kaudu agent saab roveri kohta infot küsida ja käske saata.

**Põhimõte:** agent on töötaja, sina ehitad talle töökoha. Tegelik insener-töö on selle liidese disain — mida selgem on API, seda paremini agent töötab.

**Mida sa ehitad — paar lihtsat tööriista, mida agent saab kutsuda:**

| Tööriist | Mida teeb | Vastus |
|:---|:---|:---|
| `rover_camera` | Salvestab praeguse esikaamera pildi failina | Pildi failitee (nt `/tmp/rover_now.jpg`) |
| `rover_status` | Tagastab roveri praeguse oleku | JSON: `{"on_target": false, "battery_pct": 72, "last_action": "drive 2s"}` |
| `rover_rotate <kraadid>` | Pöörab rover kohapeal (+ paremale, − vasakule) | OK / ERR |
| `rover_drive <sek>` | Sõidab edasi etteantud aja | OK / ERR |
| `rover_click <px> <py>` | Teeb V3 raycast-klõpsu pildi koordinaadile | OK / ERR |
| `rover_stop` | Peatab kohe kõik mootorid | OK |

Lihtne CLI-tööriist: `rover camera`, `rover rotate -- -30`, `rover drive 2`. Või MCP-server, mille Claude Code laeb otse — kumb sulle parem tundub.

**Mida operaator teeb:**

Operaator avab Claude Code'i (või Cursor'i vms) oma sülearvutis ja annab lihtsa eesmärgi:

> "Sa juhid roverit. Eesmärk: leia areenil punane ala ja jää selle peale. Kasutada saad neid tööriistu: rover_camera, rover_status, rover_rotate, rover_drive, rover_click, rover_stop. Ütle, kui oled kohal või kui ei suuda eesmärki täita."

Edasi võtab agent ise tsükli enda peale: võtab pildi, mõtleb, kutsub tööriista, vaatab tulemust, kohaneb. Sinul pole vaja prompt-tsüklit kirjutada — see on agendi enda asi.

**Operaator näeb iga sammu** sellest samast terminalist, kus agent töötab — milline pilt anti, mida agent otsustas, mis tööriista kutsus. See ongi loomulik silumise ja turvalisuse vaade. Manuaali tagasi võtmiseks lihtsalt sulgeb agendi tsükli ja avab uuesti tavalise veebiliidese.

**Pedagoogiline mõte:**

- Tegelik töö **pole agendi ehitamine**, vaid puhta tööriistakomplekti disain. Selgemad tööriistanimed, parem dokumentatsioon, vähem üllatusi → parem agendi käitumine.
- Õpid, kuidas agendid päriselt töötavad: nad pole imed, vaid süsteemid, mis vajavad selget I/O.
- Sama töövoog kantakse edasi: kui sul on kunagi vaja, et mingi süsteem oleks agentidele kättesaadav, kasutad sama mõttemustrit (tööriistad, JSON-vastused, dokumenteeritud käitumine).

**Mida V4 hindab:**

- Kas API on **selge ja iseseisev**? Testi: anna keegi (sõber, õpetaja) Claude Code'i ja sinu dokumentatsioon — kas ta saab roveriga rääkima ilma sinu abita?
- Kas agendi tegevus on **läbipaistev**? Iga tööriista-kõne ja vastus on logitud ja vaadatav.
- Kas operaator saab agendi tegevuse **igal hetkel peatada** ja manuaali tagasi võtta?

**Tüüpilised vead:**

- **API liiga keeruline** — agent ei saa aru parameetritest. Lihtsusta nimesid, lisa selgeid näiteid dokumentatsioonis.
- **Tööriistad blokeerivad** — agent kutsub `rover_drive 5` ja peab ootama 5 sek enne järgmist sammu. Otsusta, kas eelistad sünkroonset (lihtsam, aga aeglane) või asünkroonset (kiirem, aga keerukam); dokumenteeri valik.
- **Agent ei vaata vahepealset olukorda** — kui pärast `rover_drive` agent ei kutsu uuesti `rover_camera`, ei tea ta, kus rover on. Dokumenteeri töövoo soovitus: alusta iga otsus pildiga.
- **Agendi tsükkel ei lõpe** — lisa eesmärgile alati "ütle kindlasti, kui oled kohal või kui ei suuda jätkata", muidu agent võib lõputult proovida.

**Astmete vahetamine:** sama nagu Aste 2 — kui operaator vahetab manuaaliks, peatub rover ohutult ja agent lõpetab tsükli.

**Disainivabadus:** kõik kolm astet ei pea olema täiuslikult valmis. V4 hindab seda, kuidas iga aste **töötab ja millal ta katki läheb**. Aste 3 on uudne ja eksperimentaalne — kui agent leiab punase ala 60% juhtudest ja kukub 40% läbi, on see hea aruteluteema, mitte projekti läbikukkumine. Tähtsam on, mida sa selle 40% kohta tead.

**YouTube/AI otsisõnad:**

- `Claude Code custom tools CLI`
- `MCP server tutorial python`
- `LLM tool use simple API design`
- `agentic loop screenshot feedback`

---

### 4. Mängu kontekst — ülevaate kaamera ja matši-protokoll *(roveri skoobist väljas)*

Päris matš vajab ka mängu infrastruktuuri: **ülevalt vaatavat kaamerat**, mis annab kohtunikule ametliku skoori ja salvestab matši, ning **matši-protokolli serverit** (start, 90 sek taandarv, stop, lõppskoor). Need ehitatakse eraldi V4-st välja, koos mängu enda valmistumisega. V4 ülesanne on teha rover, mis selles infrastruktuuris kindlalt töötab.

**Mida sa pead V4-s teadma, et roveri õigesti ehitada:**

- **Mängu reeglid kehtivad:** 90 sekundit, võidab see meeskond, kelle rovereid on lõpus rohkem punaste alade peal (≥ 70% kattumine).
- **Ametliku skoori loeb mängujuht ülevaate kaameralt.** Roveri "ON KOHAL" indikaator on **operaatori UX-tagasiside**, mitte ametlik skoori autoriteet (vt sektsioon 2).
- **Info-mulli põhimõte:** rover ja operaator töötavad ainult roveri enda andurite infoga. **Ülevalt vaadet operaator ei näe** — ei juhtimisliideses, ei info-paneelil, ei pärast matši ülevaateks. Kui operaator näeks ülevalt, oleks see petturlik abi, mis lõhuks projekti pedagoogilise mõtte.
- **Matši algus ja lõpp tulevad kohtuniku märguandena.** Rover ja operaator hoiavad arvet matši olekust (**ON** / **OFF**) ja käituvad vastavalt:
  - **Matš ON** (kohtunik saatis "start", kell jookseb): kõik käsud lubatud — manuaalne klõps, autopiloot, agent
  - **Matš OFF** (enne starti, pärast stoppi): **ainult ettevalmistuse käsud** — manuaalne ühe-sammu liigutus paigutamiseks, värvianduri kalibreerimine, kaamera test. Autonoomsed režiimid ei tööta matši väljas.

  Filter on **kaks kihti**: (1) operaatori liides ei lase mängu-režiimi käske saata, kui matš pole alanud (nupud grayed-out); (2) **rover ise** kontrollib matši olekut ja **ignoreerib** kõik mittevastavad käsud, mis matšiväliselt jõuavad — defense in depth, kui üks kiht jätab vea sisse, peatab teine.

  **Stop-käsule peab rover reageerima koheselt — igal ajal**, sõltumata matši olekust (füüsiline turvameede).
- **Roveril peab olema selge meeskonna märgis ülapinnal** (vt sektsioon 1, korpuse nõuded), et ülevaate kaamera teda tuvastaks. Väldi punast meeskonna värvi — see ajab segadusse punaste alade tuvastamisega.

**V4-s testides ilma täis-infrastruktuurita:**

- 90-sek matši simuleeri lihtsa taimeriga (telefon, kronomeeter)
- Punase ala asemel saad kasutada A4 prinditud paberit või värvilist teipi põrandal
- Kaks rover-operaatori paari kohapeal "vastamisi" — üks meeskonnaliige loeb kell, teine kontrollib visuaalselt, kus roverid lõpetasid
- Need pole päris-matšid, aga annavad V4 testide jaoks piisavalt konteksti

Päris matš ülevaate kaameraga ja serverskooriga tuleb hiljem; sinu V4 töö on teha rover, mis töötab kindlalt nii harjutus-tingimustes kui ka päris matšidel, kui infrastruktuur valmis saab.

---

### Operaatori-tagasiside täpsus (Analüüs 1)

**Eeldus:** sektsioon 2 (rover annab operaatorile "ON KOHAL" tagasisidet — variant A, B või C) töötab.

**Eesmärk:** mõõta, kas roveri "ON KOHAL" indikaator vastab tegelikkusele — kus rover füüsiliselt punase ala suhtes asub. Operaatorile on tähtis usaldusväärne tagasiside; kui indikaator vilgub valesti, kaotab ta usalduse ja matš muutub ebaefektiivseks.

**Referents:** sa ise paigutad roveri teadlikult kindlatesse positsioonidesse (keskel, serval, paljas areen) ja võrdled, kas indikaator vastab oodatule. Pole vaja mängujuhi infrastruktuuri — sina tead, kuhu rovverit panid. Kui mängujuhi süsteem hiljem valmis saab, saab sama testi korrata tema referentsiga ja võrrelda tulemusi.

**Mõõtmine — kolm testpositsiooni:**

1. **Punase ala keskel** — peab selgelt deklareerima "ON KOHAL" (variant A: kindlus ≥ 0,7; variant B: ≥ 70% andureid; variant C: ≥ 70% pildi pindala)
2. **Punase ala serval** — rover poolik peal, poolik kõrval, peab selgelt deklareerima "ei ole kohal" (mõõtmine alla läve)
3. **Paljal areeni pinnal** — peab deklareerima "ei ole kohal"

Igal positsioonil loe 30 sekundit (≈ 600 näitu 50 ms vahega).

**Salvesta CSV-na** vastavalt valitud variandile:

- **Variant A:** ajatempel, andurinäit, kindluse skoor, "deklareerib KOHAL jah/ei"
- **Variant B:** ajatempel, iga anduri näit, "X/N nõustus", "deklareerib KOHAL jah/ei"
- **Variant C:** ajatempel, pildi pindala %, "deklareerib KOHAL jah/ei"

**Jupyter Lab analüüs:**

| Test | Deklareerib "KOHAL" % | Mediaanmõõdik | Märkused |
|:---|:---|:---|:---|
| Ala keskel | 100% (oodatud) | 0,92 / 4 andurit 4-st / 88% pindala | Tugev signaal |
| Ala serval | 5% (oodatud 0) | 0,65 / 2 andurit 4-st / 55% | Mõnikord deklareerib valesti |
| Paljal areenil | 0% (oodatud 0) | — | Korras |

**Hinnang:**

- **Keskelt deklareerimise %** peab olema lähedal 100% — kui alla 90%, on anduri või mõõtmise nõrkus
- **Servalt deklareerimise %** peab olema lähedal 0% — kui üle 10%, eksitab roveri indikaator operaatorit (näitab "ON KOHAL", kuigi rover on tegelikult serval ja päris matšil punkti ei tuleks)
- **Paljal areenil deklareerimise %** peab olema täpselt 0% — kui üle 0, on midagi väga valesti

**Variantide võrdlus** (kui jõudsid mitut katsetada): pane variandid tabelis kõrvuti samadel testidel. Kus üks variant töötab paremini kui teine? Variant B (mitu andurit) peaks olema servadel parem kui variant A (üks andur). Variant C (kaamera) peaks olema parem ebakorrapärase ala-kuju puhul.

---

### Autonoomsuse astmete võrdlus (Analüüs 2)

**Eeldus:** kõik kolm autonoomsuse astet (samm 3) on vähemalt esmaselt töökindlad.

**Eesmärk:** mõõta, kui hästi iga aste töötab — mitte ainult kas üldse töötab. See annab projekti **õpiväljundi tähtsaima osa**: õpilane mõistab, kus iga lähenemine sobib ja kus mitte.

**Mõõtmine — sama ülesanne, kolm astet:**

Ülesanne: "Sõida punasele alale ja jää paigale." Stardpunkt fikseeritud (näiteks roveri seina ääres), sihtmärgiks üks kindel punane ala areenil. Ulatus identne kõikide astmete jaoks.

Iga aste sooritab ülesande **5 korda** järjestikku. Mõõda:

| Mõõdik | Kuidas mõõta |
|:---|:---|
| Edukus (jah/ei) | Kas rover on lõpus alal ja seal püsib? |
| Aeg (s) | Kui kaua võttis stardist sihtmärgini |
| Operaatori klõpsude arv | Mitu interaktsiooni operaator pidi tegema |
| Valed sammud | Mitu korda rover sõitis valele kohale enne sihtmärgini jõudmist — vt näited allpool |

**Mida lugeda "valeks sammuks":**

- **Aste 1 (manuaal):** operaator klõpsas vale punkti peale ja pidi uuesti klõpsama, et roveri kurssi parandada
- **Aste 2 (autopilot):** tarkvara leidis vale punase piirkonna (nt meeskonna märgis, valgustusest tekkinud peegeldus, lehe värv areeni serval) ja saatis rovveri sinna
- **Aste 3 (agent):** Claude Code valis pildilt vale sihtmärgi või tegi otsuse, mis lõpetas roveri valele kohale

Loendad iga sellise eksimuse, mille pead pärast parandama: rover läks kõrvale, sa vahetad astme või klõpsad uuesti, et kursi tagasi viia. Edukas tee = 0 valet sammu; tüüpiline tee on 1–3.

**Salvesta CSV-na** veergudega: aste, katse number, edukus, aeg, operaatori klõpsud, valed sammud.

**Jupyter Lab analüüs:**

- **Edukuse %** astmete kaupa
- **Mediaanaeg** astmete kaupa
- **Operaatori kognitiivne koormus** = klõpsude arv × aeg

**Tabel raportis:**

| Aste | Edukus 5/5 | Mediaanaeg (s) | Klõpsude keskmine | Märkused |
|:---|:---|:---|:---|:---|
| 1: Manuaalne | ... | ... | ... | |
| 2: Autopilot | ... | ... | ... | |
| 3: LLM agent | ... | ... | ... | |

**Hinnang ja arutelu:**

- **Kus on iga aste parim?** Manuaalne on tavaliselt kiire, kui operaator on hea ja sihtmärk on nähtav. Autopilot võidab, kui sihtmärk on selgelt äratuntav, aga operaator ei taha ise klõpsata. LLM agent võib olla aeglasem, kuid töötab, kui sihtmärki on raskem leida või kui ülesanne on suurem ("kontrolli kogu areen ja leia kõik punased alad").
- **Kus iga aste kukub?** Manuaalne kukub, kui operaator väsib või sihtmärk on kaameravaates pisike. Autopilot kukub, kui valgustus on muutunud või pildil on muid punaseid esemeid. LLM agent kukub, kui pilt on segane, kui agent eksib oma kirjelduses või kui API on aeglane.

Pärast tabelit kirjuta **lõik vabas vormis**: kus eelistaksid sina iga astet pärast neid teste? See lõik koondab V4 ühe põhilise õpiväljundi.

---

### Süsteemi usaldusväärsus 10 matši jooksul (Analüüs 3)

**Eeldus:** kõik V4 funktsioonid töötavad.

**Eesmärk:** sõida **10 järjestikust 90-sekundilist matši** päris matšitingimustes ja logi tarkvarast iga süsteemiviga. See on **diagnostika**, mitte pass/fail nõue: tahad teada, kus süsteem aja jooksul nõrgaks läheb, et need kohad enne turniiri parandada.

**Sündmuste tüübid, mida logida:**

| Sündmus | Mis tähendab | Kuidas tuvastada |
|:---|:---|:---|
| `wifi_disconnect` | Operaator või rover kaotas ühenduse | WebSocket close event |
| `lost_command` | Käsk saadetud, rover ei vastanud | Käsk + 100 ms timeout ilma ACK |
| `sensor_unstable` | Värvianduri kindlus < 0,5 üle 1 sek | Stabiilsuse filter ei jõua kokku |
| `motor_stall` | Mootor proovib pöörata, aga ei liigu | Voolutarbimine kõrge, kaugus ei muutu |
| `agent_error` | Claude Code / agent tagastas vea või tööriist ebaõnnestus | API vastuse parsimise viga, exit-code |
| `false_on_target` | Rover deklareeris "ON KOHAL", aga ise vaatasid — polnud | Operaatori käsitsi logi |
| `restart_required` | Operaator pidi käsitsi taaskäivitama | Manuaalne logi |

**Tabel raportis:**

| Matš # | Rover-skoor (lõpus) | WiFi | Kaotatud käske | Anduri ebastabiilsust | Agendi vigu | Valed ON KOHAL | Taaskäivitus? |
|:---|:---|:---|:---|:---|:---|:---|:---|
| 1 | 4 | 0 | 0 | 0 | 0 | 0 | ei |
| 2 | 3 | 0 | 1 | 0 | 0 | 0 | ei |
| 3 | 5 | 0 | 0 | 2 | 1 | 0 | ei |
| ... | ... | ... | ... | ... | ... | ... | ... |

**Jupyter Lab kokkuvõte:**

- Vigade arv matši kohta (joongraafik ajas — kas vead kasvavad ajaga?)
- Kogusumma iga sündmuse tüübi kohta
- Kus on muster: kas vead esinevad alati samal hetkel matšis, sama tüüpi situatsioonides?

**Hinnang ja tegevus:** loendamine ei lõpe siin — iga viga on järgmise sammu sisend. Kui WiFi katkeb regulaarselt, uuri, kas probleem on areenis (teised seadmed sama kanali peal), toites või tarkvaras. Kui mälu lekib (vead kasvavad ajaga), profileeri server. Kui käske kaotatakse korduvalt sama hetkel — vaata logi, otsi muster. **Eesmärk pole nullini jõuda**, vaid teada, kus su süsteem nõrgaks läheb ja kas need kohad on tähtsuse järjekorras parandatavad enne areeniüritust.

---

### Hindamiskriteeriumid

| Kategooria | Punktid | Mida hinnatakse |
|:---|:---|:---|
| Tööfailid | 4 p | Kood repos, STL-id **+ CAD lähtefailid** (Fusion `.f3z`/`.f3d` või CadQuery `.py`), fotod ja videod korpusest ning matšidest |
| Analüüs | 4 p | 3 Jupyter notebook'i (operaatori-tagasiside täpsus, autonoomsuse astmete võrdlus, 10 matši usaldusväärsus) |
| Prototüüp | 4 p | PLA korpus poldikinnitustega, vähemalt kaks autonoomsuse astet töötavad, 90-sek matš lõpetab puhtalt |
| Dokumentatsioon | 4 p | Spetsifikatsiooni uuendus + kasutusjuhendi mustand |
| Küsimused-vastused | 4 p | Demo kohtumisel + arutelu autonoomsuse astmete üle |
| **Kokku** | **20 p** | |

---

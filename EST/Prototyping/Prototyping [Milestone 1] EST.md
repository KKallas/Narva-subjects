## Prototüüpimine: Verstapost 1

Eelmisel semestril ehitasid alamsüsteeme. Andmehõive andis sulle andurid ja mõõteahelad. Nutilahendused andis veebiliidesed, VPN-tunnelid ja MQTT infrastruktuuri. 3D Printimine andis mehhaanilise disaini ja tootmisoskused. Iga aine andis töötavad tükid. Ükski neist ei andnud töötavat süsteemi.

See aine on koht kus tükid saavad süsteemiks. Sa tuled testitud komponentide ja tõestatud tehnoloogiatega. Väljakutse on integratsioon, viimistlemine ja millegi tegemine mis töötab piisavalt usaldusväärselt et päriselt kasutada.

Aga enne kui puudutad ühtegi juhet või prindid ühtegi detaili — kirjutad spetsifikatsiooni. Ehitamine ilma spetsifikatsioonita on kuidas projektid surevad. Sa ei tea milline "valmis" välja näeb, sa ei saa tööd meeskonnas jagada ja sul pole mille vastu testida. Spetsifikatsioon on leping sinu praeguse mina (kellel on ideed) ja tuleviku mina (kes peab tulemuse andma) vahel.

See verstapost on koht kus meeskond valib projektiraja ja koostab spetsifikatsiooni mis on piisavalt detailne et teine meeskond saaks süsteemi ainult sinu dokumendi põhjal üles ehitada.

### Vali oma rada

Meeskond valib ühe kolmest projektirajast. Loe kõik kolm hoolikalt läbi enne otsustamist.

| | Rada A: Süstla doseerija | Rada B: Sumorobot | Rada C: MG400 tööpink |
| :--- | :--- | :--- | :--- |
| **Staatus** | Vaikimisi rada | Boonusprojekt | Boonusprojekt |
| **Järjepidevus** | Jätkab otse 1. semestrit | Uus projekt, uus valdkond | Uus projekt, laiendab MG400 ökosüsteemi |
| **Roboti platvorm** | Dobot MG400 | Android telefon + SMARS-inspireeritud šassii | Dobot MG400 |
| **Peamised distsipliinid** | Andur, pneumaatika, täppiskontroll | Mobiilne arvutus, mootorijuhtimine, mehhaaniline disain | Modulaarne kinnitamine, mehhaaniline disain, USB integratsioon |
| **Riistvara alguspunkt** | Suurem osa olemas 1. semestrist | Taaskasutatud telefon, ümbertöödeldud mootorid/akud, 3D-prinditud šassii | Alumiiniumprofiil, 3D-prinditud kinnitused, USB-C seadmed |
| **Riski tase** | Madal — tuntud probleem, varasem töö olemas | Kõrge — uus territoorium, suve tähtaeg | Keskmine — hästi piiritletud mehhaaniline probleem |
| **Reaalmaailma motivatsioon** | Kommertsdoseerimistööriistad maksavad 10x rohkem kui robot ise | Narva Kolledži robotiareeni inauguratsiooniüritus sel suvel | Portatiivsed silumistööriistad maksimeerivad õppimisaega igal pool |

*Rada A on turvaline valik — sa tunned probleemi ja sul on töötavad komponendid. Rajad B ja C on boonusprojektid suurema vabaduse ja suurema riskiga. Kui sinu spetsifikatsioon boonusraja jaoks pole piisavalt veenev et sa mõistad probleemi sügavuti ja suudad tulemuse anda, võib juhendaja paluda sul rada A peale vahetada.*

---

#### Rada A: Süstla doseerija

Dobot MG400 külge paigaldatud süstla doseerimissüsteem silikooni kandmiseks. See on jätk kõigele mida ehitasid eelmisel semestril — rõhuandur Andmehõivest, liidestus Nutilahendusest ja mehhaanilised komponendid 3D Printimisest.

**Mida doseerid ja miks:** Solenoidklapil on kaanekork mis istub solenoidikorpuse peal. Selles korgis on kinnitatud kas 4mm toru. Need torud on liimitud omale kohale silikooniga. Ülesanne on täita see väike korgi maht korpuse ja torude vahel silikooniga — täpselt ja korratavalt. Sul on juba olemas solenoid, käsitsi ehitatud versioon koostust ja Fusion 360 mudel detailist. Geomeetria on teada; väljakutse on täitmise automatiseerimine.

**Aktuatsiooni küsimus:** Kuidas suruda süstla kolbi? Sinu spetsifikatsioon peab valima kolmest variantist sobivama loogiliste põhjenduste lausel:

* **Doboti pneumaatiline süsteem** — kasutab MG400 sisseehitatud õhuvarustust kolvi surumiseks suruõhuga. Lihtne juhtimine (avatud/suletud/üle-, ala- rõhk klapp), kuid rõhuregulatsioon määrab voolu täpsuse.
* **Väike servomootor** — servo surub mehhaaniliselt kolbi. Annab otsese positsiooni juhtimise selle üle kui kaugele kolb on liikunud, kuid lisab mehhaanilist keerukust kinnitusele.
* **MG400 sisseehitatud pöördtelg** — kasuta roboti enda 4. telje pööret või Z-telje liikumist suruva mehhanismina. Lisaktuaatorit pole vaja, kuid piirab roboti positsioneerimist doseerimise ajal.

Sinu spetsifikatsioon peab defineerima terviksüsteemi: milline aktuatsiooni meetod ja miks, täpsuseesmärgid (täitemahu täpsus, korratavus), juhtimisarhitektuur andurist roboti liikumiseni ja testimismetoodika doseerimiskvaliteedi valideerimiseks teadaoleva korgi geomeetria vastu.

Milline "valmis" välja näeb Prototüüpimise kursuse lõpus: tootmisvalmis doseerimissüsteem mis suudab tõmmata sirgeid jooni, kaari ja täitealasid ühtlase laiuse ja paksusega, automaatse testimisega kasutades puhaste plaatide sisendpuhvrit ja valminud näidiste väljundpuhvrit.

Sul on eelis kolme kursuse jagu töötavaid prototüüpe, mõõdetud andmeid ja dokumenteeritud ebaõnnestumisi. Kasuta neid. Spetsifikatsioon peaks viitama konkreetsetele numbritele sinu 1. semestri tööst — mitte teooriale vaid sellele mida sa tegelikult mõõtsid.

---

#### Rada B: Sumorobot

SMARS-inspireeritud kuid veelgi lihtsam akutoitel robot mida juhib Android telefon, mõeldud sumomaadluse võistlusteks Narva Kolledži robotiareeni inauguratsiooniüritusel sel suvel. Disainifilosoofia: alusta lihtsalt, taaskasuta vana elektroonikat (vanad telefonid, ümbertöödeldud mootorid, taaskasutatud akud) ja ehita kõigepealt midagi mis töötab. Robotid peavad päriselt töötama ja päriselt võistlema — see ei ole lihtsalt harjutus.

**Telefon-ajuna kontseptsioon:** Vanem Android telefon on roboti aju. Sellel on kaamera, arvutusvõimsus, ekraan ja ühenduvus juba sisseehitatult. Telefon ühendub mootoršassiiga läbi USB OTG kaabli ja käitab kaugjuhtimise tarkvara. See tähendab et sinu "manussüsteem" on tegelikult Androidi rakendus. Telefon istub šassii peal, OTG kaabel jookseb mootori draiverikplaadini ja operaator juhib robotit kaugelt.

**Areeni formaat:** Areen on 3×3 meetrit punase ringiga keskel. Mäng paneb 5 robotit kummalegi poolele — kokku 10 robotit väljakul. Punasesse ringi mahub napilt 5 botti, mis tähendab et positsioneerimine, tõukejõud ja väledus kõik loevad. Sumoreeglid kehtivad: tõuka vastased välja, jää ise sisse.

Sinu spetsifikatsioon peab katma: šassii mehhaaniline disain (SMARS-inspireeritud roomikud, maavaba, kaalujaotumine tõukamiseks — hoia lihtne ja prinditav), mootorite valik ja draiverelektroonika (eelista taaskasutatud/ümbertöödeldud komponente kus võimalik), telefoni kinnitamine ja OTG liideseprotokoll, tarkvaraarhitektuur (Androidi rakendus kaugjuhtimiseks), areeni mõõtmed ja 5v5 mängu piirangud, energiaeelarve ja aku tööaeg ning realistlik ajakava mis lõpeb töötavate robotitega enne suve.

Suve tähtaeg on reaalne. Sinu spetsifikatsioon peab sisaldama arendusgraafikut mis arvestab osade tellimise tarneaega, printimise aega, tarkvaraarenduse iteratsioone ja vähemalt kaht nädalat testimist enne üritust. Sul on vaja piisavalt roboteid 5v5 matšiks — planeeri vastavalt.

---

#### Rada C: MG400 modulaarne tööpink

Portatiivsed modulaarne tööpink mis pannakse kokku ümber Dobot MG400 roboti, inspireeritud keevitajate T-soontega laudadest. Kontseptsioon: alumiiniumprofiili raam mis loob 4-teljelise tööpiirkonna ümber roboti, standardiseeritud kinnituskohtadega 3D-prinditud tööriistahoidjatele. Silumis- ja tootmistööriistad kinnituvad kindlatesse positsioonidesse kus nii robot kui operaator nendeni ulatub.

**Eelarve piirang:** Kogukulu lisaks MG400 robotile ei tohi ületada 1000 eurot. See katab raami, ühendused, 3D-prinditud detailid, tööriistad ja USB-C jaoturi — kõik mis on vajalik palja roboti muutmiseks terviklikuks tööjaamaks.

**Portatiivsuse nõue:** See tööpink peab olema midagi mida üliõpilane saab oma kodu kööglauale üles panna ja kergesti uuesti kokku pakkida. Samuti peab see kohanduma ühelt projektilt teisele kooli sees — vaheta tööriistahoidjaid, konfigureeri positsioone ümber ja kasuta erinevate ülesannete jaoks ilma raami ümber ehitamata. Mõtle sellele kui komplektile mis läheb kohvrist tööjaamaks alla 10 minutiga.

**Näidislik tööriistade nimekiri ja ligikaudsed hinnad:**

| Tööriist | Otstarve | Ligikaudne hind | Märkused |
| :--- | :--- | :--- | :--- |
| USB videomikroskoop | PCB kontroll, jootmiskohtade kvaliteet | €30–80 | USB-C eelistatud |
| USB-C jootekolb (TS101 vms) | Jootmine ja ümbertöö | €50–80 | PD-toitel |
| Kompaktne digitaalne ostsilloskoob (DSO138 või USB-põhine) | Signaalide silumine | €30–150 | USB-C kui saadaval |
| USB signaaligeneraator | Testsignaalide genereerimine | €20–50 | Funktsioonigeneraatori moodul |
| USB-C PD toiteplokk (65W+) | USB-C tööriistade toide | €30–50 | GaN laadija |
| USB-C jaotur (toitega, 7+ porti) | Tsentraalne seadmeühendus | €30–60 | Peab toetama PD läbilaskmist |
| Alumiiniumprofiili komplekt (2020/2040 profiilid + kinnitused) | Raami konstruktsioon | €80–150 | Mõõtu lõigatud või modulaarsed pikkused |
| 3D printimise filament | Tööriistahoidjad, kinnitused, rakised | €20–40 | PLA/PETG |
| Kinnitused, T-mutrid, nurgaklambrid | Koostelisemise riistvara | €20–40 | M5 2020 profiili jaoks |

*See on algusnäidis — sinu spetsifikatsioon peab sisaldama enda uuritud BOM-i tegelike tootelinkkide ja kontrollitud hindadega. Kogusumma peab jääma alla 1000 euro.*

Sinu spetsifikatsioon peab katma: raami mõõtmed ja alumiiniumprofiili valiku (2020, 2040 jne), integratsiooni MG400 tööulatuse ja koordinaatsüsteemiga, 3D-prinditud hoidjate disainid iga tööriista positsiooni jaoks, USB-C jaoturi arhitektuur ja toitejaotumine ühendatud seadmetele, kaabelhaldus, koostamise/lahtivõtmise protseduur, tööriistade positsioonide spetsifikatsioonid roboti koordinaadistiku suhtes ja kontrollimeetod tagamaks korratavat positsioneerimist pärast uuesti kokku panemist.

Eesmärk: üliõpilane kellel on see tööpink saab harjutada robootikat, jootmist, mõõtmist ja silumist kodus samade tööriistadega mis laboris, ning kergesti kohandada seadistust kooliprojektide vahel. Rohkem tööriistade kättesaadavust tähendab rohkem õppimisaega.

---

### Eesmärk

Kirjuta põhjalik süsteemispetsifikatsioon oma valitud projektiraja jaoks. Spetsifikatsioon peab sisaldama funktsionaalseid nõudeid, jõudluseesmärke, liideste definitsioone, komponentide valikuid koos põhjendustega, riskianalüüsi ja testkriteeriume. See peab olema piisavalt detailne et teine meeskond saaks süsteemi ainult sinu dokumendi põhjal üles ehitada.

*See on elav dokument, uuenda eesmärke kui need töö käigus muutuvad — uued teadmised muudavad vanad eesmärgid vahel mõttetuks. Eesmärk on hoida meeskonda kogu aeg sihil, et ei eksitaks detailide metsa ära ja põhiprobleem jääb lahendamata*

*Sinu spetsifikatsioon on sinu juhend verstapostide 2–5 jaoks. Kui vahetad rada hiljem, kaotad spetsifikatsiooni töö. Vali hoolikalt ja spetsifitseeri põhjalikult.*

### Taustainfo

#### Jagatud ressursid (kõik rajad)

* **Kuidas kirjutada tehnilist spetsifikatsiooni**
  [https://www.youtube.com/watch?v=OA6BfCUBnuo](https://www.youtube.com/watch?v=OA6BfCUBnuo)
* **Nõuete inseneeria — MoSCoW prioritiseerimine**
  [https://www.youtube.com/watch?v=jBMnTJa4ZnI](https://www.youtube.com/watch?v=jBMnTJa4ZnI)
* **draw.io süsteemidiagrammide jaoks**
  [https://app.diagrams.net/](https://app.diagrams.net/)
* **Kuidas koostada BOM-i (materjalide nimekiri)**
  [https://www.youtube.com/watch?v=fRhL7bXjITg](https://www.youtube.com/watch?v=fRhL7bXjITg)

#### Rada A: Süstla doseerija

* **Dobot MG400 dokumentatsioon ja tööulatus**
  [https://www.dobot-robots.com/products/desktop-four-axis/mg400.html](https://www.dobot-robots.com/products/desktop-four-axis/mg400.html)
* **Kommertsdoseerimissüsteemide võrdlusalused (Nordson EFD)**
  [https://www.nordson.com/en/divisions/efd/products/dispensing-systems](https://www.nordson.com/en/divisions/efd/products/dispensing-systems)
* **Aja-rõhu doseerimise põhimõtted**
  [https://www.youtube.com/watch?v=jG5Lab-z3r4](https://www.youtube.com/watch?v=jG5Lab-z3r4)

#### Rada B: Sumorobot

* **SMARS — avatud lähtekoodiga modulaarne robotiplatvorm (disaini inspiratsioon)**
  [https://www.smarsfan.com/](https://www.smarsfan.com/)
* **Robotisumo võistlusreeglid (RobotChallenge)**
  [https://www.robotchallenge.org/fileadmin/user_upload/en_Mini_Sumo.pdf](https://www.robotchallenge.org/fileadmin/user_upload/en_Mini_Sumo.pdf)
* **Android USB Host (OTG) režiimi dokumentatsioon**
  [https://developer.android.com/develop/connectivity/usb/host](https://developer.android.com/develop/connectivity/usb/host)
* **Alalisvoolumootorite juhtimine H-sillaga (TB6612FNG)**
  [https://www.youtube.com/watch?v=JPPTRj0KWFg](https://www.youtube.com/watch?v=JPPTRj0KWFg)
* **Diferentsiaalajam / tankroolimise kinemaatika**
  [https://www.youtube.com/watch?v=aE7RosGMcwg](https://www.youtube.com/watch?v=aE7RosGMcwg)
* **Androidi rakenduste arendamine Kotliniga**
  [https://developer.android.com/courses](https://developer.android.com/courses)

#### Rada C: MG400 modulaarne tööpink

* **Alumiiniumprofiili (2020 V-soon) süsteemi juhend**
  [https://www.youtube.com/watch?v=pT03yWCTmGg](https://www.youtube.com/watch?v=pT03yWCTmGg)
* **Dobot MG400 tööulatus ja koordinaatsüsteem**
  [https://www.dobot-robots.com/products/desktop-four-axis/mg400.html](https://www.dobot-robots.com/products/desktop-four-axis/mg400.html)
* **USB-C Power Delivery selgitatuna**
  [https://www.youtube.com/watch?v=LhTd5siGE1c](https://www.youtube.com/watch?v=LhTd5siGE1c)
* **Modulaarse kinnitamise kontseptsioonid (keevituslaua tarvikud)**
  [https://www.youtube.com/watch?v=mH2h0NBlYeg](https://www.youtube.com/watch?v=mH2h0NBlYeg)
* **Portatiivsed elektroonika tööjaama disainiideed**
  [https://www.youtube.com/watch?v=YLIPaSk5vos](https://www.youtube.com/watch?v=YLIPaSk5vos)

*Lisa siia omapoolseid allikaid ja kasulikku informatsiooni mis aitaks sul projektis aru saada aastaid hiljem kui selle uuesti lahti teed.*

### Vahendid

1. Fusion 360 (kontseptsiooni maketid ja ruumiline analüüs)
2. draw.io või Excalidraw (süsteemiarhitektuuri diagrammid)
3. Git repositoorium
4. VS Code või tekstiredaktor (spetsifikatsiooni dokument)
5. Jupyter Lab (teostatavuse arvutused ja analüüs)
6. Tabelarvutustööriist (BOM, kuluanalüüs, võrdlustabelid)

Rajaspetsiifilised täiendused:

* Rada A: Ostsilloskoob, rõhutestimise pink, 1. semestri prototüüp referentsmõõtmisteks
* Rada B: Android telefon OTG teostatavuse testimiseks, mootori draiverikplaat pinktestide jaoks
* Rada C: Nihikkaliiber, mõõdulint, MG400 juurdepääs tööulatuse kontrollimiseks

*Kui plaan muutub siis muuda ka vahendeid, või tee [draw.io](http://draw.io)'s joonis kuidas asjad funktsionaalselt seostuvad.*

### Mida spetsifikatsioon sisaldab

See sektsioon õpetab sulle kuidas korralik insenerispetsifikatsioon välja näeb. Iga allolev alajaotis peab esinema sinu spetsifikatsiooni dokumendis. Näited kasutavad süstla doseerijat, kuna kõik mõistavad seda konteksti 1. semestrist — kohanda need oma valitud raja järgi.

*Sul on 10 tundi. Terviklik aga pinnapealne spetsifikatsioon on parem kui sügav aga mittetäielik. Kata kõigepealt kõik sektsioonid, seejärel süvene sinu raja jaoks kõige kriitilisematesse valdkondadesse.*

#### Süsteemi ülevaade

Ühe lõigu kirjeldus sellest mida süsteem teeb. Kontekstidiagramm mis näitab süsteemi piiri — mis on sees vs. väljas. Kes kasutab, kes hooldab, millises keskkonnas töötab.

#### Funktsionaalsed nõuded

Nummerdatud nimekiri asjadest mida süsteem PEAB tegema. Iga nõue peab olema testitav — saad kirjutada testi mis tõestab et see töötab või ei tööta.

Kasuta MoSCoW prioritiseerimist:
* **PEAB** (MUST) — süsteem kukub ilma selleta läbi
* **PEAKS** (SHOULD) — oluline aga mitte kriitiline
* **VÕIKS** (COULD) — tore kui aeg lubab

Näide: *"FN-001 (PEAB): Süsteem peab doseerima ühtlase joonega materjali ühtlase laiusega (varieeruvus < 10% sihtlaiusest) kiirustel 5 mm/s kuni 50 mm/s."*

Eesmärk on vähemalt 10 funktsionaalset nõuet.

#### Jõudluseesmärgid

Kvantitatiivsed spetsifikatsioonid ühikute ja mõõtemeetoditega. Kasuta seda tabeliformaati:

| Parameeter | Eesmärk | Minimaalne vastuvõetav | Mõõtemeetod |
| :--- | :--- | :--- | :--- |
| Joone laiuse täpsus | ±0.1 mm | ±0.3 mm | Mikroskoobimõõtmine |
| Doseerimiskiirus | 5–50 mm/s | 5–20 mm/s | Roboti trajektoori ajastus |
| Süstla vahetuse aeg | < 30 s | < 60 s | Stopper |

Täida see oma raja tegelike parameetritega.

#### Süsteemi arhitektuur

Plokkskeem mis näitab kõiki alamsüsteeme ja nende liidesesid. Iga liidese jaoks täpsusta: protokoll, signaalitasemed, andmeformaat. Viita selgelt kolmele eeldusainele — milline alamsüsteem tuli millisest ainest (või on selle projekti jaoks uus).

#### Komponentide valik ja põhjendus

Iga olulise komponendi kohta: mis see on, miks sa selle valisid, milliseid alternatiive kaalusid. Kasuta sama otsustusmudelit mis Andmehõive Labor 2-s (kus võrdlesid pingejaagurit vs. op-ampi) — sama struktuur, erinev teema.

Lisa esialgne BOM (materjalide nimekiri) koos hinnanguliste kuludega. Radade B ja C meeskonnad: lisage kust iga komponenti tellida ja hinnangulised tarneajad.

#### Mehhaaniline kontseptsioon

Mõõtmetega kontseptsioonijoonis — kas Fusion 360 renderid või käsijoonised mõõtmetega. Identifitseeri kriitilised mõõtmed ja tolerantsid. Põhjenda materjalivalikuid.

Vähemalt üks kriitiline mõõde peab olema füüsiliselt kontrollitud — mõõdetud päris riistvaralt, andmelehelt või robotilt endalt. Ära arva — mõõda.

#### Elektriline arhitektuur

Plokitaseme skemaatiline joonis kõikidest elektrilistest ühendustest. Energiaeelarve: pingeriiulid, voolutarbimine alamsüsteemide kaupa, kogutarbimine vs. toitevõimsus. Signaalide nimekiri: mis ühendub millega, pingetasemed, protokollid.

#### Tarkvaraarhitektuur

Mooduldiagramm mis näitab tarkvarakomponente ja nende seoseid. Kommunikatsiooniprotokollide definitsioonid. Olekumasin või vooskeem peamise juhtusloogika jaoks.

Rada B meeskonnad: siin elab teie Androidi rakenduse arhitektuur. Defineeri OTG kommunikatsiooniprotokoll, mootori juhtimisliides ja kasutajaliides.

#### Riskianalüüs

Tabel tuvastatud tehnilistest riskidest. Iga risk saab: kirjeldus, tõenäosus (K/M/M), mõju (K/M/M) ja leevendusstrateegia. Tuvasta vähemalt 5 reaalset riski — mitte üldist "asjad võivad katki minna" vaid konkreetseid tehnilisi riske mida oled spetsifikatsiooni kirjutamise käigus tuvastanud.

Näide: *"Risk: ESP32 ADC mittelineaarsus põhjustab >5% viga kõrgel rõhul. Tõenäosus: M. Mõju: K. Leevendus: Kasuta op-amp signaali konditsioneerimist AH Labor 2 disainist, valideeri kalibreerimisega 5 rõhupunktis."*

#### Testimisplaan

Iga funktsionaalse nõude kohta: kuidas testid seda? Millist varustust on vaja? Mis on läbinud/läbikukkunud kriteerium? See toidab otse verstaposti 2 (võtmetehnoloogia valideerimine) — testid mida siin defineerid on testid mida seal käivitad.

#### Arenduse ajakava

Kaardista ülejäänud verstapostid 2–5 konkreetsete tulemustega. Kes teeb mida (meeskonna rollide jaotus). Ülesannete vahelised sõltuvused. Rada B jaoks: ajakava peab lõppema töötavate robotitega enne suve areeniüritust — planeeri sellest kuupäevast tagurpidi.

### Projekti ülesehitus

**Faas 1: Uurimine ja võrdlusanalüüs**

- [ ] Uuri olemasolevaid kommerts- või avatud lähtekoodiga lahendusi oma valitud raja jaoks
- [ ] Dokumenteeri vähemalt 3 referentssüsteemi koos nende spetsifikatsioonidega
- [ ] Tuvasta olemasolevate lahenduste peamised eristajad ja piirangud

**Faas 2: Nõuete defineerimine**

- [ ] Kirjuta funktsionaalsed nõuded (vähemalt 10)
- [ ] Defineeri jõudluseesmärgid koos mõõtemeetoditega
- [ ] Tuvasta kõik välised liidesed (mehhaanilised, elektrilised, tarkvaralised)

**Faas 3: Süsteemiarhitektuur**

- [ ] Loo süsteemi plokkskeem draw.io's
- [ ] Defineeri kõik alamsüsteemide vahelised liidesed
- [ ] Kaardista alamsüsteemid eelduskursuste tööga (mis on olemas vs. mis on uus)

**Faas 4: Teostatavusanalüüs**

- [ ] Komponentide valik koos alternatiivide analüüsiga
- [ ] Esialgne BOM kuluhinnanguga
- [ ] Energiaeelarve arvutus
- [ ] Tuvasta 5 peamist tehnilist riski koos leevendusstrateegiatega

**Faas 5: Kontseptsiooni disain**

- [ ] Mehhaanilise kontseptsiooni visandid kriitiliste mõõtmetega
- [ ] Elektriline plokkskeem signaalide nimekirjaga
- [ ] Tarkvaraarhitektuuri diagramm

**Faas 6: Testimise planeerimine ja ajakava**

- [ ] Kirjuta testimisplaan iga funktsionaalse nõude jaoks
- [ ] Loo arenduse ajakava verstapostide 2–5 jaoks
- [ ] Määra meeskonna rollid ja vastutused

*Kaugel oled? Millal valmis saad? Kuidas kiiremini saaks? — need tavalised küsimused*

### Teostatavusanalüüs

Kuna sa kirjutad spetsifikatsiooni ja veel ei ehita, on selle verstaposti "simulatsioon" analüütiline töö mis valideerib kas sinu spetsifikatsioon on füüsiliselt teostatav. Ära spetsifitseeri midagi mida sa ehitada ei suuda.

#### Analüüs 1: Füüsilise teostatavuse kontroll

Vali oma spetsifikatsioonist kõige kriitilisem jõudlusparameeter. Näita arvutuste või lihtsa simulatsiooniga et sinu disain suudab seda saavutada.

**Rada A näide:** Arvuta rõhk mis on vajalik sihtvoolu saavutamiseks läbi antud nõelagabarite. Kasuta Poiseuille'i seadust või tootja andmeid. Kas sinu pneumaatiline süsteem annab piisavalt rõhku? Kas voolu kiirus on ühilduv sinu sihtdoseerimiskiirusega?

**Rada B näide:** Arvuta pöördemoment mis on vajalik vastase roboti (hinnanguline mass) areenist välja tõukamiseks ajalimiti jooksul. Kas sinu valitud mootor annab ülekandearvu kaudu piisavalt pöördemomenti? Milline on aku tööaeg täiskoormusel?

**Rada C näide:** Modelleeri MG400 tööulatus Fusion 360-s. Paiguta oma tööpingi raam ja tööriistahoidjad mudelisse. Kas robot ulatub kõigisse vajalikesse positsioonidesse ilma kokkupõrketeta? Milline on maksimaalne tööriista kõrgus enne kui robot ei ulatu sellest üle?

#### Analüüs 2: Kulu-jõudluse kompromiss

Tuvasta üks disainiotsus kus seisad silmitsi kulu-jõudluse kompromissiga. Esita analüüs samas formaadis nagu pingejaguri vs. op-ampi võrdlus Andmehõive Labor 2-st:

* Variant A: kirjeldus, kulu, jõudlus
* Variant B: kirjeldus, kulu, jõudlus
* Otsus ja põhjendus

#### Analüüs 3: Varasema töö ülevaade

**Rada A:** Vaata üle mõõtmisandmed, veebiliidese jõudlus või mehhaaniline disain 1. semestrist. Mis töötas? Mida on vaja parandada? Viita konkreetsetele numbritele oma varasemast laborist — mitte teooriale vaid sellele mida sa mõõtsid. Kasuta neid andmeid spetsifikatsioonivalikute põhjendamiseks.

**Rajad B ja C:** Kuna 1. semestri eelkäijat pole, tee selle asemel tehnoloogia uuring. Leia 3 sarnast projekti (GitHubi repod, Instructables, teadusartiklid, YouTube'i ehitused) ja analüüsi nende spetsifikatsioone vs. tegelikke tulemusi. Mida saad nende kogemusest õppida? Milliseid vigu sa väldid?

*Need on sinu esimesed analüüsid. Lisa rohkem kui avastad küsimusi spetsifikatsiooni kirjutamise käigus. Spetsifikatsioon mis ei tekita ühtegi küsimust on spetsifikatsioon mis ei vaadanud piisavalt sügavale.*

### Arenduslogi

### Tulemused

**Kõik rajad esitavad:**

| Väljund | Kirjeldus |
| :--- | :--- |
| Spetsifikatsiooni dokument | PDF või Markdown — kõik sektsioonid ülalpool olevast "Mida spetsifikatsioon sisaldab" |
| Süsteemiarhitektuuri diagramm | draw.io — plokkskeem liidestega |
| Teostatavusanalüüsi notebook | Jupyter Lab — kõik kolm analüüsi koos arvutustega |
| BOM tabel | Komponendid, kogused, ühikuhinnad, kokku ja tarnija lingid |
| Kontseptsioonimudelid | Fusion 360 — mõõtmetega kontseptsiooni maketid |
| Arenduse ajakava | Gantti diagramm või verstapostide tabel verstapostide 2–5 jaoks |

Git repo:
Spetsifikatsiooni dokument:
Süsteemiarhitektuuri diagramm:
Teostatavusanalüüsi notebook:
BOM tabel:
Arenduslogi:

### Hindamine

Iga kategooria on kuni 4 punkti. Kokku: 20 punkti.

**Tööfailid (4 punkti) — Spetsifikatsiooni terviklikkus**

Kõik nõutud spetsifikatsiooni sektsioonid olemas ja sisulised (mitte kohahoidjad). Fusion 360 kontseptsioonimudelid olemas ja korrektselt piiratud. draw.io diagrammid selged ja terviklikud. Failid organiseeritud git repositooriumis tähendusrikka commit ajalooga.

* 4 p: Kõik sektsioonid terviklikud ja sügavad
* 3 p: Enamik sektsioone terviklikud, väikesed puudujäägid
* 2 p: Ainult tuumsektsioonid, olulised puudujäägid
* 1 p: Skelettdokument
* 0 p: Esitamata

**Simulatsioon / Analüüs (4 punkti) — Teostatavuse valideerimine**

Füüsilise teostatavuse arvutus on korrektne ja asjakohane. Kulu-jõudluse kompromissi analüüs kasutab tegelikke numbreid. 1. semestri retrospektiiv (Rada A) viitab tegelikele mõõdetud andmetele, või tehnoloogiauuring (Rajad B/C) viitab reaalsetele projektidele. Arvutused on reprodutseeritavad esitatud Jupyteri notebooks.

* 4 p: Kõik kolm analüüsi terviklikud korrektse metoodikaga
* 3 p: Kaks analüüsi terviklikud
* 2 p: Üks analüüs terviklik
* 1 p: Katse ilma ranguseta
* 0 p: Analüüs puudub

**Prototüüp / Füüsiline (4 punkti) — Kontseptsiooni elujõulisus**

Mehhaanilisel kontseptsioonil on realistlikud mõõtmed (mitte fantaasianumbrid). Komponentide valikud on tegelikult ostetavad detailid koos andmelehtedega. Energiaeelarve läheb kokku (kogutarbimine vs. toitevõimsus). Vähemalt üks kriitiline mõõde on füüsiliselt kontrollitud (mõõdetud päris riistvaralt või andmelehelt). Rada A jaoks: 1. semestri prototüübi fotod/mõõtmised lisatud viitena.

* 4 p: Kontseptsioon on ehitatav nagu spetsifitseeritud
* 3 p: Enamasti ehitatav, väikesed teostatavuse puudujäägid
* 2 p: Olulised teostatavuse puudujäägid tuvastatud
* 1 p: Mõõtmed või komponendid pole realistlikud
* 0 p: Kontseptsiooni disain puudub

**Dokumentatsioon (4 punkti) — Spetsifikatsiooni kvaliteet**

Nõuded on nummerdatud, testitavad ja prioritiseeritud (PEAB/PEAKS/VÕIKS). Diagrammid kasutavad korrektset notatsioon ja on loetavad. Riskianalüüs tuvastab reaalseid riske (mitte üldisi). Testimisplaan seostub konkreetsete nõuetega. Kirjutamine on selge, organiseeritud ja ühemõtteline.

* 4 p: Spetsifikatsioon saaks suunata arendust teise meeskonna poolt
* 3 p: Selge aga vajab kohati täpsustamist
* 2 p: Arusaadav ainult autoritele
* 1 p: Korraldamata
* 0 p: Dokumenteerimata

**Küsimuste-vastuste sessioon ja tagasiside (4 punkti) — Kaitsmine**

Meeskond suudab selgitada ja kaitsta igat spetsifikatsiooni valikut. Meeskond suudab tuvastada nõrkused ja tundmatused oma spetsifikatsioonis. Meeskond esitab sisulisi küsimusi ja tagasisidet teiste meeskondade spetsifikatsioonidele.

* 4 p: Tugev kaitsmine ja aktiivne osalemine
* Skaleeritakse proportsionaalselt alla

### Tagasiside

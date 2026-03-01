## Prototüüpimine: Verstapost 1

Eelmisel semestril ehitasid alamsüsteeme. Andmehõive andis sulle andurid ja mõõteahelad. Nutilahendused andis veebiliidesed, VPN-tunnelid ja MQTT infrastruktuuri. 3D Printimine andis mehhaanilise disaini ja tootmisoskused. Iga aine andis töötavad tükid. Ükski neist ei andnud töötavat süsteemi.

See aine on koht kus tükid saavad süsteemiks. Sa tuled testitud komponentide ja tõestatud tehnoloogiatega. Väljakutse on integratsioon, viimistlemine ja millegi tegemine mis töötab piisavalt usaldusväärselt et päriselt kasutada.

Aga enne kui puudutad ühtegi juhet või prindid ühtegi detaili — kirjutad spetsifikatsiooni. Ehitamine ilma spetsifikatsioonita on kuidas projektid surevad. Sa ei tea milline "valmis" välja näeb, sa ei saa tööd meeskonnas jagada ja sul pole mille vastu testida. Spetsifikatsioon on leping sinu praeguse mina (kellel on ideed) ja tuleviku mina (kes peab tulemuse andma) vahel.

See verstapost on koht kus meeskond valib projektiraja ja koostab spetsifikatsiooni mis on piisavalt detailne et teine meeskond saaks süsteemi ainult sinu dokumendi põhjal üles ehitada.

---

#### A: Süstla doseerija

Dobot MG400 külge paigaldatud süstla doseerimissüsteem silikooni kandmiseks. See on jätk kõigele mida ehitasid eelmisel semestril — rõhuandur Andmehõivest, liidestus Nutilahendusest ja mehhaanilised komponendid 3D Printimisest.

**Mida doseerid ja miks:** Solenoidklapil on kaanekork mis istub solenoidikorpuse peal. Selles korgis on kinnitatud kaks 4 millimeetrist toru. Need torud on liimitud omale kohale silikooniga. Ülesanne on täita see väike maht korgi korpuse ja torude vahel silikooniga — täpselt ja korratavalt. Sul on juba olemas solenoidi kaan, käsitsi ehitatud versioon koostust ja Fusion 360 mudel detailist. Geomeetria on teada; väljakutse on täitmise automatiseerimine. Ka kaane enda disaini võib muuta. 

**Aktuatsiooni küsimus:** Kuidas suruda süstla kolbi? Sinu spetsifikatsioon peab valima kolmest variantist sobivama loogiliste põhjenduste lausel:

* **Doboti pneumaatiline süsteem** — kasutab MG400 sisseehitatud õhuvarustust kolvi surumiseks suruõhuga. Lihtne juhtimine (avatud/suletud/üle-, ala- rõhk klapp), kuid rõhuregulatsioon määrab voolu täpsuse.
* **Väike servomootor** — servo surub mehhaaniliselt kolbi. Annab otsese positsiooni juhtimise selle üle kui kaugele kolb on liikunud, kuid lisab mehhaanilist keerukust kinnitusele.
* **MG400 sisseehitatud pöördtelg** — kasuta roboti enda 4. telje pööret või Z-telje liikumist suruva mehhanismina. Lisaktuaatorit pole vaja, kuid piirab roboti positsioneerimist doseerimise ajal.

Sinu spetsifikatsioon peab defineerima terviksüsteemi: milline aktuatsiooni meetod ja miks, täpsuseesmärgid (täitemahu täpsus, korratavus), juhtimisarhitektuur andurist roboti liikumiseni ja testimismetoodika doseerimiskvaliteedi valideerimiseks teadaoleva korgi geomeetria vastu.

Milline "valmis" välja näeb Prototüüpimise kursuse lõpus: tootmisvalmis doseerimissüsteem mis suudab tõmmata sirgeid jooni, kaari ja täitealasid ühtlase laiuse ja paksusega, automaatse testimisega kasutades puhaste plaatide sisendpuhvrit ja valminud näidiste väljundpuhvrit.

Sul on eelis kolme kursuse jagu töötavaid lahendusi, mõõdetud andmeid ja dokumenteeritud ebaõnnestumisi. Kasuta neid. 

---

#### B: Sumorobot

SMARS-inspireeritud kuid veelgi lihtsam akutoitel robot mida juhib Android telefon, mõeldud sumomaadluse võistlusteks Narva Kolledži robotiareeni avaüritusel sel suvel. Disainifilosoofia: alusta lihtsalt, taaskasuta vana elektroonikat (süstemaatiliselt saab ksutada telefone) ja ehita kõigepealt midagi mis töötab. Robotid peavad päriselt töötama sõitma mõõtma kaugust eest, nägmea värvi enda all, nägema kaamera pilti enda ees ja positsioneerima ennast lugedes laest QR koode ja nende asukohtasi. 

**Telefon-ajuna kontseptsioon:** Vanem Android telefon on roboti aju. Sellel on kaamera, arvutusvõimsus, ekraan ja ühenduvus juba sisseehitatult. Telefon ühendub mootoršassiiga läbi USB OTG kaabli ja ESP32 MCU mis liidestab kaugjuhtimise tarkvara. See tähendab et sinu "manussüsteem" on tegelikult Androidi rakendus. Telefon istub šassii peal, OTG kaabel jookseb mootori draiverikplaadini ja operaator juhib robotit kaugelt.

**Areeni formaat:** Areen on 3×3 meetrit punase ringiga keskel. Mäng paneb 5 robotit kummalegi poolele — kokku 10 robotit väljakul. Punasesse ringi mahub napilt 5 botti, mis tähendab et positsioneerimine, tõukejõud ja väledus kõik loevad. Sumoreeglid kehtivad: tõuka vastased välja, jää ise sisse.

Sinu spetsifikatsioon peab katma: šassii mehhaaniline disain (SMARS-inspireeritud roomikud, maavaba, kaalujaotumine tõukamiseks — hoia lihtne ja prinditav), mootorite valik ja draiverelektroonika (eelista taaskasutatud/ümbertöödeldud komponente kus võimalik), telefoni kinnitamine ja OTG liideseprotokoll, tarkvaraarhitektuur (Androidi rakendus kaugjuhtimiseks), areeni mõõtmed ja 5v5 mängu piirangud ja aku tööaeg ning realistlik ajakava mis lõpeb töötavate robotitega enne suve.

Suve tähtaeg on reaalne. Sinu spetsifikatsioon peab sisaldama arendusgraafikut mis arvestab osade tellimise tarneaega, printimise aega, tarkvaraarenduse iteratsioone ja vähemalt kaht nädalat testimist enne üritust. Sul on vaja piisavalt roboteid 5v5 matšiks — planeeri vastavalt.

---

#### C: MG400 modulaarne tööpink

See projekt koosneb kolmest omavahel seotud alamprojektist mis koos moodustavad tervikliku portatiivse tööjaama Dobot MG400 roboti ümber. Eesmärk on et tudeng saab kogu töövoo — roboti, töölaua, tööriistad ja dokumentatsiooni — koju kaasa võtta või kooli sees projektide vahel ümber seadistada. Kui dokumentatsioon on korras, saab sama töövoo üles panna ka teise samasuguse roboti peale kasvõi teises riigis.

**Eelarve:** Sinu spetsifikatsioon peab defineerima kogu komplekti sihteelarve (lisaks MG400 robotile) ja seda põhjendama. Kui palju tohib kogu komplekt maksma minna et kool saaks seda tudengitele rentimiseks pakkuda? See number peab tulema sinu analüüsist, mitte ette antud piirangust.

##### Alamprojekt 1: Töölaud

Modulaarne töölaud kuhu peale saab lihtsalt kinnitada 3D-prinditud konstruktsioone — tööriistahoidjaid, rakiseid, kinnituselemente. Töölaud peab looma roboti ümber tööpiirkonna kus nii robot kui operaator tööriistadeni ulatuvad.

Peamine disainiküsimus: kuidas ehitada laud mis on piisavalt jäik tööks, piisavalt kerge transportimiseks ja piisavalt modulaarne ümberseadistamiseks? Variante on palju — alumiiniumprofiil (2020/2040), PVC-lehed punnkinnitustega, 3D-prinditud ühendused metalltoruga, vineer CNC-ga lõigatud pesadega — ja igal lähenemisel on omad kompromissid jäikuse, kaalu, hinna ja modulaarsuse vahel. Sinu ülesanne on valida ja põhjendada.

Kriitilised nõuded:
* Peab integreeruma MG400 tööulatuse ja koordinaatsüsteemiga
* 3D-prinditud hoidjate kinnituspositsioonid peavad olema dokumenteeritud roboti koordinaadistiku suhtes
* Pärast lahtivõtmist ja uuesti kokkupanemist peavad positsioonid olema korratavad
* Kogu töölaua dokumentatsioon peab olema piisav et keegi teine saaks sama seadistuse reprodutseerida

##### Alamprojekt 2: Transpordisüsteem

Transpordikast (papp, vineer, vahtkast vms) kuhu mahub Dobot MG400, töölaud ja kõik tööriistad. See peab olema piisavalt vastupidav et tudeng saab komplekti kooli ja kodu vahel turvaliselt transportida.

Spetsifikatsioon peab katma:
* Kasti sisemised mõõtmed ja paigutus — kõik peab oma kohale mahtuma ilma lahtise ruumita kus asjad ringi logisevad
* Kaitsev polsterdus roboti ja tööriistade jaoks
* Kaal ja kandevõime — üks inimene peab suutma kanda
* Materjali valik ja hind
* Inventuuri nimekiri kastis (et kontrollida kas kõik on tagastatud)

##### Alamprojekt 3: Elektroonika tööriistad

Komplekt elektroonika tööriistu mis katab jootmise, mõõtmise, silumise ja signaalianalüüsi. Eelistada USB-C toitega tööriistu kus võimalik — üks toiteplokk ja jaotur katab kogu komplekti.

| Tööriist | Otstarve | Märkused |
| :--- | :--- | :--- |
| Jootekolb (TS101 vms) | Jootmine ja ümbertöö | USB-C PD toitel |
| Ostsilloskoob / multimeeter | Signaalide mõõtmine ja silumine | Kompaktne, USB-põhine või DSO138 |
| Toiteplokk | Reguleeritav pinge ahelate toiteks | USB-C PD kui võimalik |
| Signaaligeneraator | Testsignaalide genereerimine | Funktsioonigeneraatori moodul |
| Seerialanalüsaator | UART/SPI/I2C silumiseks | Saleae Logic vms |
| Jootmismikroskoop | PCB kontroll, jootmiskohtade kvaliteet | USB videomikroskoop |
| USB-C PD toiteplokk (65W+) | Kõigi USB-C tööriistade toide | GaN laadija |
| USB-C jaotur (toitega, 7+ porti) | Tsentraalne ühendus | Peab toetama PD läbilaskmist |

*See on algusnäidis — sinu spetsifikatsioon peab sisaldama enda uuritud BOM-i tegelike tootelinkkide ja kontrollitud hindadega.*

Sinu spetsifikatsioon peab katma kõik kolm alamprojekti koos BOM-i, mõõtmete, materjalivalikute ja põhjendustega. Iga tehniline omadus — eelarve, kaal, mõõtmed, tööriistade arv, toitevõimsus — on midagi mida sina defineerid ja põhjendad, mitte midagi mis on ette antud. Kogu süsteem peab olema dokumenteeritud nii et teine meeskond saaks selle reprodutseerida.

---

### Eesmärk

Kirjuta põhjalik süsteemispetsifikatsioon oma valitud projektiraja jaoks. Spetsifikatsioon peab sisaldama funktsionaalseid nõudeid, jõudluseesmärke, liideste definitsioone, komponentide valikuid koos põhjendustega, riskianalüüsi ja testkriteeriume. See peab olema piisavalt detailne et teine meeskond saaks süsteemi ainult sinu dokumendi põhjal üles ehitada.

### Taustainfo

#### Jagatud ressursid

#### A: Süstla doseerija

* **Dobot MG400 dokumentatsioon ja tööulatus**
  [https://www.dobot-robots.com/products/desktop-four-axis/mg400.html](https://www.dobot-robots.com/products/desktop-four-axis/mg400.html)
* **Kommertsdoseerimissüsteemide võrdlusalused**
  
  tba
* **Aja-rõhu doseerimise põhimõtted**
  [https://www.youtube.com/watch?v=jG5Lab-z3r4](https://www.youtube.com/watch?v=jG5Lab-z3r4)

#### B: Sumorobot

* **SMARS — avatud lähtekoodiga modulaarne robotiplatvorm (disaini inspiratsioon)**
  [https://www.smarsfan.com/](https://www.smarsfan.com/)
* **mecArena**
  [https://github.com/KKallas/Robot-Arena/blob/main/BOT-SPECIFICATIONS.md](https://github.com/KKallas/Robot-Arena/blob/main/BOT-SPECIFICATIONS.md)
* **Android USB Host (OTG) režiimi dokumentatsioon**
  [https://developer.android.com/develop/connectivity/usb/host](https://developer.android.com/develop/connectivity/usb/host)
* **Alalisvoolumootorite juhtimine**
  [https://www.youtube.com/watch?v=ygrsIqWOh3Y&t=77s](https://www.youtube.com/watch?v=ygrsIqWOh3Y&t=77s)
* **Diferentsiaalajam / tankroolimise kinemaatika**
  [https://www.youtube.com/watch?v=aE7RosGMcwg](https://www.youtube.com/watch?v=aE7RosGMcwg)
* **Androidi terminal (python ja flask)**
  [hhttps://www.youtube.com/watch?v=HarwU8bxvTQ](https://www.youtube.com/watch?v=HarwU8bxvTQ)

#### C: MG400 modulaarne tööpink

* **Dobot MG400 tööulatus ja koordinaatsüsteem**
  [https://www.dobot-robots.com/products/desktop-four-axis/mg400.html](https://www.dobot-robots.com/products/desktop-four-axis/mg400.html)

* **Modulaarse kinnitamise kontseptsioonid**
  tba


*Lisa siia omapoolseid allikaid ja kasulikku informatsiooni mis aitaks sul projektis aru saada aastaid hiljem kui selle uuesti lahti teed.*

### Vahendid

1. Fusion 360 (kontseptsiooni maketid ja ruumiline analüüs)
2. draw.io või Excalidraw (süsteemiarhitektuuri diagrammid)
3. Git repositoorium
4. VS Code või tekstiredaktor (spetsifikatsiooni dokument)
5. Jupyter Lab (teostatavuse arvutused ja analüüs)
6. Tabelarvutustööriist (BOM, kuluanalüüs, võrdlustabelid)

* A: Ostsilloskoob, rõhutestimise pink, 1. semestri prototüüp referentsmõõtmisteks
* B: Android telefon OTG teostatavuse testimiseks, mootori draiverikplaat pinktestide jaoks
* C: Nihikkaliiber, mõõdulint, MG400 juurdepääs tööulatuse kontrollimiseks

*Kui plaan muutub siis muuda ka vahendeid, või tee [draw.io](http://draw.io)'s joonis kuidas asjad funktsionaalselt seostuvad.*

### Mida spetsifikatsioon sisaldab

See sektsioon õpetab sulle kuidas korralik insenerispetsifikatsioon välja näeb. Iga allolev alajaotis peab esinema sinu spetsifikatsiooni dokumendis. Näited kasutavad süstla doseerijat, kuna kõik mõistavad seda konteksti 1. semestrist — kohanda need oma valitud projekti järgi.

*Sul on 10 tundi. Terviklik aga pinnapealne spetsifikatsioon on parem kui sügav aga mittetäielik. Kata kõigepealt kõik sektsioonid, seejärel süvene sinu projekti jaoks kõige kriitilisematesse valdkondadesse.*

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

Kvantitatiivsed spetsifikatsioonid ühikute ja mõõtemeetoditega. Iga parameeter on midagi mida sina defineerid — mis on sinu süsteemi jaoks oluline mõõta, milline on siht ja milline on minimaalselt vastuvõetav tase? Kasuta seda tabeliformaati:

| Parameeter | Eesmärk | Minimaalne vastuvõetav | Mõõtemeetod |
| :--- | :--- | :--- | :--- |
| ... | ... | ... | ... |
| ... | ... | ... | ... |
| ... | ... | ... | ... |

Vali parameetrid mis on sinu projekti jaoks kriitilised. Numbrid peavad tulema sinu analüüsist — ära võta laest ega arva, vaid põhjenda miks just see väärtus.

#### Komponentide valik ja põhjendus

Iga olulise komponendi kohta: mis see on, miks sa selle valisid, milliseid alternatiive kaalusid. Kasuta sama otsustusmudelit mis Andmehõive Labor 2-s (kus võrdlesid pingejaagurit vs. op-ampi) — sama struktuur, erinev teema.

Lisa esialgne BOM (materjalide nimekiri) koos hinnanguliste kuludega. B ja C meeskonnad: lisage kust iga komponenti tellida ja hinnangulised tarneajad.

#### Mehhaaniline kontseptsioon

Mõõtmetega kontseptsioonijoonis — kas Fusion 360 renderid või käsijoonised mõõtmetega. Identifitseeri kriitilised mõõtmed ja tolerantsid. Põhjenda materjalivalikuid.

Vähemalt üks kriitiline mõõde peab olema füüsiliselt kontrollitud — mõõdetud päris riistvaralt, andmelehelt või robotilt endalt. Ära arva — mõõda.

#### Elektriline arhitektuur

Plokitaseme skemaatiline joonis kõikidest elektrilistest ühendustest. Energiaeelarve: pingeriiulid, voolutarbimine alamsüsteemide kaupa, kogutarbimine vs. toitevõimsus. Signaalide nimekiri: mis ühendub millega, pingetasemed, protokollid.

#### Tarkvaraarhitektuur

Mooduldiagramm mis näitab tarkvarakomponente ja nende seoseid. Kommunikatsiooniprotokollide definitsioonid. Olekumasin või vooskeem peamise juhtusloogika jaoks.

B meeskonnad: siin elab teie Androidi rakenduse arhitektuur. Defineeri OTG kommunikatsiooniprotokoll, mootori juhtimisliides ja kasutajaliides.

#### Testimisplaan

Iga funktsionaalse nõude kohta: kuidas testid seda? Millist varustust on vaja? Mis on läbinud/läbikukkunud kriteerium? See toidab otse verstaposti 2 (võtmetehnoloogia valideerimine) — testid mida siin defineerid on testid mida seal käivitad.

#### Arenduse ajakava

Kaardista ülejäänud verstapostid 2–5 konkreetsete tulemustega. Kes teeb mida (meeskonna rollide jaotus). Ülesannete vahelised sõltuvused. B jaoks: ajakava peab lõppema töötavate robotitega enne suve areeniüritust — planeeri sellest kuupäevast tagurpidi.

### Projekti ülesehitus

**Faas 1: Uurimine ja võrdlusanalüüs**

- [ ] Uuri olemasolevaid kommerts- või avatud lähtekoodiga lahendusi oma valitud projekti jaoks
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

**A näide:** Arvuta rõhk mis on vajalik sihtvoolu saavutamiseks läbi antud nõelagabarite. Kasuta Poiseuille'i seadust või tootja andmeid. Kas sinu pneumaatiline süsteem annab piisavalt rõhku? Kas voolu kiirus on ühilduv sinu sihtdoseerimiskiirusega?

**B näide:** Arvuta pöördemoment mis on vajalik vastase roboti (hinnanguline mass) areenist välja tõukamiseks ajalimiti jooksul. Kas sinu valitud mootor annab ülekandearvu kaudu piisavalt pöördemomenti? Milline on aku tööaeg täiskoormusel?

**C näide:** Modelleeri MG400 tööulatus Fusion 360-s. Paiguta oma tööpingi raam ja tööriistahoidjad mudelisse. Kas robot ulatub kõigisse vajalikesse positsioonidesse ilma kokkupõrketeta? Milline on maksimaalne tööriista kõrgus enne kui robot ei ulatu sellest üle?

#### Analüüs 2: Kulu-jõudluse kompromiss

Tuvasta üks disainiotsus kus seisad silmitsi kulu-jõudluse kompromissiga. Esita analüüs samas formaadis nagu pingejaguri vs. op-ampi võrdlus Andmehõive Labor 2-st:

* Variant A: kirjeldus, kulu, jõudlus
* Variant B: kirjeldus, kulu, jõudlus
* Otsus ja põhjendus

#### Analüüs 3: Varasema töö ülevaade

**A:** Vaata üle mõõtmisandmed, veebiliidese jõudlus või mehhaaniline disain 1. semestrist. Mis töötas? Mida on vaja parandada? Viita konkreetsetele numbritele oma varasemast laborist — mitte teooriale vaid sellele mida sa mõõtsid. Kasuta neid andmeid spetsifikatsioonivalikute põhjendamiseks.

**B ja C:** Kuna 1. semestri eelkäijat pole, tee selle asemel tehnoloogia uuring. Leia 3 sarnast projekti (GitHubi repod, Instructables, teadusartiklid, YouTube'i ehitused) ja analüüsi nende spetsifikatsioone vs. tegelikke tulemusi. Mida saad nende kogemusest õppida? Milliseid vigu sa väldid?

*Need on sinu esimesed analüüsid. Lisa rohkem kui avastad küsimusi spetsifikatsiooni kirjutamise käigus. Spetsifikatsioon mis ei tekita ühtegi küsimust on spetsifikatsioon mis ei vaadanud piisavalt sügavale.*

### Arenduslogi

### Tulemused

**Kaitsmiseks on vaja ainult git repositooriumi linki.**

Repositoorium peab sisaldama:

* **Projekti kirjeldus `.md` formaadis** — spetsifikatsioon, simulatsioonid, analüüsid ja seletused kuidas projekt läbi viia. Markdown on põhiformaat kogu dokumentatsiooni jaoks.
* **Tarkvarafailide arhiivid** — kui kasutasid tarkvara nagu Fusion 360, FlatCAM vms, siis esitamise versioon peab olema arhiivina (`.zip`, `.7z`) git'i üles laetud. Õppejõud peab saama testida just seda versiooni mida sa kaitsed.
* **Milestone iga verstaposti kohta** — loo GitHub/GitLab'is milestone iga järgmise verstaposti (2–5) jaoks. See on sinu arendusgraafik ja ülesannete jälgimine ühes kohas.
* **Esimese prototüübi ostunimekiri** — nimekiri komponentidest mida on vaja tellida või osta et ehitada verstaposti 2 tehnoloogia prototüüp. Iga komponendi kohta: nimetus, kogus, tarnija, hind ja tarneaeg. Eesmärk on et tellimused saab kohe pärast kaitsmist välja saata ja ei kaota aega.

| Väljund | Formaat |
| :--- | :--- |
| Spetsifikatsiooni dokument | `.md` — kõik sektsioonid ülalpool olevast "Mida spetsifikatsioon sisaldab" |
| Süsteemiarhitektuuri diagramm | draw.io (`.drawio` fail repos) — plokkskeem liidestega |
| Teostatavusanalüüsi notebook | Jupyter Lab (`.ipynb` fail repos) — kõik kolm analüüsi koos arvutustega |
| BOM tabel | `.md` või `.csv` — komponendid, kogused, ühikuhinnad, kokku ja tarnija lingid |
| Kontseptsioonimudelid | Fusion 360 (`.f3z` arhiiv repos) — mõõtmetega kontseptsiooni maketid |
| Arenduse ajakava | GitHub/GitLab milestones — verstapostide 2–5 jaoks |
| Esimese prototüübi ostunimekiri | `.md` või `.csv` — komponendid, kogused, tarnija, hind, tarneaeg |

Git repo link:

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

Füüsilise teostatavuse arvutus on korrektne ja asjakohane. Kulu-jõudluse kompromissi analüüs kasutab tegelikke numbreid. 1. semestri retrospektiiv (A) viitab tegelikele mõõdetud andmetele, või tehnoloogiauuring (B/C) viitab reaalsetele projektidele. Arvutused on reprodutseeritavad esitatud Jupyteri notebooks.

* 4 p: Kõik kolm analüüsi terviklikud korrektse metoodikaga
* 3 p: Kaks analüüsi terviklikud
* 2 p: Üks analüüs terviklik
* 1 p: Katse ilma ranguseta
* 0 p: Analüüs puudub

**Prototüüp / Füüsiline (4 punkti) — Kontseptsiooni elujõulisus**

Mehhaanilisel kontseptsioonil on realistlikud mõõtmed. Komponentide valikud on tegelikult ostetavad detailid koos andmelehtedega. Energiaeelarve läheb kokku (kogutarbimine vs. toitevõimsus). Vähemalt üks kriitiline mõõde on füüsiliselt kontrollitud (mõõdetud päris riistvaralt või andmelehelt). A jaoks: 1. semestri prototüübi fotod/mõõtmised lisatud viitena.

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

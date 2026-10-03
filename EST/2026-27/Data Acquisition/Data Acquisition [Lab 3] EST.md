## Andmehõive: Labor 3 — Tilk ja katkestus

**Töömaht:** 30 tundi | **Hindamine:** 20 punkti | **Meeskond:** 3 tudengit | **Välja antud:** 28.10.26 | **Tellimise kuupäev:** 06.11.26 | **Esimene kaitsmine:** 17.11.26, veebis

### Kuidas see dokument töötab

* Repo ja töökord on Laborist 1 olemas ja samad.
* Too sellest dokumendist oma projekti repo juurde see, mida vaja: selle labori kaust, `README.md`, kuhu lähevad su enda numbrid, otsused ja KAARDISTA ISE vastused, ja failid, mida kontrollnimekiri nimetab. Tervet dokumenti üle kopeerida ei ole vaja.
* Skeemid ja simulatsioonid lähevad dokumenti pildina, pildi juurde link elavale failile, et teine saaks selle lahti teha ja edasi muuta.

### Eesmärk

Seni tegi pump ühte tööd: imes, ja napp hoidis klaasi. Nüüd teeb sama pump teist tööd ka. Ta puhub süstlasse, ja süstla otsikust tuleb tilk liimi. Kumba tööd pump parajasti teeb, otsustab solenoidklapp, ja klappi juhib sinu Atom.

Liim on läbipaistev vaik, mis kõveneb 405 nm valguse käes. Tilk läheb Atomi ekraani peale, klaas tilga peale, ja UV LED kõvendab liimi läbi klaasi.

Sellest tuleb kaks küsimust, ja need on selle labori kaks poolt.

**Kui suur on tilk?** Tilga suurus on rõhk korda aeg korda otsiku ava — ja veel see, kui palju vaiku süstlas on, kui soe on ruum, ja kui pikk on voolik. Liiga väike tilk ei hoia klaasi kinni. Liiga suur pressitakse klaasi alt välja ja Atomi külgedele. Kui suur on paras, ei tea praegu keegi; see on number, mille sina mõõdad. Tulemus on **retsept**: otsik, rõhk, impulsi pikkus, kõvendamise aeg.

**Mis siis, kui midagi läheb valesti?** Kaks asja lähevad kindlasti.

* **Otsik kõveneb kinni.** Päevavalguses on piisavalt UV-d, ja lamp on sealsamas kõrval. Kinni otsikuga süstal on suletud anum, kuhu pump puhub. Liim ei tule, rõhk tuleb.
* **Süstal saab tühjaks.** Otsikust tuleb õhk, mitte liim, ja robot paneb klaasi kuiva Atomi peale.

Mõlemal juhul peab klapp kohe tagasi minema ja robot peab teada saama. "Kohe" ei tähenda siis, kui jaam järgmine kord küsib. Jaam on sülearvuti teisel pool USB kaablit ja tal on parajasti muud teha. Otsus tehakse seal, kus on andur, ja seda ei tee programmi põhitsükkel, vaid **katkestus**: riistvara ise ütleb protsessorile, et nüüd, ja protsessor jätab kõik muu pooleli.

Laboris 2 lubati, et rõhu **kalle** on Labori 3 töö. Siin see on. Poolikut haaret eristas korralikust see, kui kiiresti rõhk langeb. Kinnist otsikut eristab lahtisest see, kuidas rõhk tõuseb. Mõlemad on tuletis, ja tuletisel on üks ebameeldiv omadus, mille sa Fourier' abil ise ära näed: ta võimendab müra, ja seda rohkem, mida kõrgem on sagedus. Seepärast tuleb filter enne tuletist, mitte pärast.

Selles laboris on neli asja:

1. **Klapp ja impulss.** Atom lülitab klappi, impulsi pikkuse loeb riistvarataimer, ja ostsilloskoop ütleb, kui pikk impulss päriselt oli.
2. **Tilga suurus.** Eri pikkusega impulsid, eri suurusega tilgad, iga tilga rõhukõver. Sealt tuleb retsept.
3. **Filter ja tuletis.** Salvestatud kõverate peal: toores kalle, filtreeritud kalle, ja spekter, mis ütleb, miks üks neist on kasutu.
4. **Katkestus.** Komparaator Falstadis, siis plaadil. Kinnine otsik ja tühi süstal päriselt läbi proovitud, ja reageerimise aeg ostsilloskoobilt.

Esimesel päeval uusi osi ei ole. Ehita sellest, mis riiulil on, ja kirjuta puuduv tellimuseks, mis läheb välja 06.11.

*See on elav dokument. Uuenda eesmärke, kui need töö käigus muutuvad — uued teadmised teevad vanad eesmärgid vahel mõttetuks. Mõte on hoida meeskond kogu aeg sihil, et ei eksitaks detailide metsa ja põhiprobleem ei jääks lahendamata.*

**KAARDISTA ISE — eesmärk nii, nagu ta tegelikult välja tuli.**

### Kontrollnimekiri

**Peab olema tehtud**

- [ ] Klapp lülitab Atomi käsu peale. Vooluta on pump napa peal. Mõõdetud, mitte oletatud.
- [ ] Impulsi pikkust loeb riistvarataimer. Käsk ja ostsilloskoobilt mõõdetud pikkus kõrvuti viie pikkuse kohta.
- [ ] UV LED lülitab Atomi käsu peale ja kustub alati ise.
- [ ] Anduri koht voolikus valitud ja põhjendatud.
- [ ] Tilgad: vähemalt viis impulsi pikkust, kümme tilka igaühega, iga tilk mõõdetud ja iga tilga rõhukõver salvestatud. Fail `data/drops.csv`.
- [ ] Teine muutuja läbi proovitud: teine otsik või teine rõhk, kolme impulsi pikkusega.
- [ ] Retsept kirjas failis `docs/recipe.md`: otsik, rõhk, impulss, kõvendamise aeg, ja klaas selle tilga peal läbi proovitud.
- [ ] Toores ja filtreeritud kalle kõrvuti samal kõveral, spektrid kõrvuti. Filter valitud numbritega.
- [ ] Sama kalle Labori 2 pooliku haarde logil: kas "vaakum püsib" on nüüd otsus.
- [ ] Komparaator Falstadis: lülitub kinnise otsiku peale, ei lülitu tavalise tilga ega müra peale.
- [ ] Komparaator plaadil, katkestus Atomis: klapp tagasi, alarm lukus, sündmus välja.
- [ ] Reageerimise aeg ostsilloskoobilt, kümme korda, katkestusega ja ilma. Fail `docs/latency.csv`.
- [ ] Kinnine otsik kümme korda ja tühi süstal kümme korda: mitu korda tabas. Tavaline tilk kolmkümmend korda: mitu valehäiret.
- [ ] Tellimus 06.11 failis `docs/bom.md`.
- [ ] Repo ja arenduspäevik täidetud, tag `data-acquisition-lab3`.

**KAARDISTA ISE — kuupäevad ja sinu enda sammud.**

### Sisendid

* Laborist 1 ja 2: andur koos astmega, 100 Hz logija, CSV formaat, pumbajuhtimine ribaga (`pump_control.md`), pooliku haarde logid.
* Õppejõult: 3/2 solenoidklapp, MOSFET-moodul klapi lülitamiseks, vaik, süstlad ja otsikud kolmes suuruses, otsikukorgid, 405 nm LED draiveriga, 405 nm kaitseprillid, nitriilkindad, isopropanool. Üks otsik, mis on meelega kinni kõvendatud.
* Riiulilt: komparaator või LM358N teine pool, takistite ja kondensaatorite komplekt, ostsilloskoop, multimeeter, nihik.
* 3D printimise L3-st: tööriist, mis hoiab süstalt, ja süstla õhuühendus, mis peab rõhku. Kuni seda ei ole, on süstal statiivis laua peal.
* Nutikate Lahenduste L3-st: Atomi leht, kuhu klapi ja LED-i seaded ja testinupud lähevad.

### Vahendid

1. AtomS3, USB-C kaablid
2. Sinu andur ja aste Laborist 2
3. 3/2 solenoidklapp, MOSFET-moodul, kaitsediood
4. Süstlad, otsikud, otsikukorgid, 405 nm vaik
5. 405 nm LED draiveriga; kaitseprillid, nitriilkindad, isopropanool, paberrätikud
6. Komparaator (LM393) või LM358N, takistite ja kondensaatorite komplekt, maketeerimisplaat
7. Ostsilloskoop, kaks kanalit; multimeeter
8. Nihik; kaal 0,01 g, kui on
9. MG400 koos pumbakastiga
10. Arduino IDE või PlatformIO; Python 3, Jupyter Lab, numpy, pandas, scipy, matplotlib
11. Falstad; git

*Kui plaan muutub, uuenda ka vahendeid, või tee draw.io skeem, mis näitab, kuidas asjad omavahel töötavad.*

**KAARDISTA ISE — mida sa päriselt kasutasid.**

### Taustainfo

* **ESP32 katkestus**
  [https://www.youtube.com/watch?v=WVK2Wx386XE](https://www.youtube.com/watch?v=WVK2Wx386XE)
* **Schmitti triger** — komparaator, mis ei jää läve peal värisema
  [https://www.youtube.com/watch?v=Nrp8OgQLAlw](https://www.youtube.com/watch?v=Nrp8OgQLAlw)
* **Madalpääsfilter**
  [https://www.youtube.com/watch?v=OBM5T5_kgdI](https://www.youtube.com/watch?v=OBM5T5_kgdI)
* **Kõrgpääsfilter** — sama asi, mis tuletis, ainult teise nimega
  [https://www.youtube.com/watch?v=H30kRgI5bi0](https://www.youtube.com/watch?v=H30kRgI5bi0)
* **Mürahaldus**
  [https://www.youtube.com/watch?v=u40kX1DYKdA](https://www.youtube.com/watch?v=u40kX1DYKdA)
* **Kuidas op-amp töötab** — komparaator on sama kolmnurk ilma tagasisideta
  [https://www.youtube.com/watch?v=kbVqTMy8HMg](https://www.youtube.com/watch?v=kbVqTMy8HMg)
* **Solenoid, MOSFET ja kaitsediood**
  (link puudu — YouTube: "flyback diode solenoid MOSFET explained")
* **ESP32 riistvarataimer**
  (link puudu — YouTube: "ESP32 hardware timer interrupt")
* **Falstad**
  [https://www.falstad.com/circuit/circuitjs.html](https://www.falstad.com/circuit/circuitjs.html)

*Lisa siia oma allikaid ja kasulikku infot, mis aitaks sul projektist aru saada ka aastaid hiljem, kui selle uuesti lahti teed.*

**KAARDISTA ISE — sinu allikad.**

### Osad

#### 1. Klapp ja impulss

Klapp on mähis, ja mähis tahab rohkem voolu, kui Atomi viik annab, ja teist pinget. Vahele käib MOSFET-moodul. Loe klapi pealt, mis pinget ta tahab, enne kui midagi ühendad.

Mähisel on üks omadus, mis teeb elektroonika katki: kui vool välja lülitatakse, tekitab mähis hetkeks pinge, mis on mitu korda suurem kui toide. **Kaitsediood** mähise peal võtab selle enda peale. Vaata, kas su moodulil on ta olemas. Kui ei ole, pane. Ostsilloskoop näitab sulle seda tippu ilma dioodita ja dioodiga — tee see pilt, enne kui Atom samas ahelas on.

**Ohutu olek.** Klapp on vedruga: vooluta läheb ta tagasi ühte kindlasse asendisse. See asend peab olema napp, mitte süstal. Kontrolli seda päriselt: tõmba Atomilt USB välja, pane pump puhuma ja vaata, kas süstla harus on rõhku. Ei tohi olla. See on sama reegel, mis Laboris 1: kui midagi on valesti, ei juhtu midagi.

**Impulss.** Tilk on klapi lahtioleku aeg. Kui seda aega loeb programmi põhitsükkel, mis samal ajal joonistab ekraani ja saadab ridu, on impulss iga kord natuke erineva pikkusega, ja tilk ka. Impulsi pikkuse loeb **riistvarataimer**: sa ütled talle millisekundid, ta sulgeb klapi ise, ükskõik mida ülejäänud programm sel hetkel teeb. Mõõda ostsilloskoobiga klapi juhtsignaali: käsk oli 200 ms, kui pikk oli impulss? Viis pikkust, kümme korda igaüht. Keskmine ja kõikumine.

Ja üks asi, mida ostsilloskoop ei näe: klapp ise on mehaaniline ja tal kulub avanemiseks aega. Rõhukõver näitab seda. Kui kaua pärast käsku hakkab rõhk süstla harus tõusma? See on lühim impulss, millel on üldse mõtet.

**Kus andur istub.** Sul on üks andur. Ta võib istuda pumba ja klapi vahel: siis näeb ta mõlemat haru, aga kumbagi läbi klapi. Või süstla harus: siis näeb ta tilka teravalt ja nappa üldse mitte. Vali, ja ütle, millest sa loobusid.

**UV LED** saab sama kohtlemise: Atom lülitab ta draiveri kaudu sisse ja taimer lülitab välja. LED ei jää põlema sellepärast, et käsk "välja" ei jõudnud kohale.

```
arvuti → Atom:  {"cmd":"dispense","ms":200}    {"cmd":"uv","ms":5000}    {"cmd":"clear"}
Atom → arvuti:  {"ev":"dispense_start","t":123456}    {"ev":"dispense_end","t":123660}
```

Kirjuta üles: klapi pinge ja kuidas ta on ühendatud, skeem pildina; ostsilloskoobi pilt mähise pingest väljalülitamisel; mis rõhk on süstla harus, kui Atom on vooluta; impulsi pikkuse tabel, käsk ja mõõdetud; klapi avanemise viivitus rõhukõveralt; anduri koht ja põhjus.

#### 2. Tilga suurus

Kõigepealt see, mida sa hoiad paigal. Rõhk: Labori 1 riba hoiab pumpa kahe lülituspunkti vahel, ja see töötab ka puhumisel. Pane riba kitsaks ja kirjuta üles, mis rõhul sa doseerid. Otsik: alusta keskmisest. Süstal: täis, ja märgi, kui täis.

Siis muuda ühte asja: impulsi pikkust. Vähemalt viis pikkust, lühimast, mis üldse midagi välja annab, kuni sellise, mis on ilmselgelt liiga suur. Kümme tilka igaühega. Tilgad lähevad proovialusele — paberile, kilele või ohvriklaasile —, kõvendatakse lambiga ja mõõdetakse. Läbimõõt nihikuga. Kui sul on 0,01 g kaal, siis ka mass, sest läbimõõt sõltub sellest, kuidas tilk laiali vajub, mass mitte.

Iga tilga kohta salvestatakse ka rõhukõver, sama tilga numbriga. See ei ole paberitöö. Sa tahad teada, kas kõver ütleb tilga suuruse ette — kas platoo kõrgus või kõvera alune pindala käib tilga suurusega kaasas. Kui käib, saab iga tilka kontrollida ilma teda mõõtmata. Labor 5 ehitab selle peale.

Kolm asja, mida vaadata:

* **Kas sõltuvus on sirge?** Kaks korda pikem impulss, kas kaks korda suurem tilk? Kui ei ole, siis kust ta kõveraks läheb ja miks.
* **Kui palju sama impulss kõigub?** Kümme tilka sama käsuga ei ole kümme ühesugust tilka. Standardhälve jagatud keskmisega. See number ütleb, kui täpne su doseerimine on, ja ta on tähtsam kui keskmine.
* **Esimene tilk.** Kas esimene tilk pärast pausi on sama, mis kümnes? Kui ei ole, siis sellepärast on laual prügitops.

Siis muuda teist asja ja korda lühemalt: teine otsik või teine rõhk, kolm impulsi pikkust. Kumb mõjutab tilka rohkem, kas aeg või ava?

Ja lõpuks päris katse. Tilk Atomi mannekeeni peale, klaas peale, vaata läbi klaasi. Liim peab katma piisavalt, et hoida, ja ei tohi jõuda servani. Otsusta, milline tilk on paras. Kõvenda ja mõõda, kui kaua see võtab: millal klaas enam ei nihku.

Kirjuta üles: read failis `data/drops.csv` (tilga number, otsik, rõhk, impulss ms, läbimõõt mm, mass mg kui on, kõvera fail, märkus); graafik, tilga suurus impulsi pikkuse vastu, hajuvusega; kõikumine protsentides iga pikkuse kohta; kas kõvera platoo või pindala käib tilga suurusega kaasas; retsept failis `docs/recipe.md` — otsik, rõhk, impulss, kõvendamise aeg, ja foto klaasist selle tilga peal.

#### 3. Filter ja tuletis

See osa käib arvutis, kõverate peal, mis sul juba on.

Võta üks tilga kõver ja arvuta kalle kõige lihtsamal moel: `dP/dt = (P praegu − P eelmine) / 10 ms`. Joonista. See ei näe välja nagu kalle, vaid nagu müra, ja põhjus on arvutatav. Tuletis korrutab iga sageduse tema enda sagedusega: aeglane muutus, mida sa otsid, jääb väikeseks, ja kiire värin, mida sa ei otsi, kasvab suureks. Tee spekter signaalist ja spekter tuletisest ja pane kõrvuti. Suhe igal sagedusel on `2πf`. Labori 1 spektrist tead sa juba, millised tipud seal on; nüüd näed, milline neist tuletise ära rikub.

Seega filter enne. Proovi vähemalt kahte: libisev keskmine ja mediaan. Nad ei tee sama asja — keskmine määrib üksiku terava tipu laiali, mediaan viskab ta välja. Iga filtri kohta kaks numbrit: kui palju müra tuletises alles jäi, ja **kui palju filter hiljaks jääb**. Filter ei ole tasuta. Kümne punkti keskmine teab muutusest alles siis, kui see on juba pool oma akent vana. Katkestuse jaoks on see viivitus osa reageerimise ajast.

Vali üks. Põhjus on kaks numbrit kõrvuti, mitte "tundus sujuvam".

Siis tee sama asi, mille Labor 2 lubas. Võta pooliku haarde logid ja arvuta nende peal filtreeritud kalle pärast pumba väljalülitumist. Laboris 2 küsiti, mitu sekundit kulub, enne kui poolik haare on korralikust eristatav. Nüüd on küsimus: kas on olemas kalde lävi, mis eristab nad ära, ja kui kiiresti? See on otsus "vaakum püsib", ja robot tõstab selle peale.

Ja lõpuks see, mille pärast osa 4 olemas on. Pane kolm kõverat kõrvuti: tavaline tilk, kinnine otsik, tühi süstal. Mis neid eristab — tõusu kalle, platoo kõrgus, või see, kuidas rõhk pärast klapi sulgumist langeb? Seda ei tea ette keegi. Vaata oma andmeid ja vali tunnus, mille järgi katkestus lülitub.

Kirjuta üles: toores ja filtreeritud kalle samal kõveral; spektrid kõrvuti; iga filtri müra ja viivitus, ja kumma sa valisid; kalde lävi korraliku ja pooliku haarde vahel ja aeg otsuseni; kolm doseerimise kõverat kõrvuti ja tunnus, mis neid eristab, numbritega.

#### 4. Katkestus

Nüüd tehakse sama otsus riistvaras.

**Falstadis enne.** Komparaator võrdleb kahte pinget ja tema väljund on üks kahest: kõrge või madal. Ühes sisendis on sinu signaal — kas astme väljund ise või tema tuletis, olenevalt sellest, mille sa osas 3 valisid —, teises on lävi. Kolm sisendit, mida proovida: tavaline tilk, kinnine otsik, ja tavaline tilk, mille peal on müra. Komparaator peab lülituma teise peale ja mitte esimese ega kolmanda peale.

Kolmas on see, mis esimesel korral ei õnnestu. Kui signaal on täpselt läve juures, lülitab müra komparaatorit edasi-tagasi kümneid kordi. Lahendus on **hüsterees**: natuke väljundist tagasi sisendisse, nii et sisselülitamise lävi on kõrgemal kui väljalülitamise oma. See on Schmitti triger, ja see on sama mõte, mis Labori 1 pumbajuhtimise riba: kaks läve ühe asemel, et asi värisema ei jääks. Takistid tulevad Falstadist.

**Siis plaadil.** Komparaatori väljund läheb Atomi viiku, mis teeb katkestuse. Mõõda multimeetriga, et väljund ei lähe üle 3,3 V, enne kui ta Atomi külge läheb.

```
dispense: kui alarm on lukus → keeldu
          klapp süstlale → taimer loeb ms → klapp tagasi napale
katkestus: klapp kohe napale → alarm lukku → {"ev":"alarm","why":"clog"} välja
tühi süstal: kui rõhk ei jõua platoole ettenähtud aja sees → alarm lukku, "empty"
alarm püsib, kuni tuleb {"cmd":"clear"}
```

Katkestuse sees tehakse nii vähe kui võimalik: klapp kinni, lipp püsti. Kõik muu — ekraan, rida arvutile — tehakse hiljem, põhitsüklis. Alarm jääb lukku. Süsteem, mis pärast ummistust ise uuesti proovib, pumpab kinnisesse süstlasse teist korda.

**Mõõda, kui kiire see on.** Ostsilloskoobi üks kanal on rõhk, teine klapi juhtsignaal. Kinnine otsik peal. Aeg hetkest, mil rõhk ületab läve, hetkeni, mil klapp lahti lastakse. Kümme korda.

Siis ehita sama kaitse ilma katkestuseta: põhitsükkel loeb iga ringiga andurit ja võrdleb lävega. Mõõda sama aeg, kümme korda. Ja siis anna põhitsüklile tööd — joonista ekraanile, saada ridu — ja mõõda uuesti. Katkestuse number ei tohiks muutuda. Põhitsükli oma muutub. Kirjuta kõrvale ka see, kui kaua kummagi tööle saamine võttis: kiirem lahendus on tavaliselt ka see, mille kallal kauem istuti, ja mõlemad numbrid kuuluvad otsuse juurde.

**Ja lõpuks päris katse.** Kinnine otsik, kümme korda: mitu korda alarm tuli. Tühi süstal, kümme korda. Tavaline tilk retsepti järgi, kolmkümmend korda: mitu korda alarm tuli siis, kui ei oleks pidanud. Kaitse, mis annab valehäireid, lülitatakse välja kolmandal päeval, ja siis ei ole kaitset.

Kirjuta üles: Falstadi skeem pildina ja lingina, takistid, lävi ja hüstereesi laius; ostsilloskoobi pilt lävest ja klapist samal ekraanil; read failis `docs/latency.csv` (katse, viis, koormus, aeg ms), keskmine ja halvim katkestusega ja ilma; kümnest kinnisest otsikust tabatud, kümnest tühjast süstlast tabatud, kolmekümnest tavalisest tilgast valehäireid; arendusaeg kummagi lahenduse kohta; üks lause, kumma sa jätad ja miks.

**KAARDISTA ISE — vastused.** Iga osa kohta: numbrid, ühikud, kus fail on. Tegemata asja kohta üks rida, miks.

### Ohutus

* **405 nm valgus ja silmad.** LED-i ei vaadata. Kui LED on draiveri küljes, on kõigil laua ääres 405 nm kaitseprillid ees. Lamp on suunatud laua poole. LED kustub alati ise, taimeriga, ja vooluta on ta väljas.
* **Vaik.** Kõvenemata vaik ärritab nahka ja võib tekitada allergia, mis ei lähe üle. Nitriilkindad käes, kui süstal on lahti. Maha läinud vaik pühitakse isopropanooli ja paberiga, ja paber kõvendatakse lambi all enne prügikasti. Kõvenemata vaiku kraanikaussi ei valata.
* **Lampi ei suunata otsikule.** Kinni kõvenenud otsik on see viga, mida sa siin avastama õpid. Meelega tehakse neid üks, ja selle annab õppejõud.
* **Kinnine süstal on suletud anum rõhu all.** Ummistuskatse ajal on süstal hoidikus või statiivis, mitte käes. Enne kui süstla ära võtad, lase rõhk klapi kaudu välja. Kuni katkestus ei ole läbi proovitud, on iga ummistuskatse ajal inimese käsi pumba lüliti juures.
* **Otsikul on kork peal**, kui sa ei doseeri. Päevavalgus kõvendab liimi otsikus aeglaselt, aga kindlalt.
* **Mähis ja diood.** Klappi ei lülitata ilma kaitsedioodita. Klapi pinge ei ole Atomi pinge: MOSFET-mooduli kaks poolt ei saa kokku.
* **ADC viik ja katkestuse viik ei kannata 5 V.** Komparaatori väljund mõõdetakse multimeetriga üle, enne kui ta Atomi külge läheb.
* USB ja toide välja, enne kui juhet liigutad. Pumbakast on 24 V.
* Lahtine voolik +110 kPa juures lendab; ära suuna kellegi poole.
* Robot: käed ei ole laual, kui robot on sisse lülitatud. Tilku mõõdad sa esialgu laual, mitte roboti otsas.
* Selles laboris ei joodeta.

### Komponendid selle labori jaoks

Tellimus läheb välja 06.11.26 ja jõuab kohale enne kaitsmist. Valmis nimekirja ei ole: meeskond paneb tellimuse ise kokku faili `docs/bom.md`, iga rea juures üks lause, milline osa või number seda küsib.

Tellimine käib ühisest tellimistabelist: [https://moodle.ut.ee/mod/url/view.php?id=1535601](https://moodle.ut.ee/mod/url/view.php?id=1535601). Kanna oma read sinna enne tellimise kuupäeva; mida tabelis ei ole, seda ei tellita. Fail `docs/bom.md` jääb sinu reposse põhjenduseks, miks sa just neid asju küsisid.

Mõtle näiteks: kas su MOSFET-moodulil on kaitsediood peal või tuleb see eraldi; kas komparaatoriks on eraldi kiip mõistlikum kui LM358N teine pool, ja mida andmeleht tema väljundi kohta ütleb; kas hüstereesi takistid, mille Falstad andis, on komplektis olemas; kas otsikuid ja korke jätkub, kui iga kinni läinud otsik on kadunud otsik; kas vaiku on viiekümne tilga ja mõne ebaõnnestumise jaoks; ja millega sa tilka mõõdad, kui nihikust ei piisa.

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — Atomi püsivara taimeri, katkestuse ja alarmi lukuga, logija, `drops.csv` koos kõveratega, analüüsi märkmik | 5 p |
| Analüüs — impulss käsu ja mõõdetu kõrval, tilga suurus impulsi vastu hajuvusega, toores ja filtreeritud kalle spektritega, filtri viivitus, reageerimise aeg katkestusega ja ilma | 5 p |
| Prototüüp — klapp vooluta napa peal, tilk retsepti järgi hoiab klaasi ja ei jõua servani, kinnine otsik ja tühi süstal annavad alarmi, tavaline tilk ei anna | 5 p |
| Dokumentatsioon — README, arenduspäevik, `recipe.md`, `latency.csv`, Falstadi eksport, `pump_control.md` uuendatud, `bom.md`, AGENTS.md | 5 p |
| **Kokku** | **20 p** |

### Kaitsmine

Link git repole, tag `data-acquisition-lab3`.

Kaitsmine on lihtne suuline 15 minuti jutuajamine. Teed ühe tilga retsepti järgi ja näitad selle rõhukõverat. Paned peale kinnise otsiku ja näitad ostsilloskoobil, kuidas klapp lahti lastakse ja kui kiiresti. Näitad, et teine tilk ei tule enne, kui alarm on maha võetud. Avad oma arenduspäeviku. Õppejõud küsib umbes viis küsimust selle kohta, kuidas sa selle tegid. Kui esimesel korral ei õnnestu, tuled uuesti.

Repos on kaustas `data-acquisition/lab3/`: `src/` püsivara ja logijaga, `data/` kaustas `drops.csv` ja kõverad, `notebooks/` tilkade, kalde ja spektritega, `docs/` skeemi foto, ostsilloskoobi piltide, Falstadi ekspordi, `recipe.md`, `latency.csv`, uuendatud `pump_control.md` ja `bom.md`-ga, `README.md` selle labori kohta, ja `AGENTS.md` uuendatud.

### Arenduspäevik

**KAARDISTA ISE — päevik.** Üks sissekanne iga töösessiooni kohta, kirjutatud iseendale, nii et inimene, kes seal ei olnud, saab aru. Sissekandeid lisatakse, mitte ei muudeta.

Omadussõnad ei ole tulemused. "Tilgad olid ebaühtlased" ei ole midagi; "200 ms impulss, kümme tilka, 3,1 ± 0,4 mm" on sissekanne.

**PP.KK.AA — kes olid kohal**
* Tegime:
* Juhtus (numbrid):
* Otsustasime, ja miks:
* Lahti järgmiseks korraks:

### Väljundid ja tulemused

**Väljundid**
* Nutikad Lahendused L3: klapi ja LED-i käsud, mille seaded ja testinupud lähevad Atomi lehele; alarmi sündmus, mille peale jaam roboti peatab.
* 3D printimine L3: kui pikk tohib voolik klapi ja süstla vahel olla, ja kus andur istub.
* Andmehõive L4: retsept ja kõverad, mille peale ehitatakse sajad tsüklid; kolm märgistatud olukorda — tavaline, kinnine, tühi.

**KAARDISTA ISE, lõpus.**
* Git repo ja tag:
* Numbrid, mille see labor andis, ühikutega:
* Mida me teeksime teisiti:
* Mida järgmine labor peaks enne alustamist teadma:

### Tagasiside

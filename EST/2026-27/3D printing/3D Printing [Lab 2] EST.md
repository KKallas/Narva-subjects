## 3D printimine ja CAD: Labor 2 — Kinnitus, mis tuleb samasse kohta tagasi

**Töömaht:** 30 tundi | **Hindamine:** 20 punkti | **Meeskond:** 3 tudengit | **Välja antud:** 06.10.26 | **Tellimise kuupäev:** 16.10.26 | **Esimene kaitsmine:** 27.10.26, veebis

### Kuidas see dokument töötab

* Repo ja töökord on Laborist 1 olemas ja samad.
* Too sellest dokumendist oma projekti repo juurde see, mida vaja: selle labori kaust, `README.md`, kuhu lähevad su enda numbrid, otsused ja KAARDISTA ISE vastused, ja failid, mida kontrollnimekiri nimetab. Tervet dokumenti üle kopeerida ei ole vaja.

### Eesmärk

Töölaua annab õppejõud, ja ta ei ole plaat. Ta on 16 mm alumiiniumvardad, 120 mm sammuga. Üks varras jookseb roboti käe keskelt, kaks käivad robotist mõlemalt poolt mööda. Vardal ei ole auke, kuhu midagi kinnitada — sinu kinnitus haarab varda ümbert kinni. Ja kuna üks varras ei hoia midagi paigal, ulatub iga kinnitus **kahe või kolme varda peale korraga**.

Aasta lõpuks paneb MG400 kokku sildi: AtomS3, mille ekraani peale on liimitud polükarbonaatklaas. Selleks peavad klaas ja Atom olema kohas, mille robot teab. Ja seda kohta ei õpetata iga kord uuesti: kinnitus tuleb varraste pealt maha ja läheb tagasi, ning detail on ikka samas kohas. See labor teeb selle kinnituse.

Laboris 1 mõõtsid sa ära, mis lõtk sellel printeril päriselt on, ja kust su plast paindub ja kust murdub. Nüüd lähevad need numbrid käiku: klambri ava on see lõtk, ja iga vedrutav osa on see paindumine.

Selles laboris on kolm asja:

1. **Kinnitus.** Kuidas asi varraste külge käib ja mis teda seal paigal hoiab.
2. **Pesad.** Klaasile, Atomile, valmis sildile. Robot paneb sisse, inimene saab välja.
3. **Korduvtäpsus.** Võta maha, pane tagasi, kas õpetatud punkt kehtib veel. Kümme korda.

Esimesel päeval uusi osi ei ole. Ehita sellest, mis riiulil on, ja kirjuta puuduv tellimuseks, mis läheb välja 16.10.

*See on elav dokument. Uuenda eesmärke, kui need töö käigus muutuvad — uued teadmised teevad vanad eesmärgid vahel mõttetuks. Mõte on hoida meeskond kogu aeg sihil, et ei eksitaks detailide metsa ja põhiprobleem ei jääks lahendamata.*

**KAARDISTA ISE — eesmärk nii, nagu ta tegelikult välja tuli.**

### Kontrollnimekiri

**Peab olema tehtud**

- [ ] Vardad mõõdetud: läbimõõt mitmest kohast, varraste vahe, kõrguste vahe. Fusionis parameetritena.
- [ ] Klamber valmis. Kolm tükki prinditud ja omavahel vahetatavad.
- [ ] Kinnitus ulatub kahe või kolme varda peale ja ei liigu ühessegi suunda. Ka mitte piki varrast.
- [ ] Pesad valmis: klaas, AtomS3, valmis silt. Robot paneb klaasi pessa, inimene saab selle sõrmedega välja.
- [ ] Korduvtäpsuse test tehtud: kümme maha-tagasi tsüklit, tulemus failis `docs/refit_test.csv`.
- [ ] Tellimus 16.10: mis selle labori jaoks puudu jäi, failis `docs/bom.md`.
- [ ] Repo ja arenduspäevik täidetud, tag `3d-print-lab2`.

**KAARDISTA ISE — kuupäevad ja sinu enda sammud.**

### Sisendid

* Õppejõult: töölaud — 16 mm alumiiniumvardad 120 mm sammuga, üks käe keskelt, kaks robotist mööda. MG400 negatiivse püramiidaluse peal.
* Riiulilt: printerid, PLA, PETG, nihik, poldid ja mutrid, M3 kuumsisestused.
* 3D printimise L1-st: lõtk, paindumise ja murdumise numbrid, pastakahoidik.
* Nutikate Lahenduste L1-st: jaam, millega punkte õpetada ja üle mängida, ja `data/positions.json`.
* Andmehõive L1-st: iminapp ja pumba juhtimine käsurealt — sellega käib klaasi tõstmise test.

### Vahendid

1. Fusion 360, hariduslitsents
2. PrusaSlicer, labori printerid, PLA ja PETG
3. Nihik, 300 mm joonlaud
4. Poldid, mutrid ja M3 kuumsisestused klambrite jaoks, jootekolb sisestusotsikuga
5. MG400 koos baaspaketi, pumbakasti ja iminapaga
6. Polükarbonaatklaasid 24 × 24 × 2 mm; AtomS3 või prinditud mannekeen 24 × 24 × 13 mm
7. 16 mm varda jupp töölaual proovimiseks, kui saada on
8. Git, üks repo meeskonna kohta, `AGENTS.md` juurkaustas

*Kui plaan muutub, uuenda ka vahendeid, või tee draw.io skeem, mis näitab, kuidas asjad omavahel töötavad.*

**KAARDISTA ISE — mida sa päriselt kasutasid.**

### Taustainfo

* **Fusion 360 mudeldamine FDM printimise jaoks**
  [https://www.youtube.com/watch?v=5hComh1hFzY](https://www.youtube.com/watch?v=5hComh1hFzY)
* **Parameetrid Fusionis.** Varda läbimõõt, varraste samm ja lõtk ei ole numbrid, mille sa mudelisse trükid. Need on parameetrid, millele mudel viitab. Kui printer järgmisel korral teisiti prindib, muudad ühte numbrit, mitte kahtkümmend.
* **Lõhikklamber.** Ümar varras, ava ümber varda, lõhik ühest küljest ja polt üle lõhiku. Polti pingutades ava tõmbub kokku ja haarab. Kogu selle labori kinnitus võib olla see üks tükk, korrutatuna kolmega.
* **Prinditavad vedrud ja liigendid**
  [https://www.youtube.com/watch?v=wpriGP45Unw](https://www.youtube.com/watch?v=wpriGP45Unw)
  [https://www.youtube.com/watch?v=fYDJLdOV_zE](https://www.youtube.com/watch?v=fYDJLdOV_zE)
* **3D mudelite harjutused**
  [https://www.tootalltoby.com/](https://www.tootalltoby.com/)
* **PrusaSlicer**
  [https://www.prusa3d.com/page/prusaslicer_424/](https://www.prusa3d.com/page/prusaslicer_424/)
* **MG400 flants**
  [https://a360.co/4nruicX](https://a360.co/4nruicX)

*Lisa siia oma allikaid ja kasulikku infot, mis aitaks sul projektist aru saada ka aastaid hiljem, kui selle uuesti lahti teed.*

**KAARDISTA ISE — sinu allikad.**

### Osad

#### 1. Kinnitus

Kõigepealt mõõda vardad. Läbimõõt kolmest kohast ühe varda pikkuses ja siis kolmest erinevast vardast — 16 mm varras ei ole igal pool 16,00 mm ja sinu klamber peab mahtuma ka kõige jämedama otsa peale. Varraste vahe nii, et mõõdad kahe vahe üle ja jagad kahega. Ja kontrolli, kas vardad on sama kõrgel; kui ei ole, siis kui palju. Need numbrid lähevad Fusionisse parameetritena.

Siis mõtle läbi, mida klamber ümarvarda peal päriselt kinni hoiab. Tee seda enne, kui midagi joonistad, sest vastus ei ole see, mida sa esimesena arvad.

Üks klamber ühe varda ümber ei lase kinnitusel külgsuunas liikuda ega kalduda. Kaks asja jäävad vabaks: ta **libiseb piki varrast** ja ta **pöörleb varda ümber**. Võta pliiats ja sõrmus ning proovi järele — mõlemat näed kahe sekundiga.

Lisa teine varras, ja pöörlemine kaob: kaks klambrit 120 mm vahega ei saa mõlemad ümber oma varda pöörelda. Aga libisemine jääb, sest mõlemad vardad on ühesuunas.

**Libisemine piki varrast on see üks asi, mis sul üle jääb, ja ta ei kao iseenesest.** Kaks vastust:

* **Hõõrdumine.** Polt kinni ja lootus. Töötab, aga sõltub sellest, kui tugevasti eelmine inimene keeras. Homme on ta mujal.
* **Positiivne tõke.** Midagi, mis puutub vastu varda otsa, vastu teist klambrit, või tihvt läbi varda ristiaugu. See tuleb tagasi samasse kohta ka siis, kui keeraja on väsinud.

Vali, ja kirjuta üles, miks. Korduvtäpsuse test osas 3 vastab sulle nagunii.

Siis ava mõõt. Lõhikklambri puhul on see üks kord, kus sa ava **meelega alamõõduliseks** teed: polt tõmbab ava kokku ja ava ülesanne on haarata, mitte lasta libiseda. Labori 1 lõtk ütleb sulle, kui palju prinditud ava nagunii väiksem tuleb — see number on siin sisendiks, mitte vastuseks. Teine tee on pealeklõpsatav klamber, ja tema elab Labori 1 paindumise numbrite peal, mitte lõtku peal. Kaks teed, kaks erinevat Labori 1 numbrit. Ütle, kumma sa võtsid.

Ja siis suurus, sest see otsustatakse enne joonistamist, mitte pärast. Kaks varrast on 120 mm vahe, kolm varrast 240 mm. Mõõda oma printeri lauda enne, kui kolme varda kasuks otsustad: 240 mm pluss klambrid ei pruugi lauale tasapinnaliselt ära mahtuda. Kui ei mahu, on kolm päris vastust — prindi diagonaali peale, prindi kahes tükis ja ühenda, või jää kahe varda juurde. Neljas vastus, mis on mõõtmata jätmine ja lootmine, ei ole vastus.

Prindi kolm ühesugust klambrit. Pane sama pesa kordamööda nende otsa ja lase robotil tõsta. Kui kolm klambrit ei ole omavahel vahetatavad, ei ole ka pesa oma kohal.

Kirjuta üles: varraste läbimõõt kolmest kohast ja kolmest vardast, varraste vahe, kõrguste vahe; mis jääb vabaks ühe varda peal ja mis kahe varda peal; kuidas sa libisemise piki varrast ära võtad ja miks nii; ava mõõt ja kumma Labori 1 numbri pealt see tuli; kaks või kolm varrast ja miks; kas see mahtus printeri lauale ja mida sa tegid, kui ei mahtunud; kas kolm klambrit on omavahel vahetatavad.

#### 2. Pesad

Klaas on 24 × 24 × 2 mm polükarbonaat. AtomS3 on 24 × 24 × 13 mm. Pesa lõtk tuleb Labori 1 kuubist — kirjuta üles, millise numbri sa võtsid ja miks just selle.

Igal pesal on kolm nõuet, ja need kolm on põhjus, miks pesa ei ole lihtsalt auk:

* **Sissejuhtiv kaldserv.** Robot ei pane detaili täpselt keskele. Kaldserv parandab paari kümnendiku vea ise ära; ilma selleta jääb detail serva peale seisma.
* **Kätte saamine.** Kaks millimeetrit paks klaas siledas pesas on sõrmedega võimatu välja võtta. Väljalükkeauk põhjas, väljalõige servas või pesa madalamaks — sinu valik, aga see peab olemas olema. Proovi ise järele, enne kui otsustad, et küll saab.
* **Peale midagi ei ulatu.** Iminapp tuleb otse alla. Kõik, mis detailist kõrgemale jääb, on tee peal.

Atomi pesa käib ekraan ülespoole. Ekraan jääb vabaks, USB-C ja nupp peavad ligipääsetavaks jääma.

Ja üks asi, mida plaadi peal ei oleks: **varraste vahel on tühjus.** Mis pesast välja kukub, kukub põrandale. Kui su paigutus lubab klaasil üle serva minna, on sul kas äär või kandik all.

Kui palju pesi, on sinu otsus, aga vähemalt: koht, kust klaasid tulevad, koht, kus Atom on, ja koht, kuhu valmis silt läheb. Joonista paigutus paberile enne, kui Fusioni avad, ja mõtle roboti tee läbi — kaks pesa, mille vahel käsi risti üle kolmanda käib, ei ole hea paigutus.

Kirjuta üles: kasutatud lõtk ja Labori 1 number, mille pealt see tuli; iga pesa mõõdetud nihikuga, nominaal kõrval; mis läks esimese prindi juures valesti ja mis selle parandas; foto kinnitustest ja pesadest varraste peal ülevalt, joonlaud kaadris.

#### 3. Korduvtäpsus

Enne, kui sa oma kinnitust testima hakkad, vaata ära, kuidas robot selle sama probleemi juba lahendatud on. Tasub vaadata, sest see on sama ülesanne, tehtud rauast.

MG400 istub **negatiivse püramiidaluse** peal: punktid püramiidikujulistes pesades. Sinna on täpselt üks viis istuda, ja seetõttu tuleb roboti asend varraste suhtes iseenesest tagasi — mitte tarkvarast, vaid geomeetriast. Ja alla on käinud lüliti: kui robot millegi vastu läheb, tuleb ta oma pesadest välja, lüliti vabaneb ja kõik jääb seisma. Sa paned ta pesadesse tagasi, teed reseti, ja õpetatud punktid kehtivad edasi. Kukkumine ei lõhkunud midagi ja ei nihutanud midagi.

Sinu kinnitusel seda ei ole. Selle labori küsimus on, kas sa suudad talle midagi samaväärset anda.

Test: õpeta jaamaga klaasi võtmise punkt. Siis võta kinnitus varraste pealt maha, pane tagasi, lase robotil võtta. Kümme korda järjest, sama punkt, punkti vahepeal ei muudeta.

Kui mõni kord ei õnnestu, on see kõige kasulikum rida terves tabelis. Kirjuta üles, mis juhtus: kas nap võttis servast, kas klaas jäi kaldserva peale, kas kinnitus nihkus piki varrast. See viimane on kõige tõenäolisem ja see ütleb sulle, et osas 1 valisid sa hõõrdumise, mitte tõkke.

Siis teine küsimus: kas sama õpetatud punkt töötab ka teise, samast failist prinditud pesaga? Kui töötab, on sul standard. Kui ei tööta, on sul üks pesa — ja kirjuta üles, kui palju need kaks erinesid.

Kirjuta üles: kümme rida failis `docs/refit_test.csv` (tsükli number, kas võttis, kas pani, märkus); mitu korda kümnest õnnestus; kui palju detail nihkus, kui sa seda nihikuga või kaameraga mõõta saad; kas teine prinditud pesa töötas sama punktiga. See viimane number ütleb, kui palju lõtku järgmised laborid peavad taluma — kirjuta ta eraldi välja.

**KAARDISTA ISE — vastused.** Iga osa kohta: numbrid, ühikud, kus fail on. Tegemata asja kohta üks rida, miks.

### Ohutus

* **Roboti all olev lüliti on ohutusseade.** Roboti aluse alla ei kiilu midagi, aluse külge ei kinnitata midagi ja alust ei hoita kinni. Kui robot ei saa oma pesadest välja tulla, ei saa ka lüliti tööd teha. Kui su kinnitus ulatub roboti aluse alla või vastu, disainid sa ohutusseadme välja.
* Kinnitus, mis saab piki varrast libiseda, libiseb, ja robot leiab ta üles. Kontrolli klambrid üle enne iga jooksu.
* Klambrid keeratakse kinni siis, kui robot on keelatud. Käsi ei ole klambri peal, kui robot on lubatud.
* Robot: käed ei ole laua kohal, kui robot on sisse lülitatud. Esimene jooks aeglaselt, hädastopp käeulatuses.
* Uue kinnituse esimene tõstmine käib 20 % kiirusel ja iminapp jääb 20 mm kõrgemale, õhku.
* Printeri otsik on 200–230 °C. Detailid spaatliga, kui laud on jahtunud.
* Kuumsisestused: kolb on 200 °C või kuumem. Tööta lauakattel.
* Küljelõikurid lõikavad näost eemale.

### Komponendid selle labori jaoks

Tellimus läheb välja 16.10.26 ja jõuab kohale enne kaitsmist. Valmis nimekirja ei ole: meeskond paneb tellimuse ise kokku faili `docs/bom.md`, iga rea juures üks lause, milline osa seda küsib.

Mõtle näiteks: milline polt su lõhikklambrisse käib ja kas neid on selles pikkuses; kas mutter või kuumsisestus — ja mida sa kummagagi võidad; kas PETG on otsas; kas 16 mm varda jupp oleks abiks, et klambrit laua taga proovida, selle asemel et iga proovi jaoks töölaud kinni panna; ja kas klaase on piisavalt, sest vähemalt üks läheb selle labori jooksul katki.

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — parameetritega klamber ja pesad, STL ja 3MF iga prindi kohta | 5 p |
| Analüüs — varraste mõõdud, mis jääb vabaks ja mis selle ära võtab, kasutatud lõtk ja kust see tuli, korduvtäpsuse tabel | 5 p |
| Prototüüp — kinnitus kahe või kolme varda peal ei liigu ja tuleb samasse kohta tagasi, robot võtab klaasi pesast, inimene saab selle välja | 5 p |
| Dokumentatsioon — README, arenduspäevik, `refit_test.csv`, `bom.md`, AGENTS.md | 5 p |
| **Kokku** | **20 p** |

### Kaitsmine

Link git repole, tag `3d-print-lab2`.

Kaitsmine on lihtne suuline 15 minuti jutuajamine. Võtad kinnituse varraste pealt maha ja paned tagasi, ja robot võtab klaasi ikka õigest kohast, ilma et sa punkti uuesti õpetaksid. Avad oma arenduspäeviku. Õppejõud küsib umbes viis küsimust selle kohta, kuidas sa selle tegid. Kui esimesel korral ei õnnestu, tuled uuesti.

Repos on kaustas `3d-print/lab2/`: lähtefailid, STL ja `.3mf` iga prindi kohta, `docs/` kaustas `refit_test.csv`, `bom.md` ja fotod, `README.md` selle labori kohta, ja `AGENTS.md` uuendatud.

### Arenduspäevik

**KAARDISTA ISE — päevik.** Üks sissekanne iga töösessiooni kohta, kirjutatud iseendale, nii et inimene, kes seal ei olnud, saab aru. Sissekandeid lisatakse, mitte ei muudeta.

**PP.KK.AA — kes olid kohal**
* Tegime:
* Juhtus (numbrid):
* Otsustasime, ja miks:
* Lahti järgmiseks korraks:

### Väljundid ja tulemused

**Väljundid**
* Andmehõive L2: klaas kindlas kohas, et rõhukõverat saaks päris tõstmise pealt mõõta.
* Nutikad Lahendused L2: laud, mida kaamera näeb, ja kinnitus, mille asukoht on teada.
* 3D printimine L3: klambri standard, mille peale järgmised moodulid käivad, ja korduvtäpsuse number.

**KAARDISTA ISE, lõpus.**
* Git repo ja tag:
* Numbrid, mille see labor andis, ühikutega:
* Mida me teeksime teisiti:
* Mida järgmine labor peaks enne alustamist teadma:

### Tagasiside

## Andmehõive: Labor 4 — Masin, mis mõõdab ise

**Töömaht:** 30 tundi | **Hindamine:** 20 punkti | **Meeskond:** 3 tudengit | **Välja antud:** 18.11.26 | **Tellimise kuupäev:** 27.11.26 | **Esimene kaitsmine:** 10.12.26, veebis

### Kuidas see dokument töötab

* Repo ja töökord on Laborist 1 olemas ja samad.
* Too sellest dokumendist oma projekti repo juurde see, mida vaja: selle labori kaust, `README.md`, kuhu lähevad su enda numbrid, otsused ja KAARDISTA ISE vastused, ja failid, mida kontrollnimekiri nimetab. Tervet dokumenti üle kopeerida ei ole vaja.
* Skeemid ja simulatsioonid lähevad dokumenti pildina, pildi juurde link elavale failile, et teine saaks selle lahti teha ja edasi muuta.

### Eesmärk

Laboris 3 tegi robot tilga, kaamera pildistas, ja sina lugesid pildid arvutis läbi. Sealt tuli retsept: otsik, rõhk, impulss, kõvendamise aeg. Retsept on üks punkt. Liin, mis teeb sadu silte, ei saa iga tilka inimesega üle vaadata, ja süstal ei ole sajandal tilgal sama, mis esimesel: vaiku jääb vähemaks, ruum läheb soojemaks, otsik määrdub.

Selles laboris teeb masin kolm asja ise.

* **Mõõdab.** Laboris 3 luges programm laigud pildilt kokku ja sina vaatasid iga pildi peal üle, kas tema piirjooned olid õiges kohas. Nüüd jookseb sama programm iga tsükli järel ise, ja keegi ei vaata. Kas talle saab usaldada, ütleb kaks asja: Labori 3 üle vaadatud pildid ja kaal.
* **Ennustab ja parandab.** Andmetest sobitatud **mudel** ütleb ette, kui pikk impulss annab sihtsuuruses tilga. Ja kui tilk tuli ikka liiga väike, on järgmine impulss natuke pikem: see on **tagasiside**, mõõtmine läheb otse doseerimisse, ja tilk püsib sihis ka siis, kui süstal tühjeneb.
* **Kirjutab üles.** Iga tsükkel jätab ühe kirje: seaded, rõhukõver, pilt, mõõdetud tilk, ja mis päriselt juhtus. Sadu kirjeid, ja igaühel on teada, kas see oli tavaline tilk, kinnine otsik või tühi süstal. Labor 5 õpetab nende peal masinat ära tundma, mis juhtus, ilma pilti vaatamata.

Ja relee läheb välja. Laboris 3 mõõtsid sa tema piirid: viivitus, põrge, kontakti eluiga, ja et kiireks lülitamiseks ta ei sobi. Nüüd tuleb tema asemele **MOSFET**, ja samad numbrid mõõdetakse uuesti tema peal.

Kirje kuju on ühine Nutikate Lahenduste Labor 4 andmebaasiga. Lepi nendega kokku enne, kui esimene kirje kirjutatakse.

Selles laboris on viis asja:

1. **MOSFET.** Relee asemele, samad mõõtmised, numbrid relee omade kõrval.
2. **Tsükkel ja kirje.** Üks tsükkel, üks kirje, ühes kokkulepitud kujus.
3. **Masin mõõdab.** Programm loeb tilga pildilt ise, keegi ei vaata üle, ja kaal kinnitab, et ta ei eksi.
4. **Mudel ja tagasiside.** Mudel pakub impulsi ette, tagasiside parandab järele, ja tilk jääb sihtsuurusesse ka siis, kui süstal tühjeneb.
5. **Andmestik.** Sadu tsükleid, iga kirje märgistatud, valmis Labori 5 jaoks.

Esimesel päeval uusi osi ei ole. Ehita sellest, mis riiulil on, ja kirjuta puuduv tellimuseks, mis läheb välja 27.11.

*See on elav dokument. Uuenda eesmärke, kui need töö käigus muutuvad — uued teadmised teevad vanad eesmärgid vahel mõttetuks. Mõte on hoida meeskond kogu aeg sihil, et ei eksitaks detailide metsa ja põhiprobleem ei jääks lahendamata.*

**KAARDISTA ISE — eesmärk nii, nagu ta tegelikult välja tuli.**

### Kontrollnimekiri

**Peab olema tehtud**

- [ ] MOSFET lülitab klappi relee asemel. Kaitsediood on peal. Vooluta on süstal endiselt õhu peal.
- [ ] Lülitamise aeg, lühim tilk ja mähise vool mõõdetud MOSFET-iga, numbrid Labori 3 relee omade kõrval.
- [ ] Kirje kuju kokku lepitud Nutikate Lahendustega ja kirjas failis `docs/record.md`.
- [ ] Üks tsükkel algusest lõpuni ilma inimeseta: tilk plaadile, pilt, mõõtmine, kirje.
- [ ] Programm mõõdab tilga pildilt ise, ilma et keegi üle vaataks. Kontrollitud kahel moel: Labori 3 üle vaadatud pildid annavad samad numbrid, ja tilgaplaadi kaal on programmi ruumalaga nõus. Erinevus protsentides.
- [ ] Mudel sobitatud: tilga pindala impulsi, rõhu ja otsiku järgi, vähemalt kaks kuju proovitud, viga kontrolli andmetel protsentides, süstla täidetus proovitud tunnusena.
- [ ] Tagasiside: sihtsuurus seatud, impulss muutub mõõtmise järgi, ülempiiriga.
- [ ] Kolm moodi kõrvuti, sada tilka igaüks: ainult retsept, ainult tagasiside, mudel ja tagasiside. Tilkade arv sihini pärast süstla vahetust.
- [ ] Vähemalt 300 tsüklit kirjas, igal kirjel märge: tavaline, kinnine või tühi. Süstal kaalutud iga 25 tsükli järel.
- [ ] Andmestik failides `data/cycles.csv`, `data/curves/`, `data/images/`, ja Nutikate Lahenduste andmebaasis.
- [ ] Tellimus 27.11 failis `docs/bom.md`.
- [ ] Repo ja arenduspäevik täidetud, tag `data-acquisition-lab4`.

**KAARDISTA ISE — kuupäevad ja sinu enda sammud.**

### Sisendid

* Laborist 3: retsept (`recipe.md`), `drops.csv`, `placement.csv`, rõhukõverad, tilgaplaadi ja vahetükkide mudel, mõõtmise programm, relee numbrid, katkestus ja alarm.
* 3D printimise L3-st: tööriist süstla, lambi ja kaameraga, kolm nihet failis `tool_offsets.md`, prügitops ja otsiku parkimiskoht.
* 3D printimise L4-st: kui detail laual vahetub, kuupäev — kirjed enne ja pärast ei pruugi olla võrreldavad.
* Nutikate Lahenduste L4-st: ühine andmebaas, kirje kuju ja töövoo salvestaja, millega robot tsükleid kordab.
* Õppejõult: MOSFET IRLZ34N, vaiguga täidetud süstlad, kaal 0,01 g.

### Vahendid

1. MG400 koos pumbakasti, napi, klapi ja tööriistaga
2. AtomS3, andur ja op-amp, komparaator ja katkestus Laborist 3
3. IRLZ34N, kaitsediood, takistid, maketeerimisplaat
4. Ostsilloskoop, kaks kanalit; multimeeter
5. Tööriista kaamera, tilgaplaadid, vahetükid, viis polükarbonaatklaasi ringluseks
6. Vaiguga täidetud süstlad, otsikud, otsikukorgid, kaitseprillid 405 nm jaoks, nitriilkindad, isopropanool
7. Kaal 0,01 g
8. Python 3, Jupyter Lab, numpy, pandas, scipy, matplotlib; git

*Kui plaan muutub, uuenda ka vahendeid, või tee draw.io skeem, mis näitab, kuidas asjad omavahel töötavad.*

**KAARDISTA ISE — mida sa päriselt kasutasid.**

### Taustainfo

* **MOSFET lülitina** — miks ta kütab vähem ja lülitab kiiremini kui relee
  [https://www.youtube.com/watch?v=XiOcxyyTxy4](https://www.youtube.com/watch?v=XiOcxyyTxy4)
* **Loogikatasemega MOSFET** — miks 3,3 V viik ei ava iga MOSFET-i
  [https://www.youtube.com/watch?v=GrvvkYTW_0k](https://www.youtube.com/watch?v=GrvvkYTW_0k)
* **PWM ja mähise hoidevool**
  [https://www.youtube.com/watch?v=KymiLQwKpMY](https://www.youtube.com/watch?v=KymiLQwKpMY)
* **Lineaarne regressioon ja vähimruutude meetod**
  [https://www.youtube.com/watch?v=PaFPbb66DxQ](https://www.youtube.com/watch?v=PaFPbb66DxQ)
* **Õppe- ja kontrolliandmed** — miks mudelit ei kontrollita samadel andmetel, millega ta sobitati
  [https://www.youtube.com/watch?v=_vdMKioCXqQ](https://www.youtube.com/watch?v=_vdMKioCXqQ)
* **Tagasiside ja P-regulaator**
  [https://www.youtube.com/watch?v=E0rdLQLMZdA](https://www.youtube.com/watch?v=E0rdLQLMZdA)
* **Katseplaneerimine ja juhuslik järjekord**
  [https://www.youtube.com/watch?v=rbW9rs7rFis](https://www.youtube.com/watch?v=rbW9rs7rFis)

*Lisa siia oma allikaid ja kasulikku infot, mis aitaks sul projektist aru saada ka aastaid hiljem, kui selle uuesti lahti teed.*

**KAARDISTA ISE — sinu allikad.**

### Osad

#### 1. MOSFET

Laboris 3 käis klappi lülitama relee: mehaaniline kontakt, mis põrkab, kulub ja ei jõua kiiresti. Nüüd tuleb tema asemele IRLZ34N. Ta on lüliti, millel ei ole liikuvaid osi: Atomi viik paneb tema paisule pinge, ja ta laseb voolu läbi.

Kolm asja peavad paigas olema. **Paisu takisti** viigu ja paisu vahel piirab voolu, mis paisu laadimisel tekib. **Allatõmbetakisti** paisult maasse hoiab MOSFET-i kinni, kui Atom on vooluta või alles käivitub — muidu jääb pais hõljuma ja klapp võib ise lahti minna. **Kaitsediood** jääb klapi mähise peale samamoodi nagu Laboris 3, sest mähis teeb väljalülitamisel sama pingetipu, ükskõik mis teda lülitab. Ilma dioodita ei ela MOSFET seda kaua üle.

IRLZ34N on loogikatasemega: ta avaneb juba madala paisupingega. Aga 3,3 V on tema jaoks ikka piiri lähedal. Mõõda, kui palju pinget jääb MOSFET-i peale, kui klapp on voolu all, ja kui soojaks ta läheb. Kui pinge on suur, ei ole ta täiesti lahti.

Siis samad mõõtmised, mis relee peal. Ostsilloskoobi üks kanal Atomi viigul, teine klapi mähisel. Kui palju aega kulub käsust mähiseni, sisse ja välja? Kas serv põrkab? Mis on nüüd lühim tilk, mida süsteem teha saab — ja kes on nüüd aeglasem, lüliti või klapp ise? Ja üks asi, mida relee ei osanud: **PWM**. Klapp vajab avanemiseks täisvoolu, aga lahti hoidmiseks vähem. Pane pärast avanemist PWM peale ja mõõda, kui palju mähise vool langeb ja kui palju vähem ta soojeneb, ilma et klapp kinni kukuks.

Kirjuta üles: skeem pildina, takistite väärtused ja miks; pinge MOSFET-i peal ja tema temperatuur; lülitamise ajad ja lühim tilk relee numbrite kõrval; PWM-i sagedus ja täitetegur, mähise vool ja temperatuur täisvoolu ja PWM-iga.

#### 2. Tsükkel ja kirje

Üks tsükkel on üks kord kõike, mida liin teeb: tilk, mõõtmine, ja klaas edasi. Liimi selles laboris klaasi alla ei panda. Tilgad lähevad tilgaplaadile, ja klaasid käivad ringi: viis klaasi liiguvad sisendist väljundisse, ja kui sisend on tühi, vahetavad hoidikud tarkvaras rollid. Nii jookseb laud sadu tsükleid ilma, et inimene klaase tagasi tõstaks.

Iga tsükkel jätab ühe kirje. Kirje kuju lepivad Andmehõive ja Nutikad Lahendused kokku enne, kui esimene kirje kirjutatakse, ja pärast kaitsmist seda enam ei muudeta: Labor 5 ja teised meeskonnad loevad neid kirjeid.

```
{"cycle": 1287, "team": "A", "t": "2026-11-30T14:02:11", "tip": 0.41, "pressure_kpa": 22.0,
 "pulse_ms": 140, "drop_area_mm2": 6.8, "drop_target_mm2": 7.0, "label": "normal",
 "label_source": "image", "syringe_g": 18.42, "curve": "curves/1287.csv", "image": "images/1287.jpg"}
```

Iga kirje juures on ka see, **kuidas märge teada on**: kas inimene vaatas, pilt ütles, või kaal ütles. Märge, mille päritolu ei tea keegi, ei ole Labori 5 jaoks midagi väärt.

Kirjuta üles: `docs/record.md` — iga välja nimi, ühik ja kust ta tuleb; tsükli samm-sammult; mitu sekundit üks tsükkel võtab ja mis selle ajast kõige rohkem võtab.

#### 3. Masin mõõdab

Laboris 3 kirjutasid sa programmi, mis eraldab heleda plaadi tumedast vaigust ja loeb laigud pikslitest kokku. Seal joonistas ta leitud piirjooned pildi peale, ja sina vaatasid iga pildi peal üle, kas nad olid seal, kus laik päriselt on. Nüüd jookseb ta iga tsükli järel ise, ja keegi ei vaata.

Seega pead teadma, kui palju sa talle usaldad, ja selleks on kaks võrdlust, mis ei sõltu sellest, kas programm täna hästi töötab.

**Labori 3 pildid.** Need pildid, mille piirjooned sa Laboris 3 üle vaatasid ja heaks kiitsid, on sinu võrdlus. Lase praegune programm nende peal uuesti käia. Ta peab andma samad numbrid, mis siis. Kui ta annab teised, muutsid sa vahepeal midagi — läve, valgust, kõrgust —, ja pead teadma, mida.

**Kaal.** Kaamera näeb laigu pindala, ja vahetükkide kõrgus teeb sellest ruumala. Kaal näeb massi, ja ta ei tea kaamerast midagi. Kaalu tilgaplaat enne tilku ja pärast, ja jaga tilkade arvuga: see on keskmine tilk grammides. Vaigu tihedus andmelehelt teeb sellest ruumala. Kas see on programmi keskmise ruumalaga nõus? Üks tilk on kaalu jaoks liiga kerge: arvuta, mitu tilka peab plaadil olema, et kaalu 0,01 g samm oleks alla 2 % kogu massist.

Siis vaata, kus programm eksib: kas servas, kui laik on hägune, kas peegelduse peal, kas siis, kui kaks laiku on liiga lähedal? Ja mis teeb ta pildiga, kus laiku ei ole üldse — kas ta ütleb "tühi" või leiab laigu mürast?

Programm, mis eksib vaikselt, on ohtlikum kui programm, mis ütleb, et ei tea. Kui pilt ei vasta sellele, mida programm ootab — liiga tume, liiga hele, laike vale arv —, märgib ta kirje "ei mõõdetud", mitte ei paku numbrit.

Kirjuta üles: Labori 3 piltide uus mõõtmine vana kõrval, erinevus protsentides; tilgaplaadi kaal enne ja pärast, tilkade arv, keskmine tilk kaalust ja programmist, erinevus protsentides; kolm pilti, kus masin eksis, ja miks; mis juhtub pildiga, kus laiku ei ole.

#### 4. Mudel ja tagasiside

Kaks moodi tilka sihti saada, ja selles osas proovid mõlemat ja nende summat.

**Mudel ette.** Sul on Laborist 3 `drops.csv`, ja osa 5 juhuslikus järjekorras tsüklitest tuleb juurde iga päev. Nendest saab arvutada, kui suur tilk tuleb, kui impulss on nii pikk, rõhk nii suur ja otsik see. See on lihtsaim masinõpe: **mudel, mis on andmete järgi sobitatud**.

Alusta sirgest:

```
pindala = a · impulss + b
```

`a` ja `b` tulevad vähimruutude meetodiga: need on numbrid, mille juures mudeli ja mõõdetu vahede ruutude summa on kõige väiksem. Sobita iga otsiku ja rõhu jaoks eraldi, või pane rõhk mudelisse teise tunnusena. Siis proovi üht kõverat — näiteks ruutliikmega või logaritmiga — ja jäta see, mis võidab **uutel andmetel**, mitte neil, millega ta sobitati.

Sellepärast jaga andmed enne sobitamist kaheks: suurem osa sobitamiseks, väiksem osa, mida mudel kunagi ei näe, kontrolliks. Mudeli viga ütled sa kontrolli osa pealt, protsentides. Mudel, mis on hea ainult oma õppeandmetel, on päheõpitud, mitte õpitud.

Ja üks tunnus, mida Labori 3 retsept ei teadnud: **kui täis on süstal**. Kaal ütleb seda iga 25 tsükli järel. Kas mudel läheb paremaks, kui süstla täidetus on sees? Kui läheb, siis süstla tühjenemine ei ole enam müra, vaid sisend.

Siis pööra mudel ümber: sihtsuurus sisse, impulss välja. See on esimene pakkumine, enne kui ühtegi tilka on mõõdetud.

**Tagasiside järele.** Mudel ei ole kunagi täpne: süstal, otsik ja ruum muutuvad pidevalt. Seepärast parandab masin pärast iga mõõdetud tilka järgmist impulssi:

```
viga = siht - mõõdetud
järgmine_impulss = praegune_impulss + k · viga
```

Liiga väike `k`, ja süstla tühjenemine jõuab ette. Liiga suur, ja tilk kõigub siht ümber edasi-tagasi, iga kord vales suunas üle. Proovi mitut `k` väärtust ja vaata, mis juhtub. Kui süstal saab tühjaks või otsik kinni, paneb tagasiside impulsi aina pikemaks, kuni katkestus vahele tuleb. Pane talle ülempiir, ja kirjuta, miks just see.

**Võrdlus.** Kolm moodi, sada tilka igaüks, sama süstlaga järjest: ainult Labori 3 retsept; ainult tagasiside; mudel ette ja tagasiside järele. Joonista tilga suurus tilga numbri vastu kõigil kolmel. Ja süstla vahetuse järel: mitme tilgaga jõuab tilk sihti ainult tagasisidega, ja mitmega mudeli abiga?

Kirjuta üles: mudelid, mida proovisid, nende `a`, `b` ja muud numbrid; kontrolli osa viga protsentides igal mudelil, ja kumma sa jätsid; kas süstla täidetus tegi mudeli paremaks; valitud `k` ja teised, mida proovisid; kolm graafikut kõrvuti; kõikumine protsentides igal moel; tilkade arv sihini pärast süstla vahetust mudeliga ja ilma; impulsi ülempiir ja põhjus.

#### 5. Andmestik

Nüüd jookseb laud. Vähemalt 300 tsüklit, ja seaded ei ole kõik ühesugused: muuda impulssi, rõhku ja otsikut **juhuslikus järjekorras**, mitte esimesed sada ühega ja järgmised sada teisega. Muidu ei saa Labor 5 eristada, kas tilk muutus seadete pärast või sellepärast, et süstal oli tühjem ja ruum soojem.

Kolm olukorda peavad andmestikus olema, ja igaüks mitu korda: tavaline tilk, kinnine otsik (sinu Labori 3 meelega kinni kõvendatud otsik) ja tühi süstal. Kaalu süstalt iga 25 tsükli järel: kaalust tuleb, palju vaiku päriselt läks, ja see on kõige ausam märge, mis sul on.

Laud, mis jookseb sadu tsükleid, jookseb ka siis, kui keegi parajasti ei vaata. Ruumis on ikka inimene, kes hädastoppi ulatub.

Kirjuta üles: mitu tsüklit, mitu igas olukorras; seadete jaotus; `data/cycles.csv`, `data/curves/`, `data/images/`; mitu kirjet jõudis Nutikate Lahenduste andmebaasi ja mitu kadus; süstla kaal tsüklite kaupa; üks lõik selle kohta, mida andmestikus ei ole ja mida Labor 5 peaks teadma.

**KAARDISTA ISE — vastused.** Iga osa kohta: numbrid, ühikud, kus fail on. Tegemata asja kohta üks rida, miks.

### Ohutus

* **Mähis ja diood.** MOSFET-iga klappi ei lülitata ilma kaitsedioodita. Klapi pinge ei ole Atomi pinge: MOSFET-i maa on ühine, aga klapi toide ei tohi Atomi viiku jõuda.
* **MOSFET läheb soojaks.** Mõõda, ära katsu.
* **405 nm valgus ja silmad.** Valgustamine käib katte all. Kui LED on draiveri küljes, on kõigil laua ääres kaitseprillid 405 nm jaoks ees.
* **Vaik.** Nitriilkindad, kui süstal on lahti. Kõvenemata vaiku kraanikaussi ei valata. Tilgaplaadid kõvendatakse enne prügikasti.
* **Pikk jooks.** Laud, mis jookseb sadu tsükleid, ei jookse tühjas ruumis. Inimene hädastopi juures on ruumis kogu aja.
* **Kinnine süstal on suletud anum rõhu all.** Ummistuskatse ajal on süstal tööriistas, mitte käes.
* Robot: käed ei ole laual, kui robot on sisse lülitatud. Uue jada esimene jooks 20 % kiirusel.
* Selles laboris ei joodeta.

### Komponendid selle labori jaoks

Tellimus läheb välja 27.11.26 ja jõuab kohale enne kaitsmist. Valmis nimekirja ei ole: meeskond paneb tellimuse ise kokku faili `docs/bom.md`, iga rea juures üks lause, milline osa või number seda küsib.

Tellimine käib ühisest tellimistabelist: [https://moodle.ut.ee/mod/url/view.php?id=1535601](https://moodle.ut.ee/mod/url/view.php?id=1535601). Kanna oma read sinna enne tellimise kuupäeva; mida tabelis ei ole, seda ei tellita.

Mõtle näiteks: kas IRLZ34N-e on varuks, kui üks läheb katki; kas kaitsediood kannab klapi voolu ka PWM-iga; mis takistid paisule ja allatõmbeks; kas otsikuid ja korke jätkub sadade tilkade jaoks; mitu tilgaplaati 300 tsüklit vajab ja kas filamenti jätkub; ja kas vaiku jätkub, kui iga tilk on paar mikroliitrit ja iga süstla vahetus kulutab ka.

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — Atomi püsivara MOSFET-i ja PWM-iga, tsükli programm, mõõtmise programm, mudel, tagasiside, `cycles.csv` koos kõverate ja piltidega | 5 p |
| Analüüs — MOSFET relee kõrval, masina mõõtmine Labori 3 piltide ja kaalu vastu, mudeli viga kontrolli andmetel, kolme moodi võrdlus, seadete jaotus ja märgete päritolu | 5 p |
| Prototüüp — klapp lülitub MOSFET-iga ja vooluta on süstal õhu peal, tsükkel jookseb inimeseta, tilk jääb mudeli ja tagasisidega sihti, vähemalt 300 kirjet andmebaasis | 5 p |
| Dokumentatsioon — README, arenduspäevik, `record.md`, skeem, `pump_control.md` uuendatud, `bom.md`, AGENTS.md | 5 p |
| **Kokku** | **20 p** |

### Kaitsmine

Link git repole, tag `data-acquisition-lab4`.

Kaitsmine on lihtne suuline 15 minuti jutuajamine. Laud teeb sinu silme all kümme tsüklit, ja kirjed ilmuvad andmebaasi. Näitad ostsilloskoobil MOSFET-i ja relee serva kõrvuti. Näitad kolme moodi graafikut kõrvuti ja ütled, kui suur on mudeli viga andmetel, mida ta ei näinud. Näitad ühte pilti, kus masin mõõtis valesti, ja mida ta sellega tegi. Avad oma arenduspäeviku. Õppejõud küsib umbes viis küsimust selle kohta, kuidas sa selle tegid. Kui esimesel korral ei õnnestu, tuled uuesti.

Repos on kaustas `data-acquisition/lab4/`: `src/` püsivara, tsükli, mõõtmise, mudeli ja tagasiside koodiga, `data/` kaustas `cycles.csv`, kõverad ja pildid, `notebooks/` võrdluste ja graafikutega, `docs/` kaustas skeem, ostsilloskoobi pildid, `record.md`, uuendatud `pump_control.md` ja `bom.md`, `README.md` selle labori kohta, ja `AGENTS.md` uuendatud.

### Arenduspäevik

**KAARDISTA ISE — päevik.** Üks sissekanne iga töösessiooni kohta, kirjutatud iseendale, nii et inimene, kes seal ei olnud, saab aru. Sissekandeid lisatakse, mitte ei muudeta.

Omadussõnad ei ole tulemused. "Tagasiside töötas hästi" ei ole midagi; "k = 0,8, sada tilka, 7,0 ± 0,3 mm², ilma tagasisideta 7,0 ± 0,9 mm²" on sissekanne.

**PP.KK.AA — kes olid kohal**
* Tegime:
* Juhtus (numbrid):
* Otsustasime, ja miks:
* Lahti järgmiseks korraks:

### Väljundid ja tulemused

**Väljundid**
* Andmehõive L5: märgistatud andmestik — kirjed, kõverad ja pildid —, mille peal masin õpib tavalist, kinnist ja tühja eristama; ja tilga suuruse mudel, millest edasi minnakse.
* Nutikad Lahendused L5: sadu päris kirjeid andmebaasis ja tagasiside, mida liides saab näidata.
* Integratsiooniprojekt: retsept koos mudeli ja tagasisidega, ja MOSFET-i skeem, mis läheb tööriista plaadile.

**KAARDISTA ISE, lõpus.**
* Git repo ja tag:
* Numbrid, mille see labor andis, ühikutega:
* Mida me teeksime teisiti:
* Mida järgmine labor peaks enne alustamist teadma:

### Tagasiside

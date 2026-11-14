## Nutikad Lahendused: Labor 4 — Ühine andmebaas ja töövoo salvestaja

**Töömaht:** 30 tundi | **Hindamine:** 20 punkti | **Meeskond:** 3 tudengit | **Välja antud:** 18.11.26 | **Tellimise kuupäev:** 27.11.26 | **Esimene kaitsmine:** 10.12.26, veebis

### Kuidas see dokument töötab

* Repo ja töökord on Laborist 1 olemas ja samad.
* Too sellest dokumendist oma projekti repo juurde see, mida vaja: selle labori kaust, `README.md`, kuhu lähevad su enda numbrid, otsused ja KAARDISTA ISE vastused, ja failid, mida kontrollnimekiri nimetab. Tervet dokumenti üle kopeerida ei ole vaja.
* Skeemid ja simulatsioonid lähevad dokumenti pildina, pildi juurde link elavale failile, et teine saaks selle lahti teha ja edasi muuta.

### Eesmärk

Laborite 1–3 lõpuks on sul robot, jaam, Atom, kaks kaamerat, ruuter, tunnel ja droplet. Igaüks neist kirjutab midagi kuhugi: CSV jaamas, logi dropletis, rida Atomi ekraanil. Andmehõive Labor 4 hakkab nüüd laskma robotil sadu tsükleid järjest, ja iga tsükkel jätab ühe kirje. Kui need kirjed on viies kohas viies kujus, ei saa keegi neid kasutada.

Selles laboris on kaks poolt.

**Ühine andmebaas.** Kõik kirjed lähevad ühte kohta dropletis, ühes kujus, ja igal kirjel on silt, mis meeskonnalt ta tuli. **Üks andmebaas, üks kirje kuju, kõik meeskonnad.** Jaam saadab, droplet võtab vastu, ja kumbki pool ei kaota midagi ka siis, kui tunnel vahepeal ära kukub. Kirje kuju lepitakse Andmehõivega kokku, ja pärast kaitsmist seda enam ei muudeta: Andmehõive Labor 5 õpib nende kirjete peal.

**Töövoo salvestaja.** Seni õpetati robotile punkte ükshaaval, ja tsükli kirjutas keegi koodi. Nüüd õpetab operaator terve tsükli lehelt: liigutab kätt, vaatab kaamerast, vajutab "salvesta" igas punktis, valib tegevuse — napp sisse, napp välja, doseeri N ms, kõvenda N s, puhu, oota — ja salvestab. "Mängi" teeb tsükli läbi. Töövoog on JSON-fail repos: teda saab võrrelda, teisele meeskonnale anda ja käsitsi parandada. Labori 1 punktide õpetamine kasvab selleks; midagi ei visata ära.

Ja kaks asja, ilma milleta see ohtlikuks läheb. **Operaatori lukk**: kui neli inimest on korraga lehel, juhib robotit ainult üks, ja teised vaatavad. **Puhver**: kui ühendus kaob, ei lähe kirjed kaduma, vaid ootavad ja lähevad hiljem.

Ja üks uks tuleviku jaoks. Laboris 5 juhib laua tööd agent. Selles laboris saab jaam **MCP ukse**, mille kaudu agent loeb kõike, mida sina lehel näed — seisu, kirjeid, kaameraid —, aga ei liiguta midagi. Liigutamise õiguse annab Labor 5.

Vastuvõtukatse on lihtne: **teine meeskond salvestab sinu jaamas töötava töövoo alla viie minutiga, ilma sinu abita.**

Selles laboris on kuus asja:

1. **Kirje kuju.** Kokku lepitud, kirjas, lukus.
2. **Tee andmebaasi.** Jaamast tunneli kaudu dropletisse, ükski kirje ei kao.
3. **Kui ühendus kaob.** Puhver, mis kannatab tunneli kadumise ja Atomi taaskäivituse.
4. **Töövoo salvestaja.** Õpeta, salvesta, mängi.
5. **Lukk ja katse.** Üks juhib korraga, ja teine meeskond saab hakkama ilma sinuta.
6. **MCP uks, ainult lugemiseks.** Agent näeb, aga ei liiguta.

Esimesel päeval uusi osi ei ole. Ehita sellest, mis riiulil on, ja kirjuta puuduv tellimuseks, mis läheb välja 27.11.

*See on elav dokument. Uuenda eesmärke, kui need töö käigus muutuvad — uued teadmised teevad vanad eesmärgid vahel mõttetuks. Mõte on hoida meeskond kogu aeg sihil, et ei eksitaks detailide metsa ja põhiprobleem ei jääks lahendamata.*

**KAARDISTA ISE — eesmärk nii, nagu ta tegelikult välja tuli.**

### Kontrollnimekiri

**Peab olema tehtud**

- [ ] Kirje kuju kokku lepitud Andmehõivega ja kõigi meeskondadega, kirjas failis `docs/record.md`. Iga välja nimi, ühik ja kust ta tuleb.
- [ ] Andmebaas dropletis, kättesaadav ainult tunneli kaudu. Igal meeskonnal oma kasutaja ja õigus kirjutada ainult oma siltidega.
- [ ] Jaam saadab iga tsükli kirje; droplet kirjutab ta andmebaasi meeskonna sildiga.
- [ ] 500 kirjet saadetud ja üle loetud: mitu saadeti, mitu jõudis, mitu oli topelt. Kadunud kirjeid null.
- [ ] Tunnel võetud maha keset jooksu ja Atom tõmmatud vooluta keset tsüklit: kirjed ootasid ja jõudsid hiljem kohale, ükski kaks korda.
- [ ] Töövoo salvestaja jaama lehel: punkt, tegevus, salvesta, mängi. Töövoog JSON-failina repos.
- [ ] Üks töövoog mängitud läbi 20 korda järjest, iga kord sama tulemusega.
- [ ] Operaatori lukk: teine kasutaja näeb, aga ei juhi. Luku vabastamine on kirjas ja proovitud.
- [ ] MCP uks jaamas: `guide`, `status`, `look` ja `api` ainult lugemiseks. Vaikimisi kinni, salajane link, läheb ise kinni, iga kutse logis.
- [ ] Keelatud kutse ja kinnine uks vastavad lausega, mitte veakoodiga. Proovitud.
- [ ] Agent vastas ainult lingi kaudu kolmele küsimusele. Vastused ja kutsete arv kirjas.
- [ ] Teine meeskond salvestas sinu jaamas töötava töövoo alla viie minutiga ilma sinu abita. Aeg ja nende märkmed kirjas.
- [ ] Labori 3 ohutuskokkulepe täiendatud: kes tohib töövoogu kaugelt käivitada.
- [ ] Tellimus 27.11 failis `docs/bom.md`.
- [ ] Repo ja arenduspäevik täidetud, tag `smart-solutions-lab4`.

**KAARDISTA ISE — kuupäevad ja sinu enda sammud.**

### Sisendid

* Laborist 1: jaam, MG400 baaspakett, punktide õpetamine ja kordamine, Atomi leht.
* Laborist 2: droplet ja domeen, postkontor, kaks kaamerat jaama lehel, ohutuskokkulepe.
* Laborist 3: ruuter, tunnel, aadressiplaan, ühenduse katkemise reegel, 48 tunni tunneli logi.
* Andmehõive L4-st: kirje väljad, mida nende tsükkel annab — seaded, rõhukõver, pilt, mõõdetud tilk, märge —, ja sadu kirjeid, mida nad saadavad.
* Andmehõive L3-st: klapi ja UV LED-i käsud Atomi lehel.
* 3D printimise L4-st: kui detail laual vahetub, kuupäev.

### Vahendid

1. Labori 3 laud: jaam, MG400, Atom, kaamerad, ruuter, tunnel
2. Droplet: MQTT vahendaja, andmebaas, pöördproksi
3. AtomS3 välkmäluga puhvri jaoks
4. Python 3, Flask; git; draw.io
5. Stopper ja teine meeskond vastuvõtukatseks
6. MCP klient katseks, näiteks Claude Code

*Kui plaan muutub, uuenda ka vahendeid, või tee draw.io skeem, mis näitab, kuidas asjad omavahel töötavad.*

**KAARDISTA ISE — mida sa päriselt kasutasid.**

### Taustainfo

* **MQTT** — teated teema järgi, vahendaja keskel
  (link puudu)
* **MQTT teenustase (QoS)** — mis vahe on "kord", "vähemalt kord" ja "täpselt kord"
  (link puudu)
* **Aegridade andmebaas** — sildid ja väljad, miks silte ei tohi olla lõputult
  (link puudu)
* **Puhver ja korduvsaatmine** — kuidas mitte saata sama kirjet kaks korda
  (link puudu)
* **MCP** — kuidas agent küsib programmilt tööriistu ja kutsub neid välja
  (link puudu)
* **JSON-RPC** — üks päring, üks vastus, number vahel
  (link puudu)
* **Andmebaasi konsultatsioon** — MQTT, andmebaas ja kirje kuju samm-sammult. Aeg lepitakse meeskondadega jooksvalt kokku. Tule sinna oma kirje kujuga.
  [Ainepassi kontakttunnid](../../Smart%20Solutions/SVNC.00.321_SO%20EST%20v2.md#kontakttundide-ajakava)

*Lisa siia oma allikaid ja kasulikku infot, mis aitaks sul projektist aru saada ka aastaid hiljem, kui selle uuesti lahti teed.*

**KAARDISTA ISE — sinu allikad.**

### Osad

#### 1. Kirje kuju

Enne, kui midagi kuhugi saadetakse, lepivad kõik kokku, mis üks kirje on. Andmehõive Labor 4 ütleb, mis väljad nende tsükkel annab. Sinu töö on teha neist kuju, mis kehtib kõigile meeskondadele ja ei muutu.

Igal väljal on nimi, ühik ja päritolu. Iga kirje juures on meeskond, aeg ja tsükli number, ja tsükli number on unikaalne: sellest teab andmebaas, et sama kirje tuli kaks korda.

```
{"cycle": 1287, "team": "A", "t": "2026-11-30T14:02:11", "pulse_ms": 140, "pressure_kpa": 22.0,
 "drop_area_mm2": 6.8, "label": "normal", "label_source": "image",
 "curve": "curves/1287.csv", "image": "images/1287.jpg"}
```

Üks otsus on andmebaasi jaoks tähtsam kui kõik teised: mis on **silt** ja mis on **väli**. Silt on see, mille järgi otsitakse — meeskond, märge. Väli on see, mida mõõdetakse — impulss, rõhk, tilga pindala. Kui paned sildiks midagi, millel on lõputult väärtusi, näiteks tsükli numbri, kasvab andmebaas, kuni ta ei jaksa.

Rõhukõver ja pilt on suured. Otsusta, kas nad lähevad andmebaasi või failina kõrvale ja kirjesse läheb ainult viide.

Kirjuta üles: `docs/record.md` — iga väli, ühik, päritolu, kas silt või väli; mis kõverast ja pildist sai ja miks; kuupäev, millal kuju lukku pandi, ja kes allkirjastas.

#### 2. Tee andmebaasi

Jaam saadab kirje teele, droplet võtab ta vastu ja kirjutab andmebaasi. Vahel on **MQTT**: jaam saadab teate teemasse, vahendaja dropletis võtab ta vastu, ja programm dropletis kuulab seda teemat ja kirjutab andmebaasi. Jaam ei pea teadma, kes kuulab.

Vahendaja kuulab ainult tunneli aadressil. Labori 3 reegel kehtib edasi: postkontor on avalik, kõik muu on tunnelis. Igal meeskonnal on oma kasutaja ja parool, ja ta tohib kirjutada ainult oma meeskonna teemasse.

Siis **teenustase**. Rõhunäidud, mis tulevad 100 korda sekundis, võivad vahel kaduda, ja keegi ei märka. Tsükli kirje ei tohi. Vali kummalegi teenustase ja kirjuta, miks.

Ja siis loe üle. 500 kirjet: mitu jaam saatis, mitu andmebaasis on, mitu on seal kaks korda. Kui mõni kadus, leia, kus.

Kirjuta üles: skeem draw.io-s, jaamast andmebaasini; vahendaja ja andmebaasi seadistus ilma paroolideta; teemade nimed; teenustase ja põhjus; loendus 500 kirje kohta.

#### 3. Kui ühendus kaob

Laboris 3 mõõtsid sa, et tunnel katkeb. Kui ta katkeb keset jooksu, ei tohi kirjed kaduda.

Seega kirje ei kao jaamast enne, kui droplet on öelnud, et sai. Kuni seda ei ole, ootab ta puhvris ja saadetakse uuesti. Ja kuna ta võib nii jõuda kaks korda, viskab andmebaas topelt välja tsükli numbri järgi.

Atom on teine koht, kus asjad kaovad: kui ta taaskäivitub keset tsüklit, on tema mälus olnud read läinud. Kirjuta tsükli lõpu sündmus Atomi välkmällu enne, kui ta saadetakse, ja kustuta alles siis, kui jaam on kinnitanud.

Siis proovi. Võta tunnel maha keset jooksu, kümme minutit, ja pane tagasi. Tõmba Atom vooluta keset tsüklit. Mõlemal korral: mitu kirjet ootas, mitu jõudis, mitu oli topelt.

Kirjuta üles: kuidas puhver töötab, samm-sammult; mitu kirjet mahub puhvrisse ja mis juhtub, kui ta saab täis; kaks katset ja nende loendused.

#### 4. Töövoo salvestaja

Jaama leht saab uue osa. Operaator liigutab robotit lehelt ja vaatab samal ajal tööriista kaamerat. Igas punktis vajutab ta "salvesta", ja punkti juurde valib tegevuse: napp sisse, napp välja, doseeri N ms, kõvenda N s, puhu, oota N ms. Lõpuks salvestab ta töövoo nimega.

```
{"name": "silt_v1", "speed_pct": 20, "steps": [
  {"pose": [250.0, -60.0, 40.0, 0.0], "action": "move"},
  {"pose": [250.0, -60.0, 12.5, 0.0], "action": "suction_on"},
  {"pose": [250.0, -60.0, 40.0, 0.0], "action": "move"},
  {"pose": [210.0,  20.0, 30.0, 0.0], "action": "dispense", "ms": 140},
  {"pose": [210.0,  20.0, 30.0, 0.0], "action": "cure", "s": 8}]}
```

"Mängi" teeb töövoo läbi. Esimene kord 20 % kiirusel, ja ruumis on inimene hädastopi juures. Iga töövoog on fail repos: seda saab võrrelda eelmise versiooniga, anda teisele meeskonnale ja parandada käsitsi.

Kaks asja, mida salvestaja peab ise kontrollima, enne kui mängib: kas iga punkt on roboti ulatuses, ja kas ükski tegevus ei ole ohutuse piirist üle — näiteks UV kõvendamine, mis on pikem kui Andmehõive lubatud ülempiir. Töövoog, mis seda ei läbi, ei käivitu.

Siis mängi üks töövoog 20 korda järjest ja vaata, kas iga kord juhtus sama.

Kirjuta üles: töövoo faili kuju failis `docs/workflow.md`; mida salvestaja enne mängimist kontrollib; 20 korduse tulemus; mis läks esimesel korral valesti.

#### 5. Lukk ja katse

Kui leht on kaugelt kättesaadav, võib seal olla korraga mitu inimest. Robot kuulab ühte. **Lukk**: kes vajutab "võtan juhtimise", see juhib, ja teised näevad, kes juhib, aga nende nupud ei tee midagi. Lukk vabaneb, kui juhtija vajutab "loobun" või kui ta on teatud aja vait. Kui kaua, on sinu otsus; kirjuta, miks.

Ja siis **vastuvõtukatse**. Teine meeskond tuleb sinu jaama juurde. Sa ei räägi ega näita. Stopper käima: nad peavad salvestama töövoo, mis võtab klaasi ja paneb ta teise hoidikusse, ja selle läbi mängima. Alla viie minuti. Kui ei õnnestu, ei ole viga nendes. Kirjuta üles, kus nad jäid kinni, paranda, ja kutsu järgmine meeskond.

Kirjuta üles: luku reeglid ja kuidas proovisid; vastuvõtukatse aeg, kes tegi, kus jäädi kinni ja mis selle järel muutus.

#### 6. MCP uks, ainult lugemiseks

Laboris 5 hakkab robotit juhtima agent: programm, mis loeb, mida jaam oskab, ja teeb töö ise ära — näiteks Claude Code. Selleks vajab ta ust. Selles laboris ehitad ukse, aga ainult lugemiseks: agent näeb kõike, mida sina lehel näed, ja ei liiguta midagi.

**MCP** (Model Context Protocol) on kokkulepe, kuidas agent küsib programmilt, mis tööriistad tal on, ja kutsub neid välja. Sõnum on JSON: üks POST päring sisse, üks JSON vastus välja. Selle saab kirjutada ühe Flaski marsruudina, ilma lisateegita — ja see on mõte: sa näed, mis MCP päriselt on, mitte seda, mida teek sinu eest peidab.

```
agent → jaam:  {"jsonrpc": "2.0", "id": 3, "method": "tools/call", "params": {"name": "look", "arguments": {"camera": "table"}}}
jaam → agent:  {"jsonrpc": "2.0", "id": 3, "result": {"content": [{"type": "image", "data": "…", "mimeType": "image/jpeg"}]}}
```

Neli tööriista, ja rohkem ei ole vaja:

* **guide()** — "loe see enne kõike muud läbi": mida agent tohib, mida mitte, ja jaama marsruutide nimekiri.
* **status()** — "alusta siit": kas robot on üleval, kes juhib, mitu tsüklit täna, viimane kirje, mitu minutit uks veel lahti on.
* **look(camera)** — pilt laua või tööriista kaamerast.
* **api(path)** — jaama enda olemasolevad marsruudid, ainult lugemine, ja ainult need, mis on lubatud nimekirjas. Uut koodi ei tule: MCP on õhuke kiht olemasoleva lehe peal, ja iga marsruut kontrollib ise, mida ta lubab.

**Uks on vaikimisi kinni.** Operaator teeb ta jaama lehel lahti, ja ta läheb ise kinni, kui agent on teatud aja vait. Lahti tegemisel tuleb salajane link: link on ainus võti, ja uus link tühistab vana kohe. Kinnine uks vastab ikka, aga ütleb sõnadega, et ta on kinni ja kes ta lahti teeb — mitte 404, sest selle peale jätab agent ukse üldse meelde võtmata. Uks on ainult tunnelis, nagu andmebaas.

Iga kutse läheb logisse: aeg, tööriist, argumendid. Ja kontrolli, et ta päriselt ainult loeb: proovi `api` kaudu midagi kirjutada või lubamata marsruuti avada, ja vaata, mis vastus tuleb. Vastus peab olema lause, mille agent aru saab, mitte veakood.

Siis katse. Anna agendile ainult link, mitte midagi muud. Küsi kolm küsimust, millele ta saab vastata ainult ukse kaudu: mitu tsüklit täna tehti ja mitu neist oli kinnine otsik? Kas sisendhoidikus on klaas? Mis kell tuli viimane kirje? Kas ta vastas õigesti, ja mitu kutset tal kulus?

Kirjuta üles: `guide()` tekst failis `docs/mcp.md`; tööriistade ja lubatud marsruutide nimekiri; mida vastab kinnine uks; mida vastab keelatud kutse; logi katsest; kolm küsimust, agendi vastused, õiged vastused ja kutsete arv.

**KAARDISTA ISE — vastused.** Iga osa kohta: numbrid, ühikud, kus fail on. Tegemata asja kohta üks rida, miks.

### Ohutus

* **Töövoog liigutab robotit ilma, et keegi iga liigutust vajutaks.** Esimene mängimine 20 % kiirusel, ja ruumis on inimene hädastopi juures. Ka kaugelt käivitatud töövoo ajal.
* **Lukk on ohutusvahend, mitte mugavus.** Kaks inimest, kes juhivad sama robotit korraga, on kokkupõrge, mis ootab juhtumist.
* **UV LED-i ei lülitata kaugelt.** Töövoog, milles on kõvendamine, käivitatakse ainult siis, kui ruumis on inimene, kellel on kaitseprillid ees.
* **Labori 3 ohutuskokkulepe** täiendatakse enne, kui töövoog esimest korda kaugelt käivitatakse: kes tohib ja mida ta peab enne kontrollima.
* **Paroolid ja võtmed ei lähe reposse.** Ka mitte andmebaasi ja vahendaja omad.
* Andmebaas ja vahendaja kuulavad ainult tunnelis. Avalik postkontor ei saa andmebaasi kirjutada.
* **MCP uks ei liiguta selles laboris midagi.** Ta on vaikimisi kinni, läheb ise kinni, ja tema link on võti: ta ei lähe reposse ega vestlusse. Kui link lekib, tee uus.
* Agent, kes ukse kaudu loeb, loeb ka seda, mis kaamera näeb. Lepi meeskonnas kokku, mida kaamera vaateväljas olla ei tohi.
* MG400 reeglid Laborist 1 kehtivad edasi: käed ei ole laual, kui robot on sisse lülitatud; käsklusi saadab robotile korraga ainult üks programm.

### Komponendid selle labori jaoks

Droplet ja ruuter on olemas. Tellimus läheb välja 27.11.26 ja jõuab kohale enne kaitsmist. Valmis nimekirja ei ole: meeskond paneb tellimuse ise kokku faili `docs/bom.md`, iga rea juures üks lause, milline osa seda küsib.

Tellimine käib ühisest tellimistabelist: [https://moodle.ut.ee/mod/url/view.php?id=1535601](https://moodle.ut.ee/mod/url/view.php?id=1535601). Kanna oma read sinna enne tellimise kuupäeva; mida tabelis ei ole, seda ei tellita.

Mõtle näiteks: kas dropleti ketas ja mälu jaksavad sadu kirjeid koos piltidega; kas kõik meeskonnad mahuvad ühele dropletile; ja kas jaama ja laua vahel on midagi, mis kaotab ühenduse sagedamini kui tunnel.

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — vahendaja ja andmebaasi seadistus ilma paroolideta, jaama saatmine puhvriga, Atomi välkmälu puhver, töövoo salvestaja, lukk, MCP uks | 5 p |
| Analüüs — kirje kuju koos siltide ja väljadega, 500 kirje loendus, kahe katkestuse katse, 20 korduse tulemus, vastuvõtukatse aeg ja kinnijäämise kohad, agendi kolm vastust | 5 p |
| Prototüüp — kirjed jõuavad andmebaasi ainult tunneli kaudu ja ükski ei kao, töövoog salvestatakse lehelt ja mängitakse läbi, lukk töötab, teine meeskond saab hakkama alla viie minutiga, MCP uks loeb ja ei kirjuta | 5 p |
| Dokumentatsioon — README, arenduspäevik, `record.md`, `workflow.md`, `mcp.md`, skeem, ohutuskokkulepe, `bom.md`, AGENTS.md | 5 p |
| **Kokku** | **20 p** |

### Kaitsmine

Link git repole, tag `smart-solutions-lab4`.

Kaitsmine on lihtne suuline 15 minuti jutuajamine. Õppejõud salvestab sinu jaamas ise ühe töövoo ja mängib ta läbi. Võtad tunneli maha keset jooksu, paned tagasi, ja näitad, et kirjed jõudsid kohale ja ükski kaks korda. Näitad lukku kahest brauserist korraga. Teed MCP ukse lahti, ja agent vastab õppejõu küsimusele ainult ukse kaudu. Avad oma arenduspäeviku. Õppejõud küsib umbes viis küsimust selle kohta, kuidas sa selle tegid. Kui esimesel korral ei õnnestu, tuled uuesti.

Repos on kaustas `smart-solutions/lab4/`:

* `src/` jaama kood saatmise, puhvri, salvestaja, luku ja MCP uksega
* `server/` dropleti kood: kuulaja
* `firmware/` Atomi PlatformIO projekt puhvriga
* `workflows/` töövood JSON-failidena
* `docs/`: `record.md`, `workflow.md`, `mcp.md`, skeem draw.io-s, vahendaja ja andmebaasi seadistus ilma paroolideta, ohutuskokkulepe, ekraanipildid, `bom.md`
* `README.md` selle labori kohta
* `AGENTS.md` uuendatud

### Arenduspäevik

**KAARDISTA ISE — päevik.** Üks sissekanne iga töösessiooni kohta, kirjutatud iseendale, nii et inimene, kes seal ei olnud, saab aru. Sissekandeid lisatakse, mitte ei muudeta.

**PP.KK.AA — kes olid kohal**
* Tegime:
* Juhtus (numbrid):
* Otsustasime, ja miks:
* Lahti järgmiseks korraks:

### Väljundid ja tulemused

**Väljundid**
* Andmehõive L4: kirje kuju, teema ja töövoog, mis jooksutab nende sadu tsükleid.
* Andmehõive L5: andmebaas, mille peal kõigi meeskondade mudelid õpivad.
* Nutikad Lahendused L5: MCP uks, millele Labor 5 annab õiguse liigutada — ainult siis, kui kohalik operaator on lukust loa andnud —, ja portaal, mis näitab kõigi meeskondade robotite seisu ühel lehel.
* Integratsiooniprojekt: töövoog, mis teeb esimese täieliku sildi.

**KAARDISTA ISE, lõpus.**
* Git repo ja tag:
* Numbrid, mille see labor andis, ühikutega:
* Mida me teeksime teisiti:
* Mida järgmine labor peaks enne alustamist teadma:

### Tagasiside

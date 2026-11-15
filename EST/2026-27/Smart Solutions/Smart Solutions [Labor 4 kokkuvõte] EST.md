## Nutikad Lahendused: Labor 4 — Ühine andmebaas ja töövoo salvestaja

**Maht:** 30 tundi | **Hindamine:** 20 punkti | **Meeskonnatöö:** 3-liikmelised meeskonnad | **Välja antud:** 18.11.26 | **Tellimise kuupäev:** 27.11.26 | **Esimene kaitsmine:** 10.12.26, veebis

### Mida teete

Laborite 1–3 lõpuks on sul robot, jaam, Atom, kaks kaamerat, ruuter, tunnel ja droplet. Igaüks neist kirjutab midagi kuhugi: CSV jaamas, logi dropletis, rida Atomi ekraanil. Andmehõive Labor 4 laseb nüüd robotil teha sadu tsükleid järjest, ja iga tsükkel jätab ühe kirje. Kui need kirjed on viies kohas viies kujus, ei saa keegi neid kasutada.

Selles laboris on kaks poolt. **Ühine andmebaas**: kõik kirjed lähevad ühte kohta dropletis, ühes kujus, ja igal kirjel on silt, mis meeskonnalt ta tuli. Ükski kirje ei kao ka siis, kui tunnel vahepeal ära kukub. **Töövoo salvestaja**: operaator õpetab terve tsükli jaama lehelt — liigutab kätt, vaatab kaamerast, salvestab punkti ja valib tegevuse — ja "Mängi" teeb tsükli läbi. Töövoog on JSON-fail repos.

Ja kaks asja, ilma milleta see ohtlikuks läheb: **operaatori lukk**, et robotit juhib korraga ainult üks, ja **puhver**, et kirjed ei kao, kui ühendus kaob. Laboris 5 hakkab laua tööd juhtima agent, ja selleks saab jaam nüüd **MCP ukse**, mille kaudu agent näeb kõike, aga ei liiguta midagi.

Vastuvõtukatse on lihtne: **teine meeskond salvestab sinu jaamas töötava töövoo alla viie minutiga, ilma sinu abita.**

Kuus osa:

**1. Kirje kuju** — Andmehõive Labor 4 ütleb, mis väljad nende tsükkel annab, ja sinu töö on teha neist kuju, mis kehtib kõigile meeskondadele. Igal väljal on nimi, ühik ja päritolu, ja tsükli number on unikaalne. Kõige tähtsam otsus on, mis on **silt** (mille järgi otsitakse) ja mis on **väli** (mida mõõdetakse). Tulemus: `docs/record.md`, kuupäev, millal kuju lukku pandi, ja kes allkirjastas.

**2. Tee andmebaasi** — jaam saadab kirje MQTT kaudu, vahendaja ja andmebaas on dropletis ja kuulavad ainult tunnelis. Igal meeskonnal on oma kasutaja ja ta tohib kirjutada ainult oma teemasse. Rõhunäidule ja tsükli kirjele valitakse eri teenustase, põhjusega. Tulemus: skeem jaamast andmebaasini, seadistus ilma paroolideta, ja loendus 500 kirje kohta: mitu saadeti, mitu jõudis, mitu oli topelt.

**3. Kui ühendus kaob** — kirje ei kao jaamast enne, kui droplet on öelnud, et sai, ja andmebaas viskab topelt välja tsükli numbri järgi. Atom kirjutab tsükli lõpu välkmällu enne, kui ta saadetakse. Kaks katset: tunnel maha kümneks minutiks keset jooksu, ja Atom vooluta keset tsüklit. Tulemus: puhvri töö samm-sammult ja mõlema katse loendused.

**4. Töövoo salvestaja** — punkt, tegevus (napp sisse, napp välja, doseeri, kõvenda, puhu, oota), salvesta, mängi. Enne mängimist kontrollib salvestaja ise, kas iga punkt on roboti ulatuses ja kas ükski tegevus ei ole ohutuse piirist üle. Üks töövoog mängitakse läbi 20 korda järjest. Tulemus: `docs/workflow.md`, töövood failidena kaustas `workflows/`, ja 20 korduse tulemus.

**5. Lukk ja katse** — kes võtab juhtimise, see juhib, teised näevad, aga nende nupud ei tee midagi. Lukk vabaneb, kui juhtija loobub või on teatud aja vait. Siis vastuvõtukatse: teine meeskond, stopper, sina ei räägi ega näita. Tulemus: luku reeglid, katse aeg, kus jäädi kinni ja mis selle järel muutus.

**6. MCP uks, ainult lugemiseks** — üks Flaski marsruut ilma lisateegita, neli tööriista: `guide`, `status`, `look` ja `api`. Uks on vaikimisi kinni, avamisel tuleb salajane link, ta läheb ise kinni, ja iga kutse läheb logisse. Kinnine uks ja keelatud kutse vastavad lausega, mitte veakoodiga. Siis saab agent ainult lingi ja vastab kolmele küsimusele. Tulemus: `docs/mcp.md`, logi katsest, agendi vastused õigete kõrval ja kutsete arv.

### Kuidas töö käib

Repo ja töökord on Laborist 1 olemas ja samad. Tervet töölehte üle kopeerida ei ole vaja — too oma repo juurde see, mida vaja, ja täida `README.md` oma numbrite ja otsustega. Skeemid lähevad dokumenti pildina, pildi juurde link elavale failile. Ei tulnud esimesel korral välja, tule homme tagasi ja proovi uuesti.

Enne, kui töövoog esimest korda kaugelt käivitatakse, täiendab meeskond Labori 3 ohutuskokkulepet: kes tohib töövoogu kaugelt käivitada ja mida ta peab enne kontrollima. Esimene mängimine käib 20 % kiirusel, ja ruumis on inimene hädastopi juures. UV LED-i kaugelt ei lülitata. Paroolid, võtmed ja MCP ukse link reposse ei lähe.

Esimesel päeval uusi osi ei ole — ehita sellest, mis riiulil on. Andmebaasi konsultatsiooni aeg lepitakse meeskondadega jooksvalt kokku; tule sinna oma kirje kujuga.

### Komponendid selle labori jaoks

Droplet ja ruuter on olemas; neid tellimusse ei panda. Tellimus läheb välja 27.11.26 ja jõuab kohale enne kaitsmist. Valmis nimekirja ei ole: meeskond paneb tellimuse ise kokku faili `docs/bom.md`, iga rea juures üks lause, milline osa seda küsib. Tellimine käib ühisest tellimistabelist: [https://moodle.ut.ee/mod/url/view.php?id=1535601](https://moodle.ut.ee/mod/url/view.php?id=1535601).

### Kaitsmiseks on vaja

**Ainult git repositooriumi link, tag `smart-solutions-lab4`.** Kaustas `smart-solutions/lab4/` peab olema:
- `src/` jaama kood saatmise, puhvri, salvestaja, luku ja MCP uksega, `server/` dropleti kuulaja, `firmware/` Atomi PlatformIO projekt puhvriga
- `workflows/` töövood JSON-failidena
- `docs/`: `record.md`, `workflow.md`, `mcp.md`, skeem draw.io-s, vahendaja ja andmebaasi seadistus ilma paroolideta, ohutuskokkulepe, ekraanipildid, `bom.md`
- Täidetud `README.md` koos arenduspäevikuga
- `AGENTS.md` uuendatud

Kaitsmine on lihtne suuline 15 minuti jutuajamine. Õppejõud salvestab sinu jaamas ise ühe töövoo ja mängib ta läbi. Võtad tunneli maha keset jooksu, paned tagasi, ja näitad, et kirjed jõudsid kohale ja ükski kaks korda. Näitad lukku kahest brauserist korraga. Teed MCP ukse lahti, ja agent vastab õppejõu küsimusele ainult ukse kaudu. Avad oma arenduspäeviku. Umbes viis küsimust selle kohta, kuidas sa selle tegid. Kaitsta saab nii mitu korda, kui vaja.

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — vahendaja ja andmebaasi seadistus ilma paroolideta, jaama saatmine puhvriga, Atomi välkmälu puhver, töövoo salvestaja, lukk, MCP uks | 5 p |
| Analüüs — kirje kuju koos siltide ja väljadega, 500 kirje loendus, kahe katkestuse katse, 20 korduse tulemus, vastuvõtukatse aeg ja kinnijäämise kohad, agendi kolm vastust | 5 p |
| Prototüüp — kirjed jõuavad andmebaasi ainult tunneli kaudu ja ükski ei kao, töövoog salvestatakse lehelt ja mängitakse läbi, lukk töötab, teine meeskond saab hakkama alla viie minutiga, MCP uks loeb ja ei kirjuta | 5 p |
| Dokumentatsioon — README, arenduspäevik, `record.md`, `workflow.md`, `mcp.md`, skeem, ohutuskokkulepe, `bom.md`, AGENTS.md | 5 p |
| **Kokku** | **20 p** |

### Täielik tööleht

📎 [Link täielikule töölehele](https://github.com/KKallas/Narva-subjects/blob/main/EST/2026-27/Smart%20Solutions/Smart%20Solutions%20%5BLab%204%5D%20EST.md)

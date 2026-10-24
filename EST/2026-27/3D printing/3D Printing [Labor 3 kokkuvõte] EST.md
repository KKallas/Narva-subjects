## 3D printimine ja CAD: Labor 3 — Tööriist: napp, süstal ja UV-lamp

**Maht:** 28 tundi | **Hindamine:** 20 punkti | **Meeskonnatöö:** 3-liikmelised meeskonnad | **Välja antud:** 27.10.26 | **Tellimise kuupäev:** 06.11.26 | **Esimene kaitsmine:** 19.11.26, veebis

### Mida teete

Laud on valmis ja hoidikud on ruudustikus. Käe otsas on napp ja kaamera, ja sellega saab tõsta. Aga silt ei saa kokku ainult tõstmisega: klaas **liimitakse** Atomi ekraani peale. Liim on 3D-printeri vaik, mis kõveneb 405 nm valguse käes. Seega peab robot oskama kolme asja: **tõsta** iminapaga, **doseerida** süstlaga, millest õhurõhk surub tilga välja, ja **kõvendada** UV LED-iga läbi klaasi. Käsi on üks, nii et kõik kolm on ühes tööriistas, koos kaameraga Laborist 2.

Pumpa on samuti üks, ja ta kas imeb või puhub. Imedes hoiab napp klaasi, puhudes surub õhk süstlast tilga välja, nii et tilk tehakse enne, kui klaas võetakse. Tilga algust ja lõppu otsustab **solenoidklapp** süstla ees: voolu all läheb pumba õhk süstlasse, vooluta laseb vedru süstla rõhu õhku. Napp on klapist mööda, otse pumba voolikus.

See on esimene detail sellel kursusel, millel on korraga kolm vaenlast: **rõhk**, mis leiab üles iga prao kihtide vahel; **kaal**, sest käsi tõstab 500 g koos tööriista, täis süstla ja klaasiga korraga; ja **geomeetria**, sest kolm otsikut segavad üksteist, kui sa ei ole läbi mõelnud, kes millal all on.

Viis osa:

**1. Mõõda ja paiguta** — enne Fusioni. Kõik osad nihikuga ja kaalul, õhu teekond skeemina koos rõhuanduri ja voolikute pikkustega, kaalueelarve suurima koormaga. Ja esimene päris otsus: kas klapp elab käe otsas või laua peal. Tulemus: `docs/tool_layout.md`.

**2. Klapi kinnitus** — kinnitus on olemas: [Solenoidklapi kinnitus.f3z](Solenoidklapi%20kinnitus.f3z). Poldid suruvad kihid kokku, voolik läheb otse klapi juurde, hambaork hoiab voolikut paigal ja silikoon tihendab. Prindi, pane kokku ja pane süsteemi külge: Gridfinity hoidikuga laua peale või tööriistahoidiku külge käe otsa. Tulemus: kinnitus koos voolikutega süsteemi küljes ja klapi temperatuur pärast kümmet minutit voolu all.

**3. Tööriist** — uus tööriistahoidik roboti nina külge: napp, süstal, UV-lamp ja kaamera ühes tükis. Pane kogu tööriist Fusionis jointidega kokku ja tee liikumise uuring läbi kõigi töökohtade ja hoidikute. Süstal vahetub ühe käega ja ilma tööriistadeta, ja otsik on pärast vahetust samas kohas. Lambi valguskoonus läheb otsikust mööda, ja valgustamine käib musta katte all. LED-i ja draiveri valid ise, õppejõud ostab need Mouserist. Tulemus: tööriist alla 500 g suurima koormaga ja neli nihet failis `docs/tool_offsets.md`.

**4. Õhk peab pidama** — süstla päis on pooleli: [Süstla päis poolik.f3z](S%C3%BCstla%20p%C3%A4is%20poolik.f3z). Ta on 10 cc süstlale ([Metcal 910-B, andmeleht joonisega](https://www.farnell.com/datasheets/3919444.pdf)), ja süstal on mudelina olemas: [Metcal 910 süstal 10cc.f3d](Metcal%20910%20s%C3%BCstal%2010cc.f3d), parameetritega, mida saad oma mõõtude järgi muuta, ning Metcali enda mudelid: [süstal](Metcal%20910-N%20s%C3%BCstal%2010cc.f3d) ja [kolb](Metcal%20910-WW%20kolb%2010cc.f3d), ja päis koos süstlaga lukus: [Süstla päis ja süstal 10cc.f3d](S%C3%BCstla%20p%C3%A4is%20ja%20s%C3%BCstal%2010cc.f3d). Fusionis sobib, aga päris printeri lõtk on sinu kontrollida. Tihendit ei ole, ja selle teed sina, O-rõngaga komplektist ja arvutatud soonega. Kui tahad oma päise teha, on eeskujuks eelmise aasta Metcali päis: [Metcal 910-3RHB.f3d](Metcal%20910-3RHB.f3d). Päis peab vastu pumba täie rõhu. Tulemus: survekatse ja `docs/leak_test.csv`, enne ja pärast sadat klapi lülitust.

**5. Katse** — prügitops ja otsiku parkimiskoht ruudustikku. Siis kuiv läbijooks: mine doseerimise asendisse, tõsta klaas, mine kõvendamise asendisse, pane klaas ära, 20 korda. Tulemus: `docs/cycle_test.csv`, mitu kahekümnest läks puhtalt läbi, ja kas nihked kehtivad pärast tööriista mahavõtmist.

### Kuidas töö käib

Repo ja töökord on Laborist 1 olemas ja samad. Tervet töölehte üle kopeerida ei ole vaja — too oma repo juurde see, mida vaja, ja täida `README.md` oma numbrite ja otsustega. Iga print on uus versioon; vana jääb alles. Ei tulnud esimesel korral välja, tule homme tagasi ja proovi uuesti.

Esimesel päeval uusi osi ei ole — ehita sellest, mis riiulil on. Selles laboris vaiku süstlas ei ole: katsed käivad õhu ja seebiveega. LED-i juures on kõigil kaitseprillid 405 nm jaoks ees.

### Komponendid selle labori jaoks

Tellimus läheb välja 06.11.26 ja jõuab kohale enne kaitsmist. Valmis nimekirja ei ole: meeskond paneb tellimuse ise kokku faili `docs/bom.md`, iga rea juures üks lause, milline osa seda küsib. LED-i ja draiveri jaoks läheb tabelisse Mouseri tootekood.

### Kaitsmiseks on vaja

**Ainult git repositooriumi link, tag `3d-print-lab3`.** Kaustas `3d-print/lab3/` peab olema:
- lähtefailid, STL ja `.3mf` iga prindi kohta
- `docs/`: `tool_layout.md`, `tool_offsets.md`, `leak_test.csv`, `cycle_test.csv`, `bom.md`, fotod
- Täidetud `README.md` koos arenduspäevikuga
- `AGENTS.md` uuendatud

Kaitsmine on lihtne suuline 15 minuti jutuajamine. Vahetad süstla ühe käega. Robot teeb ühe kuiva ringi: läheb doseerimise asendisse, tõstab klaasi, läheb kõvendamise asendisse, paneb klaasi ära. Näitad paberil, kuhu lambi laik langeb. Avad oma arenduspäeviku. Umbes viis küsimust selle kohta, kuidas sa selle tegid. Kaitsta saab nii mitu korda, kui vaja.

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — parameetritega tööriist, klapi kinnituse adapter ja lõpuni tehtud süstla päis koos sisse modelleeritud osadega, prügitopsi ja parkimiskoha hoidikud, STL ja 3MF iga prindi kohta, peatuse kõrgused 3MF-is | 5 p |
| Analüüs — osade mõõdud ja kaalueelarve, õhu skeem, klapi asukoha valik, klambri paindumine Labori 1 numbri vastu, lambi koonus, O-rõnga soone arvutus, survekatse ja lekkekatse tabel, neli nihet | 5 p |
| Prototüüp — tööriist roboti küljes alla 500 g koos täis süstla ja klaasiga, süstal vahetub ühe käega, lamp tabab liimi kohta ja mitte otsikut, süstla haru peab rõhku, 20 kuiva ringi ilma haakumata | 5 p |
| Dokumentatsioon — README, arenduspäevik, `tool_layout.md`, `tool_offsets.md`, `leak_test.csv`, `cycle_test.csv`, `bom.md`, AGENTS.md | 5 p |
| **Kokku** | **20 p** |

### Täielik tööleht

📎 [Link täielikule töölehele](https://github.com/KKallas/Narva-subjects/blob/main/EST/2026-27/3D%20printing/3D%20Printing%20%5BLab%203%5D%20EST.md)

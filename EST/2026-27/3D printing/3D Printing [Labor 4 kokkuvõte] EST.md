## 3D printimine ja CAD: Labor 4 — Üks detail paremaks, kolmel moel

**Maht:** 30 tundi | **Hindamine:** 20 punkti | **Meeskonnatöö:** 3-liikmelised meeskonnad | **Välja antud:** 17.11.26 | **Tellimise kuupäev:** 27.11.26 | **Esimene kaitsmine:** 10.12.26, veebis

### Mida teete

Laua peal on nüüd kolme labori jagu detaile, ja neid on nädalaid kasutatud: hoidikud ruudustikus Laborist 2, tööriist, klapi kinnitus ja süstla päis Laborist 3. Iga detail joonistati üks kord ja prinditi kohe, kui ta töötas. Keegi ei küsinud, kas ta võiks olla kergem, kiirem printida või kauem vastu pidada.

Selles laboris võtad ühe neist detailidest ja teed ta **ühe mõõdiku järgi paremaks**. Mõõdikuid on neli ja valid ühe: **prindiaeg** sama tugevuse juures, **tugevus** sama prindiaja juures (±5 %), **kaal** sama tugevuse juures, või **kasutuskorrad**, enne kui mõõdetud omadus läheb tolerantsist välja.

Ja teed seda **kolmel moel**: **originaal**, nii nagu ta on; **käsitsi ümber tehtud**; ja **generatiivne disain** Fusionis, kus kinnituskohad, koormused ja keelualad on samad ja kuju otsib arvuti. Kõik kolm lähevad enne printimist läbi simulatsiooni, kõik kolm prinditakse ja kõik kolm läbivad sama katse roboti peal. Vastus on ühele küsimusele: **kas sellise detaili puhul on käsitsi tehtud disain parem kui generatiivne, ja miks?**

Viis osa:

**1. Vali detail ja mõõdik** — detail, mille paremaks tegemine midagi päriselt muudab, ja üks mõõdik. Koormus ühe lausega: kust jõud tuleb, mis suunas ja kui suur, mõõdetud, mitte oletatud. Tulemus: detail, mõõdik ja põhjus kirjas esimesel päeval.

**2. Originaal ja katse** — enne, kui midagi ümber joonistad. Originaali prindiaeg, mass, tugi, orientatsioon, nõrk koht ja koht, kus materjal ei kanna midagi. Katse on sama kõigile kolmele versioonile: rakis, jõu suund, roboti kiirus ja mis on "katki" või "tolerantsist väljas". Proovi ta originaali peal läbi. Tulemus: `docs/analysis_original.md` ja originaali tulemus kolme eksemplariga.

**3. Kaks uut versiooni** — mõlemal täpselt samad liidesed kui originaalil. Käsitsi versioon samas Fusioni failis: ribid sinna, kust jõud läbi käib, seinad otsiku laiuse kordsed, kaldserv toe asemel, polt kannab tõmmet ja plast ainult survet. Generatiivne versioon: mis peab jääma, kuhu materjali panna ei tohi, koormused varuteguriga 2 ja tootmise piirangud. Vali üks tulemus mõõdiku järgi ja tee temast keha, mis prindib ilma tugede metsata. Tulemus: kaks uut versiooni Fusionis ja generatiivse uuringu seadistus.

**4. Simulatsioon enne printi** — kõik kolm versiooni sama koormuse, samade kinnituste ja sama võrgusilma suurusega. Ennustus on kirjas enne, kui esimene eksemplar printerist tuleb: kus ta murdub ja millise jõu juures. Simulatsioon arvestab materjali, mis on igas suunas ühesugune; prinditud detail ei ole, ja Labori 1 suhe ütleb, kui palju. Siis iga versioon kolmes asendis läbi slaiseri. Tulemus: simulatsiooni pildid, ennustus kuupäevaga ja üheksa orientatsiooni tabel.

**5. Katse ja võrdlus** — iga versioon prinditud kolm korda samal printeril ja sama filamendiga, kaalutud ja mõõdetud. Katse käib segamini järjekorras, mitte esimesena kõik originaalid. Võitja läheb lauale, ja kõik, mis temast sõltub, mõõdetakse üle. Tulemus: `data/test.csv`, võrdlustabel ennustusega mõõdetu kõrval, ja üks lõik vastusega, kas käsitsi oli parem kui generatiivne ja miks.

### Kuidas töö käib

Repo ja töökord on Laborist 1 olemas ja samad. Tervet töölehte üle kopeerida ei ole vaja — too oma repo juurde see, mida vaja, ja täida `README.md` oma numbrite ja otsustega. Iga print on uus versioon; vana jääb alles. Ei tulnud esimesel korral välja, tule homme tagasi ja proovi uuesti.

Esimesel päeval uusi osi ei ole — ehita sellest, mis riiulil on. Materjal on PLA, ja kõik versioonid prinditakse ühel ja samal printeril. Laud teeb samal ajal Andmehõive L4 tsükleid originaaldetailidega: lepi kokku, millal detail vahetatakse. Tõmbekatsel on kaitseprillid ees ja robot tõmbab 20 % kiirusel.

### Komponendid selle labori jaoks

Tellimus läheb välja 27.11.26 ja jõuab kohale enne kaitsmist. Valmis nimekirja ei ole: meeskond paneb tellimuse ise kokku faili `docs/bom.md`, iga rea juures üks lause, milline osa seda küsib. Tellimine käib ühisest tellimistabelist: [https://moodle.ut.ee/mod/url/view.php?id=1535601](https://moodle.ut.ee/mod/url/view.php?id=1535601).

### Kaitsmiseks on vaja

**Ainult git repositooriumi link, tag `3d-print-lab4`.** Kaustas `3d-print/lab4/` peab olema:
- kolm versiooni lähtefailidena (Fusioni disainid arhiivina, `.f3d` või `.f3z`), STL ja `.3mf` iga prindi kohta
- `notebooks/` orientatsiooni ja võrdlusega
- `data/test.csv`
- `docs/`: `analysis_original.md`, simulatsiooni pildid, `bom.md`, fotod
- Täidetud `README.md` koos arenduspäevikuga
- `AGENTS.md` uuendatud

Kaitsmine on lihtne suuline 15 minuti jutuajamine. Näitad kolme versiooni kõrvuti ja võrdlustabelit. Robot teeb ühe katse otse. Ütled, kumb võitis, käsitsi või generatiivne, ja miks, ja kus simulatsioon eksis. Avad oma arenduspäeviku. Umbes viis küsimust selle kohta, kuidas sa selle tegid. Kaitsta saab nii mitu korda, kui vaja.

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — kolm versiooni Fusionis samade liidestega, generatiivse uuringu seadistus, simulatsioon, slaiseri projektid, STL ja 3MF iga prindi kohta | 5 p |
| Analüüs — originaali analüüs, koormus mõõdetud, ennustus enne printi, üheksa orientatsiooni tabel, võrdlustabel keskmise ja vahemikuga, ennustus mõõdetu kõrval | 5 p |
| Prototüüp — kõik kolm versiooni prinditud ja katsetatud sama katsega, võitja laual ja kõik temast sõltuv töötab | 5 p |
| Dokumentatsioon — README, arenduspäevik, `analysis_original.md`, `test.csv`, `bom.md`, AGENTS.md | 5 p |
| **Kokku** | **20 p** |

### Täielik tööleht

📎 [Link täielikule töölehele](https://github.com/KKallas/Narva-subjects/blob/main/EST/2026-27/3D%20printing/3D%20Printing%20%5BLab%204%5D%20EST.md)

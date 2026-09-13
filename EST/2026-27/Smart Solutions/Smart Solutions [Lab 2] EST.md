## Nutikad Lahendused: Labor 2 — Jaam internetis ja kaamera laua kohal

**Töömaht:** 28 tundi | **Hindamine:** 20 punkti | **Meeskond:** 3 tudengit | **Välja antud:** 07.10.26 | **Tellimise kuupäev:** 16.10.26 | **Esimene kaitsmine:** 27.10.26, veebis

### Kuidas see dokument töötab

* Repo ja töökord on Laborist 1 olemas ja samad.
* Too sellest dokumendist oma projekti repo juurde see, mida vaja: selle labori kaust, `README.md`, kuhu lähevad su enda numbrid, otsused ja KAARDISTA ISE vastused, ja failid, mida kontrollnimekiri nimetab. Tervet dokumenti üle kopeerida ei ole vaja.
* Skeemid ja simulatsioonid lähevad dokumenti pildina, pildi juurde link elavale failile, et teine saaks selle lahti teha ja edasi muuta.

### Eesmärk

Laboris 1 sai jaam robotiga rääkima ja Atom sai oma lehe. Kõik see töötab ainult siis, kui sa oled laboris.

Su sülearvutil ei ole aadressi, mille peale keegi väljastpoolt saaks ühendust võtta. Labori võrk annab talle privaatse aadressi — samasuguseid aadresse on internetis miljoneid ja ükski marsruuter ei tea, milline neist sinu oma on. Sisse ei saa. Aga välja saab: sinu arvuti võtab ise ühendust ja vastus tuleb tagasi sama teed. Kogu see labor on ehitatud selle asümmeetria peale.

Vahele tuleb **droplet**: väike Linuxi server, millel on päris avalik aadress ja päris nimi. Jaam võtab ise dropletiga ühendust ja hoiab seda üleval. Droplet suunab brauseri päringud sedasama teed tagasi jaamale. Nii saab lehe lahti telefonist, mis ei ole labori võrgus.

Ja laua kohale tuleb **kaamera**, sest robotit, mida sa ei näe, sa ei käsuta. Kui robot teeb kodust vaadates midagi ootamatut, on sul kaks võimalust: sõita laborisse ja loota, et ta teeb seda uuesti, või vaadata pilti. Teine on odavam ja tihti ainus, mis töötab.

Labori 1 lubadus kehtib edasi: **iga riistvara, mis Atomi külge tuleb, saab oma seaded ja testinupu sellele samale lehele.** Andmehõive Labor 2 paneb Atomi külge rõhuanduri koos astmega. Selle seaded ja test lähevad Atomi lehele, mitte uude kohta.

Selles laboris on kolm asja:

1. **Droplet.** Server, domeen, võtmed, HTTPS.
2. **Relee.** Jaam võtab ise ühendust välja. Labori 1 leht avaneb telefonist mobiilse andmesidega. Ja mis juhtub, kui ühendus katkeb keset liigutust.
3. **Kaamera ja Atomi leht.** Laud on näha. Rõhuandur saab Atomi lehele oma seaded ja testinupu.

Esimesel päeval uusi osi ei ole. Ehita sellest, mis riiulil on, ja kirjuta puuduv tellimuseks, mis läheb välja 16.10.

*See on elav dokument. Uuenda eesmärke, kui need töö käigus muutuvad — uued teadmised teevad vanad eesmärgid vahel mõttetuks. Mõte on hoida meeskond kogu aeg sihil, et ei eksitaks detailide metsa ja põhiprobleem ei jääks lahendamata.*

**KAARDISTA ISE — eesmärk nii, nagu ta tegelikult välja tuli.**

### Kontrollnimekiri

**Peab olema tehtud**

- [ ] Droplet töötab. SSH võtmega sisse, paroolisisselogimine keelatud, tulemüür lahti ainult nendel portidel, mida sa päriselt kasutad.
- [ ] Domeen viitab dropletile ja leht käib HTTPS-i peal.
- [ ] Relee üleval: Labori 1 jaama leht avaneb telefonist, mille WiFi on välja lülitatud.
- [ ] Latentsus mõõdetud: 30 vajutust labori võrgus ja 30 üle interneti.
- [ ] Ühenduse katkemine keset liigutust otsustatud, tehtud ja läbi proovitud.
- [ ] Kaamera näitab lauda, pilt käib sama relee kaudu ja sama parooli taga.
- [ ] Kaamera viide, kaadrisagedus ja ribalaius mõõdetud; juhtimise latentsus mõõdetud uuesti, kaamera töötamise ajal.
- [ ] Rõhuanduri seaded ja testinupp Atomi lehel, `docs/atom_page.md` uuendatud.
- [ ] Ohutuskokkulepe kirjas ja kõigil meeskonnaliikmetel loetud.
- [ ] Tellimus 16.10 failis `docs/bom.md`.
- [ ] Repo ja arenduspäevik täidetud, tag `smart-solutions-lab2`.

**KAARDISTA ISE — kuupäevad ja sinu enda sammud.**

### Sisendid

* Laborist 1: jaam, MG400 baaspakett, `data/positions.json`, Atomi püsivara ja leht, aadressiplaan.
* Õppejõult: droplet ja domeen. Neid meeskond ise ei telli — kursuse peale on üks droplet ja üks nimi, õppejõu konto pealt. Sina saad ligipääsu ja oma alamdomeeni või alamtee.
* Riiulilt: veebikaamera, USB pikenduskaabel.
* Andmehõive L2-st: rõhuandur koos astmega ja kalibratsioonikonstandid, mis Atomi lehele lähevad.
* 3D printimise L2-st: kinnitus kaamerale — töölaud on 16 mm vardad, nii et ka kaamera käib varda otsa; ja laud, mida kaamera näeb.

### Vahendid

1. Labori 1 jaam ja Atom
2. Digital Ocean droplet, väikseim, Ubuntu
3. Domeen õppejõult
4. SSH ja SSH võtmed
5. Tunnel jaama ja dropleti vahel: WireGuard või SSH pöördtunnel, sinu valik
6. Pöördproksi, mis oskab sertifikaadi ise võtta ja ise uuendada
7. Veebikaamera, USB pikenduskaabel
8. Telefon mobiilse andmesidega, millega väljastpoolt testida
9. Python 3, Flask; git; draw.io

*Kui plaan muutub, uuenda ka vahendeid, või tee draw.io skeem, mis näitab, kuidas asjad omavahel töötavad.*

**KAARDISTA ISE — mida sa päriselt kasutasid.**

### Taustainfo

* **Droplet** — mis see on ja kuidas üks püsti panna
  [https://docs.digitalocean.com/products/droplets/](https://docs.digitalocean.com/products/droplets/)
* **SSH võtmed.** Parool internetis olevale serverile on halb mõte: seda proovitakse ära arvata pidevalt ja automaatselt, mitte sellepärast, et keegi sind otsib, vaid sellepärast, et proovitakse kõiki. Võti on nii pikk, et seda ei arvata. Genereeri võti, pane avalik pool serverisse, keela paroolisisselogimine ära.
* **WireGuard** — tunnel kahe masina vahele, väike ja kiire
  [https://www.wireguard.com/quickstart/](https://www.wireguard.com/quickstart/)
* **Caddy** — pöördproksi, mis võtab HTTPS-sertifikaadi ise ja uuendab seda ise
  [https://caddyserver.com/](https://caddyserver.com/)
* **Let's Encrypt** — tasuta sertifikaadid, mille peale eelmine punkt ehitatud on
  [https://letsencrypt.org/](https://letsencrypt.org/)
* **Flask ja voogedastus** — kuidas üks marsruut saadab pilti lõputult, ühe vastuse sees
  [https://flask.palletsprojects.com/en/stable/patterns/streaming/](https://flask.palletsprojects.com/en/stable/patterns/streaming/)
* **MJPEG.** Lihtsaim videovoog, mis brauseris ilma midagi installimata töötab: järjest JPEG pilte ühes ja samas vastuses. Kliendi pool on üks `<img>` silt. Kvaliteedi ja kaadrisageduse eest maksad ribalaiusega, ja seda ribalaiust jagad sa juhtimisega.
* **ESP32-Image-Server** — Atomi leht, mille peale Laboris 1 ehitasid
  [https://github.com/KKallas/ESP32-Image-Server](https://github.com/KKallas/ESP32-Image-Server)
* **NAT ja privaatsed aadressid.** Võta Labori 1 aadressiplaan lahti ja võrdle seda dropleti aadressiga. Üks neist on selline, mida on internetis üks; teisi on miljoneid.

*Lisa siia oma allikaid ja kasulikku infot, mis aitaks sul projektist aru saada ka aastaid hiljem, kui selle uuesti lahti teed.*

**KAARDISTA ISE — sinu allikad.**

### Osad

#### 1. Droplet

Väikseim droplet, Ubuntu. Kolm asja tehakse enne kõike muud, mitte pärast:

* SSH võti sisse ja paroolisisselogimine välja.
* Tulemüür püsti nii, et lahti on ainult need pordid, mida sa päriselt kasutad. Iga lahtise pordi kohta pead oskama öelda, mis seal taga on.
* Uuendused peale.

Siis domeen. Õppejõud ostab ühe nime ja iga meeskond saab sealt oma alamdomeeni või alamtee. Pane see dropleti aadressi peale viitama ja oota ära, kuni ta tööle hakkab — DNS ei ole hetkeline ja esimene kord, kui sa seda ootad, tundub see nagu viga.

Siis HTTPS. Pöördproksi, mis võtab sertifikaadi ise. Ilma selleta käib su parool üle interneti lugemiskõlblikult, ja "aadressi ei tea keegi" ei ole parool.

Ja üks asi, mida teha kohe, mitte hiljem: **tee server üks kord meelega uuesti.** Kustuta droplet ära ja ehita uus, ainult oma märkmete järgi. Kui märkmetest ei piisa, said sa just teada, mis neist puudu on — ja said selle teada praegu, kell kaks päeval, mitte siis, kui midagi päriselt katki läheb.

Kirjuta üles: dropleti suurus ja asukoht, aadress, domeeninimi; millised pordid on lahti ja mis iga ühe taga on; kuidas sa sisse saad; kaua võttis uuesti ehitamine ja mis märkmetest puudu oli.

#### 2. Relee

Vali üks: WireGuardi tunnel jaama ja dropleti vahel, SSH pöördtunnel, või oma väike releeteenus. Kõik kolm töötavad. Kirjuta üles, miks sina selle valisid ja mis sulle teise juures ei meeldinud — kolme aasta pärast on see ainus rida, mis sind aitab.

Siis pane Labori 1 jaama leht dropleti kaudu käima. Test on lihtne ja seda ei saa võltsida: võta telefon, **lülita WiFi välja**, ava leht mobiilse andmesidega. Kui leht tuleb ja nupud liigutavad robotit, on relee olemas. Kui sa testid labori WiFi pealt, ei ole sa midagi testinud.

Siis mõõda. 30 nupuvajutust labori võrgus ja 30 üle interneti. Iga vajutuse kohta aeg vajutusest liigutuseni. Keskmine ja maksimum mõlemas. Vahe ei ole ainult number: ta ütleb sulle, kas kaugjuhtimine on selle süsteemi jaoks üldse mõistlik või ainult vaatamiseks.

Ja siis kõige tähtsam osa selles laboris. **Ühendus katkeb keset liigutust.** See juhtub, ja mitte harva — WiFi kukub, tunnel jookseb kokku, droplet käib ümber. Laboris 1 on sul see reegel juba olemas: kui rida ei tule 500 ms jooksul, pump seisab. Nüüd on sama küsimus suuremas mõõtkavas, ja vastust ei saa oletada.

Otsusta, mis juhtub. Tee see ära. Ja tõmba siis kaabel välja keset liigutust, et näha, kas see päriselt nii läks. Kolm korda, sest esimene kord võib vedada.

Kirjuta üles: milline relee ja miks; lehe aadress; ekraanipilt telefonist, kus on näha, et WiFi on väljas; latentsuse tabel, labor ja internet, keskmine ja maksimum; mis juhtub ühenduse katkemisel ja mis päriselt juhtus, kui sa kaabli välja tõmbasid.

#### 3. Kaamera ja Atomi leht

Kaamera vaatab lauda: robot, kinnitus, detail. Kaadris peab olema nii palju, et sa kodust vaadates saaksid vastata küsimusele "mis seal päriselt juhtus". Liiga lähedalt näed sa ühte pesa ja mitte seda, et käsi läks mujale.

Pilt käib sama relee kaudu ja sama parooli taga, mitte eraldi lahtise aadressi peal. Kaamera, mis on lahti kõigile, on kaamera sinu klassiruumis, mis on lahti kõigile.

Mõõda kolm asja: kui palju aega jääb sündmuse ja selle nägemise vahele, mitu kaadrit sekundis tuleb, ja kui palju ribalaiust see sööb. Siis mõõda **juhtimise latentsus uuesti, kaamera töötamise ajal.** Kaamera ja juhtimine käivad sama toru kaudu ja kaamera on neist kaugelt ahnem. Kui latentsus kasvas, on sul valida: väiksem pilt, vähem kaadreid, või aeglasem juhtimine. Vali ja kirjuta põhjus välja.

Atomi leht: Labori 1 lubadus. Andmehõive Labor 2 pani Atomi külge rõhuanduri koos astmega. Sellele lehele tulevad nüüd juurde anduri seaded — kalibratsioonikonstandid, mis Andmehõives välja tulid — ja testinupp, mis näitab korraga toorest ADC lugemit, pinget ja kPa. Kolm numbrit kõrvuti sellepärast, et kui üks neist on vale, näed sa kohe, kumb pool valesti on: andur või valem. Uut lehte ei tehta.

Kirjuta üles: foto sellest, mida kaamera näeb; viide millisekundites, kaadreid sekundis, ribalaius; juhtimise latentsus kaameraga ja ilma; Atomi lehe seadete ja testide nimekiri failis `docs/atom_page.md`.

**KAARDISTA ISE — vastused.** Iga osa kohta: numbrid, ühikud, kus fail on. Tegemata asja kohta üks rida, miks.

### Ohutus

Selles laboris muutub ohutus teistsuguseks, kui ta seni oli. Seni oli robot ruumis, kus sa ise olid. Nüüd ta enam ei ole.

* **Robot, mille juurde saab internetist, saab liikuma panna keegi, keda ruumis ei ole.** Enne, kui relee esimest korda püsti läheb, lepite meeskonnas kokku ja kirjutate faili: kes tohib kaugelt käsu anda, ja mida ta peab enne seda tegema.
* **Hädastopp on roboti alusel.** Kodus seda nuppu ei ole. Seega: kaugelt ei jooksutata midagi, mille ajal ruumis ei ole inimest, kes hädastoppi ulatub. Kui ruumis ei ole kedagi, on robot välja lülitatud, mitte ainult keelatud.
* **Kaamera ei ole mugavus, vaid ohutusvahend.** Kui pilti ei tule, ei käsutata.
* Üks ohutusseade selles ruumis töötab ka siis, kui kedagi kohal ei ole, ja tasub teada, milline. MG400 istub negatiivse püramiidaluse peal ja tema all on lüliti: kui robot millegi vastu läheb, tuleb ta pesadest välja, lüliti vabaneb ja kõik jääb seisma. Tarkvara seda ei tee ja internet seda ei takista. Aga tagasi pesadesse paneb ta ainult inimene — ehk kaugelt sa pärast seda enam midagi käima ei pane. Kirjuta üles, kuidas sa kaugelt aru saad, et see juhtus: mille pealt sa seda lehel või kaameras näed.
* Parool ja HTTPS. Aadress, mida keegi ei tea, ei ole parool — ja aadresse skaneeritakse.
* Ühenduse katkemine keset liigutust on läbi mängitud enne, kui robot kaugelt esimest korda liigub. Mitte pärast.
* MG400 reeglid Laborist 1 kehtivad edasi: käed ei ole laual, kui robot on sisse lülitatud; uue jada esimene jooks 20 % kiirusel; käsklusi saadab robotile korraga ainult üks programm.
* Kui Atom laborist välja läheb, vaheta WiFi parool vaikimisi omast ära.

### Komponendid selle labori jaoks

Droplet ja domeen on kursuse peale ühed ja käivad õppejõu kontolt. Neid sa oma tellimusse ei pane.

Sinu tellimusse läheb see, mis laua juures puudu on. Tellimus läheb välja 16.10.26, faili `docs/bom.md`, iga rea juures üks lause, milline osa seda küsib.

Mõtle näiteks: kas kaamera on olemas ja kas ta näeb piisavalt laia kaadrit sellelt kauguselt, kuhu ta mahub; kas USB kaabel ulatub sinna, kuhu vaja; ja mille küljes kaamera kinni on, kui ta laua serva ei mahu.

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — dropleti seadistus kirjas ja korratav, relee konfiguratsioon, kaamera voog, Atomi lehe uued osad | 5 p |
| Analüüs — latentsus labori võrgus ja üle interneti, kaamera viide, kaadrisagedus ja ribalaius, latentsus kaameraga ja ilma | 5 p |
| Prototüüp — leht avaneb telefonist mobiilse andmesidega HTTPS-i peal, kaamera näitab lauda, katkenud ühendus viib süsteemi ohutusse olekusse | 5 p |
| Dokumentatsioon — README, arenduspäevik, `atom_page.md`, ohutuskokkulepe, `bom.md`, AGENTS.md | 5 p |
| **Kokku** | **20 p** |

### Kaitsmine

Link git repole, tag `smart-solutions-lab2`.

Kaitsmine on lihtne suuline 15 minuti jutuajamine. Avad oma telefonist mobiilse andmesidega jaama lehe, liigutad robotit ja näed seda kaameras, ja näitad, mis juhtub, kui ühendus katkeb. Avad oma arenduspäeviku. Õppejõud küsib umbes viis küsimust selle kohta, kuidas sa selle tegid. Kui esimesel korral ei õnnestu, tuled uuesti.

Repos on kaustas `smart-solutions/lab2/`:

* `src/` jaama kood koos relee poolega ja kaamera vooga
* `firmware/` Atomi PlatformIO projekt uuendatud lehega
* `docs/`: dropleti ehitus samm-sammult, relee skeem draw.io-s, `atom_page.md`, ohutuskokkulepe, latentsuse CSV-d, ekraanipildid ja fotod, `bom.md`
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
* Andmehõive L2: Atomi leht, kust anduri lugemit, seadeid ja testi näeb.
* 3D printimine L2: kaamera, mille pealt näeb, kas robot tabab pesa, ka siis, kui sa ise laual ei ole.
* Nutikad Lahendused L3: droplet ja relee, mille peale järgmine kiht ehitatakse.

**KAARDISTA ISE, lõpus.**
* Git repo ja tag:
* Numbrid, mille see labor andis, ühikutega:
* Mida me teeksime teisiti:
* Mida järgmine labor peaks enne alustamist teadma:

### Tagasiside

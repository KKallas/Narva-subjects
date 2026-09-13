## Andmehõive: Labor 2 — Op-amp, lihtne aga keeruline

**Maht:** 32 tundi | **Hindamine:** 20 punkti | **Meeskonnatöö:** 3-liikmelised meeskonnad | **Välja antud:** 07.10.26 | **Tellimise kuupäev:** 16.10.26 | **Esimene kaitsmine:** 27.10.26, veebis

### Mida teete

Laboris 1 läks andur otse ADC-sse ja vahel ei olnud midagi. See oli meelega. MPX5700AP väljund liigub pumba kogu ulatuses ainult 0,40 … 1,56 V — kolmandik ADC vahemikust, üks ADC samm 125 Pa. Nüüd ehitate vahele astme, mis lahutab nihke maha ja võimendab signaali ADC vahemikku täitma, ja mõõdate ära, mis sellest muutus.

Aste ei ole eesmärk. Eesmärk on **poolik haare**: napp on klaasil, aga serv jäi lahti, pump jääb lühitsüklisse ja kast näeb väljastpoolt välja nagu töötav kast — rõhk on vahemikus, ekraan ütleb, et hoiab. Poolik haare ei erine korralikust haardest rõhu *väärtuse*, vaid rõhu *languse kiiruse* poolest, ja see vahe kaob 125 Pa sammu alla. Selle otsa peal ripub polükarbonaatklaas: "vaakum on käes" ei ole otsus, mille peale tõsta — otsus on "vaakum püsib".

Neli osa:

**1. Mis on puudu** — Labori 1 CSV ja spekter lahti. Mitu volti anduri väljund liigub, mitu protsenti see on ADC vahemikust, mitu Pa on üks ADC samm. Siit tuleb otsus, mida aste peab tegema, ja esimene siht 0,2 … 3,3 V koos võimendusega. Tulemus: numbrid, mille vastu kõike edasist mõõdetakse.

**2. Aste, esimene versioon** — Falstadis enne, maketeerimisplaadil pärast. Kaks tingimust, kaks võrrandit, takistid tulevad sealt. Müraallikas Falstadis näitab, miks siin üldse op-amp on. Plaadil mõõdetakse multimeetriga kolmes rõhus ja skoobiga kahe kanaliga. Tulemus: takistid, viitepinge, mõõdetu arvutatu kõrval — **ja parandada ei tohi veel midagi.**

**3. Parandus** — mõõdetu ei lähe arvutatuga kokku, eriti otstes. Selgita, miks: kus on op-ampi tegelikud piirid, mida ADC otstes teeb, ja miks Falstad seda ei näidanud. Siis arvuta siht ümber, vaheta takistid ja mõõda uuesti. Tulemus: uued numbrid vanade kõrval ja üks lause selle kohta, kuidas sa edaspidi sihtvahemikku valid.

**4. Vahe** — sama pumba impulss logitakse mõlemas konfiguratsioonis, `config` veerg CSV-s. Spektrid kõrvuti Labori 1 omadega, Pa ühe sammu kohta ja SNR enne ja pärast. Siis Labori 1 pumbajuhtimine uue signaali pealt läbi, ja neljas olukord, mida Laboris 1 ei olnud: poolik haare. Tulemus: mitu sekundit kulub, enne kui poolik haare on korralikust eristatav — mõlema signaaliga.

### Kuidas töö käib

Repo ja töökord on Laborist 1 olemas ja samad. Tervet töölehte üle kopeerida ei ole vaja — too oma repo juurde see, mida vaja, ja täida `README.md` oma numbrite ja otsustega. Midagi ei kustutata: vale number jääb, parandus tuleb tema alla. Skeemid ja simulatsioonid lähevad dokumenti pildina, pildi juurde link elavale failile. Ei tulnud esimesel korral välja, tule homme tagasi ja proovi uuesti.

Esimesel päeval uusi osi ei ole — ehita sellest, mis riiulil on.

### Komponendid selle labori jaoks

Tellimus läheb välja 16.10.26 ja jõuab kohale enne kaitsmist. Valmis nimekirja ei ole: meeskond paneb tellimuse ise kokku faili `docs/bom.md`, iga rea juures üks lause, milline osa või number seda küsib.

### Kaitsmiseks on vaja

**Ainult git repositooriumi link, tag `data-acquisition-lab2`.** Kaustas `data-acquisition/lab2/` peab olema:
- `src/` püsivara ja logijaga, `data/` CSV failidega, `notebooks/` spektrite ja SNR-iga
- `docs/`: skeemi foto, ostsilloskoobi pildid, Falstadi eksport, `pump_control.md` uuendatud, `bom.md`
- Täidetud `README.md` koos arenduspäevikuga
- `AGENTS.md` uuendatud

Kaitsmine on lihtne suuline 15 minuti jutuajamine. Näitad ostsilloskoobil anduri väljundit ja astme väljundit korraga sama impulsi peal, ütled esimese versiooni pealt, kus ta katki läks ja miks, näitad, kuidas pump uue signaaliga seisma jääb, ja avad oma arenduspäeviku. Umbes viis küsimust selle kohta, kuidas sa selle tegid. Kaitsta saab nii mitu korda, kui vaja.

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — Atomi püsivara mõlema konfiguratsiooniga, logija `config` veeruga, CSV failid | 5 p |
| Analüüs — Pa ühe sammu kohta enne ja pärast, spektrid kõrvuti, SNR, pumbajuhtimise uued numbrid | 5 p |
| Prototüüp — aste plaadil mõõdetud kolmes rõhus enne ja pärast parandust, lõplik väljund mõlemas otsas lineaarne, pumbajuhtimine töötab uue signaaliga | 5 p |
| Dokumentatsioon — README, arenduspäevik, Falstadi eksport, `pump_control.md` uuendatud, `bom.md`, AGENTS.md | 5 p |
| **Kokku** | **20 p** |

### Täielik tööleht

📎 [Link täielikule töölehele](https://github.com/KKallas/Narva-subjects/blob/main/EST/2026-27/Data%20Acquisition/Data%20Acquisition%20%5BLab%202%5D%20EST.md)

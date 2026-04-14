# Prototüüpimine — plaan B: Dobot MG400 mosaiiklade

Ühe meeskonna projekt: ehita Dobot MG400 robotkäele töölaud ja tarkvara, mis võimaldab vaakumhaaratsi abil mosaiikkive automaatselt mustri järgi laotada.

Eesmärk: töötav mosaiigi ladumise süsteem — modulaarne töölaud + veebitarkvara + vaakumsüsteem.

### Süsteemi ülevaade

**Dobot MG400** on 4-teljeline lauapealne robotkäsi (tööraadius ~340 mm, korduvtäpsus ±0,05 mm). Roboti juhtimine käib üle TCP/IP — Dobot pakub oma API-t mille kaudu saab saata liikumiskäske, lugeda positsiooni ja juhtida I/O väljundeid (vaakumpump).

**Vaakumsüsteem:** vaakumpump + iminapp otsikus. Pump lülitatakse Doboti I/O väljundist. Iminapp peab hoidma kivi kogu liikumise ajal — kukkumine tähendab vale kivi positsiooni ja võimalikku purunemist.

**Töölaud:** tudengid projekteerivad ja ehitavad ise modulaarse töölaua MG400 ümber. Töölaud koosneb 100×100 mm moodulitest (PVC või polükarbonaat, CNC ruuteriga lõigatud). Moodulitel on aukude võrgustik 3D-prinditud hoidikute kinnitamiseks:
- **Kivihoidikud** — pesad kust robot kive võtab (magazine)
- **Tööala** — ala kuhu robot kive asetab (mosaiigi alus)
- **Referentspunktid** — teadaolevad positsioonid töölaua ja roboti koordinaatsüsteemide sidumiseks

**Andurid töölaual:**
- Kivi olemasolu andur (fotoelektriline või mehaaniline) — kas kivihoidikus on kive järel?
- Optiline andur tööalal — kas kivi on korrektselt asetatud?

**Tarkvara:**
- Python veebiserver (FastAPI)
- Veebiliides operaatorile:
  - **Mustri sisestamine:** kasutaja teeb telefoniga foto mosaiigist mida tahab laotada, või laeb üles pildi oma seadmest. Tarkvara teisendab pildi kivi-positsioonide kaardiks (pikslid → lähim kivi värv → koordinaadid).
  - Mustri eelvaade, ladumise käivitamine, protsessi jälgimine
- Dobot API klient: liikumiskäsud, I/O juhtimine, positsiooni lugemine
- Mustri generaator: pilt → pikslikaart → kivi värvi ja positsiooni kaart → roboti koordinaadid

### Kaitsmised

Kolm kaitsmist. Kaitsed **kõik tööd mis selleks hetkeks valmis on** — pole oluline milline verstapost, oluline on et töö on tehtud ja dokumenteeritud.

| Kaitsmine | Kuupäev | Mida |
|:---|:---|:---|
| 1. kaitsmine | **T 14.04 (online)** | V1: spetsifikatsioon + võtmetehnoloogia prototüüp |
| 2. kaitsmine | **T 26.05 (online)** | V2: integreeritud süsteem + V3: täisfunktsionaalne süsteem |
| 3. kaitsmine | **Kuupäev määratakse pärast 2. kaitsmist** | V4: tootmisvalmis süsteem, demonstratsioon |

---

## Tellimuste ajakava

Iga tellimus peab olema välja saadetud **vähemalt 10 päeva enne** vastavat kohtumist. Meeskond otsustab ise mida ja kust tellida. Eelarve **300 €**.

| Tellimus | Esitamise tähtaeg | Kohtumine |
|:---|:---|:---|
| 1. tellimus (CNC lõikus, andurid, iminapp, kivid) | **08.04** (10 päeva enne 18.04) | 3. kohtumine 18.04 |
| 2. tellimus (viimased komponendid) | **20.05** (10 päeva enne 30.05) | 4. kohtumine 30.05 |

---

## Verstapost 1: Spetsifikatsioon + võtmetehnoloogia prototüüp (26 t)

**Kohtumine: laupäev 21.03**

Kirjuta spetsifikatsioon ja testi kohe kõige kriitilisemad komponendid. Kuna esimene kohtumine (28.02) on juba möödas, on spetsifikatsioon ja esimesed testid ühendatud üheks verstapostiks.

### Tulemused — spetsifikatsioon

- [ ] Süsteemi ülevaade: mis süsteem on, mida teeb, kuidas töötab
- [ ] Funktsionaalsed nõuded (vähemalt 10, MoSCoW prioritiseeritud)
  - Kivi haaramine vaakumiga
  - Kivi transportimine hoidikust tööalale
  - Kivi asetamine täpse positsiooniga
  - Kivi olemasolu tuvastamine hoidikus
  - Mustri laadimine veebiliidesest (foto/pilt)
  - Ladumise protsessi jälgimine reaalajas
  - Vea tuvastamine (kivi kukkus, hoidik tühi)
  - Ladumise peatamine ja jätkamine
- [ ] Jõudluseesmärgid tabelina (paigutustäpsus, tsükliaeg ühe kivi kohta, maksimaalne kivi mass, vaakumhoidejõud)
- [ ] Töölaua mehhaaniline kontseptsioon (mõõtmetega, Fusion 360)
  - 100×100 mm moodulite paigutus MG400 tööulatuse piires
  - Kivihoidiku disain (magazine) — mitu kivi mahub, kuidas robot ligi pääseb
  - Tööala disain — kuhu kivid asetatakse, kuidas mosaiigi alus kinnitub
  - Referentspunktide asukohad koordinaatsüsteemi kalibreerimiseks
  - Moodulite kinnitusmehhanism (augud + 3D-prinditud klambrid)
  - Materjal: PVC või polükarbonaat, paksus, CNC lõikuse joonised
- [ ] Vaakumsüsteemi spetsifikatsioon
  - Iminappu tüüp ja suurus (vastavalt kivi massile)
  - Vaakumpumba parameetrid
  - Ühendus Doboti I/O väljundiga
- [ ] Elektriline plokkskeem (draw.io)
  - Dobot MG400 ↔ arvuti (Ethernet/WiFi)
  - Vaakumpump ↔ Dobot I/O
  - Andurid ↔ ESP32 (või Dobot I/O)
  - Toitehierarhia
- [ ] Tarkvaraarhitektuur
  - **Veebiserver (Python + FastAPI):**
    - REST API endpointid: pildi üleslaadimine, mustri genereerimine, ladumise käivitamine, staatuse päring, peatamine
    - Veebiliides: foto tegemine / pildi üleslaadimine → eelvaade → ladumise käivitamine, reaalajas protsessi vaade, andurite olek
  - **Dobot API klient:**
    - Ühenduse loomine ja haldamine (TCP/IP)
    - Liikumiskäsud: MovJ (liigespööre), MovL (lineaarne), Jump (tõste-liikumine)
    - I/O juhtimine: vaakumpumba sisse/välja lülitamine
    - Positsiooni tagasiside lugemine
  - **Mustri moodul:**
    - Pildi töötlemine: pilt → skaleerimine kivi suurusele → iga pikslibloki lähim kivi värv → positsioonide kaart
    - Mustri kirjelduse formaat (JSON: kivi positsioonid, värvid, järjekord)
    - Koordinaatide teisendus: mustri koordinaadid → roboti koordinaadid
    - Kivihoidiku koordinaadid: kust järgmine värvi kivi võtta
  - **Kommunikatsiooniprotokoll:**
    - API käskude formaat ja vastused
    - Veatöötlus (Dobot tagastab veakoodi → veebiliides näitab)
    - Staatusmuutuste logi
- [ ] Testimisplaan iga nõude jaoks
- [ ] BOM koos hindade ja tarnijatega
- [ ] Arenduse ajakava verstapostide 2–4 jaoks
- [ ] GitHub/GitLab milestones

### Tulemused — võtmetehnoloogia prototüüp

- [ ] **Dobot API side töötab:**
  - Python skript mis ühendub MG400-ga üle TCP/IP
  - Liikumiskäskude saatmine (MovJ, MovL, Jump)
  - Positsiooni tagasiside lugemine
  - I/O väljundi juhtimine (vaakumpump sisse/välja)
  - Testid: liiguta kätt 5 erinevasse punkti, loe positsioon tagasi
- [ ] **Vaakumi prototüüp töötab:**
  - Iminapp kinnitatud Doboti otsikusse
  - Vaakumpump ühendatud I/O kaudu
  - Testid: tõsta kivi üles, hoia 10 sekundit, aseta maha. Kas kivi jääb pidama?
  - Testi erinevate kivi pindadega (sile, kare, niiske)
- [ ] **Veebiliidese prototüüp:**
  - FastAPI server jookseb
  - Minimaalne veebileht: üks nupp → robot liigub ettemääratud punkti
  - Teine nupp → vaakum sisse/välja
  - Testid: latentsus nupuvajutusest liikumiseni
- [ ] **Töölaua prototüüp:**
  - Vähemalt 1 moodul (100×100 mm) valmis — kas käsitsi lõigatud testimiseks
  - 3D-prinditud kivihoidik (magazine) prototüüp: kas robot saab kivi kätte?
  - Testid: kas hoidiku positsioneerimine on piisavalt täpne?
- [ ] Spetsifikatsiooni uuendus: mis muutus pärast esimesi teste?
- [ ] **CNC lõikuse joonised valmis** — DXF failid töölaua moodulite jaoks
  - Aukude paigutus
  - Materjali valik ja paksus kinnitatud
  - Lõikuse tellimiseks valmis

### Teostatavusanalüüs (Jupyter Lab)

#### Analüüs 1: Töölaua kavandamine ja vaakumtesti tulemused

**Samm 1: Töölaua paigutusjoonis**

Joonista pealtvaade (käsitsi paberil, CAD-is või Jupyter Lab'is — oluline on tulemus, mitte tööriist). Joonisel peab olema:
- MG400 aluse asukoht
- Roboti tööulatus (max ~340 mm, min ~150 mm robotist)
- 100×100 mm moodulite paigutus koos funktsioonidega

Töölaud vajab vähemalt kolme funktsionaalset ala:
1. **Kivihoidikud** — pesad kust robot kive võtab. Mitu värvi? Mitu kivi ühte värvi mahub?
2. **Tööala** — ala kuhu robot mosaiiki ladub. Tööala suurus = suurim võimalik mosaiik.
3. **Kivi kinnitamine tööalal** — kuidas kivi pärast asetamist paigale jääb? Valikud: kahepoolne teip, liimikiht, 3D-prinditud pesad. Vali üks ja põhjenda.

**Põhiküsimus:** kas robot ulatub kõigi hoidikute ja tööala iga punktini? Seda ei pea arvutama — pane robot lauale, liiguta käsi äärmuspositsiooni ja mõõda joonlauaga. Märgi piirid joonisele.

**Samm 2: Kivihoidiku disainivalik**

Kaks põhivarianti:
- **Virn** (kived üksteise peal) — väike pind, aga iga kivi võtmine muudab Z-kõrgust. Robot peab teadma mitu kivi on järel, või kasutama andurit.
- **Rida** (kived kõrvuti pesades) — Z-kõrgus alati sama, aga võtab rohkem ruumi. Robot peab teadma milline pesa on tühi.

Kummalgi variandil on omad probleemid. Vali üks, põhjenda miks, ja kirjelda kuidas lahendad selle variandi nõrkust.

**Samm 3: Vaakumhaarats — praktiline test**

Vaakumjõudu pole mõtet arvutada — 5 g kivi hoidmiseks piisab igast mõistlikust iminappist kordades. Päris küsimus on: **kas iminapp üldse tihendab kivi pinnal?**

Testi:
1. Proovi iminappu vähemalt 3 erineva pinnaga kivil (sile, matt, kare/looduslik).
2. Hoia kivi iminappiga, liiguta käsitsi kiirelt küljele ja üles-alla. Kas kivi püsib?
3. Märgi tulemused:

| Kivi pind | Kas tihendab? | Kas püsib liikumisel? | Märkused |
|:---|:---|:---|:---|
| Sile glasuur | Jah / Ei | Jah / Ei | |
| Matt pind | Jah / Ei | Jah / Ei | |
| Kare/looduslik | Jah / Ei | Jah / Ei | |

Kui kare pind ei tihenda — kas on vaja teist tüüpi iminappu (pehmem silikoon), või tuleb kivi võtta ainult küljelt/alt?

#### Analüüs 2: Kulu-jõudluse kompromiss
Tuvasta üks disainiotsus kus seisad silmitsi kulu-jõudluse kompromissiga. Näiteks: PVC vs. polükarbonaat töölaua materjalina, või erinevat tüüpi iminappude võrdlus. Esita analüüs: variant A kirjeldus/kulu/jõudlus, variant B kirjeldus/kulu/jõudlus, otsus ja põhjendus.

#### Analüüs 3: Tehnoloogiauuring
Leia 3 sarnast projekti (Dobot pick-and-place, mosaiigi robotid, vaakumhaaratsi süsteemid). Analüüsi nende lahendusi vs. tegelikke tulemusi. Tee nimekiri: 5 ideed mida kaasa võtad ja 5 mida tead nüüd vältida.

### Prototüüpimise analüüs (Jupyter Lab)

#### Analüüs 1: Paigutustäpsus

**Päris küsimus:** kas robot paneb kivi sinna kuhu sa tahad? Mosaiigikivis on kivi samm tüüpiliselt 10–20 mm — kui paigutusviga on üle poole sammu, jooksevad read viltu ja tulemus näeb halb välja.

**Test:**

1. Märgi tööalale ruudustik (nt 5×5, iga 15 mm — sinu tegelik kivi samm).
2. Lase robotil igale positsioonile kivi asetada.
3. Mõõda joonlauaga: kas kivi on märgil? Kui ei, siis mitu mm kõrval?

| Rida, veerg | Viga X (mm) | Viga Y (mm) | Märkused |
|:---|:---|:---|:---|
| 1,1 | ... | ... | |
| 1,2 | ... | ... | |
| ... | ... | ... | |

**Hinnang:** kui viga on alla 1 mm — mosaiik näeb korralik välja. Kui viga kasvab äärtesse → koordinaatteisendus vajab parandamist. Kui viga on juhuslik → mehaaniline probleem (nt töölaud liigub).

#### Analüüs 2: Esimene pick-and-place tsükkel

**Päris küsimus:** kas terve tsükkel (võta kivi → liiguta → aseta) üldse töötab algusest lõpuni? Mis läheb katki?

**Test:**

1. Pane üks kivi hoidikusse.
2. Programmeeri robot: liigu hoidiku kohale → lülita pump sisse → liigu alla → tõsta kivi → liigu tööala kohale → liigu alla → lülita pump välja → liigu üles.
3. Korda 10 korda, logi iga katse:

| Katse # | Kivi võtmine OK? | Transport OK? | Asetamine OK? | Mis läks valesti? |
|:---|:---|:---|:---|:---|
| 1 | jah/ei | jah/ei | jah/ei | |
| ... | ... | ... | ... | |

**Hinnang:** kui 10-st 7+ töötavad → baastsükkel on korras, edasi saab optimeerida. Kui alla 5 → kas probleem on Z-kõrgustes, vaakumi ajastuses, või koordinaatides?

#### Analüüs 3: Maksimaalne töökiirus

**Päris küsimus:** kui kiiresti saab robot kivi transportida ilma et see maha kukuks? See määrab kogu süsteemi tootlikkuse.

**Test:**

1. Testi pick-and-place tsüklit erinevatel kiiruse seadetel (Dobot API kiiruse parameeter).
2. Alusta aeglasest, tõsta kiirust kuni kivi kukub.
3. Iga kiiruse juures 5 kordust:

| Kiirus (%) | 5-st mitu õnnestus | Märkused |
|:---|:---|:---|
| 20 | .../5 | |
| 40 | .../5 | |
| 60 | .../5 | |
| 80 | .../5 | |
| 100 | .../5 | |

**Hinnang:** maksimaalne usaldusväärne kiirus on see kus 5/5 õnnestub. Kasuta seda kiirust edaspidi.

---

## Verstapost 2: Integreeritud süsteem (18 t)

**Kohtumine: laupäev 18.04**

**NB: 1. tellimus (CNC lõikus + materjalid + andurid) peab olema esitatud hiljemalt 08.04!**

Pane kõik kokku: töölaud + robot + tarkvara + vaakum. Süsteem peab suutma laotada lihtsa mustri algusest lõpuni.

### Tulemused

- [ ] **CNC-lõigatud töölaua moodulid kohal ja kokku pandud**
  - Moodulid kinnituvad üksteisega
  - Aukude samm on täpne (3D-prinditud hoidikud sobivad)
  - Töölaud on stabiilne (ei nihku ladumise ajal)
- [ ] **Kivihoidikud (magazine) töötavad:**
  - Robot saab kivi kätte igast pesast
  - Kivi olemasolu andur tuvastab kas pesa on tühi
  - Hoidik mahutab vähemalt 10 kivi
- [ ] **Tööala töötab:**
  - Robot asetab kivi õigesse kohta
  - Kivi jääb paika (ei libise, ei pöördu)
  - Referentspunktide kaudu kalibreeritud
- [ ] **Tervikmustri ladumine töötab:**
  - Lihtne muster (nt 3×3 ruudustik ühevärvilistest kividest)
  - Tarkvara arvutab trajektoorid mustri põhjal
  - Robot laob mustri algusest lõpuni ilma sekkumiseta
- [ ] **Veebiliides näitab protsessi:**
  - Mustri vaade (mis kivid on laotud, mis on järgmine)
  - Andurite olek (kas kive on järel)
  - Peatamise ja jätkamise nupud
- [ ] Spetsifikatsiooni uuendus: integratsiooniprobleemid ja lahendused

### Analüüs (Jupyter Lab)

#### Analüüs 1: Mustri laotamise täpsus

**Mõõtmismeetod:** telefoniga foto pealtvaates + pilditöötlus Pythonis. Kividele on enne laotamist märgitud keskpunkt (markeriga täpp või kleebis). Foto põhjal saab iga kivi tegeliku positsiooni pikslitest millimeetritesse teisendada.

**Ettevalmistus:**

1. Märgi igale kivile keskpunkt (nt must täpp valgele kivile).
2. Pane tööala kõrvale mõõtjoon (joonlaud) — selle järgi arvutad mitu pikslit = 1 mm.
3. Defineeri muster teadaolevate positsioonidega (nt 5×5, iga kivi 15 mm sammuga).
4. Lase robotil muster laotada.
5. Tee telefoniga foto **otse pealtvaates** (telefon paralleelselt tööalaga, mida kõrgemalt seda vähem moonutust).

**Pildi analüüs Jupyter Lab'is:**

1. Lae pilt, leia mõõtjoon pikslites → arvuta skaala (px/mm).
2. Tuvasta kivide keskpunktid (must täpp valgel — lihtsaim on lävendiga binariseerimine + kontuuride leidmine OpenCV-ga).
3. Teisenda pikslid millimeetriteks.
4. Võrdle tegelikud positsioonid kavandatud positsioonidega.

**Tabel (genereeritakse automaatselt pildist):**

| Kivi # | Kavandatud X,Y (mm) | Mõõdetud X,Y (mm) | Viga X (mm) | Viga Y (mm) |
|:---|:---|:---|:---|:---|
| 1 | 0, 0 | ... | ... | ... |
| 2 | 15, 0 | ... | ... | ... |
| ... | ... | ... | ... | ... |

**Graafik:** joonista mustri pealtvaade — kavandatud positsioonid (ristid) vs. mõõdetud (ringid). Kas viga on süstemaatiline (kõik nihkes samas suunas → kalibreerimisviga) või juhuslik (→ mehaaniline mäng)?

#### Analüüs 2: Tsükliaeg

**Mida mõõdad:** aeg ühe kivi laotamiseks — hoidikust võtmine kuni tööalale asetamiseni.

**Mõõtmine:**

1. Logi tarkvara poolt iga kivi algus- ja lõpuaeg.
2. Laota vähemalt 20 kivi.
3. Arvuta iga kivi tsükliaeg.

**Tabel:**

| Kivi # | Algus (s) | Lõpp (s) | Tsükliaeg (s) |
|:---|:---|:---|:---|
| 1 | 0.0 | ... | ... |
| 2 | ... | ... | ... |
| ... | ... | ... | ... |

**Hinnang:** keskmine tsükliaeg × kivide arv mustris = kogu ladumisaeg. Kui 100-kivine muster võtab üle 30 min → optimeeri trajektoore (lühem tee hoidiku ja tööala vahel).

#### Analüüs 3: Anduri tuvastamise usaldusväärsus

Kivi olemasolu andur: mõõda 30 korda "kivi on" ja 30 korda "kivi puudub". Mitu korda 30-st tuvastab õigesti? Kas on valepositiivseid (tühi pesa → andur ütleb "kivi on")?

---

## Verstapost 3: Täisfunktsionaalne süsteem (16 t)

**Kohtumine: laupäev 30.05**

**NB: 2. tellimus peab olema esitatud hiljemalt 20.05!**

Süsteem töötab usaldusväärselt keerulisemate mustritega. Veebiliides on valmis. Veatöötlus toimib.

### Tulemused

- [ ] **Keerulisemad mustrid:**
  - Mitu kivi värvi (eri hoidikutest)
  - Suurem muster (vähemalt 5×5)
  - Mustri genereerimine JSON failist
- [ ] **Veatöötlus:**
  - Kivi kukkumise tuvastamine (andur tööalal või jõutagasiside)
  - Tühja hoidiku tuvastamine → peata ja teata operaatorile
  - Ladumise jätkamine pärast vea parandamist
- [ ] **Veebiliides valmis:**
  - Foto tegemine telefoniga / pildi üleslaadimine → automaatne teisendus mosaiigimustrik
  - Mustri eelvaade ja käsitsi korrigeerimine enne ladumist
  - Reaalajas vaade: laotud / laotamata kivid
  - Protsessi juhtimine: käivita, peata, jätka, tühista
  - Andurite olek
  - Veateated
- [ ] **Töölaud lõplikul kujul:**
  - Kõik moodulid CNC-lõigatud ja kokku pandud
  - Kõik hoidikud 3D-prinditud ja kinnitatud
  - Kaablihaldus korras
- [ ] Kasutusjuhendi mustand

### Analüüs (Jupyter Lab)

#### Analüüs 1: Suurima mustri ladumine

Laota suurim muster mida süsteem suudab (mitu värvi, vähemalt 25+ kivi). See on terviksüsteemi tõehetk — kõik peab koos töötama.

Logi iga kivi kohta:

| Kivi # | Värv | Edukas? | Vea tüüp (kui ei) |
|:---|:---|:---|:---|
| 1 | punane | jah | — |
| 2 | sinine | jah | — |
| ... | ... | ... | ... |

**Päris küsimused:** Kas vead kogunevad mustri lõpu poole (nt hoidik tühi, koordinaadid nihkuvad)? Kas mõni värv tekitab rohkem probleeme (nt erineva pinnatekstuuriga kivi)? Kas veatöötlus toimib — kui kivi kukub, kas süsteem peab pausi ja teatab operaatorile?

#### Analüüs 2: Operaatori õppimiskõver

Lase 3 operaatorit (kes pole süsteemi varem kasutanud) igaüks laotada sama mustrit veebiliidese kaudu. Mõõda aeg mustri laadimisest kuni ladumise käivitamiseni.

| Operaator | Katse # | Aeg (s) | Vigu protsessis |
|:---|:---|:---|:---|
| A | 1 | ... | ... |
| A | 2 | ... | ... |
| ... | ... | ... | ... |

**Hinnang:** kas liides on intuitiivne? Kui 1. katse võtab üle 5 min → liides vajab lihtsustamist.

#### Analüüs 3: Foto-mosaiik pipeline

**Päris küsimus:** kas foto üleslaadimisest kuni valmis mustrini jõuab terve ahel läbi? Kus tekivad ootamatud probleemid?

**Test:**
1. Tee 3 erinevat fotot (üks lihtne, üks detailne, üks halva valgustusega).
2. Laadi iga foto üles veebiliideses.
3. Logi tulemused:

| Foto | Pikslikaart mõistlik? | Värvid õigesti tuvastatud? | Ladumine õnnestus? | Probleem |
|:---|:---|:---|:---|:---|
| Lihtne logo | jah/ei | jah/ei | jah/ei | |
| Detailne pilt | jah/ei | jah/ei | jah/ei | |
| Halb valgustus | jah/ei | jah/ei | jah/ei | |

**Hinnang:** kas värvide kvantiseerimine (foto pikslid → lähim kivi värv) annab tulemuse mida kasutaja ära tunneb? Kui mitte — kas probleem on resolutsioonis (liiga vähe kive), värvivalikus (liiga vähesed värvid), või algoritmis?

---

## Verstapost 4: Tootmisvalmis süsteem (14 t)

**Kohtumine: laupäev 30.05**

Iga meeskond viimistleb süsteemi ja dokumentatsiooni.

### Tulemused

- [ ] **Töötav süsteem** — demonstreeritav ja usaldusväärne
- [ ] **Dokumentatsioon:**
  - Töölaua kokkupanekujuhend piltidega
  - 3D prindifailid (hoidikud, klambrid) valideeritud seadetega
  - CNC lõikusfailid (DXF)
  - BOM lõplik versioon
  - Tarkvarapaigalduse juhend (Python keskkond → seadista → töötab)
  - Mustri loomise juhend (JSON formaat)
  - Teadaolevad probleemid ja lahendused
- [ ] **Demomuster valmis** — üks ilus muster mis näitab süsteemi võimekust
- [ ] **Git repositoorium korras**
  - Kõik failid (.md, .f3z, .dxf, Python kood)
  - README mis selgitab repo struktuuri
  - Milestones täidetud

### Analüüs (Jupyter Lab)

#### Analüüs 1: Süsteemi piirangute kokkuvõte
Koonda kõigist varasematest testidest süsteemi tegelikud piirangud: maksimaalne töökiirus, suurim muster mida saab laotada, millised kivi pinnad töötavad, minimaalne kivi samm, tsükliaeg ühe kivi kohta. Võrdle spetsifikatsioonis planeeritut tegelikkusega — mis pidas paika, mis mitte?

#### Analüüs 2: Dokumentatsiooni läbikäik
Anna oma kokkupanekujuhend ja tarkvara paigaldusjuhend meeskonnaliikmele kes ei olnud ehitaja. Ta loeb läbi ja märgib iga koha kus info puudub, on ebaselge või vale. Nimekiri puudustest mida parandada.

#### Analüüs 3: V1–V3 mõõtmiste koondgraafik
Koonda kõigi varasemate verstapostide mõõtmised ühte Jupyter notebooki: paigutustäpsus (V1), API latentsus (V1), vaakumi edukus% (V1), mustri täpsus (V2), tsükliaeg (V2), anduri täpsus (V2), pikaajaline edukus% (V3). Visualiseeri süsteemi areng V1-st V3-ni.

---

## Demonstratsioon (pärast kaitsmist)

Pärast viimast kaitsmist on võimalik süsteemi demonstreerida. Demonstratsioon ei ole kohustuslik — meeskonnad võivad osaleda kui soovivad.

- [ ] Demomustri laotamine publikule
- [ ] Süsteemi tutvustamine

---

## Ajakava kokkuvõte

| | Kuupäev | Sisu |
|:---|:---|:---|
| ~~1. kohtumine~~ | ~~L 28.02~~ | ~~Möödas~~ |
| 2. kohtumine | L 21.03 | V1: spetsifikatsioon + esimesed testid |
| | **K 08.04** | **1. tellimuse (CNC lõikus + materjalid) tähtaeg** |
| 1. kaitsmine | **T 14.04** | **Kõik valmis tööd (online)** |
| 3. kohtumine | L 18.04 | V2: integratsioonitöö |
| | **K 20.05** | **2. tellimuse tähtaeg** |
| 2. kaitsmine | **T 26.05** | **Kõik ülejäänud tööd (online)** |
| 4. kohtumine | L 30.05 | V3–V4: viimistlus, demonstratsioon |
| 3. kaitsmine | **Määratakse pärast 2. kaitsmist** | **Lõplik kaitsmine (online)** |

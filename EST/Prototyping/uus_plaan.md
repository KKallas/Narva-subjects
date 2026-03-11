# Prototüüpimine — uuendatud plaan

Kõik meeskonnad valisid B-raja: SMARS-inspireeritud sumorobot. See plaan kirjutab lahti kõik viis verstaposti konkreetselt sumoroboti jaoks.

Eesmärk: töötavad robotid 5v5 matšiks Narva Kolledži areeniüritusel suvel.

### Arvutusplatvorm

Roboti aju võib olla kas Android telefon või eraldiseisev mikrokontrollerilahendus — meeskond valib ise. Nõue on et robotil peab olema **ettepoole suunatud kaamera** ja **veebipõhine operaatoriliides**.

**Variant A: Android telefon**
Vanem Android telefon on roboti aju. Sellel on kaamera, arvutusvõimsus, ekraan ja ühenduvus juba sisseehitatult. Telefon ühendub ESP32-ga läbi USB OTG. Tarkvara: Python + FastAPI Termuxis, teenindab veebilehte operaatorile.

**Variant B: ESP32 + M5-CAM**
ESP32 on roboti aju, M5-CAM moodul annab kaamera. Veebiliides jookseb otse ESP32 peal (või eraldi M5-CAM serveerib pilti). Kompaktsem ja kergem lahendus, kuid piiratum arvutusvõimsus — QR-koodi tuvastus ja pilditöötlus nõuavad optimeeritud koodi.

Mõlemal juhul peab lõpptulemus olema sama: operaator avab veebilehe, näeb kaamera pilti ja saab robotit juhtida.

### Areen

3×3 meetrit, kokku pandud 1×1 m OSB moodulitest (kokku 9 moodulit).

**Pind:** Iga moodul on puuritud 10×10 cm võrgustikuga, augud 5 mm läbimõõduga. Aukudesse käivad 3D-prinditud punnid (1 mm paks plaat pealt, 5 mm sügav tihvt alt) — need hoiavad peal vahetatavaid värvilisi plönne. Nii saab areeni pinda kiiresti ümber konfigureerida: erinevad värvilised tsoonid, punane ring keskel, väljapiiri markeeringud. Robot peab suutma eristada enda all olevat värvi — plönnide värv defineerib tsoone.

**Seinad:** 3D-prinditud hoovad kinnituvad kõige välimistesse aukudesse. Iga hoob kannab 10 cm kõrgust silda mis moodustab seina areeni poole. Seinad hoiavad roboteid areenil — robot kukub välja ainult kui lükatakse üle seina.

**Mõõtmed spetsifikatsiooni jaoks:**

| Parameeter | Väärtus |
|:---|:---|
| Areeni kogumõõtmed | 3000 × 3000 mm |
| Mooduli suurus | 1000 × 1000 mm |
| Augu samm | 100 mm (10×10 võrgustik mooduli kohta) |
| Augu läbimõõt | 5 mm |
| Seina kõrgus | 100 mm |
| Seina kinnitus | välimised augud |
| Pinna materjal | OSB + vahetatavad värvilised plönnid |

---

## Tellimuste ajakava

Iga tellimus peab olema välja saadetud **vähemalt 10 päeva enne** vastavat kohtumist — et asjad jõuaksid kohale.

| Tellimus | Esitamise tähtaeg | Kohtumine | Mida |
|:---|:---|:---|:---|
| 1. tellimus | **11.03** (10 päeva enne 21.03) | 2. kohtumine 21.03 | Mootorid, rattad/roomikud, akud, mootori draiverid, ESP32 plaadid, OTG kaablid, kruvid/mutrid |
| 2. tellimus (PCB) | **08.04** (10 päeva enne 18.04) | 3. kohtumine 18.04 | Mootori draiveri trükkplaat (JLCPCB), puuduvad komponendid esimesest testist |
| 3. tellimus | **20.05** (10 päeva enne 30.05) | 4. kohtumine 30.05 | Viimased komponendid: parandused pärast integratsioonitesti, varuosad võistluseks, lisaakud |

---

## Verstapost 1: Spetsifikatsioon (10 t)

**Kohtumine: laupäev 28.02 — kaitsmine: teisipäev 17.03 (online)**

Kirjuta süsteemispetsifikatsioon sumoroboti jaoks. Spetsifikatsioon peab olema piisavalt detailne et teine meeskond saaks roboti ainult sinu dokumendi põhjal üles ehitada.

### Tulemused

- [ ] Süsteemi ülevaade: mis robot on, mida teeb, kuidas töötab
- [ ] Funktsionaalsed nõuded (vähemalt 10, MoSCoW prioritiseeritud)
  - Sõitmine (diferentsiaalajam)
  - Kauguse mõõtmine eest
  - Värvi lugemine enda alt (areenipinna vs. väljapiiri)
  - Kaamera pilt enda ees
  - QR-koodide lugemine laest positsioneerimiseks
  - OTG side telefoni ja ESP32 vahel
  - Kaugjuhtimine operaatori poolt
- [ ] Jõudluseesmärgid tabelina (kiirus, tõukejõud, aku tööaeg, reaktsiooniaeg)
- [ ] Šassii mehhaaniline kontseptsioon (mõõtmetega, Fusion 360)
  - SMARS-inspireeritud roomikud
  - Maavaba ja kaalujaotumine tõukamiseks
  - Telefoni kinnituskoht
  - Lihtne ja prinditav
- [ ] Mootorite valik ja draiverelektroonika
  - Aku tööaja arvutus täiskoormusel
  - Eelista taaskasutatud komponente kus võimalik
- [ ] Elektriline plokkskeem (draw.io)
  - ESP32 ↔ mootori draiver ↔ mootorid
  - ESP32 ↔ telefon (USB OTG)
  - Toitehierarhia (aku → regulaatorid)
  - Andurid (kaugus, värv, kaamera)
- [ ] Tarkvaraarhitektuur (vali variant A või B, kirjelda mõlemat juhul kui meeskond pole veel otsustanud)
  - **Variant A — telefon:**
    - FastAPI server Termuxis, teenindab veebilehte
    - Telefoni kaamera → veebivoog operaatorile
    - Käsud telefonist ESP32-le läbi USB OTG (JSON üle seeriali)
  - **Variant B — ESP32 + M5-CAM:**
    - M5-CAM serveerib kaamera pilti HTTP kaudu
    - ESP32 teenindab veebilehte (või M5-CAM teeb seda)
    - Side ESP32 ↔ M5-CAM (UART/I2C/WiFi)
  - **Veebiliides (mõlemal variandil sama nõue):**
    - Kaamera voog reaalajas
    - Klõpsa-ja-sõida: vajuta pildil kohta → robot sõidab sinna
    - Andurite andmed reaalajas (kaugus, piiri olek, aku)
    - Režiimi valik: manuaalne / autonoomne
  - **ESP32 firmware:**
    - Mootori juhtimine (PWM, suund)
    - Andurite lugemine (kaugus, värv)
    - Seeriaprotokoll käskude vastuvõtmiseks (OTG või WiFi)
  - **Kommunikatsiooniprotokoll:**
    - Käsu formaat (nt JSON)
    - Anduriandmete tagastamine
    - Veakäsitlus ja taasühendamine
- [ ] Testimisplaan iga nõude jaoks
- [ ] BOM koos hindade ja tarnijatega
- [ ] **Esimese prototüübi ostunimekiri** — et tellimus läheks kohe pärast kaitsmist välja
- [ ] Arenduse ajakava verstapostide 2–5 jaoks (tagurpidi arvutatud suve tähtajast)
- [ ] GitHub/GitLab milestones verstapostide 2–5 jaoks

### Teostatavusanalüüs (Jupyter Lab)

1. **Tõmbejõu hinnang**: kas valitud mootorid suudavad vastase (hinnanguline mass) areenist välja tõugata? Arvuta mootori tõmbejõud andmelehe parameetritest (pöördemoment × ülekandearv / ajamiratta raadius). Võrdle vastase hõõrdejõuga (mass × g × hõõrdetegur). Roomikul on hõõrdetegur keerulisem kui rattal — kasuta lihtsustatud hinnangut ja valideeri V2-s füüsilise tõuketestiga
2. **Aku tööaja arvutus**: kui kaua peab vastu täiskoormusel? Mitu matši saab ühe laadimisega?
3. **Tehnoloogiauuring**: 3 sarnast projekti (GitHub, Instructables, YouTube) — mida nad tegid, mida õppida, milliseid vigu vältida

---

## Verstapost 2: Võtmetehnoloogia prototüüp (16 t)

**Kohtumine: laupäev 21.03 — kaitsmine: teisipäev 17.03 (online)**

**NB: 1. tellimus peab olema esitatud hiljemalt 11.03!**

Ehita ja testi kõige kriitilisemad tehnilised komponendid eraldi — enne kui proovid kõike kokku panna.

### Tulemused

- [ ] **Ajami prototüüp**: mootorid + draiver + rattad/roomikud lihtsale testšassiiale
  - Testid: edasi/tagasi, pööramine, koormustesti (lisa raskusi kuni mootor ei jaksa)
  - Mõõda: maksimaalne tõukejõud, kiirus, voolutarbimine
  - Jupyter Lab analüüs: mõõdetud vs. spetsifikatsioonis arvutatud väärtused
- [ ] **Side prototüüp** (vastavalt valitud variandile):
  - **A:** ESP32 ↔ telefon USB OTG kaudu, JSON üle seeriali
  - **B:** ESP32 ↔ M5-CAM (UART/WiFi), kaamera HTTP voog
  - Testid: käskude saatmine ja vastuvõtmine
  - Jupyter Lab: latentsuse jaotus (100+ mõõtmist)
- [ ] **Veebiliidese prototüüp**:
  - **A:** Termux + FastAPI telefoni peal
  - **B:** ESP32 veebiserver (või M5-CAM teenindab pilti)
  - Minimaalne veebileht: üks nupp → mootor liigub
  - Kaamera voog veebilehele
  - Testid: latentsus klõpsust mootori liikumiseni
- [ ] **Anduri prototüüp**: kaugusandur ja/või värviandur maketeerimisplaadil
  - Testid: tuvastuskaugus, usaldusväärsus, müratase
  - Jupyter Lab: anduri näitude statistika erinevatel kaugustel
- [ ] Spetsifikatsiooni uuendus: mis muutus pärast esimesi teste?
- [ ] **PCB disain alustatud** — mootori draiveri plaat Fusion 360 EDA-s
  - Skeem valmis
  - Komponentide paigutus
  - DRC kontroll
  - Gerber failid genereeritud

---

## Verstapost 3: Integreeritud tehniline prototüüp (18 t)

**Kohtumine: laupäev 18.04 — kaitsmine: teisipäev 14.04 (online)**

**NB: 2. tellimus (PCB) peab olema esitatud hiljemalt 08.04!**

Pane kõik komponendid kokku üheks töötavaks robotiks. Veel pole vaja ilusat korpust — oluline on et kõik alamsüsteemid töötavad koos.

### Tulemused

- [ ] **Töötav robot** mis sõidab ja mida juhitakse veebiliidese kaudu
  - Ajam + andurid + ESP32 (+ telefon/M5-CAM) kõik ühel šassiil
  - Operaator ühendub roboti WiFi-ga ja avab veebilehe
- [ ] **Andurite integratsioon**:
  - Kaugusandur: takistuste tuvastamine sõidu ajal
  - Värviandurid: areenipinna vs. väljapiiri eristamine
  - Kaamera: pildi edastamine veebiliidesele
- [ ] **Klõpsa-ja-sõida veebiliides** töötab:
  - Operaator näeb kaamera pilti veebilehel
  - Klõpsab pildil kohta → robot sõidab sinna
  - Server tõlgib ekraanikoordinaadid → suund + kaugus → mootori käsud
  - Latentsus klõpsust liikumiseni mõõdetud ja aktsepteeritav
- [ ] **QR-koodi positsioneerimine** (algne versioon):
  - Laes olevate QR-koodide lugemine kaameraga
  - Positsiooni arvutamine QR-koodi suuruse ja nurga põhjal
- [ ] **Autonoomne käitumine** (algne):
  - Piiri tuvastamine ja tagasipööramine
  - Vastase tuvastamine ja jälitamine
- [ ] Süsteemiintegratsiooni testid Jupyter Lab'is:
  - Andurite reageerimisnäitajad koostöös
  - Juhtimisvigade jaotus
  - Aku tööaeg tervikliku süsteemiga
- [ ] Spetsifikatsiooni uuendus: integratsiooniprobleemid ja lahendused

---

## Verstapost 4: Korpusega funktsionaalne prototüüp (16 t)

**Kohtumine: laupäev 30.05 — kaitsmine: teisipäev 26.05 (online)**

**NB: 3. tellimus (viimased komponendid) peab olema esitatud hiljemalt 20.05!**

Ehita robot valmis — korralik korpus, kaablihaldus, vastupidavus tõukamisele ja kukkumisele.

### Tulemused

- [ ] **3D-prinditud korpus**
  - Kõik komponendid kindlalt kinnitatud
  - Telefon lihtsalt eemaldatav/vahetatav
  - Kaablid korralikult marsruutitud
  - Vastupidav tõugetele (sumomaadlus!)
  - Aku ligipääsetav vahetamiseks matšide vahel
- [ ] **Täiustatud autonoomne käitumine**
  - Strateegia: positsioneerimine QR-koodide järgi, vastase otsimine, tõukamine
  - Piiri vältimise algoritm peenhäälestatud
  - Operaatori ja autonoomse režiimi vahel lülitamine
- [ ] **Vastupidavustestid**
  - Robot peab vastu vähemalt 10 järjestikust matši
  - Kukkumistest (areenilt alla — mis läheb katki, mis peab vastu?)
  - Kokkupõrketest (robot vs. robot täiskiirusel)
- [ ] **Operaatoriliides** (veebileht):
  - Kaamera pilt reaalajas
  - Klõpsa-ja-sõida peenhäälestatud (sujuv, usaldusväärne)
  - Andurite andmed reaalajas (kaugus, piiri olek, aku tase)
  - Režiimi valik: manuaalne klõpsa-ja-sõida / autonoomne sumo
  - Mitme roboti tugi (üks operaator, mitu robotit) kui aeg lubab
- [ ] Kasutusjuhendi mustand

---

## Verstapost 5: Tootmisvalmis süsteem (14 t)

**Kohtumine: laupäev 30.05 — kaitsmine: teisipäev 26.05 (online)**

Viimane viimistlus ja valmistumine areeniürituseks. Fookus: usaldusväärsus, reprodutseeritavus, dokumentatsioon.

### Tulemused

- [ ] **Iga meeskond vajab piisavalt roboteid 5v5 matšiks** — planeeri vastavalt
  - Vähemalt 5 robotit kummalegi poolele (kokku 10)
  - Kui meeskondi on vähem, siis rohkem roboteid meeskonna kohta
- [ ] **Reprodutseeritavuse test**
  - Teine meeskonnaliige ehitab roboti dokumentatsiooni põhjal — kas saab hakkama?
  - Mõõda ehitusaeg ja tuvasta dokumentatsiooni puudujäägid
- [ ] **Strateegia optimeerimine**
  - Testmatšid meeskondade vahel
  - Strateegia peenhäälestamine vastavalt teiste robotite käitumisele
  - Varustrateegiad (kui QR ei tööta? kui kaamera ei näe?)
- [ ] **Täielik dokumentatsioonipakett**
  - BOM lõplik versioon (tegelikud kulud)
  - Kokkupanekujuhend piltidega
  - Tarkvarapaigalduse juhend
  - Hooldusjuhend (mis kulub, mida vahetada)
  - Teadaolevad probleemid ja lahendused
- [ ] **Git repositoorium korras**
  - Kõik failid (.md, .f3z, .drawio, Arduino kood, Androidi projekt)
  - README mis selgitab repo struktuuri
  - Milestones täidetud

---

## Areeniürituse ettevalmistus (pärast kaitsmist)

- [ ] Areeniseadmed kontrollitud (3×3m, punane ring)
- [ ] Reeglid kokku lepitud ja meeskondadele jagatud
- [ ] Varuakud laetud
- [ ] Varurobotid valmis
- [ ] Kohtunikud ja ajamõõtmine

---

## Ajakava kokkuvõte

| | Kuupäev | Sisu |
|:---|:---|:---|
| 1. kohtumine | L 28.02 | Spetsifikatsiooni kirjutamine, verstapostide tutvustus |
| | **E 11.03** | **1. tellimuse tähtaeg** |
| V1+V2 kaitsmine | **T 17.03** | **V1 + V2 kaitsmine (online)** |
| 2. kohtumine | L 21.03 | Levinud prototüüpimisvead, integratsioonitöö |
| | **K 08.04** | **2. tellimuse (PCB) tähtaeg** |
| V3 kaitsmine | **T 14.04** | **V3 kaitsmine (online)** |
| 3. kohtumine | L 18.04 | Tootmisprototüübi dokumenteerimine |
| | **K 20.05** | **3. tellimuse tähtaeg** |
| V4+V5 kaitsmine | **T 26.05** | **V4 + V5 kaitsmine (online)** |
| 4. kohtumine | L 30.05 | Viimane viimistlus, testmatšid, areeniürituse ettevalmistus |
| Areeniüritus | 11.06 | 5v5 sumomaadlus |

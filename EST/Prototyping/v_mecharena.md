# Prototüüpimine — uuendatud plaan

Kõik meeskonnad valisid B-projekti: SMARS-inspireeritud sumorobot. See plaan kirjutab lahti kõik viis verstaposti konkreetse prototüüpimise aine jaoks.

Eesmärk: iga meeskond ehitab ühe töötava roboti prototüübi. Tiraaž toimub enne areeniüritust.

### Arvutusplatvorm

Roboti aju võib olla kas Android telefon või eraldiseisev mikrokontrollerilahendus — meeskond valib ise. Nõue on et robotil peab olema **ettepoole suunatud kaamera**, **veebipõhine operaatoriliides** ja **positisoneerimise süsteem areenil**. 

**Variant A: Android telefon**
Vanem Android telefon on roboti aju. Sellel on kaamera, arvutusvõimsus, ekraan ja ühenduvus juba sisseehitatult. Telefon ühendub ESP32-ga läbi USB OTG. Tarkvara: Python + FastAPI Termuxis, teenindab veebilehte operaatorile. Ettevaatav kaamera saab vaadata areeni lakke ja lugeda sealt QR koode positsioneerimiseks.

**Variant B: ESP32 + M5-CAM**
ESP32 on roboti aju, M5-CAM moodul annab kaamera. Veebiliides jookseb otse ESP32 peal (või eraldi M5-CAM serveerib pilti). Kompaktsem ja kergem lahendus, kuid piiratum arvutusvõimsus.
Tõenäoliselt on liskas vaja veel mõnda positsioneerimise tehnolligiat nagu UWB positiosneerimine.

Mõlemal juhul peab lõpptulemus olema sama: operaator avab veebilehe, näeb kaamera pilti ja saab robotit juhtida vajutades pildil kohale kus ta tahab et robot liiguks.

### Areen

3×3 meetrit, kokku pandud 1×1 m OSB moodulitest (kokku 9 moodulit).

**Pind:** Iga moodul on puuritud 10×10 cm võrgustikuga, augud 5 mm läbimõõduga. Aukudesse käivad 3D-prinditud punnid (5 mm sügav ava tihvtile) — need hoiavad peal vahetatavaid värvilisi plönne (mitte kõrgemad kui 2mm põrandast). Nii saab areeni pinda kiiresti ümber konfigureerida: erinevad värvilised tsoonid, punane ring keskel, väljapiiri markeeringud. Robot peab suutma eristada enda all olevat värvi — plönnide värv defineerib tsoone.

**Seinad:** 3D-prinditud hoovad kinnituvad kõige välimistesse aukudesse. Iga hoob kannab 10 cm kõrgust silda mis moodustab seina areeni poole. Seinad hoiavad roboteid areenil — robotid ei saa välja kukkuda.

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

### Kaitsmised

Kolm kaitsmist. Kaitsed **kõik tööd mis selleks hetkeks valmis on** — pole oluline milline verstapost, oluline on et töö on tehtud ja dokumenteeritud.

| Kaitsmine | Kuupäev | Mida |
|:---|:---|:---|
| 1. kaitsmine | **T 14.04 (online)** | Kõik verstapostid mis selleks hetkeks valmis on |
| 2. kaitsmine | **T 26.05 (online)** | Kõik verstapostid mis selleks hetkeks valmis on |
| 3. kaitsmine | **Kuupäev määratakse pärast 2. kaitsmist** | Ülejäänud verstapostid |

---

## Tellimuste ajakava

Iga tellimus peab olema välja saadetud **vähemalt 10 päeva enne** vastavat kohtumist — et asjad jõuaksid kohale. Meeskond otsustab ise mida ja kust tellida. Kogu roboti eelarve on **300 €** (telefon 50 € õppejõu poolt, ülejäänu meeskonna hallata).

| Tellimus | Esitamise tähtaeg | Kohtumine |
|:---|:---|:---|
| 1. tellimus | **11.03** (10 päeva enne 21.03) | 2. kohtumine 21.03 |
| 2. tellimus (PCB) | **08.04** (10 päeva enne 18.04) | 3. kohtumine 18.04 |
| 3. tellimus | **20.05** (10 päeva enne 30.05) | 4. kohtumine 30.05 |

---

## Verstapost 1: Spetsifikatsioon (10 t)

**Kohtumine: laupäev 28.02**

Kirjuta süsteemispetsifikatsioon sumoroboti jaoks. Spetsifikatsioon peab olema piisavalt detailne et teine meeskond saaks roboti ainult sinu dokumendi põhjal üles ehitada.

### Tulemused

- [ ] Süsteemi ülevaade: mis robot on, mida teeb, kuidas töötab
- [ ] Funktsionaalsed nõuded (vähemalt 10, MoSCoW prioritiseeritud)
  - Sõitmine (diferentsiaalajam)
  - Kauguse mõõtmine eest
  - Värvi lugemine enda alt (areenipinna vs. väljapiiri)
  - Kaamera pilt enda ees
  - Side arvutusplatvormi ja ESP32 vahel
  - Kaugjuhtimine operaatori poolt veebiliidesest
- [ ] Jõudluseesmärgid tabelina (kiirus, tõukejõud, aku tööaeg, reaktsiooniaeg)
- [ ] Šassii mehhaaniline kontseptsioon (mõõtmetega, Fusion 360)
  - SMARS-inspireeritud roomikud
  - Maavaba ja kaalujaotumine tõukamiseks
  - Arvutusplatvormi kinnituskoht (telefon või M5-CAM)
  - Kaamera kinnituse nurk (vajalik raycast arvutuseks)
  - Lihtne ja prinditav
- [ ] Mootorite valik ja draiverelektroonika
  - Aku tööaja arvutus täiskoormusel
  - Eelista taaskasutatud komponente kus võimalik
- [ ] Elektriline plokkskeem (draw.io)
  - ESP32 ↔ mootori draiver ↔ mootorid
  - ESP32 ↔ arvutusplatvorm (OTG või WiFi)
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
  - **Klõpsa-ja-sõida raycast loogika:**
    - Kaamera kinnituse nurk ja kõrgus maapinnast on teada (mõõdetud)
    - Kaamera FOV on teada (andmelehelt)
    - Klõps pildil → kiir kaamerast läbi piksli → lõikepunkt maapinnaga
    - Tulemus: suund ja kaugus maapinnal → pööra + sõida
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

#### Analüüs 1: Mootori ja käigukasti valik

**Samm 1: Kiirus ratta suuruse ja distantsi järgi**

Sa tead areeni mõõtmeid (3×3 m). Otsusta kui kiiresti peab robot areeni ühest otsast teise jõudma — see annab soovitud kiiruse (m/s).

Ratta ümbermõõt = π × d (kus d on ratta diameeter meetrites). Üks ratta pööre viib robotit edasi ühe ümbermõõdu jagu.

Vajalik RPM väljundvõllil = (soovitud kiirus × 60) / (π × d)

Näide: tahad 0,5 m/s, ratas 40 mm → RPM = (0,5 × 60) / (π × 0,04) = 239 RPM

**Samm 2: Pöördemoment kohalt ärasõiduks**

Robot peab liikuma kohalt. Vajalik jõud = roboti mass × g × hõõrdetegur (kumm OSB peal ~0,5). Vajalik pöördemoment väljundvõllil = jõud × ratta raadius.

Näide: robot 500g → F = 0,5 × 9,81 × 0,5 = 2,45 N → moment = 2,45 × 0,02 = 0,049 Nm = 49 mNm

**Samm 3: Pöördemoment vastase äralükkamiseks**

Halvim juht: vastane on risti ees pargitud ja sa pead ta plönnilt maha lükkama. Nüüd pead liigutama enda massi + vastase massi (hõõrdeteguriga). Vajalik jõud = (oma mass + vastase mass) × g × hõõrdetegur. Vajalik pöördemoment = jõud × ratta raadius.

Näide: oma 500g + vastane 500g → F = 1,0 × 9,81 × 0,5 = 4,9 N → moment = 4,9 × 0,02 = 0,098 Nm = 98 mNm

**Samm 4: Mootori valimine andmelehelt**

Andmelehel on mootori RPM (tühikäigul) ja pöördemoment (blokeerimismoment). Käigukast vähendab RPM-i ja suurendab momenti sama ülekandearvu võrra.

Väljundi RPM = mootori RPM / ülekandearv
Väljundi moment = mootori moment × ülekandearv

Kontrolli:
1. Kas väljundi RPM ≥ samm 1 vajalik RPM?
2. Kas väljundi moment ≥ samm 3 vajalik moment?

Kui RPM on liiga suur ja moment liiga väike → vaja suuremat ülekannet. Kui RPM on liiga väike → vaja väiksemat ülekannet või kiiremat mootorit. Kui mõlemad ei sobi → vaja teist mootorit.

**Samm 5: Aku tööaeg**

Kui telefon on aku (OTG kaudu toidab ka ESP32 ja mootoreid), siis arvutamine andmelehelt ei aita — telefoni aku mahtuvus ja tegelik väljundvõimsus OTG kaudu varieeruvad. Mõõda praktikas: ühenda mootorid koormuse alla (V2 tõuketestist), jälgi telefoni aku protsenti aja jooksul. Joonista graafik: aeg (min) vs. aku %. Kui palju protsenti langeb 3 minutiga täiskoormusel? Mitu matši saab enne kui aku on 20% juures?

#### Analüüs 2: Kulu-jõudluse kompromiss
Tuvasta üks disainiotsus kus seisad silmitsi kulu-jõudluse kompromissiga. Esita analüüs sarnaselt aga nagu oleks pidanud pingejaguri vs. op-ampi võrdlus Andmehõive Labor 2-st: variant A kirjeldus/kulu/jõudlus, variant B kirjeldus/kulu/jõudlus, otsus ja põhjendus.

#### Analüüs 3: Tehnoloogiauuring
Kuna 1. semestri eelkäijat pole, leia 3 sarnast projekti (GitHubi repod, Instructables, YouTube'i ehitused) ja analüüsi nende spetsifikatsioone vs. tegelikke tulemusi. Tee nimekiri mis ideed kaasa võtad ja mida tead nüüd välitada 5 ja 5.

---

## Verstapost 2: Võtmetehnoloogia prototüüp (16 t)

**Kohtumine: laupäev 21.03**

**NB: 1. tellimus peab olema esitatud hiljemalt 11.03!**

Ehita ja testi kõige kriitilisemad tehnilised komponendid eraldi — enne kui proovid kõike kokku panna. Mida väiksemad tükid seda kiiremini kitereerid ja jõuad töötava tulemuseni.

### Tulemused

- [ ] **Ajami prototüüp**: mootorid + draiver + rattad/roomikud lihtsale testšassiile
  - Testid: edasi/tagasi, pööramine, koormustestid (lisa raskusi kuni mootor ei suuda endam raskust liigutada)
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

### Analüüs (Jupyter Lab)

#### Analüüs 1: Tõuketest

**Ülesehitus:** kinnita testšassii (mootorid + rattad + draiver) nööriga kelgu külge. Kelk on kast mille sisse saab raskusi lisada (nt mutrivõtmed, poldipakid, telefon — peaasi et saad kaaluda). Kelk liigub siledal pinnal (OSB).

**Mõõtmine:**

1. Märgi maha kaks joont teadaoleval kaugusel (nt 0.1 m).
2. Pane kelku teadaolev raskus (alusta tühjast, lisa 100 g kaupa).
3. Käivita mootor täisgaasil. Mõõda aeg sekundites mis kulub 0.1 m läbimiseks (stopper või video).
4. Korda iga raskusega 3 korda ja võta keskmine.
5. Suurenda raskust kuni mootor ei suuda enam kelku liigutada — see on mootori maksimaalne tõmbejõud selle ülekandega.

**Arvutus:**

- Kiirus: v = distants / aeg (m/s)
- Tõmbejõud: F = raskus × g × hõõrdetegur (kelk OSB peal, hõõrdetegur ~0,3–0,5 — mõõda see enne eraldi: kalluta OSB plaati kuni kelk hakkab libisema, hõõrdetegur = tan(nurk))
- Võimsus: P = F × v (W)

**Tabel:**

| Koormamass (g) | Aeg 1m (s) | Kiirus (m/s) | Tõmbejõud (N) | Võimsus (W) |
|:---|:---|:---|:---|:---|
| 0 | ... | ... | ... | ... |
| 100 | ... | ... | ... | ... |
| 200 | ... | ... | ... | ... |
| ... | ... | ... | ... | ... |
| mootor ei jaksa | — | 0 | max jõud | 0 |

**Graafik:** koormamass (x) vs. kiirus (y) — näed kuidas mootor aeglustub koormuse kasvades. Kanna samale graafikule V1 spetsifikatsioonis arvutatud väärtused (samm 2 ja 3). Kus on erinevus ja miks?

#### Analüüs 2: Side latentsus

**Mida mõõdad:** aeg millisekundites hetkest kui arvutusplatvorm saadab käsu ("sõida edasi") kuni hetkeni kui ESP32 kinnitab vastuvõttu (või mootor hakkab liikuma). See on side latentsus — viivitus käsu ja tegevuse vahel.

**Mõõtmine:**

1. Kirjuta skript mis saadab käsu ja salvestab ajatempli (nt Pythonis `time.time()` enne saatmist ja pärast vastuse saamist).
2. Korda vähemalt 100 korda järjest (loop).
3. Salvesta iga mõõtmise latentsus millisekundites CSV faili.

**Histogram — mis see on ja kuidas teha:**

Histogram näitab kui tihti mingi väärtus esineb. X-teljel on latentsus (ms), y-teljel on mitu mõõtmist sattus sellesse vahemikku. Nii näed kohe kas enamus käske jõuavad kohale nt 10 ms-ga ja mõni üksik võtab 50 ms, või on jaotus laiali.

```python
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("latentsus.csv")  # veerg: "latentsus_ms"

plt.hist(df["latentsus_ms"], bins=20, edgecolor="black")
plt.xlabel("Latentsus (ms)")
plt.ylabel("Mõõtmiste arv")
plt.title("Side latentsuse jaotus (n=100+)")
plt.axvline(df["latentsus_ms"].median(), color="red", linestyle="--", label=f"mediaan: {df['latentsus_ms'].median():.1f} ms")
plt.legend()
plt.show()

print(f"Mediaan: {df['latentsus_ms'].median():.1f} ms")
print(f"95. protsentiil: {df['latentsus_ms'].quantile(0.95):.1f} ms")
print(f"Max: {df['latentsus_ms'].max():.1f} ms")
```

**Hinnang:** inimese reaktsiooniaeg on ~200 ms. Kui 95% käskudest jõuab kohale alla 100 ms, on side piisavalt kiire operaatori juhtimiseks. Kui mediaan on üle 200 ms, tunneb operaator viivitust ja robot muutub raskesti juhitavaks.

#### Analüüs 3: Anduri tuvastusstatistika

**Eesmärk:** määra iga anduri **täpsus** (accuracy) ja **lahutusvõime** (resolution).

- **Täpsus** — kui lähedal on mõõtetulemus tegelikule väärtusele? Arvutad: keskmine viga = keskmine(mõõdetud) − tegelik.
- **Lahutusvõime** — mis on väikseim muutus mida andur suudab eristada? Arvutad: standardhälve näitab müra suurust. Kui standardhälve on 3 mm, siis alla 3 mm muutust andur usaldusväärselt ei erista.

**Kaugusandur:**

1. Aseta takistus teadaolevale kaugusele (nt 5 cm, 10 cm, 20 cm, 30 cm, 50 cm).
2. Mõõda igal kaugusel **vähemalt 30 korda** (liigutamata midagi vahepeal).
3. Salvesta kõik näidud CSV faili.

**Värviandur:**

1. Vali 4–5 erinevat pinda (valge OSB, punane plönn, sinine plönn, must piir, roheline plönn).
2. Mõõda igal pinnal **vähemalt 30 korda**.
3. Salvesta toorväärtused (RGB või analoogväärtus) CSV faili.

**Arvutus ja tabel:**

```python
import pandas as pd
import numpy as np

df = pd.read_csv("kaugusandur.csv")  # veerud: "tegelik_cm", "mõõdetud_cm"

tabel = df.groupby("tegelik_cm")["mõõdetud_cm"].agg(
    keskmine="mean",
    standardhälve="std",
    min="min",
    max="max",
    n="count"
)
tabel["viga_cm"] = tabel["keskmine"] - tabel.index  # täpsus
tabel["lahutusvõime_cm"] = tabel["standardhälve"]    # ≈ väikseim eristatav muutus
print(tabel)
```

**Tabel (kaugusandur):**

| Tegelik (cm) | Keskmine (cm) | Viga (cm) | Standardhälve (cm) | Min | Max | n |
|:---|:---|:---|:---|:---|:---|:---|
| 5 | ... | ... | ... | ... | ... | 30 |
| 10 | ... | ... | ... | ... | ... | 30 |
| 20 | ... | ... | ... | ... | ... | 30 |
| 30 | ... | ... | ... | ... | ... | 30 |
| 50 | ... | ... | ... | ... | ... | 30 |

**Hinnang:**
- Kui viga kasvab kaugusega → andur on ebatäpne kaugemal, arvesta sellega tarkvaras.
- Kui standardhälve on suurem kui vajalik eristus (nt robot peab eristama 5 cm vs. 10 cm, aga standardhälve on 8 cm) → andur ei sobi selleks ülesandeks.
- Värvianduri puhul: kas erinevate värvide mõõtmised kattuvad? Kui punase ja valge väärtused kattuvad → andur ei erista neid usaldusväärselt.

---

## Verstapost 3: Integreeritud tehniline prototüüp (18 t)

**Kohtumine: laupäev 18.04**

**NB: 2. tellimus (PCB) peab olema esitatud hiljemalt 08.04!**

Pane kõik komponendid kokku üheks töötavaks robotiks. Veel pole vaja ilusat kaablimanageerimist ja korpust — oluline on et kõik põhisüsteemid töötavad koos.

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
  - Klõpsab pildil kohta → raycast maapinnale → robot pöörab ja sõidab
  - Kaamera nurk, kõrgus ja FOV peavad olema kalibreeritud
  - Testid: klõpsa 5 eri kohta, mõõda kuhu robot tegelikult jõuab vs. kuhu pidi
- [ ] **Piiri tuvastamine** töötab:
  - Värviandur tuvastab väljapiiri → robot peatub/pöörab
  - Testid: mitu korda 10-st tuvastab piiri enne ülesõitmist?
- [ ] Süsteemiintegratsiooni testid Jupyter Lab'is:
  - Andurite reageerimisnäitajad koostöös
  - Raycast täpsus erinevatel kaugustel
  - Aku tööaeg tervikliku süsteemiga
- [ ] Spetsifikatsiooni uuendus: integratsiooniprobleemid ja lahendused

### Analüüs (Jupyter Lab)

#### Analüüs 1: Klõpsa-ja-sõida täpsus

**Ettevalmistus:**

1. Märgi roboti korpusele üks selge **referentspunkt** (nt rist korpuse keskel või ninaosa tipp) — sellest punktist mõõdad alati roboti tegelikku positsiooni. Ilma selleta ei ole mõõtmised võrreldavad.
2. Märgi areenile 10 sihtpunkti teadaolevatel koordinaatidel (kasuta areeni 10×10 cm auguvõrgustikku — augud ongi su koordinaatsüsteem). Kirjuta iga punkti koordinaadid üles (nt A3, E7, H2).
3. Aseta robot alati samasse alguspunkti ja algussuunda.

**Mõõtmine:**

1. Klõpsa veebiliideses sihtpunktile.
2. Oota kuni robot peatub.
3. Mõõda roboti referentspunkti tegelik positsioon areeni auguvõrgustiku järgi (lähim auk + nihke hinnang cm-des).
4. Korda iga sihtpunkti kohta 3 korda.

**Tabel:**

| Sihtpunkt | Siht X,Y (cm) | Tegelik X,Y (cm) | Viga (cm) | Kaugus alguspunktist (cm) | Nurk alguspunktist (°) |
|:---|:---|:---|:---|:---|:---|
| A3 | 20, 30 | ... | ... | ... | ... |
| E7 | 60, 70 | ... | ... | ... | ... |
| ... | ... | ... | ... | ... | ... |

**Graafik:** joonista areeni pealtvaade — sihtpunktid ühe värviga, tegelikud lõpp-punktid teise värviga, jooned nende vahel. Nii näed visuaalselt kus süsteem eksib. Kas viga kasvab kaugusega? Kas teatud nurga all on suurem viga (nt raycast on ebatäpsem pildi servades)?

#### Analüüs 2: Piiri tuvastamise usaldusväärsus

**Probleem:** piiriala ring on 10 cm lai. Robot peab jõudma reageerida (tuvastada + pidurdada) enne kui on ringist läbi sõitnud. Küsimus on: kui kiiresti andur reageerib ja kui kaugele robot selle ajaga jõuab?

**Mõõtmine 1 — anduri reaktsiooniaeg:**

1. Aseta värviandur statsionaarselt piiriala kohal (andur näeb piiriala värvi).
2. Libista piiriala alt ära (nt tõmba plönn kiiresti eest) ja mõõda kui kiiresti anduri näit muutub. Kasuta ESP32 ajatemplit mikrosekundites.
3. Korda 30 korda. Salvesta iga mõõtmise reaktsiooniaeg CSV faili.

**Arvutus — pidurdusteekond:**

- Anduri reaktsiooniaeg (mediaan ja max) millisekunditest
- Tarkvara töötlusaeg (käsu saatmine mootoridraivile) — mõõdetud V2 latentsustestist
- Kogu reaktsiooniaeg = anduri aeg + tarkvara aeg + mootori pidurdusaeg
- Pidurdusteekond = roboti kiirus × kogu reaktsiooniaeg

**Tabel:**

| Parameeter | Min | Mediaan | Max |
|:---|:---|:---|:---|
| Anduri reaktsiooniaeg (ms) | ... | ... | ... |
| Tarkvara latentsus (ms) | ... | ... | ... |
| Kogu reaktsiooniaeg (ms) | ... | ... | ... |
| Roboti kiirus (m/s) | ... | ... | ... |
| Pidurdusteekond (cm) | ... | ... | ... |

**Hinnang:** kui maksimaalne pidurdusteekond on alla 10 cm → robot jõuab piiriala sees reageerida. Kui üle 10 cm → robot sõidab ringist läbi enne kui peatub. Sel juhul tuleb kas kiirust piirata piiri lähedal, alustada pidurdamist varem, või kasutada laiemat piiriala.

#### Analüüs 3: Aku tööaeg tervikliku süsteemiga
Lae aku täis, sõida robotiga nagu matšis (aktiivselt). Logi pinget aja jooksul. Mitu minutit kestab? Mitu 3-minutilist matši saab?

---

## Verstapost 4: Korpusega funktsionaalne prototüüp (16 t)

**Kohtumine: laupäev 30.05**

**NB: 3. tellimus (viimased komponendid) peab olema esitatud hiljemalt 20.05!**

Ehita robot valmis — korralik korpus, kaablihaldus, vastupidavus tõukamisele ja kukkumisele. Lisa autonoomne käitumine.

### Tulemused

- [ ] **3D-prinditud korpus**
  - Kõik komponendid kindlalt kinnitatud
  - Arvutusplatvorm (telefon/M5-CAM) lihtsalt eemaldatav/vahetatav
  - Kaabli kanalid läbimõeldud
  - Vastupidav tõugetele (sumomaadlus!)
  - Aku ligipääsetav vahetamiseks matšide vahel
- [ ] **Autonoomne käitumine**
  - Piiri tuvastamine ja tagasipööramine (V3-st edasi arendatud)
  - Vastase tuvastamine kaugusanduriga ja tõukamine
  - Operaatori ja autonoomse režiimi vahel lülitamine
- [ ] **Vastupidavustestid**
  - Robot peab vastu vähemalt 10 järjestikust matši
  - Kokkupõrketest (robot vs. sein täiskiirusel — mis läheb katki?)
  - Aku vahetus matšide vahel testitud
- [ ] **Operaatoriliides** (veebileht):
  - Kaamera pilt reaalajas
  - Klõpsa-ja-sõida peenhäälestatud (sujuv, usaldusväärne)
  - Andurite andmed reaalajas (kaugus, piiri olek, aku tase)
  - Režiimi valik: manuaalne klõpsa-ja-sõida / autonoomne sumo
- [ ] Kasutusjuhendi mustand

### Analüüs (Jupyter Lab)

#### Analüüs 1: Kokkupõrketest

Sõida robotiga 10 korda täiskiirusel vastu seina. Pärast iga kokkupõrget pildista ja kirjelda kahjustusi. Koonda tabel:

| Katse # | Kahjustus | Otsus: varuosa või disainimuutus? |
|:---|:---|:---|
| 1 | — | — |
| 2 | ... | ... |
| ... | ... | ... |

**Otsus iga kahjustuse kohta:** kui osa läheb lihtsalt lahti või nihkub → piisab varuosast (prindi tiraaži jaoks ekstra). Kui sama osa puruneb korduvalt → disainimuutus (paksem sein, tugevdam, muu materjal). Lõpptulemus: uuendatud varuosade nimekiri ja vajalikud STL muudatused enne tiraaži.

#### Analüüs 2: Operaatori õppimiskõver

**Ülesehitus:** ehita areenile labürint 3D-prinditud seintega (kasuta areeni 100 mm auguvõrgustikku — seinad kinnituvad samadesse aukudesse nagu areeni välisseinad). Labürint peab nõudma vähemalt 3–4 pööret, et operaator peaks korduvalt klõpsama ja manööverdama.

**Mõõtmine:**

1. Lase 3 operaatorit (kes pole robotit varem juhtinud) igaüks läbida labürint 5 korda.
2. Mõõda iga katse aeg sekundites (algusest kuni robot on lõpus).
3. Märgi üles ka kokkupõrgete arv seintega.

**Tabel:**

| Operaator | Katse # | Aeg (s) | Kokkupõrkeid |
|:---|:---|:---|:---|
| A | 1 | ... | ... |
| A | 2 | ... | ... |
| ... | ... | ... | ... |

**Graafik:** katse number (x) vs. aeg (y), iga operaator eraldi joon. Kas 5. katse on alla 2× esimese ajast? Kui ei → liides vajab lihtsustamist.

#### Analüüs 3: Süsteemi usaldusväärsus

Sõida robotiga 10 järjestikust 3-minutilist matši (nagu turniiril). Logi iga matši ajal tarkvarast automaatselt: WiFi katkestused, kaotatud käsud (saadeti aga vastust ei tulnud), anduri vead, veebiliidese hangumised. Pärast iga matši märgi üles ka manuaalselt: kas midagi vajab taaskäivitamist?

**Tabel:**

| Matš # | WiFi katkestusi | Kaotatud käske | Anduri vigu | Taaskäivitus vajalik? |
|:---|:---|:---|:---|:---|
| 1 | 0 | 0 | 0 | ei |
| 2 | ... | ... | ... | ... |
| ... | ... | ... | ... | ... |

**Hinnang:** kui 10 matši jooksul on 0 taaskäivitust ja alla 5 kaotatud käsku kokku → süsteem on turniirivalmis. Kui WiFi katkeb regulaarselt → uuri kas probleem on levis, toites või tarkvaras.

---

## Verstapost 5: Tootmisvalmis süsteem (14 t)

**Kohtumine: laupäev 30.05**

Iga meeskond viimistleb oma prototüübi ja valmistab dokumentatsiooni tiraaži jaoks. Tiraaž toimub pärast kaitsmist, enne areeniüritust.

### Tulemused

- [ ] **Üks töötav prototüüp meeskonna kohta** — testitud ja usaldusväärne
- [ ] **Tiraaživalmis dokumentatsioon** — et pärast kaitsmist saaks kiirelt lisaroboteid toota:
  - Kokkupanekujuhend piltidega (et keegi teine saaks ehitada)
  - 3D prindifailid valideeritud seadetega (orientatsioon, tugestinad, täituvus)
  - BOM lõplik versioon (tegelikud kulud, tarnijad)
  - Tarkvarapaigalduse juhend (flash → seadista → töötab)
  - Hooldusjuhend (mis kulub, mida vahetada)
  - Teadaolevad probleemid ja lahendused
- [ ] **Testmatšid meeskondade vahel** (iga meeskond oma prototüübiga) — viimane kontroll enne tiraaži
- [ ] **Git repositoorium korras**
  - Kõik failid (.md, .f3z, .drawio, Arduino kood, Androidi projekt)
  - README mis selgitab repo struktuuri
  - Milestones täidetud

### Analüüs (Jupyter Lab)

#### Analüüs 1: Tiraaži ajaeelarve
Mõõda iga 3D-prinditud detaili printimisaeg ja kokkupaneku aeg. Koonda tabel: detail, printimisaeg, montaaž. Koguaeg ühe roboti jaoks. Mitu robotit jõuab toota 12 päevaga (30.05–11.06) arvestades printeri ja inimeste arvu?

#### Analüüs 2: Dokumentatsiooni läbikäik
Anna oma kokkupanekujuhend meeskonnaliikmele kes ei olnud ehitaja. Ta loeb läbi ja märgib iga koha kus info puudub, on ebaselge või vale. Nimekiri puudustest mida parandada enne tiraaži.

#### Analüüs 3: V1–V4 mõõtmiste koondgraafik
Koonda kõigi varasemate verstapostide mõõtmised ühte Jupyter notebooki: tõukejõud (V2), latentsus (V2), anduri täpsus (V2), raycast viga (V3), piiri tuvastamise % (V3), aku tööaeg (V3), kokkupõrke kahjustused (V4). Visualiseeri roboti areng V2-st V4-ni — mis paranes, mis halvenes, mis jäi lahendamata?

---

## Tiraaž ja areeniüritus (pärast kaitsmist)

Pärast viimast kaitsmist (26.05) ja kohtumist (30.05) kuni areeniürituseni (11.06) on ~12 päeva tiraaži jaoks. Tiraaž ei ole kohustuslik — meeskonnad võivad osaleda kui soovivad, aga ei pea.

- [ ] Soovijad toodavad lisaroboteid dokumentatsiooni järgi
- [ ] Robotite arv sõltub formaadist — lepitakse kokku 4. kohtumisel
- [ ] Areeniseadmed kontrollitud (3×3m, plönnid paigas, seinad kinni)
- [ ] Reeglid kokku lepitud ja meeskondadele jagatud
- [ ] Varuakud laetud
- [ ] Kohtunikud ja ajamõõtmine

---

## Ajakava kokkuvõte

| | Kuupäev | Sisu |
|:---|:---|:---|
| 1. kohtumine | L 28.02 | Spetsifikatsiooni kirjutamine, verstapostide tutvustus |
| | **E 11.03** | **1. tellimuse tähtaeg** |
| 2. kohtumine | L 21.03 | Levinud prototüüpimisvead, komponentide test |
| | **K 08.04** | **2. tellimuse (PCB) tähtaeg** |
| 1. kaitsmine | **T 14.04** | **Kõik valmis tööd (online)** |
| 3. kohtumine | L 18.04 | Integratsioonitöö, tootmisprototüübi dokumenteerimine |
| | **K 20.05** | **3. tellimuse tähtaeg** |
| 2. kaitsmine | **T 26.05** | **Kõik ülejäänud tööd (online)** |
| 4. kohtumine | L 30.05 | Testmatšid, tiraaži planeerimine, areeniürituse ettevalmistus |
| 3. kaitsmine | **Määratakse pärast 2. kaitsmist** | **Lõplik kaitsmine (online)** |
| Tiraaž | 30.05–10.06 | Lisarobotite tootmine dokumentatsiooni järgi |
| Areeniüritus | 11.06 | Sumomaadlus |

## Andmehõive: Labor 2

## Eesmärk

Labor 2 on otsustamis- ja integratsioonipunkt. Labor 1-s testisime pingejaguri lahendust MPX5700AP rõhuanduri liidestamiseks ESP32-ga. Nüüd ehitame op-amp põhise alternatiivi (LM358N), mõõdame selle täpsust ja kulu, võrdleme kahte lähenemist ja valime millega edasi minna. Valitud lahendusega disainime PCB Autodesk Fusionis ja tellime JLCPCB-st. Paralleelselt valideerime kogu süsteemi kontseptsiooni \- ehitame töötava prototüübi kus füüsiline signaal (rõhk süstalast) liigub läbi ESP32 ja jõuab UR5 robotini, pannes selle pead pöörama proportsionaalselt mõõdetud rõhule.

Kui labor õnnestub, meil on kaks konkreetset tulemust: tehtud otsus ja valmis PCB disain järgmiseks laboriks, ning töötav prototüüp mis tõestab et signaalitee (süstal→andur→ESP32), suhtlusprotokoll (GPIO+HTTP) ja kontrolliloogika (rõhk→roboti liikumine) käivad kokku.

### Labori struktuur

#### Osa 1: Signaalitöötluse valik

Labor 1 andis meile pingejaguri tulemused. Nüüd prototüüpime op-amp variandi breadboardil või prototüübiplaadil. LM358N dual op-amp: üks pool nihutab signaali 0.2V allapoole, teine pool skaleerib ülemise otsa 3.2V peale. Mõõdame täpsust oscilloskoobiga, teeme samad 30 mõõtmist (1ml, 5ml, 9ml) Jupyter Labis ja võrdleme pingejaguriga. Otsustame hinna, täpsuse ja arendusaja põhjal.

#### Osa 2: PCB disain

Võtame valitud lahenduse ja joonistame Fusionis trükiplaadi mis ühendab MPX5700AP, signaalitöötlusringi (pingejagur VÕI op-amp), ja M5 Atom Lite liidese. Labor lõpeb Gerber failidega mis on JLCPCB tellimiseks valmis.

#### Osa 3: Roboti integratsioon

Kasutame olemasolevat prototüüpi (breadboard setup) et testida kogu ahelat:

* GPIO äratamine: vajutad nuppu ESP32 peal, ESP32 sikutab GPIO otsikut, UR5 ärkab  
* HTTP suhtlus: robot saadab GET päringu, ESP32 vastab rõhuväärtusega  
* Kontrolliloogika: robot teisendab rõhu pöördenurgaks ja liigutab pead

See osa annab funktsionaalse kinnituse et kontseptsioon töötab enne kui läheme lõpliku PCB juurde.

### Tehnilised ülesanded

#### Signaalitöötluse prototüüp:

* Ehita LM358N vooluahelad breadboardil  
* Kalibreeri nihutus ja skaleerimine  
* Mõõda oscilloskoobiga signaalikvaliteeti  
* Dokumenteeri komponendid ja kulud

#### Võrdlusanalüüs (Jupyter Lab):

* 30 mõõtmist op-amp lahendusega (10 × 1ml, 10 × 5ml, 10 × 9ml)  
* Teisenda ADC väärtused Pascaliteks  
* Arvuta resolutsioon ja müratase  
* Võrdle Labor 1 pingejaguri tulemustega  
* Otsusta: hind/täpsus/kompleksus balanss

#### PCB disain (Fusion):

* Skemaatiline joonis valitud lahendusest  
* Komponentide paigutus  
* Traceide tõmbamine  
* Design Rule Check  
* Gerber failide genereerimine JLCPCB spetsifikatsioonide järgi

#### Roboti funktsionaalne test:

* GPIO pinni konfigureerimine ESP32 ja UR5 vahel  
* HTTP API loomine ESP32-le (endpoint rõhu lugemiseks)  
* UR5 programmi kirjutamine: GPIO kuulamine → HTTP GET → rõhu lugemine → pea pööramine  
* Testimine: süstal→rõhk→robot reageerib

*See on elav dokument, uuenda eesmärke kui need töö käigus muutuvad, uued teadmised muudavad vanad eesmärgid pahtiti mõttetuks. Eesmärk on et hoida meeskonda kogu aeg sihil, et ei eksitaks detailide metsa ära ja põhi probleem jääb lahendamata*

### Taustainfo

* **Fusion**  
  Esimene trükiplaat: [https://www.youtube.com/playlist?list=PLmA\_xUT-8UlL80Xm8Gxz98YNum3I9GInr](https://www.youtube.com/playlist?list=PLmA_xUT-8UlL80Xm8Gxz98YNum3I9GInr)  
  Või  
  [https://www.youtube.com/watch?v=H6CNmnT6kGo](https://www.youtube.com/watch?v=H6CNmnT6kGo)  
  Kuidas tellimus ette valmistada JLCPCB jaoks:  
  [https://www.youtube.com/watch?v=Ufu4nr0PfIc](https://www.youtube.com/watch?v=Ufu4nr0PfIc)  
* **UR5 robot**  
  Mannual: [https://www.universal-robots.com/download/manuals-cb-series/user/ur5/16/user-manual-ur5-cb-series-sw16-english-us/](https://www.universal-robots.com/download/manuals-cb-series/user/ur5/16/user-manual-ur5-cb-series-sw16-english-us/)  
  GPIO:  
  [https://www.universal-robots.com/articles/ur/interface-communication/connecting-internal-inputs-and-outputs-io-on-the-robots-controller/](https://www.universal-robots.com/articles/ur/interface-communication/connecting-internal-inputs-and-outputs-io-on-the-robots-controller/)  
* **LM358N**  
  Kes ja mis on opamp: [https://www.youtube.com/watch?v=kbVqTMy8HMg](https://www.youtube.com/watch?v=kbVqTMy8HMg)  
  Kirjeldus kuidas dual opampi kasutada: [https://www.hnhcart.com/blogs/learn/lm358-ic-and-its-applications?srsltid=AfmBOopTLVTs58AWnydEefADw4rA58yyP0q2xIXfWn7fCmtJJsc2qgXH](https://www.hnhcart.com/blogs/learn/lm358-ic-and-its-applications?srsltid=AfmBOopTLVTs58AWnydEefADw4rA58yyP0q2xIXfWn7fCmtJJsc2qgXH)  
  Kasuta ühte poolt et nihutada signaali 0.2V allapoole ja skalleri ülemine ots ca 3.2V peale teise poolega LM358N’iga  
* **Analoog digitaal liidese loogika**  
  Ja kuidas need kõik sõltuvad opampidest  
  [https://www.youtube.com/watch?v=g4BvbAKNQ90](https://www.youtube.com/watch?v=g4BvbAKNQ90)

*Lisa siia omapoolseid allikaid ja kasuliku informatsiooni mis aitaks sul projektis aru saada aastaid hiljem kui selle uuesti lahti teed.*

### Vahendid

1. M5 Atom  
2. MPX5010DP  
3. Arduino IDE  
4. MS Code  
5. Git  
6. Ossilliscope  
7. Multimeter  
8. UR5  
9. Ruuter?

*Kui plaan muutub siis muuda ka vahendeid, või thee [draw.io](http://draw.io)’s joonis kuidas asjad funktsionaalselt seostuvad.*

### Projekti üleshitus

- [ ] Opamp simulatsioon (nihe ja skaleerimine)  
- [ ] Signaalitöötluse prototüüp  
- [ ] Täpsuse määramine protüüp v2’le  
- [ ] Võrdlusanalüüs  
- [ ] PCB disain  
- [ ] M5 Atom trakvara parandused robotiga liidestuseks  
- [ ] Roboti funktsionaalne test

*Kaugel oled? Millal valmis saad? Kuidas kiiremini saaks? \- need tavalised küsimused*

### Simulatsioon

Sul on MPX5700AP mis annab 0.2V kuni 4.7V. ESP32 ADC tahab 0V kuni 3.3V. Kaks probleemi: vale alguspunkt ja vale pinge.

**Esimene op-amp:** Nihutab signaali 0.2V allapoole. Nüüd on sul 0V kuni 4.5V.

**Teine op-amp:** Skaleerib 4.5V vahemiku umbes 3.2V peale. Jätad 0.1V puhverruumi et ADC ei satureeruks.

#### Mida teha simulaatoris

**Näide 1:** Ehita summeeriv võimendi mis võtab 0.2V DC nihke maha. Määra  takistite väärtused ja kirjelda kuidas need väärtused valisid.

**Näide 2:** Ehita mitteinverteeriv võimendi teguriga alla ühe (atenuaator) mis pressib 4.5V vahemiku 3.2V peale. Jälle \- määra  takistite väärtused ja kirjelda kuidas need väärtused valisid.

### Miks simuleerida

Testi vead vooluahelas odavalt ekraanil, mitte breadboardil. Kui aasta pärast tagasi tuled, näed kohe miks sa valisid just need komponendid. Muuda parameetreid, vaata mis juhtub, õpi kuidas ahel käitub enne kui komponente kastst otsima lähed.

### Analüüs

**Võrdlusanalüüs**

Võrdle pingejagurit (Labor 1\) ja op-amp lahendust:

* Täpsus: ADC müratase ja resolutsioon mõlema puhul  
* Hind: komponentide kogumaksumus  
* Arendusaeg: kui kaua kulus prototüübi ehitamiseks, kuidas arenduse kulu jaguneb tootele  
* Protsessi keerukuse hinnang

**Nõuded**

Määra minimaalne täpsus mida vajad. Kui täpne peab rõhumõõtmine olema et robot saaks dispenserit efektiivselt kasutada?

**Automatiseerimine**

Tee testskript mis kontrollib automaatselt:

* ADC loeb andurit korrektselt (võrdle teadaoleva rõhuga)  
* Signaalitöötlus ei satureeru äärmistel väärtustel  
* …

*Need on kaks esimest näidet, lisa siia järgmised testid et kui hakkad sellele projektile uusi osasi lisama siis saad kontrollida et põhi osa pole katki läinud automaatselt \- kui seda tööd teha käsitsis siis see on kuhu läheb enamus projekti ressursi\!*

### Arenduslogi

### Tulemuised

Git repo:  
Readme:  
Arenduslogi:

### Tagasiside

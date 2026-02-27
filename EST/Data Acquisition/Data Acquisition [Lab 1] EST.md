## Andmehõive: Labor 1

### Eesmärk

On ehitada rõhumõõdiku makett mida hiljem kasutada süstla dosaatori rõhu juhtimiseks. Ehitame tehnoloogia maketti kus on põhilisest funktsionaalsest komponentis ja skelett kasutajaliidesest, kasutame MPX5700AP sensorit ja ESP32 põhist M5 Atom Lite juhtmoodulit. Differentsiaalrõhu sensorile ühendamine plastik toruga süstla ja üritame reaalajas näidata rõhku koduleheküljele (\~4hz).

Määrame süsteemi täpsuse ja mõõtetiheduse (resolutsioon)

*See on elav dokument, uuenda eesmärke kui need töö käigus muutuvad, uued teadmised muudavad vanad eesmärgid pahtiti mõttetuks. Eesmärk on et hoida meeskonda kogu aeg sihil, et ei eksitaks detailide metsa ära ja põhi probleem jääb lahendamata*

### Taustainfo

* **Elektroonika alused**  
  tinkercad: [https://www.tinkercad.com/circuits](https://www.tinkercad.com/circuits)  
  falstad sim: [https://www.falstad.com/circuit/circuitjs.html](https://www.falstad.com/circuit/circuitjs.html)

*Lisa siia omapoolseid allikaid ja kasuliku informatsiooni mis aitaks sul projektis aru saada aastaid hiljem kui selle uuesti lahti teed.*

### Vahendid

1. M5 Atom  
2. MPX5010DP  
3. Arduino IDE  
4. MS Code  
5. Git  
6. Ossilliscope

*Kui plaan muutub siis muuda ka vahendeid, või thee [draw.io](http://draw.io)’s joonis kuidas asjad funktsionaalselt seostuvad.*

### Projekti üleshitus

- [ ] Alusprojekt (joonis ja kirjeldus)  
- [ ] rõhu test ossiloskoobiga  
- [ ] muuda html lehtne nii et oleks ainult rõhu näitamine ja wifi setup  
- [ ] ühenda rõhuandur M5 Atomi külge  
- [ ] Lisa vajali API endpoint ja testi  
- [ ] Jupyter lab resultsiooni analüüs

*Kaugel oled? Millal valmis saad? Kuidas kiiremini saaks? \- need tavalised küsimused*

### Simulatsioon

Esimesel projektil on elektrooika aluste õppimisest põhi osa simulaatoritel, palun esitage 1 simulatsioon ja seletus millist osa protsessist testitiste ja mida õppisite

### Analüüs

#### Määra resolutsioon ja diapasson digitaalsele süsteemile

Loo jupyter lab töövihik, mõõåda 30x rõhkus (vähe, keskmine, palju) luues süstalaga rõhu kolbi sisse surudes kas 1ml, 5ml või 9ml

#### Loos Pascalites skaala

Loo arevestuslik skaala Pascalites, paku välja kuidas testida kas kogu skaala ulatuses on viga lineaarne

#### Analüüsi ülesehitus

##### Jupyter Lab töövihiku ettevalmistamine

1. Loo uus notebook  
2. Impordi andmeanalüüsi teegid  
3. Loo funktsioon ESP32-st andmete lugemiseks

##### Katseprotokoll: 30 mõõtmist kolmes kategoorias

Madal rõhk (1ml):

* 10 mõõtmist süstlaga 1ml õhku  
* Salvesta andmed

Keskmine rõhk (5ml):

* 10 mõõtmist süstlaga 5ml õhku  
* Salvesta andmed

Kõrge rõhk (9ml):

* 10 mõõtmist süstlaga 9ml õhku  
* Salvesta andmed

### **Analüüsi ülesanded**

1. **Pascali skaala loomine** \- teisenda ADC väärtused Pascaliteks MPX5700AP valemi järgi  
2. **Lineaarsuse test** \- kontrolli kas seos süstla mahu ja rõhu vahel on lineaarne  
3. **Resolutsiooni määramine** \- arvuta müra tase ja efektiivne resolutsioon

*Need on kaks esimest näidet, lisa siia järgmised testid et kui hakkad sellele projektile uusi osasi lisama siis saad kontrollida et põhi osa pole katki läinud automaatselt \- kui seda tööd teha käsitsis siis see on kuhu läheb enamus projekti ressursi\!*

### Arenduslogi

### Tulemuised

Git repo:  
Readme:  
Arenduslogi:

### Tagasiside

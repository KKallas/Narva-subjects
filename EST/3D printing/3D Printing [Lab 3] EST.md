## 3D printimine ja CAD: Labor 3

### Eesmärk

Disaini ja prindi esimene funktsionaalne korpus süstlahoidikule, mis integreerib kõik vajalikud komponendid üheks töötavaks tervikuks. See ei ole enam prototüüp breadboardil—nüüd peab kõik mahuma kompaktsesse ja funktsionaalsesse korpusesse.

#### Disainikitsendused

Lahendus peab arvestama järgmisi nõudeid:

**Pneumaatiline süsteem:** Rõhuandur ja solenoidklapp peavad olema süstlale võimalikult lähedal. Eesmärk on minimeerida "surnud" õhumaht süsteemis—iga lisakuupsentimeeter voolikut ja õõnsust lisab viivitust ja vähendab täpsust. Mida lühem on tee kompressorilt süstlani, seda kiiremini reageerib süsteem ja seda vähem energiat läheb kaduma rõhu ülesehitamiseks tühjas ruumis.

**~~Elektritoide:~~** ~~Kuna UR5 digital IO on 24V, on mõistlik toita ka ESP32 moodulit samast allikast läbi pingeregulaatori. Liskas kasutame siis veel kahte pingeregulaatorit 24V-\>12V Solenoidi jaoks ja 24V-\>5V Atomi jaoks. 24V toiteplokk läheb roboti kontrolleri kasti ja peaks olema piisavalt jõuline nii solenoidile (tüüpiliselt 0.5-1A) kui ESP32-le (maksimaalselt 500mA koos perifeeriaga).~~

**Elektritoide:** Kuna UR5 digital IO on 24V, on mõistlik toita ka ESP32 moodulit samast allikast läbi pingeregulaatori. Lisaks kasutame pingeregulaatorit 24V→5V Atomi jaoks. Solenoid on 24V, seega saab seda toita otse 24V toiteallikast (läbi relee või MOSFET-i, mida ESP32 juhindab). 24V toiteplokk läheb roboti kontrolleri kasti ja peaks olema piisavalt jõuline nii solenoidile (tüüpiliselt 0.5-1A) kui ESP32-le (maksimaalselt 500mA koos perifeeriaga).

**Signaalide edastamine:** ESP32 peab saatma signaale roboti kontrollerisse—kas digitaalsed või analoogsed sõltuvalt sellest, mida mõõdad ja kuidas roboti tarkvara on seadistatud. Need signaalid peavad olema usaldusväärsed ja mürakindlad, sest roboti liigutused ja solenoidklapi lülitamine tekitavad elektromagnetilist häiret.

Analoogsignaalide jaoks tuleb ESP32 väljund (0-3.3V) võimendada op-amp'iga roboti 0-10V analoogsisendi vahemikku. Digitaalsignaalide jaoks on kaks head võimalust ESP32 3.3V loogika tõstmiseks roboti 24V sisendile: MOSFET (näiteks 2N7002) koos pull-up takistiga 24V poole, või optokulper (näiteks PC817) kui soovid galvaanilist eraldust ja lisakaitset.

WiFi ruuter on ühendatud nii robotiga kui ESP32-ga, võimaldades võrgusuhtlust läbi protokollide nagu Modbus TCP/IP.

**PCB kui konstruktsioonielement:** Kuna elektroonika tuleb niikuinii süstla lähedale, ära raiska seda võimalust—kasuta PCB plaati mehhaanilise tugevuse osana. Protsess on järgmine: prindi esmalt eraldi raam, seejärel prindi korpuse toorik koos avaga PCB jaoks. Peata print õigel kõrgusel, aseta PCB avasse ja pane raam PCB peale nii, et see toob plaadi ääred kõige kõrgema komponendi ja augu sügavusega tasaseks. Nüüd jätka printimist pealt kinni—raam hoiab PCB õiges positsioonis ja tagab tugeva kinnituse. Nii saab plaat osaks konstruktsioonist, sarnaselt sellele kuidas keermelatid või terastorud annavad lisajäikust. PCB annab tugevust just seal, kus elektroonika asub, ja vähendab eraldiseisvate tugikonstruktsioonide vajadust.

**Mehaaniline tugevus:** Roboti liigutused tekitavad inertsijõude, süstlasse surumise ajal tekib reaktsioonijõud, ja kogu konstruktsioon peab seda taluma ilma paindumata. Kasuta 16mm läbimõõduga torusid ja M5 keermelatte tugevuse suurendamiseks. Võid kas printida need sisse pausiga (disaini ava, peata print, aseta element, jätka printimist) või kinnitada hiljem kokku eraldi kruvide ja klipsidega. Mõlemad on aktsepteeritud—oluline on, et konstruktsioon ei paine ega värrise kasutamise ajal.

### Funktsionaalsed nõuded

Korpus peab täitma järgmisi funktsioone:

**Roboti külge kinnitamine:** Süstal peab kinnituma roboti otsiku külge turvaliselt ja täpselt. Kinnituspunkt peab olema piisavalt jäik, et süstla asukoht ruumis oleks ennustatav.

**Pneumaatiline doseerimine:** Süstla tagumise otsa külge keeratakse pneumaatiline otsik (keeratav kork vooliku otsas), mis võimaldab suruda kolviga silikooni välja kontrollitud kogustes. Iga süstla vahetuse ajal tuleb pneumaatiline otsik käsitsi lahti keerata vanalt süstlalt ja kinni keerata uuele süstlale. Korpuse disain peab võimaldama lihtsat juurdepääsu süstla tagumisele otsale, et otsiku vahetamine oleks mugav ilma korpuse osade eemaldamata.

**Kiire vahetus:** Süstlat peab saama vahetada lihtsalt ja kiiresti ilma tööriistadeta. Mõtle selle peale nagu kiirvahetuskinnitust—klõpsa lahti, võta vana süstal välja, pane uus sisse, klõpsa kinni. Kui süstal on õiges kohas ja lukustunud, peaks olema selge tagasiside: kuuldav klõps, nähtav äärejoon mis jääb tasaseks korpusega, või mehaaniline tunne et lukustusmehhanism on täielikult kohale läinud. Operaator ei tohiks pidama jääma kahtlema, kas süstal on korralikult kinni või mitte.

**Ohutuselemendid:** M5 Atom Lite peab olema süstla lähedal ja selle nuppu saab kasutada hädapeatus-nupuna kui midagi läheb valesti. See annab operaatorile füüsilise kontrolli süsteemi üle ka siis, kui roboti tarkvara ei reageeri või ühendus katkeb.

**Välised ühendused:** 24V toiteplokk ja GPIO ühendused paiknevad roboti kontrolleri kastis—see tähendab, et sinu korpusest peavad tulema kaablid, mis ulatuvad sinna. Arvesta kaablite tee pikkusega ja võimalusega neid korralikult kinnitada, et need ei jääks roboti liigutuste alla.

*See on elav dokument, uuenda eesmärke kui need töö käigus muutuvad, uued teadmised muudavad vanad eesmärgid pahtiti mõttetuks. Eesmärk on et hoida meeskonda kogu aeg sihil, et ei eksitaks detailide metsa ära ja põhi probleem jääb lahendamata*

### Taustainfo

* **Komponent vs keha**  
  [https://www.youtube.com/watch?v=L6MMw-dfS8s](https://www.youtube.com/watch?v=L6MMw-dfS8s)  
* **Teras sisuga 3D trükk**  
  [https://www.youtube.com/watch?v=XpDG8VxZsw4](https://www.youtube.com/watch?v=XpDG8VxZsw4)  
* **Poldid ristipidi kihtidega**  
  [https://www.youtube.com/watch?v=cC5KlelZlx4](https://www.youtube.com/watch?v=cC5KlelZlx4)  
  Ja õpime teiste vigadest  
  [https://www.youtube.com/watch?v=A1d8aFPtQ8c](https://www.youtube.com/watch?v=A1d8aFPtQ8c)  
* **Fusioni projekt RPI Pico Box**  
  [https://www.youtube.com/watch?v=wt1nlLSl8TQ](https://www.youtube.com/watch?v=wt1nlLSl8TQ)  
* **Infill**  
  [​​https://www.youtube.com/watch?v=nV3GbN6hLjg](https://www.youtube.com/watch?v=nV3GbN6hLjg)

*Lisa siia omapoolseid allikaid ja kasuliku informatsiooni mis aitaks sul projektis aru saada aastaid hiljem kui selle uuesti lahti teed.*

### Vahendid

1. Fusion 360  
2. Prusa Core One  
3. Süstal 10ml N1  
4. Universal Robotics UR5 robot  
5. M5 Atom Lite  
6. PCB plaat (Labor 3 andmehõivest)  
7. Solenoidklapp 12V  
8. Pneumaatilised otsikud ja voolikud  
9. 24V toiteplokk (olenevalt konfiguratsioonist)  
10. ~~BUCK 24V-\>12V~~  
11. BUCK 24V-\>5V  
12. …

*Kui plaan muutub siis muuda ka vahendeid, või thee [draw.io](http://draw.io)’s joonis kuidas asjad funktsionaalselt seostuvad.*

### Projekti üleshitus

* **Osa 1: Komponentide skeem** Koosta skemaatiline diagramm (draw.io), mis näitab kõiki komponente: PCB, M5 Atom, solenoidklapp, rõhuandur, süstal, pneumaatilised ühendused, kaablid. Märgi ära, mis läheb korpuse sisse ja mis jääb välja.  
* **Osa 2: Sisemiste komponentide modelleerimine** Modelleeri Fusion 360s kõik sisemised komponendid ja planeeri, kuidas need print-pause meetodil sisse paigutada. Märgi pausipunktid ja veendu, et ülemised pinnad jäävad järgmise kihiga tasaseks.  
* **Osa 3: Väliskorpuse disain** Disaini väliskorpus, mis mahutab kõik komponendid ja vastab funktsionaalsetele nõuetele (kiire vahetus, mehaaniline tugevus, kaablite väljundid).  
* **Osa 4: Slicerimise plaan** Loo Prusa Sliceris printimisplaan koos pausidega. Dokumenteeri (video või ekraanitõmmised), millistes kohtades print peatub ja millised komponendid siis sisse paigutad.  
* **Osa 5: Printimine ja kokkupanek** Prindi korpus, paigalda komponendid, testi funktsionaalsust.

*Kaugel oled? Millal valmis saad? Kuidas kiiremini saaks? \- need tavalised küsimused*

### Arenduslogi

### Tulemuised

Vaata et hindamiseks oleks antud ikkagit kõik asjad et saaks:

* Tööfailid (**4** punkti): Fusion 360 failid  
* Simulatsioon (seekord skeem diagram komponentidest) (**4** punkti): draw.io  
* Prototüüp (**4** punkti):   
* Dokumentatsioon (**4** punkti): spetsifikatsioonid, disaini valikute põhjendused, kasutusjuhend

Fusioni projekt:  
Arenduslogi:  
Versioon 3 lähteülesanne:

### Tagasiside

## Nutilahendused: Labor 1

**Eesmärk** Luua M5Stack Atom Lite mikrokontrollerile veebiserver, mis jagab kasutajaliidesena ühte veebilehte ning pakub kahte teenuse lõpp-punkti (WEB API endpoint). Esimene versioon muudab sissehitatud LED-i värvi vastavalt sisendile.

**Funktsionaalsus**

Atomile on sisse ehitatud üks RGB SK seeria LED. Kasutame seda näidisfunktsionaalsusena, et juhtida kaugelt veebiliidese kaudu, kasutades REST-põhiseid API lõpp-punkte:

* **GET /get** – tagastab hetke värvi 8-bitise RGB väärtusena HEX kodeeringus, kus `#000000` on must ja `#FFFFFF` on valge. Värvi järjekord on punane, roheline, sinine.  
* **GET /set?value=\<väärtus\>** – seadistab LED-i värvi vastavalt saadud väärtusele. Väärtus on string, mis algab märgiga \# ja on HEX kodeeringus RGB väärtus.

Serveeritav veebileht on lihtne JavaScriptiga rikastatud rakendus, mis kuvab LED-i hetke väärtust, sisaldab värviratast uue väärtuse määramiseks ning võimaldab kasutajal muuta WiFi võrgu SSID-i ja parooli seadistus nupu kaudu.

**Turvalisus**: Esimene versioon töötab ainult AP režiimis, seega eeldame, et füüsiline lähendus võrdub autoriseeritud ligipääsuga seadmele. WiFi infrastruktuuri ja VPN-i lisamisel tuleb ka paketid allkirjastada kasutaja õiguste kontrollimiseks.

**Arenduse põhimõtted**: Arenda väikeste sammudega, kasuta debugimiseks print funktsiooni. Kui väiksed osad töötavad, hakka neid kokku panema tervikprojektiks. Kasuta git repositooriumit.

*See on elav dokument, uuenda eesmärke kui need töö käigus muutuvad, uued teadmised muudavad vanad eesmärgid pahtiti mõttetuks. Eesmärk on et hoida meeskonda kogu aeg sihil, et ei eksitaks detailide metsa ära ja põhi probleem jääb lahendamata*

### Taustainfo

* **M5 Atom**  
  Seade spesifiaktsioon, arduino valmis tarkvaranäited  
  [https://shop.m5stack.com/products/atom-lite-esp32-development-kit](https://shop.m5stack.com/products/atom-lite-esp32-development-kit)  
* **Arduino arenduskeskkond**  
  IDE(Integrated Development Environment/Integreeritud arenduskeskond) kus arendame ja testime M5 Atom’i peal jooksvat tarkvara  
  [https://docs.m5stack.com/en/arduino/arduino\_ide](https://docs.m5stack.com/en/arduino/arduino_ide)  
* **Print debug**  
  Kun ESP32 vajab eraldi debuggerit(silur) ja Atom’il ei ole neid klemme välja toodud siis kõige mõistlikum lahendus on kasutada serial terminali arenduse käigus vea otsimiseks.  
  [https://docs.arduino.cc/language-reference/en/functions/communication/serial/print/](https://docs.arduino.cc/language-reference/en/functions/communication/serial/print/)  
* **WiFi AP ja HTTP  server**  
  Kuidas seadistada WiFi AP ja näidis kood HTTP serveri loomiseks  
  [https://randomnerdtutorials.com/esp32-web-server-beginners-guide/](https://randomnerdtutorials.com/esp32-web-server-beginners-guide/)  
* **MS Code ja Jupyter lab**  
  Töövahendid et luua qr generaator ja automaatsed testid  
  [https://code.visualstudio.com/docs/datascience/jupyter-notebooks](https://code.visualstudio.com/docs/datascience/jupyter-notebooks)  
* **Git**  
  Kuidas luua arendusprojekti repositoorium mida saab mitu inimest kasutada  
  [https://www.youtube.com/watch?v=fK6jAzQvfRg](https://www.youtube.com/watch?v=fK6jAzQvfRg)  
  Ning kuidas kasutada MS Code’is  
  [https://code.visualstudio.com/docs/sourcecontrol/overview](https://code.visualstudio.com/docs/sourcecontrol/overview)  
* **Võibolla on sinuga kaa juhtunud**  
  Erinevad probleemid ja lahendused kui tegeled ESP arendusega  
  [https://randomnerdtutorials.com/esp32-troubleshooting-guide/](https://randomnerdtutorials.com/esp32-troubleshooting-guide/)

*Lisa siia omapoolseid allikaid ja kasuliku informatsiooni mis aitaks sul projektis aru saada aastaid hiljem kui selle uuesti lahti teed.*

### Vahendid

1. M5 Atom  
2. Arduino IDE  
3. MS Code  
4. Git

*Kui plaan muutub siis muuda ka vahendeid, või thee [draw.io](http://draw.io)’s joonis kuidas asjad funktsionaalselt seostuvad.*

### Projekti üleshitus

- [ ] Arduino arenduskeskkond M5Stacki toodete jaoks  
- [ ] WiFi ühendus  
- [ ] HTTP ja js lehekülg  
- [ ] get/set funktsionaalsus  
- [ ] Jupyter lab qr generator

*Kaugel oled? Millal valmis saad? Kuidas kiiremini saaks? \- need tavalised küsimused*

### Simulatsioon

Kuna päris solenoidklapi simulatsioon on keeruline, on selle projekti jaoks loodud väike **tööriist QR-koodide genereerimiseks** (Jupyter Lab'i keskkonnas).

Tööriista eesmärk on lihtsustada seadme kasutamise algust:

1. Kui **Atom on arvutiga otse ühendatud** (USB või WiFi kaudu), saab tööriist automaatselt tuvastada ja kuvada vajalikud seadistused:  
* WiFi võrgu nimi (SSID)  
* WiFi parool  
* Krüptograafiline võti (autentimiseks)  
2. Kui automaatne tuvastamine ei toimi, tuleb need väärtused sisestada käsitsi.  
3. Tööriist genereerib sisestatud andmete põhjal QR-koodi.  
4. Kasutaja saab oma telefoniga skannida selle QR-koodi, mis ühendab telefoni automaatselt Atomile loodud WiFi-võrku ja avab veebilehe klapi juhtimiseks.

Seejärel saab klappi juhtida otse telefoni brauserist.

### Testimine

#### Testinäide 1: LED värvi uuendamise visuaalse sujuvuse test

See test määrab kasutaja tagasiside põhjal optimaalse värvimuutmise sageduse, et tagada sujuv kasutajakogemus.

Test töötab interaktiivselt ja hindab täisahela piirangute mõju visuaalsele kvaliteedile. Alustab madala sagedusega ja suurendab järk-järgult kuni kasutaja märkab kvaliteedi langust.

**Protsess:** Test käivitab tsüklilise värvimuutuse (punane → roheline → sinine → punane) ja näitab seda 5 sekundit igal sagedusel. Alustab 1 Hz-st (üks muutus sekundis) ja suurendab järk-järgult: 2Hz → 5Hz → 10Hz → 20Hz → 50Hz. Pärast iga 5-sekundilist perioodi küsib: "Kas värvimuutused olid sujuvad ja selgelt eristatavad? (jah/ei)". Jätkab kuni kasutaja vastab "ei" \- see märgib punkti, kus LED hakkab vilkuma liiga kiiresti või jätab värve vahele.

**Tulemus:** Viimane "hea" sagedus salvestatakse kui optimaalne värvimuutmise kiirus veebiliidese jaoks. See annab praktilise ülempiiri, mida kasutada throttling seadistamiseks \- kui kasutaja lohistab värvirattal kiiresti, saata värvimuutmise käske mitte rohkem kui leitud optimaalne sagedus.

Tee testist video kus on näha M5 Atom’i led ja ekraanil toimuv

#### Testinäide 2: ESP32 ülekoormuse ja stabiilsuse test

Test kontrollib süsteemi käitumist äärmuslike tingimuste korral ja määrab kindlaks, millal ESP32 hakkab käske kaotama või täielikult kinni jookseb.

Testimise eesmärk on leida praktilised piirangud, et veebiliides saaks ennetada süsteemi ülekoormust ja tagada graceful degradation intensiivse kasutamise korral.

**Eskaleeruv koormustest:** Alustab 10 SET käsuga sekundis, saates juhuslikke RGB väärtusi. Suurendab järk-järgult kuni 100+ käsuni sekundis. Jälgib HTTP vastuse aegu ja märgib, millal vastused muutuvad aeglasemaks (\>500ms) või jäävad täiesti välja. Kontrollib GET käskudega (kontrolli programmi koodist et LEDi olek  oleks oleks uuendatud pärast LEDi enda uuendamist), kas seadistatud värvid jõuavad tegelikult LED-ile või jäävad mõned käsud vahele. Määrab kindlaks kritilise punkti, kus seade hakkab käituma ebastabiilselt.

**Taastumistest:** Kui seade on ülekoormatud, lõpetab käskude saatmise täielikult. Kontrollib, kas süsteem taastub automaatselt ja kui kiiresti. Testib, kas viimane saadetud värv jääb LED-ile õigesti püsima. Verifitseerib, et API vastab uuesti normaalselt pärast taastumist.

**Praktiline väärtus:** Annab konkreetsed numbrid veebiliidese jaoks \- kui kiiresti võib kasutaja värviratast lohistada enne, kui süsteem hakkab maha jääma. Võimaldab implementeerida intelligentset throttling-ut, mis hoiab süsteemi stabiilsena ka intensiivse kasutamise korral.

*Need on kaks esimest näidet, lisa siia järgmised testid et kui hakkad sellele projektile uusi osasi lisama siis saad kontrollida et põhi osa pole katki läinud automaatselt \- kui seda tööd teha käsitsis siis see on kuhu läheb enamus projekti ressursi\!*

### Arenduslogi

### Tulemuised

Git repo:  
Readme:  
Arenduslogi:  
Jupyter qr generator file:  
Test log:

### Tagasiside

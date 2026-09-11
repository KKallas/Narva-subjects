# Roboti kokkupaneku juhend

## 1. Kasutatavad komponendid / BOM

| Komponent | Kogus | Link / tootekood | Ühiku hind | Rea hind | Märkused |
|---|---:|---|---:|---:|---|
| ESP32-PICO / M5Stack Atom Matrix | 1 | [Mouser: C008-B-V11](https://www.mouser.ee/ProductDetail/M5Stack/C008-B-V11?qs=y9%2FpVxnqej%2FAOC1wJ%2FMV8g%3D%3D) | 12,86 € | 12,86 € | Roboti põhimikrokontroller. |
| M5Stack AtomS3R M12 kaameramoodul / OV3660 camera module | 1 | [Mouser: C126-M12](https://www.mouser.ee/ProductDetail/170-C126-M12) | 20,60 € | 20,60 € | Kasutatakse pilditöötluseks / objekti tuvastuseks. |
| DFRobot DRI0044 TB6612 Dual DC Motor Driver | 1 | [Mouser: DRI0044](https://www.mouser.ee/ProductDetail/426-DRI0044) | 3,87 € | 3,87 € | Kahe DC mootori juhtimiseks. |
| 6 V DC reduktormootor, 150 RPM mudel | 2 | [AliExpress: 1005006908511003](https://www.aliexpress.com/item/1005006908511003.html) | 3,47 € | 6,94 € | Vasak ja parem veomootor. Valida 150 RPM variant. |
| Pimoroni VL53L1X Time-of-Flight kaugusandur | 1 | [Mouser: PIM373](https://www.mouser.ee/ProductDetail/397-PIM373) | 16,43 € | 16,43 € | Eesmine kaugusandur. |
| DFRobot 18650 battery holder | 1 | [Mouser: DFR0969](https://www.mouser.ee/ProductDetail/426-DFR0969) | 9,50 € | 9,50 € | 2 × 18650 akuhoidik. Akud on rööbiti, seega robot töötab vajadusel ka ühe akuga. |
| 18650 Li-ion aku, BAK N18650CL 2900 mAh 8.25 A 3.6 V | 2 | [Patareid.ee: BAK N18650CL](https://www.patareid.ee/en/products/bak-n18650cl-2900mah-825a-36v-li-ion-battery-1pc/) | 4,95 € | 9,90 € | Soovituslikult kasutada kahte sama tüüpi ja sarnase seisukorraga akut. |
| Prinditav kere | 1 komplekt | Failid `3dprint` kaustas | 20 €/kg | 2,00 € | Kere, rattad, roomikud, ratta insertid ja kaamerahoidja. Arvestatud filamentkulu 99,98 g. |
| Kruvid M3 × 8 mm | 2 | Akuhoidiku komplektist | - | - | Akuhoidiku originaalkruvid lähevad taaskasutusse. |
| Kruvid M3 × 20 mm | 2 | - | - | - | Akuhoidiku ja kaamerahoidja kinnitamiseks. |
| Väikesed jämeda keermega / coarse thread kruvid | 2 | Mõõt täpsustamisel | - | - | TOF sensori kinnitamiseks roboti etteotsa. |
| Dupont juhtmed / ühendusjuhtmed | Vajaduse järgi | - | - | - | Kulumaterjal. Ühendused tehakse eraldi pinouti faili järgi. |

**Teadaolev koguhind koos filamentkuluga:** 82,10 €

---

## 2. Kere valmistamine

Roboti kere detailid tuleb 3D-printida. Kõik vajalikud failid asuvad projekti `3dprint` kaustas.

Printida tuleb järgmised komponendid:

| Detail | Kogus | Fail / nimi | Printimise märkus | Eeldatav filamentkulu |
|---|---:|---|---|---:|
| Roboti põhikere | 1 | Shell.stl | Supports = enabled | 45 g kokku, millest umbes 15 g on supportid |
| Rattad koos insertidega | 4 komplekti | SMARS failid | Tavalised SMARS rattad koos sisudega | 30 g kokku |
| Roomiku lülid | 32 | SMARS failid | 16 lüli kummalegi küljele | 0,64 g / lüli, kokku 20,48 g |
| Kaamerahoidja | 1 | cameramount2.stl | Väike eraldi detail | 4,5 g |

**Teadaolev filamentkulu kokku:** 99,98 g  
**Sellest supportid:** umbes 15 g  
**Reaalne detailide kaal ilma kere supportideta:** umbes 84,98 g

### 2.1. 3D-printimise üldised seaded

| Seade | Väärtus |
|---|---|
| Perimeetrid / loopid / walls | 2 |
| Infill | 15% |
| Supportid | Kere jaoks enabled |
| Materjal | PLA või PETG |
| Kihi kõrgus | 0,2 mm |

### 2.2. 3D-printimise juhised

1. Ava `3dprint` kaustas olevad mudelid slicer-programmis.
2. Kontrolli, et kõik vajalikud detailid oleksid printimiseks valitud.
3. Kasuta 2 loopi / seina ja 15% infilli.
4. Roboti põhikere printimisel lülita supportid sisse.
5. Prindi kõik kere detailid välja.
6. Pärast printimist eemalda põhikere supportid. Kere puhul on eeldatav kogukulu umbes 45 g, millest umbes 15 g moodustavad supportid.
7. Puhasta detailid ja kontrolli, et snap-fit kinnitused, mootori pesad ja kruviaugud oleksid vabad.
8. Kontrolli enne lõplikku kokkupanekut, et mootorid, driver, ESP32-PICO / Atom Matrix ja akuhoidik sobituksid oma pesadesse.


---

## 3. Elektroonika valmistamine

Kõik elektrilised ühendused tehakse eraldi pinouti faili järgi. Selles juhendis ei ole pinouti dubleeritud, et vältida erinevate versioonide tekkimist.

Enne lõplikku kokkupanekut tuleb teha vajalikud jootmistööd.

### 3.1. Mootorite ettevalmistamine

Mõlemale 6 V DC reduktormootorile tuleb külge joota kaks juhet.

1. Lõika või vali sobiva pikkusega juhtmed.
2. Jooda kummagi mootori klemmidele kaks juhet.
3. Juhtmete teise otsa peab jääma Dupont pistik või muu sobiv ühendus, millega saab juhtmed ühendada mootori driveri külge.
4. Vajadusel märgi vasak ja parem mootor, et hiljem oleks lihtsam juhtmeid ühendada.

**Märkus:** kui mootor liigub hiljem vales suunas, saab mootori suuna parandada kas juhtmete polaarsuse vahetamisega või tarkvaras mootori suuna ümberpööramisega.


### 3.2. Mootori driveri ettevalmistamine

DFRobot DRI0044 TB6612 mootori driverile tuleb joota pikad isased pin-id.

1. Aseta pin-headerid driveri plaadile õigesse asendisse.
2. Jooda pin-id plaadi külge.
3. Kontrolli, et ükski jootekoht ei oleks lühises kõrvaloleva pin-iga.
4. Kontrolli, et Dupont juhtmeid oleks võimalik mugavalt külge ühendada.

Kuna motor driveri pinout PCBl on teisele küljele märgitud siis on mõistlik kasutada seda abistavat pilti:
![Dual motor driver TB6612](https://gitlab.ut.ee/margo.mols/rar-tartu-protyypimine/-/raw/master/media/tb6612.png){:height="50%" width="50%"}

### 3.3. Akuhoidiku / toiteplaadi ettevalmistamine

Battery holderile tuleb joota vajalikud toiteühendused.

Joota tuleb:

| Toiteliin | Vajalik ühendus |
|---|---|
| 5 V | 3 × `5V` ja `GND` pin |
| 3.3 V | 1 × `3.3V` ja `GND` pin |

Neid ühendusi kasutatakse komponentide toitmiseks. Täpne ühendusloogika tuleb teha pinouti faili järgi.

1. Jooda battery holderile vajalikud pin-id.
2. Kontrolli jootekohti.
3. Veendu, et 5 V ja 3.3 V pooled ei oleks omavahel lühises.
4. Enne komponentide ühendamist kontrolli võimalusel multimeetriga, et väljundpinged oleksid õiged.


---

## 4. Üldine kokkupaneku järjekord

Enamik roboti komponente kinnitub kere külge snap-fit kinnitustega. Kruve kasutatakse kaugusanduri, akuhoidiku ja kaamerahoidja kinnitamiseks.

### 4.1. Tee juhtmeühendused ette valmis

Enne komponentide kere külge paigaldamist on soovitatav valmistada ette kõik Dupont juhtmetega ühendused.

1. Võta ette eraldi pinouti fail.
2. Ühenda ESP32-PICO / M5Stack Atom Matrix, mootori driver, mootorid, TOF-andur, kaamera ja toide pinouti järgi.
3. Kontrolli, et kõik juhtmed oleksid piisava pikkusega, kuid ei jääks roomikute või rataste liikumisele ette.
4. Vajadusel märgi juhtmed, näiteks `vasak mootor`, `parem mootor`, `TOF`, `kaamera`, `5V`, `3.3V` ja `GND`.


### 4.2. Paigalda mootorid

1. Suru mõlemad 6 V reduktormootorid kere vastavatesse pesadesse.
2. Veendu, et mootorid istuksid kindlalt.
3. Kontrolli, et mootori juhtmed jääksid kere sisse või küljele nii, et need ei takistaks roomikuid.


### 4.3. Paigalda mootori driver

1. Suru DFRobot DRI0044 TB6612 driver kere vastavasse snap-fit pessa.
2. Ühenda mootori juhtmed driveri külge.
3. Ühenda driver ESP32-PICO / Atom Matrix külge pinouti faili järgi.
4. Ühenda driveri toide pinouti faili järgi.


### 4.4. Paigalda ESP32-PICO / M5Stack Atom Matrix

1. Suru ESP32-PICO / M5Stack Atom Matrix kere vastavasse snap-fit kinnitusse.
2. Ühenda kõik vajalikud signaalijuhtmed pinouti faili järgi.
3. Kontrolli, et USB-pesa jääks ligipääsetavaks, kui seda on vaja programmeerimiseks või testimiseks kasutada.


### 4.5. Paigalda VL53L1X kaugusandur

1. Aseta Pimoroni VL53L1X Time-of-Flight andur kere etteotsa.
2. Kinnita andur kahe väikese jämeda keermega / coarse thread kruviga.
3. Ühenda anduri juhtmed ESP32-PICO / Atom Matrix külge pinouti faili järgi.
4. Ühenda anduri 3.3 V toide ja GND.

![TOF sensor](https://gitlab.ut.ee/margo.mols/rar-tartu-protyypimine/-/raw/master/media/TOF.jpg){:height="50%" width="50%"}

### 4.6. Paigalda rattad, insertid ja roomikud

1. Paigalda ratta insertid rataste sisse.
2. Paigalda rattad roboti kerele / mootori võllidele.
3. Paigalda roomikud ratastele. Kokku on vaja 32 roomikulüli: 16 vasakule ja 16 paremale küljele.
4. Kontrolli käsitsi, et roomikud liiguksid vabalt ega hõõruks kere vastu.
5. Vajadusel puhasta või lihvi 3D-prinditud detaile kergelt, kui liikumine on liiga tihe.


### 4.7. Paigalda battery holder

Enne battery holderi kinnitamist tuleb selle alt eemaldada pleksiklaasist alus.

1. Eemalda battery holderi alumine pleksiklaasist alus.
2. Hoia alles kaks M3 × 8 mm kruvi, mis olid akuhoidiku küljes.
3. Aseta battery holder roboti kere peale õigesse asendisse.
4. Kinnita battery holder kere külge.
5. Veendu, et juhtmed ei jääks akuhoidiku alla pingesse või muljutud asendisse.

![Battery holder enne paigaldamist](https://gitlab.ut.ee/margo.mols/rar-tartu-protyypimine/-/raw/master/media/wiring.jpg){:height="50%" width="50%"}

![State of Charge indicator](https://gitlab.ut.ee/margo.mols/rar-tartu-protyypimine/-/raw/master/media/indicator.jpg){:height="50%" width="50%"}

Roboti sisselülitamiseks tuleb On/Off lülitit ühe korra vajutada ning väljalülitamiseks kaks kiiret vajutust. Laadida saab USB-C ning micro USB kaabliga. State of charge jaoks on 4 led-i. Robot töötab hästi ka ainult ühe akuga.

### 4.8. Paigalda kaamerahoidja ja kaamera

Kaamerahoidja kinnitamiseks kasutatakse kahte M3 × 20 mm kruvi.

1. Aseta kaamerahoidja battery holderi kohale õigesse asendisse.
2. Paigalda M3 × 20 mm kruvid nii, et need lähevad läbi roboti kere, läbi battery holderi ja kinnituvad kaamerahoidja külge.
3. Kinnita M5Stack AtomS3R M12 kaameramoodul kaamerahoidja külge.
4. Ühenda kaamera ESP32-PICO / Atom Matrix külge pinouti faili järgi.
5. Kontrolli, et kaamera oleks suunatud ettepoole ja ei oleks viltu.

![Front camera](https://gitlab.ut.ee/margo.mols/rar-tartu-protyypimine/-/raw/master/media/Baruto1.jpg){:height="50%" width="50%"}

---

## 5. Lõppkontroll enne käivitamist

Enne roboti sisselülitamist kontrolli järgmisi punkte:

| Kontrollitav koht | Olek |
|---|---|
| Kõik 3D-prinditud detailid on paigaldatud | ☐ |
| Mõlemad mootorid on kinnitatud | ☐ |
| Mootori juhtmed on joodetud ja driveriga ühendatud | ☐ |
| Mootori driver on kere küljes | ☐ |
| ESP32-PICO / Atom Matrix on paigaldatud | ☐ |
| VL53L1X TOF-andur on kinnitatud ja ühendatud | ☐ |
| Kaamera on kinnitatud ja ühendatud | ☐ |
| Battery holder on kinnitatud | ☐ |
| 5 V ja 3.3 V toiteühendused on kontrollitud | ☐ |
| Juhtmed ei jää roomikute ega rataste vahele | ☐ |
| Roomikud liiguvad käsitsi vabalt | ☐ |
| Pinouti faili järgi on kõik ühendused üle kontrollitud | ☐ |

---

## 6. Esmane testimine

1. Kontrolli veel kord, et toiteühendused oleksid õiged.
2. Lülita robot sisse.
3. Ühenda vajadusel ESP32-PICO / Atom Matrix arvutiga.
4. Laadi roboti tarkvara peale.
5. Testi eraldi:
   - vasakut mootorit;
   - paremat mootorit;
   - TOF kaugusandurit;
   - kaameramoodulit;
   - aku/toite toimimist.
6. Kui mootorid liiguvad vales suunas, vaheta vastava mootori juhtmete polaarsus või muuda suund tarkvaras.
7. Kui mõni andur ei tööta, kontrolli esmalt pinouti faili järgi ühendusi ning seejärel toitepinget.


---

## 7. Tüüpilised vead ja kontrollkohad

| Probleem | Võimalik põhjus | Kontroll / lahendus |
|---|---|---|
| Robot ei lülitu sisse | Aku puudub, tühi aku või vale toiteühendus | Kontrolli akut, 5 V ja GND ühendusi |
| Üks mootor ei tööta | Mootori juhtmed valesti ühendatud või halb joode | Kontrolli mootori jootekohti ja driveri ühendusi |
| Mootor liigub vales suunas | Mootori polaarsus on vastupidine | Vaheta mootori juhtmed omavahel või muuda suund tarkvaras |
| Mõlemad mootorid ei tööta | Driveril puudub toide või signaal | Kontrolli driveri 5 V/GND ja juhtsignaale pinouti järgi |
| TOF-andurit ei leita | Vale I2C ühendus või vale toide | Kontrolli SDA, SCL, 3.3 V ja GND ühendusi |
| Kaamera ei tööta | Vale UART ühendus või puuduv toide | Kontrolli kaamera ühendusi pinouti järgi |
| Roomikud liiguvad raskelt | 3D-prinditud detailid on liiga tihedad | Puhasta, lihvi või kontrolli rataste joondust |
| Juhtmed jäävad roomikute vahele | Juhtmed on liiga pikad või halvasti paigutatud | Kinnita juhtmed kere sisse või eemale liikuvatest osadest |


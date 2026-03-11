## Üldinfo
### Eesmärgid
Anda praktilised oskused kaasaegsete nutilahenduste loomiseks, kasutades ESP32 mikrokontrollereid ja M5Stack komponente. Õpetada looma süsteeme, mida saab jälgida ja juhtida mobiilseadmete kaudu. Kursus keskendub päris maailmas kasutatavate nutisüsteemide ülesehitusele alates andurite ühendamisest kuni kasutajaliidese loomiseni. Oluline osa on ka seadmete kaugjuhtimise ja -jälgimise võimaluste loomisel.

### Õpiväljundid
Õppeaine läbinud õppija:
oskab luua terviklikke nutikatele seadmetele põhinevaid süsteeme. Ta tunneb ESP32 mikrokontrollerite programmeerimist, oskab ühendada erinevaid andureid ning luua veebipõhiseid kasutajaliideseid. Üliõpilane mõistab MQTT protokolli kasutamist seadmetevahelises suhtluses ning suudab luua töökindlaid automaatikasüsteeme. Ta oskab kasutada M5Stack mooduleid kiireks prototüüpimiseks ning valida ja ühendada sobivaid andureid asukoha, rõhu ja voolu mõõtmiseks. Tähtis osa on ka turvameetmete rakendamisel nutisüsteemides.

### Sisu lühikirjeldus
Kursus õpetab looma mobiilseid nutilahendusi, mida on lihtne teistele demonstreerida ja praktikas kasutada. Kasutatavad tehnoloogiad vastavad tänapäeva tööstuse nõudmistele, keskendudes veebipõhistele kasutajaliidestele ja nende integreerimisele füüsiliste seadmetega.
Keskendudes universaalsetele veebiliidestele eriotstarbelise riistvara asemel, omandavad üliõpilased oskused, mis on tööstuses laialdaselt kasutusel. Kursus õpetab tööd levinud tehnoloogiatega nagu ESP32, Arduino, MQTT, veebirakendused (HTML, CSS, JavaScript), RESTful API-d ja Model-Context-Protocol (MCP) põhimõtteid.
Praktilise oskusena õpitakse seadistama turvalisi MQTT-brokereid pilveteenustes ning looma turvatud tunneleid veebiliidestele kaugjuurdepääsuks. See võimaldab luua nutisüsteeme, mis on ligipääsetavad ja juhitavad üle interneti, järgides samal ajal kaasaegseid turvanõudeid.
Iga arendatav seade saab oma nutika kasutajaliidese. Käesoleval õppeaastal on praktikaprojektiks süstladosaatori loomine Dobot robotile koos kasutajasõbraliku veebiliidesega, mis võimaldab roboti tööd jälgida ja juhtida.

### Hindamine
Iseseisvate tööde loetelu ja juhised nende tegemiseks:

#### Ülesanne 1: Põhiline M5Stack ESP32 juhtimissüsteem
Arendada põhiline juhtimissüsteem pneumaatilisele doseerijale, kasutades M5Stack ESP32 moodulit. Tudengid rakendavad põhilise GPIO juhtimise solenoidklapile, konfigureerivad ESP32 WiFi pääsupunktina ja loovad lihtsa veebiserveri. Veebiliides peaks võimaldama käsitsi klapi aktiveerimist ja kuvama süsteemi põhiolekut. Lisada QR-koodi genereerimine, mis ühendab kasutajad otse juhtimisliidesega, kasutades lihtsat autentimist.

#### Ülesanne 2: Turvalise kaugjuurdepääsu rakendamine
Luua turvaline kaug juurdepääsusüsteem doseerimis kontrollerile. Tudengid seadistavad VPN serveri dropletil, konfigureerivad M5Stack ESP32 VPN kliendina ja rakendavad korrektset sertifikaadipõhist autentimist. Süsteem peaks võimaldama krüpteeritud suhtlust kontrolleri ja kaugkasutajate vahel, võimaldades turvalist jälgimist ja juhtimist väljaspool kohalikku võrku. Lisada korralikud võtmehalduse tavad ja juurdepääsu logimine.

#### Ülesanne 3: Pilvepõhise MQTT vahendaja juurutamine
Juurutada ja konfigureerida skaleeritav MQTT vahendaja AWS EC2 või Digital Ocean platvormil. Tudengid rakendavad TLS krüpteerimise kogu MQTT liiklusele, seadistavad korralikud juurdepääsukontrolli poliitikad ja loovad turvalise sidekanali doseerimissüsteemi ja pilveteenuste vahel. Vahendaja peaks toetama seadmete autentimist, teemapõhist turvalisust ja sõnumite püsivust. Tudengid rakendavad korraliku kredientiaalide halduse ESP32 klientidel ja demonstreerivad turvalist andmevahetust.

#### Ülesanne 4: API-põhine doseerimisteenus OAuth-iga
Luua REST API teenus OAuth 2.0 autentimisega, mis võimaldab doseerimissüsteemi programmipõhist juhtimist. Tudengid rakendavad tokenipõhise autentimise, päringute allkirjastamise ja korralikud API turvatavad. Arendada klientrakendus, mis demonstreerib turvalist API kasutust, võimaldades programmeerida dosimisjärjestusi koos nõuetekohase autoriseerimisega. Lisada päringute arvu piiramine ja auditilogimine kuritarvitamise vältimiseks.

#### Ülesanne 5: Kahe kaamera positsiooni tuvastussüsteem
Rakendada kahe kaamera positsiooni tuvastussüsteem, kasutades kahte ESP32-CAM moodulit, mis on paigutatud 90-kraadise nurga all üksteise suhtes, et määrata süstla nõela asukoht 3D ruumis. Tudengid arendavad kaamera kalibreerimisprotseduuri, loovad lihtsa kaamera-põhise koordinaatide määramise algoritmi ja integreerivad selle teabe Dobot koordinaadisüsteemiga. 90-kraadine paigutus võimaldab lihtsustatud kolmemõõtmelise positsiooni arvutamist ilma keeruka stereonägemise algoritmita. Süsteem peaks andma reaalajas tagasisidet nõela positsiooni ja kõrguse kohta doseerimispinna suhtes, koos veebipõhise juhtimisliidesega.

#### Lisaülesanne: Turvaline kaugdoseerimissüsteem
Integreerida turvaline VPN juurdepääs, pilvepõhine MQTT vahendaja ja põhiline veebijuhtimisliides eelmistest ülesannetest funktsionaalseks kaugdoseerimissüsteemiks. Tudengid:
1. Konfigureerivad turvalise kaugjuurdepääsu doseerimiskontrollerile
2. Rakendavad põhilise autentimise veebiliidesele
3. Seadistavad krüpteeritud MQTT suhtluse pilvevahendajaga
4. Loovad juhtpaneeli, mis võimaldab kaugjälgimist ja põhijuhtimist
5. Dokumenteerivad rakendatud turvameetmed ja allesjäänud turvakaalutlused

### Hindamismeetodid ja -kriteeriumid

### Lõpphindamisele pääsemise tingimused
Õppija on positiivsele tulemusele kaitsnud vähemalt ühe labori.

### Lõpphindamise skaala
Eristav (A, B, C, D, E, F, mi)

### Hindamistulemuste teatamise aeg
Info puudub

### Lõpphinde kujunemine
Info puudub

|   |   |
|---|---|
| A | 91 punkti |
| B | 81 punkti |
| C | 71 punkti |
| D | 61 punkti |
| E | 51 punkti |
| F | vähem kui 51 punkti |

### Võlgnevuste likvideerimine
Info puudub

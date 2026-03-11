## Üldinfo
### Eesmärgid
Anda tudengitele praktilised põhioskused ESP32 mikrokontrolleri programmeerimises, veebiliideste loomises, võrgutehnoloogias ja krüptograafilise turvalisuse rakendamises. Kursus valmistab ette edasise nutilahenduste aine jaoks, kus tegeletakse hajussüsteemide, andmebaaside, kaamerasüsteemide ja API-de ehitamisega.

### Õpiväljundid
Õppeaine läbinud õppija:
oskab luua ESP32-l töötava veebiserveri koos REST API lõpp-punktidega. Tunneb WiFi pääsupunkti ja kliendirežiimi seadistamist. Suudab seadistada VPN serveri pilveteenuses ja luua turvalise kaugühenduse ESP32 seadmele. Mõistab krüptograafilise autentimise põhimõtteid (HMAC-SHA256) ja oskab neid rakendada API päringute allkirjastamiseks. Oskab kasutada Linuxi käsureatööriistu serveri haldamiseks. Tunneb võrgupõhitõdesid: IP aadressid, marsruutimine, NAT, tulemüür, reverse proxie.

### Sisu lühikirjeldus
Kursus annab praktilise sissejuhatuse IoT süsteemide alustesse. Esimene labor keskendub ESP32 veebiserveri loomisele ja GPIO juhtimisele — tudengid ehitavad töötava veebiliidese mis juhib seadme riistvara läbi HTTP päringute. Teine labor lisab turvalisuse ja kaugligipääsu kihi: VPN server pilveteenuses, krüptograafilised käsusignatuurid ja turvaline side üle avaliku interneti. Mõlema labori juures testitakse süsteemi piire — latentsust, läbilaskevõimet ja tõrkekindlust.

### Hindamine
Iseseisvate tööde loetelu ja juhised nende tegemiseks:

#### Labor 1: Veebipõhine juhtimisliides
Loo M5 Atom Lite peal veebiserver mis teenindab ühte veebilehte ja pakub kahte API lõpp-punkti. Esimene versioon juhib pardal olevat RGB LED-i värvi veebiliidese kaudu. GET /get tagastab praeguse LED värvi 8-bitise RGB hex-väärtusena, GET /set?value=<väärtus> muudab värvi. Veebileht kuvab praegust värvi, sisaldab värvivalijat ja WiFi seadistuse nuppu. Ainult AP režiim (WiFi otse seadmesse). Testi: (1) LED värvimuutuse sujuvus — leia optimaalne värskendussagedus kus kasutaja tajub sujuvat üleminekut ilma vilkumiseta, (2) ESP32 ülekoormuse test — eskaleeri käskude arvu kuni süsteem ebaõnnestub ja taastub.

#### Labor 2: Turvaline kaugligipääs krüptograafiaga
Lisa WiFi kliendirežiim RGB LED juhtimisele ja krüptograafiline turvakiht. Loo avalik ligipääs VPN releed kaudu Digital Oceani dropletil + OpenVPN serveriga. Teosta käsusignatuuride autentimine ajatemplipõhise HMAC-SHA256-ga. AP režiimi leht krüptovõtme üleslaadimiseks (ühekordne, seejärel ligipääsmatu). Allkirjastatud API päringud. VPN-ühendatud ruuter doseerimissüsteemi turvaliseks ligipääsuks. Testi: (1) õige võti töötab, vale ebaõnnestub, (2) käsu latentsus — mõõda aeg ESP32 käsu vastuvõtmisest vastuse saatmiseni.

#### Lisaülesanne: Turvaauditi ja läbistustestimine
Dokumenteeri oma süsteemi turvaanalüüs: millised ründevektorid on võimalikud, kuidas HMAC-SHA256 neid blokeerib, ja millised nõrkused jäävad alles. Demonstreeri vähemalt ühe ründe katselt (nt taasesitusrünne ilma ajatempli kontrollita).

### Lõpphindamisele pääsemise tingimused
Õppija on positiivsele tulemusele kaitsnud vähemalt ühe labori.

### Minimaalne punktide kogusumma lõpphindamisele pääsemiseks
21

### Lõpphindamise skaala
Eristav (A, B, C, D, E, F, mi)

### Hindamistulemuste teatamise aeg
Info puudub

### Lõpphinde kujunemine
Info puudub

|   |   |
|---|---|
| A | 37 punkti |
| B | 33 punkti |
| C | 29 punkti |
| D | 25 punkti |
| E | 21 punkti |
| F | vähem kui 21 punkti |
| mi | Õppija ei ole ülesandeid esitanud ega lõpphindamisel osalenud |

### Võlgnevuste likvideerimine
Kokkuleppel vastutava õppejõuga

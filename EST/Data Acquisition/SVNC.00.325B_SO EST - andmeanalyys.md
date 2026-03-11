## Üldinfo
### Eesmärgid
Anda tudengitele süvendatud oskused keerukate mõõtesüsteemide ehitamises, mitme meetodi võrdlevas analüüsis, masinõppemudelite rakendamises andmehõive probleemidele ja automatiseeritud kvaliteedikontrollis. Kursus eeldab sissejuhatava andmehõive kursuse läbimist (SVNC.00.326) ning ehitab seal omandatud andurite, trükkplaatide ja Jupyter Lab'i oskustele.

### Õpiväljundid
Õppeaine läbinud õppija:
oskab disainida ja võrrelda mitut erinevat analoogset signaali töötlemise meetodit ühel trükkplaadil. Suudab ehitada automatiseeritud testpingi suure hulga mõõtmiste kogumiseks. Oskab rakendada masinõppemudeleid (lineaarne regressioon, otsustuspuu) mõõteandmete põhjal ennustamiseks. Suudab ehitada robotipõhise automatiseeritud kvaliteedikontrolli süsteemi. Tunneb statistilise analüüsi meetodeid mõõtesüsteemide hindamiseks: lahutus, mõõtemääramatus, absoluutne täpsus. Oskab integreerida mõõtesüsteemi tööstusrobotiga reaalajalise tagasiside jaoks.

### Sisu lühikirjeldus
Kursus jätkab sealt, kus sissejuhatav andmehõive lõpetas. Esimene labor võrdleb nelja erinevat analoogsignaali töötlemise meetodit süstla täitetaseme mõõtmiseks — tudengid disainivad ühe trükkplaadi mis toetab kahte meetodit ja koguvad sadu mõõtmisi süstemaatilise testimisega. Teine labor rakendab masinõpet: labori 3 andmete põhjal treenitakse mudel mis ennustab süstla mahtu rõhusignaali järgi. Kolmas labor ehitab robotipõhise kvaliteedikontrolli süsteemi mis hindab doseerimise tulemusi automaatselt. Integratsiooniprojekt ühendab kõik — rõhupõhine jälgimine, mahuhinnangu mudel ja kvaliteedi hindamine — ühtseks suletud ringi süsteemiks.

### Hindamine
Iseseisvate tööde loetelu ja juhised nende tegemiseks:

#### Ülesanne 1: Mahumõõtmise meetodid
Loo ja testi 2 meetodit (4-st valikust) süstla täitetaseme mõõtmiseks suruõhu impulsi abil. Valikud: (1) MPX5700AP otse M5 Atomile, (2) pingejaguri kaudu kahetuumalise lõimestamisega, (3) opampiga 0–3,3V skaleerimisega ja digitaalfiltreerimisega, (4) opamp Schmitt-päästikuna positiivse tagasisidega. Disaini üks trükkplaat mis toetab mõlemat valitud meetodit hüppiklõhkude või 0Ω takistitega. Kogu 6×100 mõõtmist erinevatel täitetasemetel (10ml, 8ml, 6ml, 4ml, 2ml, 0ml). Võrdle täpsust ja töökindlust mõlema meetodi vahel.

#### Ülesanne 2: Testpingi ja masinõppe mudeli ehitamine
Kasuta ülesande 1 mõõteandmeid (6×100 mõõtmist kahest meetodist) masinõppe mudeli treenimiseks. Ehita testpink paralleelsete mõõtesüsteemidega täiendavate andmete kogumiseks erinevate teadaolevate mahtude juures. Kasuta lihtsat lineaarset regressioonimudelit otsingutabeli (LUT) ehitamiseks reaalajalise süsteemi jaoks ja testi hindamissüsteemi.

#### Ülesanne 3: Kvaliteedi ennustav mudel
Joonista levinumad kujundid mida kasutatakse silikooni või joodisepasta doseerimiseks: sirge joon, kaar ja pinnatäide. Ehita testpink sisend- ja väljundpuhvriga testplaatide hoidmiseks — robot saab teha 5 tükki enne kui lisad uued puhtad plaadid ja kogud valmis proovid. Tee plaatidest kõrglahutusega pildid ja analüüsi milline kiiruse, rõhu ja nurkkiiruse kombinatsioon annab parima tulemuse.

#### Lisaülesanne: Tagasisidestatud optimeerimine
Disaini süstladoseerija mis kasutab suruõhku silikooni/joodisepasta väljasurumiseks ja suudab teha kvaliteetseid sirgeid jooni, kaari ja pinnatäidet. Integreeri rõhupõhine protsessijälgimine, mahuhinnangu mudel ja kvaliteedi hindamine ühtseks suletud ringi süsteemiks. Testimiseks ehita automatiseeritud testid puhtate plaatide sisendpuhvriga.

### Lõpphindamisele pääsemise tingimused
Õppija on positiivsele tulemusele kaitsnud vähemalt ühe labori.

### Minimaalne punktide kogusumma lõpphindamisele pääsemiseks
51

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
| F | Õppija on kogunud vähem kui 51 punkti |
| mi | Õppija ei ole ülesandeid esitanud ega lõpphindamisel osalenud |

### Võlgnevuste likvideerimine
Kokkuleppel vastutava õppejõuga

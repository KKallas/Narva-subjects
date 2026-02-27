## Andmehõive: Labor 3

## \! Ohutusjuhend \!

### UR5 roboti kasutamine

Enne roboti aktiveerimist veendu, et tööruum on puhas ja keegi ei viibi roboti tööpiirkonnas. Kui robot käivitad, seisa alati vähemalt kahe meetri kaugusel kuni süsteem on täielikult initsialiseerunud ja programm laetud.

Uue programmi testimisel hoia käsi kogu aeg STOP-nupul. Ära kunagi vaata roboti liikumist usaldades—eelda, et midagi võib minna valesti. Esimesed läbimised tee alati aeglustatud kiirusel (25-50%), isegi kui programm tundub õige. Kui robot käitub ootamatult või teeb imelikke liigutusi, vajuta kohe STOP. Ära ürita robotit peatada käega—see on ohtlik nii sulle kui robotile.

Enne töölõppu vii robot alati turvalisse kodupositiooni ja lülita välja. Jäta tööpind korrastatuna, et järgmine kasutaja ei kohtaks ootamatuid takistusi.

### Pneumaatilise süsteemi kasutamine

Pneumaatiline süsteem töötab kuni 7 baari rõhul, mis on piisav vigastuste tekitamiseks kui voolik või ühendus lahti lendab. Enne süsteemi survestavat kontrolli kõik ühendused käega—6mm ja 4mm quick-fit ühendused peavad olema täielikult kinnitatud kuuldava kliksu heliga. Kui ühendus läheb peale kergelt ilma takistuseta, pole see korralikult kinni.

Kompressori ja vooliku vaheline ühendus on eriti kriitiline, sest seal on kõrgeim rõhk ja suurim õhuvool. Kontrolli seda ühendustakku iga kord enne kompressori sisselülitamist. Kui kuuled süsteemist sisisevat heli, on kusagil lekkind ühendus—lülita kohe kompressor välja ja leia leke enne jätkamist.

Ära kunagi suuna survestatut õhuvoogu enda või teiste poole. Ära ühenda ega lahuta quick-fit ühendusi kui süsteem on surveline—esmalt vabasta rõhk solenoidklapi kaudu või lülita kompressor välja ja oota kuni rõhk on langenud nullini.

Kui töötad samaaegselt nii roboti kui pneumaatikaga, veendu et pneumaatilised voolikud ei jää roboti liikumistrajektoori peale. Robot ei "tunneta" voolikut ja võib selle kinni pigistada või kaasa vedada.

## Eesmärk

Luua ja testida 2 meetodit kuidas ainult suruõhuga mõõta süstlas alles jäänud materjali ja kas süstal on tühi või umbes. Esimene meetod on  nr 4 allpool ja teise võib vabalt valida ülejäänust kolmest.

Printsiip on lihtne: kui meil on konstantse rõhuga rõhu allikas ja lülitav solenoidklapp (täiesti lahti või kinni), siis süstlas rõhk kasvab kuni kolb ületab silikooni takistuse ja hakkab liikuma. Kuni kolb kinni on, kasvab rõhk suletud mahus kiiresti. Kui kolb hakkab liikuma, rõhu kasvamise kiirus väheneb märkimisväärselt, sest ruumala kuhu õhk voolab hakkab kasvama. Mõne millisekundiga jõuab süsteem dünaamilisse tasakaalu—rõhk stabiliseerub ja jääb konstantseks, sest õhu sissevool tasakaalustab väljuva silikooni mahu. Dünaamilises tasakaalus kolb liigub edasi ühtlase kiirusega, mida piirab nõelaotsa takistus, mitte õhu sissevool. Kogu see rõhu ülesehitamine ja stabiliseerumine toimub kiiresti aga silikoon liigu aeglaselt, sellepärast on meil vaja jälgida 2-100 hetkest kus rõhk voolama hakkab kuni kolb peaks oma kohalt liikunud olema. 

Meil on vaja leida kaks parameetrit: kui kaua läheb aega enne kui kolb liikuma hakkab, ja milline on kolbi positsioon 100 millisekundi pärast liikuma hakkamist. Distants jagatud ajaga annab meile keskmise kiiruse. Meil on valida mõned lahendused kuidas soovitud tulemus saada

1. MPX5700AP ühendatud otse M5 Atom Lite külge  
   Õpetab timerite kasutamist ja põhilisi ESP32 ADC omadusi  
   \>2ms võimaldab ESP32 nii pollida kui kasutada timer lahendusi. Seekord palun lahendada andmete muutuste lugemine läbi taimeri.  
2. MPX5700AP läbi pingejaguri M5 Atom Lite küge  
   Õpetab mitmetuumalise protsessori programmeerimist ja jagatud muutujate haldamist  
   Siin palun lahendada anduri lugemine läbi lisa threadi mis jookseb teise tuuma peal täiesti üksi et suudaksime 1ms või alla selle lugemisi teha.   
3. MPX5700AP läbi op-amp’i skaleerides ainult meid huvitava vahemiku 0-3.3V ja võimendatud signaal  M5 Atom Lite küge  
   Õpetab analoogset signaali konditsioneerimist ja digitaalset filtreerimist  
   Sisuliselt digitaalne filtreerimine, kasuta taimerit.  
4. MPX5700AP läbi op-amp’i kus jälgitakse muutumise kiirust  
   Õpetab diferentsiaalse signaali töötlemist ja tuletise mõõtmist analoogses domeenis ja IRQ lahendus ESP32 peal  
   MPX5700AP läbi op-amp'i (LM358N) mis on seadistatud Schmitt-trigger komparaatorina positiivse tagasiside abil. Op-amp jälgib rõhu muutuse kiirust—kui muutus aeglustub (kolb hakkas liikuma), genereerib see IRQ signaali mikrokontrollerile. Positiivne tagasiside loob hüstereesi, mis hoiab signaali puhtana ja vältib võnkumist lävendite vahel. Kasuta IRQ'd et teada saada millal kolb liikuma hakkas, ja käivita timer mis teeb täpselt 100 millisekundi pärast teise mõõtmise et teada saada kui kõrgeks on rõhk jõudnud kasvada.

Vali välja vabatahtlik disaini versioon ja joonista üks plaat Fusion 360 EDA’s milles saab kas juperiga või 0R takistite jootmisega teha mõlemad versioonid. Kui esimesel ringil op-amp jäi segaseks soovitan siin vahetada versioon 4 \-\> 3\. Tee teist korda sama läbi ja saad asjast palju paremini aru.

### Signaalide filtreerimine

Signaalide filtreerimine on koht kus müra kohtub mõttega, kus universumi kaos saab kasutatavateks andmeteks. 

#### Analoog pool

Takisti ja kondensaator koos teevad RC-filtri, aga tegelikult nad venitatavad aega. Takisti pidurdab voolu, kondensaator kogub laengu. Takisti tekitab viivituse, mis laseb kiiretel muutustel sumbuda, samal ajal kui aeglasemad muutused pääsevad läbi. Seda näed kõikjal toiteahelates, sest lülitusregulaatorid ja digitaallülitused pritsivad elektromagnetilist müra üle kogu spektri. RC-filter ütleb kõigele "oota natuke", ja müra, olles kannatamatu ja kiirsageduslik, väsib ära.

Kondensaator üksi, otse maasse, töötab teisiti. Takistit pole, seega pole ka tahtlikku viivitust sinu signaali teel, aga kondensaator ikka loob kiiretele sagedustele madala takistusega tee maasse. See on agressiivne filtreerimine—müra suunatakse maha peaaegu kohe, kuigi päris komponendid lisavad alati natuke viivitust, lihtsalt nanosekundeid mikrosekundite asemel.

Diferentsiaalse signaali trikk on elegantne: võta oma algne signaal, filtreeri üks koopia läbi RC-ahela, et luua viivitatud, silutud versioon, siis võrdle seda filtreerimata versiooniga. Mida sa saad, on sisuliselt tuletis—muutuse kiirus. Müra kipub olema mõlemas signaalid ühesugune ja tühistub võrdlemisel. Päris informatsioon, servad ja üleminekud, jäävad selgelt näha. Sellepärast diferentsiaalülekanne valitseb kõikjal, kus signaal peab kaugele jõudma või puhtana püsima.

#### Digitaalne pool

Digitaalne filtreerimine töötab teise põhimõtte järgi—sa ei saa füüsikat muuta, aga sa saad rohkem proove võtta ja targemaid küsimusi küsida. Ülekogus tähendab, et sa loeb oma ADC-d kiiremini kui rangelt vaja või keskmistada mitut kõrvutiolevat lugemist. Igas proovis on müra, aga kui see müra on juhuslik (ja tavaliselt on), siis mitme proovi ühtlustamisel teravad nurgad nühitakse maha,  samal ajal kui signaal ennast tugevdab. Matemaatika on lihtne; tulemused on võimsad.

Ruumiline ülekogus tähendab mitme füüsilise sensori või mitme punkti lugemist ruumis—mõtle, et loed kolme temperatuuriandurit ja keskmistada neid, või skanneerida detektorimassiivi ja kombineerida piksleid. Bitisügavuse ülekogus tähendab 12-bitise ADC võtmist ja selle tuhandeid kordi lugemist, et saavutada tegelik 14-bitine või 16-bitine täpsus. Müratase ei muutu, aga sinu võime läbi selle näha küll.

Mõnikord lihtne lähenemine—võta väikesest kogusest proovidest mediaan mitte keskmine—töötab paremini kui keeruline keskmistamine. Mediaan ignoreerib väljalangevusi täielikult. Kui sinu müras on aeg-ajalt metsikuid piike elektromagnetilisest häirest või bitiveast, keskmistamine laotab selle piigi üle kogu filtreeritud väljundi. Mediaan lihtsalt viskab selle minema. Kolm või viis proovidet, võta keskelt väärtus, liigu edasi. See on toores aga efektiivne, eriti vaenulikus elektromagnetilises keskkonnas mikrokontrolleri sees, kus mootoriajurid või solenoidid tekitavad pinge ebaühtlusi.

Sügavam tõde on see, et kogu filtreerimine, analoog või digitaalne, on mõistmine sellest, mida sa üritad säilitada versus mida sa üritad hävitada. Pole olemas universaalset "puhas signaal"—on ainult küsimus, mis on oluline sinu konkreetses süsteemis, sinu konkreetsetel ajaskaaladel, ja mida võib turvaliselt ignoreerida.

## Labori struktuur

### Osa 1: Vali kaks lahendust ja ehita prototüüp

Vali välja vabatahtlik lahendus kolmest pakutud variandist. Ehita mõlemad prototüübid breadboardil, et testida nende tööpõhimõtteid enne PCB disaini. Kui pole varem sarnast analoogahela loogikat ehitanud, simuleeri esmalt Falstadis (pane kindlasti arenduslogisse, tuleb hindamisele kasuks) läbi—see säästab aega ja komponente.

### Osa 2: PCB disain

Disaini üks PCB, millest saab lihtsa vaevaga ehitada mõlemad väljavalitud lahendused. Kasuta skeemis jumpereid või 0Ω takistite positsioone, mida saab vastavalt vajadusele joota, et valida kahe konfiguratsiooni vahel. Märgi selgelt *silkscreenil* või kommentaarides, millised komponendid kuhu paigutada kummalgi konfiguratsioonil.

Telli vähemalt 10 plaati (tavaliselt tuleb JLCPCB-lt niikuinii 5 tükki miinimumina). Arvestades, et iga plaat jääb peale jootmist üheks konkreetseks konfiguratsiooniks, vajad vähemalt nelja töötavat plaati—kaks iga lahenduse testimiseks ja kaks varuks kui midagi läheb katki või jootmine ebaõnnestub. 

### Osa 3: PCB funktsionaalne test

Jooda kokku mõlemad konfiguratsioonid (kasuta kahte erinevat plaati erineva konfiguratsiooniga). Testi, et mõlemad analoogahelad annavad oodatud väljundsignaale—kontrolli op-amp'i väljundeid ostsilloskoobi ja multimeetriga. Veendu, et IRQ signaalid genereeruvad õigetes hetkedest ja timer loeb ADC-d õige intervalliga.

### Osa 4: Rõhusüsteemiga integreerimine ja mõõtmine

Ühenda mõlemad lahendused pneumaatilise süsteemi külge ja tee läbi täielik testimine vastavalt analüüsi sektsioonis kirjeldatule. 3D prindi rakis ja seadista kaamera ning ülejäänud testimise raud/tarkvara. Tee 6×100 mõõtmist mõlema konfiguratsiooni kohta ja analüüsi tulemusi Jupyter Labis. Võrdle mõlema meetodi täpsust, korratavust ja usaldusväärsust (hälvet).

### Tehnilised ülesanded

#### Võrdlusanalüüs (Jupyter Lab):

* Määra mõlema lahenduse resolutsioon, mõõtemääramatus ja absoluutne täpsus kogutud andmete põhjal ([link](https://docs.google.com/document/d/1JpWw1INjQ7y8hc0LWF63XZwhcZW0h86u2kE3aBuDFro/edit?usp=sharing))  
* Hinda 100 tükki tootmise kogumaksumus komponentide ja PCB hinna põhjal, vormista BOM (bill of materials) \- lihtne tabel, komponent, kogus, asukoht, link tootele, kust saab  
* Loo 6×100 mõõtmiste tabel kuue erineva täituvuse kohta: 10ml, 8ml, 6ml, 4ml, 2ml ja 0ml

#### PCB disain (Fusion):

* Koosta skemaatiline joonis, mis võimaldab mõlemat lahendust jumperite või 0Ω takistite abil  
  Märgi selgelt skemaatilisse joonisesse, millised komponendid on jagatud ja millised on erinevad kummalgi konfiguratsioonil  
* Koosta PCB layout  
* Tee Design Rule Check enne plaadi viimistlemist  
* Genereeri Gerber failid JLCPCB spetsifikatsioonide järgi ja kontrolli neid vaatajaga üle

#### Kood (Arduino):

* Implementeeri katkestuse (IRQ) käsitlemine Schmitt-triggeri väljundi jaoks  
* Seadista timer 0.5ms intervalli analoogsisendi lugemiseks  
* Kasuta threade diferentsiaalsignaali pollimise jaoks teisel tuumal  
* Kirjuta automaattestid, mis kontrollivad mõlema meetodi tulemuste vastavust oodatud väärtustele

*See on elav dokument, uuenda eesmärke kui need töö käigus muutuvad, uued teadmised muudavad vanad eesmärgid pahtiti mõttetuks. Eesmärk on et hoida meeskonda kogu aeg sihil, et ei eksitaks detailide metsa ära ja põhi probleem jääb lahendamata*

### Taustainfo

* **ESP32 Interrupt**  
  [https://www.youtube.com/watch?v=WVK2Wx386XE](https://www.youtube.com/watch?v=WVK2Wx386XE)  
* **ESP32 threads**  
  [https://www.youtube.com/watch?v=k\_D\_Qu0cgu8](https://www.youtube.com/watch?v=k_D_Qu0cgu8)  
* **Schmitt trigger**  
  [https://www.youtube.com/watch?v=Nrp8OgQLAlw](https://www.youtube.com/watch?v=Nrp8OgQLAlw)  
* **Low Pass filter**  
  [https://www.youtube.com/watch?v=OBM5T5\_kgdI](https://www.youtube.com/watch?v=OBM5T5_kgdI)  
  [https://www.youtube.com/watch?v=oHKwwvcn77Y](https://www.youtube.com/watch?v=oHKwwvcn77Y)  
* **High Pass filter**  
  [https://www.youtube.com/watch?v=H30kRgI5bi0](https://www.youtube.com/watch?v=H30kRgI5bi0)  
* **Mürahaldus**  
  [https://www.youtube.com/watch?v=u40kX1DYKdA](https://www.youtube.com/watch?v=u40kX1DYKdA)  
* **Kihtide konfigureerimine Fusion 360-s**  
  * Ava oma trükkplaadi projekt Fusion 360 elektroonika tööruumis. Kihtide haldurile pääsed Electronics vahekaardilt: Create \> Layer Stack View. Kihtide halduris näed vaikimisi kihte (Top, Bottom, Core, Solder Mask).  
  * Põhimaterjali ehk core'i jaoks määra FR4 paksusega umbes 1,5mm (kui lõplik plaat on 1,6mm). Mõlemad vasekihid sea 1 oz peale (35 µm). Lisa jootemaski kihid üles ja alla (umbes 0.2-0.4mm (1 mil) paksused). Kontrolli, et kogupaksus vastaks JLCPCB standardvalikutele (näiteks 1,6mm) – neil on kindlad standardsed kihistused ja see lihtsustab asja.  
  * **Projekteerimine ja eksport**  
    * Tootmisfailide genereerimiseks ekspordi Gerber-failid ja puurimisfailid CAM eelvaate kaudu või kasuta ODB++ faili, veendudes et kihistus on korrektselt tõlgendatud.

*Lisa siia omapoolseid allikaid ja kasuliku informatsiooni mis aitaks sul projektis aru saada aastaid hiljem kui selle uuesti lahti teed.*

### Vahendid

1. M5 Atom  
2. M5 Camera module  
3. MPX5700AP  
4. Arduino IDE  
5. MS Code  
6. Git  
7. Ossilliscope  
8. Multimeter  
9. UR5

*Kui plaan muutub siis muuda ka vahendeid, või thee [draw.io](http://draw.io)’s joonis kuidas asjad funktsionaalselt seostuvad.*

### Projekti üleshitus

Enne kui projektiga alustad jaga see loogilisteks tükkideks et saaks hinnata progressi 

*Kaugel oled? Millal valmis saad? Kuidas kiiremini saaks? \- need tavalised küsimused*

**Simulatsioon**

Enne füüsilise ahela ehitamist simuleeri Falstadis analoogahel, mis jälgib pinge muutumise kiirust. Ahel peab reageerima pinge üles või alla tõmbamisega hetkel, kui rõhu kasvu kõver aeglustub—see on signaal, et kolb on liikuma hakanud.

Kasuta simulatsioonis op-ampi diferentsiaalvõimendina või komparaatorina. Sisendiks anna aeglaselt kasvav pinge, mis simuleerib rõhuanduri väljundit, ja lisa murdehetk kus kasvu kiirus järsult väheneb. Jälgi op-amp'i väljundit ja kohanda tagasiside takisteid ning kondensaatoreid kuni leiad konfiguratsiooni, mis annab selge loogikalise signaali murdehetkel.

**Miks simuleerida**

Simulatsioon annab sulle kolm olulist asja enne kui hakkad riistvara kokku panema. Esiteks näed, kas sinu analoogahel üldse käitub nagu oodatud—kas tuletise võtmine või komparaatori lävi töötab õigete ajavahemike ja pingeväärtuste juures. Teiseks leiad sobiva lävendi IRQ signaali genereerimiseks ilma et peaks korduvalt komponente ümber jootma. Kolmandaks saad testida erinevaid mürastsenaariume—lisa simulatsioonis sisendsignaalile väikest võnkumist ja vaata, kas Schmitt-triggeri hüsterees hoiab väljundi stabiilsena.

Falstad on ideaalne tööriist selle jaoks, sest saad reaalajas muuta takistite ja kondensaatorite väärtusi ning kohe näha tulemust. Salvesta oma töötav skeem ja lisa projektidokumenti—aastaid hiljem on see seletuseks miks valisid just need komponendiväärtused, ning hindele tuleb ka kasuks.

**Analüüs**

Testimiseks ehita lihtne kahe süstla süsteem. Võta kaks tavalist 10ml süstalt ja ühenda need omavahel lühikese 4mm vooliku tükiga. Mõlema süstla ülaossa ühenda pneumaatiline otsik, mis läheb edasi solenoidklappi—nii saad kontrollida suruõhu voolu mõlemasse süstlasse.

Esimese süstla külge kinnita kaamera, mis suudab automaatselt tuvastada süstla täituvust. See töötab seetõttu, et tume silikoonkork eristub selgelt heleda süstlakorpuse taustal, ja pildilt saab lugeda tegeliku materjali mahu.

Testi tsükkel toimib nii: suru õhuga ettenähtud kogus (aeg) materjali esimesest süstlast teise, tee oma mõõtmised, siis kasuta teist pneumaatilist otsikut et suruda materjal tagasi esimesse süstlasse. Nüüd saad testi korrata ilma süsteemi lahti võtmata.

Enne põhjalikku testimist seadista timer nii, et analoogsisend salvestatakse 0.5ms intervalliga (proovi kasutada supersämplimist). See kiire sämplimissagedus (2kHz) võimaldab näha rõhu kasvu kiiruse muutumist piisava detailsusega—saad täpselt määrata hetke, mil kolb liikuma hakkab ja rõhu kasv aeglustub.

Sellise abivahendiga saad teha sadu mõõtmisi minimaalsete käsitsitööga. Kogu andmed Jupyter Lab raportisse kuue erineva täituvuse kohta: 10ml, 8ml, 6ml, 4ml, 2ml ja 0ml. Iga täituvuse juures tee 60-100 mõõtmist, et saada statistiliselt usaldusväärne pilt mõlema meetodi täpsusest ja korratavusest.

Kogutud andmetest saad leida op-amp'i rõhu kasvu kiiruse jälgimise jaoks optimaalse piirmäära—see hetk, millest alates hakata aega lugema, et määrata kui kaugele on kolb 100ms jooksul jõudnud. Samadest andmetest arvuta ka resolutsioon ja mõõtemääramatus mõlema meetodi jaoks. Kui lisad ahelasse kalibreeritud referentsmõõdiku, saad määrata ka absoluutse täpsuse.

*Need on kaks esimest näidet, lisa siia järgmised testid et kui hakkad sellele projektile uusi osasi lisama siis saad kontrollida et põhi osa pole katki läinud automaatselt \- kui seda tööd teha käsitsis siis see on kuhu läheb enamus projekti ressursi\!*

### Arenduslogi

### Tulemuised

Vaata et hindamiseks oleks antud ikkagit kõik asjad et saaks:

* Tarkvara/Tööfailid (**4** punkti): koodi, EDA disaini või tehnilised failid  
* Simulatsioon (**4** punkti): sobivad simulatsioonimeetodid, analüüs, testimine  
* Prototüüp/Füüsiline projekt (**4** punkti): teostus, kvaliteet, funktsionaalsus  
* Dokumentatsioon (**4** punkti): spetsifikatsioonid, disainivalikute põhjendused, kasutusjuhend

Git repo:  
Arduino fail:  
Jupyter Analüüs (konkreetse failide nimed kaa palun, muidu äkki vaatan valet asja):  
Arenduslogi:

### Tagasiside

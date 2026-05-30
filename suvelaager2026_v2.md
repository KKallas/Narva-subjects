# Robootika suvelaager

## Kaks päeva, üks masin

Laager kestab kaks päeva. Meil on kolm lauda, igal laual kaks robotkätt vastamisi — kokku kuus robotit. Meeskonnad jaotuvad laudade vahel ja kasutavad kogu laagri sama riistvara.

Esimesel päeval ehitavad meeskonnad ise tööriista, millega teisel päeval mängitakse. Mida rohkem ülesandeid jõuad lahendada, seda paremini oled võistluseks valmis. Tööriist, millega lõpus võideldakse, ei tule kuskilt valmis kujul — õpilased on selle ise kokku pannud.

Masin teeb täpselt seda, mida käsid. Esimesel päeval saavad õpilased aru, kui keeruline on masinaga õigesti rääkida. Teisel päeval saavad nad aru, kui keeruline on omavahel kokku leppida, mida masinale rääkida.

---

## Riistvara

Igal laual on sama komplekt.

**Kaks Dobot MG400 robotkätt** vastamisi, kummalgi vaakumpump otsas. Tööstuslik robotkäsi — samasugune, mis tehases asju kokku paneb, ainult väiksem. Liigub kiiresti ja täpselt, kui temaga õigesti rääkida. Kaks kätt jagavad sama tööpinda ja jõuavad teineteisele jalgu astuda — selles ongi mängu mõte.

**Kümme M5 Atom moodulit** laual. Igaühel ekraan, kus kuvatakse QR kood, ja akumoodul, mis annab tervikule kaalu ja kuju, et vaakumpump saaks ta üles tõsta ja kogumiskasti tuua. QR kood on aatomi nägu — liides loeb selle kaamerast välja ja otsustab koodi põhjal, mida aatomiga teha.

**IP kaamera** ülevalt, otse laua kohal. Kogu klõpsamine ja kogu otsustamine käib selle pildi peal.

**WiFi ruuter**, mis hoiab kõik koos.

---

## Kuidas juhitakse

Kõik kasutavad arvutist sama veebiliidest. Liidesel on kolm osa.

Esimene on kaameravaade ülevalt. Näed lauda nagu RTS mängu kasutajaliides. Klõpsad pildil kohale — robot liigub sinna. Kogu juhtimine algab siit.

Teine on koodipaneel. Iga klõps käivitab Pythoni käsu ja paneel näitab, mis täpselt juhtub. Siia kirjutatakse kalibreerimine, QR koodide lugemine ja mängu loogika.

Kolmas on jututsänn tehisintellektiga. Claude Code näeb nii koodi kui kaamerapilti. Temalt võib küsida, miks robot valesti läks, paluda nõu strateegia kohta või lasta tal kood ise valmis kirjutada. Tema pakub lahenduse, sina vaatad üle ja annad loa käivitada.

Töövoog on lihtne: vaata, kirjelda, kontrolli, proovi, kinnita. Just nõnda käib töö ka päris tarkvarameeskondades — õpilased ei tee lihtsustatud versiooni, vaid sama asja.

---

## Esimene päev — tööriista ehitamine

### Päeva ülesehitus

Päev jaguneb kuueks pooletunniseks plokiks. Esimene on sissejuhatus. Järgmised viis on iseseisvad mängud. Kokku kolm tundi laua taga.

### Sissejuhatus (30 min)

Tutvutakse liidesega: klõpsa aatomile, käsi tõstab üles, paneb kogumiskasti. Lihtne. Aga peagi selgub, et käsi ei lähe alati just sinna, kuhu klõpsati — kaameranurk tekitab nihke. Keegi ei räägi sellest ette. Õpilased põrkavad ise vastu seina ja avavad jututsänni, et küsida, mis lahti.

See pool tundi — kui saadakse aru, et masin ei eksinud, vaid eeldus oli vale — on kogu laagri kõige tähtsam hetk.

### Viis mängu (igaüks 30 min)

Igal laual on kaks robotkätt vastamisi — sama laua taga harjutavad korraga kaks meeskonda, kumbki oma poole peal. Esimesed neli mängu hoiavadki kogu tegevuse sinu poole peal: kaks kätt teineteist ei sega ja mõlemad meeskonnad saavad korraga proovida. Viies mäng murrab selle joone.

Iga meeskond ehitab oma lahenduse ise, aga ideid jagad alati — see on kogu laagri läbiv mõte. Jagatud teadmine on kõige odavam teadmine.

Iga mäng käib sama mustriga:

- **Umbes minutiline video** seletab, mis on ülesanne ja kuidas punkte loetakse.
- **Viis minutit lihtsalt katsetamist** — käed küljes, ilma jututsännita. Saad aru, mida masin praegu teeb ja mida ta veel ei tee.
- **Ülejäänud aeg** läheb arutamiseks ja parandamiseks. Räägitakse läbi, mis töötab ja mis mitte, ning katsetatakse tehisintellekti abiga ideid kiiresti läbi — paku lahendus, vaata üle, käivita, vaata mis juhtus, paranda uuesti. Iga ring kümme-kakskümmend sekundit. Iga ring viib ühe sammu edasi.

Eesmärk on antud aja jooksul üks mäng korralikult lahendada. Kõiki viit ei pea jõudma — meeskonnad jõuavad eri kaugele ja see on loomulik. Üks korralikult lõpuni viidud mäng õpetab rohkem kui viis poolikut katset.

Mängud lähevad järjest raskemaks ja iga järgmine eeldab eelmise lahendust.

1. **Esimene mäng** — pane kõik kümme aatomit kogumiskasti. Vaakumpump tuleb kalibreerida, et ta võtaks aatomist õigesti kinni.
2. **Teine mäng** — Tetrises tuleb klotse võtta kindlas järjekorras. Sama lugu siin. Aatomid pannakse mängu alguses lauale juhuslikku paika, aga igal QR kood. Korja nad üles järjekorras: mis kasutjaliides näitab et järgmiseks tuleb võtta. 
3. **Kolmas mäng** — QR koodid muutuvad iga 10 sekundi tagant. Õige aatom tuleb kätte saada enne, kui kood vahetub. 
4. **Neljas mäng** — koodidel on erinev väärtus. Kallimate järele lähed esimesena. Automaatne juhtimine, kus mudel otsustab QR koodi järgi pildil kuhu robotkäsi saata mitte kasjutaja hiireklõpsust.
5. **Viies mäng** — esimest korda peab käsi ulatuma üle laua keskme, vastase poole peale. Aga naabri käsi teeb sedasama. Kaks kätt liiguvad korraga sama laua kohal — kood peab oskama oodata, plaan ümber teha või vastasest mööda hiilida. See mäng ongi otsene proovikivi homsele võistlusele.

Iga mängu lõpus on lühike tagasivaade: mis sai ehitatud, mis töötab, mis on habras. Habras kood saab homme valusa nahatäie.

---

## Teine päev — võistlus

### Lauad ja broneerimine

Päeva jaoks on kolm lauda. Kaks neist on võistluslauad — siin käivad päris matšid, kell tiksub ja punktid lähevad kirja. Ülejäänud laud on treeningulaud — sama riistvara, aga mõeldud koodi parandamiseks ja strateegia katsetamiseks enne, kui asi päriselt loeb - äkki nägid võistlusteil teistel head ideed mida tahad veel kasutada proovida.

Treeningulaud jagatakse kümneminutiliste plokkide kaupa. Korraga võib ette broneerida kuni kolm slotti — kes ees, see mees. Broneerimine käib veebivormi kaudu sülearvutist või telefonist, vaba ploki saab ühe klõpsuga endale. 

### Reeglid

Kujuta ette "Hungry Hungry Hippos" mängu — neli plastikust jõehobu, kes kõik korraga keskelt kuulikesi haaravad. Võidab see, kes haarab kõige rohkem kuulikesi enda ette. Sama lugu, ainult robotkätega ja koodiga. Sinu jõehobu on programm, mille sa eile ise kirjutasid.

Üks töölaud, kaks robotkätt vastamisi, kümme aatomit keskel. Üheksakümmend sekundit. Mõlemad meeskonnad alustavad korraga ja lõpetavad korraga — keegi oma järjekorda ei oota. Vaakum tõmbab, kogumiskast täitub, kell jookseb.

Iga aatom annab ühe punkti. Aga liides näitab korraga ühte erilist QR koodi, mis on väärt viis. Sama kood võib parasjagu olla mitmel aatomil — sinu poolel, vastase poolel või mõlemal — või ainult ühel. Iga vastava aatomi tabamine annab viis punkti. Sihtmärk püsib seni, kuni viimane sama koodiga aatom on korjatud või kuni selle taimer täis saab. Alles siis läheb liides järgmise koodi peale. Sinu liides peab pidevalt vaatama, mis kood on parasjagu väärtuslik ja kus ta asub.

### Mis siin põnevat on

Kordamööda siin ei käida. Kaks kätt liiguvad korraga, vaatavad sama lauda ja jõuavad teineteisele jalgu satuda. Kui sa lähed erilise järele ja vastane astub ette, läheb su robot lukku — pead ta uuesti lahti saama, ja see võtab kallid sekundid.

Iga aatom annab punkti. Sihtmärgi tabamine annab viis. Meeskond, kes ahnitseb kõike, mis lähedal — nagu jõehobu —, võib lüüa selle, kes pidevalt sihtmärki taga ajab ja teel kinni jääb. Aga kui vastane sind segab ja sa tavalisi koguda ei jõua, siis just need viiepunktilised teevad vahe sisse. Õiget strateegiat ei ole — kõik sõltub sellest, mida vastane parasjagu teeb ja kui hästi sinu eilne kood seda märkab.

Erinevalt päris jõehobudest ei loe siin ainult kiirus. Robot liigub nii kiiresti, kui kiiresti sa ta kaamerast lugema, otsustama ja liigutama panid. Eilne päev läkski just selle kiiruse ja taibukuse ehitamise peale.

Voorude vahel on viis minutit, mil tohib jututsännis koodi parandada. Kes küsib "miks meie liides seda aatomit ei näe, mis kaameras selgelt silma paistab", saab parema vastuse kui see, kes lihtsalt ütleb "tee paremaks". Õigete küsimuste esitamine on samuti õppekava osa.

---

## Kuidas see sarnaneb päris robootikaga

Kahe päeva jooksul ei tee õpilased mitte ühtegi harjutust, mis meenutaks inseneritööd. Nad teevad inseneritööd.

Claude Code on sama tööriist, mida kasutavad professionaalsed tarkvaraarendajad iga päev — vaata, mis muutub, otsusta, kas käivitad, kinnita tulemus. Seda nimetatakse koodiülevaatuseks ja õpilased tegid seda ilma, et keegi oleks pidanud sõnagi seletama.

Kohe alguses loob Claude Code igale meeskonnale isikliku GitHubi repo. Iga oluline edasiminek saab oma haru ja liidetakse hiljem põhitööga kokku — kui kaks meeskonnaliiget proovivad korraga eri suunas, ei lähe nende töö omavahel sassi. Kui midagi katki läheb või eile-õhtune lahendus oli parem kui tänahommikune, saab kümne sekundiga ajas tagasi minna. Seda nimetatakse versioonihalduseks ja õpilased kasutasid seda ilma, et keegi oleks neile sellest midagi õpetanud.

Esimene lahendus, mida Claude Code pakub, on alati liiga pikk ja liiga keerukas. Kolmandal katsel — pärast kahte luhtumist — jõutakse lahenduseni, mis päriselt töötab. Keegi ei ütle neile "hoia lihtsana" — nad tunnevad ise, kuidas tarbetu keerukus kokku vajub.

Ja teisel päeval, kui meeskond paneb oma eilse töö võistlusse, tunnevad nad asja, mida koolis harva tunda saab: nende enda kood ongi see, mis võidab või kaotab. Mitte hinne paberil — punktid laual.

Kahe päeva lõpuks tead kolme asja. Masin teeb täpselt seda, mida käsid. Õige küsimus on väärtuslikum kui kiire käsk. Ja tööriist, mille täna ehitad, on see, millega homme võistled.

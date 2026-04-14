# Robootika suvelaager

## Kaks päeva, kaks masinat, üks tõdemus

Laager kestab kaks päeva. Robotkäsi on neli — õpilased jagunevad meeskondadesse ja õpivad koos. Esimesel päeval juhib iga meeskond üht robotkätt. Võisteldakse nii meeskondlikult kui individuaalselt. Teisel päeval juhivad samad meeskonnad rovereid sarnaste vahenditega, aga 3 × 3 m väljakul kaheksa robotit korraga. Riistvara muutub, aga tööriistad jäävad samaks — ja see kordus ongi asja mõte.

Masinad teevad täpselt seda, mida neile öeldakse. Esimesel päeval on see lihtsalt huvitav. Teisel päeval, kui mitu inimest peavad omavahel kokku leppima, mida masinatele öelda, selgub tõeline keerukus. Asi pole puuduvas nupus masinal — probleem on hoopis kadunud fokusel, meeskonnatöö keerukusel.

---

## Robotid

Laagris on kahte sorti roboteid.

**Dobot MG400** on tööstuslik robotkäsi — samasugune, nagu tehastes asju kokku paneb, ainult väiksem. Ta ulatub laua kohale, saab asju üles tõsta ja maha panna. Liigub kiiresti ja täpselt, kui talle õigesti oma soove väljendada.

**SMARS rover** on väike ratastega robot, mis sõidab mööda põrandat. Igaüks on umbes peopesa suurune. Neid juhitakse samast liidesest mis robotkätt — klõpsa kaamerapildil kohale ja rover sõidab sinna.

---

## Kuidas juhitakse

Mõlemal päeval kasutavad kõik sama veebiliidest sülearvuti ekraanil. Liidesel on kolm osa.

Esiteks kaamera vaade otse ülevalt. Näed töölauda või väljakut linnulennult. Klõpsad pildil kohale — robot liigub sinna. See on kogu juhtimise alus.

Teiseks koodipaneel. Iga klõps käivitab Pythoni käsu ja koodipaneel näitab, mida see käsk täpselt teeb. Siia saab kirjutada kalibreerimise, automaatse tee planeerimise jne.

Kolmandaks jututsänn tehisintellektiga. Claude Code näeb nii koodi kui kaamerapilti. Temalt saab küsida, miks robot valesti läks, paluda strateegiat või lasta tal ise koodi kirjutada. Ta pakub lahendust, palub kasutaja valideerimist ja siis saab selle ka käivitada.

Töövoog on: näe, kirjelda, vaata üle, testi, kinnita. Nii töötavad ka päris tarkvarameeskonnad — õpilased ei tee lihtsustatud versiooni, nad teevad sama asja.

---

## Esimene päev — robotkäsi

### Mida õpitakse

Viie õpilasega meeskonnad, üks masin. Hommikul õpitakse liidest tundma: klõpsa kuubikule, käsi tõstab üles, paneb kogumiskasti. Lihtne. Aga siis selgub, et käsi ei peatu alati täpselt seal, kuhu klõpsati — kaameranurk tekitab nihet. Keegi ei hoiata selle eest ette. Nad põrkavad ise vastu tegelikkust ja avavad jututsäni, et küsida, miks.

See pool tundi — kui nad avastavad, et masin ei eksinud, vaid nende eeldus oli vale — on laagri kõige olulisem hetk.

Ülejäänud hommik kulub strateegia peale. Laual on erineva väärtusega kuubikuid — kollased lähedal ja odavad, punased kaugel ja kallid. Meeskonnad peavad ise välja mõtlema, kas tasub punaste järele minna. Keegi neile seda ei ütle.

### Milles võisteldakse

Robotite töölaud, kaks robotkätt vastaskülgedel, mõlemad ulatuvad samale tööpinnale. Korraga võistleb kaks meeskonda. Üheksakümmend sekundit aega. Eesmärk on koguda oma kasti rohkem punkte kui vastane.

Kollane kuubik annab kaks punkti ja on käe lähedal. Roheline annab viis ja on keskel. Punane annab üheksa, aga asub kõige kaugemal — neid on ainult kolm. Neli kollast annavad kaheksa punkti ja nende kogumine võtab murdosa ajast, mis kulub ühe punase peale. Vahe on üks punkt. Meeskond, kes selle matemaatika ise avastab, võidab — mitte kiiremini liigutades, vaid paremini mõeldes.

Voorude vahel on viis minutit, mil tohib Claude Code'ilt nõu küsida. Need, kes küsivad "mis on kiireim marsruut just praeguse kuubikute paigutuse jaoks," saavad parema vastuse kui need, kes ütlevad lihtsalt "tee kiiremaks." Õige küsimuse esitamine on osa õppekavast.

Aga kõige kavalamad õpivad vahepeal teise kätt segama, sest kui nende kood sellega ei arvesta, siis peavad nad roboti uuesti lukust lahti saama — ja see võtab juba palju väärtuslikke sekundeid.

---

## Teine päev — roverid

### Mida õpitakse

Igal meeskonnal viis liiget ja neli roverit. Sama liides, sama kaamera, sama jututsänn — aga piloote on neli korda rohkem ja üks neist ei juhi roverit. Juhendaja annab ühe ainsa vihje: viis inimest, neli roverit — üks teist ei juhi masinat. Mida meeskonnad selle viienda inimesega peale hakkavad, on täiesti nende enda asi.

Mõni meeskond paneb ta sektoreid hüüdma. Mõni paneb ta Claude Code'i jututsänni taha. Mõni ignoreerib vihjet ja annab talle roveri ka. Iga valik õpetab midagi.

Hommikul avastavad nad kohe, mis juhtub, kui kaks operaatorit saadavad oma roveri samale täpile, või kui kolmas rover jääb neljanda ette. Halva koostöö hinda tuntakse enne, kui võistlus seda kalliks teeb.

Teine päev lisab ka hoo kogumise. Iga korjatud täpp tõstab kogu meeskonna roverite kiirust. Väikesed varajased kogumised liituvad. Parim avakäik pole kõige kallim täpp — see on täpp, mis viib sind kallimate juurde enne vastast.

Ja siis on veel üks võimalus. Meeskond võib avada jututsäni ja paluda Claude Code'il üht roverit ise juhtida. See on lubatud, aga nõuab nelja tiimikaaslase nõusolekut. Läbirääkimine, mis selle ümber tekib — kas usaldame masinat, mida me ise enam ei juhi — on väärtuslikum kui ükskõik mis muu laagris planeeritu.

### Milles võisteldakse

Punane meeskond vastu sinist, neli roverit neli vastu, 3 × 3 meetrisel areenil. Viis inimest, neli roverit — kes juhib ja kes koordineerib, tuleb ise otsustada. Üheksakümmend sekundit. Põrandal on värvilised kettad — valged keskel ühe punkti eest, kollased laiali kolme eest, punased seinte ääres seitsme eest. Kogutud täppide summa loeb.

Meeskond, kus keegi jälgib suurt pilti, keegi hoiab silma vastasel ja keegi otsustab, millal minna kallimate täppide järele, võidab meeskonna üle, kes lihtsalt klõpsab kiiremini.

---

## Kuidas see sarnaneb päris robootikaga

Kogu laagri vältel ei tee õpilased harjutust, mis meenutab inseneritööd. Nad teevad inseneritööd.

Claude Code on sama tööriist, mida kasutavad professionaalsed tarkvaraarendajad iga päev — vaata, mis muutub, otsusta, kas käivitad, kinnita tulemus. Seda nimetatakse koodiülevaatuseks ja nad tegid seda ilma, et keegi oleks seletanud, mis see on.

Kõik kinnitatud muudatused salvestatakse versioonihaldusega. Kui midagi läheb katki, saab kümne sekundiga tagasi minna. Seda nimetatakse versioonikontrolliks ja nad kasutasid seda ilma, et keegi oleks õpetanud, mis see on.

Esimene lahendus, mida Claude Code pakub, on alati liiga pikk ja liiga keeruline. Kolme rea pärast, pärast kahte ebaõnnestunud katset, jõutakse lahenduseni, mis tegelikult töötab. Keegi ei ütle neile "hoia lihtsana" — nad tunnevad ise, kuidas tarbetu keerukus kokku vajub.

Ja teisel päeval, kui meeskond palub tehisintellektil üht roverit juhtida, ei peta nad. Nad teevad täpselt seda, mida teevad päris insenerid — leiavad kõige võimsama saadaoleva tööriista ja kasutavad seda. Küsimus pole kunagi "kas tohib," vaid "kas meeskond on nõus."

Kahe päeva lõpuks teavad nad kolme asja. Masin teeb täpselt seda, mida käsitakse. Õige küsimus on väärtuslikum kui kiire käsk. Ja kui viis inimest peavad koos töötama, siis kõige raskem osa pole kunagi robot.
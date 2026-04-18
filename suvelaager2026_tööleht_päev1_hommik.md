# Tööleht — päev 1 hommik — robotkäsi

**Kestus:** ~3 tundi (9:00–12:00)
**Osalejad:** 4 meeskonda à 5 õpilast, igal meeskonnal üks robotkäsi (Dobot MG400)
**Formaat:** viieastmeline mäng — värvi-tetris.

---

## Pedagoogiline põhimõte — juhendaja, loe läbi enne laagrit

### Kolm astet on baastase. Viis on neile, kes jõuavad kaugemale.

Mäng on kalibreeritud nii, et **enamik meeskondi jõuab kolmanda astmeni.** Vähesed jõuavad viiendani. Kumbki pole läbikukkumine ega erisaavutus — see on maastik, kus erinevad meeskonnad jõuavad erinevale kaugusele.

Juhendaja ei survesta kedagi viienda astme poole. Ei lohuta kedagi, kes jõudis ainult kolmandani. Kolm on hea tulemus. Viis on hea tulemus. Üks on hea tulemus, kui meeskond mõistab, mida nad tegid.

### Õpilane peab mõistma, mida tema teeb

Kood on tööriist, mitte õppeaine. Õpilase ülesanne ei ole Pythoni mõistmine — see on **oma teo mõistmine**. Miks nende robot nüüd kiiremini jõuab. Miks see muudatus aitas. Millise otsuse nad tegid.

- *"Mis see Pythoni rida teeb?"* — pole laagri küsimus.
- *"Mis teie jaoks just muutus?"* — on laagri küsimus.

Kui programm töötab, ei sunni koodi lugema. Kui programm ei tööta, meeskond vaatab ise — ja alles siis on paslik küsida.

---

## Mängu mehaanika

**Värvi-tetris (tagurpidi tetris):**

- Laual on laiali värvilisi nuppe (punased, kollased, rohelised, sinised). Kokku 25–30 nuppu.
- Robotkäe-poolses servas asub **kogumistsoon**.
- Robotkäsi tõstab nuppe vaakumiga: laskub nupule, haarab, tõstab, viib, laseb lahti.
- Ekraanil on **aktiivne värv** ja **taganloendav taimer**.
- Õige värvi nupp, mis jõuab kogumistsooni enne taimeri lõppu = **1 punkt**.
- Taimer otsa → algab uus aken. Kas tuleb sama värv või vahetub juhuslikult.
- Kui meeskond tõstis nupu üles, aga see ei jõua kogumistsooni enne värvi vahetust — **nupp läheb kaotsi**. Punkte ei saa ja nupp on ära kasutatud (kogumistsoonis, ei tule tagasi lauale).

**Valuline koht:** robot on poole peal, kui värv vahetub. Otsus: kas lasta nupp maha (kaotad selle, punkte ei saa, aga saad uue värvi järele minna) või jätkata (panustad, et sama värv tuleb kohe uuesti — võib-olla tuleb, võib-olla ei).

**Robotkäe kiirus (juhendajale taustaks):**
- Nupule liikumine: ~2 sek
- Vaakumiga haaramine: ~1 sek
- Kogumistsooni viimine: ~2 sek
- Mahapanek: ~1 sek
- **Kokku üks korjamine: ~6 sek**

Sellest järeldub: 5-sekundise aknaga ei jõua käsitsi üldse. 15-sekundise aknaga jõuad mugavalt kaks. Sellele toetub mängu raskusgradient.

---

## Üldine struktuur

**Iga aste on sama mäng. Rohkem aknaid, lühemad ajad.**

| Aste | Akent | Aja aken | Punktilävi | Uus tööriist |
|---|---|---|---|---|
| 1 | 3 | 15 s | 2 / 3 | — |
| 2 | 5 | 12 s | 3 / 5 | — |
| 3 | 8 | 10 s | 4 / 8 | **Kalibreerimine** |
| 4 | 12 | 8 s | 6 / 12 | **Automaatne tuvastus (süsteem näitab, mis on võimalik)** |
| 5 | 20 | 6 s | 10 / 20 | **Täisautomaatika (süsteem valib ja saadab ise)** |

Läve ületamine avab järgmise astme automaatselt. Meeskond võib proovida nii tihti, kui soovib.

---

## 1. aste — kolm akent, rahulik tempo

**Avab:** laager algab siin.

**Mäng:** 3 värviakent, igaüks 15 sek. Lävi: 2 punkti 3-st.

**Mida meeskond avastab:** kuidas liides töötab, kuidas robot nupule jõuab, kuidas vaakum haarab. 15-sekundine aken on mugav — jõuad ühe nupu kätte ja aega jääb veel.

**Juhendaja märkused:**
- Ära seleta. Lase katsetada.
- Lase kõigil viiel meeskonnakaaslasel korra klõpsata, kui soovivad.
- Kui meeskond küsib, mida vaakum teeb, vasta: *"Proovige."*

---

## 2. aste — viis akent, pinge tõuseb

**Avab:** 1. aste läbitud.

**Mäng:** 5 akent × 12 sek. Lävi: 3 punkti 5-st.

**Mida meeskond avastab:** aeg pigistab. Kui klõps tuli aeglaselt või robot eksis, aken saab otsa. Esimene kokkupuude kaotsi läinud nupuga.

**Juhendaja märkused:**
- Kui meeskond frustreerub kaotsi läinud nupust, ära lohuta. See on mängu mehaanika.
- Ära soovita strateegiat. Värvi meeskond ei vali — see on etteantud. Aga mitme aktiivse värvi nupu seast saab valida, ja lähima valik säästab sekundeid. Las nad avastavad selle ise.

---

## 3. aste — kaheksa akent *(avab: kalibreerimine)* — **enamiku finiš**

**Avab:** 2. aste läbitud.

**Uus tööriist (mäng näitab pärast astme avanemist):**

> *"Robotkäsi ei taba alati täpselt seal, kuhu klõpsasid — kaamera on nurga all. Iga möödaminek sööb sekundeid. Saad küsida AI-lt, kuidas kalibreerida."*

**Mäng:** 8 akent × 10 sek. Lävi: 4 punkti 8-st.

**Mida meeskond avastab:** ilma kalibreerimata vaakum ei haara (maandub nupu kõrval) → katse kordub → aken saab otsa → nupp kaotsi. Kalibreerimine on ainus tee edasi.

**Juhendaja märkused:**
- See aste on **enamiku meeskondade finišijoon**. Kui meeskond läbib, on laager nende jaoks pedagoogiliselt õnnestunud.
- Ära ütle "kalibreerige." Mäng ütleb seda.
- **Pärast läbimist küsi ÜKS küsimus:** *"Mis teie jaoks just muutus?"*
  - Hea vastus: *"Kalibreerisime, nüüd robot tabab, jõuame ajas tagasi."*
  - Ebapiisav vastus: *"Ei tea, läks lihtsalt paremaks."*
  - Kui vastus on ebapiisav, istu kõrvale ja arutage oma sõnades, kuni meeskond suudab kirjeldada, mida **nemad** tegid.
- Meeskond, kes ei oska pärast 3. astet oma sõnades seletada, mida nad tegid, ei ole valmis pärastlõunaks — isegi kui tehnilise läve ületas.

---

## 4. aste — kaksteist akent *(avab: automaatne tuvastus)*

**Avab:** 3. aste läbitud.

**Uus tööriist:**

> *"Liides oskab kaamerapildilt ise leida kõik nupud ja nende värvid. Lisaks: need nupud, mida jõuad veel käe praegusest asukohast ja allesjäänud ajast ära tuua, märgitakse roheliselt. Klõpsad ikka sina ise — süsteem näitab ainult, mis on võimalik."*

**Mäng:** 12 akent × 8 sek. Lävi: 6 punkti 12-st.

**Mida meeskond avastab:** silmadega otsimine "kus on aktiivne värv ja kas jõuan" on aeglane. Süsteem teeb otsingu ja teostatavusarvutuse nende eest — nad klõpsavad vaid rohelise nupu peale. Aeg, mis varem kulus otsimisele, saab nüüd teo jaoks kasutada.

**Juhendaja märkused:**
- Meeskond klõpsab ikkagi ise. Süsteem näitab valikud, nemad teevad otsuse.
- Kui mõni roheline kaob käe liikudes — see on mehaanika. Teostatavus muutub reaalajas.
- Kui meeskond küsib *"miks see nupp pole roheline?"*, vasta: *"Arvutage ise — kas jõuaksite sinna ja kogumistsooni enne akna lõppu?"*
- **Pärast läbimist küsi:** *"Mis muutus võrreldes 3. astmega?"*
  - Oodatud vastus: *"Me ei pea enam otsima, kus õige värv on — süsteem näitab, mis on võimalik."*

---

## 5. aste — kakskümmend akent *(avab: täisautomaatika)*

**Avab:** 4. aste läbitud.

**Uus tööriist:**

> *"Eelmisel astmel pidid veel ise klõpsama. Nüüd saad lasta süsteemil ka valida ja saata — sina annad ainult strateegia (näiteks: eelista alati lähimat; või hoia käsi keskel; või ennusta korduvat värvi)."*

**Mäng:** 20 akent × 6 sek. Lävi: 10 punkti 20-st.

**Mida meeskond avastab:** 6 sek = vähem kui ühe nupu transport. Klõpsata enam ei jõua. Ainult täisautomaatika suudab — ja isegi see mitte 100%. Strateegia loeb:
- Alati lähim sama-värvi nupp?
- Hoida käsi keskel, et kõikjale jõuaks kiiresti?
- Ennustada, et sama värv tuleb uuesti, ja panustada?

**Juhendaja märkused:**
- See aste on **vähestele**. Kui meeskond ei jõua siia, ei ole midagi puudu. 3. aste on baastase.
- Meeskonnad, kes jõuavad siia, peavad tegema strateegilise valiku. Küsi: *"Mis strateegia te programmile andsite ja miks?"*
- See küsimus eristab: kas meeskond mõistab, mida **nemad** programmile ütlesid, või lasid AI-l enda eest otsustada.

---

## Kontroll enne lõunat

Mitte testina, vaid juhendaja enesevaatluseks. Kas meeskond suudab oma sõnades vastata:

**Pärast 3. astet (enamiku finiš):**
1. Miks vaakum alguses ei haaranud alati nuppu?
2. Mis muutus, kui te kalibreerisite?

**Pärast 4. astet:**
3. Miks rohelised nupud ekraanil aitavad kiiremini otsustada?

**Pärast 5. astet:**
4. Mis strateegia te süsteemile andsite ja miks?

Meeskond, kes ei oska vastata, ei ole valmis pärastlõunaseks võistluseks — isegi kui tehnilise läve ületas. Võistlus on pingeline ja pimedad teod seal ei päästa.

---

## Juhendaja põhimõtted

1. **Mäng õpetab, mitte sina.** Sinu töö on jälgida, mitte seletada.
2. **Kolm on hea, viis on hea, üks on hea — kui nad teavad, mida nad tegid.** Ära survesta kiirust. Ära halvusta aeglust.
3. **Ära sunni koodi vaatama.** Kui programm töötab, lase meeskonnal edasi minna. Kui programm katkeb, avab kood end ise.
4. **Küsi, mida nemad tegid, mitte mida kood tegi.** *"Mis teie jaoks muutus?"* > *"Mis see kood teeb?"*
5. **Frustratsioon on osa mängust.** Kui meeskond on kinni, ära päästa. Küsi üks küsimus ja istu kõrvale.
6. **Ära kommenteeri jooksvat tulemust.** Ei "tubli", ei "halvasti" ajal, kui meeskond töötab. Kõnele faktidega: nende punktid, nende otsus.
7. **Aga leidmise hetke — seda tuleb märgata.** Kui meeskond oli frustratsioonis kinni ja siis leidis tee välja, pööra tähelepanu **tundele**, mitte tulemusele: *"Olite kinni, siis läks läbi. Pange see tunne meelde — järgmine kord, kui olete kinni, teate, mida otsida."* Frustratsioon ilma leidmise äratundmiseta õpetab, et asi on raske. Frustratsioon koos leidmise äratundmisega õpetab, et see on tee.
8. **Kui meeskond näitab koodi ja küsib "kas see on õige" — vasta: *"Käivitage ja vaadake."*** Kood, mis töötab, on õige. Kood, mis ei tööta, avab end ise.

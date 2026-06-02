## Prototüüpimine: Verstapost 5 — Tootmisvalmis süsteem

**Maht:** 14 tundi | **Hindamine:** 20 punkti | **Meeskonnatöö:** 4-liikmelised meeskonnad

### Mida teete

V5 on viimane verstapost enne areeniüritust. Põhisõnum: **kui keegi teine saab sinu repo ja seda lugedes ehitab sama roveri, on V5 lõpetatud**. Te viimistlete oma rovveri, lisate asukoha määramise areeni standardvarustuse abil, teete dokumentatsiooni tiraaživalmis ja koondate V1–V4 mõõtmised üheks pildiks.

V5-l on kolm paralleelset eesmärki:

- Viimistleda rover lõplikuks — V4 nõrkused parandatud või ausalt dokumenteeritud
- Lisada asukoha määramine (ArUco markerid laes + valikuline värvitäpid/magnetid põrandal)
- Teha dokumentatsioon tiraaživalmis (võõras inimene peab repost roveri kokku panema)

**Viimistlus ja piirangute dokumentatsioon** — V5 pole "paranda kõik" verstapost, vaid **piirangute aus dokumentatsioon**. Iga V4-st järelejäänud puudus peab jõudma V5 lõppu kas (a) parandatuna ja uuesti testituna, või (b) selgelt kirjas kui **dokumenteeritud piirang** — mehaaniliselt enam ei lahenda, jätame tarkvarale, juhtimisloogikale või järgmise põlvkonna riistvarale. Dokumenteeritud piirang on lahendatav ülemises kihis; peidetud piirang hammustab kasutajat. V5 tabel jätkub V4 tabeli kõrvalt ("Komponent | V4 staatus | V5 otsus | Tulemus | Lõplik staatus") ja sisaldab nii lahendatud kui dokumenteeritud piiranguid.

**Asukoha määramine — areeni standardvarustus** — areenil on kolm tasandit navigatsiooniabi, kõikidele meeskondadele kättesaadavad:

- **Tasand 1 — ArUco markerid laes** (ruudu-täpsus, soovituslik baas): 9 markerit DICT_4X4_50, igaüks 20 × 20 cm, paigaldatud iga 1×1 m OSB mooduli keskele ~2 m kõrgusele lakke. Chess-laadne notatsioon A1–C3, ID 0–8, kõik "ülemise" küljega sinise poole suunatud. Rover vajab ülespoole vaatavat kaamerat.
- **Tasand 2 — Värvitäpid põrandavõrgustikul** (täpsem, kasutab V4 värviandurit): sinised mooduli keskpunktis (9), kollased mooduli nurkades (9 × 4 = 36), roheline B2 keskel (origin). Punased mängualad lõigatakse vajadusel täppide kohale auguga.
- **Tasand 3 — Magnetid põrandavõrgustikus** (väga täpne, valikuline): NdFeB 5 × 2 mm sama paigutusega kui värvitäpid, Hall-andur rovveril. Töötab ka punaste alade all (loeb läbi mitte-magnetilise katte).

Areeni standardformaat ei piira — meeskond võib kasutada ka muid asukoha-tuvastamise lahendusi (UWB, magnetkompass, optiline flow vms).

**Tiraaživalmis dokumentatsioon** — keegi kolmas (teise meeskonna liige) peab saama sinu repo ja tellitud komponentidega sama roveri kokku panna ilma sinult küsimata. Sisaldab: README, kokkupanekujuhend (samm-sammuline, piltidega), 3D prindifailid valideeritud seadetega, BOM, tarkvarapaigalduse juhend, hooldusjuhend, teadaolevate probleemide nimekiri.

**Operaatori juhend — 1 lehekülg** — A4 lehekülg, mille pealt operaator (kes pole varem näinud) saab terve matši algusest lõpuni läbi viia. Reegel: mitte rohkem kui üks lehekülg.

### Analüüsid (Jupyter Lab)

Kolm analüüsi Jupyter notebooks:

1. **Tiraaži ajaeelarve** — mõõda iga 3D-detaili printimisaeg, kokkupaneku aeg, komponentide tarneaeg. Arvuta välja, mitu lisaroverit jõuad tiraaži-aja jooksul (30.05–11.06, ~12 päeva) toota.
2. **Dokumentatsiooni läbikäik** — anna repo kolmandale inimesele (teise meeskonna liikmele), lase tal proovida ühte konkreetset ülesannet (tarkvara paigaldus, BOM-ist komponendi leidmine, kokkupanekujuhendi lugemine). Märgi iga koht, kus ta jääb kinni.
3. **V1–V4 mõõtmiste koondgraafik** — kogu projekti tõehetk. Koonda kõikide verstapostide mõõtmised ühte notebook'i: V1 spetsifikatsioon, V2 testid, V3 integratsioon, V4 viimistlus. Visualiseeri roveri arengu lugu. Lisa lõikorefleksioon: mis pidas paika, mis läks vale, mida muudaksid V1 spetsifikatsioonis täna.

### Kaitsmiseks on vaja

**Ainult git repositooriumi link.** Repos peab olema:

- Lõplik töötav kood (vähemalt 2 autonoomsuse astet V4-st + V5 viimistlused)
- Ülespoole vaatava kaamera + ArUco dekoodri implementatsioon (Tasand 1 standardvarustusest)
- Analüüside Jupyter notebooks koos mõõteandmetega (CSV)
- Tiraaživalmis dokumentatsioon (README, kokkupanek, tarkvara, BOM, hooldus, teadaolevad probleemid)
- 1-leheline operaatori juhend
- STL-id valideeritud prindiseadetega **+ CAD lähtefailid** (Fusion 360 `.f3z`/`.f3d` arhiivid või CadQuery `.py` skriptid) — STL on eksport, lähtefail on muudetav disain
- Uuendatud spetsifikatsioon + V5 viimistlustabel (V4 jätkuks)
- Fotod ja videod lõplikust roverist

### Hindamiskriteeriumid

| Kategooria | Punktid |
| :--- | :--- |
| Tööfailid — lõplik kood, STL-id **+ CAD lähtefailid** (Fusion `.f3z`/`.f3d` või CadQuery `.py`), BOM, fotod/videod | 4 p |
| Analüüs — 3 Jupyter notebook'i (tiraaži ajaeelarve, dokumentatsiooni läbikäik, V1–V4 koondgraafik) | 4 p |
| Prototüüp — rover viimistletud, asukoha määramine (ArUco lakke) töötab, tulemused dokumenteeritud | 4 p |
| Dokumentatsioon — tiraaživalmis (kokkupanek, tarkvara, hooldus, operaatori juhend, teadaolevad probleemid) | 4 p |
| Küsimuste-vastuste sessioon — demo + refleksioon (mis õpitu kandub edasi järgmistesse projektidesse?) | 4 p |
| **Kokku** | **20 p** |

### Täielik tööleht

📎 *Lisa siia link täielikule töölehele*

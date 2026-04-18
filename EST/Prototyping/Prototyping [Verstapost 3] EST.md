## Prototüüpimine: Verstapost 3 — Integreeritud tehniline prototüüp

**Maht:** 18 tundi | **Hindamine:** 20 punkti | **Kohtumine: L 18.04**

**NB: 2. tellimus: Kellel veel PCB tellimata siis teeme kiiresti ära**

V2 lõpus sul oli sõitev testšassii ja veebileht nupuga "edasi". Nüüd paned kõik kokku ühele šassiile ja asendad nupud kaamerapildil klõpsamisega. Kui operaator klõpsab pildil kohale, sõidab robot sinna — see on V3 põhiülesanne.

Prioriteet on järjekorras: kõigepealt pane komponendid ühele šassiile ja kontrollime üle et kõik ikka töötab. Siis kalibreeri kaamera (ilma selleta ei saa klõpsu pildil asukohaks maapinnal tõlgendada). Siis ehita raycast loogika. Leia lahendus kuidas nüüd robot "enam vähem" ±10mm ja ±3 kraadi nurgaga. Kui midagi ei tööta, küsi kõigepealt meeskonna kaaslaselt, siis moodli foorumis või minult isiklikult, ära marineeri kauem kui 15 minutit plaani tegemisega.

---

### 1. Integreeritud šassii

**Eeldus:** V2 ajam, side ja veebiliides peavad töötama.

**Eesmärk:** Koosta kõik komponendid ja oma PCB ühel šassiil, toide ühest akust, üks süsteem mis käivitub ühe lülitiga.

**Mida vaja:**
- Kõik V2 komponendid (mootorid, draiver, MCU, andurid, arvutusplatvorm)
- Aku (LiPo, USB powerbank vms. — sõltub sinu valikust)
- Toitelüliti
- Juhtmed, klemmid, kahepoolne teip / kruvid

**Ülesanne:**

1. Paiguta komponendid šassiile nii et kaamera näeb ette (raycast jaoks), andurid on oma kohtades (kaugus ette, värv alla), ja aku on lihtne vahetada
2. Ühenda ühine toitesüsteem — üks lüliti sisse/välja
3. Käivita, ava veebileht, kontrolli et kõik mis V2 lõpus töötas töötab ikka
4. Kui midagi ei tööta pärast kokkupanekut → **ära jätka**, otsi viga üles (tavaliselt: halb maandus, kontakt lahti, toitepinge langeb koormuse all)

**Toitehierarhia kontroll:**

- Aku pinge (nt 7.4V LiPo või 5V powerbank) → (Boost 5V/12V) → Motor Driver → Motor
- Aku pinge (nt 7.4V LiPo või 5V powerbank) → regulaator → 5V loogikale ja 3.3V MCU-le
- **Ühine GND kõigil komponentidel** — ilma selleta ei tööta side

**Kontroll multimeetriga:**

```
Enne pinge rakendamist (multimeeter, toide VÄLJAS):
1. Lühiühenduse test — multimeeter „continuity" režiimis (piiks). Kontrolli VCC → GND,
   12V → GND, 6V → GND, 5V → GND, 3.3V → GND. Kui piiksub või takistus on alla ~10 Ω → lühis, ära lülita sisse.
2. Mõõda aku pinge (akuklemmid, koormuseta) — nt LiPo 2S täis ~8.4V, kui erineb millegipooles, peatu, uuri, saa aru 

Alles nüüd lülita sisse:
3. Mõõda toitejaotuse punkte koormuse all — kas 5V on tõesti 5V, 6V tõesti 6V?
4. Kontrolli et MCU käivitus (LED, seerial output). Kui mingi regulaator on kuum — kohe välja.
```

**YouTube/AI otsisõnad:**
- `rover robot chassis layout design`
- `LiPo battery voltage regulator 12V 5V 3.3V`
- `USB-C PD trigger`
- `How to test PCBs`
- `Top PCB hidden tricks`
---

### 2. Kaamera kalibreerimine — A4 malelaud + OpenCV

**Eesmärk:** kalibreeri kaamera ühe A4 prinditud malelaudga. OpenCV tuvastab kõik malelaud nurgad automaatselt alla-piksli täpsusega, malelaud ise defineerib koordinaatsüsteemi, ja homograafiamaatriks tõlgib iga klõpsu otse põrandakoordinaatideks. **Mitte ühtegi käsitsi mõõdulindiga mõõtmist kalibreerimise hetkel.**

**Miks see on parem kui mõõdulint/laser:**
- **Sub-piksli täpsus** — `cv2.cornerSubPix` täpsustub alla 0,1 piksli
- **63 punkti 4 asemel** (tavaline 7×9 malelaud) — RANSAC filtreerib müra välja
- **Kogu geomeetria tuleb mustri sisemisest struktuurist** (teadaolev ruudu suurus) — mitte käsitsi mõõtmisest
- **Korratav** — printi üks kord, kasuta alati samamoodi
- **Visuaalne kontroll** — OpenCV joonistab tuvastatud nurgad peale, näed kohe kas töötab
- **Sama tehnika** mida kasutavad päris visioonisüsteemid (autod, droonid, tööstusrobootika)

**Koordinaadisüsteem:** malelaud defineerib geomeetria, aga me tahame koordinaate **roboti pöördekeskme** suhtes, mitte malelaua suhtes. Sellepärast mõõdame kalibreerimise ajal ühe arvu: **kui kaugel on malelaua keskpunkt roboti pöördekeskmest** (`X0_CM`). See arv läheb otse homograafia arvutusse — iga piksliklõps annab kohe roboti-suhtelise koordinaadi. X = ette, Y = paremale.

**Paigutus:** robot seisab paigal, kaamera vaatab ette. Pane malelaud põrandale kaamera vaatevälja — sinna kuhu enamus klõpse läheb. Mõõda roboti pöördekeskmest malelaua keskpunktini — see on `X0_CM`. Kui malelaud on roboti pikiteljel sümmeetriliselt, siis `Y0_CM = 0`. Üks mõõtmine, üks kord.

**Mida vaja:**
- Töötav kaamera voog + võimalus salvestada üks kaader
- A4 prinditud 7×9 sisemise nurgaga malelaud (vt all)
- Mõõdulint (üks mõõtmine: robot → malelaua keskpunkt)
- Python paketid: `opencv-python`, `numpy`

---

**Samm 1: Genereeri ja prindi malelaud A4-le**

Soovitatav on ise genereerida PDF Pythoni koodiga — siis tead kindlalt mis ruudu suurus on ja sul on kontrollmärk peale. Skript Jupyter Lab'is:

```python
# pip install matplotlib  (kui pole)
import matplotlib.pyplot as plt
import matplotlib.patches as patches

# --- Parameetrid ---
COLS = 8           # ruute horisontaalselt (annab 7 sisemist nurka)
ROWS = 10          # ruute vertikaalselt (annab 9 sisemist nurka)
SQUARE_MM = 25.0   # ühe ruudu külg millimeetrites
REF_LINE_MM = 50.0 # kontrolljoon printimise verifitseerimiseks

# A4 mõõdud tollides (matplotlib tahab tolle)
A4_W_IN = 210 / 25.4
A4_H_IN = 297 / 25.4

fig, ax = plt.subplots(figsize=(A4_W_IN, A4_H_IN))
fig.subplots_adjust(left=0, right=1, top=1, bottom=0)

# Muster tsentreeritud
pat_w_mm = COLS * SQUARE_MM
pat_h_mm = ROWS * SQUARE_MM
x0_mm = (210 - pat_w_mm) / 2
y0_mm = (297 - pat_h_mm) / 2

# Joonista mustad ruudud
for r in range(ROWS):
    for c in range(COLS):
        if (r + c) % 2 == 0:
            x = (x0_mm + c * SQUARE_MM) / 25.4
            y = (y0_mm + r * SQUARE_MM) / 25.4
            s = SQUARE_MM / 25.4
            ax.add_patch(patches.Rectangle((x, y), s, s, facecolor='black'))

# Kontrolljoon all servas (mõõda joonlauaga pärast printimist!)
ax.plot([10/25.4, (10 + REF_LINE_MM)/25.4], [5/25.4, 5/25.4],
        'k-', linewidth=2)
ax.text(10/25.4, 8/25.4,
        f'Kontrolljoon: {REF_LINE_MM:.0f} mm — mõõda joonlauaga',
        fontsize=8)
ax.text(10/25.4, 12/25.4,
        f'Ruudu suurus: {SQUARE_MM:.1f} mm | Muster: {COLS}x{ROWS}',
        fontsize=8)

ax.set_xlim(0, A4_W_IN)
ax.set_ylim(0, A4_H_IN)
ax.set_aspect('equal')
ax.axis('off')

plt.savefig('malelaud_a4.pdf', format='pdf', bbox_inches=None, pad_inches=0)
print("Salvestatud: malelaud_a4.pdf")
```

**Printimisel kriitiline:**

- **„Scale = 100%" / „Actual size"** — MITTE „Fit to page", „Shrink oversized", „Auto rotate and scale"
- Pärast printimist **mõõda joonlauaga kontrolljoont** — kui see on 50 mm (±0,5 mm), siis ruudud on ka õiged 25 mm
- **Kui kontrolljoon on vale** → muuda `SQUARE_MM` koodis päris väärtuseks (nt mõõdad 49 mm → ruut on 24,5 mm) või printida uuesti teise printeriga

**Varuvariant — valmis PDF internetist:**

Kui Python ei ole käepärast, [calib.io pattern generator](https://calib.io/pages/camera-calibration-pattern-generator) teeb sama asja brauseris. Vali „Checkerboard", 8×10 ruutu, 25 mm ruut, lae alla PDF. Kontrollida ikka trükitud suurust joonlauaga.

**Samm 2: Paigutus ja offset mõõtmine**

1. Pane robot põrandale, kaamera vaatab ette
2. Pane malelaud kaamera vaatevälja — nihuta kuni **malelaua keskpunkt on umbes pildi keskel** (parim nurkade levikut)
3. Mõõda roboti pöördekeskmest malelaua keskpunktini: see on `X0_CM`. Kui malelaud on roboti ees sümmeetriliselt, siis `Y0_CM = 0`
4. Kirjuta need arvud koodi — need lähevad homograafia arvutusse

**Samm 3: Salvesta üks kaader malelaudga**

Salvesta üks jpg/png kaader kaamerast (nt ava kaamera `/capture` endpoint või salvesta pildi brauserist). Malelaud peab olema tervesti nähtav — kõik 63 sisemist nurka kaadris.

**Samm 4: Tuvasta nurgad ja arvuta homograafia**

*testimata näidiskood, võibolla vajab parandamist, polnud andmeid veel et testida*

```python
import cv2
import numpy as np

# --- Parameetrid ---
PATTERN_SIZE = (7, 9)       # sisemiste nurkade arv (veerud, read)
SQUARE_MM    = 25.3         # tegelik prinditud ruudu suurus (mõõda joonlauaga!)

# Roboti pöördekeskmest malelaua keskpunktini (mõõdetud samm 2-s)
X0_CM        = 30.0         # ette (cm)
Y0_CM        = 0.0          # paremale (cm), 0 kui sümmeetriline

# --- Lae kaader ---
img = cv2.imread("calibration_frame.jpg")
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# --- Tuvasta malelaud nurgad ---
found, corners = cv2.findChessboardCorners(gray, PATTERN_SIZE, None)
if not found:
    raise RuntimeError("Malelauda ei leitud! Kontrolli valgustust, mustri asendit, fokuseerimist.")

# Täpsusta sub-piksli tasemele
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
corners_refined = cv2.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)
pixel_pts = corners_refined.reshape(-1, 2).astype(np.float32)

# --- Genereeri iga nurga tegelikud (X, Y) cm-des ---
# Koordinaadid on keskpunkti ümber: esimene nurk on (-half_h, -half_w) kaugusel keskpunktist
half_rows = (PATTERN_SIZE[1] - 1) / 2.0   # X suunas poollaius (cm)
half_cols = (PATTERN_SIZE[0] - 1) / 2.0   # Y suunas poollaius (cm)

floor_pts = []
for row in range(PATTERN_SIZE[1]):         # rida = X suunas (ette)
    for col in range(PATTERN_SIZE[0]):     # veerg = Y suunas (paremale)
        x_cm = X0_CM + (row - half_rows) * (SQUARE_MM / 10.0)
        y_cm = Y0_CM + (col - half_cols) * (SQUARE_MM / 10.0)
        floor_pts.append([x_cm, y_cm])
floor_pts = np.array(floor_pts, dtype=np.float32)

# --- Arvuta homograafia (63 punkti, RANSAC väljastab outlierid) ---
H, mask = cv2.findHomography(pixel_pts, floor_pts, cv2.RANSAC, 5.0)

# --- Salvesta ---
np.save("homography.npy", H)
print(f"Tuvastati {len(pixel_pts)} nurka, kasutati {int(mask.sum())} inlierit")

# --- Visuaalne kontroll ---
vis = img.copy()
cv2.drawChessboardCorners(vis, PATTERN_SIZE, corners_refined, found)
cv2.imwrite("calibration_check.jpg", vis)
```

**Samm 5: Kontrolli tulemust**

Avada `calibration_check.jpg` — iga malelaud nurk peab olema märgitud värvilise ringiga, joonte jadas. Kui ühel real on puuduv või kohane mujal, tuvastamine ei töötanud — kontrolli valgustust (vältida varje, peegeldumisi) ja muster peab olema tervesti kaadris.

---

**Kui sul pole printerit — varuvariant:**

Märgi põrandale 4 teipmärki sinna, kus nad paistavad kaamera pildi nurkades, ja mõõda mõõdulindiga nende X ja Y roboti pöördekeskmest. Siis `cv2.getPerspectiveTransform(4 pikslit, 4 põrandapunkti)` asendab `cv2.findHomography` + malelaua osa. Täpsus on ~±2 cm parimal juhul, malelauaga saad alla 1 cm.

---

**YouTube/AI otsisõnad:**
- `OpenCV findChessboardCorners Python`
- `cv2 cornerSubPix tutorial`
- `chessboard camera calibration OpenCV`
- `cv2 findHomography RANSAC`
- `print chessboard A4 calibration` (malelaud PDF-id)
- `ArUco marker calibration` (alternatiiv kui malelaud ei tööta)

---

### 3. Pixel-to-ground homograafiaga

**Mis on `H` maatriks?** H = **h**omograafia (kreeka: *homo* = sama, *graphia* = joonis). See on 3×3 maatriks mis teisendab pikslikoordinaadi põrandakoordinaadiks. Malelaua kalibreerimine andis OpenCV-le 63 paari: "see piksel = see punkt põrandal." Nendest 63 paarist arvutas OpenCV ühe maatriksi mis töötab **kõigi** pikslite jaoks, mitte ainult 63 nurga jaoks — see ongi H. Pärast arvutamist malelaua enam vaja ei ole, H-s on kogu teisendus sees.

```
piksel (px, py)  →  [ H ]  →  põrand (x_cm, y_cm) roboti suhtes
```

**Eeldus:** kalibreerimine (samm 2) tehtud, `H` maatriks olemas.

**Eesmärk:** iga klõps pildil → põrandakoordinaat `(x_ette, y_paremale)`.

**Koodi idee:**

*testimata näidiskood, võibolla vajab parandamist, polnud andmeid veel et testida*

```python
import cv2
import numpy as np

# Lae homograafia kettalt (või kasuta mälus olevat)
H = np.load("homography.npy")

def pixel_to_ground(px, py):
    """Klõps pildil (px, py) → põrandakoordinaat (x_cm_ette, y_cm_paremale)."""
    point = np.array([[[float(px), float(py)]]], dtype=np.float32)
    transformed = cv2.perspectiveTransform(point, H)
    x_fwd, y_right = transformed[0][0]
    return float(x_fwd), float(y_right)
```

See on kogu loogika — 3 rida tööd teevad cv2 eest. Pikslist põrandakoordinaadiks, läätsemoonutust arvestades, ilma trigonomeetriata.

**Kontroll enne edasiminemist:**

1. Pane ekstra objekt (nt pudelikaas) põrandale teadud kohta — näiteks `(60 cm ette, 20 cm paremale)`.
2. Klõpsa sellele pildil — sinu kood peab serverisse saatma klõpsu koordinaadid.
3. Serveris kutsu `pixel_to_ground(px, py)` — kas tulemus on lähedal `(60, 20)`-le?
4. Korda 5 kohaga üle põranda (lähedal, kaugel, servades).

**Tolerants:** mediaan viga peaks olema alla 3 cm. Kui üle 5 cm → 4 nurga mõõtmised olid ebatäpsed, kalibreeri uuesti.

**Kui servades on palju suurem viga** → kaameral on läätsemoonutus (fisheye). Lahendus: vali 4 kalibreerimispunkti, mis katavad pildi keskosa (20%–80%), mitte servad.

**YouTube/AI otsisõnad:**
- `cv2 perspectiveTransform point example`
- `pixel to world coordinates homography`
- `robot camera ground plane mapping`

---

### 4. Klõpsa-ja-sõida loogika

**Eeldus:** homograafia (samm 3) annab usaldusväärseid põrandakoordinaate.

**Eesmärk:** ühenda kogu ahel — klõps → `pixel_to_ground` → arvuta kaugus + nurk → pööra → sõida → peatu.

**Põhiloogika:**

Klõps pildil käivitab järgmise ahela:

1. **Piksel → põrandakoordinaat**: homograafia (samm 3) teisendab klõpsu piksli (px, py) põrandakoordinaadiks (x_ette, y_paremale) roboti suhtes
2. **Koordinaat → kaugus ja nurk**: Pythagorase teoreemiga kaugus, `atan2`-ga nurk. Nurk 0° = otse ees, positiivne = paremale, negatiivne = vasakule
3. **Kontroll**: kui sihtpunkt on roboti taga (x negatiivne) või liiga kaugel (üle 3m) → loobu, ära sõida
4. **Pööra**: kui nurk on üle 5° (alla seda mürasse läheb), pööra õiges suunas. Pööramisaeg = nurk jagatud pöördekiirusega (kraadi sekundis, mõõdetud). Peata, oota hetk (inerts)
5. **Sõida otse**: sõiduaeg = kaugus jagatud kiirusega (cm/s, mõõdetud). Peata.

Sul on vaja kahte mõõdetud konstanti oma robotilt: **lineaarne kiirus** (cm/s) ja **pöördekiirus** (kraadi/s). Mõlemad mõõdad kronomeetriga.

**Veebiliidese pool:**

Asenda V2 nupud kaamera pildiga mille peale saab klõpsata. Klõpsu koordinaadid (pikslites) lähevad serverisse, server käivitab pööra-ja-sõida ahela. Pea meeles: brauseris on pilt skaleeritud — klõpsu piksel tuleb teisendada kaamera tegelikuks resolutsiooniks (`naturalWidth` / kuvatud laius).

**Ülesanne:**

1. Mõõda lineaarne kiirus ja pööramiskiirus oma robotil — pane kronomeeter, tee tee pöörde suunaks ja ajaks ning otse sõitmiseks ja ajaks
2. Lisa drive_to_point loogika serverisse
3. Lisa klõps sündmus veebilehele
4. Ava veebileht, klõpsa pildil otse roboti ette 50 cm kaugusele — kas jõuab umbes kohale?
5. Klõpsa diagonaalile — kas pöörab õigesse suunda?

**Tüüpilised probleemid:**

- **Robot jookseb üle:** lineaar kiirus on tegelikult väiksem — mõõda uuesti
- **Pöörab liiga palju/vähe:** pöördekiirus vale — mõõda uuesti
- **Piksli koordinaadid valed:** unusta brauseris skaleerimine (`naturalWidth` vs `clientWidth`)

**YouTube/AI otsisõnad:**
- `differential drive robot turn calculation`
- `JavaScript image click coordinate`
- `FastAPI GET parameters`
- `open loop robot motion timing`

---

### 5. Piiri ja tsoonide tuvastamine

**Eeldus:** värviandur töötab V2 maketeerimisplaadil, on nüüd robotile paigaldatud.

**Eesmärk:** robot peab aru saama:
- **millal on õiget värvi blokil** (nt skooripunkt, algpositsioon, turvatsoon)
- **millal on piiril** (punane joon — peata kohe)
- **millal ei sobi miski** — nüüd saadab anduri näidud operaatorile, et teada mida tegelikult näeb

Viimane punkt on oluline: kui andur näeb midagi ootamatut (läikiv pind, varjus, kahe plönnsi vaheline servaala), ei tohi loogika kohkuda ega eksitada. Operaator saab reaalajas näidud → saab kalibreerimist parandada. Andur peaks jääma 5cm raadiussesse roboti pöörlemise keskmest.

---

**Põhimõte — kihiline:**

1. **MCU kiht:** andur loeb alati. Kui värv vastab **punasele piirile** → mootorid kohe peatatud, sõltumata serveri käskudest. See on turvamehhanism, mis ei tohi viibida.
2. **Telemeetria kiht:** andur saadab näidud (R, G, B, C + klassifikatsioon) serverile/veebiliidesele iga ~100 ms. Operaator näeb päriselt mida robot „näeb" ja saab klassifitseerida.
3. **Klassifitseerimise kiht:** tarkvara otsustab näitude järgi millises tsoonis robot on. Reeglid on lihtsad (RGB vahemikud) ja kirjutatud serveris, et saaks neid muuta ilma MCU-d uuesti flashima.

---

**Kalibreeri tsoonid (üks kord areenil):**

Enne mängu pane robot iga värvi plönn peale, loe 30 näitu, arvuta mediaan ja standardhälve.

Tee tabel: iga tsoon → keskmine (R, G, B, C) + hajuvus. Tuvastamine on siis „millisele tsoonile mu näit lähim on" — klassika lähima naabri meetod.

---

**MCU kiht (piirihoid + pidev telemeetria):**

ESP32 peab tegema kaht asja:
1. **Iga loop-iteratsioon:** kontrolli piiri (punane joon → stop). Kõige kiirem otsus, mitte mingit klassifitseerimist.
2. **Iga ~100 ms:** saada anduri näidud (R, G, B, C) veebiliidesele — 100ms intervall on operaatori jaoks piisav.

---

**Veebiliides:**

- **Praegune tsoon** (tekst/värv): „punane plönn", „kollane plönn", „punane piir", „**tundmatu**"
- **Toorväärtused** (debug): R, G, B, C reaalajas

Viimane info on kuld kui midagi ei tööta — operaator näeb et „robot oli vist kahe plönnsi serval, seepärast ei klassifitseerinud".

---

**Ülesanne:**

1. Kirjuta `zone_calibration.py` — kalibreeri kõik areeni värvid (3 pinda)
2. Lisa MCU loopi **ainult piiri lävi + pidev telemeetria** (ei klassifitseerida kogu masinas)
3. Lisa serverisse `classify_reading()` ja saada tulemus WebSocketi kaudu veebiliidesele
4. Lisa veebiliidesele „praegune tsoon" kuvar + toorväärtused
5. Testi stendil: pane robot iga tsooni peale, kontrolli et klassifitseerimine vastab. Pane kahe plönnsi vahele — kas kuvab „tundmatu"?
6. Testi elus: saada klõpsa-ja-sõida käsk mis viiks roboti piirist üle → kas peatub enne piiri?

**YouTube/AI otsisõnad:**
- `Arduino non-blocking loop sensor check`
- `Color calibration multiple surfaces`
- `safety watchdog microcontroller`

---

### 6. Aku logimine

**Eesmärk:** tea kui kaua robot vastu peab enne akut vahetada. Vajalik ka V3 analüüsis 3 (aku tööaeg).

**Kaks võimalust sõltuvalt sinu raudvarast:**

**A: Telefon on aku** — Termuxis saad `termux-battery-status` käsuga küsida telefoni aku protsendi JSON-ina. Kirjuta skript mis küsib seda iga 30 sekundi tagant ja logib CSV-sse (ajatempel + protsent). Vajalik `pkg install termux-api` + Termux:API äpp.

**B: LiPo aku + ESP32 ADC** — mõõda akupinge ESP32 ADC-ga pingejaguri kaudu. LiPo 2S täispinge on 8.4V, aga ESP32 ADC loeb max 3.3V — seega vajad pingejagurit (nt 3:1 suhe). ESP32 loeb ADC väärtuse, teisendab pingeks (ADC näit × referentspinge / resolutsioon × jaguri suhe) ja saadab iga 5 sekundi tagant JSON-ina seerialporti. Server logib CSV-sse.

**YouTube/AI otsisõnad:**
- `ESP32 battery voltage monitoring ADC`
- `voltage divider battery measurement`
- `termux-api battery status`
- `LiPo voltage state of charge`

---

### Klõpsa-ja-sõida täpsus (Analüüs 1)

**Eeldus:** samm 4 töötab.

**Ettevalmistus:**

1. Märgi roboti korpusele üks selge **referentspunkt** (nt rist korpuse keskel või ninaosa tipp). Sellest mõõdad alati roboti positsiooni.
2. Märgi areenile 10 sihtpunkti teadaolevatel koordinaatidel — kasuta areeni 10×10 cm auguvõrgustikku.
3. Aseta robot alati samasse alguspunkti ja algussuunda (märgi põrandale teibiga).

**Soovitatav ekstra: allavaatav sihik (3D-prinditud)**

Asenda silma-järgi-hindamine füüsilise sihikuga — muudab mõõtmise palju täpsemaks ja kiiremaks.

3D-prindi väike vars mis kinnitub roboti külge ja hoiab otsas **allavaatavat risti** (õhuke 3D-prinditud rist, ilma elektroonikata — laserit pole vaja).

**Asukoht:** pöördekeskme alla on tavaliselt rattad ja elektroonika — sinna sihikut panna on raske. Kaks praktilist varianti:

- **Ette-keskele** (soovitatud) — vars ulatub roboti ninast ette, rist kõlgub põranda kohal. Näed visuaalselt kuidas sihik läheneb sihtpunktile sõidu ajal.
- **Taha-keskele** — sama asi roboti tagasuunas. Vähem intuitiivne sõidu ajal, aga sobib kui nina on juba täis (kaamera, ToF).

Ideaalis on sihik roboti pikitelgel, aga praktikas on alati mingi Y-nihe ka. **Mõõda mõlemad nihked** — matemaatika ei ole keerulisem.

**Kuidas sõiduloogikas arvestada:**

Mõõda sihiku asukoht roboti pöördekeskmest: `SIGHT_X_CM` (ette) ja `SIGHT_Y_CM` (paremale). Me tahame et **sihik** jõuaks sihtpunktile, mitte pöördekese. Seega arvutame pöördekeskme sihtkoha:

```python
# Sihtpunkt roboti raamis (homograafiast)
target_x, target_y = pixel_to_ground(px, py)

# Pöördekeskme sihtkoht = sihtpunkt miinus sihiku nihe
adj_x = target_x - SIGHT_X_CM
adj_y = target_y - SIGHT_Y_CM

# Edasi sama loogika: nurk ja kaugus adj_x, adj_y järgi
distance_cm = math.sqrt(adj_x**2 + adj_y**2)
angle_deg = math.degrees(math.atan2(adj_y, adj_x))
```

**Disainispetsid STL jaoks:**
- Vars piisavalt pikk et rist ulatub üle roboti korpuse ääre (ei blokeeri vaatepilti)
- Modulaarne kinnitus — sihik tuleb küljest ära kui segab
- Kinnituspunkt olemasolevas 3D-prinditud korpuses
- Risti jooned õhukesed (1–2 mm), et mitte varjata sihtpunkti mõõtmise ajal
- STL repo all näiteks `cad/sight_cross.stl`

**Kasu:**
- Mõõtmine muutub **vaatluslikuks**: paned roboti paika, rist näitab põrandal täpset punkti, mõõdad selle kauguse sihtpunktist auguvõrgustikus
- Ei pea enam arvama "kas referentspunkt korpuse keskel oli ikka täpselt auguvõrgustiku kohal"
- Sama asi töötab V4 autonoomse režiimi valideerimisel

**Mõõtmine:**

1. Klõpsa veebiliideses sihtpunktile
2. Oota kuni robot peatub
3. Mõõda referentspunkti (sihiku rist) tegelik positsioon auguvõrgustiku järgi (lähim auk + nihke hinnang cm-des)
4. Korda iga sihtpunkti 3 korda

**Andmete analüüs Jupyter Lab'is:**

Salvesta mõõtmised CSV-na (veerud: `target_x`, `target_y`, `actual_x`, `actual_y`). Jupyter notebookis tee järgmist:

1. **Arvuta iga mõõtmise viga** — eukleidiline kaugus sihtpunkti ja tegeliku peatumiskoha vahel (cm)
2. **Arvuta iga sihtpunkti kaugus alguspunktist** — et näha kas viga sõltub kaugusest
3. **Scatter-graafik "siht vs tegelik"** — joonista samale graafikule sinised punktid (kuhu pidid jõudma) ja punased punktid (kuhu tegelikult jõudsid), ühenda iga paar hallide joontega. See näitab visuaalselt kus ja kui palju robot eksib.
4. **Scatter-graafik "viga vs kaugus"** — X-teljel sihtpunkti kaugus algusest, Y-teljel viga. Kas kaugemad sihtpunktid on ebatäpsemad?
5. **Mediaan- ja maksimaalne viga** — kaks arvu mis kokkuvõtlikult ütlevad kui täpne süsteem on

**Hinnang:** kui mediaanviga on alla 10 cm ja max alla 20 cm → kasutatav manuaalse juhtimise jaoks. Kui viga kasvab kaugusega → homograafia on ebatäpne kaugemal (tüüpiline), arvesta sellega või piira maksimaalset sihikaugust.

---

### Piiri tuvastamise reaktsiooniaeg (Analüüs 2)

**Eeldus:** samm 5 töötab.

**Probleem:** piiriala on 10 cm lai. Robot peab jõudma tuvastada + peatuda enne kui sellest läbi sõidab. Mõõdame: kui kiiresti andur reageerib ja kui kaugele robot jõuab selle aja jooksul.

**Mõõtmine 1 — anduri reaktsiooniaeg:**

1. Aseta värviandur statsionaarselt piiriala kohal (andur näeb punast piirivärvi)
2. Kiiresti tõmba piir anduri alt ära (või libista anduri alla teine värv)
3. Kirjuta MCU koodi mõõtmisloogika: vajutad Serial Monitoris Enter → taimer käivitub → kui anduri näit muutub (punane kaob) → taimer peatub → kuvab millisekundites. Loogika: `micros()` enne ja pärast, vahe on reaktsiooniaeg.
4. Korda 30 korda, salvesta CSV-sse

**Arvutus — pidurdusteekond:**

Pidurdusteekond koosneb kolmest osast mis kuhjuvad:

1. **Anduri reaktsiooniaeg** — mõõtsid just (mediaan ja max CSV-st)
2. **Side latentsus** — kui kaua läheb käsk MCU-lt mootoriteni (V2-st juba mõõdetud)
3. **Mootori pidurdusaeg** — sõida täiskiirusel, saada stop-käsk, mõõda kui kaugele robot veel liigub

Kogu reaktsiooniaeg (halvimal juhul) = anduri max + side max + mootori pidurdus

Pidurdusteekond (cm) = roboti kiirus (cm/s) × kogu reaktsiooniaeg (s)

**Tabel:**

| Parameeter | Min | Mediaan | Max |
|:---|:---|:---|:---|
| Anduri reaktsioon (ms) | ... | ... | ... |
| Side latentsus (ms, V2-st) | ... | ... | ... |
| Mootori pidurdus (ms) | ... | ... | ... |
| Kogu reaktsioon (ms) | ... | ... | ... |
| Pidurdusteekond (cm) | ... | ... | ... |

**Hinnang:** kui max pidurdusteekond on alla 10 cm → robot peatub piirialas. Kui üle → kas piirdu kiirust, alusta tuvastust varem, või tee piiriala laiem.

---

### Aku tööaeg tervikliku süsteemiga (Analüüs 3)

**Eeldus:** aku logimine (samm 6) töötab.

**Mõõtmine:**

1. Lae aku 100%-ni
2. Käivita robot, käivita aku logimise skript
3. Sõida 3 minutit aktiivselt (klõpsi veebilehel, pane robot sõitma) — simuleeri matši koormust
4. Seejärel 1 minut passiivselt (robot seisab, aga süsteem töötab) — matši vahe
5. Korda kuni aku on 20% juures

**Jupyter Lab analüüs:**

1. **Joongraafik: aku % vs aeg (minutites)** — X-teljel aeg alates algusest, Y-teljel aku protsent. Lisa horisontaalne joon 20% juures (ohulävi).
2. **Arvuta aeg 20%-ni** — mitu minutit kulus?
3. **Arvuta mitu matši saad** — aeg 20%-ni jagatud 4-ga (3 min matš + 1 min vahe)

**Hinnang:** kui saad alla 3 matši → vaja suuremat akut, kiiremat laadijat või vahetatavaid akusid. Kui üle 5 → korras.

---

### Hindamiskriteeriumid

| Kategooria | Punktid | Mida hinnatakse |
|:---|:---|:---|
| Tööfailid | 4 p | Kood repos, fotod/videod integreeritud robotist |
| Analüüs | 4 p | 3 Jupyter notebooki (täpsus, piiri reaktsioon, aku) |
| Prototüüp | 4 p | Kas klõpsa-ja-sõida töötab? Kas piir peatab roboti? |
| Dokumentatsioon | 4 p | Spetsifikatsiooni uuendus integratsiooniprobleemidega |
| Küsimused-vastused | 4 p | Demo kohtumisel + arutelu |
| **Kokku** | **20 p** | |

---

### YouTube/AI otsisõnade koondnimekiri

Otsi neid YouTube/AI'ist — ära vaata kogu videot, keri sinna kus sinu probleem on.

**Kokkupanek ja toide:**
- `robot chassis layout design`
- `LiPo battery voltage regulator 5V 3.3V`
- `robot power distribution bus`
- `common ground wiring microcontroller`

**Kaamera ja homograafia:**
- `OpenCV findChessboardCorners Python`
- `cv2 cornerSubPix tutorial`
- `chessboard camera calibration OpenCV`
- `cv2 findHomography RANSAC`
- `print chessboard A4 calibration` (malelaud PDF-id)
- `ArUco marker calibration` (alternatiiv)

**Klõpsa-ja-sõida:**
- `differential drive robot turn calculation`
- `JavaScript image click coordinate`
- `FastAPI GET parameters`
- `open loop robot motion timing`

**Piiri tuvastamine:**
- `Arduino non-blocking loop sensor check`
- `robot boundary detection line sensor`
- `TCS34725 color threshold detection`
- `safety watchdog microcontroller`

**Aku jälgimine:**
- `ESP32 battery voltage monitoring ADC`
- `voltage divider battery measurement`
- `termux-api battery status`
- `LiPo voltage state of charge`

**Andmeanalüüs:**
- `matplotlib scatter plot tutorial`
- `pandas groupby aggregate`
- `numpy interp interpolation`

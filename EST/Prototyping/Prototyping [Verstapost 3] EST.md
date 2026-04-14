## Prototüüpimine: Verstapost 3 — Integreeritud tehniline prototüüp

**Maht:** 18 tundi | **Hindamine:** 20 punkti | **Kohtumine: L 18.04**

**NB: 2. tellimus (PCB) peab olema esitatud hiljemalt 08.04!**

V2 lõpus sul oli sõitev testšassii ja veebileht nupuga "edasi". Nüüd paned kõik kokku ühele šassiile ja asendad nupud kaamerapildil klõpsamisega. Kui operaator klõpsab pildil kohale, sõidab robot sinna — see on V3 põhiülesanne.

Prioriteet on järjekorras: kõigepealt pane komponendid ühele šassiile ja kontrolli et kõik ikka töötab. Siis kalibreeri kaamera (ilma selleta ei saa klõps → maapind töötama). Siis ehita raycast loogika. Siis integreeri andurid piiri tuvastamiseks. Kui midagi ei tööta, küsi enne kui kulutad kogu päeva silumisele.

---

### 1. Integreeritud šassii

**Eeldus:** V2 ajam, side ja veebiliides peavad töötama.

**Eesmärk:** kõik komponendid ühel šassiil, toide ühest akust, üks süsteem mis käivitub ühe lülitiga.

**Mida vaja:**
- Kõik V2 komponendid (mootorid, draiver, MCU, andurid, arvutusplatvorm)
- Aku (LiPo või USB powerbank — sõltub sinu valikust)
- Toitelüliti
- Juhtmed, klemmid, kahepoolne teip / kruvid

**Ülesanne:**

1. Paiguta komponendid šassiile nii et kaamera näeb ette (raycast jaoks), andurid on oma kohtades (kaugus ette, värv alla), ja aku on lihtne vahetada
2. Ühenda ühine toitesüsteem — üks lüliti sisse/välja
3. Käivita, ava veebileht, kontrolli et kõik mis V2 lõpus töötas töötab ikka
4. Kui midagi ei tööta pärast kokkupanekut → **ära jätka**, otsi viga üles (tavaliselt: halb maandus, kontakt lahti, toitepinge langeb koormuse all)

**Toitehierarhia kontroll:**

- Aku pinge (nt 7.4V LiPo või 5V powerbank) → regulaator → 5V loogikale ja 3.3V MCU-le
- Mootorid saavad toidet kas otse akult (kui aku on 6–12V vahemikus) või eraldi liinilt
- **Ühine GND kõigil komponentidel** — ilma selleta ei tööta side

**Kontroll multimeetriga:**

```
Enne esimest käivitust:
1. Mõõda aku pinge laadituna (nt LiPo 2S: ~8.4V täis)
2. Mõõda toitejaotuse punkte — kas kõik mis peab olema 5V on 5V?
3. Kontrolli ühendusi: pole lühiühendust VCC → GND?
4. Alles siis lülita sisse
```

**YouTube otsisõnad:**
- `robot chassis layout design`
- `LiPo battery voltage regulator 5V 3.3V`
- `robot power distribution bus`
- `common ground wiring microcontroller`

---

### 2. Kaamera kalibreerimine — A4 malelaud + OpenCV

**Eesmärk:** kalibreeri kaamera ühe A4 prinditud malelaudga ja rakisega. OpenCV tuvastab kõik malelaud nurgad automaatselt sub-piksli täpsusega, rakis fikseerib roboti ja malelaud suhtelise asendi, ja homograafiamaatriks tõlgib iga klõpsu otse põrandakoordinaatideks. **Mitte ühtegi käsitsi tape-mõõtmist kalibreerimise hetkel.**

**Miks see on parem kui tape/laser:**
- **Sub-piksli täpsus** — `cv2.cornerSubPix` täpsustub alla 0,1 piksli
- **63 punkti 4 asemel** (tavaline 7×9 malelaud) — RANSAC filtreerib müra välja
- **Null mõõtmisviga kalibreerimise hetkel** — kogu geomeetria tuleneb rakise ehitusest
- **Korratav** — printi üks kord, kasuta alati samamoodi
- **Visuaalne kontroll** — OpenCV joonistab tuvastatud nurgad peale, näed kohe kas töötab
- **Sama tehnika** mida kasutavad päris visioonisüsteemid (autod, droonid, tööstusrobootika)

**Koordinaadisüsteem:** põrandatasapind on matemaatiliselt lõpmatu ja origo võime valida kus tahes. Panime origo **malelaua nurka `[0,0]`** — ehk malelaud ise defineerib koordinaatsüsteemi. X = kaugus ette (malelaua pikiteljel), Y = positiivne paremale.

**Kus on robot selles süsteemis?** Robot pöörab rataste vahelise punkti (pöördekese) ümber. Selle positsioon malelaua koordinaatides `(robot_X, robot_Y)` tuleneb **sellest, kuidas malelaud paika pandi**:

- **Lihtsaim juhtum:** paigutad malelaua nii, et selle nurk `[0,0]` on **täpselt roboti pöördekesel** (vajaduse korral rakis fikseerib selle). Siis `robot_X = 0, robot_Y = 0` ja malelaua koordinaat = roboti koordinaat otse.
- **Tavaline juhtum:** malelaud asub roboti ees mingi nihke `(X0, Y0)` võrra. Need kaks arvu tulenevad rakise ehitusest, mitte joostes mõõtmistest. Iga klõps → malelaua koordinaat → lahuta `(X0, Y0)` → saad roboti raamis oleva vektori.

Niisiis: **ainukesed mõõdud mida vaja on rakise kaks konstantsi** — sama rakis, samad numbrid igal kalibreerimisel.

---

**Mida vaja:**
- Töötav kaamera voog + võimalus salvestada üks kaader
- A4 prindid 7×9 sisemise nurgaga malelaudst (vt all)
- Rakis mis hoiab roboti ja malelaud kindlas asendis
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
- **Liimi jäigale alusele** (papp, PET-plaat, MDF) — voldi või kõveraks jäänud muster annab vale tuvastuse

**Varuvariant — valmis PDF internetist:**

Kui Python ei ole käepärast, [calib.io pattern generator](https://calib.io/pages/camera-calibration-pattern-generator) teeb sama asja brauseris. Vali „Checkerboard", 8×10 ruutu, 25 mm ruut, lae alla PDF. Kontrollida ikka trükitud suurust joonlauaga.

**Samm 2: Rakis paigutab malelaua ja roboti**

Rakise ainus ülesanne: kindlustada, et **malelaud ja robot on igal kalibreerimisel samas suhtelises asendis**. Rakis ei mõõda midagi — see **kordub**. Ehita seda **üks kord**, siis kogu koordinaatsüsteem tuleneb sellest.

Kaks lähenemist, kumb sulle mugavam:

**Lähenemine A — malelaud tõmmatakse roboti ette, mingi nihke võrra:**
- Rakis hoiab roboti kindlal kohal.
- Sama rakis (või eraldi riba põrandal) hoiab malelauda kindlal kaugusel roboti eest, nt `15 cm` pöördekesest edasi.
- Koodis: `X0_CM = 15.0, Y0_CM = -(COLS-1)*SQUARE_MM/20` (malelaud sümmeetriliselt keskel).

**Lähenemine B — malelaud otse pöördekeskme alla:**
- Paigutad malelaua nii, et nurk `[0,0]` on **täpselt roboti pöördekese all või kõrval** (sama positsioon).
- Koodis: `X0_CM = 0, Y0_CM = 0`.
- Robot on ise osaliselt malelaua peal — see toimib, kui robot ei varja tervet mustrit kaamerast. Kui varjab liiga palju, kasuta A.

Mõlemal juhul: **mõõda rakise geomeetria üks kord disainimisel**, pane see koodi, ära muuda.

**Kui rakist veel pole:** märgi põrandale teibiga kaks risti (rataste kontaktpunktid) ja kolmas joon kaugusel `X0_CM` ette. Malelaud tõmmatakse kolmanda joone vastu. Vähem kordustäpne, aga toimib.

**Samm 3: Salvesta üks kaader malelaudga**

Robot rakises, malelaud servas, kaamera tavapaikas. Salvesta üks jpg/png kaader kaamerast (nt ava kaamera `/capture` endpoint või salvesta selle piksli-täpsusega).

**Samm 4: Tuvasta nurgad ja arvuta homograafia**

```python
import cv2
import numpy as np

# --- Malelaua ja rakise parameetrid (kõik tulenevad rakise ehitusest, üks kord mõõdetud) ---
PATTERN_SIZE = (7, 9)       # sisemiste nurkade arv (veerud, read)
SQUARE_MM    = 25.3         # tegelik prinditud ruudu suurus (mõõda joonlauaga!)

# Malelaua nurga [0,0] asukoht roboti raamis:
# Lähenemine A (malelaud ees):  X0_CM = 15.0, Y0_CM = -8.75 (sümmeetriline keskjoonel)
# Lähenemine B (malelaud pöördekesel): X0_CM = 0.0, Y0_CM = 0.0
X0_CM        = 15.0
Y0_CM        = -(PATTERN_SIZE[0] - 1) * SQUARE_MM / 20.0  # sümmeetriliselt keskel

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
# Malelaua nurkade järjekord: rida-rea kaupa, vasakult paremale
floor_pts = []
for row in range(PATTERN_SIZE[1]):         # rida = X suunas (ette)
    for col in range(PATTERN_SIZE[0]):     # veerg = Y suunas (paremale)
        x_cm = X0_CM + row * (SQUARE_MM / 10.0)
        y_cm = Y0_CM + col * (SQUARE_MM / 10.0)
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

**Kui sul pole printerit või tahad alustada kiiresti — varuvariandid:**

**Varu 1: 4 teipmärki põrandale + mõõdulint.** Märgi põrandale 4 nurka mida kaamera näeb, mõõda tape'iga X ja Y pöördekeskmest. `cv2.getPerspectiveTransform(4 pikslit, 4 põrandapunkti)`. ±2 cm täpsus parimal juhul.

**Varu 2: rakis + laserkaugusmõõtja + trilateration.** Kaks sihikut rakise rataste kohal, laser annab `d_L` ja `d_R` igale sihtpunktile, trilateri arvutab XY:

```python
def trilaterate(d_L, d_R, W):
    y = (d_L**2 - d_R**2) / (2 * W)
    x = (d_L**2 - (y + W/2)**2) ** 0.5
    return x, y
```

Parem kui mõõdulint (±5 mm), aga ikka 10× halvem kui malelaud meetod.

---

**YouTube otsisõnad:**
- `OpenCV findChessboardCorners Python`
- `cv2 cornerSubPix tutorial`
- `chessboard camera calibration OpenCV`
- `cv2 findHomography RANSAC`
- `print chessboard A4 calibration` (malelaud PDF-id)
- `ArUco marker calibration` (alternatiiv kui malelaud ei tööta)

---

### 3. Pixel-to-ground homograafiaga

**Eeldus:** kalibreerimine (samm 2) tehtud, `H` maatriks olemas.

**Eesmärk:** iga klõps pildil → põrandakoordinaat `(x_ette, y_paremale)`.

**Kood:**

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

**Tolerants:** mediaan viga peaks olema alla 5 cm. Kui üle 10 cm → 4 nurga mõõtmised olid ebatäpsed, kalibreeri uuesti.

**Kui servades on palju suurem viga** → kaameral on läätsemoonutus (fisheye). Lahendus: vali 4 kalibreerimispunkti, mis katavad pildi keskosa (20%–80%), mitte servad.

**YouTube otsisõnad:**
- `cv2 perspectiveTransform point example`
- `pixel to world coordinates homography`
- `robot camera ground plane mapping`

---

### 4. Klõpsa-ja-sõida loogika

**Eeldus:** homograafia (samm 3) annab usaldusväärseid põrandakoordinaate.

**Eesmärk:** ühenda kogu ahel — klõps → `pixel_to_ground` → arvuta kaugus + nurk → pööra → sõida → peatu.

**Põhiloogika:**

```python
import time
import math

WHEELBASE_CM = 12.0       # rataste vaheline kaugus (oma mõõt!)
SPEED_CM_PER_S = 20.0     # mõõdetud V2 tõuketestist
TURN_RATE_DEG_PER_S = 90  # mõõda eraldi: pane robot pöörama 90°, ajasta

def drive_to_point(px, py):
    """Klõps pildil (px, py) → robot sõidab sinna."""
    x_fwd, y_right = pixel_to_ground(px, py)

    # Teisenda kaugus + nurk
    distance_cm = math.sqrt(x_fwd**2 + y_right**2)
    angle_deg = math.degrees(math.atan2(y_right, x_fwd))
    # Nurk: positiivne = paremale, negatiivne = vasakule, 0 = otse ees

    # Sanity check — kui klõps on roboti taga või liiga kaugel, loobu
    if x_fwd < 0 or distance_cm > 300:
        print(f"Kehtetu siht: x={x_fwd:.0f}, d={distance_cm:.0f} cm")
        return

    # 1. Pööra
    if abs(angle_deg) > 5:  # alla 5° ära pööra (mürasse läheb)
        turn_time = abs(angle_deg) / TURN_RATE_DEG_PER_S
        if angle_deg < 0:
            send_cmd("left", 150)
        else:
            send_cmd("right", 150)
        time.sleep(turn_time)
        send_cmd("stop")
        time.sleep(0.1)  # inertsi ootamine

    # 2. Sõida
    drive_time = distance_cm / SPEED_CM_PER_S
    send_cmd("forward", 200)
    time.sleep(drive_time)
    send_cmd("stop")
```

**Veebiliidese pool:**

Kui V2 HTML-is oli varem `<button>` nupud, lisa nüüd `<img>` element kaamera voo jaoks ja klõpsutus sündmus:

```html
<img id="cam" src="/stream" style="cursor: crosshair;">
<script>
document.getElementById('cam').addEventListener('click', async (e) => {
  const rect = e.target.getBoundingClientRect();
  const px = Math.round(e.clientX - rect.left);
  const py = Math.round(e.clientY - rect.top);
  // Skaleeri brauseri pildi suurus → tegelik kaamera resolutsioon
  const scaleX = e.target.naturalWidth / rect.width;
  const scaleY = e.target.naturalHeight / rect.height;
  const realX = Math.round(px * scaleX);
  const realY = Math.round(py * scaleY);

  await fetch(`/click?x=${realX}&y=${realY}`);
});
</script>
```

FastAPI serveris:

```python
@app.get("/click")
def on_click(x: int, y: int):
    drive_to_point(x, y)
    return {"status": "done"}
```

**Ülesanne:**

1. Mõõda `SPEED_CM_PER_S` ja `TURN_RATE_DEG_PER_S` oma robotil — pane kronomeeter, saada käsk, ajastada
2. Lisa drive_to_point loogika serverisse
3. Lisa klõps sündmus veebilehele
4. Ava veebileht, klõpsa pildil otse roboti ette 50 cm kaugusele — kas jõuab umbes kohale?
5. Klõpsa diagonaalile — kas pöörab õigesse suunda?

**Tüüpilised probleemid:**

- **Robot jookseb üle:** `SPEED_CM_PER_S` on tegelikult väiksem — mõõda uuesti
- **Pöörab liiga palju/vähe:** `TURN_RATE_DEG_PER_S` vale — mõõda uuesti
- **Piksli koordinaadid valed:** unusta brauseris skaleerimine (`naturalWidth` vs `clientWidth`)

**YouTube otsisõnad:**
- `differential drive robot turn calculation`
- `JavaScript image click coordinate`
- `FastAPI GET parameters`
- `open loop robot motion timing`

---

### 5. Piiri tuvastamine ja reaktsioon

**Eeldus:** värviandur töötab V2 maketeerimisplaadil, on nüüd robotile paigaldatud.

**Eesmärk:** kui värviandur näeb piiriala värvi (nt must joon), robot peatub automaatselt — enne kui sõidab areenilt maha.

**Põhimõte:**

Piirituvastus peab töötama **paralleelselt** klõpsa-ja-sõida loogikaga. See ei tohi olla midagi mis käivitub ainult kui kood jõuab vastava rea peale — see peab olema alati valvel. Lihtsaim viis: kontrolli iga kord kui saadad mootori käsu.

**Kaks lähenemist — vali üks:**

**Variant A: MCU-l autonoomne valvur (soovitatud)**

ESP32 kontrollib värviandurit iga loop'i iteratsiooni ja kui näeb piiri, peatab mootorid kohe ise — sõltumata sellest mis käsku veebiliides saatis. See on kõige töökindlam.

```cpp
// Add to main loop on ESP32:
void loop() {
  server.handleClient();  // or serial.available() — whichever you have

  // Boundary check runs every iteration
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  if (c < BOUNDARY_THRESHOLD) {  // dark = boundary
    stop();
    // Optionally: send notification to operator
    if (!boundaryFlag) {
      Serial.println("{\"event\":\"boundary_detected\"}");
      boundaryFlag = true;
    }
  } else {
    boundaryFlag = false;
  }
}
```

**Variant B: serveripoolne valvur**

Server küsib iga 100 ms ESP32-lt anduri näitu ja kui piir, saadab stop-käsu. Aeglasem (side latentsus) ja ebausaldusväärsem — MCU-l autonoomia on alati kindlam.

**Läve (threshold) valimine:**

Kasuta V2 anduri analüüsi tulemusi. Sul on areenipinna ja piirivärvi näitude jaotused. Vali lävi mis on nende **vahel** ja millel ei kattu kumbki jaotus. Näiteks kui areenipind on clear=800±50 ja piir on clear=200±40 → lävi 500 on ohutu.

**Ülesanne:**

1. Määra BOUNDARY_THRESHOLD V2 värvianduri mõõtmiste järgi (keskkoht kahe jaotuse vahel)
2. Lisa piirikontroll MCU loop'i
3. Testi stendil: pane piiriala värv roboti alla → kas peatub? Pane areenipind alla → kas käivitub uuesti?
4. Testi elus: saada klõpsa-ja-sõida käsk mis viiks roboti piirist üle → kas peatub enne piiri ületamist?

**YouTube otsisõnad:**
- `Arduino non-blocking loop sensor check`
- `robot boundary detection line sensor`
- `TCS34725 color threshold detection`
- `safety watchdog microcontroller`

---

### 6. Aku logimine

**Eesmärk:** tea kui kaua robot vastu peab enne akut vahetada. Vajalik ka V3 analüüsis 3 (aku tööaeg).

**Kaks võimalust:**

**A: Telefon on aku** — kasuta Android API-d `BatteryManager`. Termuxis:

```python
import subprocess
import time

def get_battery():
    result = subprocess.run(
        ["termux-battery-status"],
        capture_output=True, text=True
    )
    # Tagastab JSON: {"percentage": 85, "status": "DISCHARGING", ...}
    import json
    return json.loads(result.stdout)

# Log every 30 seconds
with open("battery.csv", "w") as f:
    f.write("timestamp,percent\n")
    while True:
        data = get_battery()
        f.write(f"{time.time()},{data['percentage']}\n")
        f.flush()
        time.sleep(30)
```

NB: vajalik `pkg install termux-api` + Termux:API äpp Play Store'ist või F-Droid'ist.

**B: LiPo aku + ESP32 ADC** — mõõda akupinge ESP32 ADC-ga pingejaguri kaudu (LiPo 2S = 8.4V täis, ADC tald 3.3V — jagur 3:1 teeb sellest 2.8V).

```cpp
const int BATT_ADC_PIN = 34;
const float DIVIDER_RATIO = 3.0;  // sõltub su takistitest
const float ADC_REF = 3.3;
const int ADC_RESOLUTION = 4095;

float readBatteryVoltage() {
  int raw = analogRead(BATT_ADC_PIN);
  float pin_v = (raw / (float)ADC_RESOLUTION) * ADC_REF;
  return pin_v * DIVIDER_RATIO;
}

// In loop, send every 5 seconds:
void loop() {
  static unsigned long last = 0;
  if (millis() - last > 5000) {
    float v = readBatteryVoltage();
    Serial.print("{\"battery_v\":");
    Serial.print(v);
    Serial.println("}");
    last = millis();
  }
}
```

**YouTube otsisõnad:**
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

Oluline: sihik peab olema **täpselt roboti pikitelgel** (X-teljel). Siis on Y-nihet null ja matemaatika lihtne.

**Kuidas sõiduloogikas arvestada:**

Kui sihik on `SIGHT_X_CM` roboti pöördekeskmest ees (või taga, negatiivne), siis:

1. Robot pöörab nii, et nina (ja sihik) on sihi suunas — sama nagu varem
2. Sõidu distants on **sihtpunkti kaugus MIINUS sihiku nihke**: `drive_cm = distance_cm - SIGHT_X_CM`

Nii jääb sihik täpselt sihtpunktile. `drive_to_point` koodis vajad vaid ühte rida juurde.

**Disainispetsid STL jaoks:**
- Vars piisavalt pikk et rist ulatub üle roboti korpuse ääre (ei blokeeri vaatepilti)
- Modulaarne kinnitus — sihik tuleb küljest ära kui segab
- Kinnituspunkt olemasolevas 3D-prinditud korpuses (M3 kruvi või klambrituul)
- Risti jooned õhukesed (1–2 mm), et mitte varjata sihtpunkti mõõtmise ajal
- STL repo all näiteks `cad/sight_cross.stl`

**Kasu:**
- Mõõtmine muutub **vaatluslikuks**: paned roboti paika, rist näitab põrandal täpset punkti, mõõdad selle kauguse sihtpunktist auguvõrgustikus
- Ei pea enam arvama "kas referentspunkt korpuse keskel oli ikka täpselt auguvõrgustiku kohal"
- Sama asi töötab V4 autonoomse režiimi valideerimisel

**Mõõtmine:**

1. Klõpsa veebiliideses sihtpunktile
2. Oota kuni robot peatub
3. Mõõda referentspunkti (sihiku laser / rist) tegelik positsioon auguvõrgustiku järgi (lähim auk + nihke hinnang cm-des)
4. Korda iga sihtpunkti 3 korda

**Andmete analüüs Jupyter Lab'is:**

```python
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv("accuracy.csv")  # columns: target_x, target_y, actual_x, actual_y

df["error_cm"] = np.sqrt(
    (df["actual_x"] - df["target_x"])**2 +
    (df["actual_y"] - df["target_y"])**2
)
df["distance_cm"] = np.sqrt(df["target_x"]**2 + df["target_y"]**2)

# Scatter: sihtpunktid vs tegelikud
plt.figure(figsize=(8, 8))
plt.scatter(df["target_x"], df["target_y"], c="blue", label="Siht", s=50)
plt.scatter(df["actual_x"], df["actual_y"], c="red", label="Tegelik", s=50)
for _, row in df.iterrows():
    plt.plot([row["target_x"], row["actual_x"]],
             [row["target_y"], row["actual_y"]], "gray", alpha=0.3)
plt.xlabel("X (cm)")
plt.ylabel("Y (cm)")
plt.legend()
plt.axis("equal")
plt.title("Klõpsa-ja-sõida täpsus")
plt.show()

# Viga vs kaugus
plt.scatter(df["distance_cm"], df["error_cm"])
plt.xlabel("Sihi kaugus alguspunktist (cm)")
plt.ylabel("Viga (cm)")
plt.title("Kas viga kasvab kaugusega?")
plt.show()

print(f"Mediaanviga: {df['error_cm'].median():.1f} cm")
print(f"Max viga: {df['error_cm'].max():.1f} cm")
```

**Hinnang:** kui mediaanviga on alla 10 cm ja max alla 20 cm → kasutatav manuaalse juhtimise jaoks. Kui viga kasvab kaugusega → raycast on ebatäpne kaugemal (tüüpiline), arvesta sellega või piira maksimaalset sihikaugust.

---

### Piiri tuvastamise reaktsiooniaeg (Analüüs 2)

**Eeldus:** samm 5 töötab.

**Probleem:** piiriala on 10 cm lai. Robot peab jõudma tuvastada + peatuda enne kui sellest läbi sõidab. Mõõdame: kui kiiresti andur reageerib ja kui kaugele robot jõuab selle aja jooksul.

**Mõõtmine 1 — anduri reaktsiooniaeg:**

1. Aseta värviandur statsionaarselt piiriala kohal (andur näeb piirivärvi)
2. Kiiresti tõmba piir anduri alt ära (või libista anduri alla teine värv)
3. MCU koodis: mõõda aeg mikrosekundites anduri muutuse tuvastamiseni

```cpp
// Measure reaction time
unsigned long t_start = 0;
bool waiting_for_change = false;

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  if (Serial.available()) {
    Serial.readStringUntil('\n');  // press Enter in Serial Monitor to arm
    t_start = micros();
    waiting_for_change = true;
    Serial.println("Armed — change surface now");
  }

  if (waiting_for_change && c > LIGHT_THRESHOLD) {
    unsigned long elapsed_us = micros() - t_start;
    Serial.print(elapsed_us / 1000.0);
    Serial.println(" ms");
    waiting_for_change = false;
  }
}
```

4. Korda 30 korda, salvesta CSV-sse

**Arvutus — pidurdusteekond:**

```python
import pandas as pd

df = pd.read_csv("sensor_reaction.csv")  # column: "reaction_ms"

sensor_median = df["reaction_ms"].median()
sensor_max = df["reaction_ms"].max()

# From V2 latency analysis
comm_latency_median = 15   # fill in from V2
comm_latency_max = 50      # fill in from V2

# Measured separately — pressing "stop" and measuring distance traveled
motor_brake_time_ms = 100  # mõõda: sõida täisgaasil, saada stop, mõõda läbitud teekond

total_worst = sensor_max + comm_latency_max + motor_brake_time_ms
robot_speed_cm_per_s = 20  # from V2

brake_distance_cm = robot_speed_cm_per_s * (total_worst / 1000)

print(f"Anduri reaktsioon (mediaan/max): {sensor_median:.1f} / {sensor_max:.1f} ms")
print(f"Kogu reaktsiooniaeg (max): {total_worst:.1f} ms")
print(f"Pidurdusteekond: {brake_distance_cm:.1f} cm")
```

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

**Graafik:**

```python
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("battery.csv")
df["minutes"] = (df["timestamp"] - df["timestamp"].iloc[0]) / 60

plt.figure(figsize=(10, 5))
plt.plot(df["minutes"], df["percent"])
plt.xlabel("Aeg (min)")
plt.ylabel("Aku (%)")
plt.axhline(20, color="red", linestyle="--", label="20% lävi")
plt.legend()
plt.title("Aku tööaeg simuleeritud matšitingimustes")
plt.grid(True)
plt.show()

# Mitu matši saab?
time_to_20pct = df[df["percent"] <= 20]["minutes"].min()
matches = time_to_20pct / 4  # 3 min matš + 1 min vahe
print(f"Aeg 20%-ni: {time_to_20pct:.1f} min")
print(f"Matše: {matches:.1f}")
```

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

### YouTube otsisõnade koondnimekiri

Otsi neid YouTube'ist — ära vaata kogu videot, keri sinna kus sinu probleem on.

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

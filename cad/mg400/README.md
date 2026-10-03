# Dobot MG400 — 3D mudel Fusion 360 jaoks

`MG400_assembled_mm.stl` — kogu robot ühes mesh-failis, **millimeetrites**, kõik liigendid 0°.
Baasi alumine tald on Z = 0 tasapinnal, pöördtelg J1 on ligikaudu X = 0 / Y = 0 juures.

Gabariidid mudelis: X −95…300 mm, Y −95…95 mm, Z 0…460 mm.
Baasi jalajälg 190 × 190 mm, max ulatus 440 mm, kaal 8 kg, toide 100–240 V AC (150 W).

## Fusion 360-sse toomine

1. `Insert → Insert Mesh` (mitte Upload) → vali `MG400_assembled_mm.stl`, ühikuks **Millimeter**.
2. Töölaua joonestamiseks jäta see meshiks — see on ainult viide. Ära ürita seda BRep-iks
   konverteerida (78 684 kolmnurka, aeglane ja mõttetu).
3. Tekita eraldi komponendina tööala silinder: R = 440 mm ümber J1 telje, et näha,
   kui palju lauda robot tegelikult vajab.

## Failid

- `MG400_assembled_mm.stl` — kokku pandud robot (import see)
- `links/*.STL` — üksikud lülid, iga oma lüli koordinaatsüsteemis (meetrites)
- `mg400.urdf` — liigendite asukohad ja piirid
- `merge.py` — skript, mis URDF-i põhjal lülid kokku paneb; muuda liigendinurki,
  kui vaja mudelit mõnes muus poosis

## Päritolu

Meshid: [Dobot-Arm/MG400_ROS](https://github.com/Dobot-Arm/MG400_ROS) (Dobot'i enda ROS-pakett).
Ametlik parametriline CAD (Creo 4.0 / SolidWorks 2014) on Dobot'i Download Centeris
tootja lehel — see on solid, aga nõuab konto/allalaadimist ja Fusioni jaoks konverteerimist.

## Tööpinna mõõdud roboti ees (arvutatud)

Roboti koordinaatide nullpunkt (J1 telg, J2 kõrgus) on **228 mm** kõrgemal tasapinnast,
kuhu alus kinnitub. 40 mm kõrgune tööpind on seega robotile Z = **−188 mm**.

MG400 tööruum tõmbub allpool kokku, seetõttu on madalal pinnal ulatus rõngas, mitte ketas:

| tööpinna kõrgus | ulatuv rõngas J1 teljest | rõnga laius |
|---|---|---|
| 20 mm | R 245 … 320 | 75 mm |
| **40 mm** | **R 235 … 372** | **137 mm** |
| 80 mm | R 222 … 419 | 197 mm |
| 120 mm | R 196 … 437 | 241 mm |

Tööriista pikkus mõjub täpselt samamoodi (40 mm pind + 80 mm haarats ≡ 120 mm pind):

| tööriist | ulatuv rõngas |
|---|---|
| 0 mm (paljas äärik) | R 235 … 372 |
| 50 mm | R 217 … 426 |
| 80 mm | R 196 … 437 |

**Soovitus: pealispind 480 × 240 mm**, lähiserv 200 mm J1 teljest
(= 105 mm roboti aluse esiservast), keskel roboti keskjoonel.
480 = 4 × 120, 240 = 2 × 120 — mõlemas suunas täisarv torusammu.

Torud (16 mm, samm 120 mm), kaks võimalust:
- **eest-taha**: 5 toru Y = 0, ±120, ±240, iga 240 mm pikk (10 jalga)
- **külgsuunas**: 3 toru X = 200, 320, 440, iga 480 mm pikk (6 jalga; läbipaine ~0,4 mm)

Kõrguse eelarve 40 mm: 16 mm toru + ~12 mm plaat + ~12 mm jalg.

Kaetus 80 mm tööriistaga ~89% — puudu jäävad ainult kaugemad nurgad.
Kui on vaja 100%, siis kas **480 × 180** või lõika kaugemad nurgad 120 mm 45° all maha.

Vaata `bench_plan.png`.

## Põhikontroller: Atom Pico / Atom Matrix

| Funktsioon                  | Atom/Pico GPIO | Ühendub millega                      | Märkus                                                                |
|-----------------------------|---------------:|--------------------------------------|-----------------------------------------------------------------------|
| Vasaku mootori PWM          |            G19 | DRI0044 / TB6612 `PWM1`              | Vasaku mootori kiiruse juhtimine                                      |
| Vasaku mootori DIR          |            G22 | DRI0044 / TB6612 `DIR1`              | Vasaku mootori suuna juhtimine                                        |
| Parema mootori PWM          |            G23 | DRI0044 / TB6612 `PWM2`              | Parema mootori kiiruse juhtimine                                      |
| Parema mootori DIR          |            G33 | DRI0044 / TB6612 `DIR2`              | Parema mootori suuna juhtimine                                        |
| VL53L1X SDA                 |            G25 | VL53L1X `SDA`                        | I2C andmesiin                                                         |
| VL53L1X SCL                 |            G21 | VL53L1X `SCL`                        | I2C kellasignaal                                                      |
| Kaamera UART RX Pico poolel |            G32 | Kaamera M12 `G1 / TX / valge juhe`   | Pico võtab kaameralt vastu `BLOB` / `NONE` andmeid                    |
| Kaamera UART TX Pico poolel |            G26 | Kaamera M12 `G2 / RX / kollane juhe` | Pico saadab kaamerale käske, näiteks `mode tune` / `mode run`         |
| GND                         |            GND | GND                                  | Peab olema ühine kaamera, TOF-anduri, mootoridraiveri ja akumooduliga |

---

## Kaamera: AtomS3R-M12 HY2.0-4P / Grove pistik

| Kaamera pistiku juhtme värv | Kaamera signaal | Ühendub millega | Märkus                               |
|-----------------------------|-----------------|-----------------|--------------------------------------|
| Must                        | GND             | Ühine GND       | Ühine maa                            |
| Punane                      | 5V              | 5V toide        | Kaamera toide                        |
| Kollane                     | G2 / RX         | Pico G26 / TX   | Kaamera võtab Pico käsklusi vastu    |
| Valge                       | G1 / TX         | Pico G32 / RX   | Kaamera saadab blob’i andmed Picosse |

---

## Mootoridraiver: DRI0044 / TB6612

| DRI0044 / TB6612 pin | Ühendub millega             | Märkus                                                               |
|----------------------|-----------------------------|----------------------------------------------------------------------|
| `DIR1`               | Pico G22                    | Vasaku mootori suund                                                 |
| `PWM1`               | Pico G19                    | Vasaku mootori kiirus                                                |
| `PWM2`               | Pico G23                    | Parema mootori kiirus                                                |
| `DIR2`               | Pico G33                    | Parema mootori suund                                                 |
| `VCC`                | Akumooduli +5V              | Mootoridraiveri loogikatoide                                         |
| `VM`                 | Akumooduli +5V              | Mootorite toide                                                      |
| `GND`                | Ühine GND                   | Peab olema ühendatud Pico, kaamera, TOF-anduri ja aku maaga          |
| `M1+`                | Vasaku mootori esimene juhe | Kui vasak mootor liigub vales suunas, vaheta `M1+` ja `M1-` omavahel |
| `M1-`                | Vasaku mootori teine juhe   | Vasaku mootori väljund                                               |
| `M2+`                | Parema mootori esimene juhe | Kui parem mootor liigub vales suunas, vaheta `M2+` ja `M2-` omavahel |
| `M2-`                | Parema mootori teine juhe   | Parema mootori väljund                                               |

---

## VL53L1X TOF-kaugusandur

| VL53L1X pin   | Ühendub millega  | Märkus                                                                       |
|---------------|------------------|------------------------------------------------------------------------------|
| `VCC` / `VIN` | Akumooduli 3.3V  | Kasutada 3.3V toidet/loogikat, kui breakout-plaat ei ole kindlalt 5V ühilduv |
| `GND`         | Ühine GND        | Ühine maa                                                                    |
| `SDA`         | Pico G25         | I2C andmesiin                                                                |
| `SCL`         | Pico G21         | I2C kellasignaal                                                             |
| `INT`         | Ei ole ühendatud | Praeguses koodis ei kasutata                                                 |

---

## Toitejaotus

| Moodul                  | Toiteühendus                     | Märkus                                                |
|-------------------------|----------------------------------|-------------------------------------------------------|
| Atom Pico / Atom Matrix | Akumooduli +5V                   | Põhikontroller                                        |
| AtomS3R-M12 kaamera     | 5V läbi HY2.0-4P / Grove pistiku |                                                       |
| DRI0044 / TB6612 `VCC`  | Akumooduli +5V                   | Loogikatoide                                          |
| DRI0044 / TB6612 `VM`   | Akumooduli +5V                   | Mootorite toide                                       |
| VL53L1X                 | Akumooduli 3.3V                  | Anduri toide                                          |
| Kõik GND-d              | Ühine GND                        | Vajalik UART-i, I2C ja mootorijuhtimise töökindluseks |

---

## Märkused

- Kui robot liigub edasi käsu peale tagurpidi, vaheta vastava mootori juhtmed omavahel või muuda koodis `MOTOR_L_INVERT` / `MOTOR_R_INVERT` väärtust.
- Kui vasak ja parem mootor on omavahel vahetuses, vaheta füüsilised mootorikanalid või muuda koodis vasaku/parema mootori pinimääranguid.
# Õpiväljundite kaetus — plan v3 vs. ÕIS

Checked 10.09.26. Source of truth for the outcomes: `EST/*/SVNC.00.32x_SO EST v2.md`. Source for the labs: `plan_2026_27_ENG_v3.md`.

Status: **OK** = covered and named in a lab · **PATCHED** = was missing, added to v3 today · **ASENDATUD** = covered, but on different hardware than the ÕIS text names; the substitution is written out in section 3 so it is defensible to a reviewer.

---

## SVNC.00.325 Data Acquisition

| # | Õpiväljund (lühendatult) | Kaetud | Kus |
| :-- | :--- | :--- | :--- |
| 1 | eristab andmehõivesüsteemi komponente, kirjeldab signaalitee analoog- ja digitaalosa | OK | L1 (andur → ADC → UART), L2 (kogu ahel) |
| 2 | selgitab ADC tööpõhimõtet, veaallikaid ja efektiivse resolutsiooni arvutamist | OK | L1: Pa/LSB mõlemale andurile, 15 % skaalast, müralävi paskalites |
| 3 | projekteerib op-amp konditsioneerimisahela (nihe ja skaleerimine), põhjendab simulatsiooni ja mõõtmistega | OK | L2 config 3, Falstad enne maketti |
| 4 | valib mõõdetud võrdluse alusel alternatiivide vahel — pingejagur vs op-amp, analoog- vs digitaalfilter, **polling vs IRQ** — arvestades täpsust, **kulu ja arendusaega** | PATCHED | L2 neli konfiguratsiooni; **L3 uus punkt 5**: sama kaitse pollinguna ja katkestusena kõrvuti, halvim latentsus, koodiridade arv ja tööle saamise aeg |
| 5 | rakendab analoog- (RC, Schmitt) ja digitaalfiltreerimist (**keskmistamine, mediaan, ülekoguse võtmine**), hindab Fourier'ga | PATCHED | **L2 config 4 laiendatud**: libisev keskmine + mediaan + ülekoguse võtmine detsimeerimisega, igaühe spekter eraldi |
| 6 | programmeerib ESP32 katkestuste, riistvaraliste taimerite ja **kahetuumalise tööga** reaalajas | PATCHED | **L3 uus punkt 6**: mõõtmine ja ohutus ühel tuumal, JSON-voog teisel, järjekord vahel; värina mõõtmine mõlemal juhul |
| 7 | disainib trükkplaadi (**Fusion 360 EDA**), Gerber, tellib JLCPCB-st | PATCHED | L3 punkt 9 — tööriist nimetatud, oli enne "KiCad või Fusion" |
| 8 | iseloomustab mõõtesüsteemi statistiliselt: resolutsioon, **mõõtemääramatus**, **absoluutne täpsus**, korratavus | PATCHED | **L2 uus punkt 7**: määramatuse eelarve — resolutsioon, müra, triiv tunni jooksul, absoluutne täpsus etaloni vastu, üks number ja dominantne liige |
| 9 | automatiseerib andmekogumise (Python + roboti API), kogub piisava andmestiku | OK | L4 — aga vaata konflikti 1 allpool |
| 10 | treenib ja valideerib ML mudeli (scikit-learn), tunnused aegreast sh Fourier | OK | L5 punktid 1–8 |
| lisa | Lisaülesanne: suletud ahel — doseerib → mõõdab → mudel hindab → hoiatus | OK | L5 punktid 9–10 (bandiit) ja Prototüüpimine M3 |

## SVNC.00.322 3D Printing and CAD

| # | Õpiväljund (lühendatult) | Kaetud | Kus |
| :-- | :--- | :--- | :--- |
| 1 | modelleerib Blenderis, selgitab mesh-probleeme (avatud servad, valed normaalid, non-manifold) | OK | L1 punkt 5 — pliiatsihoidik Blenderis, slicer kaebab, parandamine |
| 2 | selgitab miks Fusion solid väldib neid ja miks piirangupõhine disain on parem | OK | L1 punkt 1 (esimene Fusion sessioon), L2 punkt 6 (sama detail uuesti, parameetriliselt) |
| 3 | selgitab FDM füüsikat: 45° overhang, **sirge vs. kõver joon printimisajas**, orientatsioon vs tugevus | PATCHED | Overhang ja tõmbekatsed olid; **"sirge vs kõver" oli koormusauditis välja lõigatud ja on nüüd tagasi** L1 punktina 7, aga odavamalt: mõlemad lõigatakse slicer'is, prinditakse üks paar |
| 4 | arvutab printimisaja ristlõigete integreerimisena, optimeerib orientatsiooni | OK | L1 punkt 8 — neli orientatsiooni pluss kaks toru |
| 5 | disainib snap-fit kinnitusi, rakendab polt-mutter-seib kompressiooni | OK | L2 punktid 1–3 ja 5 |
| 6 | rakendab print-pause töövoogu metallsisestustele | OK | L4 punkt 6 |
| 7 | analüüsib olemasolevat disaini, parandab ühe mõõdiku kaupa, **võrdleb käsitsi ja generatiivset disaini** | OK | L4 punkt 7 — kaks lähenemist on täpselt see paar, mida õpiväljund nõuab |
| 8 | koostab ISO joonise **GD&T-ga**, tellib CNC teenuselt | PATCHED | L5 punkt 5 — GD&T nüüd nimetatud: tasapinnalisus, asukoht, pinna profiil, baaspinnad |
| 9 | valideerib tellitud detaili mõõtmete vastavust joonisele | OK | L5 punkt 9 — valideerimisplaan enne, mõõtmine pärast |

Lisandunud, ÕIS-is nõudmata aga õpiväljundit 3 teenindav: kalibratsiooniplaat kohapeal prinditud ja eraldi prinditud sobivustega.

## SVNC.00.321 Smart Solutions

| # | Õpiväljund (lühendatult) | Kaetud | Kus |
| :-- | :--- | :--- | :--- |
| 1 | **seadistab Raspberry Pi juhtimisjaama** (OS, SSH, staatiline IP, võrguliidesed) | ASENDATUD | L1 punkt 1 (ruuter, aadressiplaan, DHCP, tulemüür) + L1 punkt 6 (jaam: staatiline IP, käivitub ise, SSH) + L3 punkt 1 (Linux, SSH, tulemüür dropletil). Vaata asendus 3 |
| 2 | selgitab IPv4 ruutimist ja konfigureerib **RPI** mitme alamvõrguga | ASENDATUD | L1 punkt 1 ja L3 punktid 8–9 — ruutimistabel ruuteril ja jaamas, traceroute kolmes suunas, üks marsruut meelega katki, NAT vaadatuna. Ruuter on selle õpiväljundi jaoks parem katsealune kui RPI oli |
| 3 | programmeerib MG400 TCP/IP API-t Pythonis, ehitab Flask veebiliidese | OK | L1 punktid 1–6 |
| 4 | integreerib ESP32 andureid (USB/UART, WiFi, HTTP, MQTT) | OK | L2 punktid 1–7 |
| 5 | seadistab Digital Ocean dropleti (Linux, SSH, tulemüür) | OK | L3 punkt 1 |
| 6 | selgitab VPN tunneldamist (WireGuard krüpto, võtmepaar, NAT-i läbimine), seadistab tunneli | OK | L3 punktid 2–3 |
| 7 | selgitab reverse proxy't, seadistab nginx (proxy_pass, HTTPS) | OK | L3 punktid 4–7 |
| 8 | rakendab kasutaja lukustusmehhanismi | OK | L4 punkt 8 |
| 9 | seadistab MQTT andmelogi (Mosquitto + InfluxDB), ehitab **ajaloolise andmete dashboard'i** | PATCHED | L4 punkt 7 laiendatud: ajalooline vaade salvestatud seeriate üle, mitte ainult live-staatus |
| 10 | analüüsib odava raudvara piiranguid konkurentsel programmeerimisel (**Python GIL**, blokeerimine, protsessid vs threadid) | ASENDATUD + PATCHED | L5 punktid 1–2 mõlemal protsessoril: jaamas GIL, blokeerimine, protsessid vs threadid; **ESP32-l** kui odaval üksusel — koorma kuni midagi katkeb ja kirjuta üles mis: kadunud mõõtmine, ületäitunud järjekord, otsa saanud mälu või valvekoer. Pluss DA L3 kahetuumaline töö |
| 11 | mõõdab tõrkestsenaariume, disainib ohutu oleku taastumise | OK | L5 punktid 3–5 |
| 12 | ehitab REST API ja demonstreerib **LLM integratsiooni** süsteemiga | OK | L5 punktid 6 ja 11 — agent teeb sildi ainult dokumentatsiooni põhjal |

---

# Otsustuskohad

## 1. Mõõtmiste arvud on ÕIS-i teksti sisse kirjutatud

Koormusaudit lõikas kordusi. Aga need konkreetsed arvud seisavad registreeritud ainekavas, ülesannete kirjeldustes:

| ÕIS ütleb | Plan v3 ütleb |
| :--- | :--- |
| Ülesanne 1: "koguda **30 mõõtmist** kolmes rõhukategoorias" | 10 × 3 vale anduriga ja pumbaga, 30 × 3 õige anduriga |
| Ülesanne 2: "**4 × 30 = 120 mõõtmist**" | 15 konfiguratsiooni kohta = 60 |
| Ülesanne 4: "koguda vähemalt **500 mõõtmist** (5 kiirust × 5 rõhku × 20 kordust)" | 3 × 3 × 20 = 180 meeskonna kohta, neli meeskonda koos üle 700 |

Õpiväljund ise ütleb ainult "piisava andmestiku", nii et väljund on kaetud. Aga ülesande tekst ütleb 500. Kaks ausat teed:

* **Jäta arvud alles.** Ülesanne 4 puhul on see peaaegu tasuta — robot käib ise, tudengi tunde see ei söö. Soovitan seda: taasta 5 × 5 × 20 ja võida audit tagasi mujalt.
* **Või sõnasta ÕIS ümber**: "vähemalt 500 kirjet ühiselt kogutud andmestikus" ja "vähemalt 15 mõõtmist konfiguratsiooni kohta". Seda saab teha ainult enne semestri algust.

Ülesande 1 ja 2 lõiked on tudengi tunde, mitte roboti aega — need tasuvad end ära. Ülesande 4 oma mitte.

## 2. Rõhk ja andurid ÕIS-i tekstis

* ÕIS ülesanne 3: "**Rõhk süsteemis on ~2 bar**". Uus rakk töötab −70 … +110 kPa juures, ehk umbes 1,1 bar ülerõhku. Õpiväljundit see ei riiva, aga tekst on vale.
* ÕIS nimetab läbivalt **MPX5700AP**-d, ka op-amp ülesandes. Uus plaan viib MPX5100DP ja MPXV6115V peale ning jätab MPX5700AP "vale mõõtepiirkonna" näiteks. See on parem, aga tekst räägib muust.

Mõlemad on ainekava teksti parandused, mitte labori omad.

## 3. Raspberry Pi asendus — riistvara nimi muutub, aine sisu mitte

RPI-d ei ole. Tema kolm rolli on lahku löödud ja igaüks läheb sinna, kus ta on tegelikult parem:

| RPI tegi | Nüüd teeb | Miks see on vähemalt sama hea |
| :--- | :--- | :--- |
| kolm võrguliidest, ruutimistabel, alamvõrgud, NAT | **ruuter** | Ruuter *on* see seade, kus IPv4 ruutimine elab. RPI kolm liidest olid ruuteri imitatsioon; nüüd konfigureeritakse päris asja — alamvõrk, DHCP reserveeringud, tulemüür, marsruut tunnelisse |
| Linux, SSH, staatiline IP, tulemüür, alati püsti | **DO droplet** + laua peal olev jaam | Linuxi ja SSH õpiväljund on täidetud dropletil, mida nad ehitavad nullist juba L3 punktis 1. Alati-püsti roll läheb sinna, kuhu ta kuulub |
| odav protsessor, mis teenindab mitut perifeeriat korraga | **ESP32** | Siin võidab asendus kõige rohkem. ESP32 piirangud on teravamad ja käegakatsutavamad kui RPI omad: kaks tuuma, FreeRTOS prioriteedid, järjekorrad, valvekoer, hunniku otsasaamine, WiFi-pinu blokeerimine. "Üks odav protsessor teenindab mitut perifeeriaseadet reaalajas" on ESP32-l päriselt tõsi, RPI-l oli see pigem jutt |

Õpiväljundite sõnastuses seisab ikka "Raspberry Pi". Kaetud on need kõik — ainult teise raua peal, ja õpiväljund 10 on nüüd tugevamalt kaetud kui varem, sest ESP32-l saab piirangu päriselt seina äärde ajada ja number kirja panna.

Kui ainekava teksti kunagi uuendatakse, on õige sõnastus umbes: *"seadistab juhtimisjaama ja kohtvõrgu (ruuter, alamvõrgud, staatiline IP, SSH)"* ja *"analüüsib piiratud ressursiga mikrokontrolleri (ESP32) piiranguid reaalajalisel ja konkurentsel programmeerimisel"*. Enne seda ei pea midagi ootama — sisu on kaetud, ja see on see, mida hinnatakse.

## 4. Jootmine

ÕIS kirjeldab konsultatsiooni 1 harjutusplaadiga: TH ja SMD jootmine, tulemuseks "tudeng oskab joota TH ja SMD komponente". Harjutusplaadid võeti välja, sest neid ei ole.

Jootmine ise ei ole üheski õpiväljundis — nii et miski ei ole katmata. Aga trükkplaat tuleb ikkagi koost panna, kui see novembris kohale jõuab. Kaks võimalust: konsultatsioon liigub sinna, kus plaat päriselt joodetakse (L4 algus), või jääb ÕIS-i tekst nii nagu on ja konsultatsioon peetakse vanade plaatide peal vanast kastist. Vanad plaadid on riiulil ja need on tasuta harjutusmaterjal.

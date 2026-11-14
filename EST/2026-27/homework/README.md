# 2026-27: kodutööd, mis katavad mitut ainet

Siin on meeskonnad, kelle üks repo katab kõiki kolme ainet (3D printimine, Andmehõive, Nutikad Lahendused). Ühe aine kodutööd on selle aine kaustas, näiteks `Data Acquisition/homework/`.

Tudengite repod on siin lingina (git submodule), mitte koopiana. Iga link on lukus selle tagi või commiti peal, mis viimati läbi vaadati.

| Kaust | Repo | Lukus | Commit | Märkus |
| :--- | :--- | :--- | :--- | :--- |
| `AVeske/Robootika/` | [AVeske/Robootika](https://github.com/AVeske/Robootika) | tag `smart-solutions-lab2` | `39ae26e` | Kõik kuus tagi (`3d-print-lab1/2`, `data-acquisition-lab1/2`, `smart-solutions-lab1/2`) on sama commiti peal. Kaitsmine L1 + L2 12.11.26 pärast 19:15. Küsimused: [AVeske kaitsmisküsimused L1-L2.md](AVeske%20kaitsmisk%C3%BCsimused%20L1-L2.md) |
| `AVeske/ESP32-Image-Server-Fork/` | [AVeske/ESP32-Image-Server-Fork](https://github.com/AVeske/ESP32-Image-Server-Fork) | `main`, tagi ei ole | `bebe80d` | Atomi püsivara (captive portal, tähe valik, postil käimine) ja XIAO kaamera |
| `AVeske/mg400-base-Fork/` | [AVeske/mg400-base-Fork](https://github.com/AVeske/mg400-base-Fork) | `main`, tagi ei ole | `ed4defd` | Jaam: `/api/letter`, tähtede järjekord, tähed punktidena |

## Lingi uuendamine järgmise labori tagile

```
cd "EST/2026-27/homework/AVeske/Robootika"
git fetch --tags
git checkout smart-solutions-lab3
cd -
git add "EST/2026-27/homework/AVeske/Robootika"
```

Siis uuenda ülal tabelis tag ja commit, ja commit.

## Repo kloonimine koos kodutöödega

```
git clone --recurse-submodules https://github.com/KKallas/Narva-subjects.git
```

Olemasolevas kloonis: `git submodule update --init`.

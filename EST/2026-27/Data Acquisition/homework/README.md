# Andmehõive 2026-27: kodutööd

Tudengite repod on siin lingina (git submodule), mitte koopiana. Iga link on lukus selle tagi peal, mis viimati läbi vaadati.

| Kaust | Repo | Lukus tagil | Commit | Märkus |
| :--- | :--- | :--- | :--- | :--- |
| `Dennel04/` | [Dennel04/data-acquisition-course](https://github.com/Dennel04/data-acquisition-course) | `data-acquisition-lab1` | `4c18e9e` | Labor 1. **UUENDA:** järgmine on `data-acquisition-lab2` |

## Lingi uuendamine järgmise labori tagile

```
cd "EST/2026-27/Data Acquisition/homework/Dennel04"
git fetch --tags
git checkout data-acquisition-lab2
cd -
git add "EST/2026-27/Data Acquisition/homework/Dennel04"
```

Siis uuenda ülal tabelis tag ja commit, ja commit.

## Repo kloonimine koos kodutöödega

```
git clone --recurse-submodules https://github.com/KKallas/Narva-subjects.git
```

Olemasolevas kloonis: `git submodule update --init`.

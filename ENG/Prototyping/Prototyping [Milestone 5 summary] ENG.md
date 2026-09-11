## Prototyping: Milestone 5 — Production-Ready System

**Workload:** 14 hours | **Assessment:** 20 points | **Teamwork:** teams of 4

### What you do

M5 is the last milestone before the arena event. The core message: **if somebody else can take your repo, read it and build the same rover, M5 is finished**. You refine your rover, add localisation using the arena's standard equipment, make the documentation ready for a production run, and bring the M1–M4 measurements together into one picture.

M5 has three parallel goals:

- Refine the rover into its final form — M4 weaknesses fixed or honestly documented
- Add localisation (ArUco markers on the ceiling + optional colour dots/magnets on the floor)
- Make the documentation production-run ready (a stranger must be able to assemble the rover from the repo)

**Refinement and documentation of limitations** — M5 is not a "fix everything" milestone but an **honest documentation of limitations**. Every shortcoming left over from M4 must reach the end of M5 either (a) fixed and re-tested, or (b) clearly written down as a **documented limitation** — no longer solvable mechanically, left to software, control logic or the next hardware generation. A documented limitation can be handled in the layer above; a hidden limitation bites the user. The M5 table continues alongside the M4 table ("Component | M4 status | M5 decision | Result | Final status") and contains both the fixes and the documented limitations.

**Localisation — the arena's standard equipment** — the arena has three levels of navigation aid, available to all teams:

- **Level 1 — ArUco markers on the ceiling** (square accuracy, the recommended baseline): 9 markers from DICT_4X4_50, each 20 × 20 cm, mounted at the centre of every 1×1 m OSB module on the ceiling at ~2 m height. Chess-style notation A1–C3, IDs 0–8, all with their "top" edge facing the blue side. The rover needs an upward-facing camera.
- **Level 2 — Colour dots on the floor grid** (more accurate, uses the M4 colour sensor): blue at the module centre (9), yellow at the module corners (9 × 4 = 36), green at the centre of B2 (origin). The red play areas are cut with a hole over the dots where needed.
- **Level 3 — Magnets in the floor grid** (very accurate, optional): NdFeB 5 × 2 mm in the same layout as the colour dots, a Hall sensor on the rover. Works under the red areas as well (reads through a non-magnetic cover).

The arena's standard format is not a restriction — a team may also use other localisation solutions (UWB, magnetic compass, optical flow, etc.).

**Production-run-ready documentation** — a third party (a member of another team) must be able to take your repo and the ordered components and assemble the same rover without asking you anything. It contains: README, assembly instructions (step by step, with pictures), 3D print files with validated settings, BOM, software installation guide, maintenance guide, list of known issues.

**Operator guide — 1 page** — an A4 page from which an operator (who has never seen the system before) can run a whole match from start to finish. The rule: no more than one page.

### Analyses (Jupyter Lab)

Three analyses in Jupyter notebooks:

1. **Production-run time budget** — measure the print time of every 3D part, the assembly time, the lead time of the components. Work out how many extra rovers you can produce within the production window (30.05–11.06, ~12 days).
2. **Documentation walkthrough** — give the repo to a third person (a member of another team), let them try one specific task (software installation, finding a component from the BOM, following the assembly instructions). Note every point where they get stuck.
3. **Combined graph of the M1–M4 measurements** — the moment of truth for the whole project. Bring the measurements of every milestone together into a single notebook: M1 specification, M2 tests, M3 integration, M4 refinement. Visualise the story of the rover's development. Add a closing reflection: what held true, what went wrong, what you would change in the M1 specification today.

### Required for the defence

**Only a link to the git repository.** The repo must contain:

- Final working code (at least 2 levels of autonomy from M4 + the M5 refinements)
- An implementation of the upward-facing camera + ArUco decoder (Level 1 of the standard equipment)
- Jupyter notebooks for the analyses together with the measurement data (CSV)
- Production-run-ready documentation (README, assembly, software, BOM, maintenance, known issues)
- A 1-page operator guide
- STLs with validated print settings **+ CAD source files** (Fusion 360 `.f3z`/`.f3d` archives or CadQuery `.py` scripts) — the STL is an export, the source file is the editable design
- An updated specification + the M5 refinement table (continuing from M4)
- Photos and videos of the final rover

### Assessment criteria

| Category | Points |
| :--- | :--- |
| Work files — final code, STLs **+ CAD source files** (Fusion `.f3z`/`.f3d` or CadQuery `.py`), BOM, photos/videos | 4 p |
| Analysis — 3 Jupyter notebooks (production-run time budget, documentation walkthrough, M1–M4 combined graph) | 4 p |
| Prototype — rover refined, localisation (ArUco on the ceiling) works, results documented | 4 p |
| Documentation — production-run ready (assembly, software, maintenance, operator guide, known issues) | 4 p |
| Q&A session — demo + reflection (what of this carries over into the next projects?) | 4 p |
| **Total** | **20 p** |

### Full worksheet

📎 *Add a link to the full worksheet here*

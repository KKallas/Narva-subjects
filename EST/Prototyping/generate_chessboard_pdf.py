#!/usr/bin/env python3
"""
Malelaua kalibreerimismustri genereerimine A4 PDF-ina.

Kasutus:
    python generate_chessboard_pdf.py
    python generate_chessboard_pdf.py --square-mm 30 --cols 7 --rows 10

Väljund: malelaud_a4.pdf (samas kaustas kus skript käivitati)

Pärast printimist:
    1. Veendu et printimisel on "Scale = 100%" / "Actual size"
       (MITTE "Fit to page", "Shrink oversized", "Auto rotate and scale")
    2. Mõõda joonlauaga paberi alumises servas olevat kontrolljoont.
       Kui see on 50 mm (±0,5 mm), ruudud on õigesti 25 mm.
       Kui see on vale, muuda koodis SQUARE_MM tegelikuks mõõdetud ruudu suuruseks
       või proovi teise printeriga.

Sõltuvused:
    pip install matplotlib
"""

import argparse

import matplotlib.patches as patches
import matplotlib.pyplot as plt


def generate_chessboard_pdf(
    cols: int = 8,
    rows: int = 10,
    square_mm: float = 25.0,
    ref_line_mm: float = 50.0,
    output_path: str = "malelaud_a4.pdf",
) -> None:
    """Genereeri malelaua kalibreerimismustri A4 PDF.

    Args:
        cols: Ruute horisontaalselt (annab cols - 1 sisemist nurka)
        rows: Ruute vertikaalselt (annab rows - 1 sisemist nurka)
        square_mm: Ühe ruudu külje pikkus millimeetrites
        ref_line_mm: Kontrolljoone pikkus mm (prinditud paberile)
        output_path: Kuhu PDF salvestatakse
    """
    # A4 mõõdud tollides (matplotlib tahab tolle)
    a4_w_in = 210 / 25.4
    a4_h_in = 297 / 25.4

    fig, ax = plt.subplots(figsize=(a4_w_in, a4_h_in))
    fig.subplots_adjust(left=0, right=1, top=1, bottom=0)

    # Muster tsentreeritud
    pat_w_mm = cols * square_mm
    pat_h_mm = rows * square_mm

    if pat_w_mm > 210 or pat_h_mm > 297:
        raise ValueError(
            f"Muster ({pat_w_mm:.0f}x{pat_h_mm:.0f} mm) ei mahu A4-le (210x297 mm). "
            f"Vähenda cols/rows või square_mm."
        )

    x0_mm = (210 - pat_w_mm) / 2
    y0_mm = (297 - pat_h_mm) / 2

    # Joonista mustad ruudud
    for r in range(rows):
        for c in range(cols):
            if (r + c) % 2 == 0:
                x = (x0_mm + c * square_mm) / 25.4
                y = (y0_mm + r * square_mm) / 25.4
                s = square_mm / 25.4
                ax.add_patch(
                    patches.Rectangle((x, y), s, s, facecolor="black")
                )

    # Kontrolljoon all servas (mõõda joonlauaga pärast printimist!)
    ax.plot(
        [10 / 25.4, (10 + ref_line_mm) / 25.4],
        [5 / 25.4, 5 / 25.4],
        "k-",
        linewidth=2,
    )
    ax.text(
        10 / 25.4,
        8 / 25.4,
        f"Kontrolljoon: {ref_line_mm:.0f} mm — mõõda joonlauaga",
        fontsize=8,
    )
    ax.text(
        10 / 25.4,
        12 / 25.4,
        f"Ruudu suurus: {square_mm:.1f} mm | Muster: {cols}x{rows} "
        f"(sisemisi nurki: {cols - 1}x{rows - 1})",
        fontsize=8,
    )

    ax.set_xlim(0, a4_w_in)
    ax.set_ylim(0, a4_h_in)
    ax.set_aspect("equal")
    ax.axis("off")

    plt.savefig(output_path, format="pdf", bbox_inches=None, pad_inches=0)
    plt.close(fig)


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Genereeri kaamerakalibreerimise malelaua A4 PDF."
    )
    parser.add_argument(
        "--cols",
        type=int,
        default=8,
        help="Ruute horisontaalselt (default: 8, annab 7 sisemist nurka)",
    )
    parser.add_argument(
        "--rows",
        type=int,
        default=10,
        help="Ruute vertikaalselt (default: 10, annab 9 sisemist nurka)",
    )
    parser.add_argument(
        "--square-mm",
        type=float,
        default=25.0,
        help="Ühe ruudu külg mm-des (default: 25.0)",
    )
    parser.add_argument(
        "--ref-line-mm",
        type=float,
        default=50.0,
        help="Kontrolljoone pikkus mm-des (default: 50.0)",
    )
    parser.add_argument(
        "-o",
        "--output",
        default="malelaud_a4.pdf",
        help="Väljundfail (default: malelaud_a4.pdf)",
    )
    args = parser.parse_args()

    print(f"Genereerin malelaua PDF-i:")
    print(f"  Muster: {args.cols} x {args.rows} ruutu")
    print(f"  Sisemised nurgad: {args.cols - 1} x {args.rows - 1}")
    print(f"  Ruudu suurus: {args.square_mm} mm")
    print(f"  Mustri kogusuurus: {args.cols * args.square_mm} x "
          f"{args.rows * args.square_mm} mm")
    print(f"  Kontrolljoon: {args.ref_line_mm} mm")

    generate_chessboard_pdf(
        cols=args.cols,
        rows=args.rows,
        square_mm=args.square_mm,
        ref_line_mm=args.ref_line_mm,
        output_path=args.output,
    )

    print(f"\nSalvestatud: {args.output}")
    print("\nPrintimise meelespea:")
    print('  - "Scale = 100%" / "Actual size" (MITTE "Fit to page")')
    print("  - Pärast printimist mõõda kontrolljoont joonlauaga")
    print("  - Kui kontrolljoon on vale, kohanda --square-mm päris väärtusega")


if __name__ == "__main__":
    main()

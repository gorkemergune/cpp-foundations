"""Checks a built PDF and renders its pages to PNG for a visual check.

    <python with pymupdf> _tools/preview.py L01 [dpi]

Reports: page count, text that falls outside the printable area (clipped code lines),
characters drawn with a fallback/missing glyph, and Turkish characters present.
PNG files go to _tools/out/<lab>-p<N>.png
"""
import sys
from pathlib import Path

import pymupdf

TOOLS = Path(__file__).resolve().parent
ROOT = TOOLS.parent

lab = sys.argv[1]
dpi = int(sys.argv[2]) if len(sys.argv) > 2 else 80
pdf = next(ROOT.glob(f"week*/{lab}-*/{lab}-*.pdf"))
doc = pymupdf.open(pdf)
print(f"{pdf.name}: {doc.page_count} pages")
problems = 0
for pno, page in enumerate(doc, 1):
    W = page.rect.width
    right_limit = W - 15 * 72 / 25.4 + 2  # right margin 15 mm
    for b in page.get_text("dict")["blocks"]:
        for line in b.get("lines", []):
            for span in line["spans"]:
                if span["bbox"][2] > right_limit and span["text"].strip():
                    print(f"  p{pno}: text past right margin: {span['text'][:70]!r}")
                    problems += 1
                if "�" in span["text"]:
                    print(f"  p{pno}: replacement character in {span['text'][:60]!r}")
                    problems += 1
    out = TOOLS / "out" / f"{lab}-p{pno}.png"
    page.get_pixmap(dpi=dpi).save(out)
text = "".join(p.get_text() for p in doc)
print("  Turkish letters found:", "".join(sorted(set(c for c in text if c in "çğıöşüÇĞİÖŞÜ"))))
fonts = sorted({f[3] for p in doc for f in p.get_fonts()})
print("  fonts:", ", ".join(fonts))
print("  problems:", problems)

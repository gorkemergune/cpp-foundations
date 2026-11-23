"""Builds the lab PDFs.

    python _tools/build.py            build every lab that has a template in _tools/labs/
    python _tools/build.py L02        build one lab
    python _tools/build.py verify     compile + test starters and reference solutions

How it works
- _tools/labs/LXX.html is the content of one PDF. Inside it, {{ expr }} is evaluated
  with the helpers below (code from real files, program output, tables, SVG drawings).
- Code shown in the PDF is read from the compiled files (starter, header, solutions),
  so the PDF and the tested code cannot drift apart.
- cases(...) tables are also written to <lab>/tests/pdf_cases.inc, and the tests
  run exactly those rows. A row in the PDF is therefore a row in the test.
- The HTML is printed to PDF with headless Microsoft Edge.
"""
from __future__ import annotations

import html as H
import os
import re
import subprocess
import sys
import textwrap
from pathlib import Path

from pygments import highlight
from pygments.formatters import HtmlFormatter
from pygments.lexers import CppLexer, TextLexer

sys.path.insert(0, str(Path(__file__).resolve().parent))
import draw  # noqa: E402

TOOLS = Path(__file__).resolve().parent
ROOT = TOOLS.parent  # lab-camp/
OUT = TOOLS / "out"
EDGE = Path(r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe")

# --------------------------------------------------------------------------- code


def _read_region(path: Path, region: str | None) -> str:
    text = path.read_text(encoding="utf-8")
    if region is None:
        lines = [l for l in text.splitlines() if "@begin" not in l and "@end" not in l and "@show" not in l]
        return "\n".join(lines).strip("\n")
    m = re.search(rf"//\s*@begin {re.escape(region)}(?: empty)?\s*\n(.*?)\n\s*//\s*@end {re.escape(region)}", text, re.S) \
        or re.search(rf"//\s*@show {re.escape(region)}\s*\n(.*?)\n\s*//\s*@endshow {re.escape(region)}", text, re.S)
    if not m:
        raise SystemExit(f"region '{region}' not found in {path}")
    return textwrap.dedent(m.group(1))


def _hl(src: str, lang: str = "cpp") -> str:
    lexer = CppLexer() if lang == "cpp" else TextLexer()
    return highlight(src, lexer, HtmlFormatter(nowrap=True, classes=True))


class Ctx:
    """Everything a template can call."""

    def __init__(self, lab_id: str, lab_dir: Path):
        self.lab_id = lab_id
        self.lab_dir = lab_dir
        self.sol_dir = ROOT / "solutions" / lab_id
        self.case_sets: list[tuple[str, list[tuple]]] = []

    # ---- paths: "lab:lab01.h", "sol:lab01.cpp", "camp:..." (relative to lab-camp)
    def _path(self, ref: str) -> Path:
        kind, _, rel = ref.partition(":")
        base = {"lab": self.lab_dir, "sol": self.sol_dir, "root": ROOT}[kind]
        return base / rel

    def code(self, ref: str, region: str | None = None, title: str | None = None, lang="cpp") -> str:
        path = self._path(ref)
        src = _read_region(path, region)
        self._check_width(src, ref)
        cap = f'<div class="code-title">{H.escape(title)}</div>' if title else ""
        cls = "code long" if len(src.splitlines()) > 26 else "code"
        return f'<div class="{cls}">{cap}<pre>{_hl(src, lang)}</pre></div>'

    def snippet(self, src: str, title: str | None = None, lang="cpp") -> str:
        """Short code written in the template itself (not compiled). Use for 1-3 line fragments."""
        src = textwrap.dedent(src).strip("\n")
        self._check_width(src, "snippet")
        cap = f'<div class="code-title">{H.escape(title)}</div>' if title else ""
        return f'<div class="code">{cap}<pre>{_hl(src, lang)}</pre></div>'

    @staticmethod
    def _check_width(src: str, where: str):
        for i, line in enumerate(src.splitlines(), 1):
            if len(line) > 104:
                raise SystemExit(f"code line too long for the page ({len(line)} chars) in {where}:{i}: {line}")

    def run(self, ref: str, stdin: str = "") -> str:
        """Compile a standalone program and show its real output.
        A file containing the comment "expected warning" may produce warnings; they are shown."""
        path = self._path(ref)
        OUT.mkdir(exist_ok=True)
        exe = OUT / f"{self.lab_id}-{path.stem}.exe"
        r = subprocess.run(["g++", "-std=c++17", "-Wall", "-Wextra", str(path), "-o", str(exe)],
                           capture_output=True, text=True)
        if r.returncode != 0:
            raise SystemExit(f"compile failed: {path}\n{r.stderr}")
        warn = ""
        if r.stderr.strip():
            if "expected warning" not in path.read_text(encoding="utf-8"):
                raise SystemExit(f"warnings in {path}:\n{r.stderr}")
            msgs = [re.sub(r"^.*?:(\d+):(\d+): ", r"line \1: ", l) for l in r.stderr.splitlines() if "warning:" in l]
            warn = ('<div class="code bad"><div class="code-title">Compiler output (g++ -Wall)</div><pre>'
                    + H.escape("\n".join(msgs)) + "</pre></div>")
        out = subprocess.run([str(exe)], input=stdin, capture_output=True, text=True, timeout=10).stdout
        return warn + f'<div class="code output"><div class="code-title">Output</div><pre>{H.escape(out.rstrip())}</pre></div>'

    # ---- test tables shared with the C++ tests
    def cases(self, name: str, headers: list[str], rows: list[tuple], widths: list[str] | None = None) -> str:
        """Last column of each row is a description shown only in the PDF."""
        self.case_sets.append((name, [r[:-1] for r in rows]))
        cols = "".join(f'<col style="width:{w}">' for w in widths) if widths else ""
        head = "".join(f"<th>{h}</th>" for h in ["#"] + headers + ["What it checks"])
        body = ""
        for i, r in enumerate(rows, 1):
            cells = [f"<td>{i}</td>"] + [f"<td><code>{H.escape(show(v))}</code></td>" for v in r[:-1]]
            cells.append(f"<td>{r[-1]}</td>")
            body += "<tr>" + "".join(cells) + "</tr>"
        if widths:
            cols = '<col style="width:5%">' + cols
        return f'<table class="cases">{cols}<thead><tr>{head}</tr></thead><tbody>{body}</tbody></table>'

    def write_cases(self):
        if not self.case_sets:
            return
        lines = ["// Generated by _tools/build.py from the test tables in the PDF. Do not edit.",
                 "// Every row here is a row of a table in the lab PDF.", "#pragma once", ""]
        for name, rows in self.case_sets:
            lines.append(f"inline const std::vector<{name}_Case> {name} = {{")
            for r in rows:
                lines.append("    {" + ", ".join(cpp(v) for v in r) + "},")
            lines.append("};")
            lines.append("")
        (self.lab_dir / "tests" / "pdf_cases.inc").write_text("\n".join(lines), encoding="utf-8")

    # ---- drawings
    def vec(self, *a, **k) -> str:
        return vec_svg(*a, **k)

    def header(self, week, day, title, time, topic, related="", slides="", archive="", course_line=None, timed=False, one="M"):
        """Course line, title and the meta table at the top of page 1."""
        files = sorted(p.name for p in self.lab_dir.iterdir() if p.suffix in (".h", ".cpp"))
        mine = {f.name for f in self.sol_dir.glob("*") if not f.name.startswith("alternatives")} if self.sol_dir.exists() else set()
        yours = [f for f in files if f in mine or (not mine and f.endswith(".cpp") and not f.startswith("warmup"))]
        given = [f for f in files if f not in yours and not f.startswith("warmup")]
        warm = [f for f in files if f.startswith("warmup")]
        fl = " · ".join([f"<code>{f}</code> (given)" for f in given] + [f"<code>{f}</code> (you write)" for f in yours]
                        + [f"<code>{f}</code>" for f in warm] + ["<code>tests/</code>"])
        kind = {"L": "Lab", "C": "Challenge Set", "P": "Mini Project"}[self.lab_id[0]]
        cl = course_line or f"CSE 211 · Data Structures · Lab Camp — Week {week}" + (f" · Day {day}" if day else "") + (" · Timed lab" if timed else "")
        rows = [("Time limit" if timed else "Estimated time", time), ("Topic", topic), ("Files", fl),
                ("Run the tests", f"<code>.\\run.ps1 {self.lab_id}</code> · one question: <code>.\\run.ps1 {self.lab_id} {self.lab_id}-{one}</code>")]
        if slides:
            rows.append(("Course slides", slides))
        if archive:
            rows.append(("Course archive", archive))
        if related:
            rows.append(("Related problems", related))
        body = "".join(f'<tr><td class="k">{k}</td><td>{v}</td></tr>' for k, v in rows)
        return (f'<div class="course">{cl}</div><h1>{kind} {self.lab_id[1:]} — {title}</h1>'
                f'<table class="meta">{body}</table>')

    def banner(self, note="önce İngilizce soruyu kendin çözmeyi dene"):
        return f'<div class="page-break"></div><div class="lang-banner">Türkçe anlatım ve görsel inceleme <small>· {note}</small></div>'

    def lc(self, num, slug, title):
        return f'<a href="https://leetcode.com/problems/{slug}/">LeetCode {num} · {title}</a>'

    def gfg(self, slug, title):
        return f'<a href="https://www.geeksforgeeks.org/problems/{slug}">GeeksforGeeks · {title}</a>'

    def steps(self, rows: list[tuple[str, str, str]]) -> str:
        """rows: (label, svg, note)"""
        out = '<table class="steps">'
        for label, svg, note in rows:
            out += f'<tr><td class="st-label">{label}</td><td class="st-svg">{svg}</td><td class="st-note">{note}</td></tr>'
        return out + "</table>"


def show(v) -> str:
    if isinstance(v, bool):
        return "true" if v else "false"
    if isinstance(v, (list, tuple)):
        return "{" + ", ".join(show(x) for x in v) + "}"
    if isinstance(v, str):
        return '"' + v.replace(chr(10), "\\n").replace(chr(9), "\\t") + '"'
    return str(v)


def cpp(v) -> str:
    if isinstance(v, bool):
        return "true" if v else "false"
    if isinstance(v, (list, tuple)):
        return "{" + ", ".join(cpp(x) for x in v) + "}"
    if isinstance(v, str):
        return '"' + v.replace("\\", "\\\\").replace('"', '\\"').replace(chr(10), "\\n").replace(chr(9), "\\t") + '"'
    return str(v)


# --------------------------------------------------------------------------- SVG

PAL = {
    "cell": "#ffffff", "line": "#33415c", "idx": "#6b7280", "unused": "#eef1f5",
    "blue": "#dbeafe", "green": "#dcfce7", "yellow": "#fef3c7", "red": "#fee2e2",
    "purple": "#ede9fe", "gray": "#e5e7eb", "accent": "#1d4ed8", "warn": "#b91c1c",
}


def vec_svg(values, cap=None, name=None, hl=None, ptr=None, arrows=None, groups=None,
            cw=36, ch=28, show_size=True, faded=None) -> str:
    """A vector drawn as cells.
    values: list of shown values (strings or ints); cap: capacity (extra dashed slots)
    hl: {index: color-name}; ptr: {label: index} drawn above; arrows: [(from, to)] curved above
    groups: [(lo, hi, label, color-name)] brackets below; faded: set of indices drawn gray text
    """
    hl, ptr, arrows, groups, faded = hl or {}, ptr or {}, arrows or [], groups or [], faded or set()
    n = len(values)
    show_cap = cap is not None
    cap = max(cap or n, n)
    left = 70 if name else 8
    top = 8 + (22 if ptr else 0) + (26 if arrows else 0)
    width = left + cap * cw + (120 if show_size else 10)
    height = top + ch + 16 + (26 if groups else 0) + 4
    s = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" '
         f'viewBox="0 0 {width} {height}" font-family="Consolas, monospace" font-size="13">']
    s.append('<defs><marker id="ah" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="7" markerHeight="7" '
             f'orient="auto-start-reverse"><path d="M0,0 L10,5 L0,10 z" fill="{PAL["accent"]}"/></marker></defs>')
    if name:
        s.append(f'<text x="{left - 8}" y="{top + ch / 2 + 5}" text-anchor="end" font-weight="bold" '
                 f'fill="{PAL["line"]}">{H.escape(str(name))}</text>')
    for i in range(cap):
        x = left + i * cw
        if i < n:
            fill = PAL[hl[i]] if i in hl else PAL["cell"]
            s.append(f'<rect x="{x}" y="{top}" width="{cw}" height="{ch}" fill="{fill}" stroke="{PAL["line"]}" stroke-width="1.2"/>')
            col = "#9ca3af" if i in faded else "#111827"
            s.append(f'<text x="{x + cw / 2}" y="{top + ch / 2 + 5}" text-anchor="middle" fill="{col}">{H.escape(str(values[i]))}</text>')
        else:
            s.append(f'<rect x="{x}" y="{top}" width="{cw}" height="{ch}" fill="{PAL["unused"]}" stroke="#9ca3af" '
                     f'stroke-dasharray="3,2"/>')
        s.append(f'<text x="{x + cw / 2}" y="{top + ch + 12}" text-anchor="middle" font-size="10" fill="{PAL["idx"]}">{i}</text>')
    if show_size:
        tx = left + cap * cw + 10
        label = f"size={n}" + (f" cap={cap}" if show_cap else "")
        s.append(f'<text x="{tx}" y="{top + ch / 2 + 5}" font-size="11" fill="{PAL["idx"]}">{label}</text>')
    # pointers
    by_idx: dict[int, list[str]] = {}
    for lab, i in ptr.items():
        by_idx.setdefault(i, []).append(lab)
    for i, labs in by_idx.items():
        x = left + i * cw + cw / 2
        y0 = top - (26 if arrows else 0) - 4
        s.append(f'<text x="{x}" y="{y0 - 10}" text-anchor="middle" font-size="11" font-weight="bold" '
                 f'fill="{PAL["accent"]}">{H.escape(",".join(labs))}</text>')
        s.append(f'<line x1="{x}" y1="{y0 - 6}" x2="{x}" y2="{top - 1}" stroke="{PAL["accent"]}" stroke-width="1.3" marker-end="url(#ah)"/>')
    # arrows (moves between cells)
    for a, b in arrows:
        xa, xb = left + a * cw + cw / 2, left + b * cw + cw / 2
        if a == b:
            continue
        lift = 20
        s.append(f'<path d="M{xa},{top - 2} C{xa},{top - lift} {xb},{top - lift} {xb},{top - 3}" fill="none" '
                 f'stroke="{PAL["accent"]}" stroke-width="1.3" marker-end="url(#ah)"/>')
    # groups
    for lo, hi, lab, colr in groups:
        x1, x2 = left + lo * cw + 3, left + (hi + 1) * cw - 3
        y = top + ch + 17
        c = {"red": PAL["warn"], "green": "#15803d", "blue": PAL["accent"], "gray": "#6b7280"}.get(colr, PAL["line"])
        s.append(f'<path d="M{x1},{y} L{x1},{y + 5} L{x2},{y + 5} L{x2},{y}" fill="none" stroke="{c}" stroke-width="1.4"/>')
        s.append(f'<text x="{(x1 + x2) / 2}" y="{y + 18}" text-anchor="middle" font-size="10.5" fill="{c}">{H.escape(lab)}</text>')
    s.append("</svg>")
    return "".join(s)


# --------------------------------------------------------------------------- page

FORCE_STARTER = False
CSS = (TOOLS / "style.css").read_text(encoding="utf-8") if (TOOLS / "style.css").exists() else ""


STARTER_MARK = "(starter generated from the reference solution)"


def make_starter(sol_file: Path) -> str:
    """Student version of a solution file.
    // @begin NAME        ... // @end NAME   -> signature kept, body replaced by TODO();
    // @begin NAME empty  ... // @end NAME   -> signature kept, body emptied (constructors/destructors)
    // @solution-only     ... // @end-solution-only   -> removed
    lines containing @solution-note are removed; '@begin/@end' lines are dropped."""
    out, lines, i = [], sol_file.read_text(encoding="utf-8").splitlines(), 0
    while i < len(lines):
        line = lines[i]
        st = line.strip()
        if "@solution-note" in line or st.startswith("// @show") or st.startswith("// @endshow"):
            i += 1
            continue
        if st.startswith("// @solution-only"):
            while not lines[i].strip().startswith("// @end-solution-only"):
                i += 1
            i += 1
            continue
        if st.startswith("// @begin"):
            empty = st.endswith(" empty")
            i += 1
            sig = []
            while True:                      # signature lines up to the opening brace
                sig.append(lines[i])
                if lines[i].rstrip().endswith("{"):
                    break
                i += 1
            indent = sig[0][: len(sig[0]) - len(sig[0].lstrip())]
            init = [k for k, l in enumerate(sig) if l.strip().startswith(":")]
            if init:                         # constructor initializer list: the student writes it
                sig = sig[: init[0]]
                sig[-1] = sig[-1].rstrip() + " {"
            out += sig
            out.append(indent + ("    // TODO: write this (it must not throw)" if empty else "    TODO();"))
            out.append(indent + "}")
            while not lines[i].strip().startswith("// @end"):
                i += 1
            i += 1
            continue
        out.append(line)
        i += 1
    text = "\n".join(out) + "\n"
    return text


def write_starters(lab_id: str, lab_dir: Path, force=False):
    sol_dir = ROOT / "solutions" / lab_id
    if not sol_dir.exists():
        return
    for f in sorted(sol_dir.iterdir()):
        if f.suffix not in (".cpp", ".h") or f.name.startswith("alternatives"):
            continue
        target = lab_dir / f.name
        if target.exists() and not force:
            continue                         # never overwrite a student's work
        target.write_text(make_starter(f), encoding="utf-8")
        print(f"  starter written: {target.relative_to(ROOT)}")


def find_lab_dir(lab_id: str) -> Path:
    for d in sorted(ROOT.glob(f"week*/{lab_id}-*")):
        if d.is_dir():
            return d
    raise SystemExit(f"no folder for {lab_id}")


EXPR = re.compile(r"\{\{(.*?)\}\}", re.S)


def render(lab_id: str) -> Path:
    tpl_path = TOOLS / "labs" / f"{lab_id}.html"
    lab_dir = find_lab_dir(lab_id)
    write_starters(lab_id, lab_dir, force=FORCE_STARTER)
    ctx = Ctx(lab_id, lab_dir)
    env = {name: getattr(ctx, name) for name in dir(ctx) if not name.startswith("_")}
    env.update(PAL=PAL, show=show)
    for fn in ("ll", "stack", "row", "graph", "tree", "bst_from", "heap_tree", "buckets"):
        env[fn] = getattr(draw, fn)
    tpl = tpl_path.read_text(encoding="utf-8")

    def sub(m):
        expr = textwrap.dedent(m.group(1)).strip()
        try:
            return str(eval(expr, env))
        except SystemExit:
            raise
        except Exception as e:  # make template errors readable
            raise SystemExit(f"{tpl_path.name}: error in {{{{ {expr[:80]} }}}}: {e!r}")

    body = EXPR.sub(sub, tpl)
    ctx.write_cases()
    pyg_css = HtmlFormatter(style="friendly").get_style_defs(".code pre")
    footer = f"CSE 211 Lab Camp · {lab_id}"
    page = f"""<!doctype html><html lang="en"><head><meta charset="utf-8"><title>{lab_id}</title>
<style>{CSS}
{pyg_css}
@page {{ @bottom-left {{ content: "{footer}"; }} @bottom-right {{ content: counter(page) " / " counter(pages); }} }}
</style></head><body>{body}</body></html>"""
    OUT.mkdir(exist_ok=True)
    html_path = OUT / f"{lab_id}.html"
    html_path.write_text(page, encoding="utf-8")
    pdf_path = lab_dir / f"{lab_dir.name}.pdf"
    r = subprocess.run([str(EDGE), "--headless=new", "--disable-gpu", "--no-pdf-header-footer",
                        f"--print-to-pdf={pdf_path}", html_path.resolve().as_uri()],
                       capture_output=True, text=True, timeout=120)
    if not pdf_path.exists():
        raise SystemExit(f"Edge did not write {pdf_path}\n{r.stderr}")
    print(f"  {lab_id}: {pdf_path.relative_to(ROOT)}")
    return pdf_path


# --------------------------------------------------------------------------- verify


def verify(only=None) -> bool:
    ok = True
    labs = sorted(p.stem for p in (TOOLS / "labs").glob("[LCP]*.html"))
    if only:
        labs = [l for l in labs if l in only]
    for lab_id in labs:
        lab_dir = find_lab_dir(lab_id)
        for mode in ("starter", "solution"):
            srcs = []
            for f in sorted(lab_dir.glob("*.cpp")):
                if f.name.startswith(("warmup", "main")):
                    continue
                sol = ROOT / "solutions" / lab_id / f.name
                srcs.append(str(sol if mode == "solution" and sol.exists() else f))
            srcs += [str(p) for p in sorted((lab_dir / "tests").glob("*.cpp"))]
            srcs.append(str(ROOT / "framework" / "main.cpp"))
            OUT.mkdir(exist_ok=True)
            exe = OUT / f"verify-{lab_id}-{mode}.exe"
            sol_inc = [f"-I{ROOT / 'solutions' / lab_id}"] if mode == "solution" else []
            r = subprocess.run(["g++", "-std=c++17", "-Wall", "-Wextra", "-Wno-unused-parameter", "-g", "-O0", *sol_inc, f"-I{lab_dir}",
                                f"-I{ROOT / 'framework'}", *srcs, "-o", str(exe)], capture_output=True, text=True)
            if r.returncode != 0 or r.stderr.strip():
                print(f"  ✗ {lab_id} {mode}: compile problem\n{r.stderr}")
                ok = False
                continue
            run = subprocess.run([str(exe)], capture_output=True, text=True, encoding="utf-8", timeout=60)
            text = re.sub(r"\x1b\[[0-9;]*m", "", run.stdout)
            if mode == "solution":
                good = run.returncode == 0 and "✗" not in text and "·" not in text and "💥" not in text
            else:
                lines = [l for l in text.splitlines() if re.match(r"[LCP][0-9][0-9]-", l)]
                good = lines and all(("not written yet" in l or "· needs " in l) for l in lines)
            print(f"  {'✓' if good else '✗'} {lab_id} {mode}")
            if not good:
                print(text)
                ok = False
        for alt in sorted((ROOT / "solutions" / lab_id).glob("alternatives*.cpp")):
            exe = OUT / f"{lab_id}-{alt.stem}.exe"
            r = subprocess.run(["g++", "-std=c++17", "-Wall", "-Wextra", f"-I{lab_dir}", str(alt), "-o", str(exe)],
                               capture_output=True, text=True)
            good = r.returncode == 0 and not r.stderr.strip()
            if good:
                good = subprocess.run([str(exe)], capture_output=True, timeout=30).returncode == 0
            print(f"  {'✓' if good else '✗'} {lab_id} {alt.name} compiles and its asserts pass")
            if not good:
                print(r.stderr)
            ok &= good
        for m in sorted(lab_dir.glob("main*.cpp")):      # demo programs build with the solution
            libs = [str(ROOT / "solutions" / lab_id / f.name) for f in sorted(lab_dir.glob("*.cpp"))
                    if not f.name.startswith(("warmup", "main"))]
            r = subprocess.run(["g++", "-std=c++17", "-Wall", "-Wextra", f"-I{ROOT / 'solutions' / lab_id}", f"-I{lab_dir}",
                                f"-I{ROOT / 'framework'}", str(m), *libs, "-o", str(OUT / "m.exe")], capture_output=True, text=True)
            good = r.returncode == 0 and not r.stderr.strip()
            print(f"  {'✓' if good else '✗'} {lab_id} {m.name} builds with the solution")
            if not good:
                print(r.stderr[:2000])
            ok &= good
        for w in sorted(lab_dir.glob("warmup*.cpp")):
            r = subprocess.run(["g++", "-std=c++17", "-Wall", "-Wextra", str(w), "-o", str(OUT / "w.exe")],
                               capture_output=True, text=True)
            expected = "expected warning" in w.read_text(encoding="utf-8")
            good = r.returncode == 0 and (expected or not r.stderr.strip())
            note = " (with the expected warning)" if expected else " without warnings"
            print(f"  {'✓' if good else '✗'} {lab_id} {w.name} compiles{note}")
            ok &= good
    return ok


if __name__ == "__main__":
    args = sys.argv[1:]
    if "--force-starter" in args:
        FORCE_STARTER = True
        args = [a for a in args if a != "--force-starter"]
    if args and args[0] == "verify":
        sys.exit(0 if verify(args[1:]) else 1)
    targets = args or sorted(p.stem for p in (TOOLS / "labs").glob("[LCP]*.html"))
    for t in targets:
        render(t)

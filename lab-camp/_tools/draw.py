"""SVG drawings for the lab PDFs: linked lists, stacks, queues, graphs, trees, hash tables.
All functions return an <svg> string. Colors are names from PAL (build.py)."""
from __future__ import annotations

import html as H
import math

PAL = {
    "cell": "#ffffff", "line": "#33415c", "idx": "#6b7280", "unused": "#eef1f5",
    "blue": "#dbeafe", "green": "#dcfce7", "yellow": "#fef3c7", "red": "#fee2e2",
    "purple": "#ede9fe", "gray": "#e5e7eb", "accent": "#1d4ed8", "warn": "#b91c1c",
}
FONT = 'font-family="Consolas, monospace" font-size="13"'


def _defs(uid: str) -> str:
    return (f'<defs><marker id="a{uid}" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="7" markerHeight="7" '
            f'orient="auto-start-reverse"><path d="M0,0 L10,5 L0,10 z" fill="{PAL["line"]}"/></marker>'
            f'<marker id="b{uid}" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="7" markerHeight="7" '
            f'orient="auto-start-reverse"><path d="M0,0 L10,5 L0,10 z" fill="{PAL["accent"]}"/></marker>'
            f'<marker id="r{uid}" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="7" markerHeight="7" '
            f'orient="auto-start-reverse"><path d="M0,0 L10,5 L0,10 z" fill="{PAL["warn"]}"/></marker></defs>')


_uid = [0]


def _new_uid() -> str:
    _uid[0] += 1
    return str(_uid[0])


def esc(x) -> str:
    return H.escape(str(x))


# --------------------------------------------------------------------------- linked list

def ll(values, labels=None, hl=None, null=True, double=False, circular=False, cut=None,
       relink=None, name=None, gap=34, faded=None, tail_label=None):
    """Singly (or doubly) linked list drawn as [value|•] boxes.
    labels: {index: "head"} or {index: ["head", "cur"]} drawn above the node
    hl: {index: color}; cut: set of i whose next-arrow is crossed out (red)
    relink: [(i, j, color)] extra curved arrow from node i to node j drawn below (new link)
    circular: last node points back to the first (arc below)
    double: draw prev arrows as well
    faded: set of indices drawn as deleted (dashed, gray)
    """
    labels, hl, cut, relink, faded = labels or {}, hl or {}, cut or set(), relink or [], faded or set()
    u = _new_uid()
    bw, dw, bh = 40, 18, 28          # value part, pointer part, height
    n = len(values)
    left = (64 if name else 8)
    top = 30 if labels else 10
    step = bw + dw + gap
    width = max(left + n * step + (50 if null and not circular else 10), left + 110)
    below = 34 if (circular or relink or double) else 8
    height = top + bh + below + 8
    s = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" viewBox="0 0 {width} {height}" {FONT}>',
         _defs(u)]
    if name:
        s.append(f'<text x="{left - 8}" y="{top + bh / 2 + 5}" text-anchor="end" font-weight="bold" fill="{PAL["line"]}">{esc(name)}</text>')
    for i, v in enumerate(values):
        x = left + i * step
        fill = PAL[hl[i]] if i in hl else PAL["cell"]
        dash = ' stroke-dasharray="4,3"' if i in faded else ""
        col = "#9ca3af" if i in faded else "#111827"
        s.append(f'<rect x="{x}" y="{top}" width="{bw}" height="{bh}" fill="{fill}" stroke="{PAL["line"]}" stroke-width="1.2"{dash}/>')
        s.append(f'<rect x="{x + bw}" y="{top}" width="{dw}" height="{bh}" fill="{fill}" stroke="{PAL["line"]}" stroke-width="1.2"{dash}/>')
        s.append(f'<text x="{x + bw / 2}" y="{top + bh / 2 + 5}" text-anchor="middle" fill="{col}">{esc(v)}</text>')
        s.append(f'<circle cx="{x + bw + dw / 2}" cy="{top + bh / 2}" r="2.6" fill="{PAL["line"]}"/>')
        # next arrow
        sx, sy = x + bw + dw / 2, top + bh / 2
        if i < n - 1:
            ex = x + step
            colr, mk = (PAL["warn"], f"r{u}") if i in cut else (PAL["line"], f"a{u}")
            yy = sy - (5 if double else 0)
            s.append(f'<line x1="{sx}" y1="{yy}" x2="{ex - 2}" y2="{yy}" stroke="{colr}" stroke-width="1.4" marker-end="url(#{mk})"/>')
            if i in cut:
                mx = (sx + ex) / 2
                s.append(f'<path d="M{mx - 6},{yy - 6} L{mx + 6},{yy + 6} M{mx + 6},{yy - 6} L{mx - 6},{yy + 6}" stroke="{PAL["warn"]}" stroke-width="2"/>')
            if double:
                s.append(f'<line x1="{ex + 6}" y1="{sy + 6}" x2="{x + bw + dw + 2}" y2="{sy + 6}" stroke="{PAL["idx"]}" stroke-width="1.2" marker-end="url(#a{u})"/>')
        elif null and not circular:
            s.append(f'<line x1="{sx}" y1="{sy}" x2="{sx + 22}" y2="{sy}" stroke="{PAL["line"]}" stroke-width="1.4" marker-end="url(#a{u})"/>')
            s.append(f'<text x="{sx + 26}" y="{sy + 4}" font-size="11" fill="{PAL["idx"]}">null</text>')
    if n == 0 and null:
        s.append(f'<text x="{left}" y="{top + bh / 2 + 4}" font-size="12" fill="{PAL["idx"]}">null (empty)</text>')
    if circular and n > 0:
        x0 = left + 6
        xl = left + (n - 1) * step + bw + dw / 2
        yb = top + bh
        s.append(f'<path d="M{xl},{top + bh / 2} C{xl + 26},{top + bh / 2} {xl + 26},{yb + 24} {xl - 20},{yb + 24} '
                 f'L{x0 + 20},{yb + 24} C{x0 - 6},{yb + 24} {x0},{yb + 14} {x0 + 4},{yb + 2}" fill="none" stroke="{PAL["line"]}" stroke-width="1.4" marker-end="url(#a{u})"/>')
    for (i, j, colr) in relink:
        xa = left + i * step + bw + dw / 2
        xb = left + j * step + bw / 2
        yb = top + bh
        c = PAL.get(colr, PAL["accent"]) if colr in ("warn", "accent") else PAL["accent"]
        mk = f"r{u}" if colr == "warn" else f"b{u}"
        s.append(f'<path d="M{xa},{yb} C{xa},{yb + 28} {xb},{yb + 28} {xb},{yb + 3}" fill="none" stroke="{c}" stroke-width="1.5" stroke-dasharray="5,3" marker-end="url(#{mk})"/>')
    for i, lab in labels.items():
        labs = lab if isinstance(lab, list) else [lab]
        x = left + i * step + bw / 2 if i >= 0 else left + n * step + 10
        s.append(f'<text x="{x}" y="{top - 14}" text-anchor="middle" font-size="11" font-weight="bold" fill="{PAL["accent"]}">{esc(",".join(labs))}</text>')
        s.append(f'<line x1="{x}" y1="{top - 10}" x2="{x}" y2="{top - 1}" stroke="{PAL["accent"]}" stroke-width="1.3" marker-end="url(#b{u})"/>')
    s.append("</svg>")
    return "".join(s)


# --------------------------------------------------------------------------- stack

def stack(items_bottom_to_top, name=None, hl=None, top_label="top", width=64, empty_text="empty"):
    """Vertical stack, top drawn highest."""
    hl = hl or {}
    u = _new_uid()
    n = len(items_bottom_to_top)
    bh = 24
    h = max(n, 1) * bh + 40
    w = width + 90
    s = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{w}" height="{h}" viewBox="0 0 {w} {h}" {FONT}>', _defs(u)]
    x0 = 10
    ybase = h - 18
    s.append(f'<path d="M{x0 - 4},{ybase - n * bh - 6} L{x0 - 4},{ybase + 2} L{x0 + width + 4},{ybase + 2} L{x0 + width + 4},{ybase - n * bh - 6}" fill="none" stroke="{PAL["line"]}" stroke-width="1.6"/>')
    for i, v in enumerate(items_bottom_to_top):
        y = ybase - (i + 1) * bh
        fill = PAL[hl[i]] if i in hl else PAL["cell"]
        s.append(f'<rect x="{x0}" y="{y}" width="{width}" height="{bh - 2}" fill="{fill}" stroke="{PAL["line"]}"/>')
        s.append(f'<text x="{x0 + width / 2}" y="{y + bh / 2 + 3}" text-anchor="middle">{esc(v)}</text>')
    if n:
        yt = ybase - n * bh + bh / 2 - 1
        s.append(f'<line x1="{x0 + width + 46}" y1="{yt}" x2="{x0 + width + 8}" y2="{yt}" stroke="{PAL["accent"]}" stroke-width="1.3" marker-end="url(#b{u})"/>')
        s.append(f'<text x="{x0 + width + 50}" y="{yt + 4}" font-size="11" font-weight="bold" fill="{PAL["accent"]}">{esc(top_label)}</text>')
    else:
        s.append(f'<text x="{x0 + width / 2}" y="{ybase - 6}" text-anchor="middle" font-size="11" fill="{PAL["idx"]}">{esc(empty_text)}</text>')
    if name:
        s.append(f'<text x="{x0 + width / 2}" y="{h - 3}" text-anchor="middle" font-size="11" font-weight="bold" fill="{PAL["line"]}">{esc(name)}</text>')
    s.append("</svg>")
    return "".join(s)


def row(*svgs) -> str:
    """Several drawings side by side."""
    return '<div style="display:inline-flex;gap:14px;align-items:flex-end;flex-wrap:nowrap">' + "".join(svgs) + "</div>"


# --------------------------------------------------------------------------- graph

def graph(nodes, edges, directed=False, pos=None, hl=None, labels=None, edge_hl=None, size=220, r=15, weights=None):
    """nodes: list of names; edges: list of (a, b); pos: {node: (x, y)} in 0..1 (default circle)
    hl: {node: color}; labels: {node: "small text under the node"}; edge_hl: set of (a,b) drawn in accent"""
    hl, labels, edge_hl, weights = hl or {}, labels or {}, set(edge_hl or []), weights or {}
    u = _new_uid()
    n = len(nodes)
    if pos is None:
        pos = {v: (0.5 + 0.42 * math.cos(2 * math.pi * i / n - math.pi / 2),
                   0.5 + 0.42 * math.sin(2 * math.pi * i / n - math.pi / 2)) for i, v in enumerate(nodes)}
    W, Hh = size + 40, size + 34
    P = {v: (20 + pos[v][0] * size, 14 + pos[v][1] * size) for v in nodes}
    s = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{Hh}" viewBox="0 0 {W} {Hh}" {FONT}>', _defs(u)]
    for e in edges:
        a, b = e[0], e[1]
        (x1, y1), (x2, y2) = P[a], P[b]
        d = math.hypot(x2 - x1, y2 - y1) or 1
        ux, uy = (x2 - x1) / d, (y2 - y1) / d
        sx, sy, ex, ey = x1 + ux * r, y1 + uy * r, x2 - ux * (r + 2), y2 - uy * (r + 2)
        on = (a, b) in edge_hl or (not directed and (b, a) in edge_hl)
        col = PAL["accent"] if on else PAL["line"]
        mk = f' marker-end="url(#{"b" if on else "a"}{u})"' if directed else ""
        wdt = 2.4 if on else 1.3
        s.append(f'<line x1="{sx:.1f}" y1="{sy:.1f}" x2="{ex:.1f}" y2="{ey:.1f}" stroke="{col}" stroke-width="{wdt}"{mk}/>')
        if (a, b) in weights:
            mx, my = (x1 + x2) / 2, (y1 + y2) / 2
            s.append(f'<rect x="{mx - 9}" y="{my - 8}" width="18" height="15" fill="white"/>'
                     f'<text x="{mx}" y="{my + 4}" text-anchor="middle" font-size="11" fill="{PAL["warn"]}">{esc(weights[(a, b)])}</text>')
    for v in nodes:
        x, y = P[v]
        fill = PAL[hl[v]] if v in hl else PAL["cell"]
        s.append(f'<circle cx="{x:.1f}" cy="{y:.1f}" r="{r}" fill="{fill}" stroke="{PAL["line"]}" stroke-width="1.4"/>')
        s.append(f'<text x="{x:.1f}" y="{y + 4.5:.1f}" text-anchor="middle" font-weight="bold">{esc(v)}</text>')
        if v in labels:
            s.append(f'<text x="{x:.1f}" y="{y + r + 12:.1f}" text-anchor="middle" font-size="10" fill="{PAL["accent"]}">{esc(labels[v])}</text>')
    s.append("</svg>")
    return "".join(s)


# --------------------------------------------------------------------------- binary tree

def tree(t, hl=None, notes=None, dx=34, dy=48, r=15, empty_text="(empty)"):
    """t: nested tuples (value, left, right) with None for missing children, or None.
    hl: {value: color}; notes: {value: "text under the node"}"""
    hl, notes = hl or {}, notes or {}
    u = _new_uid()
    if t is None:
        return f'<svg xmlns="http://www.w3.org/2000/svg" width="80" height="30" {FONT}><text x="4" y="20" fill="{PAL["idx"]}">{esc(empty_text)}</text></svg>'
    order = []

    def walk(node, depth):
        if node is None:
            return
        v, l, rr = (node + (None, None))[:3] if isinstance(node, tuple) else (node, None, None)
        walk(l, depth + 1)
        order.append((v, depth, node))
        walk(rr, depth + 1)

    walk(t, 0)
    pos = {}
    for i, (v, d, node) in enumerate(order):
        pos[id(node)] = (20 + i * dx, 20 + d * dy)
    maxd = max(d for _, d, _ in order)
    W = 40 + (len(order) - 1) * dx
    Hh = 40 + maxd * dy + (12 if notes else 0)
    s = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{Hh}" viewBox="0 0 {W} {Hh}" {FONT}>', _defs(u)]

    def edges(node):
        if node is None or not isinstance(node, tuple):
            return
        v, l, rr = (node + (None, None))[:3]
        x, y = pos[id(node)]
        for ch in (l, rr):
            if ch is not None:
                cx, cy = pos[id(ch)]
                d = math.hypot(cx - x, cy - y)
                s.append(f'<line x1="{x + (cx - x) * r / d:.1f}" y1="{y + (cy - y) * r / d:.1f}" x2="{cx - (cx - x) * r / d:.1f}" '
                         f'y2="{cy - (cy - y) * r / d:.1f}" stroke="{PAL["line"]}" stroke-width="1.3"/>')
                edges(ch)

    edges(t)
    for v, d, node in order:
        x, y = pos[id(node)]
        fill = PAL[hl[v]] if v in hl else PAL["cell"]
        s.append(f'<circle cx="{x}" cy="{y}" r="{r}" fill="{fill}" stroke="{PAL["line"]}" stroke-width="1.4"/>')
        s.append(f'<text x="{x}" y="{y + 4.5}" text-anchor="middle" font-size="{12 if len(str(v)) > 2 else 13}">{esc(v)}</text>')
        if v in notes:
            s.append(f'<text x="{x}" y="{y + r + 12}" text-anchor="middle" font-size="10" fill="{PAL["accent"]}">{esc(notes[v])}</text>')
    s.append("</svg>")
    return "".join(s)


def bst_from(keys):
    """Nested-tuple BST built by inserting keys in order (equal keys go right)."""
    def ins(node, k):
        if node is None:
            return (k, None, None)
        v, l, r = node
        return (v, ins(l, k), r) if k < v else (v, l, ins(r, k))
    t = None
    for k in keys:
        t = ins(t, k)
    return t


def heap_tree(arr):
    """Nested tuples for an array-based heap (index 0 = root)."""
    def build(i):
        if i >= len(arr):
            return None
        return (arr[i], build(2 * i + 1), build(2 * i + 2))
    return build(0)


# --------------------------------------------------------------------------- hash table (chaining)

def buckets(chains, hl=None, name=None, bw=34):
    """chains: list (one per bucket) of lists of keys. hl: {(bucket, pos): color}"""
    hl = hl or {}
    u = _new_uid()
    m = len(chains)
    bh = 26
    longest = max((len(c) for c in chains), default=0)
    W = 70 + longest * (bw + 26) + 20
    Hh = m * bh + 14
    s = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{Hh}" viewBox="0 0 {W} {Hh}" {FONT}>', _defs(u)]
    for b, chain in enumerate(chains):
        y = 6 + b * bh
        s.append(f'<text x="18" y="{y + 16}" text-anchor="end" font-size="10" fill="{PAL["idx"]}">{b}</text>')
        s.append(f'<rect x="22" y="{y}" width="26" height="{bh - 4}" fill="{PAL["gray"]}" stroke="{PAL["line"]}"/>')
        x = 48
        if not chain:
            s.append(f'<text x="28" y="{y + 15}" font-size="10" fill="{PAL["idx"]}">∅</text>')
        for p, key in enumerate(chain):
            nx = x + 22
            s.append(f'<line x1="{x - 8}" y1="{y + 11}" x2="{nx - 2}" y2="{y + 11}" stroke="{PAL["line"]}" stroke-width="1.3" marker-end="url(#a{u})"/>')
            fill = PAL[hl[(b, p)]] if (b, p) in hl else PAL["cell"]
            s.append(f'<rect x="{nx}" y="{y}" width="{bw}" height="{bh - 4}" fill="{fill}" stroke="{PAL["line"]}"/>')
            s.append(f'<text x="{nx + bw / 2}" y="{y + 15}" text-anchor="middle" font-size="12">{esc(key)}</text>')
            x = nx + bw + 4
    s.append("</svg>")
    return "".join(s)

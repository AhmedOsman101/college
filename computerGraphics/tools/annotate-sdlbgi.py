#!/usr/bin/env python3
"""Annotate SDL_bgi.h with parameter names and doc comments.

The installed SDL_bgi header declares every function with unnamed parameters
(`void rectangle (int, int, int, int);`), so the editor shows no hints and no
description. Upstream's own src/SDL_bgi.c has both: named parameters and a
comment at the top of each function body.

This script rewrites the declarations to carry those names plus a Doxygen-style
doc block, using upstream's wording as the summary. For the functions this
course uses, a curated table supplies BGI-accurate parameter names
(left/top/right/bottom rather than x1/y1/x2/y2), one line per parameter, and
extra notes about state, units and pitfalls.

Usage:
    ./annotate-sdlbgi.py --c src/SDL_bgi.c --header in.h --out out.h

Output is a drop-in replacement for /usr/local/include/SDL2/SDL_bgi.h.
"""

import argparse
import re
import textwrap

# Functions this course calls: BGI-accurate parameter names, per-parameter
# help, and notes the parameter list cannot carry (units, y direction, which
# drawing state the call consumes).
CURATED = {
    "initgraph": {
        "params": ["graphdriver", "graphmode", "pathtodriver"],
        "paramdocs": {
            "graphdriver": "pass DETECT; its value is otherwise ignored",
            "graphmode": "graphics mode: VGAHI is 640x480. Initialise it — "
                          "`int gm = VGAHI;` — an uninitialized value lands on "
                          "SDL_bgi's 800x600 default",
            "pathtodriver": "BGI driver path, ignored by SDL_bgi (pass \"\")",
        },
        "notes": ["Opens a window and clears it. One call per program."],
    },
    "closegraph": {
        "params": [],
        "paramdocs": {},
        "notes": ["Destroys the window. Call it after the last getch()."],
    },
    "cleardevice": {
        "params": [],
        "paramdocs": {},
        "notes": ["Paints the whole window with the current background colour "
                  "and homes the current position to (0,0)."],
    },
    "line": {
        "params": ["x1", "y1", "x2", "y2"],
        "paramdocs": {
            "x1": "start x, pixels",
            "y1": "start y, pixels; y grows downward",
            "x2": "end x, pixels",
            "y2": "end y, pixels",
        },
        "notes": ["Drawn in the current colour and line style, clipped to the "
                  "window. Use linerel() for a relative segment."],
    },
    "rectangle": {
        "params": ["left", "top", "right", "bottom"],
        "paramdocs": {
            "left": "x of the left edge, pixels",
            "top": "y of the top edge, pixels (top < bottom, y grows downward)",
            "right": "x of the right edge, pixels",
            "bottom": "y of the bottom edge, pixels",
        },
        "notes": ["Draws four edges in the current colour and leaves the "
                  "interior untouched. Add bar() with the same coordinates to "
                  "fill it; bar() alone draws no border."],
    },
    "circle": {
        "params": ["x", "y", "radius"],
        "paramdocs": {
            "x": "centre x, pixels",
            "y": "centre y, pixels",
            "radius": "radius in pixels",
        },
        "notes": ["Outline only, in the current colour. Not filled: use "
                  "fillellipse() or floodfill() from the centre."],
    },
    "arc": {
        "params": ["x", "y", "stangle", "endangle", "radius"],
        "paramdocs": {
            "x": "centre x, pixels",
            "y": "centre y, pixels",
            "stangle": "start angle, degrees, counter-clockwise from 3 o'clock",
            "endangle": "end angle, degrees; equal to stangle draws one pixel, "
                        "not a line",
            "radius": "radius in pixels",
        },
        "notes": ["Angles run counter-clockwise while y still grows downward."],
    },
    "ellipse": {
        "params": ["x", "y", "stangle", "endangle", "xradius", "yradius"],
        "paramdocs": {
            "x": "centre x, pixels",
            "y": "centre y, pixels",
            "stangle": "start angle, degrees, counter-clockwise from 3 o'clock",
            "endangle": "end angle, degrees; 0 to 360 closes the curve",
            "xradius": "horizontal radius, pixels",
            "yradius": "vertical radius, pixels",
        },
        "notes": ["Outline only. Upper half is 0 to 180."],
    },
    "fillellipse": {
        "params": ["x", "y", "xradius", "yradius"],
        "paramdocs": {
            "x": "centre x, pixels",
            "y": "centre y, pixels",
            "xradius": "horizontal radius, pixels",
            "yradius": "vertical radius, pixels",
        },
        "notes": ["Interior uses the current fill style and colour; the outline "
                  "uses the current colour from setcolor()."],
    },
    "sector": {
        "params": ["x", "y", "stangle", "endangle", "xradius", "yradius"],
        "paramdocs": {
            "x": "centre x, pixels",
            "y": "centre y, pixels",
            "stangle": "start angle, degrees, counter-clockwise from 3 o'clock",
            "endangle": "end angle, degrees",
            "xradius": "horizontal radius, pixels",
            "yradius": "vertical radius, pixels",
        },
        "notes": ["Filled pie slice: two radii plus the arc between them. "
                  "Slices that sum to 360 fill the whole ellipse with no gaps "
                  "(0-40, 40-140, 140-180, 180-360 for a pie chart)."],
    },
    "pieslice": {
        "params": ["x", "y", "stangle", "endangle", "radius"],
        "paramdocs": {
            "x": "centre x, pixels",
            "y": "centre y, pixels",
            "stangle": "start angle, degrees, counter-clockwise",
            "endangle": "end angle, degrees",
            "radius": "radius in pixels",
        },
        "notes": ["Circular version of sector()."],
    },
    "bar": {
        "params": ["left", "top", "right", "bottom"],
        "paramdocs": {
            "left": "x of the left edge, pixels",
            "top": "y of the top edge, pixels",
            "right": "x of the right edge, pixels",
            "bottom": "y of the bottom edge, pixels",
        },
        "notes": ["Filled rectangle that draws NO outline — the fill pattern is "
                  "the edge. For a border, follow it with rectangle() using the "
                  "same coordinates."],
    },
    "bar3d": {
        "params": ["left", "top", "right", "bottom", "depth", "topflag"],
        "paramdocs": {
            "left": "x of the front face, left edge",
            "top": "y of the front face, top edge",
            "right": "x of the front face, right edge",
            "bottom": "y of the front face, bottom edge",
            "depth": "3D offset in pixels; 0 gives a flat bar",
            "topflag": "non-zero draws the top face; 0 leaves the bar open",
        },
        "notes": ["depth 20 / topflag 0 looks like an open box; depth 20 / "
                  "topflag 1 looks like a solid block."],
    },
    "drawpoly": {
        "params": ["numpoints", "polypoints"],
        "paramdocs": {
            "numpoints": "number of points; repeat the first point to close the shape",
            "polypoints": "flat int array x1,y1,x2,y2,... — 2*numpoints entries",
        },
        "notes": ["Naming one fewer point than the array holds leaves the last "
                  "edge open (drawpoly(3, tri) draws two edges)."],
    },
    "fillpoly": {
        "params": ["numpoints", "polypoints"],
        "paramdocs": {
            "numpoints": "number of points; repeat the first point to close the shape",
            "polypoints": "flat int array x1,y1,x2,y2,... — 2*numpoints entries",
        },
        "notes": ["Filled with the current fill style; the outline is drawn in "
                  "the current colour."],
    },
    "putpixel": {
        "params": ["x", "y", "color"],
        "paramdocs": {
            "x": "pixel x",
            "y": "pixel y",
            "color": "BGI palette index 0-15, not an RGB triple",
        },
        "notes": ["Visible immediately and unaffected by setcolor(). The "
                  "primitive under every raster algorithm."],
    },
    "getpixel": {
        "params": ["x", "y"],
        "paramdocs": {"x": "pixel x", "y": "pixel y"},
        "returndoc": "palette index 0-15 of that pixel",
        "notes": ["Returns the screen as drawn, not the current drawing colour."],
    },
    "setcolor": {
        "params": ["color"],
        "paramdocs": {"color": "BGI palette index 0-15 (WHITE, RED, GREEN, ...), not RGB"},
        "notes": ["Affects line, circle, rectangle, arc, drawpoly, outtextxy and "
                  "the outline of filled shapes — not bar() or fillpoly()'s "
                  "interior. Also the colour floodfill() checks against."],
    },
    "setbkcolor": {
        "params": ["color"],
        "paramdocs": {"color": "BGI palette index 0-15, not RGB"},
        "notes": ["Takes effect on the next cleardevice()."],
    },
    "setfillstyle": {
        "params": ["pattern", "color"],
        "paramdocs": {
            "pattern": "EMPTY_FILL, SOLID_FILL, LINE_FILL, HATCH_FILL, ... (0-11)",
            "color": "BGI palette index 0-15",
        },
        "notes": ["Applies to bar, bar3d, fillpoly, fillellipse, sector and "
                  "floodfill. EMPTY_FILL leaves the interior untouched."],
    },
    "floodfill": {
        "params": ["x", "y", "border"],
        "paramdocs": {
            "x": "seed x; must lie inside the closed area",
            "y": "seed y",
            "border": "palette index of the outline the fill must stop at",
        },
        "notes": ["If the outline is not closed, or setcolor changed after it "
                  "was drawn, the fill escapes and covers the window."],
    },
    "outtextxy": {
        "params": ["x", "y", "textstring"],
        "paramdocs": {
            "x": "left edge of the string, pixels",
            "y": "top edge of the string, pixels",
            "textstring": "NUL-terminated string",
        },
        "notes": ["Colour from setcolor(), font and size from settextstyle(). "
                  "Not clipped to the viewport."],
    },
    "outtext": {
        "params": ["textstring"],
        "paramdocs": {"textstring": "string drawn at the current position (CP)"},
        "notes": ["The CP advances past the string; moveto() sets it."],
    },
    "settextstyle": {
        "params": ["font", "direction", "charsize"],
        "paramdocs": {
            "font": "DEFAULT_FONT, TRIPLEX_FONT, SMALL_FONT, SANS_SERIF_FONT, GOTHIC_FONT",
            "direction": "HORIZ_DIR (left to right) or VERT_DIR (runs upward)",
            "charsize": "magnification factor, not a point size",
        },
        "notes": ["VERT_DIR starts at the given point and runs up the screen, so "
                  "use a y near the bottom for an axis title."],
    },
    "moveto": {
        "params": ["x", "y"],
        "paramdocs": {"x": "new current position, x", "y": "new current position, y"},
        "notes": ["Only changes the CP; nothing is drawn."],
    },
    "lineto": {
        "params": ["x", "y"],
        "paramdocs": {"x": "target x", "y": "target y"},
        "notes": ["Draws from the CP to (x,y) and moves the CP there."],
    },
    "linerel": {
        "params": ["dx", "dy"],
        "paramdocs": {"dx": "x offset from the CP", "dy": "y offset from the CP"},
        "notes": ["Draws a segment relative to the CP and moves the CP to its end."],
    },
    "moverel": {
        "params": ["dx", "dy"],
        "paramdocs": {"dx": "x offset", "dy": "y offset"},
        "notes": ["Moves the CP without drawing."],
    },
    "getmaxx": {
        "params": [],
        "paramdocs": {},
        "returndoc": "largest valid x coordinate (639 in a 640x480 window)",
        "notes": ["Use it instead of hardcoding 639 so a drawing tracks the mode."],
    },
    "getmaxy": {
        "params": [],
        "paramdocs": {},
        "returndoc": "largest valid y coordinate (479 in a 640x480 window)",
        "notes": ["Use it instead of hardcoding 479."],
    },
    "delay": {
        "params": ["msec"],
        "paramdocs": {"msec": "milliseconds to wait"},
        "notes": ["Also pumps the event queue, which is what keeps the window "
                  "responsive during animation."],
    },
}

DECL_RE = re.compile(
    r"^(?P<ret>(?:char\s*\*|void|int|unsigned\s+int|unsigned|char|signed\s+char|double|float|"
    r"struct\s+\w+\s*\*?|[A-Za-z_]\w*\s*\*))\s*"
    r"(?P<name>[A-Za-z_]\w*)\s*\((?P<params>[^;]*)\)\s*;\s*$"
)

DEF_HEAD_RE = re.compile(
    r"^(?P<ret>void|int|unsigned\s+int|unsigned|char\s*\*|char|size_t|struct\s+\w+\s*\*)"
    r"\s*(?P<name>[A-Za-z_]\w*)\s*\("
)

TYPE_WORDS = {
    "void", "int", "char", "unsigned", "signed", "long", "short", "float",
    "double", "const", "struct", "enum", "union", "Uint32", "Uint8", "size_t",
}


def split_params(text):
    parts, depth, cur = [], 0, ""
    for ch in text:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            parts.append(cur)
            cur = ""
        else:
            cur += ch
    if cur.strip():
        parts.append(cur)
    return [p.strip() for p in parts if p.strip()]


def parse_definitions(c_path):
    """name -> {'params': [names], 'summary': [lines]} from upstream .c."""
    with open(c_path, encoding="utf-8", errors="replace") as fh:
        lines = fh.read().splitlines()

    defs = {}
    for i, line in enumerate(lines):
        m = DEF_HEAD_RE.match(line)
        if not m:
            continue
        name = m.group("name")

        # The parameter list may span several lines.
        params_txt = ""
        j = i
        while j < len(lines):
            params_txt += lines[j]
            if ")" in lines[j]:
                break
            j += 1
        open_paren = params_txt.find("(")
        close_paren = params_txt.find(")", open_paren)
        params_txt = params_txt[open_paren + 1:close_paren]

        names = []
        for part in split_params(params_txt):
            tokens = part.replace("*", " ").split()
            if not tokens:
                continue
            cand = tokens[-1]
            if cand == "void":
                names.append("void")
            elif re.match(r"^[A-Za-z_]\w*$", cand):
                names.append(cand)

        # The summary: the `//` comments at the top of the body.
        k = j + 1
        while k < len(lines) and lines[k].strip() in ("", "{", "}"):
            k += 1
        summary = []
        while k < len(lines):
            s = lines[k].strip()
            if not s.startswith("//"):
                break
            body = s[2:].strip()
            if body:
                summary.append(body)
            k += 1

        if name not in defs:
            defs[name] = {"params": names, "summary": summary}

    return defs


def merge_continuations(lines):
    """Join declarations that upstream split over two lines, e.g.

        unsigned int
             getpixel (int, int);
    """
    out = []
    i = 0
    while i < len(lines):
        line = lines[i]
        stripped = line.strip()
        if (not stripped
                or DECL_RE.match(line)
                or stripped.startswith(("#", "//", "/*", "*"))):
            out.append(line)
            i += 1
            continue

        if re.match(r"^\s*(unsigned|signed|char|int|void|struct)\b[^;()]*$", line):
            buf = line.rstrip()
            j = i + 1
            while j < len(lines) and ";" not in buf:
                buf += " " + lines[j].strip()
                j += 1
            if DECL_RE.match(buf):
                out.append(buf)
                i = j
                continue

        out.append(line)
        i += 1
    return out


def already_named(decl):
    """True when a declared parameter already carries a name (`int color`)."""
    tokens = decl.replace("*", " ").split()
    if len(tokens) < 2:
        return False
    return tokens[-1] not in TYPE_WORDS and tokens[-2] in TYPE_WORDS | {"*"}


def wrap(text, indent, width=78):
    """Wrap a doc line, keeping `indent` on continuation lines."""
    return textwrap.wrap(
        " ".join(text.split()),
        width=width,
        initial_indent=" * " + indent,
        subsequent_indent=" * " + " " * len(indent),
    ) or [" * " + indent.rstrip()]


def build_annotation(name, defn):
    curated = CURATED.get(name)
    params = curated["params"] if curated else defn["params"]
    summary = defn["summary"]

    out = ["/**"]
    if summary:
        body = " ".join(summary).replace("*/", "*\\/")
        out.extend(wrap(body, ""))
    else:
        out.extend(wrap(name + "()", ""))

    if curated:
        docs = curated.get("paramdocs", {})
        block = []
        for p in [p for p in params if p != "void"]:
            if p in docs:
                block.extend(wrap(docs[p], f"@param {p} "))

        ret = curated.get("returndoc")
        if ret:
            block.extend(wrap(ret, "@return "))

        for n in curated.get("notes", []):
            if block:
                block.append(" *")
            block.extend(wrap(n, ""))

        if block:
            out.append(" *")
            out.extend(block)

    out.append(" */")
    return out


def rewrite(header_path, defs, out_path):
    with open(header_path, encoding="utf-8") as fh:
        lines = merge_continuations(fh.read().splitlines())

    result = []
    annotated = 0
    untouched = 0

    for line in lines:
        m = DECL_RE.match(line)
        if not m:
            result.append(line)
            continue

        name = m.group("name")
        defn = defs.get(name)
        if defn is None:
            result.append(line)
            untouched += 1
            continue

        curated = CURATED.get(name)
        params = curated["params"] if curated else defn["params"]

        declared = split_params(m.group("params"))
        new_params = []
        for idx, decl in enumerate(declared):
            decl = decl.strip()
            if decl in ("void", ""):
                new_params.append(decl)
                continue
            pname = params[idx] if idx < len(params) else None
            if pname in ("void", None) or already_named(decl):
                new_params.append(decl)
            elif "(*)" in decl:
                # `int (*)(void)` -> `int (*detect)(void)`
                new_params.append(decl.replace("(*)", f"(*{pname})"))
            else:
                new_params.append(f"{decl} {pname}")
        if not new_params:
            new_params = ["void"]

        result.extend(build_annotation(name, defn))
        result.append(f"{m.group('ret')} {name} ({', '.join(new_params)});")
        annotated += 1

    banner = [
        "// " + "=" * 74,
        "//  ANNOTATED COPY of SDL_bgi.h — generated, do not edit by hand.",
        "//  Parameter names and descriptions come from upstream src/SDL_bgi.c",
        "//  (SDL_bgi 3.0.0), plus curated @param/notes text for the course API.",
        "//  Regenerate with computerGraphics/tools/annotate-sdlbgi.py.",
        "// " + "=" * 74,
        "",
    ]

    with open(out_path, "w", encoding="utf-8") as fh:
        fh.write("\n".join(banner + result) + "\n")

    return annotated, untouched


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--c", required=True, help="upstream src/SDL_bgi.c")
    ap.add_argument("--header", required=True, help="pristine SDL_bgi.h")
    ap.add_argument("--out", required=True, help="annotated header to write")
    args = ap.parse_args()

    defs = parse_definitions(args.c)
    annotated, untouched = rewrite(args.header, defs, args.out)
    print(f"annotated {annotated} declarations, left {untouched} untouched -> {args.out}")


if __name__ == "__main__":
    main()

# `graphics.h` on Linux — how this repo runs it

The course code is written against Borland **BGI** via **WinBGIm**. It runs here
through **SDL_bgi 3.0.0**, built from source against SDL2, with two small compat
headers. No VM, no Wine. See
[ADR 0001](adr-0001-graphics-h-runtime-on-linux.md) for why.

## What is installed

| File | Path |
| --- | --- |
| `graphics.h` | `/usr/local/include/graphics.h` |
| `SDL_bgi.h` | `/usr/local/include/SDL2/SDL_bgi.h` |
| `libSDL_bgi.so` | `/usr/local/lib/libSDL_bgi.so` |
| man page | `/usr/local/share/man/man3/graphics.3.gz` |

Reinstalling from scratch:

```bash
git clone --depth 1 https://github.com/sergev/SDL_bgi.git /tmp/SDL_bgi
make -C /tmp/SDL_bgi/src
sudo make -C /tmp/SDL_bgi/src install \
  LIB_DIR=/usr/local/lib \
  SDL_INC=/usr/local/include/SDL2 \
  INC_DIR=/usr/local/include \
  MANDIR=/usr/local/share/man/man3
sudo ldconfig
```

Build first, override paths on `install` only: the Linux `Makefile` uses
`INC_DIR`/`SDL_INC` both to compile and to install, and the real SDL2 headers
live in `/usr/include/SDL2`.

## Building a program

```bash
cd computerGraphics
./bin/bgic examples/section-1/line_skeleton.cpp -o /tmp/line
./bin/bgic examples/section-2/fills.cpp -c -o /tmp/fills   # compile only
```

`bin/bgic` is a thin wrapper over `cppc` that adds:

```
-include compat/bgi_compat.hpp   -I compat   -lSDL_bgi
```

It sets **no environment variables**. Anything `cppc` accepts passes through.

## The two rules that differ from the material

### 1. Set the mode explicitly

```cpp
int gd = DETECT;
int gm = VGAHI;          // 640x480 — the resolution every example assumes
initgraph(&gd, &gm, "");
```

The vault's `int gm;` is *uninitialized*, and `initgraph` reads `*graphmode`
before it checks `DETECT` (`SDL_bgi.c:2527-2530`). The garbage lands in the mode
`switch`, whose `default:` calls `initwindow(800,600)`
(`SDL_bgi.c:2607-2610`) — verified: `getmaxx()` then reports 799 and every
coordinate in the material is off by the window's larger size.

`VGAHI` is the BGI *mode* constant (4 = 640×480). `VGA` is the BGI *driver*
constant that happens to share the value 4 inside SDL_bgi; prefer `VGAHI` so the
line reads as a mode.

For code pasted verbatim, the runtime switch is `SDL_BGI_RES=VGA`:

```bash
SDL_BGI_RES=VGA ./pasted_program
```

### 2. Include the compat header

`bin/bgic` pre-includes `compat/bgi_compat.hpp`, which adds `const char*`
overloads for `initgraph`, `outtext`, `outtextxy`, `textheight`, `textwidth`.
SDL_bgi declares those as `char*`, so literals produce
`-Wwrite-strings` warnings (GCC 16: warning, not error). With the shim: zero
warnings.

`compat/conio.h` supplies `clrscr()` and `gotoxy()`. `getch()`, `kbhit()` and
`delay()` come from `<graphics.h>` itself.

## Running

A 640×480 window opens; press any key to close it. Screenshot with:

```bash
import -window "$(xdotool search --name 'SDL_bgi' | head -1)" out.png
# or: maim -i <window-id> out.png
```

Headless (no `DISPLAY`, e.g. over SSH):

```bash
SDL_VIDEODRIVER=dummy ./program
```

The window becomes invisible — fine for checking that a program runs, useless
for looking at it.

## Failure modes

| Symptom | Cause and fix |
| --- | --- |
| `ISO C++ forbids converting a string constant to 'char*'` | Literal passed to the raw API. Build through `./bin/bgic`, which pre-includes `compat/bgi_compat.hpp`. |
| `conio.h: No such file or directory` | Same — `bgic` adds `-I compat`. |
| `undefined reference to initgraph` | Missing `-lSDL_bgi`; use `bgic`. |
| Window appears and vanishes instantly | That program has no `getch()`. |
| Window shows but the drawing is blank | Add `refresh()` before `getch()`. |
| Drawing sits off-centre / too small | The program still uses `int gm;`. Set `int gm = VGAHI;`. |
| `floodfill` covers the whole window | Seed reached the window edge: the outline was not closed, or `border` no longer matches the outline colour. `setcolor` must not run between drawing the outline and filling it. |

## Verified results (this machine, 2026-10-31)

All 13 programs build with `-Wall -Wextra` and **zero warnings**:

| Program | Build | Interactive run |
| --- | --- | --- |
| `examples/section-1/line_skeleton.cpp` | ok | window, one line (100,100)→(300,200) |
| `examples/section-1/dda_bresenham.cpp` | ok | prints both pixel lists (identical, per the lecture table) |
| `examples/section-2/ellipses.cpp` | ok | yellow ellipse, cyan half-ellipse, red filled ellipse |
| `examples/section-2/circles_arcs_sectors.cpp` | ok | 3 concentric circles; arc 0-360/0-180/45-90/90-90 (the last a dot); blue 0-90 sector |
| `examples/section-2/polys.cpp` | ok | closed triangle, open `drawpoly(3, …)`, filled triangle and square |
| `examples/section-2/pixels_colors.cpp` | ok | 100-pixel diagonal, four circles, 16-swatch palette |
| `examples/section-2/fills.cpp` | ok | solid, hatch and `EMPTY_FILL` interiors; no escape past the borders |
| `examples/section-2/composite.cpp` | ok | blue disc inside red ring inside yellow frame, labelled |
| `examples/section-3/bars.cpp` | ok | `bar()`, `bar()`+`rectangle()`, bare `rectangle()`, hatched floodfill |
| `examples/section-3/bar_chart.cpp` | ok | bars 120/180/90/210 with tops at 280/220/310/190, `VERT_DIR` "Units" |
| `examples/section-3/bar3d_text.cpp` | ok | depth 0 / depth 20 open top / depth 20 closed top; both text directions |
| `tasks/task-1/pie_chart.cpp` | ok | four slices filling the ellipse, labels around it |
| `tasks/task-1/house3d.cpp` | ok | five faces in back-to-front order, window and door on top |

The window stays open until you press a key while it has focus, or close it
with the X button. In scripted runs it can also exit `0` immediately; both are
fine, anything else (`134`, `139`) is a real failure.

## Behaviour differences from WinBGIm worth knowing

- **Angles are counter-clockwise**, y still grows downward: 0° is 3 o'clock and
  sweeps upward. Verified against the Task-1 pie chart.
- **`arc(x,y,90,90,r)` draws a single dot**, not a line — the material warns
  about this and SDL_bgi agrees.
- **Colours are palette indices 0–15**, not VGA DAC values; geometry is
  pixel-accurate, exact RGB is not.
- **Bresenham tie-breaks vary by formulation.** The lecture line (2,2)→(10,6)
  hits a pixel corner every step: `p = 2dy − dx` matches the lecture's table,
  an error-accumulator with `e2 < dx` gives the mirrored pixels. Both are valid.
- **No `registermousehandler`** (WinBGIm-only) and **no image export**; use
  `import`/`maim`.

## The Windows fallback, if ever needed

The lecturer's files were verified to *link* (not run) with the cross toolchain:

```bash
i686-w64-mingw32-g++ prog.cpp -I graphics-lib -L graphics-lib \
  -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -o prog.exe
wine prog.exe
```

`libbgi.a` is a 32-bit MinGW archive, so `i686-w64-mingw32-g++` is required;
`wine` is **not installed** on this machine. Use this only if grading demands
byte-identical WinBGIm output.

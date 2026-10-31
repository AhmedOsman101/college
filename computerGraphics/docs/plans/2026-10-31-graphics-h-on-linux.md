# graphics.h on Linux — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use /subagent-driven-development (recommended) or /executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Run the course's `graphics.h` programs natively on Arch Linux — no Windows VM, no Wine — by installing the SDL2-based `SDL_bgi`, adding a compatibility shim, and porting every sample from Sections 1–3 plus both Task-1 programs.

**Architecture:** `SDL_bgi` 3.0.0 (a superset of BGI + WinBGIm, backed by SDL2) is built from its GitHub mirror and installed into `/usr/local`. Two small compat headers bridge the dialect gap to the course's WinBGIm material: const-correct `char*` overloads (C++23 rejects string literals) and a `conio.h`. A `bgic` wrapper adds those flags to the existing `cppc` workflow, so every program builds and runs with one command.

**Tech Stack:** Arch Linux (x86_64), GCC 16.2.1, SDL2 (already installed), `make`, `cppc` (`/home/othman/scripts/cppc`), ImageMagick `import` / `maim` for screenshots.

**Spec:** `~/Documents/obsidian/src/College/yearThree/firstTerm/ComputerGraphics/Sections/Section-1.md`, `Section-2.md`, `Section-3.md`, `Tasks/Task-1.md`.

## Global Constraints

- Library source: `https://github.com/sergev/SDL_bgi`, branch `main`, `VERSION` = `3.0.0`. The AUR package `sdl_bgi` (2.5.0) is **unusable** — its source URL `https://sourceforge.net/projects/libxbgi/files/SDL_bgi-2.5.0.tar.gz` returns 404 behind a Cloudflare challenge (a live `paru -S sdl_bgi` failed exactly this way). Do not retry AUR.
- Install prefix `/usr/local`: `INC_DIR=/usr/local/include`, `SDL_INC=/usr/local/include/SDL2`, `LIB_DIR=/usr/local/lib`, `MANDIR=/usr/local/share/man/man3`. Verified on this machine: `/usr/local/lib` is in `ld`'s `SEARCH_DIR` and `/etc/ld.so.conf.d/usr-local-lib.conf` covers runtime, so no env vars and no `-Wl,-rpath` are needed.
- Build the library with **default** include paths (real SDL2 lives in `/usr/include/SDL2`), then apply the `/usr/local` overrides on the *install* step only. SDL_bgi's Linux `Makefile` hardcodes `INC_DIR`/`SDL_INC`/`LIB_DIR` for compiling and installing alike.
- `graphics-lib/` and `readme.txt` (the lecturer's WinBGIm Windows artifacts) have been **removed by the user and must not be re-added**. For the record: `libbgi.a` was an Intel i386 COFF archive and its `graphics.h`/`winbgim.h` included `<windows.h>`, so they could never build natively on Linux. `docs/graphics-on-linux.md` keeps the Wine fallback for anyone who still needs them.
- **The vault is a starting point, not a contract: setup may differ per machine; core API calls may not.** Every program here writes its own setup line —

  ```cpp
  int gd = DETECT;
  int gm = VGAHI;                    // 640x480
  initgraph(&gd, &gm, "");
  ```

  — and otherwise keeps the material's `circle`, `line`, `sector`, `fillpoly`, `outtextxy`, … calls exactly as written.
- **Why setup must differ:** `initgraph` consumes `*graphmode` **before** it checks `DETECT` (`SDL_bgi.c:2527-2530`), so the vault's `int gm;` feeds an uninitialized `int` into the mode `switch`, which falls through to `default:` → `initwindow(800,600)` (`SDL_bgi.c:2607-2610`). `VGAHI` is the BGI *mode* constant (640×480) in both SDL_bgi and real BGI; `VGA` is the BGI *driver* constant and only collides with the same value inside SDL_bgi.
- **No environment variables anywhere.** `bgic` exports nothing: resolution is visible in the source. `SDL_BGI_RES=VGA` is documented in the how-to purely as the runtime workaround for snippets pasted with `int gm;` intact.
- `cppc` stays the verification entry point (repo `AGENTS.md`), invoked through `bin/bgic`. `cppc -a` takes **one space-separated string** of compiler flags (`cppc -a "-DFOO -DBAR" file.cpp`), not one `-a` per flag; verified to work with the flags before or after the file. It splits on whitespace, so no flag and no path may contain spaces.
- Verification is evidence-based: every task records the command run and the observed output. No "should work" claims.

## Background: what the course actually calls

Required surface, extracted from the three Sections and Task 1:

| Group      | Symbols                                                                                                                  |
| ---------- | ------------------------------------------------------------------------------------------------------------------------ |
| Lifecycle  | `initgraph`, `closegraph`, `getch`, `cleardevice`                                                                        |
| Primitives | `line`, `circle`, `arc`, `ellipse`, `fillellipse`, `sector`, `rectangle`, `drawpoly`, `fillpoly`, `putpixel`, `getpixel` |
| State      | `setcolor`, `setfillstyle`, `setbkcolor`, `settextstyle`, `outtextxy`, `textheight`, `getmaxx`, `getmaxy`                |
| Fills/bars | `bar`, `bar3d`, `floodfill`                                                                                              |
| Constants  | `DETECT`, 16 BGI color names, 12 `*_FILL` patterns, `DEFAULT_FONT`, `HORIZ_DIR`, `VERT_DIR`                              |

SDL_bgi 3.0.0 provides every symbol above (verified in `src/SDL_bgi.h`). Known gaps, none used by the course: no `registermousehandler`, no WinBGIm `snapshot`. Unlike 2.5.0, 3.0.0 spells the font `SANS_SERIF_FONT` (the course only uses `DEFAULT_FONT`) and adds `refresh()`, `sdlbgiauto()`, `installuserfont()`.

## Review Focus

1. **String literals meet `char*` parameters.** SDL_bgi declares `initgraph(int*, int*, char*)` and `outtextxy(int,int,char*)`, so every literal in the material triggers `-Wwrite-strings`. Verified on GCC 16.2.1: this is a **warning, not an error** (5 warnings per example file, exit status 0) — an earlier draft of this plan wrongly called it an error. The const-correct overloads must remove those warnings so `-Wall -Wextra` builds stay clean, and must keep working if anyone ever adds `-Werror`.
2. **All material assumes a 640×480 screen.** Coordinates like `(320,240)`, `560`, `420` are hardcoded, yet SDL_bgi 3.0.0 defaults to 800×600 and the vault leaves `gm` uninitialized. Expectation: `(320,240)` is the centre of the window and `getmaxx()` reports 639, with no environment variables in play.
3. **`getch()` is what keeps the window alive.** Expectation: the window persists until a key is pressed, and `closegraph()` tears it down. Under no `DISPLAY` (SSH, CI) SDL cannot open a window at all; the documented answer is `SDL_VIDEODRIVER=dummy`, and no smoke test may hang forever.
4. **`floodfill` on an unclosed shape fills the whole screen** — or, with a `border` argument that no longer matches the outline after a later `setcolor`, silently escapes the intended region. This is the historic BGI crash; expectation is a fill that stays put.
5. **`sector`/`arc` angles run counter-clockwise while y grows downward.** `sector(cx,cy,0,40,...)` must appear to start at 3 o'clock and sweep *upward*. Backwards here mirrors the Task-1 pie chart.

---

## File Map

```
computerGraphics/
├── compat/
│   ├── bgi_compat.hpp              const-correct overloads; pre-included by bgic
│   ├── conio.h                     clrscr/gotoxy; getch/kbhit come from graphics.h
│   └── selftest.cpp                regression guard for the shim
├── bin/
│   └── bgic                        thin wrapper: cppc + compat flags + -lSDL_bgi
├── examples/
│   ├── section-1/                  line_skeleton.cpp, dda_bresenham.cpp
│   ├── section-2/                  ellipses.cpp, circles_arcs_sectors.cpp, polys.cpp,
│   │                               pixels_colors.cpp, fills.cpp, composite.cpp
│   └── section-3/                  bars.cpp, bar_chart.cpp, bar3d_text.cpp
├── tasks/task-1/                   pie_chart.cpp, house3d.cpp, README.md
└── docs/
    ├── plans/2026-10-31-graphics-h-on-linux.md     (this file)
    ├── adr-0001-graphics-h-runtime-on-linux.md
    └── graphics-on-linux.md        how-to + failure table + Wine fallback
```

---

### Task 1: Build and install SDL_bgi 3.0.0

**Files:**
- Create: `/tmp/opencode/SDL_bgi/` (out-of-tree clone, not committed)
- Modify: system `/usr/local` (two headers, `libSDL_bgi.so`, man page)

**Interfaces:**
- Produces: `<graphics.h>` resolving to `/usr/local/include/graphics.h`, `<SDL2/SDL_bgi.h>`, linkable `-lSDL_bgi`.

- [ ] **Step 1: Clone the maintained mirror**

```bash
git clone --depth 1 https://github.com/sergev/SDL_bgi.git /tmp/opencode/SDL_bgi
cat /tmp/opencode/SDL_bgi/VERSION
```
Expected: `3.0.0`

- [ ] **Step 2: Build with default include paths**

```bash
make -C /tmp/opencode/SDL_bgi/src
```
Expected: `libSDL_bgi.so` appears in `/tmp/opencode/SDL_bgi/src`. Warnings are acceptable; errors are not.

- [ ] **Step 3: Confirm the library exports the course API**

```bash
nm -D --defined-only /tmp/opencode/SDL_bgi/src/libSDL_bgi.so \
  | grep -cE ' T (initgraph|closegraph|line|circle|arc|ellipse|fillellipse|sector|rectangle|drawpoly|fillpoly|putpixel|getpixel|setcolor|setfillstyle|setbkcolor|settextstyle|outtextxy|textheight|getmaxx|getmaxy|bar|bar3d|floodfill|getch|cleardevice)$'
grep -n 'define getch bgi_getch' /tmp/opencode/SDL_bgi/src/SDL_bgi.h
```
Expected: `25`, not 26 — `getch` is a **header macro**, not an exported symbol: `SDL_bgi.h:384` declares `bgi_getch` and `:386` does `#define getch bgi_getch` ("to avoid a bug with Mingw64"). The second command must print that `#define`, which is what makes `getch()` available to any program including `<graphics.h>`. All 26 course symbols are therefore usable; 25 of them are real exports.

- [ ] **Step 4: Install to `/usr/local` (overrides at install time only)**

> **Human step.** `sudo` on this machine requires an interactive password, so an agent cannot run this block.

```bash
sudo make -C /tmp/opencode/SDL_bgi/src install \
  LIB_DIR=/usr/local/lib \
  SDL_INC=/usr/local/include/SDL2 \
  INC_DIR=/usr/local/include \
  MANDIR=/usr/local/share/man/man3
sudo ldconfig
```
Expected: **five** lines — one `install -d` creating the four directories, then four file installs (`libSDL_bgi.so`, `SDL_bgi.h`, `graphics.h`, `graphics.3.gz`). A `make -n install` dry run with these overrides emits exactly those five and no compiler invocation, so the install cannot trigger a rebuild with the wrong include paths.

- [ ] **Step 5: Verify resolution and linkage**

```bash
ls -l /usr/local/include/graphics.h /usr/local/include/SDL2/SDL_bgi.h /usr/local/lib/libSDL_bgi.so
ldconfig -p | grep SDL_bgi
printf '#include <graphics.h>\nint main(){return 0;}\n' > /tmp/opencode/inc.cpp
g++ -std=c++23 -E -H /tmp/opencode/inc.cpp 2>&1 | grep -m1 'SDL_bgi.h'
```
Expected: all three files exist; `ldconfig` lists `libSDL_bgi.so (libc6,x86-64) => /usr/local/lib/libSDL_bgi.so`; the preprocessor reports `/usr/local/include/SDL2/SDL_bgi.h`.

- [ ] **Step 6: Runtime smoke test — and capture the resolution trap as evidence**

This smoke deliberately reproduces the vault's `int gm;` idiom so it demonstrates *both* behaviours before any example depends on them.

```bash
cat > /tmp/opencode/smoke.cpp <<'EOF'
#include <graphics.h>
#include <cstdio>
int main() {
  int gd = DETECT, gm;             // vault idiom: gm uninitialized
  initgraph(&gd, &gm, (char*)"");  // plain g++ here, no compat shim yet
  printf("maxx=%d maxy=%d gm=%d\n", getmaxx(), getmaxy(), gm);
  line(0, 0, getmaxx(), getmaxy());
  refresh();
  getch();
  closegraph();
  return 0;
}
EOF
g++ -std=c++23 -Wall -Wextra /tmp/opencode/smoke.cpp -lSDL_bgi -o /tmp/opencode/smoke
SDL_BGI_RES=VGA timeout 10 /tmp/opencode/smoke
timeout 10 /tmp/opencode/smoke
```
Expected: the first run prints `maxx=639 maxy=479 gm=4`; the second prints `maxx=799 maxy=599` with a small or garbage `gm`. Confirm **both** — this is the experiment that justifies every example writing `int gm = VGAHI;` instead of copying the vault's declaration. Both runs open a window with a diagonal line and wait for a key.

- [ ] **Step 7: Commit**

```bash
cd /home/othman/work/college
git add computerGraphics/docs/plans/2026-10-31-graphics-h-on-linux.md
git commit -m "docs(graphics): plan for running graphics.h natively on Linux"
```

---

### Task 2: Compat layer (`bgi_compat.hpp`, `conio.h`, `selftest.cpp`)

**Files:**
- Create: `computerGraphics/compat/bgi_compat.hpp`
- Create: `computerGraphics/compat/conio.h`
- Create: `computerGraphics/compat/selftest.cpp` (committed — the regression guard)

**Interfaces:**
- Produces: `bgi_compat.hpp` — `#pragma once`, includes `<graphics.h>`, then `inline` overloads `outtextxy(int,int,const char*)`, `outtext(const char*)`, `textheight(const char*)`, `textwidth(const char*)`, and `initgraph(int*,int*,const char*)`, each forwarding to the `char*` version via `const_cast<char*>`; plus `#ifndef SANS_SERIF_FONT` / `#define SANS_SERIF_FONT SANSSERIF_FONT` / `#endif` so an older 2.x install still compiles.
- Produces: `conio.h` — `#pragma once`, `#include <graphics.h>` (which supplies `getch`, `kbhit`, `delay`), then `static inline void clrscr(void)` forwarding to `cleardevice()` and `static inline void gotoxy(int,int)` emitting the ANSI cursor escape. `static inline` avoids duplicate symbols across translation units. Note the semantic choice: BGI's `clrscr` clears the text console, but in a graphics program that is never what is wanted, so it clears the graphics screen.

- [ ] **Step 1: Write the failing test**

```cpp
// compat/selftest.cpp — must fail to compile before the compat header exists.
#include <graphics.h>
#include <conio.h>
int main() {
  int gd = DETECT;
  int gm = VGAHI;                 // 640x480
  initgraph(&gd, &gm, "");        // literal, not char*
  setcolor(WHITE);
  rectangle(10, 10, 100, 100);
  outtextxy(20, 20, "hello");     // literal, not char*
  outtext("x");
  int h = textheight("Ag");
  int w = textwidth("Ag");
  clrscr();
  gotoxy(1, 1);
  return (h > 0 && w > 0) ? 0 : 1;
}
```

- [ ] **Step 2: Run it and confirm the expected failure**

```bash
cd /home/othman/work/college/computerGraphics
g++ -std=c++23 -c compat/selftest.cpp -o /tmp/opencode/selftest.o
```
Expected: FAIL — `conio.h: No such file or directory`. Then, to see the literal problem on its own, compile again with only `-I compat` (no `-include`): expect five `-Wwrite-strings` warnings (`ISO C++ forbids converting a string constant to 'char*'`) and **exit 0** — GCC 16 treats it as a warning.

- [ ] **Step 3: Implement the two headers** exactly per the Interfaces block. No other symbols, no `using namespace`, nothing that changes BGI semantics.

- [ ] **Step 4: Re-run with the headers on the include path**

```bash
g++ -std=c++23 -Wall -Wextra -I compat -include compat/bgi_compat.hpp \
    -c compat/selftest.cpp -o /tmp/opencode/selftest.o
```
Expected: PASS with zero warnings. `-include` is what makes this work for course files that include `<graphics.h>` themselves: the pre-included header pulls it in first, then its guard makes the later include a no-op.

- [ ] **Step 5: Confirm it links and runs**

```bash
g++ -std=c++23 -I compat -include compat/bgi_compat.hpp compat/selftest.cpp \
    -lSDL_bgi -o /tmp/opencode/selftest
timeout 10 /tmp/opencode/selftest; echo "exit=$?"
```
Expected: `exit=0`, a window opens and closes immediately (no `getch()` in the test).

- [ ] **Step 6: Commit**

```bash
git add computerGraphics/compat
git commit -m "feat(graphics): add const-correct BGI compat header and conio shim"
```

---

### Task 3: `bgic` build wrapper over `cppc`

**Files:**
- Create: `computerGraphics/bin/bgic` (executable, `#!/usr/bin/env bash`)
- Create: `computerGraphics/examples/section-1/line_skeleton.cpp` (first consumer)

**Interfaces:**
- Consumes: `cppc` at `/home/othman/scripts/cppc`; headers from Task 2.
- Produces: `bgic <file.cpp> [cppc args…]` — resolves its own directory from `${BASH_SOURCE[0]}`, then execs `cppc -a "-include <repo>/compat/bgi_compat.hpp -I<repo>/compat -lSDL_bgi" "$@"`. Exit code and stdout belong to `cppc`. It sets **no** environment variables: window size comes from the program's own `int gm = VGAHI;`.

- [ ] **Step 1: Write the failing check**

```bash
cd /home/othman/work/college/computerGraphics
./bin/bgic examples/section-1/line_skeleton.cpp
```
Expected: FAIL — `bin/bgic: No such file or directory`.

- [ ] **Step 2: Implement `bin/bgic`** with `set -euo pipefail`, `REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"`, and the single-`-a` `exec cppc` line from the Interfaces block, then `chmod +x`.

- [ ] **Step 3: Author `examples/section-1/line_skeleton.cpp`** — the Section-1 minimal program (`Section-1.md:178-194`) with Linux setup: `int gd = DETECT; int gm = VGAHI; initgraph(&gd, &gm, "");` then the material's `line(100,100,300,200)`, `getch()`, `closegraph()` unchanged.

- [ ] **Step 4: Build and run through the wrapper**

```bash
./bin/bgic examples/section-1/line_skeleton.cpp -o /tmp/opencode/line_skeleton
timeout 10 /tmp/opencode/line_skeleton
```
Expected: compiles with zero warnings; a 640×480 window shows one line from (100,100) to (300,200); process waits for a key and exits 0.

- [ ] **Step 5: Prove the program pins 640×480 on its own**

Compiled and run with **no** environment variables — the mode must come from the source alone.

```bash
cat > /tmp/opencode/res.cpp <<'EOF'
#include <graphics.h>
#include <cstdio>
int main() {
  int gd = DETECT;
  int gm = VGAHI;
  initgraph(&gd, &gm, "");
  printf("maxx=%d maxy=%d gm=%d\n", getmaxx(), getmaxy(), gm);
  closegraph();
  return 0;
}
EOF
./bin/bgic /tmp/opencode/res.cpp -o /tmp/opencode/res
env -u SDL_BGI_RES timeout 10 /tmp/opencode/res
```
Expected: `maxx=639 maxy=479 gm=4`. If it prints 799/599, the file's `gm` initialiser is missing — `bgic` will not rescue it, by design.

- [ ] **Step 6: Verify the wrapper does not swallow `cppc` flags**

```bash
./bin/bgic examples/section-1/line_skeleton.cpp -c -o /tmp/opencode/line_only
ls -l /tmp/opencode/line_only
```
Expected: binary produced, nothing run. Confirms `-c` and `-o` pass straight through.

- [ ] **Step 7: Commit**

```bash
git add computerGraphics/bin/bgic computerGraphics/examples/section-1/line_skeleton.cpp
git commit -m "feat(graphics): add bgic wrapper and Section 1 skeleton example"
```

---

### Task 4: Section 1 — DDA and Bresenham pixels

**Files:**
- Create: `computerGraphics/examples/section-1/dda_bresenham.cpp`

**Interfaces:**
- Consumes: `bgic`; `putpixel`, `line`, `getmaxx`/`getmaxy`; standard setup line.

- [ ] **Step 1: Author `dda_bresenham.cpp`** — port `ddaLine()` verbatim from `Section-1.md:133-149`, draw the lecture line (2,2)→(10,6) with `putpixel` in one colour, then the Bresenham pixel list from `Section-1.md:159` in another, and print both lists to stdout so the two algorithms are compared textually as the material does. Offset the drawn copies (e.g. start at 120,120) so the pixels are visible.

  **Bresenham must use the decision-parameter form** `p = 2dy − dx` (initialise `p`, then `p += 2dy` when `p < 0`, else `y += sy; p += 2(dy − dx)`). This line has slope exactly 0.5, so every step lands on a pixel corner and the tie-break decides the result: the decision-parameter form prints `(3,3) (5,4) (7,5) (9,6)`, while an error-accumulator testing `e2 < dx` prints `(3,2) (5,3) (7,4) (9,5)`. Only the first agrees with the lecture table; both are valid rasterisations, so this is a formulation choice, not a bug to "fix" in the material.

- [ ] **Step 2: Run it and check the printed lists**

```bash
cd /home/othman/work/college/computerGraphics
./bin/bgic examples/section-1/dda_bresenham.cpp -o /tmp/opencode/dda
timeout 10 /tmp/opencode/dda
```
Expected stdout: two identical 9-pixel sequences `(2,2) … (10,6)`, matching the table at `Section-1.md:121-131`.

- [ ] **Step 3: Check the drawn result survives a redraw**

If the window shows a blank background instead of pixels, add `refresh()` before `getch()` and rerun, keeping it only if it was needed. Record which in the commit message (it is a real finding for Task 8).

- [ ] **Step 4: Commit**

```bash
git add computerGraphics/examples/section-1/dda_bresenham.cpp
git commit -m "feat(graphics): Section 1 DDA and Bresenham pixel example"
```

---

### Task 5: Section 2 — primitives, palette and fills

**Files:**
- Create: `examples/section-2/ellipses.cpp` (`Section-2.md:64-93`)
- Create: `examples/section-2/circles_arcs_sectors.cpp` (`Section-2.md:95-144`)
- Create: `examples/section-2/polys.cpp` (`Section-2.md:166-199`)
- Create: `examples/section-2/pixels_colors.cpp` (`Section-2.md:201-249`)
- Create: `examples/section-2/fills.cpp` (`Section-2.md:251-282`)
- Create: `examples/section-2/composite.cpp` (`Section-2.md:284-323`)

**Interfaces:**
- Consumes: `bgic`; every primitive and state function from Background.

- [ ] **Step 1: Author the six files**, transcribing the material's calls in the material's order. Every file starts with the standard setup (`int gd = DETECT; int gm = VGAHI; initgraph(&gd, &gm, "");`) and ends with `getch(); closegraph();`. One file per subsection so a broken call is localised.

- [ ] **Step 2: Compile all six**

```bash
cd /home/othman/work/college/computerGraphics
for f in examples/section-2/*.cpp; do
  ./bin/bgic "$f" -c -o "/tmp/opencode/$(basename "${f%.cpp}")" || echo "FAILED: $f"
done
```
Expected: no `FAILED:` lines, zero warnings.

- [ ] **Step 3: Run each and compare with the material's stated output**

```bash
for f in examples/section-2/*.cpp; do
  name="$(basename "${f%.cpp}")"
  ./bin/bgic "$f" -o "/tmp/opencode/$name" >/dev/null
  timeout 5 "/tmp/opencode/$name"; echo "$name exit=$?"
done
```
Expected: each window shows the shapes named in `Section-2.md` — yellow and cyan ellipses; three green concentric circles; blue quarter sector; nested rectangles; an open triangle for `drawpoly(3,…)`; a blue 100-pixel diagonal; a red-ringed blue disc in the composite. `exit=124` means the window was still waiting on `getch()` and is the normal result; anything else is a defect in that file.

- [ ] **Step 4: Inspect `fills.cpp` specifically (Review Focus #4)**

The circle interior must be fully cyan, and the process must neither hang nor exit 134/139. `floodfill(320,240,WHITE)` requires the outline to still be `WHITE` at fill time; if the sequence changed colour first, the fill escapes to the window edge. Record which of the two happened.

- [ ] **Step 5: Check sector/arc orientation (Review Focus #5)**

`sector(320,240,0,90,200,120)` must fill the **upper-right** quadrant: 0° at 3 o'clock, sweeping up. If it fills lower-right, the convention is flipped relative to the material — record the finding for Task 8 and adjust only the example, never the shim.

- [ ] **Step 6: Commit**

```bash
git add computerGraphics/examples/section-2
git commit -m "feat(graphics): Section 2 primitive, fill and composite examples"
```

---

### Task 6: Section 3 — bars, text, 3D

**Files:**
- Create: `examples/section-3/bars.cpp` (`Section-3.md:27-44`, `63-83`)
- Create: `examples/section-3/bar_chart.cpp` (`Section-3.md:129-192`)
- Create: `examples/section-3/bar3d_text.cpp` (`Section-3.md:96-127`, `194-222`)

**Interfaces:**
- Consumes: `bgic`; `bar`, `bar3d`, `settextstyle`, `outtextxy`, `floodfill`; standard setup line.

- [ ] **Step 1: Author the three files** from the material, each with the standard setup. `bar_chart.cpp` keeps the dataset `{120,180,90,210}` and `baseY=400`, including the `VERT_DIR` axis title at `(40,300)`.

- [ ] **Step 2: Verify the chart arithmetic**

Bars sit at x = 110, 220, 330, 440 with width 80; the tallest bar (210 → top 190) is the fourth and the shortest (90 → top 310) is the third, per `Section-3.md:184-189`.

- [ ] **Step 3: Verify `VERT_DIR` text grows upward**

`outtextxy(40,300,"Units")` must read bottom-to-top starting at y=300. If it runs off-screen downward, record it — this is the classic WinBGIm/BGI divergence. If text is missing entirely, note that only `DEFAULT_FONT` is really implemented in SDL_bgi.

- [ ] **Step 4: Verify `bar3d` topflag behaviour**

`bar3d(220,300,300,400,20,0)` shows a side but no top face; `bar3d(340,300,420,400,20,1)` shows both, per `Section-3.md:213-222`.

- [ ] **Step 5: Commit**

```bash
git add computerGraphics/examples/section-3
git commit -m "feat(graphics): Section 3 bar, bar chart and bar3d examples"
```

---

### Task 7: Task 1 coursework programs

**Files:**
- Create: `tasks/task-1/pie_chart.cpp` (from `Tasks/Task-1.md:52-96`)
- Create: `tasks/task-1/house3d.cpp` (from `Tasks/Task-1.md:120-160`)
- Create: `tasks/task-1/README.md` — build command and screenshot capture for submission

**Interfaces:**
- Consumes: `bgic`; `sector`, `fillpoly`, `bar`, `outtextxy`; standard setup line.

- [ ] **Step 1: Author `pie_chart.cpp`** (standard setup first) with the four sectors `0-40`, `40-140`, `140-180`, `180-360` around `(320,260)` at radii `230×150`, plus the five labels at the coordinates the material gives.

- [ ] **Step 2: Author `house3d.cpp`** (standard setup first) with far roof, side, near roof and front `fillpoly` calls plus the two `bar()` openings, in the material's far-to-near order.

- [ ] **Step 3: Run both and check adjacency, not overlap**

```bash
cd /home/othman/work/college/computerGraphics
./bin/bgic tasks/task-1/pie_chart.cpp -o /tmp/opencode/pie_chart
./bin/bgic tasks/task-1/house3d.cpp -o /tmp/opencode/house3d
timeout 10 /tmp/opencode/pie_chart
```
Expected: the pie is fully filled with four colours, the iron slice starting at 3 o'clock and sweeping up; no gaps or slivers between slice edges. A gap means an angle-boundary mismatch in that file's values.

- [ ] **Step 4: Capture a submission screenshot**

With the window visible and focused:

```bash
import -window "$(xdotool search --name 'SDL_bgi' | head -1)" /tmp/opencode/task1-pie.png
maim -i "$(xdotool search --name 'SDL_bgi' | head -1)" /tmp/opencode/task1-pie-maim.png  # fallback
```
Expected: a PNG containing exactly the drawing area. Both `import` (ImageMagick) and `maim` are installed.

- [ ] **Step 5: Commit**

```bash
git add computerGraphics/tasks/task-1
git commit -m "feat(graphics): Task 1 pie chart and 3D house programs"
```

---

### Task 8: Documentation, ADR and known gaps

**Files:**
- Create: `docs/adr-0001-graphics-h-runtime-on-linux.md`
- Create: `docs/graphics-on-linux.md`

**Interfaces:**
- Consumes: every finding recorded in Tasks 1–7 (the 800×600 trap, whether `refresh()` was needed, angle conventions, `exit=124` semantics).

- [ ] **Step 1: Write the ADR.** Decision: SDL_bgi 3.0.0, native, `/usr/local`. Alternatives rejected with verified reasons: WinBGIm through Wine + `i686-w64-mingw32-g++` (compiles — proven — but needs a 1 GB runtime and a non-native loop); AUR `sdl_bgi` 2.5.0 (source URL 404 behind Cloudflare); AUR `libgraph` (SDL 1.2 + `guile1.8`, stale); hand-written SDL2 shim (700–1000 LOC of fill and font surface to own forever). Consequences: shapes are BGI-faithful but palette RGB values differ from VGA DAC values; `registermousehandler` absent; setup line differs from the vault by one initialiser.

- [ ] **Step 2: Write `docs/graphics-on-linux.md`** covering: the install commands from Task 1; the `bgic` one-liner; the resolution contract (`int gm = VGAHI;` → `getmaxx()==639`, why the vault's `int gm;` silently yields 800×600, and that `SDL_BGI_RES=VGA` is a runtime workaround for pasted code); `SDL_VIDEODRIVER=dummy` for headless; screenshot commands; the failure-mode table (`ISO C++ forbids converting a string constant` → include `bgi_compat.hpp`, which `bgic` does; `undefined reference to initgraph` → missing `-lSDL_bgi`; window closes instantly → missing `getch()`; blank window → missing `refresh()`; drawing off-centre → `int gm;` instead of `int gm = VGAHI;`); and the Wine fallback with the exact verified link line `i686-w64-mingw32-g++ … -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32`.

- [ ] **Step 3: Reconcile the two orientation findings** from Tasks 5 and 6 into the ADR's consequences — whatever `sector` and `VERT_DIR` actually did on this build.

- [ ] **Step 4: Commit**

```bash
git add computerGraphics/docs
git commit -m "docs(graphics): ADR and Linux how-to for the SDL_bgi toolchain"
```

---

### Task 9: Full verification sweep

**Files:**
- Modify: `docs/graphics-on-linux.md` (append the results table)

- [ ] **Step 1: Run every program non-interactively**

```bash
cd /home/othman/work/college/computerGraphics
for f in examples/section-*/*.cpp tasks/task-1/*.cpp; do
  out="/tmp/opencode/$(echo "$f" | tr '/' '_' | sed 's/\.cpp$//')"
  ./bin/bgic "$f" -o "$out" >/dev/null 2>&1 || { echo "BUILD FAIL $f"; continue; }
  rc=0
  timeout 5 "$out" >/dev/null 2>&1 || rc=$?
  printf '%-45s build=ok exit=%s\n' "$f" "$rc"
done
```
Expected: every line `build=ok`, with `exit` either `0` (closed itself) or `124` (timed out waiting for a key). No `BUILD FAIL`, no `134`, no `139`.

- [ ] **Step 2: Audit the resolution setup across every program**

```bash
grep -L 'int gm = VGAHI;' examples/section-*/*.cpp tasks/task-1/*.cpp
```
Expected: no output. Any file listed is missing the 640×480 initialiser and would silently open an 800×600 window.

- [ ] **Step 3: Confirm no warnings anywhere**

```bash
for f in examples/section-*/*.cpp tasks/task-1/*.cpp; do
  ./bin/bgic "$f" -c -o /tmp/opencode/w.o 2>&1 | grep -i warning && echo "WARN in $f"
done
```
Expected: no output. `cppc` already passes `-Wall -Wextra`, so a warning here is a real defect in the ported file.

- [ ] **Step 4: Record the pass table** in `docs/graphics-on-linux.md` (file → build → run → notes) with the actual observed exit codes.

- [ ] **Step 5: Commit**

```bash
git add computerGraphics/docs/graphics-on-linux.md
git commit -m "test(graphics): verification sweep results for all examples"
```

---

## Open Questions

Resolved during implementation:

1. ~~`graphics-lib/` and `readme.txt`~~ — removed by the user; the Wine recipe now
   lives in `docs/graphics-on-linux.md` as the fallback.
2. ~~`arc(...,90,90,...)` may draw nothing under SDL_bgi~~ — it draws a single dot,
   matching the material. Confirmed on screen in `circles_arcs_sectors.cpp`.

Still open:

1. Task-1 is graded work. If the grader demands byte-exact WinBGIm rendering (VGA
   DAC colours, bitmap font rasterisation), the Wine route in
   `docs/graphics-on-linux.md` is the escape hatch — proven to link, not yet run.

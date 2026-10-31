# ADR 0001 — Running the course's `graphics.h` natively on Linux

- **Status:** accepted
- **Date:** 2026-10-31
- **Context:** Computer Graphics coursework (year three, first term) is written
  against Borland **BGI** via **WinBGIm** — `graphics.h` + `libbgi.a`, built in
  Code::Blocks under Windows.

## Decision

Use **SDL_bgi 3.0.0** (`github.com/sergev/SDL_bgi`) built from source and
installed into `/usr/local`, plus two small compat headers in this repo.

## Context that forced a decision

The lecturer's `graphics-lib/` cannot work here at all:

| Artifact | Why it fails on Linux |
| --- | --- |
| `graphics.h`, `winbgim.h` | `#include <windows.h>`; GDI32-bound, 362 lines of Win32 |
| `libbgi.a` | **Intel i386 COFF** archive (32-bit MinGW), unlinkable with a 64-bit ELF toolchain |

So the choice is which *reimplementation* to run.

## Alternatives considered

| Option | Verdict |
| --- | --- |
| **SDL_bgi 3.0.0 from source** | **Chosen.** Builds against the SDL2 already installed, no VM, no Wine. Implements every function the course uses (verified symbol by symbol), plus `refresh()`, `sdlbgiauto()`, `installuserfont()`. |
| AUR `sdl_bgi` 2.5.0 | Rejected — unusable in practice: the PKGBUILD pulls from SourceForge, which now returns 404 behind a Cloudflare challenge. A live `paru -S sdl_bgi` failed on exactly that URL. |
| AUR `libgraph` | Rejected — SDL 1.2 + `guile1.8`, stale and crash-prone. |
| WinBGIm under Wine, cross-compiled with `i686-w64-mingw32-g++` | Verified to *link* against the lecturer's `libbgi.a`, so it stays documented as the fidelity fallback. Rejected as the daily driver: ~1 GB of Wine plus a non-native debug loop for coursework that only needs the BGI API. |
| Hand-written SDL2 shim in this repo | Rejected — 700–1000 lines of fill patterns, floodfill and bitmap fonts to own forever, for a result no better than SDL_bgi. |

## Consequences

- **Resolution is the program's job.** `initgraph` consumes `*graphmode`
  *before* checking `DETECT`, so the vault's `int gm;` lands on an 800×600
  default. Every program here writes `int gm = VGAHI;` (= 640×480).
  `SDL_BGI_RES=VGA` is the equivalent runtime switch for code pasted verbatim.
- **String literals need a shim.** SDL_bgi declares `char*` parameters;
  GCC 16 reports `-Wwrite-strings` for each literal (a warning, not an error).
  `compat/bgi_compat.hpp` adds `const char*` overloads so builds stay clean.
- **`conio.h` does not exist.** `compat/conio.h` supplies `clrscr()` (mapped to
  `cleardevice()`) and `gotoxy()`. `getch`, `kbhit` and `delay` come from
  `<graphics.h>` itself.
- **Colours are BGI palette indices, not VGA DAC values.** Shape geometry is
  pixel-accurate; the exact RGB of color 4 (RED) differs from DOS.
- **`sector`/`arc` angles are counter-clockwise** with y growing downward, so
  0° is 3 o'clock and sweeps upward — verified on screen against the Task-1 pie
  chart, which is the behaviour the material documents.
- **Bresenham tie-breaks are implementation-defined.** On the lecture line
  (2,2)→(10,6) every step lands on a pixel corner; the decision-parameter form
  (`p = 2dy − dx`) reproduces the lecture's table, while an error-accumulator
  variant testing `e2 < dx` yields the mirrored pixels. Both are correct
  rasterisations; the examples use the form that agrees with the material.
- **No `registermousehandler`** (WinBGIm-only) and no image-export function;
  screenshots come from `import`/`maim`.
- **Course behaviour is 32-bit-BGI-like but not a DOS emulator.** Programs
  using `DOS.H`, `BIOS.H` or hardware key codes still need DOSBox.

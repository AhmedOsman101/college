# Task 1 — pie chart and 3D house

Both slides from `Tasks/Task-1.md`, ported to run on Linux against SDL_bgi.

## Build and run

```bash
cd computerGraphics
./bin/bgic tasks/task-1/pie_chart.cpp -o /tmp/pie_chart && /tmp/pie_chart
./bin/bgic tasks/task-1/house3d.cpp   -o /tmp/house3d   && /tmp/house3d
```

A 640×480 window opens; press any key to close it.

## Screenshot for submission

With the window open and focused:

```bash
import -window "$(xdotool search --name 'SDL_bgi' | head -1)" pie.png
```

`maim -i <window-id> pie.png` works too. Both tools are installed on this machine.

## What differs from the vault code

Only the setup lines. The vault uses the Turbo C idiom:

```cpp
int gd = DETECT;
int gm;                       // uninitialized
initgraph(&gd, &gm, "C:\\tc\\bgi");
```

SDL_bgi reads `*graphmode` before it looks at `DETECT`, so an uninitialized
`gm` selects its 800×600 default and every coordinate in the drawing lands in
the wrong place. These programs use the BGI mode constant instead:

```cpp
int gd = DETECT;
int gm = VGAHI;               // 640x480
initgraph(&gd, &gm, "");
```

Everything else — `sector`, `fillpoly`, `bar`, `outtextxy`, the coordinates,
the draw order — is as written in the material.

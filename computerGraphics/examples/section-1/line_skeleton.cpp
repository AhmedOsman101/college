// Section 1 — the smallest BGI program (Section-1.md:178-194).
//
// The material's `int gm;` is left uninitialized, which SDL_bgi reads before
// it looks at DETECT, landing on its 800x600 default. `VGAHI` is the BGI mode
// constant for 640x480, the resolution every example in this course assumes.
#include <graphics.h>
#include <conio.h>

int main() {
  int gd = DETECT;
  int gm = VGAHI;
  initgraph(&gd, &gm, "");

  line(100, 100, 300, 200);

  refresh();
  getch();
  closegraph();
  return 0;
}

// compat/selftest.cpp — must fail to compile before the compat header exists.
#include <graphics.h>
#include "conio.h"

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

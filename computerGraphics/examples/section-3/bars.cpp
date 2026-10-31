// Section 3 — bar() versus rectangle(), and floodfill() inside an outline
// (Section-3.md:27-83).
#include <graphics.h>
#include <conio.h>

int main() {
  int gd = DETECT;
  int gm = VGAHI;
  initgraph(&gd, &gm, "");

  setbkcolor(BLACK);
  cleardevice();
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

  // bar(): filled, no outline of its own.
  setfillstyle(SOLID_FILL, BLUE);
  bar(60, 100, 160, 300);

  // A bordered bar is bar() plus rectangle() with the same coordinates.
  setfillstyle(SOLID_FILL, GREEN);
  bar(220, 100, 320, 300);
  setcolor(WHITE);
  rectangle(220, 100, 320, 300);

  // rectangle() alone: four lines, empty inside.
  setcolor(LIGHTRED);
  rectangle(380, 100, 480, 300);

  // Hatch fill seeded in the middle of a plain outline.
  setcolor(WHITE);
  rectangle(380, 340, 560, 440);
  setfillstyle(HATCH_FILL, GREEN);
  floodfill(470, 390, WHITE);

  setcolor(WHITE);
  outtextxy(60, 320, "bar()");
  outtextxy(190, 320, "bar()+rectangle()");
  outtextxy(370, 320, "rectangle()");
  outtextxy(380, 450, "floodfill HATCH_FILL");

  refresh();
  getch();
  closegraph();
  return 0;
}

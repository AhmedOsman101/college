// Section 2 — circle(), arc() and sector() (Section-2.md:95-144).
#include <graphics.h>
#include <conio.h>

int main() {
  int gd = DETECT;
  int gm = VGAHI;
  initgraph(&gd, &gm, "");

  setbkcolor(BLACK);
  cleardevice();
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

  // Left: three concentric circles.
  setcolor(GREEN);
  circle(150, 240, 50);
  circle(150, 240, 100);
  circle(150, 240, 140);

  // Right: the arc table from the material.
  setcolor(YELLOW);
  arc(420, 110, 0, 360, 70);      // full circle
  setcolor(CYAN);
  arc(420, 110, 0, 180, 55);      // upper half
  setcolor(LIGHTRED);
  arc(420, 110, 45, 90, 40);      // quarter arc, first quadrant
  setcolor(MAGENTA);
  arc(420, 110, 90, 90, 90);      // single point, not a line

  // Bottom right: a filled quarter ellipse.
  setcolor(WHITE);
  setfillstyle(SOLID_FILL, BLUE);
  sector(420, 380, 0, 90, 130, 70);

  setcolor(WHITE);
  outtextxy(90, 40, "circle x3");
  outtextxy(370, 210, "arc 0-360 / 0-180 / 45-90 / 90-90");
  outtextxy(360, 470, "sector 0-90");

  refresh();
  getch();
  closegraph();
  return 0;
}

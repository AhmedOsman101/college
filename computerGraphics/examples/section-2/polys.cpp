// Section 2 — drawpoly() and fillpoly() (Section-2.md:166-199).
#include <graphics.h>
#include <conio.h>

int main() {
  int gd = DETECT;
  int gm = VGAHI;
  initgraph(&gd, &gm, "");

  setbkcolor(BLACK);
  cleardevice();
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

  // Closed triangle: the first vertex repeats, so number == 4.
  int tri[] = {140, 60, 40, 240, 240, 240, 140, 60};
  setcolor(WHITE);
  drawpoly(4, tri);

  // Same triangle with number == 3: the last edge is missing.
  int open[] = {420, 60, 320, 240, 520, 240};
  setcolor(LIGHTRED);
  drawpoly(3, open);

  // Filled triangle.
  int filled[] = {140, 300, 40, 460, 240, 460, 140, 300};
  setcolor(WHITE);
  setfillstyle(SOLID_FILL, GREEN);
  fillpoly(4, filled);

  // Filled square, for comparison with rectangle().
  int square[] = {340, 300, 500, 300, 500, 460, 340, 460, 340, 300};
  setfillstyle(SOLID_FILL, MAGENTA);
  fillpoly(5, square);

  setcolor(WHITE);
  outtextxy(30, 260, "drawpoly(4) closed");
  outtextxy(340, 260, "drawpoly(3) open");
  outtextxy(40, 470, "fillpoly");
  outtextxy(400, 470, "fillpoly square");

  refresh();
  getch();
  closegraph();
  return 0;
}

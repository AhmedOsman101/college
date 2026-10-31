// Task 1, slide 1 — pie chart of the Earth's crust (Tasks/Task-1.md:49-95).
#include <graphics.h>
#include <conio.h>

int main() {
  int gd = DETECT;
  int gm = VGAHI;
  initgraph(&gd, &gm, "");

  setbkcolor(BLACK);
  cleardevice();

  int cx = 320;   // centre of the ellipse
  int cy = 260;
  int rx = 230;   // horizontal radius
  int ry = 150;   // vertical radius

  // Slice 1: iron, 0 to 40 degrees
  setfillstyle(SOLID_FILL, RED);
  sector(cx, cy, 0, 40, rx, ry);

  // Slice 2: silicon, 40 to 140 degrees
  setfillstyle(SOLID_FILL, YELLOW);
  sector(cx, cy, 40, 140, rx, ry);

  // Slice 3: aluminium, 140 to 180 degrees
  setfillstyle(SOLID_FILL, GREEN);
  sector(cx, cy, 140, 180, rx, ry);

  // Slice 4: oxygen, 180 to 360 degrees
  setfillstyle(SOLID_FILL, BROWN);
  sector(cx, cy, 180, 360, rx, ry);

  // Title and labels
  setcolor(WHITE);
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
  outtextxy(140, 60, "Elements available in the Earth's crust");
  outtextxy(320, 130, "silicon");
  outtextxy(560, 240, "iron");
  outtextxy(300, 420, "oxygen");
  outtextxy(120, 300, "aluminium");

  refresh();
  getch();
  closegraph();
  return 0;
}

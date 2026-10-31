// Section 3 — bar3d() depth/topflag and settextstyle() directions
// (Section-3.md:96-127, 194-222).
#include <graphics.h>
#include <conio.h>

int main() {
  int gd = DETECT;
  int gm = VGAHI;
  initgraph(&gd, &gm, "");

  setbkcolor(BLACK);
  cleardevice();
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

  // Three bars showing the effect of depth and topflag.
  setfillstyle(SOLID_FILL, LIGHTCYAN);
  bar3d(60, 300, 140, 400, 0, 0);     // flat
  bar3d(180, 300, 260, 400, 20, 0);   // depth, open top
  bar3d(300, 300, 380, 400, 20, 1);   // depth, closed top

  setcolor(WHITE);
  outtextxy(60, 415, "depth 0");
  outtextxy(175, 415, "depth 20, topflag 0");
  outtextxy(310, 415, "depth 20, topflag 1");

  // Text: horizontal label above a vertical one.
  setcolor(WHITE);
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
  outtextxy(420, 60, "Sales by year");

  settextstyle(DEFAULT_FONT, VERT_DIR, 2);
  outtextxy(440, 380, "Units");

  refresh();
  getch();
  closegraph();
  return 0;
}

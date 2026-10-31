// Section 2 — setfillstyle() and floodfill() (Section-2.md:251-282).
#include <graphics.h>
#include <conio.h>

int main() {
  int gd = DETECT;
  int gm = VGAHI;
  initgraph(&gd, &gm, "");

  setbkcolor(BLACK);
  cleardevice();
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

  // Circle with a solid cyan interior, seeded from the centre.
  setcolor(WHITE);
  circle(180, 220, 120);
  setfillstyle(SOLID_FILL, CYAN);
  floodfill(180, 220, WHITE);

  // Rectangle with a hatch interior, seeded from its middle.
  setcolor(WHITE);
  rectangle(360, 100, 560, 250);
  setfillstyle(HATCH_FILL, GREEN);
  floodfill(460, 175, WHITE);

  // Empty fill: outline only, the interior keeps the background.
  setcolor(YELLOW);
  circle(460, 370, 80);
  setfillstyle(EMPTY_FILL, YELLOW);
  floodfill(460, 370, YELLOW);

  setcolor(WHITE);
  outtextxy(90, 40, "floodfill SOLID_FILL");
  outtextxy(360, 60, "floodfill HATCH_FILL");
  outtextxy(410, 470, "EMPTY_FILL");

  refresh();
  getch();
  closegraph();
  return 0;
}

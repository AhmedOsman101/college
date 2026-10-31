// Section 2 — ellipse() and fillellipse() (Section-2.md:59-93).
#include <graphics.h>
#include <conio.h>

int main() {
  int gd = DETECT;
  int gm = VGAHI;
  initgraph(&gd, &gm, "");

  setbkcolor(BLACK);
  cleardevice();

  // Full outline, then the upper half of a smaller one.
  setcolor(YELLOW);
  ellipse(320, 240, 0, 360, 200, 120);

  setcolor(CYAN);
  ellipse(320, 240, 0, 180, 120, 80);

  // Filled variant: red interior, white outline — drawn lower so both show.
  setcolor(WHITE);
  setfillstyle(SOLID_FILL, RED);
  fillellipse(320, 400, 120, 50);

  setcolor(WHITE);
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
  outtextxy(20, 20, "ellipse(YELLOW) + half ellipse(CYAN) + fillellipse(RED)");

  refresh();
  getch();
  closegraph();
  return 0;
}

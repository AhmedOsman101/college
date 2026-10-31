// Section 2 — the worked composite example (Section-2.md:284-325).
#include <graphics.h>
#include <conio.h>

int main() {
  int gd = DETECT;
  int gm = VGAHI;
  initgraph(&gd, &gm, "");

  setbkcolor(BLACK);
  cleardevice();

  // Outer frame
  setcolor(YELLOW);
  rectangle(80, 60, 560, 420);

  // Circle with an outline, then a filled inner disc
  setcolor(RED);
  circle(320, 240, 120);
  setfillstyle(SOLID_FILL, BLUE);
  floodfill(320, 240, RED);

  // Label the picture
  setcolor(WHITE);
  outtextxy(250, 400, "Blue disc in a red ring");

  refresh();
  getch();
  closegraph();
  return 0;
}

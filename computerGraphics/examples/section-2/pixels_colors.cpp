// Section 2 — putpixel(), setcolor() and the 16-colour BGI palette
// (Section-2.md:201-249).
#include <graphics.h>
#include <conio.h>

int main() {
  int gd = DETECT;
  int gm = VGAHI;
  initgraph(&gd, &gm, "");

  setbkcolor(BLACK);
  cleardevice();
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

  // 100 blue pixels along the diagonal.
  for (int i = 0; i < 100; i++) {
    putpixel(40 + i, 80 + i, BLUE);
  }

  // The same circle in four colours.
  circle(160, 300, 70);
  setcolor(RED);
  circle(320, 300, 70);
  setcolor(GREEN);
  circle(480, 300, 70);
  setcolor(YELLOW);
  circle(480, 300, 40);

  // The palette itself: a swatch per index, 0..15.
  for (int c = 0; c < 16; c++) {
    setfillstyle(SOLID_FILL, c);
    bar(40 + c * 35, 420, 40 + c * 35 + 30, 450);
  }

  setcolor(WHITE);
  outtextxy(40, 40, "putpixel diagonal, three circles, palette 0-15");

  refresh();
  getch();
  closegraph();
  return 0;
}

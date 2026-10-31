// Section 3 — the labelled bar chart (Section-3.md:129-192).
#include <graphics.h>
#include <conio.h>
#include <cstdio>

int main() {
  int gd = DETECT;
  int gm = VGAHI;
  initgraph(&gd, &gm, "");

  setbkcolor(BLACK);
  cleardevice();

  int values[4] = {120, 180, 90, 210};
  int colors[4] = {BLUE, GREEN, RED, MAGENTA};
  int baseY = 400;          // y of the zero line
  int scale = 1;            // 1 pixel per unit

  // Axes
  setcolor(WHITE);
  line(80, 100, 80, baseY);        // y axis
  line(80, baseY, 560, baseY);     // x axis

  // One bar per value, 80 pixels wide, 110 pixels apart
  for (int i = 0; i < 4; i++) {
    int left = 110 + i * 110;
    int top = baseY - values[i] * scale;
    setfillstyle(SOLID_FILL, colors[i]);
    bar(left, top, left + 80, baseY);

    // Value above the bar
    char label[10];
    std::sprintf(label, "%d", values[i]);
    setcolor(WHITE);
    outtextxy(left + 30, top - 20, label);
  }

  // Axis titles
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
  outtextxy(250, 420, "Year");
  settextstyle(DEFAULT_FONT, VERT_DIR, 1);
  outtextxy(40, 300, "Units");

  refresh();
  getch();
  closegraph();
  return 0;
}

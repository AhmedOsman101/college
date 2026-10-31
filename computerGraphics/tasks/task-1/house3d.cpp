// Task 1, slide 2 — 3D house from filled polygons, back faces first
// (Tasks/Task-1.md:121-161).
#include <graphics.h>
#include <conio.h>

int main() {
  int gd = DETECT;
  int gm = VGAHI;
  initgraph(&gd, &gm, "");

  setbkcolor(BLACK);
  cleardevice();

  // 1. Far roof plane, drawn first so it sits behind everything
  int farRoof[] = {120, 230, 200, 150, 360, 90, 280, 170};
  setfillstyle(SOLID_FILL, DARKGRAY);
  fillpoly(4, farRoof);

  // 2. Right side wall
  int side[] = {280, 380, 440, 320, 440, 170, 280, 230};
  setfillstyle(SOLID_FILL, CYAN);
  fillpoly(4, side);

  // 3. Near roof plane
  int nearRoof[] = {200, 150, 280, 230, 440, 170, 360, 90};
  setfillstyle(SOLID_FILL, DARKGRAY);
  fillpoly(4, nearRoof);

  // 4. Front gable, a pentagon
  int front[] = {120, 380, 120, 230, 200, 150, 280, 230, 280, 380};
  setfillstyle(SOLID_FILL, CYAN);
  fillpoly(5, front);

  // 5. Window on the front face
  setfillstyle(SOLID_FILL, BLACK);
  bar(150, 265, 205, 320);

  // 6. Door on the side wall
  bar(330, 290, 375, 380);

  refresh();
  getch();
  closegraph();
  return 0;
}

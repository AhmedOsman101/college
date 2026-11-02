// NOTE: I'm running Linux, some headers might look different from the Windows version.
#include <SDL2/SDL_bgi.h> // Comment this line if it gives you an error
#include <graphics.h>
#include <conio.h>

// Defaults to white text
void writeText(const char *text, int x, int y) {
  setcolor(WHITE);
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
  outtextxy(x, y, text);
}
// override the default color
void writeText(const char *text, int x, int y, int color) {
  setcolor(color);
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
  outtextxy(x, y, text);
}

// I know it's overkill but who hates a helper function ;)
void filledSector(int x, int y, int startAngle, int endAngle, int radiusX, int radiusY, int color) {
  setfillstyle(SOLID_FILL, color);
  sector(x, y, startAngle, endAngle, radiusX, radiusY);
}

int main() {
  int windowId = initwindow(800, 600);

  // set background color
  setbkcolor(BLACK);
  cleardevice();

  // Title
  writeText("Elements available in the Earth's crust", 230, 60);

  // Center of the ellpise
  int cx = 400, cy = 300;
  int rx = 230;   // Horizontal radius
  int ry = 150;   // Vertical radius

  // Slice 1: iron, 0 to 40 degrees
  writeText("iron", 640, 230);
  filledSector(cx, cy, 0, 40, rx, ry, RED);

  // Slice 2: silicon, 40 to 160 degrees
  writeText("silicon", 340, 120);
  filledSector(cx, cy, 40, 160, rx, ry, YELLOW);

  // Slice 3: aluminium, 160 to 220 degrees
  writeText("aluminium", 50, 300);
  filledSector(cx, cy, 160, 220, rx, ry, GREEN);

  // Slice 4: oxygen, 220 to 360 degrees
  writeText("oxygen", 400, 480);
  // I didn't find that dark yellow color anywhere
  filledSector(cx, cy, 220, 360, rx, ry, BROWN);

  // cleanup and close the window
  refresh();
  getch();
  closewindow(windowId);
  return 0;
}

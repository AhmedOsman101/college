// NOTE: I'm running Linux, some headers might look different from the Windows version.
#include <SDL2/SDL_bgi.h> // Comment this line if it gives you an error
#include <graphics.h>
#include <conio.h>

void filledRectangle(int left, int top, int width, int height, int color) {
  // set the color and style
  setfillstyle(SOLID_FILL, color);
  // width = left + width, height = top + height
  rectangle(left, top, width + left, height + top);
  // Use bar for filling the rectangle
  bar(left, top, width + left, height + top);
}

void filledPolygon(int vertices, int points[], int color) {
  setfillstyle(SOLID_FILL, color);
  fillpoly(vertices, points);
}

int main() {
  int windowId = initwindow(920, 480);

  // set background color
  setbkcolor(BLACK);
  cleardevice();

  // front wall
  filledRectangle(360, 190, 360, 190, CYAN);
  // front door
  filledRectangle(530, 285, 50, 90, BLACK);

  // roof
  int roof[] = {
    260, 100,  // top left
    630, 100,  // top right
    720, 190, // bottom right
    360, 190,  // bottom left
    260, 100,  // top left
  };
  filledPolygon(5, roof, LIGHTGRAY);

  // roof side
  int roofSide[] = {
    260, 100,  // top
    360, 190, // bottom right
    160, 210, // bottom left
    260, 100,  // top
  };
  filledPolygon(4, roofSide, CYAN);

  // sideWall
  int sideWall[] = {
    180, 208, // top left
    360, 190, // top right
    360, 380, // bottom right
    180, 310, // bottom left
    180, 208, // top left
  };
  filledPolygon(5, sideWall, CYAN);

  // sideWindow
  int sideWindow[] = {
    240, 215, // top left
    300, 225, // top right
    300, 285, // bottom right
    240, 275, // bottom left
    240, 215, // top left
  };
  filledPolygon(5, sideWindow, BLACK);

  // cleanup and close the window
  refresh();
  getch();
  closewindow(windowId);
  return 0;
}

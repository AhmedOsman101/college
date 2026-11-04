#include <SDL2/SDL_bgi.h>
#include <graphics.h>
#include <conio.h>

void rect(int left, int top, int width, int height) {
  // width = left + width, height = top + height
  rectangle(left, top, width + left, height + top);
}

int main() {
  int windowId = initwindow(1200, 700);

  // background color
  setbkcolor(GREEN);
  cleardevice();
  
  // center line
  line(600, 0, 600, 700);

  // center circle
  circle(600, 350, 50);

  // center dot
  setfillstyle(SOLID_FILL, WHITE);
  fillellipse(600, 350, 5, 5);

  // small rectangle left
  int smallRectLeft[] = {
    0, 300, // top left
    100, 300, // top right
    100, 400, // bottom right
    0, 400 // bottom left
  };
  drawpoly(4, smallRectLeft);
  // big rectangle left
  int bigRectLeft[] = {
    0, 250, // top left
    150, 250, // top right
    150, 450, // bottom right
    0, 450 // bottom left
  };
  drawpoly(4, bigRectLeft);

  // small arc left
  arc(150, 350, 270, 90, 25);
  
  // small rectangle right
  int smallRectRight[] = {
    1200, 300, // top left
    1100, 300, // top right
    1100, 400, // bottom right
    1200, 400 // bottom left
  };
  drawpoly(4, smallRectRight);

  // big rectangle right
  int bigRectRight[] = {
    1200, 250, // top left
    1050, 250, // top right
    1050, 450, // bottom right
    1200, 450 // bottom left
  };
  drawpoly(4, bigRectRight);

  // small arc right
  arc(1050, 350, 90, 270, 25);
  
  // cleanup and close the window
  getch();
  closewindow(windowId);
  return 0;
}

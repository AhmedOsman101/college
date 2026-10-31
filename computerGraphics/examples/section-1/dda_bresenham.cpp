// Section 1 — DDA and Bresenham on the same line, compared pixel by pixel.
//
// The lecture line (2,2) -> (10,6) has slope exactly 0.5, so both algorithms
// produce the same nine pixels (Section-1.md:121-131). Each pixel is printed
// as it is plotted, and the line is also drawn enlarged so the stepping is
// visible on screen.
#include <graphics.h>
#include <conio.h>

#include <algorithm>
#include <cmath>
#include <cstdio>

namespace {

const int kX1 = 2, kY1 = 2, kX2 = 10, kY2 = 6;
const int kScale = 22;   // enlargement factor for the on-screen copy
const int kOriginX = 60;
const int kOriginY = 60;

// One enlarged pixel: a kScale-square block with a 1px border.
void block(int x, int y, int color) {
  int left = kOriginX + x * kScale;
  int top = kOriginY + y * kScale;
  setfillstyle(SOLID_FILL, color);
  bar(left, top, left + kScale - 2, top + kScale - 2);
}

// Section-1.md:133-149 — the DDA from the lecture.
void ddaLine(int x1, int y1, int x2, int y2, bool plot) {
  int dx = x2 - x1;
  int dy = y2 - y1;
  int steps = std::max(std::abs(dx), std::abs(dy));
  float xinc = static_cast<float>(dx) / steps;
  float yinc = static_cast<float>(dy) / steps;
  float x = static_cast<float>(x1);
  float y = static_cast<float>(y1);

  for (int i = 0; i <= steps; i++) {
    int px = static_cast<int>(std::round(x));
    int py = static_cast<int>(std::round(y));
    std::printf("(%d,%d) ", px, py);
    if (plot) putpixel(px, py, RED);
    x += xinc;
    y += yinc;
  }
  std::printf("\n");
}

// Integer Bresenham in decision-parameter form, p = 2dy - dx.
//
// The tie-break matters here: on this line every step lands exactly on a pixel
// corner, so an error-accumulator variant that tests `e2 < dx` keeps y on the
// previous row and prints (3,2) where DDA prints (3,3). The lecture table says
// both algorithms agree, which is true for this formulation.
void bresenhamLine(int x1, int y1, int x2, int y2, bool plot) {
  int dx = std::abs(x2 - x1);
  int dy = std::abs(y2 - y1);
  int sx = (x1 < x2) ? 1 : -1;
  int sy = (y1 < y2) ? 1 : -1;
  int p = 2 * dy - dx;

  std::printf("(%d,%d) ", x1, y1);
  if (plot) putpixel(x1, y1, GREEN);

  while (x1 != x2) {
    x1 += sx;
    if (p < 0) {
      p += 2 * dy;
    } else {
      y1 += sy;
      p += 2 * (dy - dx);
    }
    std::printf("(%d,%d) ", x1, y1);
    if (plot) putpixel(x1, y1, GREEN);
  }
  std::printf("\n");
}

}  // namespace

int main() {
  int gd = DETECT;
  int gm = VGAHI;
  initgraph(&gd, &gm, "");

  setbkcolor(BLACK);
  cleardevice();

  std::printf("DDA       : ");
  ddaLine(kX1, kY1, kX2, kY2, false);
  std::printf("Bresenham : ");
  bresenhamLine(kX1, kY1, kX2, kY2, false);

  // Enlarged view: DDA pixels at the original coordinates, red.
  setcolor(DARKGRAY);
  for (int x = 0; x <= 10; x++)
    for (int y = 0; y <= 6; y++)
      rectangle(kOriginX + x * kScale, kOriginY + y * kScale,
                kOriginX + x * kScale + kScale - 2, kOriginY + y * kScale + kScale - 2);

  ddaLine(kX1, kY1, kX2, kY2, false);
  {
    // Re-run without the stdout noise: draw the nine pixels as blocks.
    int dx = kX2 - kX1, dy = kY2 - kY1;
    int steps = std::max(std::abs(dx), std::abs(dy));
    float xinc = static_cast<float>(dx) / steps;
    float yinc = static_cast<float>(dy) / steps;
    float x = static_cast<float>(kX1), y = static_cast<float>(kY1);
    for (int i = 0; i <= steps; i++) {
      block(static_cast<int>(std::round(x)), static_cast<int>(std::round(y)), RED);
      x += xinc; y += yinc;
    }
  }

  setcolor(WHITE);
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
  outtextxy(60, 30, "DDA (red) = Bresenham (green): (2,2)..(10,6)");

  refresh();
  getch();
  closegraph();
  return 0;
}

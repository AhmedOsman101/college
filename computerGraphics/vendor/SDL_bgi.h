// ==========================================================================
//  ANNOTATED COPY of SDL_bgi.h — generated, do not edit by hand.
//  Parameter names and descriptions come from upstream src/SDL_bgi.c
//  (SDL_bgi 3.0.0), plus curated @param/notes text for the course API.
//  Regenerate with computerGraphics/tools/annotate-sdlbgi.py.
// ==========================================================================

// SDL_bgi.h	-*- C -*-

// SDL_bgi is a graphics library (GRAPHICS.H) for C, C++, WebAssembly,
// and Python. It's based on SDL2 and it's portable on many platforms.
// Easy to use, pretty fast, useful for porting old programs
// and for teaching introductory computer graphics.
//
// By Guido Gonzato, PhD
// Automatic refresh patch, CHR font support:
// Marco Diego Aurélio Mesquita
// Latest update: December 12, 2022

// ZLib License

/*

Copyright (c) 2014-2022 Guido Gonzato, PhD

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

*/

#ifndef _SDL_BGI_H
#define _SDL_BGI_H

#ifndef __GRAPHICS_H
#define __GRAPHICS_H

// SDL2 stuff
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <stdio.h>   // for fprintf()
#include <stdint.h>  // for uint* types
#include <stdlib.h>  // for exit(), calloc()
#include <math.h>    // for sin(), cos()
#include <string.h>  // for strlen(), memcpy()

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define SDL_BGI_VERSION 3.0.0

enum { NOPE, YEAH } ;
#define BGI_WINTITLE_LEN 512 // more than enough

// number of concurrent windows that can be created

#define NUM_BGI_WIN 16

// everything gets drawn here

extern SDL_Window   *bgi_window;
extern SDL_Renderer *bgi_renderer;
extern SDL_Texture  *bgi_texture;
// !!! deprecated! Use getpalettesize() instead.
// extern Uint32        PALETTE_SIZE;

// available visual pages

#define VPAGES 4

// BGI fonts

enum {
  DEFAULT_FONT,      // 8x8 bitmap
  TRIPLEX_FONT,      // trip.h
  SMALL_FONT,        // litt.h
  SANS_SERIF_FONT,   // sans.h
  GOTHIC_FONT,       // goth.h
  SCRIPT_FONT,       // scri.h
  SIMPLEX_FONT,      // simp.h
  TRIPLEX_SCR_FONT,  // tscr.h
  COMPLEX_FONT,      // lcom.h
  EUROPEAN_FONT,     // euro.h
  BOLD_FONT,         // bold.h
  LAST_SPEC_FONT
};

enum { HORIZ_DIR, VERT_DIR };

#define USER_CHAR_SIZE 0

enum {
  LEFT_TEXT, CENTER_TEXT, RIGHT_TEXT,
  BOTTOM_TEXT = 0, TOP_TEXT = 2
};

// BGI colours, including CGA and EGA palettes

enum {
  BLACK        = 0,                         EGA_BLACK        = 0,
  BLUE         = 1,                         EGA_BLUE         = 1,
  GREEN        = 2,  CGA_GREEN        = 2,  EGA_GREEN        = 2,
  CYAN         = 3,  CGA_CYAN         = 3,  EGA_CYAN         = 3,
  RED          = 4,  CGA_RED          = 4,  EGA_RED          = 4,
  MAGENTA      = 5,  CGA_MAGENTA      = 5,  EGA_MAGENTA      = 5,
  BROWN        = 6,  CGA_BROWN        = 6,  EGA_BROWN        = 6,
  LIGHTGRAY    = 7,  CGA_LIGHTGRAY    = 7,  EGA_LIGHTGRAY    = 7,
  DARKGRAY     = 8,                         EGA_DARKGRAY     = 8,
  LIGHTBLUE    = 9,                         EGA_LIGHTBLUE    = 9,
  LIGHTGREEN   = 10, CGA_LIGHTGREEN   = 10, EGA_LIGHTGREEN   = 10,
  LIGHTCYAN    = 11, CGA_LIGHTCYAN    = 11, EGA_LIGHTCYAN    = 11,
  LIGHTRED     = 12, CGA_LIGHTRED     = 12, EGA_LIGHTRED     = 12,
  LIGHTMAGENTA = 13, CGA_LIGHTMAGENTA = 13, EGA_LIGHTMAGENTA = 13,
  YELLOW       = 14, CGA_YELLOW       = 14, EGA_YELLOW       = 14,
  WHITE        = 15, CGA_WHITE        = 15, EGA_WHITE        = 15,
  MAXCOLORS    = 15
};

// ARGB colours, set by COLOR (), COLOR32 (), and RGBPALETTE ()

enum {
  ARGB_FG_COL   = 16,
  ARGB_BG_COL   = 17,
  ARGB_FILL_COL = 18,
  ARGB_TMP_COL  = 19,
  TMP_COLORS    = 4
};

// line style, thickness, and drawing mode

enum { NORM_WIDTH = 1, THICK_WIDTH = 3 };

enum { SOLID_LINE, DOTTED_LINE, CENTER_LINE, DASHED_LINE, USERBIT_LINE };

enum { COPY_PUT, XOR_PUT, OR_PUT, AND_PUT, NOT_PUT };

// fill styles

enum {
  EMPTY_FILL,       // fills area in background color
  SOLID_FILL,       // fills area in solid fill color
  LINE_FILL,        // --- fill
  LTSLASH_FILL,     // /// fill
  SLASH_FILL,       // /// fill with thick lines
  BKSLASH_FILL,     // \\\ fill with thick lines
  LTBKSLASH_FILL,   // \\\ fill
  HATCH_FILL,       // light hatch fill
  XHATCH_FILL,      // heavy cross hatch fill
  INTERLEAVE_FILL,  // interleaving line fill
  WIDE_DOT_FILL,    // Widely spaced dot fill
  CLOSE_DOT_FILL,   // Closely spaced dot fill
  USER_FILL         // user defined fill
};

// mouse events - compatible with WinBGIm

#define WM_MOUSEMOVE       SDL_MOUSEMOTION

#define WM_LBUTTONDOWN     SDL_BUTTON_LEFT
#define WM_LBUTTONUP       SDL_MOUSEBUTTONUP   + SDL_BUTTON_LEFT
#define WM_LBUTTONDBLCLK   SDL_MOUSEBUTTONDOWN + SDL_BUTTON_LEFT + 2

#define WM_MBUTTONDOWN     SDL_BUTTON_MIDDLE
#define WM_MBUTTONUP       SDL_MOUSEBUTTONUP   + 10*SDL_BUTTON_MIDDLE
#define WM_MBUTTONDBLCLK   SDL_MOUSEBUTTONDOWN + 10*SDL_BUTTON_MIDDLE + 2

#define WM_RBUTTONDOWN     SDL_BUTTON_RIGHT
#define WM_RBUTTONUP       SDL_MOUSEBUTTONUP   + 20*SDL_BUTTON_RIGHT
#define WM_RBUTTONDBLCLK   SDL_MOUSEBUTTONDOWN + 20*SDL_BUTTON_RIGHT + 2

#define WM_WHEEL           SDL_MOUSEWHEEL
#define WM_WHEELUP         SDL_BUTTON_RIGHT + 1
#define WM_WHEELDOWN       SDL_BUTTON_RIGHT + 2

// keys
#define KEY_HOME        SDLK_HOME
#define KEY_LEFT        SDLK_LEFT
#define KEY_UP          SDLK_UP
#define KEY_RIGHT       SDLK_RIGHT
#define KEY_DOWN        SDLK_DOWN
#define KEY_PGUP        SDLK_PAGEUP
#define KEY_PGDN        SDLK_PAGEDOWN
#define KEY_END         SDLK_END
#define KEY_INSERT      SDLK_INSERT
#define KEY_DELETE      SDLK_DELETE
#define KEY_F1          SDLK_F1
#define KEY_F2          SDLK_F2
#define KEY_F3          SDLK_F3
#define KEY_F4          SDLK_F4
#define KEY_F5          SDLK_F5
#define KEY_F6          SDLK_F6
#define KEY_F7          SDLK_F7
#define KEY_F8          SDLK_F8
#define KEY_F9          SDLK_F9
#define KEY_F10         SDLK_F10
#define KEY_F11         SDLK_F11
#define KEY_F12         SDLK_F12
#define KEY_CAPSLOCK    SDLK_CAPSLOCK
#define KEY_LEFT_CTRL   SDLK_LCTRL
#define KEY_RIGHT_CTRL  SDLK_RCTRL
#define KEY_LEFT_SHIFT  SDLK_LSHIFT
#define KEY_RIGHT_SHIFT SDLK_RSHIFT
#define KEY_LEFT_ALT    SDLK_LALT
#define KEY_RIGHT_ALT   SDLK_RALT
#define KEY_ALT_GR      SDLK_MODE
#define KEY_LGUI        SDLK_LGUI
#define KEY_RGUI        SDLK_RGUI
#define KEY_MENU        SDLK_MENU
#define KEY_TAB         SDLK_TAB
#define KEY_BS          SDLK_BACKSPACE
#define KEY_RET         SDLK_RETURN
#define KEY_PAUSE       SDLK_PAUSE
#define KEY_SCR_LOCK    SDLK_SCROLLOCK
#define KEY_ESC         SDLK_ESCAPE

#define QUIT            SDL_QUIT

// graphics modes. Expanded from the original GRAPHICS.H

enum {
  DETECT = -1,
  SDL = 0,
  // all modes @ 320x200
  SDL_320x200 = 1, SDL_CGALO = 1, CGA = 1, CGAC0 = 1, CGAC1 = 1,
  CGAC2 = 1, CGAC3 = 1, MCGAC0 = 1, MCGAC1 = 1, MCGAC2 = 1,
  MCGAC3 = 1, ATT400C0 = 1, ATT400C1 = 1, ATT400C2 = 1, ATT400C3 = 1,
  // all modes @ 640x200
  SDL_640x200 = 2, SDL_CGAHI = 2, CGAHI = 2, MCGAMED = 2,
  EGALO = 2, EGA64LO = 2,
  // all modes @ 640x350
  SDL_640x350 = 3, SDL_EGA = 3, EGA = 3, EGAHI = 3,
  EGA64HI = 3, EGAMONOHI = 3,
  // all modes @ 640x480
  SDL_640x480 = 4, SDL_VGA = 4, VGA = 4, MCGAHI = 4, VGAHI = 4,
  IBM8514LO = 4,
  // all modes @ 720x348
  SDL_720x348 = 5, SDL_HERC = 5,
  // all modes @ 720x350
  SDL_720x350 = 6, SDL_PC3270 = 6, HERCMONOHI = 6,
  // all modes @ 800x600
  SDL_800x600 = 7, SDL_SVGALO = 7, SVGA = 7,
  // all modes @ 1024x768
  SDL_1024x768 = 8, SDL_SVGAMED1 = 8,
  // all modes @ 1152x900
  SDL_1152x900 = 9, SDL_SVGAMED2 = 9,
  // all modes @ 1280x1024
  SDL_1280x1024 = 10, SDL_SVGAHI = 10,
  // all modes @ 1366x768
  SDL_1366x768 = 11, SDL_WXGA = 11,
  // other
  SDL_USER = 12, SDL_FULLSCREEN = 13
};

// error messages
enum graphics_errors {
  grOk               =   0,
  grNoInitGraph      =  -1,
  grNotDetected      =  -2,
  grFileNotFound     =  -3,
  grInvalidDriver    =  -4,
  grNoLoadMem        =  -5,
  grNoScanMem        =  -6,
  grNoFloodMem       =  -7,
  grFontNotFound     =  -8,
  grNoFontMem        =  -9,
  grInvalidMode      = -10,
  grError            = -11,
  grIOerror          = -12,
  grInvalidFont      = -13,
  grInvalidFontNum   = -14,
  grInvalidVersion   = -18
};

// libXbgi compatibility

#define X11_CGALO       SDL_CGALO
#define X11_CGAHI       SDL_CGAHI
#define X11_EGA         SDL_EGA
#define X11             SDL
#define X11_VGA         SDL_VGA
#define X11_640x480     SDL_640x480
#define X11_HERC        SDL_HERC
#define X11_PC3270      SDL_PC3270
#define X11_SVGALO      SDL_SVGALO
#define X11_800x600     SDL_800x600
#define X11_SVGAMED1    SDL_SVGAMED1
#define X11_1024x768    SDL_1024x768
#define X11_SVGAMED2    SDL_SVGAMED2
#define X11_1152x900    SDL_1152x900
#define X11_SVGAHI      SDL_SVGAHI
#define X11_1280x1024   SDL_1280x1024
#define X11_WXGA        SDL_WXGA
#define X11_1366x768    SDL_1366x768
#define X11_USER        SDL_USER
#define X11_FULLSCREEN  SDL_FULLSCREEN

// structs

struct arccoordstype {
  int x;
  int y;
  int xstart;
  int ystart;
  int xend;
  int yend;
};

struct date {
  int da_year;
  int da_day;
  int da_mon;
};

struct fillsettingstype {
  int pattern;
  int color;
};

struct linesettingstype {
  int linestyle;
  unsigned int upattern;
  int thickness;
};

struct palettetype {
  unsigned char size;
  Uint32 colors[MAXCOLORS + 1];
};

// SDL_bgi extension
struct rgbpalettetype {
  Uint32 size;
  Uint32 *colors;
};

struct textsettingstype {
  int font;
  int direction;
  int charsize;
  int horiz;
  int vert;
};

struct viewporttype {
  int left;
  int top;
  int right;
  int bottom;
  int clip;
};

// prototypes - standard BGI
// let's make them C++ compatible

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Draws a circular arc centered at (x, y), with a radius given by radius,
 * traveling from stangle to endangle.
 *
 * @param x centre x, pixels
 * @param y centre y, pixels
 * @param stangle start angle, degrees, counter-clockwise from 3 o'clock
 * @param endangle end angle, degrees; equal to stangle draws one pixel, not a
 *                 line
 * @param radius radius in pixels
 *
 * Angles run counter-clockwise while y still grows downward.
 */
void arc (int x, int y, int stangle, int endangle, int radius);
/**
 * Draws a three-dimensional, filled-in rectangle (bar), using the current
 * fill colour and fill pattern.
 *
 * @param left x of the front face, left edge
 * @param top y of the front face, top edge
 * @param right x of the front face, right edge
 * @param bottom y of the front face, bottom edge
 * @param depth 3D offset in pixels; 0 gives a flat bar
 * @param topflag non-zero draws the top face; 0 leaves the bar open
 *
 * depth 20 / topflag 0 looks like an open box; depth 20 / topflag 1 looks
 * like a solid block.
 */
void bar3d (int left, int top, int right, int bottom, int depth, int topflag);
/**
 * Draws a filled-in rectangle (bar), using the current fill colour and fill
 * pattern.
 *
 * @param left x of the left edge, pixels
 * @param top y of the top edge, pixels
 * @param right x of the right edge, pixels
 * @param bottom y of the bottom edge, pixels
 *
 * Filled rectangle that draws NO outline — the fill pattern is the edge. For
 * a border, follow it with rectangle() using the same coordinates.
 */
void bar (int left, int top, int right, int bottom);
/**
 * Draws a circle of the given radius at (x, y).
 *
 * @param x centre x, pixels
 * @param y centre y, pixels
 * @param radius radius in pixels
 *
 * Outline only, in the current colour. Not filled: use fillellipse() or
 * floodfill() from the centre.
 */
void circle (int x, int y, int radius);
/**
 * Clears the graphics screen, filling it with the current background color.
 *
 * Paints the whole window with the current background colour and homes the
 * current position to (0,0).
 */
void cleardevice (void);
/**
 * Clears the viewport, filling it with the current background color.
 */
void clearviewport (void);
/**
 * Closes the graphics system.
 *
 * Destroys the window. Call it after the last getch().
 */
void closegraph (void);
/**
 * Waits for 'msec' milliseconds.
 *
 * @param msec milliseconds to wait
 *
 * Also pumps the event queue, which is what keeps the window responsive
 * during animation.
 */
void delay (int msec);
/**
 * Detects the graphics driver and graphics mode to use.
 */
void detectgraph (int * graphdriver, int * graphmode);
/**
 * Draws a polygon of numpoints vertices.
 *
 * @param numpoints number of points; repeat the first point to close the
 *                  shape
 * @param polypoints flat int array x1,y1,x2,y2,... — 2*numpoints entries
 *
 * Naming one fewer point than the array holds leaves the last edge open
 * (drawpoly(3, tri) draws two edges).
 */
void drawpoly (int numpoints, int * polypoints);
/**
 * Draws an elliptical arc centered at (x, y), with axes given by xradius and
 * yradius, traveling from stangle to endangle. Bresenham-based if complete
 *
 * @param x centre x, pixels
 * @param y centre y, pixels
 * @param stangle start angle, degrees, counter-clockwise from 3 o'clock
 * @param endangle end angle, degrees; 0 to 360 closes the curve
 * @param xradius horizontal radius, pixels
 * @param yradius vertical radius, pixels
 *
 * Outline only. Upper half is 0 to 180.
 */
void ellipse (int x, int y, int stangle, int endangle, int xradius, int yradius);
/**
 * Draws an ellipse centered at (x, y), with axes given by xradius and
 * yradius, and fills it using the current fill color and fill pattern.
 *
 * @param x centre x, pixels
 * @param y centre y, pixels
 * @param xradius horizontal radius, pixels
 * @param yradius vertical radius, pixels
 *
 * Interior uses the current fill style and colour; the outline uses the
 * current colour from setcolor().
 */
void fillellipse (int x, int y, int xradius, int yradius);
/**
 * Draws a polygon of numpoints vertices and fills it using the current fill
 * color.
 *
 * @param numpoints number of points; repeat the first point to close the
 *                  shape
 * @param polypoints flat int array x1,y1,x2,y2,... — 2*numpoints entries
 *
 * Filled with the current fill style; the outline is drawn in the current
 * colour.
 */
void fillpoly (int numpoints, int * polypoints);
/**
 * Fills an enclosed area with colour.
 *
 * @param x seed x; must lie inside the closed area
 * @param y seed y
 * @param border palette index of the outline the fill must stop at
 *
 * If the outline is not closed, or setcolor changed after it was drawn, the
 * fill escapes and covers the window.
 */
void floodfill (int x, int y, int border);
/**
 * Returns the active page number.
 */
int getactivepage (void);
/**
 * Gets the coordinates of the last call to arc(), filling the arccoords
 * structure.
 */
void getarccoords (struct arccoordstype *);
/**
 * Retrieves the current graphics mode's aspect ratio. Irrelevant on modern
 * hardware.
 */
void getaspectratio (int * xasp, int * yasp);
/**
 * Returns the current background color.
 */
int getbkcolor (void);
/**
 * Waits for a key and returns its ASCII value or code, or QUIT if the user
 * asked to close the window
 */
int bgi_getch (void);
// for Msys / Mingw64
#define getch bgi_getch
/**
 * Returns the current drawing (foreground) color.
 */
int getcolor (void);
/**
 * Returns the default palette
 */
struct palettetype * getdefaultpalette (void);
/**
 * Returns a pointer to a string containing the name of the current graphics
 * driver.
 */
char * getdrivername (void);
/**
 * Copies the user-defined fill pattern, as set by setfillpattern, into the
 * 8-byte area pointed to by pattern.
 */
void getfillpattern (char * pattern);
/**
 * Fills the fillsettingstype structure pointed to by fillinfo with
 * information about the current fill pattern and fill color.
 */
void getfillsettings (struct fillsettingstype *);
/**
 * Returns the current graphics mode.
 */
int getgraphmode (void);
/**
 * Copies a bit image of the specified region into the memory pointed by
 * bitmap.
 */
void getimage (int left, int top, int right, int bottom, void * bitmap);
/**
 * Fills the linesettingstype structure pointed by lineinfo with information
 * about the current line style, pattern, and thickness.
 */
void getlinesettings (struct linesettingstype *);
/**
 * Returns the maximum color value available (MAXCOLORS).
 */
int getmaxcolor (void);
/**
 * Returns the maximum mode number for the current driver.
 */
int getmaxmode (void);
/**
 * Returns the maximum x screen coordinate.
 *
 * @return largest valid x coordinate (639 in a 640x480 window)
 *
 * Use it instead of hardcoding 639 so a drawing tracks the mode.
 */
int getmaxx (void);
/**
 * Returns the maximum y screen coordinate.
 *
 * @return largest valid y coordinate (479 in a 640x480 window)
 *
 * Use it instead of hardcoding 479.
 */
int getmaxy (void);
/**
 * Returns a pointer to a string containing the name of the specified graphics
 * mode.
 */
char * getmodename (int mode_number);
/**
 * Gets the range of valid graphics modes.
 */
void getmoderange (int graphdriver, int * lomode, int * himode);
/**
 * Fills the palettetype structure pointed by palette with information about
 * the current palette's size and colors.
 */
void getpalette (struct palettetype *);
/**
 * Returns the size of the palette, depending of bgi_argb_mode.
 */
int getpalettesize (void);
/**
 * Returns the color of the pixel located at (x, y).
 *
 * @param x pixel x
 * @param y pixel y
 * @return palette index 0-15 of that pixel
 *
 * Returns the screen as drawn, not the current drawing colour.
 */
unsigned int getpixel (int x, int y);
/**
 * Fills the textsettingstype structure pointed to by texttypeinfo with
 * information about the current text font, direction, size, and
 * justification.
 */
void gettextsettings (struct textsettingstype *);
/**
 * Fills the viewporttype structure pointed to by viewport with information
 * about the current viewport.
 */
void getviewsettings (struct viewporttype *);
/**
 * Returns the visual page number.
 */
int getvisualpage (void);
/**
 * Returns the current x coordinate, relative to the viewport.
 */
int getx (void);
/**
 * Returns the current y coordinate, relative to the viewport.
 */
int gety (void);
/**
 * Resets all graphics settings to their defaults.
 */
void graphdefaults (void);
/**
 * Returns a pointer to the error message string associated with errorcode,
 * returned by graphresult().
 */
char * grapherrormsg (int errorcode);
/**
 * Returns the error code for the last unsuccessful graphics operation and
 * resets the error level to grOk.
 */
int graphresult (void);
/**
 * Returns the size in bytes of the memory area required to store a bit image.
 */
unsigned imagesize (int left, int top, int right, int bottom);
/**
 * Initializes the graphics system.
 *
 * @param graphdriver pass DETECT; its value is otherwise ignored
 * @param graphmode graphics mode: VGAHI is 640x480. Initialise it — `int gm =
 *                  VGAHI;` — an uninitialized value lands on SDL_bgi's
 *                  800x600 default
 * @param pathtodriver BGI driver path, ignored by SDL_bgi (pass "")
 *
 * Opens a window and clears it. One call per program.
 */
void initgraph (int * graphdriver, int * graphmode, char * pathtodriver);
/**
 * installuserdriver()
 */
int installuserdriver (char * name, int (*detect)(void));
/**
 * Loads a CHR font from disk. Undocumented feature: if the font file is not
 * found, this function returns LAST_SPEC_FONT.
 */
int installuserfont (char * name);
/**
 * Returns 1 when a key is pressed, or QUIT if the user asked to close the
 * window
 */
int k_bhit (void);
// fix for MSYS / Mingw64
#define kbhit k_bhit
/**
 * Returns the last key pressed
 */
int lastkey (void);
/**
 * Draws a line between two specified points.
 *
 * @param x1 start x, pixels
 * @param y1 start y, pixels; y grows downward
 * @param x2 end x, pixels
 * @param y2 end y, pixels
 *
 * Drawn in the current colour and line style, clipped to the window. Use
 * linerel() for a relative segment.
 */
void line (int x1, int y1, int x2, int y2);
/**
 * Draws a line from the CP to a point that is (dx,dy) pixels from the CP.
 *
 * @param dx x offset from the CP
 * @param dy y offset from the CP
 *
 * Draws a segment relative to the CP and moves the CP to its end.
 */
void linerel (int dx, int dy);
/**
 * Draws a line from the CP to (x, y), then moves the CP to (dx, dy).
 *
 * @param x target x
 * @param y target y
 *
 * Draws from the CP to (x,y) and moves the CP there.
 */
void lineto (int x, int y);
/**
 * Moves the CP by (dx, dy) pixels.
 *
 * @param dx x offset
 * @param dy y offset
 *
 * Moves the CP without drawing.
 */
void moverel (int dx, int dy);
/**
 * Moves the CP to the position (x, y), relative to the viewport.
 *
 * @param x new current position, x
 * @param y new current position, y
 *
 * Only changes the CP; nothing is drawn.
 */
void moveto (int x, int y);
/**
 * Outputs textstring at the CP.
 *
 * @param textstring string drawn at the current position (CP)
 *
 * The CP advances past the string; moveto() sets it.
 */
void outtext (char * textstring);
/**
 * Outputs textstring at (x, y). What happens to the CP afterwards?
 * Undocumented feature!
 *
 * @param x left edge of the string, pixels
 * @param y top edge of the string, pixels
 * @param textstring NUL-terminated string
 *
 * Colour from setcolor(), font and size from settextstyle(). Not clipped to
 * the viewport.
 */
void outtextxy (int x, int y, char * textstring);
/**
 * Draws and fills a pie slice centered at (x, y), with a radius given by
 * radius, traveling from stangle to endangle.
 *
 * @param x centre x, pixels
 * @param y centre y, pixels
 * @param stangle start angle, degrees, counter-clockwise
 * @param endangle end angle, degrees
 * @param radius radius in pixels
 *
 * Circular version of sector().
 */
void pieslice (int x, int y, int stangle, int endangle, int radius);
/**
 * Puts the bit image pointed to by bitmap onto the screen.
 */
void putimage (int left, int top, void * bitmap, int op);
/**
 * Plots a point at (x,y) in the color defined by 'color'.
 *
 * @param x pixel x
 * @param y pixel y
 * @param color BGI palette index 0-15, not an RGB triple
 *
 * Visible immediately and unaffected by setcolor(). The primitive under every
 * raster algorithm.
 */
void putpixel (int x, int y, int color);
#define random(range) (rand() % (range))
/**
 * Draws a rectangle delimited by (left,top) and (right,bottom).
 *
 * @param left x of the left edge, pixels
 * @param top y of the top edge, pixels (top < bottom, y grows downward)
 * @param right x of the right edge, pixels
 * @param bottom y of the bottom edge, pixels
 *
 * Draws four edges in the current colour and leaves the interior untouched.
 * Add bar() with the same coordinates to fill it; bar() alone draws no
 * border.
 */
void rectangle (int left, int top, int right, int bottom);
/**
 * registerbgidriver()
 */
int registerbgidriver (void (*driver)(void));
/**
 * registerbgifont()
 */
int registerbgifont (void (*font)(void));
/**
 * Hides the graphics window.
 */
void restorecrtmode (void);
/**
 * Draws and fills an elliptical pie slice centered at (x, y), horizontal and
 * vertical radii given by xradius and yradius, traveling from stangle to
 * endangle.
 *
 * @param x centre x, pixels
 * @param y centre y, pixels
 * @param stangle start angle, degrees, counter-clockwise from 3 o'clock
 * @param endangle end angle, degrees
 * @param xradius horizontal radius, pixels
 * @param yradius vertical radius, pixels
 *
 * Filled pie slice: two radii plus the arc between them. Slices that sum to
 * 360 fill the whole ellipse with no gaps (0-40, 40-140, 140-180, 180-360 for
 * a pie chart).
 */
void sector (int x, int y, int stangle, int endangle, int xradius, int yradius);
/**
 * Makes 'page' the active page for all subsequent graphics output.
 */
void setactivepage (int page);
/**
 * Sets the current palette to the values given in palette.
 */
void setallpalette (struct palettetype *);
/**
 * Changes the default aspect ratio of the graphics. Actually, it does
 * nothing; it makes no sense on modern hardware.
 */
void setaspectratio (int xasp, int yasp);
/**
 * Sets the current background color using the default palette.
 *
 * @param color BGI palette index 0-15, not RGB
 *
 * Takes effect on the next cleardevice().
 */
void setbkcolor (int color);
/**
 * Sets the current drawing color using the default palette.
 *
 * @param color BGI palette index 0-15 (WHITE, RED, GREEN, ...), not RGB
 *
 * Affects line, circle, rectangle, arc, drawpoly, outtextxy and the outline
 * of filled shapes — not bar() or fillpoly()'s interior. Also the colour
 * floodfill() checks against.
 */
void setcolor (int color);
/**
 * Sets a user-defined fill pattern.
 */
void setfillpattern (char * upattern, int color);
/**
 * Sets the fill pattern and fill color.
 *
 * @param pattern EMPTY_FILL, SOLID_FILL, LINE_FILL, HATCH_FILL, ... (0-11)
 * @param color BGI palette index 0-15
 *
 * Applies to bar, bar3d, fillpoly, fillellipse, sector and floodfill.
 * EMPTY_FILL leaves the interior untouched.
 */
void setfillstyle (int pattern, int color);
/**
 * setgraphbufsize()
 */
unsigned setgraphbufsize (unsigned bufsize);
/**
 * Shows the window that was hidden by restorecrtmode ().
 */
void setgraphmode (int mode);
/**
 * Sets the line width and style for all lines drawn by line(), lineto(),
 * rectangle(), drawpoly(), etc.
 */
void setlinestyle (int linestyle, unsigned upattern, int thickness);
/**
 * Changes the standard palette entry 'colornum' to 'color'; it also changes
 * pixels onscreen.
 */
void setpalette (int colornum, int color);
/**
 * Sets text justification.
 */
void settextjustify (int horiz, int vert);
/**
 * Sets the text font, the direction of the text (HORIZ DIR, VERT DIR), and
 * the size of characters.
 *
 * @param font DEFAULT_FONT, TRIPLEX_FONT, SMALL_FONT, SANS_SERIF_FONT,
 *             GOTHIC_FONT
 * @param direction HORIZ_DIR (left to right) or VERT_DIR (runs upward)
 * @param charsize magnification factor, not a point size
 *
 * VERT_DIR starts at the given point and runs up the screen, so use a y near
 * the bottom for an axis title.
 */
void settextstyle (int font, int direction, int charsize);
/**
 * Changes the font width and height.
 */
void setusercharsize (int multx, int divx, int multy, int divy);
/**
 * Sets the current viewport for graphics output.
 */
void setviewport (int left, int top, int right, int bottom, int clip);
/**
 * Sets the visual graphics page number.
 */
void setvisualpage (int page);
/**
 * Sets the writing mode for line drawing. 'mode' can be COPY PUT, XOR PUT, OR
 * PUT, AND PUT, and NOT PUT.
 */
void setwritemode (int mode);
/**
 * Returns the height in pixels of a string.
 */
int textheight (char * textstring);
/**
 * Returns the width in pixels of a string.
 */
int textwidth (char * textstring);

// SDL_bgi extensions

/**
 * Returns the alpha (transparency) component of 'color' in the ARGB palette.
 */
int ALPHA_VALUE (int color);
/**
 * Returns the blue component of 'color' in the ARGB palette
 */
int BLUE_VALUE (int color);
/**
 * Closes a window.
 */
void closewindow (int id);
/**
 * Can be used as an argument for setcolor() and setbkcolor() to set an ARGB
 * color.
 */
int COLOR (int r, int g, int b);
/**
 * Can be used as an argument for setcolor() and setbkcolor() to set an ARGB
 * color.
 */
int COLOR32 (Uint32 color);
/**
 * colorname()
 */
char * colorname (int color);
#define colorRGB(r,g,b)  0xff000000 | ((r) << 16) | ((g) << 8) | (b)
/**
 * Copies a surface to the active page
 */
void copysurface (SDL_Surface * surface, int x1, int y1, int x2, int y2);
/**
 * doubleclick()
 */
int doubleclick (void);
/**
 * Waits for 'msec' milliseconds and returns SDL_FALSE if no event occurred in
 * the meantime, SDL_TRUE otherwise
 */
int edelay (int msec);
/**
 * Returns SDL_TRUE if an event has occurred, SDL_FALSE otherwise.
 */
int event (void);
/**
 * Returns the type of the last event: SDL_KEYDOWN, SDL_MOUSEMOTION,
 * SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONUP, SDL_MOUSEWHEEL, SDL_QUIT
 */
int eventtype (void);
/**
 * like putpixel (), but not immediately displayed
 */
void fputpixel (int x, int y);
/**
 * Copies the current window contents to 'buffer', which must have the same
 * width and height as the current window.
 */
void getbuffer (Uint32 * buffer);
/**
 * Waits for a button click.
 */
int getclick (void);
/**
 * Returns the ID of current window
 */
int getcurrentwindow (void);
/**
 * getleftclick()
 */
void getleftclick (void);
/**
 * Waits for a keypress or mouse click, and returns the code of the mouse
 * event or key that was pressed.
 */
int getevent (void);
/**
 * getleftclick()
 */
void getleftclick (void);
/**
 * Copies the screen line at 'y' coordinate to 'linebuffer'; faster than
 * getpixel ()
 */
void getlinebuffer (int y, Uint32 * linebuffer);
/**
 * Returns the maximum height available for a new window.
 */
int getmaxheight (void);
/**
 * Returns the maximum width available for a new window.
 */
int getmaxwidth (void);
/**
 * Waits for a middle button click + release.
 */
void getmiddleclick (void);
/**
 * Sets the x, y coordinates of the last 'kind' button click expected by
 * ismouseclick().
 */
void getmouseclick (int kind, int * x, int * y);
/**
 * Fills the rgbpalettetype structure pointed by palette with information
 * about the current RGB palette's size and colors.
 */
void getrgbpalette (struct rgbpalettetype *, int size);
/**
 * Returns the current size of the ARGB palette.
 */
int getrgbpalettesize (void);
/**
 * Waits for a right button click + release.
 */
void getrightclick (void);
/**
 * Reports the screen size, regardless of the window dimensions.
 */
void getscreensize (int * x, int * y);
#define getwindowwidth  getmaxx
#define getwindowheight getmaxy
/**
 * Returns the green component of 'color' in the ARGB palette
 */
int GREEN_VALUE (int color);
/**
 * Initialises the default palette
 */
void initpalette (void);
/**
 * Initializes the graphics system, opening a 'width' x 'height' window.
 */
int initwindow (int width, int height);
/**
 * Returns 1 if 'color' belongs to the default palette
 */
int IS_BGI_COLOR (int color);
/**
 * Returns 1 if the 'btn' mouse button is being clicked.
 */
int ismouseclick (int btn);
/**
 * Returns 1 if 'color' belongs to the ARGB palette. The 'color' argument is
 * actually redundant
 */
int IS_RGB_COLOR (int color);
/**
 * Waits for 'msec' milliseconds and returns SDL_FALSE if no keyboard event
 * occurred in the meantime, SDL_TRUE otherwise
 */
int kdelay (int msec);
/**
 * Returns the code of the current mouse event (WM_MOUSEMOVE, WM_LBUTTONDOWN
 * etc.), or SDL_FALSE if no mouse event is occurring.
 */
int mouseclick (void);
/**
 * Returns the X coordinate of the last mouse click.
 */
int mousex (void);
/**
 * Returns the Y coordinate of the last mouse click.
 */
int mousey (void);
/**
 * Copies 'buffer' to the screen; 'buffer' must have the same width and height
 * as the current window. Inspired by:
 * https://lodev.org/cgtutor/examples.html#Drawbuffer
 */
void putbuffer (Uint32 * buffer);
/**
 * Copies 'linebuffer' to the 'y' coordinate; faster than putpixel ()
 */
void putlinebuffer (int y, Uint32 * linebuffer);
#define _putpixel fputpixel
/**
 * Returns the red component of 'color' in the ARGB palette
 */
int RED_VALUE (int color);
/**
 * Can be used as an argument for setcolor() and setbkcolor() to set an ARGB
 * color.
 */
int RGBPALETTE (int color);
/**
 * Reads a .bmp file and displays it immediately at (x1, y1).
 */
void readimagefile (char * bitmapname, int x1, int y1, int x2, int y2);
/**
 * Updates the screen.
 */
void refresh (void);
/**
 * Resets title and window position.
 */
void resetwinoptions (int id, char * title, int x, int y);
/**
 * Resizes the ARGB palette to 'newsize'
 */
int resizepalette (Uint32 newsize);
/**
 * Triggers "auto refresh mode", i.e. refresh() is performed automatically on
 * a separate thread. Auto mode can't work in Emscripten.
 */
void sdlbgiauto (void);
/**
 * Triggers "fast mode", i.e. refresh() is needed to display graphics.
 */
void sdlbgifast (void);
/**
 * Triggers "slow mode", i.e. refresh() is not needed to display graphics.
 */
void sdlbgislow (void);
/**
 * Sets the current RGB palette to the values given in palette.
 */
void setallrgbpalette (struct rgbpalettetype *);
/**
 * Sets alpha transparency for 'col' to 'alpha' (0-255).
 */
void setalpha (int col, Uint8 alpha);
/**
 * Sets the current background color to the 'colornum' colour in the ARGB
 * palette.
 */
void setbkrgbcolor (int colornum);
/**
 * Sets the blending mode; it can be either SDL_BLENDMODE_NONE or
 * SDL_BLENDMODE_BLEND
 */
void setblendmode (int blendmode);
/**
 * Sets the current window.
 */
void setcurrentwindow (int id);
/**
 * Sets the current foreground color to the 'colornum' colour in the ARGB
 * palette.
 */
void setrgbcolor (int colornum);
/**
 * Sets the 'colornum' entry in the ARGB palette specifying its r, g, and b
 * components.
 */
void setrgbpalette (int colornum, int red, int green, int blue);
/**
 * Sets window options.
 */
void setwinoptions (char * title, int x, int y, Uint32 flags);
/**
 * Sets the window title.
 */
void setwintitle (int id, char * title);
/**
 * Opens an info box
 */
void showinfobox (const char * message);
/**
 * Opens an error box
 */
void showerrorbox (const char * message);
/**
 * Swaps current visual and active pages.
 */
void swapbuffers (void);
/**
 * Writes a .bmp file from the screen rectangle defined by 'left', 'top',
 * 'right', 'bottom'.
 */
void writeimagefile (char * filename, int left, int top, int right, int bottom);
/**
 * Returns 1 when a key is pressed, or QUIT if the user asked to close the
 * window
 */
int xkb_hit (void);
// fix for for MSYS / Mingw64 bug
#define xkbhit xkb_hit
  
#ifdef __cplusplus
}
#endif

#endif // __GRAPHICS_H

#endif // _SDL_BGI_H

// --- End of file SDL_bgi.h

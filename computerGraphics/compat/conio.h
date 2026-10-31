// conio.h    -*- C -*-

// Minimal <conio.h> shim for BGI programs built against SDL_bgi.
//
// getch(), kbhit() and delay() are supplied by <graphics.h> (SDL_bgi defines
// getch and kbhit as macros over bgi_getch and k_bhit), so this file must not
// declare or define them again.
//
// clrscr() and gotoxy() are not part of SDL_bgi and are provided here.
// `static inline` keeps them internal to each translation unit, so including
// this header from several files does not produce duplicate symbols.
//
// Deliberately valid C: SDL_bgi itself is a C library, so this header must
// compile whether the editor or a compiler parses it as C or as C++.

#pragma once

#include <graphics.h>

#include <stdio.h>

// BGI's clrscr() clears the text console, but in a graphics program that is
// never what is wanted; clear the graphics screen instead.
static inline void clrscr (void) {
  cleardevice ();
}

// BGI's gotoxy() is 1-based (column, row); ANSI CUP is row;column, also 1-based.
static inline void gotoxy (int x, int y) {
  printf ("\x1b[%d;%dH", y, x);
}

// --- End of file conio.h

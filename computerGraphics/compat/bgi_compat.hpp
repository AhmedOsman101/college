// bgi_compat.hpp    -*- C++ -*-

// Const-correct shims for SDL_bgi's BGI API.
//
// SDL_bgi declares its string parameters as `char *`, following the original
// BGI header, so C++23 rejects string literals: initgraph(&gd, &gm, "") and
// outtextxy(x, y, "hi") do not compile. These inline overloads take
// `const char *` and forward to the original functions, so course code that
// passes literals compiles unchanged.
//
// Include it first (`-include compat/bgi_compat.hpp`) for files that include
// <graphics.h> themselves: this header pulls it in, then its include guard
// makes the later #include a no-op.

#pragma once

#include <graphics.h>

// Font names: version 2.x of SDL_bgi spells this font SANSSERIF_FONT; 3.x
// spells it SANS_SERIF_FONT, and there it is an enum member rather than a
// macro. The preprocessor cannot see enum members, so an unconditional
// `#ifndef SANS_SERIF_FONT / #define SANS_SERIF_FONT SANSSERIF_FONT` fallback
// would rewrite the name that already works into one 3.x does not define, and
// break every `settextstyle (SANS_SERIF_FONT, ...)`. If an older 2.x install
// is ever used, pass -DSANS_SERIF_FONT=SANSSERIF_FONT instead.

inline void initgraph (int *graphdriver, int *graphmode, const char *path) {
  ::initgraph (graphdriver, graphmode, const_cast<char *>(path));
}

inline void outtext (const char *textstring) {
  ::outtext (const_cast<char *>(textstring));
}

inline void outtextxy (int x, int y, const char *textstring) {
  ::outtextxy (x, y, const_cast<char *>(textstring));
}

inline int textheight (const char *textstring) {
  return ::textheight (const_cast<char *>(textstring));
}

inline int textwidth (const char *textstring) {
  return ::textwidth (const_cast<char *>(textstring));
}

// --- End of file bgi_compat.hpp

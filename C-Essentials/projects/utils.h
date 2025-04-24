#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

// Clears the input buffer
void clearInputBuffer(void);

// Reads a line of input safely, removing the newline
void readline(char* buffer, int size, FILE *stream);

// Reads an integer with validation
int readInt(int min, int max, const char* prompt);

#endif // UTILS_H

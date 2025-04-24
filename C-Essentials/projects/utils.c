#include "utils.h"
#include <string.h>

void readline(char* restrict s, int n, FILE *restrict stream) {
  fgets(s, n, stream);
  s[strcspn(s, "\n")] = '\0'; // Remove the newline '\n' character
}

// Clear input buffer
void clearInputBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

int readInt(int min, int max, const char* prompt) {
  int value;
  printf("%s", prompt);
  while (scanf("%d", &value) != 1 || value < min || value > max) {
    printf("Invalid input. Enter a number between %d and %d: ", min, max);
    clearInputBuffer();
  }
  clearInputBuffer();
  return value;
}


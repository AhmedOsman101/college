#include <stdio.h>
#include <string.h>

int char2index(char c) {
  return c - 97;
}

char index2char(char c) {
  return c + 97;
}


/**
 * Replaces or removes a specific character in a string.
 *
 * This function performs two operations based on the replace parameter:
 * 1. If replace contains a character, it replaces all occurrences of 'find' with that character
 * 2. If replace is empty, it removes all occurrences of 'find' from the string
 *
 * @param string      The input string to modify (modified in-place)
 * @param target      The character to find and replace/remove
 * @param replace     The replacement string (use "" to remove instead of replace)
 *
 * @note The function modifies the string in-place to save memory
 * @note For replacement, only the first character of replace string is used
 */
void str_replace(char* string, char target, const char* replace) {

  if (replace && *replace) {
    // Replace with new character
    for (int i = 0; string[i] != '\0'; i++) {
      if (string[i] == target) string[i] = replace[0];
    }
  } else {
    char* result = string;

    // Remove character (replace with empty string)
    while (*string) {
      if (*string != target) {
        // Copy only non-matching characters
        *result = *string;
        result++;
      }

      string++;
    }

    // Terminate the modified string
    *result = '\0';
  }
}

int* multiplyMatrices(int* A, int sizeA, int* B, int sizeB) {
  
}

int main() {
  int E[2][2] = {
    {3, 6},
    {1, 5}
  };

  int E_inverse[2][2] = {
    {15, 8},
    {23, 9}
  };

  char text[51], operation;
  printf("Enter any text (max 50 chars): ");

  fgets(text, 51, stdin);
  text[strlen(text) - 1] = '\0'; // trim newline charachter
  str_replace(text, ' ', ""); // remove whitespaces

  printf("\nType E to encrypt or D to decrypt (D/E): ");
  scanf("%c", &operation);

  // result = operation == 'E' ? encrypt(text) : decrypt(text);
  // printf("%s\n", result);
  return 0;
}

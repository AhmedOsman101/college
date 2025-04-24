#include <stdio.h>

const unsigned short WINNING_COMBOS[8][3] = {
  {0, 1, 2}, // Top row
  {0, 3, 6}, // Left column
  {3, 4, 5}, // Middle row
  {1, 4, 7}, // Middle column
  {6, 7, 8}, // Bottom row
  {2, 5, 8}, // Right column
  {0, 4, 8}, // Main diagonal
  {2, 4, 6}, // Counter diagonal
};

enum Boolean {
  false,
  true
};

enum Cell {
  BLANK,
  X,
  O
};

void initializeBoard(enum Cell board[9]) {
  for (short i = 0; i < 9; i++) board[i] = BLANK;
}

// Function to print the board
void printBoard(const enum Cell board[9]) {
  printf("---+---+---\n");
  for (int i = 0; i < 9; i++) {
    unsigned short index = (i + 1) % 3;

    if (board[i] == BLANK) printf(" . ");
    else if (board[i] == X) printf(" X ");
    else printf(" O ");

    if (index) printf("|");
    else printf("\n---+---+---\n");

  }
  printf("\n");
}

enum Boolean makeMove(enum Cell board[9]) {
  printf("Make a move (1-9): ");
  scanf("%hu", %)
  return true;
}

int main() {
  enum Cell board[9] = {};
  initializeBoard(board);

  printBoard(board);

  return 0;
}

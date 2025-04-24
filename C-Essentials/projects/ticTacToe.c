#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

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

enum boolean { false, true };

enum Cell { BLANK, X, O };

struct GameState {
  enum Cell board[9];
  enum Cell turn;
  enum boolean isOver;
};

void initializeBoard(enum Cell board[9]) {
  for (short i = 0; i < 9; i++) board[i] = BLANK;
}

void initializeGame(struct GameState *state) {
  state->isOver = false;
  state->turn = X;
  initializeBoard(state->board);
}

// Function to print the board
void printBoard(const enum Cell board[9]) {
  printf("---+---+---\n");
  for (int i = 0; i < 9; i++) {
    unsigned short index = (i + 1) % 3;

    if (board[i] == BLANK) printf(" %d ", i + 1);
    else if (board[i] == X) printf(" X ");
    else printf(" O ");

    if (index) printf("|");
    else printf("\n---+---+---\n");

  }
  printf("\n");
}

void toggleTurn(struct GameState* state) {
  state->turn = state->turn == X ? O : X;
}

enum boolean makeMove(struct GameState* state) {
  if (state->isOver) return false;

  unsigned short move;
  move = readInt(1, 9, "Make a move (1-9): ") - 1;

  if (state->board[move] == BLANK) {
    state->board[move] = state->turn;
    toggleTurn(state);
  } else {
    printf("The square %hu is occupied, try again\n", move + 1);
    return false;
  }

  return true;
}

enum boolean checkWinning(struct GameState *state) {
  for (unsigned short i = 0; i < 8; i++) {
    unsigned short a = WINNING_COMBOS[i][0],
                   b = WINNING_COMBOS[i][1],
                   c = WINNING_COMBOS[i][2];
    if (
      state->board[a] != BLANK &&
      state->board[a] == state->board[b] &&
      state->board[b] == state->board[c]
    ) {
      toggleTurn(state);
      printf("Player %c Won!\n", state->turn == X ? 'O' : 'X');
      return true;
    }
  }

  return false;
}

enum boolean checkDraw(struct GameState *state) {
  for (unsigned short i = 0; i < 9; i++) {
    if (state->board[i] == BLANK) return false;
  }

  printf("It's a Draw!\n");
  return true;
}

void mainLoop(struct GameState *state) {
  while (!state->isOver) {
    char command;
    printBoard(state->board);
    if (!makeMove(state)) continue;
    if (checkWinning(state) || checkDraw(state)) {
      printf("Do you want to play again? (y/n): ");
      scanf("%c", &command);
      clearInputBuffer();
      if (tolower(command) == 'y') {
        initializeGame(state);
      } else {
        printf("Goodbye\n");
        exit(0);
      }
    }
  }
}

int main() {
  struct GameState state;
  initializeGame(&state);
  mainLoop(&state);

  return 0;
}

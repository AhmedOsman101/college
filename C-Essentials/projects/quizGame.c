#include <ctype.h>
#include <stdio.h>
#include "utils.h"

#define NUM_QUESTIONS 5

struct Question {
  char question[255];
  char answer;
};

struct Question questions[NUM_QUESTIONS] = {
  {
    .question = "What is the correct syntax to declare an integer variable in C?\n"
                "A) int x;\n"
                "B) integer x;\n"
                "C) var x: int;\n"
                "D) x = int;\n",
    .answer = 'A'
  },
  {
    .question = "Which symbol is used for single-line comments in C?\n"
                "A) //\n"
                "B) /* */\n"
                "C) #\n"
                "D) --\n",
    .answer = 'A'
  },
  {
    .question = "What does the 'printf' function do in C?\n"
                "A) Reads input from the user\n"
                "B) Prints output to the console\n"
                "C) Declares a variable\n"
                "D) Loops through an array\n",
    .answer = 'B'
  },
  {
    .question = "Which loop in C executes at least once before checking the condition?\n"
                "A) for\n"
                "B) while\n"
                "C) do-while\n"
                "D) switch\n",
    .answer = 'C'
  },
  {
    .question = "What is the size of a 'char' data type in C (in bytes)?\n"
                "A) 1\n"
                "B) 2\n"
                "C) 4\n"
                "D) 8\n",
    .answer = 'A'
  }
};

int main() {
  unsigned short score = 0;
  char answer;

  printf("Welcome to the quiz game\n");
  printf("-------------------------------------------------\n");

  for (short i = 0; i < NUM_QUESTIONS; i++) {
    printf("%s\nYour Answer: ", questions[i].question);
    scanf("%c", &answer);
    clearInputBuffer();

    if (tolower(answer) == tolower(questions[i].answer)) {
      score++;
      printf("Correct!\n\n");
    } else printf("Wrong Answer!\nThe right answer is: %c\n\n", questions[i].answer);
  }

  printf("Your Scored %d out of 5\n", score);

  return 0;
}

#include <stdio.h>
#include <string.h>

const char FILENAME[11] = "grades.txt";

struct Student {
  char name[50];
  int marks[3];
  float average;
};

void calculateAverage(struct Student *s) {
  float sum = 0;

  for (int i = 0; i < 3; i++) {
    sum += s->marks[i];
  }

  s->average = sum / 3.0;
}

void readline(char* restrict s, int n, FILE *restrict stream) {
  fgets(s, n, stream);
  s[strcspn(s, "\n")] = '\0'; // Remove the newline '\n' character
}

// Clear input buffer
void clearInputBuffer() {
  int c;

  while ((c = getchar()) != '\n' && c != EOF);
}


int main() {
  FILE *file = fopen(FILENAME, "w"); // Open file in write mode
  int character;

  // check if file was opened successfully
  if (file == NULL) {
    printf("Error opening %s!\n", FILENAME);
    return 1;
  }

  struct Student students[3];

  for (int i = 0; i < 3; i++) {
    printf("Enter details for student %d:\n", i + 1);

    printf("Name: ");
    readline(students[i].name, 50, stdin);

    for (int j = 0; j < 3; j++) {
      printf("Subject %d marks: ", j + 1);
      scanf("%d", &students[i].marks[j]);
    }

    clearInputBuffer();

    calculateAverage(&students[i]);
  }

  for (int i = 0; i < 3; i++) {
    struct Student s = students[i];
    fprintf(file,
      "Name: '%s', Average: %.2f\n",
      s.name, s.average
    );
  }

  fclose(file); // close the file the reopen it in read mode

  file = fopen(FILENAME, "r"); // Open file in read mode

  // check if file was opened successfully
  if (file == NULL) {
    printf("Error reading from %s!\n", FILENAME);
    return 1;
  }


  printf("Reading content from %s:\n\n", FILENAME);

  // Read the file character by character until the end of the file (EOF) is reached
  while ((character = fgetc(file)) != EOF) {
    // Print the character to the console
    putchar(character);
  }

  // close the file stream
  fclose(file);
  return 0;
}

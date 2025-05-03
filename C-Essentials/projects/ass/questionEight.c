#include <stdio.h>
#include <string.h> // String manipulation functions

// Define filename as a constant
const char FILENAME[11] = "grades.txt";

// Student structure
struct Student {
  char name[50]; // Student name
  int marks[3]; // Marks for 3 subjects
  float average; // Calculated average
};

// Function to calculate average marks
void calculateAverage(struct Student *s) {
  float sum = 0;

  for (int i = 0; i < 3; i++) {
    sum += s->marks[i];
  }

  s->average = sum / 3.0;
}

// Function to read a line, removing newline
void readline(char* restrict s, int n, FILE *restrict stream) {
  fgets(s, n, stream);
  s[strcspn(s, "\n")] = '\0';
}

// Function to clear input buffer
void clearInputBuffer() {
  int c;

  while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
  // Open file in write mode ("w"). Creates or overwrites.
  FILE *file = fopen(FILENAME, "w");
  int character; // Variable for reading characters

  // Check if file opened successfully for writing
  if (file == NULL) {
    printf("Error opening %s!\n", FILENAME);
    return 1;
  }

  // Array of 3 Student structures
  struct Student students[3];

  // Input data for 3 students
  for (int i = 0; i < 3; i++) {
    printf("Enter details for student %d:\n", i + 1);
    printf("Name: ");
    readline(students[i].name, 50, stdin);

    for (int j = 0; j < 3; j++) {
      printf("Subject %d marks: ", j + 1);
      scanf("%d", &students[i].marks[j]);
    }

    clearInputBuffer(); // Clear buffer after scanf

    calculateAverage(&students[i]); // Calculate average
  }

  // Write student name and average to file
  for (int i = 0; i < 3; i++) {
    struct Student s = students[i];
    fprintf(file,
      "Name: '%s', Average: %.2f\n",
      s.name, s.average
    );
  }

  // Close the file after writing
  fclose(file);

  // Reopen the file in read mode ("r")
  file = fopen(FILENAME, "r");

  // Check if file opened successfully for reading
  if (file == NULL) {
    printf("Error reading from %s!\n", FILENAME);
    return 1;
  }

  printf("Reading content from %s:\n\n", FILENAME);

  // Read and print file content character by character
  while ((character = fgetc(file)) != EOF) {
    putchar(character);
  }

  // Close the file after reading
  fclose(file);

  return 0; // Indicate success
}

#include <stdio.h>

// Define a structure named Student
struct Student {
  int id; // Student ID
  char name[50]; // Student name (character array to hold the string)
  int marks[3]; // Array to hold marks for 3 subjects
};

int main() {
  // Declare an array of 3 Student structures
  struct Student students[3];

  // Input data for 3 students
  for (int i = 0; i < 3; i++) { // Loop through each student
    printf("Enter details for student %d:\n", i + 1); // Prompt for student details
    printf("ID: ");
    scanf("%d", &students[i].id); // Read student ID

    printf("Name: ");
    // Read student name. scanf("%s", ...) reads a single word and stops at whitespace.
    // Be cautious with scanf("%s") for names with spaces; fgets is generally safer.
    scanf("%s", students[i].name);

    // Input marks for the 3 subjects for the current student
    for (int j = 0; j < 3; j++) { // Loop through each subject
      printf("Subject %d marks: ", j + 1);
      scanf("%d", &students[i].marks[j]); // Read subject marks
    }
  }

  printf("---------------------\n"); // Separator line for output

  // Display data for the 3 students
  for (int i = 0; i < 3; i++) { // Loop through each student
    printf("\nStudent %d:\n", i + 1); // Display student number
    printf("ID: %d\n", students[i].id); // Display student ID
    printf("Name: %s\n", students[i].name); // Display student name

    // Display marks for the 3 subjects for the current student
    for (int j = 0; j < 3; j++) { // Loop through each subject
      printf("Subject %d marks: %d\n", j + 1, students[i].marks[j]); // Display subject marks
    }
  }

  return 0;
}

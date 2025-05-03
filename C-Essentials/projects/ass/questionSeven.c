#include <stdio.h>
#include <string.h> // Include string library for string manipulation functions

// Define a structure named Student
struct Student {
  int id; // Student ID
  char name[50]; // Student name
  int marks[3]; // Array to hold marks for 3 subjects
  float average; // Variable to store the calculated average
};

// Function to calculate the average marks for a student
// Takes a pointer to a Student structure as input
void calculateAverage(struct Student *s) {
  float sum = 0; // Initialize sum of marks

  // Loop through the marks array to calculate the sum
  for (int i = 0; i < 3; i++) {
    sum += s->marks[i]; // Add current subject's mark to sum (using pointer dereference ->)
  }

  // Calculate the average and store it in the average field of the structure
  s->average = sum / 3.0; // Use 3.0 for floating-point division
}

// Function to read a line from input, removing the newline character
void readline(char* restrict s, int n, FILE *restrict stream) {
  fgets(s, n, stream);
  s[strcspn(s, "\n")] = '\0'; // Remove the newline '\n' character
}

// Function to clear the input buffer
void clearInputBuffer() {
  int c;

  while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
  // Declare an array of 5 Student structures
  struct Student students[5];

  // Input data for 5 students
  for (int i = 0; i < 5; i++) { // Loop through each student
    printf("Enter details for student %d:\n", i + 1); // Prompt for student details

    printf("ID: ");
    scanf("%d", &students[i].id); // Read student ID
    clearInputBuffer(); // Clear buffer after reading integer

    printf("Name: ");
    readline(students[i].name, 50, stdin); // Read student name (handles spaces)

    // Input marks for the 3 subjects for the current student
    for (int j = 0; j < 3; j++) { // Loop through each subject
      printf("Subject %d marks: ", j + 1);
      scanf("%d", &students[i].marks[j]); // Read subject marks
    }

    calculateAverage(&students[i]); // Calculate average for the student
  }

  printf("\nStudent Grading Report:\n"); // Header for the report

  // Display data for the 5 students
  for (int i = 0; i < 5; i++) { // Loop through each student
    struct Student s = students[i]; // Create a copy for easier access (optional, could use students[i] directly)
    printf(
      "ID: %d, Name: '%s', Marks: %d, %d, %d, Average: %.2f\n",
      s.id, s.name, s.marks[0], s.marks[1], s.marks[2], s.average // Print student details and calculated average
    );
  }

  // Demonstrate updating a student's mark using a pointer
  struct Student *p = &students[0]; // Declare a pointer 'p' and point it to the first student structure

  p->marks[0] = 90; // Update the first subject's mark for the first student using the pointer

  calculateAverage(p); // Recalculate the average for the first student after updating marks

  printf("\nAfter updating student 1's subject 1 mark to 90:\n"); // Message indicating the update
  printf(
    "ID: %d, Name: '%s', Marks: %d, %d, %d, Average: %.2f\n",
    p->id, p->name, p->marks[0], p->marks[1], p->marks[2], p->average // Display updated details
  );

  return 0;
}

#include <stdio.h>

int main() {
  // 2D array for 5 students, 3 subjects
  int marks[5][3];
  int total; // Variable for total marks per student

  // Input marks
  for (int i = 0; i < 5; i++) { // Loop through students
    printf("\nEnter marks for student %d:\n", i + 1);

    for (int j = 0; j < 3; j++) { // Loop through subjects
      printf("Subject %d: ", j + 1);
      scanf("%d", &marks[i][j]); // Read marks
    }
  }

  printf("\n"); // Newline for output formatting

  // Calculate and display total marks
  for (int i = 0; i < 5; i++) { // Loop through students
    total = 0; // Reset total for each student

    for (int j = 0; j < 3; j++) { // Loop through subjects to sum marks
      total += marks[i][j]; // Add subject mark to total
    }

    // Display total marks for the current student
    printf("Total marks for student %d: %d\n", i + 1, total);
  }

  return 0; // Indicate success
}

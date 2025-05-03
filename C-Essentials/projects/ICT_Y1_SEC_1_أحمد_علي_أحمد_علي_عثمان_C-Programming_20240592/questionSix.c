#include <stdio.h>

int main() {
  // Declare a one-dimensional array to store marks for 5 students in 3 subjects.
  // Total elements = 5 students * 3 subjects = 15.
  int marks[15];

  // Input marks for 5 students (3 subjects each) into the 1D array.
  // The index calculation i * 3 + j maps the 2D logic (student i, subject j)
  // to the 1D array index.
  for (int i = 0; i < 5; i++) { // Loop through each student
    printf("Enter marks for student %d:\n", i + 1);

    for (int j = 0; j < 3; j++) { // Loop through each subject
      printf("Subject %d: ", j + 1);
      scanf("%d", &marks[i * 3 + j]); // Read marks into the calculated 1D index
    }
  }

  // Declare an integer pointer and initialize it to point to the beginning of the 'marks' array.
  // The array name 'marks' itself acts as a pointer to its first element.
  int* ptr = marks;

  printf("---------------------\n"); // Separator line for output


  // Loop to display marks using the pointer to traverse the array.
  for (int i = 0; i < 5; i++) { // Loop through each student
    printf("Student %d marks: ", i + 1);

    for (int j = 0; j < 3; j++) { // Loop through each subject for the current student
      printf("%d ", *ptr); // Dereference the pointer to access the value at the current memory location
      ptr++; // Increment the pointer to move to the next integer element in the array
    }

    printf("\n"); // Newline after displaying marks for each student
  }


  return 0;
}

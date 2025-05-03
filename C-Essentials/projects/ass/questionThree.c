#include <stdio.h>

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

int main() {
  // Declare and initialize a Student structure variable 's1'
  struct Student s1 = {
    .id = 1, // Initialize ID
    .name = "John", // Initialize name
    .marks = { 80, 85, 90 }, // Initialize marks for 3 subjects
    .average = 0.0 // Initialize average (will be calculated later)
  };

  // Display student details before calculating the average
  printf("Before\n");
  printf("Student ID: %d\nName: %s\nAverage: %.2f\n", s1.id, s1.name, s1.average);

  // Call the calculateAverage function, passing the address of s1
  // This allows the function to modify the s1 structure directly
  calculateAverage(&s1);

  // Display student details after calculating the average
  printf("\nAfter\n");
  printf("Student ID: %d\nName: %s\nAverage: %.2f\n", s1.id, s1.name, s1.average);

  return 0;
}

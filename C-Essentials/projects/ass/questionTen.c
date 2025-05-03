#include <stdio.h> // Standard I/O library
#include <string.h> // String manipulation functions

// Define filename
const char FILENAME[11] = "grades.txt";

int main() {
  // Open file in read mode ("r")
  FILE *file = fopen(FILENAME, "r");

  // Check for file open errors
  if (file == NULL) {
    printf("Error opening file.\n");
    return 1; // Indicate error
  }

  char line[100]; // Buffer for reading lines
  printf("Student Grades Report:\n"); // Report header

  // Read file line by line using fgets
  while (fgets(line, 100, file) != NULL) {
    char name[50]; // Variable for name
    float average; // Variable for average

    /*
      Parse line using sscanf:
      - "Name: %[^,]" extracts name up to comma.
      - ", " matches literal comma and space.
      - "Average: %f" extracts float after "Average: ".
    */
    sscanf(line, "Name: %[^,], Average: %f", name, &average);

    // Print extracted data
    printf("Name: %s, Average: %.2f\n", name, average);
  }

  // Close the file
  fclose(file);

  return 0; // Indicate success
}

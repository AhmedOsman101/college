#include <stdio.h> // Standard I/O library for file operations, printf, scanf
#include <stdlib.h> // Standard library for exit()
#include <string.h> // String manipulation functions for strcspn, strcpy

// Student structure definition
struct Student {
  int id; // Student ID
  char name[50]; // Student name
  int marks[3]; // Marks for 3 subjects
  float average; // Calculated average
};

// Function to calculate average marks for a student
void calculateAverage(struct Student *s) {
  float sum = 0;

  for (int i = 0; i < 3; i++) {
    sum += s->marks[i];
  }

  s->average = sum / 3.0;
}

// Function to read a line from input, removing newline
void readline(char* restrict s, int n, FILE *restrict stream) {
  fgets(s, n, stream);
  s[strcspn(s, "\n")] = '\0'; // Remove the newline '\n' character
}

// Function to clear input buffer after scanf
void clearInputBuffer() {
  int c;

  while ((c = getchar()) != '\n' && c != EOF);
}

// Function to read student details from user input
void readStudent(struct Student *s) {
  printf("\nEnter student ID: ");
  scanf("%d", &s->id);
  clearInputBuffer(); // Clear buffer after reading integer

  printf("Name: ");
  readline(s->name, 50, stdin); // Read name (handles spaces)

  for (int j = 0; j < 3; j++) {
    printf("Subject %d marks: ", j + 1);
    scanf("%d", &s->marks[j]); // Read subject marks
  }

  clearInputBuffer(); // Clear buffer after reading marks

  calculateAverage(s); // Calculate average after input
}


// Function to create an empty file
// Returns 0 on success, 1 on failure
int createFile(const char* filename) {
  FILE *file;
  file = fopen(filename, "w"); // Open file in write mode (creates or clears)

  if (file == NULL) {
    printf("Error: Could not create file %s\n", filename);
    return 1; // Indicate error
  }

  fclose(file); // Close immediately to leave it empty
  return 0; // Indicate success
}

// Function to save student data to a file
void saveData(struct Student students[], int n, const char* filename) {
  FILE *file = fopen(filename, "w"); // Open file in write mode

  if (file == NULL) {
    printf("Error opening file for saving.\n");
    exit(1); // Exit on critical error
  }

  // Write student data in a formatted way
  for (int i = 0; i < n; i++) {
    fprintf(
      file, "%d %s %d %d %d\n", // Format: ID Name Mark1 Mark2 Mark3
      students[i].id, students[i].name, students[i].marks[0],
      students[i].marks[1], students[i].marks[2]
    );
  }

  fclose(file); // Close file after saving
}


// Function to load student data from a file
// 'checked' flag prevents infinite recursion on file not found
void loadData(struct Student students[], int n, const char* filename, short checked) {
  FILE *fp = fopen(filename, "r"); // Open file in read mode

  if (fp == NULL) {
    if (checked) {
      printf("Error opening file for loading.\n");
      exit(1); // Exit if file should exist but doesn't
    } else {
      // If file doesn't exist on first try, create it, get input, save, and try loading again
      printf("File not found. Creating new file and getting student data.\n");
      createFile(filename);

      for (int i = 0; i < n; i++) {
        readStudent(&students[i]); // Get student data from user
      }

      saveData(students, n, filename); // Save the newly entered data

      loadData(students, n, filename, 1); // Try loading again (checked is now 1)
      return;
    }
  }

  // Read student data from file using fscanf
  for (int i = 0; i < n; i++) {
    fscanf(
      fp, "%d %s %d %d %d", // Format to match saveData
      &students[i].id, students[i].name, &students[i].marks[0],
      &students[i].marks[1], &students[i].marks[2]
    );
    calculateAverage(&students[i]); // Calculate average after loading marks
  }

  fclose(fp); // Close file after loading
}

int main() {
  struct Student students[5]; // Array to hold 5 students
  const char* filename = "students.txt"; // Data file name

  // Load student data from file (or get input if file doesn't exist)
  loadData(students, 5, filename, 0);

  // Display current student data
  printf("\nCurrent Student Data:\n");

  for (int i = 0; i < 5; i++) {
    printf(
      "ID: %d, Name: %s, Marks: %d, %d, %d, Average: %.2f\n",
      students[i].id, students[i].name, students[i].marks[0],
      students[i].marks[1], students[i].marks[2], students[i].average
    );
  }

  // Update marks section
  int id;
  printf("\nEnter student ID to update: ");
  scanf("%d", &id); // Get ID to update
  int index = -1; // Index of student to update

  // Find the student by ID
  for (int i = 0; i < 5; i++) {
    if (students[i].id == id) {
      index = i; // Found student, store index
      break;
    }
  }

  // Handle student not found
  if (index == -1) {
    printf("Student not found.\n");
    return 1; // Exit or handle error
  }

  // Get new marks for the selected student
  printf("Enter new marks for student %d:\n", id);

  for (int j = 0; j < 3; j++) {
    printf("Subject %d: ", j + 1);
    scanf("%d", &students[index].marks[j]); // Read new marks
  }

  calculateAverage(&students[index]); // Recalculate average after update

  // Display updated student data
  printf("\nUpdated Student Data:\n");

  for (int i = 0; i < 5; i++) {
    printf(
      "ID: %d, Name: %s, Marks: %d, %d, %d, Average: %.2f\n",
      students[i].id, students[i].name, students[i].marks[0],
      students[i].marks[1], students[i].marks[2], students[i].average
    );
  }

  // Save the updated data back to the file
  saveData(students, 5, filename);
  printf("\nData saved to %s\n", filename);

  return 0; // Indicate successful execution
}

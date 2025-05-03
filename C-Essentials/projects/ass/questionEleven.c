#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
  int id;
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

void readStudent(struct Student *s) {
  printf("\nEnter student ID: ");
  scanf("%d", &s->id);
  clearInputBuffer();

  printf("Name: ");
  readline(s->name, 50, stdin);

  for (int j = 0; j < 3; j++) {
    printf("Subject %d marks: ", j + 1);
    scanf("%d", &s->marks[j]);
  }

  clearInputBuffer();


  calculateAverage(s);
}


// Function to create an empty file
// Returns 0 on success, 1 on failure
int createFile(const char* filename) {
  FILE *file; // Declare a file pointer

  // Open the file in write mode ("w").
  // If the file exists, its contents are discarded (it becomes empty).
  // If the file does not exist, it is created.
  file = fopen(filename, "w");

  // Check if the file was opened successfully
  if (file == NULL) {
    // If fopen returns NULL, there was an error opening/creating the file
    printf("Error: Could not create file %s\n", filename);
    return 1; // Indicate an error by returning a non-zero value
  }

  // If the file was opened successfully, immediately close it.
  // This leaves the file empty.
  fclose(file);

  return 0; // Indicate successful execution
}

void saveData(struct Student students[], int n, const char* filename) {
  FILE *file = fopen(filename, "w");

  if (file == NULL) {
    printf("Error opening file.\n");
    exit(1);
  }

  for (int i = 0; i < n; i++) {
    fprintf(
      file, "%d %s %d %d %d\n",
      students[i].id, students[i].name, students[i].marks[0],
      students[i].marks[1], students[i].marks[2]
    );
  }

  fclose(file);
}


void loadData(struct Student students[], int n, const char* filename, short checked) {
  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    if (checked) {
      printf("Error opening file.\n");
      exit(1);
    } else {
      createFile(filename);

      for (int i = 0; i < n; i++) {
        readStudent(&students[i]);
      }

      saveData(students, n, filename);

      loadData(students, n, filename, 1);
      return;
    }
  }

  for (int i = 0; i < n; i++) {
    fscanf(
      fp, "%d %s %d %d %d",
      &students[i].id, students[i].name, &students[i].marks[0],
      &students[i].marks[1], &students[i].marks[2]
    );
    calculateAverage(&students[i]);
  }

  fclose(fp);
}

int main() {
  struct Student students[5];
  const char* filename = "students.txt";

  // Load data
  loadData(students, 5, filename, 0);

  // Display current data
  printf("\nCurrent Student Data:\n");

  for (int i = 0; i < 5; i++) {
    printf(
      "ID: %d, Name: %s, Marks: %d, %d, %d, Average: %.2f\n",
      students[i].id, students[i].name, students[i].marks[0],
      students[i].marks[1], students[i].marks[2], students[i].average
    );
  }

  // Update marks
  int id;
  printf("\nEnter student ID to update: ");
  scanf("%d", &id);
  int index = -1;

  for (int i = 0; i < 5; i++) {
    if (students[i].id == id) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    printf("Student not found.\n");
    return 1;
  }

  printf("Enter new marks for student %d:\n", id);

  for (int j = 0; j < 3; j++) {
    printf("Subject %d: ", j + 1);
    scanf("%d", &students[index].marks[j]);
  }

  calculateAverage(&students[index]);

  // Display updated data
  printf("\nUpdated Student Data:\n");

  for (int i = 0; i < 5; i++) {
    printf(
      "ID: %d, Name: %s, Marks: %d, %d, %d, Average: %.2f\n",
      students[i].id, students[i].name, students[i].marks[0],
      students[i].marks[1], students[i].marks[2], students[i].average
    );
  }

  // Save data
  saveData(students, 5, filename);
  printf("\nData saved to %s\n", filename);

  return 0;
}

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 20
#define GRADES_COUNT 5

const char SUBJECTS[][10] = { "IoT", "C", "MS-Office", "English", "Math" };

struct Student {
  int index;
  unsigned int id;
  char name[NAME_LENGTH];
  unsigned short grades[GRADES_COUNT];
  float averageGrades;
};

struct StudentArray {
  struct Student* students; // Pointer to array of students
  unsigned int count; // Current number of students
  unsigned int capacity; // Total allocated capacity
};

const struct Student NotFound = {
  .index = -1,
  .id = 0,
  .name = "",
  .grades = {0, 0, 0, 0, 0},
  .averageGrades = 0.0
};


void initStudentArray(struct StudentArray *arr) {
  arr->students = NULL;
  arr->count = 0;
  arr->capacity = 0;
}

// Free the dynamic array
void freeStudentArray(struct StudentArray *arr) {
  free(arr->students);
  arr->students = NULL;
  arr->count = 0;
  arr->capacity = 0;
}

int generateId() {
  static int count = 1; // Static variable retains value between calls
  return count++;
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

void printStudent(const struct Student *student) {

  if (student == NULL) {
    printf("Error: Invalid student data\n");
    return;
  }

  printf("------------- Details of Student %-2u -------------\n", student->id);
  printf("Student ID: %u\n", student->id);
  printf("Name: %s\n", student->name);
  printf("Grades:\n");

  for (int i = 0; i < GRADES_COUNT; i++) {
    printf("  %s: %hu\n", SUBJECTS[i], student->grades[i]);
  }

  printf("Average Grade: %.2f\n", student->averageGrades);
  printf("-------------------------------------------------\n");
}

void printStudents(struct StudentArray *arr) {
  if (arr->count == 0) {
    printf("The student list is empty.\nPlease use the 'Add Student' command first to add students.\n");
    return;
  }

  for (unsigned int i = 0; i < arr->count; i++) {
    printStudent(&arr->students[i]);
  }
}


int main() {
  printf("hello world\n");

  return 0;
}

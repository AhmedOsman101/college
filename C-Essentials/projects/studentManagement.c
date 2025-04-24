#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

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

struct Student searchById(struct StudentArray *arr) {
  unsigned int target;

  printf("Enter ID to search for: ");
  scanf("%u", &target);
  clearInputBuffer();

  for (unsigned int i = 0; i < arr->count; i++) {
    if (arr->students[i].id == target) {
      struct Student s = arr->students[i];
      s.index = i;
      return s;
    }
  }

  printf("Student with ID %u was not found.\n", target);

  return NotFound;
}

struct Student readStudent(const unsigned int id) {
  struct Student s;
  s.index = -1;

  if (id == 0) s.id = generateId(); // Automatically generated ID
  else s.id = id;

  printf("--------- Reading Details of Student %-2u ---------\n", s.id);
  printf("Enter your name: ");
  readline(s.name, NAME_LENGTH, stdin);

  unsigned int total = 0;

  for (int i = 0; i < GRADES_COUNT; i++) {
    printf("Enter your grades for %s: ", SUBJECTS[i]);
    unsigned short grade;
    scanf("%hu", &grade); // %hu for unsigned short
    clearInputBuffer(); // Consume the newline

    if (grade < 0 || grade > 100) {
      printf("Grade must between 0-100. Using 0 instead.\n");
      grade = 0;
    }

    s.grades[i] = grade;

    total += s.grades[i];
  }

  s.averageGrades = total * 1.0 / GRADES_COUNT; // multiply by 1.0 to ensure float division

  return s;
}

void addStudent(struct StudentArray *arr) {
  /*
  If the items count is bigger than the capacity:
    - Double the capacity of the array (if 0 initialize with 2)
    - Reallocate memory for the array to be twice the size
    - Memory allocation works by multiplying the array's capacity by the size of the datatype in bytes
   */
  if (arr->count >= arr->capacity) {
    arr->capacity = (arr->capacity == 0) ? 2 : arr->capacity * 2;
    arr->students = realloc(arr->students, arr->capacity * sizeof(struct Student));

    if (arr->students == NULL) {
      printf("Memory allocation failed!\n");
      exit(1);
    }
  }

  arr->students[arr->count] = readStudent(0);
  arr->count++;
}

void deleteStudent(struct StudentArray *arr) {

  if (arr->count == 0) {
    printf("The student list is empty.\nPlease use the 'Add Student' command first to add students.\n");
    return;
  }

  struct Student targetStudent = searchById(arr);
  if (targetStudent.id == 0) return;

  printf("Delete student with ID %u? (y/n): ", targetStudent.id);
  char confirm;
  scanf("%c", &confirm);
  clearInputBuffer();
  if (tolower(confirm) != 'y') {
    printf("Deletion cancelled.\n");
    return;
  }


  // Shift elements to overwrite the deleted student
  for (unsigned int i = targetStudent.index; i < arr->count - 1; i++) {
    arr->students[i] = arr->students[i + 1];
  }

  arr->count--;

  printf("Student with ID %u deleted successfully!\n", targetStudent.id);
}

void updateStudent(struct StudentArray *arr) {

  if (arr->count == 0) {
    printf("The student list is empty.\nPlease use the 'Add Student' command first to add students.\n");
    return;
  }

  struct Student student = searchById(arr);
  if (student.id == 0) return;

  struct Student updatedStudent = readStudent(student.id);

  printf("Update student with ID %u? (y/n): ", student.id);
  char confirm;
  scanf("%c", &confirm);
  clearInputBuffer();
  if (tolower(confirm) != 'y') {
    printf("Update cancelled.\n");
    return;
  }

  arr->students[student.index] = updatedStudent;

  printf("Student with ID %u updated successfully!\n", student.id);
}


void searchByName(struct StudentArray *arr) {
  char target[NAME_LENGTH];
  printf("Enter the name to search for: ");
  readline(target, NAME_LENGTH, stdin);

  unsigned short found = 0;
  for (unsigned int i = 0; i < arr->count; i++) {
    // search for partial case case-insensitive matches
    if (strcasestr(arr->students[i].name, target) != NULL) {
      printStudent(&arr->students[i]);
      found = 1;
    }
  }

  if (!found) printf("No student found with name %s\n", target);
}

void greetUser() {
  printf("Welcome to the Student Management System!\n");
  printf("Manage student records with ease.\n");
  printf("-------------------------------------------------\n");
}

void printCommands() {
  printf("\nStudent Management System\n");
  printf("1: Add Student\n");
  printf("2: Search by ID\n");
  printf("3: Search by Name\n");
  printf("4: Delete Student\n");
  printf("5: Update Student\n");
  printf("6: Print All Students\n");
  printf("0: Exit\n");
  printf("Enter your choice: ");
}

int main() {
  greetUser();

  struct StudentArray arr;
  initStudentArray(&arr);
  unsigned short command = 1;

  while (command != 0) {
    printCommands();
    scanf("%hu", &command);
    clearInputBuffer();
    struct Student s;

    switch (command) {
      case 0:
        break;

      case 1:
        addStudent(&arr);
        break;

      case 2:
        s = searchById(&arr);
        if (s.id != 0) {
          printStudent(&s);
        }
        break;

      case 3:
        searchByName(&arr);
        break;

      case 4:
        deleteStudent(&arr);
        break;

      case 5:
        updateStudent(&arr);
        break;

      case 6:
        printStudents(&arr);
        break;
    }
  }

  printf("Goodbye!\n");

  // Clean up
  freeStudentArray(&arr);
  return 0;
}

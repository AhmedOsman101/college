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


int main() {
  printf("hello world\n");

  return 0;
}

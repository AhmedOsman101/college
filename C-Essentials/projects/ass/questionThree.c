#include <stdio.h>

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

int main() {
  struct Student s1 = {
    .id = 1,
    .name = "John",
    .marks = { 80, 85, 90 },
    .average = 0.0
  };

  printf("Before\n");
  printf("Student ID: %d\nName: %s\nAverage: %.2f\n", s1.id, s1.name, s1.average);

  calculateAverage(&s1);

  printf("\nAfter\n");
  printf("Student ID: %d\nName: %s\nAverage: %.2f\n", s1.id, s1.name, s1.average);
  return 0;
}

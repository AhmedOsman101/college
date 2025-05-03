#include <stdio.h>

struct Student {
  int id;
  char name[50];
  int marks[3];
};

int main() {
  struct Student students[3];

  // Input data
  for (int i = 0; i < 3; i++) {
    printf("Enter details for student %d:\n", i + 1);
    printf("ID: ");
    scanf("%d", &students[i].id);
    printf("Name: ");
    scanf("%s", students[i].name);

    for (int j = 0; j < 3; j++) {
      printf("Subject %d marks: ", j + 1);
      scanf("%d", &students[i].marks[j]);
    }
  }

  printf("---------------------\n");

  // Display data
  for (int i = 0; i < 3; i++) {
    printf("\nStudent %d:\n", i + 1);
    printf("ID: %d\n", students[i].id);
    printf("Name: %s\n", students[i].name);

    for (int j = 0; j < 3; j++) {
      printf("Subject %d marks: %d\n", j + 1, students[i].marks[j]);
    }
  }

  return 0;
}

#include <stdio.h>

int main() {
  int marks[15];

  for (int i = 0; i < 5; i++) {
    printf("Enter marks for student %d:\n", i + 1);

    for (int j = 0; j < 3; j++) {
      printf("Subject %d: ", j + 1);
      scanf("%d", &marks[i * 3 + j]);
    }
  }

  int* ptr = marks;

  printf("---------------------\n");


  for (int i = 0; i < 5; i++) {
    printf("Student %d marks: ", i + 1);

    for (int j = 0; j < 3; j++) {
      printf("%d ", *ptr);
      ptr++;
    }

    printf("\n");
  }

  return 0;
}

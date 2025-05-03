#include <stdio.h>

int main() {
  int studentId = 100;
  int* idPtr = &studentId;

  printf("student ID before edit: %d\n", studentId);

  *idPtr = 101;

  printf("student ID after edit (var): %d\n", studentId);
  printf("student ID after edit (pointer): %d\n", *idPtr);
  return 0;
}

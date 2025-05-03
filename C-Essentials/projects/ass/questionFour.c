#include <stdio.h>

int main() {
  // Declare an integer variable and initialize it
  int studentId = 100;

  // Declare an integer pointer and initialize it to point to the memory address of studentId
  int* idPtr = &studentId;

  // Print the initial value of studentId using the variable name
  printf("student ID before edit: %d\n", studentId);

  // Change the value of the variable studentId using the pointer
  // The '*' operator dereferences the pointer, accessing the value at the memory address it points to
  *idPtr = 101;

  // Print the updated value of studentId using the variable name
  printf("student ID after edit (var): %d\n", studentId);

  // Print the updated value of studentId using the pointer dereference
  // This shows that the value pointed to by idPtr has also changed
  printf("student ID after edit (pointer): %d\n", *idPtr);

  return 0;
}

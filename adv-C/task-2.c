#include <stdio.h>
#include <stdbool.h>

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

// cool trick that I learned
void xorSwap(int *x, int *y) {
  *x ^= *y; // x = x ^ y
  *y ^= *x; // y = y ^ x = y ^ x ^ y = x (y is cancelled out)
  *x ^= *y; // x = x ^ y = x ^ y ^ x = y (x is cancelled out)
}

void square(int *x) {
  *x = (*x) * (*x);
}

void celsius2Fahrenheit(double c, double *f) {
  *f = (1.8 * c) + 32; // 9/5 = 1.8
}

void decompose(double num, long *integer, double *decimal) {
  *integer = (int)num;
  *decimal = num - (*integer);
}

int *larger(int *a, int *b) {
  return *a > *b ? a : b;
}

void bubbleSort(int arr[], const int length, int *min, int *max) {
  int result[length];
  // copy the original array into the result array to prevent modification.
  for (int i = 0; i < length; i++) result[i] = arr[i];

  for (int i = 0; i < length; i++) {
    bool isSorted = true;
    for (int j = 0; j < length - i - 1; j++) {
      if (result[j] > result[j + 1]) {
        int temp = result[j];
        result[j] = result[j + 1];
        result[j + 1] = temp;
        isSorted = false;
      }
    }
    // if we didn't swap anything, then the array is already sorted.
    if (isSorted) break;
  }
  *min = result[0];
  *max = result[length - 1];
}

void classifyNumbers(int arr[], const int length, int *zeros, int *negatives, int *positives) {
  *zeros = *negatives = *positives = 0;

  for (int i = 0; i < length; i++) {
    if (arr[i] < 0) *negatives += 1;
    if (arr[i] == 0) *zeros += 1;
    if (arr[i] > 0) *positives += 1;
  }
}

void reverse(int arr[], const int length) {
  int *start = arr;
  int *end = arr + length - 1;
  int count = length % 2 == 0 ? length / 2 : (length - 1) / 2;

  for (int i = 0; i < count; i++) {
    xorSwap(start, end); // swap the values
    start++;
    end--;
  }
}

/* Does that really need its own question and function???????? */
void setValue(int **ptrPtr, int v) {
  **ptrPtr = v;
}

void sumRow(int arr[2][3]) {
  int (*row)[3] = arr;

  for (int i = 0; i < 2; i++) {
    int sum = 0;
    printf("sum for row %d: ", i + 1);
    for (int j = 0; j < 3; j++) sum += (*row + (i == 0 ? 0 : 3))[j];
    printf("%d\n", sum);
  }
}

void zeroColumn(int arr[2][3], int target) {
  int (*row)[3] = arr;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      if (j == target) {
        (*row + (i == 0 ? 0 : 3))[j] = 0;
      }
    }
  }
}

int main(int argc, char **argv) {

  printf("===== Swap =====\n");
  int x = 2;
  int y = 4;
  printf("x: %d, y: %d (origin)\n", x, y);
  swap(&x, &y);
  printf("x: %d, y: %d (temp swap)\n", x, y);
  xorSwap(&x, &y);
  printf("x: %d, y: %d (xor swap)\n", x, y);


  printf("===== Square =====\n");
  printf("y = %d", y);
  square(&y);
  printf(", y^2 = %d\n", y);


  printf("===== Celsius to Fahrenheit =====\n");
  double c = 20, f;
  celsius2Fahrenheit(c, &f);
  printf("c: %.1f, f: %.1f\n", c, f);


  printf("===== Decompose =====\n");
  double z = 5.89, decimal;
  long integer;
  decompose(z, &integer, &decimal);
  printf("z: %.3f, integer: %ld, decimal: %.3f\n", z, integer, decimal);


  printf("===== Larger =====\n");
  int *bigger = larger(&x, &y);
  printf("x: %d, y: %d, larger: %d\n", x, y, *bigger);


  printf("===== Sort =====\n");
  int min, max, numbers[] = {4, 8, 9, 7, 5, 2, 1, 6, 3, 0};
  bubbleSort(numbers, 10, &min, &max);
  printf("min: %d, max: %d\n", min, max);


  printf("===== Count zeros, negatives, and positives =====\n");
  int zeros, negatives, positives, mixedNumbers[] = {2, 0, -3, -5, 4, -2, 3, -1, 1, -4, 5};
  classifyNumbers(mixedNumbers, 11, &zeros, &negatives, &positives);
  printf("negatives: %d, zeros: %d, positives: %d\n", negatives, zeros, positives);


  printf("===== Reverse =====\n");
  for (int i = 0; i < 10; i++) printf("%d ", numbers[i]);
  printf("\n");
  reverse(numbers, 10);
  for (int i = 0; i < 10; i++) printf("%d ", numbers[i]);
  printf("\n");


  printf("===== Ptr to Ptr =====\n");
  int a = 10;
  int *ptr = &a;
  int **ptrPtr = &ptr;
  setValue(ptrPtr, 25);
  printf("a: %d, ptr: %d, ptrPtr: %d\n", a, *ptr, **ptrPtr);


  printf("===== Row Sum =====\n");
  int matrix[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
  };
  sumRow(matrix);


  printf("===== Column Zero =====\n");
  zeroColumn(matrix, 1);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) printf("%d ", matrix[i][j]);
    printf("\n");
  }
}

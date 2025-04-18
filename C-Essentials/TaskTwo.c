#include <stdio.h>

/*
Q1. Write a C program that does the following using arrays:
1. Accept 5 integers from the user and store them in an array.
2. Find and display the largest number in the array.
3. Calculate and print the sum of all elements
*/
void q1() {
  int nums[5], sum = 0, largest;

  printf("Enter 5 numbers: ");

  for (int i = 0; i < 5; i++) scanf("%d", &nums[i]);

  largest = nums[0]; // set the first element as the pivot

  for (int i = 0; i < 5; i++) {
    int n = nums[i];

    sum += n;

    if (n > largest) largest = n;
  }

  printf("Sum: %d\nLargest number: %d\n", sum, largest);
}

/*
Q2. Accept and Print Array Elements
- Write a C program to accept 10 integers from the user and print them in the same order.
*/
void q2() {
  int n;

  printf("Enter 10 numbers: ");

  for (int i = 0; i < 10; i++) {
    scanf("%d", &n);
    printf("%d ", n);
  }

  printf("\n");
}

/*
Q3. Reverse an Array
- Accept N numbers from the user, store them in an array, and print them in reverse order.
*/
void q3() {
  int len;

  printf("Enter the array's length: ");
  scanf("%d", &len);

  int nums[len];

  printf("Enter the numbers: ");

  for (int i = 0; i < len; i++) scanf("%d", &nums[i]);

  printf("Array elements in reverse: ");

  for (int i = len - 1; i >= 0; i--) printf("%d ", nums[i]);

  printf("\n");
}

/*
Q4. Find the Sum of Array Elements
- Write a program to compute the sum of all elements in an array.
*/
void q4() {
  int nums[5], sum = 0;

  printf("Enter 5 numbers: ");

  for (int i = 0; i < 5; i++) scanf("%d", &nums[i]);

  for (int i = 0; i < 5; i++) {
    int n = nums[i];
    sum += n;
  }

  printf("Sum: %d\n", sum);
}

/*
Q5. Find the Largest and Smallest Element
- Accept N numbers and find the largest and smallest number in the array.
*/
void q5() {
  int len, largest, smallest;

  printf("Enter the array's length: ");
  scanf("%d", &len);

  int nums[len];

  printf("Enter the numbers: ");

  for (int i = 0; i < len; i++) scanf("%d", &nums[i]);

  largest = nums[0]; // set the first element as the pivot
  smallest = nums[0]; // set the first element as the pivot

  for (int i = 0; i < 5; i++) {
    int n = nums[i];

    if (n > largest) largest = n;

    if (n < smallest) smallest = n;
  }

  printf("Largest number: %d\nSmallest number: %d\n", largest, smallest);
}

/*
Q6. Count Even and Odd Numbers
- Accept N numbers, count and display how many are even and how many are odd.
*/
void q6() {
  short len, n, even = 0, odd = 0;

  printf("Enter the length: ");
  scanf("%hd", &len); // NOTE: use %hd for short integer

  printf("Enter the numbers: ");

  for (short i = 0; i < len; i++) {
    scanf("%hd", &n);

    n % 2 == 0 ? even++ : odd++;
  }

  printf("Even: %hd\nOdd: %hd\n", even, odd);
}

/*
Q7. Sort an Array in Ascending Order
- Accept N numbers, sort them in ascending order, and display the sorted array.
*/

void bubbleSort(int arr[], const int len, const char mode) {
  for (int i = 0; i < len; i++) {
    short swapped = 0;

    for (int j = i; j < len; j++) {
      int temp;

      if (mode == 'a') { // mode "a" for decending order
        if (arr[j] < arr[i]) {
          temp = arr[j];
          arr[j] = arr[i];
          arr[i] = temp;
          swapped = 1; // Set the flag if a swap happened
        }
      } else if (mode == 'd') { // mode "d" for ascending order
        if (arr[i] < arr[j]) {
          temp = arr[i];
          arr[i] = arr[j];
          arr[j] = temp;
          swapped = 1; // Set the flag if a swap happened
        }
      }
    }

    // If no swaps occurred in this iteration, the array is sorted
    if (swapped == 0) break;
  }
}

void q7() {
  int len;

  printf("Enter the length: ");
  scanf("%d", &len);

  int nums[len];
  printf("Enter the numbers: ");

  for (int i = 0; i < len; i++) scanf("%d", &nums[i]);

  bubbleSort(nums, len, 'a'); // modifies the original array

  printf("Sorted Array (asc): ");

  for (int i = 0; i < len; i++) printf("%d ", nums[i]);

  printf("\n");
}

void q8() {}

void q9() {}

void q10() {}

int main() {
  // q1();
  // q2();
  // q3();
  // q4();
  // q5();
  // q6();
  q7();
  // q8();
  // q9();
  // q10();
  return 0;
}

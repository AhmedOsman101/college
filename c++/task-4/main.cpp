#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

const array<int, 5> nums = {50, 10, 30, 70, 25};

template<typename T, size_t N>
void printArray(const array<T, N> &local) {
  for (size_t i = 0; i < N; i++) cout << local[i] << " ";

  printf("\n");
}

template<typename T, size_t N>
void bubbleSort(std::array<T, N> &arr, const char mode = 'a') {
  size_t len = arr.size();

  for (size_t i = 0; i < len; i++) {
    bool swapped = false;

    for (size_t j = 0; j < len - i - 1; j++) {
      T temp;

      if (mode == 'a') { // mode "a" for ascending order
        if (arr[j + 1] < arr[j]) {
          temp = arr[j + 1];
          arr[j + 1] = arr[j];
          arr[j] = temp;
          swapped = true; // Set the flag if a swap happened
        }
      } else if (mode == 'd') { // mode "d" for decending order
        if (arr[j] < arr[j + 1]) {
          temp = arr[j];
          arr[j] = arr[j + 1];
          arr[j + 1] = temp;
          swapped = true; // Set the flag if a swap happened
        }
      }
    }

    // If no swaps occurred in this iteration, the array is sorted
    if (!swapped) break;
  }
}


// Find the sum and average of one dimensional integer array.
void q1() {
  int sum = 0;

  for (int i = 0; i < 5; i++) sum += nums[i];

  float average = sum / 5.0;

  printf("Sum: %d, Average: %.2f\n", sum, average);
}

// swap first and last element of an integer 1-d array.
void q2() {
  auto local = nums;
  int temp = local[4];
  local[4] = local[0];
  local[0] = temp;

  // Easier solution:
  // swap(local[4], local[0]);

  printArray(local);
}

// reverse the element of an integer 1-D array.
void q3() {
  auto local = nums;
  array<int, 5> reversed;

  for (int i = 0; i < 5; i++) reversed[4 - i] = local[i];

  // Easier solution:
  reverse(local.rbegin(), local.rend());

  printArray(local);
  printArray(reversed);
}

// find the largest and smallest element of an array.
void q4() {
  auto local = nums;
  bubbleSort(local);
  printf("Smallest: %d, Biggest: %d\n", local[0], local[4]);
  printArray(local);
}

// Factorial
int factorial(int n) {
  int result = 1;

  for (int i = 1; i <= n; i++) result *= i;

  return result;
}

void smaller(int &x, int &y) {
  x <= y ? x = 0 : y = 0;
}

double power(double base, int p = 2) {
  double res = 1;
  for (int i = 0; i < p; i++) res *= base;
  return res;
}

double sum(double x, double y) {
  return x + y;
};
double subtract(double x, double y) {
  return x - y;
};
double multiply(double x, double y) {
  return x * y;
};
double divide(double x, double y) {
  if (y == 0) {
    fprintf(stderr, "Error: Cannot divide by zero.\n");
    exit(1);
  }

  return x / y;
};

int showChoice() {
  static bool welcomeShowed = false;

  if (!welcomeShowed) {
    printf("### Welcome to Super Simple Calculator ###\n");
    welcomeShowed = true;
  }

  int choice;

  printf("Choose an operation\n");
  printf("(1) Addition\n");
  printf("(2) Subtraction\n");
  printf("(3) Multiplication\n");
  printf("(4) Division\n");
  printf("(0) Exit\n");
  printf("Enter your choice: ");
  cin >> choice;

  if (choice <= 4 && choice >= 0) return choice;

  return -1;
}

void calculator() {
  int choice = showChoice();

  while (choice != 0) {
    double x, y;

    switch (choice) {
      case 1:
        cout << "Enter x and y: "; cin >> x >> y;
        printf("%2.lf + %2.lf = %2.lf\n", x, y, sum(x, y));
        break;

      case 2:
        cout << "Enter x and y: "; cin >> x >> y;
        printf("%2.lf - %2.lf = %2.lf\n", x, y, subtract(x, y));
        break;

      case 3:
        cout << "Enter x and y: "; cin >> x >> y;
        printf("%2.lf * %2.lf = %2.lf\n", x, y, multiply(x, y));
        break;

      case 4:
        cout << "Enter x and y: "; cin >> x >> y;
        printf("%2.lf / %2.lf = %2.lf\n", x, y, divide(x, y));
        break;

      default:
        fprintf(stderr, "Invalid operation!\n");
        break;
    }

    printf("\n");
    choice = showChoice();
  }

  printf("Goodbye!\n");
}

int main() {
  printf("\r===    Question 1 (sum/avg of array )    ===\n");
  q1();

  printf("\n===  Question 2 (palindrome number)      ===\n");
  q2();

  printf("\n===  Question 3 (reverse 1-D array)      ===\n");
  q3();

  printf("\n===  Question 4 (biggest/smallest item)  ===\n");
  q4();

  printf("\n===  Question 5 (Factorial)              ===\n");
  int n; printf("Enter n: "); cin >> n;
  cout << factorial(n) << "\n";

  printf("\n===  Question 6 (Smaller to zero)        ===\n");
  int x = 5, y = 7;
  printf("x: %d, y: %d\n", x, y);
  smaller(x, y);
  printf("x: %d, y: %d\n", x, y);

  printf("\n===  Question 7 (power)                  ===\n");
  double base; int p = 2; printf("Enter base and power: "); cin >> base >> p;
  cout << power(base, p) << "\n";

  printf("\n===  Question 8 (calculator)             ===\n");
  calculator();

  return 0;
}

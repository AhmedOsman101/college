#include <cmath>
#include <iostream>
#include <string>

using namespace std;

/*
Read a three-digit integer n.
Calculate the sum of digits of the difference between a number and its reversed form.
*/
void q1() {
  string input;
  cout << "Enter a 3-digit number: ";
  cin >> input;

  string reversed(input.rbegin(), input.rend());
  int n = stoi(input), reverse = stoi(reversed);

  int diff = n - reverse;
  string diffString = to_string(diff);

  int sum = 0;

  for (size_t i = 0; i < diffString.length(); i++) {
    sum += diffString[i] - '0'; // convert from ascii to the digit value
  }

  printf("%d\n", sum);
}

// palindrome number
void q2() {
  string n;
  cout << "Enter a number: "; cin >> n;
  bool isPalindrome = true;
  size_t len = n.length();

  for (size_t i = 0; i < len / 2; i++) {
    if (n[i] != n[len - i - 1]) {
      isPalindrome = false;
      break;
    }
  }

  printf("%sPalindrome\n", isPalindrome ? "" : "Not ");

}

// day number to date (use switch)
void q3() {
  int date;
  cout << "Enter a day: "; cin >> date;

  int day = date % 30;
  day = day == 0 ? 1 : day; // handle first day of the month
  printf("Month %.0f, Day %d\n", ceil(date / 30.0), day); // easier solution

  switch ((int) ceil(date / 30.0)) {
    case 1:
      printf("Month 1, Day %d\n", day);
      break;

    case 2:
      printf("Month 2, Day %d\n", day);
      break;

    case 3:
      printf("Month 3, Day %d\n", day);
      break;

    case 4:
      printf("Month 4, Day %d\n", day);
      break;

    case 5:
      printf("Month 5, Day %d\n", day);
      break;

    case 6:
      printf("Month 6, Day %d\n", day);
      break;

    case 7:
      printf("Month 7, Day %d\n", day);
      break;

    case 8:
      printf("Month 8, Day %d\n", day);
      break;

    case 9:
      printf("Month 9, Day %d\n", day);
      break;

    case 10:
      printf("Month 10, Day %d\n", day);
      break;

    case 11:
      printf("Month 11, Day %d\n", day);
      break;

    case 12:
      printf("Month 12, Day %d\n", day);
      break;

    default:
      printf("Invalid date\n");
      break;
  }
}

// Tax rate by income (use switch)
void q4() {
  int income; cout << "Enter income: "; cin >> income;
  int tax;

  switch (income / 10000) {
    case 0:
    case 1:
      tax = 0;
      break;

    case 2:
    case 3:
    case 4:
      tax = 5;
      break;

    case 5:
    case 6:
    case 7:
      tax = 10;
      break;

    case 8:
    case 9:
      tax = 15;
      break;

    default:
      tax = 20;
      break;
  }

  printf("Tax Rate: %d%%\n", tax);
}

// Next calendar date (no loops)
void q5() {
  int day, month, year;

  cout << "Enter the date (d m y): ";
  cin >> day >> month >> year;

  switch (month) {
    case 2:
      if (year % 4 == 0 && day < 29) day++;
      else if (day < 28) day++;
      else {
        day = 1;
        month++;
      }

      break;

    case 4:
    case 5:
    case 9:
    case 11:
      if (day == 30) {
        day = 1;
        month++;
      } else day++;

      break;

    case 12:
      if (day == 31) {
        day = 1;
        month = 1;
        year++;
      } else day++;

      break;


    default:
      if (day == 31) {
        day = 1;
        month++;
      } else day++;

      break;
  }


  printf("%i %i %i\n", day, month, year);
}

int main() {
  printf("===    Question 1 (sum of digits)    ===\n");
  q1();
  printf("\n===  Question 2 (palindrome number)  ===\n");
  q2();
  printf("\n===  Question 3 (day number to date) ===\n");
  q3();
  printf("\n===  Question 4 (Tax rate by income) ===\n");
  q4();
  printf("\n===  Question 5 (Next calendar date) ===\n");
  q5();

  return 0;
}

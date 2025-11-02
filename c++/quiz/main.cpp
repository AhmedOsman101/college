#include <iostream>

using namespace std;

void q1() {
  int a, b, c, LHS, largest;

  cout << "Enter three numbers (A B C): ";
  cin >> a >> b >> c;

  if (a < b) LHS = b;
  else LHS = a;

  if (LHS < c) largest = c;
  else largest = LHS;

  cout << largest << " is the largest\n";
}

void q2() {
  int x, y;
  cout << "Enter x and y: ";
  cin >> x >> y;

  if (x == 0 && y == 0) {
    cout << "At origin point\n";
  } else if (x == 0 && y != 0) {
    cout << "At y-axis\n";
  } else if (x != 0 && y == 0) {
    cout << "At x-axis\n";
  } else if (x < 0 && y > 0) {
    cout << "At Quadrant 1\n";
  } else if (x < 0 && y > 0) {
    cout << "At Quadrant 2\n";
  } else if (x < 0 && y < 0) {
    cout << "At Quadrant 3\n";
  } else {
    cout << "At Quadrant 4\n";
  }
}


void q3() {
  int day, month, year;

  cout << "Enter the date (d m y): ";
  cin >> day >> month >> year;

  switch (month) {
    case 2:
      if (year % 4 == 0) {
        printf("I'm here\n");

        if (day < 29) day++;
        else {
          day = 1;
          month++;
        }
      } else {
        if (day < 28) day++;
        else {
          day = 1;
          month++;
        }
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


void q4() {
  int number;
  cout << "Enter the number: ";
  cin >> number;
  printf("%d %d %d", number / 10, (number / 10) % 10, (number % 100) / 10);

}


int main() {
  // cout << "First question: find biggest of three numbers\n";
  // q1();
  cout << "Fourth question\n";
  q4();

  return 0;
}

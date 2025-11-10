#include <cmath>
#include <iostream>

using namespace std;


int factorial(int n) {
  if (n <= 2) return n;

  int result = 1;

  for (int i = 2; i <= n; i++) result *= i;

  return result;
}

int main() {
  int x = 3, n;
  double y = 0;
  cout << "Enter upper bound: ";
  cin >> n;

  for (int i = 1; i < n; i++) {
    y += pow((5 + x) / (2 * x), i) * (1.0 / factorial(i));
  }

  cout << "y = " << y << endl;

  return 0;
}

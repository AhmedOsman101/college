#include <cmath>
#include <iostream>

using namespace std;


unsigned long long factorial(unsigned long long n) {
  if (n <= 2) return n;

  unsigned long long result = 1;

  for (unsigned long long i = 2; i <= n; i++) result *= i;

  return result;
}

int main() {
  unsigned long long x = 3, n;
  double y = 0;
  cout << "Enter upper bound: ";
  cin >> n;
  printf("%llu\n", factorial(n));

  for (int i = 1; i < n; i++) {
    y += pow((5 + x) / (2 * x), i) * (1.0 / factorial(i));
  }

  return 0;
}

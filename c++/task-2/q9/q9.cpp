#include <iostream>

using namespace std;

int main() {
  int n;
  cout << "Enter limit: ";
  cin >> n;

  for (int i = 2; i <= n; i++) {
    bool isPrime = true;

    for (int j = 2; j < i; j++) {
      if (i % j == 0) {
        isPrime = false;
        break;
      }
    }

    if (isPrime) printf("%d\n", i);
  }

  return 0;
}

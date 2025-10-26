#include <iostream>

using namespace std;

int main() {
  float c;
  cout << "Enter temprature in Celsius: ";
  cin >> c;

  printf("%.2fc => %.2ff \n", c, (c * 1.8) + 32);

  return 0;
}

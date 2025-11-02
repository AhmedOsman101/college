#include <iostream>

using namespace std;


void q1() {
  for (int i = 1; i <= 3; i++) printf("%d²: %d\n", i, i * i);
}

void q2() {
  for (int i = 0; i <= 5; i++) {
    for (int j = 0; j < i; j++) {
      printf("* ");
    }

    printf("\n");
  }
}

int main() {
  q2();
  return 0;
}

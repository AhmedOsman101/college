#include <cstdio>

int main() {
  int sum = 0;
  printf("Iteration\tSum\n");
  printf("------------------------------------------\n");

  for (int i = 1; i <= 10; i++) {
    if (i % 2 != 0) sum += i;

    printf("%-8d\t%-8d\n", i, sum);
  }

  return 0;
}

#include <cstdio>

int main() {
  printf("Iteration\tValue of i\n");
  printf("------------------------------------------\n");

  for (int i = 0; i < 5; i++) {
    printf("%-8d\t%-8d\n", i, i + 1);
  }

  return 0;
}

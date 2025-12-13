#include <iostream>
#include <string>

using namespace std;

int main() {
  char str[] = "A string";
  char *ptr = str;

  printf("%c %p %c\n", *ptr, ptr, ptr[3]);
  return 0;
}

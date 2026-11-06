#include <stdio.h>
#include <stdbool.h>

int square(int x) {
  return x * x;
}

double celsius2Fahrenheit(double c) {
  return (1.8 * c) + 32; // 9/5 = 1.8
}

bool isPrime(int x) {
  for (int i = 2; i < x / 2; i++) {
    if (i == x) continue;
    if (x % i == 0) return false;
  }
  return true;
}

char toUpper(char c) {
  return c + 32;
}

/** Takes an integer number and print its binary representation in reverse order */
void printBinaryReversed(unsigned int v) {
  do {
    putchar('0' + (v & 1u));
    v >>= 1;
  } while (v);
}

unsigned int gcd(unsigned int a, unsigned int b) {
  while (b) {
    unsigned int temp = a % b;
    a = b;
    b = temp;
  }
  return a;
}

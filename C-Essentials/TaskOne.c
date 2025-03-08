#include <stdio.h>

void q1() {
  int width, length;
  scanf("%i %i", &width, &length);

  double area = width * length;

  printf("area = %d * %d = %.2f\n", width, length, area);
}

void q2() { // solution for Questions 2 and 6
  int n;
  scanf("%i", &n);

  printf(n % 2 == 0 ? "Even\n" : "Odd\n");
}

void q3() {
  for (int i = 1; i <= 10; i++)
    printf("%i\n", i);
}

void q4() {
  int a, b;

  scanf("%i %i", &a, &b);

  printf("a + b = %i\na - b = %i\na * b = %i\na / b = %.2f\n",
    a + b,
    a - b,
    a * b,
    a / (b * 1.0)
  );
}

void q5() {
  float grade;
  scanf("%f", &grade);

  if (grade <= 100 && grade >= 90) printf("A\n");
  else if (grade <= 80 && grade >= 89) printf("B\n");
  else if (grade <= 70 && grade >= 79) printf("C\n");
  else if (grade <= 60 && grade >= 69) printf("D\n");
  else printf("Fail\n");
}

int main() {
  // q1();
  // q2();
  // q3();
  // q4();
  // q5();
  return 0;
}

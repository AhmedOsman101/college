import java.io.PrintStream;
import java.util.Scanner;

class Task4 {
  // `static final` defines a constant value
  static final Scanner stdin = new Scanner(System.in);
  static final PrintStream stdout = System.out;
  static final PrintStream stderr = System.err;

  public static void task1() {
    stdout.print("Enter the number a: ");
    int a = stdin.nextInt();

    stdout.print("Enter the number b: ");
    int b = stdin.nextInt();

    if (a == 1 && (b == 1 || b == 2)) stdout.println("B " + b);
    else stdout.println("A " + a);
  }

  public static void task2() {
    stdout.print("Enter the base: ");
    int base = stdin.nextInt();

    stdout.print("Enter the power: ");
    int power = stdin.nextInt();

    int result = 1;

    for (int i = 0; i < power; i++) result *= base;

    stdout.printf("  %d^%d = %d\n", base, power, result);
  }

  public static void task3() {
    stdout.print("Enter a number: ");
    int number = stdin.nextInt();

    stdout.printf("The square root of %d is %.2f\n", number, Math.sqrt(number));
  }

  public static void task4() {
    stdout.print("Enter a number: ");
    int number = stdin.nextInt();

    for (int i = 1; i <= number; i++) {
      if (number % i == 0) stdout.printf("%d ", i);
    }

    stdout.println();
  }

  public static void task5() {
    for (int i = 1; i <= 12; i++) {
      for (int j = i; j <= 12; j++) {
        stdout.printf("%02d x %02d = %03d; ", i, j, i * j);
      }

      stdout.println();
    }

  }

  public static int factorial(int n) {
    int res = 1;

    for (int i = 2; i <= n; i++) res *= i;

    return res;
  }

  public static void task6() {
    stdout.print("Enter a number: ");
    int num = stdin.nextInt();

    stdout.printf("%d! = %d\n", num, factorial(num));
  }

  private static boolean isPrime(int number) {
    if (number <= 1) return false; // 0, 1, and negatives are not prime

    if (number == 2) return true; // 2 is prime

    if (number % 2 == 0) return false; // skip even numbers

    for (int i = 3; i <= (int) Math.sqrt(number); i += 2) {
      if (number % i == 0) return false;
    }

    return true;
  }

  public static void task7() {
    stdout.print("Enter the start: ");
    int start = stdin.nextInt();

    stdout.print("Enter the end: ");
    int end = stdin.nextInt();

    int primes = 0;

    for (int i = start; i <= end; i++) {
      if (isPrime(i)) {
        primes++;
        stdout.printf("%d ", i);
      }
    }

    if (0 < primes) stdout.println("Are Prime Numbers");
    else stdout.println("There are no primes in this range");
  }

  public static void task8() {
    String answer = "";
    int zeros = 0, positives = 0, negatives = 0;

    while (!"exit".equals(answer)) {
      stdout.print("Enter a number or 'exit' to quit: ");
      answer = stdin.nextLine().toLowerCase().trim();

      if ("exit".equals(answer)) break;

      try {
        int maybeNumber = Integer.parseInt(answer);

        if (maybeNumber > 0) positives++;

        if (maybeNumber == 0) zeros++;

        if (maybeNumber < 0) negatives++;
      } catch (NumberFormatException e) {
        stderr.printf("%s: %s\n", e.getMessage(), answer);
      }
    }

    stdout.printf("There are: %d negatives, %d zeros, and %d positives\n", negatives, zeros, positives);
  }

  public static void task9() {
    stdout.print("Enter a number: ");
    int num = stdin.nextInt();
    double sum = 0;

    for (int i = 1; i <= num; i++) sum += 1.0 / i;

    stdout.printf("Sum = %.2f\n", sum);
  }

  public static void task10() {
    int rand = (int) Math.ceil(Math.random() * 7);

    switch (rand) {
      case 1:
        stdout.println("Today is Sunday");
        break;

      case 2:
        stdout.println("Today is Monday");
        break;

      case 3:
        stdout.println("Today is Tuesday");
        break;

      case 4:
        stdout.println("Today is Wednesday");
        break;

      case 5:
        stdout.println("Today is Thursday");
        break;

      case 6:
        stdout.println("Today is Friday");
        break;

      case 7:
        stdout.println("Today is Saturday");
        break;

      default:
        stdout.println("Today is Unknown");
        break;
    }
  }

  public static void task11() {
    int score = 0;

    while (score < 5) {
      int secret = (int) Math.ceil(Math.random() * 10);

      while (true) {
        stdout.print("Guess the number (1-10): ");
        int guess = stdin.nextInt();

        if (guess == secret) {
          stdout.println("Correct!\n");
          score++;
          break;
        }

        if (guess < secret) stdout.println("Bigger");

        if (guess > secret) stdout.println("Smaller");
      }
    }

    stdout.println("You won!");
  }

  public static long fib(int n, long memo[]) {
    if (n == 0) return 0;

    if (n == 1) return 1;

    if (memo[n] != 0) return memo[n];

    memo[n] = fib(n - 1, memo) + fib(n - 2, memo);
    return memo[n];
  }

  public static void task12() {
    stdout.print("Enter a number: ");
    int n = stdin.nextInt();
    long[] memo = new long[n];

    for (int i = 1; i < n; i++) {
      long res = fib(i, memo);
      stdout.printf("%d ", res);
    }

    stdout.println();
  }

  private static String wrapsString(String s, String wrapper) {
    return wrapper + s + wrapper;
  }

  public static void task13() {
    stdout.print("Enter a number: ");
    int n = stdin.nextInt();

    for (int i = 0; i < n; i++) stdout.println("*".repeat(10));

    stdout.println("-".repeat(20));

    for (int ii = 1; ii <= n; ii++) stdout.println("*".repeat(ii));

    stdout.println("-".repeat(20));

    for (int iii = 1; iii <= n; iii++) stdout.println(" ".repeat(n - iii) + "*".repeat(iii));

    stdout.println("-".repeat(20));

    for (int iv = 0; iv < n; iv++) {
      stdout.println(" ".repeat(n - (iv + 1)) + "*".repeat((iv * 2) + 1));
    }

    stdout.println("-".repeat(20));

    for (int v = 0; v < n; v++) stdout.println(Integer.toString(v + 1).repeat((v * 2) + 1));

    stdout.println("-".repeat(20));
    String vi_string = "";

    for (int vi = 1; vi <= n; vi++) {
      if (vi_string.equals("")) vi_string = Integer.toString(vi);
      else vi_string = wrapsString(vi_string, Integer.toString(vi));

      stdout.println(vi_string);
    }

    stdout.println("-".repeat(20));
  }

  public static void task14() {
    stdout.print("Enter a number: ");
    int n = stdin.nextInt();
    double result = 0.0;

    for (int i = 1; i <= n; i++) {
      if (i % 2 == 1) result += (1.0 / i);
      else result -= (1.0 / i);
    }

    stdout.printf("ln(2) ≈ %.6f (after %d terms)\n", result, n);
  }

  public static void task15() {
    stdout.print("Enter a number: ");
    String str = stdin.nextLine().trim();
    int len = str.length();
    char[] reversed = new char[len];

    for (int i = 0; i < len; i++) {
      reversed[i] = str.charAt(len - i - 1);
    }

    stdout.printf("%s -> %s\n", str, new String(reversed));
  }

  public static void task16() {
    stdout.print("Enter x: ");
    double x = stdin.nextDouble();

    stdout.print("Enter a positive number: ");
    int n = stdin.nextInt();

    double result = 0.0;
    boolean isSum = true;

    for (int i = 1; i <= n; i += 2) {
      if (isSum) result += Math.pow(x, i) / factorial(i);
      else result -= Math.pow(x, i) / factorial(i);

      isSum = !isSum;
    }

    stdout.printf("sin(%.4f) = %.4f (after %d terms)\n", x, result, n);
  }

  public static void main(String[] args) {
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();
    task9();
    task10();
    task11();
    task12();
    task13();
    task14();
    task15();
    task16();

    stdin.close();
  }


}

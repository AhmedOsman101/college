import java.io.PrintStream;
import java.util.Scanner;

class Task2 {
  // `static final` defines a constant value
  static final Scanner stdin = new Scanner(System.in);
  static final PrintStream stdout = System.out;

  public static void task1() {
    stdout.println("Running task 1:");
    stdout.print("  Enter a number: ");
    int sum = 0;
    int number = stdin.nextInt();
    int len = Integer.toString(number).length();

    for (int i = 0; i < len; i++) {
      int divisor = (int) Math.pow(10, i);

      // To get the nth digit we use (number / 10^n) % 10
      int currentDigit = (number / divisor) % 10;
      sum += (int) Math.pow(currentDigit, len);
    }

    if (sum == number) {
      stdout.printf("  Number %d is an Armstrong number\n", number);
    } else {
      stdout.printf("  Number %d is not an Armstrong number\n", number, sum, number);
      stdout.printf("  %d does not equal %d\n", sum, number);
    }
  }

  public static void task2() {
    stdout.println("\nRunning task 2:");
    stdout.print("  Enter a number: ");
    double number = stdin.nextDouble();

    if (number < 0) {
      stdout.printf("  Number %.1f is negative\n", number);
    } else {
      stdout.printf("  Number %.1f is positive\n", number);
    }
  }

  public static void main(String[] args) {
    task1();
    task2();

    stdin.close();
  }
}

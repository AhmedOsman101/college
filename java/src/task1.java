import java.io.PrintStream;
import java.util.Scanner;

class Task1 {
  // `static final` defines a constant value
  static final Scanner stdin = new Scanner(System.in);
  static final PrintStream stdout = System.out;

  public static void task1() {
    stdout.println("Running task 1:");
    stdout.println("  Welcome");
    int num1 = 5;
    stdout.println("  Num1 = " + num1);
    stdout.println("  Thank u!");
  }

  public static void task2() {
    stdout.println("\nRunning task 2:");
    stdout.print("  Enter the radius: ");
    double radius = stdin.nextDouble();
    double area = Math.pow(radius, 2) * Math.PI;

    stdout.println("  Area = PI * R^2");
    stdout.printf("  Area = %.2f * %.2f^2 = %.2fm²\n", Math.PI, radius, area);
  }

  public static void main(String[] args) {
    task1();
    task2();

    stdin.close();
  }
}

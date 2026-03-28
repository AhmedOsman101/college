import java.util.Scanner;

class Task1 {
  // `static final` defines a constant value
  static final Scanner scanner = new Scanner(System.in);

  public static void tabPrint(String str, int padding) {
    String pad = " ".repeat(padding);
    System.out.print(pad + str);
  }

  public static void tabPrintln(String str, int padding) {
    String pad = " ".repeat(padding);
    System.out.println(pad + str);
  }

  public static void tabPrintf(String str, int padding, Object... args) {
    String pad = " ".repeat(padding);
    System.out.printf(pad + str, args);
  }

  // Overloads with default padding = 4
  public static void tabPrint(String str) {
    tabPrint(str, 4);
  }

  public static void tabPrintln(String str) {
    tabPrintln(str, 4);
  }

  public static void tabPrintf(String str, Object... args) {
    tabPrintf(str, 4, args);
  }

  public static void task1() {
    System.out.println("Running task 1:");
    tabPrintln("Welcome");
    int num1 = 5;
    tabPrintln("Num1 = " + num1);
    tabPrintln("Thank u!");
  }

  public static void task2() {
    System.out.println("Running task 2:");
    tabPrint("Enter the radius: ");
    double radius = scanner.nextDouble();
    double area = Math.pow(radius, 2) * Math.PI;

    tabPrintln("Area = PI * R^2");
    tabPrintf("Area = %.2f * %.2f^2 = %.2fm²\n", Math.PI, radius, area);
  }

  public static void main(String[] args) {
    task1();
    task2();

    scanner.close();
  }
}

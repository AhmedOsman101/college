import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Scanner;

public class Task6 {
  // The "final" keyword defines a constant value
  static final Scanner stdin = new Scanner(System.in);
  static final PrintStream stdout = System.out;
  static final PrintStream stderr = System.err;

  public static void task1() {
    stdout.print("Enter a year: ");
    int year = stdin.nextInt();
    stdin.nextLine(); // cleanup the '\n'
    boolean isLeap = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
    stdout.println(isLeap ? "Leap year" : "Not a leap year");
  }

  public static void task2() {
    stdout.print("Enter a day: ");
    int day = stdin.nextInt();
    stdin.nextLine(); // cleanup the '\n'
    switch (day) {
      case 1: stdout.println("Sunday"); break;
      case 2: stdout.println("Monday"); break;
      case 3: stdout.println("Tuesday"); break;
      case 4: stdout.println("Wednsday"); break;
      case 5: stdout.println("Thursday"); break;
      case 6: stdout.println("Friday"); break;
      case 7: stdout.println("Saturday"); break;
      default: stdout.println("Invalid"); break;
    }
  }

  public static void task3() {
    stdout.print("Enter traingle sides separeted by commas: ");
    String line = stdin.nextLine();
    String[] parts = line.split(",");

    int a = Integer.parseInt(parts[0].trim());
    int b = Integer.parseInt(parts[1].trim());
    int c = Integer.parseInt(parts[2].trim());

    if (a + b <= c || a + c <= b || b + c <= a) {
      stdout.println("Not a triangle");
    } else if (a == b && b == c) {
      stdout.println("Equilateral");
    } else if (a == b || b == c || a == c) {
      stdout.println("Isosceles");
    } else {
      stdout.println("Scalene");
    }
  }

  public static void task4() {
    stdout.print("Enter time in seconds: ");
    int seconds = stdin.nextInt();
    stdin.nextLine(); // cleanup the '\n'
    if (seconds < 0) {
      stderr.println("Seconds cannot be negative");
      return;
    }

    // Constants
    final int ONE_DAY = 86400, ONE_HOUR = 3600, ONE_MINUTE = 60;

    int days = seconds / ONE_DAY;
    seconds %= ONE_DAY;

    int hours = seconds / ONE_HOUR;
    seconds %= ONE_HOUR;

    int minutes = seconds / ONE_MINUTE;
    seconds %= ONE_MINUTE;

    ArrayList<String> parts = new ArrayList<>();
    if (days > 0) parts.add(days + "d");
    if (hours > 0) parts.add(hours + "h");
    if (minutes > 0) parts.add(minutes + "m");
    if (seconds > 0) parts.add(seconds + "s");

    stdout.println(parts.isEmpty() ? "0s" : String.join(" ", parts));
  }

  public static void task5() {
    stdout.print("Enter a sentence: ");
    String line = stdin.nextLine();

    String result = "";
    boolean isNewWord = true;

    for (int i = 0; i < line.length(); i++) {
      char c = line.charAt(i);

      if (c == ' ') {
        isNewWord = true;
        result += c;
      } else if (isNewWord) {
        result += Character.toUpperCase(c);
        isNewWord = false;
      } else {
        result += c;
      }
    }

    stdout.println(result);
  }

  public static void task6() {
    stdout.print("Enter some numbers: ");
    String line = stdin.nextLine();
    String[] parts = line.split(",");
    ArrayList<Integer> nums = new ArrayList<>();
    int total = 0;
    for (String part : parts) {
      int n = Integer.parseInt(part);
      nums.add(n);
      total += n;
    }

    double average = (total * 1.0) / nums.size();
    int count = 0;

    for (int n : nums) {
      if (n >= average) count++;
    }

    stdout.printf("Above average: %d\n", count);
  }

  public static void task7() {
    stdout.print("Enter a number: ");
    int n = stdin.nextInt();
    stdin.nextLine();                       // leftover '\n' — same bug as before

    if (n < 0) {
      stdout.println("n must be >= 0");
      return;
    }

    int a = 0;
    int b = 1;

    for (int i = 0; i < n; i++) {
      if (0 < i) stdout.print(" ");
      stdout.print(a);

      int next = a + b;
      a = b;
      b = next;
    }

    stdout.println();
  }

  public static void task8() {
    stdout.print("Enter a lowercase string: ");
    String text = stdin.nextLine();
    stdout.print("Enter the shift: ");
    int shift = stdin.nextInt();
    stdin.nextLine(); // cleanup the '\n'

    if (shift < 0) {
      stderr.println("Shift cannot be negative");
      return;
    }

    shift %= 26;
    String result = "";

    for (int i = 0; i < text.length(); i++) {
      char c = text.charAt(i);

      if (c >= 'a' && c <= 'z') {
        int position = c - 'a' + shift;
        if (position >= 26) position -= 26;
        result += (char)('a' + position);
      } else {
        result += c;
      }
    }

    stdout.println(result);
  }

  public static void task9() {
    stdout.print("Enter the first word: ");
    String first = stdin.nextLine();
    stdout.print("Enter the second word: ");
    String second = stdin.nextLine();

    if (first.length() != second.length()) {
      stdout.println("No");
      return;
    }

    int[] counts = new int[26];

    for (int i = 0; i < first.length(); i++) {
      counts[first.charAt(i) - 'a']++;
      counts[second.charAt(i) - 'a']--;
    }

    boolean isAnagram = true;
    for (int count : counts) {
      if (count != 0) isAnagram = false;
    }

    stdout.println(isAnagram ? "Yes" : "No");
  }

  public static void task10() {
    stdout.print("Enter a lowercase string: ");
    String text = stdin.nextLine();

    if (text.isEmpty()) {
      stderr.println("The string cannot be empty");
      return;
    }

    String result = "";
    char current = text.charAt(0);
    int count = 1;

    for (int i = 1; i < text.length(); i++) {
      char c = text.charAt(i);

      if (c == current) {
        count++;
      } else {
        result += current + "" + count;
        current = c;
        count = 1;
      }
    }

    // The loop only writes a group when the next group starts,
    // so the last group still needs to be added here.
    result += current + "" + count;

    stdout.println(result);
  }

  public static void main(String[] args) {
    stdout.println("--- Running task1 ---\n");
    task1();

    stdout.println("--- Running task2 ---\n");
    task2();

    stdout.println("--- Running task3 ---\n");
    task3();

    stdout.println("--- Running task4 ---\n");
    task4();

    stdout.println("--- Running task5 ---\n");
    task5();

    stdout.println("--- Running task6 ---\n");
    task6();

    stdout.println("--- Running task7 ---\n");
    task7();

    stdout.println("--- Running task8 ---\n");
    task8();

    stdout.println("--- Running task9 ---\n");
    task9();

    stdout.println("--- Running task10 ---\n");
    task10();

    stdin.close();
  }
}

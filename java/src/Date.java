import java.util.ArrayList;

public class Date {
  public int year;
  public int month;
  public int day;

  public Date(int year, int month, int day) {
    this.year = year;
    this.month = month;
    this.day = day;
  }

  public boolean checkMonth() {
    if (this.month < 1 || this.month > 12) {
      throw new IllegalArgumentException("Invalid month");
    }

    return true;
  }

  public boolean isLeapYear() {
    return this.year % 4 == 0 && (this.year % 100 != 0 || this.year % 400 == 0);
  }

  public boolean checkDay() {
    // All months
    if (this.day < 1 || this.day > 31) {
      throw new IllegalArgumentException("Day cannot be less than 1 or more than 31");
    }

    // 31 Days months
    if (
      this.month == 1 ||
      this.month == 3 ||
      this.month == 5 ||
      this.month == 7 ||
      this.month == 8 ||
      this.month == 10 ||
      this.month == 12
    ) {
      if (day > 31) {
        throw new IllegalArgumentException("Invalid day, this month is 31 days only");
      }
    }


    // 30 Days months
    if (
      this.month == 4 ||
      this.month == 6 ||
      this.month == 9 ||
      this.month == 11
    ) {
      if (day > 30) throw new IllegalArgumentException("Invalid day, this month is 30 days only");
    }

    if (this.month == 2) {
      if (this.isLeapYear() && this.day > 29) {
        throw new IllegalArgumentException("February is 29 days only");
      }
      if (!this.isLeapYear() && this.day > 28) {
        throw new IllegalArgumentException("February is 28 days only");
      }
    }

    return true;
  }

  public String toString() {
    return String.format("Date: %d-%d-%d", this.year, this.month, this.day);
  }

  public void print() {
    System.out.printf(
      "Year: %d, Month: %d, Day: %d\n",
      this.year,
      this.month,
      this.day
    );
  }

  public static void main(String args[]) {
    new Date(2024, 2, 29).checkDay(); // Leap year, feb 29
    new Date(2025, 10, 31).checkDay(); // 31 day for 31 day month
    System.out.println(new Date(2025, 11, 30).toString());
    new Date(2026, 2, 29).checkDay(); // Not leap year, feb 29
    new Date(2024, 2, 30).checkDay(); // Leap year, feb 30
    new Date(2025, 4, 31).checkDay(); // 31 day for 30 day month
    new Date(2025, 10, 32).checkDay(); // 32 day for 31 day month
  }
}

public class Course {
  // `static final` defines a constant value
  static final int MAX_CREDITS = 6;

  private String code;
  private String title;
  private int credits;
  private final String department;

  // Default constructor
  Course() {
    this.code = "N/A";
    this.title = "Untitled";
    this.credits = 0;
    this.department = "General";
  }

  // Parameterized constructor
  Course(String code, String title, int credits, String department) {
    this.code = code;
    this.title = title;
    this.credits = credits;
    this.department = department;
  }

  // Copy constructor
  Course(Course other) {
    this.code = other.code;
    this.title = other.title;
    this.credits = other.credits;
    this.department = other.department;
  }

  String getCode() {
    return this.code;
  }

  String getTitle() {
    return this.title;
  }

  int getCredits() {
    return this.credits;
  }

  String getDepartment() {
    return this.department;
  }

  void setCode(String code) {
    this.code = code;
  }

  void setTitle(String title) {
    this.title = title;
  }

  void setCredits(int credits) {
    if (credits < 0 || credits > MAX_CREDITS) return;
    this.credits = credits;
  }

  void print() {
    System.out.printf("  %s - %s (%d credits, %s)\n",
      this.code, this.title, this.credits, this.department);
  }
}
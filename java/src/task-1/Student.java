class Student {
  // `static` counter shared across all Student instances
  static int totalStudents = 0;

  private final int id;
  private String name;
  private int age;
  private Course[] courses; // Has-A relationship
  private int courseCount;

  // Default constructor
  Student() {
    this.id = ++totalStudents;
    this.name = "Unknown";
    this.age = 0;
    this.courses = new Course[5];
    this.courseCount = 0;
  }

  // Parameterized constructor
  Student(String name, int age) {
    this.id = ++totalStudents;
    this.name = name;
    this.age = age;
    this.courses = new Course[5];
    this.courseCount = 0;
  }

  // Copy constructor
  Student(Student other) {
    this.id = ++totalStudents;
    this.name = other.name;
    this.age = other.age;
    this.courses = new Course[other.courses.length];
    this.courseCount = other.courseCount;
    for (int i = 0; i < other.courseCount; i++) {
      this.courses[i] = new Course(other.courses[i]);
    }
  }

  int getId() {
    return this.id;
  }

  String getName() {
    return this.name;
  }

  int getAge() {
    return this.age;
  }

  int getCourseCount() {
    return this.courseCount;
  }

  static int getTotalStudents() {
    return totalStudents;
  }

  void setName(String name) {
    this.name = name;
  }

  void setAge(int age) {
    if (age < 0) return;
    this.age = age;
  }

  boolean enroll(Course course) {
    if (courseCount >= courses.length) return false;
    courses[courseCount++] = course;
    return true;
  }

  void printCourses() {
    System.out.println("  Courses for " + this.name + ":");
    if (this.courseCount == 0) {
      System.out.println("    (none)");
      return;
    }
    for (int i = 0; i < this.courseCount; i++) {
      this.courses[i].print();
    }
  }
}
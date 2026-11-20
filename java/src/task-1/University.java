public class University {
  private final String name; // `final`: name never changes
  private Student[] students; // Has-A relationship
  private Course[] courses;   // Has-A relationship
  private int studentCount;
  private int courseCount;

  // Default constructor
  University() {
    this("Unknown University");
  }

  // Parameterized constructor
  University(String name) {
    this.name = name;
    this.students = new Student[10];
    this.courses = new Course[10];
    this.studentCount = 0;
    this.courseCount = 0;
  }

  // Copy constructor
  University(University other) {
    this.name = other.name;
    this.students = new Student[other.students.length];
    this.courses = new Course[other.courses.length];
    this.studentCount = other.studentCount;
    this.courseCount = other.courseCount;
    for (int i = 0; i < other.studentCount; i++) {
      this.students[i] = new Student(other.students[i]);
    }
    for (int i = 0; i < other.courseCount; i++) {
      this.courses[i] = new Course(other.courses[i]);
    }
  }

  String getName() {
    return this.name;
  }

  boolean addCourse(Course course) {
    if (courseCount >= courses.length) return false;
    courses[courseCount++] = new Course(course);
    return true;
  }

  boolean addStudent(Student student) {
    if (studentCount >= students.length) return false;
    students[studentCount++] = new Student(student);
    return true;
  }

  void printAll() {
    System.out.println("University: " + this.name);
    System.out.println("Courses (" + this.courseCount + "):");
    for (int i = 0; i < this.courseCount; i++) {
      this.courses[i].print();
    }
    System.out.println("Students (" + this.studentCount + "):");
    for (int i = 0; i < this.studentCount; i++) {
      System.out.println("  Student[id=" + this.students[i].getId() +
        ", name=" + this.students[i].getName() +
        ", age=" + this.students[i].getAge() + "]");
      this.students[i].printCourses();
    }
  }
}
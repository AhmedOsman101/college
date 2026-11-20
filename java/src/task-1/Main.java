import java.io.PrintStream;
import java.util.Scanner;

public class Main {
  // `static final` defines a constant value
  static final Scanner stdin = new Scanner(System.in);
  static final PrintStream stdout = System.out;

  static void task1() {
    // Parameterized constructors
    Course oop = new Course("CS201", "Object-Oriented Programming", 3, "Computer Science");

    // Default constructor + setters
    Course math = new Course();
    math.setCode("MATH101");
    math.setTitle("Calculus I");
    math.setCredits(4);

    // Copy constructor
    Course oopCopy = new Course(oop);

    stdout.println("Course copy:");
    oopCopy.print();
  }

  static void task2() {
    Student alice = new Student("Alice", 20);
    Student bob   = new Student("Bob", 22);

    alice.enroll(new Course("CS201", "Object-Oriented Programming", 3, "Computer Science"));
    alice.enroll(new Course("CS202", "Data Structures", 4, "Computer Science"));
    bob.enroll(new Course("CS301", "Databases", 3, "Computer Science"));

    alice.printCourses();
    bob.printCourses();

    stdout.println("Total students: " + Student.getTotalStudents());
  }

  static void task3() {
    // Default constructor student
    Student unknown = new Student();
    unknown.setName("Charlie");
    unknown.setAge(19);
    unknown.enroll(new Course("MATH101", "Calculus I", 4, "General"));

    unknown.printCourses();

    // Copy constructor
    Student copy = new Student(unknown);
    copy.printCourses();
  }

  static void task4() {
    University uni = new University("Tech University");

    uni.addCourse(new Course("CS201", "Object-Oriented Programming", 3, "Computer Science"));
    uni.addCourse(new Course("CS202", "Data Structures", 4, "Computer Science"));
    uni.addCourse(new Course("CS301", "Databases", 3, "Computer Science"));

    Student alice = new Student("Alice", 20);
    alice.enroll(new Course("CS201", "Object-Oriented Programming", 3, "Computer Science"));
    alice.enroll(new Course("CS202", "Data Structures", 4, "Computer Science"));

    uni.addStudent(alice);

    uni.printAll();
  }

  public static void main(String args[]) {
    task1();
    task2();
    task3();
    task4();

    stdin.close();
  }
}

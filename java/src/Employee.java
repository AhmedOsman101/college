class Employee {
  private int id;
  private String firstName;
  private String lastName;
  private float salary;

  public Employee(int id, String firstName, String lastName, float salary) {
    this.id = id;
    this.firstName = firstName;
    this.lastName = lastName;
    this.salary = salary;
  }

  int getID() {
    return this.id;
  }
  String getFirstName() {
    return this.firstName;
  }
  String getLastName() {
    return this.lastName;
  }
  String getName() {
    return this.firstName + " " + this.lastName;
  }
  float getSalary() {
    return this.salary;
  }
  void setSalary(float salary) {
    this.salary = salary;
  }
  float getAnnualSalary() {
    return 12 * this.salary;
  }
  float raiseSalary(float percent) {
    this.setSalary(this.salary + (this.salary * percent));
    return this.getSalary();
  }
}

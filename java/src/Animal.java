public class Animal {
  private String name;

  public Animal(String name) { this.name = name; }
  public String getName() { return this.name; }
  public void makeSound() { System.out.println("Mooooo"); }

  public static void main(String args[]) {
    System.out.println("Default sound");
  }
}

class Dog extends Animal {
  public Dog(String name) { super(name); }
  public void makeSound() { System.out.println("Ruff Ruff"); }
}
class Cat extends Animal {
  public Cat(String name) { super(name); }
  public void makeSound() { System.out.println("Meow Meow"); }
}

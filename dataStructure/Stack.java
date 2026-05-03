import java.io.PrintStream;

class Stack<T> {
  // `static final` defines a constant value
  static final PrintStream stdout = System.out;
  static final PrintStream stderr = System.err;

  private int top;
  private int length;
  private T[] items;

  public Stack(int length) {
    this.length = length;
    this.top = -1;
    this.items = (T[]) new Object[length];
  }

  public void push(T item) {
    if (this.isFull()) stderr.println("Stack is full!");
    else {
      this.top++;
      this.items[this.top] = item;
    }
  }

  public void pop() {
    if (this.isEmpty()) stderr.println("Stack is empty!");
    else this.top--;
  }

  public int size() {
    return this.top + 1;
  }

  public int length() {
    return this.length;
  }

  public T top() throws Error {
    if (this.isEmpty()) throw new Error("Stack is empty!");
    return this.items[this.top];
  }

  public boolean isEmpty() {
    return this.top == -1;
  }

  public boolean isFull() {
    return this.top == this.length - 1;
  }

  public void display() {
    stdout.printf("[");
    for (int i = this.top; i >= 0; i--) stdout.print(" " + this.items[i]);
    stdout.println(" ]");
  }
}

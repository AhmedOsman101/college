import java.io.PrintStream;

class Stack<T> {
  // `static final` defines a constant value
  static final PrintStream stdout = System.out;
  static final PrintStream stderr = System.err;

  private int topIdx;
  private int length;
  private T[] items;

  public Stack(int length) {
    this.length = length;
    this.topIdx = -1;
    this.items = (T[]) new Object[length];
  }

  public void push(T item) {
    if (this.isFull()) stderr.println("Stack is full!");
    else {
      this.topIdx++;
      this.items[this.topIdx] = item;
    }
  }

  public void pop() {
    if (this.isEmpty()) stderr.println("Stack is empty!");
    else this.topIdx--;
  }

  public int size() {
    return this.topIdx + 1;
  }

  public T top() throws Error {
    if (this.isEmpty()) throw new Error("Stack is empty!");
    return this.items[this.topIdx];
  }

  public boolean isEmpty() {
    return this.topIdx == -1;
  }

  public boolean isFull() {
    return this.topIdx == this.length - 1;
  }

  public void display() {
    stdout.printf("[");
    for (int i = this.topIdx; i >= 0; i--) stdout.print(" " + this.items[i]);
    stdout.println(" ]");
  }
};


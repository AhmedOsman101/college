import java.io.PrintStream;

class Queue<T> {
  private int length;
  private int rear;
  private T[] items;

  // `static final` defines a constant value
  static final PrintStream stdout = System.out;
  static final PrintStream stderr = System.err;

  @SuppressWarnings("unchecked")
  public Queue(int length) {
    this.length = length;
    this.rear = -1;
    this.items = (T[]) new Object[this.length];
  }

  public void enqueue(T item) {
    if (this.isFull()) stderr.println("Queue is full!");
    else {
      this.rear++;
      this.items[this.rear] = item;
    }
  }

  public void dequeue() {
    if (this.isEmpty()) stderr.println("Queue is empty!");
    else {
      // shift the whole array.
      for (int i = 0; i < this.rear; i++) this.items[i] = this.items[i + 1];
      this.rear--;
    }
  }

  public int size() {
    return this.rear + 1;
  }

  public T front() throws Error {
    if (this.isEmpty()) throw new Error("Queue is empty!");
    return this.items[0];
  }

  public T back() throws Error {
    if (this.isEmpty()) throw new Error("Queue is empty!");
    return this.items[this.rear];
  }

  public boolean isEmpty() {
    return this.rear == -1;
  }

  public boolean isFull() {
    return this.rear == this.length - 1;
  }

  public void display() {
    stdout.printf("[");
    for (int i = 0; i <= this.rear; i++) stdout.print(" " + this.items[i]);
    stdout.println(" ]");
  }
}

class SimpleQueue<T> {
  private int frontIdx;
  private int rearIdx;
  private int length;
  private T[] items;

  // `static final` defines a constant value
  static final PrintStream stdout = System.out;
  static final PrintStream stderr = System.err;

  @SuppressWarnings("unchecked")
  public SimpleQueue(int len) {
    this.frontIdx = -1;
    this.rearIdx = -1;
    this.length = len;
    this.items = (T[]) new Object[len];
  }

  public void enqueue(T item) {
    if (this.isFull()) stderr.println("Queue is full!");
    else {
      if (this.frontIdx == -1) this.frontIdx = 0;
      this.rearIdx++;
      this.items[this.rearIdx] = item;
    }
  }

  public void dequeue() {
    if (this.isEmpty()) stderr.println("Queue is empty!");
    else {
      this.frontIdx++;
      if (this.frontIdx > this.rearIdx) {
        this.frontIdx = -1;
        this.rearIdx = -1;
      }
    }
  }

  public int size() {
    if (this.isEmpty()) return 0;
    return this.rearIdx - this.frontIdx + 1;
  }

  public T front() throws Error {
    if (this.isEmpty()) throw new Error("Queue is empty!");
    return this.items[this.frontIdx];
  }

  public T back() throws Error {
    if (this.isEmpty()) throw new Error("Queue is empty!");
    return this.items[this.rearIdx];
  }

  public boolean isEmpty() {
    return this.frontIdx == -1;
  }

  public boolean isFull() {
    return this.rearIdx == this.length - 1;
  }

  public void display() {
    stdout.print("[");
    for (int i = this.frontIdx; i <= this.rearIdx; i++) stdout.print(" " + this.items[i]);
    stdout.println(" ]");
  }
}

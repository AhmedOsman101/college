import java.io.PrintStream;

class Array<T> {
  // `static final` defines a constant value
  static final PrintStream stdout = System.out;
  static final PrintStream stderr = System.err;

  private int length; // How many items can we store
  private int size;   // Index of the last stored item
  private T[] items;
  // constructor
  public Array(int length) {
    this.items = (T[]) new Object[length];
    this.length = length;
    this.size = -1;

  }

  public void push(T item) {
    if (this.isFull()) stderr.println("Array is full!");
    else {
      this.size++;
      this.items[this.size] = item;
    }
  }

  public T pop() throws Error {
    // NOTE: The item isn't really removed, it will be overwritten in the next push.
    if (this.isEmpty()) throw new Error("Array is empty!");
    else return this.items[this.size--];
  }

  public void display() {
    stdout.printf("[");
    for (int i = 0; i <= this.size; i++) stdout.print(" " + this.items[i]);
    stdout.println(" ]");
  }

  /*
    * returns how many items are actually stored in the array.
   */
  public int getSize() {
    return this.size + 1;
  }
  /*
    * returns how many items can be stored in the array.
   */
  public int getLength() {
    return this.length;
  }

  public boolean isEmpty() {
    return this.size == -1;
  }

  public boolean isFull() {
    return this.size == this.length - 1;
  }
}

// int main() {
//   Array arr = Array<int>(5);

//   arr.push(1);
//   arr.push(2);
//   arr.push(3);
//   arr.display();

//   return 0;
// }

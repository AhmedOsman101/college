import java.io.PrintStream;

public class Main {
  static final PrintStream stdout = System.out;
  static final PrintStream stderr = System.err;

  public static void main(String[] args) {
    stdout.println("=== Testing Array ===");
    testArray();

    stdout.println("\n=== Testing Stack ===");
    testStack();

    stdout.println("\n=== Testing Queue ===");
    testQueue();

    stdout.println("\n=== Testing SimpleQueue ===");
    testSimpleQueue();

    stdout.println("\n=== Testing SingleLinkedList ===");
    testSingleLinkedList();

    stdout.println("\n=== Testing DoubleLinkedList ===");
    testDoubleLinkedList();
  }

  static void testArray() {
    Array<Integer> arr = new Array<>(5);

    stdout.println("Is empty: " + arr.isEmpty());
    arr.push(1);
    arr.push(2);
    arr.push(3);
    stdout.print("After pushing 1,2,3: ");
    arr.display();

    stdout.println("Size: " + arr.size());
    stdout.println("Length: " + arr.length());

    try {
      stdout.println("Popped: " + arr.pop());
    } catch (Error e) {
      stderr.println(e.getMessage());
    }
    stdout.print("After pop: ");
    arr.display();

    arr.push(4);
    arr.push(5);
    arr.push(6); // Should print "Array is full!"
    stdout.print("After pushing 4,5,6: ");
    arr.display();

    stdout.println("Is full: " + arr.isFull());
  }

  static void testStack() {
    Stack<Integer> stack = new Stack<>(5);

    stdout.println("Is empty: " + stack.isEmpty());
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stdout.print("After pushing 1,2,3: ");
    stack.display();

    stdout.println("Size: " + stack.size());
    stdout.println("Top: " + stack.top());

    stack.pop();
    stdout.print("After pop: ");
    stack.display();

    stack.push(4);
    stack.push(5);
    stack.push(6); // Should print "Stack is full!"
    stdout.print("After pushing 4,5,6: ");
    stack.display();

    stdout.println("Is full: " + stack.isFull());
  }

  static void testQueue() {
    Queue<Integer> queue = new Queue<>(5);

    stdout.println("Is empty: " + queue.isEmpty());
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    stdout.print("After enqueue 1,2,3: ");
    queue.display();

    stdout.println("Size: " + queue.size());
    try {
      stdout.println("Front: " + queue.front());
      stdout.println("Back: " + queue.back());
    } catch (Error e) {
      stderr.println(e.getMessage());
    }

    queue.dequeue();
    stdout.print("After dequeue: ");
    queue.display();

    queue.enqueue(4);
    queue.enqueue(5);
    queue.enqueue(6); // Should print "Queue is full!"
    stdout.print("After enqueue 4,5,6: ");
    queue.display();

    stdout.println("Is full: " + queue.isFull());
  }

  static void testSimpleQueue() {
    SimpleQueue<Integer> queue = new SimpleQueue<>(5);

    stdout.println("Is empty: " + queue.isEmpty());
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    stdout.print("After enqueue 1,2,3: ");
    queue.display();

    stdout.println("Size: " + queue.size());
    try {
      stdout.println("Front: " + queue.front());
      stdout.println("Back: " + queue.back());
    } catch (Error e) {
      stderr.println(e.getMessage());
    }

    queue.dequeue();
    stdout.print("After dequeue: ");
    queue.display();

    queue.enqueue(4);
    queue.enqueue(5);
    queue.enqueue(6); // Should print "Queue is full!"
    stdout.print("After enqueue 4,5,6: ");
    queue.display();

    stdout.println("Is full: " + queue.isFull());
  }

  static void testSingleLinkedList() {
    SingleLinkedList<Integer> list = new SingleLinkedList<>();

    stdout.println("Is empty: " + list.isEmpty());
    list.append(5);
    list.append(6);
    list.append(7);
    stdout.print("After append 5,6,7: ");
    list.display();

    stdout.println("Count: " + list.count());
    stdout.println("Search 6: " + list.search(6));
    stdout.println("Search 9: " + list.search(9));

    list.insertBefore(6, 10);
    stdout.print("After insertBefore(6, 10): ");
    list.display();

    list.deleteValue(5);
    stdout.print("After deleteValue(5): ");
    list.display();

    stdout.println("Count: " + list.count());
  }

  static void testDoubleLinkedList() {
    DoubleLinkedList<Integer> list = new DoubleLinkedList<>();

    stdout.println("Is empty: " + list.isEmpty());
    list.append(5);
    list.append(6);
    list.append(7);
    stdout.print("After append 5,6,7: ");
    list.display();

    stdout.print("Reverse: ");
    list.displayReverse();

    stdout.println("Count: " + list.count());
    stdout.println("Search 6: " + list.search(6));
    stdout.println("Search 9: " + list.search(9));

    list.insertBefore(6, 10);
    stdout.print("After insertBefore(6, 10): ");
    list.display();
    stdout.print("Reverse: ");
    list.displayReverse();

    list.deleteValue(5);
    stdout.print("After deleteValue(5): ");
    list.display();
    stdout.print("Reverse: ");
    list.displayReverse();

    stdout.println("Count: " + list.count());
  }
}

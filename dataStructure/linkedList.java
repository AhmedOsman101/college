import java.io.PrintStream;

class Node<T> {
  T data;
  Node<T> next;

  Node(T data, Node<T> next) {
    this.data = data;
    this.next = next;
  }
}

class SingleLinkedList<T> {
  static final PrintStream stdout = System.out;
  static final PrintStream stderr = System.err;

  private Node<T> head;

  public SingleLinkedList() {
    this.head = null;
  }

  public boolean isEmpty() {
    return this.head == null;
  }

  public void append(T value) {
    if (this.isEmpty()) {
      this.head = new Node<T>(value, null);
      return;
    }

    Node<T> current = this.head;
    while (current.next != null) current = current.next;
    current.next = new Node<T>(value, null);
  }

  public void display() {
    Node<T> current = this.head;
    while (current != null) {
      stdout.print(current.data + " ");
      current = current.next;
    }
    stdout.println();
  }

  public int count() {
    int c = 0;
    Node<T> current = this.head;
    while (current != null) {
      c++;
      current = current.next;
    }
    return c;
  }

  public boolean search(T value) {
    Node<T> current = this.head;
    while (current != null) {
      if (current.data.equals(value)) return true;
      current = current.next;
    }
    return false;
  }

  public void insertBefore(T item, T value) {
    if (this.isEmpty()) return;

    if (this.head.data.equals(item)) {
      Node<T> newNode = new Node<T>(value, this.head);
      this.head = newNode;
      return;
    }

    Node<T> prev = this.head;
    Node<T> current = this.head.next;
    while (current != null && !current.data.equals(item)) {
      prev = current;
      current = prev.next;
    }

    if (current != null) prev.next = new Node<>(value, current);
  }

  public void deleteValue(T value) {
    if (this.isEmpty()) return;

    if (this.head.data.equals(value)) {
      this.head = this.head.next;
      return;
    }

    Node<T> prev = this.head;
    Node<T> current = this.head.next;
    while (current != null && !current.data.equals(value)) {
      prev = current;
      current = prev.next;
    }

    if (current != null) {
      prev.next = current.next;
    }
  }
}

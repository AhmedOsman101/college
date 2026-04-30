import java.io.PrintStream;

class DNode<T> {
  T data;
  DNode<T> prev;
  DNode<T> next;

  DNode(T data, DNode<T> prev, DNode<T> next) {
    this.data = data;
    this.prev = prev;
    this.next = next;
  }
}

class DoubleLinkedList<T> {
  static final PrintStream stdout = System.out;
  static final PrintStream stderr = System.err;

  private DNode<T> head;

  public DoubleLinkedList() {
    this.head = null;
  }

  public boolean isEmpty() {
    return this.head == null;
  }

  public void append(T value) {
    if (this.isEmpty()) {
      this.head = new DNode<>(value, null, null);
      return;
    }

    DNode<T> current = this.head;
    while (current.next != null) current = current.next;
    current.next = new DNode<>(value, current, null);
  }

  public void display() {
    if (this.isEmpty()) {
      stdout.println();
      return;
    }
    DNode<T> current = this.head;
    while (current != null) {
      stdout.print(current.data + " ");
      current = current.next;
    }
    stdout.println();
  }

  public void displayReverse() {
    if (this.isEmpty()) {
      stdout.println();
      return;
    }

    DNode<T> current = this.head;
    while (current.next != null) current = current.next;
    while (current != null) {
      stdout.print(current.data + " ");
      current = current.prev;
    }
    stdout.println();
  }

  public int count() {
    int c = 0;
    DNode<T> current = this.head;
    while (current != null) {
      c++;
      current = current.next;
    }
    return c;
  }

  public boolean search(T value) {
    DNode<T> current = this.head;
    while (current != null) {
      if (current.data.equals(value)) return true;
      current = current.next;
    }
    return false;
  }

  public void insertBefore(T item, T value) {
    if (this.isEmpty()) return;

    if (this.head.data.equals(item)) {
      DNode<T> newDNode = new DNode<>(value, null, this.head);
      this.head = newDNode;
      this.head.next.prev = this.head;
      return;
    }

    DNode<T> prev = this.head;
    DNode<T> current = this.head.next;
    while (current != null && !current.data.equals(item)) {
      prev = current;
      current = prev.next;
    }

    if (current != null) {
      DNode<T> newDNode = new DNode<>(value, prev, current);
      prev.next = newDNode;
      current.prev = newDNode;
    }
    else stderr.println("Item not found!");
  }

  public void deleteValue(T value) {
    if (this.isEmpty()) return;

    if (this.head.data.equals(value)) {
      this.head = this.head.next;
      if (this.head != null) this.head.prev = null;
      return;
    }

    DNode<T> prev = this.head;
    DNode<T> current = this.head.next;
    while (current != null && !current.data.equals(value)) {
      prev = current;
      current = prev.next;
    }

    if (current != null) {
      prev.next = current.next;
      if (current.next != null) current.next.prev = prev;
    }
    else stderr.println("Value not found!");
  }
}

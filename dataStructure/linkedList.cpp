#include <iostream>

using namespace std;

template <typename T>
struct Node {
  T data;
  Node *next;
};

template <typename T>
class SingleLinkedList {
 private:
  Node<T> *head;
 public:
  SingleLinkedList() : head(nullptr) {}

  bool isEmpty() {
    return head == nullptr;
  }

  void append(T value) {
    if (isEmpty()) {
      head = new Node<T> {value, nullptr};
      return;
    }

    Node<T> *current = head;

    while (current->next != nullptr) current = current->next;
    current->next = new Node<T> {value, nullptr};
  }

  void display() {
    Node<T> *current = head;
    while (current != nullptr) {
      cout << current->data << ' ';
      current = current->next;
    }
    cout << endl;
  }

  int count() {
    int c = 0;
    Node<T> *current = head;
    while (current != nullptr) {
      c++;
      current = current->next;
    }

    return c;
  }

  bool search(T value) {
    Node<T> *current = head;
    while (current != nullptr) {
      if (current->data == value) return true;
      current = current->next;
    }

    return false;
  }

  void insertBefore(T item, T value) {
    if (isEmpty() || !search(item)) return;

    if (head->data == item) {
      Node<T> *newNode = new Node<T> {value, head};
      head = newNode;
      return;
    }

    Node<T> *prev = head;
    Node<T> *current = head->next;
    while (current != nullptr && current->data != item) {
      prev = current;
      current = prev->next;
    }

    prev->next = new Node<T> {value, current};
  }

  void deleteValue(T value) {
    if (isEmpty() || !search(value)) return;

    if (head->data == value) {
      Node<T> *temp = head;
      head = head->next;
      delete temp;
      return;
    }

    Node<T> *prev = head;
    Node<T> *current = head->next;
    while (current != nullptr && current->data != value) {
      prev = current;
      current = prev->next;
    }

    if (current->next == nullptr) prev->next = nullptr;
    else prev->next = current->next;
  }
};


int main() {
  SingleLinkedList<int> arr;
  arr.append(5);
  arr.append(6);
  arr.append(7);
  arr.deleteValue(5);
  arr.append(8);
  arr.display();
  return 0;
}

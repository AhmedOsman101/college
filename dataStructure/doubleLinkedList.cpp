#include <iostream>

using namespace std;

template <typename T>
struct DNode {
  T data;
  DNode *prev;
  DNode *next;
};


template <typename T>
class DoubleLinkedList {
 private:
  DNode<T> *head;
 public:
  DoubleLinkedList() : head(nullptr) {}
  ~DoubleLinkedList() {
    DNode<T> *current = head;

    while (current != nullptr) {
      DNode<T> *next = current->next;
      delete current;
      current = next;
    }
  }

  bool isEmpty() {
    return head == nullptr;
  }

  void append(T value) {
    if (isEmpty()) {
      head = new DNode<T> {value, nullptr, nullptr};
      return;
    }

    DNode<T> *current = head;

    while (current->next != nullptr) current = current->next;
    current->next = new DNode<T> {value, current, nullptr};
  }

  void display() {
    if (isEmpty()) return;
    DNode<T> *current = head;
    while (current != nullptr) {
      cout << current->data << ' ';
      current = current->next;
    }
    cout << endl;
  }

  void displayReverse() {
    if (isEmpty()) return;

    DNode<T> *current = head;
    while (current->next != nullptr) current = current->next;
    while (current != nullptr) {
      cout << current->data << ' ';
      current = current->prev;
    }
    cout << endl;
  }

  int count() {
    int c = 0;
    DNode<T> *current = head;
    while (current != nullptr) {
      c++;
      current = current->next;
    }

    return c;
  }

  bool search(T value) {
    DNode<T> *current = head;
    while (current != nullptr) {
      if (current->data == value) return true;
      current = current->next;
    }

    return false;
  }

  void insertBefore(T item, T value) {
    if (isEmpty()) return;

    if (head->data == item) {
      DNode<T> *newDNode = new DNode<T> {value, nullptr, head};
      head = newDNode;
      head->next->prev = head;
      return;
    }

    DNode<T> *prev = head;
    DNode<T> *current = head->next;
    while (current != nullptr && current->data != item) {
      prev = current;
      current = prev->next;
    }

    if (current != nullptr) {
      DNode<T> *newDNode = new DNode<T> {value, prev, current};
      prev->next = newDNode;
      current->prev = newDNode;
    }
  }

  void deleteValue(T value) {
    if (isEmpty()) return;

    if (head->data == value) {
      DNode<T> *temp = head;
      head = head->next;
      if (head != nullptr) head->prev = nullptr;
      delete temp;
      return;
    }

    DNode<T> *prev = head;
    DNode<T> *current = head->next;
    while (current != nullptr && current->data != value) {
      prev = current;
      current = prev->next;
    }

    if (current != nullptr) {
      prev->next = current->next;
      if (current->next != nullptr) current->next->prev = prev;
      delete current;
    }
  }
};


int main() {
  DoubleLinkedList<int> arr;
  arr.append(5);
  arr.append(6);
  arr.append(7);
  arr.deleteValue(5);
  arr.append(8);
  arr.display();
  arr.displayReverse();
  return 0;
}

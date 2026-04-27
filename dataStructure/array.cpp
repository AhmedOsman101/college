#include <iostream>

using namespace std;

class Array {
 public:
  // constructor
  Array(int len) : length(len), size(-1) {
    items = new int[length];
  };
  // destructor
  ~Array() {
    delete [] items;
  }

  void push(int item) {
    if (isFull()) cerr << "Array is full!\n";
    else {
      size++;
      items[size] = item;
    }
  }

  void pop() {
    // NOTE: The item isn't really removed, it will be overwritten in the next push.
    if (isEmpty()) cerr << "Array is empty!\n";
    else size--;
  }

  void display() {
    printf("[");
    for (int i = 0; i <= size; i++) printf(" %d", items[i]);
    printf(" ]\n");
  }

  int getSize() {
    return size;
  }
  int getLength() {
    return length;
  }

  bool isEmpty() {
    return size == -1;
  }

  bool isFull() {
    return size == length - 1;
  }

 private:
  int length; // How many items can we store
  int size;   // Index of the last stored item
  int *items;
};

int main() {
  Array arr = Array(5);

  arr.push(1);
  arr.push(2);
  arr.push(3);
  arr.display();

  return 0;
}

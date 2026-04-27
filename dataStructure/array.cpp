#include <iostream>

using namespace std;

template <typename T>
class Array {
 public:
  // constructor
  Array(unsigned int len) : length(len), size(-1) {
    items = new T[length];
  };
  // destructor
  ~Array() {
    delete [] items;
  }

  void push(T item) {
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
    for (int i = 0; i <= size; i++) cout << ' ' << items[i];
    printf(" ]\n");
  }

  /*
    * returns how many items are actually stored in the array.
   */
  int getSize() {
    return size + 1;
  }
  /*
    * returns how many items can be stored in the array.
   */
  unsigned int getLength() {
    return length;
  }

  bool isEmpty() {
    return size == -1;
  }

  bool isFull() {
    return size == length - 1;
  }

 private:
  unsigned int length; // How many items can we store
  int size;   // Index of the last stored item
  T *items;
};

int main() {
  Array arr = Array<int>(5);

  arr.push(1);
  arr.push(2);
  arr.push(3);
  arr.display();

  return 0;
}

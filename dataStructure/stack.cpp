#include <cstdio>
#include <iostream>

using namespace std;

template <typename T>
class Stack {
 public:
  Stack(unsigned int len) : length(len), topIdx(-1) {
    items = new T[length];
  }
  ~Stack() {
    delete [] items;
  }

  void push(T item) {
    if (isFull()) cerr << "Stack is full!\n";
    else {
      topIdx++;
      items[topIdx] = item;
    }
  }

  void pop() {
    if (isEmpty()) cerr << "Stack is empty!\n";
    else topIdx--;
  }

  int size() {
    return topIdx + 1;
  }

  T top() {
    if (isEmpty()) cerr << "Stack is empty!\n";
    return items[topIdx];
  }

  bool isEmpty() {
    return topIdx == -1;
  }

  bool isFull() {
    return topIdx == length - 1;
  }

  void display() {
    printf("[");
    for (int i = topIdx; i >= 0; i--) cout << ' ' << items[i];
    printf(" ]\n");
  }


 private:
  int topIdx;
  unsigned int length;
  T *items;
};

int main() {
  Stack arr = Stack<int>(5);

  arr.push(1);
  arr.push(2);
  arr.push(3);
  arr.display();
  arr.pop();
  arr.push(4);
  arr.display();
  printf("%d\n", arr.top());

  return 0;
}

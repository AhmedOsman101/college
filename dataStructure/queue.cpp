#include <cstdio>
#include <iostream>

using namespace std;

template <typename T>
class Queue {
 public:
  Queue(unsigned int len) : length(len), rear(-1) {
    items = new T[length];
  }
  ~Queue() {
    delete [] items;
  }

  void push(T item) {
    if (isFull()) cerr << "Queue is full!\n";
    else {
      rear++;
      items[rear] = item;
    }
  }

  void pop() {
    if (isEmpty()) cerr << "Queue is empty!\n";
    else {
      // shift the whole array.
      for (int i = 0; i < rear; i++) items[i] = items[i + 1];
      rear--;
    }
  }

  int size() {
    return rear + 1;
  }

  T front() {
    if (isEmpty()) cerr << "Queue is empty!\n";
    return items[0];
  }

  T back() {
    if (isEmpty()) cerr << "Queue is empty!\n";
    return items[rear];
  }

  bool isEmpty() {
    return rear == -1;
  }

  bool isFull() {
    return rear == length - 1;
  }

  void display() {
    printf("[");
    for (int i = 0; i <= rear; i++) cout << ' ' << items[i];
    printf(" ]\n");
  }


 private:
  int rear;
  unsigned int length;
  T *items;
};

int main() {
  Queue arr = Queue<int>(5);

  arr.push(1);
  arr.push(2);
  arr.push(3);
  arr.display();
  arr.pop();
  arr.push(4);
  arr.display();
  printf("%d\n", arr.front());

  return 0;
}

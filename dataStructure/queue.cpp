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

  void enqueue(T item) {
    if (isFull()) cerr << "Queue is full!\n";
    else {
      rear++;
      items[rear] = item;
    }
  }

  void dequeue() {
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
    if (isEmpty()) {
      cerr << "Queue is empty!\n";
      return T();
    }
    return items[0];
  }

  T back() {
    if (isEmpty()) {
      cerr << "Queue is empty!\n";
      return T();
    }
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

template <typename T>
class SimpleQueue {
 public:
  SimpleQueue(unsigned int len) : frontIdx(-1), rearIdx(-1), length(len) {
    items = new T[length];
  }
  ~SimpleQueue() {
    delete [] items;
  }

  void enqueue(T item) {
    if (isFull()) cerr << "Queue is full!\n";
    else {
      if (frontIdx == -1) frontIdx = 0;
      rearIdx++;
      items[rearIdx] = item;
    }
  }

  void dequeue() {
    if (isEmpty()) cerr << "Queue is empty!\n";
    else {
      frontIdx++;

      if (frontIdx > rearIdx) {
        frontIdx = -1;
        rearIdx = -1;
      }
    }
  }

  int size() {
    if (isEmpty()) return 0;
    return rearIdx - frontIdx + 1;
  }

  T front() {
    if (isEmpty()) {
      cerr << "Queue is empty!\n";
      return T();
    }
    return items[frontIdx];
  }

  T back() {
    if (isEmpty()) {
      cerr << "Queue is empty!\n";
      return T();
    }
    return items[rearIdx];
  }

  bool isEmpty() {
    return frontIdx == -1;
  }

  bool isFull() {
    return rearIdx == length - 1;
  }

  void display() {
    printf("[");
    for (int i = frontIdx; i <= rearIdx; i++) cout << ' ' << items[i];
    printf(" ]\n");
  }

 private:
  int frontIdx;
  int rearIdx;
  unsigned int length;
  T *items;
};

int main() {
  Queue arr = Queue<int>(5);

  arr.enqueue(1);
  arr.enqueue(2);
  arr.enqueue(3);
  arr.display();
  arr.dequeue();
  arr.enqueue(4);
  arr.display();
  printf("%d\n", arr.front());

  SimpleQueue arr2 = SimpleQueue<int>(5);

  arr2.enqueue(1);
  arr2.enqueue(2);
  arr2.enqueue(3);
  arr2.display();
  arr2.dequeue();
  arr2.enqueue(4);
  arr2.display();
  printf("%d\n", arr2.front());

  return 0;
}

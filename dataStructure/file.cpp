#include <iostream>

using namespace std;

void bubbleSort(int arr[], int length) {
  for (int i = 0; i < length; i++) {
    bool isSorted = true;
    for (int j = 0; j < length - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        isSorted = false;
      }
    }
    // if we didn't swap anything, then the array is already sorted.
    if (isSorted) break;
  }
}

int search(int arr[], int length, int value) {
  for (int i = 0; i < length; i++) {
    if (arr[i] == value) return i;
  }
  return -1; // -1 means not found
}

int main() {
  int arr[10] = {20, 50, 10, 5, 30, 8, 9, 10, 6, 2};

  for (auto i : arr) printf("%d ", i);

  int index = search(arr, 10, 30);
  if (index == -1) cout << "\nValue 30 was not found!\n\n";
  else printf("\nValue 30 was found at index %d\n\n", index);

  bubbleSort(arr, 10);
  cout << "Sorted Array:\n";
  for (auto i : arr) printf("%d ", i);
  printf("\n");
  return 0;
}

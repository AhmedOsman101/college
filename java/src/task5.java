import java.io.PrintStream;
import java.util.Arrays;
import java.util.Scanner;

class Task5 {
  // `static final` defines a constant value
  static final Scanner stdin = new Scanner(System.in);
  static final PrintStream stdout = System.out;
  static final PrintStream stderr = System.err;

  // --- Helpers Start --- //
  public static int randomInt(int end) {
    return (int) Math.floor(Math.random() * end);
  }

  public static int randomInt(int start, int end) {
    return (int) Math.floor(Math.random() * (end - start + 1)) + start;
  }

  public static int[] randomIntArray(int len) {
    int[] array = new int[len];
    for (int i = 0; i < len; i++) array[i] = randomInt(1, len);
    return array;
  }

  public static int[] randomIntArray(int len, int endRange) {
    int[] array = new int[len];
    for (int i = 0; i < len; i++) array[i] = randomInt(1, endRange);
    return array;
  }

  public static int[] randomIntArray(int len, int startRange, int endRange) {
    int[] array = new int[len];
    for (int i = 0; i < len; i++) array[i] = randomInt(startRange, endRange);
    return array;
  }

  /**
   * @param mode  the sorting order - "asc" for ascending order or "desc" for descending order
   */
  public static int[] bubbleSort(int[] array, String mode) {
    int[] sorted = array.clone(); // clone instead of modifing the original array.

    for (int i = 0; i < sorted.length; i++) {
      boolean didSwap = false;
      for (int j = 0; j < sorted.length - 1 - i; j++) {
        switch (mode) {
          case "asc":
            if (sorted[j + 1] < sorted[j]) {
              int temp = sorted[j];
              sorted[j] = sorted[j + 1];
              sorted[j + 1] = temp;
              didSwap = true;
            }
            break;
          case "desc":
            if (mode.equals("desc") && sorted[j + 1] > sorted[j]) {
              int temp = sorted[j];
              sorted[j] = sorted[j + 1];
              sorted[j + 1] = temp;
              didSwap = true;
            }
            break;
          default:
            stderr.printf("Invalid Mode: %s\n", mode);
            System.exit(1);
            break;
        }
      }

      if (!didSwap) break;
    }

    return sorted;
  }

  public static int[] bubbleSort(int[] array) {
    return bubbleSort(array, "asc");
  }


  public static void printArray(int[] array) {
    for (int i : array) stdout.printf("%d ", i);
    stdout.println();
  }
  public static void printArray(int[] array, String message) {
    stdout.print(message);
    printArray(array);
  }
  // --- Helpers End --- //

  public static void task1() {
    int len = 5;
    int[] nums1 = randomIntArray(len);
    int[] nums2 = randomIntArray(len);
    int[] common = new int[len];
    int commonSize = 0;

    printArray(nums1, "Array 1: ");
    printArray(nums2, "Array 2: ");
    stdout.println();

    for (int i = 0; i < len; i++) {
      for (int j = 0; j < len; j++) {
        if (nums2[j] == nums1[i]) {
          common[commonSize] = nums1[i];
          commonSize++;
          break;
        }
      }
    }

    stdout.print("The common elements are: ");
    common = Arrays.copyOf(common, commonSize); // trim first
    common = bubbleSort(common);                // then sort

    int lastPrinted = -1;
    for (int item : common) {
      if (item == lastPrinted) continue;
      else {
        lastPrinted = item;
        stdout.printf("%d ", item);
      }
    }

    stdout.println();
  }

  public static void task2() {
    int[] nums = randomIntArray(10);
    int[] sorted = bubbleSort(nums);
    int current = sorted[sorted.length - 1], secondBiggest = current;

    for (int i = sorted.length - 1; 0 <= i; i--) {
      if (current == sorted[i]) continue;
      else {
        secondBiggest = sorted[i];
        break;
      }
    }

    printArray(sorted, "Array (sorted):  ");
    stdout.printf("Second biggest is: %d\n", secondBiggest);
  }

  public static void task3() {
    int arr[] = randomIntArray(5, 20);
    int last = arr[arr.length - 1];
    printArray(arr, "Original: ");

    for (int i = arr.length - 1; i >= 1; i--) arr[i] = arr[i - 1];
    arr[0] = last;
    printArray(arr, "Result: ");
  }

  public static void task4() {
    int arr[] = randomIntArray(10);
    int sorted[] = bubbleSort(arr);
    int sum = 0;
    printArray(sorted, "Array (Sorted): ");

    // If the array has 2 elements exactly, then that wouldn't work
    for (int i = 1; i < sorted.length - 1; i++) sum += sorted[i];

    double average = sum / (sorted.length - 2.0);
    stdout.printf("Total: %d, Avg: %.2f\n", sum, average);
  }

  public static void task5() {
    int arr[] = new int[10];

    for (int i = 0; i < arr.length; i++) arr[i] = randomInt(-10, 10);

    printArray(arr, "Original: ");
    printArray(bubbleSort(arr), "Sorted: ");
  }

  public static void task6() {
    int arr[] = randomIntArray(10);
    int sorted[] = bubbleSort(arr);
    int repeated = 0;

    printArray(sorted, "Array (Sorted): ");

  outer: // Using the sorted array would make lookup faster
    for (int i = 0; i < sorted.length; i++) {
      for (int j = i + 1; j < sorted.length; j++) {
        if (sorted[i] == sorted[j]) {
          repeated++;
          // This jumps to the outer loop instead of the inner one
          continue outer;
        }
      }
    }

    stdout.printf("There are %d repeated items\n", repeated);
  }

  public static void task7() {
    int arr[] = {11, 12, 13, 14, 15};

    for (int item : arr) {
      if (item % 2 == 0) stdout.printf("%d ", item);
    }

    stdout.println();
  }

  public static void task8() {
    int arr1[] = {30, 10, 50};
    int arr2[] = {5, 100, 70};
    int merged[] = new int[arr1.length + arr2.length];

    int size = 0;

    for (int item : arr1) merged[size++] = item;
    for (int item : arr2) merged[size++] = item;

    printArray(bubbleSort(merged), "Merged Array (Sorted): ");
  }

  public static void task9() {
    int arr[] = randomIntArray(10, 0, 45);
    printArray(arr, "Original: ");
    printArray(bubbleSort(arr, "desc"), "Sorted: ");
  }

  public static void task10() {
    int arr[] = {10, 20, 30, 40};
    int newArr[] = new int[arr.length + 1];
    newArr[2] = 100;

    for (int i = 0; i < newArr.length; i++) {
      if (i < 2) newArr[i] = arr[i];
      else if (i > 2) newArr[i] = arr[i - 1];
    }

    printArray(newArr, "Added 100 at idx 2: ");
  }

  public static void main(String[] args) {
    stdout.println("--- Running task1 ---\n");
    task1();

    stdout.println("--- Running task2 ---\n");
    task2();

    stdout.println("--- Running task3 ---\n");
    task3();

    stdout.println("--- Running task4 ---\n");
    task4();

    stdout.println("--- Running task5 ---\n");
    task5();

    stdout.println("--- Running task6 ---\n");
    task6();

    stdout.println("--- Running task7 ---\n");
    task7();

    stdout.println("--- Running task8 ---\n");
    task8();

    stdout.println("--- Running task9 ---\n");
    task9();

    stdout.println("--- Running task10 ---\n");
    task10();

    stdin.close();
  }
}

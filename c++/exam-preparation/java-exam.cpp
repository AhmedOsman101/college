#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void pattern() {
  int rows, width, minuses, pluses = 1;
  cout << "Enter how many rows: \n"; cin >> rows;

  width = (rows * 2) - 1;

  for (int i = 0; i < rows; i++) {
    minuses = (width - pluses) / 2;

    for (int j = 0; j < minuses; j++) cout << "-";

    for (int k = 0; k < pluses; k++) cout << "+";

    for (int l = 0; l < minuses; l++) cout << "-";

    pluses += 2;
    cout << endl;
  }
}

const string OUTPUT_DIR = "/home/othman/work/college/c++/exam-preparation/invoices";

struct Product {
  string name;
  double price;
};

const int NUM_PRODUCTS = 3;

// Create an array of Product objects
Product PRODUCTS[NUM_PRODUCTS] = {
  {"keyboard", 50.0},
  {"mouse", 30.0},
  {"scanner", 100.0}
};

int generateId() {
  static int id = 1;
  return ++id;
}

class Invoice {
 public:
  int id;
  vector<Product> items = {};
  double totalPrice;
  string fileName;

  Invoice() {
    id = generateId();
    fileName = to_string(id) + "-invoice.txt";
  }

  void addItem(const Product& p) {
    items.push_back(p);
    totalPrice += p.price;
  }
};

void invoice() {
  const string message = "If you want to record another invoice, press the letter 'p'\nIf you want to exit the program, type 'exit'\n";
  string option, items_string;

  while (option != "exit") {
    vector<int> items = {};
    cout << message;
    getline(cin, option);

    if (option != "p" && option != "exit") {
      cout << "Invalid option: " << option << "\n" << message;
      continue;
    } else if (option == "exit") break;

    for (int i = 0; i < NUM_PRODUCTS; i++) {
      cout << i + 1 << ": " << PRODUCTS[i].name << " (" << PRODUCTS[i].price << ")" << "\n";
    }

    cout << "Choose product numbers to add (separate items with commas ','): ";
    getline(std::cin, items_string);

    for (char item : items_string) {
      if (item < '1' || item > '3') continue;

      items.push_back(item - '1'); // subtract the ascii value
    }

    Invoice currentInvoice;

    for (auto item : items) currentInvoice.addItem(PRODUCTS[item]);
  }

  cout << "Goodbye!" << endl;
}

int main() {
  invoice();

  return 0;
}

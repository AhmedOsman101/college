#include <cstdio>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

int main() {
  string names, grades, name, option;
  int count = 1, grade1, grade2, grade3;

  while (option != "exit") {
    name = "", option = "";

    cout << "Enter option: ";
    getline(cin, option);

    if (option == "exit") break;

    printf("Enter student %d name: ", count);
    getline(cin, name);
    names += name + ';';

    printf("Enter 3 grades separated by spaces: ");
    cin >> grade1 >> grade2 >> grade3;

    // Clear the input buffer after reading the grades
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    grades += "AS:" + to_string(grade1) + ",BS:" + to_string(grade2) + ",CS:" + to_string(grade3) + ';';
    count++;
  }

  int nskip = 0, idx = 0;

  for (auto c : names) {
    if (nskip == idx) {
      // names = "ahmad;mohamed;ali;"
      // grades= "A:1,B:2,C:3;A:4,B:5,C:6;A:7,B:8,C:9;"
      if (c == ';') {
        printf("\n");
        int gskip = 0;

        for (auto g : grades) {
          if (gskip == idx) {
            if (g == ';') {
              printf("\n\n");
              idx++; nskip++;
              break;
            } else if (g == ',') {
              printf("\n");
            } else {
              printf("%c", g);
            }
          }

          if (g == ';') gskip++;
        }
      } else {
        cout << c;
      }
    }
  }

  return 0;
}

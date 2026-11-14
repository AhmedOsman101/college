#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// From lecture 5
#define __STRINGIFY__(x) #x
#define STRINGIFY(x) __STRINGIFY__(x)

#define NAME_LENGTH 24
typedef struct {
  int id;
  float gpa;
  char name[NAME_LENGTH + 1];
} Student;

void topStudent(Student students[], int length) {
  Student bestStudent = {-1, -1, "null"}; // placeholder student
  for (int i = 0; i < length; i++) {
    if (students[i].gpa > bestStudent.gpa) {
      bestStudent = students[i];
    }
  }

  printf("id: %d, name: %s, gpa: %.2f\n", bestStudent.id, bestStudent.name, bestStudent.gpa);
}

#define BUFFER_SIZE 254
typedef struct {
  char title[BUFFER_SIZE];
  struct Date {
    unsigned int year;
    unsigned int month;
    unsigned int day;
  } date;
} Book;

void librarySearch(Book books[], int length, struct Date date) {
  for (int i = 0; i < length; i++) {
    Book book = books[i];
    if (
      // 2025 > 2024
      (book.date.year > date.year) ||
      // 2024-5 > 2024-3
      ((book.date.year == date.year) && (book.date.month > date.month)) ||
      // 2024-3-25 > 2024-3-19
      ((book.date.year == date.year) && (book.date.month == date.month) && (book.date.day > date.day))
    ) {
      printf("%s\n", book.title);
    }
  }
}

typedef union {
  int x;
  float y;
} Number;

void intOrFloat(int choice) {
  Number number;
  if (choice == 1) {
    scanf("%d", &number.x);
    printf("Integer: %d\n", number.x);
  } else if (choice == 2) {
    scanf("%f", &number.y);
    printf("Float: %.2f\n", number.y);
  } else {
    fprintf(stderr, "Invalid choice '%d'. Valid choices are: 1,2\n", choice);
    exit(2); // Exit code 2: Usage error
  }
}

typedef union {
  unsigned int studentId;
  char guestName[NAME_LENGTH + 1];
} PersonInfo;

typedef struct {
  unsigned int type;
  PersonInfo info;
} Person;

void studentOrGuest(Person *person) {
  if (person->type == 1) {
    scanf("%d", &person->info.studentId);
    printf("Student ID: %d\n", person->info.studentId);
  } else if (person->type == 2) {
    scanf("%" STRINGIFY(NAME_LENGTH) "s", person->info.guestName);
    printf("Guest name: %s\n", person->info.guestName);
  } else {
    fprintf(stderr, "Invalid choice '%d'. Valid choices are: 1,2\n", person->type);
    exit(2); // Exit code 2: Usage error
  }
}

int main(int argc, char **argv) {
  // ===== Top Student ===== //
  // int studentsLength; scanf("%d", &studentsLength);
  // Student students[studentsLength];
  // for (int i = 0; i < studentsLength; i++) {
  //   // Read NAME_LENGTH bytes only, avoids overflow.
  //   // The string expands to "%24s %d %f" at compilation time.
  // scanf(
  // "%" STRINGIFY(NAME_LENGTH) "s %d %f",
  // students[i].name,
  // &students[i].id,
  // &students[i].gpa
  // );
  // }
  // topStudent(students, studentsLength);

  // ===== Library Search ===== //
  // int booksLength; scanf("%d", &booksLength);
  // Book books[booksLength]; struct Date date;
  // for (int i = 0; i < booksLength; i++) {
  //   // Read NAME_LENGTH bytes only, avoids overflow.
  //   // The string expands to "%24s %d %f" at compilation time.
  // scanf(
  // "%" STRINGIFY(BUFFER_SIZE) "s %d %d %d",
  // books[i].title,
  // &books[i].date.day,
  // &books[i].date.month,
  // &books[i].date.year
  // );
  // }
  // scanf("%d %d %d", &date.day, &date.month, &date.year);
  // librarySearch(books, booksLength, date);

  // ===== Int or Float ===== //
  // int choice; scanf("%d", &choice);
  // intOrFloat(choice);

  // ===== Student or Guest ===== //
  // int peopleLength; scanf("%d", &peopleLength);
  // Person people[peopleLength];
  // for (int i = 0; i < peopleLength; i++) {
  //   Person p;
  //   scanf("%d", &p.type);
  //   studentOrGuest(&p);
  // }

  return 0;
}

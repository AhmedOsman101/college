#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct {
  unsigned int type;
  union {
    unsigned int studentId;
    char guestName[NAME_LENGTH + 1];
  } info;
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

typedef enum { MON, TUE, WED, THU, FRI, SAT, SUN } Day;

char *nextDay(Day day) {
  switch (day) {
    case MON: return "SUN";
    case TUE: return "WED";
    case WED: return "THU";
    case THU: return "FRI";
    case FRI: return "SAT";
    case SAT: return "SUN";
    case SUN: return "MON";
    default:
      fprintf(stderr, "Invalid day\n");
      exit(2);
  }
}

bool isWeekend(Day day) {
  switch (day) {
    case SAT:
    case SUN:
      return true;
    default: return false;
  }
}

typedef enum {
  SUCCESS = 0,
  FILE_NOT_FOUND = 100,
  PERMISSION_DENIED = 200,
  OUT_OF_MEMORY = 300
} ErrorCode;

char *errorCode2msg(ErrorCode code) {
  switch (code) {
    case SUCCESS: return "Success";
    case FILE_NOT_FOUND: return "File not found";
    case PERMISSION_DENIED: return "Permission Denied";
    case OUT_OF_MEMORY: return "Out of memory";
    default:
      fprintf(stderr, "Invalid error code\n");
      exit(2);
  }
}

typedef struct {
  enum {
    INT,
    FLOAT,
    CHAR
  } type;
  union {
    int x;
    float y;
    char z;
  } value;
} VariableData;

void readVariant(VariableData *data) {
  scanf("%d", &data->type);
  switch (data->type) {
    case INT:
      scanf("%d", &data->value.x);
      break;
    case FLOAT:
      scanf("%f", &data->value.y);
      break;
    case CHAR:
      scanf("%1s", &data->value.z);
      break;
    default:
      fprintf(stderr, "Invalid type\n");
      exit(2);
  }
}

void printVariant(VariableData data) {
  switch (data.type) {
    case INT:
      printf("INT: %d\n", data.value.x);
      break;
    case FLOAT:
      printf("FLOAT: %.2f\n", data.value.y);
      break;
    case CHAR:
      printf("CHAR: %c\n", data.value.z);
      break;
  }
}

typedef struct {
  enum ShapeType { CIRCLE, RECTANGLE, TRIANGLE } type;
  union {
    // NOTE: I can't declare height twice because I'm using an unnamed struct.
    // I prefixed all dimensions to make it more clear which belongs to which
    struct {
      int c_radius;
    };
    struct {
      int r_width;
      int r_height; // rectangle height
    };
    struct {
      int t_base;
      int t_height; // triangle height
    };
  };
} Shape;

void readShape(Shape *shape) {
  switch (shape->type) {
    case CIRCLE:
      scanf("%d", &shape->c_radius);
      break;
    case RECTANGLE:
      scanf("%d %d", &shape->r_width, &shape->r_height);
      break;
    case TRIANGLE:
      scanf("%d %d", &shape->t_base, &shape->t_height);
      break;
    default:
      fprintf(stderr, "Invalid type\n");
      exit(2);
  }
}

float shapeArea(Shape shape) {
  float area;
  switch (shape.type) {
    case CIRCLE:
      area = 3.14 * shape.c_radius * shape.c_radius;
      return area;
    case RECTANGLE:
      area = shape.r_width * shape.r_height;
      return area;
    case TRIANGLE:
      area = 0.5 * shape.t_base * shape.t_height;
      return area;
    default:
      fprintf(stderr, "Invalid type\n");
      exit(2);
  }
}

int main(int argc, char **argv) {
  // printf("===== Top Student =====\n");
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

  // printf("\n===== Library Search =====\n");
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

  // printf("\n===== Int or Float =====\n");
  // int choice; scanf("%d", &choice);
  // intOrFloat(choice);

  // printf("\n===== Student or Guest =====\n");
  // int peopleLength; scanf("%d", &peopleLength);
  // Person people[peopleLength];
  // for (int i = 0; i < peopleLength; i++) {
  // scanf("%d", &people[i].type);
  // studentOrGuest(&people[i]);
  // }

  // printf("\n===== Days of the Week =====\n");
  // Day day; scanf("%d", &day);
  // printf("Next day: %s\n", nextDay(day));
  // printf("Weekend: %s\n", isWeekend(day) ? "True" : "False");

  // printf("\n===== Error Codes =====\n");
  // ErrorCode code; scanf("%d", &code);
  // printf("%s\n", errorCode2msg(code));

  // printf("\n===== Variant Data =====\n");
  // int varsLength; scanf("%d", &varsLength);
  // VariableData vars[varsLength];
  // for (int i = 0; i < varsLength; i++) {
  // readVariant(&vars[i]);
  // printVariant(vars[i]);
  // }

  printf("\n===== Shape Manager =====\n");
  float areaTotal = 0.0; char *output = "\r";
  while (true) {
    printf(
      "\n1) Add circle (radius)\n"
      "2) Add rectangle (width, height)\n"
      "3) Add triangle (base, height)\n"
      "4) Print all shapes and exit\n\n"
    );
    int choice; scanf("%d", &choice);
    switch (choice) {
      case 1: {
          Shape shape = { .type = CIRCLE };
          readShape(&shape);
          float area = shapeArea(shape);
          areaTotal += area;
          char *buff;
          sprintf(buff, "\nCircle area = %.2f\n", area);
          strcat(buff, output);
          break;
        }
      case 2: {
          Shape shape = { .type = RECTANGLE };
          readShape(&shape);
          float area = shapeArea(shape);
          areaTotal += area;
          sprintf(output, "%s\nRectangle area = %.2f\n", output, area);
          break;
        }
      case 3: {
          Shape shape = { .type = TRIANGLE };
          readShape(&shape);
          float area = shapeArea(shape);
          areaTotal += area;
          sprintf(output, "%s\nTriangle area = %.2f\n", output, area);
          break;
        }
      case 4:
        printf("Total area = %.2f\n", areaTotal);
        exit(0);
      default:
        fprintf(stderr, "Invalid choice '%d'. Valid choices are: 1-4\n", choice);
        exit(2); // Exit code 2: Usage error
    }
  }

  return 0;
}

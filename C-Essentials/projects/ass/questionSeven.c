#include <stdio.h>
#include <string.h>

struct Student {
  int id;
  char name[50];
  int marks[3];
  float average;
};

void calculateAverage(struct Student *s) {
  float sum = 0;

  for (int i = 0; i < 3; i++) {
    sum += s->marks[i];
  }

  s->average = sum / 3.0;
}

void readline(char* restrict s, int n, FILE *restrict stream) {
  fgets(s, n, stream);
  s[strcspn(s, "\n")] = '\0'; // Remove the newline '\n' character
}

// Clear input buffer
void clearInputBuffer() {
  int c;

  while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
  struct Student students[5];

  for (int i = 0; i < 5; i++) {
    printf("Enter details for student %d:\n", i + 1);

    printf("ID: ");
    scanf("%d", &students[i].id);
    clearInputBuffer();

    printf("Name: ");
    readline(students[i].name, 50, stdin);

    for (int j = 0; j < 3; j++) {
      printf("Subject %d marks: ", j + 1);
      scanf("%d", &students[i].marks[j]);
    }

    calculateAverage(&students[i]);
  }

  printf("\nStudent Grading Report:\n");

  for (int i = 0; i < 5; i++) {
    struct Student s = students[i];
    printf(
      "ID: %d, Name: '%s', Marks: %d, %d, %d, Average: %.2f\n",
      s.id, s.name, s.marks[0], s.marks[1], s.marks[2], s.average
    );
  }

  struct Student *p = &students[0];

  p->marks[0] = 90;
  calculateAverage(p);

  printf("\nAfter updating student 1's subject 1 mark to 90:\n");
  printf(
    "ID: %d, Name: '%s', Marks: %d, %d, %d, Average: %.2f\n",
    p->id, p->name, p->marks[0], p->marks[1], p->marks[2], p->average
  );

  return 0;
}

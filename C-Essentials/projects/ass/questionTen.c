#include <stdio.h>
#include <string.h>

const char FILENAME[11] = "grades.txt";

int main() {
  FILE *file = fopen(FILENAME, "r");

  if (file == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  char line[100];
  printf("Student Grades Report:\n");

  while (fgets(line, 100, file) != NULL) {
    char name[50];
    float average;
    /*
      %[^,]: matches everything after 'Name: ' up until the comma (not included)
      %f: matches any floating number after 'Average: '
    */
    sscanf(line, "Name: %[^,], Average: %f", name, &average);
    printf("Name: %s, Average: %.2f\n", name, average);
  }

  fclose(file);
  return 0;
}

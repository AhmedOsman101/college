**5. Arrays vs. Structures in C**

- **Arrays**

  - Hold multiple elements of the _same_ type (e.g. all `int` or all `double`).
  - Laid out contiguously in memory—you can index into them (`arr[5]`) and perform pointer‑arithmetic.
  - Good when you need a simple list or table of values, all governed by the same operations.

- **Structures**

  - Bundle together one or more variables, possibly of _different_ types, under a single name.
  - Each member can be accessed by name (`person.age`, `person.name`), improving clarity when you have logically related but type‑varying data.
  - Memory layout may include padding to satisfy alignment, but you don’t lose the benefit of grouping.

> **When to prefer a `struct` over separate arrays?**
> Use a `struct` when you’re modelling an entity that has multiple attributes—especially if those attributes are not all the same data type. With arrays you’d need parallel arrays (e.g. `ages[i]`, `names[i]`, `grades[i]`), which is error‑prone and scatters related data. A `struct` keeps each “record” intact, makes function interfaces cleaner, and aligns with best practices for data encapsulation.

```c
#include <stdio.h>

/* Define a student record with mixed fields */
struct Student {
  char name[32];
  int age;
  float gpa;
} ;

int main() {
  /* Array of structures: each element is a complete student record */
  struct Student classroom[3] = {
    { "Alice", 20, 3.8f },
    { "Bob", 22, 3.2f },
    { "Cara", 19, 3.9f }
  };

  /* Print each student’s data */
  for (int i = 0; i < 3; i++) {
    printf(
      "Student %d: %s, age %d, GPA %.2f\n",
      i + 1,
      classroom[i].name,
      classroom[i].age,
      classroom[i].gpa
    );
  }

  return 0;
}
```

- **Why this is better than parallel arrays**

  - You avoid mistakes like shifting one array and not the others.
  - Passing one `Student` to a function is simpler than passing three separate arrays plus an index.
  - The code is self‑documenting: `student.age` vs. `ages[i]`.

**9. Difference between `"w"` and `"a"` modes in `fopen`**

| Mode  | Behavior                                                                                                       | Existing file content            |
| ----- | -------------------------------------------------------------------------------------------------------------- | -------------------------------- |
| `"w"` | Open for writing. If the file exists, truncate it to zero length (erase all data). If absent, create new file. | Discarded (file is cleared)      |
| `"a"` | Open for writing. If the file exists, writing always goes to the end (append). If absent, create new file.     | Preserved; new data added at end |

> **Key point:**
>
> - Use `"w"` when you want to start fresh and do not care about any previous content.
> - Use `"a"` when you want to preserve existing content and add more data at the end.

```c
#include <stdio.h>

int main(void) {
    FILE *fp;

    /* Example with "w" */
    fp = fopen("log.txt", "w");
    if (!fp) { perror("fopen w"); return 1; }
    fprintf(fp, "Log start: %s\n", __TIME__);
    fclose(fp);
    /* At this point, any old data in log.txt is gone; only this line remains. */

    /* Now open with "a" */
    fp = fopen("log.txt", "a");
    if (!fp) { perror("fopen a"); return 1; }
    fprintf(fp, "Appending entry: %s\n", __TIME__);
    fclose(fp);
    /* The new line is added after the first; previous content stays intact. */

    return 0;
}
```

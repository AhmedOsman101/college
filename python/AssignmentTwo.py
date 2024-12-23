# ---- Task1 ----- #
print("# ---- Task1 ----- #")

grade = int(input("Enter your grade (0~100): "))

if grade in range(101):
  if grade in range(85, 101):
    print("Excellent")
  elif grade in range(75, 85):
    print("Very Good")
  elif grade in range(65, 75):
    print("Good")
  elif grade in range(60, 65):
    print("Acceptable:")
  else:
    print("Fail")
else:
  print(f"Invalid grade: {grade}, you must enter values between 0 and 100.")

# ---- Task3 ----- #
print("# ---- Task3 ----- #")

while True:
  grade2 = input("Enter your grade (0~100) or type 'exit' to quit: ")

  # The program stops only when the user writes the word `exit` in lowercase letters (case insensitive).
  if grade2.lower() == "exit":
    print("Goodbye!")
    break
  else:
    grade2 = int(grade2)

  if grade2 in range(101):
    if grade2 in range(85, 101):
      result = "Excellent"
    elif grade2 in range(75, 85):
      result = "Very Good"
    elif grade2 in range(65, 75):
      result = "Good"
    elif grade2 in range(60, 65):
      result = "Acceptable:"
    else:
      result = "Fail"
    print(result, end="\n\n")
  else:
    print(f"Invalid grade: {grade2}, you must enter values between 0 and 100.")

print("# ---- Task4 ----- #")
# ---- Task4 ----- #

while True:
  height = input("Enter the height: ")
  if height == "exit":
    print("Goodbye!")
    break
  elif height.isdigit():
    if 0 < int(height):
      for i in range(1, int(height)+1):
        print(i*"*")
    else:
      print("Invalid height, you must enter an integer bigger than 0.")
  else:
    print("Invalid height, you must either enter an integer or type 'exit' to quit.")


# ---- Task7 ----- #
print("# ---- Task7 ----- #")


def task7():
  while True:
    grade = input("Enter your grade (0~100) or type 'exit' to quit: ")
    # The program stops only when the user writes the word `exit` in lowercase letters (case insensitive).
    if grade.lower() == "exit":
      print("Goodbye!")
      return
    elif grade.isdigit():
      grade = int(grade)
      if grade in range(101):
        if grade in range(85, 101):
          result = "Excellent"
        elif grade in range(75, 85):
          result = "Very Good"
        elif grade in range(65, 75):
          result = "Good"
        elif grade in range(60, 65):
          result = "Acceptable:"
        else:
          result = "Fail"
        print(result, end="\n\n")
      else:
        print(f"Invalid grade: {
              grade}, you must enter values between 0 and 100.")
    else:
      print(f"Invalid input, you must either enter an integer or type 'exit' to quit.")


task7()

# ---- Task8 ----- #
print("# ---- Task8 ----- #")


def task8():
  data = {}
  name = input("Enter your name: ")
  degree = int(input("Enter your degree: "))
  data = {
      "name": name,
      "degree": degree
  }
  print(data)


task8()

# ---- Task9 ----- #
print("# ---- Task9 ----- #")


def inFloatRange(value, start=0, end=1):
  return start <= value and value < end


def getGrade(percentage: float):
  if inFloatRange(percentage, 0, 101):
    if inFloatRange(percentage, 85, 101):
      return "Excellent"
    elif inFloatRange(percentage, 75, 85):
      return "Very Good"
    elif inFloatRange(percentage, 65, 75):
      return "Good"
    elif inFloatRange(percentage, 60, 65):
      return "Acceptable:"
    else:
      return "Fail"
  else:
    print(f"Invalid percentage: {
          percentage}, you must enter values between 0 and 100.")
    exit(-1)


def task9():
  data = {}
  marks = 0
  data["name"] = input("Enter your name: ")
  for i in range(1, 5):
    marks += int(input(f"Please enter you mark for subject{i}: "))

  if not marks in range(400):
    print("Invalid input, marks should be between 0 and 400.")
    return

  data["total_marks"] = marks

  percentage = (marks * 100) / 400

  data["grade"] = getGrade(percentage)

  print(data)


task9()

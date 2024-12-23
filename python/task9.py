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
    print(f"Invalid percentage: {percentage}, you must enter values between 0 and 100.")
    exit(-1)


def task9():
  data = {}
  marks = 0
  data["name"] = input("Enter your name: ")
  for i in range(1, 5):
    marks += int(input(f"Please enter you mark for subject{i}: "))

  if not marks in range(401):
    print("Invalid input, marks should be between 0 and 400.")
    return

  data["total_marks"] = marks

  percentage = (marks * 100) / 400

  data["grade"] = getGrade(percentage)

  print(data)


task9()

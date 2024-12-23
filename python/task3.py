while True:
  grade = input("Enter your grade (0~100) or type 'exit' to quit: ")

  # The program stops only when the user writes the word `exit` in lowercase letters (case insensitive).
  if grade.lower() == "exit":
    print("Goodbye!")
    break
  else:
    grade = int(grade2)

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
    print(f"Invalid grade: {grade}, you must enter values between 0 and 100.")

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

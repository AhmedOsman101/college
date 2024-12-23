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

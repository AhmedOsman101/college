arr = [3, 7, 3, 5, 11, 9, 7, 1]
arrSize = len(arr)
odds = []
counts = {}
bigNum = ""

# [1] Write only the odd numbers
for i in arr:
    if i % 2 != 0:
        odds.append(i)

print(odds)

# [2] Count the repeated odd numbers
for i in odds:
    if odds.count(i) > 1:
        counts[i] = odds.count(i)

print(counts)

# [3] Print the largest possible number formed from all the numbers
for i in range(arrSize):
    arr[i] = str(arr[i])

arr.sort()

for i in range(arrSize - 1, -1, -1):
    print(arr[i], end="")

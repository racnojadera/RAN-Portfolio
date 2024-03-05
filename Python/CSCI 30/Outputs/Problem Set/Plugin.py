userInput = input()
unrepeatedLetters = []

for i in userInput:
	if len(unrepeatedLetters) == 0:
		unrepeatedLetters.append(i)
	elif i == unrepeatedLetters[len(unrepeatedLetters)-1]:
		unrepeatedLetters.pop()
	else:
		unrepeatedLetters.append(i)
print("".join(unrepeatedLetters))
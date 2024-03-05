def program(string):
	inputString = string
	if inputString[0] == "[" or inputString[0] == "]":
		return program(inputString[1:])
	for i in inputString:
		stringFront = ""
		stringBack = ""
		indexCounter = 0
		if i == "[":
			indexCounter = inputString.index(i)
			stringFront = inputString[:indexCounter]
			stringBack = inputString[indexCounter+1:]
			if i == "[":
				inputString = stringBack + stringFront
			elif i == "]":
				inputString = stringFront + stringBack
			return program(inputString)
	print(inputString)

def main():
	while True:
		inputString = input()
		program(inputString)
	return 0

main()
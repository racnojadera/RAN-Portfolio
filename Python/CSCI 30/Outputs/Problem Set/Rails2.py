def program(n):
	tempValue = n
	middleStack = []
	while True:
		initialStack = 0
		while len(middleStack) > 0:
			middleStack.pop()
		outputValue = list(map(int, input().rstrip().split()))
		if outputValue[0] == 0:
			return None
		
		for element in outputValue:
			while initialStack < tempValue and initialStack != element:
				if len(middleStack) > 0 and middleStack[-1] == element:
					break
				initialStack += 1
				middleStack.append(initialStack)
			if middleStack[-1] == element:
				middleStack.pop()
		if len(middleStack) == 0:
			print("Yes")
		else:
			print("No")

def main():
	while True:
		inputValue = int(input())
		if inputValue == 0:
			break
		program(inputValue)
		print("")
main()
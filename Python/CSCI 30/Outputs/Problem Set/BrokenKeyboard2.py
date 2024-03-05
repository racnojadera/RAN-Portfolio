from collections import deque
import sys

def main(inputText):
	inputValue = str(inputText)
	if len(inputValue) != 0:
		outputList = deque()
		outputList.clear()
		leftDeterminer = True
		inputString = ""
		for i in range(0, len(inputValue), 1):
			if inputValue[i] == "[":
				outputList.appendleft(inputString)
				inputString = ""
				leftDeterminer = True
			elif inputValue[i] == "]":
				outputList.appendleft(inputString)
				inputString = ""
				leftDeterminer = False
			else:
				if leftDeterminer:
					inputString += inputValue[i]
				else:
					outputList.append(inputValue[i])
		if leftDeterminer:
			outputList.appendleft(inputString)
		outputList = list(map(str.strip, outputList))
		outputList = list(filter(lambda a: a != "", outputList))
		outputString = "".join(outputList) + "\n"
		print(outputString, end = "")
		try:
			main(input())
		except EOFError:
			return 0
	else:
		print("")
		return 0
main(input())
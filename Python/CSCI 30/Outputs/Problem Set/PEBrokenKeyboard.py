from collections import deque
import sys

def main():
	input()
	for line in sys.stdin:
		inputText = line
		
		outputList = deque()
		outputList.clear()
		leftDeterminer = True
		inputString = ""
		for i in range(0, len(inputText), 1):
			#print("Now checking index: " + str(i))
			#print("Input has a length of: " + str(len(inputText)))
			#print("")
			if inputText[i] == "[":
				#print("To Be Transferred: " + inputString)
				outputList.appendleft(inputString)
				inputString = ""
				leftDeterminer = True
			elif inputText[i] == "]":
				outputList.appendleft(inputString)
				inputString = ""
				leftDeterminer = False
			else:
				if leftDeterminer:
					inputString += inputText[i]
				else:
					outputList.append(inputText[i])
		if leftDeterminer:
			outputList.appendleft(inputString)
		print("".join(outputList))#, file = f))
#f = open("output.txt", "a")
main()
#f.close()
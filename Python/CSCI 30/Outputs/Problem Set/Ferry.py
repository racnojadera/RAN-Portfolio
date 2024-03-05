from collections import deque

def main():
	numOfCases = int(input())
	for i in range(numOfCases):
		inputValues = list(map(int, input().rstrip().split(" ")))
		boatLength = inputValues[0] * 100
		numOfCars = inputValues[1]
		leftQueue = deque()
		rightQueue = deque()
		
		for j in range(numOfCars):
			inputCarData = list(map(str, input().rstrip().split(" ")))
			if inputCarData[1] == "left":
				leftQueue.append(int(inputCarData[0]))
			elif inputCarData[1] == "right":
				rightQueue.append(int(inputCarData[0]))
		
		leftRightIndicator = 0
		outputNumber = 0
		while len(leftQueue) + len(rightQueue) != 0:
			outputNumber += 1
			currentSum = 0
			if leftRightIndicator != 0:
				while (len(rightQueue) != 0) and (currentSum + rightQueue[0] <= boatLength):
					currentSum += rightQueue.popleft()
			else:
				while (len(leftQueue) != 0) and (currentSum + leftQueue[0] <= boatLength):
					currentSum += leftQueue.popleft()
			leftRightIndicator  = 1 - leftRightIndicator
			
		
		print(outputNumber)
main()
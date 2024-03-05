numberOfInput = int(input())
for i in range(numberOfInput):
	outputValue = 0
	testCaseArray = list(map(int, input().split(' ')))
	if testCaseArray[0] > testCaseArray[1]:
		largerDigit = testCaseArray[0]
		smallerDigit = testCaseArray[1]
	else:
		largerDigit = testCaseArray[1]
		smallerDigit = testCaseArray[0]
	sum = largerDigit + smallerDigit
	
	inputCount = abs(largerDigit)
	if smallerDigit < 0:
		inputCount += abs(smallerDigit - 1)
	else:
		inputCount -= abs(smallerDigit - 1)
	
	if inputCount%2 == 1:
		outputValue = smallerDigit + inputCount//2
		
	outputValue += sum*(inputCount//2)

	testCaseArray.clear()
	print("Test case # {}: {}".format(int(i + 1), outputValue))
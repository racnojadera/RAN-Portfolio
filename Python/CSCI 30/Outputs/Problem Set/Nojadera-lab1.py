#I have not discussed the Python language code in my program with anyone other than my instructor or the teaching assistants assigned to this course.
#I have not used Python language code obtained from another student, or any other unauthorized source, either modified or unmodified.
#If any Python language code or documentation used in my program was obtained from another source, such as a textbook or course notes, that has been clearly noted with a proper citation in the comments of my program.

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
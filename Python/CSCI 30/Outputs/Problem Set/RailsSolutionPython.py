def rearrangement(it, ol):
	initialTrain = it
	outputList = ol
	middleTrain = []
	valueChecker = False
	counter = 0
	while len(outputList) != 0:
		##
		print("Now checking " + str(outputList[counter]))
		print("initStack: ")
		print(initialTrain)
		print("midStack: ")
		print(middleTrain)
		print()
		##
		if len(outputList) != counter:
			if len(initialTrain) != 0:
				middleTrain.append(initialTrain[0])
				del initialTrain[0]
			if middleTrain[-1] == outputList[counter]:
				valueChecker = True
				middleTrain.pop()
				del outputList[counter]
				if counter != 0:
					counter -= 1
				else:
					counter = 0
			else:
				valueChecker = False
				counter += 1
		else:
			if middleTrain[-1] == outputList[0]:
				valueChecker = True
				counter -= 1
				del outputList[0]
				middleTrain.pop()
			else:
				valueChecker = False
				break
	return valueChecker
			

def main():
	loop = 2
	while loop != 0:
		confirmation = 1
		outputList = []
		initialTrain = []
		
		inputValue = input().rstrip().split(" ")
		
		if len(inputValue) == 1:
			if int(inputValue[0]) == 0:
				if loop > 0:
					print("")
					loop -= 1
					confirmation = 0
			else:
				inputValue = int(inputValue[0])
				initialTrain = [int(i) for i in range(1, inputValue+1)]
				outputList = [int(i) for i in input().rstrip().split()]
				result = rearrangement(initialTrain, outputList)
				loop = 2
		else:
			outputList = [int(i) for i in inputValue]
			initialTrain = [int(i) for i in range(1, max(outputList)+1)]
			result = rearrangement(initialTrain, outputList)
			loop = 2
		if confirmation == 1:
			if result:
				print("Yes")
			else:
				print("NO")
				
main()
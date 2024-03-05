def printAnswer(n):
	tempDirList = n
	outputValue = "/"
	for i in range(0, len(directoryList), 1):
		outputValue += directoryList[i] + "/"
	print(outputValue)

numberOfInput = int(input())
directoryList = []

for i in range(numberOfInput):
	inputFetcher = list(map(str, input().rstrip().split(' ')))
	if inputFetcher[0] == "pwd":
		printAnswer(directoryList)
		
	elif inputFetcher[0] == "cd":
		subDirectory = inputFetcher[1]
		if subDirectory[0] == "/":
			directoryList.clear()
			subDirectory = subDirectory[1:].split("/")
		else:
			subDirectory = subDirectory.split("/")

		for i in range(0, len(subDirectory), 1):
			if subDirectory[i] == "..":
				if len(directoryList) != 0:
					directoryList.pop()
			else:
				directoryList.append(subDirectory[i])
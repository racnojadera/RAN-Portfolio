def rearrangement(l):
	outputList = l
	if outputList.pop() == 0:
		return None
	
	initialPosition = []
	for i in range(len(outputList), 0, -1):
		initialPosition.append(outputList[i-1])
	
	middlePosition = []
	for i in range(len(outputList)):
		while True:
			if len(middlePosition) > 0:
				middleChecker = middlePosition.pop()
				if outputList[i] == middleChecker:
					break
				else:
					middlePosition.append(middleChecker)

			if len(initialPosition) > 0:
				initialChecker = initialPosition.pop()
				if outputList[i] == initialChecker:
					break
					
				elif outputList[i] != initialChecker:
					middlePosition.append(initialChecker)
					continue
			
			return "NO"
		
	return "YES"
			
def main(t):
	loop = t
	if loop == 1 or loop == 3:
		n = int(input())
		if n != 0:
			loop += 1
	if loop >= 2:
		pop = list(map(int, input().rstrip().split(' ')))
		result = rearrangement(pop)
		if result == None:
			print()
			main(1)
		else:
			print(result)
			main(2)

main(3)

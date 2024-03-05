def rearrangement(l):
	outputList = l
	if outputList[-1] == 0:
		return None
	
	initialPosition = []
	middlePosition = []
	
	for i in range(len(outputList), 0, -1):
		initialPosition.append(i)
	##print(initialPosition)
	
	for element in outputList:
		##print("Now Checking: " + str(element))
		while True:
			if len(middlePosition) != 0:
				if middleStackCheck(middlePosition, element):
					middlePosition.pop()
					##print("Initial Position: ")
					##print(initialPosition)
					##print("Middle Position: ")
					##print(middlePosition)
					##print()
					break
				##print("Last value for Middle Stack: " + str(middlePosition))
				##print()
				if middlePosition[-1] > element:
					return "NO"
			if len(initialPosition) != 0:
				if initStackCheck(initialPosition, element):
					initialPosition.pop()
					##print("Initial Position: ")
					##print(initialPosition)
					##print("Middle Position: ")
					##print(middlePosition)
					##print()
					break
				else:
					##print("transferred init to middle")
					##print()
					middlePosition.append(initialPosition.pop())
		
	return "YES"
	
def middleStackCheck(ms, vc):
	stack = ms
	valueCheck = vc
	if stack[-1] == valueCheck:
		return True
	else:
		return False

def initStackCheck(initial, vc):
	stack = initial
	valueCheck = vc
	if stack[-1] == valueCheck:
		return True
	else:
		return False

def main(t):
	loop = t
	if loop == 3 or loop == 1:
		n = int(input())
		if n > 0:
			loop += 1
	if loop >= 2:
		pop = list(map(int, input().rstrip().split(" ")))
		result = rearrangement(pop)
		if result == None:
			print()
			main(1)
			
		else:
			print(result)
			main(2)
main(3)
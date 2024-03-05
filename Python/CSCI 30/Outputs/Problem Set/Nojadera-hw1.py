#I have not discussed the Python language code in my program with anyone other than my instructor or the teaching assistants assigned to this course.
#I have not used Python language code obtained from another student, or any other unauthorized source, either modified or unmodified.
#If any Python language code or documentation used in my program was obtained from another source, such as a textbook or course notes, that has been clearly noted with a proper citation in the comments of my program.

#O(n)
import math

numberOfValues = int(input())

for i in range(numberOfValues):
	valueInput = int(input())
	numberOfDivisors = 0
	checker = 1
	
	while checker <= math.sqrt(valueInput):
		if valueInput % checker == 0:
			if checker**2 == valueInput:
				numberOfDivisors += 1
			else:
				numberOfDivisors += 2
		checker += 1
	
	print(numberOfDivisors)

#O(log n)
import math

numberOfValues = int(input())

for i in range(numberOfValues):
	valueInput = int(input())
	divisorExponentArray = []
	numberOfDivisors = 1
	
	while valueInput > 1:
		primeChecker = 2
		primeExponentChecker = 1
		oddIterations = 0
		
	#if even
		while valueInput % 2 == 0:
			if valueInput % (primeChecker**primeExponentChecker) == 0:
				primeExponentChecker += 1
			else:
				primeExponentChecker -=1
				divisorExponentArray.append(primeExponentChecker)
				valueInput /= (primeChecker**primeExponentChecker)
				break
		
	#if odd
		while (valueInput % 2 != 0) and (valueInput > 1):
			primeChecker = 3 + 2*oddIterations
			if valueInput % primeChecker != 0:
				oddIterations += 1
				continue
			while valueInput % primeChecker == 0:
				if valueInput % (primeChecker**primeExponentChecker) == 0:
					primeExponentChecker += 1
				
				else:
					primeExponentChecker -= 1
					divisorExponentArray.append(primeExponentChecker)
					valueInput /= (primeChecker**primeExponentChecker)
					oddIterations -= 1
					break
			break
	
	i = 0
	while i <= len(divisorExponentArray) - 1:
		numberOfDivisors = numberOfDivisors * (divisorExponentArray[i] + 1)
		i += 1
	print(numberOfDivisors)
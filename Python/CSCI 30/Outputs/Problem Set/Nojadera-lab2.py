#I have not discussed the Python language code in my program with anyone other than my instructor or the teaching assistants assigned to this course.
#I have not used Python language code obtained from another student, or any other unauthorized source, either modified or unmodified.
#If any Python language code or documentation used in my program was obtained from another source, such as a textbook or course notes, that has been clearly noted with a proper citation in the comments of my program.

import math

def numberOfLoops(n):
	if n > 0:
		listOfSquares.clear()
		sumOfSquares = 0
		userOutput = 0
		
		lowerBound, upperBound = map(int, input().split(" "))
		checkForSquares(lowerBound, upperBound)
		userOutput = averageSquares(sumOfSquares, len(listOfSquares))
		
		print("{0:.2f}".format(round(userOutput, 2)))
		numberOfLoops(n-1)
	
def checkForSquares(l, u):
	if l <= u:
		if (l >= 1) and (math.sqrt(l)%1 == 0):
			listOfSquares.append(l)
		checkForSquares(l+1, u)

def averageSquares(s, i):
	if i > 0:
		s += listOfSquares[i-1]
		return averageSquares(s, i-1)
	elif (i == 0) and (len(listOfSquares) != 0):
		return s/len(listOfSquares)
		
	else:
		return 0

m = int(input())
listOfSquares = []
sumOfSquares = 0
userOutput = 0
numberOfLoops(m)

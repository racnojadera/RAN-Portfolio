
import math
import os
import random
import re
import sys

# Complete the largestRectangle function below.
def largestRectangle(h):
    tempList = h
    resultList = []
    for i in range(len(tempList)):
        counter = 0
        for j in range(i, len(tempList)):
            if tempList[i] <= tempList[j]:
                counter += 1
            else:
                break    
        resultList.append(counter*tempList[i])
		
    for i in range(len(tempList)-1, 0, -1):
        counter = 0
        for j in range(i, 0, -1):
            if tempList[i] <= tempList[j]:
                counter += 1
            else:
                break    
        resultList.append(counter*tempList[i])
        print("result " + str(i) + ":" + str(resultList[i]) + " counter: " + str(counter))
    return max(resultList)

n = int(input())
h = list(map(int, input().rstrip().split()))
result = largestRectangle(h)
print(result)
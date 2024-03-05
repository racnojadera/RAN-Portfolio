
import math
import os
import random
import re
import sys

# Complete the isBalanced function below.
def isBalanced(s):
    compList = list(s)
    if len(compList) % 2 == 1:
        return "NO"
    openStack = []
    openList = ["{", "[", "("]
    for checkElement in compList:
        if checkElement in openList:
            openStack.append(checkElement)
        else:
            if len(openStack) == 0:
                return "NO"
            stackChecker = openStack.pop()
            if checkElement == "}" and stackChecker != "{":
                return "NO"
            if checkElement == "]" and stackChecker != "[":
                return "NO"
            if checkElement == ")" and stackChecker != "(":
                return "NO"
    if len(openStack) == 0:
        return "YES"
    else:
        return "NO"

t = int(input())

for i in range(t):
    s = input()

    result = isBalanced(s)

    print(result)

#https://www.toppr.com/guides/python-guide/questions/what-is-pascal-triangle-in-python/#:~:text=Pascals%20Triangle%20in%20python%20is,the%20two%20numbers%20above%20it.
def PascalTriangle(n):
    listOutput = []
    for i in range(n+1):
        tempList = []
        coefficient = 1
        for j in range(1, i+1):
            tempStr = str(coefficient) + " "
            tempList.append(tempStr)
            coefficient = coefficient * (i - j) // j
        
        tempOutput = ""
        for j in tempList:
            tempOutput += j + " "
        listOutput.append(tempOutput)
    
    margin = len(listOutput[-1])
    for i in listOutput:
        print(" "*(margin-len(i)//2) + i)

PascalTriangle(int(input("input: ")))
import os
import pandas as pd
from os import system, name

def ImportInputs(filename, listToOutput):
    file = open(".\\Output\\" + filename, "r")
    print("currently working with " + filename)
    fileLinePerLine = list(file)


    for line in fileLinePerLine:
        lineElements = line.split(", ")
        
        for i in lineElements:
            i.replace("['" , "a")
            print(i)

        listToOutput.append(tuple(lineElements))
    file.close()

def main():
    tupleOfOutputs = []
    for filename in os.listdir(".\\Output\\"):
        if filename.endswith(".txt"):
            ImportInputs(filename, tupleOfOutputs)
            print("\n\n\n")
    
    for i in tupleOfOutputs:
        print(i)
    pd.DataFrame(tupleOfOutputs).to_excel('output.xlsx', header=False, index=False)

main()
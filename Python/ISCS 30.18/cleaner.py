import os
import pandas as pd
from os import system, name

def clear():
    if name == "nt":
        _ = system("cls")
    else:
        _ = system("clear")

def RepresentsInt(s):
    try:
        int(s)
        return True
    except ValueError:
        return False

def GeneralizeFormat(line):
    indexOfGeneralStart = 0
    for lineToCheck in line:
        if "%;FICHIER-ACTIONS" in lineToCheck:
            indexOfGeneralStart = line.index(lineToCheck)

    newListOfLines = ['', '', '', '', '', '', '', '']
    for oldLine in line[indexOfGeneralStart:]:
        newListOfLines.append(oldLine)
    
    return newListOfLines

def ExtractRedundantFields(line, list):
    for lineToCheck in line: #school, run
        if "#laclasse=" in lineToCheck:
            list.append(lineToCheck.strip("\n"))
            break
    
    for lineToCheck in line: #student identifier
        if "#identifiant=" in lineToCheck:
            list.append(lineToCheck.strip("\n"))
            break

    list.append("F for set")

    for lineToCheck in line: #prob no
        if "#NumeroExercice=" in lineToCheck:
            list.append(lineToCheck.strip("\n"))
            break
    
    list.append("F for AbsProb")

    for lineToCheck in line: #date, time
        if "%;ACTIONS;" in lineToCheck:
            list.append(lineToCheck.strip("\n"))
            break

    for lineToCheck in line: #level
        if "#InfoListeEngendree=" in lineToCheck:
            list.append(lineToCheck.strip("\n"))
            break

def ExtractRedundantData(line, dataToBeExtracted):
    if dataToBeExtracted == "school":
        splittedLine = line.split()
        splittedLine[0] = splittedLine[0][11:]
        indexOfRun = splittedLine.index("Run")
        toReturn = ''
        for i in splittedLine[0:indexOfRun]:
            toReturn = toReturn + " " + i
        return toReturn[1:]
    elif dataToBeExtracted == "run":
        splittedLine = line.split()
        return splittedLine[-1][:-1]

    elif dataToBeExtracted == "student":
        indexOfStudentIdentifier = line.index("s")
        if RepresentsInt(line[indexOfStudentIdentifier+1:-1]):
            return int(line[indexOfStudentIdentifier+1:-1])
        else:
            return str(line[indexOfStudentIdentifier+1:]) + " but as an error"
    elif dataToBeExtracted == "probNo":
        if RepresentsInt(line[16:]):
            return int(line[16:])
        else:
            return str(line[16:]) + " but as an error"
    elif dataToBeExtracted == "date" or dataToBeExtracted == "time":
        splittedLine = line.split(";")
        dateTimeSplit = splittedLine[2].split("#")
        date,time = dateTimeSplit[1][5:], dateTimeSplit[2][6:]
        if dataToBeExtracted == "date":
            return date
        else:
            return time
    elif dataToBeExtracted == "level":
        splittedLine = line.split(" ")
        return splittedLine[1][1:-2]

def ExtractActionData(line):
    splittedLine = line.split(";")
    return splittedLine[:-1]
    
def ImportFile(filename, listOfRedundantInfo, listOfActions):
    file = open(".\\Input\\" + filename, "r")
    fileLinePerLine = list(file)

    #redundant info - start
    listContainingRedundantData = []
    ExtractRedundantFields(fileLinePerLine, listContainingRedundantData)
    #print("Data for " + filename)
    #print(listContainingRedundantData[1])

    listOfRedundantInfo.append(ExtractRedundantData(listContainingRedundantData[0], "school"))
    listOfRedundantInfo.append(ExtractRedundantData(listContainingRedundantData[0], "run"))
    listOfRedundantInfo.append(ExtractRedundantData(listContainingRedundantData[1], "student"))
    listOfRedundantInfo.append("Filler for Set")                                       #insert set here
    listOfRedundantInfo.append(ExtractRedundantData(listContainingRedundantData[3], "probNo"))
    listOfRedundantInfo.append("Filler for Absolute Problem No.")                      #insert absprob here
    listOfRedundantInfo.append(ExtractRedundantData(listContainingRedundantData[5], "date"))
    listOfRedundantInfo.append(ExtractRedundantData(listContainingRedundantData[5], "time"))
    listOfRedundantInfo.append(ExtractRedundantData(listContainingRedundantData[6], "level"))

    #print(fileLinePerLine[11]) #identifiant    //r1s01
    #print(fileLinePerLine[22]) #class          //Saint Paul Run 1
    #print(fileLinePerLine[33]) #problem no
    #print(fileLinePerLine[36]) #level          //CHABRO-1.0 B3
    #print(fileLinePerLine[72]) #date, time
    #redundant info - end

    #actions - start
    indexForStartOfActions = 0
    for line in fileLinePerLine:
        if "%;ACTIONS;" in line:
            indexForStartOfActions = fileLinePerLine.index(line)
    for lineForActions in fileLinePerLine[indexForStartOfActions+2:]:
        listOfActions.append(ExtractActionData(lineForActions))
    
    file.close()

def ExportFile(filename, listOfOutputs):
    file = open(".\\Output\\" + filename, "w+")
    for line in listOfOutputs:
        file.write(str(line).strip("\n") + "\n")
    file.close()

def ToExcel(listOfOut):
    pd.DataFrame(tuple(listOfOut)).to_excel('output.xlsx', header=False, index=False)

def main():
    listOfTotalOutputs = [["School", "Run", "Student", "Set", "Problem No.", "Absolute Problem No.", "Date", "Time Started", "Level", "Step", "Duration", "Action", "Error", "Etape", "Expression", "Etat", "Cursor", "Selection", "Equivalence", "Resolution"]]
    for filename in os.listdir(".\\Input"):
        listOfOutputs = []
        listOfRedundantInfo = []       #format = [school, run, student, set, absolute problem no., date, time started, level]
        listOfActions = []
        print("Currently working on " + str(filename))
        if filename.endswith(".txt"):
            ImportFile(filename, listOfRedundantInfo, listOfActions)
            for correspondingActions in listOfActions:
                listOfOutputs.append(listOfRedundantInfo + correspondingActions)
                listOfTotalOutputs.append(listOfRedundantInfo + correspondingActions)
            ExportFile(filename[:-4] + "-cleaned.txt", listOfOutputs)
    ToExcel(listOfTotalOutputs)

main()
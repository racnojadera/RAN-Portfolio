import os

directory = ".\\Input\\"
for filename in os.listdir(directory):
    oldFile = os.path.join(directory, filename)
    newFile = os.path.join(directory, filename[:-4] + ".txt")
    os.rename(oldFile, newFile)
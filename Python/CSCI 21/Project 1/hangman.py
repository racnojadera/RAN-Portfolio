import os

ALPHABET = [ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']

def cls():
	os.system(['clear','cls'][os.name == 'nt'])

def game(maxGuesses):
	def printWinMessage():
		print("Congratulations! You win!")

	def printLoseMessage():
		print("SORRY! YOU ARE HANGED!")
	
print("Please enter a word for the other player to guess:")
word = input()
cls()
game(6)

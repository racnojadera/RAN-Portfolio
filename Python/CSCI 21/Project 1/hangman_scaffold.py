# Identifying Header Information

# Certificate of Authorship

import os

ALPHABET = [ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']

# clears screen to hide previous input
def cls():
	os.system(['clear','cls'][os.name == 'nt'])
	
# controls game play
def game(maxGuesses):

	# print message when player wins
	def printWinMessage():
		print("Congratulations! You win!")

	# print message when player loses
	def printLoseMessage():
		print("SORRY! YOU ARE HANGED!")

	# concantenates each letter in a list to form one string
	def combine():
		return ''.join(unusedLetters)
			
	# replace dashes in guess with letter if the word contains the letter in those positions
	def makeGuess(letter):
		i = 0
		while i < len(word):
			if letter == word[i]:
				guessListKey[i] = 1
			i += 1
	
	# removes all elements in list equal to toRemove
	def remove(toRemove):
		while toRemove in unusedLetters:
			unusedLetters.remove(toRemove)
		
	# a string of blanks (hypens) equal in length to word
	def toBlanks(words): # DEBUG THIS FOR FUCKS SAKE UR FINISHED NA
		i = 0
		guesstemp = ''
		while i < len(word):
			if guessListKey[i] == 1:
				guesstemp += word[i]
			else:
				guesstemp += '-'
			i += 1
		return guesstemp
			
	guessListKey = []
	for i in word:
		guessListKey.append(0)
	guess = toBlanks(word)
	numGuessesLeft = maxGuesses
	unusedLetters = ALPHABET
	
	win = False 
	lose = False 
		
	
	# continuous game
	while True:
		print("\nGuess the word,", numGuessesLeft, "guess(es) left:", guess)
		print("Unused letters:", combine())
		
		#condition to end game
		if numGuessesLeft == 0:
			lose = True
			break
		elif '-' not in guess:
			win = True
			break
		
		# read input only if game is still ongoing
		newLetter = input().upper()
		
		# decide what to do based on input
		if (newLetter not in word) and (newLetter in unusedLetters):
			# a guess is used up and update the list of letters
			numGuessesLeft -= 1
			remove(newLetter)
		# when chosen letter has been previously used
		elif newLetter not in unusedLetters:
			# ask for input again
			continue
		# when chosen letter occurs in word to be guessed
		elif newLetter in unusedLetters:
			# process the guess with the letter and update the list of letters
			makeGuess(newLetter)
			guess = toBlanks(newLetter)
			remove(newLetter)
		# what to do when chosen letter does not occur in word to be guessed

	
	# when game ends, print appropriate message
	if win:
		return printWinMessage()
	elif lose:
		return printLoseMessage()
		
# ask player for word to be guessed
print("Please enter a word for the other player to guess:")
word = input().upper()
cls()
game(6)

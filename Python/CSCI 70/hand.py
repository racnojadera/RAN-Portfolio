import random

def DealCard():
    return random.randint(1,10)

def NewHand():
    return [DealCard()]

def UpCard(currentHand):
    return currentHand[0]

def AddCard(currentHand, newCard):
    currentHand.append(newCard)
    return currentHand

def Total(currentHand):
    return sum(currentHand)
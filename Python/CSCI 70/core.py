import hand

#if the total value of the hand currently checking is less than 17
#then the strategy has not yet satisfied
def StopAt17Strategy(currentHand, otherPlayerVisibleCard):
    if hand.Total(currentHand) < 17:
        return False
    return True

#if the dealer's visible card is less than or equal to 6,
#strategy is satisfied if their hand's total value is greater than or equal to 13
#otherwise, if the dealer's visible card is greater than 6 then StopAt17 strategy is implemented
def CheckDealersHandStrategy(currentHand, otherPlayerVisibleCard):
    if otherPlayerVisibleCard <= 6:
        return True if hand.Total(currentHand) >= 13 else False
    else:
        return StopAt17Strategy(currentHand, otherPlayerVisibleCard)

#returns the total value of all the cards of the player
def PlayHand(strategyToUse, currentHand, otherPlayerVisibleCard):
    if hand.Total(currentHand) == 21:
        return currentHand
    
    if (not strategyToUse(currentHand, otherPlayerVisibleCard)):
        hand.AddCard(currentHand, hand.DealCard())
        PlayHand(strategyToUse, currentHand, otherPlayerVisibleCard)
    
    return currentHand

#main flow of the game
def PlayGame(playerStrategy, dealerStrategy):
    dealerHand = hand.NewHand()
    playerHand = PlayHand(playerStrategy, hand.NewHand(), hand.UpCard(dealerHand))
    result = "" #for UI display
    
    dealerHand = PlayHand(dealerStrategy, dealerHand, hand.UpCard(playerHand))

    if (hand.Total(dealerHand) > 21):
        #print(1)
        result = "Dealer busts, Player wins"
    elif hand.Total(playerHand) > 21:
        #print(0)
        result = "Player busts, Dealer wins" #for UI display
    elif (hand.Total(playerHand) > hand.Total(dealerHand)):
        #print(1)
        result = "Player wins" #for UI display
    else:
        #print(0)
        result = "Dealer wins" #for UI display

    #additional conditions
    if (hand.Total(dealerHand) == hand.Total(playerHand)):                    #additional condition
        result = "Both hands are equal, game is a Tie"                        #additional condition
    if ((hand.Total(dealerHand) > 21) and (hand.Total(playerHand) > 21)):     #additional condition
        result = "Both hands bust, Dealer wins"                               #additional condition

    UIDisplayResults(playerStrategy, dealerStrategy, dealerHand, playerHand, result) #for UI display only
    return

#prints the strategies used, the hands, the total value of the hands, and the result of who won
def UIDisplayResults(playerStrategy, dealerStrategy, dealerHand, playerHand, result):
    #maxHandLength = max(len(str(dealerHand)), len(str(playerHand)))
    maxHandLength = 40
    print("Dealer's Strategy: " + dealerStrategy.__name__)
    print("Player's Strategy: " + playerStrategy.__name__ + "\n")
    print("Dealer's Hand: " + str(dealerHand) + " "*(maxHandLength-len(str(dealerHand))+10) + "Total: " + str(hand.Total(dealerHand)))
    print("Player's Hand: " + str(playerHand) + " "*(maxHandLength-len(str(playerHand))+10) + "Total: " + str(hand.Total(playerHand)))
    print("\n" + result + "\n")
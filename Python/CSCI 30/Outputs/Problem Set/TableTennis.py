n, k = map(int, input().rstrip().split(' '))
players = list(map(int, input().rstrip().split(' ')))
 
if n <= k:
	k = n - 1

playerWinner = 0
countUntilWin = 0

for i in range(1, n):
	tempComp = max(players[i], players[playerWinner])
	if players[playerWinner] == tempComp:
		countUntilWin += 1
	else:
		countUntilWin = 1
		playerWinner = i
	if countUntilWin == k:
		break
		
print(players[playerWinner])
import core

def start():
    core.PlayGame(core.CheckDealersHandStrategy, core.StopAt17Strategy)
    input()
    print("\n\n\n\n\n")
    start()

start()
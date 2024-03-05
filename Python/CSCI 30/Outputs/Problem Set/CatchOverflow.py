stack = [0]
limit = 2**32
queue = []
numberOfInputs = int(input())
 
for i in range(numberOfInputs):
    instructions = list(map(str, input().rstrip().split()))
    if instructions[0] == "for":
        stack.append(0.0)
        queue.append(int(instructions[1]))
        
    elif instructions[0] == "add":
        stack[len(stack)-1] = stack[len(stack)-1] + 1
        
    elif instructions[0] == "end":
        stack[len(stack)-1] = stack.pop() * queue.pop() + stack[len(stack)-1]
 
 
if stack[0] < limit:
	print(int(stack[0]))
else:
	print("OVERFLOW!!!")
/*
    4 points: Implemented an IntNode struct.
    6 points: Implemented a linked list but it's not quite a stack (demonstrate creation and traversal, at least).
    6 points: Implemented an IntStack struct (including push and pop functions).
    4 points: Implementation has no danger of causing a memory leak.
*/

#include <iostream>
#include "Lab3_Grp18_IntStack.hpp"

using namespace std;

void linkedListTraversal(IntNode *node)
{
    int i = 0;
    while (node != NULL)
    {
        i++;

        cout << "Node " << i << ": " << (*node).getNodeData() << endl;
        node = (*node).getNextNode();
    }
}

int main(void)
{
    IntNode *nextNode = NULL;
    IntNode *nodeList;
    for (int i = 10; i > 0; i--)
    {
        nodeList = new IntNode(i, nextNode);
        nextNode = nodeList;
    }
    cout << "Linked List Traversal" << endl;
    linkedListTraversal(nodeList);

    cout << "\n\n\nIntStack" << endl;
    IntStack *stack = new IntStack();
    cout << "\nPUSHING" << endl;
    for (int i = 1; i <= 10; i++)
    {
        cout << "Pushed: " << i << " to top" << endl;
        (*stack).push(i);
    }

    IntNode *newTopNode = (*stack).getTopNode();
    cout << "\nStack array of pushed elements" << endl;
    linkedListTraversal(newTopNode);

    cout << "\n\nPopping" << endl;
    for (int i = 1; i <= 5; i++)
    {
        cout << "Popped: " << (*stack).pop() << " from top" << endl;
    }

    newTopNode = (*stack).getTopNode();
    cout << "\n\nStack array of popped elements" << endl;
    linkedListTraversal(newTopNode);

    //Deallocate memory
    delete stack;
    stack = NULL;
    delete nodeList;
    nodeList = NULL;

    return 0;
}
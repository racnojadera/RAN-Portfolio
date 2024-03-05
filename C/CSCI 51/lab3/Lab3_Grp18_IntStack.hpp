#include "Lab3_Grp18_IntNode.hpp"

struct IntStack
{
private:
    IntNode *top;

public:
    IntStack()
    {
        top = NULL;
    }
    void push(int data)
    {
        top = new IntNode(data, top);
    }
    IntNode *getTopNode()
    {
        return top;
    }
    int pop()
    {
        int elementData = 0;
        if (top != NULL)
        {
            //get value of element on top of array
            elementData = (*top).getNodeData();

            IntNode *tempTop = (*top).getNextNode();

            delete top;
            top = tempTop;
            return elementData;
        }
        return elementData;
    }
    ~IntStack()
    {
        while (top != NULL)
        {
            IntNode *tempTop = top;
            top = (*top).getNextNode();
            delete tempTop;
            tempTop = NULL;
        }
    }
};
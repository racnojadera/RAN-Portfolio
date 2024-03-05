struct IntNode
{
private:
    int nodeData;
    IntNode *nextNode;

public:
    IntNode(int data, IntNode *node)
    {
        nodeData = data;
        nextNode = node;
    }
    int getNodeData()
    {
        return nodeData;
    }
    IntNode *getNextNode()
    {
        return nextNode;
    }
    ~IntNode() {}
};
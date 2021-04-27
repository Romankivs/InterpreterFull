#include "STNode.h"

fullCmdNode::fullCmdNode()
{

}

void fullCmdNode::performAction()
{

}

equalSignNode::equalSignNode(string& name, string& value)
{
    equalSignData tmp = {&name, &value};
    NodeData = tmp;
    cout << name << "=" << value << endl;
};

void equalSignNode::performAction()
{

}

cmdNode::cmdNode()
{

}

void cmdNode::performAction()
{

}

runNode::runNode(string& func, string& lib)
{
    cout << "run " << func << " from " << lib << endl;
}

void runNode::performAction()
{

}

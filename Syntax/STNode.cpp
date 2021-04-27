#include "STNode.h"

fullCmdNode::fullCmdNode()
{

}

void fullCmdNode::performAction()
{

}

equalSignNode::equalSignNode(string& name, string& value)
{
    NodeData = equalSignData{make_shared<string>(name), make_shared<string>(value)};
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

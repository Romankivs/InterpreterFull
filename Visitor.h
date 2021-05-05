#pragma once
#include "STNode.h"

class Visitor {
public:
  virtual void visit(argcNode &node) = 0;
  virtual void visit(argvNode &node) = 0;
  virtual void visit(cmdNode &node) = 0;
  virtual void visit(echoNode &node) = 0;
  virtual void visit(envpNode &node) = 0;
  virtual void visit(equalSignNode &node) = 0;
  virtual void visit(fullCmdNode &node) = 0;
  virtual void visit(helpNode &node) = 0;
  virtual void visit(quitNode &node) = 0;
  virtual void visit(rawNode &node) = 0;
  virtual void visit(runNode &node) = 0;
  virtual void visit(stringNode &node) = 0;
  virtual void visit(varsNode &node) = 0;
  virtual void visit(varSubstitutionNode &node) = 0;

  virtual ~Visitor() = default;
};


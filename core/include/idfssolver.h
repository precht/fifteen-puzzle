#ifndef IDFSSOLVER_H
#define IDFSSOLVER_H

#include "solver.h"
#include <stack>

class IdfsSolver : public Solver
{
  std::stack<State> mStack;
  int64_t cDepthLimit = 10; //1.31e12;

private:
  bool solve() override;
};

#endif // IDFSSOLVER_H

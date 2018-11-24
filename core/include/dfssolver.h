#ifndef DFSSOLVER_H
#define DFSSOLVER_H

#include "solver.h"
#include <stack>

class DfsSolver : public Solver
{
  std::stack<State> mStack;

  bool solve() override;
};

#endif // DFSSOLVER_H
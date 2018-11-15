#ifndef BFSSOLVER_H
#define BFSSOLVER_H

#include "solver.h"
#include <queue>

class BfsSolver : public Solver
{
  std::queue<State> mQueue;

private:
  bool solve() override;
};

#endif // BFSSOLVER_H

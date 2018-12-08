#ifndef DFSSOLVER_H
#define DFSSOLVER_H

#include "solver.h"
#include <stack>

class DfsSolver : public Solver
{
  std::stack<State> mStack;

public:
  bool initializeSearchLoop(const Board &cInitialBoard, const Heuristic::Type cType) override;
  bool isLoopEmpty() const override;
  bool processNextState() override;
};

#endif // DFSSOLVER_H

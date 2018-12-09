#ifndef DFSSOLVER_H
#define DFSSOLVER_H

#include "solver.h"
#include <stack>

class DfsSolver : public Solver
{
  std::stack<State> m_stack;

public:
  bool initializeSearchLoop(const Board &c_initialBoard, const Heuristic::Type c_type) override;
  bool isLoopEmpty() const override;
  bool processNextState() override;
};

#endif // DFSSOLVER_H

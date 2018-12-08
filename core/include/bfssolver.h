#ifndef BFSSOLVER_H
#define BFSSOLVER_H

#include "solver.h"
#include <queue>

class BfsSolver : public Solver
{
  std::queue<State> mQueue;

public:
  bool initializeSearchLoop(const Board &cInitialBoard, const Heuristic::Type cType) override;
  bool isLoopEmpty() const override;
  bool processNextState() override;
};

#endif // BFSSOLVER_H

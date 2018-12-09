#ifndef BFSSOLVER_H
#define BFSSOLVER_H

#include "solver.h"
#include <queue>

class BfsSolver : public Solver
{
  std::queue<State> m_queue;

public:
  bool initializeSearchLoop(const Board &c_initialBoard, const Heuristic::Type c_type) override;
  bool isLoopEmpty() const override;
  bool processNextState() override;
};

#endif // BFSSOLVER_H

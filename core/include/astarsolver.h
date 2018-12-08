#ifndef ASTARSOLVER_H
#define ASTARSOLVER_H

#include "solver.h"
#include <queue>

class AStarSolver : public Solver
{
public:
  struct AState
  {
    uint64_t memory = 0;
    Direction direction;
    uint32_t estimatedCost = 0;
    uint32_t depth = 0;

    AState() = default;
    AState(const Board &cBoard, const uint32_t cEstimatedCost);
    operator State() const;
  };

  struct Greater
  {
    bool operator()(const AState &cLhs, const AState &cRhs) const;
  };

  bool initializeSearchLoop(const Board &cInitialBoard, const Heuristic::Type cType) override;
  bool isLoopEmpty() const override;
  bool processNextState() override;

private:
  std::priority_queue<AState, std::vector<AState>, Greater> mPriorityQueue;
  Heuristic mHeuristic;
};

#endif // ASTARSOLVER_H

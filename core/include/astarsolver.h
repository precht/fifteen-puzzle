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
    unsigned estimatedTotalCost = 0;
    unsigned visitedCost = 0;

    AState() = default;
    AState(const Board &cBoard, const int cEstimatedTotalCost);
    operator State() const;
  };

  struct Greater
  {
    bool operator()(const AState &cLhs, const AState &cRhs) const;
  };

private:
  std::priority_queue<AState, std::vector<AState>, Greater> mPriorityQueue;
  Heuristic mHeuristic;

  bool solve();
};

#endif // ASTARSOLVER_H

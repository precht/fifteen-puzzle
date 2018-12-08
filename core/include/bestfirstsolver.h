#ifndef BESTFIRSTSOLVER_H
#define BESTFIRSTSOLVER_H

#include "solver.h"
#include "heuristic.h"
#include <queue>


class BestFirstSolver : public Solver
{
public:
  struct BFState
  {
    uint64_t memory = 0;
    Direction direction = Direction::None;
    uint8_t estimatedCost = 0;

    BFState() = default;
    BFState(const Board &cBoard, const uint8_t cEstimatedCost);
    operator State() const;
  };

  struct Greater
  {
    bool operator()(const BFState &cLhs, const BFState &cRhs) const;
  };

private:
  std::priority_queue<BFState, std::vector<BFState>, Greater> mPriorityQueue;
  Heuristic mHeuristic;

public:
  bool initializeSearchLoop(const Board &cInitialBoard, const Heuristic::Type cType) override;
  bool isLoopEmpty() const override;
  bool processNextState() override;
};

#endif // BESTFIRSTSOLVER_H

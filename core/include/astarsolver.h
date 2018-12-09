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
    AState(const Board &c_board, const uint32_t c_estimatedCost);
    operator State() const;
  };

  struct Greater
  {
    bool operator()(const AState &c_lhs, const AState &c_rhs) const;
  };

  bool initializeSearchLoop(const Board &c_initialBoard, const Heuristic::Type c_type) override;
  bool isLoopEmpty() const override;
  bool processNextState() override;

private:
  std::priority_queue<AState, std::vector<AState>, Greater> m_priorityQueue;
  Heuristic m_heuristic;
};

#endif // ASTARSOLVER_H

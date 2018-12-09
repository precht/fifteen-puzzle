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
    BFState(const Board &c_board, const uint8_t c_estimatedCost);
    operator State() const;
  };

  struct Greater
  {
    bool operator()(const BFState &c_lhs, const BFState &c_rhs) const;
  };

private:
  std::priority_queue<BFState, std::vector<BFState>, Greater> m_priorityQueue;
  Heuristic m_heuristic;

public:
  bool initializeSearchLoop(const Board &c_initialBoard, const Heuristic::Type c_type) override;
  bool isLoopEmpty() const override;
  bool processNextState() override;
};

#endif // BESTFIRSTSOLVER_H

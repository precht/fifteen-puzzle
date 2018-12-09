#ifndef SMASTARSOLVER_H
#define SMASTARSOLVER_H

#include "solver.h"
#include <set>
#include <unordered_map>
#include <climits>

class SmaStarSolver : public Solver
{
  static const uint32_t cInfinity = UINT32_MAX;
  // to find path of length N, cSizeLimit has to be at least N+1
  static const uint32_t cSizeLimit = 1e6; // TODO estimate proper limit

public:
  struct SetState
  {
    uint64_t memory = 0;
    uint32_t depth = 1;
    uint32_t estimatedCost = 0;
  };

  struct GraphState
  {
    Direction direction;
    uint32_t depth = 1;
    uint32_t estimatedCost = 0;
    std::vector<std::pair<uint64_t, bool>> children; // first = memory, second = is good
  };

  struct Less
  {
    bool operator()(const SetState &c_lhs, const SetState &c_rhs) const;
  };

private:
  std::set<SetState, Less> m_set;
  std::unordered_map<uint64_t, GraphState> m_graph;
  Heuristic m_heuristic;
  Less m_less;

  SetState m_finalSetState;

public:
  bool initializeSearchLoop(const Board &c_initialBoard, const Heuristic::Type c_type) override;
  bool isLoopEmpty() const override;
  bool processNextState() override;

private:
  void insert(const uint64_t cMemory, const GraphState cGraphState);
  void update(const SetState &setState);
  void storeResult() override;
};

#endif // SMASTARSOLVER_H

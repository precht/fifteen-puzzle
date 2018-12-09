#ifndef IDFSSOLVER_H
#define IDFSSOLVER_H

#include "solver.h"
#include "board.h"
#include "direction.h"
#include <stack>

class IdfsSolver : public Solver
{
public:
  struct IdfsState
  {
    uint64_t memory;
    Direction direction;
    uint32_t depth = 0;

    IdfsState(const Board &c_board);
    operator State() const;

    struct Hash
    {
      std::size_t operator()(const State &c_state) const;
    };

    struct Equal
    {
      bool operator()(const State &c_lhs, const State &c_rhs) const;
    };
  };

  bool initializeSearchLoop(const Board &c_initialBoard, const Heuristic::Type c_type) override;
  bool isLoopEmpty() const override;
  bool processNextState() override;

private:
  std::stack<IdfsState> mStack;
  std::unordered_set<IdfsState, IdfsState::Hash, IdfsState::Equal> mIdfsVisited;
  uint32_t mcDepthLimit = 2e8;
  uint32_t mDepth = 0;
};

#endif // IDFSSOLVER_H

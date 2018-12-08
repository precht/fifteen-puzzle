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

    IdfsState(const Board &cBoard);
    operator State() const;

    struct Hash
    {
      std::size_t operator()(const State &cState) const;
    };

    struct Equal
    {
      bool operator()(const State &cLhs, const State &cRhs) const;
    };
  };

  bool initializeSearchLoop(const Board &cInitialBoard, const Heuristic::Type cType) override;
  bool isLoopEmpty() const override;
  bool processNextState() override;

private:
  std::stack<IdfsState> mStack;
  std::unordered_set<IdfsState, IdfsState::Hash, IdfsState::Equal> mIdfsVisited;
  uint32_t mcDepthLimit = 2e8;
  uint32_t mDepth = 0;
};

#endif // IDFSSOLVER_H

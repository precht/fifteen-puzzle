#ifndef IDFSSOLVER_H
#define IDFSSOLVER_H

#include "solver.h"
#include "board.h"
#include "direction.h"
#include <stack>

class IdfsSolver : public Solver
{
  struct IdfsState
  {
    uint64_t memory;
    Direction direction;
    int depth = 0;

    IdfsState(const Board &cBoard);
    operator State() const;
  };

  std::stack<IdfsState> mStack;
  int cDepthLimit = 2e8;

  bool solve() override;
};

#endif // IDFSSOLVER_H

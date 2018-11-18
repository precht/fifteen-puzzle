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
  };

private:
  std::stack<IdfsState> mStack;
  uint32_t cDepthLimit = 2e8;

  bool solve() override;
};

#endif // IDFSSOLVER_H

#ifndef SOLVER_H
#define SOLVER_H

#include "direction.h"
#include "board.h"
#include "history.h"
#include "heuristic.h"
#include <vector>

class Solver
{
protected:
  Board mInitialBoard;
  Board mFinalBoard;
  History mVisited;
  std::vector<Direction> mResult;
  uint64_t mCheckedStates = 0;
  HeuristicType mDistanceType = WrongCount;

public:
  bool solve(const Board &cInitialBoard, const HeuristicType cType = WrongCount);
  std::vector<Direction> result() const;
  uint64_t checkedStates() const;

  virtual ~Solver() = default;

private:
  virtual bool solve() = 0;
};

#endif // SOLVER_H

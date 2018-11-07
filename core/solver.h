#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"
#include "history.h"
#include "direction.h"

#include <vector>

class SearchStrategyContainer;

class Solver
{
  Board mInitialBoard;
  Board mFinalBoard;
  History mVisited;
  std::vector<Direction> mResult;
  SearchStrategyContainer *mpWaitingMovements;

public:
  Solver();
  Solver(const Board &cInitialBoard);
  Board initialBoard() const;
  void setInitialBoard(const Board &cInitialBoard);
  bool solve(SearchStrategyContainer *pContainer);
  std::vector<Direction> result() const;

private:
  bool solve();
};

#endif // SOLVER_H

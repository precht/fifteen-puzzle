#include "solver.h"
#include "utils.h"

#include <algorithm>

bool Solver::solve(const Board &cInitialBoard)
{
  mInitialBoard = cInitialBoard;
  mFinalBoard = Utils::constructFinalBoard(cInitialBoard.rows(), cInitialBoard.columns());

  mResult.clear();
  mVisited.clear();
  mCheckedStates = 1;

  if (mInitialBoard == mFinalBoard)
    return true;

  if (!Utils::isSolvable(cInitialBoard) || !solve())
    return false;

  State currentState = mVisited.getFirstInserted({mFinalBoard, None});
  while (currentState.direction != None) {
    mResult.push_back(currentState.direction);
    Utils::reverseMovement(currentState.board, currentState.direction);
    currentState = mVisited.getFirstInserted(currentState);
  }
  std::reverse(mResult.begin(), mResult.end());

  return true;
}

std::vector<Direction> Solver::result() const
{
  return mResult;
}

uint64_t Solver::checkedStates() const
{
  return mCheckedStates;
}

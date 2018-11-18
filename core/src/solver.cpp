#include "solver.h"
#include "utils.h"

#include <algorithm>

bool Solver::solve(const Board &cInitialBoard, const Heuristic::Type cType)
{
  mInitialBoard = cInitialBoard;
  mFinalBoard = Utils::constructFinalBoard(cInitialBoard.rows(), cInitialBoard.columns());
  mDistance = cType;

  mResult.clear();
  mVisited.clear();
  mCheckedStates = 1;

  if (mInitialBoard == mFinalBoard)
    return true;

  if (!Utils::isSolvable(cInitialBoard) || !solve())
    return false;

  storeResult();
  return true;
}

void Solver::storeResult()
{
  Board board = mFinalBoard;
  State state = mVisited.getFirstInserted(mFinalBoard);
  while (state.direction != Direction::None) {
    mResult.push_back(state.direction);
    Utils::reverseMovement(board, state.direction);
    state = mVisited.getFirstInserted(board);
  }
  std::reverse(mResult.begin(), mResult.end());
}

std::vector<Direction> Solver::result() const
{
  return mResult;
}

uint64_t Solver::checkedStates() const
{
  return mCheckedStates;
}

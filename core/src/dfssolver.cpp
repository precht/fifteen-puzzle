#include "dfssolver.h"
#include "utils.h"
#include <cassert>

bool DfsSolver::initializeSearchLoop(const Board &cInitialBoard, const Heuristic::Type cType)
{
  if (Solver::initializeSearchLoop(cInitialBoard, cType) == false)
    return false;

  mStack = {};
  mStack.push({ mInitialBoard });
  return true;
}

bool DfsSolver::isLoopEmpty() const
{
    return (mStack.empty() || mIsSolved);
}

bool DfsSolver::processNextState()
{
  assert(!isLoopEmpty());
  Board board = mInitialBoard;
  State state = mStack.top();
  mStack.pop();
  mCheckedStates++;

  board.setMemory(state.memory);
  Utils::makeMovement(board, state.direction);
  state.memory = board.memory();

  if (mVisited.find(board) != mVisited.end())
    return false;
  mVisited.insert(state);

  if (board == mFinalBoard) {
    mIsSolved = true;
    storeResult();
    return true;
  }

  const Direction currentDirection = state.direction;
  auto possibleDirections = generatePossibleDirections(board);
  for (auto &direction : possibleDirections) {
    if (Direction::isReverseDirection(direction, currentDirection))
      continue;
    state.direction = direction;
    mStack.push(state);
  }

  return false;
}

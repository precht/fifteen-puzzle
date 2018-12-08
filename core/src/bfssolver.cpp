#include "bfssolver.h"
#include "utils.h"
#include <cassert>

bool BfsSolver::initializeSearchLoop(const Board &cInitialBoard, const Heuristic::Type cType)
{
  if (Solver::initializeSearchLoop(cInitialBoard, cType) == false)
    return false;

  mQueue = {};
  mQueue.push({ mInitialBoard });
  return true;
}

bool BfsSolver::isLoopEmpty() const
{
  return (mQueue.empty() || mIsSolved);
}

bool BfsSolver::processNextState()
{
  assert(!isLoopEmpty());
  Board board = mInitialBoard;
  State state = mQueue.front();
  mQueue.pop();
  mCheckedStates++;

  board.setMemory(state.memory);
  Utils::makeMovement(board, state.direction);
  state.memory = board.memory();

  if (mVisited.find(board) != mVisited.end())
    return  false;
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
    mQueue.push(state);
  }

  return false;
}

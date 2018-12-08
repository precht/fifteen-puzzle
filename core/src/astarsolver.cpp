#include "astarsolver.h"
#include "utils.h"
#include <climits>
#include <cassert>

bool AStarSolver::initializeSearchLoop(const Board &cInitialBoard, const Heuristic::Type cType)
{
  if (Solver::initializeSearchLoop(cInitialBoard, cType) == false)
    return false;

  mPriorityQueue = {};
  AState state = { mInitialBoard, mHeuristic(mInitialBoard, mFinalBoard, mDistance) };
  mPriorityQueue.push(state);
  return true;
}

bool AStarSolver::isLoopEmpty() const
{
  return (mPriorityQueue.empty() || mIsSolved);
}

bool AStarSolver::processNextState()
{
  assert(!isLoopEmpty());
  Board board = mInitialBoard;
  AState state = mPriorityQueue.top();
  mPriorityQueue.pop();
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

  // prevent overflow
  if (state.depth + UINT8_MAX >= UINT32_MAX)
    return false;

  state.depth++;
  state.estimatedCost = state.depth + mHeuristic(board, mFinalBoard, mDistance);

  const Direction currentDirection = state.direction;
  auto possibleDirections = generatePossibleDirections(board);
  for (auto &direction : possibleDirections) {
    if (Direction::isReverseDirection(direction, currentDirection))
      continue;
    state.direction = direction;
    mPriorityQueue.push(state);
  }

  return false;
}

AStarSolver::AState::AState(const Board &cBoard, const uint32_t cEstimatedCost)
  : memory(cBoard.memory()), estimatedCost(cEstimatedCost)
{ }

AStarSolver::AState::operator State() const
{
  return { memory, direction };
}

bool AStarSolver::Greater::operator()(const AState &cLhs, const AState &cRhs) const
{
  return (cLhs.estimatedCost > cRhs.estimatedCost);
}

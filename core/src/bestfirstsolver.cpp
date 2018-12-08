#include "bestfirstsolver.h"
#include "utils.h"
#include <cassert>

BestFirstSolver::BFState::BFState(const Board &cBoard, const uint8_t cEstimatedCost)
  : memory(cBoard.memory()), estimatedCost(cEstimatedCost)
{ }

BestFirstSolver::BFState::operator State() const
{
  return { memory, direction };
}

bool BestFirstSolver::Greater::operator()(const BFState &cLhs, const BFState &cRhs) const
{
  return (cLhs.estimatedCost > cRhs.estimatedCost);
}


bool BestFirstSolver::initializeSearchLoop(const Board &cInitialBoard, const Heuristic::Type cType)
{
  if (Solver::initializeSearchLoop(cInitialBoard, cType) == false)
    return false;

  mPriorityQueue = {};
  BFState state = { mInitialBoard, mHeuristic(mInitialBoard, mFinalBoard, mDistance) };
  mPriorityQueue.push(state);
  return true;
}

bool BestFirstSolver::isLoopEmpty() const
{
  return (mPriorityQueue.empty() || mIsSolved);
}

bool BestFirstSolver::processNextState()
{
  assert(!isLoopEmpty());
  Board board = mInitialBoard;
  BFState state = mPriorityQueue.top();
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

  state.estimatedCost = mHeuristic(board, mFinalBoard, mDistance);

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

#include "bestfirstsolver.h"
#include "utils.h"

bool BestFirstSolver::solve()
{
  mPriorityQueue = {};
  Board board = mInitialBoard;
  BFState state = { mInitialBoard, mHeuristic(mInitialBoard, mFinalBoard, mDistance) };
  mVisited.insert(mInitialBoard);

  auto possibleDirections = Utils::generatePossibleDirections(mInitialBoard);
  for (auto &direction : possibleDirections) {
    state.direction = direction;
    mPriorityQueue.push(state);
  }

  while (!mPriorityQueue.empty()) {
    state = mPriorityQueue.top();
    mPriorityQueue.pop();
    mCheckedStates++;

    board.setMemory(state.memory);
    Utils::makeMovement(board, state.direction);
    state.memory = board.memory();

    if (mVisited.find(board))
      continue;
    mVisited.insert(state);

    if (board == mFinalBoard)
      return true;

    state.estimatedCost = mHeuristic(board, mFinalBoard, mDistance);

    const Direction currentDirection = state.direction;
    possibleDirections = Utils::generatePossibleDirections(board);
    for (auto &direction : possibleDirections) {
      if (Direction::isReverseDirection(direction, currentDirection))
        continue;
      state.direction = direction;
      mPriorityQueue.push(state);
    }
  }

  return false;
}

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

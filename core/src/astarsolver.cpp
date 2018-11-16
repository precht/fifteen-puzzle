#include "astarsolver.h"
#include "utils.h"

bool AStarSolver::solve()
{
  mPriorityQueue = {};
  Board board = mInitialBoard;
  AState state = { mInitialBoard, mHeuristic(mInitialBoard, mFinalBoard, mDistance) };
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

    state.visitedCost++;
    state.estimatedTotalCost = state.visitedCost + mHeuristic(board, mFinalBoard, mDistance);

    possibleDirections = Utils::generatePossibleDirections(board);
    for (auto &direction : possibleDirections) {
      state.direction = direction;
      mPriorityQueue.push(state);
    }
  }

  return false;
}

AStarSolver::AState::AState(const Board &cBoard, const int cEstimatedTotalCost)
  : memory(cBoard.memory()), estimatedTotalCost(cEstimatedTotalCost)
{ }

AStarSolver::AState::operator State() const
{
  return { memory, direction };
}

bool AStarSolver::Greater::operator()(const AState &cLhs, const AState &cRhs) const
{
  return (cLhs.estimatedTotalCost > cRhs.estimatedTotalCost);
}

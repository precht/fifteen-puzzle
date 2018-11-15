#include "bestfirstsolver.h"
#include "utils.h"

bool BestFirstSolver::solve()
{
  mPriorityQueue = {};
  State currentState = {mInitialBoard, None};
  currentState.estimatedTotalCost = mHeuristic(mInitialBoard, mFinalBoard, mDistanceType);
  mVisited.insert(currentState);

  auto possibleDirections = Utils::generatePossibleDirections(mInitialBoard);
  for (auto &direction : possibleDirections) {
    currentState.direction = direction;
    mPriorityQueue.push(currentState);
  }

  while (!mPriorityQueue.empty()) {
    currentState = mPriorityQueue.top();
    mPriorityQueue.pop();
    mCheckedStates++;

    Utils::makeMovement(currentState.board, currentState.direction);
    currentState.estimatedTotalCost = mHeuristic(currentState.board, mFinalBoard, mDistanceType);
    if (mVisited.find(currentState))
      continue;
    mVisited.insert(currentState);

    if (currentState.board == mFinalBoard)
      return true;

    possibleDirections = Utils::generatePossibleDirections(currentState.board);
    for (auto &direction : possibleDirections) {
      currentState.direction = direction;
      mPriorityQueue.push(currentState);
    }
  }

  return false;
}

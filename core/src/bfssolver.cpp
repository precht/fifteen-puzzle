#include "bfssolver.h"
#include "utils.h"

bool BfsSolver::solve()
{
  mQueue = {};
  State currentState = {mInitialBoard, None};
  mVisited.insert(currentState);

  auto possibleDirections = Utils::generatePossibleDirections(mInitialBoard);
  for (auto &direction : possibleDirections) {
    currentState.direction = direction;
    mQueue.push(currentState);
  }

  while (!mQueue.empty()) {
    currentState = mQueue.front();
    mQueue.pop();
    mCheckedStates++;

    Utils::makeMovement(currentState.board, currentState.direction);
    if (mVisited.find(currentState))
      continue;
    mVisited.insert(currentState);

    if (currentState.board == mFinalBoard)
      return true;

    possibleDirections = Utils::generatePossibleDirections(currentState.board);
    for (auto &direction : possibleDirections) {
      currentState.direction = direction;
      mQueue.push(currentState);
    }
  }

  return false;
}

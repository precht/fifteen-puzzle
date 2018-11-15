#include "dfssolver.h"
#include "utils.h"

bool DfsSolver::solve()
{
  mStack = {};
  State currentState = {mInitialBoard, None};
  mVisited.insert(currentState);

  auto possibleDirections = Utils::generatePossibleDirections(mInitialBoard);
  for (auto &direction : possibleDirections) {
    currentState.direction = direction;
    mStack.push(currentState);
  }

  while (!mStack.empty()) {
    currentState = mStack.top();
    mStack.pop();
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
      mStack.push(currentState);
    }
  }

  return false;
}

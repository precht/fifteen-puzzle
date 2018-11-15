#include "idfssolver.h"
#include "utils.h"

bool IdfsSolver::solve()
{
  for (int64_t iCost = 1; iCost < cPathLenghtLimit; iCost++) {
    mStack = {};
    mVisited.clear();

    State currentState = { mInitialBoard, None };
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
      mVisited.insert(currentState);

      if (currentState.board == mFinalBoard)
        return true;

      currentState.visitedCost++;
      if (currentState.visitedCost >= iCost)
        continue;

      possibleDirections = Utils::generatePossibleDirections(currentState.board);
      for (auto &direction : possibleDirections) {
        currentState.direction = direction;
        mStack.push(currentState);
      }
    }
  }

  return false;
}

#include "idfssolver.h"
#include "utils.h"

bool IdfsSolver::solve()
{
  for (int64_t iDepth = 1; iDepth < cDepthLimit; iDepth++) {
    mStack = {};
    mVisited.clear();

    State currentState = { mInitialBoard, None, iDepth };
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

      currentState.level--;
      if (currentState.level <= 0)
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

#include "dfssolver.h"
#include "utils.h"

bool DfsSolver::solve()
{
  mStack = {};
  Board board = mInitialBoard;
  State state = { mInitialBoard };
  mVisited.insert(mInitialBoard);

  auto possibleDirections = Utils::generatePossibleDirections(mInitialBoard);
  for (auto &direction : possibleDirections) {
    state.direction = direction;
    mStack.push(state);
  }

  while (!mStack.empty()) {
    state = mStack.top();
    mStack.pop();
    mCheckedStates++;

    board.setMemory(state.memory);
    Utils::makeMovement(board, state.direction);
    state.memory = board.memory();

    if (mVisited.find(board))
      continue;
    mVisited.insert(state);

    if (board == mFinalBoard)
      return true;

    possibleDirections = Utils::generatePossibleDirections(board);
    for (auto &direction : possibleDirections) {
      state.direction = direction;
      mStack.push(state);
    }
  }

  return false;
}

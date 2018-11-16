#include "bfssolver.h"
#include "utils.h"

bool BfsSolver::solve()
{
  mQueue = {};
  Board board = mInitialBoard;
  State state { mInitialBoard };
  mVisited.insert(mInitialBoard);

  auto possibleDirections = Utils::generatePossibleDirections(mInitialBoard);
  for (auto &direction : possibleDirections) {
    state.direction = direction;
    mQueue.push(state);
  }

  while (!mQueue.empty()) {
    state = mQueue.front();
    mQueue.pop();
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
      mQueue.push(state);
    }
  }

  return false;
}

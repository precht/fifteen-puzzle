#include "bfssolver.h"
#include "utils.h"

bool BfsSolver::solve()
{
  mQueue = {};
  Board board = mInitialBoard;
  State state { mInitialBoard };
  mVisited.insert(mInitialBoard);

  auto possibleDirections = generatePossibleDirections(mInitialBoard);
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

    if (mVisited.find(board) != mVisited.end())
      continue;
    mVisited.insert(state);

    if (board == mFinalBoard)
      return true;

    const Direction currentDirection = state.direction;
    possibleDirections = generatePossibleDirections(board);
    for (auto &direction : possibleDirections) {
      if (Direction::isReverseDirection(direction, currentDirection))
        continue;
      state.direction = direction;
      mQueue.push(state);
    }
  }

  return false;
}

Solver* BfsSolver::clone() const
{
  return new BfsSolver(dynamic_cast<const BfsSolver&>(*this));
}

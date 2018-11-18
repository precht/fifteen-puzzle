#include "idfssolver.h"
#include "utils.h"

bool IdfsSolver::solve()
{
  for (uint32_t iDepth = 1; iDepth < cDepthLimit; iDepth++) {
    mStack = {};
    mVisited.clear();
    Board board = mInitialBoard;
    IdfsState state = { mInitialBoard };
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

      state.depth++;
      if (state.depth >= iDepth)
        continue;

      const Direction currentDirection = state.direction;
      possibleDirections = Utils::generatePossibleDirections(board);
      for (auto &direction : possibleDirections) {
        if (Direction::isReverseDirection(direction, currentDirection))
          continue;
        state.direction = direction;
        mStack.push(state);
      }
    }
  }

  return false;
}

IdfsSolver::IdfsState::IdfsState(const Board &cBoard)
  : memory(cBoard.memory())
{ }

IdfsSolver::IdfsState::operator State() const
{
  return { memory, direction };
}

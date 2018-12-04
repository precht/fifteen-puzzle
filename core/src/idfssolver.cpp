#include "idfssolver.h"
#include "utils.h"

bool IdfsSolver::solve()
{
  for (uint32_t iDepth = 1; iDepth < cDepthLimit; iDepth++) {
    mStack = {};
    mIdfsVisited.clear();
    Board board = mInitialBoard;
    IdfsState state = { mInitialBoard };
    mIdfsVisited.insert(mInitialBoard);

    auto possibleDirections = generatePossibleDirections(mInitialBoard);
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

      auto it = mIdfsVisited.find(board);
      if (it != mIdfsVisited.end()) {
        if (it->depth <= state.depth)
          continue;
        mIdfsVisited.erase(it);
      }
      mIdfsVisited.insert(state);

      if (board == mFinalBoard) {
        mVisited.clear();
        while (!mIdfsVisited.empty()) {
          mVisited.insert(*mIdfsVisited.begin());
          mIdfsVisited.erase(mIdfsVisited.begin());
        }
        return true;
      }

      state.depth++;
      if (state.depth >= iDepth)
        continue;

      const Direction currentDirection = state.direction;
      possibleDirections = generatePossibleDirections(board);
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

std::size_t IdfsSolver::IdfsState::Hash::operator()(const State &cState) const
{
  return cState.memory;
}

bool IdfsSolver::IdfsState::Equal::operator()(const State &cLhs, const State &cRhs) const
{
  return (cLhs.memory == cRhs.memory);
}

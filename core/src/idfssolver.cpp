#include "idfssolver.h"
#include "utils.h"
#include <cassert>

bool IdfsSolver::initializeSearchLoop(const Board &cInitialBoard, const Heuristic::Type cType)
{
  return Solver::initializeSearchLoop(cInitialBoard, cType);
}

bool IdfsSolver::isLoopEmpty() const
{
  return ((mStack.empty() && mDepth >= mcDepthLimit) || mIsSolved);
}

bool IdfsSolver::processNextState()
{
  assert(!isLoopEmpty());
  if (mStack.empty()) {
    mDepth++;
    mStack.push({ mInitialBoard });
    mIdfsVisited.clear();
  }

  Board board = mInitialBoard;
  IdfsState state = mStack.top();
  mStack.pop();
  mCheckedStates++;

  board.setMemory(state.memory);
  Utils::makeMovement(board, state.direction);
  state.memory = board.memory();

  auto it = mIdfsVisited.find(board);
  if (it != mIdfsVisited.end()) {
    if (it->depth <= state.depth)
      return false;
    mIdfsVisited.erase(it);
  }
  mIdfsVisited.insert(state);

  if (board == mFinalBoard) {
    mVisited.clear();
    mIsSolved = true;
    while (!mIdfsVisited.empty()) {
      mVisited.insert(*mIdfsVisited.begin());
      mIdfsVisited.erase(mIdfsVisited.begin());
    }
    storeResult();
    return true;
  }

  state.depth++;
  if (state.depth >= mDepth)
    return false;

  const Direction currentDirection = state.direction;
  auto possibleDirections = generatePossibleDirections(board);
  for (auto &direction : possibleDirections) {
    if (Direction::isReverseDirection(direction, currentDirection))
      continue;
    state.direction = direction;
    mStack.push(state);
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

#include "idfssolver.h"
#include "utils.h"
#include <cassert>

bool IdfsSolver::initializeSearchLoop(const Board &c_initialBoard, const Heuristic::Type c_type)
{
  return Solver::initializeSearchLoop(c_initialBoard, c_type);
}

bool IdfsSolver::isLoopEmpty() const
{
  return ((mStack.empty() && mDepth >= mcDepthLimit) || m_isSolved);
}

bool IdfsSolver::processNextState()
{
  assert(!isLoopEmpty());
  if (mStack.empty()) {
    mDepth++;
    mStack.push({ m_initialBoard });
    mIdfsVisited.clear();
  }

  Board board = m_initialBoard;
  IdfsState state = mStack.top();
  mStack.pop();
  m_checkedStates++;

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

  if (board == m_finalBoard) {
    m_visited.clear();
    m_isSolved = true;
    while (!mIdfsVisited.empty()) {
      m_visited.insert(*mIdfsVisited.begin());
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

IdfsSolver::IdfsState::IdfsState(const Board &c_board)
  : memory(c_board.memory())
{ }

IdfsSolver::IdfsState::operator State() const
{
  return { memory, direction };
}

std::size_t IdfsSolver::IdfsState::Hash::operator()(const State &c_state) const
{
  return c_state.memory;
}

bool IdfsSolver::IdfsState::Equal::operator()(const State &c_lhs, const State &c_rhs) const
{
  return (c_lhs.memory == c_rhs.memory);
}

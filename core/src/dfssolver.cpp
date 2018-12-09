#include "dfssolver.h"
#include "utils.h"
#include <cassert>

bool DfsSolver::initializeSearchLoop(const Board &c_initialBoard, const Heuristic::Type c_type)
{
  if (Solver::initializeSearchLoop(c_initialBoard, c_type) == false)
    return false;

  m_stack = {};
  m_stack.push({ m_initialBoard });
  return true;
}

bool DfsSolver::isLoopEmpty() const
{
    return (m_stack.empty() || m_isSolved);
}

bool DfsSolver::processNextState()
{
  assert(!isLoopEmpty());
  Board board = m_initialBoard;
  State state = m_stack.top();
  m_stack.pop();
  m_checkedStates++;

  board.setMemory(state.memory);
  Utils::makeMovement(board, state.direction);
  state.memory = board.memory();

  if (m_visited.find(board) != m_visited.end())
    return false;
  m_visited.insert(state);

  if (board == m_finalBoard) {
    m_isSolved = true;
    storeResult();
    return true;
  }

  const Direction currentDirection = state.direction;
  auto possibleDirections = generatePossibleDirections(board);
  for (auto &direction : possibleDirections) {
    if (Direction::isReverseDirection(direction, currentDirection))
      continue;
    state.direction = direction;
    m_stack.push(state);
  }

  return false;
}

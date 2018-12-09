#include "astarsolver.h"
#include "utils.h"
#include <climits>
#include <cassert>

bool AStarSolver::initializeSearchLoop(const Board &c_initialBoard, const Heuristic::Type c_type)
{
  if (Solver::initializeSearchLoop(c_initialBoard, c_type) == false)
    return false;

  m_priorityQueue = {};
  AState state = { m_initialBoard, m_heuristic(m_initialBoard, m_finalBoard, m_distance) };
  m_priorityQueue.push(state);
  return true;
}

bool AStarSolver::isLoopEmpty() const
{
  return (m_priorityQueue.empty() || m_isSolved);
}

bool AStarSolver::processNextState()
{
  assert(!isLoopEmpty());
  Board board = m_initialBoard;
  AState state = m_priorityQueue.top();
  m_priorityQueue.pop();
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

  // prevent overflow
  if (state.depth + UINT8_MAX >= UINT32_MAX)
    return false;

  state.depth++;
  state.estimatedCost = state.depth + m_heuristic(board, m_finalBoard, m_distance);

  const Direction currentDirection = state.direction;
  auto possibleDirections = generatePossibleDirections(board);
  for (auto &direction : possibleDirections) {
    if (Direction::isReverseDirection(direction, currentDirection))
      continue;
    state.direction = direction;
    m_priorityQueue.push(state);
  }

  return false;
}

AStarSolver::AState::AState(const Board &c_board, const uint32_t c_estimatedCost)
  : memory(c_board.memory()), estimatedCost(c_estimatedCost)
{ }

AStarSolver::AState::operator State() const
{
  return { memory, direction };
}

bool AStarSolver::Greater::operator()(const AState &c_lhs, const AState &c_rhs) const
{
  return (c_lhs.estimatedCost > c_rhs.estimatedCost);
}

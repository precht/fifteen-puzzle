#include "bestfirstsolver.h"
#include "utils.h"
#include <cassert>

BestFirstSolver::BFState::BFState(const Board &c_board, const uint8_t c_estimatedCost)
  : memory(c_board.memory()), estimatedCost(c_estimatedCost)
{ }

BestFirstSolver::BFState::operator State() const
{
  return { memory, direction };
}

bool BestFirstSolver::Greater::operator()(const BFState &c_lhs, const BFState &c_rhs) const
{
  return (c_lhs.estimatedCost > c_rhs.estimatedCost);
}


bool BestFirstSolver::initializeSearchLoop(const Board &c_initialBoard, const Heuristic::Type c_type)
{
  if (Solver::initializeSearchLoop(c_initialBoard, c_type) == false)
    return false;

  m_priorityQueue = {};
  BFState state = { m_initialBoard, m_heuristic(m_initialBoard, m_finalBoard, m_distance) };
  m_priorityQueue.push(state);
  return true;
}

bool BestFirstSolver::isLoopEmpty() const
{
  return (m_priorityQueue.empty() || m_isSolved);
}

bool BestFirstSolver::processNextState()
{
  assert(!isLoopEmpty());
  Board board = m_initialBoard;
  BFState state = m_priorityQueue.top();
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

  state.estimatedCost = m_heuristic(board, m_finalBoard, m_distance);

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

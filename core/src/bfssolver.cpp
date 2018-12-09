#include "bfssolver.h"
#include "utils.h"
#include <cassert>

bool BfsSolver::initializeSearchLoop(const Board &c_initialBoard, const Heuristic::Type c_type)
{
  if (Solver::initializeSearchLoop(c_initialBoard, c_type) == false)
    return false;

  m_queue = {};
  m_queue.push({ m_initialBoard });
  return true;
}

bool BfsSolver::isLoopEmpty() const
{
  return (m_queue.empty() || m_isSolved);
}

bool BfsSolver::processNextState()
{
  assert(!isLoopEmpty());
  Board board = m_initialBoard;
  State state = m_queue.front();
  m_queue.pop();
  m_checkedStates++;

  board.setMemory(state.memory);
  Utils::makeMovement(board, state.direction);
  state.memory = board.memory();

  if (m_visited.find(board) != m_visited.end())
    return  false;
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
    m_queue.push(state);
  }

  return false;
}

#include "solver.h"
#include "utils.h"
#include <cassert>
#include <algorithm>
#include <random>
#include <chrono>
//#include <iostream>

Solver::Solver()
{
  std::random_device rd;
  m_randomGenerator = std::mt19937(rd());
}

Solver::~Solver()
{ }

bool Solver::solve(const Board &c_initialBoard, const Heuristic::Type c_type)
{
  if (!initializeSearchLoop(c_initialBoard, c_type))
    return false;

  while (!isLoopEmpty() && !processNextState());
  return m_isSolved;
}

bool Solver::initializeSearchLoop(const Board &c_initialBoard, const Heuristic::Type c_type)
{
  m_initialBoard = c_initialBoard;
  m_finalBoard = Utils::constructFinalBoard(c_initialBoard.rows(), c_initialBoard.columns());
  m_distance = c_type;

  m_result.clear();
  m_visited.clear();
  m_checkedStates = 0;
  m_isSolved = false;

  return Utils::isSolvable(c_initialBoard);
}

void Solver::storeResult()
{
  m_result.clear();

  Board board = m_finalBoard;
  State state = *(m_visited.find(m_finalBoard));
  while (state.direction != Direction::None) {
    m_result.push_back(state.direction);
    Utils::reverseMovement(board, state.direction);
    assert(m_visited.find(board) != m_visited.end());
    state = *(m_visited.find(board));
  }
  std::reverse(m_result.begin(), m_result.end());
}

std::vector<Direction> Solver::result() const
{
  return m_result;
}

uint64_t Solver::checkedStates() const
{
  return m_checkedStates;
}

std::vector<Direction> Solver::generatePossibleDirections(const Board &c_board)
{
  std::vector<Direction> possibleDirections;
  auto zero = c_board.getPosition(0);
  if (m_order.empty()) {
    if (zero.row != 0)
      possibleDirections.push_back(Direction::Down);
    if (zero.row != c_board.rows() - 1)
      possibleDirections.push_back(Direction::Up);
    if (zero.column != 0)
      possibleDirections.push_back(Direction::Right);
    if (zero.column != c_board.columns() - 1)
      possibleDirections.push_back(Direction::Left);
    return possibleDirections;
  }

  if (m_isRandomOrder)
    std::shuffle(m_order.begin(), m_order.end(), m_randomGenerator);

  for (auto &x : m_order) {
    if (x == Direction::Down) {
      if (zero.row != 0)
        possibleDirections.push_back(x);
    } else if (x == Direction::Up) {
      if (zero.row != c_board.rows() - 1)
        possibleDirections.push_back(x);
    } else if (x == Direction::Right) {
      if (zero.column != 0)
        possibleDirections.push_back(x);
    } else if (x == Direction::Left) {
      if (zero.column != c_board.columns() - 1)
        possibleDirections.push_back(x);
    }
  }
  return possibleDirections;
}

void Solver::setOrder(const std::vector<Direction> &c_order)
{
  m_order = c_order;
}

void Solver::randomOrder(bool isRandomOrder)
{
  m_order = { Direction::Left, Direction::Right, Direction::Up, Direction::Down };
  m_isRandomOrder = isRandomOrder;
}

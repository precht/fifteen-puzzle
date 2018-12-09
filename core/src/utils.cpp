#include "utils.h"
#include "core.h"
#include <vector>
#include <ostream>

bool Utils::isSolvable(const Board &c_board)
{
  if (c_board.size() == 0)
    return false;
  std::vector<bool> isValue(16);
  for (uint8_t index = 0; index < c_board.size(); index++)
    isValue[c_board.valueAt(index / c_board.columns(), index % c_board.columns())] = true;
  for (uint8_t index = 0; index < c_board.size(); index++)
    if (!isValue[index])
      return false;

  uint32_t inversionCount = 0;
  for (uint8_t iLater = 1; iLater < c_board.size(); iLater++) {
    for (uint8_t iFormer = 0; iFormer < iLater; iFormer++) {
      auto former = c_board.valueAt(iFormer / c_board.columns(), iFormer % c_board.columns());
      auto later = c_board.valueAt(iLater / c_board.columns(), iLater % c_board.columns());
      if (later != 0 && former > later) inversionCount++;
    }
  }

  // https://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/
  auto zeroPosition = c_board.getPosition(0);
  if ((c_board.columns() % 2 == 1) || ((c_board.rows() - zeroPosition.row) % 2 == 1))
    return inversionCount % 2 == 0;
  else
    return inversionCount % 2 == 1;
}

Board Utils::constructFinalBoard(const uint8_t c_rows, const uint8_t c_columns)
{
  Board board = Board(c_rows, c_columns);
  const uint8_t cSize = c_rows * c_columns;
  for (uint8_t index = 0; index < cSize; index++) {
    uint8_t row = index / c_columns;
    uint8_t column = index % c_columns;
    uint8_t value = (index + 1) % cSize;
    board.setValueAt(row, column, value);
  }
  return board;
}

void Utils::makeMovement(Board &r_board, Direction direction)
{
  auto zeroPosition = r_board.getPosition(0);

  bool isCorrectDirection = true;
  switch (direction) {
  case Direction::Left: isCorrectDirection = (zeroPosition.column + 1 != r_board.columns()); break;
  case Direction::Right: isCorrectDirection = (zeroPosition.column != 0); break;
  case Direction::Up: isCorrectDirection = (zeroPosition.row + 1 != r_board.rows()); break;
  case Direction::Down: isCorrectDirection = (zeroPosition.row != 0); break;
  default:; // do nothing
  }
  if (!isCorrectDirection)
    throw CoreException(__FILE__, __LINE__, direction);

  uint8_t value;
  switch (direction) {
  case Direction::Left:
    value = r_board.valueAt(zeroPosition.row, zeroPosition.column + 1);
    r_board.setValueAt(zeroPosition.row, zeroPosition.column, value);
    r_board.setValueAt(zeroPosition.row, zeroPosition.column + 1, 0);
    break;
  case Direction::Right:
    value = r_board.valueAt(zeroPosition.row, zeroPosition.column - 1);
    r_board.setValueAt(zeroPosition.row, zeroPosition.column, value);
    r_board.setValueAt(zeroPosition.row, zeroPosition.column - 1, 0);
    break;
  case Direction::Up:
    value = r_board.valueAt(zeroPosition.row + 1, zeroPosition.column);
    r_board.setValueAt(zeroPosition.row, zeroPosition.column, value);
    r_board.setValueAt(zeroPosition.row + 1, zeroPosition.column, 0);
    break;
  case Direction::Down:
    value = r_board.valueAt(zeroPosition.row - 1, zeroPosition.column);
    r_board.setValueAt(zeroPosition.row, zeroPosition.column, value);
    r_board.setValueAt(zeroPosition.row - 1, zeroPosition.column, 0);
    break;
  default:; // do nothing
  }
}

void Utils::reverseMovement(Board &r_board, Direction direction)
{
  switch (direction) {
  case Direction::Left: direction = Direction::Right; break;
  case Direction::Right: direction = Direction::Left; break;
  case Direction::Up: direction = Direction::Down; break;
  case Direction::Down: direction = Direction::Up; break;
  default:; // do nothing
  }
  Utils::makeMovement(r_board, direction);
}

void Utils::printBoard(const Board &c_board, std::ostream &r_output)
{
  const uint8_t c_columns = c_board.columns();
  const auto cMaxDigitCount = std::to_string(c_board.size()).size();

  r_output << std::string(c_columns * (cMaxDigitCount + 1) + 3, '*') << '\n';
  for (uint8_t iRow = 0; iRow < c_board.rows(); iRow++) {
    r_output << "* ";
    for (uint8_t iColumn = 0; iColumn < c_columns; iColumn++) {
      const auto c_value = c_board.valueAt(iRow, iColumn);
      std::string stringValue = std::to_string(c_value);
      if (c_value == 0)
        stringValue = " ";
      r_output << stringValue << std::string(cMaxDigitCount - stringValue.size() + 1, ' ');
    }
    r_output << "*\n";
  }
  r_output << std::string(c_columns * (cMaxDigitCount + 1) + 3, '*') << '\n';
}

Solver* Utils::constructSolver(Solver::Algorithm algorithm)
{
  switch (algorithm) {
  case Solver::Bfs: return new BfsSolver();
  case Solver::Dfs: return new DfsSolver();
  case Solver::Idfs: return new IdfsSolver();
  case Solver::BestFirst: return new BestFirstSolver();
  case Solver::AStar: return new AStarSolver();
  case Solver::SmaStar: return new SmaStarSolver();
  }
  return nullptr;
}

#include "utils.h"
#include "coreexception.h"
#include <vector>
#include <ostream>

bool Utils::isSolvable(const Board &cBoard)
{
  if (cBoard.size() == 0)
    return false;
  std::vector<bool> isValue(16);
  for (uint8_t index = 0; index < cBoard.size(); index++)
    isValue[cBoard.valueAt(index / cBoard.columns(), index % cBoard.columns())] = true;
  for (uint8_t index = 0; index < cBoard.size(); index++)
    if (!isValue[index])
      return false;

  uint32_t inversionCount = 0;
  for (uint8_t iLater = 1; iLater < cBoard.size(); iLater++) {
    for (uint8_t iFormer = 0; iFormer < iLater; iFormer++) {
      auto former = cBoard.valueAt(iFormer / cBoard.columns(), iFormer % cBoard.columns());
      auto later = cBoard.valueAt(iLater / cBoard.columns(), iLater % cBoard.columns());
      if (later != 0 && former > later) inversionCount++;
    }
  }

  // https://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/
  auto zeroPosition = cBoard.getPosition(0);
  if ((cBoard.columns() % 2 == 1) || ((cBoard.rows() - zeroPosition.row) % 2 == 1))
    return inversionCount % 2 == 0;
  else
    return inversionCount % 2 == 1;
}

Board Utils::constructFinalBoard(const uint8_t cRows, const uint8_t cColumns)
{
  Board board = Board(cRows, cColumns);
  const uint8_t cSize = cRows * cColumns;
  for (uint8_t index = 0; index < cSize; index++) {
    uint8_t row = index / cColumns;
    uint8_t column = index % cColumns;
    uint8_t value = (index + 1) % cSize;
    board.setValueAt(row, column, value);
  }
  return board;
}

std::vector<Direction> Utils::generatePossibleDirections(const Board &cBoard)
{
  std::vector<Direction> possibleDirections;
  auto zero = cBoard.getPosition(0);
  if (zero.row != 0)
    possibleDirections.push_back(Direction::Down);
  if (zero.row != cBoard.rows() - 1)
    possibleDirections.push_back(Direction::Up);
  if (zero.column != 0)
    possibleDirections.push_back(Direction::Right);
  if (zero.column != cBoard.columns() - 1)
    possibleDirections.push_back(Direction::Left);
  return possibleDirections;
}

void Utils::makeMovement(Board &board, Direction direction)
{
  auto zeroPosition = board.getPosition(0);

  bool isCorrectDirection = true;
  switch (direction) {
  case Direction::Left: isCorrectDirection = (zeroPosition.column + 1 != board.columns()); break;
  case Direction::Right: isCorrectDirection = (zeroPosition.column != 0); break;
  case Direction::Up: isCorrectDirection = (zeroPosition.row + 1 != board.rows()); break;
  case Direction::Down: isCorrectDirection = (zeroPosition.row != 0); break;
  default: isCorrectDirection = false;
  }
  if (!isCorrectDirection)
    throw CoreException(__FILE__, __LINE__, direction);

  uint8_t value;
  switch (direction) {
  case Direction::Left:
    value = board.valueAt(zeroPosition.row, zeroPosition.column + 1);
    board.setValueAt(zeroPosition.row, zeroPosition.column, value);
    board.setValueAt(zeroPosition.row, zeroPosition.column + 1, 0);
    break;
  case Direction::Right:
    value = board.valueAt(zeroPosition.row, zeroPosition.column - 1);
    board.setValueAt(zeroPosition.row, zeroPosition.column, value);
    board.setValueAt(zeroPosition.row, zeroPosition.column - 1, 0);
    break;
  case Direction::Up:
    value = board.valueAt(zeroPosition.row + 1, zeroPosition.column);
    board.setValueAt(zeroPosition.row, zeroPosition.column, value);
    board.setValueAt(zeroPosition.row + 1, zeroPosition.column, 0);
    break;
  case Direction::Down:
    value = board.valueAt(zeroPosition.row - 1, zeroPosition.column);
    board.setValueAt(zeroPosition.row, zeroPosition.column, value);
    board.setValueAt(zeroPosition.row - 1, zeroPosition.column, 0);
    break;
  default:
    throw CoreException(__FILE__, __LINE__);
  }
}

void Utils::reverseMovement(Board &board, Direction direction)
{
  switch (direction) {
  case Direction::Left: direction = Direction::Right; break;
  case Direction::Right: direction = Direction::Left; break;
  case Direction::Up: direction = Direction::Down; break;
  case Direction::Down: direction = Direction::Up; break;
  default: throw CoreException(__FILE__, __LINE__);
  }
  Utils::makeMovement(board, direction);
}

void Utils::printBoard(const Board &cBoard, std::ostream &output)
{
  const uint8_t cColumns = cBoard.columns();
  const auto cMaxDigitCount = std::to_string(cBoard.size()).size();

  output << std::string(cColumns * (cMaxDigitCount + 1) + 3, '*') << '\n';
  for (uint8_t iRow = 0; iRow < cBoard.rows(); iRow++) {
    output << "* ";
    for (uint8_t iColumn = 0; iColumn < cColumns; iColumn++) {
      const auto cValue = cBoard.valueAt(iRow, iColumn);
      std::string stringValue = std::to_string(cValue);
      if (cValue == 0)
        stringValue = " ";
      output << stringValue << std::string(cMaxDigitCount - stringValue.size() + 1, ' ');
    }
    output << "*\n";
  }
  output << std::string(cColumns * (cMaxDigitCount + 1) + 3, '*') << '\n';
}

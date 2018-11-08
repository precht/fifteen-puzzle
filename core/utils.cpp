#include "utils.h"

#include "board.h"
#include "state.h"
#include "coreexception.h"

#include <vector>
#include <iostream>

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

  int inversionCount = 0;
  for (uint8_t iLater = 1; iLater < cBoard.size(); iLater++) {
    for (uint8_t iFormer = 0; iFormer < iLater; iFormer++) {
      auto former = cBoard.valueAt(iFormer / cBoard.columns(), iFormer % cBoard.columns());
      auto later = cBoard.valueAt(iLater / cBoard.columns(), iLater % cBoard.columns());
      if (later != 0u && former > later) inversionCount++;
    }
  }

  // https://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/
  Position zeroPosition = Utils::getZeroPosition(cBoard);
  if ((cBoard.columns() % 2 == 1) || ((cBoard.rows() - zeroPosition.row) % 2 == 1))
    return inversionCount % 2 == 0;
  else
    return inversionCount % 2 == 1;
}

Position Utils::getZeroPosition(const Board &cBoard)
{
  int zeroCount = 0;
  Position position = {0, 0};
  for (uint8_t iRow = 0; iRow < cBoard.rows(); iRow++)
    for (uint8_t iColumn = 0; iColumn < cBoard.columns(); iColumn++)
      if (cBoard.valueAt(iRow, iColumn) == 0u) {
        position = {iRow, iColumn};
        zeroCount++;
      }
  if (zeroCount == 0 || zeroCount > 1)
    throw CoreException(__FILE__, __LINE__);
  return position;
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
  Position zero = Utils::getZeroPosition(cBoard);
  if (zero.row != 0)
    possibleDirections.push_back(Down);
  if (zero.row != cBoard.rows() - 1)
    possibleDirections.push_back(Up);
  if (zero.column != 0)
    possibleDirections.push_back(Right);
  if (zero.column != cBoard.columns() - 1)
    possibleDirections.push_back(Left);
  return possibleDirections;
}

void Utils::makeMovement(State &movement)
{
  auto zeroPosition = Utils::getZeroPosition(movement.board);

  bool isCorrectDirection = true;
  switch (movement.direction) {
  case Left: isCorrectDirection = (zeroPosition.column + 1 != movement.board.columns()); break;
  case Right: isCorrectDirection = (zeroPosition.column != 0); break;
  case Up: isCorrectDirection = (zeroPosition.row + 1 != movement.board.rows()); break;
  case Down: isCorrectDirection = (zeroPosition.row != 0); break;
  default: isCorrectDirection = false;
  }
  if (!isCorrectDirection)
    throw CoreException(__FILE__, __LINE__);

  uint8_t value;
  switch (movement.direction) {
  case Left:
    value = movement.board.valueAt(zeroPosition.row, zeroPosition.column + 1);
    movement.board.setValueAt(zeroPosition.row, zeroPosition.column, value);
    movement.board.setValueAt(zeroPosition.row, zeroPosition.column + 1, 0);
    break;
  case Right:
    value = movement.board.valueAt(zeroPosition.row, zeroPosition.column - 1);
    movement.board.setValueAt(zeroPosition.row, zeroPosition.column, value);
    movement.board.setValueAt(zeroPosition.row, zeroPosition.column - 1, 0);
    break;
  case Up:
    value = movement.board.valueAt(zeroPosition.row + 1, zeroPosition.column);
    movement.board.setValueAt(zeroPosition.row, zeroPosition.column, value);
    movement.board.setValueAt(zeroPosition.row + 1, zeroPosition.column, 0);
    break;
  default: // Down
    value = movement.board.valueAt(zeroPosition.row - 1, zeroPosition.column);
    movement.board.setValueAt(zeroPosition.row, zeroPosition.column, value);
    movement.board.setValueAt(zeroPosition.row - 1, zeroPosition.column, 0);
  }
}

void Utils::reverseMovement(State &movement)
{
  switch (movement.direction) {
  case Left: movement.direction = Right; break;
  case Right: movement.direction = Left; break;
  case Up: movement.direction = Down; break;
  case Down: movement.direction = Up; break;
  default: throw CoreException(__FILE__, __LINE__);
  }
  Utils::makeMovement(movement);
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

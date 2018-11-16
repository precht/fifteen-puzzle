#include "heuristic.h"
#include "board.h"
#include "utils.h"
#include "coreexception.h"

uint8_t Heuristic::operator()(const Board &cLhs, const Board &cRhs, const Type cType) const
{
  switch (cType) {
  case ZeroTaxicab: return zeroTaxicab(cLhs, cRhs);
  case AllTaxicab: return allTaxicab(cLhs, cRhs);
  case WrongCount: return wrongCount(cLhs, cRhs);
  default: throw CoreException(__FILE__, __LINE__);
  }
}

uint8_t Heuristic::wrongCount(const Board &cLhs, const Board &cRhs)
{
  if (cLhs.rows() != cRhs.rows() || cLhs.columns() != cRhs.columns())
    throw CoreException(__FILE__, __LINE__);

  uint8_t count = 0;
  for (uint8_t iRow = 0; iRow < cLhs.rows(); iRow++)
    for (uint8_t iColumn = 0; iColumn < cLhs.columns(); iColumn++)
      if (cLhs.valueAt(iRow, iColumn) != cRhs.valueAt(iRow, iColumn))
        count++;
  return count;
}

uint8_t Heuristic::zeroTaxicab(const Board &cLhs, const Board &cRhs)
{
  if (cLhs.rows() != cRhs.rows() || cLhs.columns() != cRhs.columns())
    throw CoreException(__FILE__, __LINE__);

  auto lhsZero = cLhs.getPosition(0);
  auto rhsZero = cRhs.getPosition(0);
  return (abs(lhsZero.row - rhsZero.row) + abs(lhsZero.column - rhsZero.column));
}

uint8_t Heuristic::allTaxicab(const Board &cLhs, const Board &cRhs)
{
  if (cLhs.rows() != cRhs.rows() || cLhs.columns() != cRhs.columns())
    throw CoreException(__FILE__, __LINE__);

  uint8_t distance = 0;
  for (uint8_t iRow = 0; iRow < cLhs.rows(); iRow++) {
    for (uint8_t iColumn = 0; iColumn < cLhs.columns(); iColumn++) {
      auto rhsPosition = cRhs.getPosition(cLhs.valueAt(iRow, iColumn));
      distance += abs(rhsPosition.row - iRow) + abs(rhsPosition.column - iColumn);
    }
  }
  return distance;
}

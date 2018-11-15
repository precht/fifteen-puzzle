#include "heuristic.h"
#include "board.h"
#include "utils.h"
#include "coreexception.h"

int64_t Heuristic::operator()(const Board &cLhs, const Board &cRhs, const HeuristicType cType) const
{
  switch (cType) {
  case ZeroTaxicab: return zeroTaxicab(cLhs, cRhs);
  case AllTaxicab: return allTaxicab(cLhs, cRhs);
  case WrongCount: return wrongCount(cLhs, cRhs);
  default: throw CoreException(__FILE__, __LINE__);
  }
}

int64_t Heuristic::wrongCount(const Board &cLhs, const Board &cRhs)
{
  if (cLhs.rows() != cRhs.rows() || cLhs.columns() != cRhs.columns())
    throw CoreException(__FILE__, __LINE__);

  int64_t count = 0;
  for (uint8_t iRow = 0; iRow < cLhs.rows(); iRow++)
    for (uint8_t iColumn = 0; iColumn < cLhs.columns(); iColumn++)
      if (cLhs.valueAt(iRow, iColumn) != cRhs.valueAt(iRow, iColumn))
        count++;
  return count;
}

int64_t Heuristic::zeroTaxicab(const Board &cLhs, const Board &cRhs)
{
  if (cLhs.rows() != cRhs.rows() || cLhs.columns() != cRhs.columns())
    throw CoreException(__FILE__, __LINE__);

  Position lhsZero = cLhs.getPosition(0u);
  Position rhsZero = cRhs.getPosition(0u);
  return (abs(lhsZero.row - rhsZero.row) + abs(lhsZero.column - rhsZero.column));
}

int64_t Heuristic::allTaxicab(const Board &cLhs, const Board &cRhs)
{
  if (cLhs.rows() != cRhs.rows() || cLhs.columns() != cRhs.columns())
    throw CoreException(__FILE__, __LINE__);

  int64_t distance = 0;
  for (uint8_t iRow = 0; iRow < cLhs.rows(); iRow++) {
    for (uint8_t iColumn = 0; iColumn < cLhs.columns(); iColumn++) {
      Position rhsPosition = cRhs.getPosition(cLhs.valueAt(iRow, iColumn));
      distance += abs(rhsPosition.row - iRow) + abs(rhsPosition.column - iColumn);
    }
  }
  return distance;
}

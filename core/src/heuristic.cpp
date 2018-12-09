#include "heuristic.h"
#include "board.h"
#include "utils.h"
#include "coreexception.h"

uint8_t Heuristic::operator()(const Board &c_lhs, const Board &c_rhs, const Type c_type) const
{
  switch (c_type) {
  case ZeroTaxicab: return zeroTaxicab(c_lhs, c_rhs);
  case AllTaxicab: return allTaxicab(c_lhs, c_rhs);
  case WrongCount: return wrongCount(c_lhs, c_rhs);
  default: throw CoreException(__FILE__, __LINE__);
  }
}

uint8_t Heuristic::wrongCount(const Board &c_lhs, const Board &c_rhs)
{
  if (c_lhs.rows() != c_rhs.rows() || c_lhs.columns() != c_rhs.columns())
    throw CoreException(__FILE__, __LINE__);

  uint8_t count = 0;
  for (uint8_t iRow = 0; iRow < c_lhs.rows(); iRow++)
    for (uint8_t iColumn = 0; iColumn < c_lhs.columns(); iColumn++)
      if (c_lhs.valueAt(iRow, iColumn) != c_rhs.valueAt(iRow, iColumn))
        count++;
  return count;
}

uint8_t Heuristic::zeroTaxicab(const Board &c_lhs, const Board &c_rhs)
{
  if (c_lhs.rows() != c_rhs.rows() || c_lhs.columns() != c_rhs.columns())
    throw CoreException(__FILE__, __LINE__);

  auto lhsZero = c_lhs.getPosition(0);
  auto rhsZero = c_rhs.getPosition(0);
  return (abs(lhsZero.row - rhsZero.row) + abs(lhsZero.column - rhsZero.column));
}

uint8_t Heuristic::allTaxicab(const Board &c_lhs, const Board &c_rhs)
{
  if (c_lhs.rows() != c_rhs.rows() || c_lhs.columns() != c_rhs.columns())
    throw CoreException(__FILE__, __LINE__);

  uint8_t distance = 0;
  for (uint8_t iRow = 0; iRow < c_lhs.rows(); iRow++) {
    for (uint8_t iColumn = 0; iColumn < c_lhs.columns(); iColumn++) {
      const uint8_t lhsValue = c_lhs.valueAt(iRow, iColumn);
      if (lhsValue == 0u)
        continue;
      auto rhsPosition = c_rhs.getPosition(lhsValue);
      distance += abs(rhsPosition.row - iRow) + abs(rhsPosition.column - iColumn);
    }
  }
  return distance;
}

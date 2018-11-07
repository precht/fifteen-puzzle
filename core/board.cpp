#include "board.h"
#include "coreexception.h"

#include <vector>

Board::Board()
  : mRows(0), mColumns(0), mMemory(0)
{ }

Board::Board(const uint8_t cRows, const uint8_t cColumns)
  : mRows(cRows), mColumns(cColumns), mMemory(0)
{
  if (mRows * mColumns > 16)
    throw CoreException(__FILE__, __LINE__, "Board size is bigger then 15 puzzle. Unsupported.");
}

uint8_t Board::rows() const
{
  return mRows;
}

uint8_t Board::columns() const
{
  return mColumns;
}

uint8_t Board::size() const
{
  return mRows * mColumns;
}

uint64_t Board::memory() const
{
  return mMemory;
}

uint8_t Board::valueAt(const uint8_t cRow, const uint8_t cColumn) const
{
  if (cRow >= mRows || cColumn >= mColumns)
    throw CoreException(__FILE__, __LINE__);
  const auto cFirstBitPosition = (cRow * mColumns + cColumn) << 2;
  return (mMemory >> cFirstBitPosition) & 0b1111;
}

void Board::setValueAt(const uint8_t cRow, const uint8_t cColumn, const uint8_t cValue)
{
  if (cRow >= mRows || cColumn >= mColumns || cValue >= 16)
    throw CoreException(__FILE__, __LINE__, std::to_string(mRows) + " " + std::to_string(mColumns) + " " + std::to_string(cValue));
  const auto cFirstBitPosition = (cRow * mColumns + cColumn) << 2;
  mMemory &= ~(static_cast<uint64_t>(0b1111) << cFirstBitPosition);
  mMemory |= (static_cast<uint64_t>(cValue) << cFirstBitPosition);
}

bool Board::operator==(const Board &cOther) const
{
  return (this->columns() == cOther.columns()
          && this->rows() == cOther.rows()
          && this->mMemory == cOther.mMemory);
}

bool Board::operator!=(const Board &cOther) const
{
  return !(*this == cOther);
//  return false;
}

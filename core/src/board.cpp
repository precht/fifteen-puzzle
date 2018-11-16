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
    throw CoreException(__FILE__, __LINE__);
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

void Board::setMemory(const uint64_t &memory)
{
    mMemory = memory;
}

uint8_t Board::valueAt(const uint8_t cRow, const uint8_t cColumn) const
{
  if (cRow >= mRows || cColumn >= mColumns)
    throw CoreException(__FILE__, __LINE__);
  const auto cFirstBitPosition = (cRow * mColumns + cColumn) << 2;
  return (mMemory >> cFirstBitPosition) & 0b1111;
}

uint8_t Board::valueAt(const Position cPosition) const
{
  return valueAt(cPosition.row, cPosition.column);
}

void Board::setValueAt(const uint8_t cRow, const uint8_t cColumn, const uint8_t cValue)
{
  if (cRow >= mRows || cColumn >= mColumns || cValue >= 16)
    throw CoreException(__FILE__, __LINE__);
  const auto cFirstBitPosition = (cRow * mColumns + cColumn) << 2;
  mMemory &= ~(static_cast<uint64_t>(0b1111) << cFirstBitPosition);
  mMemory |= (static_cast<uint64_t>(cValue) << cFirstBitPosition);
}

void Board::setValueAt(const Position cPosition, const uint8_t cValue)
{
  setValueAt(cPosition.row, cPosition.column, cValue);
}

Board::Position Board::getPosition(const uint8_t cValue) const
{
  for (uint8_t iRow = 0; iRow < mRows; iRow++)
    for (uint8_t iColumn = 0; iColumn < mColumns; iColumn++)
      if (valueAt(iRow, iColumn) == cValue)
        return { iRow, iColumn };
  throw CoreException(__FILE__, __LINE__);
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
}

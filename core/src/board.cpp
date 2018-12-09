#include "board.h"
#include "coreexception.h"
#include <vector>

Board::Board()
    : m_rows(0), m_columns(0), m_memory(0)
{ }

Board::Board(const uint8_t c_rows, const uint8_t c_columns)
  : m_rows(c_rows), m_columns(c_columns), m_memory(0)
{
  if (m_rows * m_columns > 16)
    throw CoreException(__FILE__, __LINE__);
}

Board::Board(const uint8_t c_rows, const uint8_t c_columns, const std::vector<uint8_t> &c_values)
  : Board(c_rows, c_columns)
{
  setValues(c_values);
}

uint8_t Board::rows() const
{
  return m_rows;
}

uint8_t Board::columns() const
{
  return m_columns;
}

uint8_t Board::size() const
{
  return m_rows * m_columns;
}

uint64_t Board::memory() const
{
  return m_memory;
}

void Board::setMemory(const uint64_t &c_memory)
{
    m_memory = c_memory;
}

uint8_t Board::valueAt(const uint8_t c_row, const uint8_t c_column) const
{
  if (c_row >= m_rows || c_column >= m_columns)
    throw CoreException(__FILE__, __LINE__);
  const auto cFirstBitPosition = (c_row * m_columns + c_column) << 2;
  return (m_memory >> cFirstBitPosition) & 0b1111;
}

uint8_t Board::valueAt(const Position c_position) const
{
  return valueAt(c_position.row, c_position.column);
}

void Board::setValueAt(const uint8_t c_row, const uint8_t c_column, const uint8_t c_value)
{
  if (c_row >= m_rows || c_column >= m_columns || c_value >= 16)
    throw CoreException(__FILE__, __LINE__);
  const auto cFirstBitPosition = (c_row * m_columns + c_column) << 2;
  m_memory &= ~(static_cast<uint64_t>(0b1111) << cFirstBitPosition);
  m_memory |= (static_cast<uint64_t>(c_value) << cFirstBitPosition);
}

void Board::setValueAt(const Position c_position, const uint8_t c_value)
{
  setValueAt(c_position.row, c_position.column, c_value);
}

void Board::setValues(const std::vector<uint8_t> &c_values)
{
  const uint8_t c_size = size();
  if (c_values.size() != c_size)
    throw CoreException(__FILE__, __LINE__);
  for (uint8_t index = 0; index < c_size; index++)
    setValueAt(index / m_columns, index % m_columns, c_values[index]);
}

Board::Position Board::getPosition(const uint8_t c_value) const
{
  for (uint8_t iRow = 0; iRow < m_rows; iRow++)
    for (uint8_t iColumn = 0; iColumn < m_columns; iColumn++)
      if (valueAt(iRow, iColumn) == c_value)
        return { iRow, iColumn };
  throw CoreException(__FILE__, __LINE__);
}

bool Board::operator==(const Board &c_other) const
{
  return (this->columns() == c_other.columns()
          && this->rows() == c_other.rows()
          && this->m_memory == c_other.m_memory);
}

bool Board::operator!=(const Board &c_other) const
{
  return !(*this == c_other);
}

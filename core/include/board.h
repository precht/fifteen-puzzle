#ifndef BOARD_H
#define BOARD_H

#include "direction.h"
#include <cstdint>
#include <vector>

class Board
{
  uint8_t m_rows, m_columns;
  uint64_t m_memory;

public:
  struct Position
  {
    uint8_t row;
    uint8_t column;
  };

  Board();
  Board(const uint8_t c_rows, const uint8_t c_columns);
  Board(const uint8_t c_rows, const uint8_t c_columns, const std::vector<uint8_t> &c_values);

  uint8_t rows() const;
  uint8_t columns() const;
  uint8_t size() const;
  uint64_t memory() const;
  void setMemory(const uint64_t &c_memory);

  uint8_t valueAt(const uint8_t c_row, const  uint8_t c_column) const;
  uint8_t valueAt(const Position c_position) const;
  void setValueAt(const uint8_t c_row, const uint8_t c_column, const uint8_t c_value);
  void setValueAt(const Position c_position, const uint8_t c_value);
  void setValues(const std::vector<uint8_t> &c_values);

  Position getPosition(const uint8_t c_value) const;
  bool operator==(const Board &c_other) const;
  bool operator!=(const Board &c_other) const;
};

#endif // BOARD_H

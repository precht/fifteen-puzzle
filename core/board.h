#ifndef BOARD_H
#define BOARD_H

#include "direction.h"

#include <cstdint>

struct Position
{
  uint8_t row;
  uint8_t column;
};

class Board
{
  uint8_t mRows, mColumns;
  uint64_t mMemory;

public:
  Board();
  Board(const uint8_t cRows, const uint8_t cColumns);
  uint8_t rows() const;
  uint8_t columns() const;
  uint8_t size() const;
  uint64_t memory() const;
  uint8_t valueAt(const uint8_t cRow, const  uint8_t cColumn) const;
  void setValueAt(const uint8_t cRow, const uint8_t cColumn, const uint8_t cValue);
  bool operator==(const Board &cOther) const;
  bool operator!=(const Board &cOther) const;
};

#endif // BOARD_H

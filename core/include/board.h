#ifndef BOARD_H
#define BOARD_H

#include "direction.h"
#include <cstdint>

class Board
{
  uint8_t mRows, mColumns;
  uint64_t mMemory;

public:
  struct Position
  {
    uint8_t row;
    uint8_t column;
  };

  Board();
  Board(const uint8_t cRows, const uint8_t cColumns);

  uint8_t rows() const;
  uint8_t columns() const;
  uint8_t size() const;
  uint64_t memory() const;
  void setMemory(const uint64_t &memory);

  uint8_t valueAt(const uint8_t cRow, const  uint8_t cColumn) const;
  uint8_t valueAt(const Position cPosition) const;
  void setValueAt(const uint8_t cRow, const uint8_t cColumn, const uint8_t cValue);
  void setValueAt(const Position cPosition, const uint8_t cValue);

  Position getPosition(const uint8_t cValue) const;
  bool operator==(const Board &cOther) const;
  bool operator!=(const Board &cOther) const;
};

#endif // BOARD_H

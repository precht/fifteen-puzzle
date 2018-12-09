#ifndef HEURISTIC_H
#define HEURISTIC_H

#include <cstdint>
class Board;

struct Heuristic
{
  enum Type { WrongCount, ZeroTaxicab, AllTaxicab };

  uint8_t operator()(const Board &c_lhs, const Board &c_rhs, const Type c_type) const;
  static uint8_t wrongCount(const Board& c_lhs, const Board &c_rhs);
  static uint8_t allTaxicab(const Board& c_lhs, const Board &c_rhs);
  static uint8_t zeroTaxicab(const Board& c_lhs, const Board &c_rhs);
};

#endif // HEURISTIC_H

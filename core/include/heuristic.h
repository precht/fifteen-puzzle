#ifndef HEURISTIC_H
#define HEURISTIC_H

#include <cstdint>
class Board;

struct Heuristic
{
  enum Type { WrongCount, ZeroTaxicab, AllTaxicab };

  uint8_t operator()(const Board &cLhs, const Board &cRhs, const Type cType) const;
  static uint8_t wrongCount(const Board& cLhs, const Board &cRhs);
  static uint8_t allTaxicab(const Board& cLhs, const Board &cRhs);
  static uint8_t zeroTaxicab(const Board& cLhs, const Board &cRhs);
};

#endif // HEURISTIC_H

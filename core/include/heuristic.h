#ifndef HEURISTIC_H
#define HEURISTIC_H

#include <cstdint>
class Board;

enum HeuristicType { WrongCount, ZeroTaxicab, AllTaxicab};

struct Heuristic
{
  int64_t operator()(const Board &cLhs, const Board &cRhs, const HeuristicType cType) const;
  static int64_t wrongCount(const Board& cLhs, const Board &cRhs);
  static int64_t allTaxicab(const Board& cLhs, const Board &cRhs);
  static int64_t zeroTaxicab(const Board& cLhs, const Board &cRhs);
};

#endif // HEURISTIC_H

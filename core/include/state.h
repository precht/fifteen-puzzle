#ifndef STATE_H
#define STATE_H

#include "board.h"
#include "direction.h"

/* State is a Board wrapper for History class.
 * State's compare function checks only if boards are identical and ommits other members.
 */
struct State
{
  Board board;
  Direction direction;
  int64_t visitedCost = 0;
  int64_t estimatedTotalCost = 0;

  State();
  State(const Board &board, const Direction direction);
};

struct StateBoardHash
{
  std::size_t operator()(const State &cState) const;
};

struct StateBoardEqual
{
  bool operator()(const State &cLhs, const State &cRhs) const;
};

struct StateTotalCostGreater
{
  bool operator()(const State &cLhs, const State &cRhs) const;
};


#endif // STATE_H

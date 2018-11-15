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
  int64_t level = 0;

public:
  State();
  State(const Board &board, const Direction direction, int64_t level = 0);
  bool operator==(const State &cOther) const;
  bool operator!=(const State &cOther) const;
};

struct StateHash
{
  std::size_t operator()(const State &cState) const noexcept;
};

#endif // STATE_H

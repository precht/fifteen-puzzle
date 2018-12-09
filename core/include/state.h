#ifndef STATE_H
#define STATE_H

#include "board.h"
#include "direction.h"

struct State
{
  uint64_t memory = 0;
  Direction direction;

  State() = default;
  State(const uint64_t &c_memory, const Direction c_direction = Direction::None);
  State(const Board& c_board, const Direction c_direction = Direction::None);

  struct Hash
  {
    std::size_t operator()(const State &c_state) const;
  };

  struct Equal
  {
    bool operator()(const State &c_lhs, const State &c_rhs) const;
  };
};

#endif // STATE_H

#ifndef STATE_H
#define STATE_H

#include "board.h"
#include "direction.h"

struct State
{
  uint64_t memory = 0;
  Direction direction;

  State() = default;
  State(const uint64_t &cMemory, const Direction cDirection = Direction::None);
  State(const Board& cBoard, const Direction cDirection = Direction::None);

  struct Hash
  {
    std::size_t operator()(const State &cState) const;
  };

  struct Equal
  {
    bool operator()(const State &cLhs, const State &cRhs) const;
  };
};

#endif // STATE_H

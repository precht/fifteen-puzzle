#include "state.h"

State::State(const uint64_t &c_memory, const Direction c_direction)
  : memory(c_memory), direction(c_direction)
{ }

State::State(const Board &c_board, const Direction c_direction)
  : memory(c_board.memory()), direction(c_direction)
{ }

std::size_t State::Hash::operator()(const State &c_state) const
{
    return c_state.memory;
}

bool State::Equal::operator()(const State &c_lhs, const State &c_rhs) const
{
    return (c_lhs.memory == c_rhs.memory);
}

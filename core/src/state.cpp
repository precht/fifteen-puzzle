#include "state.h"

State::State(const uint64_t &cMemory, const Direction cDirection)
  : memory(cMemory), direction(cDirection)
{ }

State::State(const Board &cBoard, const Direction cDirection)
  : memory(cBoard.memory()), direction(cDirection)
{ }

std::size_t State::Hash::operator()(const State &cState) const
{
    return cState.memory;
}

bool State::Equal::operator()(const State &cLhs, const State &cRhs) const
{
    return (cLhs.memory == cRhs.memory);
}

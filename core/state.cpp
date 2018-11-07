#include "state.h"

State::State()
{ }

State::State(const Board &board, const Direction direction)
  : board(board), direction(direction)
{ }

bool State::operator==(const State &cOther) const
{
  return (cOther.board == this->board);
}

bool State::operator!=(const State &cOther) const
{
  return !(*this == cOther);
}

std::size_t StateHash::operator()(const State &cState) const noexcept
{
  return cState.board.memory();
}

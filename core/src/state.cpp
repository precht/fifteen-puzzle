#include "state.h"

State::State()
{ }

State::State(const Board &board, const Direction direction)
  : board(board), direction(direction)
{ }

std::size_t StateBoardHash::operator()(const State &cState) const
{
  return cState.board.memory();
}

bool StateBoardEqual::operator()(const State &cLhs, const State &cRhs) const
{
  return (cLhs.board == cRhs.board);
}

bool StateTotalCostGreater::operator()(const State &cLhs, const State &cRhs) const
{
  return (cLhs.estimatedTotalCost > cRhs.estimatedTotalCost);
}

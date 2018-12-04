#include "astarsolver.h"
#include "utils.h"
#include <iostream>
#include <climits>

bool AStarSolver::solve()
{
  mPriorityQueue = {};
  Board board = mInitialBoard;
  AState state = { mInitialBoard, mHeuristic(mInitialBoard, mFinalBoard, mDistance) };
  mVisited.insert(mInitialBoard);

  auto possibleDirections = generatePossibleDirections(mInitialBoard);
  for (auto &direction : possibleDirections) {
    state.direction = direction;
    mPriorityQueue.push(state);
  }

  while (!mPriorityQueue.empty()) {
    state = mPriorityQueue.top();
    mPriorityQueue.pop();
    mCheckedStates++;

    board.setMemory(state.memory);
    Utils::makeMovement(board, state.direction);
    state.memory = board.memory();

    if (mVisited.find(board) != mVisited.end())
      continue;
    mVisited.insert(state);

    if (board == mFinalBoard)
      return true;

    // prevent overflow
    if (state.depth + UINT8_MAX >= UINT32_MAX)
      continue;

    state.depth++;
    state.estimatedCost = state.depth + mHeuristic(board, mFinalBoard, mDistance);

    const Direction currentDirection = state.direction;
    possibleDirections = generatePossibleDirections(board);
    for (auto &direction : possibleDirections) {
      if (Direction::isReverseDirection(direction, currentDirection))
        continue;
      state.direction = direction;
      mPriorityQueue.push(state);
    }
  }

  return false;
}

Solver* AStarSolver::clone() const
{
  return new AStarSolver(dynamic_cast<const AStarSolver&>(*this));
}

AStarSolver::AState::AState(const Board &cBoard, const uint32_t cEstimatedCost)
  : memory(cBoard.memory()), estimatedCost(cEstimatedCost)
{ }

AStarSolver::AState::operator State() const
{
  return { memory, direction };
}

bool AStarSolver::Greater::operator()(const AState &cLhs, const AState &cRhs) const
{
  return (cLhs.estimatedCost > cRhs.estimatedCost);
}

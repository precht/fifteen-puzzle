#include "solver.h"
#include "coreexception.h"
#include "searchstrategycontainer.h"
#include "utils.h"

#include <iostream>
#include <algorithm>

Solver::Solver()
{ }

Solver::Solver(const Board &cInitialBoard)
  : mInitialBoard(cInitialBoard)
  , mFinalBoard(Utils::constructFinalBoard(cInitialBoard.rows(), cInitialBoard.columns()))
{ }

Board Solver::initialBoard() const
{
  return mInitialBoard;
}

void Solver::setInitialBoard(const Board &cInitialBoard)
{
  mInitialBoard = cInitialBoard;
  mFinalBoard = Utils::constructFinalBoard(cInitialBoard.rows(), cInitialBoard.columns());
}

bool Solver::solve(SearchStrategyContainer *pContainer)
{
  mResult.clear();
  mVisited.clear();
  pContainer->clear();
  mpWaitingMovements = pContainer;

  if (mInitialBoard == mFinalBoard)
    return true;

  if (!solve())
    return false;

  State currentState = mVisited.getFirstInserted({mFinalBoard, None});
  while (currentState.direction != None) {
    mResult.push_back(currentState.direction);
    Utils::reverseMovement(currentState);
    currentState = mVisited.getFirstInserted(currentState);
  }
  std::reverse(mResult.begin(), mResult.end());

  return true;
}

bool Solver::solve()
{
  State currentState = {mInitialBoard, None};
  mVisited.insert(currentState);

  auto possibleDirections = Utils::generatePossibleDirections(mInitialBoard);
  for (auto &direction : possibleDirections) {
    currentState.direction = direction;
    mpWaitingMovements->push(currentState);
  }

  while (!mpWaitingMovements->isEmpty()) {
    currentState = mpWaitingMovements->next();
    mpWaitingMovements->pop();

    Utils::makeMovement(currentState);
    if (mVisited.find(currentState))
      continue;
    mVisited.insert(currentState);

    if (currentState.board == mFinalBoard) {
      mVisited.insert(currentState);
      return true;
    }

    possibleDirections = Utils::generatePossibleDirections(currentState.board);
    for (auto &direction : possibleDirections) {
      currentState.direction = direction;
      mpWaitingMovements->push(currentState);
    }
  }

  return false;
}

std::vector<Direction> Solver::result() const
{
  return mResult;
}




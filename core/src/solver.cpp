#include "solver.h"
#include "utils.h"
#include <cassert>
#include <algorithm>
#include <random>
#include <chrono>
//#include <iostream>

Solver::Solver()
{
  std::random_device rd;
  mRandomGenerator = std::mt19937(rd());
//  std::cout << "solver created" << std::endl;
}

Solver::~Solver()
{
//  std::cout << "solver deleted" << std::endl;
}

bool Solver::solve(const Board &cInitialBoard, const Heuristic::Type cType)
{
//  mInitialBoard = cInitialBoard;
//  mFinalBoard = Utils::constructFinalBoard(cInitialBoard.rows(), cInitialBoard.columns());
//  mDistance = cType;

//  mResult.clear();
//  mVisited.clear();
//  mCheckedStates = 1;

//  if (mInitialBoard == mFinalBoard)
//    return true;

//  if (!Utils::isSolvable(cInitialBoard) || !solve())
//    return false;

//  storeResult();
//  return true;

  if (!initializeSearchLoop(cInitialBoard, cType))
    return false;
  while (!isLoopEmpty() && !processNextState());
  return mIsSolved;
}

bool Solver::initializeSearchLoop(const Board &cInitialBoard, const Heuristic::Type cType)
{
  mInitialBoard = cInitialBoard;
  mFinalBoard = Utils::constructFinalBoard(cInitialBoard.rows(), cInitialBoard.columns());
  mDistance = cType;

  mResult.clear();
  mVisited.clear();
  mCheckedStates = 0;
  mIsSolved = false;

  return Utils::isSolvable(cInitialBoard);
}

void Solver::storeResult()
{
  mResult.clear();

  Board board = mFinalBoard;
  State state = *(mVisited.find(mFinalBoard));
  while (state.direction != Direction::None) {
    mResult.push_back(state.direction);
    Utils::reverseMovement(board, state.direction);
    assert(mVisited.find(board) != mVisited.end());
    state = *(mVisited.find(board));
  }
  std::reverse(mResult.begin(), mResult.end());
}

std::vector<Direction> Solver::result() const
{
  return mResult;
}

uint64_t Solver::checkedStates() const
{
  return mCheckedStates;
}

std::vector<Direction> Solver::generatePossibleDirections(const Board &cBoard)
{
  std::vector<Direction> possibleDirections;
  auto zero = cBoard.getPosition(0);
  if (mOrder.empty()) {
    if (zero.row != 0)
      possibleDirections.push_back(Direction::Down);
    if (zero.row != cBoard.rows() - 1)
      possibleDirections.push_back(Direction::Up);
    if (zero.column != 0)
      possibleDirections.push_back(Direction::Right);
    if (zero.column != cBoard.columns() - 1)
      possibleDirections.push_back(Direction::Left);
    return possibleDirections;
  }

  if (mIsRandomOrder)
    std::shuffle(mOrder.begin(), mOrder.end(), mRandomGenerator);

  for (auto &x : mOrder) {
    if (x == Direction::Down) {
      if (zero.row != 0)
        possibleDirections.push_back(x);
    } else if (x == Direction::Up) {
      if (zero.row != cBoard.rows() - 1)
        possibleDirections.push_back(x);
    } else if (x == Direction::Right) {
      if (zero.column != 0)
        possibleDirections.push_back(x);
    } else if (x == Direction::Left) {
      if (zero.column != cBoard.columns() - 1)
        possibleDirections.push_back(x);
    }
  }
  return possibleDirections;
}

void Solver::setOrder(const std::vector<Direction> &order)
{
  mOrder = order;
}

void Solver::randomOrder(bool isRandomOrder)
{
  mOrder = { Direction::Left, Direction::Right, Direction::Up, Direction::Down };
  mIsRandomOrder = isRandomOrder;
}

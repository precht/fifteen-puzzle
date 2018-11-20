#ifndef SOLVER_H
#define SOLVER_H

#include "direction.h"
#include "board.h"
#include "state.h"
#include "heuristic.h"
#include <vector>
#include <unordered_set>
#include <random>

class Solver
{
public:
  enum Algorithm { Bfs, Dfs, Idfs, BestFirst, AStar, SmaStar };

protected:
  Board mInitialBoard;
  Board mFinalBoard;
  uint64_t mCheckedStates = 0;
  std::vector<Direction> mResult;
  Heuristic::Type mDistance = Heuristic::AllTaxicab;
  std::unordered_set<State, State::Hash, State::Equal> mVisited;
  std::vector<Direction> mOrder;
  bool mIsRandomOrder = false;
  std::mt19937 mRandomGenerator;

public:
  Solver();
  bool solve(const Board &cInitialBoard, const Heuristic::Type cType = Heuristic::AllTaxicab);
  std::vector<Direction> result() const;
  uint64_t checkedStates() const;
  virtual ~Solver() = default;

  std::vector<Direction> generatePossibleDirections(const Board &cBoard);

  void setOrder(const std::vector<Direction> &order);
  void randomOrder(bool isRandomOrder);

private:
  virtual bool solve();
  virtual void storeResult();
};

#endif // SOLVER_H

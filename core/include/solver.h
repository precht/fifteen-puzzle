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
  // TODO change all names to m_ ??

  Board mInitialBoard;
  Board mFinalBoard;
  uint64_t mCheckedStates = 0;
  std::vector<Direction> mResult;
  Heuristic::Type mDistance = Heuristic::AllTaxicab;
  std::unordered_set<State, State::Hash, State::Equal> mVisited;
  std::vector<Direction> mOrder;
  bool mIsRandomOrder = false;
  std::mt19937 mRandomGenerator;
  bool mIsSolved = false;

public:
  Solver();
  virtual ~Solver();

  /**
   * @brief single method implementing whole solving proccess
   * @return true if solved board, false if failed or board is not solvable
   *
   * @details This method should be used in most cases for solving board. The exception is when you
   * need a way to interupt process. In such case you should implement similar logic
   * as present in this method but between each call of 'processNextState' check for interupts.
   */
  bool solve(const Board &cInitialBoard, const Heuristic::Type cType = Heuristic::AllTaxicab);

  void setOrder(const std::vector<Direction> &order);
  void randomOrder(bool isRandomOrder);
  std::vector<Direction> result() const;
  uint64_t checkedStates() const;

  /**
   * @brief generates possible directions based on passed board and settings via
   * by setOrder and randomOrder functions
   */
  std::vector<Direction> generatePossibleDirections(const Board &cBoard);

  /**
   * @brief starts searching loop
   * @return false if board is not solvable
   * @details derived classes should call this parent method to initialize varaibles
   */
  virtual bool initializeSearchLoop(const Board &cInitialBoard, const Heuristic::Type cType = Heuristic::AllTaxicab);
  virtual bool isLoopEmpty() const = 0;
  /**
   * @brief process next state from search loop and add child states to loop
   * @return returns true if found
   * @details if found solution should store it
   */
  virtual bool processNextState() = 0;

protected:
  /**
   * @brief store result in mResult after search reaches final board.
   *
   * @details If derived class does not remembers visited states in mVisited, then it should
   * override this method.
   */
  virtual void storeResult();

//  // TODO remove
//  virtual bool solve() = 0;

};

#endif // SOLVER_H


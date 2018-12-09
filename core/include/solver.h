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
  Board m_initialBoard;
  Board m_finalBoard;
  uint64_t m_checkedStates = 0;
  std::vector<Direction> m_result;
  Heuristic::Type m_distance = Heuristic::AllTaxicab;
  std::unordered_set<State, State::Hash, State::Equal> m_visited;
  std::vector<Direction> m_order;
  bool m_isRandomOrder = false;
  std::mt19937 m_randomGenerator;
  bool m_isSolved = false;

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
  bool solve(const Board &c_initialBoard, const Heuristic::Type c_type = Heuristic::AllTaxicab);

  void setOrder(const std::vector<Direction> &c_order);
  void randomOrder(bool isRandomOrder);
  std::vector<Direction> result() const;
  uint64_t checkedStates() const;

  /**
   * @brief generates possible directions based on passed board and settings via
   * by setOrder and randomOrder functions
   */
  std::vector<Direction> generatePossibleDirections(const Board &c_board);

  /**
   * @brief starts searching loop
   * @return false if board is not solvable
   * @details derived classes should call this parent method to initialize varaibles
   */
  virtual bool initializeSearchLoop(const Board &c_initialBoard, const Heuristic::Type c_type = Heuristic::AllTaxicab);
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
};

#endif // SOLVER_H


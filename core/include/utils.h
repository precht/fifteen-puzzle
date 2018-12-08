#ifndef SOLVERUTILS_H
#define SOLVERUTILS_H

#include "board.h"
#include "solver.h"
#include <vector>

struct Utils
{
  static bool isSolvable(const Board &cBoard);
  static Board constructFinalBoard(const uint8_t cRows, const uint8_t cColumns);
  static void makeMovement(Board &board, Direction direction);
  static void reverseMovement(Board &board, Direction direction);
  static void printBoard(const Board &cBoard, std::ostream &output);
  static Solver* constructSolver(Solver::Algorithm algorithm);
};

#endif // SOLVERUTILS_H

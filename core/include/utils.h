#ifndef SOLVERUTILS_H
#define SOLVERUTILS_H

#include "board.h"
#include "solver.h"
#include <vector>

struct Utils
{
  static bool isSolvable(const Board &c_board);
  static Board constructFinalBoard(const uint8_t c_rows, const uint8_t c_columns);
  static void makeMovement(Board &r_board, Direction direction);
  static void reverseMovement(Board &r_board, Direction direction);
  static void printBoard(const Board &c_board, std::ostream &output);
  static Solver* constructSolver(Solver::Algorithm algorithm);
};

#endif // SOLVERUTILS_H

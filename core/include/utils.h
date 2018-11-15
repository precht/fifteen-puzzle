#ifndef SOLVERUTILS_H
#define SOLVERUTILS_H

#include <direction.h>

#include <cstdint>
#include <vector>

class Board;
struct Position;

struct Utils
{
  static bool isSolvable(const Board &cBoard);
  static Position getZeroPosition(const Board &cBoard);
  static Board constructFinalBoard(const uint8_t cRows, const uint8_t cColumns);
  static std::vector<Direction> generatePossibleDirections(const Board &cBoard);
  static void makeMovement(Board &board, Direction direction);
  static void reverseMovement(Board &board, Direction direction);
  static void printBoard(const Board &cBoard, std::ostream &output);
};

#endif // SOLVERUTILS_H

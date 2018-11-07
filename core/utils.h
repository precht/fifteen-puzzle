#ifndef SOLVERUTILS_H
#define SOLVERUTILS_H

#include <direction.h>

#include <cstdint>
#include <vector>

class Board;
struct State;
struct Position;

struct Utils
{
  static bool isSolvable(const Board &cBoard);
  static Position getZeroPosition(const Board &cBoard);
  static Board constructFinalBoard(const uint8_t cRows, const uint8_t cColumns);
  static std::vector<Direction> generatePossibleDirections(const Board &cBoard);
  static void makeMovement(State &movement);
  static void reverseMovement(State &movement);
  static void printBoard(const Board &cBoard, std::ostream &output);
};

#endif // SOLVERUTILS_H

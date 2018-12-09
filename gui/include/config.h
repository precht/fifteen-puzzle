#ifndef CONFIG_H
#define CONFIG_H

#include "solver.h"

struct Config {
  Board board;
  Solver::Algorithm algorithm;
  Heuristic::Type heuristic;
  std::vector<Direction> order;
  bool isRandomOrder = false;
  int requestId = 0;
};

#endif // CONFIG_H

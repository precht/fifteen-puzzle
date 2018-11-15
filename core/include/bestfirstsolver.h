#ifndef BESTFIRSTSOLVER_H
#define BESTFIRSTSOLVER_H

#include "solver.h"
#include "heuristic.h"
#include <queue>

class BestFirstSolver : public Solver
{
  std::priority_queue<State, std::vector<State>, StateTotalCostGreater> mPriorityQueue;
  Heuristic mHeuristic;

private:
  bool solve();
};

#endif // BESTFIRSTSOLVER_H

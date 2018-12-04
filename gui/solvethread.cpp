#include "solvethread.h"

SolveThread::SolveThread(const Board &board, QSharedPointer<Solver> &p_solver, Heuristic::Type heuristic, QObject *parent)
  : QThread(parent), m_board(board), mp_solver(p_solver), m_heuristic(heuristic)
{
  startTimer(0);
}

void SolveThread::run()
{
  bool isSolved = mp_solver->solve(m_board, m_heuristic);
  emit solved(isSolved);
}

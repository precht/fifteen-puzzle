#ifndef SOLVEWORKER_H
#define SOLVEWORKER_H

#include "solver.h"
#include <QSharedPointer>
#include <QThread>

class SolveThread : public QThread
{
  Q_OBJECT
  Board m_board;
  QSharedPointer<Solver> mp_solver;
  Heuristic::Type m_heuristic;

public:
  SolveThread(const Board &board, QSharedPointer<Solver> &p_solver, Heuristic::Type heuristic, QObject *parent = 0);

public slots:
  void run() override;

signals:
  void solved(bool isSolved);
};

#endif // SOLVEWORKER_H

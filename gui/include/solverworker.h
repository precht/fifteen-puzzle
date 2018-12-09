#ifndef SOLVERWORKER_H
#define SOLVERWORKER_H

#include "solver.h"
#include "config.h"
#include "answear.h"
#include <QObject>

struct Config;

class SolverWorker : public QObject
{
  Q_OBJECT
  Config m_config;
  Answear *mp_answear;

public:
  SolverWorker(const Config &c_config, Answear *p_answear);

public slots:
  void solve();

signals:
  void solved();
  void finished();

private:
  void finishSolving(Solver *p_solver);
};

#endif // SOLVERWORKER_H

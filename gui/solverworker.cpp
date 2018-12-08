#include "solverworker.h"
#include "utils.h"
#include <sstream>
#include <QThread>

SolverWorker::SolverWorker(const Config &config, Answear *p_answear)
  : m_config(config), mp_answear(p_answear)
{ }

void SolverWorker::solve()
{
  Solver *p_solver = Utils::constructSolver(m_config.algorithm);
  p_solver->setOrder(m_config.order);
  p_solver->randomOrder(m_config.isRandomOrder);

  mp_answear->isSolvable = p_solver->initializeSearchLoop(m_config.board, m_config.heuristic);
  if (!mp_answear->isSolvable) {
    mp_answear->result = "Board is not solvable.";
    return finishSolving(p_solver);
  }

  mp_answear->isSolved  = false;
  while (!mp_answear->isSolved && p_solver->isLoopEmpty() == false) {
    if (QThread::currentThread()->isInterruptionRequested()) {
      mp_answear->wasInterrupted = true;
      return finishSolving(p_solver);
    }
    mp_answear->isSolved |= p_solver->processNextState();
    QThread::currentThread()->yieldCurrentThread();
  }

  if (mp_answear->isSolved) {
    std::stringstream sstream;
    for (auto &d : p_solver->result())
      sstream << d;
    mp_answear->result = QString::fromStdString(sstream.str());
    if (p_solver->result().size() == 0)
      mp_answear->result = "Board is already solved.";
    mp_answear->checkStates = p_solver->checkedStates();
  }

  if (mp_answear->result.size() == 0)
    mp_answear->result = "Failed to solve board.";

  return finishSolving(p_solver);
}

void SolverWorker::finishSolving(Solver *p_solver)
{
  emit solved();
  delete p_solver;
//  QThread::currentThread()->quit();
}

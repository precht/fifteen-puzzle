#include "boardmodel.h"
#include "config.h"
#include "solverworker.h"
#include "core.h"
#include <sstream>
#include <QThread>

BoardModel::BoardModel(QObject *parent)
  : QObject (parent)
{ }

BoardModel::~BoardModel()
{
  // they will be deleted automatically because of delateLater slot
//  if (m_worker != nullptr)
//    delete m_worker;
//  if (m_thread != nullptr)
//    delete m_thread;
}

bool BoardModel::resetBoard(int rows, int columns)
{
  if (rows < 1 || rows > 4 || columns < 1 || columns > 4)
    return false;
  m_board = Utils::constructFinalBoard(rows, columns);
  return true;
}

int BoardModel::valueAt(int row, int column) const
{
  if (row < 0 || row > m_board.rows() || column < 0 || column > m_board.columns())
    return -1;
  return m_board.valueAt(row, column);
}

void BoardModel::setValueAt(int row, int column, int value)
{
  if (row < 0 || row > m_board.rows() || column < 0 || column > m_board.columns())
    return;
  m_board.setValueAt(row, column, value);
}

int BoardModel::solve(QString algorithmText, QString orderText, int heuristicIndex)
{
  if (!Utils::isSolvable(m_board)) {
    m_answear.result = "Board is not solvable.";
    return false;
  }
  
  if (m_board == Utils::constructFinalBoard(m_board.rows(), m_board.columns())) {
    m_answear.result = "Board is already solved.";
    return false;
  }
  
  Config config;
  config.board = m_board;
  
  bool isError = false;
  if (algorithmText == "BFS")
    config.algorithm = Solver::Bfs;
  else if (algorithmText == "DFS")
    config.algorithm = Solver::Dfs;
  else if (algorithmText == "IDFS")
    config.algorithm = Solver::Idfs;
  else if (algorithmText == "Best-First")
    config.algorithm = Solver::BestFirst;
  else if (algorithmText == "A*")
    config.algorithm = Solver::AStar;
  else if (algorithmText == "SMA*")
    config.algorithm = Solver::SmaStar;
  else
    isError = true;
  
  if (orderText == "RAND") {
    config.isRandomOrder = true;
  } else {
    for (auto &x : orderText) {
      if (x == 'L')
        config.order.push_back(Direction::Left);
      else if (x == 'R')
        config.order.push_back(Direction::Right);
      else if (x == 'U')
        config.order.push_back(Direction::Up);
      else if (x == 'D')
        config.order.push_back(Direction::Down);
      else
        isError = true;
    }
  }
  
  if (heuristicIndex == 0)
    config.heuristic = Heuristic::AllTaxicab;
  else if (heuristicIndex == 1)
    config.heuristic = Heuristic::ZeroTaxicab;
  else if (heuristicIndex == 2)
    config.heuristic = Heuristic::WrongCount;
  else
    isError = true;
  
  if (isError) {
    m_answear.result = "Error";
    return false;
  }

  // they will be deleted automatically because of delateLater slot
//  if (m_thread != nullptr) {
//    m_thread->requestInterruption();
//    delete m_thread;
//  }
//  if (m_worker != nullptr)
//    delete m_worker;

  m_answear = {};
  mp_worker = new SolverWorker(config, &m_answear);
  mp_thread = new QThread();

  mp_worker->moveToThread(mp_thread);
  connect(mp_thread, SIGNAL(started()), mp_worker, SLOT(solve()));
  connect(mp_worker, SIGNAL(solved()), this, SLOT(handleSolved()));
  connect(mp_worker, SIGNAL(solved()), mp_worker, SLOT(deleteLater()));
  connect(mp_worker, SIGNAL(solved()), mp_thread, SLOT(quit()));
  connect(mp_thread, SIGNAL(finished()), mp_thread, SLOT(deleteLater()));
  mp_thread->start();
  
  return true;
}

void BoardModel::handleSolved()
{
  emit solved(m_answear.isSolved);
}

QString BoardModel::resultText() const
{
  return m_answear.result;
}

int BoardModel::checkedStates() const
{
  return m_answear.checkStates;
}

int BoardModel::resultLength() const
{
  return m_answear.result.size();
}

void BoardModel::cancelSolving()
{
  mp_thread->requestInterruption();
}

bool BoardModel::wasInterrupted() const
{
  return m_answear.wasInterrupted;
}




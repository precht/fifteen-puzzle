#include "boardmodel.h"
#include "core.h"
#include <sstream>
#include <memory>
#include <QScopedPointer>
#include "solvethread.h"

BoardModel::BoardModel(QObject *parent)
  : QObject (parent)
{ }

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

bool BoardModel::solve(QString algorithmText, QString orderText, int heuristicIndex)
{
  if (!Utils::isSolvable(m_board)) {
    m_result = "Board is not solvable.";
    return false;
  }

  if (m_board == Utils::constructFinalBoard(m_board.rows(), m_board.columns())) {
    m_result = "Board is already solved.";
    return false;
  }

  bool isError = false;
  if (algorithmText == "BFS")
    mp_solver = QSharedPointer<Solver>(new BfsSolver());
  else if (algorithmText == "DFS")
    mp_solver = QSharedPointer<Solver>(new DfsSolver());
  else if (algorithmText == "IDFS")
    mp_solver = QSharedPointer<Solver>(new IdfsSolver());
  else if (algorithmText == "Best-First")
    mp_solver = QSharedPointer<Solver>(new BestFirstSolver());
  else if (algorithmText == "A*")
    mp_solver = QSharedPointer<Solver>(new AStarSolver());
  else if (algorithmText == "SMA*")
    mp_solver = QSharedPointer<Solver>(new SmaStarSolver());
  else
    isError = true;

  if (orderText == "RAND") {
    mp_solver->randomOrder(true);
  } else {
    std::vector<Direction> order;
    for (auto &x : orderText) {
      if (x == 'L')
        order.push_back(Direction::Left);
      else if (x == 'R')
        order.push_back(Direction::Right);
      else if (x == 'U')
        order.push_back(Direction::Up);
      else if (x == 'D')
        order.push_back(Direction::Down);
      else
        isError = true;
    }
    mp_solver->setOrder(order);
  }

  Heuristic::Type heuristic;
  if (heuristicIndex == 0)
    heuristic = Heuristic::AllTaxicab;
  else if (heuristicIndex == 1)
    heuristic = Heuristic::ZeroTaxicab;
  else if (heuristicIndex == 2)
    heuristic = Heuristic::WrongCount;
  else
    isError = true;

  if (isError) {
    m_result = "Error";
    return false;
  }

  mp_solveThread = new SolveThread(m_board, mp_solver, heuristic);
  connect(mp_solveThread, &SolveThread::solved, this, &BoardModel::handleSolved);
  connect(mp_solveThread, &SolveThread::finished, mp_solveThread, &QObject::deleteLater);
  mp_solveThread->start();

  return true;
}

void BoardModel::handleSolved(bool isSolved)
{
  if (isSolved) {
    std::stringstream sstream;
    for (auto &d : mp_solver->result())
      sstream << d;
    m_result = QString::fromStdString(sstream.str());
    emit solved(true);
    return;
  }

  m_result = "Failed to solve board.";
  emit solved(false);
}

QString BoardModel::resultText() const
{
  return m_result;
}

int BoardModel::checkedStates() const
{
  return mp_solver->checkedStates();
}

int BoardModel::resultLength() const
{
  return mp_solver->result().size();
}

void BoardModel::cancelSolving()
{
  mp_solveThread->terminate();
  mp_solveThread->wait();
}


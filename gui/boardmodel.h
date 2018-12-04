#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include "board.h"
#include "solver.h"
#include "solvethread.h"
#include <memory>
#include <QSharedPointer>
#include <QObject>

class BoardModel : public QObject
{
  Q_OBJECT
  Board m_board;
  QString m_result = "";
  QSharedPointer<Solver> mp_solver;
  SolveThread *mp_solveThread;

public:
  explicit BoardModel(QObject *parent = 0);

public slots:
  bool resetBoard(int rows, int columns);
  int valueAt(int row, int column) const;
  void setValueAt(int row, int column, int value);
  bool solve(QString algorithmText, QString orderText, int heuristicIndex);
  QString resultText() const;
  int checkedStates() const;
  int resultLength() const;
  void cancelSolving();

private slots:
  void handleSolved(bool isSolved);

signals:
  void solved(bool isSolved);
};

#endif // BOARDMODEL_H

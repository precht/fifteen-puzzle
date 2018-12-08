#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include "board.h"
#include "solver.h"
#include "solverworker.h"
#include "answear.h"
#include <QObject>

class BoardModel : public QObject
{
  Q_OBJECT
  Board m_board;
  Answear m_answear;
  QThread *m_thread = nullptr;
  SolverWorker *m_worker = nullptr;

public:
  explicit BoardModel(QObject *parent = 0);
  ~BoardModel();

public slots:
  bool resetBoard(int rows, int columns);
  int valueAt(int row, int column) const;
  void setValueAt(int row, int column, int value);
  int solve(QString algorithmText, QString orderText, int heuristicIndex);
  QString resultText() const;
  int checkedStates() const;
  int resultLength() const;
  void cancelSolving();
  bool wasInterrupted() const;

private slots:
  void handleSolved();

signals:
  void solved(bool isSolved);
};

#endif // BOARDMODEL_H

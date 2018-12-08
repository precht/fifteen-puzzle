#ifndef ANSWEAR_H
#define ANSWEAR_H
#include <QString>

struct Answear {
  QString result = "";
  bool isSolvable = false;
  bool isSolved = false;
  int checkStates = 0;
  bool wasInterrupted = false;
};

#endif // ANSWEAR_H

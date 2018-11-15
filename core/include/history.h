#ifndef HISTORY_H
#define HISTORY_H

#include "state.h"
#include <unordered_set>

class History
{
  std::unordered_set<State, StateBoardHash, StateBoardEqual> mVisited;

public:
  bool insert(const State &cState);
  bool find(const State &cState) const;
  State getFirstInserted(const State &cState) const;
  size_t size() const;
  void clear();
};

#endif // HISTORY_H

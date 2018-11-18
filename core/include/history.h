#ifndef HISTORY_H
#define HISTORY_H

#include "state.h"
#include <unordered_set>


// TODO remove history and replace with std::unordered_set
class History
{
  std::unordered_set<State, State::Hash, State::Equal> mVisited;

public:
  bool insert(const State &cState);
  bool find(const State &cState) const;
  void erase(const State &cState);
  State getFirstInserted(const State &cState) const;
  size_t size() const;
  void clear();
};

#endif // HISTORY_H

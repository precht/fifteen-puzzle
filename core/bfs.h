#ifndef BFS_H
#define BFS_H

#include "searchstrategycontainer.h"

#include <queue>

class Bfs : public SearchStrategyContainer
{
  std::queue<State> mQueue;

public:
  void push(const State &cState);
  State next() const;
  void pop();
  void clear();
  bool isEmpty() const;
  std::size_t size() const;
};

#endif // BFS_H

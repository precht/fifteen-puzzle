#ifndef DFS_H
#define DFS_H

#include "searchstrategycontainer.h"

#include <stack>

class Dfs : public SearchStrategyContainer
{
  std::stack<State> mStack;
public:
  void push(const State &cState);
  State next() const;
  void pop();
  std::size_t size() const;
  bool isEmpty() const;
  void clear();
};

#endif // DFS_H

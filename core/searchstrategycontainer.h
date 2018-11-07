#ifndef SEARCHSTRATEGY_H
#define SEARCHSTRATEGY_H

#include "state.h"

class SearchStrategyContainer
{
public:
  virtual void push(const State &cState) = 0;
  virtual State next() const = 0;
  virtual void pop() = 0;
  virtual bool isEmpty() const = 0;
  virtual void clear() = 0;
  virtual std::size_t size() const = 0;
  virtual ~SearchStrategyContainer();
};

#endif // SEARCHSTRATEGY_H

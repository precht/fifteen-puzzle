#include "dfs.h"
#include "coreexception.h"

void Dfs::push(const State &cState)
{
  mStack.push(cState);
}

State Dfs::next() const
{
  if (mStack.empty())
    throw CoreException(__FILE__, __LINE__);
  return mStack.top();
}

void Dfs::pop()
{
  mStack.pop();
}

std::size_t Dfs::size() const
{
  return mStack.size();
}

bool Dfs::isEmpty() const
{
  return mStack.empty();
}

void Dfs::clear()
{
  mStack = {};
}

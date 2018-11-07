#include "bfs.h"
#include "coreexception.h"

void Bfs::push(const State &cState)
{
  mQueue.push(cState);
}

State Bfs::next() const
{
  if (mQueue.empty())
    throw CoreException(__FILE__, __LINE__);
  return mQueue.front();
}

void Bfs::pop()
{
  mQueue.pop();
}

bool Bfs::isEmpty() const
{
  return mQueue.empty();
}

std::size_t Bfs::size() const
{
  return mQueue.size();
}

void Bfs::clear()
{
  mQueue = {};
}

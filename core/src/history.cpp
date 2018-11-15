#include "history.h"
#include "coreexception.h"

bool History::insert(const State &cState)
{
  return  mVisited.insert(cState).second;
}

bool History::find(const State &cState) const
{
  return (mVisited.find(cState) != mVisited.end());
}

State History::getFirstInserted(const State &cState) const
{
  auto ptr = mVisited.find(cState);
  if (ptr == mVisited.end())
    throw CoreException(__FILE__, __LINE__);
  return *ptr;
}

size_t History::size() const
{
  return mVisited.size();
}

void History::clear()
{
  mVisited.clear();
}

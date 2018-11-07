#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

#include "dfs.h"
#include "bfs.h"
#include "coreexception.h"

#include <algorithm>

TEST(SearchStrategy, DFS_pushNextPop_shouldPass)
{
  Board a(1, 1);
  Dfs dfs;
  a.setValueAt(0, 0, 1);
  dfs.push({a, None});
  a.setValueAt(0, 0, 2);
  dfs.push({a, None});
  EXPECT_EQ(dfs.next().board.valueAt(0, 0), 2);
  dfs.pop();
  a.setValueAt(0, 0, 3);
  dfs.push({a, None});
  EXPECT_EQ(dfs.next().board.valueAt(0, 0), 3);
  dfs.pop();
  EXPECT_EQ(dfs.next().board.valueAt(0, 0), 1);
  dfs.pop();
}

TEST(SearchStrategy, DFS_isEmpty_shouldPass)
{
  Board a(1, 1);
  Dfs dfs;
  EXPECT_TRUE(dfs.isEmpty());
  dfs.push({a, None});
  dfs.pop();
  EXPECT_TRUE(dfs.isEmpty());
  dfs.push({a, None});
  dfs.clear();
  EXPECT_TRUE(dfs.isEmpty());
}

TEST(SearchStrategy, DFS_next_shouldThrow)
{
  Dfs dfs;
  EXPECT_THROW(dfs.next(), CoreException);
}

TEST(SearchStrategy, BFS_pushNextPop_shouldPass)
{
  Board a(1, 1);
  Bfs bfs;
  a.setValueAt(0, 0, 1);
  bfs.push({a, None});
  a.setValueAt(0, 0, 2);
  bfs.push({a, None});
  EXPECT_EQ(bfs.next().board.valueAt(0, 0), 1);
  bfs.pop();
  a.setValueAt(0, 0, 3);
  bfs.push({a, None});
  EXPECT_EQ(bfs.next().board.valueAt(0, 0), 2);
  bfs.pop();
  EXPECT_EQ(bfs.next().board.valueAt(0, 0), 3);
  bfs.pop();
}

TEST(SearchStrategy, BFS_isEmpty_shouldPass)
{
  Board a(1, 1);
  Bfs bfs;
  EXPECT_TRUE(bfs.isEmpty());
  bfs.push({a, None});
  bfs.pop();
  EXPECT_TRUE(bfs.isEmpty());
  bfs.push({a, None});
  bfs.clear();
  EXPECT_TRUE(bfs.isEmpty());
}

TEST(SearchStrategy, BFS_next_shouldThrow)
{
  Bfs bfs;
  EXPECT_THROW(bfs.next(), CoreException);
}

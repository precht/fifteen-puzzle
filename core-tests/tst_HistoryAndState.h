#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

#include "history.h"

TEST(HistoryAndState, createHistory_shouldCreate)
{
  State s;
  History h;
}

TEST(HistoryAndState, stateEquals_shouldPass)
{
  Board a;
  State s1(a, Left), s2(a, Right);
  EXPECT_EQ(s1, s2);
}


TEST(HistoryAndState, stateEquals_shouldFail)
{
  Board a(1, 1), b(1, 1);
  a.setValueAt(0, 0, 1);
  b.setValueAt(0, 0, 2);
  State s1(a, Left), s2(b, Right);
  EXPECT_NE(s1, s2);
}

TEST(HistoryAndState, insertDifferentBoards_shouldInsert)
{
  History h;
  Board a(4, 4), b(4, 4), c(4, 4);
  b.setValueAt(1, 2, 3);
  c.setValueAt(1, 2, 4);
  EXPECT_TRUE(h.insert({a, None}));
  EXPECT_TRUE(h.insert({b, None}));
  EXPECT_TRUE(h.insert({c, None}));
}

TEST(HistoryAndState, insertDifferentBoards_shouldFind)
{
  History h;
  Board a(4, 4), b(4, 4), c(4, 4);
  b.setValueAt(1, 2, 3);
  c.setValueAt(1, 2, 4);
  h.insert({a, None});
  h.insert({b, None});
  h.insert({c, None});
  EXPECT_TRUE(h.find({a, None}));
  EXPECT_TRUE(h.find({b, None}));
  EXPECT_TRUE(h.find({c, None}));
}

TEST(HistoryAndState, insertDupplicatesBoards_shouldNotInsert)
{
  History h;
  Board b;
  h.insert({b, None});
  EXPECT_FALSE(h.insert({b, None}));
}

TEST(HistoryAndState, insertSameBoardWithDifferentDirections_shouldNotInsert)
{
  History h;
  Board b;
  h.insert({b, None});
  EXPECT_FALSE(h.insert({b, Left}));
  EXPECT_FALSE(h.insert({b, Right}));
  EXPECT_FALSE(h.insert({b, Up}));
  EXPECT_FALSE(h.insert({b, Down}));
}

TEST(HistoryAndState, insertOneBoard_shouldFindWithDifferentDirections)
{
  History h;
  Board b;
  h.insert({b, None});
  EXPECT_TRUE(h.find({b, None}));
  EXPECT_TRUE(h.find({b, Left}));
  EXPECT_TRUE(h.find({b, Right}));
  EXPECT_TRUE(h.find({b, Up}));
  EXPECT_TRUE(h.find({b, Down}));
}

TEST(HistoryAndState, clear_shouldBeEmpty)
{
  History h;
  Board a(4, 4), b(4, 4), c(4, 4);
  b.setValueAt(1, 2, 3);
  c.setValueAt(1, 2, 4);
  h.insert({a, None});
  h.insert({b, None});
  h.insert({c, None});
  h.clear();
  EXPECT_EQ(h.size(), 0u);
  EXPECT_FALSE(h.find({a, None}));
  EXPECT_FALSE(h.find({b, None}));
  EXPECT_FALSE(h.find({c, None}));
}

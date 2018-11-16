#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

#include "history.h"
#include <queue>

TEST(HistoryAndState, createHistory_shouldCreate)
{
  State s;
  History h;
}

TEST(HistoryAndState, stateEquals_shouldPass)
{
  Board a;
  State s1(a, Direction::Left), s2(a, Direction::Right);
  State::Equal equal;
  EXPECT_TRUE(equal(s1, s2));
}

TEST(HistoryAndState, stateEquals_shouldFail)
{
  Board a(1, 1), b(1, 1);
  a.setValueAt(0, 0, 1);
  b.setValueAt(0, 0, 2);
  State s1(a, Direction::Left), s2(b, Direction::Right);
  State::Equal equal;
  EXPECT_FALSE(equal(s1, s2));
}

TEST(HistoryAndState, insertDifferentBoards_shouldInsert)
{
  History h;
  Board a(4, 4), b(4, 4), c(4, 4);
  b.setValueAt(1, 2, 3);
  c.setValueAt(1, 2, 4);
  EXPECT_TRUE(h.insert({a}));
  EXPECT_TRUE(h.insert({b}));
  EXPECT_TRUE(h.insert({c}));
}

TEST(HistoryAndState, insertDifferentBoards_shouldFind)
{
  History h;
  Board a(4, 4), b(4, 4), c(4, 4);
  b.setValueAt(1, 2, 3);
  c.setValueAt(1, 2, 4);
  h.insert({a});
  h.insert({b});
  h.insert({c});
  EXPECT_TRUE(h.find({a}));
  EXPECT_TRUE(h.find({b}));
  EXPECT_TRUE(h.find({c}));
}

TEST(HistoryAndState, insertDupplicatesBoards_shouldNotInsert)
{
  History h;
  Board b;
  h.insert({b});
  EXPECT_FALSE(h.insert({b}));
}

TEST(HistoryAndState, insertSameBoardWithDifferentDirections_shouldNotInsert)
{
  History h;
  Board b;
  h.insert({b});
  EXPECT_FALSE(h.insert({b, Direction::Left}));
  EXPECT_FALSE(h.insert({b, Direction::Right}));
  EXPECT_FALSE(h.insert({b, Direction::Up}));
  EXPECT_FALSE(h.insert({b, Direction::Down}));
}

TEST(HistoryAndState, insertOneBoard_shouldFindWithDifferentDirections)
{
  History h;
  Board b;
  h.insert({b});
  EXPECT_TRUE(h.find({b}));
  EXPECT_TRUE(h.find({b, Direction::Left}));
  EXPECT_TRUE(h.find({b, Direction::Right}));
  EXPECT_TRUE(h.find({b, Direction::Up}));
  EXPECT_TRUE(h.find({b, Direction::Down}));
}

TEST(HistoryAndState, clear_shouldBeEmpty)
{
  History h;
  Board a(4, 4), b(4, 4), c(4, 4);
  b.setValueAt(1, 2, 3);
  c.setValueAt(1, 2, 4);
  h.insert({a});
  h.insert({b});
  h.insert({c});
  h.clear();
  EXPECT_EQ(h.size(), 0u);
  EXPECT_FALSE(h.find({a}));
  EXPECT_FALSE(h.find({b}));
  EXPECT_FALSE(h.find({c}));
}

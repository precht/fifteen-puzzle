#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

#include "state.h"
#include <queue>
#include <unordered_set>

TEST(State, stateEquals_shouldPass)
{
  Board a;
  State s1(a, Direction::Left), s2(a, Direction::Right);
  State::Equal equal;
  EXPECT_TRUE(equal(s1, s2));
}

TEST(State, stateEquals_shouldFail)
{
  Board a(1, 1), b(1, 1);
  a.setValueAt(0, 0, 1);
  b.setValueAt(0, 0, 2);
  State s1(a, Direction::Left), s2(b, Direction::Right);
  State::Equal equal;
  EXPECT_FALSE(equal(s1, s2));
}

TEST(State, insertDifferentBoards_shouldInsert)
{
  std::unordered_set<State, State::Hash, State::Equal> h;
  Board a(4, 4), b(4, 4), c(4, 4);
  b.setValueAt(1, 2, 3);
  c.setValueAt(1, 2, 4);
  EXPECT_TRUE(h.insert(a).second);
  EXPECT_TRUE(h.insert(b).second);
  EXPECT_TRUE(h.insert(c).second);
}

TEST(State, insertDifferentBoards_shouldFind)
{
  std::unordered_set<State, State::Hash, State::Equal> h;
  Board a(4, 4), b(4, 4), c(4, 4);
  b.setValueAt(1, 2, 3);
  c.setValueAt(1, 2, 4);
  h.insert({a});
  h.insert({b});
  h.insert({c});
  EXPECT_NE(h.find(a), h.end());
  EXPECT_NE(h.find(b), h.end());
  EXPECT_NE(h.find(c), h.end());
}

TEST(State, insertDupplicatesBoards_shouldNotInsert)
{
  std::unordered_set<State, State::Hash, State::Equal> h;
  Board b;
  h.insert({b});
  EXPECT_FALSE(h.insert(b).second);
}

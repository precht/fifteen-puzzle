#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

#include "utils.h"
#include "board.h"
#include "state.h"
#include "coreexception.h"

#include <algorithm>

TEST(Utils, constructSquareFinalBoard_shouldBeCorrectlyFilled)
{
  Board a = Utils::constructFinalBoard(4, 4);
  for (uint8_t i = 0; i < 6; i++)
    EXPECT_EQ(a.valueAt(i / 4, i % 4), (i + 1) % 16);
}

TEST(Utils, constructRectangleFinalBoard_shouldBeCorrectlyFilled)
{
  Board a = Utils::constructFinalBoard(2, 3);
  for (uint8_t i = 0; i < 6; i++)
    EXPECT_EQ(a.valueAt(i / 3, i % 3), (i + 1) % 6);
}

TEST(Utils, isSolvable_shouldBeTrue)
{
  Board a = Utils::constructFinalBoard(2, 3);

  EXPECT_TRUE(Utils::isSolvable(a));
  Board b(3, 2);
  for (uint8_t i = 0; i < 6; i++)
    b.setValueAt(i / 2, i % 2, (i + 1) % 6);
  EXPECT_TRUE(Utils::isSolvable(b));

  b.setValueAt(2, 1, 5);
  b.setValueAt(2, 0, 0);
  EXPECT_TRUE(Utils::isSolvable(b));

  Board c(3, 3);
  c.setValueAt(0, 0, 1);
  c.setValueAt(0, 1, 8);
  c.setValueAt(0, 2, 2);

  c.setValueAt(1, 0, 0);
  c.setValueAt(1, 1, 4);
  c.setValueAt(1, 2, 3);

  c.setValueAt(2, 0, 7);
  c.setValueAt(2, 1, 6);
  c.setValueAt(2, 2, 5);

  EXPECT_TRUE(Utils::isSolvable(b));

}

TEST(Utils, isSolvable_shouldNotBeTrue)
{
  Board a, b(2, 3), c(4, 4), d(2, 2), e(2, 2), f(3, 3);
  for (uint8_t i = 0; i < 16; i++)
    c.setValueAt(i / 4, i % 4, 8);
  for (uint8_t i = 0; i < 4; i++) {
    d.setValueAt(i / 2, i % 2, (i + 4) % 7);
    e.setValueAt(i / 2, i % 2, (i + 1) % 4);
  }
  e.setValueAt(0, 0, 2);
  e.setValueAt(0, 1, 1);
  for (uint8_t i = 0; i < 9; i++)
    f.setValueAt(i / 3, i % 3, (i+1) % 9);
  f.setValueAt(0, 0, 2);
  f.setValueAt(0, 1, 1);
  EXPECT_FALSE(Utils::isSolvable(a));
  EXPECT_FALSE(Utils::isSolvable(b));
  EXPECT_FALSE(Utils::isSolvable(c));
  EXPECT_FALSE(Utils::isSolvable(d));
  EXPECT_FALSE(Utils::isSolvable(e));
  EXPECT_FALSE(Utils::isSolvable(f));

  Board g(4, 4);
  g.setValueAt(0, 0, 3);
  g.setValueAt(0, 1, 9);
  g.setValueAt(0, 2, 1);
  g.setValueAt(0, 3, 15);

  g.setValueAt(1, 0, 14);
  g.setValueAt(1, 1, 11);
  g.setValueAt(1, 2, 4);
  g.setValueAt(1, 3, 6);

  g.setValueAt(2, 0, 13);
  g.setValueAt(2, 1, 0);
  g.setValueAt(2, 2, 10);
  g.setValueAt(2, 3, 12);

  g.setValueAt(3, 0, 2);
  g.setValueAt(3, 1, 7);
  g.setValueAt(3, 2, 8);
  g.setValueAt(3, 3, 5);

  EXPECT_FALSE(Utils::isSolvable(g));
}

TEST(Utils, getZeroPosition_shouldPass)
{
  Board a(2, 2);
  a.setValueAt(0, 0, 3);
  a.setValueAt(0, 1, 0);
  a.setValueAt(1, 0, 1);
  a.setValueAt(1, 1, 2);
  EXPECT_EQ(Utils::getZeroPosition(a).row, 0);
  EXPECT_EQ(Utils::getZeroPosition(a).column, 1);
}

TEST(Utils, getZeroPosition_shouldFail)
{
  Board a(2, 2);
  EXPECT_THROW(Utils::getZeroPosition(a), CoreException);
  a.setValueAt(0, 0, 3);
  a.setValueAt(0, 1, 3);
  a.setValueAt(1, 0, 3);
  a.setValueAt(1, 1, 3);
  EXPECT_THROW(Utils::getZeroPosition(a), CoreException);
}

TEST(Utils, generatePossibleDirection_zeroIsInCerter)
{
  Board a(3, 3);
  a.setValueAt(0, 0, 1);
  a.setValueAt(0, 1, 2);
  a.setValueAt(0, 2, 3);
  a.setValueAt(1, 0, 4);
  a.setValueAt(1, 1, 0);
  a.setValueAt(1, 2, 5);
  a.setValueAt(2, 0, 6);
  a.setValueAt(2, 1, 7);
  a.setValueAt(2, 2, 8);
  auto d = Utils::generatePossibleDirections(a);
  EXPECT_EQ(d.size(), 4u);
  EXPECT_TRUE(std::find(d.begin(), d.end(), Left) != d.end());
  EXPECT_TRUE(std::find(d.begin(), d.end(), Right) != d.end());
  EXPECT_TRUE(std::find(d.begin(), d.end(), Up) != d.end());
  EXPECT_TRUE(std::find(d.begin(), d.end(), Down) != d.end());
}

TEST(Utils, generatePossibleDirectoin_zeroIsInUpLeftCorner)
{
  Board a(2, 2);
  a.setValueAt(0, 0, 0);
  a.setValueAt(0, 1, 1);
  a.setValueAt(1, 0, 2);
  a.setValueAt(1, 1, 3);
  auto d = Utils::generatePossibleDirections(a);
  EXPECT_EQ(d.size(), 2u);
  EXPECT_TRUE(std::find(d.begin(), d.end(), Up) != d.end());
  EXPECT_TRUE(std::find(d.begin(), d.end(), Left) != d.end());
}

TEST(Utils, generatePossibleDirectoin_zeroIsInDownRightCorner)
{
  Board a(2, 2);
  a.setValueAt(0, 0, 3);
  a.setValueAt(0, 1, 1);
  a.setValueAt(1, 0, 2);
  a.setValueAt(1, 1, 0);
  auto d = Utils::generatePossibleDirections(a);
  EXPECT_EQ(d.size(), 2u);
  EXPECT_TRUE(std::find(d.begin(), d.end(), Down) != d.end());
  EXPECT_TRUE(std::find(d.begin(), d.end(), Right) != d.end());
}

TEST(Utils, makeMovement_shouldMake)
{
  Board a(2, 2);
  a.setValueAt(0, 0, 0);
  a.setValueAt(0, 1, 1);
  a.setValueAt(1, 0, 2);
  a.setValueAt(1, 1, 3);

  State s(a, Left);
  Utils::makeMovement(s);
  a.setValueAt(0, 0, 1);
  a.setValueAt(0, 1, 0);
  EXPECT_EQ(s.board, a);

  s.direction = Up;
  Utils::makeMovement(s);
  a.setValueAt(0, 1, 3);
  a.setValueAt(1, 1, 0);
  EXPECT_EQ(s.board, a);

  s.direction = Right;
  Utils::makeMovement(s);
  a.setValueAt(1, 1, 2);
  a.setValueAt(1, 0, 0);
  EXPECT_EQ(s.board, a);

  s.direction = Down;
  Utils::makeMovement(s);
  a.setValueAt(0, 0, 0);
  a.setValueAt(1, 0, 1);
  EXPECT_EQ(s.board, a);
}

TEST(Utils, makeMovement9Puzzle)
{
  Board board(3, 3);
  board.setValueAt(0, 0, 1);
  board.setValueAt(0, 1, 2);
  board.setValueAt(0, 2, 3);

  board.setValueAt(1, 0, 4);
  board.setValueAt(1, 1, 0);
  board.setValueAt(1, 2, 5);

  board.setValueAt(2, 0, 7);
  board.setValueAt(2, 1, 8);
  board.setValueAt(2, 2, 6);

  State s(board, Right);
  Board expect = board;
  expect.setValueAt(1, 1, 4);
  expect.setValueAt(1, 0, 0);
  Utils::makeMovement(s);
  EXPECT_EQ(s.board, expect);

  s = {board, Left};
  expect = board;
  expect.setValueAt(1, 1, 5);
  expect.setValueAt(1, 2, 0);
  Utils::makeMovement(s);
  EXPECT_EQ(s.board, expect);

  s = {board, Up};
  expect = board;
  expect.setValueAt(1, 1, 8);
  expect.setValueAt(2, 1, 0);
  Utils::makeMovement(s);
  EXPECT_EQ(s.board, expect);

  s = {board, Down};
  expect = board;
  expect.setValueAt(1, 1, 2);
  expect.setValueAt(0, 1, 0);
  Utils::makeMovement(s);
  EXPECT_EQ(s.board, expect);
}


TEST(Utils, makeMovement_shouldThrow)
{
  Board a(2, 2);
  a.setValueAt(0, 0, 0);
  a.setValueAt(0, 1, 1);
  a.setValueAt(1, 0, 2);
  a.setValueAt(1, 1, 3);
  State s = {a, Right};
  EXPECT_THROW(Utils::makeMovement(s), CoreException);
  s = {a, Down};
  EXPECT_THROW(Utils::makeMovement(s), CoreException);
  a.setValueAt(0, 0, 3);
  a.setValueAt(0, 1, 1);
  a.setValueAt(1, 0, 2);
  a.setValueAt(1, 1, 0);
  s = {a, Left};
  EXPECT_THROW(Utils::makeMovement(s), CoreException);
  s = {a, Up};
  EXPECT_THROW(Utils::makeMovement(s), CoreException);
}

TEST(Utils, reverseMovement_shouldMake)
{
  Board a(2, 2);
  a.setValueAt(0, 0, 0);
  a.setValueAt(0, 1, 1);
  a.setValueAt(1, 0, 2);
  a.setValueAt(1, 1, 3);

  State s(a, Right);
  Utils::reverseMovement(s);
  a.setValueAt(0, 0, 1);
  a.setValueAt(0, 1, 0);
  EXPECT_EQ(s.board, a);

  s.direction = Down;
  Utils::reverseMovement(s);
  a.setValueAt(0, 1, 3);
  a.setValueAt(1, 1, 0);
  EXPECT_EQ(s.board, a);

  s.direction = Left;
  Utils::reverseMovement(s);
  a.setValueAt(1, 1, 2);
  a.setValueAt(1, 0, 0);
  EXPECT_EQ(s.board, a);

  s.direction = Up;
  Utils::reverseMovement(s);
  a.setValueAt(0, 0, 0);
  a.setValueAt(1, 0, 1);
  EXPECT_EQ(s.board, a);
}

TEST(Utils, reverseMovement_shouldThrow)
{
  Board a(2, 2);
  a.setValueAt(0, 0, 0);
  a.setValueAt(0, 1, 1);
  a.setValueAt(1, 0, 2);
  a.setValueAt(1, 1, 3);
  State s = {a, Left};
  EXPECT_THROW(Utils::reverseMovement(s), CoreException);
  s = {a, Up};
  EXPECT_THROW(Utils::reverseMovement(s), CoreException);
  a.setValueAt(0, 0, 3);
  a.setValueAt(0, 1, 1);
  a.setValueAt(1, 0, 2);
  a.setValueAt(1, 1, 0);
  s = {a, Right};
  EXPECT_THROW(Utils::reverseMovement(s), CoreException);
  s = {a, Down};
  EXPECT_THROW(Utils::reverseMovement(s), CoreException);
}

TEST(Utils, reverseMovement9Puzzle)
{
  Board board(3, 3);
  board.setValueAt(0, 0, 1);
  board.setValueAt(0, 1, 2);
  board.setValueAt(0, 2, 3);

  board.setValueAt(1, 0, 4);
  board.setValueAt(1, 1, 0);
  board.setValueAt(1, 2, 5);

  board.setValueAt(2, 0, 7);
  board.setValueAt(2, 1, 8);
  board.setValueAt(2, 2, 6);

  State s(board, Right);
  Utils::makeMovement(s);
  Utils::reverseMovement(s);
  EXPECT_EQ(s.board, board);

  s = {board, Right};
  Utils::makeMovement(s);
  Utils::reverseMovement(s);
  EXPECT_EQ(s.board, board);

  s = {board, Right};
  Utils::makeMovement(s);
  Utils::reverseMovement(s);
  EXPECT_EQ(s.board, board);

  s = {board, Right};
  Utils::makeMovement(s);
  Utils::reverseMovement(s);
  EXPECT_EQ(s.board, board);
}

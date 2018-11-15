#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

#include "board.h"
#include "coreexception.h"

TEST(Board, createBoard_shouldCreate)
{
  Board a, b(2, 3), c(4, 4);
}

TEST(Board, equals_shouldBeEqual)
{
  Board a, b(1, 1), c(1, 1);
  b.setValueAt(0, 0, 1);
  c.setValueAt(0, 0, 1);
  EXPECT_EQ(a, a);
  EXPECT_EQ(b, c);
}

TEST(Board, equals_shouldNotBeEqual)
{
  Board a, b(1, 1), c(1, 1);
  EXPECT_NE(a, b);
  b.setValueAt(0, 0, 1);
  c.setValueAt(0, 0, 2);
  EXPECT_NE(b, c);
}

TEST(Board, createRectangleBoard_shouldHaveCorrectSize)
{
  Board b(2, 3);
  EXPECT_EQ(b.rows(), 2);
  EXPECT_EQ(b.columns(), 3);
  EXPECT_EQ(b.size(), 6);
}

TEST(Board, createTooBigBoard_shouldThrowException)
{
  EXPECT_THROW(Board(5, 4), CoreException);
  EXPECT_THROW(Board(4, 5), CoreException);
}

TEST(Board, setValueAtPosition_shouldGetSameValueAtPosition)
{
  Board b(2, 3);
  for (uint8_t i = 0; i < 6; i++)
    b.setValueAt(i / 3, i % 3, i + 10);
  for (uint8_t i = 0; i < 6; i++)
    EXPECT_EQ(b.valueAt(i / 3, i % 3),  i + 10);
}

TEST(Board, compareBoardsAndHashes_shouldBeSame)
{
  Board a(4, 4), b(4, 4);
  EXPECT_EQ(a, b);
  EXPECT_EQ(a.memory(), b.memory());
  a.setValueAt(1, 2, 3);
  b.setValueAt(1, 2, 3);
  EXPECT_EQ(a, b);
  EXPECT_EQ(a.memory(), b.memory());
}

TEST(Board, compareBoardsAndHashes_shouldBeDifferent) {
  Board a(2, 3), b(4, 4), c(4, 4);
  EXPECT_NE(a, b);
  b.setValueAt(1, 2, 3);
  c.setValueAt(1, 2, 4);
  EXPECT_NE(b, c);
  EXPECT_NE(b.memory(), c.memory());
}

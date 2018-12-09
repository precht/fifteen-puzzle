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

TEST(Board, getPosition_shouldPass)
{
  Board a(2, 2);
  a.setValueAt(0, 0, 3);
  a.setValueAt(0, 1, 0);
  a.setValueAt(1, 0, 1);
  a.setValueAt(1, 1, 2);
  EXPECT_EQ(a.getPosition(0).row, 0);
  EXPECT_EQ(a.getPosition(0).column, 1);
}

TEST(Board, setValues_shouldPass)
{
  std::vector<uint8_t> values = { 0, 8, 7,
                                  6, 5, 4,
                                  3, 2, 1 };
  Board a(3, 3, values);
  for (uint8_t index = 0; index < 9; index++)
    EXPECT_EQ(a.valueAt(index / 3, index % 3), values[index]);

  a = Board(3, 3);
  a.setValues(values);
  for (uint8_t index = 0; index < 9; index++)
    EXPECT_EQ(a.valueAt(index / 3, index % 3), values[index]);

  values = { 0,  15, 14, 13,
             12, 11, 10, 9,
             8,  7,  6,  5,
             4,  3,  2,  1 };

  a = Board(4, 4, values);
  for (uint8_t index = 0; index < 16; index++)
    EXPECT_EQ(a.valueAt(index / 4, index % 4), values[index]);

  a = Board(4, 4);
  a.setValues(values);
  for (uint8_t index = 0; index < 16; index++)
    EXPECT_EQ(a.valueAt(index / 4, index % 4), values[index]);
}

#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

#include "board.h"
#include "utils.h"
#include "heuristic.h"

class HeuristicTest : public ::testing::Test
{
protected:
  Board board, expect;
  Heuristic h;

  void SetUp() override
  {
    board = Board(3, 3);
    board.setValueAt(0, 0, 1);
    board.setValueAt(0, 1, 0);
    board.setValueAt(0, 2, 3);

    board.setValueAt(1, 0, 4);
    board.setValueAt(1, 1, 2);
    board.setValueAt(1, 2, 6);

    board.setValueAt(2, 0, 7);
    board.setValueAt(2, 1, 5);
    board.setValueAt(2, 2, 8);

    expect = Utils::constructFinalBoard(3, 3);
  }
};

TEST_F(HeuristicTest, checkZeroTaxicab)
{
  EXPECT_EQ(h(board, expect, ZeroTaxicab), 3);
  EXPECT_EQ(Heuristic::zeroTaxicab(board, expect), 3);
}

TEST_F(HeuristicTest, checkAllTaxicab)
{
  EXPECT_EQ(h(board, expect, AllTaxicab), 6);
  EXPECT_EQ(Heuristic::allTaxicab(board, expect), 6);
}

TEST_F(HeuristicTest, checkWrongCount)
{
  EXPECT_EQ(h(board, expect, WrongCount), 4);
  EXPECT_EQ(Heuristic::wrongCount(board, expect), 4);
}

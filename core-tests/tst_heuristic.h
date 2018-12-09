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
    board = Board(3, 3, { 1, 0, 3,
                          4, 2, 6,
                          7, 5, 8 });
    expect = Utils::constructFinalBoard(3, 3);
  }
};

TEST_F(HeuristicTest, checkZeroTaxicab)
{
  EXPECT_EQ(h(board, expect, Heuristic::ZeroTaxicab), 3);
  EXPECT_EQ(Heuristic::zeroTaxicab(board, expect), 3);
}

TEST_F(HeuristicTest, checkAllTaxicab)
{
  EXPECT_EQ(h(board, expect, Heuristic::AllTaxicab), 3);
  EXPECT_EQ(Heuristic::allTaxicab(board, expect), 3);
}

TEST_F(HeuristicTest, checkWrongCount)
{
  EXPECT_EQ(h(board, expect, Heuristic::WrongCount), 4);
  EXPECT_EQ(Heuristic::wrongCount(board, expect), 4);
}

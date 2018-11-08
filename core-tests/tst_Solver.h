#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

#include "dfs.h"
#include "bfs.h"
#include "solver.h"
#include "utils.h"

TEST(Solver, check1)
{
  Board board(3, 3);
  board.setValueAt(0, 0, 0);
  board.setValueAt(0, 1, 1);
  board.setValueAt(0, 2, 3);

  board.setValueAt(1, 0, 4);
  board.setValueAt(1, 1, 2);
  board.setValueAt(1, 2, 5);

  board.setValueAt(2, 0, 7);
  board.setValueAt(2, 1, 8);
  board.setValueAt(2, 2, 6);

  {
    Solver solver(board);
    Bfs bfs;
    ASSERT_TRUE(solver.solve(&bfs));
    State state = {board, None};
    for (auto &d : solver.result()) {
      state.direction = d;
      Utils::makeMovement(state);
    }
    EXPECT_EQ(state.board, Utils::constructFinalBoard(3, 3));
  }
  {
    Solver solver(board);
    Dfs dfs;
    ASSERT_TRUE(solver.solve(&dfs));
    State state = {board, None};
    for (auto &d : solver.result()) {
      state.direction = d;
      Utils::makeMovement(state);
    }
    EXPECT_EQ(state.board, Utils::constructFinalBoard(3, 3));
  }
}

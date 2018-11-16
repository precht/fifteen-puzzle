#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

#include "core.h"
#include <iostream>

class Solvers : public ::testing::Test
{
protected:
  Board b1, b2, b3, b4, board;
  Solver *solver;

  void SetUp() override
  {
    b1 = Board(3, 3);
    b1.setValueAt(0, 0, 7);
    b1.setValueAt(0, 1, 4);
    b1.setValueAt(0, 2, 3);

    b1.setValueAt(1, 0, 8);
    b1.setValueAt(1, 1, 0);
    b1.setValueAt(1, 2, 5);

    b1.setValueAt(2, 0, 2);
    b1.setValueAt(2, 1, 1);
    b1.setValueAt(2, 2, 6);

    b2 = Board(4, 4);
    b2.setValueAt(0, 0, 5);
    b2.setValueAt(0, 1, 1);
    b2.setValueAt(0, 2, 2);
    b2.setValueAt(0, 3, 3);

    b2.setValueAt(1, 0, 9);
    b2.setValueAt(1, 1, 10);
    b2.setValueAt(1, 2, 6);
    b2.setValueAt(1, 3, 4);

    b2.setValueAt(2, 0, 13);
    b2.setValueAt(2, 1, 0);
    b2.setValueAt(2, 2, 7);
    b2.setValueAt(2, 3, 8);

    b2.setValueAt(3, 0, 14);
    b2.setValueAt(3, 1, 15);
    b2.setValueAt(3, 2, 11);
    b2.setValueAt(3, 3, 12);

    b3 = Board(4, 4);
    b3.setValueAt(0, 0, 0);
    b3.setValueAt(0, 1, 1);
    b3.setValueAt(0, 2, 3);
    b3.setValueAt(0, 3, 4);

    b3.setValueAt(1, 0, 5);
    b3.setValueAt(1, 1, 2);
    b3.setValueAt(1, 2, 6);
    b3.setValueAt(1, 3, 8);

    b3.setValueAt(2, 0, 9);
    b3.setValueAt(2, 1, 10);
    b3.setValueAt(2, 2, 7);
    b3.setValueAt(2, 3, 11);

    b3.setValueAt(3, 0, 13);
    b3.setValueAt(3, 1, 14);
    b3.setValueAt(3, 2, 15);
    b3.setValueAt(3, 3, 12);

    b4 = Board(4, 4);
    b4.setValueAt(0, 0, 1);
    b4.setValueAt(0, 1, 2);
    b4.setValueAt(0, 2, 3);
    b4.setValueAt(0, 3, 4);

    b4.setValueAt(1, 0, 5);
    b4.setValueAt(1, 1, 6);
    b4.setValueAt(1, 2, 7);
    b4.setValueAt(1, 3, 8);

    b4.setValueAt(2, 0, 9);
    b4.setValueAt(2, 1, 0);
    b4.setValueAt(2, 2, 11);
    b4.setValueAt(2, 3, 12);

    b4.setValueAt(3, 0, 13);
    b4.setValueAt(3, 1, 10);
    b4.setValueAt(3, 2, 14);
    b4.setValueAt(3, 3, 15);

//    b4 = Board(4, 4);
//    b4.setValueAt(0, 0, );
//    b4.setValueAt(0, 1, );
//    b4.setValueAt(0, 2, );
//    b4.setValueAt(0, 3, );

//    b4.setValueAt(1, 0, );
//    b4.setValueAt(1, 1, );
//    b4.setValueAt(1, 2, );
//    b4.setValueAt(1, 3, );

//    b4.setValueAt(2, 0, );
//    b4.setValueAt(2, 1, );
//    b4.setValueAt(2, 2, );
//    b4.setValueAt(2, 3, );

//    b4.setValueAt(3, 0, );
//    b4.setValueAt(3, 1, );
//    b4.setValueAt(3, 2, );
//    b4.setValueAt(3, 3, );
  }

  void check()
  {
    ASSERT_TRUE(solver->solve(board));
    for (auto &d : solver->result())
      Utils::makeMovement(board, d);
    EXPECT_EQ(board, Utils::constructFinalBoard(board.rows(), board.columns()));
    std::cout << "checkedStates: " << solver->checkedStates() << "\n";
  }
};

TEST_F(Solvers, checkBfs_board3x3)
{
  board = b1;
  BfsSolver s;
  solver = &s;
  check();
}

TEST_F(Solvers, checkBfs_board4x4)
{
  board = b2;
  BfsSolver s;
  solver = &s;
  check();
}

TEST_F(Solvers, checkDfs_board3x3)
{
  board = b1;
  DfsSolver s;
  solver = &s;
  check();
}

// // Too complex board for dfs - takes a lot of time
//TEST_F(Solvers, checkDfs_board4x4)
//{
//  board = b2;
//  DfsSolver s;
//  solver = &s;
//  check();
//}

TEST_F(Solvers, checkIdfs_board3x3)
{
  board = b1;
  IdfsSolver s;
  solver = &s;
  check();
}

TEST_F(Solvers, checkIdfs_board4x4)
{
  board = b2;
  IdfsSolver s;
  solver = &s;
  check();
}

TEST_F(Solvers, checkBestFirst_board3x3)
{
  board = b1;
  BestFirstSolver s;
  solver = &s;
  check();
}

TEST_F(Solvers, checkBestFirst_board4x4)
{
  board = b2;
  BestFirstSolver s;
  solver = &s;
  check();
}

TEST_F(Solvers, checkAStar_board3x3)
{
  board = b1;
  AStarSolver s;
  solver = &s;
  check();
}

TEST_F(Solvers, checkAStar_board4x4)
{
  board = b2;
  AStarSolver s;
  solver = &s;
  check();
}

TEST_F(Solvers, checkSmaStar_board3x3)
{
  board = b1;
  SmaStarSolver s;
  solver = &s;
  check();
}

TEST_F(Solvers, checkSmaStar_board4x4)
{
  board = b2;
  SmaStarSolver s;
  solver = &s;
  check();
}

TEST_F(Solvers, checkBestFirst_comparator)
{
  using T = BestFirstSolver::BFState;
  using C = BestFirstSolver::Greater;
  std::priority_queue<T, std::vector<T>, C> pq;
  T a, b, c;
  a.estimatedCost = 1;
  b.estimatedCost = 2;
  c.estimatedCost = 3;
  pq.push(b);
  pq.push(a);
  pq.push(b);
  pq.push(c);
  EXPECT_EQ(pq.top().estimatedCost, 1);
  pq.pop();
  EXPECT_EQ(pq.top().estimatedCost, 2);
  pq.pop();
  EXPECT_EQ(pq.top().estimatedCost, 2);
  pq.pop();
  EXPECT_EQ(pq.top().estimatedCost, 3);
  pq.pop();
}

TEST_F(Solvers, checkAStar_comparator)
{
  using T = AStarSolver::AState;
  using C = AStarSolver::Greater;
  std::priority_queue<T, std::vector<T>, C> pq;
  T a, b, c;
  a.estimatedTotalCost = 1;
  b.estimatedTotalCost = 2;
  c.estimatedTotalCost = 3;
  pq.push(b);
  pq.push(a);
  pq.push(b);
  pq.push(c);
  EXPECT_EQ(pq.top().estimatedTotalCost, 1u);
  pq.pop();
  EXPECT_EQ(pq.top().estimatedTotalCost, 2u);
  pq.pop();
  EXPECT_EQ(pq.top().estimatedTotalCost, 2u);
  pq.pop();
  EXPECT_EQ(pq.top().estimatedTotalCost, 3u);
  pq.pop();
}

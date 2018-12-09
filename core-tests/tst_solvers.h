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
    b1 = Board(3, 3, {
                 7, 4, 3,
                 8, 0, 5,
                 2, 1, 6
               });

    b2 = Board(4, 4, {
                 5,  1,  2,  3,
                 9,  10, 6,  4,
                 13, 0,  7,  8,
                 14, 15, 11, 12
               });
  }

  void check()
  {
    ASSERT_TRUE(solver->solve(board));
    try {
      for (auto &d : solver->result())
        Utils::makeMovement(board, d);
    } catch (CoreException &e) {
      ASSERT_FALSE(true); // failed to make movement, wrong result!
    }
    EXPECT_EQ(board, Utils::constructFinalBoard(board.rows(), board.columns()));
    std::cout << "checkedStates: " << solver->checkedStates() << "\n";
    std::cout << "resultLenght: " << solver->result().size() << "\n";
  }
};

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
  EXPECT_EQ(pq.top().estimatedCost, 1u);
  pq.pop();
  EXPECT_EQ(pq.top().estimatedCost, 2u);
  pq.pop();
  EXPECT_EQ(pq.top().estimatedCost, 2u);
  pq.pop();
  EXPECT_EQ(pq.top().estimatedCost, 3u);
  pq.pop();
}

TEST_F(Solvers, checkAStar_comparator)
{
  using T = AStarSolver::AState;
  using C = AStarSolver::Greater;
  std::priority_queue<T, std::vector<T>, C> pq;
  T a, b, c;
  a.estimatedCost = 1;
  b.estimatedCost = 2;
  c.estimatedCost = 3;
  pq.push(b);
  pq.push(a);
  pq.push(b);
  pq.push(c);
  EXPECT_EQ(pq.top().estimatedCost, 1u);
  pq.pop();
  EXPECT_EQ(pq.top().estimatedCost, 2u);
  pq.pop();
  EXPECT_EQ(pq.top().estimatedCost, 2u);
  pq.pop();
  EXPECT_EQ(pq.top().estimatedCost, 3u);
  pq.pop();
}

TEST_F(Solvers, checkSmaStar_comparator)
{
  using T = SmaStarSolver::SetState;
  using C = SmaStarSolver::Less;
  std::set<T, C> set;
  T a, b, c, d, e;
  a.depth = 1;
  a.estimatedCost = 1;
  b.depth = 2;
  b.estimatedCost = 1;
  c.depth = 3;
  c.estimatedCost = 1;
  d.depth = 1;
  d.estimatedCost = 2;
  e.depth = 2;
  e.estimatedCost = 2;
  set.insert(a);
  set.insert(b);
  b.memory = 1u;
  set.insert(b);
  set.insert(c);
  set.insert(d);
  set.insert(e);
  auto it = set.begin();
  EXPECT_EQ(it->estimatedCost, 1u);
  EXPECT_EQ(it->depth, 3u);
  ++it;
  EXPECT_EQ(it->estimatedCost, 1u);
  EXPECT_EQ(it->depth, 2u);
  ++it;
  EXPECT_EQ(it->estimatedCost, 1u);
  EXPECT_EQ(it->depth, 2u);
  ++it;
  EXPECT_EQ(it->estimatedCost, 1u);
  EXPECT_EQ(it->depth, 1u);
  ++it;
  EXPECT_EQ(it->estimatedCost, 2u);
  EXPECT_EQ(it->depth, 2u);
  ++it;
  EXPECT_EQ(it->estimatedCost, 2u);
  EXPECT_EQ(it->depth, 1u);
}

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

// Too complex board for dfs - takes a lot of time, test timeout
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

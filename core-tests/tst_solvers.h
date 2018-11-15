#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

#include "core.h"
#include <iostream>

class Solvers : public ::testing::Test
{
protected:
  Board b1, b2, board;
  Solver *solver;

  void SetUp() override
  {
    b1 = Board(3, 3);
    b1.setValueAt(0, 0, 0);
    b1.setValueAt(0, 1, 1);
    b1.setValueAt(0, 2, 3);

    b1.setValueAt(1, 0, 4);
    b1.setValueAt(1, 1, 2);
    b1.setValueAt(1, 2, 5);

    b1.setValueAt(2, 0, 7);
    b1.setValueAt(2, 1, 8);
    b1.setValueAt(2, 2, 6);

    b2 = Board(4, 4);
    b2.setValueAt(0, 0, 1);
    b2.setValueAt(0, 1, 2);
    b2.setValueAt(0, 2, 3);
    b2.setValueAt(0, 3, 4);

    b2.setValueAt(1, 0, 5);
    b2.setValueAt(1, 1, 6);
    b2.setValueAt(1, 2, 7);
    b2.setValueAt(1, 3, 8);

    b2.setValueAt(2, 0, 9);
    b2.setValueAt(2, 1, 0);
    b2.setValueAt(2, 2, 11);
    b2.setValueAt(2, 3, 12);

    b2.setValueAt(3, 0, 13);
    b2.setValueAt(3, 1, 10);
    b2.setValueAt(3, 2, 14);
    b2.setValueAt(3, 3, 15);

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

TEST_F(Solvers, checkDfs_board4x4)
{
  board = b2;
  DfsSolver s;
  solver = &s;
  check();
}

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

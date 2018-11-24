#include "tst_board.h"
#include "tst_utils.h"
#include "tst_history_state.h"
#include "tst_heuristic.h"
#include "tst_solvers.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

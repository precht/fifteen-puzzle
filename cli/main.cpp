#include <iostream>
#include <cstdint>
#include <bitset>

#include "core.h"

using namespace std;

int main()
{
  freopen("input", "r", stdin);

  try {
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

    Solver solver(board);
    Bfs bfs;
    Dfs dfs;
    cout << Utils::isSolvable(board) << endl;
    cout << solver.solve(&bfs) << endl;
  }
  catch(const CoreException &exception) {
      std::cerr << exception.what() << std::endl;
  }
  return 0;
}

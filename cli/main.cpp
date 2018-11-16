#include <iostream>
#include <cstdint>
#include <bitset>
#include <string>

#include "core.h"

using namespace std;

int main()
{
  freopen("input", "r", stdin);

  try {
    Board board(4, 4);
    board.setValueAt(0, 0, 13);
    board.setValueAt(0, 1, 2);
    board.setValueAt(0, 2, 10);
    board.setValueAt(0, 3, 3);

    board.setValueAt(1, 0, 1);
    board.setValueAt(1, 1, 12);
    board.setValueAt(1, 2, 8);
    board.setValueAt(1, 3, 4);

    board.setValueAt(2, 0, 5);
    board.setValueAt(2, 1, 0);
    board.setValueAt(2, 2, 9);
    board.setValueAt(2, 3, 6);

    board.setValueAt(3, 0, 15);
    board.setValueAt(3, 1, 14);
    board.setValueAt(3, 2, 11);
    board.setValueAt(3, 3, 7);

    Solver *solver = new DfsSolver();
    cout << "Is solvable: " << solver->solve(board) << "\nResult:\n";
    for (auto &a : solver->result()) {
      std::string s = a;
      cout << s << " ";
    }
    cout << '\n';
    cout << "Result: " << solver->result().size() << '\n';
    cout << "Checked: " << solver->checkedStates() << '\n';
  }
  catch(const CoreException &exception) {
      std::cerr << exception.what() << std::endl;
  }
  return 0;
}

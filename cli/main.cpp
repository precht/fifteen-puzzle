#include <iostream>
#include <cstdint>
#include <bitset>
#include <string>

#include "core.h"

using namespace std;

#include <limits>
#include <climits>
#include <unordered_map>
#include <map>

int main()
{
  freopen("input", "r", stdin);

//  try {
    Board b2 = Board(4, 4);
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

    Board b4 = Board(4, 4);
    b4.setValueAt(0, 0, 1);
    b4.setValueAt(0, 1, 2);
    b4.setValueAt(0, 2, 3);
    b4.setValueAt(0, 3, 4);

    b4.setValueAt(1, 0, 5);
    b4.setValueAt(1, 1, 6);
    b4.setValueAt(1, 2, 7);
    b4.setValueAt(1, 3, 8);

    b4.setValueAt(2, 0, 9);
    b4.setValueAt(2, 1, 10);
    b4.setValueAt(2, 2, 11);
    b4.setValueAt(2, 3, 12);

    b4.setValueAt(3, 0, 13);
    b4.setValueAt(3, 1, 0);
    b4.setValueAt(3, 2, 14);
    b4.setValueAt(3, 3, 15);

    Solver *solver = new SmaStarSolver();
    cout << "Is solvable: " << solver->solve(b2) << endl; //"\nResult:\n";
    for (auto &a : solver->result()) {
      std::string s = a;
      cout << s << " ";
    }
    cout << '\n';
    cout << "Result: " << solver->result().size() << '\n';
    cout << "Checked: " << solver->checkedStates() << '\n';
//  }
//  catch(const CoreException &exception) {
//      std::cerr << exception.what() << std::endl;
//  }
  return 0;
}

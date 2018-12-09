#include "core.h"
#include <iostream>
#include <cstring>
#include <cassert>
#include <chrono>
#include <memory>

using namespace std;

struct Config
{
  Board board;
  Solver::Algorithm algorithm;
  string algorithmName;
  std::vector<Direction> order;
  bool isRandom = false;
  Heuristic::Type heuristic;
};

string msg = ""
             "Possible algorithms:\n"
             "-b/--bfs order   Breadth-first search\n"
             "-d/--dfs order   Depth-first search\n"
             "-i/--idfs order   Iterative deepenening DFS\n"
             "-h/--bf id_of_heurisic   Best-first strategy\n"
             "-a/--astar id_of_heurisic   A* strategy\n"
             "-s/--sma id_of_heurisic   SMA* strategy\n"
             "\n"
             "Order can be composed of four letter 'L', 'R', 'D', 'U' or a string 'RAND'.\n"
             "\n"
             "Heuristics:\n"
             "0   AllTaxicab - taxicab distance to correct position of all cells except 0\n"
             "1   ZeroTaxicab - taxicab distance of 0 cell to correct position\n"
             "2   WrongCount - number of wrong places cells\n"
    ;

Config readArgs(int argc, char *argv[])
{
  if (argc == 1 || strncmp(argv[1], "--help", 6) == 0) {
    cout << msg;
    exit(0);
  }

  if (argc != 3)
    throw CoreException("Wrong number of arguments.");

  Config config;
  string str = argv[1];
  string order;
  string heuristic;

  if (str == "-b" || str == "--bfs") {
    order = argv[2];
    config.algorithm = Solver::Bfs;
    config.algorithmName = "Bfs";
  } else if (str == "-d" || str == "--dfs") {
    order = argv[2];
    config.algorithm = Solver::Dfs;
    config.algorithmName = "Dfs";
  } else if (str == "-i" || str == "--idfs") {
    order = argv[2];
    config.algorithm = Solver::Idfs;
    config.algorithmName = "Idfs";
  } else if (str == "-h" || str == "--bf") {
    heuristic = argv[2];
    config.algorithm = Solver::BestFirst;
    config.algorithmName = "BestFirst";
  } else if (str == "-a" || str == "--astar") {
    heuristic = argv[2];
    config.algorithm = Solver::AStar;
    config.algorithmName = "AStar";
  } else if (str == "-s" || str == "--sma") {
    heuristic = argv[2];
    config.algorithm = Solver::SmaStar;
    config.algorithmName = "SmaStart";
  } else {
    throw CoreException("Wrong argument: " + str + ".");
  }

  if (order.size() > 0) {
    if (order.size() != 4)
      throw CoreException("Wrong order size.");

    if (order == "RAND") {
      config.isRandom = true;
    }
    else {
      for (auto &x : order) {
        switch (x) {
        case 'L': config.order.push_back(Direction::Left); break;
        case 'R': config.order.push_back(Direction::Right); break;
        case 'U': config.order.push_back(Direction::Up); break;
        case 'D': config.order.push_back(Direction::Down); break;
        default: throw CoreException("Wrong order: " + order + ".");
        }
      }

      int count[4] = { 0, 0, 0, 0 };
      for (auto &x : config.order)
        count[x]++;
      for (int i = 0; i < 4; i++)
        if (count[i] != 1)
          throw CoreException("Wrong order: " + order + ".");
    }
  }

  if (heuristic.size() > 0) {
    int id;
    try {
      id = std::stoi(heuristic);
    } catch (std::exception &e) {
      throw CoreException("Wrong heuristic id.");
    }
    switch (id) {
    case 0: config.heuristic = Heuristic::AllTaxicab; break;
    case 1: config.heuristic = Heuristic::ZeroTaxicab; break;
    case 2: config.heuristic = Heuristic::WrongCount; break;
    default: throw CoreException("Wrong heurisitc id.");
    }
  }

  try {
    unsigned rows, columns;
    cin >> rows >> columns;
    config.board = Board(rows, columns);
    for (unsigned iRow = 0; iRow < rows; iRow++) {
      for (unsigned iColumn = 0; iColumn < columns; iColumn++) {
        unsigned value;
        cin >> value;
        config.board.setValueAt(iRow, iColumn, value);
      }
    }
  } catch (CoreException &e) {
    throw CoreException("Fail to create board from input.");
  }

  return config;
}

void run(Config config) {
  std::unique_ptr<Solver> pSolver;
  switch (config.algorithm) {
  case Solver::Bfs: pSolver = std::make_unique<BfsSolver>(); break;
  case Solver::Dfs: pSolver = std::make_unique<DfsSolver>(); break;
  case Solver::Idfs: pSolver = std::make_unique<IdfsSolver>(); break;
  case Solver::BestFirst: pSolver = std::make_unique<BestFirstSolver>(); break;
  case Solver::AStar: pSolver = std::make_unique<AStarSolver>(); break;
  case Solver::SmaStar: pSolver = std::make_unique<SmaStarSolver>(); break;
  default: assert(false);
  }

  if (config.order.size() > 0)
    pSolver->setOrder(config.order);
  if (config.isRandom == true)
    pSolver->randomOrder(true);

  if (!Utils::isSolvable(config.board)) {
    cout << "Board is not solvable." << endl;
    return;
  }

  auto startTime = chrono::system_clock::now();
  bool isSolved = pSolver->solve(config.board, config.heuristic);
  auto finishTime = chrono::system_clock::now();

  if (isSolved) {
    Board board = config.board;
    for (auto &x : pSolver->result())
      Utils::makeMovement(board, x);
    isSolved = (board == Utils::constructFinalBoard(board.rows(), board.columns()));
  }

  if (!isSolved) {
    cout << "Failed to solve board." << endl;
    return;
  }

  cout << "Algorithm: " << config.algorithmName << "\n";
  cout << "Checked nodes: " << pSolver->checkedStates() << "\n";
  chrono::duration<double> time = finishTime - startTime;
  cout << "Time: " << time.count() << "s\n";
  cout << "Result lenght: " << pSolver->result().size() << "\n";
  cout << "Result:\n";
  for (auto &x : pSolver->result())
    cout << x << " ";
  cout << endl;
}

int main(int argc, char* argv[])
{
  ios_base::sync_with_stdio(false);
//  freopen("input", "r", stdin);

  try {
    run(readArgs(argc, argv));
  } catch (CoreException &e) {
    cerr << "ERROR: " << e.what() << endl;
    return 1;
  }

  return 0;
}


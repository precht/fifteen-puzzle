#include "smastarsolver.h"
#include "utils.h"
#include "coreexception.h"
#include <algorithm>
#include <iostream>
#include <cassert>
#include <queue>

bool SmaStarSolver::solve()
{
  mSet = {};
  mGraph = {};
  mCheckedStates = 0;

  Board board = mInitialBoard;
  {
    SetState setState;
    GraphState graphState;

    graphState.estimatedCost = 1;
    setState.estimatedCost = 1;
    setState.memory = board.memory();

    mGraph[board.memory()] = graphState;
    mSet.insert(setState);
//    mIds[board.memory()] = ++mCounter;
  }

  while (!mSet.empty()) {
    mCheckedStates++;
    assert(mSet.begin() != mSet.end());
    SetState setState = *(mSet.begin());
    assert((mGraph.find(setState.memory) != mGraph.end()));
    GraphState &graphState = mGraph[setState.memory];
//    std::cout<< ">>> Node: " << mIds[setState.memory] << " "
//             << graphState.direction << std::endl;
//    print();
    board.setMemory(setState.memory);

    if (board == mFinalBoard) {
      mFinalSetState = setState;
      return true;
    }

    // set estimated cost of current node to depth and backtrack update
    // do this to prevent deletion of nodes that are on current path
    assert(mSet.find(setState) != mSet.end());
    mSet.erase(setState);
    setState.estimatedCost = setState.depth;
    mSet.insert(setState);
    graphState.estimatedCost = setState.depth;
    if (setState.depth > 1) {
      Utils::reverseMovement(board, graphState.direction);
      SetState tmpSetState;
      tmpSetState.memory = board.memory();
      tmpSetState.depth = setState.depth - 1;
      assert((mGraph.find(board.memory()) != mGraph.end()));
      tmpSetState.estimatedCost = mGraph[board.memory()].estimatedCost;
      update(tmpSetState);
    }
//    print();

    // insert new nodes
    board.setMemory(setState.memory);
    auto possibleDirections = generatePossibleDirections(board);
    for (auto &direction : possibleDirections) {
      board.setMemory(setState.memory);
      Utils::makeMovement(board, direction);

      // if node is in stored or its depth exceeds cSizeLimit then omit it
      if ((mGraph.find(board.memory()) != mGraph.end()) || (setState.depth + 1 > cSizeLimit))
        continue;

      bool isChildProccessed = false;
      for (auto &x : graphState.children)
        if (x.first == board.memory() && x.second == false)
          isChildProccessed = true;
      if (isChildProccessed)
        continue;

      SetState childSetState;
      childSetState.depth = setState.depth + 1;
      childSetState.memory = board.memory();
      childSetState.estimatedCost = setState.depth + mHeuristic(board, mFinalBoard, mDistance);

      GraphState childGraphState;
      childGraphState.depth = childSetState.depth;
      childGraphState.estimatedCost = childSetState.estimatedCost;
      childGraphState.direction = direction;

      graphState.children.push_back({ board.memory(), true });
//      if (mIds.find(board.memory()) == mIds.end())
//        mIds[board.memory()] = ++mCounter;

      // remove if no more space
      if (mSet.size() == cSizeLimit) {
        SetState lastSetstate = *(mSet.rbegin());
        if (mLess(lastSetstate, childSetState)) {
//          std::cout<< "InsertOmmit: " << mIds[childSetState.memory] << std::endl;
          continue;
        }
        // delete of children of the state we need to drop from set
//        std::cout<< "InsertDelete: " << mIds[lastSetstate.memory] << std::endl;
        std::queue<SetState> toDelete;
        toDelete.push(lastSetstate);

        while (!toDelete.empty()) {
          SetState deleteState = toDelete.front();
          toDelete.pop();
          assert(mGraph.find(deleteState.memory) != mGraph.end());
          for (auto &child : mGraph[deleteState.memory].children) {
            if ((child.second == true)
                && (mGraph.find(child.first) != mGraph.end())
                && (mGraph[child.first].depth == deleteState.depth + 1)) {
              SetState tmpState;
              tmpState.memory = child.first;
              tmpState.estimatedCost = mGraph[child.first].estimatedCost;
              tmpState.depth = deleteState.depth + 1;
              toDelete.push(tmpState);
            }
          }
          mGraph.erase(deleteState.memory);
          mSet.erase(deleteState);
        }
      }

      mSet.insert(childSetState);
      mGraph[board.memory()] = childGraphState;
    }

    // set estimated cost of current node to minimum estimated cost of children
    // if no child exists or all children have estimated cost cInfinity then remove current node
    update(setState);
  }

  return false;
}

void SmaStarSolver::update(const SetState &setState)
{
//  std::cout<< "Update: " << mIds[setState.memory] << std::endl;

  Board board = mInitialBoard;
  SetState iSetState = setState;

  while (true) {
//    std::cout<< "_" << mIds[iSetState.memory] << std::endl;
    uint64_t memory = iSetState.memory;
    assert(mGraph.find(memory) != mGraph.end());
    GraphState &iGraphState = mGraph[memory];
    Direction iDirection = iGraphState.direction;
    uint32_t previousCost = iGraphState.estimatedCost;

    bool cannotBeDeleted = false;
    iGraphState.estimatedCost = cInfinity;
    for (auto &x : iGraphState.children) {
      cannotBeDeleted |= x.second;
      if (mGraph.find(x.first) != mGraph.end()) {
        assert(mGraph.find(x.first) != mGraph.end());
        iGraphState.estimatedCost = std::min(iGraphState.estimatedCost,
                                             mGraph[x.first].estimatedCost);
      }
    }

    if (previousCost == iGraphState.estimatedCost)
        break;

    assert(mSet.find(iSetState) != mSet.end());
    mSet.erase(iSetState);
    if (cannotBeDeleted == true && iGraphState.estimatedCost == cInfinity)
      iGraphState.estimatedCost = cInfinity - 1;
    iSetState.estimatedCost = iGraphState.estimatedCost;
    mSet.insert(iSetState);

    SetState tmpState = iSetState;
    if (iSetState.depth > 1) {
      board.setMemory(memory);
      Utils::reverseMovement(board, iDirection);
      tmpState.depth--;
      tmpState.memory = board.memory();
      if (mGraph.find(board.memory()) == mGraph.end()) {
        print();
//        std::cout << "Failed on " << mIds[board.memory()] << std::endl;
      }
      assert(mGraph.find(board.memory()) != mGraph.end());
      tmpState.estimatedCost = mGraph[board.memory()].estimatedCost;
    }

    if (iGraphState.estimatedCost == cInfinity) {
//      std::cout<< "UpdateDelete: " << mIds[iSetState.memory] << std::endl;
      mSet.erase(iSetState);
      mGraph.erase(memory);

      if (iSetState.depth > 1)
        for (auto &x : mGraph[tmpState.memory].children)
          if (x.first == iSetState.memory)
            x.second = false;
    }

    if (iSetState.depth <= 1)
      break;
    iSetState = tmpState;
  }
}

void SmaStarSolver::storeResult()
{
  SetState iSetState = mFinalSetState;
  while (iSetState.depth > 1) {
    assert(mGraph.find(iSetState.memory) != mGraph.end());
    Direction direction = mGraph[iSetState.memory].direction;
    mResult.push_back(direction);
    Board board = mInitialBoard;
    board.setMemory(iSetState.memory);
    Utils::reverseMovement(board, direction);
    assert(mGraph.find(board.memory()) != mGraph.end());
    iSetState.depth--;
    iSetState.memory = board.memory();
  }
  std::reverse(mResult.begin(), mResult.end());
}

void SmaStarSolver::print()
{
//  for (auto &xs : mSet)
//    std::cout << "(" << mIds[xs.memory] << "," << xs.estimatedCost << "," << xs.depth << ") ";
//  std::cout << std::endl;
}

bool SmaStarSolver::Less::operator()(const SetState &cLhs, const SetState &cRhs) const
{
  if (cLhs.estimatedCost == cRhs.estimatedCost) {
    if (cLhs.depth == cRhs.depth)
      return cLhs.memory < cRhs.memory;
    return cLhs.depth > cRhs.depth;
  }
  return cLhs.estimatedCost < cRhs.estimatedCost;
}

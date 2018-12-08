#include "smastarsolver.h"
#include "utils.h"
#include "coreexception.h"
#include <algorithm>
#include <cassert>
#include <queue>

bool SmaStarSolver::initializeSearchLoop(const Board &cInitialBoard, const Heuristic::Type cType)
{
  if (Solver::initializeSearchLoop(cInitialBoard, cType) == false)
    return false;

  mSet = {};
  mGraph = {};
  mCheckedStates = 0;

  Board board = mInitialBoard;
  SetState setState;
  GraphState graphState;

  graphState.estimatedCost = 1;
  setState.estimatedCost = 1;
  setState.memory = board.memory();

  mGraph[board.memory()] = graphState;
  mSet.insert(setState);
  return true;
}

bool SmaStarSolver::isLoopEmpty() const
{
  return (mSet.empty() || mIsSolved);
}

bool SmaStarSolver::processNextState()
{
  assert(!isLoopEmpty());
  mCheckedStates++;
  Board board = mInitialBoard;

  assert(mSet.begin() != mSet.end());
  SetState setState = *(mSet.begin());
  board.setMemory(setState.memory);

  assert((mGraph.find(setState.memory) != mGraph.end()));
  GraphState &graphState = mGraph[setState.memory];

  if (board == mFinalBoard) {
    mFinalSetState = setState;
    mIsSolved = true;
    storeResult();
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

    // remove if no more space
    if (mSet.size() == cSizeLimit) {
      SetState lastSetstate = *(mSet.rbegin());
      if (mLess(lastSetstate, childSetState)) {
        continue;
      }
      // delete of children of the state we need to drop from set
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

  return false;
}

void SmaStarSolver::update(const SetState &setState)
{
  Board board = mInitialBoard;
  SetState iSetState = setState;

  while (true) {
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
      assert(mGraph.find(board.memory()) != mGraph.end());
      tmpState.estimatedCost = mGraph[board.memory()].estimatedCost;
    }

    if (iGraphState.estimatedCost == cInfinity) {
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

bool SmaStarSolver::Less::operator()(const SetState &cLhs, const SetState &cRhs) const
{
  if (cLhs.estimatedCost == cRhs.estimatedCost) {
    if (cLhs.depth == cRhs.depth)
      return cLhs.memory < cRhs.memory;
    return cLhs.depth > cRhs.depth;
  }
  return cLhs.estimatedCost < cRhs.estimatedCost;
}

#include "smastarsolver.h"
#include "utils.h"
#include "coreexception.h"
#include <algorithm>
#include <cassert>
#include <queue>

bool SmaStarSolver::initializeSearchLoop(const Board &c_initialBoard, const Heuristic::Type c_type)
{
  if (Solver::initializeSearchLoop(c_initialBoard, c_type) == false)
    return false;

  m_set = {};
  m_graph = {};
  m_checkedStates = 0;

  Board board = m_initialBoard;
  SetState setState;
  GraphState graphState;

  graphState.estimatedCost = 1;
  setState.estimatedCost = 1;
  setState.memory = board.memory();

  m_graph[board.memory()] = graphState;
  m_set.insert(setState);
  return true;
}

bool SmaStarSolver::isLoopEmpty() const
{
  return (m_set.empty() || m_isSolved);
}

bool SmaStarSolver::processNextState()
{
  assert(!isLoopEmpty());
  m_checkedStates++;
  Board board = m_initialBoard;

  assert(m_set.begin() != m_set.end());
  SetState setState = *(m_set.begin());
  board.setMemory(setState.memory);

  assert((m_graph.find(setState.memory) != m_graph.end()));
  GraphState &graphState = m_graph[setState.memory];

  if (board == m_finalBoard) {
    m_finalSetState = setState;
    m_isSolved = true;
    storeResult();
    return true;
  }

  // set estimated cost of current node to depth and backtrack update
  // do this to prevent deletion of nodes that are on current path
  assert(m_set.find(setState) != m_set.end());
  m_set.erase(setState);
  setState.estimatedCost = setState.depth;
  m_set.insert(setState);
  graphState.estimatedCost = setState.depth;
  if (setState.depth > 1) {
    Utils::reverseMovement(board, graphState.direction);
    SetState tmpSetState;
    tmpSetState.memory = board.memory();
    tmpSetState.depth = setState.depth - 1;
    assert((m_graph.find(board.memory()) != m_graph.end()));
    tmpSetState.estimatedCost = m_graph[board.memory()].estimatedCost;
    update(tmpSetState);
  }

  // insert new nodes
  board.setMemory(setState.memory);
  auto possibleDirections = generatePossibleDirections(board);
  for (auto &direction : possibleDirections) {
    board.setMemory(setState.memory);
    Utils::makeMovement(board, direction);

    // if node is in stored or its depth exceeds cSizeLimit then omit it
    if ((m_graph.find(board.memory()) != m_graph.end()) || (setState.depth + 1 > cSizeLimit))
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
    childSetState.estimatedCost = setState.depth + m_heuristic(board, m_finalBoard, m_distance);

    GraphState childGraphState;
    childGraphState.depth = childSetState.depth;
    childGraphState.estimatedCost = childSetState.estimatedCost;
    childGraphState.direction = direction;

    graphState.children.push_back({ board.memory(), true });

    // remove if no more space
    if (m_set.size() == cSizeLimit) {
      SetState lastSetstate = *(m_set.rbegin());
      if (m_less(lastSetstate, childSetState)) {
        continue;
      }
      // delete of children of the state we need to drop from set
      std::queue<SetState> toDelete;
      toDelete.push(lastSetstate);

      while (!toDelete.empty()) {
        SetState deleteState = toDelete.front();
        toDelete.pop();
        assert(m_graph.find(deleteState.memory) != m_graph.end());
        for (auto &child : m_graph[deleteState.memory].children) {
          if ((child.second == true)
              && (m_graph.find(child.first) != m_graph.end())
              && (m_graph[child.first].depth == deleteState.depth + 1)) {
            SetState tmpState;
            tmpState.memory = child.first;
            tmpState.estimatedCost = m_graph[child.first].estimatedCost;
            tmpState.depth = deleteState.depth + 1;
            toDelete.push(tmpState);
          }
        }
        m_graph.erase(deleteState.memory);
        m_set.erase(deleteState);
      }
    }

    m_set.insert(childSetState);
    m_graph[board.memory()] = childGraphState;
  }

  // set estimated cost of current node to minimum estimated cost of children
  // if no child exists or all children have estimated cost cInfinity then remove current node
  update(setState);

  return false;
}

void SmaStarSolver::update(const SetState &c_setState)
{
  Board board = m_initialBoard;
  SetState iSetState = c_setState;

  while (true) {
    uint64_t memory = iSetState.memory;
    assert(m_graph.find(memory) != m_graph.end());
    GraphState &iGraphState = m_graph[memory];
    Direction iDirection = iGraphState.direction;
    uint32_t previousCost = iGraphState.estimatedCost;

    bool cannotBeDeleted = false;
    iGraphState.estimatedCost = cInfinity;
    for (auto &x : iGraphState.children) {
      cannotBeDeleted |= x.second;
      if (m_graph.find(x.first) != m_graph.end()) {
        assert(m_graph.find(x.first) != m_graph.end());
        iGraphState.estimatedCost = std::min(iGraphState.estimatedCost,
                                             m_graph[x.first].estimatedCost);
      }
    }

    if (previousCost == iGraphState.estimatedCost)
      break;

    assert(m_set.find(iSetState) != m_set.end());
    m_set.erase(iSetState);
    if (cannotBeDeleted == true && iGraphState.estimatedCost == cInfinity)
      iGraphState.estimatedCost = cInfinity - 1;
    iSetState.estimatedCost = iGraphState.estimatedCost;
    m_set.insert(iSetState);

    SetState tmpState = iSetState;
    if (iSetState.depth > 1) {
      board.setMemory(memory);
      Utils::reverseMovement(board, iDirection);
      tmpState.depth--;
      tmpState.memory = board.memory();
      assert(m_graph.find(board.memory()) != m_graph.end());
      tmpState.estimatedCost = m_graph[board.memory()].estimatedCost;
    }

    if (iGraphState.estimatedCost == cInfinity) {
      m_set.erase(iSetState);
      m_graph.erase(memory);

      if (iSetState.depth > 1)
        for (auto &x : m_graph[tmpState.memory].children)
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
  SetState iSetState = m_finalSetState;
  while (iSetState.depth > 1) {
    assert(m_graph.find(iSetState.memory) != m_graph.end());
    Direction direction = m_graph[iSetState.memory].direction;
    m_result.push_back(direction);
    Board board = m_initialBoard;
    board.setMemory(iSetState.memory);
    Utils::reverseMovement(board, direction);
    assert(m_graph.find(board.memory()) != m_graph.end());
    iSetState.depth--;
    iSetState.memory = board.memory();
  }
  std::reverse(m_result.begin(), m_result.end());
}

bool SmaStarSolver::Less::operator()(const SetState &c_lhs, const SetState &c_rhs) const
{
  if (c_lhs.estimatedCost == c_rhs.estimatedCost) {
    if (c_lhs.depth == c_rhs.depth)
      return c_lhs.memory < c_rhs.memory;
    return c_lhs.depth > c_rhs.depth;
  }
  return c_lhs.estimatedCost < c_rhs.estimatedCost;
}

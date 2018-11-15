#include "direction.h"

std::string DirectionToString::operator()(const Direction direction) const
{
  switch (direction) {
  case Left: return "Left";
  case Right: return "Right";
  case Up: return "Up";
  case Down: return "Down";
  default: return "None";
  }
}

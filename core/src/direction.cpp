#include "direction.h"

Direction::Direction(const Direction::Type cType)
  : mType(static_cast<uint8_t>(cType))
{ }

Direction::operator uint8_t() const
{
  return mType;
}

Direction::operator std::string() const
{
  switch (mType) {
  case Left: return "L";
  case Right: return "R";
  case Up: return "U";
  case Down: return"D";
  default: return "N";
  }
}

std::ostream& operator<<(std::ostream &stream, const Direction &cDirection)
{
  stream << std::string(cDirection);
  return stream;
}

bool Direction::isReverseDirection(const Direction &cLhs, const Direction &cRhs)
{
  switch (cLhs) {
  case Left: return cRhs == Right;
  case Right: return cRhs == Left;
  case Up: return cRhs == Down;
  case Down: return cRhs == Up;
  default: return false;
  }
}

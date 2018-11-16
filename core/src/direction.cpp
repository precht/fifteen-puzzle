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
  case Left: return "Left";
  case Right: return "Right";
  case Up: return "Up";
  case Down: return"Down";
  default: return "None";
  }
}

std::ostream& operator<<(std::ostream &stream, const Direction &cDirection)
{
  stream << std::string(cDirection);
  return stream;
}

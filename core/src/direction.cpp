#include "direction.h"

Direction::Direction(const Direction::Type c_type)
  : m_type(static_cast<uint8_t>(c_type))
{ }

Direction::operator uint8_t() const
{
  return m_type;
}

Direction::operator std::string() const
{
  switch (m_type) {
  case Left: return "L";
  case Right: return "R";
  case Up: return "U";
  case Down: return"D";
  default: return "N";
  }
}

std::ostream& operator<<(std::ostream &r_stream, const Direction &c_direction)
{
  r_stream << std::string(c_direction);
  return r_stream;
}

bool Direction::isReverseDirection(const Direction &c_lhs, const Direction &c_rhs)
{
  switch (c_lhs) {
  case Left: return c_rhs == Right;
  case Right: return c_rhs == Left;
  case Up: return c_rhs == Down;
  case Down: return c_rhs == Up;
  default: return false;
  }
}

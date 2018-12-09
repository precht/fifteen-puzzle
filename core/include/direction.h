#ifndef DIRECTION_H
#define DIRECTION_H

#include <ostream>

class Direction
{
  uint8_t m_type = 4;

public:
  enum Type { Left = 0, Right = 1, Up = 2, Down = 3, None = 4 };

  Direction() = default;
  Direction(const Type c_type);
  operator uint8_t() const;
  operator std::string() const;
  friend std::ostream& operator<<(std::ostream &r_stream, const Direction &c_direction);
  static bool isReverseDirection(const Direction &c_lhs, const Direction &c_rhs);
};

#endif // DIRECTION_H

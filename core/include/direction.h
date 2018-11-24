#ifndef DIRECTION_H
#define DIRECTION_H

#include <ostream>

class Direction
{
  uint8_t mType = 4;

public:
  enum Type { Left = 0, Right = 1, Up = 2, Down = 3, None = 4 };

  Direction() = default;
  Direction(const Type cType);
  operator uint8_t() const;
  operator std::string() const;
  friend std::ostream& operator<<(std::ostream &stream, const Direction &cDirection);
  static bool isReverseDirection(const Direction &cLhs, const Direction &cRhs);
};

#endif // DIRECTION_H

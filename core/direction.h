#ifndef DIRECTION_H
#define DIRECTION_H

#include <string>

enum Direction { Left, Right, Up, Down, None };

struct DirectionToString
{
  std::string operator()(const Direction direction) const;
};

#endif // DIRECTION_H

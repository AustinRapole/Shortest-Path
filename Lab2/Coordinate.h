#ifndef COORDINATE__H
#define COORDINATE__H

struct Coordinate{
  Coordinate();
  Coordinate(int a, int b);
  int x;
  int y;
};

Coordinate operator+(const Coordinate& a, const Coordinate& b);
Coordinate operator/(const Coordinate& a, int b);
bool operator==(const Coordinate& a, const Coordinate& b);
Coordinate operator-(const Coordinate& a, const Coordinate& b);

#endif

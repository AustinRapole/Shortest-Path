#include "Coordinate.h"

Coordinate::Coordinate(){
  x = 0;
  y =0;
}

Coordinate::Coordinate(int a, int b){
  x =a;
  y =b;
}

Coordinate operator+(const Coordinate& a, const Coordinate& b){
  return Coordinate(a.x+b.x,a.y+b.y);
}

Coordinate operator/(const Coordinate& a, int b){
  return Coordinate(a.x/b,a.y/b);
}

bool operator==(const Coordinate& a, const Coordinate& b){
	return a.x==b.x && a.y==b.y;
}
Coordinate operator-(const Coordinate& a, const Coordinate& b){
  return Coordinate(a.x-b.x,a.y-b.y);
}


#include "point.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void Point::move(double dx, double dy) {
  x = x + dx;
  y = y + dy;
}

double Point::distanceFrom(const Point & p) {
  double distance;
  distance = sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
  return distance;
}

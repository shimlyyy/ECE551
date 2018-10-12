#include "circle.h"
#define PI 3.1415926535
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Circle::Circle(Point c, double r) : center(c), radius(r) {}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double distance = center.distanceFrom(otherCircle.center);
  double area, alpha, s;
  if (distance >= (radius + otherCircle.radius)) {
    area = 0;
  }
  else if (distance <= abs(radius - otherCircle.radius)) {
    if (radius <= otherCircle.radius) {
      area = PI * radius * radius;
    }
    else {
      area = PI * otherCircle.radius * otherCircle.radius;
    }
  }
  else {
    alpha = acos((distance * distance + radius * radius - otherCircle.radius * otherCircle.radius) /
                 (2 * distance * radius));
    area = alpha * radius * radius;
    alpha = acos((distance * distance + otherCircle.radius * otherCircle.radius - radius * radius) /
                 (2 * distance * otherCircle.radius));
    area += alpha * otherCircle.radius * otherCircle.radius;
    s = (distance + radius + otherCircle.radius) / 2;
    area -= sqrt(s * (s - distance) * (s - radius) * (s - otherCircle.radius)) * 2;
  }
  return area;
}

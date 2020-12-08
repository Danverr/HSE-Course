#include "square.h"

Square::Square(const Point& p1, const Point& p2) 
    : Rectangle(p1, p2, 1) {}

Circle Square::circumscribedCircle() const {
    return Circle(center(), dist(points[0], points[2]));
}

Circle Square::inscribedCircle() const {
    return Circle(center(), dist(points[0], points[1]));
}
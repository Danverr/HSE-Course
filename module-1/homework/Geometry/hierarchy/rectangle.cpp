#include "rectangle.h"

Rectangle::Rectangle(const Point& p1, const Point& p2, const double& coef) : Polygon({}) {
    double l_angle = radToDeg(atan(coef));
    double r_angle = 90 - l_angle;
    double diag = dist(p1, p2);
    double long_side = diag / sqrt(coef*coef + 1);
    double short_side = long_side * coef;

    points = std::vector<Point>{        
        p1,
        (Vector(p1, p2) * (long_side / diag)).rotate(l_angle).end(),
        p2,
        (Vector(p1, p2) * (short_side / diag)).rotate(-r_angle).end()
    };
}

Point Rectangle::center() const {
    return (points[0] + points[2]) / 2;
}

std::pair<Line, Line> Rectangle::diagonals() const {
    return {Line(points[0], points[2]), Line(points[1], points[3])};
}
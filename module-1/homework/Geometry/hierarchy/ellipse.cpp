#include "ellipse.h"

Ellipse::Ellipse(const Point& f1, const Point& f2, const double& dist)
    : f1(f1), f2(f2), a(dist / 2) {}

double Ellipse::c() const {
    return dist(f1, f2) / 2;
}

double Ellipse::b() const {
    double _c = c();
    return std::sqrt(a * a - _c * _c);
}

double Ellipse::perimeter() const {
    double _c = c();
    double _b = b();
    return 4 * (PI * a * _b + (a - _b)) / (a + _b);
}

double Ellipse::area() const {
    return PI * a * b();
}

bool Ellipse::operator==(const Shape& another) const {
    const auto* ellipse = dynamic_cast<const Ellipse*>(&another);

    if (ellipse != nullptr) {
        return ((f1 == ellipse->f1 && f2 == ellipse->f2)
               || (f1 == ellipse->f2 && f2 == ellipse->f1))
               && a == ellipse->a;
    }else{
        return false;
    }    
}

bool Ellipse::isCongruentTo(const Shape& another) const {
    const auto* ellipse = dynamic_cast<const Ellipse*>(&another);

    if (ellipse != nullptr) {
        return a == ellipse->a && b() == ellipse->b();
    }else{
        return false;
    }    
}

bool Ellipse::isSimilarTo(const Shape& another) const {
    const auto* ellipse = dynamic_cast<const Ellipse*>(&another);

    if (ellipse != nullptr) {
        return a / ellipse->a == b() / ellipse->b();
    }else{
        return false;
    }    
}

bool Ellipse::containsPoint(const Point& point) const {
    return dist(point, f1) + dist(point, f2) <= 2 * a;
}

Shape& Ellipse::rotate(const Point& center, const double& angle) {
    f1 = Vector(center, f1).rotate(angle).end();
    f2 = Vector(center, f2).rotate(angle).end();
    return *this;
}

Shape& Ellipse::reflex(const Point& center) {
    f1 = (Vector(f1, center) * 2).end();
    f2 = (Vector(f2, center) * 2).end();
    return *this;
}

Shape& Ellipse::reflex(const Line& axis) {
    f1 = (Vector(f1, axis.getProjection(f1)) * 2).end();
    f2 = (Vector(f2, axis.getProjection(f2)) * 2).end();
    return *this;
}

Shape& Ellipse::scale(const Point& center, const double& coef) {
    f1 = (Vector(center, f1) * coef).end();
    f2 = (Vector(center, f2) * coef).end();
    a *= coef;
    return *this;
}

std::pair<Point, Point> Ellipse::focuses() const {
    return {f1, f2};
}

std::pair<Line, Line> Ellipse::directrices() const {
    double e = eccentricity();
    return {Line(Point(a / e, 0), Point(a / e, 1)), 
            Line(Point(-a / e, 0), Point(-a / e, 1))};
}

double Ellipse::eccentricity() const {
    return c() / a;
}

Point Ellipse::center() const {
    return (f1 + f2) / 2;
}
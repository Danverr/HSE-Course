#include "vector.h"

Vector::Vector(const Point& a, const Point& b)
    : _beg(a),
    _end(b) {};

bool Vector::operator==(const Vector& another) const {
    return _beg == another._beg && _end == another._end;
}

bool Vector::operator!=(const Vector& another) const {
    return !(*this == another);
}

double Vector::length() const{
    return dist(_beg, _end);
}

Vector Vector::operator+(const Vector& another) const {
    return Vector(*this) += another;
}

Vector Vector::operator-(const Vector& another) const {
    return Vector(*this) -= another;
}

Vector Vector::operator*(const double& coef) const {
    return Vector(*this) *= coef;
}

Vector Vector::operator/(const double& coef) const {
    return Vector(*this) /= coef;
}

double Vector::operator*(const Vector& another) const {
    Point coord = value();
    Point another_coord = another.value();
    return coord.x * another_coord.x + coord.y * another_coord.y;
}

double Vector::operator^(const Vector& another) const {    
    Point coord = value();
    Point another_coord = another.value();
    return coord.x * another_coord.y - another_coord.x * coord.y;
}

Vector& Vector::operator+=(const Vector& another) {
    this->_end += another.value();
    return *this;
}

Vector& Vector::operator-=(const Vector& another) {
    this->_end -= another.value();
    return *this;
}

Vector& Vector::operator*=(const double& coef) {
    _end = _beg + value() * coef;
    return *this;
}

Vector& Vector::operator/=(const double& coef) {
    _end = _beg + value() / coef;
    return *this;
}

double Vector::orientation(const Point& point) const {
    return *this ^ Vector(_beg, point);
}

bool Vector::isLeft(const Point& point) const {
    return this->orientation(point) > 0;
}

bool Vector::isRight(const Point& point) const{
    return this->orientation(point) < 0;
}

Vector& Vector::rotate(double angle){
    double rad = degToRad(angle);
    Point coord = value();
    double x = coord.x * cos(rad) - coord.y * sin(rad);
    double y = coord.x * sin(rad) + coord.y * cos(rad);
    
    this->_end = Point(x, y);

    return *this;
}

Point Vector::beg() const {
    return _beg;
}

Point Vector::end() const {
    return _end;
}

Point Vector::value() const {
    return _end - _beg;
}

double angle(const Vector& a, const Vector& b) {
    return radToDeg(asin((a ^ b) / (a.length() * b.length())));
}
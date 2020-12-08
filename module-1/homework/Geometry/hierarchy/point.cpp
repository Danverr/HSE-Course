#include "point.h"

Point::Point(const double& x, const double& y) : x(x), y(y) {};

bool Point::operator==(const Point& another) const {
	return equal(x, another.x) && equal(y, another.y);
}

bool Point::operator!=(const Point& another) const {
	return !(*this == another);
}

Point Point::operator+(const Point& another) const {
	Point copy = *this;
	return copy += another;
}

Point Point::operator-(const Point& another) const {
	Point copy = *this;
	return copy -= another;
}

Point Point::operator*(const double& coef) const {
	Point copy = *this;
	return copy *= coef;
}

Point Point::operator/(const double& coef) const {
	Point copy = *this;
	return copy *= coef;
}

Point& Point::operator+=(const Point& another) {
	this->x += another.x;
	this->y += another.y;
	return *this;
}

Point& Point::operator-=(const Point& another) {
	this->x -= another.x;
	this->y -= another.y;
	return *this;
}

Point& Point::operator*=(const double& coef) {
	this->x *= coef;
	this->y *= coef;
	return *this;
}

Point& Point::operator/=(const double& coef) {
	this->x /= coef;
	this->y /= coef;
	return *this;
}

double dist(const Point& a, const Point& b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double area(const Point& p1, const Point& p2, const Point& p3) {
	double a = dist(p1, p2), b = dist(p2, p3), c = dist(p3, p1);
	double p = (a + b + c) / 2;

	return sqrt(p * (p - a) * (p - b) * (p - c));
}

double angleBetween(const Point& p1, const Point& p2, const Point& p0 = Point(0, 0)) {
	double a = dist(p0, p1), b = dist(p0, p2), c = dist(p1, p2);
	return radToDeg(acos((a * a + b * b - c * c) / (2 * a * b)));
}
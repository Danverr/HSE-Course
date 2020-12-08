#include "line.h"

Line::Line(const Point& beg, const Point& end)
	: a(beg.y - end.y),
	b(end.x - beg.x),
	c(beg.x * end.y - end.x * beg.y),
	vector(Vector(beg, end)) {}

Line::Line(const Vector& vector) 
	: Line(vector.beg(), vector.end()) {}

bool Line::operator==(const Line& another) const {
	return a * another.b == another.a * b
		&& a * another.c == another.a * c
		&& b * another.c == another.b * c;
}

bool Line::operator!=(const Line& another) const {
	return !(*this == another);
}

// https://matworld.ru/analytic-geometry/proekcija-tochki-na-prjamuju.php
Point Line::getProjection(const Point& point) const {
	double m = vector.value().x, p = vector.value().y;
	double x = vector.end().x, y = vector.end().y;
	double t = (m * point.x + p * point.y - m * x - p * y) / (m*m + p*p);

	return Point(m * t + x, p * t + y);
}
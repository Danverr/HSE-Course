#pragma once
#include "point.h"
#include "vector.h"

class Point;

class Line {

public:

	Line(const Point& beg, const Point& end);
	Line(const Vector& vector);

	bool operator==(const Line& another) const;
	bool operator!=(const Line& another) const;

	Point getProjection(const Point& point) const;

private:

	double a, b, c;
	Vector vector;

};
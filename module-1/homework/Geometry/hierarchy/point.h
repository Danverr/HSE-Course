#pragma once
#include "geometry.h"

class Point {

public:

	double x, y;

	Point(const double&, const double&);

	bool operator==(const Point& another) const;
	bool operator!=(const Point& another) const;
	Point operator+(const Point& another) const;
	Point operator-(const Point& another) const;
	Point operator*(const double& coef) const;
	Point operator/(const double& coef) const;
	Point& operator+=(const Point& another);
	Point& operator-=(const Point& another);
	Point& operator*=(const double& coef);
	Point& operator/=(const double& coef);
};

double dist(const Point& a, const Point& b);
double area(const Point& a, const Point& b, const Point& c);
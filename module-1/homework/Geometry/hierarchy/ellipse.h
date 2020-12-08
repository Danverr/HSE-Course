#pragma once
#include "shape.h"

class Ellipse : public Shape {

public:

	Ellipse(const Point& f1, const Point& f2, const double& dist);

	double perimeter() const override;
	double area() const override;
	bool operator==(const Shape& another) const override;
	bool isCongruentTo(const Shape& another) const override;
	bool isSimilarTo(const Shape& another) const override;
	bool containsPoint(const Point& point) const override;
	Shape& rotate(const Point& center, const double& angle) override;
	Shape& reflex(const Point& center) override;
	Shape& reflex(const Line& axis) override;
	Shape& scale(const Point& center, const double& coef) override;
		
	std::pair<Point, Point> focuses() const;
	std::pair<Line, Line> directrices() const;
	double eccentricity() const;
	Point center() const;	
	
protected:

	double c() const;
	double b() const;

	Point f1, f2;
	double a;

};
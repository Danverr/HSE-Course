#pragma once
#include "shape.h"
#include "circle.h"

class Polygon : public Shape {

public:

	Polygon(std::vector<Point> points);

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
	
	int verticesCount() const;
	std::vector<Point> getVertices() const;
	bool isConvex() const;
	

protected:

	std::vector<Point> points;
};
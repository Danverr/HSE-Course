#include "polygon.h"

Polygon::Polygon(std::vector<Point> points) : points(points) {}

double Polygon::perimeter() const {
	int perimeter = dist(points[0], points[points.size() - 1]);

	for (int i = 0; i + 1 < points.size(); i++) {
		perimeter += dist(points[i], points[i + 1]);
	}

	return perimeter;
}

double Polygon::area() const {
	double area = 0;

	for (int i = 1; i + 1 < points.size(); i++) {
		area += ::area(points[0], points[i], points[i + 1]);
	}

	return area;
}

bool Polygon::operator==(const Shape& another) const {
	int n = points.size();
	const auto* polygon = dynamic_cast<const Polygon*>(&another);

	// If shape is not a polygon OR shape dont have enough points
	if (polygon == nullptr || n != polygon->points.size()) {
		return false;
	}

	// this_shape_points[start] == another_shape_points[0]
	int start = std::find(points.begin(), points.end(), polygon->points[0]) - points.begin();

	// Index doesn`t exist
	if (start == n) {
		return false;
	}

	// Comparing points forward direction	
	for (int i = 0; i < n; i++) {
		if (points[(start + i + n) % n] != polygon->points[i]) {
			return false;
		}
	}

	return true;
}

bool Polygon::isCongruentTo(const Shape& another) const {
	int n = points.size();
	const auto* polygon = dynamic_cast<const Polygon*>(&another);

	// If shape is not a polygon OR shape dont have enough points
	if (polygon == nullptr || n != polygon->points.size()) {
		return false;
	}

	// Creating Vectors from points 
	std::vector<Vector> vectors, polygon_vectors;

	for (int i = 0; i < n; i++) {
		vectors.push_back(Vector(points[i], points[(i + 1) % n]));
		polygon_vectors.push_back(Vector(polygon->points[i], polygon->points[(i + 1) % n]));
	}

	// Comparing Vectors in forward direction
	for (int start = 0; start < n; start++) {
		bool areEqual = true;

		for (int i = 0; i < n; i++) {
			if (vectors[(start + i + n) % n] != polygon_vectors[i]) {
				areEqual = false;
				break;
			}
		}

		if (areEqual) {
			return true;
		}
	}

	return false;
}

bool Polygon::isSimilarTo(const Shape& another) const {
	int n = points.size();
	const auto* polygon = dynamic_cast<const Polygon*>(&another);

	// If shape is not a polygon OR shape dont have enough points
	if (polygon == nullptr || n != polygon->points.size()) {
		return false;
	}

	// Creating Vectors from points 
	std::vector<Vector> vectors, polygon_vectors;

	for (int i = 0; i < n; i++) {
		vectors.push_back(Vector(points[i], points[(i + 1) % n]));
		polygon_vectors.push_back(Vector(polygon->points[i], polygon->points[(i + 1) % n]));
	}

	// Comparing Vectors in forward direction
	for (int start = 0; start < n; start++) {
		bool areEqual = true;
		double coef = 0;

		for (int i = 0; i < n; i++) {
			double vec_len = vectors[(start + i + n) % n].length();
			double another_vec_len = polygon_vectors[i].length();

			if (coef == 0) {
				coef = vec_len / another_vec_len;
			}

			if (!equal(vec_len, another_vec_len * coef)) {
				areEqual = false;
				break;
			}
		}

		if (areEqual) {
			return true;
		}
	}

	return false;
}

// https://neerc.ifmo.ru/wiki/index.php?title=Принадлежность_точки_выпуклому_и_невыпуклому_многоугольникам
bool Polygon::containsPoint(const Point& point) const {
	int intersections = 0;

	for (int i = 0; i < points.size(); i++) {
		Point min_point = points[i], max_point = points[(i + 1) % points.size()];

		if (min_point.y > max_point.y) {
			std::swap(min_point, max_point);
		}

		if (max_point.y <= point.y || min_point.y > point.y) {
			continue;
		}

		// min_point.y <= point.y < max_point.y
		int orient = Vector(min_point, max_point).orientation(point);

		if (orient == 0) {
			return true;
		}
		else if (orient > 0) {
			intersections++;
		}
	}

	return intersections % 2;
}

Shape& Polygon::rotate(const Point& center, const double& angle) {
	for (int i = 0; i < points.size(); i++) {
		points[i] = Vector(center, points[i]).rotate(angle).end();
	}

	return *this;
}

Shape& Polygon::reflex(const Point& center) {
	for (int i = 0; i < points.size(); i++) {
		points[i] = (Vector(points[i], center) * 2).end();
	}

	return *this;
}

Shape& Polygon::reflex(const Line& axis) {
	for (int i = 0; i < points.size(); i++) {
		Point proj = axis.getProjection(points[i]);
		points[i] = (Vector(points[i], proj) * 2).end();
	}

	return *this;
}

Shape& Polygon::scale(const Point& center, const double& coef) {
	for (int i = 0; i < points.size(); i++) {
		points[i] = (Vector(center, points[i]) * coef).end();
	}

	return *this;
}

int Polygon::verticesCount() const {
	return points.size();
}

std::vector<Point> Polygon::getVertices() const {
	return points;
}

bool Polygon::isConvex() const {
	for (int i = 0; i < points.size(); i++) {
		Point a = points[i], b = points[(i + 1) % points.size()], c = points[(i + 2) % points.size()];

		if (Vector(a, b).isRight(c)) {
			return false;
		}
	}

	return true;
}
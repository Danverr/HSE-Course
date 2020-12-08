#pragma once
#include <vector>
#include <cmath>
#include <algorithm>

class Vector;
class Point;
class Line;
class Shape;
class Polygon;
class Ellipse;
class Circle;
class Rectangle;
class Square;
class Triangle;

const double EPS = 1e-6;
const double PI = 3.1415926;

double radToDeg(double rad);
double degToRad(double deg);
bool equal(double a, double b);
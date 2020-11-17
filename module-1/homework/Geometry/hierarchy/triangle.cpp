#include "triangle.h"

Triangle::Triangle(const Point& a, const Point& b, const Point& c)
    : Polygon({a, b, c}) {}

// https://www.fxyz.ru/формулы_по_геометрии/плоские_фигуры/вписанные_и_описанные_многоугольники/радиус_описанной_окружности/треугольника/
Circle Triangle::circumscribedCircle() const {
    double a = Vector(points[0], points[1]).length();
    double b = Vector(points[1], points[2]).length();
    double c = Vector(points[2], points[0]).length();
    double p = (a + b + c) / 2;
    double R = a * b * c / (4 * sqrt(p * (p - a) * (p - b) * (p - c)));

    auto temp = Vector((points[0] + points[1]) / 2, points[1]).rotate(-90);
    Point center = (temp * (R / temp.length())).end();

    return Circle(center, R);
}

// https://www.fxyz.ru/формулы_по_геометрии/плоские_фигуры/вписанные_и_описанные_многоугольники/радиус_вписанной_окружности/в_треугольник/
Circle Triangle::inscribedCircle() const {   
    double a = Vector(points[0], points[1]).length();
    double b = Vector(points[1], points[2]).length();
    double c = Vector(points[2], points[0]).length();
    double p = (a + b + c) / 2;
    double r = sqrt((p - a) * (p - b) * (p - c) / p);

    double ang = angle(Vector(points[0], points[1]), Vector(points[0], points[2]));
    Point center = Vector(points[0], points[1]).rotate(ang / 2).end();

    return Circle(center, r);
}
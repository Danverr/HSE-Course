#pragma once
#include "point.h"

class Vector{

public:    

    Vector(const Point& a, const Point& b);

    bool operator==(const Vector& another) const;
    bool operator!=(const Vector& another) const;
    Vector operator+(const Vector& another) const;
    Vector operator-(const Vector& another) const;
    Vector operator*(const double& coef) const;
    double operator*(const Vector& another) const;
    double operator^(const Vector& another) const;
    Vector operator/(const double& coef) const;
    Vector& operator+=(const Vector& another);
    Vector& operator-=(const Vector& another);
    Vector& operator*=(const double& coef);
    Vector& operator/=(const double& coef);
    
    double orientation(const Point& point) const;
    bool isLeft(const Point& point) const;
    bool isRight(const Point& point) const;

    Point end() const;
    Point beg() const;
    Point value() const;    
    double length() const;

    Vector& rotate(double angle);    

private:

    Point _beg, _end;

};

double angle(const Vector& a, const Vector& b);
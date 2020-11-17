#pragma once
#include "polygon.h"

class Triangle : public Polygon {

public:

    Triangle(const Point& a, const Point& b, const Point& c);

    Circle circumscribedCircle() const;
    Circle inscribedCircle() const;
    
};
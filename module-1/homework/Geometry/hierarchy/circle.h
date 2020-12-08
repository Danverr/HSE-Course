#pragma once
#include "ellipse.h"

class Circle : public Ellipse {

public:

    Circle(const Point& center, const double& r);

    double radius() const;
    
};
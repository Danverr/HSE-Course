#include "geometry.h"

double radToDeg(double rad){
    return rad * 180.0 / PI;
}

double degToRad(double deg){
    return deg * PI / 180.0;
}

bool equal(double a, double b){
    return fabs(a - b) <= EPS;
}
#pragma once
#ifndef TOWN_H_INCLUDED
#define TOWN_H_INCLUDED
#include "tsp.h"

struct Town
{
    float x, y, sx, sy;
    Town():x(0), y(0), sx(0), sy(0){}
    Town(float _x, float _y):x(_x), y(_y), sx(_x), sy(_y){}
    const float dist(const Town& rhs) const
    {
        float dx=x-rhs.x;
        float dy=y-rhs.y;
        return sqrt(dx*dx+dy*dy);
    }
};

#endif // TOWN_H_INCLUDED

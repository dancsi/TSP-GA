#pragma once
#ifndef OBJECTIVE_H_INCLUDED
#define OBJECTIVE_H_INCLUDED

#include "tsp.h"

float Objective(GAGenome& g);
extern int ntowns;
extern float** DISTANCE;

#endif // OBJECTIVE_H_INCLUDED

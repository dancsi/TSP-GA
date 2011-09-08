#pragma once
#ifndef MUTATOR_H_INCLUDED
#define MUTATOR_H_INCLUDED

#include "tsp.h"

int Mutator_2opt(GAGenome& g, float pmut);
int Mutator_old(GAGenome& g, float pmut);

#endif // MUTATOR_H_INCLUDED

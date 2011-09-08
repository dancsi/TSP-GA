#pragma once
#ifndef CROSSOVER_H_INCLUDED
#define CROSSOVER_H_INCLUDED

#include "tsp.h"

extern int ntowns;
int ERXover(const GAGenome& g1, const GAGenome& g2, GAGenome* c1, GAGenome* c2);
void ERXOneChild(const GAGenome& g1, const GAGenome& g2, GAGenome* c1);
int PMXover(const GAGenome& g1, const GAGenome& g2, GAGenome* c1, GAGenome* c2);


#endif // CROSSOVER_H_INCLUDED

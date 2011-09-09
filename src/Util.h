#pragma once
#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "tsp.h"

extern int ntowns;
void Initializer(GAGenome& g);
template <> int GAListGenome<int>::write(STD_OSTREAM & os) const;
bool isnum(char c);
float Comparator(const GAGenome& g1, const GAGenome& g2);
GABoolean Terminator(GAGeneticAlgorithm &g);

#endif // UTIL_H_INCLUDED

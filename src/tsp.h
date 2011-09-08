#ifndef TSP_H_INCLUDED
#define TSP_H_INCLUDED
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <limits>
#include <ga/GASStateGA.h>
#include <ga/GAListGenome.h>
#include <ga/garandom.h>
#include <ga/std_stream.h>
#include "Crossover.h"
#include "Mutator.h"
#include "Objective.h"
#include "Util.h"
#include "Town.h"
#include "Init.h"
#include "Graphics.h"

extern const char* TSP_FILE;
extern std::vector<Town> towns;
extern int ntowns;
extern float** DISTANCE;
extern int* CLOSEST;
extern int (*XOVER)(const GAGenome& , const GAGenome& , GAGenome* , GAGenome* );
extern GAPopulation& pop;
extern GAListGenome<int>* genome;
extern GASteadyStateGA* ga;
extern int seed;
extern std::ostream& dbg;

#endif // TSP_H_INCLUDED

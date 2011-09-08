#include "tsp.h"

//const int MAX_TOWNS = 50;
const char* TSP_FILE = "in.tsp";

std::vector<Town> towns;
int ntowns;
float** DISTANCE;
int* CLOSEST;

//int (*XOVER)(const GAGenome& , const GAGenome& , GAGenome* , GAGenome* ) = PMXover;       // (Partial Match Crossover)
int (*XOVER)(const GAGenome& , const GAGenome& , GAGenome* , GAGenome* ) = ERXover;       // (Edge Recombination Crossover)

int (*Mutator)(GAGenome& g, float pmut) = Mutator_2opt;

GAListGenome<int>* genome;
GASteadyStateGA* ga;
int seed;
std::ostream& dbg=std::cerr;
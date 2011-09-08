#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "tsp.h"
namespace Init
{
	void ReadTowns();
	void ConstructDistances();
	void GAStuff();
	void GenomeInitializer(GAGenome& _g);
}


#endif
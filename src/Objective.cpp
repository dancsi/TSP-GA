#include "Objective.h"


// Here are the genome operators that we want to use for this problem.
// Thanks to Jan Kees IJspeert for isolating an order-of-evaluation problem
// in the previous implementation of this function.
float Objective(GAGenome& g)
{
    GAListGenome<int> & genome = (GAListGenome<int> &)g;
    float dist = 0;
    if(genome.head())
        {
            for(int i=0; i<ntowns; i++)
                {
                    int xx = *genome.current();
                    int yy = *genome.next();
                    dist += DISTANCE[xx][yy];
                }
        }
    return dist;
}

#include "Objective.h"

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

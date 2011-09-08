#include "Mutator.h"

int Mutator_2opt(GAGenome& g, float pmut)
{
	if ((GARandomFloat() >= pmut) || (pmut <= 0)) return 0;
	GAListGenome<int>& child=(GAListGenome<int> &)g;
    GAListIter<int> cura(child), nexta(child);
	nexta.next();
	
	for(int i=0;i<ntowns;i++, cura.next(), nexta.next())
	{
		GAListIter<int> curb(child), nextb(child);
		nextb.next();
		
		for(int j=0;j<ntowns;j++, curb.next(), nextb.next())
		{
			if(DISTANCE[*cura.current()][*nexta.current()]+DISTANCE[*curb.current()][*nextb.current()]>
				DISTANCE[*cura.current()][*nextb.current()]+DISTANCE[*curb.current()][*nexta.current()])
			{
				std::swap(*nexta.current(), *nextb.current());
			}
		}
	}
	return 1;
}

int Mutator_old(GAGenome& g, float pmut)
{
    GAListGenome<int> &child=(GAListGenome<int> &)g;
    register int n, i;
    if ((GARandomFloat() >= pmut) || (pmut <= 0)) return 0;

    n = child.size();

    if (GARandomFloat()<0.5)
        {
            child.swap(GARandomInt(0,n-1),GARandomInt(0,n-1)); // swap only one time
        }
    else
        {
            int nNodes = GARandomInt(1,((int)(n/2-1)));       // displace nNodes
            child.warp(GARandomInt(0,n-1));                   // with or without
            GAList<int> TmpList;                              // inversion
            for(i=0; i<nNodes; i++)
                {
                    int *iptr = child.remove();
                    TmpList.insert(*iptr,GAListBASE::AFTER);
                    delete iptr;
                    child.next();
                }
            int invert;
            child.warp(GARandomInt(0,n-nNodes));
            invert = (GARandomFloat()<0.5) ? 0 : 1;
            if (invert) TmpList.head();
            else TmpList.tail();

            for(i=0; i<nNodes; i++)
                {
                    int *iptr = TmpList.remove();
                    child.insert(*iptr,GAListBASE::AFTER);
                    delete iptr;
                    if (invert) TmpList.prev();
                    else TmpList.next();
                }
        }
    child.head();		// set iterator to root node

    return (1);
}

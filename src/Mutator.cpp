#include "Mutator.h"

int Mutator(GAGenome& g, float pmut)
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

#include "Crossover.h"

int ERXover(const GAGenome& g1, const GAGenome& g2, GAGenome* c1, GAGenome* c2)
{
    int nc=0;
    if(c1)
        {
            ERXOneChild(g1,g2,c1);
            nc+=1;
        }
    if(c2)
        {
            ERXOneChild(g1,g2,c2);
            nc+=1;
        }
    return nc;
}

void ERXOneChild(const GAGenome& g1, const GAGenome& g2, GAGenome* c1)
{
    GAListGenome<int> &mate1=(GAListGenome<int> &)g1;
    GAListGenome<int> &mate2=(GAListGenome<int> &)g2;
    GAListGenome<int> &sis=(GAListGenome<int> &)*c1;

    int i,j,k,t1,t2,town;

    char **CM=new char*[ntowns],*visit=new char[ntowns];
    for(int i=0;i<ntowns;i++)
    {
        CM[i]=new char[ntowns];
        memset(CM[i], 0, ntowns*sizeof(char));
    }
    memset(visit, 0, ntowns*sizeof(char));

    while (sis.head()) sis.destroy();

    // create connection matrix
    mate1.head();
        for(j=0; j<ntowns; j++)
        {
            t1 = *mate1.current();
            t2 = *mate1.next();
            CM[t1][t2]=1;
            CM[t2][t1]=1;
        }
    mate2.head();
    for(j=0; j<ntowns; j++)
        {
            t1 = *mate2.current();
            t2 = *mate2.next();
            CM[t1][t2]=1;
            CM[t2][t1]=1;
        }

    // select 1st town randomly
    town=GARandomInt(0,ntowns-1);
    visit[town]=1;
    memset(CM[town], 0, ntowns*sizeof(char));
    sis.insert(town); // the head node

    GAList<int> PossFollowList;
    GAList<int> FollowersList[5];
    while (PossFollowList.head()) PossFollowList.destroy();
    for(k=0; k<5; k++)
        {
            while (FollowersList[k].head()) FollowersList[k].destroy();
        }

    // select the following town with the minimal no of next folling towns
    int nPoss,nFollow;
    for(i=1; i<ntowns; i++)
        {
            nPoss = 0;
            for(j=0; j<ntowns; j++)            // no of poss. following towns
                {
                    if (CM[j][town])
                        {
                            nPoss += 1;
                            PossFollowList.insert(j);
                        }
                }
            // nPoss = 0;
            if (nPoss == 0)
                {
                    do
                        {
                            town=GARandomInt(0,ntowns-1);
                        }
                    while (visit[town]);   // no follower
                    visit[town]=1;
                    memset(CM[town], 0, ntowns*sizeof(char));
                    sis.insert(town);
                }
            else
                {
                    PossFollowList.head();
                    for(j=0; j<nPoss; j++)
                        {
                            nFollow = 0;
                            town = (*PossFollowList.current());
                            for(k=0; k<ntowns; k++)
                                {
                                    if (CM[k][town]) nFollow++;
                                }
                            FollowersList[nFollow].insert(town);
                            PossFollowList.next();
                        }
                    k=0;
                    while (FollowersList[k].size() == 0) k++;
                    FollowersList[k].warp(GARandomInt(0,FollowersList[k].size()));
                    town = (*FollowersList[k].current());
                    visit[town]=1;
                    memset(CM[town], 0, ntowns*sizeof(char));
                    sis.insert(town);
                }
            while (PossFollowList.head()) PossFollowList.destroy();
            for(k=0; k<5; k++)
                {
                    while (FollowersList[k].head()) FollowersList[k].destroy();
                }
        }
    sis.head();         // set iterator to head of list
    //CLEANUP
    for(int i=0;i<ntowns;i++)
        delete[] CM[i];
    delete[] CM;
    delete[] visit;
}

int PMXover(const GAGenome& g1, const GAGenome& g2, GAGenome* c1, GAGenome* c2)
{
    GAListGenome<int> &mom=(GAListGenome<int> &)g1;
    GAListGenome<int> &dad=(GAListGenome<int> &)g2;

    int a = GARandomInt(0, mom.size());
    int b = GARandomInt(0, dad.size());
    int h;
    if (b<a)
        {
            h=a;
            a=b;
            b=h;
        }

    int* index;
    int i,j,nc=0;

    if(c1)
        {
            GAListGenome<int> &sis=(GAListGenome<int> &)*c1;
            sis.GAList<int>::copy(mom);
            GAListIter<int> diter(dad);
            index = diter.warp(a);
            for(i=a; i<b; i++, index=diter.next())
                {
                    if(*sis.head() == *index)
                        {
                            sis.swap(i,0);
                        }
                    else
                        {
                            for(j=1; (j<sis.size()) && (*sis.next() != *index); j++);
                            sis.swap(i,j);  // no op if j>size
                        }
                }
            sis.head();         // set iterator to head of list
            nc += 1;
        }
    if(c2)
        {
            GAListGenome<int> &sis=(GAListGenome<int> &)*c2;
            sis.GAList<int>::copy(mom);
            GAListIter<int> diter(dad);
            index = diter.warp(a);
            for(i=a; i<b; i++, index=diter.next())
                {
                    if(*sis.head() == *index)
                        {
                            sis.swap(i,0);
                        }
                    else
                        {
                            for(j=1; (j<sis.size()) && (*sis.next() != *index); j++);
                            sis.swap(i,j);  // no op if j>size
                        }
                }
            sis.head();         // set iterator to head of list
            nc += 1;
        }

    return nc;
}

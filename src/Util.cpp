#include "Util.h"


void Initializer(GAGenome& _g)
{
    GAListGenome<int> &g=(GAListGenome<int> &)_g;
    while(g.head()) g.destroy(); // destroy any pre-existing list
    bool* visited=new bool[ntowns];
    memset(visited, 0, ntowns*sizeof(bool));
    int start=GARandomInt(0, ntowns-1);
    g.insert(start);
    visited[start]=1;
    for(int j=1; j<ntowns; j++)
    {
        if(!visited[CLOSEST[start]])
        {
            start=CLOSEST[start];
        }
        else
        {
            float closestDist=std::numeric_limits<float>::max();
            int closest=0;
            for(int next=0; next<ntowns; next++)
            {
                if(DISTANCE[start][next]<=closestDist&&!visited[next])
                {
                    closestDist=DISTANCE[start][next];
                    closest=next;
                }
            }
            start=closest;
        }
        visited[start]=1;
        g.insert(start);
    }
    //GAPopulation p=ga->population();
    delete[] visited;
}


template <> int GAListGenome<int>::write(std::ostream & os) const
{
    int *cur, *head;
    GAListIter<int> tmpiter(*this);
    if((head=tmpiter.head()) != 0)
    {
        os << *head << " ";
        for(cur=tmpiter.next(); cur && cur != head; cur=tmpiter.next())
            os << *cur << " ";
    }

    return os.fail() ? 1 : 0;
}

bool isnum(char c)
{
    return c>='0'&&c<='9';
}


float Comparator(const GAGenome& g1, const GAGenome& g2)
{
    GAListGenome<int> &a = (GAListGenome<int> &)g1;
    GAListGenome<int> &b = (GAListGenome<int> &)g2;

    int i,j,t1,t2;
    float dist=ntowns;

    bool **CM1=new bool*[ntowns], **CM2=new bool*[ntowns];
    for(int i=0; i<ntowns; i++)
    {
        CM1[i]=new bool[ntowns];
        memset(CM1[i], 0, ntowns*sizeof(bool));
        CM2[i]=new bool[ntowns];
        memset(CM2[i], 0, ntowns*sizeof(bool));
    }

    // create connection matrix CM1
    a.head();
    for(i=0; i<ntowns; i++)
    {
        t1 = *a.current();
        t2 = *a.next();
        CM1[t1][t2]=1;
        CM1[t2][t1]=1;
    }
    // create connection matrix CM2
    b.head();
    for(i=0; i<ntowns; i++)
    {
        t1 = *b.current();
        t2 = *b.next();
        CM2[t1][t2]=1;
        CM2[t2][t1]=1;
    }
    //calc distance = how many edges are different
    for (i=0; i<ntowns; i++)
    {
        for (j=i; j<ntowns; j++)
        {
            if (CM1[i][j]&CM2[i][j]) dist--;
        }
    }
    for(int i=0; i<ntowns; i++)
    {
        delete[] CM1[i];
        delete[] CM2[i];
    }
    delete[] CM1;
    delete[] CM2;
    return (dist);
}

GABoolean Terminator(GAGeneticAlgorithm& g)
{
	if((BestLength!=0.0)&&((WorstLength/BestLength)<=1.00005||g.population().best()==g.population().worst()))
		return gaTrue;
	else return gaFalse;
}
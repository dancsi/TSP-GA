#include "Init.h"

namespace Init
{
	void ReadTowns()
	{
		ntowns=0;
		char c;
		while(!isnum(c=getchar()))
		{
			while((c=getchar())!='\n');
		}
		ungetc(c, stdin);
		int id;
		float x, y;

		while(scanf("%d", &id)&&!feof(stdin))
		{
			scanf("%f%f", &x, &y);
			ntowns++;
			towns.push_back(Town(x, y));
		}
	}
	void ConstructDistances()
	{
		DISTANCE=new float*[ntowns];
		CLOSEST=new int[ntowns];
		int closest=0;
		float closestDist;
		for(int i=0;i<ntowns;i++)
			DISTANCE[i]=new float[ntowns];
		for(int i=0; i<ntowns; i++)
		{
			closest=0; closestDist=std::numeric_limits<float>::max();
			for(int j=0;j<i;j++)
			{
				if(DISTANCE[i][j]<closestDist)
				{
					closestDist=DISTANCE[i][j];
					closest=j;
				}
			}
			DISTANCE[i][i]=0;
			for(int j=i+1; j<ntowns; j++)
			{
				DISTANCE[j][i]=DISTANCE[i][j]=towns[i].dist(towns[j]);
				if(DISTANCE[i][j]<closestDist)
				{
					closestDist=DISTANCE[i][j];
					closest=j;
				}
			}
			CLOSEST[i]=closest;
		}
	}
	void GAStuff()
	{
		genome = new GAListGenome<int>(Objective);
		genome->initializer(::Initializer);
		genome->mutator(::Mutator);
		genome->comparator(::Comparator);
		genome->crossover(XOVER);
		dbg<<"inicijalizovao genom\n";

		ga = new GASteadyStateGA(*genome);
		dbg<<"napravio ga\n";
		ga->minimize();
		ga->pReplacement(1.0);
		ga->populationSize(100);
		ga->nGenerations(100);
		ga->pMutation(0.1);
		ga->pCrossover(1.0);
		ga->pMutation(0.3);
		ga->terminator(Terminator);
		//ga->pConvergence(1);
		ga->selectScores(GAStatistics::AllScores);
		//ga->terminator(GAGeneticAlgorithm::TerminateUponPopConvergence);
		//ga.parameters(argc, argv);
		ga->initialize(seed);
		dbg<<"inicijalozovao GA\n";
	}

}

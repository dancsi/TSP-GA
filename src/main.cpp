#include "tsp.h"

int main(int argc, char *argv[])
{
    if(argc>1)
    {
        freopen(argv[1], "r", stdin);
    }
    else
    {
        freopen(TSP_FILE, "r", stdin);
    }

	Init::ReadTowns();
    dbg<<"ucitao "<<ntowns<<" gradova\n";

	Init::ConstructDistances();
    dbg<<"alocirao memoriju\n";

	Init::GAStuff();
    dbg<<"inicijalizovao GAStuff\n";
#ifndef BENCHMARK
	Graphics::Init(1366, 768);
	Graphics::Scale();
#endif
	static const GAPopulation& pop=ga->population();
    while(!ga->done())
    {
        ga->step();
		GAListGenome<int> & worst = (GAListGenome<int> &)pop.worst();
		GAListGenome<int> & best = (GAListGenome<int> &)pop.best();
#ifndef BENCHMARK
		Graphics::DrawTowns();
		glLineWidth(1);
		Graphics::DrawGenome(worst, 0, 0, 128);
		glLineWidth(2);
		Graphics::DrawGenome(best);
		SDL_GL_SwapBuffers();
#endif
		BestLength=0, WorstLength=0;
		if(best.head()&&worst.head())
		{
			for(int i=0; i<ntowns; i++)
			{
				int xb = *best.current();
				int xw = *worst.current();
				int yb = *best.next();
				int yw = *worst.next();
				BestLength+=DISTANCE[xb][yb];
				WorstLength+=DISTANCE[xw][yw];

			}
			//Graphics::ScreenDump("screenshot.tga", Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT);
		}
		float ratio = WorstLength/BestLength;
		dbg<<BestLength<<" <-> "<<WorstLength<<", ratio: "<<ratio<<'\n';
    }

    *genome = ga->statistics().bestIndividual();
	std::ofstream out("best.dat");
    std::cout << "najkraci put je " << genome->score() << "\n";
	out<<*genome<<": "<<genome->score();
    std::cout << "gradovi\n";
    std::cout << *genome << "\n\n";
	out.close();
    //std::cout << ga->statistics() << "\n";
#ifndef BENCHMARK
	bool running=true;
	while(running)
	{
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			if(e.type==SDL_MOUSEBUTTONUP)
				running=false;
		}
	}
#endif
    return 0;
}

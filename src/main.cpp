#include "tsp.h"

FILE* fout;

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
	
	Graphics::Init(1366, 768);
	Graphics::Scale();
	
	static const GAPopulation& pop=ga->population();
    while(!ga->done())
    {
        ga->step();
		
		Graphics::DrawTowns();
		glLineWidth(1);
		GAListGenome<int> & worst = (GAListGenome<int> &)pop.worst();
		Graphics::DrawGenome(worst, 80, 80, 80);
		glLineWidth(2);
		GAListGenome<int> & best = (GAListGenome<int> &)pop.best();
		Graphics::DrawGenome(best);
		SDL_GL_SwapBuffers();
		
		fout=fopen("best.dat", "w");
		float BestLength=0, WorstLength=0;
		if(best.head()&&worst.head())	
		{
			for(int i=0; i<ntowns; i++)
			{
				int xb = *best.current();
				int xw = *worst.current();
				fprintf(fout, "%d ", xb);
				int yb = *best.next();
				int yw = *worst.next();
				BestLength+=DISTANCE[xb][yb];
				WorstLength+=DISTANCE[xw][yw];
				
			}
			fprintf(fout, ": %f\n", BestLength);
			//Graphics::ScreenDump("screenshot.tga", Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT);
		}
		fclose(fout);
		float ratio = WorstLength/BestLength;
		dbg<<BestLength<<" <-> "<<WorstLength<<", ratio: "<<ratio<<'\n';
    }
	
    *genome = ga->statistics().bestIndividual();
    std::cout << "najkraci put je " << genome->score() << "\n";
    std::cout << "gradovi\n";
    std::cout << *genome << "\n\n";
    //std::cout << ga->statistics() << "\n";
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
	
    return 0;
}

#include "Graphics.h"

namespace Graphics
{
	float minx=std::numeric_limits<float>::max(), 
		miny=std::numeric_limits<float>::max(), 
		maxx=std::numeric_limits<float>::min(), 
		maxy=std::numeric_limits<float>::min();
	int SCREEN_WIDTH, SCREEN_HEIGHT;
	GLint displayList;
	
	void Init(int width, int height)
	{
		SCREEN_WIDTH=width, SCREEN_HEIGHT=height;
		// Initialize SDL
		SDL_Init( SDL_INIT_EVERYTHING );
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); 
		SDL_SetVideoMode( width, height, 32, SDL_OPENGL );
		glClearColor( 1, 1, 1, 0 );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glOrtho( 0, width, 0, height, -1, 1 );
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		//glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND|GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_LINE_SMOOTH);
		//glEnable(GL_POLYGON_SMOOTH);
		//glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapBuffers();
		displayList=glGenLists(1);
	}
	void Scale(bool b)
	{
		if(!b) return;
		for(int i=0;i<ntowns;i++)
		{
			if(towns[i].x<minx)
				minx=towns[i].x;
			if(towns[i].y<miny)
				miny=towns[i].y;
			if(towns[i].x>maxx)
				maxx=towns[i].x;
			if(towns[i].y>maxy)
				maxy=towns[i].y;
		}
		maxx-=minx;
		maxy-=miny;
		for(int i=0;i<ntowns;i++)
		{
			towns[i].sx-=minx;
			towns[i].sy-=miny;
			
			towns[i].sx/=maxx*1.2;
			towns[i].sy/=maxy*1.2;
			
			towns[i].sx*=SCREEN_WIDTH;
			towns[i].sy*=SCREEN_HEIGHT;
			
			towns[i].sx+=SCREEN_WIDTH*0.05;
			towns[i].sy+=SCREEN_HEIGHT*0.05;
		}
		glClear(GL_COLOR_BUFFER_BIT);
		glNewList(displayList, GL_COMPILE); 
			glColor3f(0, 0, 0);
			for(int i=0;i<ntowns;i++)
			{
				CircleFill(towns[i].sx, towns[i].sy, 5, 4);
			}
		glEndList();
	}
	void PushCircle(double _x, double _y,double _HRadius, int _vertices)
	{
		double angleStep = 2*PI/_vertices;
		for(int i=0; i < _vertices; i++)
		{
			glVertex2d( cos(i*angleStep)*_HRadius + _x, sin(i*angleStep)*_HRadius + _y);
		}
	}

	void CircleFill(double _x, double _y,double _HRadius, int _vertices)
	{
		glBegin(GL_TRIANGLE_FAN);
		glVertex2d( _x, _y);
		PushCircle(_x,_y,_HRadius,_vertices);
		glVertex2d( _HRadius + _x,0 + _y);
		glEnd();
	}
	void DrawTowns()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glCallList(displayList);
	}
	void DrawGenome(GAListGenome<int> & genome, GLubyte r, GLubyte g, GLubyte b)
	{
		glColor3ub(r, g, b);
		glBegin(GL_LINE_LOOP);
		if(genome.head())
        {
            for(int i=0; i<ntowns; i++)
                {
                    int xx = *genome.current();
                    int yy = *genome.next();
                    glVertex2f(towns[xx].sx, towns[xx].sy);
                }
        }
		glEnd();
	}
	void ScreenDump(char *destFile, short W, short H) 
	{ 
		FILE   *out = fopen(destFile, "w"); 
		char   *pixel_data = new char[3*W*H]; 
		short  TGAhead[] = {0, 2, 0, 0, 0, 0, W, H, 24}; 
		glReadBuffer(GL_FRONT); 
		glReadPixels(0, 0, W, H, GL_BGR, GL_UNSIGNED_BYTE, pixel_data); 
		fwrite(&TGAhead, sizeof(TGAhead), 1, out); 
		fwrite(pixel_data, 3*W*H, 1, out); fclose(out); 
		delete[] pixel_data;
	}
}

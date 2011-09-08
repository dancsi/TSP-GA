#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "tsp.h"

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#define PI 3.14159

namespace Graphics
{
	extern int SCREEN_WIDTH, SCREEN_HEIGHT;
	extern float minx, miny, maxx, maxy;
	void Init(int width, int height);
	void Scale(bool b=true);
	void DrawGenome(GAListGenome<int> & genome, GLubyte r=255, GLubyte g=255, GLubyte b=255);
	void DrawTowns();
	void CircleFill(double _x, double _y,double _HRadius, int _vertices);
	void PushCircle(double _x, double _y,double _HRadius, int _vertices);
	void ScreenDump(char *destFile, short W, short H) ;
}

#endif
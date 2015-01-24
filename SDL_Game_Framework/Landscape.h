// Corey Bradford - University of Bolton - 1202670

#pragma once
#include "WorldConst.h"

class Landscape{
private:
	Tile *m_tileData;

	int *m_tiles;

	SDL_Surface *m_landscape;
	SDL_Surface *m_tileSheet;
public:
	Landscape(int width, int height, int tileSize, int tiles[], Tile tileData[], SDL_Surface* tileSheet);
	Landscape(int width, int height, int tileSize);
	~Landscape(void);

	void createLandscape(int width, int height, int size);
	void newSurface(int width, int height, int tileSize);
	int* tiles();
	SDL_Surface* tileSheet();
	SDL_Surface* landscape();
};


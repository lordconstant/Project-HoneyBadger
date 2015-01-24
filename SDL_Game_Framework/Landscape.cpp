#include "Landscape.h"

Landscape::Landscape(int width, int height, int tileSize, int tiles[], Tile tileData[], SDL_Surface* tileSheet){
	m_tileData = tileData;
	m_tileSheet = tileSheet;
	m_tiles = tiles;

	createLandscape(width, height, tileSize);
}

Landscape::Landscape(int width, int height, int tileSize){
	m_tileData = NULL;
	m_tileSheet = NULL;
	m_tiles = NULL;

	newSurface(width, height, tileSize);
}
Landscape::~Landscape(void)
{
	if(m_tiles != NULL){
		delete[] m_tiles;
	}

	if(m_tileData != NULL){
		delete[] m_tileData;
	}
}

void Landscape::newSurface(int width, int height, int tileSize){
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif
	SDL_Surface *scr = SDL_GetVideoSurface();
	SDL_Surface *temp;
	temp = SDL_CreateRGBSurface(scr->flags, width * tileSize, height * tileSize, 32, rmask, gmask, bmask, amask);
	m_landscape = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	SDL_FillRect(m_landscape, NULL, SDL_MapRGB(m_landscape->format, 0, 150, 0));
}

void Landscape::createLandscape(int width, int height, int size){
	newSurface(width, height, size);
	SDL_Rect t_tile, t_place;
	t_tile.x = t_tile.y = t_place.x = t_place.y = 0;
	t_tile.w = t_tile.h = t_place.w = t_place.h = size;

	for(int i = 0; i < width * height; i++){
		t_tile.x = m_tileData[m_tiles[i]].X() * size;
		t_tile.y = m_tileData[m_tiles[i]].Y() * size;

		if(t_place.x >= width * size){
			t_place.x = 0;
			t_place.y += size;
		}
		SDL_BlitSurface(m_tileSheet, &t_tile, m_landscape, &t_place);
		t_place.x += size;
	}
}

int* Landscape::tiles(){
	return m_tiles;
}

SDL_Surface* Landscape::tileSheet(){
	return m_tileSheet;
}

SDL_Surface* Landscape::landscape(){
	return m_landscape;
}

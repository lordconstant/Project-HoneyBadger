// Corey Bradford - University of Bolton - 1202670

#pragma once
#include "WorldConst.h"
#include "Landscape.h"
#include "Zone.h"
#include "Chunk.h"

class WorldData{
private:
	int m_width, m_height, m_uniqTiles, m_tileSize, m_chunkSize, m_numChunks, m_numZones;
	int *m_tiles;

	SDL_Surface *m_landscape;
	SDL_Surface *m_tileSheet;
	Tile *m_tileData;
	Zone *m_zones;

public:
	WorldData(int width, int height, int uniqTiles, int tileSize, int chunkSize, int numChunks, int numZones, int tiles[], Tile tileData[], SDL_Surface* landscape, SDL_Surface* tileSheet, Zone zones[]);
	~WorldData();

	int width();
	int height();
	int uniqTiles();
	int tileSize();
	int chunkSize();
	int* tiles();
	int numChunks();
	int numZones();

	SDL_Surface* landscape();
	SDL_Surface* tileSheet();

	Tile* tileData();
	Zone* Zones();

	void newLandscape(SDL_Surface* landscape);

	void numChunks(int num);
	void Zones(Zone zone[], int numZone);
};

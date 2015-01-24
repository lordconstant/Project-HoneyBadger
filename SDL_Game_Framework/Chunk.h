// Corey Bradford - University of Bolton - 1202670

#pragma once

#include "Zone.h"
#include "Tile.h"

class Chunk{
private:
	int m_x, m_y;
	Zone* m_zones;
	Tile* m_solids;
public:
	Chunk(Zone* zones, Tile* solids);
	~Chunk(void);

	int X();
	int Y();

	void X(int xPos);
	void Y(int yPos);

	Tile* solidTiles(void);
	Zone* zones(void);
};


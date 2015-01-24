#include "Chunk.h"
#include <iostream>

Chunk::Chunk(Zone* zones, Tile* solids)
{
	m_solids = solids;
	m_zones = zones;
}


Chunk::~Chunk(void)
{
	if(m_solids != NULL){
		//delete m_solids;
	}

	if(m_zones != NULL){
		delete m_zones;
	}
}

int Chunk::X(){
	return m_x;
}

int Chunk::Y(){
	return m_y;
}

void Chunk::X(int xPos){
	m_x = xPos;
}

void Chunk::Y(int yPos){
	m_y = yPos;
}

Tile* Chunk::solidTiles(void)
{
	return m_solids;
}


Zone* Chunk::zones(void)
{
	return m_zones;
}

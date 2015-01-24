#include "Tile.h"

Tile::Tile(void){
	m_X = 0;
	m_Y = 0;
	m_tileID = m_biomeID = 0;
	m_colourFade = 0.0;
	m_canWeather = m_solid = false;
}

Tile::Tile(int x, int y){
	m_X = x;
	m_Y = y;
	m_tileID = m_biomeID = 0;
	m_colourFade = 0.0;
	m_canWeather = m_solid = false;
}

Tile::Tile(int x, int y, int tileID, int biomeID, float colourFade, bool canWeather, bool solid)
{
	m_X = x;
	m_Y = y;
	m_tileID = tileID;
	m_biomeID = biomeID;
	m_colourFade = colourFade;
	m_canWeather = canWeather;
	m_solid = solid;
}

Tile::~Tile(void){
}
	
int Tile::X(){
	return m_X;
}

int Tile::Y(){
	return m_Y;
}

int Tile::tileID(){
	return m_tileID;
}

int Tile::biomeID(){
	return m_biomeID;
}

float Tile::colourFade(){
	return m_colourFade;
}

bool Tile::Weather(){
	return m_canWeather;
}

bool Tile::solid(){
	return m_solid;
}
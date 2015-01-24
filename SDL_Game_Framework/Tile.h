// Corey Bradford - University of Bolton - 1202670

#pragma once
class Tile{
private:
	int m_X, m_Y, m_tileID, m_biomeID;
	float m_colourFade;
	bool m_canWeather, m_solid;
public:
	Tile(void);
	Tile(int x, int y);
	Tile(int x, int y, int tileID, int biomeID, float colourFade, bool canWeather, bool solid);
	~Tile(void);
	int X();
	int Y();
	int tileID();
	int biomeID();
	float colourFade();
	bool Weather();
	bool solid();
};
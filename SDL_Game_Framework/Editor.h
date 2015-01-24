// Corey Bradford - University of Bolton - 1202670

#pragma once
#include <vector>
#include "gamebase.h"
#include "WorldManager.h"
#include "Camera.h"
#include "GUI.h"

const int MENU_WIDTH = 64;

enum TOOL {TILE, ZONE};

class Editor : public GameBase{
private:
	int m_selTile;

	//variables used for frames per second counter
	DWORD curTime, elasTime, fpsa, fpsc, fpsl;

	//Used for getting tile from tilesheet and placing onto landscape
	SDL_Rect m_place, m_tile;

	Camera* m_mCam;

	//used for tile placement
	bool click;
	float m_brushSize;

	//Boxes for displaying information
	GUIBox *disFPS, *disBrushSize, *disBrush, *disTool, *disOut;

	GUIButton *b_tile, *b_zone, *b_addZone, *b_menu;
	GUIDropDown *selZone;
	int tool;

	//variables for zone editing
	SDL_Rect m_nZA;
	AWSprite* zoneDis;
	bool m_showZone;
	bool m_drawZone;
	bool m_editZone;

	vector<Zone*>* m_zones;
	vector<Npc*>* m_zoneNpc;

	int m_curZone;

public:
	Editor(void);
	~Editor(void);

	void fps();

	WorldData *world;
	
	//tile placement functions
	void redrawTile(int x, int y, int tile);
	void brush();

	void setup();
	void start();
	void logic();
	void draw();

	//zone editing functions
	void newZone();
	void curZone(int zone);
	void saveZone();
	void addNpc(bool agressive);

	//input event handlers
	void onMousePressed();
	void onMouseMoved();
	void onMouseReleased();
	void onKeyPressed();
	void onKeyReleased();
};
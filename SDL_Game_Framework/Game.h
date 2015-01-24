// Christopher Gough - University of Bolton

/*
	Edited by Corey Bradford
	- added chunk loading
	- added collision with solid tiles
	- added zones and collision with enemies in the zones
*/

#pragma once
#include "gamebase.h"
#include "WorldManager.h"
#include "ItemDesigner.h"
#include "QuestHandler.h"
#include "Camera.h"
#include "Player.h"
#include "Npc.h"
#include <vector>

class Chunk;

class Game :public GameBase{
	WorldData* world;
	Chunk* loadedChunks;
	Chunk* curChunk;

	bool space;

	Camera* cam;

	Player* player;

	GUIBox* cCoord;
	
	vector<QuestHandler*> QuestLog;

	bool inCombat;

	GUIBox* playerHealth, *playerMana, *enemyHealth;
public:
	Game(void);
	~Game(void);

	void setup();
	void start();
	void logic();
	void draw();

	void collision();

	void loadPlayer();
	void savePlayer();

	void onKeyPressed();
	void onKeyReleased();

	void combatLoop(Npc* enemy);
	void combatLogic(Npc* enemy);
	void combatDraw(Npc* enemy);

	SDL_Rect createRect(int x, int y, int w, int h);
};


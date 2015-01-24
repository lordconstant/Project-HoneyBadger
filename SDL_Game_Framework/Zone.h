// Corey Bradford - University of Bolton - 1202670

#pragma once
#include "SDL.h"
#include "Npc.h"

class Zone{
private:
	SDL_Rect m_area;
	Npc* m_npcs;
	int m_numNpcs;
	int x, y, h, w;
public:
	Zone(void);
	Zone(int numNpcs, Npc npc[], SDL_Rect area);
	~Zone(void);

	SDL_Rect area();
	Npc* npcs();
	int numNpcs();

	void npcs(Npc npc[], int numNpc);

	void update(int tarX, int tarY, int screenX, int screenY, bool inZone);
};


#pragma once
#include "quest.h"
class EscortQuest :public Quest{
	SDL_Rect m_loc;

public:
	EscortQuest();
	EscortQuest(string name, string desc, int reqLvl, int time, int gold, int exp, SDL_Rect loc, SDL_Rect giver, SDL_Rect area);
	~EscortQuest(void);

protected:
	void privUpdate();
};


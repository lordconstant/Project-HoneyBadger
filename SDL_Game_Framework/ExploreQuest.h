#pragma once
#include "quest.h"

class ExploreQuest :public Quest{
	vector<SDL_Rect>* m_areas;
public:
	ExploreQuest();
	ExploreQuest(string name, string desc, int reqLvl, int time, int gold, int exp, SDL_Rect giver, SDL_Rect area);
	~ExploreQuest(void);

	void setArea(SDL_Rect area);
protected:
	void privUpdate();
};


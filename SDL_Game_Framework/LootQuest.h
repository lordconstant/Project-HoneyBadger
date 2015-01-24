#pragma once
#include "quest.h"

class LootQuest :public Quest{
	vector<string>* m_loot;
	int m_lootNum, m_lootCount;
public:
	LootQuest(void);
	LootQuest(string name, string desc, int lootNum, int reqLvl, int time, int gold, int exp, string loot, SDL_Rect giver, SDL_Rect area);
	~LootQuest(void);

	bool addTarget(string name);

	bool checkQuest(string name);

protected:
	void privUpdate();
};


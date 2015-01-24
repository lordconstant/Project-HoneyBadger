#pragma once
#include "quest.h"

class KillQuest :public Quest{
	vector<string>* m_enemy;
	int m_killNum, m_killCount;

public:
	KillQuest();
	KillQuest(string name, string desc, int killNum, int reqLvl, int time, int gold, int exp, string enemy, SDL_Rect giver, SDL_Rect area);
	~KillQuest(void);

	bool addTarget(string name);
	bool checkQuest(string name);
protected:
	void privUpdate();
};


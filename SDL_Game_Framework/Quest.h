#pragma once
#include <iostream>
#include <string>
#include "SDL.h"
#include "ItemDesigner.h"
#include <vector>
#include "timer.h"

using namespace timer;
using namespace std;

class Quest{
	string m_name, m_desc;
	int m_reqLvl, m_time, m_exp, m_gold, m_x, m_y, m_rewNum;
	bool m_completed, m_accepted;
	SDL_Rect m_giver, m_area;
	vector<Item*>* m_item;
	ItemDesigner* m_iDesign;
	Timer* m_timer;

public:
	Quest(void);
	Quest(string name, string desc, int reqLvl, int time, int gold, int exp, SDL_Rect giver, SDL_Rect area);
	~Quest(void);

	void update();

	string getName();
	string getDesc();
	
	int getReqLvl();
	int getTime();
	int getGold();
	int getExp();
	int getRewNum();
	int getX();
	int getY();

	Item* getItem(int num);

	bool getCompleted();
	bool getAccepted();
	bool displayQuest(int lvl);
	bool addItem(Item* item);

	void setCompleted(bool complete);
	void setAccepted(bool accept);
	void setPos(int x, int y);
	void generateRewards(int lvl);

	virtual void setArea(SDL_Rect area);

	virtual bool addTarget(string name);
	virtual bool checkQuest(string name);

	SDL_Rect getGiver();
	SDL_Rect getArea();

protected:
	bool checkBounds(SDL_Rect bounds);
	bool checkDist(int x, int y);

	virtual void privUpdate() = 0;
};


// Christopher Gough - University of Bolton

/*
	Edited by Corey Bradford
	- added agression state
*/

#pragma once
#include "AWSprite.h"
#include "timer.h"

using namespace timer;

class Npc: public AWSprite{
	int m_faction, m_health, m_curHealth, m_minDamage, m_maxDamage, m_aSpeed, m_speed;
	int m_xLo, m_yLo, m_xHi, m_yHi;
	bool m_aggresive, m_down, m_up, m_left, m_right, m_dead;
	Timer* m_aTimer;
public:
	Npc();
	~Npc();

	void move(int targetX, int targetY);
	int dealDamage();
	int getCurHealth();
	int getMaxHealth();

	bool takeDamage(int dmg);

	void Bounds(int xLo, int yLo, int xHi, int yHi);

	void combatMode();
	void playMode();

	void combatUpdate(int targetX, int targetY);

	void aggressive(bool agro);
	bool aggressive();
	bool isDead();

	void kill(bool dead);
};
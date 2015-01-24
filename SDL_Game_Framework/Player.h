//Christopher Gough - University of Bolton

/*
	Edited by Corey Bradford
	- removed Camera system
	- added Bounds to keep the player within a set area
*/

#pragma once
#include "awsprite.h"
#include "ItemDesigner.h"
#include "PlayerDisplay.h"
#include "Inventory.h"
#include "timer.h"

const int ARMORSLOTS = 5;
const float STAMINAMULTIPLIER = 10;
const float INTELLECTMULTIPLIER = 25;
const float STRENGTHMULTIPLIER = 0.5f;

class Player: public AWSprite{
	bool m_right, m_left, m_up, m_down, grounded;
	bool xCol, yCol, wCol, hCol, m_invShow;
	int m_lvl, m_exp, m_reqExp, m_gold, m_speed, m_maxHealth, m_curHealth, m_maxMana, m_curMana;
	int m_xB, m_yB;
	int playX, playY;

	map<string, int> m_stats;

	float XslowRate, YslowRate;

	Item* m_wep;
	Item* m_armor[ARMORSLOTS];
	ItemDesigner* m_IDesign;

	PlayerDisplay* m_display;

	Inventory<Item>* m_inv;

	timer::Timer* m_dmgDispTimer;
	GUIBox* m_dmgDispBox;
	int m_dmgDispYOffset;
public:
	Player(void);
	~Player(void);

	void xBound(int x);
	void yBound(int y);

	bool l();
	bool u();
	bool r();
	bool d();
	bool showInv();
	void setShowInv(bool show);

	void setRight(bool right);
	void setLeft(bool left);
	void setUp(bool up);
	void setDown(bool down);
	void setExp(int exp);
	void setGold(int gold);

	bool collision(int x, int y, int w, int h);
	bool checkDist(int x, int y, float distance);

	void update();

	void equipWeapon(Item* wep);
	void equipArmor(Item* armor);
	void dropWeapon(Item* wep);
	void dropArmor(Item* armor);
	void updateStats();
	void combatMode();
	void playMode();
	void combatUpdate();
	void takeDamage(int dmg);
	void updateDisplay();

	int getMaxHealth();
	int getcurHealth();
	int getMaxMana();
	int getCurMana();
	int getLvl();
	int getExp();
	int getGold();
	int getReqExp();
	int dealDamage();

	int getStats(string name);

	PlayerDisplay* getDisplay();
	Item* getWeapon();
	Inventory<Item>* getInv();
	Item* getArmor(int armorItem);

	void renderCombat();
private:
};


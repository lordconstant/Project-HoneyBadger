// Christopher Gough - University of Bolton

#pragma once
#include "ItemDatabase.h"
#include "random.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum QUALITYEXT{WEAK, DULL, PATHETIC, SILLY, BENDY, HEROIC, SWIFT, SHARP, EPIC, GREAT, OLD, POWERFUL, MAJESTIC, UNIQUE, POINTLESS, GODLY, RANDOM, SANTA, DOLEY, QCOUNT};
enum POWEREXT{STORM, ZEPHYR, POWER, WINTER, NIGHT, ELEMENTS, ACCURACY, FIRE, ICE, EARTH, LIGHTNING, GODS, UNICORN, MOUNTAIN, STREAM, IMAGINATION, RAIDER, THIEF, MOON, JOKER, PCOUNT};
enum WEAPONTYPE{SWORD, MACE, BOW, STAFF, WAND, CROSSBOW, SPEAR, AXE, WTCOUNT};
enum ARMORTYPE{HANDS, FEET, HEAD, CHEST, LEGS, ATCOUNT};
enum CONSUMABLETYPE{BREAD, CHEESE, MILK, MANAPOT, HEALTHPOT, CAKE, ORANGE, APPLE, CHERRY, WATER, BEER, CTCOUNT};

class ItemDesigner{
	string name, iType, filePath;
	map<string, int> properties;
public:
	ItemDesigner(void);
	~ItemDesigner(void);

	Item* createRandom(int lvl);
	Item* createWeapon(int lvl);
	Item* createArmor(int lvl);
	Item* createConsumable(int lvl);

private:
	void setQuality(int quality, int lvl);
	string setPower(int power, int lvl);
};


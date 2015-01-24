#pragma once
#include "GUI.h"
#include "Item.h"
#include "Inventory.h"

const int EQPINT = 6;

class PlayerDisplay{
	GUIBox* bgBox, *playerImg, *expBar;
	GUIButton **invIcon, **eqpIcon;
	int m_size;
public:
	PlayerDisplay(int size, string file);
	~PlayerDisplay(void);

	void setIcon(int num, string file, int stackNum);
	void setEquipIcon(int num, string file);
	void setPlayerImage(string file);
	void clearIcon(int num);
	void update(Inventory<Item>* playerInv);
	void permUpdate(int maxExp, int exp);
};


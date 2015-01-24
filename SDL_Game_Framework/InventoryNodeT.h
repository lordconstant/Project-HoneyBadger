#pragma once

class InventoryT;

class InventoryNodeT{
	int m_id;
	int m_curStack;
	int m_maxStack;

	InventoryNodeT(int id, int curStack, int maxStack);
	~InventoryNodeT();

	friend InventoryT;
public:
	void setId(int id);

	//Lowers curStack to be equal to the new maxStack if needed
	void setMaxStack(int maxStack);

	//Adds as much as possible to the current stack
	void addToStack(int& amount);

	//Removes as much as possible from the current stack
	void removeFromStack(int& amount);

	int getId();
	int getCurStack();
	int getMaxStack();
};


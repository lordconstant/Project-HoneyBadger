#pragma once
#include "InventoryNodeT.h"
#include <vector>

class InventoryT{
	std::vector<InventoryNodeT*> m_itemNodes;
	int m_curSize, m_size;
	bool m_full;
public:
	InventoryT(int size);
	~InventoryT();

	//Adds a specified item with a max stack (current stack is assmued to be 1)
	//If maxStack is less than 1 it will be set to 1
	bool addItem(int id, int maxStack);
	//Same as above but with a specified stack size
	//if curStack is less than 1 it will fail
	bool addItem(int id, int& curStack, int maxStack);
	//Adds an existing inventoryNode (clones the node)
	bool addItem(InventoryNodeT* item);

	//Attemps to add an item at a specific node
	//Look at addItem for how it acts
	bool addItemAt(int id, int maxStack, int loc);
	bool addItemAt(int id, int& curStack, int maxStack, int loc);

	//Adds as much of another inventory into itself as possible
	bool addInventory(InventoryT* otherInv);

	//Checks to see if inventory contains specified item
	bool checkForItem(int id);

	//Gets first node for an item
	InventoryNodeT* getNodeOfItem(int id);

	//Gets the node specified, if it exists
	InventoryNodeT* getItemAtNode(int nodeNum);

	int getSize();

	//Attempts to resize the inventory (Will fail if the new size is less than the number of items)
	bool setSize(int size);

	//Removes as much of an item as possible
	//If amount is -1 it will wipe all of that item
	bool removeItem(int id, int amount = -1);
	//Completely removes an item from the location specified
	bool removeItemAt(int loc);
	//Removes node provided
	bool removeInvNode(InventoryNodeT* invNode);

	//Remove all items from inventory
	bool clearInv();

	//Sorts items by id using a bubble sort
	void sort();
};


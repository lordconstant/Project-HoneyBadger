#pragma once
#include "Item.h"
#include "Log.h"
#include <sstream>
#include <map>

class ItemDatabase{
	string m_databaseFile, m_propertiesFile;
	map<int, Item*> m_loadedItems;

	ItemDatabase(void);
public:
	static ItemDatabase& getInstance();
	~ItemDatabase(void);

	//Returns false if item is in the database
	bool addItemToDataBase(Item* newItem);

	//Returns NULL if item isn't in the database
	Item* getItem(int id, bool load = true);

	//Loads an item in for fast recall
	//Returns false if item doesnt exist
	bool loadItem(int id);
};


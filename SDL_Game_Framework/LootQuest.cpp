#include "LootQuest.h"


LootQuest::LootQuest(): Quest(){
	m_lootNum = m_lootCount = 0;
	m_loot = NULL;
}

LootQuest::LootQuest(string name, string desc, int lootNum, int reqLvl, int time, int gold, int exp, string loot, SDL_Rect giver, SDL_Rect area): Quest(name, desc, reqLvl, time, gold, exp, giver, area){
	m_lootNum = lootNum;
	m_lootCount = 0;
	
	m_loot = new vector<string>;
	m_loot->push_back(loot);
}

LootQuest::~LootQuest(){
	delete m_loot;
}
//Adds a new loot item by name
bool LootQuest::addTarget(string name){
	if(name == ""){
		return false;
	}

	if(m_loot == NULL){
		m_loot = new vector<string>;
	}

	for(int i = 0; i < m_loot->size(); i++){
		if(m_loot->at(i) == name){
			return true;
		}
	}

	m_loot->push_back(name);

	return true;
}
//Checks if the item that got picked up is a quest item
bool LootQuest::checkQuest(string name){
	if(m_loot == NULL){
		return false;
	}

	for(int i = 0; i < m_loot->size(); i++){
		if(m_loot->at(i) == name){
			m_lootCount++;
			return true;
		}
	}

	return false;
}
//Checks if you have looted enough of the item
void LootQuest::privUpdate(){
	if(m_lootCount >= m_lootNum){
		setCompleted(true);
	}
}
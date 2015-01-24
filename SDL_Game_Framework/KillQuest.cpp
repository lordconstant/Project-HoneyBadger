#include "KillQuest.h"


KillQuest::KillQuest():Quest(){
	m_killCount = m_killNum = 0;
	m_enemy = NULL;
}

KillQuest::KillQuest(string name, string desc, int killNum, int reqLvl, int time, int gold, int exp, string enemy, SDL_Rect giver, SDL_Rect area): Quest(name, desc, reqLvl, time, gold, exp, giver, area){
	m_killNum = killNum;
	m_killCount = 0;
	m_enemy = new vector<string>;
	m_enemy->push_back(enemy);
}

KillQuest::~KillQuest(void){
	delete m_enemy;
}
//Checks to see if you have killed all the enemies
void KillQuest::privUpdate(){
	if(m_killCount >= m_killNum){
		setCompleted(true);
	}
}
//Adds more enemies to kill by name
bool KillQuest::addTarget(string name){
	if(name == ""){
		return false;
	}

	if(m_enemy == NULL){
		m_enemy = new vector<string>;
	}

	for(int i = 0; i < m_enemy->size(); i++){
		if(m_enemy->at(i) == name){
			return true;
		}
	}

	m_enemy->push_back(name);

	return true;
}
//checks if the npc that died is part of the quest
bool KillQuest::checkQuest(string name){
	if(m_enemy == NULL){
		return false;
	}

	for(int i = 0; i < m_enemy->size(); i++){
		if(m_enemy->at(i) == name){
			m_killCount++;
			return true;
		}
	}

	return false;
}

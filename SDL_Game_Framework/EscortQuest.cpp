#include "EscortQuest.h"


EscortQuest::EscortQuest(void){
	m_loc = SDL_Rect();
}

EscortQuest::EscortQuest(string name, string desc, int reqLvl, int time, int gold, int exp, SDL_Rect loc, SDL_Rect giver, SDL_Rect area): Quest(name, desc, reqLvl, time, gold, exp ,giver, area){
	m_loc = loc;
}

EscortQuest::~EscortQuest(void){
}

//Checks if the quest has arrived at the location
void EscortQuest::privUpdate(){
	if(checkBounds(m_loc)){
		setCompleted(true);
	}
}
#include "ExploreQuest.h"


ExploreQuest::ExploreQuest(): Quest(){
	m_areas = NULL;
}

ExploreQuest::ExploreQuest(string name, string desc, int reqLvl, int time, int gold, int exp, SDL_Rect giver, SDL_Rect area): Quest(name, desc, reqLvl, time, gold, exp ,giver, area){
	m_areas = new vector<SDL_Rect>;
	m_areas->push_back(area);
}

ExploreQuest::~ExploreQuest(){
	delete m_areas;
}

//Deletes an area on exploration when there are 0 areas its complete
void ExploreQuest::privUpdate(){
	if(m_areas == NULL || m_areas->empty()){
		setCompleted(true);
	}

	for(int i = 0; i < m_areas->size(); i++){
		if(checkBounds(m_areas->at(i))){
			m_areas->erase(m_areas->begin()+i);
		}
	}
}
//Replaces the current setArea function to add more areas to the exploreQuest
void ExploreQuest::setArea(SDL_Rect area){
	if(m_areas == NULL){
		m_areas = new vector<SDL_Rect>;
	}

	m_areas->push_back(area);
}
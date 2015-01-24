#include "Zone.h"

Zone::Zone(void){
	m_numNpcs = 0;
	m_npcs = NULL;
	SDL_Rect temp;
	temp.x = temp.y = temp.h = temp.w = 0;
	m_area = temp;
}

Zone::Zone(int numNpcs, Npc npc[], SDL_Rect area){
	m_numNpcs = numNpcs;
	m_npcs = npc;
	m_area = area;
}

Zone::~Zone(void)
{
//	if (m_npcs != NULL){
//		delete m_npcs;
//	}
}

SDL_Rect Zone::area(){
	return m_area;
}

Npc* Zone::npcs(){
	return m_npcs;
}

int Zone::numNpcs(){
	return m_numNpcs;
}

void Zone::update(int tarX, int tarY, int screenX, int screenY, bool inZone){
	for (int i = 0; i < m_numNpcs; i++){
		if (!m_npcs[i].isDead()){
			if (inZone){
				if (m_npcs[i].aggressive()){
					m_npcs[i].move(tarX, tarY);
				}
			}
			else{
				m_npcs[i].move(m_npcs[i].get_x(), m_npcs[i].get_y());
			}
			m_npcs[i].update_everything(screenX, screenY);
		}
	}
}

void Zone::npcs(Npc npc[], int numNpc){
	if (m_npcs != NULL){
		delete[] m_npcs;
	}

	m_npcs = npc;
	m_numNpcs = numNpc;
}
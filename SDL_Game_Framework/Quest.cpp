#include "Quest.h"

Quest::Quest(void){
	m_name = m_desc = "";
	m_reqLvl = m_time = m_gold = m_exp = m_rewNum = 0;
	m_item = NULL;
	m_timer = NULL;
	m_giver = m_area = SDL_Rect();
	m_completed = m_accepted  = false;
}

Quest::Quest(string name, string desc, int reqLvl, int time, int gold, int exp, SDL_Rect giver, SDL_Rect area){
	m_name = name;
	m_desc = desc;
	m_reqLvl = reqLvl;
	m_time = time;
	m_gold = gold;
	m_exp = exp;
	m_giver = giver;
	m_area = area;
	m_completed = m_accepted  = false;
	m_item = NULL;
	m_timer = NULL;
	m_rewNum = 0;
}

Quest::~Quest(void){
}
//Checks if your time for the quest is over and updates the quest if your in the defined area
void Quest::update(){
	if(m_timer == NULL && m_time > 0){
		m_timer = new Timer;
	}

	if(m_timer != NULL && m_time > 0){
		if(m_time <= m_timer->getElapsedTime()){
			setAccepted(false);
		}
	}

	if(checkBounds(getArea())){
		privUpdate();
	}
}

string Quest::getName(){
	return m_name;
}

string Quest::getDesc(){
	return m_desc;
}
	
int Quest::getReqLvl(){
	return m_reqLvl;
}

int Quest::getTime(){
	return m_time;
}

int Quest::getGold(){
	return m_gold;
}

int Quest::getExp(){
	return m_exp;
}

int Quest::getRewNum(){
	return m_rewNum;
}

int Quest::getX(){
	return m_x;
}

int Quest::getY(){
	return m_y;
}

Item* Quest::getItem(int num){
	if(num < 0 || num >= m_item->size() || m_item->at(num) == NULL){
		return NULL;
	}

	return m_item->at(num);
}

bool Quest::getCompleted(){
	return m_completed;
}

bool Quest::getAccepted(){
	return m_accepted;
}
//Checks if you are allowed to display the quest
bool Quest::displayQuest(int lvl){
	if(checkDist(m_giver.x, m_giver.y)){
		if(m_reqLvl <= lvl){
			return true;
		}
	}

	return false;
}
//Adds a new reward item
bool Quest::addItem(Item* item){
	if(item == NULL){
		return false;
	}

	if(m_item == NULL){
		m_item = new vector<Item*>;
	}

	m_item->push_back(item);
	m_rewNum++;

	return true;
}

void Quest::setAccepted(bool accept){
	m_accepted = accept;
}

void Quest::setCompleted(bool complete){
	m_completed = complete;
}

void Quest::setArea(SDL_Rect area){
	m_area = area;
}

void Quest::setPos(int x, int y){
	m_x = x;
	m_y = y;
}
//Generate four random reward items
void Quest::generateRewards(int lvl){
	m_iDesign = new ItemDesigner;

	for (int i = 0; i < 4; i++){
		addItem(m_iDesign->createRandom(lvl));
	}
}

bool Quest::addTarget(string name){
	return false;
}

bool Quest::checkQuest(string name){
	return false;
}

SDL_Rect Quest::getGiver(){
	return m_giver;
}

SDL_Rect Quest::getArea(){
	return m_area;
}
//Checks if the quest is within the area
bool Quest::checkBounds(SDL_Rect area){
	if(m_x < area.x + area.w && m_x > area.x && m_y > area.y && m_y < area.y + area.h){
		return true;
	}else{
		return false;
	}
}
//checks the quests distance from the provided location
bool Quest::checkDist(int x, int y){
	int tempX, tempY, temp;

	if(x > m_x){
		tempX = x - m_x;
	}else{
		tempX = m_x - x;
	}

	if(y > m_y){
		tempY = y - m_y;
	}else{
		tempY = m_y - y;
	}

	temp = tempX + tempY;

	if(temp < 150){
		return true;
	}else{
		return false;
	}
}
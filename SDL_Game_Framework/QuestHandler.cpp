#include "QuestHandler.h"

QuestHandler::QuestHandler(Quest* quest, char* bgFile, char* acceptImg, char* declineImg){
	m_quest = quest;
	m_bgImg = GUI::addBox(1000, 300, bgFile, "images/quest_display_mask.png");
	m_options = new vector<GUIButton*>;
	m_options->push_back(NULL);
	m_options->push_back(NULL);

	setOption(acceptImg, 0);
	setOption(declineImg, 1);
	m_qIcon = new AWSprite("images/quesclimation_mark.png", 1, "images/quesclimation_mark_mask.png", true);
	m_qIcon->set_world_position(m_quest->getGiver().x, m_quest->getGiver().y);
	m_qIcon->set_transparent_colour(255, 255, 100);
	m_rewards = NULL;
	m_showQuest = false;
	m_endOptions = false;
	m_endQuest = false;
	m_rewardItem = NULL;
	m_iDesign = new ItemDesigner;
	m_white = new AWFont("vera_white.bmp", "vera.dat");
	setRewards();
}

QuestHandler::~QuestHandler(void){
	delete m_quest;
	m_quest = NULL;
	delete m_iDesign;
	m_iDesign = NULL;

	if (m_rewardItem != NULL){
		delete m_rewardItem;
		m_rewardItem = NULL;
	}

	if (m_rewards != NULL){
		delete m_rewards;
		m_rewards = NULL;
	}
}
//handles displaying the quest on the screen when right clicking the quest
void QuestHandler::update(Player* player, int worldX, int worldY){
	m_mouseState = SDL_GetMouseState(&m_mXpos, &m_mYpos);
	m_quest->setPos(player->get_x(), player->get_y());

	if(m_mouseState == SDL_BUTTON(SDL_BUTTON_RIGHT) && !m_quest->getAccepted()){
		if (m_mXpos < m_quest->getGiver().x + m_quest->getGiver().w && m_mXpos > m_quest->getGiver().x && m_mYpos > m_quest->getGiver().y && m_mYpos < m_quest->getGiver().y + m_quest->getGiver().h){
			if (m_quest->displayQuest(player->getLvl())){
				m_showQuest = true;
			}
		}
	}

	if(m_showQuest){
		displayQuest();

		if(!m_quest->displayQuest(player->getLvl())){
			m_showQuest = false;
		}
	}

	if(m_quest->getAccepted() && !m_quest->getCompleted()){
		m_quest->update();
	}else{
		m_qIcon->update_everything(worldX, worldY);
	}

	if(m_quest->getCompleted()){
		if(!m_endOptions){
			setOption("images/quest_complete.png", 0);
			m_endOptions = true;
		}

		displayRewards(player);
	}
}
//Controls the first quest screen that pops up
void QuestHandler::displayQuest(){
	m_bgImg->update();
	
	
	if(m_options->at(0)->update(SDL_BUTTON_LEFT)){
		m_quest->setAccepted(true);
		m_showQuest = false;
	}

	if(m_options->at(1)->update(SDL_BUTTON_LEFT)){
		m_quest->setAccepted(false);
		m_showQuest = false;
	}

	for (int i = 0; i < m_rewards->size(); i++){
		m_rewards->at(i)->update(SDL_BUTTON_LEFT);
	}

	m_white->print_string(m_quest->getName().c_str(), m_bgImg->getX() + 64, m_bgImg->getY() + 64);
	m_white->print_string(m_quest->getDesc().c_str(), m_bgImg->getX() + 64, m_bgImg->getY() + 96);
}
//Sets the option buttons at the bottom of the quest
void QuestHandler::setOption(char* file, int num){
	if(m_options->at(num) != NULL){
		delete m_options->at(num);
	}

	m_options->at(num) = GUI::addButton(m_bgImg->getX()+192, m_bgImg->getY()+360+(64*num), file);
}
//Sets the reward images for the quest
void QuestHandler::setRewards(){
	string fileName;

	if (m_rewards == NULL){
		m_rewards = new vector<GUIButton*>;
	}

	for (int i = 0; i < m_quest->getRewNum(); i++){
		fileName = "images/";
		fileName += m_quest->getItem(i)->getSubType();
		fileName += "_icon.png";

		char s[255];
		strcpy(s, fileName.c_str());
		m_rewards->push_back(GUI::addButton(m_bgImg->getX() + 72 + (80 * i), m_bgImg->getY() + 280, s));
	}
}
//Displays the completed quest screen, requires the user to pick a reward if there is one
bool QuestHandler::displayRewards(Player* player){
	m_bgImg->update();

	for (int i = 0; i < m_rewards->size(); i++){
		if (m_rewards->at(i)->update(SDL_BUTTON_LEFT)){
			if (m_rewardItem != NULL){
				 m_rewardItem = NULL;
			}

			m_rewardItem = m_quest->getItem(i);
		}
	}

	m_white->print_string(m_quest->getName().c_str(), m_bgImg->getX() + 64, m_bgImg->getY() + 64);
	m_white->print_string(m_quest->getDesc().c_str(), m_bgImg->getX() + 64, m_bgImg->getY() + 96);

	if(m_options->at(0)->update(SDL_BUTTON_LEFT)){
		if (m_rewards != NULL){
			if (m_rewardItem == NULL){
				return false;
			}else{
				giveRewards(player);
				player->updateDisplay();
			}
		}
		m_endQuest = true;
	}

	return true;
}

bool QuestHandler::getEndQuest(){
	return m_endQuest;
}
//gives the player the reward
void QuestHandler::giveRewards(Player* player){
	player->setExp(player->getExp()+m_quest->getExp());
	player->setGold(player->getGold() + m_quest->getGold());
	player->getInv()->addElement(m_rewardItem, 1);
}
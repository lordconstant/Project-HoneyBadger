#pragma once
#include "KillQuest.h"
#include "LootQuest.h"
#include "EscortQuest.h"
#include "ExploreQuest.h"
#include "AWFont.h"
#include "GUI.h"
#include "Player.h"

class QuestHandler{
	Quest* m_quest;
	GUIBox* m_bgImg;
	AWSprite* m_qIcon;
	vector<GUIButton*>* m_rewards, *m_options;
	int m_mouseState, m_mXpos, m_mYpos;
	bool m_showQuest, m_endOptions, m_endQuest;
	Item* m_rewardItem;
	ItemDesigner* m_iDesign;
	AWFont* m_white;
public:
	QuestHandler(Quest* quest, char* bgFile, char* acceptImg, char* declineImg);
	~QuestHandler(void);

	void update(Player* player, int worldX = 0, int worldY = 0);

	void displayQuest();

	bool displayRewards(Player* player);
	bool getEndQuest();

	void setRewards();

	void giveRewards(Player* player);

	void setOption(char* file, int num);
	Item* giveReward(int num);
};


#pragma once

#include "EscortQuest.h"
#include "UnitTest++.h"

TEST(EscortQuestTestClass){
	SDL_Rect giver;
	SDL_Rect area;
	SDL_Rect area2;

	giver.x = giver.y = giver.w = giver.h = 10;
	area.x = area.y = area.w = area.h = 20;
	area2.x = area2.y = area2.w = area2.h = 30;
	Quest* q = new EscortQuest("name", "description", 1, 2, 3, 4, area2, giver, area);

	CHECK_EQUAL(q->getName(), "name");
	CHECK_EQUAL(q->getDesc(), "description");
	CHECK_EQUAL(q->getReqLvl(), 1);
	CHECK_EQUAL(q->getTime(), 2);
	CHECK_EQUAL(q->getGold(), 3);
	CHECK_EQUAL(q->getExp(), 4);
	CHECK_EQUAL(q->getRewNum(), 0);

	q->setCompleted(true);
	CHECK_EQUAL(q->getCompleted(), true);

	q->setAccepted(true);
	CHECK_EQUAL(q->getAccepted(), true);

	q->setPos(10, 10);
	CHECK_EQUAL(q->getX(), 10);
	CHECK_EQUAL(q->getY(), 10);

	CHECK_EQUAL(q->displayQuest(99), true);

	q->generateRewards(1);

	Item *i = q->getItem(0);
	CHECK(i != NULL);

	SDL_Rect t_giver = q->getGiver();
	SDL_Rect t_area = q->getArea();

	CHECK_EQUAL(t_giver.x, giver.x);
	CHECK_EQUAL(t_giver.y, giver.y);
	CHECK_EQUAL(t_giver.w, giver.w);
	CHECK_EQUAL(t_giver.h, giver.h);

	CHECK_EQUAL(t_area.x, area.x);
	CHECK_EQUAL(t_area.y, area.y);
	CHECK_EQUAL(t_area.w, area.w);
	CHECK_EQUAL(t_area.h, area.h);

	delete q;
	delete i;
}
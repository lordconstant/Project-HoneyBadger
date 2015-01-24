#pragma once

#include "Player.h"
#include "ItemDesigner.h"
#include "UnitTest++.h"

TEST(PlayerTestClass){
	Player* player = new Player;
	CHECK_EQUAL(true, player != NULL);

	ItemDesigner *i = new ItemDesigner;
	Item *w = i->createWeapon(6);

	player->setRight(true);
	CHECK(player->r());
	player->setRight(false);

	player->setLeft(true);
	CHECK(player->l());
	player->setLeft(false);

	player->setDown(true);
	CHECK(player->d());
	player->setDown(false);

	player->setUp(true);
	CHECK(player->u());
	player->setDown(false);

	player->set_world_position(5, 5);
	CHECK(player->collision(0, 0, 10, 10));

	player->setExp(10);
	CHECK_EQUAL(player->getExp(), 10);

	player->setGold(10);
	CHECK_EQUAL(player->getGold(), 10);

	CHECK_EQUAL(player->collision(0, 0, 10, 10), true);
	CHECK_EQUAL(player->checkDist(5, 5, 150), true);


	player->equipWeapon(w);
	CHECK_EQUAL(player->getWeapon(), w);

	CHECK(player->dealDamage() > 0);

	player->dropWeapon(w);
	CHECK(player->getWeapon() != NULL);

	CHECK(player->getMaxHealth() > 0);
	CHECK(player->getcurHealth() > 0);
	CHECK(player->getMaxMana() > 0);
	CHECK(player->getCurMana() > 0);
	CHECK(player->getLvl() > 0);
	CHECK(player->getReqExp() > 0);

	PlayerDisplay *d = player->getDisplay();
	CHECK(d != NULL);

	Inventory<Item> *inv = player->getInv();
	CHECK(inv != NULL);

	delete d;
	delete i;
	delete player;
}
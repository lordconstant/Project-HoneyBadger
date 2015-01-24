#pragma once

#include "Npc.h"
#include "UnitTest++.h"

TEST(NpcTestClass){
	Npc *n = new Npc;

	CHECK(n->dealDamage() >= 0);
	CHECK(n->getCurHealth() > 0);
	CHECK(n->getMaxHealth() >= n->getCurHealth());

	int d = n->getCurHealth();
	n->takeDamage(10);
	CHECK_EQUAL(n->getCurHealth(), d - 10);

	n->aggressive(true);
	CHECK_EQUAL(n->aggressive(), true);

	n->kill(true);
	CHECK_EQUAL(n->isDead(), true);

	delete n;
}
#pragma once

#include "UnitTest++.h"
#include "Item.h"

TEST(ItemTestClass){
	Item i("images/sword_icon.png", "Item", "weapon", "sword", 1, 2, 3, 4, 5, 6, 7, 8);

	CHECK_EQUAL(i.getName(), "Item");
	CHECK_EQUAL(i.getValue(), 1);
	CHECK_EQUAL(i.getStamina(), 2);
	CHECK_EQUAL(i.getAgility(), 3);
	CHECK_EQUAL(i.getStrength(), 4);
	CHECK_EQUAL(i.getIntellect(), 5);
	CHECK_EQUAL(i.getLuck(), 6);
	CHECK_EQUAL(i.getReqLvl(), 7);
	CHECK_EQUAL(i.getRarity(), 8);
}
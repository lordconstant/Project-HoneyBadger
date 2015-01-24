#pragma once

#include "UnitTest++.h"
#include "ItemDesigner.h"

TEST(ItemDesignerTestClass){
	ItemDesigner d;

	CHECK(d.createArmor(5));
	CHECK(d.createConsumable(5));
	CHECK(d.createWeapon(5));
}
#pragma once

#include "UnitTest++.h"
#include "Zone.h"

TEST(ZoneTestClass){
	Zone* newZone = new Zone();

	CHECK(newZone->area().h >= 0);
	CHECK(newZone->area().w >= 0);
	CHECK(newZone->area().x >= 0);
	CHECK(newZone->area().y >= 0);
	CHECK(newZone->npcs() == NULL);
	CHECK(newZone->numNpcs() >= 0);

	delete newZone;
}
#pragma once

#include "UnitTest++.h"
#include "Landscape.h"

TEST(LandscapeTestClass){
	Landscape* newLand = new Landscape(1, 1, 1);

	CHECK_EQUAL(1, newLand->landscape()->w);
	CHECK_EQUAL(1, newLand->landscape()->h);
	newLand->newSurface( 5, 5, 5);
	CHECK_EQUAL(25, newLand->landscape()->w);
	CHECK_EQUAL(25, newLand->landscape()->h);
	CHECK(newLand->tiles() >= 0);
	CHECK(newLand->tileSheet() == NULL);

	delete newLand;
}
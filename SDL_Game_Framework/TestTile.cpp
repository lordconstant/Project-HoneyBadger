#pragma once

#include "UnitTest++.h"
#include "Tile.h"

TEST(TileTestClass){
	Tile* newTile = new Tile(10, 10, 5, 4, 3, true, true);

	CHECK_EQUAL(4, newTile->biomeID());
	CHECK_EQUAL(3, newTile->colourFade());
	CHECK_EQUAL(10, newTile->X());
	CHECK_EQUAL(10, newTile->Y());
	CHECK_EQUAL(true, newTile->solid());
	CHECK_EQUAL(true, newTile->Weather());

	delete newTile;
}
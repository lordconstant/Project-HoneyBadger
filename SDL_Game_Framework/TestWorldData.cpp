#pragma once

#include "UnitTest++.h"
#include "WorldManager.h"

TEST(WorldDataTestClass){
	WorldData* newWorld = WorldManager::loadWorld(1);

	CHECK(newWorld->chunkSize() > 0);
	CHECK(newWorld->height() > 0);
	CHECK(newWorld->landscape() != NULL);
	CHECK(newWorld->numChunks() > 0);
	CHECK(newWorld->numZones() > 0);
	CHECK(newWorld->tileData() != NULL);
	CHECK(newWorld->tiles() > 0);
	CHECK(newWorld->tileSheet() != NULL);
	CHECK(newWorld->tileSize() > 0);
	CHECK(newWorld->uniqTiles() > 0);
	CHECK(newWorld->width() > 0);
	CHECK(newWorld->Zones() != NULL);

	delete newWorld;
}
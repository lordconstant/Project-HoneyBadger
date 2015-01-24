#pragma once

#include "UnitTest++.h"
#include "WorldManager.h"

TEST(WorldManagerTestClass){
	CHECK(WorldManager::loadChunk(1, 0, 0, 1, 1) != NULL);
	CHECK(WorldManager::loadWorld(1) != NULL);
	CHECK(WorldManager::saveWorld(1, WorldManager::loadWorld(1)) == true);
	CHECK(WorldManager::worldExists(1) == true);
}
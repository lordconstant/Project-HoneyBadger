// Corey Bradford - University of Bolton - 1202670

#pragma once
#include "WorldData.h"
#include <direct.h>

// This class provides functionality for loading and saving a game world

static class WorldManager{
private:
	WorldManager();

	static Tile* loadTile(int worldID, int tiles);
	static Landscape* loadLandscape(int worldID, int width, int height, int tileSize, Tile tileData[]);

	static void saveTile(int worldID, Tile* tiles, int uniqTiles);
	static void saveLandscape(int worldID, WorldData* data);
	static void saveChunks(int worldID, WorldData* data);
	static void saveZone(int worldID, Zone* zones, int numZones);
	static Zone* loadZone(int worldID, int zoneID, int tSize);
public:

	~WorldManager(void);

	static bool worldExists(int worldID);

	static WorldData* loadWorld(int worldID);
	static WorldData* loadEditor(int worldID);
	static bool saveWorld(int worldID, WorldData* data);

	static Chunk* loadChunk(int worldID, int x, int y, int cSize, int tSize);
};
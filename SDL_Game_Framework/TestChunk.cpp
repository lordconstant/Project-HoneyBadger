#include "UnitTest++.h"
#include "Chunk.h"
#include "Tile.h"
#include "Zone.h"

TEST(ChunkTest){
	Tile* newTile = new Tile();
	Zone* newZone = new Zone();
	Chunk* newChunk = new Chunk(newZone, newTile);

	newChunk->X(1);
	CHECK_EQUAL(1, newChunk->X());
	newChunk->Y(1);
	CHECK_EQUAL(1, newChunk->Y());
	CHECK_EQUAL(newTile, newChunk->solidTiles());
	CHECK_EQUAL(newZone, newChunk->zones());

	delete newChunk;
}
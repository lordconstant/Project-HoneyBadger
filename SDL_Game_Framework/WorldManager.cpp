#include "WorldManager.h"
using namespace std;

WorldManager::WorldManager(void)
{
}

WorldManager::~WorldManager(void)
{
}

bool WorldManager::worldExists(int worldID){
	char s[50];
	sprintf_s(s, "map/world %i/map.dat", worldID);
	string worldDir = s;
	ifstream data(worldDir);
	if(data){
		data.close();
		return true;
	}
	else{
		data.close();
		return false;
	}
}

WorldData* WorldManager::loadWorld(int worldID){

	int t_width, t_height, t_uniqTiles, t_tileSize,  t_chunkSize, t_numChunks, t_numZones;
	char s[50];
	sprintf_s(s, "map/world %i/map.dat", worldID);
	string worldDir = s;
	ifstream data(worldDir);

	if(!data){
		data.close();
		return NULL;
	}

	data >> t_width;
	data >> t_height;
	data >> t_uniqTiles;
	data >> t_tileSize;
	data >> t_chunkSize;
	data >> t_numChunks;
	data >> t_numZones;

	data.close();

	Tile *t_tiles = loadTile(worldID, t_uniqTiles);
	Landscape *t_landscape = loadLandscape(worldID, t_width, t_height, t_tileSize, t_tiles);
	Zone* t_zones;
	t_zones = new Zone[t_numZones];
	for (int i = 0; i < t_numZones; i++){
		t_zones[i] = *loadZone(worldID, i, t_tileSize);
	}

	WorldData *world = new WorldData(t_width, t_height, t_uniqTiles, t_tileSize, t_chunkSize, t_numChunks, t_numZones, t_landscape->tiles(), t_tiles, t_landscape->landscape(), t_landscape->tileSheet(), t_zones);

	return world;
}

Tile* WorldManager::loadTile(int worldID, int tiles){
	int t_X, t_Y, t_tileID, t_biomeID;
	float t_colourFade;
	bool t_canWeather, t_solid;

	Tile *t_tiles = new Tile[tiles];
	
	char s[50];
	sprintf_s(s, "map/world %i/tile.dat", worldID);
	string worldDir = s;
	ifstream data(worldDir);

	for(int i = 0; i < tiles; i++){
		data >> t_X;
		data >> t_Y;
		data >> t_tileID;
		data >> t_biomeID;
		data >> t_colourFade;
		data >> t_canWeather;
		data >> t_solid;
		Tile *t_tile = new Tile(t_X, t_Y, t_tileID, t_biomeID, t_colourFade, t_canWeather, t_solid);
		t_tiles[i] = *t_tile;
	}

	data.close();

	return t_tiles;
}

Landscape* WorldManager::loadLandscape(int worldID, int width, int height, int tileSize, Tile tileData[]){
	char s[50];
	sprintf_s(s, "map/world %i/map.map", worldID);
	string worldDir = s;
	ifstream data(worldDir);

	int *tiles = new int[width * height];
	for(int i = 0; i < width * height; i++){
		data >> tiles[i];
	}
	data.close();

	char t[50];
	sprintf_s(t, "map/world %i/tileSheet.png", worldID);

	SDL_Surface* t_tileSheet = IMG_Load(t);
	Landscape *t_landscape = new Landscape(width, height, tileSize, tiles, tileData, t_tileSheet);
	return t_landscape;
}

Chunk* WorldManager::loadChunk(int worldID, int x, int y, int cSize, int tSize){
	char s[50];
	sprintf_s(s, "map/world %i/chunks/chunk%i%i.map", worldID, x, y);
	string worldDir = s;
	ifstream data(worldDir);

	int solid;

	Tile* t_tiles = new Tile[100];
	for(int i = 0; i < cSize; i++){
		for(int j = 0; j < cSize; j++){
			data >> solid;
			if(solid == 1){
				t_tiles[j+(i * cSize)] = Tile(((x*cSize) + j) * tSize, ((y*cSize) + i) * tSize);
			}
			else{
				t_tiles[j+(i * cSize)] = Tile(0, 0);
			}
		}
	}
	Chunk* t_chunk = new Chunk(NULL, t_tiles);
	t_chunk->X(x);
	t_chunk->Y(y);
	return t_chunk;
}

Zone* WorldManager::loadZone(int worldID, int zoneID, int tSize){
	char s[50];
	sprintf_s(s, "map/world %i/zones/zone%i.dat", worldID, zoneID);
	string worldDir = s;
	fstream data(worldDir, ios::in);

	int t_ID, t_numNPC, t_x, t_y, t_w, t_h;

	data >> t_x;
	data >> t_y;
	data >> t_w;
	data >> t_h;
	data >> t_numNPC;

	data.close();

	sprintf_s(s, "map/world %i/zones/zone%inpc.dat", worldID, zoneID);
	worldDir = s;
	data.open(worldDir, ios::in);

	Npc *t_npcs = new Npc[t_numNPC];
	int t_nX, t_nY;
	bool t_agro;
	for (int i = 0; i < t_numNPC; i++){
		Npc *t_npc = new Npc;
		t_npcs[i] = *t_npc;
		data >> t_nX;
		data >> t_nY;
		data >> t_agro;

		t_npcs[i].set_world_position(t_nX, t_nY);
		t_npcs[i].Bounds(t_x*tSize, t_y*tSize, (t_x*tSize) + (t_w*tSize), (t_y*tSize) + (t_h*tSize));
		t_npcs[i].aggressive(t_agro);
	}
	data.close();

	SDL_Rect t_area;
	t_area.x = t_x;
	t_area.y = t_y;
	t_area.w = t_w;
	t_area.h = t_h;

	return new Zone(t_numNPC, t_npcs, t_area);
}

bool WorldManager::saveWorld(int worldID, WorldData* data){
	if(worldID == 0){
		return false;
	}
	char s[50];
	sprintf_s(s, "map/world %i", worldID);
	mkdir(s);
	sprintf_s(s, "map/world %i/map.dat", worldID);
	string worldDir = s;
	ofstream file(worldDir);

	data->numChunks((data->width() * data->height()) / data->chunkSize());

	file << data->width() << endl;
	file << data->height() << endl;
	file << data->uniqTiles() << endl;
	file << data->tileSize() << endl;
	file << data->chunkSize() << endl;
	file << data->numChunks() << endl;
	file << data->numZones() << endl;

	file.close();

	saveTile(worldID, data->tileData(), data->uniqTiles());
	saveLandscape(worldID, data);
	saveChunks(worldID, data);
	saveZone(worldID, data->Zones(), data->numZones());

	cout << "saved" << endl;

	return true;
}

void WorldManager::saveTile(int worldID, Tile* tiles, int uniqTiles){
	char s[50];
	sprintf_s(s, "map/world %i/tile.dat", worldID);
	string worldDir = s;
	ofstream data(worldDir);

	for(int i = 0; i < uniqTiles; i++){
		data << tiles[i].X() << " ";
		data << tiles[i].Y() << " ";
		data << tiles[i].tileID() << " ";
		data << tiles[i].biomeID() << " ";
		data << tiles[i].colourFade() << " ";
		data << tiles[i].Weather() << " ";
		data << tiles[i].solid() << " ";
		data << endl;
	}

	data.close();
}

void WorldManager::saveLandscape(int worldID, WorldData* data){
	char s[50];
	sprintf_s(s, "map/world %i/map.map", worldID);
	string worldDir = s;
	ofstream file(worldDir);

	int t_width = 0;
	for(int i = 0; i < data->width() * data->height(); i++){
		if(t_width >= data->width()){
			t_width = 0;
			file << endl;
		}
		if(data->tiles()[i] < 10){
			file << 0;
		}
		file << data->tiles()[i] << " ";
		t_width++;
	}
}

void WorldManager::saveChunks(int worldID, WorldData* data){
	char s[50];
	sprintf_s(s, "map/world %i/chunks", worldID);
	mkdir(s);
	for(int i = 0; i < data->height() / data->chunkSize(); i++){
		for(int j = 0; j < data->width() / data->chunkSize(); j++){
			char s[50];
			sprintf_s(s, "map/world %i/chunks/chunk%i%i.map", worldID, i, j);
			string worldDir = s;
			ofstream file(worldDir);
			for(int k = 0; k < data->chunkSize(); k++){
				for(int l = 0; l < data->chunkSize(); l++){
					file << data->tileData()[data->tiles()[(l + i*data->chunkSize())+((k + j*data->chunkSize()) * data->width())]].solid() << " ";
				}
				file << endl;
			}
			file.close();
		}
	}
}

void WorldManager::saveZone(int worldID, Zone* zones, int numZones){
	char s[50];
	sprintf_s(s, "map/world %i/zones", worldID);
	mkdir(s);

	for (int i = 0; i < numZones; i++){
		sprintf_s(s, "map/world %i/zones/zone%i.dat", worldID, i);
		string worldDir = s;
		fstream data(worldDir, ios::out);

		data << zones[i].area().x << endl;
		data << zones[i].area().y << endl;
		data << zones[i].area().w << endl;
		data << zones[i].area().h << endl;
		data << zones[i].numNpcs() << endl;

		data.close();
		
		sprintf_s(s, "map/world %i/zones/zone%inpc.dat", worldID, i);
		worldDir = s;
		data.open(worldDir, ios::out);
		for (int j = 0; j < zones[i].numNpcs(); j++){
			data << zones[i].npcs()[j].get_x() << " " << zones[i].npcs()[j].get_y() << " " << zones[i].npcs()[j].aggressive() << endl;
		}
		data.close();
	}
}
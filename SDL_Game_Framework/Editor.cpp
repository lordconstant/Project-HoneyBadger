#include "Editor.h"

Editor::Editor(void)
{
	//Displays a loading screen while Editor is initialised
	setBackground("images/loading_screen.png");
	SDL_BlitSurface(bg, NULL, screen, NULL);
	SDL_Flip(screen);

	m_selTile = 1;

	click = shiftPressed = false;
	m_showZone = m_drawZone = m_editZone = false;
	m_brushSize = 2;

	curTime = elasTime = fpsa = fpsc = fpsl = 0;
	m_nZA.x = m_nZA.y = m_nZA.w = m_nZA.h = 0;

	//initialisation of zone editing variables
	m_zones = new vector<Zone*>;
	m_zoneNpc = new vector<Npc*>;
	m_curZone = 0;

	tool = TILE;

	setup();
	start();
}

Editor::~Editor(void){
	delete world;

	delete disFPS;
	delete disBrushSize;
	delete disBrush;
	delete disTool;
	delete disOut;

	delete b_tile;
	delete b_zone;
	delete b_addZone;
	delete b_menu;

	delete selZone;

	delete zoneDis;

	m_zones->clear();
	delete m_zones;

	m_zoneNpc->clear();
	delete m_zoneNpc;

	delete m_mCam;
}

//This function calculates the frames per second that the editor runs at
void Editor::fps(){
	fpsc++;
	curTime = timeGetTime();
	elasTime = curTime - fpsl;

	//resets FPS variables every second
	if(elasTime > 1000){
		fpsa = fpsc;
		fpsc = 0;
		fpsl = curTime;
	}
}

void Editor::setup(){
	b_tile = GUI::addButton(screen->w - MENU_WIDTH / 2, 32, "images/sword_icon.png");
	b_zone = GUI::addButton(screen->w - MENU_WIDTH / 2, 96, "images/zoneEdit_icon.png");
	b_addZone = GUI::addButton(screen->w - MENU_WIDTH / 2, screen->h - 96, "images/zoneSave_icon.png");
	b_menu = GUI::addButton(32, screen->h - 16, "images/menu_icon.png");

	selZone = GUI::addDropDown(screen->w - MENU_WIDTH /2, 160, "images/zone_icon.png");

	m_mCam = new Camera(0, 0, screen->w - MENU_WIDTH, screen->h);
	m_mCam->bound(true, true, true, true);

	world = WorldManager::loadWorld(1);
	m_mCam->xBound(0, world->width() * world->tileSize());
	m_mCam->yBound(0, world->height() * world->tileSize());

	m_tile.x = m_tile.y = m_place.x = m_place.y = 0;
	m_tile.w = m_tile.h = m_place.w = m_place.h = world->tileSize();

	//Display boxes initialisation
	disBrush = GUI::addBox(80, 15, 150, 18, 0, 200, 0);
	disBrushSize = GUI::addBox(80, 40, 150, 18, 0, 200, 0);
	disFPS = GUI::addBox(80, 65, 150, 18, 200, 0, 0);
	disTool = GUI::addBox(screen->w / 2, 30, 50, 15, 225, 100, 0);
	disOut = GUI::addBox(screen->w / 2, 10, 300, 15, 225, 100, 0);

	zoneDis = new AWSprite(world->tileSize(), world->tileSize(), 0, 100, 200);
	zoneDis->set_surface_alpha(100);

	//Gets the zones from the world so they can be edited
	//Adds option for each zone to the zone selection button
	for (int i = 0; i < world->numZones(); i++){
		char *s = new char[50];
		m_zones->push_back(&world->Zones()[i]);
		sprintf(s, "Zone %i", i);

		selZone->addOption(s, 0, 100, 200);
		s = NULL;
	}

}

//The start function acts as a game loop
void Editor::start(){
	gameover = false;
	while(!gameover) {
		SDL_Delay(10);
		getUserInput();
		logic();
		SDL_BlitSurface(bg, NULL, screen, NULL);
		SDL_BlitSurface(world->landscape(), &m_mCam->cam(), screen, NULL);
		draw();
		SDL_Flip(screen);
		post();
	}
}

void Editor::logic(){
	fps();
	m_mCam->update();
}

void Editor::draw(){
	//Checks if the zones are to be displayed
	//Blits an image over every tile in the current zone
	//Displays the npcs in a zone
	if (m_showZone){
		for (int i = 0; i < m_nZA.w; i++){
			for (int j = 0; j < m_nZA.h; j++){
				m_place.x = ((m_nZA.x + i) * world->tileSize()) - m_mCam->x();
				m_place.y = ((m_nZA.y + j) * world->tileSize()) - m_mCam->y();

				SDL_BlitSurface(zoneDis->frames[0], NULL, screen, &m_place);
			}
		}
		for (int i = 0; i < m_zoneNpc->size(); i++){
			m_zoneNpc->at(i)->update_everything(m_mCam->x(), m_mCam->y());
		}
	}

	char s[50];
	sprintf_s(s, "Selected Tile : %i", m_selTile);
	disBrush->setText(s);
	disBrush->update();

	sprintf_s(s, "Brush Size : %i", (int)m_brushSize);
	disBrushSize->setText(s);
	disBrushSize->update();

	sprintf_s(s, "FPS : %i", fpsa);
	disFPS->setText(s);
	disFPS->update();

	if(b_tile->update(SDL_BUTTON_LEFT)){
		tool = TILE;
	}
	if(b_zone->update(SDL_BUTTON_LEFT)){
		m_editZone = false;
		m_curZone = -1;
		m_showZone = true;
		tool = ZONE;
	}
	if (b_zone->update(SDL_BUTTON_RIGHT)){
		m_showZone = !m_showZone;
	}


	if(tool == TILE){
		sprintf_s(s, "Tile");
	}
	else if(tool == ZONE){
		sprintf_s(s, "Zone");

		int i;
		i = selZone->update();
		if (i != -1){
			m_editZone = true;
			curZone(i);
		}

		if (b_addZone->update(SDL_BUTTON_LEFT)){
			newZone();
		}
	}
	disTool->setText(s);
	disTool->update();
	
	disOut->update();

	if (b_menu->update(SDL_BUTTON_LEFT)){
		screenNum = 0;
		gameover = true;
	}

	m_place.x = screen->w - MENU_WIDTH;
	m_place.y = 0;
	m_tile.x = world->tileData()[m_selTile].X() * world->tileSize();
	m_tile.y = world->tileData()[m_selTile].Y() * world->tileSize();
	SDL_BlitSurface(world->tileSheet(), &m_tile, screen, &m_place);
}

//Redraws a tile when it has been edited in the brush function
void Editor::redrawTile(int x, int y, int tile){
	m_place.x = x;
	m_place.y = y;

	m_tile.x = world->tileData()[tile].X() * world->tileSize();
	m_tile.y = world->tileData()[tile].Y() * world->tileSize();

	SDL_BlitSurface(world->tileSheet(), &m_tile, world->landscape(), &m_place);
}

//Calculates a circular brush and edits the tiles within that circle
void Editor::brush(){
	float t_cX = (pmouseX + m_mCam->x())/world->tileSize();
	float t_cY = (pmouseY + m_mCam->y())/world->tileSize();
	float t_X = t_cX - (m_brushSize +1)/2;
	float t_Y = t_cY - (m_brushSize +1)/2;

	double a = 0;
	double b = 0;

	//double loop for all the tiles in a square around the centre point
	for(int i = 0; i <= m_brushSize; i++){
		for(int j = 0; j <= m_brushSize; j++){
			if(t_X < 0 || t_Y < 0 || t_X >= world->width() || t_Y >= world->height()){
				t_X++;
				continue;
			}

			a = t_X - t_cX;
			b = t_Y - t_cY;

			if(a < 0){
				a = -a;
			}
			if(b < 0){
				b = -b;
			}
			//checks if the tile is within the radius of the brush
			//redraws the tile if it is
			if(m_brushSize/2 > sqrt((a*a)+(b*b))){
				int temp = (int)t_X + ((int)t_Y * world->width());
				world->tiles()[temp] = m_selTile;

				redrawTile((int)t_X * world->tileSize(), (int)t_Y * world->tileSize(), m_selTile);
			}
			t_X++;
		}
		t_X = t_cX - (m_brushSize +1)/2;
		t_Y++;
	}
}

//Creates a new zone if your not editing one
//Will overwrite the current zone if its being edited
void Editor::newZone(){
	if (!m_editZone){
		if (m_nZA.x == 0 && m_nZA.y == 0 && m_nZA.w == 0 && m_nZA.h == 0){
			disOut->setText("Invalid zone selection");
			return;
		}
		//A new zone is created and added to the zone vector
		//An option is added to the zone selction button
		Zone* t_zone = new Zone(0, NULL, m_nZA);
		m_zones->push_back(t_zone);
		char* s = new char[50];
		sprintf(s, "Zone %i", m_zones->size() - 1);
		selZone->addOption(s, 0, 100, 200);
		disOut->setText("Zone Created");
		m_curZone = m_zones->size() - 1;
		m_editZone = true;
	}
	else{
		Npc *t_npc = new Npc[m_zoneNpc->size()];
		int i = 0;
		for (vector<Npc*>::iterator it = m_zoneNpc->begin(); it != m_zoneNpc->end(); it++){
			t_npc[i] = **it;
			i++;
		}

		Zone* t_zone = new Zone(m_zoneNpc->size(), t_npc, m_nZA);
		m_zones->at(m_curZone) = t_zone;

		disOut->setText("Zone Overwritten");
	}
}

//Adds the new zones to the world data
void Editor::saveZone(){
	Zone* t_zones = new Zone[m_zones->size()];
	int i = 0;
	for (vector<Zone*>::iterator it = m_zones->begin(); it != m_zones->end(); it++){
		t_zones[i] = **it;
		i++;
	}
	world->Zones(t_zones, m_zones->size());
}

//Retrives the current zone data
void Editor::curZone(int zone){
	m_nZA = m_zones->at(zone)->area();

	m_zoneNpc->clear();
	for (int i = 0; i < m_zones->at(zone)->numNpcs(); i++){
		m_zoneNpc->push_back(&m_zones->at(zone)->npcs()[i]);
	}
	m_curZone = zone;
}

//Creates a new npc and adds it to the current zone data
void Editor::addNpc(bool agressive){
	if (mouseX + m_mCam->x() > m_nZA.x * world->tileSize() && mouseX + m_mCam->x() < (m_nZA.x* world->tileSize()) + (m_nZA.w * world->tileSize()) && mouseY + m_mCam->y() > m_nZA.y * world->tileSize() && mouseY + m_mCam->y() < (m_nZA.y * world->tileSize()) + (m_nZA.h * world->tileSize())){
		Npc *t_npc = new Npc;
		t_npc->set_world_position(((mouseX/ world->tileSize()) * world->tileSize()) + m_mCam->x(), ((mouseY / world->tileSize()) * world->tileSize()) + m_mCam->y());
		t_npc->aggressive(agressive);
		m_zoneNpc->push_back(t_npc);
		disOut->setText("Npc Created");
	}
	else{
		disOut->setText("Npc outside zone - not created");
	}
}

void Editor::onMousePressed(){
	switch (tool){
	case TILE:
		if (mouseButton == SDL_BUTTON_LEFT){
			if (mouseX < screen->w - 64){
				brush();
				click = true;
			}
		}
		if (mouseButton == SDL_BUTTON_WHEELUP){
			if (shiftPressed){
				if (m_selTile < world->uniqTiles() - 1){
					m_selTile++;
				}
			}
			else{
				m_brushSize++;
			}
		}
		if (mouseButton == SDL_BUTTON_WHEELDOWN){
			if (shiftPressed){
				if (m_selTile > 0){
					m_selTile--;
				}
			}
			else{
				if (m_brushSize > 1){
					m_brushSize--;
				}
			}
		}
		break;
	case ZONE:
		if(mouseButton == SDL_BUTTON_LEFT){
			if (mouseX < screen->w - 64){
				m_nZA.x = (mouseX + m_mCam->x()) / world->tileSize();
				m_nZA.y = (mouseY + m_mCam->y()) / world->tileSize();
				m_drawZone = true;
			}
		}
		if (mouseButton == SDL_BUTTON_RIGHT){
			if (mouseX < screen->w - 64){
				addNpc(true);
			}
		}
		if (mouseButton == SDL_BUTTON_MIDDLE){
			if (mouseX < screen->w - 64){
				addNpc(false);
			}
		}
		break;
	default:
		break;
	}
}

void Editor::onMouseMoved(){
	if(click){
		brush();
	}
	if (tool == ZONE && m_drawZone){
		if (mouseX < screen->w - 64){
			m_nZA.w = ((mouseX + m_mCam->x()) / world->tileSize()) - m_nZA.x;
			m_nZA.h = ((mouseY + m_mCam->y()) / world->tileSize()) - m_nZA.y;
		}
	}
}

void Editor::onMouseReleased(){
	switch(tool){
	case TILE:
		if(mouseButton == SDL_BUTTON_LEFT){
			click = false;
		}
		break;
	case ZONE:
		if(mouseButton == SDL_BUTTON_LEFT){
			if (mouseX < screen->w - 64){
				m_nZA.w = ((mouseX + m_mCam->x()) / world->tileSize()) - m_nZA.x;
				m_nZA.h = ((mouseY + m_mCam->y()) / world->tileSize()) - m_nZA.y;
				disOut->setText("Zone area defined");
				m_drawZone = false;
			}
		}
	}
}

void Editor::onKeyPressed(){
	switch(keyDown){
	case SDLK_a: m_mCam->l(true); break;
	case SDLK_d: m_mCam->r(true); break;
	case SDLK_w: m_mCam->u(true); break;
	case SDLK_s: m_mCam->d(true); break;
	case SDLK_p: saveZone(); WorldManager::saveWorld(1, world); disOut->setText("World Saved"); break;
	case SDLK_LSHIFT: shiftPressed = true; break;
	default: break;
	}
}

void Editor::onKeyReleased(){
	switch(keyUp){
	case SDLK_a: m_mCam->l(false); break;
	case SDLK_d: m_mCam->r(false); break;
	case SDLK_w: m_mCam->u(false); break;
	case SDLK_s: m_mCam->d(false); break;
	case SDLK_LSHIFT: shiftPressed = false; break;
	default: break;
	}
}

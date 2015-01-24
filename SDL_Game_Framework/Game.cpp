#include "Game.h"
#include "GUI.h"

Game::Game(void){
	setBackground("images/loading_screen.png");
	SDL_BlitSurface(bg, NULL, screen, NULL);
	SDL_Flip(screen);

	inCombat = false;

	setup();
}

Game::~Game(void){
	if (world){
		delete world;
	}

	if (loadedChunks){
		delete loadedChunks;
	}

	if (curChunk){
		delete curChunk;
	}

	if (cam){
		delete cam;
	}

	if (player){
		delete player;
	}

	if (cCoord){
		delete cCoord;
	}

	for (int i = 0; i < QuestLog.size(); ++i){
		delete QuestLog.at(i);
	}

	QuestLog.clear();

	if (playerHealth){
		delete playerHealth;
	}

	if (playerMana){
		delete playerMana;
	}

	if (enemyHealth){
		delete enemyHealth;
	}

}

void Game::setup(){
	world = WorldManager::loadWorld(1);

	loadedChunks = NULL;
	curChunk = NULL;
	enemyHealth = NULL;

	SDL_Rect giver, area, area2;
	giver.w = 64;
	giver.h = 64;
	giver.x = 320;
	giver.y = 320;

	area.w = 10000;
	area.h = 10000;
	area.x = 0;
	area.y = 0;

	area2.w = 2000;
	area2.h = 2000;
	area2.x = 1000;
	area2.y = 2000;

	cam = new Camera(0, 0, screen->w, screen->h);

	player = new Player();
	player->set_world_position(192, 128);
	player->xBound(world->width() * world->tileSize());
	player->yBound(world->height() *world->tileSize());
	curChunk = WorldManager::loadChunk(1, (player->get_x() / world->tileSize()) / world->chunkSize(), (player->get_y() / world->tileSize()) / world->chunkSize(), world->chunkSize(), world->tileSize());

	cam->speed(4);
	cam->bound(true, true, true, true);
	cam->xBound(0, world->width() * world->tileSize());
	cam->yBound(0, world->height() * world->tileSize());
	cam->follow(true);

	for (int i = 0; i < 1; i++){
		ExploreQuest* xQuest;
		xQuest = new ExploreQuest("Talking Bush", "hey psst ...|Word among the trees is that |there is treasure in the desert|if i had legs i would go investigate||Objective: explore the south |east desert", 1, 0, 100, 100, giver, area);
		xQuest->setArea(area2);
		xQuest->generateRewards(player->getLvl());

		QuestLog.push_back(new QuestHandler(xQuest, "images/quest_display.png", "images/quest_accept.png", "images/quest_decline.png"));

		xQuest = NULL;
	}

	cCoord = GUI::addBox(screen->w / 2, 30, 50, 15, 100, 100, 0);

	playerHealth = GUI::addBox(138, 26, "images/player_health_bar.png", "images/health_bar_mask.png");
	playerMana = GUI::addBox(400, 26, "images/player_mana_bar.png", "images/health_bar_mask.png");

	start();
}

void Game::start(){
	gameover = false;
	
	while(!gameover) {
		SDL_Delay(10);
		getUserInput();
		logic();
		SDL_BlitSurface(world->landscape(), &cam->cam(), screen, NULL);
		draw();
		SDL_Flip(screen);
		post();
	}
}

void Game::logic(){
	cam->follow(player->get_x() - (cam->w() / 2), player->get_y() - (cam->h() / 2));
	cam->update();
	player->update();
	
	for(int i = 0; i < world->chunkSize() * world->chunkSize(); i++){
		player->collision(curChunk->solidTiles()[i].X(), curChunk->solidTiles()[i].Y(), world->tileSize(), world->tileSize());
	}

	for (int i = 0; i < world->numZones(); i++){
		for (int j = 0; j < world->Zones()[i].numNpcs(); j++){
			if (!world->Zones()[i].npcs()[j].isDead()){
				if (world->Zones()[i].npcs()[j].get_x() < player->get_x() + player->get_width() && world->Zones()[i].npcs()[j].get_x() + world->Zones()[i].npcs()[j].get_width() > player->get_x()){
					if (world->Zones()[i].npcs()[j].get_y() < player->get_y() + player->get_height() && world->Zones()[i].npcs()[j].get_y() + world->Zones()[i].npcs()[j].get_height() > player->get_y()){
						if (world->Zones()[i].npcs()[j].aggressive()){
							combatLoop(&world->Zones()[i].npcs()[j]);
						}
					}
				}
			}
		}

	}
	
	if(player->get_x() + player->get_width() > (curChunk->X() +1)* (world->chunkSize() * world->tileSize())){
		delete curChunk;
		curChunk = WorldManager::loadChunk(1, ((player->get_x() + player->get_width())/ world->tileSize())/ world->chunkSize(), (player->get_y() / world->tileSize())/ world->chunkSize(), world->chunkSize(), world->tileSize());
	}
	else if(player->get_x() < curChunk->X() * world->chunkSize() * world->tileSize()){
		delete curChunk;
		curChunk = WorldManager::loadChunk(1, (player->get_x() / world->tileSize())/ world->chunkSize(), (player->get_y() / world->tileSize())/ world->chunkSize(), world->chunkSize(), world->tileSize());
	}
	else if(player->get_y() + player->get_height() > (curChunk->Y() +1) * (world->chunkSize() * world->tileSize())){
		delete curChunk;
		curChunk = WorldManager::loadChunk(1, (player->get_x() / world->tileSize())/ world->chunkSize(), ((player->get_y() + player->get_height()) / world->tileSize())/ world->chunkSize(), world->chunkSize(), world->tileSize());
	}
	else if(player->get_y() < curChunk->Y() * world->chunkSize() * world->tileSize()){
		delete curChunk;
		curChunk = WorldManager::loadChunk(1, (player->get_x() / world->tileSize())/ world->chunkSize(), (player->get_y() / world->tileSize())/ world->chunkSize(), world->chunkSize(), world->tileSize());
	}
}

void Game::collision(){

}

void Game::draw(){
	for (int i = 0; i < world->numZones(); i++){
		bool inZone = false;
		if (world->Zones()[i].area().x  * world->tileSize() < player->get_x() && (world->Zones()[i].area().x * world->tileSize()) + (world->Zones()[i].area().w * world->tileSize()) > player->get_x()
			&& world->Zones()[i].area().y * world->tileSize() < player->get_x() && (world->Zones()[i].area().y * world->tileSize()) + (world->Zones()[i].area().h * world->tileSize()) > player->get_y()){
				inZone = true;
		}
		else{
			inZone = false;
		}
		world->Zones()[i].update(player->get_x(), player->get_y(), cam->x(), cam->y(), inZone);
	}
	player->update_everything(cam->x(), cam->y());

	if(player->showInv()){
		player->getDisplay()->update(player->getInv());
	}

	for (int i = 0; i < QuestLog.size(); i++){
		if (QuestLog.at(i) != NULL){
			QuestLog.at(i)->update(player, cam->x(), cam->y());
		}

		if (QuestLog.at(i)->getEndQuest()){
			delete QuestLog.at(i);
			QuestLog.erase(QuestLog.begin()+i);
			i--;
		}
	}

	int hx, mx, gx;

	SDL_FillRect(screen, &createRect(15, 15, (246.f / player->getMaxHealth())*player->getcurHealth(), 22), 25600);
	playerHealth->update();

	SDL_FillRect(screen, &createRect(277, 15, (247.f / player->getMaxMana())*player->getCurMana(), 22), 51455);
	playerMana->update();

	hx = 105;
	hx = print(player->getcurHealth(), hx, 18, WHITE);
	hx = print("/", hx, 18, WHITE);
	print(player->getMaxHealth(), hx, 18, WHITE);

	mx = 365;
	mx = print(player->getCurMana(), mx, 18, WHITE);
	mx = print("/", mx, 18, WHITE);
	print(player->getMaxMana(), mx, 18, WHITE);

	gx = print("Gold ", 700, 10, WHITE);
	gx = print(player->getGold(), gx, 10, WHITE);
	gx = print("Lvl: ", gx + 10, 10, WHITE);
	gx = print(player->getLvl(), gx, 10, WHITE);
	gx = print("Exp", gx + 10, 10, WHITE);
	gx = print(player->getExp(), gx, 10, WHITE);
	gx = print("/", gx, 10, WHITE);
	gx = print(player->getReqExp(), gx, 10, WHITE);

	print(player->getWeapon()->getName(), 600, 700, WHITE);

	char s[50];
	sprintf_s(s, "%i, %i", (const int)((player->get_x() / world->tileSize())/ world->chunkSize()), (const int)((player->get_y() / world->tileSize())/ world->chunkSize()));
	cCoord->setText(s);
	cCoord->update();

	player->getDisplay()->permUpdate(player->getReqExp(), player->getExp());
}

void Game::onKeyPressed(){
	switch(keyDown){
	case SDLK_a: cam->l(true); player->setLeft(true); if(inCombat){ player->set_animation_subset(30, 35); } break;
	case SDLK_s: cam->d(true); player->setDown(true); break;
	case SDLK_w: cam->u(true); player->setUp(true); break;
	case SDLK_d: cam->r(true); player->setRight(true); if(inCombat){ player->set_animation_subset(6, 11);} break;
	//case SDLK_p: savePlayer(); break;
	//case SDLK_o: loadPlayer(); break;
	//player->update();
	}
}

void Game::onKeyReleased(){
	switch(keyUp){
	case SDLK_a: cam->l(false); player->setLeft(false); break;
	case SDLK_s: cam->d(false); player->setDown(false); break;
	case SDLK_w: cam->u(false); player->setUp(false); break;
	case SDLK_d: cam->r(false); player->setRight(false); break;
	case SDLK_i: player->setShowInv(!player->showInv()); break;
	case SDLK_b: screenNum = 0; gameover = true; break;
	case SDLK_SPACE: space = true; break;
//	case SDLK_c: if(!inCombat){combatLoop();} break;
	case SDLK_x: inCombat = false; break;
	}
}

void Game::combatLoop(Npc* enemy){
	inCombat = true;
	player->combatMode();
	enemy->combatMode();
	SDL_FreeSurface(bg);
	setBackground("images/dungeon_bg.png");

	//playerHealth = GUI::addBox(138, 26, "images/player_health_bar.png", "images/health_bar_mask.png");
	enemyHealth = GUI::addBox(screen->w-138, 26, "images/enemy_health_bar.png", "images/health_bar_mask.png");

	while(inCombat && !gameover){
		SDL_Delay(10);
		getUserInput();
		combatLogic(enemy);
		SDL_BlitSurface(bg, NULL, screen, NULL);
		combatDraw(enemy);
		SDL_Flip(screen);
		post();
	}

	delete enemyHealth;
	enemyHealth = NULL;

	player->playMode();
	enemy->playMode();
}

void Game::combatLogic(Npc* enemy){
	player->combatUpdate();
	player->getWeapon()->update_everything();

	if (player->checkDist(enemy->get_x(), enemy->get_y(), 150)){
		player->takeDamage(enemy->dealDamage());
	}

	if(player->checkDist(enemy->get_x(), enemy->get_y(), 150) && space == true){
		if(!enemy->takeDamage(player->dealDamage())){
			enemy->kill(true);
			inCombat = false;
		}
	}

	space = false;
}

void Game::combatDraw(Npc* enemy){
	enemy->update_everything();
	player->update_everything();

	SDL_FillRect(screen, &createRect(15, 15, (246.f/player->getMaxHealth())*player->getcurHealth(), 22), 25600);
	SDL_FillRect(screen, &createRect(screen->w-261, 15, (246.f/enemy->getMaxHealth())*enemy->getCurHealth(), 22), 13107200);

	playerHealth->update();
	enemyHealth->update();

	player->renderCombat();
}

void Game::savePlayer(){
	ofstream file("map/world 2/player.dat", ios::trunc);
	file.write((char*)cam, sizeof(Camera));
	file.close();
}

void Game::loadPlayer(){
	ifstream file("map/world 2/player.dat");
	file.read((char*)cam, sizeof(Camera));
	file.close();
}

SDL_Rect Game::createRect(int x, int y, int w, int h){
	SDL_Rect newRect;
	newRect.x = x;
	newRect.y = y;
	newRect.w = w;
	newRect.h = h;

	return newRect;
}
#include "Player.h"

Player::Player(void){
	m_IDesign = new ItemDesigner;
	m_right = m_left = m_up = m_down = false;
	xCol = yCol = hCol = wCol = false;
	setImage("images/wizard.png", 3, 3);
	set_transparent_colour(105, 107, 100);
	set_currentFrame(4);
	set_auto_move(5);
	m_speed = 2;
	m_xB = m_yB = 500;

	m_lvl = 1;
	m_exp = 0;
	m_gold = 100;
	m_reqExp = 500;

	m_wep = m_IDesign->createWeapon(m_lvl);
	Item* temp = m_IDesign->createConsumable(1);
	for(int i = 0; i < ARMORSLOTS; i ++){
		m_armor[i] = NULL;
	}

	for (int i = 0; i < ARMORSLOTS; ++i){
		equipArmor(m_IDesign->createArmor(m_lvl));
	}

	m_stats["stamina"] = m_stats["agility"] = m_stats["strength"] = m_stats["intellect"] = m_stats["luck"] = m_stats["defence"] = m_stats["magicResist"] = m_stats["minDamage"] = m_stats["maxDamage"] = m_stats["speed"] = 0;
	updateStats();

	m_curHealth = m_maxHealth;
	m_curMana = m_maxMana;

	m_display = new PlayerDisplay(15, "images/inventory.png");

	m_inv = new Inventory<Item>(15);
	m_inv->addElement(temp, 1);
	m_inv->addElement(temp, 1);
	m_inv->addElement(temp, 1);
	m_inv->addElement(temp, 1);

	m_display->setPlayerImage("images/player_portrait.png");
	updateDisplay();

	m_invShow = false;

	m_dmgDispTimer = new timer::Timer();
	m_dmgDispBox = NULL;
}

Player::~Player(void){
}

void Player::xBound(int x){
	m_xB = x;
}

void Player::yBound(int y){
	m_yB = y;
}

bool Player::l(){
	return m_left;
}

bool Player::u(){
	return m_up;
}

bool Player::r(){
	return m_right;
}

bool Player::d(){
	return m_down;
}

bool Player::showInv(){
	return m_invShow;
}

void Player::setShowInv(bool show){
	m_invShow = show;
}

void Player::setRight(bool right){
	m_right = right;
}

void Player::setLeft(bool left){
	m_left = left;
}

void Player::setUp(bool up){
	m_up = up;
}

void Player::setDown(bool down){
	m_down = down;
}

//Sets the players exp, if the current exp is high enough the player will level
//Any extra exp will be carried over to next level
void Player::setExp(int exp){
	m_exp = exp;

	bool leveled = false;

	while (m_exp >= m_reqExp){
		m_lvl++;
		m_exp -= m_reqExp;
		m_reqExp = (500 + m_reqExp/m_lvl) * m_lvl;
		
		leveled = true;
	}

	if (leveled){
		updateStats();

		m_curHealth = m_maxHealth;
		m_curMana = m_maxMana;
	}
}

void Player::setGold(int gold){
	m_gold = gold;
}
//Checks wether the player collides with an object
bool Player::collision(int x, int y, int w, int h){
	int pX, pY, pW, pH;
	int buffer = 1;

	pX = get_x() + buffer;
	pY = get_y() + buffer;
	pH = get_height() - buffer;
	pW = get_width() - buffer;

	if(pX > x + w +buffer){return false;}
	if(pY > y + h +buffer){return false;}
	if(pX + pW < x -buffer){return false;}
	if(pY + pH < y -buffer){return false;}

	if(pX <= x + w && pX > x + w - buffer){
		if(pY > y + buffer && pY < y + h - buffer || pY + pH > y && pY + pH < y + h - buffer || pY < y + buffer && pY + pH > y + h - buffer){
			m_left = false;
		}
	}
	if(pX + pW >= x && pX + pW < x + buffer){
		if(pY > y + buffer && pY < y + h - buffer|| pY + pH > y && pY + pH < y + h - buffer ||  pY < y + buffer && pY + pH > y + h - buffer){
			m_right = false;
		}
	}
	if(pY <= y + h && pY > y + h - buffer){
		if(pX > x + buffer && pX < x + w - buffer|| pX + pW > x && pX + pW < x + w - buffer || pX < x + buffer && pX + pW > y + h - buffer){
			m_up = false;
		}
	}
	if(pY + pH >= y && pY + pH < y + buffer){
		if(pX > x - buffer && pX < x + w - buffer|| pX + pW > x && pX + pW < x + w + buffer || pX < x + buffer && pX + pW > y + h - buffer){
			m_down = false;
		}
	}
	return true;

	/*int playerMinX, playerMinY;
	int playerMaxX, playerMaxY;
	int blockMinX, blockMinY;
	int blockMaxX, blockMaxY;

	playerMinX = get_x();
	playerMaxX = get_x() + get_width();
	playerMinY = get_y() - get_height();
	playerMaxY = get_y();*/
}

//Checks the players distance from an onject
bool Player::checkDist(int x, int y, float distance){
	int tempX, tempY, temp;

	if(x > get_x()){
		tempX = x - get_x();
	}else{
		tempX = get_x() - x;
	}

	if(y > get_y()){
		tempY = y - get_y();
	}else{
		tempY = get_y() - y;
	}

	temp = tempX + tempY;

	if(temp <= distance){
		return true;
	}else{
		return false;
	}
}

//Update the player moving it around the world
void Player::update(){
	if (m_right){
		if (get_x() < m_xB){
			XslowRate = m_speed;
			set_x_velocity(m_speed);
		}
	}

	if(m_left){
		if(get_x() > 0){
			XslowRate = m_speed;
			set_x_velocity(-m_speed);
		}
	}

	if(m_up){
		if(get_y() > 0){
			YslowRate = m_speed;
			set_y_velocity(-m_speed);
		}
	}

	if(m_down){
		if(get_y()+get_height() < m_yB){
			YslowRate = m_speed;
			set_y_velocity(m_speed);
		}
	}

	if(!m_left && !m_right){
		if(get_x_velocity() > 0){
			set_x_velocity(XslowRate);
			XslowRate -= m_speed/2;
		}
		else if(get_x_velocity() < 0){
			set_x_velocity(-XslowRate);
			XslowRate -= m_speed/2;
		}
	}

	if(!m_up && !m_down){
		if(get_y_velocity() > 0){
			set_y_velocity(YslowRate);
			YslowRate -= m_speed/2;
		}
		else if(get_y_velocity() < 0){
			set_y_velocity(-YslowRate);
			YslowRate -= m_speed/2;
		}
	}

	if(m_left && m_up){
		set_currentFrame(0);
	}else if(m_right && m_up){
		set_currentFrame(2);
	}else if(m_left && m_down){
		set_currentFrame(6);
	}else if(m_right && m_down){
		set_currentFrame(8);
	}else if(m_left){
		set_currentFrame(3);
	}else if(m_right){
		set_currentFrame(5);
	}else if(m_down){
		set_currentFrame(7);
	}else if(m_up){
		set_currentFrame(1);
	}
}

//Equip a weapon to the player
void Player::equipWeapon(Item* wep){
	if(m_wep != NULL){
		dropWeapon(m_wep);
		m_wep = NULL;
	}

	m_wep = wep;

	cout << "Equipped : " << m_wep->getName() << endl;

	updateStats();
}

//Equips armor to the player
void Player::equipArmor(Item* armor){
	if (!armor){
		return;
	}

	Item* curArmor = NULL;
	int armorSlot = 0;

	if (armor->getSubType() == "treads"){
		curArmor = m_armor[0];
		armorSlot = 0;
	}
	else if (armor->getSubType() == "gauntlets"){
		curArmor = m_armor[1];
		armorSlot = 1;
	}
	else if (armor->getSubType() == "helm"){
		curArmor = m_armor[2];
		armorSlot = 2;
	}
	else if (armor->getSubType() == "leggings"){
		curArmor = m_armor[3];
		armorSlot = 3;
	}
	else if (armor->getSubType() == "breastplate"){
		curArmor = m_armor[4];
		armorSlot = 4;
	}
	else{
		return;
	}

	if(curArmor){
		//dropArmor(curArmor);
		delete curArmor;
	}

	curArmor = NULL;

	m_armor[armorSlot] = armor;

	Log::getInstance().addLine("Equipped " + armor->getName() + " in slot - " + to_string(armorSlot));

	updateStats();
}

void Player::dropWeapon(Item* wep){
	delete wep;
}

void Player::dropArmor(Item* armor){
	delete armor;
}

//Updates the players stats relative to lvl, equipped weapon and armor
void Player::updateStats(){
	m_stats["stamina"] = m_lvl * 5; m_stats["agility"] = m_lvl * 3; 
	m_stats["strength"] = m_lvl * 3; m_stats["intellect"] = m_lvl * 3; 
	m_stats["luck"] = m_lvl * 2; m_stats["defence"] = m_lvl * 2; 
	m_stats["magicResist"] = m_lvl * 2; m_stats["minDamage"] = m_lvl * 5; 
	m_stats["maxDamage"] = (m_lvl * 5) + 5; m_stats["speed"] = 5;

	for(int i = 0; i < ARMORSLOTS; i++){
		if(m_armor[i] != NULL){
			for (auto itemProp : m_armor[i]->getProperties()){
				for (auto& myProp : m_stats){
					if (itemProp.first == myProp.first){
						myProp.second += itemProp.second;
						continue;
					}
				}
			}
		}
	}

	if(m_wep != NULL){
		for (auto itemProp : m_wep->getProperties()){
			for (auto& myProp : m_stats){
				if (itemProp.first == myProp.first){
					if (itemProp.first == "speed"){
						myProp.second = itemProp.second;
					}
					else{
						myProp.second += itemProp.second;
					}

					continue;
				}
			}
		}
	}

	m_maxHealth = m_stats["stamina"] * STAMINAMULTIPLIER;
	m_maxMana = m_stats["intellect"] * INTELLECTMULTIPLIER;

	m_stats["minDamage"] += m_stats["strength"] * STRENGTHMULTIPLIER;
	m_stats["maxDamage"] += m_stats["strength"] * STRENGTHMULTIPLIER;

	Log::getInstance().addLine("");
	Log::getInstance().addLine("---------- Players Stats ----------");
	Log::getInstance().addLine("");
	for (auto myProp : m_stats){
		Log::getInstance().addLine(myProp.first + " = " + to_string(myProp.second));
	}

	Log::getInstance().addLine("");
	Log::getInstance().addLine("--------------- end ---------------");
	Log::getInstance().addLine("");
}

void Player::takeDamage(int dmg){
	if (dmg <= 0){
		return;
	}

	m_curHealth -= dmg;
	
	m_dmgDispTimer->resetTimer();

	if (m_dmgDispBox){
		delete m_dmgDispBox;
		m_dmgDispBox = NULL;
	}

	m_dmgDispBox = GUI::addBox(get_x() + (get_width() / 2) - 8, get_y() - 2, 16, 16);
	m_dmgDispBox->setTranspareny(0, 0, 0);
	m_dmgDispBox->setText(to_string(dmg));

	m_dmgDispYOffset = -2;

	if (m_curHealth < 0){
		m_curHealth = 0;
	}
}

int Player::getMaxHealth(){
	return m_maxHealth;
}

int Player::getcurHealth(){
	return m_curHealth;
}

int Player::getMaxMana(){
	return m_maxMana;
}

int Player::getCurMana(){
	return m_curMana;
}

Item* Player::getWeapon(){
	return m_wep;
}

int Player::getLvl(){
	return m_lvl;
}

int Player::getGold(){
	return m_gold;
}

int Player::getReqExp(){
	return m_reqExp;
}

int Player::getExp(){
	return m_exp;
}

int Player::dealDamage(){
	/*Log::getInstance().addLine("");
	Log::getInstance().addLine("--------- Attacking ----------");
	Log::getInstance().addLine("");*/
	int temp;
	temp = m_stats["maxDamage"] - m_stats["minDamage"];

	if (temp <= 0){
		temp = 1;
	}

 	temp = rand() % temp;

	int totalDamage = m_stats["minDamage"] + temp;

	int critChance = 10;

	int crit = rand() % 100;

	critChance += m_stats["agility"] * 0.5f;

	if (critChance >= crit){
		int dmgDifference = rand() % ((m_stats["maxDamage"] - m_stats["minDamage"]) / 2);

		totalDamage = m_stats["maxDamage"] - dmgDifference;

		totalDamage *= 1.5f;

		//Log::getInstance().addLine("CRIT!");
		//Log::getInstance().addLine("Crit Damage = " + to_string(totalDamage));
	}
	else{
		//Log::getInstance().addLine("Damage = " + to_string(totalDamage));
	}

	/*Log::getInstance().addLine("CritChance = " + to_string(critChance) + "%");
	Log::getInstance().addLine("Crit = " + to_string(crit) + "%");
	Log::getInstance().addLine("");
	Log::getInstance().addLine("------------ end -------------");
	Log::getInstance().addLine("");*/
	return totalDamage;
}

void Player::combatMode(){
	playX = get_x();
	playY = get_y();
	setImage("images/giraffeMan.png", 6, 8, "images/giraffeMan_mask.png");
	set_auto_animate(75);
	set_world_position(100, 580);
	set_transparent_colour(147, 147, 147);
	set_currentFrame(6);
	set_auto_move(5);
	grounded = true;
}

void Player::playMode(){
	setImage("images/wizard.png", 3, 3);
	set_world_position(playX, playY);
	set_transparent_colour(105, 107, 100);
	set_currentFrame(4);
	set_auto_move(5);
}

//This loop is ran when the player is in the combat screen allowing for the different movement
void Player::combatUpdate(){
	SDL_BlitSurface(surface, NULL, m_wep->surface, NULL);
	m_wep->set_world_position(0, 0);
	if(m_right){
		set_x_velocity(m_speed*2);
	}

	if(m_left){
		set_x_velocity(-m_speed*2);
	}

	if(m_up && grounded){
		grounded = false;
		set_y_velocity(-5);
	}

	if(!m_left && !m_right){
		set_x_velocity(0);
		set_animation_subset(6, 6);
	}

	if(!grounded){
		set_y_velocity(get_y_velocity()+0.1);

		if(get_y() > 580){
			grounded = true;
			set_world_position_y(580);
			set_y_velocity(0);
		}
	}
	
	if (m_dmgDispBox){
		m_dmgDispBox->setPosition(get_x() + (get_width() / 2) - 8, get_y() + m_dmgDispYOffset);
		m_dmgDispYOffset--;
	}

	if (m_dmgDispTimer->getElapsedTime() > 1.0f){
		if (m_dmgDispBox){
			delete m_dmgDispBox;
			m_dmgDispBox = NULL;
		}
	}
}

PlayerDisplay* Player::getDisplay(){
	return m_display;
}

Inventory<Item>* Player::getInv(){
	return m_inv;
}
//Updates the players character screen display

Item* Player::getArmor(int armorItem){
	if (armorItem < ARMORSLOTS && armorItem >= 0){
		return m_armor[armorItem];
	}
	else{
		return NULL;
	}
}

void Player::updateDisplay(){
	for(int i = 0; i < 15; i++){
		if(m_inv->getElement(i)->getData() != NULL){
			m_display->setIcon(i, m_inv->getElement(i)->getData()->getFilePath(), m_inv->getElement(i)->getCurStack());
		}else{
			m_display->clearIcon(i);
		}
	}

	for (int i = 0; i < EQPINT; i++){
		char temp2[255];
		if (i == 0){
			if (m_wep){
				m_display->setEquipIcon(i, m_wep->getFilePath());
			}
		}else{
			if (m_armor[i - 1]){
				m_display->setEquipIcon(i, m_armor[i - 1]->getFilePath());
			}
		}
	}
}

void Player::renderCombat(){
	if (m_dmgDispBox){
		m_dmgDispBox->update();
	}
}
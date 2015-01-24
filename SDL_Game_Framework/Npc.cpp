#include "Npc.h"

Npc::Npc(){
	setImage("images/wizard.png", 3, 3);
	set_world_position(500, 600);
	set_transparent_colour(105, 107, 100);
	set_currentFrame(4);
	set_auto_move(5);
	m_aggresive = m_down = m_up = m_left = m_right = false;
	m_speed = 1;
	m_minDamage = 5;
	m_maxDamage = 50;
	m_aSpeed = 1;
	m_health = m_curHealth = 200;
	m_aTimer = new Timer();
	m_dead = false;
}

Npc::~Npc(){
}

void Npc::Bounds(int xLo, int yLo, int xHi, int yHi){
	m_xLo = xLo;
	m_yLo = yLo;
	m_xHi = xHi;
	m_yHi = yHi;
}
//Moves the npc in the direction of the target
void Npc::move(int targetX, int targetY){
	if(get_x() < targetX && get_x() < m_xHi){
		set_x_velocity(m_speed);
		m_right = true;
	}else{
		m_right = false;
	}

	if(get_x() > targetX && get_x() > m_xLo){
		set_x_velocity(-m_speed);
		m_left = true;
	}else{
		m_left = false;
	}

	if(get_y() < targetY && get_y() < m_yHi){
		set_y_velocity(m_speed);
		m_down = true;
	}else{
		m_down = false;
	}

	if(get_y() > targetY && get_y() > m_yLo){
		set_y_velocity(-m_speed);
		m_up = true;
	}else{
		m_up = false;
	}


	if(!m_left && !m_right){
		set_x_velocity(0);
	}

	if(!m_up && !m_down){
		set_y_velocity(0);
	}

	if(m_right && m_up){
		set_currentFrame(2);
	}else if(m_left && m_up){
		set_currentFrame(0);
	}else if(m_right && m_down){
		set_currentFrame(8);
	}else if(m_left && m_down){
		set_currentFrame(6);
	}else if(m_right){
		set_currentFrame(5);
	}else if(m_left){
		set_currentFrame(3);
	}else if(m_up){
		set_currentFrame(1);
	}else if(m_down){
		set_currentFrame(7);
	}
}

//Returns a random damage between the minimum and max damage
int Npc::dealDamage(){
	if(m_aTimer->getElapsedTime() > m_aSpeed){
		m_aTimer->resetTimer();
		set_animation_subset(18, 23);
		set_auto_animate(100, 1);
		return (rand() % (m_maxDamage-m_minDamage))+m_minDamage;
	}

	return 0;
}

int Npc::getCurHealth(){
	return m_curHealth;
}

int Npc::getMaxHealth(){
	return m_health;
}

//Initialse combat mode
void Npc::combatMode(){
	setImage("images/giraffeMan.png", 6, 8, "images/giraffeMan_mask.png");
	m_left = m_right = m_up = m_down = false;
	set_world_position(900, 580);
	set_transparent_colour(147, 147, 147);
	set_currentFrame(6);
	set_auto_move(5);
}

//Initialise play made
void Npc::playMode(){
	setImage("images/wizard.png", 3, 3);
	m_left = m_right = m_up = m_down = false;
	set_world_position(900, 580);
	set_transparent_colour(147, 147, 147);
	set_currentFrame(6);
	set_auto_move(5);
}

//Deals the provided damage to the npc, if it returns false the npc is dead
bool Npc::takeDamage(int dmg){
	m_curHealth -= dmg;
	if(m_curHealth < 1){
		m_curHealth = 0;
		return false;
	}

	return true;
}

//Controls the Npc when it goes into combat
void Npc::combatUpdate(int targetX, int targetY){
	if(get_x() < targetX){
		set_x_velocity(m_speed*2);
		set_auto_animate(75);
		m_right = true;

		if(get_currentFrame() < 6){
			set_animation_subset(0, 5);
		}
	}else{
		m_right = false;
	}

	if(get_x() > targetX+64){
		set_x_velocity(-m_speed*2);
		set_auto_animate(75);
		m_left = true;

		if(get_currentFrame() < 24 && get_currentFrame() > 29){
			set_animation_subset(24, 29);
		}
	}else{
		m_left = false;
	}

	if(!m_left && !m_right){
		set_x_velocity(0);
	}
}

void Npc::aggressive(bool agro){
	m_aggresive = agro;
}

bool Npc::aggressive(){
	return m_aggresive;
}

bool Npc::isDead(){
	return m_dead;
}

void Npc::kill(bool dead){
	m_dead = dead;
}
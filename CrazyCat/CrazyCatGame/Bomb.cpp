#include "Bomb.h"


Bomb::Bomb(int id, float x, float y, float width, float height, CSprite* spriteSource, DWORD timeExist)
{
	this->_id = id;
	this->_position_x = x;
	this->_position_y = y;
	this->_width = width;
	this->_height = height;
	this->_velocity_x = 0.0f;
	this->_velocity_y = 0.0f;

	this->_is_fire = false;
	this->_exist_time = timeExist;
	this->_sprite_resource = spriteSource;
}


Bomb::~Bomb()
{
}


void Bomb::inital(LPD3DXSPRITE sprite_handler)
{
	this->_start_time = GetTickCount();
	this->_is_fire = false;
	this->_last_time = GetTickCount();
}

void Bomb::update(int deltaTime)
{
	DWORD now = GetTickCount();
	if ((now - this->_start_time) > this->_exist_time)
		this->Fire();

	if ((now - this->_last_time) > (1000 / BOMB_ANIMATE_RATE))
	{
		if (this->_is_fire)
			return;
		this->next();
		_last_time = now;
	}
}

void Bomb::Fire(){
	if (!this->_is_fire)
		this->_is_fire = true;
}



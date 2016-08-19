#include "FireBang.h"


FireBang::FireBang(int id, float x, float y, float width, float height, CSprite* spriteSource, DWORD timeExist)
{
	this->_id = id;
	this->_position_x = x;
	this->_position_y = y;
	this->_width = width;
	this->_height = height;
	this->_velocity_x = 0.0f;
	this->_velocity_y = 0.0f;
	this->_exist_time = timeExist;
	this->_sprite_resource = spriteSource;
}


FireBang::~FireBang()
{
}


void FireBang::inital(LPD3DXSPRITE sprite_handler)
{
	this->_start_time = GetTickCount();
	this->_is_boom = false;
	this->_last_time = _start_time;
}

void FireBang::update(int deltaTime)
{
	DWORD now = GetTickCount();
	if (now - this->_start_time > this->_exist_time)
		this->_is_boom = true;
	if ((now - this->_last_time) > (1000 / FIREBANG_ANIMATE_RATE))
	{
		if (this->_is_boom)
			return;
		this->next();
		_last_time = now;
	}
}




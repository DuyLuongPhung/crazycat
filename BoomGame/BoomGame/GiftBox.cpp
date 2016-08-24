#include "GiftBox.h"


GiftBox::GiftBox(int id, DWORD existTimes, float x, float y, float width, float height, CSprite * spriteResource)
{
	this->_id = id;
	this->_position_x = x;
	this->_position_y = y;
	this->_width = width;
	this->_height = height;
	this->_velocity_x = 0.0f;
	this->_velocity_y = 0.0f;
	this->_gi_exist_times = existTimes;
	this->_sprite_resource = spriteResource;
}


GiftBox::~GiftBox()
{
}

void GiftBox::inital(LPD3DXSPRITE sprite_handler)
{
	this->_gi_start_time = GetTickCount();
	this->_gi_exist = true;
}

void GiftBox::update(int deltaTime)
{
	DWORD now = GetTickCount() - this->_gi_start_time;
	if (now > this->_gi_exist_times && this->_gi_exist_times > 0)
		this->_gi_exist = false;
}
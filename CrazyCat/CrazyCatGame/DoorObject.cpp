#include "DoorObject.h"


DoorObject::DoorObject(int id, float x, float y, float width, float height, CSprite * spriteResource)
{
	this->_id = id;
	this->_position_x = x;
	this->_position_y = y;
	this->_width = width;
	this->_height = height;
	this->_velocity_x = 0.0f;
	this->_velocity_y = 0.0f;
	this->_is_opening = false;
	this->_sprite_resource = spriteResource;
}


DoorObject::~DoorObject()
{
}

void DoorObject::next()
{
}

void DoorObject::inital(LPD3DXSPRITE sprite_handler)
{
	this->_is_opening = false;
	this->_sprite_resource->Reset();
}

void DoorObject::update(int deltaTime)
{
	DWORD now = GetTickCount();
	if ((now - this->_last_time) > (1000 / BOMB_ANIMATE_RATE))
	{
		if (!this->_is_opening)
			this->_sprite_resource->Index(0);
		else{
			if (!this->_sprite_resource->isHighestSprite()){
				this->_sprite_resource->Next();
			}
		}
		_last_time = now;
	}
}

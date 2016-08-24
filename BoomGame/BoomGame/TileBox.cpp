#include "TileBox.h"


TileBox::TileBox(int id, float x, float y, float width, float height, CSprite * spriteResource)
{
	this->_id = id;
	this->_position_x = x;
	this->_position_y = y;
	this->_width = width;
	this->_height = height;
	this->_velocity_x = 0.0f;
	this->_velocity_y = 0.0f;

	this->_sprite_resource = spriteResource;
}

TileBox::~TileBox()
{
}

#include "DynamicGameObject.h"

CDynamicGameObject::CDynamicGameObject()
{
	this->_sprite_resource = NULL;
}

CDynamicGameObject::CDynamicGameObject(int id, float x, float y, float width, float height, float vx, float vy,
	LPD3DXSPRITE sprite_handler, LPWSTR file_path, int count_sprite, int sprite_per_row)
	: CGameObject(id, x, y, width, height, vx, vy)
{
	this->_sprite_resource = new CSprite(sprite_handler, file_path, width, height, count_sprite, sprite_per_row);
}


CDynamicGameObject::~CDynamicGameObject()
{
	SAFE_DELETE(this->_sprite_resource);
}

void CDynamicGameObject::next()
{
	if (this->_sprite_resource != NULL){
		this->_sprite_resource->Next();
	}
}
CBox CDynamicGameObject::getBounding()
{
	return CBox(this->_position_x, this->_position_y, this->_width, this->_height, this->_velocity_x, this->_velocity_y);
}

void CDynamicGameObject::inital(LPD3DXSPRITE sprite_handler)
{

}

void CDynamicGameObject::update(int deltaTime)
{

}

void CDynamicGameObject::draw(D3DXVECTOR2 view_port)
{
	if (this->_sprite_resource != NULL){
		this->_sprite_resource->Render(view_port, this->_position_x, this->_position_y);
	}
}

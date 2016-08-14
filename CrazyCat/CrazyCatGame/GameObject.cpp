#include "GameObject.h"

CGameObject::CGameObject()
{
	this->_id = -1;
	this->_position_x = 0.0f;
	this->_position_y = 0.0f;
	this->_width = 0.0f;
	this->_height = 0.0f;
	this->_velocity_x = 0.0f;
	this->_velocity_y = 0.0f;
}

CGameObject::CGameObject(int id, float x, float y, float width, float height, float vx, float vy)
{
	this->_id = id;
	this->_position_x = x;
	this->_position_y = y;
	this->_width = width;
	this->_height = height;
	this->_velocity_x = vx;
	this->_velocity_y = vy;
}

CGameObject::~CGameObject()
{
}

void CGameObject::setPosition(float x, float y)
{
	this->_position_x = x;
	this->_position_y = y;
}

CBox CGameObject::getBounding()
{
	return CBox(this->_position_x, this->_position_y, this->_width, this->_height, this->_velocity_x, this->_velocity_y);
}

void CGameObject::setVelocity(float vx, float vy)
{
	this->_velocity_x= vx;
	this->_velocity_y = vy;
}

void CGameObject::inital()
{

}

void CGameObject::update()
{

}

void CGameObject::draw(D3DXVECTOR2 view_port)
{
	//m_Sprite->Render(m_Position.x, m_Position.y);
}
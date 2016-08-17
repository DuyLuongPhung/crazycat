#include "Bomb.h"


Bomb::Bomb(int id, float x, float y, float width, float height, LPD3DXSPRITE spritHandler, LPWSTR filePath,
	int countSprite, int spritePerRow, bool isLeft, bool isRight, bool isTop, bool isBottom)
	:CDynamicGameObject(id, x, y, width, height, 0.0f, 0.0f, spritHandler, filePath, countSprite, spritePerRow)
{
	this->_is_left = isLeft;
	this->_is_right = isRight;
	this->_is_top = isTop;
	this->_is_bottom = isBottom;
	this->_is_fire = false;
	this->_start_time = GetTickCount();
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
	if ((now - this->_start_time) > BOMB_TIME_FIRE)
		this->Fire();

	if ((now - this->_last_time) > (1000 / ANIMATE_RATE_BOMB))
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



#include "FireBang.h"


FireBang::FireBang(int id, float x, float y, float width, float height, LPD3DXSPRITE spritHandler, LPWSTR filePath,
	int countSprite, int spritePerRow)
	:CDynamicGameObject(id, x, y, width, height, 0.0f, 0.0f, spritHandler, filePath, countSprite, spritePerRow)
{
	this->_count_sprite = countSprite;
}


FireBang::~FireBang()
{
}


void FireBang::inital(LPD3DXSPRITE sprite_handler)
{
	this->_current_sprite = 0;
	this->_is_boom = false;
	this->_last_time = GetTickCount();
}

void FireBang::update(int deltaTime)
{
	if (this->_current_sprite > this->_count_sprite)
		this->_is_boom = true;
	DWORD now = GetTickCount();
	if ((now - this->_last_time) > (1000 / ANIMATE_RATE_BOMB))
	{
		if (this->_is_boom)
			return;
		this->next();
		this->_current_sprite++;
		_last_time = now;
	}
}




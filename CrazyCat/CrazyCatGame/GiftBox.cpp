#include "GiftBox.h"


GiftBox::GiftBox(int id, DWORD existTimes, float x, float y, float width, float height, LPD3DXSPRITE spriteHandler, LPWSTR filePath)
	: CDynamicGameObject(id, x, y, width, height, 0.0f, 0.0f, spriteHandler, filePath, 1, 1)
{
	this->_gi_exist_times = existTimes;
	
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
	if (now > this->_gi_exist_times)
		this->_gi_exist = false;
}
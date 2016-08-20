
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "GameBar.h"
#include <stdio.h>
#include <string>

class KeyGameBar :
	public GameBar
{
private:
	int _max_keys;
public:
	KeyGameBar();
	~KeyGameBar();

	void setMaxKeys(int maxkey){ this->_max_keys = maxkey; }
	virtual void draw(LPD3DXSPRITE SpriteHandler);
};

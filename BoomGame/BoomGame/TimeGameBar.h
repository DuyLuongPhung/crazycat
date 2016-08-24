
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "GameBar.h"
#include <stdio.h>
#include <string>

class TimeGameBar :
	public GameBar
{
public:
	TimeGameBar();
	~TimeGameBar();

	virtual void draw(LPD3DXSPRITE SpriteHandler);
};


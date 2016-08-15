#pragma once

#include "StaticGameObject.h"

class Brick : public CStaticGameObject
{
public:
	Brick();
	Brick(float x, float y, float width, float height, float vx, float vy);
	~Brick();
};


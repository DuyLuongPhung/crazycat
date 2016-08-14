#pragma once

#ifndef COLLISION_H
#define COLLISION_H
#include <algorithm>
#include <Windows.h>
#include <d3dx9.h>
#include "Box.h"

enum DIRECTION
{
	NONE = 0,
	NONE_CAN,	// có khả năng xảy ra va chạm
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

class CCollision
{
	D3DXVECTOR2 velocity;

public:
	CCollision();
	DIRECTION isCollision(CBox box1, CBox box2, float &collisionTime);
	D3DXVECTOR2		getVelocity(){ return velocity; };
	~CCollision();
};

#endif
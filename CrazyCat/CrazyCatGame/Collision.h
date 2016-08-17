#pragma once

#ifndef COLLISION_H
#define COLLISION_H
#include <algorithm>
#include <Windows.h>
#include <d3dx9.h>
#include "SweptAABB.h"

class CCollision
{
	D3DXVECTOR2 velocity;

public:
	CCollision();
	DIRECTION isCollision(CBox box1, CBox box2, float &collisionTime, float &offsetX, float &offsetY);
	D3DXVECTOR2		getVelocity(){ return velocity; };
	~CCollision();
};

#endif
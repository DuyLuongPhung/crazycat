#pragma once

#ifndef CDYNAMICGAMEOBJECT_H
#define CDYNAMICGAMEOBJECT_H

#include "GameObject.h"

enum Move_States{
	Walking_Left = 0,
	Walking_Right = 1,
	Walking_Front = 2,
	Walking_Behind = 3,
	None = 4
};

class CDynamicGameObject :
	public CGameObject
{
protected:
	CSprite *_sprite_resource;
public:
	CDynamicGameObject();
	CDynamicGameObject(int id, float x, float y, float width, float height, float vx, float vy,
		LPD3DXSPRITE sprite_handler, LPWSTR file_path, int count_sprite, int sprite_per_row);
	~CDynamicGameObject();

	virtual void		next();
	virtual CBox		getBounding();
	virtual void		inital(LPD3DXSPRITE sprite_handler);
	virtual void		draw(D3DXVECTOR2 view_port);
	virtual void		update(int deltaTime);
};

#endif


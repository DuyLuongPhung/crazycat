#pragma once

#ifndef CSTATICGAMEOBJECT_H
#define CSTATICGAMEOBJECT_H

#include "GameObject.h"

class CStaticGameObject : public CGameObject
{
private:
	// nothing
public:
	CStaticGameObject();
	CStaticGameObject(int id, float x, float y, float width, float height, float vx, float vy);
	~CStaticGameObject();

	virtual void		inital();
	virtual void		draw(D3DXVECTOR2 view_port);
	virtual void		update();

};

#endif

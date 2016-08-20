#pragma once
#include "DynamicGameObject.h"

class DoorObject : public CDynamicGameObject
{
private:
	bool	_is_opening;
	DWORD	_last_time;

public:
	DoorObject(int id, float x, float y, float width, float height, CSprite * spriteResource);
	~DoorObject();

	void openDoor(){ this->_is_opening = true; }
	void closeDoor(){ this->_is_opening = false; }
	bool isOpen(){ return this->_is_opening; }

	virtual void		next();
	virtual void		inital(LPD3DXSPRITE sprite_handler);
	virtual void		update(int deltaTime);
};


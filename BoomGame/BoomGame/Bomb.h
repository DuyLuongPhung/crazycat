#pragma once

#include "DynamicGameObject.h"
class Bomb : public CDynamicGameObject
{
private: 
	DWORD _start_time;	// thời gian kích hoạt
	DWORD _exist_time;
	bool _is_fire;		// đảm bảo các quả bom đã nổ sẽ bị mất đi
	DWORD _last_time;
public:
	Bomb(int id, float x, float y, float width, float height, CSprite* spriteSource, DWORD timeExist);
	~Bomb();

	virtual void		inital(LPD3DXSPRITE sprite_handler);
	virtual void		update(int deltaTime);

	bool IsFired(){ return this->_is_fire; }

private:
	void Fire();
};


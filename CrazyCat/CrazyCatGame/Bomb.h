#pragma once

#include "DynamicGameObject.h"
class Bomb : public CDynamicGameObject
{
private: 
	DWORD _start_time;	// thời gian kích hoạt
	bool  _is_left;		// xác định xem có nổ hướng bên trái hay không?
	bool  _is_right;
	bool _is_top;
	bool _is_bottom;

	bool _is_fire;		// đảm bảo các quả bom đã nổ sẽ bị mất đi
	DWORD _last_time;
public:
	Bomb(int id, float x, float y, float width, float height, LPD3DXSPRITE sprite_handler, LPWSTR file_path,
		int count_sprite, int sprite_per_row, bool isLeft, bool isRight, bool isTop, bool isBottom);
	~Bomb();

	//virtual void		next();
	//virtual CBox		getBounding();
	virtual void		inital(LPD3DXSPRITE sprite_handler);
	//virtual void		draw(D3DXVECTOR2 view_port);
	virtual void		update(int deltaTime);

	bool IsFired(){ return this->_is_fire; }

private:
	void Fire();
};


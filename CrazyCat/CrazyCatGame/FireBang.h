#pragma once

#include "DynamicGameObject.h"

class FireBang : public CDynamicGameObject
{
private:
	bool _is_boom;			// kiểm tra xem đã nổ xong chưa?
	int _current_sprite;	// sprite hiện tại
	int _count_sprite;		// tổng số sprite sẽ vẽ, sau số sprite tương ứng đã nổ xong
	DWORD _last_time;
public:
	FireBang(int id, float x, float y, float width, float height, LPD3DXSPRITE sprite_handler, LPWSTR file_path,
		int count_sprite, int sprite_per_row);
	~FireBang();

	virtual void		inital(LPD3DXSPRITE sprite_handler);
	//virtual void		draw(D3DXVECTOR2 view_port);
	virtual void		update(int deltaTime);

	bool isFiredBang(){ return this->_is_boom; }
};


#pragma once

#include "DynamicGameObject.h"

class FireBang : public CDynamicGameObject
{
private:
	bool _is_boom;			// kiểm tra xem đã nổ xong chưa?
	DWORD _start_time;		// thời điểm bắt đầu nổ
	DWORD _exist_time;		// tổng thời gian tồn tại, sau đó sẽ biến mất
	DWORD _last_time;
public:
	FireBang(int id, float x, float y, float width, float height, CSprite* spriteSource, DWORD timeExist);
	~FireBang();

	virtual void		inital(LPD3DXSPRITE sprite_handler);
	virtual void		update(int deltaTime);

	bool isFiredBang(){ return this->_is_boom; }
};


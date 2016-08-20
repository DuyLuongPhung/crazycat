#pragma once

#include "DynamicGameObject.h"

class GiftBox : public CDynamicGameObject
{
private:
	DWORD	_gi_exist_times;	// thời gian để hộp quà tồn tại
								// sau khoảng thời gian này hộp quà sẽ biến mất
	DWORD	_gi_start_time;		// thời gian bắt đầu hiện hộp quà
	bool	_gi_exist;			// hộp quà còn tồn tại hay không? 
public:
	GiftBox(int id, DWORD existTimes, float x, float y, float width, float height, CSprite * spriteResource);
	~GiftBox();

	bool				isExist(){ return this->_gi_exist; }
	virtual void		inital(LPD3DXSPRITE sprite_handler);
	virtual void		update(int deltaTime);
};

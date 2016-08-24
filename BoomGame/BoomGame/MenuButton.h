#pragma once

#include "Sprite.h"
#include "CONST.h"

class MenuButton
{
private:
	int _b_type_id;
	float _x, _y;

	CSprite* _b_sprite;
	bool _is_moving;
	bool _is_selected;
public:
	MenuButton();
	MenuButton(int typeId, int x, int y, CSprite * spriteResource, bool isMoving);
	~MenuButton();

	void resetting();
	int getTypeId(){ return this->_b_type_id; }

	void moving(){ this->_is_moving = true; }
	void leaving(){ this->_is_moving = false; }
	void select(){ this->_is_selected = true; }

	void draw();
};


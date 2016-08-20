#pragma once

#include "Sprite.h"
#include "Text.h"
#include "Box.h"
#include "CONST.h"

class GameBar
{
protected:
	int _gb_id;
	long _gb_value;
	CSprite * _gb_background;
	CText	* _gb_text_mgt;
	CBox _gb_print_text;
	D3DXVECTOR2 _gb_position;

public:
	GameBar();
	~GameBar();

	int getId(){ return this->_gb_id; }
	void inital(int id, LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE SpriteHandler, LPWSTR bgPath, int bgWidth, int bgHeight, D3DXVECTOR2 position, CBox printTextBox, int defaultValue);
	void updateValue(long newValue){ this->_gb_value = newValue; }
	virtual void draw(LPD3DXSPRITE SpriteHandler);
};


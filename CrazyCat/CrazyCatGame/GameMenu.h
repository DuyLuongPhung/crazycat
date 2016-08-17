#pragma once

#include "Sprite.h"
#include "MenuButton.h"
#include <vector>
#include "DirectX.h"

class GameMenu
{
private:
	LPDIRECT3DSURFACE9 _m_background;
	int _current_button;
	float _m_x,_m_y, _m_width,_m_height;
	std::vector<MenuButton*> _list_buttons;

public:
	GameMenu(LPDIRECT3DDEVICE9 d3ddev, float x, float y, float width, float height, int maxButtons, LPWSTR fileBackground);
	~GameMenu();

	void nextButton();
	void preButton();

	int getCurrentButtonId(){ if (_list_buttons.size() > _current_button)return this->_list_buttons.at(this->_current_button)->getTypeId(); }
	void initalStartMenu(LPD3DXSPRITE spriteHandler);
	void initalPauseMenu(LPD3DXSPRITE spriteHandler);

	void draw(CDirectX *d3ddev);
};


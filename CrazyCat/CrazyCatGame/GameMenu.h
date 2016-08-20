#pragma once

#include "Sprite.h"
#include "MenuButton.h"
#include <vector>
#include "DirectX.h"
#include "ResourceManager.h"

class GameMenu
{
private:
	CSprite* _m_background;
	int _current_button;
	float _m_x,_m_y, _m_width,_m_height;
	std::vector<MenuButton*> _list_buttons_start;
	std::vector<MenuButton*> _list_buttons_pause;
	bool _is_pause_menu;

public:
	GameMenu(float x, float y, float width, float height);
	~GameMenu();

	void nextButton();
	void preButton();

	int getCurrentButtonId();
	bool isPauseMenu(){ return this->_is_pause_menu; }

	void inital(LPD3DXSPRITE spriteHandler, ResourceManager* resourceMgt,  bool isPauseMenu);
	void draw(CDirectX *d3ddev);

	void resetMenu(bool isPauseMenu);	
};


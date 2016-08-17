#include "GameMenu.h"


GameMenu::GameMenu(LPDIRECT3DDEVICE9 d3ddev, float x, float y, float width, float height, int maxButtons, LPWSTR fileBackground)
{
	this->_m_x = x;
	this->_m_y = y;
	this->_m_width = width;
	this->_m_height = height;
	this->_m_background = LoadSurfaceFromFile(d3ddev, fileBackground, D3DCOLOR_XRGB(255, 0, 255));
}


GameMenu::~GameMenu()
{
}

void GameMenu::nextButton()
{
	if (this->_list_buttons.size() > 0){
		this->_current_button = (this->_current_button) + 1 % this->_list_buttons.size();
		this->_list_buttons.at(this->_current_button)->moving();
	}

}
void GameMenu::preButton(){
	if (this->_list_buttons.size() > 0){
		this->_current_button = (this->_current_button) - 1 % this->_list_buttons.size();
		this->_list_buttons.at(this->_current_button)->moving();
	}
}

void GameMenu::initalStartMenu(LPD3DXSPRITE spriteHandler){
	this->_list_buttons.clear();
	// start button
	MenuButton *startButton = new MenuButton(START_BUTTON_ID, this->_m_x + START_BUTTON_X,
		this->_m_y - START_BUTTON_Y, spriteHandler, START_BUTTON_IMG, BUTTON_WIDTH, BUTTON_HEIGHT, 2, 2, true);
	this->_list_buttons.push_back(startButton);
	// help button
	MenuButton *helpButton = new MenuButton(HELP_BUTTON_ID, this->_m_x + HELP_BUTTON_X,
		this->_m_y - HELP_BUTTON_Y, spriteHandler, HELP_BUTTON_IMG, BUTTON_WIDTH, BUTTON_HEIGHT, 2, 2, false);
	this->_list_buttons.push_back(helpButton);
	// exit button
	MenuButton *exitButton = new MenuButton(EXIT_BUTTON_ID, this->_m_x + EXIT_BUTTON_X,
		this->_m_y - EXIT_BUTTON_Y, spriteHandler, EXIT_BUTTON_IMG, BUTTON_WIDTH, BUTTON_HEIGHT, 2, 2, false);
	this->_list_buttons.push_back(exitButton);
	this->_current_button = 0;
}
void GameMenu::initalPauseMenu(LPD3DXSPRITE spriteHandler){}

void GameMenu::draw(CDirectX *d3ddev){
	RECT backRect;
	backRect.left = this->_m_x;
	backRect.right = backRect.left + this->_m_width;
	backRect.top = this->_m_y;
	backRect.bottom = backRect.top + this->_m_height;

	d3ddev->getDevice()->StretchRect(this->_m_background, NULL, d3ddev->getBackBuffer(), &backRect, D3DTEXF_NONE);
	for (int i = 0; i < _list_buttons.size(); i++){
		_list_buttons.at(i)->draw();
	}
}
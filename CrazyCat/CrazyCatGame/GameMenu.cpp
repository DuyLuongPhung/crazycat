#include "GameMenu.h"


GameMenu::GameMenu(LPDIRECT3DDEVICE9 d3ddev, float x, float y, float width, float height, int maxButtons, LPWSTR fileBackground)
{
	this->_m_x = x;
	this->_m_y = y;
	this->_m_width = width;
	this->_m_height = height;
}


GameMenu::~GameMenu()
{
}

void GameMenu::nextButton()
{
	if (this->_list_buttons.size() > 0){
		this->_current_button = (this->_current_button + 1) % (this->_list_buttons.size());
		if (this->_list_buttons.size() > _current_button)
		{
			for (int i = 0; i < this->_list_buttons.size(); i++)
			{
				if (i == this->_current_button){
					this->_list_buttons.at(i)->moving();
					continue;
				}
				this->_list_buttons.at(i)->leaving();
			}
		}
	}

}
void GameMenu::preButton(){
	if (this->_list_buttons.size() > 0){
		this->_current_button = ((this->_current_button) - 1) % (this->_list_buttons.size());
		if (this->_list_buttons.size() > _current_button)
		{
			for (int i = 0; i < this->_list_buttons.size(); i++)
			{
				if (i == this->_current_button){
					this->_list_buttons.at(i)->moving();
					continue;
				}
				this->_list_buttons.at(i)->leaving();
			}
		}

	}
}

int GameMenu::getCurrentButtonId()
{ 
	if (_list_buttons.size() > _current_button)
		return (this->_list_buttons.at(this->_current_button)->getTypeId()); 
}

void GameMenu::initalStartMenu(LPD3DXSPRITE spriteHandler){
	// back ground
	this->_m_background = new CSprite(spriteHandler, L"GameMenu_bg.png", 320, 416, 1, 1, NULL);


	this->_list_buttons.clear();
	// start button
	MenuButton *startButton = new MenuButton(MENU_START_BUTTON_ID, this->_m_x + MENU_START_BUTTON_X,
		this->_m_y + MENU_START_BUTTON_Y, spriteHandler, MENU_START_BUTTON_IMG, BUTTON_WIDTH, BUTTON_HEIGHT, 2, 2, true);
	this->_list_buttons.push_back(startButton);
	// help button
	MenuButton *helpButton = new MenuButton(MENU_HELP_BUTTON_ID, this->_m_x + MENU_HELP_BUTTON_X,
		this->_m_y + MENU_HELP_BUTTON_Y, spriteHandler, MENU_HELP_BUTTON_IMG, BUTTON_WIDTH, BUTTON_HEIGHT, 2, 2, false);
	this->_list_buttons.push_back(helpButton);
	// exit button
	MenuButton *exitButton = new MenuButton(MENU_EXIT_BUTTON_ID, this->_m_x + MENU_EXIT_BUTTON_X,
		this->_m_y + MENU_EXIT_BUTTON_Y, spriteHandler, MENU_EXIT_BUTTON_IMG, BUTTON_WIDTH, BUTTON_HEIGHT, 2, 2, false);
	this->_list_buttons.push_back(exitButton);
	this->_current_button = 0;
}
void GameMenu::initalPauseMenu(LPD3DXSPRITE spriteHandler){
	// back ground
	this->_m_background = new CSprite(spriteHandler, L"GameMenu_bg.png", 320, 416, 1, 1, NULL);


	this->_list_buttons.clear();
	// start button
	MenuButton *resumeButton = new MenuButton(MENU_RESUME_BUTTON_ID, this->_m_x + MENU_RESUME_BUTTON_X,
		this->_m_y + MENU_RESUME_BUTTON_Y, spriteHandler, MENU_RESUME_BUTTON_IMG, BUTTON_WIDTH, BUTTON_HEIGHT, 2, 2, true);
	this->_list_buttons.push_back(resumeButton);
	// help button
	MenuButton *helpButton = new MenuButton(MENU_HELP_BUTTON_ID, this->_m_x + MENU_HELP_BUTTON_X,
		this->_m_y + MENU_HELP_BUTTON_Y, spriteHandler, MENU_HELP_BUTTON_IMG, BUTTON_WIDTH, BUTTON_HEIGHT, 2, 2, false);
	this->_list_buttons.push_back(helpButton);
	// exit button
	MenuButton *exitButton = new MenuButton(MENU_EXIT_BUTTON_ID, this->_m_x + MENU_EXIT_BUTTON_X,
		this->_m_y + MENU_EXIT_BUTTON_Y, spriteHandler, MENU_EXIT_BUTTON_IMG, BUTTON_WIDTH, BUTTON_HEIGHT, 2, 2, false);
	this->_list_buttons.push_back(exitButton);
	this->_current_button = 0;
}

void GameMenu::draw(CDirectX *d3ddev){
	RECT backRect;
	backRect.left = this->_m_x;
	backRect.right = backRect.left + this->_m_width;
	backRect.top = this->_m_y;
	backRect.bottom = backRect.top + this->_m_height;

	d3ddev->getDevice()->ColorFill(d3ddev->getBackBuffer(), NULL, D3DCOLOR_ARGB(0, 245, 245, 245));
	d3ddev->getSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);
	this->_m_background->Render(_m_x, _m_y);

	for (int i = 0; i < _list_buttons.size(); i++){
		_list_buttons.at(i)->draw();
	}
	d3ddev->getSpriteHandler()->End();
}
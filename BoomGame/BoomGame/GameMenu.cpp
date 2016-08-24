#include "GameMenu.h"


GameMenu::GameMenu(float x, float y, float width, float height)
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
	if (this->_is_pause_menu){
		if (this->_list_buttons_pause.size() > 0){
			this->_current_button = (this->_current_button + 1) % (this->_list_buttons_pause.size());
			if (this->_list_buttons_pause.size() > _current_button)
			{
				for (int i = 0; i < this->_list_buttons_pause.size(); i++)
				{
					if (i == this->_current_button){
						this->_list_buttons_pause.at(i)->moving();
						continue;
					}
					this->_list_buttons_pause.at(i)->leaving();
				}
			}
		}
	}
	else{
		if (this->_list_buttons_start.size() > 0){
			this->_current_button = (this->_current_button + 1) % (this->_list_buttons_start.size());
			if (this->_list_buttons_start.size() > _current_button)
			{
				for (int i = 0; i < this->_list_buttons_start.size(); i++)
				{
					if (i == this->_current_button){
						this->_list_buttons_start.at(i)->moving();
						continue;
					}
					this->_list_buttons_start.at(i)->leaving();
				}
			}
		}
	}
}
void GameMenu::preButton(){
	if (this->_is_pause_menu){
		if (this->_list_buttons_pause.size() > 0){
			this->_current_button = (this->_current_button - 1) % (this->_list_buttons_pause.size());
			if (this->_list_buttons_pause.size() > _current_button)
			{
				for (int i = 0; i < this->_list_buttons_pause.size(); i++)
				{
					if (i == this->_current_button){
						this->_list_buttons_pause.at(i)->moving();
						continue;
					}
					this->_list_buttons_pause.at(i)->leaving();
				}
			}
		}
	}
	else{
		if (this->_list_buttons_start.size() > 0){
			this->_current_button = (this->_current_button - 1) % (this->_list_buttons_start.size());
			if (this->_list_buttons_start.size() > _current_button)
			{
				for (int i = 0; i < this->_list_buttons_start.size(); i++)
				{
					if (i == this->_current_button){
						this->_list_buttons_start.at(i)->moving();
						continue;
					}
					this->_list_buttons_start.at(i)->leaving();
				}
			}
		}
	}
}

int GameMenu::getCurrentButtonId()
{ 
	if (this->_is_pause_menu){
		if (_list_buttons_pause.size() > _current_button)
			return (this->_list_buttons_pause.at(this->_current_button)->getTypeId());
	}
	if (_list_buttons_start.size() > _current_button)
		return (this->_list_buttons_start.at(this->_current_button)->getTypeId());

	
}

void GameMenu::inital(LPD3DXSPRITE spriteHandler, ResourceManager* resourceMgt, bool isPauseMenu){
	this->_is_pause_menu = isPauseMenu;
	// back ground
	this->_m_background = resourceMgt->getSpriteWithID(ID_MENU_RESOURCE);

	this->_list_buttons_start.clear();
	this->_list_buttons_pause.clear();
	// start button
	MenuButton *startButton = new MenuButton(MENU_START_BUTTON_ID, this->_m_x + MENU_START_BUTTON_X,
		this->_m_y + MENU_START_BUTTON_Y, resourceMgt->getSpriteWithID(MENU_START_BUTTON_ID), true);
	this->_list_buttons_start.push_back(startButton);

	// start button
	MenuButton *resumeButton = new MenuButton(MENU_RESUME_BUTTON_ID, this->_m_x + MENU_RESUME_BUTTON_X,
		this->_m_y + MENU_RESUME_BUTTON_Y, resourceMgt->getSpriteWithID(MENU_RESUME_BUTTON_ID), true);
	this->_list_buttons_pause.push_back(resumeButton);

	// help button
	MenuButton *helpButton = new MenuButton(MENU_HELP_BUTTON_ID, this->_m_x + MENU_HELP_BUTTON_X,
		this->_m_y + MENU_HELP_BUTTON_Y, resourceMgt->getSpriteWithID(MENU_HELP_BUTTON_ID), false);
	this->_list_buttons_start.push_back(helpButton);
	this->_list_buttons_pause.push_back(helpButton);

	// exit button
	MenuButton *exitButton = new MenuButton(MENU_EXIT_BUTTON_ID, this->_m_x + MENU_EXIT_BUTTON_X,
		this->_m_y + MENU_EXIT_BUTTON_Y, resourceMgt->getSpriteWithID(MENU_EXIT_BUTTON_ID), false);
	this->_list_buttons_start.push_back(exitButton);
	this->_list_buttons_pause.push_back(exitButton);
	this->_current_button = 0;
}

void GameMenu::resetMenu(bool isPauseMenu){
	this->_is_pause_menu = isPauseMenu;
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
	if (this->_is_pause_menu){
		for (int i = 0; i < this->_list_buttons_pause.size(); i++){
			this->_list_buttons_pause.at(i)->draw();
		}
	}
	else{
		for (int i = 0; i < this->_list_buttons_start.size(); i++){
			this->_list_buttons_start.at(i)->draw();
		}
	}
	d3ddev->getSpriteHandler()->End();
}
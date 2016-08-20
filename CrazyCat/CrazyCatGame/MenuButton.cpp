#include "MenuButton.h"


MenuButton::MenuButton()
{
	this->_is_moving = false;
	this->_is_selected = false;
	this->_b_sprite->Reset();
}

MenuButton::MenuButton(int typeId, int x, int y, CSprite * spriteResource, bool isMoving)
{
	this->_x = x;
	this->_y = y;
	this->_b_type_id = typeId;
	this->_is_moving = isMoving;
	this->_b_sprite = spriteResource;
	this->_is_selected = false;
}


MenuButton::~MenuButton()
{
	SAFE_DELETE(this->_b_sprite);
}

void MenuButton::resetting(){
	this->_is_moving = false;
	this->_is_selected = false;
	this->_b_sprite->Reset();
}

void MenuButton::draw(){
	if (this->_is_moving){
		this->_b_sprite->Index(1);
	}
	else{
		this->_b_sprite->Index(0);
	}
	this->_b_sprite->Render(_x, _y); 
}
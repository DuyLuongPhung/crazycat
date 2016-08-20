#include "KeyGameBar.h"


KeyGameBar::KeyGameBar()
{
	this->_gb_value = 0;
	this->_gb_background = NULL;
	this->_gb_text_mgt = NULL;
	this->_gb_print_text = CBox();
	this->_gb_position = D3DXVECTOR2(0, 0);
}


KeyGameBar::~KeyGameBar()
{
}

void KeyGameBar::draw(LPD3DXSPRITE spriteHandler){
	// vẽ nền
	this->_gb_background->Render(this->_gb_position.x, this->_gb_position.y);
	// vẽ giá trị
	std::string valueStr = std::to_string(this->_gb_value) + " / " + std::to_string(this->_max_keys);
	char *cstr = new char[valueStr.length() + 1];
	strcpy(cstr, valueStr.c_str());
	this->_gb_text_mgt->Print(cstr, this->_gb_print_text.x + this->_gb_position.x, this->_gb_print_text.y + this->_gb_position.y,
		D3DCOLOR_XRGB(65, 44, 23), spriteHandler, 0, 0, FA_LEFT);
	delete[] cstr;
}

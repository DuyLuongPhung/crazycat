#include "TimeGameBar.h"


TimeGameBar::TimeGameBar()
{
	this->_gb_value = 0;
	this->_gb_background = NULL;
	this->_gb_text_mgt = NULL;
	this->_gb_print_text = CBox();
	this->_gb_position = D3DXVECTOR2(0, 0);
}


TimeGameBar::~TimeGameBar()
{
}

void TimeGameBar::draw(LPD3DXSPRITE spriteHandler){
	// vẽ nền
	this->_gb_background->Render(this->_gb_position.x, this->_gb_position.y);
	// vẽ giá trị
	long totalSecond = (this->_gb_value) / 1000 /1000;
	long minutes = totalSecond / 60;
	long second = totalSecond % 60;

	std::string minuteStr = std::to_string(minutes);
	minuteStr = (minuteStr.length() < 2) ? "0" + minuteStr : minuteStr;
	std::string secondStr = std::to_string(second);
	secondStr = (secondStr.length() < 2) ? "0" + secondStr : secondStr;
	std::string timeStr = minuteStr + ":" + secondStr;
	char *cstr = new char[timeStr.length() + 1];
	strcpy(cstr, timeStr.c_str());
	this->_gb_text_mgt->Print(cstr, this->_gb_print_text.x + this->_gb_position.x, this->_gb_print_text.y + this->_gb_position.y,
		D3DCOLOR_XRGB(65, 44, 23), spriteHandler, 0, 0, FA_LEFT);
	delete[] cstr;
}
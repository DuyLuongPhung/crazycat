#include "GameBar.h"


GameBar::GameBar()
{
	this->_gb_value = 0;
	this->_gb_background = NULL;
	this->_gb_text_mgt = NULL;
	this->_gb_print_text = CBox();
	this->_gb_position = D3DXVECTOR2(0,0);
}


GameBar::~GameBar()
{
}

void GameBar::inital(int id, LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE SpriteHandler, LPWSTR bgPath, int bgWidth, int bgHeight,
	D3DXVECTOR2 position, CBox printTextBox, int defaultValue){
	this->_gb_value = defaultValue;
	this->_gb_background = new CSprite(SpriteHandler, bgPath, bgWidth, bgHeight, 1, 1, NULL);
	this->_gb_text_mgt = new CText();
	this->_gb_text_mgt->Initialize(d3ddev, TEXT("Times New Roman"), GAMEBAR_FONT_SIZE,1);
	this->_gb_print_text = printTextBox;
	this->_gb_position = position;
	this->_gb_id = id;
}
char * valueBuffer = new char[30];
void GameBar::draw(LPD3DXSPRITE spriteHandler){
	// vẽ nền
	this->_gb_background->Render(this->_gb_position.x,this->_gb_position.y);
	// vẽ giá trị
	if (this->_gb_value < 0)
		this->_gb_value = 0;
	_itoa_s(this->_gb_value, valueBuffer, 30, 10);
	this->_gb_text_mgt->Print(valueBuffer, this->_gb_print_text.x + this->_gb_position.x, this->_gb_print_text.y + this->_gb_position.y,
		D3DCOLOR_XRGB(65, 44, 23), spriteHandler, 0, 0, FA_LEFT);
}
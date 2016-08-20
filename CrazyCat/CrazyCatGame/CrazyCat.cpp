#include "CrazyCat.h"
#include "CONST.h"
#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS



CrazyCat::CrazyCat(HINSTANCE hInstance, LPWSTR name, int mode, int is_fullscreen, int frame_rate) :
CGame(hInstance, name, mode, is_fullscreen, frame_rate)
{
	this->_g_currrent_mode = GAME_MODE::PlayMenu;
	this->_g_helpmgt = NULL;
	this->_g_mapmgt = NULL;
	this->_g_menu = NULL;
	this->_resourceMgt = NULL;
}


CrazyCat::~CrazyCat()
{
	SAFE_DELETE(this->_g_helpmgt);
	SAFE_DELETE(this->_g_mapmgt);
	SAFE_DELETE(this->_g_menu);
	SAFE_DELETE(this->_resourceMgt);
}

bool intersec = false;

int loop = 0;
void CrazyCat::Update(int delta)
{
	if (this->_g_currrent_mode == GAME_MODE::PlayMap){
		if (this->_g_mapmgt->isReturnMenu()){
			this->_g_menu->resetMenu(false);
			this->_g_currrent_mode = GAME_MODE::PlayMenu;
			return;
		}

		this->_g_mapmgt->update(delta, this->_directXDivice);
	}
}

void CrazyCat::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	// load sprite resource cho các đối tượng
	this->_resourceMgt = new ResourceManager();
	this->_resourceMgt->inital(this->_directXDivice);

	this->_g_helpmgt = new HelpMgt(this->_directXDivice->getDevice(), L"Help.png");

	this->_g_menu = new GameMenu(MENU_START_X, MENU_START_Y, WIDTH_MENU, HEIGHT_MENU);
	this->_g_menu->inital(this->_directXDivice->getSpriteHandler(), this->_resourceMgt, false);

	this->_g_mapmgt = new PlayMapMgt(this->_resourceMgt);
	this->_g_mapmgt->inital(this->_directXDivice, this->_screenWidth, this->_screenHeight);


}

void CrazyCat::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	CGame::RenderFrame(d3ddv, t);
	if (_g_currrent_mode == GAME_MODE::PlayMenu){
		_g_menu->draw(this->_directXDivice);
	}
	else if (_g_currrent_mode == GAME_MODE::PlayHelp){
		_g_helpmgt->draw(this->_directXDivice);
	}
	else if (_g_currrent_mode == GAME_MODE::PlayMap){
		_directXDivice->getSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);
		this->_g_mapmgt->draw(this->_directXDivice);
		_directXDivice->getSpriteHandler()->End();
	}
}

void CrazyCat::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	if (this->_g_mapmgt->isWaiting())
		return;
	if (_keyboardDevice->IsKeyDown(DIK_RIGHT))
	{
		this->_g_mapmgt->bomberRunRight();
	}
	else if (_keyboardDevice->IsKeyDown(DIK_LEFT))
	{
		this->_g_mapmgt->bomberRunLeft();
	}
	else if (_keyboardDevice->IsKeyDown(DIK_UP))
	{
		this->_g_mapmgt->bomberRunBehind();
	}
	else if (_keyboardDevice->IsKeyDown(DIK_DOWN))
	{
		this->_g_mapmgt->bomberRunFront();
	}
	else{
		this->_g_mapmgt->bomberMoveNone();
	}
}

void CrazyCat::OnKeyDown(int KeyCode)
{

	switch (KeyCode)
	{
	case DIK_SPACE:
	{
		if (_g_currrent_mode == GAME_MODE::PlayMenu)
		{
			if (_g_menu->getCurrentButtonId() == MENU_HELP_BUTTON_ID)
			{
				_g_currrent_mode = GAME_MODE::PlayHelp;
			}
			else if (_g_menu->getCurrentButtonId() == MENU_EXIT_BUTTON_ID){
				this->_is_exit = true;
			}
			else{
				_g_currrent_mode = GAME_MODE::PlayMap;
				this->_g_mapmgt->nextMap();
			}
		}
		else if (_g_currrent_mode == GAME_MODE::PlayMap){
			if (this->_g_mapmgt->isWaiting())
				return;
			this->AddBomb();
		}
		break;
	}
	case DIK_UP:
		if (_g_currrent_mode == GAME_MODE::PlayMenu)
			_g_menu->preButton();
		break;
	case DIK_DOWN:
		if (_g_currrent_mode == GAME_MODE::PlayMenu)
			_g_menu->nextButton();
		break;
	case DIK_TAB:
	{
		if (_g_currrent_mode == GAME_MODE::PlayHelp)
		{
			_g_currrent_mode = GAME_MODE::PlayMenu;
		}
		else if (_g_currrent_mode == GAME_MODE::PlayMenu){
			this->_is_exit = true;
		}
		else if (_g_currrent_mode == GAME_MODE::PlayMap){
			if (this->_g_mapmgt->isWaiting())
				return;
			_g_currrent_mode = GAME_MODE::PlayMenu;
		}

		break;
	}

	case DIK_C:
	{
		if (_g_currrent_mode == GAME_MODE::PlayHelp)
		{
			_g_currrent_mode = GAME_MODE::PlayMenu;
		}
		else if (_g_currrent_mode == GAME_MODE::PlayMenu){
			this->_is_exit = true;
		}
		else if (_g_currrent_mode == GAME_MODE::PlayMap){
			this->_g_mapmgt->gameOver();
		}

		break;
	}

	}
}

void CrazyCat::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_SPACE:
		break;
	}
}

void CrazyCat::AddBomb(){
	this->_g_mapmgt->addBomb(this->_directXDivice->getSpriteHandler());
}

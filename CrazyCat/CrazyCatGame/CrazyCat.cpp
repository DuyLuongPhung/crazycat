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
}


CrazyCat::~CrazyCat()
{
	SAFE_DELETE(this->_g_helpmgt);
	SAFE_DELETE(this->_g_mapmgt);
	SAFE_DELETE(this->_g_menu);
}
bool intersec = false;
void CrazyCat::Update(int delta)
{
	if (this->_g_currrent_mode == GAME_MODE::PlayMap){
		this->_g_mapmgt->update(delta, this->_directXDivice);
	}
}

void CrazyCat::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	this->_g_helpmgt = new HelpMgt(this->_directXDivice->getDevice(), L"Help.png");

	this->_g_menu = new GameMenu(this->_directXDivice->getDevice(), 32, 10, 320, 416, 4, L"GameMenu_bg.png");
	this->_g_menu->initalPauseMenu(this->_directXDivice->getSpriteHandler());

	this->_g_mapmgt = new PlayMapMgt();
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
			}
		}
		else if (_g_currrent_mode == GAME_MODE::PlayMap){
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
			_g_currrent_mode = GAME_MODE::PlayMenu;
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

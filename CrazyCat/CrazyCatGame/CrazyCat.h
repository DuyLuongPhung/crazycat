#pragma once

#ifndef CRAZYCAT_H
#define CRAZYCAT_H

#include "CONST.h"
#include "Game.h"
#include "Sprite.h"
#include "Character.h"
#include "QuadNode.h"
#include "Camera.h"
#include "Map.h"
#include "Text.h"
#include "Collision.h"
#include <time.h>
#include <d3dx9.h>
#include "GameMenu.h"
#include "FireBang.h"
#include "HelpMgt.h"
#include "PlayMapMgt.h"


enum GAME_MODE{
	PlayMap = 0,
	PlayMenu = 1,
	PlayHelp = 2
};


class CrazyCat : public CGame
{
public:
	GAME_MODE _g_currrent_mode;
	HelpMgt *_g_helpmgt;
	PlayMapMgt * _g_mapmgt;
	GameMenu * _g_menu;
	
public:
	CrazyCat(HINSTANCE hInstance, LPWSTR name, int mode, int is_fullscreen, int frame_rate);
	~CrazyCat();

protected:
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void Update(int Delta);

	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

private:
	void AddBomb();
};

#endif
